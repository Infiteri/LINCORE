#include "Renderer.h"
#include <glad/glad.h>

namespace Core
{
    static Renderer::State state;

    // note: To keep concise and simple, some functions will be declared here
    static void AfterResize() { glViewport(0, 0, state.Viewport.Width, state.Viewport.Height); }

    void Renderer::Init() { gladLoadGL(); }

    void Renderer::Shutdown() {}

    void Renderer::BeginFrame() {}

    void Renderer::Render()
    {
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::EndFrame() {}

    void Renderer::Viewport(float width, float height)
    {
        state.Viewport.Width = width;
        state.Viewport.Height = height;

        AfterResize();
    }

    const struct Renderer::Viewport &Renderer::GetViewport() { return state.Viewport; }
} // namespace Core
