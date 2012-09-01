#include <QtGlobal>

#include <Autopilot.h>
#include <cmath>

int sign(double value)
{
   return (value == 0.0 ? 0 :
            (value > 0 ? +1 : -1)
          );
}

double Autopilot::powerForSmoothApproach(double distance, double speed, double maxAcceleration)
{
   if (fabs(distance) < 0.00001)
   {
      return 0.0;
   }

   if (maxAcceleration == 0)
   {
      return 0.0;
   }

   double targetAcceleration = -(speed*speed) / (2*distance);
   double maxBraking = -sign(distance) * maxAcceleration;

   if (sign(speed) != sign(distance))
   {
      return 1.0 * sign(distance);
   }
   else if (fabs(targetAcceleration) < fabs(maxBraking * 0.75))
   {
      return 1.0 * sign(distance);
   }
   else
   {
      return fabs(targetAcceleration / maxBraking) * sign(distance);
   }
}
