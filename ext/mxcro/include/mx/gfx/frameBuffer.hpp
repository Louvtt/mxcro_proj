#ifndef _MX_FRAMEBUFFER_H_
#define _MX_FRAMEBUFFER_H_

#include "../core/types.hpp"

namespace mx
{

class Texture;
struct FrameBufferDesc
{
    Texture* colorAttachement;
    Texture* depthAttachement;
    Texture* stencilAttachement;
};

class FrameBuffer
{
public:
    FrameBuffer(const FrameBufferDesc& desc);
    ~FrameBuffer();

    void bind();
    void unbind();

    void resize(u32 sizeX, u32 sizeY);

private:
    FrameBufferDesc attachements;
    u32 m_ID;
};

} // namespace mx


#endif //_MX_FRAMEBUFFER_H_