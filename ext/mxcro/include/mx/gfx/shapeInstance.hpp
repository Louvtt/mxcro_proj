#ifndef _MX_SHAPEINSTANCE_H_
#define _MX_SHAPEINSTANCE_H_

#include <vector>
#include "../core/types.hpp"
#include "../maths/vec3.hpp"
#include "buffers.hpp"

namespace mx
{

class Shader;
class ShapeDrawData;
class UniformBuffer;

class ShapeInstance
{
public:
    ShapeInstance(ShapeDrawData* shape, Shader* shader, u32 reservedCount);
    void add(const vec3& pos);

    void draw(mx::UniformBuffer* cameraUbo);
private:
    VertexBuffer attributeBuffer;
    ShapeDrawData* shape;
    Shader* shader;
    std::vector<vec3> positions;
};

} // namespace mx


#endif //_MX_SHAPEINSTANCE_H_