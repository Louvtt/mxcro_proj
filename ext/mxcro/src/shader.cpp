#include "mx/shader.h"

#include <glad/gl.h>

#include <iostream>
#define LOG(msg) std::cout << msg << std::endl;
#define ERR(msg) std::cerr << msg << std::endl;

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

mx::Shader::Shader(const std::string& _path)
{
    std::string res = "";
    std::stringstream ss;
    std::ifstream file;
    file.exceptions(std::ios::badbit | std::ios::failbit);
    try
    {
        file.open(_path.c_str(), std::ios::in);
        if(!file.is_open()) throw new std::ios::failure("Cant't open the file.");

        ss << file.rdbuf();
        file.close();
        res = ss.str();
    }
    catch(const std::exception& e)
    {
        ERR("Error while opening the file [" << _path.c_str()  << "]: " << e.what());
        file.close();
    }

    // Process code line by line
    std::string vCode = "", fCode = "";
    bool isVertexCode = true;

    std::string line = "";
    std::size_t prev    = 0;
    std::size_t endLine = res.find_first_of('\n');
    while(endLine < std::string::npos)
    {
        line = res.substr(prev, endLine);
        prev = endLine;
        endLine = res.find_first_of('\n', prev);

        // version string
        if(line.substr(8) == "#version") {
            vCode += line + '\n';
            fCode += line + '\n';
            continue;
        }
        // fragment
        if(line.substr(5) == "#frag") {
            isVertexCode = false;
        }

        // just push lines
        if(isVertexCode) {
            vCode += line + '\n';
        } else {
            fCode += line + '\n'; 
        }
    }

    Shader(vCode, fCode);

}
mx::Shader::Shader(const std::string& vCode, const std::string& fCode)
{
    unsigned int vID = 0, fID = 0;
    // err
    int success = 0;
    const unsigned int bufferSize = 2048;
    char buffer[bufferSize];

    // VERTEX SHADER
    vID = glCreateShader(GL_VERTEX_SHADER);
    const char* vraw = vCode.c_str();
    glShaderSource(vID, 1, &vraw, NULL);
    glCompileShader(vID);
    glGetShaderiv(vID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vID, bufferSize, 0, &buffer[0]);
        ERR("Error while compiling the vertex shader: " << buffer);
        return;
    }

    // FRAGMENT SHADER
    fID = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fraw = fCode.c_str();
    glShaderSource(fID, 1, &fraw, NULL);
    glCompileShader(fID);
    glGetShaderiv(fID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fID, bufferSize, 0, &buffer[0]);
        ERR("Error while compiling the fragment shader: " << buffer);
        return;
    }

    // PROGRAM
    ID = glCreateProgram();
    glAttachShader(ID, vID);
    glAttachShader(ID, fID);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, bufferSize, 0, &buffer[0]);
        ERR("Error while linking the shaders: " <<  buffer);
        
        glDeleteShader(vID);
        glDeleteShader(fID);
        return;
    }

    // free the shaders that was attached
    glDeleteShader(vID);
    glDeleteShader(fID);
    LOG("Generated shader program : ID = " << ID);
}

mx::Shader::~Shader()
{
    glUseProgram(0);
    if(ID != 0) {
        glDeleteProgram(ID);
    }
}

unsigned int mx::Shader::getUniformLocation(const std::string& name)
{
    return glGetUniformLocation(ID, name.c_str());
}

void mx::Shader::setInt(const std::string& name, int value)
{
    glProgramUniform1i(ID, getUniformLocation(name), value);
}
void mx::Shader::setFloat(const std::string& name, float value)
{
    glProgramUniform1f(ID, getUniformLocation(name), value);
}
void mx::Shader::setFloat2(const std::string& name, float* value)
{
    glProgramUniform2f(ID, getUniformLocation(name), value[0], value[1]);
}
void mx::Shader::setVec2(const std::string& name, mx::vec2 value)
{
    glProgramUniform2f(ID, getUniformLocation(name), value.x, value.y);
}
void mx::Shader::setFloat3(const std::string& name, float* value)
{
    glProgramUniform3f(ID, getUniformLocation(name), value[0], value[1], value[2]);
}
void mx::Shader::setFloat4(const std::string& name, float* value)
{
    glProgramUniform4f(ID, getUniformLocation(name), value[0], value[1], value[2], value[3]);
}
void mx::Shader::setMat4(const std::string& name, float* value)
{
    glProgramUniformMatrix4fv(ID, getUniformLocation(name), 1, GL_FALSE, value);
}

void mx::Shader::bind()
{
    glUseProgram(ID);
}
void mx::Shader::unbind()
{
    glUseProgram(0);
}

u32 mx::Shader::getProgramID() const
{
    return ID;
}