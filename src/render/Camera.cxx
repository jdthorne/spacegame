
// Qt

// Spacegame
#include <Camera.h>

Camera::Camera()
{
   userOrientation_ = Quaternion(0, 0, 1, 0);
}

Camera::~Camera()
{
}

const Vector Camera::position() const
{
   return position_;
}

const Quaternion Camera::orientation() const
{
   return userOrientation_ * baseOrientation_;
}

void Camera::addUserOrientation(const Quaternion orientation)
{
   userOrientation_ = userOrientation_ * orientation;
}

void Camera::updateFocusItem(const Vector position, const Quaternion orientation)
{
   position_ = position;
   baseOrientation_ = orientation;
}
