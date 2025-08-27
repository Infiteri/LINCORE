#include "TriangleTest.h"
#include "Core/Logger.h"
#include "Renderer/Buffer/Buffer.h"
#include "Renderer/Shader.h"
#include <glad/glad.h>
#include <iostream>

namespace Core
{
    static GLuint VAO;
    static Core::Buffer *VBO, *EBO;
    static Core::Shader *shader;

    bool VBOTest::Run(std::string &reason)
    {
        // --- Vertex data (triangle with colors) ---
        float vertices[] = {
            // positions        // colors
            0.0f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, // top (red)
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // left (green)
            0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // right (blue)
        };

        // --- Vertex shader source ---
        const char *vertSrc = R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec3 aColor;

            out vec3 vColor;

            void main()
            {
                gl_Position = vec4(aPos, 1.0);
                vColor = aColor;
            }
        )";

        // --- Fragment shader source ---
        const char *fragSrc = R"(
            #version 330 core
            in vec3 vColor;
            out vec4 FragColor;

            void main()
            {
                FragColor = vec4(vColor, 1.0);
            }
        )";

        // --- Compile shader program ---
        shader = new Core::Shader(vertSrc, fragSrc);

        // --- VAO ---
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        // --- VBO ---
        VBO = new Core::Buffer(Core::BufferType::Vertex);
        VBO->Bind();
        VBO->BufferData(vertices, sizeof(vertices));

        // --- Vertex attribs ---
        VBO->AddLayout(0, 0, 3);
        VBO->AddLayout(1, 3, 3);

        // --- Render test ---
        shader->Use();
        glBindVertexArray(VAO);
        VBO->Draw();

        return true;
    }

    bool EBOTest::Run(std::string &reason)
    {
        // --- Vertex data (square with colors) ---
        float vertices[] = {
            // positions        // colors
            -0.5f, 0.5f,  0.0f, 1.0f, 0.0f, 0.0f, // top-left (red)
            0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, // top-right (green)
            0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right (blue)
            -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f  // bottom-left (yellow)
        };

        unsigned int indices[] = {
            0, 1, 2, // first triangle
            2, 3, 0  // second triangle
        };

        // --- Vertex shader ---
        const char *vertSrc = R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec3 aColor;
            out vec3 vColor;
            void main() {
                gl_Position = vec4(aPos, 1.0);
                vColor = aColor;
            }
        )";

        // --- Fragment shader ---
        const char *fragSrc = R"(
            #version 330 core
            in vec3 vColor;
            out vec4 FragColor;
            void main() {
                FragColor = vec4(vColor, 1.0);
            }
        )";

        // --- Compile shader ---
        shader = new Core::Shader(vertSrc, fragSrc);

        // --- VAO ---
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        // --- VBO ---
        VBO = new Core::Buffer(Core::BufferType::Vertex);
        VBO->Bind();
        VBO->BufferData(vertices, sizeof(vertices));
        VBO->AddLayout(0, 0, 3); // position
        VBO->AddLayout(1, 3, 3); // color

        // --- EBO ---
        EBO = new Core::Buffer(Core::BufferType::Index);
        EBO->Bind();
        EBO->BufferData(indices, sizeof(indices));

        glBindVertexArray(0);

        // --- Render ---
        shader->Use();
        glBindVertexArray(VAO);
        EBO->Draw(); // draws using indices
                     //

        return true;
    }

} // namespace Core
