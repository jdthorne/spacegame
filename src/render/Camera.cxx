
// Qt

// Spacegame
#include <Camera.h>

Camera::Camera()
   : zoom_(1.0)
{
   userOrientation_ = Quaternion(0, 0, 1, 0);
}

Camera::~Camera()
{
}

const Vector Camera::position() const
{
   Vector offset = Vector(0, 0, -zoom_).rotate(orientation().inverse());

   return position_ + offset;
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
   position_ = Vector::interpolate(position_, position, 0.75);
   baseOrientation_ = Quaternion::slerp(baseOrientation_, orientation, 0.95);
}

void Camera::addZoom(double zoom)
{
   zoom_ += zoom;
}

