
// Qt

// Spacegame
#include <Hud.h>

Hud::Hud()
{

}

Hud::~Hud()
{
}

void Hud::clear()
{
   vectors_.clear();
}

void Hud::display(const Vector vector)
{
   vectors_.append(vector);
}

QList<Vector> Hud::vectors()
{
   return vectors_;
}

