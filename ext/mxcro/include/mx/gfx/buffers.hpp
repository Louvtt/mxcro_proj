#ifndef _MX_BUFFERS_H_
#define _MX_BUFFERS_H_

#include <vector>
#include "../core/types.hpp"
#include "renderAttributeTypes.hpp"

namespace mx
{

// SubBuffer

/**
 * @brief Buffer description params
 */
struct BufferDesc
{
    /** number of element in the buffer */
    u32 count = 0;
    /** Is the buffer dynamic or static */
    bool dynamic = false;
    /** Size of each element in the buffer */
    size_t dataSize = 1;
    /** Data in the buffer (ignore in case the buffer is dynamic)*/
    void* data = nullptr;
};

/**
 * @brief Represent a OpenGL Buffer
 */
class Buffer
{
public:
    /**
     * @brief Construct a new Buffer
     * @param desc Decription of the buffer
     */
    Buffer(BufferDesc desc);
    /**
     * @brief Destroy the Buffer and delete the opengl object
     */
    virtual ~Buffer();

    /**
     * @brief Bind the buffer
     */
    virtual void bind() = 0;
    /**
     * @brief Unbind the buffer
     */
    virtual void unbind() = 0;

    /**
     * @brief [For dynamic buffer] Send data to the buffer opengl object
     * @param data data to send
     * @param count number of elements to push
     */
    void pushData(void* data, u32 count);
    /**
     * @brief [For dynamic buffer] Reset data offset and element count
     */
    void reset();

    /**
     * @brief Get the description of the buffer
     * @return BufferDesc the description of the buffer
     */
    BufferDesc getDesc() const;
    /**
     * @brief Get the current count of elements in the buffer
     * @return u32 the current count of elements
     */
    u32 getCount() const;

protected:
    BufferDesc desc;
    u32 currentCount = 0;
    unsigned int m_Id = 0;
};

///////////////////////////////////
// BUFFER TYPES CLASSES

/**
 * @brief Represent a VertexBufferObject
 */
class VertexBuffer
: public Buffer
{
public:
    /**
     * @brief Construct a new Vertex Buffer
     * @param desc Decription of the buffer
     */
    VertexBuffer(BufferDesc desc);

    /**
     * @brief Bind buffer to GL_VERTEX_BUFFER_ARRAY
     */
    void bind() override;
    /**
     * @brief Unbind buffer
     */
    void unbind() override;
};

class IndexBuffer
: public Buffer
{
public:
    /**
     * @brief Construct a new Index Buffer
     * @param desc Decription of the buffer
     */
    IndexBuffer(BufferDesc desc);

    /**
     * @brief Bind buffer to GL_ELEMENT_BUFFER_ARRAY
     */
    void bind() override;
    /**
     * @brief Unbind buffer
     */
    void unbind() override;
};

} // namespace mx


#endif //_MX_BUFFERS_H_