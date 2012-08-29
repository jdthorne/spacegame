#include <Bullet.h>
#include <Explosion.h>
#include <Mesh.h>
#include <World.h>
#include <Ship.h>

Bullet::Bullet(World& world, Ship* source, const Vector position, const Vector velocity)
   : world_(world)
   , source_(source)
   , position_(position)
   , velocity_(velocity)
   , life_(180)
{
   tail_ = velocity_ * -1.0;
}

Bullet::~Bullet()
{
}

void Bullet::simulate()
{
   position_ += velocity_;

   life_ -= 1;
   if (life_ <= 0)
   {  
      world_.removeItem(this);
      return;
   }

   foreach(Ship* ship, world_.ships())
   {
      if (ship != source_)
      {
         Vector shipVelocity = ship->velocity();

         double range = (ship->position() - position_).magnitude();
         if (range < 50.0 && ship->applyCollisionWith(range, position_, velocity_))
         {
            world_.addItem(new Explosion(world_, position_, shipVelocity, 0.125));
            world_.removeItem(this);
            return;
         }
      }
   }
}

void Bullet::render()
{
   Mesh::renderLine(position_ + tail_, position_, (life_ / 120.0));
}

const Vector Bullet::position()
{
   return position_;
}

const Quaternion Bullet::orientation()
{
   return Quaternion();
}
