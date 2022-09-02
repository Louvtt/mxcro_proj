#ifndef _MX_BROADPHASE_H_
#define _MX_BROADPHASE_H_

#include "types.h"

namespace mx
{

class World;
class Rigidbody;

class Broadphase
{
public:
    Broadphase(mx::World* world);

    void step(float delta);

private:
    bool AABBvsAABB(mx::Rect first, mx::Rect second);

private:
    mx::World* world;

    struct Pair {
        Rigidbody* first;
        Rigidbody* second;
    };

    friend class Narrowphase;
    std::vector<Pair> collided{};
};

} // namespace phsx



#endif //_MX_BROADPHASE_H_