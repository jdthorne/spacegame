#ifndef SHIP_H
#define SHIP_H

#include <QList>

#include <Vector.h>
#include <Quaternion.h>
#include <Module.h>

class Ship
{

public:
   Ship();
   ~Ship();

   void simulate();
   void simulatePhysics();
   void simulateAutopilot();

   void render();

   void installModule(Module* module);

   void applyLocalForce(const Vector& force, const Vector& atPoint);
   void applyForce(const Vector& force, const Vector& atPoint);

   const Vector& position();
   const Quaternion& orientation();

   void normalizeModules();

private:
   QList<Module*> modules_;

   Vector position_;
   Vector velocity_;

   Quaternion orientation_;
   Vector angularMomentum_;

   Vector inertialTensor_;
   Vector inverseInertialTensor_;
};

#endif
