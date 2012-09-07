
#include <Engine.h>
#include <Ship.h>

const double Engine::MAXIMUM_THRUST = 0.1;

Engine::Engine(Ship& ship, const Vector position, const Quaternion orientation)
   : Module(ship, position, orientation)
   , power_(0.01)
{
   // Sides
   connectionPoints_.append(Vector(+0.5, 0, -0.5));
   connectionPoints_.append(Vector(-0.5, 0, -0.5));
   connectionPoints_.append(Vector(0, +0.5, -0.5));
   connectionPoints_.append(Vector(0, -0.5, -0.5));

   connectionPoints_.append(Vector(+0.5, 0, +0.5));
   connectionPoints_.append(Vector(-0.5, 0, +0.5));
   connectionPoints_.append(Vector(0, +0.5, +0.5));
   connectionPoints_.append(Vector(0, -0.5, +0.5));

   // Ends
   connectionPoints_.append(Vector(0, 0, +1.0));
}

void Engine::simulate()
{
   power_ = qBound(0.0, power_, 1.0);
   Vector thrust(0, 0, MAXIMUM_THRUST * power_);

   ship_.applyLocalForce(thrust.rotate(orientation_), position_);

   glow_ = (0.5 * glow_) + (0.5 * power_);
}

void Engine::setPower(double power)
{
   power_ = power;
}

const Vector Engine::thrust()
{
   return Vector(0, 0, 1).rotate(orientation_);
}

double Engine::power()
{
   return power_;
}

double Engine::glow()
{
   return glow_;
}
