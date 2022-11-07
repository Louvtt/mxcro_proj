#ifndef _MX_UNIFORM_BUFFER_
#define _MX_UNIFORM_BUFFER_

#include "../core/types.hpp"
#include "renderAttributeTypes.hpp"
#include <vector>

namespace mx
{

class Shader;

/**
 * @brief Decription of an uniform buffer
 */
struct UniformBufferDesc {
    /** buffer name in shaders */
    const char* name = "ubo";
    /** attributes of the uniform buffer */
    std::vector<AttributeType> attributes{};
};

/**
 * @brief Represent an Uniform buffer Object
 */
class UniformBuffer {
public:
    /**
     * @brief Create a new Uniform Buffer object
     * @param desc description of the uniform buffer
     */
    UniformBuffer(const UniformBufferDesc& desc);
    /**
     * @brief Destroy the Uniform Buffer
     */
    ~UniformBuffer();

    /**
     * @brief Bind the uniform buffer in a shader
     * @param shader shader where to bind the UBO
     * @param index index of the uniform block in the shader
     */
    void bind(Shader* shader, int index = 0);
    /**
     * @brief Set an attribute value in the UBO 
     * @param idx attribute index
     * @param value value of the attribute
     */
    void setAttributeValue(int idx, void* value);
    /**
     * @brief Set the data of the UBO
     * @param values data of the UBO
     */
    void setAttributesValues(void* values);

private:
    /** OpenGL Buffer ID */
    u32 m_ID = 0;
    /** Offset from start of each attributes */
    std::vector<int> m_offsets{};
    /** Attributes of the UBO */
    std::vector<AttributeType> m_attribs{};
    /** name of the UBO */
    const char* m_name = "ubo";
    /** total UBO data size */
    int m_stride = 0;
};
} // namespace mx

#endif //_MX_UNIFORM_BUFFER_