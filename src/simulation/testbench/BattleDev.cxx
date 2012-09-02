
// Qt

// Spacegame
#include <Ship.h>
#include <World.h>
#include <BattleDev.h>
#include <Vector.h>

BattleDev::BattleDev()
   : Simulation()
{
   for (int i = 0; i < 1; i++)
   {
      addShip(0);
      addShip(1);
   }
}

void BattleDev::addShip(int team)
{
   Vector position = world_->randomVector(-25, 25);

   Ship* ship = Ship::createSwarmer(*world_, position, team);
   world_->addItem(ship);
}

BattleDev::~BattleDev()
{

}

void BattleDev::runSimulationSpecifics()
{
   // Nothing for now...
}

void BattleDev::triggerEvent()
{
   // Nothing for now...
}

