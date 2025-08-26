#pragma once

#include "Core/Application.h"
namespace Core
{

    class EngineLoop
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
