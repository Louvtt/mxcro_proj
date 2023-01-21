#ifndef _MX_CONTEXTRENDER3D_H_
#define _MX_CONTEXTRENDER3D_H_

#include "buffers.hpp"
#include "texture.hpp"
#include "uniformBuffer.hpp"
#include "../maths/math.hpp"
#include <vector>

namespace mx {

class ShapeInstance;
class Shader;
class ShapeDrawData;
class Context;
struct ContextRender3DDesc
{
    unsigned int maxBatchCapacity = 4096;
    Context* context;
};

class ContextRender3D
{
public:
    ContextRender3D(const ContextRender3DDesc& desc);

    void addInstance(ShapeInstance* instance);
    
    void resize(u32 sx, u32 sy);
    void draw(Shader* shader);

    mx::Context* getContext() const;

    void setCameraView(const mat4& view);
private:
    const ContextRender3DDesc desc;
    std::vector<ShapeInstance*> instances;

    struct CameraData {
        mat4 proj;
        mat4 view;
    } cam;
    mx::UniformBuffer cameraUbo;
};

}

#endif //_MX_CONTEXTRENDER3D_H_