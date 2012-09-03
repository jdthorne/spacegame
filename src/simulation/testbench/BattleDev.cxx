
// Qt

// Spacegame
#include <Ship.h>
#include <World.h>
#include <BattleDev.h>
#include <Vector.h>

BattleDev::BattleDev()
   : Simulation()
{
   for (int i = 0; i < 25; i++)
   {
      addShip(0);
      addShip(1);
   }
}

void BattleDev::addShip(int team)
{
   Vector position = world_->randomVector(-75, 75);

   Ship* ship = Ship::createSwarmer(*world_, position + Vector(0, 0, 200 * team), team);
   world_->addItem(ship);
}

BattleDev::~BattleDev()
{

}

void BattleDev::runSimulationSpecifics()
{
}

void BattleDev::triggerEvent()
{
   foreach(Ship* ship, world_->ships())
   {
      ship->lockToTestBench();
   }
}

