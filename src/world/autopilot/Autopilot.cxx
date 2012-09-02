#include <QtGlobal>

#include <Autopilot.h>
#include <cmath>

Autopilot::Autopilot(ShipControl& ship)
   : ship_(ship)
{
}

Autopilot::~Autopilot()
{
}

/**
 ******************************************************************************
 *
 * \brief            Core Autopilot 
 * @{
 ******************************************************************************
 */
void Autopilot::run()
{
   findTarget();
   rotateToFaceTarget();
}

void Autopilot::findTarget()
{
   QList<SensorResult> targets = ship_.scan();

   double maxDistance = 1.0/0.0;
   foreach(SensorResult target, targets)
   {
      if (target.friendly_)
      {
         continue;
      }

      double distance = target.vector_.magnitude();
      if (distance < maxDistance)
      {
         target_ = target;
         maxDistance = distance;
      }
   }
}

void Autopilot::rotateToFaceTarget()
{
   Vector forward = Vector(0, 0, 1);
   Vector toTarget = target_.vector_.normalized();

   Vector targetRotationAxis = forward.cross(toTarget);
   double targetRotationAngle = asin(targetRotationAxis.magnitude());

   Vector targetAngularVelocity = (targetRotationAxis.normalized() * targetRotationAngle) * -1;

   Vector angularVelocityError = (targetAngularVelocity - ship_.angularVelocity());

   ship_.setGyroPowerLevel(angularVelocityError);
}
//! @}

/**
 ******************************************************************************
 *
 * \brief            Helper Functions
 * @{
 ******************************************************************************
 */
int Autopilot::sign(double value)
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
//! @}

   /*
   // Find enemy ship
   QList<Ship*> allShips = world_.ships();
   Ship* targetShip = NULL;

   double closestRange = 1.0/0.0;
   foreach (Ship* ship, allShips)
   {
      if (ship != this && ship->team() != team_)
      {
         double range = (ship->position() - position_).magnitude();
         if (range < closestRange)
         {
            targetShip = ship;
            closestRange = range;
         }
      }
   }

   if (targetShip == NULL)
   {
      return;
   }

   Vector targetVector = targetShip->position() - position_;

   double interceptTime = (targetVector.magnitude() / Bullet::SPEED);
   targetVector += ((targetShip->velocity() - velocity_) * interceptTime);

   Vector target = targetVector;
   target.normalize();

   Vector fromPoint = Vector(0, 0, 1).rotate(orientation_);
   Vector toPoint = target;

   //double maxTorque = 0.1;

   Vector targetRotationAxis = fromPoint.cross(toPoint);
   double targetRotationAngle = asin(targetRotationAxis.magnitude());

   Vector targetAngularVelocity = (targetRotationAxis.normalized() * targetRotationAngle) * -1;

   //Vector angularVelocityError = (targetAngularVelocity - angularMomentum_);

   //angularVelocityError = angularVelocityError.boundedToMagnitude(maxTorque);

   //angularMomentum_ += angularVelocityError; 
   //(angularVelocityError.multiplyElementsBy(inertialTensor_));
   angularMomentum_ = targetAngularVelocity;

   // ============ ENGINE POWER ===============
   double distance = targetVector.magnitude() - 100.0;
   double speed = (velocity_ - targetShip->velocity()).magnitude();
   double maxAcceleration = (0.01 * 1.0 * 2.0) / mass_;

   if (velocity_.dot(targetShip->velocity()) < 0)
   {
      speed *= -1;
   }

   // MOAR EXCITEMENT
   distance = 999999;
   speed = 0;

   double powerLevel = Autopilot::powerForSmoothApproach(distance, speed, maxAcceleration);

   Quaternion angleToTarget = Vector(0, 0, 1).rotate(orientation_).rotationTo(target);
   double thrust = 0.0;
   if (angleToTarget.angle() < 0.1)
   {
      thrust = powerLevel;

      if (((targetShip->position() - position_).magnitude() < 120))
      {
         foreach(Module* module, modules_)
         {
            if (objectIs(module, Weapon))
            {
               ((Weapon*)module)->fire();
            }
         }
      }
   }  
   foreach(Module* module, modules_)
   {
      if (objectIs(module, Engine))
      {
         Engine& engine = *((Engine*)module);

         int directionSign = (engine.thrustIsForward() ? +1 : -1);
         double thrustForThisEngine = thrust * directionSign;

         ((Engine*)module)->setPower(thrustForThisEngine);
      }
   }
   */

   // ============================================================
   // So if we were to apply -angularVelocity until 

   //bool halfWayPoint = ???;

   //gyro.setPower(Vector(target.x, 0, 0));
