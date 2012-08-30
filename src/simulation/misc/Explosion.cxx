
#include <cmath>

#include <Explosion.h>
#include <Mesh.h>
#include <World.h>

Explosion::Explosion(World& world, const Vector position, const Vector velocity, double size)
   : world_(world)
   , position_(position)
   , velocity_(velocity)
   , size_(size)
   , ticks_(0)
   , lifetime_(30.0 + (sqrt(size) * 30.0))
{
   int fragments = qBound(5.0, (size * 5.0), 50.0);

   for (int i = 0; i < fragments; i++)
   {
      fragments_.append(world_.randomVector(-size / 2, size / 2));
   }
}

Explosion::~Explosion()
{
}

void Explosion::simulate()
{
   position_ += velocity_;
   for (int i = 0; i < fragments_.count(); i++)
   {
      fragments_[i] = fragments_[i] * 1.001;
   }  

   ticks_++;

   if (ticks_ > lifetime_)
   {  
      world_.removeItem(this);
      return;
   }
}

QList<Vector> Explosion::fragments()
{
   return fragments_;
}

double Explosion::size()
{
   return size_;
}

double Explosion::glow()
{
   double fractionOfLifeCompleted = (ticks_ / lifetime_);
   double glow = sqrt(1 - fractionOfLifeCompleted);
   return glow;
}

const Vector Explosion::position()
{
   return position_;
}

const Quaternion Explosion::orientation()
{
   return Quaternion();
}
