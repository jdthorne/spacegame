#ifndef BULLET_H
#define BULLET_H

#include <WorldItem.h>
class World;
class Ship;

class Bullet : public WorldItem
{

public:
   Bullet(World& world, Ship* source, const Vector position, const Vector velocity, int team);
   virtual ~Bullet();

   virtual void simulateMovement();
   virtual void simulateCollisions();
   virtual void simulateLogic();

   int life();
   int team();
   virtual const Vector position();
   virtual const Vector velocity();
   virtual const Quaternion orientation();

   const Vector direction();

public: // constants
   static const int MAX_LIFE;
   static const double RANGE;
   static const double SPEED;

private:
   World& world_;
   Ship* source_;

   Vector position_;
   Vector velocity_;
   Vector direction_;

   int life_;
   int team_;
};

#endif