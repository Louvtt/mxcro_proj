#ifndef _MX_TEXTURE_H_
#define _MX_TEXTURE_H_

#include "types.h"
#include <vector>

namespace mx
{

enum class TextureFilter
{
    Point,
    Linear,
    Bicubic,

    Default = Point
};

enum class TextureMode
{
    Clamp,
    Repeat,
    Mirror,

    Default = Clamp
};

struct TextureRect
{
    int x, y;
    int w, h;
};

struct TextureDesc
{
    const char* path     = "";
    TextureMode   mode   = TextureMode::Default;
    TextureFilter filter = TextureFilter::Default;
};

struct TextureImageDesc
{
    u32 width    = 0;
    u32 height   = 0;
    u32 channels = 0;
    void* data = NULL;
    TextureMode   mode   = TextureMode::Default;
    TextureFilter filter = TextureFilter::Default;
};

class Texture
{
public:
    Texture(const TextureDesc& desc);
    Texture(const TextureImageDesc& desc);

    void updateData(void* data);

    void bind(int idx = 0);
    void unbind();

    u32 getSizeX() const;
    u32 getSizeY() const;
    u32 getRendererID() const;

private:
    int m_binding = 0;

    u32 m_ID = 0;
    u32 m_sizeX = 0;
    u32 m_sizeY = 0;
};

class Subtexture
{
public:
    Subtexture(Texture& tex, TextureRect src);

    u32         getRendererID()  const;
    TextureRect getTextureRect() const;

    static std::vector<Subtexture> SplitTexture(Texture& texture, int cols, int rows);

private:
    Texture& tex;
    TextureRect src;
};

} // namespace mx


#endif //_MX_TEXTURE_H_