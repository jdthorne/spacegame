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

#endif
