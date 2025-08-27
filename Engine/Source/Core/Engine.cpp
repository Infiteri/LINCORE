#include "Engine.h"
#include "Core/Logger.h"
#include "Core/Window.h"
#include "Renderer/Renderer.h"
#include <memory>

namespace Core
{
    static Engine::State state;

    void Engine::PreInit(Application *app)
    {
        state.AppInstance = app;
        Logger::Init();

        WindowConfiguration config;
        config.Title = "Engine";
        config.Width = 1280;
        config.Height = 720;

        // todo: Better naming please
        state._Window = std::make_shared<Window>(config);

        Renderer::Init();
    }

    void Engine::Init()
    {
        if (state.AppInstance)
            state.AppInstance->Init();
    }

    bool Engine::HasCloseRequest() { return state._Window->HasCloseRequest(); }

    void Engine::Update()
    {
        if (state.AppInstance)
            state.AppInstance->Update();
    }

    void Engine::Render()
    {
        Renderer::BeginFrame();
        Renderer::Render();

        if (state.AppInstance)
            state.AppInstance->Render();

        Renderer::EndFrame();

        state._Window->Update();
    }

    void Engine::Shutdown()
    {
        if (state.AppInstance)
            state.AppInstance->Shutdown();
    }
} // namespace Core
