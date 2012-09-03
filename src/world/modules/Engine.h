#ifndef ENGINE_H
#define ENGINE_H

#include <Module.h>
#include <Vector.h>

class Ship;

class Engine : public Module
{

public:
   Engine(Ship& ship, const Vector position, const Quaternion orientation);
   virtual ~Engine() {};

   virtual void simulate();

   double power();
   void setPower(double power);

   const Vector thrust();
   double glow();

   static const double MAXIMUM_THRUST;

private:
   double power_;
   double glow_;

};

#endif
