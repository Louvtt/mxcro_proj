#ifndef _MX_SHAPEDRAWDATA_H_
#define _MX_SHAPEDRAWDATA_H_

#include "buffers.hpp"

namespace mx
{

struct ShapeDrawDataDesc
{
    VertexBuffer* vertexBuffer;
    IndexBuffer* indexBuffer  = nullptr;
    std::vector<AttributeType> attributes{};
};

class ShapeDrawData
{
public:
    ShapeDrawData(ShapeDrawDataDesc desc);
    ~ShapeDrawData();

    void bind();
    void unbind();
    void draw();
    ShapeDrawDataDesc getData() const;

private:
    ShapeDrawDataDesc desc;
    u32 ID = 0;
};

} // namespace mx

#endif //_MX_SHAPEDRAWDATA_H_