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

Ship::Ship(World& world, const Vector position)
   : world_(world)
   , deflector_(Mesh::byName("deflector"))
   , deflectorPower_(1.0)
   , position_(position)
{
   orientation_.normalize();

   modules_.append(new Engine(*this, Vector(-1, 0, 0), Quaternion::DEFAULT));
   modules_.append(new Engine(*this, Vector(1, 0, 0), Quaternion::DEFAULT));
   modules_.append(new Engine(*this, Vector(-1, 0, 2), Quaternion::SPIN_X));
   modules_.append(new Engine(*this, Vector(1, 0, 2), Quaternion::SPIN_X));

   modules_.append(new Weapon(*this, Vector(1, 1, 0), Quaternion::SPIN_Z));
   modules_.append(new Weapon(*this, Vector(-1, 1, 0), Quaternion::SPIN_Z));
   modules_.append(new Weapon(*this, Vector(1, -1, 0), Quaternion::DEFAULT));
   modules_.append(new Weapon(*this, Vector(-1, -1, 0), Quaternion::DEFAULT));

   modules_.append(new Weapon(*this, Vector(2, 0, 0), Quaternion::Z_ROT_090));
   modules_.append(new Weapon(*this, Vector(-2, 0, 0), Quaternion::Z_ROT_270));

   core_ = new Module("computer", *this, Vector(0, 0, 1), Quaternion());
   modules_.append(core_);
   modules_.append(new Gyro(*this, Vector(0, 0, -0.5)));

   normalizeModules();
}

Ship::~Ship()
{

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

void Ship::simulate()
{
   simulatePhysics();
   simulateAutopilot();

   foreach (Module* m, modules_)
   {
      m->simulate();
   }

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

void Ship::simulatePhysics()
{
   // Linear
   position_ += velocity_;

   // Rotational
   //Vector angularVelocity = angularMomentum_.multiplyElementsBy(inverseInertialTensor_);
   Vector angularVelocity = angularMomentum_;
   Quaternion spin = (-0.5 * Quaternion(angularVelocity)) * orientation_;
   orientation_ += spin;

   orientation_.normalize();
}

void Ship::render()
{
   foreach (Module* m, modules_)
   {
      m->render();
   }

   //deflector_.render(position_, orientation_, deflectorRadius());
}

double Ship::deflectorRadius()
{
   return 10.0 * deflectorPower_;
}  

bool Ship::applyCollisionWith(double distance, const Vector position, const Vector velocity)
{
   if (distance <= deflectorRadius())
   {
      double deflectorDamage = (velocity_ - velocity).magnitude();
      deflectorPower_ -= (deflectorDamage / 500.0);
      return true;
   }


   Vector localPosition = (position - position_).rotate(orientation_.inverse());

   foreach (Module* module, modules_)
   {
      if ((module->position() - localPosition).magnitude() < 1.0)
      {
         world_.addItem(new Explosion(world_, module->absolutePosition(), velocity_, 5.0));

         if (module == core_)
         {            
            world_.addItem(new Explosion(world_, module->absolutePosition(), velocity_, 25.0));
            world_.removeItem(this);
            return true;
         }

         modules_.removeAll(module);
         delete module;
         return true;
      }
   }

   return false;
}


void Ship::applyLocalForce(const Vector& localForce, const Vector& atLocalPoint)
{
   applyForce(localForce.rotate(orientation_), atLocalPoint.rotate(orientation_));
}

void Ship::applyForce(const Vector& force, const Vector& atPoint)
{
   velocity_ += force * (1.0 / mass_);

   Vector torque = force.cross(atPoint);
   angularMomentum_ += torque;   
}

void Ship::simulateAutopilot()
{
   // Find enemy ship
   QList<Ship*> allShips = world_.ships();
   Ship* targetShip = NULL;

   double closestRange = 1.0/0.0;
   foreach (Ship* ship, allShips)
   {
      if (ship != this)
      {
         double range = (ship->position() - position_).magnitude();
         if (range < closestRange)
         {
            targetShip = ship;
            closestRange = range;
         }
      }
   }

   if (targetShip == NULL)
   {
      return;
   }

   Vector targetVector = targetShip->position() - position_;

   double interceptTime = (targetVector.magnitude() / 0.75);
   targetVector += (targetShip->velocity() * interceptTime);

   Vector target = targetVector;
   target.normalize();

   Vector fromPoint = Vector(0, 0, 1).rotate(orientation_);
   Vector toPoint = target;

   //double maxTorque = 0.1;

   Vector targetRotationAxis = fromPoint.cross(toPoint);
   double targetRotationAngle = asin(targetRotationAxis.magnitude());

   Vector targetAngularVelocity = (targetRotationAxis.normalized() * targetRotationAngle) * -0.1;

   Vector angularVelocityError = (targetAngularVelocity - angularMomentum_);

   //angularVelocityError = angularVelocityError.boundedToMagnitude(maxTorque);

   angularMomentum_ += angularVelocityError; //(angularVelocityError.multiplyElementsBy(inertialTensor_));

   // ============ ENGINE POWER ===============
   double distance = targetVector.magnitude() - 30.0;
   double speed = (velocity_ - targetShip->velocity()).magnitude();
   double maxAcceleration = (0.01 * 1.0 * 2.0) / mass_;

   if (velocity_.dot(targetShip->velocity()) < 0)
   {
      speed *= -1;
   }

   double powerLevel = Autopilot::powerForSmoothApproach(distance, speed, maxAcceleration);

   Quaternion angleToTarget = Vector(0, 0, 1).rotate(orientation_).rotationTo(target);
   double thrust = 0.0;
   if (angleToTarget.angle() < 0.1)
   {
      thrust = powerLevel;

      if (((targetShip->position() - position_).magnitude() < 120))
      {
         foreach(Module* module, modules_)
         {
            if (objectIs(module, Weapon))
            {
               ((Weapon*)module)->fire();
            }
         }
      }
   }  
   foreach(Module* module, modules_)
   {
      if (objectIs(module, Engine))
      {
         Engine& engine = *((Engine*)module);

         int directionSign = (engine.thrustIsForward() ? +1 : -1);
         double thrustForThisEngine = thrust * directionSign;

         ((Engine*)module)->setPower(thrustForThisEngine);
      }
   }


   // ============================================================
   // So if we were to apply -angularVelocity until 

   //bool halfWayPoint = ???;

   //gyro.setPower(Vector(target.x, 0, 0));
}
