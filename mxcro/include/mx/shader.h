#ifndef _MX_SHADER_H_
#define _MX_SHADER_H_

#include <string>
#include "math.h"

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
    void setFloat4(const std::string& name, float* value);
    void setMat4(const std::string& name, float* value);
    
    void bind();
    void unbind();

private:
    unsigned int ID;

    unsigned int getUniformLocation(const std::string& name);
};

} // namespace mx


#endif //_MX_SHADER_H_