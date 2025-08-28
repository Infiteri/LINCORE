#pragma once

#include "Base.h"
#include "Renderer/Buffer/Framebuffer.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Shader.h"
#include <memory>

namespace Core
{
    class CE_API Renderer
    {
    public:
        static void Init();
        static void Shutdown();

        static void BeginFrame();
        static void Render();
        static void EndFrame();

        static void Viewport(float width, float height);

    public:
        struct Viewport
        {
            float Width;
            float Height;
            inline const float GetAspect() { return Width / Height; };
        };

        static const struct Viewport &GetViewport();

        struct GPUScreen
        {
            std::unique_ptr<VertexArray> Array;
            std::unique_ptr<Framebuffer> Buffer;
            std::shared_ptr<Shader> ScreenShader;
        };

        struct State
        {
            struct Viewport Viewport;
            GPUScreen Screen;
        };

    private:
        static void AfterResize();

        static void InitializeGPUScreen();
        static void BeginGPUScreenFrame();
        static void EndGPUScreenFrame();
        static void ResizeGPUScreen();
    };
} // namespace Core
