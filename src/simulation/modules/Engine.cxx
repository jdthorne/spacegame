
#include <Engine.h>
#include <Ship.h>
#include <Mesh.h>

Engine::Engine(Ship& ship, const Vector position, const Quaternion orientation)
   : Module("engine", ship, position, orientation)
   , power_(0.01)
   , thrustMesh_(Mesh::byName("engine-thrust"))
{

}

void Engine::simulate()
{
   power_ = qBound(0.0, power_, 1.0);
   Vector thrust(0, 0, 0.01 * power_);

   ship_.applyLocalForce(thrust.rotate(orientation_), position_);
}

void Engine::setPower(double power)
{
   power_ = power;
}

void Engine::render()
{
   Module::render();

   if (power_ > 0.00001)
   {
      thrustMesh_.render(absolutePosition(), absoluteOrientation());
   }
}

bool Engine::thrustIsForward()
{
   Vector thrustAngle = Vector(0, 0, 1).rotate(orientation_);

   return (thrustAngle.z > 0);
}
