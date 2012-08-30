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
   bool thrustIsForward();

private:
   double power_;

};

#endif
