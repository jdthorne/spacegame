#include <Bullet.h>
#include <Explosion.h>
#include <World.h>
#include <Ship.h>

const int Bullet::MAX_LIFE = 60;
const double Bullet::SPEED = 2.5;
const double Bullet::RANGE = SPEED * MAX_LIFE;

Bullet::Bullet(World& world, Ship* source, const Vector position, const Vector velocity, const Vector direction, int team)
   : world_(world)
   , source_(source)
   , position_(position)
   , velocity_(velocity + (direction * SPEED))
   , direction_(direction)
   , life_(MAX_LIFE)
   , team_(team)
{
}

double Bullet::glow()
{
   double lifeRemaining = ((double)life_ / MAX_LIFE);
   if (lifeRemaining > 0.1)
   {
      return 1.0;
   }

   return lifeRemaining / 0.1;
}

Bullet::~Bullet()
{
}

int Bullet::life()
{
   return life_;
}

void Bullet::simulateMovement()
{
   position_ += velocity_;
}

void Bullet::simulateCollisions()
{
   foreach(Ship* ship, world_.ships())
   {
      if (ship != source_ && ship->team() != team_)
      {
         Vector shipVelocity = ship->velocity();
         
         double range = (ship->position() - position_).magnitude();
         if (range < 50.0 && ship->applyCollisionWith(range, position_, velocity_, team_))
         {
            world_.addItem(new Explosion(world_, 0.125, NullType, 
                             position_, Quaternion(), 
                             shipVelocity, team_));

            world_.removeItem(this);
            return;
         }
      }
   }
}

void Bullet::simulateLogic()
{
   life_ -= 1;
   if (life_ <= 0)
   {  
      world_.removeItem(this);
      return;
   }
}

const Vector Bullet::position()
{
   return position_;
}

const Vector Bullet::velocity()
{
   return velocity_;
}


const Quaternion Bullet::orientation()
{
   return Quaternion();
}

int Bullet::team()
{
   return team_;
}

const Vector Bullet::direction()
{
   return direction_;
}

