#ifndef _MX_CONTEXTRENDER_H_
#define _MX_CONTEXTRENDER_H_

#include "shader.h"
#include "buffers.h"
#include "texture.h"
#include "uniformBuffer.h"
#include <vector>
#include <array>
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
    
    void drawTexture(vec2 pos, vec2 size, SubTexture* tex);
    void drawTexture(vec2 pos, vec2 size, Texture* tex);
    void drawTexture(vec2 pos, float sizeFactor, Texture* tex);

    void translateView(vec2 translation);
    void rotateView(float angle);
    void scaleView(vec2 scale);

    void resize(u32 sx, u32 sy);

    void draw();

    mx::Context* getContext() const;

private:
    ContextRenderDesc desc;

    Shader* shader;
    struct Vertex {
        mx::vec2 pos;
        mx::Color col; 
    };
    std::vector<Vertex> vertices;
    ShapeDrawData* drawData;

    Shader* circleShader;
    struct CircleVertex {
        mx::vec2 pos;
        mx::vec2 tex;
        mx::Color col; 
    };
    std::vector<CircleVertex> circleVertices;
    ShapeDrawData* circleDrawData;

    Shader* textureShader;
    struct TextureVertex {
        mx::vec2 pos;
        mx::vec2 tex;
        mx::Color col; 
        float texID;
    };
    std::vector<TextureVertex> textureVertices;
    std::array<Texture*, 32> textures;
    int currentTex = 0;
    ShapeDrawData* textureDrawData;

    Color lastColor = { 1.f, 1.f, 1.f, 1.f };
    int lineWidth = 1;

    struct CameraData {
        mat4 proj;
        mat4 view;
    } cam;
    mx::UniformBuffer cameraUbo;
};

} // namespace mx


#endif //_MX_CONTEXTRENDER_H_