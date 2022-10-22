#include <glad/gl.h>

#include "mx/contextRender.h"
#include "mx/context.h"

#include <iostream>
#define LOG(msg) std::cout << msg << std::endl;

const char* vCode = ""
"#version 460 core\n"
"layout (location = 0) in vec2 aPos;\n"
"layout (location = 1) in vec4 Color;\n"
"out vec4 color;\n"
"layout (std140) uniform camera {"
"   mat4 uProj;\n"
"   mat4 uView;\n"
"};"
"void main() {\n"
"   gl_Position = uProj * uView * vec4(aPos.x, aPos.y, 0, 1);\n"
"   color = Color;\n"
"}";
const char* fCode = ""
"#version 460 core\n"
"in vec4 color;\n"
"out vec4 frag;\n"
"void main() {\n"
"   frag = color;\n"
"}";

const char* vCode_circle = ""
"#version 460 core\n"
"layout (location = 0) in vec2 aPos;\n"
"layout (location = 1) in vec2 aTex;\n"
"layout (location = 2) in vec4 Color;\n"
"out vec4 color;\n"
"out vec2 tex;\n"
"layout (std140) uniform camera {"
"   mat4 uProj;\n"
"   mat4 uView;\n"
"};"
"void main() {\n"
"   gl_Position = uProj * uView * vec4(aPos.x, aPos.y, 0, 1);\n"
"   tex = aTex;\n"
"   color = Color;\n"
"}";
const char* fCode_circle = ""
"#version 460 core\n"
"in vec4 color;\n"
"in vec2 tex;\n"
"out vec4 frag;\n"
"void main() {\n"
"   frag = color;\n"
"   if(length(tex - vec2(.5)) > .48) discard;\n"
"}";

mx::ContextRender::ContextRender(const mx::ContextRenderDesc& _desc)
: desc(_desc),
shader(new mx::Shader(vCode, fCode)),
circleShader(new mx::Shader(vCode_circle, fCode_circle)),
cameraUbo({ "camera", { mx::AttributeType::Mat4, mx::AttributeType::Mat4 }}),
drawData(nullptr), circleDrawData(nullptr)
{
    std::vector<u32> quadIndices = {};
    quadIndices.reserve(desc.maxBatchCapacity * 6);
    for(int i = 0; i < desc.maxBatchCapacity * 4; i+=4) {
        quadIndices.push_back(0 + i); // tri 1
        quadIndices.push_back(1 + i);
        quadIndices.push_back(2 + i);
        quadIndices.push_back(2 + i); // tri 2
        quadIndices.push_back(3 + i);
        quadIndices.push_back(0 + i);
    }

    vertices.reserve(2048);
    drawData = new mx::ShapeDrawData({
        new mx::VertexBuffer(
        mx::BufferDesc{
            desc.maxBatchCapacity * 4,
            true,
            sizeof(Vertex),
            nullptr
        }),
        new mx::IndexBuffer(
        mx::BufferDesc{
            desc.maxBatchCapacity * 6,
            false,
            sizeof(u32),
            quadIndices.data()
        }),
        {
            mx::AttributeType::Pos2D,
            mx::AttributeType::RGBA
        }
    });

    
    circleVertices.reserve(2048);
    circleDrawData = new mx::ShapeDrawData({
        new mx::VertexBuffer(
        mx::BufferDesc{
            desc.maxBatchCapacity * 4,
            true,
            sizeof(CircleVertex),
            nullptr
        }),
        new mx::IndexBuffer(
        mx::BufferDesc{
            desc.maxBatchCapacity * 6,
            false,
            sizeof(u32),
            quadIndices.data()
        }),
        {
            mx::AttributeType::Pos2D,
            mx::AttributeType::TexCoords2D,
            mx::AttributeType::RGBA
        }
    });

    cam.proj = mx::mat4::ortho((f32)desc.context->getSizeX(), (f32)desc.context->getSizeY());
    cam.view = mx::mat4();
    cameraUbo.setAttributesValues((void*)&cam);
}

mx::ContextRender::~ContextRender()
{
    delete drawData;
    delete circleDrawData;
    delete shader;
    delete circleShader;
}

