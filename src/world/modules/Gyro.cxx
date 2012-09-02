
#include <Gyro.h>
#include <Ship.h>

Gyro::Gyro(Ship& ship, const Vector position)
   : Module(ship, position, Quaternion())
{

}

void Gyro::simulate()
{
   applyTorqueAlongXAxis(power_.x);
   applyTorqueAlongYAxis(power_.y);
   applyTorqueAlongZAxis(power_.z);
}

void Gyro::setPower(const Vector power)
{
   power_ = power.boundedToMagnitude(1.0) * 0.001;
}

void Gyro::applyTorqueAlongXAxis(double power)
{
   Vector thrust(0, -power, 0);

   ship_.applyLocalForce(thrust * +1.0, position_ + Vector(0, 0, -0.5));
   ship_.applyLocalForce(thrust * -1.0, position_ + Vector(0, 0, +0.5));
}
void Gyro::applyTorqueAlongYAxis(double power)
{
   Vector thrust(0, 0, power);

   ship_.applyLocalForce(thrust * +1.0, position_ + Vector(+0.5, 0, 0));
   ship_.applyLocalForce(thrust * -1.0, position_ + Vector(-0.5, 0, 0));
}
void Gyro::applyTorqueAlongZAxis(double power)
{
   Vector thrust(0, power, 0);

   ship_.applyLocalForce(thrust * +1.0, position_ + Vector(-0.5, 0, 0));
   ship_.applyLocalForce(thrust * -1.0, position_ + Vector(+0.5, 0, 0));
}
