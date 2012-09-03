#ifndef WORLDITEM_H
#define WORLDITEM_H

#include <Vector.h>
#include <Quaternion.h>

class WorldItem
{

public:
   WorldItem();
   virtual ~WorldItem();

public:
   virtual void simulateMovement() = 0;
   virtual void simulateCollisions() = 0;
   virtual void simulateLogic() = 0;

   virtual const Vector position() = 0;
   virtual const Quaternion orientation() = 0;
   
};

#endif
