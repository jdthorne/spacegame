
#include <Gyro.h>
#include <Ship.h>

Gyro::Gyro(Ship& ship, const Vector position)
   : Module(ship, position, Quaternion())
   , power_(0, 0, 0)
{

}

void Gyro::simulate()
{
   ship_.applyTorque((power_ * 0.05).rotate(ship_.orientation()));
}

void Gyro::setPower(const Vector power)
{
   power_ = Vector( qBound(-1.0, power.x, +1.0),
                    qBound(-1.0, power.y, +1.0),
                    qBound(-1.0, power.z, +1.0) );
}
