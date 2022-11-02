#include "mx/gfx/buffers.hpp"

#include <glad/gl.h>

#include <iostream>
#define LOG(msg) std::cout << msg << std::endl;

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

    currentCount = desc.count;
    if(desc.dynamic) currentCount = 0;
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
