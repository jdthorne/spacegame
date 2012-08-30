#ifndef SHIP_H
#define SHIP_H

#include <QList>

#include <Vector.h>
#include <WorldItem.h>
#include <Quaternion.h>
#include <Module.h>
#include <RacistList.h>

class World;
class Engine;
class Weapon;

class Ship : public WorldItem
{

private:
   Ship(World& world, const Vector position, int team);
   virtual ~Ship();

public:
   static Ship* createSwarmer(World& world, const Vector position, int team);
   static Ship* createAstronach(World& world, const Vector position, int team);

public:
   RacistList<Module*> modules();

   int team();

   virtual void simulate();
   void simulatePhysics();
   void simulateAutopilot();

   void applyLocalForce(const Vector& force, const Vector& atPoint);
   void applyForce(const Vector& force, const Vector& atPoint);

   virtual const Vector position();
   virtual const Vector velocity();
   virtual const Quaternion orientation();

   void normalizeModules();

   double deflectorRadius();
   bool applyCollisionWith(double distance, const Vector position, const Vector velocity);

private:
   World& world_;
   int team_;

   double deflectorPower_;

   Module* core_;
   RacistList<Module*> modules_;

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
