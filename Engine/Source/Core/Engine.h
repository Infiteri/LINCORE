#pragma once

#include "Base.h"
#include "Core/Application.h"
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
            Application *AppInstance;
        };

    public:
        static void PreInit(Application *app);
        static void Init();

        static bool HasCloseRequest();
        static void Update();
        static void Render();

        static void Shutdown();

        static std::shared_ptr<Window> GetWindow();
    };
} // namespace Core
