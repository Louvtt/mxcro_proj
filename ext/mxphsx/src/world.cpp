#include "mxphsx/world.h"

#include "mxphsx/narrowphase.h"
#include "mxphsx/broadphase.h"

#include "mxphsx/rigidbody.h"

constexpr float max_delta = 1.f / 60.f;

mx::World::World()
{
    broadphase  = new mx::Broadphase(this);
    narrowphase = new mx::Narrowphase(broadphase); 
    bodies.reserve(1024);
}

void mx::World::addBody(mx::Rigidbody* _body)
{
    bodies.push_back(_body);
}

void mx::World::step(float _delta)
{
    // avoid large gap in delta that result in tunnelling
    float step = (_delta > max_delta) ? max_delta : _delta;
    for(float acc = 0; acc < _delta; acc += step) {
        // update each body in O(n)
        for(const auto& body : bodies) {
            // avoid
            if(body->mode == mx::RigidbodyMode::Static) continue;

            body->vel += body->acc * step * body->mass;
            body->pos += body->vel * step;
            body->collided = false;
        }
        
        // collision check
        broadphase->step(step);
        narrowphase->step(step);
    }
}

std::vector<mx::Rigidbody*>
mx::World::getBodies() const
{
    return bodies;
}