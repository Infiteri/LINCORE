#pragma once

#include "Test.h"

namespace Core
{
    class VBOTest : public Test
    {
    public:
        bool Run(std::string &reason);
    };

    class EBOTest : public Test
    {
    public:
        bool Run(std::string &reason);
    };
} // namespace Core
