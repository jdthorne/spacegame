
#include <Gyro.h>
#include <Ship.h>

const double Gyro::MAXIMUM_TORQUE = 0.5;

Gyro::Gyro(Ship& ship, const Vector position)
   : Module(ship, position, Quaternion())
   , power_(0, 0, 0)
{

}

void Gyro::simulate()
{
   ship_.applyTorque((power_ * MAXIMUM_TORQUE).rotate(ship_.orientation()));
}

void Gyro::setPower(const Vector power)
{
   power_ = power.boundedToMagnitude(1.0);
}
