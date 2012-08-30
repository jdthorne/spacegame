
// Qt
#include <QGLWidget>

// Spacegame
#include <RenderCore.h>
#include <World.h>
#include <Mesh.h>
#include <RenderHelpers.h>
#include <Ship.h>

#include <Engine.h>
#include <FlightComputer.h>
#include <Weapon.h>
#include <Gyro.h>
#include <Structure.h>

#include <Bullet.h>
#include <Explosion.h>

#include <glut.h>

using namespace RenderHelpers;

RenderCore::RenderCore(World& world)
   : world_(world)
{
   for (int i = 0; i < 500; i++)
   {
      Vector direction = world_.randomVector(-1.0, 1.0).normalized();
      Vector position = (direction * 400.0);

      stars_.append(position);
   }
}

RenderCore::~RenderCore()
{
}

void RenderCore::render(const Vector cameraPosition, const Quaternion cameraOrientation)
{
   cameraPosition_ = cameraPosition;
   cameraOrientation_ = cameraOrientation;

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   setupCamera();

   drawStars();
   drawBasicMeshes();
   drawBullets();
   drawEffects();
}

/**
 ******************************************************************************
 *
 * \brief            High-level drawing commands
 * @{
 ******************************************************************************
 */
void RenderCore::setupCamera()
{
   Vector eye = cameraPosition_;
   Vector focus = cameraPosition_ + Vector(0, 0, -10).rotate(cameraOrientation_);

   gluLookAt(eye.x, eye.y, eye.z,
             focus.x, focus.y, focus.z,
             0, 1, 0);
}

void RenderCore::drawStars()
{
   glPushMatrix();
   glDisable(GL_LIGHTING);

   glPointSize(2.0);
   glColor3f(1.0, 1.0, 1.0);

   //glTranslatev(cameraPosition_);

   glBegin(GL_POINTS);
   foreach(Vector star, stars_)
   {
      glVertex3f(star.x, star.y, star.z);
   }
   glEnd();
   glPopMatrix();
}

void RenderCore::drawBasicMeshes()
{
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHTING);

   foreach(Ship* ship, world_.ships())
   {
      drawShip(*ship);
   }

   glDisable(GL_LIGHTING);
}

void RenderCore::drawBullets()
{
   glBegin(GL_LINES);

   foreach(Bullet* bullet, world_.items().all<Bullet*>())
   {
      Vector start = bullet->position();
      Vector end = bullet->position() + bullet->velocity();

      double alpha = bullet->life() / Bullet::MAX_LIFE;
      if (bullet->team() == 0)
      {
         glColor4f(1.0, 0.75, 0.25, alpha);
      }
      else
      {
         glColor4f(0.25, 0.75, 1.0, alpha);
      }

      glVertexv(start);
      glVertexv(end);
   }

   glEnd();
}

void RenderCore::drawEffects()
{
   //glEnable(GL_DEPTH_TEST);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE);

   drawExplosions();  
   drawEngineFlares();

   glDisable(GL_BLEND);
}

//! @}

/**
 ******************************************************************************
 *
 * \brief            Ship Drawing
 * @{
 ******************************************************************************
 */
void RenderCore::drawShip(Ship& ship)
{
   double distance = (cameraPosition_ - ship.position()).magnitude();
   bool shitty = (distance > 15);
 
   Color teamRed = Color(1.0, 0.0, 0.0, 1.0);
   Color teamBlue = Color(0.0, 0.0, 1.0, 1.0);

   Color teamColor = (ship.team() == 0 ? teamRed : teamBlue);

   foreach (Module* module, ship.modules())
   {
      Mesh& mesh =   objectIs(module, Engine)         ? Mesh::ENGINE
                   : objectIs(module, FlightComputer) ? Mesh::FLIGHT_COMPUTER
                   : objectIs(module, Weapon)         ? Mesh::WEAPON
                   : objectIs(module, Structure)      ? Mesh::STRUCT
                   : objectIs(module, Gyro)           ? Mesh::GYRO
                   : Mesh::DEFLECTOR;

      Color color = objectIs(module, FlightComputer) ? teamColor : Color(1, 1, 1, 1);

      mesh.render(module->absolutePosition(), module->absoluteOrientation(), 1.0, shitty, color);
   }
}

//! @}

/**
 ******************************************************************************
 *
 * \brief            Effect Drawing
 * @{
 ******************************************************************************
 */
void RenderCore::drawExplosions()
{
   foreach(Explosion* explosion, world_.items().all<Explosion*>())
   {
      bool shitty = true;
      Vector base = explosion->position();
      double alpha = explosion->glow();
      double scale = explosion->size();


      foreach(Vector frag, explosion->fragments())
      {
         glPushMatrix();

         Vector position = frag + base;
         glTranslatev(position);
         glColor4f(1.0, 0.75, 0.25, 0.4 * alpha);

         float modelView[16];
         glGetFloatv(GL_MODELVIEW_MATRIX, modelView);

         for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++)
         {
            modelView[i*4 + j] = (i == j ? 1.0 : 0.0);
         }
         glLoadMatrixf(modelView);
         glScalef(scale, scale, scale);

         Mesh::EXPLOSION.renderRawVerts(shitty);

         glPopMatrix();
      }
   }
}

void RenderCore::drawEngineFlares()
{
   foreach(Ship* ship, world_.ships())
   {
      foreach(Engine* engine, ship->modules().all<Engine*>())
      {
         if (engine->power() > 0.1)
         {
            Mesh::THRUST.render(engine->absolutePosition(), engine->absoluteOrientation(), 1.0, shittyRange(engine->absolutePosition()));
         }
      }
   }
}

//! @}
/**
 ******************************************************************************
 *
 * \brief            Helpers
 * @{
 ******************************************************************************
 */

bool RenderCore::shittyRange(const Vector position)
{
   return (position - cameraPosition_).magnitude() > 15;
}


//! @}