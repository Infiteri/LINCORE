#pragma once

#include "Core/Application.h"
#include "Core/Entry/EngineLoop.h"

extern Core::Application *Core::CreateApplication();

int main(int argc, char **argv)
{
    Core::EngineLoop loop(Core::CreateApplication());
    loop.Start();
    loop.Run();
    loop.Shutdown();
}
