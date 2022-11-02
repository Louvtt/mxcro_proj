#include "mx/gfx/shapeDrawData.hpp"

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