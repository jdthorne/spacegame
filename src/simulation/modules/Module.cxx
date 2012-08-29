#include <Module.h>
#include <Ship.h>

Module::Module(const QString& meshName, Ship& ship, const Vector position, const Quaternion orientation)
   : mesh_(Mesh::byName(meshName))
   , ship_(ship)
   , position_(position)
   , orientation_(orientation)
{

}

void Module::render()
{
   mesh_.render(absolutePosition(), absoluteOrientation());
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
   return 1.0;
}