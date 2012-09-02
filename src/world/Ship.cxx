#include <Ship.h>
#include <Engine.h>
#include <Weapon.h>
#include <Gyro.h>
#include <Vector.h>
#include <cmath>
#include <Explosion.h>
#include <World.h>
#include <QGLWidget>
#include <Helpers.h>
#include <Autopilot.h>
#include <Engine.h>
#include <FlightComputer.h>
#include <Autopilot.h>
#include <Bullet.h>
#include <Structure.h>
#include <ShipControl.h>

Ship::Ship(World& world, const Vector position, int team)
   : world_(world)
   , shipControl_(new ShipControl(*this))
   , autopilot_(new Autopilot(*shipControl_))
   , team_(team)
   , deflectorPower_(1.0)
{
   position_ = position;
   orientation_.normalize();
}

Ship::~Ship()
{

}

/**
 ******************************************************************************
 *
 * \brief            Construction and Physics
 * @{
 ******************************************************************************
 */
Ship* Ship::createSwarmer(World& world, const Vector position, int team)
{
   Ship* ship = new Ship(world, position, team);

   ship->modules_.append(new Engine(*ship, Vector(-1, 0, 0), Quaternion::DEFAULT));
   ship->modules_.append(new Engine(*ship, Vector(1, 0, 0), Quaternion::DEFAULT));
   ship->modules_.append(new Engine(*ship, Vector(-1, 0, 2), Quaternion::SPIN_X));
   ship->modules_.append(new Engine(*ship, Vector(1, 0, 2), Quaternion::SPIN_X));

   ship->modules_.append(new Weapon(*ship, Vector(1, 1, 0), Quaternion::SPIN_Z));
   ship->modules_.append(new Weapon(*ship, Vector(-1, 1, 0), Quaternion::SPIN_Z));
   ship->modules_.append(new Weapon(*ship, Vector(1, -1, 0), Quaternion::DEFAULT));
   ship->modules_.append(new Weapon(*ship, Vector(-1, -1, 0), Quaternion::DEFAULT));

   ship->modules_.append(new Weapon(*ship, Vector(2, 0, 0), Quaternion::Z_ROT_090));
   ship->modules_.append(new Weapon(*ship, Vector(-2, 0, 0), Quaternion::Z_ROT_270));

   ship->core_ = new FlightComputer(*ship, Vector(0, 0, 1), Quaternion());
   ship->modules_.append(ship->core_);
   ship->modules_.append(new Gyro(*ship, Vector(0, 0, -0.5)));

   ship->normalizeModules();

   return ship;
}

void Ship::normalizeModules()
{
   Vector centerOfMass;

   mass_ = 0;
   inertialTensor_ = Vector();

   foreach (Module* m, modules_)
   {
      double mass = m->mass();
      mass_ += mass;

      const Vector position = m->position();

      centerOfMass += position * mass;

      inertialTensor_.x += mass * (position.y*position.y + position.z*position.z);
      inertialTensor_.y += mass * (position.x*position.x + position.z*position.z);
      inertialTensor_.z += mass * (position.x*position.x + position.y*position.y);
   }
   centerOfMass = centerOfMass * (1.0/mass_);

   inverseInertialTensor_ = inertialTensor_.inverse();

   // Move modules
   foreach (Module* m, modules_)
   {
      m->setPosition(m->position() - centerOfMass);
   }
}
//! @}

/**
 ******************************************************************************
 *
 * \brief            Accessors
 * @{
 ******************************************************************************
 */
World& Ship::world()
{
   return world_;
}

const Vector Ship::position()
{
   return position_;
}

const Vector Ship::velocity()
{
   return velocity_;
}

const Quaternion Ship::orientation()
{
   return orientation_;
}

RacistList<Module*> Ship::modules()
{
   return modules_;
}

int Ship::team()
{
   return team_;
}
//! @}

/**
 ******************************************************************************
 *
 * \brief            Simulation - local
 * @{
 ******************************************************************************
 */
void Ship::simulate()
{
   autopilot_->run();
   simulatePhysics();
   simulateModules();
   simulateCollisions();
}
void Ship::simulateModules()
{
   foreach (Module* m, modules_)
   {
      m->simulate();
   }
}

void Ship::simulateCollisions()
{
   foreach(Ship* ship, world_.ships())
   {
      if (ship != this)
      {
         double range = (ship->position() - position_).magnitude();
         if (range < 50.0 && ship->applyCollisionWith(range, position_, velocity_))
         {
            return;
         }
      }
   }
}
//! @}

/**
 ******************************************************************************
 *
 * \brief            Simulation - Global
 * @{
 ******************************************************************************
 */
bool Ship::applyCollisionWith(double distance, const Vector position, const Vector velocity)
{
   if (distance <= deflectorRadius())
   {
      double deflectorDamage = (velocity_ - velocity).magnitude();
      deflectorPower_ -= (deflectorDamage / 500.0);
      return true;
   }


   Vector localPosition = (position - position_).rotate(orientation_.inverse());
   double collisionRadius = 1.0 + (velocity.magnitude() * 1.5);

   foreach (Module* module, modules_)
   {
      if ((module->position() - localPosition).magnitude() < collisionRadius)
      {
         velocity_ += (velocity - velocity_) * 0.01;

         if (module == core_)
         {
            world_.addItem(new Explosion(world_, 10.0, NullType,
                                         module->absolutePosition(), 
                                         module->absoluteOrientation(), 
                                         velocity_));
            world_.removeItem(this);
            return true;
         }

         world_.addItem(new Explosion(world_, 3.0, typeOf(module),
                                      module->absolutePosition(), 
                                      module->absoluteOrientation(), 
                                      velocity_));
         modules_.removeAll(module);
         delete module;
         return true;
      }
   }

   return false;
}

double Ship::deflectorRadius()
{
   return 25.0 * deflectorPower_;
}  

void Ship::lockToTestBench()
{
   deflectorPower_ = 0.0;
   return;

   position_ = Vector(0, 0, 0);
   velocity_ = Vector(0, 0, 0);
   orientation_ = Quaternion();
   angularMomentum_ = Vector(0, 0, 0);
}

//! @}

