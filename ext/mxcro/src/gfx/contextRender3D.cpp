#include "mx/gfx/contextRender3D.hpp"

#include "mx/gfx/shapeDrawData.hpp"
#include "mx/gfx/shader.hpp"
#include "mx/core/context.hpp"
#include "mx/core/types.hpp"

#include <iostream>

#include <glad/gl.h>

// SHAPE INSTANCE
mx::ShapeInstance::ShapeInstance(ShapeDrawData* _shape, Shader* _shader, u32 _reservedCount)
: shader(_shader),
shape(_shape)
{
    positions.reserve(_reservedCount);
    std::cout << "Generated shape instance\n";
}
void mx::ShapeInstance::add(const vec3& pos)
{
    positions.push_back(pos);
}

void mx::ShapeInstance::draw(mx::UniformBuffer* _cameraUbo)
{
    _cameraUbo->bind(shader);

    shader->bind();
    for(const auto& pos : positions) {
        shader->setVec3("pos", pos);
        shape->draw();
    }
    shader->unbind();
}

// CONTEXT RENDER 3D

mx::ContextRender3D::ContextRender3D(const ContextRender3DDesc& _desc)
: desc(_desc),
cameraUbo({ "camera3d", { AttributeType::Mat4, AttributeType::Mat4 }})
{
    f32 aspectRatio = (f32)desc.context->getSizeX()/(f32)desc.context->getSizeY();
    cam.proj = mat4::persp(90.f, aspectRatio, .01f, 100.f);
    cam.view = mat4::translation(0.f, 0.f, -3.f);
    cameraUbo.setAttributesValues((void*)&cam);
}

void mx::ContextRender3D::addInstance(ShapeInstance* instance)
{
    instances.push_back(instance);
}

void mx::ContextRender3D::resize(u32 _sx, u32 _sy)
{
    f32 aspectRatio = (f32)_sx/(f32)_sy;
    cam.proj = mat4::persp(90.f, aspectRatio, .01f, 100.f);
    cameraUbo.setAttributesValues((void*)&cam);
}

void mx::ContextRender3D::draw()
{
    for(auto instance : instances) {
        instance->draw(&cameraUbo);
    }
}

mx::Context* mx::ContextRender3D::getContext() const {
    return desc.context;
}

void mx::ContextRender3D::setCameraView(const mat4& _view)
{
    cam.view = _view;
    cameraUbo.setAttributesValues((void*)&cam);
}