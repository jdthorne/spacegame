#ifndef SHIP_H
#define SHIP_H

#include <QList>

#include <Vector.h>
#include <WorldItem.h>
#include <Quaternion.h>
#include <Module.h>

class World;
class Engine;
class Weapon;

class Ship : public WorldItem
{

public:
   Ship(World& world, const Vector position);
   virtual ~Ship();

   virtual void simulate();
   void simulatePhysics();
   void simulateAutopilot();

   virtual void render();

   void installModule(Module* module);

   void applyLocalForce(const Vector& force, const Vector& atPoint);
   void applyForce(const Vector& force, const Vector& atPoint);

   virtual const Vector position();
   virtual const Quaternion orientation();

   void normalizeModules();

private:
   World& world_;

   QList<Module*> modules_;

   QList<Engine*> engines_;
   QList<Weapon*> weapons_;

   Vector position_;
   Vector velocity_;

   Quaternion orientation_;
   Vector angularMomentum_;

   Vector inertialTensor_;
   Vector inverseInertialTensor_;

   double mass_;

   friend class Weapon;
};

#endif
