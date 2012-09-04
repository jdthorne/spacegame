
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

Color operator+(const Color lhs, const Color rhs)
{
   return Color(lhs.r + rhs.r,
                lhs.g + rhs.g,
                lhs.b + rhs.b,
                lhs.a + rhs.a);
}

Color Color::forTeam(int teamId)
{
   switch (teamId)
   {
      case 0: return Color(1.0, 0.4, 0.2, 1.0);
      case 1: return Color(0.25, 0.75, 1.0, 1.0);
      case 2: return Color(0.25, 1.0, 0.25, 1.0);
   }

   return Color(0.2, 0.2, 0.2, 1.0);
}

Color Color::glowForTeam(int teamId, double glow)
{
   return Color::forTeam(teamId) * Color(1, 1, 1, glow);
}