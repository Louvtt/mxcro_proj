#ifndef _MX_TEXTURE_H_
#define _MX_TEXTURE_H_

#include "../core/types.hpp"
#include <vector>

namespace mx
{

/**
 * @brief Filter modes of a texture
 */
enum class TextureFilter
{
    Point,
    Linear,

    Default = Point
};

/**
 * @brief Wrap modes of a texture
 */
enum class TextureMode
{
    Clamp,
    Repeat,
    Mirror,

    Default = Clamp
};

/**
 * @brief Rectangle of a texture
 */
struct TextureRect
{
    float x, y;
    float w, h;
};

/**
 * @brief Description of a Texture
 */
struct TextureDesc
{   
    /** Path to the image */
    const char* path     = "";
    /** Wrap mode of the texture */
    TextureMode   mode   = TextureMode::Default;
    /** Filter mode of the texture */
    TextureFilter filter = TextureFilter::Default;
};

/**
 * @brief Brief description of a raw Texture
 * 
 */
struct TextureImageDesc
{
    /** size x of the texture */
    u32 width    = 0;
    /** size y of the texture */
    u32 height   = 0;
    /** number of channels per pixel */
    u32 channels = 0;
    /** data of the texture */
    void* data = NULL;
    /** Wrap mode of the texture */
    TextureMode   mode   = TextureMode::Default;
    /** Filter mode of the texture */
    TextureFilter filter = TextureFilter::Default;
};

/**
 * @brief Represent an OpenGL Texture
 */
class Texture
{
public:
    /**
     * @brief Create a texture from a file
     * @param desc description of the texture
     */
    Texture(const TextureDesc& desc);
    /**
     * @brief Create a raw texture from data
     * @param desc description of the raw texture
     */
    Texture(const TextureImageDesc& desc);

    /**
     * @brief Update the data in the texture
     * @param data new data of the texture (must be the same size)
     */
    void updateData(void* data);

    /**
     * @brief Bind the texture to a specific location
     * @param idx binding index (max is 32)
     */
    void bind(int idx = 0);
    /**
     * @brief Unbind the texture from the binding index
     */
    void unbind();

    /**
     * @brief Get the SizeX of the texture
     * @return u32 the SizeX of the texture
     */
    u32 getSizeX() const;
    /**
     * @brief Get the SizeY of the texture
     * @return u32 the SizeY of the texture
     */
    u32 getSizeY() const;
    /**
     * @brief Get the OpenGL Texture ID
     * @return u32 the OpenGL Texture ID
     */
    u32 getRendererID() const;

private:
    /**
     * @brief Create a texture based on data after setting up the descriptor
     * @param data data of the texture
     */
    void createInternal(void* data);

    /** Last binding index */
    int m_binding = 0;

    /** OpenGL ID of the texture */
    u32 m_ID = 0;
    /** SizeX of the texture */
    int m_sizeX = 0;
    /** SizeY of the texture */
    int m_sizeY = 0;
    /** Number of channels in the texture */
    int m_channels = 0;

    /** Wrap mode of the texture */
    TextureMode   m_mode;
    /** Filter mode of the texture */
    TextureFilter m_filter;
};

/**
 * @brief Represent a subregion of a texture
 */
class SubTexture
{
public:
    /**
     * @brief Create a new Sub Texture
     * 
     * @param tex source texture
     * @param src source rectangle
     */
    SubTexture(Texture* tex, TextureRect src);

    /**
     * @brief Get the source rectangle
     * @return TextureRect the source rectangle
     */
    TextureRect getTextureRect() const;
    /**
     * @brief Get the source texture
     * @return Texture* the source texture
     */
    Texture*    getTexture() const;

    /**
     * @brief Create a list of subtextures from a texture.
     * Useful for tilemaps.
     * @param texture source texture
     * @param cols number of columns
     * @param rows number of rows
     * @return std::vector<SubTexture> the subtextures
     */
    static std::vector<SubTexture> SplitTexture(Texture* texture, int cols, int rows);

private:
    /** source texture */
    Texture* m_tex;
    /** source rect */
    TextureRect m_src;
};

} // namespace mx


#endif //_MX_TEXTURE_H_