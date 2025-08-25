#include "Window.h"
#include "Core/Logger.h"
#include <GLFW/glfw3.h>
#include <cstddef>

namespace Core
{
    Window::Window(WindowConfiguration &config)
    {
        if (!glfwInit())
        {
            CE_ERROR("Cannot initialize GLFW");
            return;
        }

        glfwWindowHint(GLFW_VISIBLE, false);

        GLFWmonitor *monitor = nullptr;
        if (config.SizeMode == WindowSizeMode::Fullscreen)
        {
            monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode *mode = glfwGetVideoMode(monitor);
            config.Width = mode->width;
            config.Height = mode->height;
        }

        handle = glfwCreateWindow(config.Width, config.Height, config.Title, monitor, nullptr);
        glfwMakeContextCurrent(handle);
        glfwShowWindow(handle);

        if (config.SizeMode == WindowSizeMode::Windowed)
        {

#if CE_PLATFORM == CE_PLATFORM_LINUX
            int x, y, w, h;
            GLFWmonitor *primary = glfwGetPrimaryMonitor();
            glfwGetMonitorWorkarea(primary, &x, &y, &w, &h);
            // close approx as linux doesnt really work well with maximized windows?
            glfwSetWindowSize(handle, w, h - 30);
            glfwSetWindowPos(handle, x, y);
#else
            glfwMaximizeWindow(handle); // Windows/macOS
#endif
        }
    }

    Window::~Window()
    {
        glfwDestroyWindow(handle);
        glfwTerminate();
    }

    bool Window::HasCloseRequest() { return glfwWindowShouldClose(handle); }

    void Window::Update()
    {
        glfwPollEvents();
        glfwSwapBuffers(handle);
    }

} // namespace Core
