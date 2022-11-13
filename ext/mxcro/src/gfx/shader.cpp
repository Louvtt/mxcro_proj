#include "mx/gfx/shader.hpp"

#include <glad/gl.h>

#include <iostream>
#define LOG(msg) std::cout << msg << std::endl;
#define ERR(msg) std::cerr << msg << std::endl;

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string.h>

mx::Shader::Shader(const std::string& _path)
{
    std::string res = "";
    std::stringstream ss;
    std::ifstream file;
    try
    {
        file.open(_path.c_str(), std::ios::in);
        if(!file.is_open()) throw new std::ios::failure("Cant't open the file.");

        // Process code line by line
        LOG("Processing shader file [" << _path.c_str() << "]");
        std::string line = "";
        std::string vCode = "", fCode = "";
        bool isVertexCode = true;
        // version string (first line)
        if(std::getline(file, line)
        && line.substr(0, 8) == "#version") {
            LOG("Found shader version preprocessor: " << line);
            vCode += line + '\n';
            fCode += line + '\n';
        }
        // process rest of the code
        while(std::getline(file, line)) {
            // vertex switch fragment
            if(isVertexCode
            && line.size() >= 5
            && line.substr(0, 5) == "#frag") {
                isVertexCode = false;
                continue;
            }

            // just push lines
            if(isVertexCode) {
                vCode += line + '\n';
            } else {
                fCode += line + '\n'; 
            }
        }
        file.close();

        createInternal(vCode, fCode);
        LOG("Created shader from file with ID: " << ID);
    }
    catch(const std::exception& e)
    {
        ERR("Error while opening the file [" << _path.c_str()  << "]: " << e.what());
        file.close();
        ID = 0; // no program
        return;
    }
}

mx::Shader::Shader(const std::string& vCode, const std::string& fCode)
{
    createInternal(vCode, fCode);
    LOG("Generated shader program : ID = " << ID);
}

void mx::Shader::createInternal(const std::string& vCode, const std::string &fCode)
{
    unsigned int vID = 0, fID = 0;
    // err
    int success = 0;
    const unsigned int bufferSize = 2048;
    char buffer[bufferSize];
    memset(&buffer[0], ' ', bufferSize);

    // VERTEX SHADER
    vID = glCreateShader(GL_VERTEX_SHADER);
    const char* vraw = vCode.c_str();
    glShaderSource(vID, 1, &vraw, NULL);
    glCompileShader(vID);
    glGetShaderiv(vID, GL_COMPILE_STATUS, &success);
    if(success != GL_TRUE)
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
    if(success != GL_TRUE)
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
    if(success != GL_TRUE)
    {
        glGetProgramInfoLog(ID, bufferSize, 0, &buffer[0]);
        ERR("Error while linking the shaders: " <<  buffer);
        
        glDeleteShader(vID);
        glDeleteShader(fID);
        glDeleteProgram(ID);
        ID = 0;
        return;
    }

    // free the shaders that was attached
    glDeleteShader(vID);
    glDeleteShader(fID);
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
void mx::Shader::setVec3(const std::string& name, mx::vec3 value)
{
    glProgramUniform3f(ID, getUniformLocation(name), value.x, value.y, value.z);
}
void mx::Shader::setFloat4(const std::string& name, float* value)
{
    glProgramUniform4f(ID, getUniformLocation(name), value[0], value[1], value[2], value[3]);
}
void mx::Shader::setMat4(const std::string& name, float* value)
{
    glProgramUniformMatrix4fv(ID, getUniformLocation(name), 1, GL_FALSE, value);
}
void mx::Shader::setMat4(const std::string& name, mat4 value)
{
    glProgramUniformMatrix4fv(ID, getUniformLocation(name), 1, GL_FALSE, value.getDataPtr());
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