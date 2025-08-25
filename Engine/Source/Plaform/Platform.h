#pragma once

#include "Core/Logger.h"

namespace Core
{
    class Platform
    {
    public:
        static void SetLogColor(LogColor color);
        static void OutputMessage(const char *message);
    };
} // namespace Core
