#include "mxphsx/narrowphase.h"

#include "mxphsx/rigidbody.h"
#include "mxphsx/colliders.h"
#include "mxphsx/broadphase.h"

#include <math.h>

// SOLVERS

static bool computeAABBManifold(mx::Manifold* _m)
{ 
    mx::AABBCollider* first  = dynamic_cast<mx::AABBCollider*>(_m->first->collider);
    mx::AABBCollider* second = dynamic_cast<mx::AABBCollider*>(_m->second->collider);
    
    // norm
    mx::vec2 n = second->getPos() - first->getPos();
    
    // SAT x axis
    float extent1_x =  first->size.x * .5f;
    float extent2_x = second->size.x * .5f;
    float x_overlap = extent1_x + extent2_x - abs(n.x);
    if(x_overlap > 0) {
        // SAT y axis 
        float extent1_y =  first->size.y * .5f;
        float extent2_y = second->size.y * .5f;
        float y_overlap = extent1_y + extent2_y - abs(n.y);
        if(y_overlap > 0) {
            // find least depth penetration axis
            if(x_overlap < y_overlap) {
                _m->normal = (n.x > 0) ? mx::vec2{-1, 0} : mx::vec2{-1, 0};
                _m->depth  = x_overlap;
            }
            else {
                _m->normal = (n.y > 0) ? mx::vec2{0, -1} : mx::vec2{0, 1};
                _m->depth  = y_overlap;
            }

            return true;
        }
    }

    return false;
}

static bool computeAABBCircleManifold(mx::Manifold* _m)
{ 
    mx::AABBCollider*   first  = nullptr;
    mx::CircleCollider* second = nullptr;
    bool invert = false;
    if(_m->first->collider->type == mx::BaseCollider::Type::AABB) {
        first  = dynamic_cast<mx::AABBCollider  *>(_m->first->collider);
        second = dynamic_cast<mx::CircleCollider*>(_m->second->collider);
    } else {
        first  = dynamic_cast<mx::AABBCollider  *>(_m->second->collider);
        second = dynamic_cast<mx::CircleCollider*>(_m->first->collider);
        invert = true;
    }

    mx::vec2 n = _m->second->pos - _m->first->pos;
    mx::vec2 closest = mx::vec2{n.x, n.y};
    mx::vec2 extent = first->size * .5f;
    // clamp to edge
    closest.x = mx::clamp(closest.x, -extent.x, extent.x);
    closest.y = mx::clamp(closest.y, -extent.y, extent.y);

    bool inside = false;

    if(n.x == closest.x && n.y == closest.y) // circle in AABB
    {
        inside = true;
        
        // find closest axis
        if(abs(n.x) < abs(n.y)) {
            closest.x = (closest.x < 0) ? -extent.x : extent.x; 
        } else {
            closest.y = (closest.y < 0) ? -extent.y : extent.y; 
        }
    }

    mx::vec2 norm = n - closest;
    float d = norm.sqrLength();
    float r = second->radius;

    // radius less than distance to closest point on aabb => outside
    if(r * r < d && !inside) return false;

    d = sqrt(d);

    _m->normal = (inside) ? -norm.normalized() : norm.normalized();
    _m->depth  = r - d; 

    if(invert) {
        _m->normal = -_m->normal;
        _m->depth  = -_m->depth;
    }

    return true; 
}

static bool computeCircleManifold(mx::Manifold* _m)
{ 
    mx::CircleCollider* first  = dynamic_cast<mx::CircleCollider*>(_m->first->collider);
    mx::CircleCollider* second = dynamic_cast<mx::CircleCollider*>(_m->second->collider);

    float r = first->radius + second->radius;
    float sqrR = r * r;
    mx::vec2 p = (second->pos - first->pos);
    float sqrd = p.sqrLength();
    if(sqrR < sqrd) return false;

    float d = sqrt(sqrd);
    if(d != 0) {
        _m->depth  = r - d;
        _m->normal = p.normalized();
    }

    // same position
    else {
        _m->depth = first->radius;
        _m->normal = mx::vec2{0, 1.f};
    }

    return true;
}

using CT = mx::BaseCollider::Type;
using TP = mx::TypePair;

