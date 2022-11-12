#ifndef _MX_SHADER_STORAGE_BUFFER_
#define _MX_SHADER_STORAGE_BUFFER_

#include "../core/types.hpp"

namespace mx
{
struct ShaderStorageBufferDesc {
    const char* name;
    unsigned int byteSize;
    void* data;
};

class ShaderStorageBuffer {
public:
    ShaderStorageBuffer(const ShaderStorageBufferDesc& desc);
    ~ShaderStorageBuffer();

    void bind();
    void unbind();

    void setData(void* data);
private:
    ShaderStorageBufferDesc desc;
    u32 m_ID;
};
} // namespace mx

#endif //_MX_SHADER_STORAGE_BUFFER_