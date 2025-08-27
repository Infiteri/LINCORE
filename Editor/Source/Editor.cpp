#include "Core/Application.h"
#include "Core/Entry/EntryPoint.h"
#include "Core/Logger.h"
#include "Core/Window.h"
#include "Renderer/Buffer/Buffer.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Shader.h"
#include <array>
#include <cmath>
#include <cstdlib>
#include <glad/glad.h>

// Minimal perspective helper
std::array<float, 16> Perspective(float fovDeg, float aspect, float zNear, float zFar)
{
    float f = 1.0f / tan(fovDeg * 0.5f * 3.14159265f / 180.0f);
    return {f / aspect,
            0,
            0,
            0,
            0,
            f,
            0,
            0,
            0,
            0,
            (zFar + zNear) / (zNear - zFar),
            -1,
            0,
            0,
            (2 * zFar * zNear) / (zNear - zFar),
            0};
}

// Minimal lookAt helper
std::array<float, 16> LookAt(float eyeX, float eyeY, float eyeZ, float centerX, float centerY,
                             float centerZ, float upX, float upY, float upZ)
{
    float f[3] = {centerX - eyeX, centerY - eyeY, centerZ - eyeZ};
    float fl = sqrt(f[0] * f[0] + f[1] * f[1] + f[2] * f[2]);
    for (int i = 0; i < 3; i++)
        f[i] /= fl;

    float up[3] = {upX, upY, upZ};
    float s[3] = {f[1] * up[2] - f[2] * up[1], f[2] * up[0] - f[0] * up[2],
                  f[0] * up[1] - f[1] * up[0]};
    float sl = sqrt(s[0] * s[0] + s[1] * s[1] + s[2] * s[2]);
    for (int i = 0; i < 3; i++)
        s[i] /= sl;

    float u[3] = {s[1] * f[2] - s[2] * f[1], s[2] * f[0] - s[0] * f[2], s[0] * f[1] - s[1] * f[0]};

    return {s[0],
            u[0],
            -f[0],
            0,
            s[1],
            u[1],
            -f[1],
            0,
            s[2],
            u[2],
            -f[2],
            0,
            -s[0] * eyeX - u[0] * eyeY + f[0] * eyeZ,
            -s[1] * eyeX - u[1] * eyeY + f[1] * eyeZ,
            -s[2] * eyeX - u[2] * eyeY + f[2] * eyeZ,
            1};
}

Core::VertexArray *array;

class EditorApplication : public Core::Application
{
public:
    void Init()
    {
        gladLoadGL();
        auto shader = Core::Shader("Shader.glsl");

        float vertices[] = {
            // positions       // colors
            -0.5f, 0.5f,  0.0f, 1.0f, 0.0f, 0.0f, // top-left, red
            0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, // top-right, green
            0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right, blue
            -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f  // bottom-left, yellow
        };

        unsigned int indices[] = {
            0, 1, 2, // first triangle (top-left, top-right, bottom-right)
            2, 3, 0  // second triangle (bottom-right, bottom-left, top-left)
        };

        array = new Core::VertexArray();

        array->GenerateVertexBuffer(vertices, sizeof(vertices));
        array->GetVertexBuffer()->AddLayout(0, 0, 3);
        array->GetVertexBuffer()->AddLayout(1, 3, 3);

        array->GenerateIndexBuffer(indices, sizeof(indices));

        glEnable(GL_DEPTH_TEST);

        // --- Camera ---
        auto proj = Perspective(60.0f, float(1280) / 720, 0.1f, 100.0f);
        auto view = LookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);

        shader.Use();
        shader.Mat4(proj.data(), "uProj");
        shader.Mat4(view.data(), "uView");
    }

    void Render()
    {
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        array->Bind();
        array->GetIndexBuffer()->Draw();
    }
};

Core::Application *Core::CreateApplication() { return new EditorApplication(); }
