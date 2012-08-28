
#include <Engine.h>
#include <Ship.h>

Engine::Engine(Ship& ship, const Vector& position, const Quaternion& orientation)
   : Module("engine", ship, position, orientation)
   , power_(0.0)
{

}

void Engine::simulate()
{
   Vector thrust(0, 0, 0.00001);

   //ship_.applyLocalForce(thrust.rotate(orientation_), position_);
}
