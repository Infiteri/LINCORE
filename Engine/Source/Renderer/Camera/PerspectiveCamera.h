#pragma once

#include "Camera.h"

namespace Core
{
    class CE_API PerspectiveCamera : public Camera
    {
    public:
        PerspectiveCamera();
        PerspectiveCamera(float fov, float aspect, float near, float far);

        void UpdateProjection();
        void UpdateProjection(float aspect);
        void UpdateProjection(float fov, float aspect, float near, float far);

        inline float GetFOV() { return fov; };
        inline float GetAspect() { return fov; };
        inline float GetNear() { return fov; };
        inline float GetFar() { return fov; };

        /// @brief Sets the fov to the new fov and (if true) automatically calls 'UpdateProjection',
        /// this way the projection matrix is up-to-date
        void SetFOV(const float fov, bool recalculateProjection = true);

        /// @brief Sets the aspect to the new aspect and (if true) automatically calls
        /// 'UpdateProjection', this way the projection matrix is up-to-date
        void SetAspect(const float aspect, bool recalculateProjection = true);

        /// @brief Sets the near to the new near and (if true) automatically calls
        /// 'UpdateProjection', this way the projection matrix is up-to-date
        void SetNear(const float near, bool recalculateProjection = true);

        /// @brief Sets the far to the new far and (if true) automatically calls 'UpdateProjection',
        /// this way the projection matrix is up-to-date
        void SetFar(const float far, bool recalculateProjection = true);

    private:
        float fov, aspect, near, far;
    };
} // namespace Core
