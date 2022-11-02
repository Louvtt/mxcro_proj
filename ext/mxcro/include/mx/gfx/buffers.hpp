#ifndef _MX_BUFFERS_H_
#define _MX_BUFFERS_H_

#include <vector>
#include "../core/types.hpp"
#include "renderAttributeTypes.hpp"

namespace mx
{

// SubBuffer

struct BufferDesc
{
    u32 count = 0;
    bool dynamic = false;
    size_t dataSize = 1;
    void* data = nullptr;
};

class Buffer
{
public:
    Buffer(BufferDesc desc);
    virtual ~Buffer();

    virtual void bind() = 0;
    virtual void unbind() = 0;

    void pushData(void* data, u32 count);
    void reset();

    BufferDesc getDesc() const;
    u32 getCount() const;

protected:
    BufferDesc desc;
    u32 currentCount = 0;
    unsigned int m_Id = 0;
};

///////////////////////////////////
// BUFFER TYPES CLASSES

class VertexBuffer
: public Buffer
{
public:
    VertexBuffer(BufferDesc desc);

    void bind() override;
    void unbind() override;
};

class IndexBuffer
: public Buffer
{
public:
    IndexBuffer(BufferDesc desc);

    void bind() override;
    void unbind() override;
};

} // namespace mx


#endif //_MX_BUFFERS_H_