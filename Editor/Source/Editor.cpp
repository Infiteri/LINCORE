#include "Core/Application.h"
#include "Core/Entry/EntryPoint.h"
#include "Core/Input.h"
#include "Core/Layer/Layer.h"
#include "Core/Logger.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Shader.h"
#include "imgui.h"
#include <glad/glad.h>

namespace Core
{
    static VertexArray *array;
    static Shader *shader;

    class EditorLayer : public Layer
    {
    public:
        void OnImGuiRender()
        {
            ImGui::Begin("Hello");
            ImGui::End();
        }
    };

    class EditorApplication : public Application
    {
    public:
        void Init()
        {
            LayerStack::AddLayer(new EditorLayer());
            shader = new Shader("Shader.glsl");

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

            array = new VertexArray();

            array->GenerateVertexBuffer(vertices, sizeof(vertices));
            array->GetVertexBuffer()->AddLayout(0, 0, 3);
            array->GetVertexBuffer()->AddLayout(1, 3, 3);

            array->GenerateIndexBuffer(indices, sizeof(indices));
        }

        void Render()
        {
            if (Input::IsPressed(Keys::A))
                Input::SetMouseMode(MouseModes::Hidden);

            if (Input::IsPressed(Keys::D))
                Input::SetMouseMode(MouseModes::Locked);

            if (Input::IsPressed(Keys::S))
                Input::SetMouseMode(MouseModes::Visible);

            shader->Use();
            array->Bind();
            array->GetIndexBuffer()->Draw();
        }
    };

    Application *CreateApplication() { return new EditorApplication(); }
} // namespace Core
