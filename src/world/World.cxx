#include <World.h>
#include <Bullet.h>
#include <QGLWidget>
#include <cstdlib>
#include <Helpers.h>
#include <Ship.h>
#include <ObjectType.h>

World::World()
   : camera_(*this)
{  
}

void World::addItem(WorldItem* item)
{
   all_.append(item);
}

void World::replaceItem(WorldItem* item, WorldItem* withItem)
{
   camera_.handleItemReplaced(item, withItem);

   removeItem(item);
   addItem(withItem);
}

void World::removeItem(WorldItem* item)
{
   camera_.handleItemRemoved(item);

   toRemove_.append(item);
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

   camera_.simulate();
}

void World::setSeed(int seed)
{
   srand(seed);
}

double World::randomValue(double min, double max)
{
   return min + ( (double)rand() / RAND_MAX ) * (max - min);
}

int World::randomInt(int min, int max)
{
   return min + ( rand() % (max - min + 1) );
}

const Vector World::randomVector(double min, double max)
{
   return Vector( randomValue(min, max),
                  randomValue(min, max),
                  randomValue(min, max) );
}

QList<Ship*> World::ships() const
{
   return all_.all<Ship>();
}

bool World::hasRemainingShips()
{
   return (ships().count() > 0);
}

RacistList<WorldItem*> World::items() const
{
   return all_;
}

Camera& World::camera()
{
   return camera_;
}

const Camera& World::camera() const
{
   return camera_;
}

