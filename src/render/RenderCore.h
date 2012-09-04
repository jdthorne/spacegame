#ifndef RENDERCORE
#define RENDERCORE

// Qt
#include <QString>
#include <QList>
#include <QVector>
#include <QGLWidget>

// Spacegame
#include <ObjectType.h>
#include <World.h>
#include <Explosion.h>

class Ship;
class Module;
class Mesh;
class Camera;

/**
 ******************************************************************************
 *
 * \brief            Renders a world
 *
 ******************************************************************************
 */
class RenderCore
{

public:
   RenderCore();
   ~RenderCore();

public:
   void initialize();
   void render(const World& world, const Camera& camera);
   
private: // helpers
   void loadGeneral();
   void loadTextures();

   void setupCamera();

   void drawStars();
   void drawBasicMeshes();
   void drawBullets();
   void drawEffects();

   void drawShip(Ship& ship);

   void drawExplosions();
   void drawExplosionFragment(Explosion* explosion, const Vector frag, double scale);
   void drawFlareMeshes();
   void drawFlareGlows();

   bool shittyRange(const Vector position);

private:
   Mesh& meshForType(ObjectType type);

private: // members
   const World* world_;
   const Camera* camera_;

   QVector<Vector> stars_;

   GLuint* textures_;
};

#endif
