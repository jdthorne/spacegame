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

   void setPower(double power);

private:
   double power_;

};

#endif
