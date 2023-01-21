#include "mx/gfx/shapeGeometry.hpp"

#include "mx/gfx/buffers.hpp"
#include "mx/gfx/shader.hpp"

#include <glad/gl.h>

mx::ShapeGeometry::ShapeGeometry(const mx::ShapeGeometryDesc& _desc)
: vertexBuffer(_desc.vertexBuffer), indexBuffer(_desc.indexBuffer)
{
    this->bind();
    vertexBuffer->bind();
    if(indexBuffer) {
        indexBuffer->bind();
    }
    this->setAttributes(_desc.attributes, _desc.vertexBuffer->getDesc().dataSize);
    this->unbind();
}

mx::ShapeGeometry::~ShapeGeometry() {
    internalDestroy();
    delete vertexBuffer;
    if(indexBuffer)
        delete indexBuffer;
}

void mx::ShapeGeometry::draw(mx::Shader* shader)
{
    shader->bind();
    this->bind();
    if(this->indexBuffer) {
        u32 count = this->indexBuffer->getCount();
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    } else {
        u32 count = this->vertexBuffer->getCount();
        glDrawArrays(GL_TRIANGLES, 0, count);
    }
    this->unbind();
    shader->unbind();
}

mx::VertexBuffer* mx::ShapeGeometry::getVertexBuffer() const
{
    return vertexBuffer;
}

mx::IndexBuffer* mx::ShapeGeometry::getIndexBuffer() const 
{
    return indexBuffer;
}