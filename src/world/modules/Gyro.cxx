
#include <Gyro.h>
#include <Ship.h>

const double Gyro::MAXIMUM_TORQUE = 0.5;

Gyro::Gyro(Ship& ship, const Vector position)
   : Module(ship, position, Quaternion())
   , power_(0, 0, 0)
{
   // Sides
   connectionPoints_.append(Vector(+0.5, 0, 0));
   connectionPoints_.append(Vector(-0.5, 0, 0));
   connectionPoints_.append(Vector(0, +0.5, 0));
   connectionPoints_.append(Vector(0, -0.5, 0));

   // Ends
   connectionPoints_.append(Vector(0, 0, +0.5));
   connectionPoints_.append(Vector(0, 0, -0.5));
}

void Gyro::simulate()
{
   ship_.applyTorque((power_ * MAXIMUM_TORQUE).rotate(ship_.orientation()));
}

void Gyro::setPower(const Vector power)
{
   power_ = power.boundedToMagnitude(1.0);
}
