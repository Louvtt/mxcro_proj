#include "mxphsx/rigidbody.h"

#include "mxphsx/colliders.h"

mx::Rigidbody::Rigidbody(const RigidbodyParams& _params) 
: pos(_params.pos), vel(mx::vec2{0.f, 0.f}), acc(mx::vec2{0.f, 0.f}),
  mass(_params.mass), inv_mass(1.f / _params.mass),
  collider(_params.collider), mask(_params.mask),
  mode(_params.mode)
{
    collider->parentPos = &pos; // fixture
}

void mx::Rigidbody::addForce(mx::vec2 _force, mx::ForceMode _mode)
{
    switch (_mode)
    {
    case mx::ForceMode::Force:
        acc += _force;
        break;
    case mx::ForceMode::Impulse:
        vel += _force * mass;
        break;
    default:
        break;
    }
}

mx::Rect mx::Rigidbody::getAABB() const 
{
    if(collider) {
        return collider->computeAABB();
    } else {
        return mx::Rect{
            pos,
            mx::vec2{0.f, 0.f}
        };
    }
}