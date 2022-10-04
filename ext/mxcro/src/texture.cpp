#include "mx/texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <glad/gl.h>

#include <iostream>

static GLenum format[] = {
    GL_RED,
    GL_RG,
    GL_RGB,
    GL_RGBA
};

static GLenum filters[] = {
    GL_NEAREST,
    GL_LINEAR
};

static GLenum wrap[] = {
    GL_CLAMP_TO_EDGE,
    GL_REPEAT,
    GL_MIRRORED_REPEAT
};

mx::Texture::Texture(const mx::TextureDesc& desc)
: m_filter(desc.filter), m_mode(desc.mode)
{
    unsigned char* data = stbi_load(desc.path, &m_sizeX, &m_sizeY, &m_channels, 0);
    if(data == NULL) {
        std::cerr << "ERR: Image loading failure\n";
    }

    // load opengl
    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_sizeX, m_sizeY, 0, format[m_channels-1], GL_UNSIGNED_BYTE, data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filters[(int)desc.filter]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filters[(int)desc.filter]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap[(int)desc.mode]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap[(int)desc.mode]);

    glBindTexture(GL_TEXTURE_2D, 0);

    std::cout << "Creating texture from file: " << m_ID << std::endl;
}

mx::Texture::Texture(const mx::TextureImageDesc& desc)
: m_sizeX(desc.width), m_sizeY(desc.height), m_channels(desc.channels),
m_filter(desc.filter), m_mode(desc.mode)
{
    // load opengl
    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_sizeX, m_sizeY, 0, format[m_channels-1], GL_UNSIGNED_BYTE, desc.data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filters[(int)desc.filter]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filters[(int)desc.filter]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap[(int)desc.mode]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap[(int)desc.mode]);

    glBindTexture(GL_TEXTURE_2D, 0);

    std::cout << "Creating texture from raw data: " << m_ID << std::endl;
}

void mx::Texture::bind(int idx) {
    m_binding = idx;
    glActiveTexture(GL_TEXTURE0 + idx);
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

void mx::Texture::unbind() {
    glActiveTexture(GL_TEXTURE0 + m_binding);
    glBindTexture(GL_TEXTURE_2D, 0);
}

u32 mx::Texture::getRendererID() const {
    return m_ID;
}

u32 mx::Texture::getSizeX() const {
    return m_sizeX;
}

u32 mx::Texture::getSizeY() const {
    return m_sizeY;
}

void mx::Texture::updateData(void* data)
{
    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_sizeX, m_sizeY, format[(int)m_mode], GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

/// SUBTEXTURE

mx::Subtexture::Subtexture(mx::Texture& tex, mx::TextureRect rect)
: m_tex(tex), m_src(rect)
{ }

std::vector<mx::Subtexture>
mx::Subtexture::SplitTexture(mx::Texture& tex, int cols, int rows)
{
    std::vector<mx::Subtexture> res{};
    float ds = 1.f/(float)cols;
    float dt = 1.f/(float)rows;
    for(int i = 0; i < rows; ++i) 
        for(int j = 0; j < cols; ++j)
            res.push_back(Subtexture(
                tex,
                mx::TextureRect{ds*i,dt*j,ds,dt}
            ));
    return res;
}

u32 mx::Subtexture::getRendererID() const {
    return m_tex.getRendererID();
}

mx::TextureRect
mx::Subtexture::getTextureRect() const {
    return m_src;
}