
// System
#include <time.h>

// Qt

// Spacegame
#include <Ship.h>
#include <World.h>
#include <BattleDev.h>
#include <Vector.h>

BattleDev::BattleDev()
   : Simulation()
   , ftl_(false)
{
   world_->setSeed(time(NULL));


   for (int i = 0; i < 10; i++)
   {
      int team = 1;
      Vector position = world_->randomVector(-30, 30);
      Vector velocity = world_->randomVector(-0.00001, 0.00001);

      Ship* ship = Ship::createAstronach(*world_, position + Vector(0, 0, 0), velocity, team);
      world_->addItem(ship);
   }

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
   for (int i = 0; i < 15; i++)
   {
      int team = 1;
      Vector position = world_->randomVector(-250, 250);
      Vector velocity = world_->randomVector(-0.2, 0.2);

      Ship* ship = Ship::createSwarmer(*world_, position + Vector(0, 0, 0), velocity, team);
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
   if (world_->ships().count() < 30)
   {
      ftl_ = true;
   }
   if (world_->ships().count() > 60)
   {
      ftl_ = false;
   }

   if (ftl_ && (world_->randomInt(0, 15) == 0))
   {
      int team = 0;
      int teams[3] = {0, 0, 0};
      foreach (Ship* ship, world_->ships())
      {
         teams[ship->team()]++;
      }

      if (teams[0] <= teams[1] && teams[0] <= teams[2])
      {
         team = 0;
      }
      else if (teams[1] <= teams[0] && teams[1] <= teams[2])
      {
         team = 1;
      }
      else if (teams[2] <= teams[0] && teams[2] <= teams[1])
      {
         team = 2;
      }
      else
      {
         team = world_->randomInt(0, 2);
      }

      Vector position = world_->randomVector(-100, 100);
      Vector velocity = world_->randomVector(-0.5, 0.5);

      Ship* ship = NULL;

      if (world_->randomInt(0, 6) == 0)
      {
         ship = Ship::createAstronach(*world_, position * 0.1, velocity, team);
      }
      else
      {
         ship = Ship::createSwarmer(*world_, position, velocity, team);
      }
      world_->addItem(ship);
   }

   if (ftl_ && (world_->randomInt(0, 5) == 0))
   {
      foreach(Ship* ship, world_->ships())
      {
         if (ship->boredom() > (60 * 30))
         {
            ship->explode(-1);
            break;
         }
      }
   }
}

void BattleDev::triggerEvent()
{
}

