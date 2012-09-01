#include <World.h>
#include <Bullet.h>
#include <QGLWidget>
#include <cstdlib>
#include <Helpers.h>
#include <Ship.h>

World::World()
{  
}

void World::addItem(WorldItem* item)
{
   all_.append(item);
}

void World::removeItem(WorldItem* item)
{
   toRemove_.append(item);
}

void World::simulate()
{
   foreach (WorldItem* item, all_)
   {
      item->simulate();
   }

   foreach (WorldItem* item, toRemove_)
   {
      toRemove_.removeAll(item);
      all_.removeAll(item);
      //delete item;
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

WorldItem& World::focusItem() const
{
   return *(ships()[0]);
}

QList<Ship*> World::ships() const
{
   return all_.all<Ship*>();
}

bool World::hasRemainingShips()
{
   return (ships().count() > 0);
}

RacistList<WorldItem*> World::items() const
{
   return all_;
}

