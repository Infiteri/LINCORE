#include "Camera.h"
#include "Math/Vector.h"

namespace Core
{
    void Camera::SetPosition(const Vector3 &pos) { position = pos; }

    void Camera::UpdateView() { view = Matrix4::Translate(position); }
} // namespace Core
