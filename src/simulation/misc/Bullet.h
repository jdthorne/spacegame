#ifndef BULLET_H
#define BULLET_H

#include <WorldItem.h>
class World;
class Ship;

class Bullet : public WorldItem
{

public:
   Bullet(World& world, Ship* source, const Vector position, const Vector velocity);
   virtual ~Bullet();

   virtual void simulate();
   virtual void render();

   virtual const Vector position();
   virtual const Quaternion orientation();

private:
   World& world_;
   Ship* source_;

   Vector position_;
   Vector velocity_;

   Vector tail_;

   int life_;
};

#endif