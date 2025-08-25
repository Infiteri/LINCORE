#include "Logger.h"
#include "Plaform/Platform.h"

#include <cstdarg>
#include <iostream>
#include <string>

namespace Core
{
    static const char *const LevelToString[] = {"Trace", "Debug", "Info", "Warn", "Error"};

    void Logger::Init() {}

    void Logger::Shutdown() {}

    void Logger::Log(LogLevel level, const char *msg, ...)
    {
#define LOG_MSG_SIZE 24000

        const char *strLevel = LevelToString[static_cast<int>(level)];
        LogColor color = (LogColor)level;

        char message[LOG_MSG_SIZE];

        va_list args;
        va_start(args, msg);
        int ret = std::vsnprintf(message, LOG_MSG_SIZE, msg, args);
        va_end(args);

        if (ret < 0)
            return;

        char finalMsg[LOG_MSG_SIZE];
        std::snprintf(finalMsg, LOG_MSG_SIZE, "[%s]: %s\n", strLevel, message);

        Platform::SetLogColor(color);
        Platform::OutputMessage(finalMsg);
    }

} // namespace Core
