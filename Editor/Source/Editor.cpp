#include "Core/Logger.h"
#include "Core/Window.h"
int main()
{

    Core::Logger::Init();
    Core::WindowConfiguration config{.Width = 1280,
                                     .Height = 720,
                                     .Title = "Hello world",
                                     .SizeMode = Core::WindowSizeMode::Windowed};
    Core::Window window(config);

    while (!window.HasCloseRequest())
        window.Update();
}
