#include <Ship.h>
#include <Engine.h>
#include <Weapon.h>
#include <Gyro.h>
#include <Vector.h>
#include <cmath>
#include <World.h>

Ship::Ship(World& world, const Vector position)
   : world_(world)
   , position_(position)
{
   orientation_.normalize();

   installModule(new Engine(*this, Vector(-1, 0, 0), Quaternion::DEFAULT));
   installModule(new Engine(*this, Vector(1, 0, 0), Quaternion::DEFAULT));
   installModule(new Weapon(*this, Vector(1, 1, 0), Quaternion::SPIN_Z));
   installModule(new Weapon(*this, Vector(-1, 1, 0), Quaternion::SPIN_Z));

   installModule(new Module("computer", *this, Vector(0, 0, 1), Quaternion()));
   installModule(new Gyro(*this, Vector(0, 0, -0.5)));

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

const Quaternion Ship::orientation()
{
   return orientation_;
}

void Ship::installModule(Module* module)
{
   modules_.append(module);   

   if (dynamic_cast<Engine*>(module) != NULL)
   {
      engines_.append(dynamic_cast<Engine*>(module));
   }

   if (dynamic_cast<Weapon*>(module) != NULL)
   {
      weapons_.append(dynamic_cast<Weapon*>(module));
   }
}

void Ship::simulate()
{
   simulatePhysics();
   simulateAutopilot();

   foreach (Module* m, modules_)
   {
      m->simulate();
   }
}

void Ship::simulatePhysics()
{
   // Linear
   position_ += velocity_;

   // Rotational
   Vector angularVelocity = angularMomentum_.multiplyElementsBy(inverseInertialTensor_);
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

   Vector target = targetShip->position() - position_;
   target.normalize();

   Vector fromPoint = Vector(0, 0, 1).rotate(orientation_);
   Vector toPoint = target;

   double maxTorque = 0.01;

   Vector targetRotationAxis = fromPoint.cross(toPoint);
   double targetRotationAngle = asin(targetRotationAxis.magnitude());

   Vector targetAngularVelocity = (targetRotationAxis.normalized() * targetRotationAngle) * -0.05;

   Vector angularVelocityError = (targetAngularVelocity - angularMomentum_);

   angularVelocityError = angularVelocityError.boundedToMagnitude(maxTorque);

   angularMomentum_ += angularVelocityError;


   Quaternion angleToTarget = Vector(0, 0, 1).rotate(orientation_).rotationTo(target);
   double thrust = 0.0;
   if (angleToTarget.angle() < 0.1)
   {
      thrust = 1.0;
      foreach(Weapon* weapon, weapons_)
      {
         weapon->fire();
      }
   }  
   foreach(Engine* engine, engines_)
   {
      engine->setPower(thrust);
   }


   // ============================================================
   // So if we were to apply -angularVelocity until 

   //bool halfWayPoint = ???;

   //gyro.setPower(Vector(target.x, 0, 0));
}
