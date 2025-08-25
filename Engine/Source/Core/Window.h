#pragma once

#include "Base.h"

typedef struct GLFWwindow GLFWwindow;

namespace Core
{

    enum class WindowSizeMode
    {
        Normal,
        Fullscreen,
        Windowed
    };

    struct WindowConfiguration
    {
        int Width, Height;
        const char *Title;
        WindowSizeMode SizeMode = WindowSizeMode::Normal;
    };

    class CE_API Window
    {
    public:
        /// @brief Creates a Window
        /// note: Note that the configuration passed in may change if the SizeMode is not
        /// WindowsizeMode::Normal. This happens due to the fact that the Width and Height get reset
        /// to the right values note: For example if the SizeMode is WindwoSizeMode::Fullscreen the
        /// width and height will change to the right values
        Window(WindowConfiguration &config);
        ~Window();

        bool HasCloseRequest();
        void Update();

    private:
        GLFWwindow *handle;
    };
} // namespace Core
