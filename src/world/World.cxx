#include <World.h>
#include <QGLWidget>
#include <cstdlib>

World::World()
{
   
}

void World::addShip()
{
   double worldSize = 25.0;
   Vector position = randomVector(-worldSize, worldSize);

   Ship* ship = new Ship(*this, position);

   ships_.append(ship);
   all_.append(ship);

   for (int i = 0; i < 50; i++)
   {
      Vector direction = randomVector(-1.0, 1.0).normalized();
      Vector position = (direction * 400.0);

      stars_.append(position);
   }
}

void World::addItem(WorldItem* item)
{
   lineEffects_.append(item);
   all_.append(item);
}

void World::removeItem(WorldItem* item)
{
   lineEffects_.removeAll(item);
   all_.removeAll(item);

   delete item;
}

void World::simulate()
{
   foreach (WorldItem* item, all_)
   {
      item->simulate();
   }
}

void World::render()
{
   glEnable(GL_LIGHTING);
   foreach(Ship* ship, ships_)
   {
      ship->render();
   }

   glDisable(GL_LIGHTING);
   glBegin(GL_LINES);
   glColor3f(0.25, 0.75, 1.0);
   foreach(WorldItem* item, lineEffects_) 
   {
      item->render();
   }
   glEnd();

   glBegin(GL_POINTS);
   glPointSize(1.0);
   glColor3f(1.0, 1.0, 1.0);
   foreach(Vector star, stars_)
   {
      glVertex3f(star.x, star.y, star.z);
   }
   glEnd();
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
