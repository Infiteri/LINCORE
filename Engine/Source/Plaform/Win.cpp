#include "Base.h"

#if CE_PLATFORM == CE_PLATFORM_WIN
#include "Platform.h"
#include <windows.h>

namespace Core
{

    void Platform::SetLogColor(LogColor color)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        WORD colorAttribute = FOREGROUND_INTENSITY; // Default to high-intensity (bright) text

        switch (color)
        {
        case LogColor::White:
            colorAttribute |= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
            break;

        case LogColor::Red:
            colorAttribute |= FOREGROUND_RED;
            break;

        case LogColor::Blue:
            colorAttribute |= FOREGROUND_BLUE;
            break;

        case LogColor::Green:
            colorAttribute |= FOREGROUND_GREEN;
            break;

        case LogColor::Yellow:
            colorAttribute |= FOREGROUND_RED | FOREGROUND_GREEN;
            break;

        default:
            // Default to white if an unsupported color is specified
            colorAttribute |= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
            break;
        }

        SetConsoleTextAttribute(hConsole, colorAttribute);
    }

    void Platform::OutputMessage(const char *msg)
    {
        OutputDebugStringA(msg);
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD bytesWritten;
        WriteConsoleA(hConsole, msg, strlen(msg), &bytesWritten, NULL);
    }
} // namespace Core
#endif
