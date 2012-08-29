#include <World.h>
#include <Bullet.h>
#include <QGLWidget>
#include <cstdlib>
#include <Helpers.h>
#include <Ship.h>

World::World()
{
   for (int i = 0; i < 25; i++)
   {
      addShip();
   }

   for (int i = 0; i < 500; i++)
   {
      Vector direction = randomVector(-1.0, 1.0).normalized();
      Vector position = (direction * 400.0);

      stars_.append(position);
   }
}

void World::addShip()
{
   double worldSize = 50.0;
   Vector position = randomVector(-worldSize, worldSize);

   Ship* ship = new Ship(*this, position);

   ships_.append(ship);
   all_.append(ship);
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

void World::render(const Vector cameraPosition)
{
   glBegin(GL_POINTS);
   glPointSize(1.0);
   glColor3f(1.0, 1.0, 1.0);
   foreach(Vector star, stars_)
   {
      glVertex3f(star.x, star.y, star.z);
   }
   glEnd();

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHTING);
   foreach(Ship* ship, ships_)
   {
      double distance = (cameraPosition - ship->position()).magnitude();
      Mesh::shitty = (distance > 15);
      ship->render();
   }
   foreach(WorldItem* item, sphereEffects_) 
   {
      item->render();
   }

   glDisable(GL_LIGHTING);
   glBegin(GL_LINES);
   glColor3f(0.25, 0.75, 1.0);
   foreach(WorldItem* item, lineEffects_) 
   {
      item->render();
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

bool World::hasRemainingShips()
{
   return (ships_.count() > 0);
}
