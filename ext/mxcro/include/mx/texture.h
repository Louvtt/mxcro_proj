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
    float x, y;
    float w, h;
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
    void createInternal(void* data);

    int m_binding = 0;

    u32 m_ID = 0;
    int m_sizeX = 0;
    int m_sizeY = 0;
    int m_channels = 0;

    TextureMode   m_mode;
    TextureFilter m_filter;
};

class SubTexture
{
public:
    SubTexture(Texture* tex, TextureRect src);

    TextureRect getTextureRect() const;
    Texture*    getTexture() const;

    static std::vector<SubTexture> SplitTexture(Texture* texture, int cols, int rows);

private:
    Texture* m_tex;
    TextureRect m_src;
};

} // namespace mx


#endif //_MX_TEXTURE_H_