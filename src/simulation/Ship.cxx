#include <Ship.h>
#include <Engine.h>
#include <Gyro.h>
#include <Vector.h>
#include <cmath>

Ship::Ship()
{
   orientation_.normalize();

   installModule(new Engine(*this, Vector(-1, 0, 0), Quaternion::DEFAULT));
   installModule(new Engine(*this, Vector(1, 0, 0), Quaternion::DEFAULT));

   installModule(new Module("structure", *this, Vector(0, 0, 1), Quaternion()));
   installModule(new Gyro(*this, Vector(0, 0, -0.5)));
   //installModule(new Module("weapon", *this, Vector(0, -1, 0), Quaternion()));

   normalizeModules();
}

Ship::~Ship()
{

}

void Ship::normalizeModules()
{
   Vector centerOfMass;

   inertialTensor_ = Vector();
   foreach (Module* m, modules_)
   {
      double mass = m->mass();
      const Vector& position = m->position();

      centerOfMass += position * mass;

      inertialTensor_.x += mass * (position.y*position.y + position.z*position.z);
      inertialTensor_.y += mass * (position.x*position.x + position.z*position.z);
      inertialTensor_.z += mass * (position.x*position.x + position.y*position.y);
   }

   inverseInertialTensor_ = inertialTensor_.inverse();

   // Move modules
   foreach (Module* m, modules_)
   {
      m->setPosition(m->position() - centerOfMass);
   }
}

const Vector& Ship::position()
{
   return position_;
}

const Quaternion& Ship::orientation()
{
   return orientation_;
}

void Ship::installModule(Module* module)
{
   modules_.append(module);   
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
}

void Ship::applyLocalForce(const Vector& localForce, const Vector& atLocalPoint)
{
   applyForce(localForce.rotate(orientation_), atLocalPoint.rotate(orientation_));
}

void Ship::applyForce(const Vector& force, const Vector& atPoint)
{
   velocity_ += force;

   Vector torque = force.cross(atPoint);
   angularMomentum_ += torque;   
}

void Ship::simulateAutopilot()
{
   Vector target = Vector(-5, 2, 0);
   target.normalize();

   Vector fromPoint = Vector(0, 0, 1).rotate(orientation_);
   Vector toPoint = target;

   //Quaternion targetOrientation = fromPoint.rotationTo(toPoint);

   double maxTorque = 0.01;

   Vector targetRotationAxis = fromPoint.cross(toPoint);
   double targetRotationAngle = asin(targetRotationAxis.magnitude());

   Vector targetAngularVelocity = (targetRotationAxis.normalized() * targetRotationAngle) * -0.1;

   Vector angularVelocityError = (targetAngularVelocity - angularMomentum_);

   angularVelocityError = angularVelocityError.boundedToMagnitude(maxTorque);

   qDebug("Torquing by %f", angularVelocityError.magnitude());

   angularMomentum_ += angularVelocityError;

   //qDebug("Target angular velocity: %s ==> Actual %s", qPrintable(angularVelocity.toString()), qPrintable(angularMomentum_.toString()));

   // ============================================================
   // So if we were to apply -angularVelocity until 

   //bool halfWayPoint = ???;

   //gyro.setPower(Vector(target.x, 0, 0));
}
