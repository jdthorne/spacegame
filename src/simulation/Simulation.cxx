
// Qt

// Spacegame
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
   runSimulationSpecifics();
   world_->simulate();
}

