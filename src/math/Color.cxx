
#include <Color.h>

Color::Color(double r, double g, double b, double a)
   : r(r)
   , g(g)
   , b(b)
   , a(a)
{
}

Color operator*(const Color lhs, const Color rhs)
{
   return Color(lhs.r * rhs.r,
                lhs.g * rhs.g,
                lhs.b * rhs.b,
                lhs.a * rhs.a);
}
