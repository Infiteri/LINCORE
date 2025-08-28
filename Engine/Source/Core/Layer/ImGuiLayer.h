#pragma once

#define CE_IMPLEMENT_GUI_LAYER 1

namespace Core
{
    class ImGuiLayer
    {
    public:
        static void Init();
        static void Shutdown();

        static void BeginFrame();
        static void EndFrame();

        static void SetDefaultTheme();
    };

} // namespace Core
