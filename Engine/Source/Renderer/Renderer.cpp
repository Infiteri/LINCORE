
#include "Renderer.h"
#include "Core/Logger.h"
#include "Renderer/Buffer/Framebuffer.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Shader.h"
#include <glad/glad.h>
#include <vector>

namespace Core
{
    static Renderer::State state;
    static Framebuffer *buffer;
    static VertexArray *array;
    static Shader *shader;

    // fullscreen quad: pos.xy, uv.xy
    static float screenQuadVertices[] = {
        -1.0f, 1.0f, 0.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f,

        -1.0f, 1.0f, 0.0f, 1.0f, 1.0f,  -1.0f, 1.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f};

    static void AfterResize() { glViewport(0, 0, state.Viewport.Width, state.Viewport.Height); }

    void Renderer::Init()
    {
        gladLoadGL();

        Viewport(1280, 720);

        // ---------------- Framebuffer ----------------
        FramebufferConfiguration config;
        config.Width = state.Viewport.Width;
        config.Height = state.Viewport.Height;
        config.Passes.push_back({.Type = RPTextureType::Rgb});   // color
        config.Passes.push_back({.Type = RPTextureType::Depth}); // depth
        buffer = new Framebuffer(config);

        // ---------------- Fullscreen Quad ----------------
        array = new VertexArray();
        array->GenerateVertexBuffer(screenQuadVertices, sizeof(screenQuadVertices));
        array->GetVertexBuffer()->AddLayout(0, 0, 2); // pos.xy
        array->GetVertexBuffer()->AddLayout(1, 2, 2); // uv.xy

        // ---------------- Shader ----------------
        shader = new Shader("Screen.glsl");
        shader->Use();
        shader->Int(0, "uScreenTexture"); // always use texture unit 0
    }

    void Renderer::Shutdown() {}

    void Renderer::BeginFrame()
    {
        buffer->Bind();
        glEnable(GL_DEPTH_TEST);
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Renderer::Render()
    {
        glClearColor(.2, .3, .4, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::EndFrame()
    {
        buffer->Unbind();
        glDisable(GL_DEPTH_TEST);
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        // Bind framebuffer texture
        FBRenderPass *pass = buffer->GetRenderPass(0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, pass->Id);
        shader->Int(0, "uScreenTexture");

        // Draw fullscreen quad
        shader->Use();
        array->Bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void Renderer::Viewport(float width, float height)
    {
        state.Viewport.Width = width;
        state.Viewport.Height = height;
        AfterResize();
    }

    const struct Renderer::Viewport &Renderer::GetViewport() { return state.Viewport; }
} // namespace Core
// namespace Core
