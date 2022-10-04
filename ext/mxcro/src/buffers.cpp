#include "mx/buffers.h"

#include <glad/gl.h>

#include <iostream>
#define LOG(msg) std::cout << msg << std::endl;


static void bindAttr(std::vector<mx::AttributeType> _attributes, u32 stride)
{
    size_t offset = 0;
    u32 idx       = 0;

    using VA = mx::AttributeType;
    for(const auto& attr : _attributes)
    {
        glEnableVertexAttribArray(idx);
        switch(attr)
        {
            // INT
            case VA::Int:
                glVertexAttribPointer(idx, 1, GL_INT, GL_FALSE, stride, (void*)(offset));
                offset += mx::getAttributeTypeSize(attr);
                break;

            // FLOATS
            case VA::Float:
                glVertexAttribPointer(idx, 1, GL_FLOAT, GL_FALSE, stride, (void*)(offset));
                offset += mx::getAttributeTypeSize(attr);
                break;
            case VA::Float2:
                glVertexAttribPointer(idx, 2, GL_FLOAT, GL_FALSE, stride, (void*)(offset));
                offset += mx::getAttributeTypeSize(attr);
                break;
            case VA::Float3:
                glVertexAttribPointer(idx, 3, GL_FLOAT, GL_FALSE, stride, (void*)(offset));
                offset += mx::getAttributeTypeSize(attr);
                break;
            case VA::Float4:
                glVertexAttribPointer(idx, 4, GL_FLOAT, GL_FALSE, stride, (void*)(offset));
                offset += mx::getAttributeTypeSize(attr);
                break;
            default:
                break;
        }
        ++idx;
    }
}

// DRAW DATA
mx::ShapeDrawData::ShapeDrawData(ShapeDrawDataDesc _desc)
: desc(_desc)
{
    glCreateVertexArrays(1, &ID);
    glBindVertexArray(ID);

    desc.vertexBuffer->bind();
    u32 stride = desc.vertexBuffer->getDesc().dataSize;
    bindAttr(desc.attributes, stride);

    if(desc.indexBuffer)
        desc.indexBuffer->bind();
    
    glBindVertexArray(0);
}

mx::ShapeDrawData::~ShapeDrawData()
{
    glBindVertexArray(0);
    if(ID != 0) {
        glDeleteVertexArrays(1, &ID);
    }
}

void mx::ShapeDrawData::bind()
{
    glBindVertexArray(ID);
}
void mx::ShapeDrawData::unbind()
{
    glBindVertexArray(0);
}
mx::ShapeDrawDataDesc mx::ShapeDrawData::getData() const
{
    return desc;
}
void mx::ShapeDrawData::draw()
{
    glBindVertexArray(ID);
    if(desc.indexBuffer) {
        u32 count = desc.vertexBuffer->getCount() * 6 / 4;
        desc.indexBuffer->bind();
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    } else {
        u32 count = desc.vertexBuffer->getCount();
        desc.vertexBuffer->bind();
        glDrawArrays(GL_TRIANGLES, 0, count);
    }
    glBindVertexArray(0);
}


// BUFFER

mx::Buffer::Buffer(BufferDesc _desc)
: desc(_desc)
{}

mx::Buffer::~Buffer() 
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    if(m_Id != 0) {
        glDeleteBuffers(1, &m_Id);
    } 
}

void mx::Buffer::pushData(void* _data, u32 _count)
{
    if(currentCount >= desc.count) return; // reach maximum
    if(!desc.dynamic) return; // not dynamic buffer

    glBindBuffer(GL_ARRAY_BUFFER, m_Id);
    glBufferSubData(GL_ARRAY_BUFFER, currentCount * desc.dataSize, desc.dataSize * _count, _data);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    currentCount += _count;

}
void mx::Buffer::reset()
{
    if(!desc.dynamic) return;

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    currentCount = 0;
}


mx::BufferDesc mx::Buffer::getDesc() const
{
    return desc;
}

u32 mx::Buffer::getCount() const
{
    return currentCount;
}

mx::VertexBuffer::VertexBuffer(mx::BufferDesc desc)
: mx::Buffer(desc)
{
    LOG("Creating buffer: " << ((desc.dynamic) ? "GL_DYNAMIC_DRAW" : "GL_STATIC_DRAW") << " - VERTEX");
    glGenBuffers(1, &m_Id);
    glBindBuffer(GL_ARRAY_BUFFER, m_Id);
    glBufferData(
        GL_ARRAY_BUFFER, 
        desc.count * desc.dataSize,
        desc.data, 
        (desc.dynamic) ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW
    );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void mx::VertexBuffer::bind() 
{
    glBindBuffer(GL_ARRAY_BUFFER, m_Id);
}
void mx::VertexBuffer::unbind() 
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

mx::IndexBuffer::IndexBuffer(mx::BufferDesc desc)
: mx::Buffer(desc)
{
    LOG("Creating buffer: " << ((desc.dynamic) ? "GL_DYNAMIC_DRAW" : "GL_STATIC_DRAW") << " - INDEX");
    glGenBuffers(1, &m_Id);
    glBindBuffer(GL_ARRAY_BUFFER, m_Id);
    glBufferData(
        GL_ARRAY_BUFFER, 
        desc.count * desc.dataSize,
        desc.data, 
        (desc.dynamic) ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW
    );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void mx::IndexBuffer::bind() 
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
}
void mx::IndexBuffer::unbind() 
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
