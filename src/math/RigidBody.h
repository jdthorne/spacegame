#ifndef RIGIDBODY
#define RIGIDBODY

// Qt
#include <QString>

// Spacegame
#include <Vector.h>
#include <Quaternion.h>

/**
 ******************************************************************************
 *
 * \brief            RigidBody
 *
 ******************************************************************************
 */
class RigidBody
{

public:
   RigidBody();
   ~RigidBody();

public:
   void simulatePhysics();
   void applyLocalForce(const Vector force, const Vector atPoint);
   void applyForce(const Vector force, const Vector atPoint);

public:
   const Vector angularVelocity();

private: // helpers

protected: // members
   Vector position_;
   Vector velocity_;

   Quaternion orientation_;
   Vector angularMomentum_;

   Vector inertialTensor_;
   Vector inverseInertialTensor_;

   double mass_;

};

#endif
