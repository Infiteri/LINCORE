#include "Layer.h"

namespace Core
{
    static LayerStack::State state;

    void LayerStack::Init() {}

    void LayerStack::Shutdown()
    {
        for (auto layer : state.layers)
        {
            layer->OnDetach();
            delete layer;
        }

        state.layers.clear();
    }

    void LayerStack::AddLayer(Layer *layer)
    {
        if (!layer)
            return;
        state.layers.push_back(layer);
        layer->OnAttach();
    }

    void LayerStack::Update()
    {
        for (auto &l : state.layers)
            l->OnUpdate();
    }

    void LayerStack::Render()
    {
        for (auto &l : state.layers)
            l->OnRender();
    }

    void LayerStack::RenderGui()
    {
        for (auto &l : state.layers)
            l->OnImGuiRender();
    }
} // namespace Core
