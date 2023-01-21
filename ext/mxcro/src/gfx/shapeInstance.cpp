#include "mx/gfx/shapeInstance.hpp"

#include "mx/gfx/shapeGeometry.hpp"
#include "mx/gfx/uniformBuffer.hpp"
#include "mx/gfx/shader.hpp"

#include <glad/gl.h>
#include "mx/gfx/shapeGeometry.hpp"

// SHAPE INSTANCE
mx::ShapeInstance::ShapeInstance(ShapeGeometry* _shape, u32 _reservedCount)
: shape(_shape),
attributeBuffer(mx::BufferDesc{
    _reservedCount,
    true,
    sizeof(mx::vec3),
    nullptr
})
{
    positions.reserve(_reservedCount);
    
    shape->bind();
    u32 attributeCount = shape->getAttributeCount();
    attributeBuffer.bind();
    glEnableVertexAttribArray(attributeCount);
    glVertexAttribPointer(attributeCount, 3, GL_FLOAT, GL_FALSE, sizeof(mx::vec3), 0);
    glVertexAttribDivisor(attributeCount, 1);
}

mx::ShapeInstance::~ShapeInstance()
{
    positions.clear();
}

void mx::ShapeInstance::add(const vec3& _pos)
{
    positions.push_back(_pos);

    // update data
    attributeBuffer.pushData((void*)&_pos, 1);
}

void mx::ShapeInstance::add(const std::vector<vec3>& _pos)
{
    positions.insert(positions.end(), _pos.begin(), _pos.end());

    // update data
    attributeBuffer.pushData((void*)_pos.data(), _pos.size());
}

void mx::ShapeInstance::reset()
{
    positions.clear();
    attributeBuffer.reset();
}

void mx::ShapeInstance::draw(mx::Shader* _shader)
{

    _shader->bind();
    cameraUbo->bind(_shader);
    shape->bind();

    auto indexBuf = shape->getIndexBuffer();
    if(indexBuf) {
        glDrawElementsInstanced(GL_TRIANGLES, indexBuf->getCount(), GL_UNSIGNED_INT, nullptr, positions.size());
    } else {
        auto vertexBuf = shape->getVertexBuffer();
        glDrawArraysInstanced(GL_TRIANGLES, 0, vertexBuf->getCount(), positions.size());
    }
    shape->unbind();
    _shader->unbind();
}

void mx::ShapeInstance::setCameraUBO(mx::UniformBuffer* _cameraUbo)
{
    cameraUbo = _cameraUbo;
}