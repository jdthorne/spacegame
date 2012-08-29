#ifndef WORLD_H
#define WORLD_H

#include <Ship.h>
#include <WorldItem.h>

#include <Vector.h>

class World
{

public:
   World();

   void addShip();
   void addItem(WorldItem* item);
   void removeItem(WorldItem* item);

   void simulate();
   void render(const Vector cameraPosition);

   double randomValue(double min = 0.0, double max = 1.0);
   const Vector randomVector(double min = 0.0, double max = 1.0);

   bool hasRemainingShips();

   QList<Ship*> ships();

   WorldItem& focusItem();

private:
   QList<Ship*> ships_;

   QList<WorldItem*> sphereEffects_;
   QList<WorldItem*> lineEffects_;

   QList<WorldItem*> all_;

   QList<Vector> stars_;
};

#endif
