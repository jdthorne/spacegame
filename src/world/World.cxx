#include <World.h>
#include <Bullet.h>
#include <QGLWidget>
#include <cstdlib>
#include <Helpers.h>
#include <Ship.h>
#include <ObjectType.h>

World::World()
   : focusItem_(NULL)
{  
}

void World::addItem(WorldItem* item)
{
   all_.append(item);
}

void World::replaceItem(WorldItem* item, WorldItem* withItem)
{
   if (focusItem_ == item)
   {
      focusItem_ = withItem;
   }

   removeItem(item);
   addItem(withItem);
}

void World::removeItem(WorldItem* item)
{
   toRemove_.append(item);

   if (focusItem_ == item)
   {
      focusItem_ = NULL;
   }
}

void World::simulate()
{
   foreach (WorldItem* item, all_)      item->simulateMovement();
   foreach (WorldItem* item, all_)      item->simulateCollisions();
   foreach (WorldItem* item, all_)      item->simulateLogic();

   foreach (WorldItem* item, toRemove_)
   {
      toRemove_.removeAll(item);
      all_.removeAll(item);
      //delete item;
   }
}

void World::setSeed(int seed)
{
   srand(seed);
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
   if (focusItem_ == NULL)
   {  
      focusItem_ = ships()[0];
   }

   return *focusItem_;
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

