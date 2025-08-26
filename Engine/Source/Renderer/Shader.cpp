
#include "Shader.h"
#include "Core/Logger.h"
#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>

namespace Core
{
    Shader::Shader() : id(0) {}

    Shader::Shader(const char *filePath) : id(0)
    {
        std::ifstream file(filePath);
        if (!file.is_open())
        {
            CE_ERROR("Failed to open shader file: %s", filePath);
            return;
        }

        std::stringstream ss;
        ss << file.rdbuf();
        std::string src = ss.str();

        std::string vertSrc, fragSrc;
        size_t vertPos = src.find("// VERTEX");
        size_t fragPos = src.find("// FRAGMENT");

        if (vertPos == std::string::npos || fragPos == std::string::npos)
        {
            CE_ERROR("Shader file missing // VERTEX or // FRAGMENT markers!");
            return;
        }

        vertSrc = src.substr(vertPos + 9, fragPos - (vertPos + 9)); // 9 = length of "// VERTEX"
        fragSrc = src.substr(fragPos + 11);                         // 11 = length of "// FRAGMENT"

        Compile(vertSrc.c_str(), fragSrc.c_str());
    }

    Shader::Shader(const char *vertSrc, const char *fragSrc) : id(0) { Compile(vertSrc, fragSrc); }

    Shader::~Shader()
    {
        uniforms.clear();
        if (id)
            glDeleteProgram(id);
    }

    void Shader::Use()
    {
        if (id)
            glUseProgram(id);
    }

    void Shader::Mat4(float *data, const char *name)
    {
        u32 id = GetUniId(name);
        glUniformMatrix4fv(id, 1, GL_FALSE, data);
    }

    void Shader::Compile(const char *vertSrc, const char *fragSrc)
    {
        u32 vert = CompileShader(GL_VERTEX_SHADER, vertSrc);
        u32 frag = CompileShader(GL_FRAGMENT_SHADER, fragSrc);

        id = glCreateProgram();
        glAttachShader(id, vert);
        glAttachShader(id, frag);
        glLinkProgram(id);

        int success;
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetProgramInfoLog(id, 512, nullptr, infoLog);
            CE_ERROR("Unable to link program: \n %s", infoLog);
        }

        glDeleteShader(vert);
        glDeleteShader(frag);
    }

    u32 Shader::CompileShader(u32 type, const char *src)
    {
        u32 shader = glCreateShader(type);
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            CE_ERROR("Unable to compile shader: \n %s", infoLog);
        }

        return shader;
    }

    u32 Shader::GetUniId(const char *name)
    {
        auto it = uniforms.find(name);
        if (it != uniforms.end())
            return it->second;

        int location = glGetUniformLocation(id, name);
        if (location == -1)
            CE_WARN("Warning: uniform '%s' not found!", name);

        uniforms[name] = location;
        return location;
    }
} // namespace Core
