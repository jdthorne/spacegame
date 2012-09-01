#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QList>
#include <WorldItem.h>
#include <ObjectType.h>

class World;
class Module;

class Explosion : public WorldItem
{

public:
   Explosion(World& world, double size, ObjectType explodingObjectType,
             const Vector position, const Quaternion orientation, 
             const Vector velocity);
   virtual ~Explosion();

   double glow();
   double size();
   double expansion();
   virtual void simulate();

   virtual const Vector position();
   virtual const Quaternion orientation();

   QList<Vector> fragments();

   ObjectType explodingObjectType();

private:
   World& world_;

   Vector position_;
   Vector velocity_;
   Quaternion orientation_;

   QList<Vector> fragments_;

   double size_;

   int ticks_;
   double lifetime_;

   ObjectType explodingObjectType_;
};

#endif
