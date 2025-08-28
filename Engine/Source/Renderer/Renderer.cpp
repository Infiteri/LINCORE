#include "Renderer.h"
#include "Renderer/Buffer/Framebuffer.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Shader.h"
#include <glad/glad.h>
#include <vector>

namespace Core
{
    static Renderer::State state;

    void Renderer::AfterResize()
    {
        glViewport(0, 0, state.Viewport.Width, state.Viewport.Height);

        ResizeGPUScreen();
    }

    void Renderer::Init()
    {
        gladLoadGL();

        InitializeGPUScreen();

        Viewport(1280, 720);
    }

    void Renderer::Shutdown() {}

    void Renderer::BeginFrame() { BeginGPUScreenFrame(); }

    void Renderer::Render()
    {
        glClearColor(.2, .3, .4, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::EndFrame()
    {
        EndGPUScreenFrame();

        // todo: Somewhere else?
        FBRenderPass *pass = state.Screen.Buffer->GetRenderPass(0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, pass->Id);
        state.Screen.ScreenShader->Int(0, "uScreenTexture");
        state.Screen.ScreenShader->Use();
        state.Screen.Array->Bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void Renderer::Viewport(float width, float height)
    {
        state.Viewport.Width = width;
        state.Viewport.Height = height;
        AfterResize();
    }

    const struct Renderer::Viewport &Renderer::GetViewport() { return state.Viewport; }

    // -- GPU Screen --
    void Renderer::InitializeGPUScreen()
    {
        GPUScreen &s = state.Screen;
        // array
        {
            float screenQuadVertices[] = {
                -1.0f, 1.0f, 0.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f,

                -1.0f, 1.0f, 0.0f, 1.0f, 1.0f,  -1.0f, 1.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f};

            s.Array = std::make_unique<VertexArray>();
            s.Array->GenerateVertexBuffer(screenQuadVertices, sizeof(screenQuadVertices));
            s.Array->GetVertexBuffer()->AddLayout(0, 0, 2); // pos.xy
            s.Array->GetVertexBuffer()->AddLayout(1, 2, 2); // uv.xy
        }

        // Buffer
        {
            FramebufferConfiguration config;
            config.Width = state.Viewport.Width;
            config.Height = state.Viewport.Height;
            config.Passes.push_back({.Type = RPTextureType::Rgb});   // color
            config.Passes.push_back({.Type = RPTextureType::Depth}); // depth
            s.Buffer = std::make_unique<Framebuffer>(config);
        }

        // todo: From 'system' when in place
        // shader
        {
            s.ScreenShader = std::make_shared<Shader>("Screen.glsl");
        }
    }

    void Renderer::BeginGPUScreenFrame()
    {
        GPUScreen &s = state.Screen;
        s.Buffer->Bind();
        glEnable(GL_DEPTH_TEST);
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Renderer::EndGPUScreenFrame()
    {
        GPUScreen &s = state.Screen;
        s.Buffer->Unbind();
        glDisable(GL_DEPTH_TEST);
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::ResizeGPUScreen()
    {
        GPUScreen &s = state.Screen;
        s.Buffer->Resize(state.Viewport.Width, state.Viewport.Height);
    }
    // ................
} // namespace Core
