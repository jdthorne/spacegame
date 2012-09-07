
// Qt

// Spacegame
#include <Structure.h>

Structure::Structure(Ship& ship, const Vector position, const Quaternion orientation)
   : Module(ship, position, orientation)
{
   // Sides
   connectionPoints_.append(Vector(+0.5, 0, -0.5));
   connectionPoints_.append(Vector(-0.5, 0, -0.5));
   connectionPoints_.append(Vector(0, +0.5, -0.5));
   connectionPoints_.append(Vector(0, -0.5, -0.5));

   connectionPoints_.append(Vector(+0.5, 0, +0.5));
   connectionPoints_.append(Vector(-0.5, 0, +0.5));
   connectionPoints_.append(Vector(0, +0.5, +0.5));
   connectionPoints_.append(Vector(0, -0.5, +0.5));

   // Ends
   connectionPoints_.append(Vector(0, 0, +1.0));
   connectionPoints_.append(Vector(0, 0, -1.0));
}

Structure::~Structure()
{
}

