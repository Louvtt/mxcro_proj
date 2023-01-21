#ifndef _MX_SHAPEINSTANCE_H_
#define _MX_SHAPEINSTANCE_H_

#include <vector>
#include "../core/types.hpp"
#include "../maths/vec3.hpp"
#include "buffers.hpp"
#include "shape.hpp"

namespace mx
{

class Shader;
class ShapeGeometry;
class UniformBuffer;

class ShapeInstance
{
public:
    ShapeInstance(ShapeGeometry* shape, u32 reservedCount);
    ~ShapeInstance();
    
    void add(const vec3& pos);
    void add(const std::vector<vec3>& pos);
    void reset();

    void setCameraUBO(mx::UniformBuffer* cameraUbo);
    void draw(Shader* shader);

private:
    UniformBuffer* cameraUbo;
    VertexBuffer attributeBuffer;
    ShapeGeometry* shape;
    std::vector<vec3> positions;
};

} // namespace mx


#endif //_MX_SHAPEINSTANCE_H_