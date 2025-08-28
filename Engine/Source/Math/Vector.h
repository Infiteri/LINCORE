#pragma once

#include "Base.h"

namespace Core
{
    class CE_API Vector2
    {
    public:
        float x, y;

        Vector2();
        Vector2(const Vector2 &other);
        Vector2(float x, float y);
        ~Vector2() = default;

        Vector2 operator+(const Vector2 &other) const { return Vector2(x + other.x, y + other.y); }

        Vector2 operator-(const Vector2 &other) const { return Vector2(x - other.x, y - other.y); }

        Vector2 operator*(float scalar) const { return Vector2(x * scalar, y * scalar); }

        Vector2 operator/(float scalar) const { return Vector2(x / scalar, y / scalar); }

        Vector2 operator*(const Vector2 &other) const { return Vector2(x * other.x, y * other.y); }

        bool operator==(const Vector2 &other) const { return x == other.x && y == other.y; }

        bool operator!=(const Vector2 &other) const { return !(*this == other); }

        void Set(float x, float y);
    };

} // namespace Core
