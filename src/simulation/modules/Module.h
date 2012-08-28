#ifndef MODULE_H
#define MODULE_H

#include <QString>

#include <Mesh.h>
#include <Vector.h>
#include <Quaternion.h>

class Ship;

class Module
{

public:
   Module(const QString& meshName, Ship& ship, const Vector& position, const Quaternion& orientation);
   virtual ~Module() {};

   void render();

   const Vector& position();
   void setPosition(const Vector& newPosition);

   Vector absolutePosition();

   virtual void simulate();
   virtual double mass();

protected:
   Mesh mesh_;
   Ship& ship_;

   Vector position_;
   Quaternion orientation_;

}; 

#endif
