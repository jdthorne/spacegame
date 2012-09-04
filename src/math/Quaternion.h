#ifndef QUATERNION_H
#define QUATERNION_H


#include <QString>

class Vector;

class Quaternion
{

public:
   Quaternion();
   Quaternion(double w, double x, double y, double z);
   Quaternion(double angle, const Vector axis);
   explicit Quaternion(const Vector vector);

   double angle() const;
   Vector axis() const;

   Quaternion rotationTo(const Quaternion rhs) const;

   QString toString();

public: // operations
   void normalize();
   double magnitude();

   Quaternion operator += (const Quaternion rhs);

   Quaternion inverse() const;

   static const Quaternion slerp(Quaternion q1, Quaternion q2, double t);

public: // constants
   static const Quaternion DEFAULT;
   static const Quaternion SPIN_X;
   static const Quaternion SPIN_Y;
   static const Quaternion SPIN_Z;

   static const Quaternion Z_ROT_090;
   static const Quaternion Z_ROT_270;

public:
   double w;
   double x;
   double y;
   double z;

};

#define printQuat(quat) qPrintable(quat.toString())

Quaternion operator*(double scalar, const Quaternion quaternion);
Quaternion operator*(const Quaternion quaternion, double scalar);
Quaternion operator*(Quaternion a, Quaternion b);
Quaternion operator+(Quaternion a, Quaternion b);

#endif
