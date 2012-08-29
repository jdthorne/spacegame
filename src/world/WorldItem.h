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
   virtual void simulate() = 0;
   virtual void render() = 0;

   virtual const Vector position() = 0;
   virtual const Quaternion orientation() = 0;
   
};

#endif
