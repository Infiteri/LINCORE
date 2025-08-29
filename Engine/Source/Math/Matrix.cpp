#include "Matrix.h"
#include <cmath>

namespace Core
{
    Matrix4::Matrix4()
    {
        // identity matrix
        for (int i = 0; i < 16; i++)
            data[i] = (i == 0 || i == 5 || i == 10 || i == 15) ? 1 : 0;
    }

    Matrix4::Matrix4(float *data)
    {
        // note: Not really safe
        for (int i = 0; i < 16; i++)
            this->data[i] = data[i];
    }

    Matrix4::Matrix4(const Matrix4 &m)
    {
        for (int i = 0; i < 16; i++)
            data[i] = m.data[i];
    }

    Matrix4 Matrix4::Perspective(float fov, float aspect, float near, float far)
    {
        Matrix4 m;

        float f = 1.0 / tanf(fov / 2);
        m.data[0] = f / aspect;
        m.data[1] = 0;
        m.data[2] = 0;
        m.data[3] = 0;
        m.data[4] = 0;
        m.data[5] = f;
        m.data[6] = 0;
        m.data[7] = 0;
        m.data[8] = 0;
        m.data[9] = 0;
        m.data[11] = -1;
        m.data[12] = 0;
        m.data[13] = 0;
        m.data[15] = 0;
        m.data[10] = -1;
        m.data[14] = -2 * near;

        return m;
    }

    Matrix4 Matrix4::Multiply(const Matrix4 &a, const Matrix4 &b)
    {
        Matrix4 m;
        float b00 = b.data[0 * 4 + 0];
        float b01 = b.data[0 * 4 + 1];
        float b02 = b.data[0 * 4 + 2];
        float b03 = b.data[0 * 4 + 3];
        float b10 = b.data[1 * 4 + 0];
        float b11 = b.data[1 * 4 + 1];
        float b12 = b.data[1 * 4 + 2];
        float b13 = b.data[1 * 4 + 3];
        float b20 = b.data[2 * 4 + 0];
        float b21 = b.data[2 * 4 + 1];
        float b22 = b.data[2 * 4 + 2];
        float b23 = b.data[2 * 4 + 3];
        float b30 = b.data[3 * 4 + 0];
        float b31 = b.data[3 * 4 + 1];
        float b32 = b.data[3 * 4 + 2];
        float b33 = b.data[3 * 4 + 3];
        float a00 = a.data[0 * 4 + 0];
        float a01 = a.data[0 * 4 + 1];
        float a02 = a.data[0 * 4 + 2];
        float a03 = a.data[0 * 4 + 3];
        float a10 = a.data[1 * 4 + 0];
        float a11 = a.data[1 * 4 + 1];
        float a12 = a.data[1 * 4 + 2];
        float a13 = a.data[1 * 4 + 3];
        float a20 = a.data[2 * 4 + 0];
        float a21 = a.data[2 * 4 + 1];
        float a22 = a.data[2 * 4 + 2];
        float a23 = a.data[2 * 4 + 3];
        float a30 = a.data[3 * 4 + 0];
        float a31 = a.data[3 * 4 + 1];
        float a32 = a.data[3 * 4 + 2];
        float a33 = a.data[3 * 4 + 3];
        m.data[0] = b00 * a00 + b01 * a10 + b02 * a20 + b03 * a30;
        m.data[1] = b00 * a01 + b01 * a11 + b02 * a21 + b03 * a31;
        m.data[2] = b00 * a02 + b01 * a12 + b02 * a22 + b03 * a32;
        m.data[3] = b00 * a03 + b01 * a13 + b02 * a23 + b03 * a33;
        m.data[4] = b10 * a00 + b11 * a10 + b12 * a20 + b13 * a30;
        m.data[5] = b10 * a01 + b11 * a11 + b12 * a21 + b13 * a31;
        m.data[6] = b10 * a02 + b11 * a12 + b12 * a22 + b13 * a32;
        m.data[7] = b10 * a03 + b11 * a13 + b12 * a23 + b13 * a33;
        m.data[8] = b20 * a00 + b21 * a10 + b22 * a20 + b23 * a30;
        m.data[9] = b20 * a01 + b21 * a11 + b22 * a21 + b23 * a31;
        m.data[10] = b20 * a02 + b21 * a12 + b22 * a22 + b23 * a32;
        m.data[11] = b20 * a03 + b21 * a13 + b22 * a23 + b23 * a33;
        m.data[12] = b30 * a00 + b31 * a10 + b32 * a20 + b33 * a30;
        m.data[13] = b30 * a01 + b31 * a11 + b32 * a21 + b33 * a31;
        m.data[14] = b30 * a02 + b31 * a12 + b32 * a22 + b33 * a32;
        m.data[15] = b30 * a03 + b31 * a13 + b32 * a23 + b33 * a33;

        return m;
    }

    Matrix4 Matrix4::Translate(const Vector3 &position)
    {
        Matrix4 m;

        m.data[12] = position.x;
        m.data[13] = position.y;
        m.data[14] = position.z;

        return m;
    }
} // namespace Core
