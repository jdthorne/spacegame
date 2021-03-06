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
             const Vector velocity, int team);
   virtual ~Explosion();

   double glow();
   double size();
   double expansion();

   int team();

   virtual void simulateMovement();
   virtual void simulateCollisions();
   virtual void simulateLogic();

   virtual const Vector position();
   virtual const Quaternion orientation();

   ObjectType explodingObjectType();

private:
   World& world_;

   Vector position_;
   Vector velocity_;
   Quaternion orientation_;

   QList<Vector> fragments_;

   int team_;
   double size_;

   int ticks_;
   double lifetime_;

   ObjectType explodingObjectType_;
};

#endif
