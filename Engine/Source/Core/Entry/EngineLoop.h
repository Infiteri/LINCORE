#pragma once

#include "Core/Application.h"
namespace Core
{
    class CE_API EngineLoop
    {
    public:
        EngineLoop(Application *application);
        ~EngineLoop();

        void Start();
        void Run();
        void Shutdown();

    private:
        Application *app;
    };
} // namespace Core
