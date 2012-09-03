#ifndef CAMERA
#define CAMERA

// Qt
#include <QString>

// Spacegame
#include <Vector.h>
#include <Quaternion.h>

/**
 ******************************************************************************
 *
 * \brief            Camera
 *
 ******************************************************************************
 */
class Camera
{

public:
   Camera();
   ~Camera();

public:
   void updateFocusItem(const Vector position, const Quaternion orientation);

   const Vector position() const;
   const Quaternion orientation() const;

   void addUserOrientation(const Quaternion orientation);

private: // helpers

private: // members
   Quaternion userOrientation_;
   Quaternion baseOrientation_;

   Vector position_;
};

#endif
