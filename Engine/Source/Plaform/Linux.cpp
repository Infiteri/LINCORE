#include "Base.h"

#if CE_PLATFORM == CE_PLATFORM_LINUX
#include "Platform.h"
#include <iostream>

namespace Core
{

    struct RGB
    {
        int r, g, b;
    };

    static RGB LogColorToRGB(LogColor color)
    {
        switch (color)
        {
        case LogColor::Red:
            return {255, 50, 50};
        case LogColor::Green:
            return {50, 255, 50};
        case LogColor::Yellow:
            return {255, 255, 0};
        case LogColor::Blue:
            return {50, 50, 255};
        case LogColor::White:
            return {255, 255, 255};
        default:
            return {255, 255, 255};
        }
    }

    void Platform::SetLogColor(LogColor color)
    {
        RGB c = LogColorToRGB(color);
        std::cout << "\033[38;2;" << c.r << ";" << c.g << ";" << c.b << "m";
    }

    void Platform::OutputMessage(const char *message)
    {
        std::cout << message << "\033[0m"; // reset color
    }

} // namespace Core
#endif