void mx::ContextRender::setActiveColor(mx::Color _color)
{
    lastColor = _color;
}
void mx::ContextRender::drawLine(mx::vec2 _start, mx::vec2 _end)
{
    drawLine(_start, _end, lastColor, lastColor);
}
void mx::ContextRender::drawLine(mx::vec2 _start, mx::vec2 _end, mx::Color _color)
{
    drawLine(_start, _end, _color, _color);
}
void mx::ContextRender::drawLine(mx::vec2 _start, mx::vec2 _end, mx::Color _startCol, mx::Color _endCol)
{
    vec2 dir  = (_end - _start).normalized();
    vec2 perp = mx::vec2{-dir.y, dir.x} * (float)lineWidth;

    vertices.push_back({ _start + perp, _startCol });
    vertices.push_back({ _start - perp, _startCol });
    vertices.push_back({ _end   - perp, _endCol   });
    vertices.push_back({ _end   + perp, _endCol   });
}
void mx::ContextRender::drawRect(mx::vec2 _pos, mx::vec2 _size, mx::Color _color)
{
    mx::vec2 hsize = _size * .5f;
    vertices.push_back({ {_pos.x - hsize.x, _pos.y - hsize.y}, _color });
    vertices.push_back({ {_pos.x + hsize.x, _pos.y - hsize.y}, _color });
    vertices.push_back({ {_pos.x + hsize.x, _pos.y + hsize.y}, _color });
    vertices.push_back({ {_pos.x - hsize.x, _pos.y + hsize.y}, _color });
}
void mx::ContextRender::drawRect(mx::vec2 _pos, mx::vec2 _size)
{
    drawRect(_pos, _size, lastColor);
}

void mx::ContextRender::drawSRect(mx::vec2 _pos, mx::vec2 _size, mx::Color _color)
{
    mx::vec2 hsize = _size * .5f;
    lastColor = _color;
    drawLine(_pos - mx::vec2{ hsize.x,  hsize.y}, _pos - mx::vec2{ hsize.x, -hsize.y});
    drawLine(_pos - mx::vec2{ hsize.x, -hsize.y}, _pos - mx::vec2{-hsize.x, -hsize.y});
    drawLine(_pos - mx::vec2{-hsize.x, -hsize.y}, _pos - mx::vec2{-hsize.x,  hsize.y});
    drawLine(_pos - mx::vec2{-hsize.x,  hsize.y}, _pos - mx::vec2{ hsize.x,  hsize.y});
}

void mx::ContextRender::drawPoint(mx::vec2 _pos, float _radius)
{
    drawPoint(_pos, _radius, lastColor);
}
void mx::ContextRender::drawPoint(mx::vec2 _pos, float _radius, mx::Color _color)
{
    circleVertices.push_back({ {_pos.x - _radius, _pos.y - _radius}, {1.f, 1.f}, _color });
    circleVertices.push_back({ {_pos.x + _radius, _pos.y - _radius}, {0.f, 1.f}, _color });
    circleVertices.push_back({ {_pos.x + _radius, _pos.y + _radius}, {0.f, 0.f}, _color });
    circleVertices.push_back({ {_pos.x - _radius, _pos.y + _radius}, {1.f, 0.f}, _color });
}

void mx::ContextRender::translateView(mx::vec2 translation)
{}
void mx::ContextRender::rotateView(float angle)
{}
void mx::ContextRender::scaleView(vec2 scale) 
{}


void mx::ContextRender::draw()
{
    mx::ShapeDrawDataDesc data;

    // first batch
    cameraUbo.bind(shader);

    data = drawData->getData();
    data.vertexBuffer->pushData(vertices.data(), vertices.size());

    shader->bind();
    drawData->draw();
    shader->unbind();

    data.vertexBuffer->reset();
    vertices.clear();

    // second batch
    cameraUbo.bind(circleShader);

    data = circleDrawData->getData();
    data.vertexBuffer->pushData(circleVertices.data(), circleVertices.size());

    circleShader->bind();
    circleDrawData->draw();
    circleShader->unbind();

    data.vertexBuffer->reset();
    circleVertices.clear();
}

void mx::ContextRender::resize(u32 _sx, u32 _sy)
{
    cam.proj = mx::mat4::ortho((f32)_sx, (f32)_sy);
    cameraUbo.setAttributesValues((void*)&cam);
}

mx::Context* mx::ContextRender::getContext() const {
    return desc.context;
}

constexpr float inv_255 = 1.f / 255.f;
mx::Color::Color(float _r, float _g, float _b, float _a)
: r(_r), g(_g), b(_b), a(_a) {}
mx::Color::Color(int _r, int _g, int _b, float _a)
: a(_a), r((float)_r * inv_255), g((float)_g * inv_255), b((float)_b * inv_255)
{}