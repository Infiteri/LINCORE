#pragma once

#include "Base.h"
#include "Math/Vector.h"

namespace Core
{
    class CE_API Matrix4
    {
    public:
        union
        {
            float data[16];
            float m[4][4];
        };

        Matrix4();
        Matrix4(float *data);
        Matrix4(const Matrix4 &m);

        float *operator()() { return data; };

        static Matrix4 Perspective(float fov, float aspect, float near, float far);
        static Matrix4 Multiply(const Matrix4 &a, const Matrix4 &b);

        static Matrix4 Translate(const Vector3 &position);
    };
} // namespace Core
