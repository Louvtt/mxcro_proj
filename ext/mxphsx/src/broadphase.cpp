#include "mxphsx/broadphase.h"

#include "mxphsx/world.h"
#include "mxphsx/colliders.h"
#include "mxphsx/rigidbody.h"

mx::Broadphase::Broadphase(mx::World* _world)
: collided({}), world(_world)
{ }

bool mx::Broadphase::AABBvsAABB(mx::Rect _first, mx::Rect _second)
{
    // assuming the box are centered on their positions
    mx::vec2 extentA = _first.size;
    mx::vec2 extentB = _second.size;
    
    // maxA < minB || minB > maxB
    // SAT X
    if(_first.pos.x + extentA.x < _second.pos.x - extentB.x 
    || _first.pos.x - extentA.x > _second.pos.x + extentB.x) return false;
    // SAT Y
    if(_first.pos.y + extentA.y < _second.pos.y - extentB.y 
    || _first.pos.y - extentA.y > _second.pos.y + extentB.y) return false;
    return true;
}

void mx::Broadphase::step(float _delta) 
{
    auto bodies = world->getBodies();

    // get through in O(n²/2) => not cool for physics engine
    for(int i = 0; i < bodies.size(); ++i) {
        Rigidbody* first = bodies[i];
        mx::Rect firstAABB = first->getAABB();
        
        for(int j = i+1; j < bodies.size(); ++j) {
            Rigidbody* second = bodies[j];

            // if both static doesn't check collisions
            if(first->mode  == mx::RigidbodyMode::Static
            && second->mode == mx::RigidbodyMode::Static) continue;
            
            // same collision layer
            if(first->mask & second->mask != 0) {
                mx::Rect secondAABB = second->getAABB();
                // test aabb vs aabb
                if(AABBvsAABB(firstAABB, secondAABB)) {
                    // they could collide in narrow phase
                    collided.push_back(mx::Broadphase::Pair{
                        first, second
                    });
                }
            }
        }
    }
}