#ifndef SHIP_H
#define SHIP_H

#include <QList>

#include <Vector.h>
#include <WorldItem.h>
#include <Quaternion.h>
#include <RacistList.h>
#include <RigidBody.h>
#include <Hud.h>

class Module;
class World;
class Engine;
class Weapon;
class ShipControl;
class Autopilot;

class Ship : public RigidBody, public WorldItem
{

private:
   Ship(World& world, const Vector position, const Vector velocity, int team);
   virtual ~Ship();

public:
   static Ship* createSwarmer(World& world, const Vector position, const Vector velocity, int team);
   static Ship* createAstronach(World& world, const Vector position, const Vector velocity, int team);

public:
   RacistList<Module*> modules();

   int team();
   int id();
   World& world();

   int boredom();

   virtual void simulateMovement();
   virtual void simulateCollisions();
   virtual void simulateLogic();

   void simulateModules();
   void simulateShipToShipCollisions();

   void normalizeModules();
   void lockToTestBench();

   virtual const Vector position();
   virtual const Vector velocity();
   virtual const Quaternion orientation();

   void explodeAllUnattachedModules(int forTeam);
   void explodeModule(Module* module, int forTeam);
   void explode(int forTeam);

   double deflectorRadius();
   double deflectorGlow();
   bool applyCollisionWith(double distance, const Vector position, const Vector velocity, int team);

   void handleExcitement();

   Hud& hud();

private:
   World& world_;
   ShipControl* shipControl_;
   Autopilot* autopilot_;
   int team_;
   int id_;
   int boredom_;

   double deflectorPower_;
   double deflectorGlow_;

   double maxModuleRadius_;

   Module* core_;
   RacistList<Module*> modules_;

   Hud hud_;

   friend class ShipControl;
};

#endif
