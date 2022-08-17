#include "mx/ContextRender.h"

#include "mx/context.h"
#include <glad/gl.h>

#include <iostream>
#define LOG(msg) std::cout << msg << std::endl;

const char* vCode = ""
"#version 460 core\n"
"layout (location = 0) in vec2 aPos;\n"
"layout (location = 1) in vec4 Color;\n"
"out vec4 color;\n"
"uniform mat4 uProj;\n"
"uniform mat4 uView;\n"
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

mx::ContextRender::ContextRender(const mx::ContextRenderDesc& _desc)
: desc(_desc)
{
    shader = new mx::Shader(vCode, fCode);

    std::vector<u32> quadIndices{};
    quadIndices.reserve(desc.maxBatchCapacity * 6);
    for(int i = 0; i < desc.maxBatchCapacity * 4; i+=4) {
        quadIndices.push_back(0 + i); // tri 1
        quadIndices.push_back(1 + i);
        quadIndices.push_back(2 + i);
        quadIndices.push_back(2 + i); // tri 2
        quadIndices.push_back(3 + i);
        quadIndices.push_back(0 + i);
    }

    drawData = new mx::ShapeDrawData({
        std::make_shared<mx::Buffer>(
        mx::BufferDesc{
            mx::BufferType::DynamicVertex,
            desc.maxBatchCapacity * 4,
            sizeof(Vertex),
            nullptr
        }),
        std::make_shared<mx::Buffer>(
        mx::BufferDesc{
            mx::BufferType::Index,
            desc.maxBatchCapacity * 6,
            sizeof(u32),
            quadIndices.data()
        }),
        {
            mx::ShapeAttribute::Pos2D,
            mx::ShapeAttribute::RGBA
        }
    });

    proj = mx::mat4::ortho(desc.context->getSizeX(), desc.context->getSizeY());
    view = mx::mat4();
}

mx::ContextRender::~ContextRender()
{
    delete drawData;
    delete shader;
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

void mx::ContextRender::drawPoint(mx::vec2 _pos, float _radius)
{
    drawPoint(_pos, _radius, lastColor);
}
void mx::ContextRender::drawPoint(mx::vec2 _pos, float _radius, mx::Color _color)
{
    vertices.push_back({ {_pos.x - _radius, _pos.y}, _color });
    vertices.push_back({ {_pos.x, _pos.y - _radius}, _color });
    vertices.push_back({ {_pos.x + _radius, _pos.y}, _color });
    vertices.push_back({ {_pos.x, _pos.y + _radius}, _color });
}

void mx::ContextRender::translateView(mx::vec2 translation)
{}
void mx::ContextRender::rotateView(float angle)
{}
void mx::ContextRender::scaleView(vec2 scale) 
{}


void mx::ContextRender::draw()
{
    shader->setMat4("uProj", &proj.data[0]);
    shader->setMat4("uView", &view.data[0]);

    mx::ShapeDrawDataDesc data = drawData->getData();
    data.vertexBuffer->pushData(vertices.data(), vertices.size());

    shader->bind();
    drawData->draw();
    shader->unbind();

    data.vertexBuffer->reset();
    vertices.clear();
}

constexpr float inv_255 = 1.f / 255.f;
mx::Color::Color(float _r, float _g, float _b, float _a)
: r(_r), g(_g), b(_b), a(_a) {}
mx::Color::Color(int _r, int _g, int _b, float _a)
: a(_a), r((float)_r * inv_255), g((float)_g * inv_255), b((float)_b * inv_255)
{}