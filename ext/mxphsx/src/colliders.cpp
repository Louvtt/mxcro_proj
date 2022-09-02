#include "mxphsx/colliders.h"

// INITIALISERS

mx::BaseCollider::BaseCollider(mx::vec2 _pos, mx::PhysicMaterial _mat, mx::BaseCollider::Type _type)
: pos(_pos), mat(_mat), type(_type)
{ }

mx::AABBCollider::AABBCollider(mx::vec2 _pos, mx::vec2 _size, mx::PhysicMaterial _mat)
: mx::BaseCollider(_pos, _mat, mx::BaseCollider::Type::AABB),
size(_size)
{ }
mx::AABBCollider::~AABBCollider() {}

mx::CircleCollider::CircleCollider(mx::vec2 _pos, float _radius, mx::PhysicMaterial _mat)
: mx::BaseCollider(_pos, _mat, mx::BaseCollider::Type::Circle),
radius(_radius)
{ }
mx::CircleCollider::~CircleCollider() {}

mx::ShapeCollider::ShapeCollider(mx::vec2 _pos, std::vector<mx::vec2> _vertices, mx::PhysicMaterial _mat)
: mx::BaseCollider::BaseCollider(_pos, _mat, mx::BaseCollider::Type::Custom),
vertices(_vertices)
{
    // find size
    mx::vec2 min = vertices[0], max = vertices[0];
    for(const auto& v : vertices)
    {
        min.x = (min.x > v.x)? v.x : min.x;
        min.y = (min.x > v.x)? v.y : min.y;
        max.x = (min.x < v.x)? v.x : max.x;
        max.y = (min.x < v.x)? v.y : max.y;
    }
    size = max - min;
}
mx::ShapeCollider::~ShapeCollider() 
{
    vertices.clear();
}

// compute AABBS

mx::Rect mx::AABBCollider::computeAABB() const
{
    return mx::Rect{
        pos + (*parentPos),
        size
    };
}

mx::Rect mx::CircleCollider::computeAABB() const
{
    float diameter = radius * 2.f;
    return mx::Rect{
        pos + (*parentPos),
        {diameter, diameter}
    };
}

mx::Rect mx::ShapeCollider::computeAABB() const
{
    return mx::Rect{
        pos + (*parentPos),
        size
    };
}

// Colliders general methods

mx::vec2 mx::BaseCollider::getPos() const
{
    if(!parentPos)
        return pos;
    
    return pos + (*parentPos);
}