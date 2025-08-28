#include "Window.h"
#include "Core/Input.h"
#include "Core/Logger.h"
#include "Renderer/Renderer.h"
#include <GLFW/glfw3.h>

namespace Core
{
    static void OnResize(GLFWwindow *_, int w, int h) { Renderer::Viewport(w, h); }

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

        // bind callbacks
        glfwSetWindowSizeCallback(handle, OnResize);

        glfwGetWindowSize(handle, &config.Width, &config.Height);
        UpdateState();
    }

    Window::~Window()
    {
        glfwDestroyWindow(handle);
        glfwTerminate();
    }

    bool Window::HasCloseRequest() { return glfwWindowShouldClose(handle); }

    void Window::Update()
    {

        double x, y;
        glfwGetCursorPos(handle, &x, &y);
        Input::InternalUpdateMouse((int)x, (int)y);

        for (int key = 0; key < GLFW_KEY_LAST; key++)
            Input::InternalUpdateKey((Keys)key, glfwGetKey(handle, key) != 0);

        for (int button = 0; button < GLFW_MOUSE_BUTTON_LAST; button++)
            Input::InternalUpdateButton((Buttons)button, glfwGetMouseButton(handle, button) != 0);

        glfwPollEvents();
        UpdateState();
        glfwSwapBuffers(handle);
    }

    void Window::UpdateState() { glfwGetWindowSize(handle, &state.Width, &state.Height); }
} // namespace Core
