
// Qt

// Spacegame
#include <Simulation.h>

Simulation::Simulation()
{

}

Simulation::~Simulation()
{
}

World& Simulation::world()
{
   return world_;
}

void Simulation::simulate()
{
   runSimulationSpecifics();
   world_.simulate();
}

