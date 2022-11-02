#include "mx/gfx/texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <glad/gl.h>

#include <iostream>

static const GLenum GLFORMATS[] = {
    GL_RED,
    GL_RG,
    GL_RGB,
    GL_RGBA
};

static const GLint GLFILTERS[] = {
    GL_NEAREST,
    GL_LINEAR
};

static const GLint GLWRAPS[] = {
    GL_CLAMP_TO_EDGE,
    GL_REPEAT,
    GL_MIRRORED_REPEAT
};

mx::Texture::Texture(const mx::TextureDesc& desc)
: m_filter(desc.filter), m_mode(desc.mode)
{
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(desc.path, &m_sizeX, &m_sizeY, &m_channels, 0);
    if(data == NULL) {
        std::cerr << "ERR: Image loading failure\n";
    }
    createInternal((void*)data);
    std::cout << "Creating texture from file: " << m_ID << std::endl;
    stbi_image_free(data);
}

mx::Texture::Texture(const mx::TextureImageDesc& desc)
: m_sizeX(desc.width), m_sizeY(desc.height), m_channels(desc.channels),
m_filter(desc.filter), m_mode(desc.mode)
{
    createInternal(desc.data);
    std::cout << "Creating texture from raw data: " << m_ID << std::endl;
}

void mx::Texture::createInternal(void* data)
{
    // load opengl
    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_sizeX, m_sizeY, 0, GLFORMATS[m_channels-1], GL_UNSIGNED_BYTE, data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GLFILTERS[(int)m_filter]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GLFILTERS[(int)m_filter]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GLWRAPS[(int)m_mode]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GLWRAPS[(int)m_mode]);

    glBindTexture(GL_TEXTURE_2D, 0);
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
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_sizeX, m_sizeY, GLFORMATS[(int)m_mode], GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

/// SUBTEXTURE

mx::SubTexture::SubTexture(mx::Texture* tex, mx::TextureRect rect)
: m_tex(tex), m_src(rect)
{ }

std::vector<mx::SubTexture>
mx::SubTexture::SplitTexture(mx::Texture* tex, int cols, int rows)
{
    std::vector<mx::SubTexture> res{};
    float ds = 1.f/(float)cols;
    float dt = 1.f/(float)rows;
    for(int i = 0; i < rows; ++i) 
        for(int j = 0; j < cols; ++j)
            res.push_back(SubTexture(
                tex,
                mx::TextureRect{ds*i,dt*j,ds,dt}
            ));
    return res;
}

mx::Texture* mx::SubTexture::getTexture() const {
    return m_tex;
}

mx::TextureRect
mx::SubTexture::getTextureRect() const {
    return m_src;
}