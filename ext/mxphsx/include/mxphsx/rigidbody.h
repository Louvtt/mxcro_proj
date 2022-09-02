#ifndef _MX_RIGIDBODY_H_
#define _MX_RIGIDBODY_H_

#include "types.h"
#include "math.h"

namespace mx {

class BaseCollider;

using CollisionLayerMask = unsigned long long; // allow 32 masks
constexpr int COLLISION_MASK_COUNT = 4 * sizeof(CollisionLayerMask);

enum class RigidbodyMode {
    Static,
    Dynamic,
    Kinematic
};

enum class ForceMode {
    Force,
    Impulse
};

struct RigidbodyParams {
    mx::vec2 pos            = {};
    BaseCollider* collider  = nullptr;
    float mass              = 1.f;
    RigidbodyMode mode      = RigidbodyMode::Dynamic;
    CollisionLayerMask mask = 0; // no mask
};

struct Rigidbody
{
    Rigidbody(const RigidbodyParams& params);

    // methods
    void addForce(mx::vec2 force, ForceMode mode = ForceMode::Force);

    // transform
    mx::vec2 pos{};

    // torque
    float angle = 0.f; // rad
    // float angularVelocity;
    
    // dynamics
    RigidbodyMode mode;
    mx::vec2 vel{};
    mx::vec2 acc{};

    // mass
    float mass        = 1.f;
    float inv_mass    = 1.f;
    // inertia
    // float inertia     = 1.f;
    // float inv_inertia = 1.f;

    // collision
    BaseCollider* collider = nullptr;
    CollisionLayerMask mask;
    Rect getAABB() const;
    bool collided = false;
};

}

#endif //_PHSX_RIGIDBODY_H_