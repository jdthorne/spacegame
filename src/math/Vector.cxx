#include <Vector.h>
#include <Quaternion.h>
#include <cmath>

Vector::Vector()
   : x(0.0)
   , y(0.0)
   , z(0.0)
{
}

Vector::Vector(double x, double y, double z)
   : x(x)
   , y(y)
   , z(z)
{
}

Vector::Vector(const Quaternion& quaternion)
   : x(quaternion.x)
   , y(quaternion.y)
   , z(quaternion.z)
{
}

Vector& Vector::operator += (const Vector& rhs)
{
   x += rhs.x;
   y += rhs.y;
   z += rhs.z;

   return *this;
}

Vector Vector::operator + (const Vector& rhs) const
{
   Vector result = *this;
   result += rhs;

   return result;
}

Vector Vector::operator - (const Vector& rhs) const
{
   return Vector(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vector Vector::cross(const Vector& rhs) const
{
   const Vector& one = *this;
   const Vector& two = rhs;

   return Vector( (one.y * two.z) - (two.y * one.z),
                  (one.z * two.x) - (two.z * one.x),
                  (one.x * two.y) - (two.x * one.y) );
}

double Vector::dot(const Vector& rhs) const
{
   return (x*rhs.x) + (y*rhs.y) + (z*rhs.z);
}

Vector Vector::rotate(const Quaternion& angle) const
{
   return Vector(angle * Quaternion(*this) * angle.inverse());
}

double Vector::magnitude()
{
   return sqrt(x*x + y*y + z*z);
}

Vector Vector::normalized() const
{
   Vector result = *this;
   result.normalize();
   return result;
}

void Vector::normalize()
{
   double scale = magnitude();
   x /= scale;
   y /= scale;
   z /= scale;
}

Vector operator*(const Vector& vector, double scalar)
{
   return Vector(vector.x * scalar, vector.y * scalar, vector.z * scalar);
}

QString Vector::toString() const
{
   return QString::number(x, 'f', 6) + " " + QString::number(y, 'f', 6) + " " + QString::number(z, 'f', 6);
}

Vector Vector::inverse() const
{
   return Vector(1.0/x, 1.0/y, 1.0/z);
}

Vector Vector::multiplyElementsBy(const Vector& rhs) const
{
   return Vector(x*rhs.x, y*rhs.y, z*rhs.z);
}

Quaternion Vector::rotationTo(const Vector& lookAt) const
{
   Vector axis = this->cross(lookAt);
   axis.normalize();

   double angle = acos(this->dot(lookAt));

   if (angle < 0.000001)
   {
      return Quaternion();
   }

   Quaternion result = Quaternion(angle, axis);
   result.normalize();

   return result;
}

Vector Vector::boundedToMagnitude(double maxMagnitude)
{
   double currentMagnitude = this->magnitude();
   if (currentMagnitude < maxMagnitude)
   {
      return *this;
   }

   double scale = currentMagnitude / maxMagnitude;
   return (*this) * (1.0/scale);
}
