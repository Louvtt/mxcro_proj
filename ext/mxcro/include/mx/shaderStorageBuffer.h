#ifndef _MX_SHADER_STORAGE_BUFFER_
#define _MX_SHADER_STORAGE_BUFFER_

#include "types.h"

namespace mx
{
struct ShaderStorageBufferDesc {};

class ShaderStorageBuffer {
public:
    ShaderStorageBuffer(const ShaderStorageBufferDesc& desc);
    ~ShaderStorageBuffer();

    void bind();
private:
    u32 m_ID;
};
} // namespace mx

#endif //_MX_SHADER_STORAGE_BUFFER_