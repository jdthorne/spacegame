#ifndef RENDERCORE
#define RENDERCORE

// Qt
#include <QString>
#include <QList>
#include <QVector>

// Spacegame
#include <World.h>

class Ship;

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
   void render(const Vector cameraPosition, const Quaternion cameraOrientation);
   
private: // helpers
   void setupCamera();

   void drawStars();
   void drawBasicMeshes();
   void drawBullets();
   void drawEffects();

   void drawShip(Ship& ship);

   void drawExplosions();
   void drawEngineFlares();

   bool shittyRange(const Vector position);

private: // members
   World& world_;

   Vector cameraPosition_;
   Quaternion cameraOrientation_;

   QVector<Vector> stars_;
};

#endif
