#include "Vector.h"

namespace Core
{
    Vector2::Vector2() { x = y = 0; }

    Vector2::Vector2(const Vector2 &other)
    {
        x = other.x;
        y = other.y;
    }

    Vector2::Vector2(float x, float y) : x(x), y(y) {}

    void Vector2::Set(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
} // namespace Core
