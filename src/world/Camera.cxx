
// Qt

// Spacegame
#include <Ship.h>
#include <World.h>
#include <WorldItem.h>
#include <Camera.h>

Camera::Camera(World& world)
   : world_(world)
   , focusItem_(NULL)
   , zoom_(-10.0)
{
   userOrientation_ = Quaternion(1, 0, 0, 0);
}

Camera::~Camera()
{
}

/**
 ******************************************************************************
 *
 * \brief            Accessors
 *
 ******************************************************************************
 */
const Vector Camera::position() const
{
   Vector offset = Vector(0, 0, -zoom_).rotate(orientation().inverse());

   return position_ + offset;
}

const Quaternion Camera::orientation() const
{
   return userOrientation_ * baseOrientation_;
}

/**
 ******************************************************************************
 *
 * \brief            User Settings
 *
 ******************************************************************************
 */
void Camera::setUserOrientation(const Quaternion orientation)
{
   userOrientation_ = orientation;
   userOrientation_.normalize();
}

void Camera::addZoom(double zoom)
{
   zoom_ = qBound(-5000.0, zoom_ + zoom, -5.0);
}

/**
 ******************************************************************************
 *
 * \brief            Focus Items
 *
 ******************************************************************************
 */
void Camera::updateFocusItem(const Vector position, const Quaternion orientation)
{
   position_ = Vector::interpolate(position_, position, 0.75);
   baseOrientation_ = Quaternion::slerp(baseOrientation_, orientation, 0.95);
}

void Camera::handleItemReplaced(WorldItem* item, WorldItem* newItem)
{
   if (focusItem_ == item)
   {
      focusItem_ = newItem;
   }
}

void Camera::handleItemRemoved(WorldItem* item)
{
   if (item == focusItem_)
   {
      focusOnRandomItem();
   }
}

void Camera::focusOnRandomItem()
{
   focusItem_ = NULL;

   if (world_.ships().count() > 0)
   {
      int index = world_.randomValue(0, world_.ships().count() - 1);
      index = qBound(0, index, world_.ships().count() - 1);

      focusItem_ = world_.ships()[index];
   }
}

/**
 ******************************************************************************
 *
 * \brief            Simulation
 *
 ******************************************************************************
 */
void Camera::simulate()
{
   if (focusItem_ == NULL)
   {
      focusOnRandomItem();
      return;
   }

   updateFocusItem(focusItem_->position(), focusItem_->orientation().inverse());
}

