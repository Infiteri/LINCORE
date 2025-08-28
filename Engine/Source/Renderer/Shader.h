#pragma once

#include "Base.h"
#include <string>
#include <unordered_map>

namespace Core
{
    class CE_API Shader
    {
    public:
        Shader();
        Shader(const char *filePath);
        Shader(const char *vertSrc, const char *fragSource);
        ~Shader();

        void Use();

        void Mat4(float *data, const char *name);
        void Int(int data, const char *name);

        inline u32 GetID() const { return id; };

    private:
        u32 id;
        std::unordered_map<std::string, u32> uniforms;

    private:
        void Compile(const char *vertSrc, const char *fragSource);
        u32 CompileShader(u32 type, const char *src);

        u32 GetUniId(const char *name);
    };
} // namespace Core
