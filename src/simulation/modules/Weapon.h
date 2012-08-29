#ifndef WEAPON_H
#define WEAPON_H

#include <Module.h>
#include <Vector.h>
#include <WorldItem.h>

class Ship;

class Weapon : public Module
{

public:
   Weapon(Ship& ship, const Vector position, const Quaternion orientation);
   virtual ~Weapon() {};

   void fire();
   virtual void simulate();

private:
   int cooldown_;

};

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
