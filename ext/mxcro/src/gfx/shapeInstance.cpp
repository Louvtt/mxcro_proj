#include "mx/gfx/shapeInstance.hpp"

#include "mx/gfx/shapeDrawData.hpp"
#include "mx/gfx/uniformBuffer.hpp"
#include "mx/gfx/shader.hpp"

#include <glad/gl.h>

// SHAPE INSTANCE
mx::ShapeInstance::ShapeInstance(ShapeDrawData* _shape, Shader* _shader, u32 _reservedCount)
: shader(_shader),
shape(_shape),
attributeBuffer(mx::BufferDesc{
    _reservedCount,
    true,
    sizeof(mx::vec3),
    nullptr
})
{
    positions.reserve(_reservedCount);
    
    shape->bind();
    u32 attributeCount = shape->getData().attributes.size();
    attributeBuffer.bind();
    glEnableVertexAttribArray(attributeCount);
    glVertexAttribPointer(attributeCount, 3, GL_FLOAT, GL_FALSE, sizeof(mx::vec3), 0);
    glVertexAttribDivisor(attributeCount, 1);
    
}
void mx::ShapeInstance::add(const vec3& pos)
{
    positions.push_back(pos);
}

void mx::ShapeInstance::draw(mx::UniformBuffer* _cameraUbo)
{
    _cameraUbo->bind(shader);

    shader->bind();
    u32 vertexCount = shape->getData().vertexBuffer->getCount();
    attributeBuffer.pushData((void*)positions.data(), positions.size());
    glDrawArraysInstanced(GL_TRIANGLES, 0, vertexCount, positions.size());
    shader->unbind();

    // reset ?
    // positions.clear();
}