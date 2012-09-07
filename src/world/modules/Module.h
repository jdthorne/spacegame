#ifndef MODULE_H
#define MODULE_H

#include <QList>
#include <QString>

#include <Vector.h>
#include <Quaternion.h>

class Ship;

class Module
{

public:
   Module(Ship& ship, const Vector position, const Quaternion orientation);
   virtual ~Module() {};

   bool isConnectedAtAbsolutePoint(Vector point);

   const Vector position();
   const Quaternion orientation();
   void setPosition(const Vector newPosition);

   Vector absolutePosition();
   Vector absolutePositionOf(const Vector point);
   Quaternion absoluteOrientation();

   QList<Vector> connectionPoints();

   virtual void simulate();
   virtual double mass();

protected:
   Ship& ship_;

   Vector position_;
   Quaternion orientation_;

   QList<Vector> connectionPoints_;
}; 

#endif
