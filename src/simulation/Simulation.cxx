
// Qt

// Spacegame
#include <Profile.h>
#include <Simulation.h>
#include <World.h>

Simulation::Simulation()
   : world_(new World())
{

}

Simulation::~Simulation()
{
}

World& Simulation::world()
{
   return *world_;
}

void Simulation::simulate()
{
   PROFILE_FUNCTION("Simulation");

   runSimulationSpecifics();
   world_->simulate();
}

