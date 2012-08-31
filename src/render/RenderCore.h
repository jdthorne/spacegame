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
   RenderCore(World& world);
   ~RenderCore();

public:
   void initialize();
   void render(const Vector cameraPosition, const Quaternion cameraOrientation);
   
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
   void drawEngineFlares();

   bool shittyRange(const Vector position);

private:
   Mesh& meshForType(ObjectType type);

private: // members
   World& world_;

   Vector cameraPosition_;
   Quaternion cameraOrientation_;

   QVector<Vector> stars_;

   GLuint* textures_;
};

#endif
