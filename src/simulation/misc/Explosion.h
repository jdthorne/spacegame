#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QList>
#include <WorldItem.h>

class World;
class Mesh;

class Explosion : public WorldItem
{

public:
   Explosion(World& world, const Vector position, const Vector velocity, double size);
   virtual ~Explosion();

   double glow();
   double size();
   virtual void simulate();

   virtual const Vector position();
   virtual const Quaternion orientation();

   QList<Vector> fragments();

private:
   World& world_;

   Vector position_;
   Vector velocity_;

   QList<Vector> fragments_;

   double size_;

   int ticks_;
   double lifetime_;
};

#endif
