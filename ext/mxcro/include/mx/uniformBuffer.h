#ifndef _MX_UNIFORM_BUFFER_
#define _MX_UNIFORM_BUFFER_

#include "types.h"
#include "renderAttributeTypes.h"
#include <vector>

namespace mx
{

class Shader;

struct UniformBufferDesc {
    const char* name = "ubo";
    std::vector<AttributeType> attributes{};
};

class UniformBuffer {
public:
    UniformBuffer(const UniformBufferDesc& desc);
    ~UniformBuffer();
    
    void bind(Shader* shader, int index = 0);
    void setAttributeValue(int idx, void* value);
    void setAttributesValues(void* values);
private:
    u32 m_ID = 0;
    std::vector<int> m_offsets{};
    std::vector<AttributeType> m_attribs{};
    const char* m_name = "ubo";
    int m_stride = 0;
};
} // namespace mx

#endif //_MX_UNIFORM_BUFFER_