#ifndef MODULE_H
#define MODULE_H

#include <QString>

#include <Vector.h>
#include <Quaternion.h>

class Ship;

class Module
{

public:
   Module(Ship& ship, const Vector position, const Quaternion orientation);
   virtual ~Module() {};

   const Vector position();
   const Quaternion orientation();
   void setPosition(const Vector newPosition);

   Vector absolutePosition();
   Vector absolutePositionOf(const Vector point);
   Quaternion absoluteOrientation();

   virtual void simulate();
   virtual double mass();

protected:
   Ship& ship_;

   Vector position_;
   Quaternion orientation_;

}; 

#endif
