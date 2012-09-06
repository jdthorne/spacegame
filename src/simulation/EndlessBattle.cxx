
// System
#include <time.h>

// Qt

// Spacegame
#include <Ship.h>
#include <World.h>
#include <EndlessBattle.h>
#include <Vector.h>

EndlessBattle::EndlessBattle()
   : Simulation()
   , ftl_(true)
{
   world_->setSeed(time(NULL));

   for (int i = 0; i < 20; i++)
   {
      addRandomShip();
   }
}

EndlessBattle::~EndlessBattle()
{

}

void EndlessBattle::runSimulationSpecifics()
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
      addRandomShip();
   }

   if ((world_->randomInt(0, 40) == 0))
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

void EndlessBattle::addRandomShip()
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
      ship = Ship::createAstronach(*world_, position * 0.1, velocity * 0.01, team);
   }
   else
   {
      ship = Ship::createSwarmer(*world_, position, velocity, team);
   }
   world_->addItem(ship);
}
