#include "Input.h"
#include "Core/Engine.h"
#include <GLFW/glfw3.h>

namespace Core
{
    static Input::State state;

    bool Input::IsPressed(Keys key) { return state.Key.Keys[key]; }

    bool Input::IsNotPressed(Keys key) { return !state.Key.Keys[key]; }

    bool Input::IsPressed(Buttons button) { return state.Mouse.Button[button]; }

    bool Input::IsNotPressed(Buttons button) { return !state.Mouse.Button[button]; }

    Vector2 Input::GetMousePosition() { return state.Mouse.Position; }

    Vector2 Input::GetMouseDelta() { return state.Mouse.Position - state.Mouse.Last; }

    void Input::SetMouseMode(MouseModes mode)
    {
        if (state.Mouse.Mode == mode)
            return;

        state.Mouse.Mode = mode;
        auto window = Engine::GetWindow();
        int glfw;

        switch (mode)
        {
        case MouseModes::Hidden:
            glfw = GLFW_CURSOR_HIDDEN;
            break;

        case MouseModes::Locked:
            glfw = GLFW_CURSOR_DISABLED;
            break;

        default:
        case MouseModes::Visible:
            glfw = GLFW_CURSOR_NORMAL;
            break;
        }

        glfwSetInputMode(window->GetHandle(), GLFW_CURSOR, glfw);
    }

    // -- INTERNAL --
    void Input::InternalUpdateKey(Keys key, bool pressed)
    {
        state.Key.Last[key] = state.Key.Keys[key];
        state.Key.Keys[key] = pressed;
    }

    void Input::InternalUpdateButton(Buttons btn, bool prsd) { state.Mouse.Button[btn] = prsd; }

    void Input::InternalUpdateMouse(int x, int y)
    {
        state.Mouse.Last = state.Mouse.Position;
        state.Mouse.Position = {(float)x, (float)y};
    }
    // .................
} // namespace Core
