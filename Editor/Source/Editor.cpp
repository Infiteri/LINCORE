#include "Core/Application.h"
#include "Core/Entry/EntryPoint.h"
#include "Core/Input.h"
#include "Core/Layer/Layer.h"
#include "Math/Transform.h"
#include "Math/Vector.h"
#include "Renderer/Buffer/VertexArray.h"
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

    Transform t;

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

            ImGui::DragFloat3("position", &t[0].x, 0.04);
            ImGui::DragFloat3("rotation", &t[1].x, 0.04);
            ImGui::DragFloat3("scale", &t[2].x, 0.04);

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

            float vertices[] = {// positions          // colors
                                -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  0.0f,  0.5f, -0.5f, -0.5f, 0.0f,
                                1.0f,  0.0f,  0.5f,  0.5f, -0.5f, 0.0f,  0.0f, 1.0f,  -0.5f, 0.5f,
                                -0.5f, 1.0f,  1.0f,  0.0f, -0.5f, -0.5f, 0.5f, 1.0f,  0.0f,  1.0f,
                                0.5f,  -0.5f, 0.5f,  0.0f, 1.0f,  1.0f,  0.5f, 0.5f,  0.5f,  1.0f,
                                1.0f,  1.0f,  -0.5f, 0.5f, 0.5f,  0.0f,  0.0f, 0.0f};

            unsigned int indices[] = {
                0, 1, 2, 2, 3, 0, // back
                4, 5, 6, 6, 7, 4, // front
                0, 4, 7, 7, 3, 0, // left
                1, 5, 6, 6, 2, 1, // right
                3, 2, 6, 6, 7, 3, // top
                0, 1, 5, 5, 4, 0  // bottom
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
            shader->Mat4(Matrix4::Invert(cam.GetView()), "uView");
            shader->Mat4(t.GetMatrix(), "uTransform");
            array->Bind();
            array->GetIndexBuffer()->Draw();
        }
    };

    Application *CreateApplication() { return new EditorApplication(); }
} // namespace Core
