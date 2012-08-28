#ifndef QUATERNION_H
#define QUATERNION_H

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

   const char* printable();

public: // operations
   void normalize();

   Quaternion operator += (const Quaternion rhs);

   Quaternion inverse() const;

public: // constants
   static const Quaternion DEFAULT;
   static const Quaternion FLIPPED;

public:
   double w;
   double x;
   double y;
   double z;

};

Quaternion operator*(double scalar, const Quaternion quaternion);
Quaternion operator*(Quaternion a, Quaternion b);

#endif
