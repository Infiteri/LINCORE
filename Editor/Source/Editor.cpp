#include "Core/Application.h"
#include "Core/Entry/EntryPoint.h"
#include "Core/Input.h"
#include "Core/Layer/Layer.h"
#include "Core/Logger.h"
#include "Math/Matrix.h"
#include "Math/Vector.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Camera/Camera.h"
#include "Renderer/Camera/PerspectiveCamera.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "imgui.h"
#include <glad/glad.h>

namespace Core
{
    static VertexArray *array;
    static Shader *shader;
    static PerspectiveCamera cam{90, 1280.f / 720, 0.001, 1000};

    class EditorLayer : public Layer
    {
    public:
        void OnImGuiRender()
        {
            ImGui::Begin("Hello");

            float f = cam.GetFOV();
            if (ImGui::DragFloat("FOV", &f, 0.04))
            {
                cam.SetFOV(f);
            }

            ImGui::End();
        }
    };

    class EditorApplication : public Application
    {
    public:
        void Init()
        {
            cam = PerspectiveCamera();

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
            {
                cam.GetPosition().z -= .5;
                cam.UpdateView();
            }

            if (Input::IsPressed(Keys::D))
            {
                cam.GetPosition().z += .5;
                cam.UpdateView();
            }

            cam.UpdateProjection(Renderer::GetViewport().GetAspect());

            shader->Use();
            shader->Mat4(cam.GetProjection(), "uProjection");
            shader->Mat4(cam.GetView(), "uView");
            array->Bind();
            array->GetIndexBuffer()->Draw();
        }
    };

    Application *CreateApplication() { return new EditorApplication(); }
} // namespace Core
