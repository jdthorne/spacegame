
// Qt

// Spacegame
#include <RigidBody.h>
#include <cmath>

RigidBody::RigidBody()
   : position_()
   , velocity_()
   , orientation_()
   , angularMomentum_()
   , inertialTensor_()
   , inverseInertialTensor_()
   , mass_(1.0)
{
}

RigidBody::~RigidBody()
{
}

const Vector RigidBody::angularVelocity()
{
   return angularMomentum_.multiplyElementsBy(inverseInertialTensor_);
}

void RigidBody::simulatePhysics()
{
   // Linear
   position_ += velocity_;

   // Rotational
   Quaternion spin = (-0.5 * Quaternion(angularVelocity())) * orientation_;

   orientation_ += spin;

   orientation_.normalize();
}

void RigidBody::applyLocalForce(const Vector localForce, const Vector atLocalPoint)
{
   applyForce(localForce.rotate(orientation_), atLocalPoint.rotate(orientation_));
}

void RigidBody::applyForce(const Vector force, const Vector atPoint)
{
   velocity_ += force * (1.0 / mass_);

   applyTorque(force.cross(atPoint));
}

void RigidBody::applyTorque(const Vector torque)
{
   angularMomentum_ += torque;   
}

