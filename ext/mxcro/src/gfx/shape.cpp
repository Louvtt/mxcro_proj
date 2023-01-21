#include "mx/gfx/shape.hpp"

#include <glad/gl.h>

mx::Shape::Shape()
: rendererID(0), attributeCount(0) 
{
    glGenVertexArrays(1, &rendererID);
}

void mx::Shape::internalDestroy() 
{
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &rendererID);
}

void mx::Shape::setAttributes(std::vector<mx::AttributeType> _attributes, u32 _vertexDataSize)
{
    attributeCount = _attributes.size();
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
                glVertexAttribPointer(idx, 1, GL_INT, GL_FALSE, _vertexDataSize, (void*)(offset));
                offset += mx::getAttributeTypeSize(attr);
                break;

            // FLOATS
            case VA::Float:
                glVertexAttribPointer(idx, 1, GL_FLOAT, GL_FALSE, _vertexDataSize, (void*)(offset));
                offset += mx::getAttributeTypeSize(attr);
                break;
            case VA::Float2:
                glVertexAttribPointer(idx, 2, GL_FLOAT, GL_FALSE, _vertexDataSize, (void*)(offset));
                offset += mx::getAttributeTypeSize(attr);
                break;
            case VA::Float3:
                glVertexAttribPointer(idx, 3, GL_FLOAT, GL_FALSE, _vertexDataSize, (void*)(offset));
                offset += mx::getAttributeTypeSize(attr);
                break;
            case VA::Float4:
                glVertexAttribPointer(idx, 4, GL_FLOAT, GL_FALSE, _vertexDataSize, (void*)(offset));
                offset += mx::getAttributeTypeSize(attr);
                break;
            default:
                break;
        }
        ++idx;
    }
}

void mx::Shape::bind()
{
    glBindVertexArray(rendererID);
}

void mx::Shape::unbind()
{
    glBindVertexArray(0);
}

u32 mx::Shape::getRendererID() const 
{
    return rendererID;
}

u32 mx::Shape::getAttributeCount() const 
{
    return attributeCount;
}