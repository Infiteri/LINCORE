#include "Color.h"

namespace Core
{
    Color::Color() { *this = {255, 255, 255, 255}; }

    Color::Color(const Color &other) { *this = {other.r, other.g, other.b, other.a}; }

    Color::Color(float r, float g, float b, float a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    Color Color::Normalized() const { return {r / 255, g / 255, b / 255, a / 255}; }
} // namespace Core
