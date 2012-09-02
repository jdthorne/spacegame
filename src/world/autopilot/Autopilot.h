#ifndef AUTOPILOT_H
#define AUTOPILOT_H

#include <ShipControl.h>

class Autopilot
{

public:
   Autopilot(ShipControl& ship);
   ~Autopilot();

   void run();

private:
   void findTarget();
   void rotateToFaceTarget();
   void fireWeaponsIfReady();

private:
   int sign(double value);
   double powerForSmoothApproach(double distance, double speed, double maxAcceleration);

private: // members
   ShipControl& ship_;

   SensorResult target_;

};

#endif