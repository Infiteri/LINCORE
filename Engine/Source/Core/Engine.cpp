#include "Engine.h"
#include "Core/Logger.h"
#include "Core/Window.h"
#include <memory>

namespace Core
{
    static Engine::State state;

    void Engine::PreInit()
    {
        WindowConfiguration config;
        config.Width = 1280;
        config.Height = 720;

        // todo: Better naming please
        state._Window = std::make_shared<Window>(config);

        Logger::Init();
    }

    void Engine::Init() {}

    bool Engine::HasCloseRequest() { return state._Window->HasCloseRequest(); }

    void Engine::Update() {}

    void Engine::Render() { state._Window->Update(); }

    void Engine::Shutdown() {}
} // namespace Core
