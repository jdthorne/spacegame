
#include <World.h>
#include <Weapon.h>
#include <Ship.h>
#include <Bullet.h>

Weapon::Weapon(Ship& ship, const Vector position, const Quaternion orientation)
   : Module(ship, position, orientation)
   , cooldown_(0)
   , cooldownStart_(1)
{
   // Sides
   connectionPoints_.append(Vector(0, +0.5, +0.5));
   connectionPoints_.append(Vector(0, +0.5, -0.5));
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

   Vector startPoint = newBulletPosition();

   double inaccuracy = 0.03;
   Vector initialVelocity = Vector(0, 0, Bullet::SPEED).rotate(absoluteOrientation());
   Vector randomVelocity = ship_.world().randomVector(-inaccuracy, inaccuracy);

   Vector direction = initialVelocity + randomVelocity;

   Bullet* bullet = new Bullet(ship_.world(), &ship_, startPoint, ship_.velocity(), direction.normalized(), ship_.team());
   ship_.world().addItem(bullet);

   cooldownStart_ = ship_.world().randomValue(70, 120);
   cooldown_ = cooldownStart_;

   ship_.handleExcitement();
}

double Weapon::cooldownRemaining()
{
   return ((double)cooldown_ / cooldownStart_);
}

Vector Weapon::newBulletPosition()
{
   Vector fireChamber = Vector(0, 0.3, -0.5);
   Vector startPoint = absolutePositionOf(fireChamber);

   return startPoint;
}

