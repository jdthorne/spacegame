
#include <Engine.h>
#include <Ship.h>

Engine::Engine(Ship& ship, const Vector position, const Quaternion orientation)
   : Module("engine", ship, position, orientation)
   , power_(0.01)
{

}

void Engine::simulate()
{
   Vector thrust(0, 0, 0.001 * power_);

   ship_.applyLocalForce(thrust.rotate(orientation_), position_);
}

void Engine::setPower(double power)
{
   power_ = power;
}
