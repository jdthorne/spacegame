#ifndef GYRO_H
#define GYRO_H

#include <Module.h>
#include <Vector.h>

class Ship;

class Gyro : public Module
{

public:
   Gyro(Ship& ship, const Vector position);
   virtual ~Gyro() {};

   virtual void simulate();

   void setPower(const Vector power);

private:
   void applyTorqueAlongXAxis(double power);
   void applyTorqueAlongYAxis(double power);
   void applyTorqueAlongZAxis(double power);

private:
   Vector power_;
};


#endif