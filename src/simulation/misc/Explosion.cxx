
#include <Explosion.h>
#include <Mesh.h>
#include <World.h>

Explosion::Explosion(World& world, const Vector position, const Vector velocity, double size)
   : world_(world)
   , mesh_(Mesh::byName("explosion"))
   , position_(position)
   , velocity_(velocity)
   , life_(size)
{
}

Explosion::~Explosion()
{
}

void Explosion::simulate()
{
   position_ += velocity_;

   life_ = life_ * 0.95;
   if (life_ <= 0.01)
   {  
      world_.removeItem(this);
      return;
   }
}

void Explosion::render()
{
   mesh_.render(position_, orientation(), life_);
}

const Vector Explosion::position()
{
   return position_;
}

const Quaternion Explosion::orientation()
{
   return Quaternion();
}
