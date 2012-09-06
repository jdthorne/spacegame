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

Ship::Ship(World& world, const Vector position, const Vector velocity, int team)
   : world_(world)
   , shipControl_(new ShipControl(*this))
   , autopilot_(new Autopilot(*shipControl_))
   , team_(team)
   , boredom_(0)
   , deflectorPower_(1.0)
   , deflectorGlow_(1000.0)
{
   static int id = 0;

   id_ = id++;

   velocity_ = velocity;
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
Ship* Ship::createSwarmer(World& world, const Vector position, const Vector velocity, int team)
{
   Ship* ship = new Ship(world, position, velocity, team);

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

Ship* Ship::createAstronach(World& world, const Vector position, const Vector velocity, int team)
{
   Ship* ship = new Ship(world, position, velocity, team);

   // Rear engine pod
   ship->modules_.append(new Engine(*ship, Vector(0, 0, 0), Quaternion::DEFAULT));

   ship->modules_.append(new Structure(*ship, Vector(+1, 0, 0), Quaternion::DEFAULT));
   ship->modules_.append(new Structure(*ship, Vector(-1, 0, 0), Quaternion::DEFAULT));
   ship->modules_.append(new Structure(*ship, Vector(0, +1, 0), Quaternion::DEFAULT));
   ship->modules_.append(new Structure(*ship, Vector(0, -1, 0), Quaternion::DEFAULT));

   // Outer engines
   ship->modules_.append(new Structure(*ship, Vector(-1, -1, 1), Quaternion::DEFAULT));
   ship->modules_.append(new Structure(*ship, Vector(+1, -1, 1), Quaternion::DEFAULT));
   ship->modules_.append(new Structure(*ship, Vector(-1, +1, 1), Quaternion::DEFAULT));
   ship->modules_.append(new Structure(*ship, Vector(+1, +1, 1), Quaternion::DEFAULT));

   // Edge Structures
   ship->modules_.append(new Structure(*ship, Vector(+2, 0, 1), Quaternion::DEFAULT));
   ship->modules_.append(new Structure(*ship, Vector(-2, 0, 1), Quaternion::DEFAULT));   

   // Main weapons array
   ship->modules_.append(new Weapon(*ship, Vector(-1, +2, 1), Quaternion::SPIN_Z));   
   ship->modules_.append(new Weapon(*ship, Vector(+1, +2, 1), Quaternion::SPIN_Z));   
   ship->modules_.append(new Weapon(*ship, Vector(-1, -2, 1), Quaternion::DEFAULT));   
   ship->modules_.append(new Weapon(*ship, Vector(+1, -2, 1), Quaternion::DEFAULT));   

   ship->modules_.append(new Weapon(*ship, Vector(-1, +2, 3), Quaternion::SPIN_Z));   
   ship->modules_.append(new Weapon(*ship, Vector(+1, +2, 3), Quaternion::SPIN_Z));   
   ship->modules_.append(new Weapon(*ship, Vector(-1, -2, 3), Quaternion::DEFAULT));   
   ship->modules_.append(new Weapon(*ship, Vector(+1, -2, 3), Quaternion::DEFAULT));   

   ship->modules_.append(new Weapon(*ship, Vector(+2, +1, 1), Quaternion::SPIN_Z));   
   ship->modules_.append(new Weapon(*ship, Vector(-2, +1, 1), Quaternion::SPIN_Z));   
   ship->modules_.append(new Weapon(*ship, Vector(+2, -1, 1), Quaternion::DEFAULT));   
   ship->modules_.append(new Weapon(*ship, Vector(-2, -1, 1), Quaternion::DEFAULT));   

   ship->modules_.append(new Weapon(*ship, Vector(-3, 0, 1), Quaternion::Z_ROT_270));   
   ship->modules_.append(new Weapon(*ship, Vector(+3, 0, 1), Quaternion::Z_ROT_090));   

   ship->modules_.append(new Weapon(*ship, Vector(-2, 1, 3), Quaternion::Z_ROT_270));   
   ship->modules_.append(new Weapon(*ship, Vector(+2, 1, 3), Quaternion::Z_ROT_090));   
   ship->modules_.append(new Weapon(*ship, Vector(-2, -1, 3), Quaternion::Z_ROT_270));   
   ship->modules_.append(new Weapon(*ship, Vector(+2, -1, 3), Quaternion::Z_ROT_090));   

   // More structure
   ship->core_ = new FlightComputer(*ship, Vector(0, 0, 2), Quaternion::DEFAULT);
   ship->modules_.append(ship->core_);

   ship->modules_.append(new Gyro(*ship, Vector(+1, 0, 1.5)));
   ship->modules_.append(new Gyro(*ship, Vector(-1, 0, 1.5)));
   ship->modules_.append(new Gyro(*ship, Vector(0, +1, 1.5)));
   ship->modules_.append(new Gyro(*ship, Vector(0, -1, 1.5)));
   ship->modules_.append(new Gyro(*ship, Vector(+1, 0, 2.5)));
   ship->modules_.append(new Gyro(*ship, Vector(-1, 0, 2.5)));
   ship->modules_.append(new Gyro(*ship, Vector(0, +1, 2.5)));
   ship->modules_.append(new Gyro(*ship, Vector(0, -1, 2.5)));

   ship->modules_.append(new Weapon(*ship, Vector(0, +2, 2), Quaternion::SPIN_Z));   
   ship->modules_.append(new Weapon(*ship, Vector(0, -2, 2), Quaternion::DEFAULT));   

   // Forward engines
   ship->modules_.append(new Structure(*ship, Vector(-1, -1, 3), Quaternion::SPIN_X));
   ship->modules_.append(new Structure(*ship, Vector(+1, -1, 3), Quaternion::SPIN_X));
   ship->modules_.append(new Structure(*ship, Vector(-1, +1, 3), Quaternion::SPIN_X));
   ship->modules_.append(new Structure(*ship, Vector(+1, +1, 3), Quaternion::SPIN_X));

   // Forward weapons pod
   ship->modules_.append(new Engine(*ship, Vector(0, 0, 4), Quaternion::SPIN_X));

   ship->modules_.append(new Weapon(*ship, Vector(0, +1, 4), Quaternion::SPIN_Z));   
   ship->modules_.append(new Weapon(*ship, Vector(0, -1, 4), Quaternion::DEFAULT));   
   ship->modules_.append(new Weapon(*ship, Vector(+1, 0, 4), Quaternion::Z_ROT_090));   
   ship->modules_.append(new Weapon(*ship, Vector(-1, 0, 4), Quaternion::Z_ROT_270));   


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
   maxModuleRadius_ = 0;
   foreach (Module* m, modules_)
   {
      m->setPosition(m->position() - centerOfMass);

      maxModuleRadius_ = qMax(maxModuleRadius_, m->position().magnitude());
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

Hud& Ship::hud()
{
   return hud_;
}

int Ship::id()
{
   return id_;
}

double Ship::deflectorGlow()
{
   return deflectorGlow_;
}

int Ship::boredom()
{
   return boredom_;
}

//! @}

/**
 ******************************************************************************
 *
 * \brief            Simulation - local
 * @{
 ******************************************************************************
 */
void Ship::simulateMovement()
{
   simulatePhysics();
   simulateModules();
}

void Ship::simulateCollisions()
{
   if (deflectorGlow_ > 0.1)
   {
      deflectorGlow_ = deflectorGlow_ * 0.95;
   }
   else
   {
      deflectorGlow_ = 0;
   }

   simulateShipToShipCollisions();
}

void Ship::simulateLogic()
{
   hud_.clear();
   autopilot_->run();

   boredom_++;
}

void Ship::simulateModules()
{
   foreach (Module* m, modules_)
   {
      m->simulate();
   }
}

void Ship::simulateShipToShipCollisions()
{
   foreach(Ship* ship, world_.ships())
   {
      if (ship != this)
      {
         Vector shipPosition = ship->position();

         double range = (ship->position() - position_).magnitude();
         if (range < 50.0 && ship->applyCollisionWith(range, position_, velocity_, team_))
         {
            Vector toShip = (shipPosition - position()).normalized();

            velocity_ += (toShip * (-0.1 / range));
         }
      }
   }
}

void Ship::handleExcitement()
{
   boredom_ = 0;
}

//! @}

/**
 ******************************************************************************
 *
 * \brief            Simulation - Global
 * @{
 ******************************************************************************
 */
bool Ship::applyCollisionWith(double distance, const Vector position, const Vector velocity, int team)
{
   if (distance <= deflectorRadius())
   {
      if (deflectorGlow_ < 3.0)
      {
         deflectorGlow_ += 1.0;
      }

      deflectorPower_ -= (1.0 / mass_);
      handleExcitement();
      return true;
   }

   double collisionRadius = 1.0 + ((velocity_ - velocity).magnitude() * 1.5);
   if (distance + collisionRadius <= maxModuleRadius_)
   {
      return false;
   }

   Vector localPosition = (position - position_).rotate(orientation_.inverse());

   foreach (Module* module, modules_)
   {
      if ((module->position() - localPosition).magnitude() < collisionRadius)
      {
         velocity_ += (velocity - velocity_) * 0.01;

         if (module == core_)
         {
            explode(team);
            return true;
         }

         explodeModule(module, team);
         explodeAllUnattachedModules(team);
         return true;
      }
   }

   return false;
}

void Ship::explode(int team)
{
   Explosion* explosion = new Explosion(world_, 10.0, NullType,
                                        core_->absolutePosition(), 
                                        core_->absoluteOrientation(), 
                                        velocity_, team);
   modules_.removeAll(core_);

   core_ = NULL;
   foreach(Module* module, modules_)
   {
      explodeModule(module, team);
   }

   world_.replaceItem(this, explosion);
}

void Ship::explodeAllUnattachedModules(int forTeam)
{
   QList<Module*> attachedModules;
   if (core_ != NULL) attachedModules.append(core_);

   QList<Module*> freeModules;
   freeModules.append(modules_);

   while (true)
   {
      bool foundMoreModules = false;
      foreach(Module* checkModule, freeModules)
      {
         foreach(Module* attachedModule, attachedModules)
         {
            if (checkModule->position().distanceTo(attachedModule->position()) < 1.6)
            {
               freeModules.removeAll(checkModule);
               attachedModules.append(checkModule);
               foundMoreModules = true;
            }
         }
      }

      if (!foundMoreModules) break;
   }

   // Destroy the unattached modules
   foreach(Module* module, freeModules)
   {
      explodeModule(module, forTeam);
   }
}

void Ship::explodeModule(Module* module, int forTeam)
{
   world_.addItem(new Explosion(world_, 3.0, typeOf(module),
                                module->absolutePosition(), 
                                module->absoluteOrientation(), 
                                velocity_, forTeam));
   modules_.removeAll(module);
   delete module;
}

double Ship::deflectorRadius()
{
   return 12.0 * deflectorPower_;
}  

void Ship::lockToTestBench()
{
   deflectorPower_ = 0.0;

   //position_ = Vector(0, 0, 0);
   velocity_ = Vector(0, 0, 0);
   //orientation_ = Quaternion();
   angularMomentum_ = Vector(0, 0, 0);
}

//! @}

