#pragma once

#include "Base.h"

namespace Core
{
    class Application
    {
    public:
        Application() {};
        virtual ~Application() {};

        virtual void Init() {};
        virtual void Render() {};
        virtual void Update() {};
        virtual void Shutdown() {};
    };

    Application *CreateApplication();
} // namespace Core
