#include "mx/uniformBuffer.h"

#include "mx/shader.h"
#include <glad/gl.h>
#include <iostream>

mx::UniformBuffer::UniformBuffer(const mx::UniformBufferDesc& desc)
: m_attribs(desc.attributes), m_name(desc.name), m_stride(0)
{
    m_offsets = {};
    for(mx::AttributeType attrT : m_attribs) {
        m_offsets.push_back(m_stride);
        m_stride += mx::getAttributeTypeSize(attrT);
    }

    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_UNIFORM_BUFFER, m_ID);
    glBufferData(GL_UNIFORM_BUFFER, m_stride, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

mx::UniformBuffer::~UniformBuffer() {
    m_attribs.clear();
    if(m_ID != 0) {
        glDeleteBuffers(1, &m_ID);
    }
}

void mx::UniformBuffer::bind(mx::Shader* shader, int index)
{
    u32 loc = glGetUniformBlockIndex(shader->getProgramID(), m_name);
    glUniformBlockBinding(shader->getProgramID(), loc, index);
    glBindBufferBase(GL_UNIFORM_BUFFER, index, m_ID);
}

void mx::UniformBuffer::setAttributesValues(void* values)
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_ID);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, m_stride, values);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void mx::UniformBuffer::setAttributeValue(int index, void* value) 
{
    if(index >= m_offsets.size()) return;
    int off = m_offsets[index];
    int size = mx::getAttributeTypeSize(m_attribs[index]);
    
    glBindBuffer(GL_UNIFORM_BUFFER, m_ID);
    glBufferSubData(GL_UNIFORM_BUFFER, off, size, value);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}