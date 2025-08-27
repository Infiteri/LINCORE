#include "EngineLoop.h"
#include "Core/Engine.h"
#include "Core/Logger.h"

namespace Core
{
    EngineLoop::EngineLoop(Application *application)
    {
        if (!application)
        {
            CE_ERROR("No application found when starting the engine loop");
        }

        app = application;
    }

    EngineLoop::~EngineLoop()
    {
        if (app)
            delete app;
    }

    void EngineLoop::Start()
    {
        // todo: Initialize and other engine specific stuff

        Engine::PreInit(app);
        Engine::Init();
    }

    void EngineLoop::Run()
    {
        while (!Engine::HasCloseRequest())
        {
            Engine::Update();
            Engine::Render();
        }
    }

    void EngineLoop::Shutdown()
    {
        Engine::Shutdown();
        delete app;
    }

} // namespace Core
