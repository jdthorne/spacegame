
// Qt

// Spacegame
#include <Ship.h>
#include <World.h>
#include <BattleDev.h>
#include <Vector.h>

BattleDev::BattleDev()
   : Simulation()
{
   // Create swarmers
   for (int i = 0; i < 25; i++)
   {
      int team = 0;
      Vector position = world_->randomVector(-175, 175);

      Ship* ship = Ship::createSwarmer(*world_, position, team);
      world_->addItem(ship);
   }

   // Create astronach
   for (int i = 0; i < 13; i++)
   {
      int team = 1;
      Vector position = world_->randomVector(-12, 12);

      Ship* ship = Ship::createAstronach(*world_, position + Vector(0, 0, 0), team);
      world_->addItem(ship);
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

