#include <Module.h>
#include <Ship.h>

Module::Module(Ship& ship, const Vector position, const Quaternion orientation)
   : ship_(ship)
   , position_(position)
   , orientation_(orientation)
{
}

Vector Module::absolutePosition()
{
   return (ship_.position() + position_.rotate(ship_.orientation()));
}
Vector Module::absolutePositionOf(const Vector point)
{
   return (ship_.position() + (position_ + point.rotate(orientation_)).rotate(ship_.orientation()));
}
Quaternion Module::absoluteOrientation()
{
   return (ship_.orientation() * orientation_);
}

void Module::simulate()
{
   // Do nothing
}

const Vector Module::position()
{
   return position_;
}
void Module::setPosition(const Vector newPosition)
{
   position_ = newPosition;
}

double Module::mass()
{
   return 10.0;
}

const Quaternion Module::orientation()
{
   return orientation_;
}

QList<Vector> Module::connectionPoints()
{
   return connectionPoints_;
}

bool Module::isConnectedAtAbsolutePoint(Vector point)
{
   foreach(Vector connection, connectionPoints_)
   {
      Vector distance = (absolutePositionOf(connection) - point);
      if (distance.magnitude() < 0.4)
      {
         return true;
      }
   }
   return false;
}
