#ifndef _MX_SHADER_H_
#define _MX_SHADER_H_

#include <string>
#include "../maths/math.hpp"
#include "../core/types.hpp"

namespace mx
{

/**
 * @brief Represent a Shader Program
 */
class Shader
{
public:
    /**
     * @brief Load a shader from file (vertex and frag should be in the same file separated by #frag)
     * @param filePath path to the shader file
     */
    Shader(const std::string& filePath);
    /**
     * @brief Create a new shader program based on shader code
     * 
     * @param vCode vertex shader code
     * @param fCode fragment shader code
     */
    Shader(const std::string& vCode, const std::string& fCode);
    /**
     * @brief Destroy the Shader
     */
    ~Shader();

    /**
     * @brief Set an int uniform in the shader
     * @param name uniform name
     * @param value uniform value
     */
    void setInt(const std::string& name, int value);
    /**
     * @brief Set a float uniform in the shader
     * @param name uniform name
     * @param value uniform value
     */
    void setFloat(const std::string& name, float value);
    /**
     * @brief Set a vec2 uniform in the shader
     * @param name uniform name
     * @param value uniform value
     */
    void setFloat2(const std::string& name, float* value);
    /**
     * @brief Set a vec2 uniform in the shader
     * @param name uniform name
     * @param value uniform value
     */
    void setVec2(const std::string& name, mx::vec2 value);
    /**
     * @brief Set a vec3 uniform in the shader
     * @param name uniform name
     * @param value uniform value
     */
    void setFloat3(const std::string& name, float* value);
    /**
     * @brief Set a vec3 uniform in the shader
     * @param name uniform name
     * @param value uniform value
     */
    void setVec3(const std::string& name, mx::vec3 value);
    /**
     * @brief Set a vec4 uniform in the shader
     * @param name uniform name
     * @param value uniform value
     */
    void setFloat4(const std::string& name, float* value);
    /**
     * @brief Set a mat4 uniform in the shader
     * @param name uniform name
     * @param value uniform value
     */
    void setMat4(const std::string& name, float* value);
    /**
     * @brief Set a mat4 uniform in the shader
     * @param name uniform name
     * @param value uniform value
     */
    void setMat4(const std::string& name, mat4 value);
    
    /**
     * @brief Bind shader program
     */
    void bind();
    /**
     * @brief Unbind shader program
     */
    void unbind();

    /**
     * @brief Get the Shader program OpenGL ID
     * @return u32 OpenGL Shader ID
     */
    u32 getProgramID() const;
private:
    /**
     * @brief Create a shader based on vertex code and shader code
     * @param vCode - vertex shader code
     * @param fCode - fragment shader code
     */
    void createInternal(const std::string& vCode, const std::string &fCode);

    /** OpenGL shader program ID */
    u32 ID;

    /**
     * @brief Get the location of an uniform in the shader
     * @param name uniform name
     * @return u32 the location
     */
    u32 getUniformLocation(const std::string& name);
};

} // namespace mx


#endif //_MX_SHADER_H_