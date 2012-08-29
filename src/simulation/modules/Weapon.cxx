
#include <World.h>
#include <Weapon.h>
#include <Ship.h>

Weapon::Weapon(Ship& ship, const Vector position, const Quaternion orientation)
   : Module("weapon", ship, position, orientation)
   , cooldown_(0)
{

}

void Weapon::simulate()
{
   if (cooldown_ > 0)
   {
      cooldown_--;
   }
}

void Weapon::fire()
{
   if (cooldown_ > 0)
   {
      return;
   }

   Vector fireChamber = Vector(0, -0.3, 0);

   Vector startPoint = absolutePosition(fireChamber);

   double accuracy = 0.01;
   Vector initialVelocity = Vector(0, 0, 0.3).rotate(absoluteOrientation());
   Vector randomVelocity = Vector( ship_.world_.randomValue(-accuracy, accuracy),
                                   ship_.world_.randomValue(-accuracy, accuracy),
                                   ship_.world_.randomValue(-accuracy, accuracy) );

   Vector velocity = initialVelocity + randomVelocity;

   Bullet* bullet = new Bullet(ship_.world_, &ship_, startPoint, velocity);
   ship_.world_.addItem(bullet);

   cooldown_ = 5;
}

// ---------------------- BULLET STUFF --------------------------

Bullet::Bullet(World& world, Ship* source, const Vector position, const Vector velocity)
   : world_(world)
   , source_(source)
   , position_(position)
   , velocity_(velocity)
   , life_(120)
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
         double range = (ship->position() - position_).magnitude();
         if (range < 6.0)
         {
            // Explode!
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
