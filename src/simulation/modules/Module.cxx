#include <Module.h>
#include <Ship.h>

Module::Module(const QString& meshName, Ship& ship, const Vector& position, const Quaternion& orientation)
   : mesh_(meshName)
   , ship_(ship)
   , position_(position)
   , orientation_(orientation)
{

}

void Module::render()
{
   mesh_.render(absolutePosition(), ship_.orientation() * orientation_);
}

Vector Module::absolutePosition()
{
   return (ship_.position() + position_.rotate(ship_.orientation()));
}

void Module::simulate()
{
   // Do nothing
}

const Vector& Module::position()
{
   return position_;
}
void Module::setPosition(const Vector& newPosition)
{
   position_ = newPosition;
}

double Module::mass()
{
   return 1.0;
}