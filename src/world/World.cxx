#include <World.h>
#include <Bullet.h>
#include <QGLWidget>
#include <cstdlib>
#include <Helpers.h>
#include <Ship.h>

World::World()
{  
   double worldSize = 20.0;
   /*
   {
      Vector position = randomVector(-worldSize, worldSize);

      Ship* ship = Ship::createAstronach(*this, position, 0);

      ships_.append(ship);
      all_.append(ship);
   }
   */

   for (int team = 0; team <= 1; team++)
   {
      for (int i = 0; i < 30; i++)
      {
         Vector position = randomVector(-worldSize, worldSize) + (Vector(0, -600, 0)*team);

         Ship* ship = Ship::createSwarmer(*this, position, team);

         ships_.append(ship);
         all_.append(ship);
      }
   }
}

void World::addItem(WorldItem* item)
{
   if (dynamic_cast<Bullet*>(item) != NULL)
   {
      lineEffects_.append(item);
   }
   else
   {
      sphereEffects_.append(item);
   }
   all_.append(item);
}

void World::removeItem(WorldItem* item)
{
   lineEffects_.removeAll(item);
   sphereEffects_.removeAll(item);
   all_.removeAll(item);

   if (objectIs(item, Ship))
   {
      ships_.removeAll((Ship*)item);
   }

   delete item;
}

void World::simulate()
{
   foreach (WorldItem* item, all_)
   {
      item->simulate();
   }
}

double World::randomValue(double min, double max)
{
   return min + ( (double)rand() / RAND_MAX ) * (max - min);
}

const Vector World::randomVector(double min, double max)
{
   return Vector( randomValue(min, max),
                  randomValue(min, max),
                  randomValue(min, max) );
}

WorldItem& World::focusItem()
{
   return *(ships_[0]);
}

QList<Ship*> World::ships()
{
   return ships_;
}

bool World::hasRemainingShips()
{
   return (ships_.count() > 0);
}

RacistList<WorldItem*> World::items()
{
   return all_;
}

