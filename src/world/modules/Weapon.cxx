
#include <World.h>
#include <Weapon.h>
#include <Ship.h>
#include <Bullet.h>

Weapon::Weapon(Ship& ship, const Vector position, const Quaternion orientation)
   : Module(ship, position, orientation)
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

   Vector fireChamber = Vector(0, 0.3, 0);
   Vector startPoint = absolutePositionOf(fireChamber);

   double inaccuracy = 0.03;
   Vector initialVelocity = Vector(0, 0, 1).rotate(absoluteOrientation());
   Vector randomVelocity = ship_.world().randomVector(-inaccuracy, inaccuracy);

   Vector velocity = initialVelocity + randomVelocity + ship_.velocity();

   Bullet* bullet = new Bullet(ship_.world(), &ship_, startPoint, velocity, ship_.team());
   ship_.world().addItem(bullet);

   cooldown_ = ship_.world().randomValue(35, 60);
}
