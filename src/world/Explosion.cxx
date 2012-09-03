
#include <cmath>

#include <Explosion.h>
#include <World.h>

Explosion::Explosion(World& world, double size, ObjectType explodingObjectType,
                     const Vector position, const Quaternion orientation, 
                     const Vector velocity)
   : world_(world)
   , position_(position)
   , velocity_(velocity)
   , size_(size / 3.0)
   , ticks_(0)
   , lifetime_(30.0 + (sqrt(size) * 90.0))
   , explodingObjectType_(explodingObjectType)
{
   int fragments = qBound(0.0, (size * 5.0), 10.0);

   for (int i = 0; i < fragments; i++)
   {
      fragments_.append(world_.randomVector(-size / 2, size / 2));
   }
}

Explosion::~Explosion()
{
}

void Explosion::simulateMovement()
{
   position_ += velocity_;
   for (int i = 0; i < fragments_.count(); i++)
   {
      fragments_[i] = fragments_[i] * 1.001;
   }  
}

void Explosion::simulateCollisions()
{
   // No collisions
}

void Explosion::simulateLogic()
{
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
   double t = (ticks_ / lifetime_);
   double decay = 0.95;

   double glow = (1 - pow(decay, -t)) / log(decay);

   return 1.0 - glow;
}

const Vector Explosion::position()
{
   return position_;
}

const Quaternion Explosion::orientation()
{
   return orientation_;
}

double Explosion::expansion()
{
   return ticks_ / lifetime_;
}

ObjectType Explosion::explodingObjectType()
{
   return explodingObjectType_;
}

