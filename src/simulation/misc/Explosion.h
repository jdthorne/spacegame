#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <WorldItem.h>

class World;
class Mesh;

class Explosion : public WorldItem
{

public:
   Explosion(World& world, const Vector position, const Vector velocity, double size);
   virtual ~Explosion();

   virtual void simulate();
   virtual void render();

   virtual const Vector position();
   virtual const Quaternion orientation();

private:
   World& world_;
   Mesh& mesh_;

   Vector position_;
   Vector velocity_;

   double life_;
};

#endif
