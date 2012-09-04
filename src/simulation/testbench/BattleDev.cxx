
// Qt

// Spacegame
#include <Ship.h>
#include <World.h>
#include <BattleDev.h>
#include <Vector.h>

BattleDev::BattleDev()
   : Simulation()
{
   world_->setSeed(125);

   // Create red team
   for (int i = 0; i < 40; i++)
   {
      int team = 0;
      Vector position = world_->randomVector(-150, 150);
      Vector velocity = world_->randomVector(-0.2, 0.2);

      Ship* ship = Ship::createSwarmer(*world_, position + Vector(0, 0, 100), velocity, team);
      world_->addItem(ship);
   }

   // Create create blue team
   for (int i = 0; i < 10; i++)
   {
      int team = 1;
      Vector position = world_->randomVector(-250, 250);
      Vector velocity = world_->randomVector(-0.2, 0.2);

      Ship* ship = Ship::createSwarmer(*world_, position + Vector(0, 0, 0), velocity, team);
      world_->addItem(ship);
   }

   for (int i = 0; i < 9; i++)
   {
      int team = 1;
      Vector position = world_->randomVector(-50, 50);
      Vector velocity = world_->randomVector(-0.00001, 0.00001);

      Ship* ship = Ship::createAstronach(*world_, position + Vector(0, 0, 0), velocity, team);
      world_->addItem(ship);
   }
}

void BattleDev::addShip(int team)
{
   Vector position = world_->randomVector(-75, 75);
   Vector velocity = world_->randomVector(-0.1, 0.1);

   Ship* ship = Ship::createSwarmer(*world_, position + Vector(0, 0, 200 * team), velocity, team);
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

