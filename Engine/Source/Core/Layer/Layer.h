#pragma once

#include "Base.h"
#include <vector>

namespace Core
{
    class CE_API Layer
    {
    public:
        virtual ~Layer() {};

        virtual void OnAttach() {};
        virtual void OnRender() {};
        virtual void OnUpdate() {};
        virtual void OnImGuiRender() {};
        virtual void OnDetach() {};
    };

    /// note: Due to the nature of layers and inheritance, smart ptrs would be a bit harder to
    /// implement todo: Smart ptrs sholdnt be *that* be so future me think abt it :)
    class CE_API LayerStack
    {
    public:
        static void Init();
        static void Shutdown();

        /// note: Adds a layer, the ownership remains to the user until the "LayerStack::Shutdown"
        /// function is called (they all get deleted there) note: Due to this, its best to do
        /// "LayerStack::AddLayer(new MyLayerClass());" as to not have issues with the ownership of
        /// the class
        /// note: This could be fixed using a smart pointer approach which is planned for the future
        /// as I don't want to spend too much time implementing something this trivial (dare I say
        /// overengineer (I know its not but still :))
        static void AddLayer(Layer *layer);

        static void Update();
        static void Render();
        static void RenderGui();

    public:
        struct State
        {
            std::vector<Layer *> layers;
        };
    };
} // namespace Core
