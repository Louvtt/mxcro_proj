#ifndef _MX_COLLIDERS_H_
#define _MX_COLLIDERS_H_

#include "math.h"
#include "types.h"
#include <vector>

namespace mx {

/* Material table
| Name       | Density | Resitution |
| Rock       |   0.6   |     0.1    |
| Wood       |   0.3   |     0.2    |
| Metal      |   1.2   |     0.05   |
| BouncyBall |   0.3   |     0.8    |
| SuperBall  |   0.3   |     0.95   |
| Pillow     |   0.1   |     0.2    |
| Static     |   0.0   |     0.4    |
*/

/* Represent a physic material*/
struct PhysicMaterial {
    float bounciness = 0.f;   // coeff of restitution  e
    float friction   = 0.f;   // static friction       Fn
    float dynfriction = 0.f;  // dynamic friction      Ff
};


///////////////////////
// colliders

class BaseCollider 
{
public:
    virtual ~BaseCollider() = default;

    enum class Type {
        Unknown,
        AABB,
        Circle,
        Custom,
        _Last
    };

    mx::vec2& pos;
    Type type = Type::Unknown;
    PhysicMaterial mat;

    virtual mx::Rect computeAABB() const = 0;
    mx::vec2 getPos() const;
    // get vertices for debug purpose
    // virtual std::vector<mx::vec2> getVertices() const = 0;

protected:
    mx::vec2* parentPos;
    friend class Rigidbody;

    BaseCollider(mx::vec2 pos, PhysicMaterial mat, Type type);
};

// AABB
class AABBCollider
: public BaseCollider
{
public:
    AABBCollider(mx::vec2 pos, mx::vec2 size, PhysicMaterial mat = {});
    ~AABBCollider();
    mx::vec2 size;

    mx::Rect computeAABB() const override;
    // std::vector<mx::vec2> getVertices() const override;
};
// Circle collider
class CircleCollider
: public BaseCollider
{
public:
    CircleCollider(mx::vec2 pos, float radius, PhysicMaterial mat = {});
    ~CircleCollider();
    float radius;

    mx::Rect computeAABB() const override;
    // std::vector<mx::vec2> getVertices() const override;
};

class ShapeCollider
: public BaseCollider
{
public:
    ShapeCollider(mx::vec2 pos, std::vector<mx::vec2> vertices, PhysicMaterial mat = {});
    ~ShapeCollider();

    mx::Rect computeAABB() const override;
    // std::vector<mx::vec2> getVertices() const override;

private:
    std::vector<mx::vec2> vertices;
    mx::vec2 size;
};

} // namespace mx

#endif //_PHSX_COLLIDERS_H_