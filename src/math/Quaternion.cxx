#include <Quaternion.h>
#include <Vector.h>
#include <cmath>

const Quaternion Quaternion::DEFAULT = Quaternion();
const Quaternion Quaternion::SPIN_X = Quaternion(0.0, 1.0, 0.0, 0.0);
const Quaternion Quaternion::SPIN_Y = Quaternion(0.0, 0.0, 1.0, 0.0);
const Quaternion Quaternion::SPIN_Z = Quaternion(0.0, 0.0, 0.0, 1.0);

const Quaternion Quaternion::Z_ROT_090 = Quaternion(M_PI/2, Vector(0, 0, 1));
const Quaternion Quaternion::Z_ROT_270 = Quaternion(-M_PI/2, Vector(0, 0, 1));

Quaternion::Quaternion()
   : w(1.0)
   , x(0.0)
   , y(0.0)
   , z(0.0)
{
}

Quaternion::Quaternion(double w, double x, double y, double z)
   : w(w)
   , x(x)
   , y(y)
   , z(z)
{
}

Quaternion::Quaternion(double angle, const Vector axis)
   : w(cos(angle/2))
   , x(axis.x * sin(angle/2))
   , y(axis.y * sin(angle/2))
   , z(axis.z * sin(angle/2))
{
}

Quaternion::Quaternion(const Vector vector)
   : w(0.0)
   , x(vector.x)
   , y(vector.y)
   , z(vector.z)
{

}

double Quaternion::angle() const
{
   return acos(w) * 2.0f;
}

Vector Quaternion::axis() const
{
   Vector axis(x, y, z);
   axis.normalize();

   return axis;
}

double Quaternion::magnitude()
{
   return sqrt(w*w + x*x + y*y + z*z);
}

void Quaternion::normalize()
{
   double scale = magnitude();
   w /= scale;
   x /= scale;
   y /= scale;
   z /= scale;
}

// Math is fun
// http://www.cprogramming.com/tutorial/3d/quaternions.html

Quaternion operator*(double scalar, const Quaternion quat)
{
   return Quaternion(quat.w * scalar, quat.x * scalar, quat.y * scalar, quat.z * scalar);
}

Quaternion operator*(const Quaternion quat, double scalar)
{
   return scalar * quat;
}

Quaternion operator*(const Quaternion a, const Quaternion b)
{
   return Quaternion( (a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z ),
                      (a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y ),
                      (a.w*b.y - a.x*b.z + a.y*b.w + a.z*b.x ),
                      (a.w*b.z + a.x*b.y - a.y*b.x + a.z*b.w ) );
}

Quaternion Quaternion::operator += (const Quaternion rhs)
{
   w += rhs.w;
   x += rhs.x;
   y += rhs.y;
   z += rhs.z;

   return *this;
}

Quaternion operator+(const Quaternion lhs, const Quaternion rhs)
{
   Quaternion result = lhs;
   result += rhs;
   return result;
}

Quaternion Quaternion::inverse() const
{
   return Quaternion(w, -x, -y, -z);
}

QString Quaternion::toString()
{
   return QString::number(w) + " " + QString::number(x) + " " + QString::number(y) + " " + QString::number(z);
}

Quaternion Quaternion::rotationTo(const Quaternion rhs) const
{
   return rhs * this->inverse();
}

const Quaternion Quaternion::slerp(Quaternion q1, Quaternion q2, double t)
{
   // I'm lazy - use LERP for now
   Quaternion result = (q1 * t) + (q2 * (1.0 - t));
   result.normalize();
   
   return result;
}

