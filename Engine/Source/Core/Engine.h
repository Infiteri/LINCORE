#pragma once

#include "Base.h"
#include "Core/Window.h"
#include <memory>

namespace Core
{
    class CE_API Engine
    {
    public:
        struct State
        {
            std::shared_ptr<Window> _Window;
        };

    public:
        static void PreInit();
        static void Init();

        static bool HasCloseRequest();
        static void Update();
        static void Render();

        static void Shutdown();
    };
} // namespace Core