std::unordered_map<TP, std::function<bool(mx::Manifold*)>>
mx::Narrowphase::solvers = {
    // AABB vs AABB
    {TP{CT::AABB, CT::AABB}, computeAABBManifold },
    // AABB vs Circle
    {TP{CT::AABB, CT::Circle}, computeAABBCircleManifold },
    // Circle vs Cirlce
    {TP{CT::Circle, CT::Circle}, computeCircleManifold }
};

// NARROW PHASE

mx::Narrowphase::Narrowphase(mx::Broadphase* _broadphase)
: broadphase(_broadphase)
{ }

void mx::Narrowphase::impulseResolution(Manifold _m)
{
    // impulse resolve
    mx::vec2 rv  = (_m.second->vel - _m.first->vel).normalized();
    mx::vec2 dir = (_m.second->pos - _m.first->pos).normalized();
    float nvel   = rv.dot(dir);

    if(nvel == 0.f) return;

    // restitution
    float e = fmin(_m.first->collider->mat.bounciness, _m.second->collider->mat.bounciness);

    // impulse scalar
    float j = nvel * -(1.f + e);
    j /= _m.first->inv_mass + _m.second->inv_mass;

    // apply impulse with mass ratio
    mx::vec2 impulse = _m.normal * j;

    float mass_sum = 1.f / (_m.first->mass + _m.second->mass);
    float ratio = _m.first->mass * mass_sum;
    _m.first->vel  += impulse * ratio;
    ratio = _m.second->mass * mass_sum;
    _m.second->vel -= impulse * ratio;

    ///////////////////////
    // Friction
    // rv  = (_m.second->vel - _m.first->vel).normalized();
    // mx::vec2 tangent = (rv - dir * rv.dot(dir)).normalized();
    // float jt = -tangent.dot(rv);
    // jt /= _m.first->inv_mass + _m.second->inv_mass;

    // float mu = sqrt(
    //     _m.first->collider->mat.friction  * _m.first->collider->mat.friction 
    // +   _m.second->collider->mat.friction * _m.second->collider->mat.friction 
    // );

    // mx::vec2 frictionImpulse{};
    // if(abs(jt) < j * mu) {
    //     frictionImpulse = tangent * jt;
    // } else {
    //     float dynamicFriction = sqrt(
    //         _m.first->collider->mat.dynfriction  * _m.first->collider->mat.dynfriction 
    //     +   _m.second->collider->mat.dynfriction * _m.second->collider->mat.dynfriction 
    //     );
    //     frictionImpulse = tangent * -j * dynamicFriction;
    // }

    // _m.first->vel  -= frictionImpulse * _m.first->inv_mass;
    // _m.second->vel += frictionImpulse * _m.second->inv_mass;
}

void mx::Narrowphase::positionalCorrection(Manifold _m)
{
    const float percent = 0.2;    // usually 20% to 80%  (how much we try to fix)
    const float slop    = 0.1;   // usually 0.01 to 0.1 (threshold of displacement amount)
    mx::vec2 correction = _m.normal * (fmax( _m.depth - slop, 0.0f ) / (_m.first->inv_mass + _m.second->inv_mass) * percent);
    
    if(_m.first->mode  != mx::RigidbodyMode::Static) _m.first->pos  += correction * _m.first->inv_mass;
    if(_m.second->mode != mx::RigidbodyMode::Static) _m.second->pos -= correction * _m.second->inv_mass;
}

void mx::Narrowphase::step(float _delta)
{
    // get data
    auto pairs = broadphase->collided; 
    for(const auto& [first, second] : pairs)
    {
        TP typePair = {first->collider->type, second->collider->type};
        Manifold m;
        m.first  = first;
        m.second = second;
        
        auto solver = mx::Narrowphase::solvers.find(typePair);
        if(solver != mx::Narrowphase::solvers.end()) {
            if(solver->second(&m)) {
                first->collided  = true;
                second->collided = true;

                impulseResolution(m);
                positionalCorrection(m);
            }
        }
    }
}


////////////////////////////////////
// TYPE PAIR
bool mx::operator==(const mx::TypePair& _a, const mx::TypePair& _b)
{
    return (
        (_a.typeA == _b.typeA && _a.typeB == _b.typeB)
        ||
        (_a.typeB == _b.typeA && _a.typeA == _b.typeB)
    );
}

