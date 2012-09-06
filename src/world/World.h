#ifndef WORLD_H
#define WORLD_H

#include <WorldItem.h>
#include <RacistList.h>
#include <Camera.h>

#include <Vector.h>

class Ship;

class World
{

public:
   World();

   void addItem(WorldItem* item);
   void replaceItem(WorldItem* item, WorldItem* withItem);
   void removeItem(WorldItem* item);

   void simulate();

   void setSeed(int seed);
   double randomValue(double min = 0.0, double max = 1.0);
   int randomInt(int min = 0, int max = 1);
   const Vector randomVector(double min = 0.0, double max = 1.0);

   bool hasRemainingShips();

   RacistList<WorldItem*> items() const;

   QList<Ship*> ships() const;

   Camera& camera();
   const Camera& camera() const;

private:

   Camera camera_;
   RacistList<WorldItem*> all_;
   QList<WorldItem*> toRemove_;
};

#endif
