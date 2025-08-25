#include "Core/Logger.h"
int main()
{

    Core::Logger::Init();
    CE_INFO("A %s", "S");
    CE_DEBUG("A %s", "S");
    CE_TRACE("A %s", "S");
    CE_WARN("A %s", "S");
    CE_ERROR("A %s", "S");

    while (true)
        ;
}
