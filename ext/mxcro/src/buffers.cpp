#include "mx/buffers.h"

#include <glad/gl.h>

#include <iostream>
#define LOG(msg) std::cout << msg << std::endl;

int bufferTypeToGLenum(mx::BufferType _type)
{
    switch(_type) {
        case mx::BufferType::Vertex:
        case mx::BufferType::DynamicVertex:
            return GL_ARRAY_BUFFER;
        case mx::BufferType::Index:
        case mx::BufferType::DynamicIndex:
            return GL_ELEMENT_ARRAY_BUFFER;
    }
    return GL_ARRAY_BUFFER;
};


static void bindAttr(std::vector<mx::ShapeAttribute> _attributes, int stride)
{
    size_t offset = 0;
    u32 idx       = 0;

    using VA = mx::ShapeAttribute;
    for(const auto& attr : _attributes)
    {
        glEnableVertexAttribArray(idx);
        switch(attr)
        {
            // INT
            case VA::Int:
                glVertexAttribPointer(idx, 1, GL_INT, GL_FALSE, stride, (void*)(offset));
                offset += 1 * sizeof(int);
                break;

            // FLOATS
            case VA::Float:
                glVertexAttribPointer(idx, 1, GL_FLOAT, GL_FALSE, stride, (void*)(offset));
                offset += 1 * sizeof(float);
                break;
            case VA::Float2:
                glVertexAttribPointer(idx, 2, GL_FLOAT, GL_FALSE, stride, (void*)(offset));
                offset += 2 * sizeof(float);
                break;
            case VA::Float3:
                glVertexAttribPointer(idx, 3, GL_FLOAT, GL_FALSE, stride, (void*)(offset));
                offset += 3 * sizeof(float);
                break;
            case VA::Float4:
                glVertexAttribPointer(idx, 4, GL_FLOAT, GL_FALSE, stride, (void*)(offset));
                offset += 4 * sizeof(float);
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
    int stride = desc.vertexBuffer->getDesc().dataSize;
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
{
    LOG("Creating buffer: " << ((((int)desc.type >> 2) != 0) ? "GL_DYNAMIC_DRAW" : "GL_STATIC_DRAW") << " - " << ((((int)desc.type & 0x3) == 0x1) ? "VERTEX" : "INDEX"));
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(
        GL_ARRAY_BUFFER, 
        desc.count * desc.dataSize,
        desc.data, 
        (((int)desc.type >> 2) != 0) ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW
    );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
mx::Buffer::~Buffer() 
{
    glBindVertexArray(0);
    if(ID != 0) {
        glDeleteBuffers(1, &ID);
    } 
}

void mx::Buffer::bind() 
{
    glBindBuffer(bufferTypeToGLenum(desc.type), ID);
}
void mx::Buffer::unbind() 
{
    glBindBuffer(bufferTypeToGLenum(desc.type), 0);
}

void mx::Buffer::pushData(void* _data, u32 _count)
{
    if(currentCount >= desc.count) return; // reach maximum
    if(((int)desc.type >> 2) == 0) return; // not dynamic buffer

    glBindBuffer(bufferTypeToGLenum(desc.type), ID);
    glBufferSubData(GL_ARRAY_BUFFER, currentCount * desc.dataSize, desc.dataSize * _count, _data);

    currentCount += _count;

}
void mx::Buffer::reset()
{
    if(((int)desc.type >> 2) == 0) return;

    glBindBuffer(bufferTypeToGLenum(desc.type), 0);
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