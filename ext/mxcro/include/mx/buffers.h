#ifndef _MX_BUFFERS_H_
#define _MX_BUFFERS_H_

#include <vector>
#include "types.h"

namespace mx
{

enum class BufferType
{
    Vertex        = 0x1, // VBO
    Index         = 0x2, // EBO
    DynamicVertex = 0x5, // VBO
    DynamicIndex  = 0x6, // EBO
};

// SubBuffer

struct BufferDesc
{
    BufferType type = BufferType::Vertex;
    u32 count = 0;
    size_t dataSize = 1;
    void* data = nullptr;
};

class Buffer
{
public:
    Buffer(BufferDesc desc);
    ~Buffer();

    void bind();
    void unbind();

    void pushData(void* data, u32 count);
    void reset();

    BufferDesc getDesc() const;
    u32 getCount() const;
private:
    BufferDesc desc;
    u32 currentCount = 0;
    unsigned int ID = 0;
};

///////////////////////////////////

enum class ShapeAttribute
{
    Float,
    Float2,
    Float3,
    Float4,
    Int,
    
    RGBA  = Float4,
    Pos2D = Float2,
    Pos3D = Float3, 
    Tex2D = Int,
    TexCoords2D = Float2
};

// Shape

struct ShapeDrawDataDesc
{
    Buffer* vertexBuffer;
    Buffer* indexBuffer  = nullptr;
    std::vector<ShapeAttribute> attributes{};
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


#endif //_MX_BUFFERS_H_