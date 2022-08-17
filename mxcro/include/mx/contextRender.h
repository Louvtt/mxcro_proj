#ifndef _MX_CONTEXTRENDER_H_
#define _MX_CONTEXTRENDER_H_

#include "shader.h"
#include "buffers.h"
#include <vector>
#include "math.h"

namespace mx
{

class ShapeDrawData;
class Context;
struct ContextRenderDesc
{
    unsigned int maxBatchCapacity = 4096;
    Context* context;
};

struct Color { 
    float r, g, b;
    float a;

    Color(float r, float g, float b, float a=1.f);
    Color(int r, int g, int b, float a = 1.f);
};

class ContextRender
{
public:
    ContextRender(const ContextRenderDesc& desc);
    ~ContextRender();

    void setActiveColor(Color color);
    void setLineWidth(int width);
    void drawLine(vec2 start, vec2 end);
    void drawLine(vec2 start, vec2 end, Color color);
    void drawLine(vec2 start, vec2 end, Color startCol, Color endCol);
    void drawRect(vec2 pos, vec2 size, Color color);
    void drawRect(vec2 pos, vec2 size);
    void drawSRect(vec2 pos, vec2 size, Color color);
    void drawPoint(vec2 pos, float radius);
    void drawPoint(vec2 pos, float radius, Color color);

    void translateView(vec2 translation);
    void rotateView(float angle);
    void scaleView(vec2 scale);

    void draw();

private:
    ContextRenderDesc desc;
    Shader* shader;

    struct Vertex {
        mx::vec2 pos;
        mx::Color col; 
    };
    std::vector<Vertex> vertices;
    ShapeDrawData* drawData;

    Color lastColor = { 1.f, 1.f, 1.f, 1.f };
    int lineWidth = 1;

    mat4 proj;
    mat4 view;

};

} // namespace mx


#endif //_MX_CONTEXTRENDER_H_