
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

   Vector fireChamber = Vector(0, 0.3, 0);
   Vector startPoint = absolutePositionOf(fireChamber);

   double accuracy = 0.01;
   Vector initialVelocity = Vector(0, 0, 1.0).rotate(absoluteOrientation());
   Vector randomVelocity = Vector( ship_.world_.randomValue(-accuracy, accuracy),
                                   ship_.world_.randomValue(-accuracy, accuracy),
                                   ship_.world_.randomValue(-accuracy, accuracy) );

   Vector velocity = initialVelocity + randomVelocity;

   Bullet* bullet = new Bullet(ship_.world_, &ship_, startPoint, velocity);
   ship_.world_.addItem(bullet);

   cooldown_ = ship_.world_.randomValue(3, 6);
}
