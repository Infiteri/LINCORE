#pragma once

#include "Base.h"

namespace Core
{
    struct Color
    {
        union
        {
            struct
            {
                float r, g, b, a;
            };

            float v[4];
        };

        Color();
        Color(const Color &other);
        Color(float r, float g, float b, float a);

        Color Normalized() const;
    };
} // namespace Core
