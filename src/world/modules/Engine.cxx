
#include <Engine.h>
#include <Ship.h>

Engine::Engine(Ship& ship, const Vector position, const Quaternion orientation)
   : Module(ship, position, orientation)
   , power_(0.01)
{

}

void Engine::simulate()
{
   power_ = qBound(0.0, power_, 1.0);
   Vector thrust(0, 0, 0.05 * power_);

   ship_.applyLocalForce(thrust.rotate(orientation_), position_);
}

void Engine::setPower(double power)
{
   power_ = power;
}

bool Engine::thrustIsForward()
{
   Vector thrustAngle = Vector(0, 0, 1).rotate(orientation_);

   return (thrustAngle.z > 0);
}

double Engine::power()
{
   return power_;
}
