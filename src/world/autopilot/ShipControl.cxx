
// Qt

// Spacegame
#include <Ship.h>
#include <ShipControl.h>
#include <World.h>
#include <Gyro.h>

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
 * \brief            Physics
 * @{
 ******************************************************************************
 */
const Vector ShipControl::angularVelocity()
{
   return ship_.angularVelocity();
}

void ShipControl::setGyroPowerLevel(Vector power)
{
   foreach(Gyro* gyro, ship_.modules().all<Gyro*>())
   {
      gyro->setPower(power);
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
   QList<SensorResult> results;
   foreach(Ship* target, ship_.world().ships())
   {
      SensorResult result;
      result.vector_ = (target->position() - ship_.position()).rotate(ship_.orientation());
      result.velocity_ = (target->velocity() - ship_.velocity()).rotate(ship_.orientation());
      result.friendly_ = (target->team() == ship_.team());
   }

   return results;
}
//! @}
