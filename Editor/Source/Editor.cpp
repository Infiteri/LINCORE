#include "Core/Application.h"
#include "Core/Entry/EntryPoint.h"
#include "Core/Input.h"
#include "Core/Layer/Layer.h"
#include "Core/Logger.h"
#include "Math/Transform.h"
#include "Math/Vector.h"
#include "Renderer/Buffer/Buffer.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Camera/PerspectiveCamera.h"
#include "Renderer/Color.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "imgui.h"
#include <glad/glad.h>
#include <vector>

#include <cstdlib> // for rand()
#include <ctime>   // for seeding

namespace Core
{
    struct Material
    {
        Color _Color; // later extend with textures, roughness, etc.
    };

    struct BatchRenderer
    {
        static const int MaxMeshCount = 10;

        GLuint vao = 0, vbo = 0, ebo = 0, instanceVBO = 0;
        GLuint materialSSBO = 0;
        VertexArray *array;
        Buffer *instanceBuffer;
        std::vector<Transform> transforms;
        std::vector<Material> materials;

        void Init()
        {

            // call once in Init()
            srand((unsigned)time(0));

            float vertices[] = {-0.5f, -0.5f, -0.5f, 1,    0,     0,     0.5f, -0.5f, -0.5f, 0,
                                1,     0,     0.5f,  0.5f, -0.5f, 0,     0,    1,     -0.5f, 0.5f,
                                -0.5f, 1,     1,     0,    -0.5f, -0.5f, 0.5f, 1,     0,     1,
                                0.5f,  -0.5f, 0.5f,  0,    1,     1,     0.5f, 0.5f,  0.5f,  1,
                                1,     1,     -0.5f, 0.5f, 0.5f,  0.3f,  0.7f, 0.2f};

            unsigned int indices[] = {0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4, 0, 4, 7, 7, 3, 0,
                                      1, 5, 6, 6, 2, 1, 3, 2, 6, 6, 7, 3, 0, 1, 5, 5, 4, 0};

            array = new VertexArray();

            array->GenerateVertexBuffer(vertices, sizeof(vertices));
            array->GenerateIndexBuffer(indices, sizeof(indices));

            // Position
            array->GetVertexBuffer()->AddLayout(0, 0, 3);
            array->GetVertexBuffer()->AddLayout(1, 3, 3);

            // Instance buffer
            // TODO: REFACTOR BUFFER CLASS TO SUPPORT THIS STUFF
            glGenBuffers(1, &instanceVBO);
            glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Matrix4) * MaxMeshCount, nullptr, GL_DYNAMIC_DRAW);

            for (int i = 0; i < 4; i++)
            {
                glEnableVertexAttribArray(2 + i);
                glVertexAttribPointer(2 + i, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix4),
                                      (void *)(sizeof(float) * 4 * i));
                glVertexAttribDivisor(2 + i, 1);
            }

            glGenBuffers(1, &materialSSBO);

            glBindBuffer(GL_SHADER_STORAGE_BUFFER, materialSSBO);
            glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(Material) * MaxMeshCount, nullptr,
                         GL_DYNAMIC_DRAW);
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, materialSSBO);

            glBindVertexArray(0);
        }

        void AddCube(const Transform &t, const Material &m)
        {
            transforms.push_back(t);
            materials.push_back(m);

            if (transforms.size() >= MaxMeshCount)
            {
                // Flush and immediately render the batch
                Flush();
                Render();
            }
        }

        void Flush()
        {
            if (transforms.empty())
                return;

            std::vector<Matrix4> mats;
            for (auto &t : transforms)
                mats.push_back(t.GetMatrix());

            glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, mats.size() * sizeof(Matrix4), mats.data());

            glBindBuffer(GL_SHADER_STORAGE_BUFFER, materialSSBO);
            glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, materials.size() * sizeof(Material),
                            materials.data());
        }

        void Render()
        {
            if (transforms.empty())
                return;

            array->Bind();
            glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, transforms.size());
            array->Unbind();

            Clear();
        }

        void Clear()
        {
            transforms.clear();
            materials.clear();
        }
    };

    static BatchRenderer cubeBatch;
    static Shader *shader;
    static PerspectiveCamera cam{90, 1280.f / 720, 0.001, 1000};

    class EditorLayer : public Layer
    {
    public:
        void OnImGuiRender()
        {
            ImGui::Begin("Editor");
            float f = cam.GetFOV();
            if (ImGui::DragFloat("FOV", &f, 0.04f))
                cam.SetFOV(f);
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

            cubeBatch.Init();
        }

        void Render()
        {
            shader->Use();
            shader->Mat4(cam.GetProjection(), "uProjection");
            shader->Mat4(Matrix4::Invert(cam.GetView()), "uView");

            // Add 100 cubes in grid

            for (int x = -5; x < 5; x++)
                for (int y = -5; y < 5; y++)
                {
                    Transform t;
                    t.Position = {float(x * 2), float(y * 2), -20};
                    t.Scale = {1, 1, 1};

                    Material m;
                    m._Color = {float(rand()), float(rand()), float(rand()), 255};
                    CE_DEBUG("%f %f %f %f", m._Color.r, m._Color.g, m._Color.b, m._Color.a);

                    cubeBatch.AddCube(t, m);
                }
            // flush before render to ensure GPU has transforms
            cubeBatch.Flush();
            cubeBatch.Render();
        }
    };

    Application *CreateApplication() { return new EditorApplication(); }
} // namespace Core
