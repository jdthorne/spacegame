
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
   Vector thrust(0, 0, 0.001 * power_);

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
