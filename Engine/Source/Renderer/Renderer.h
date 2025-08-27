#pragma once

#include "Base.h"

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

        struct State
        {
            struct Viewport Viewport;
        };
    };
} // namespace Core
