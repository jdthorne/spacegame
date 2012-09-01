
// Qt

// Spacegame
#include <Ship.h>
#include <Bullet.h>
#include <ExplosionDev.h>

ExplosionDev::ExplosionDev()
   : Simulation()
{
   Ship* ship = Ship::createSwarmer(world_, Vector(0, 0, 0), 0);

   world_.addItem(ship);

}

ExplosionDev::~ExplosionDev()
{
}

void ExplosionDev::runSimulationSpecifics()
{
   // Pass... FOR NOW
}

void ExplosionDev::triggerEvent()
{
   if (!world_.hasRemainingShips())
   {
      Ship* newShip = Ship::createSwarmer(world_, Vector(0, 0, 0), 0);
      world_.addItem(newShip);
      return;
   }

   Vector randomness = world_.randomVector(-0.02, 0.02);
   Bullet* bullet = new Bullet(world_, NULL, Vector(0, 40, 40), Vector(0, -1, -1) + randomness, 1);

   world_.addItem(bullet);
}

