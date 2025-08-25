#include "Core/Logger.h"
int main()
{

    Core::Logger::Init();
    Core::Logger::Log(Core::LogLevel::Info, "A %s", "S");
    Core::Logger::Log(Core::LogLevel::Debug, "A %s", "S");
    Core::Logger::Log(Core::LogLevel::Trace, "A %s", "S");
    Core::Logger::Log(Core::LogLevel::Warn, "A %s", "S");
    Core::Logger::Log(Core::LogLevel::Error, "A %s", "S");

    while (true)
        ;
}
