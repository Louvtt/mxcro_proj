#ifndef _MX_SHAPEGEOMETRY_H_
#define _MX_SHAPEGEOMETRY_H_

#include "shape.hpp"
#include "../core/types.hpp"
#include "renderAttributeTypes.hpp"
#include <string>
#include <vector>

namespace mx
{

class IndexBuffer;
class VertexBuffer;

struct ShapeGeometryDesc {
    mx::VertexBuffer* vertexBuffer;
    mx::IndexBuffer* indexBuffer  = nullptr;
    std::vector<mx::AttributeType> attributes{};
};

class ShapeGeometry
: public Shape
{
public:
    ShapeGeometry(const ShapeGeometryDesc& desc);
    ~ShapeGeometry();

    void draw(Shader* shader) override;

    VertexBuffer* getVertexBuffer() const;
    IndexBuffer*  getIndexBuffer()  const;

    // static ShapeGeometry loadFromFile(const std::string& path);

private:
    VertexBuffer* vertexBuffer;
    IndexBuffer* indexBuffer;
};

} // namespace mx


#endif //_MX_SHAPEGEOMETRY_H_