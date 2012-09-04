#ifndef WORLD_H
#define WORLD_H

#include <WorldItem.h>
#include <RacistList.h>

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
   const Vector randomVector(double min = 0.0, double max = 1.0);

   bool hasRemainingShips();

   RacistList<WorldItem*> items() const;

   QList<Ship*> ships() const;

   WorldItem& focusItem() const;

private:
   mutable WorldItem* focusItem_;

   RacistList<WorldItem*> all_;
   QList<WorldItem*> toRemove_;
};

#endif
