#ifndef _MX_WORLD_H_
#define _MX_WORLD_H_

#include <vector>


namespace mx
{
    
class Rigidbody;
class Narrowphase;
class Broadphase;

class World
{
public:
    World();

    void addBody(Rigidbody* body);

    void step(float delta);

    std::vector<Rigidbody*> getBodies() const;
private:
    Broadphase*  broadphase;
    Narrowphase* narrowphase;

    std::vector<Rigidbody*> bodies; // need to rework into dynamic tree
};

} // namespace phsx


#endif //_PHSX_WORLD_H_