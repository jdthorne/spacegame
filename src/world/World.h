#ifndef WORLD_H
#define WORLD_H

#include <Ship.h>
#include <WorldItem.h>
#include <RacistList.h>

#include <Vector.h>

class World
{

public:
   World();

   void addItem(WorldItem* item);
   void removeItem(WorldItem* item);

   void simulate();

   double randomValue(double min = 0.0, double max = 1.0);
   const Vector randomVector(double min = 0.0, double max = 1.0);

   bool hasRemainingShips();

   RacistList<WorldItem*> items();

   QList<Ship*> ships();

   WorldItem& focusItem();

private:
   RacistList<WorldItem*> all_;
   QList<WorldItem*> toRemove_;
};

#endif
