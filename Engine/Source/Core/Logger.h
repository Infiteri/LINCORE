#pragma once

#include "Base.h"

namespace Core
{
    enum class LogLevel
    {
        Trace,
        Debug,
        Info,
        Warn,
        Error
    };

    /// note: the colors here match 1:1 to the LogLevel, easier use but not so flexible
    /// todo: Maybe make it so that the logger can change which color is for each level, shouldn't
    /// be too hard
    enum class LogColor
    {
        White,
        Blue,
        Green,
        Yellow,
        Red
    };

    class CE_API Logger
    {
    public:
        static void Init();
        static void Shutdown();

        static void Log(LogLevel level, const char *msg, ...);
    };

} // namespace Core
