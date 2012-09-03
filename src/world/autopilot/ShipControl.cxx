
// System
#include <cmath>

// Qt

// Spacegame
#include <Ship.h>
#include <ShipControl.h>
#include <World.h>
#include <Gyro.h>
#include <Weapon.h>
#include <Engine.h>

ShipControl::ShipControl(Ship& ship)
   : ship_(ship)
{

}

ShipControl::~ShipControl()
{
}

/**
 ******************************************************************************
 *
 * \brief            Debug
 *
 ******************************************************************************
 */
void ShipControl::displayOnHud(const Vector vector)
{
   ship_.hud().display(vector.rotate(ship_.orientation()));
}

/**
 ******************************************************************************
 *
 * \brief            Physics
 * @{
 ******************************************************************************
 */
double ShipControl::mass()
{
   return ship_.mass_;
}

const Vector ShipControl::angularVelocity()
{
   return ship_.angularVelocity().rotate(ship_.orientation().inverse());
}

const Vector ShipControl::angularMomentum()
{
   return ship_.angularMomentum_.rotate(ship_.orientation().inverse());
}

const Vector ShipControl::inertialTensor()
{
   return ship_.inertialTensor_;
}

void ShipControl::setGyroPowerLevel(Vector power)
{
   foreach(Gyro* gyro, ship_.modules().all<Gyro*>())
   {
      gyro->setPower(power);
   }
}

double ShipControl::maximumTorque()
{
   double result = Gyro::MAXIMUM_TORQUE * ship_.modules().all<Gyro*>().count();

   return result;
}

double ShipControl::maximumForce()
{
   double result = Engine::MAXIMUM_THRUST * ship_.modules().all<Engine*>().count() * 0.5;

   return result;
}


void ShipControl::setEnginePowerLevel(Vector power)
{
   foreach(Engine* engine, ship_.modules().all<Engine*>())
   {
      double direction = engine->thrust().z * power.z;
      if (direction > 0)
      {
         engine->setPower(fabs(power.z));
      }
      else if (direction < 0)
      {
         engine->setPower(-fabs(power.z));
      }
      else
      {
         engine->setPower(0);
      }
   }
}


//! @}

/**
 ******************************************************************************
 *
 * \brief            Sensors
 * @{
 ******************************************************************************
 */
QList<SensorResult> ShipControl::scan()
{
   Quaternion orientationCorrection = ship_.orientation().inverse();

   QList<SensorResult> results;
   foreach(Ship* target, ship_.world().ships())
   {
      if (target == &ship_)
      {
         continue;
      }

      SensorResult result;
      result.vector_ = (target->position() - ship_.position()).rotate(orientationCorrection);
      result.velocity_ = (target->velocity() - ship_.velocity()).rotate(orientationCorrection);
      result.friendly_ = (target->team() == ship_.team());

      results.append(result);
   }

   return results;
}
//! @}

/**
 ******************************************************************************
 *
 * \brief            Weapons
 *
 ******************************************************************************
 */
void ShipControl::fireWeapons()
{
   foreach(Weapon* weapon, ship_.modules().all<Weapon*>())
   {
      weapon->fire();
   }
}

