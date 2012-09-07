
// Qt

// Spacegame
#include <Ship.h>
#include <World.h>
#include <Shipyard.h>

Shipyard::Shipyard()
{
   ship_ = Ship::createSwarmer(*world_, Vector(0, 0, 0), Vector(0, 0, 0), 0);
   world_->addItem(ship_);
}

Shipyard::~Shipyard()
{
}

void Shipyard::runSimulationSpecifics()
{
   ship_->lockToTestBench();  
}
