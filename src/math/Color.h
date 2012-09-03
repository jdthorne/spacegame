#ifndef COLOR_H
#define COLOR_H

struct Color
{
   Color(double r, double g, double b, double a);

   double r, g, b, a;
};

Color operator*(const Color lhs, const Color rhs);

#endif
