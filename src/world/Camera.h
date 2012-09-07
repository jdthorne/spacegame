#ifndef CAMERA
#define CAMERA

// Qt
#include <QString>

// Spacegame
#include <Vector.h>
#include <Quaternion.h>

class World;
class WorldItem;

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
   Camera(World& world);
   ~Camera();

public:
   const Vector position() const;
   const Quaternion orientation() const;

   void setUserOrientation(const Quaternion orientation);
   void addZoom(double zoom);

public:
   void handleItemReplaced(WorldItem* item, WorldItem* newItem);
   void handleItemRemoved(WorldItem* item);

   void simulate();
   void focusOnRandomItem();

private: // helpers
   void updateFocusItem(const Vector position, const Quaternion orientation);

private: // members
   World& world_;
   WorldItem* focusItem_;

   Quaternion userOrientation_;
   Quaternion baseOrientation_;

   double zoom_;

   Vector position_;
};

#endif
