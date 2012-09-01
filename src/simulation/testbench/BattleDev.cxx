
// Qt

// Spacegame
#include <Ship.h>
#include <World.h>
#include <BattleDev.h>
#include <Vector.h>

BattleDev::BattleDev()
   : Simulation()
{
   for (int i = 0; i < 100; i++)
   {
      addShip(0);
      addShip(1);
   }
}

void BattleDev::addShip(int team)
{
   double worldSize = 60;
   Vector position = world_->randomVector(-worldSize, worldSize);

   Ship* ship = Ship::createSwarmer(*world_, position + Vector(500 * team, 0, 0), team);
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

