#include <mx/mxcro.h>
#include <mxphsx/mxphsx.h>

constexpr float bounciness = 1.f;

enum class ObjectShapeType {
    Box, Circle
};

class Object
{
public:
    Object(mx::vec2 _pos, float _size, ObjectShapeType _type, mx::World* _world, bool applyGravity = false)
    : type(_type), size(_size)
    {
        mx::RigidbodyParams p;
        p.mask = 0x1;
        p.mass = _size;
        p.mode = mx::RigidbodyMode::Dynamic;
        p.pos  = _pos;
        switch(_type) {
            case ObjectShapeType::Box:
                p.collider = new mx::AABBCollider({}, {_size, _size}, {bounciness});
                break;
            case ObjectShapeType::Circle:
                p.collider = new mx::CircleCollider({}, _size, {bounciness});
                break;
        }
        body = new mx::Rigidbody(p);
        if(applyGravity) body->addForce({0.f, -1.f});

        _world->addBody(body);
    }

    void render(mx::ContextRender* _renderer) {
        mx::Color col = (body->collided) ? mx::Color{1.f, 0.f, 0.f, 1.f} : mx::Color{1.f, 1.f, 1.f, 1.f};
        switch(type) {
            case ObjectShapeType::Box:
                _renderer->drawRect(body->pos, {size, size}, col);
                break;
            case ObjectShapeType::Circle:
                _renderer->drawPoint(body->pos, size, col);
                break;
            default:
                _renderer->drawPoint(body->pos, 1.f, {1.f, 0.f, 0.f, 1.f});
                break;
        }
    }

private:
    mx::Rigidbody* body;
    float size = 1.f;
    ObjectShapeType type;
};