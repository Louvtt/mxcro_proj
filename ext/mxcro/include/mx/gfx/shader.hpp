#ifndef _MX_SHADER_H_
#define _MX_SHADER_H_

#include <string>
#include "../maths/math.hpp"
#include "../core/types.hpp"

namespace mx
{

class Shader
{
public:
    Shader(const std::string& filePath);
    Shader(const std::string& vCode, const std::string& fCode);
    ~Shader();

    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setFloat2(const std::string& name, float* value);
    void setVec2(const std::string& name, mx::vec2 value);
    void setFloat3(const std::string& name, float* value);
    void setVec3(const std::string& name, mx::vec3 value);
    void setFloat4(const std::string& name, float* value);
    void setMat4(const std::string& name, float* value);
    
    void bind();
    void unbind();

    u32 getProgramID() const;
private:
    void createInternal(const std::string& vCode, const std::string &fCode);

    u32 ID;

    u32 getUniformLocation(const std::string& name);
};

} // namespace mx


#endif //_MX_SHADER_H_