
// Qt
#include <QGLWidget>

// lodepng
#include <lodepng.h>

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

/**
 ******************************************************************************
 *
 * \brief            Initialization of OpenGL
 *
 ******************************************************************************
 */
void RenderCore::initialize()
{
   loadGeneral();
   loadTextures();
}

void RenderCore::loadGeneral()
{
   glEnable(GL_NORMALIZE);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   GLfloat mat_specular[] = { 0.2, 0.2, 0.2, 1.0 };
   GLfloat mat_shininess[] = { 1.0 };
   GLfloat light_position[] = { 0, 0, 1.0, 0.0 };
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_BACK, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);

   glShadeModel(GL_SMOOTH);
   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
   glClearDepth(1.0f);

   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);

   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void RenderCore::loadTextures()
{
   int numberOfTextures = 1;

   textures_ = new GLuint[numberOfTextures];
   glGenTextures(numberOfTextures, textures_);

   glBindTexture(GL_TEXTURE_2D, textures_[0]);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

   unsigned int width = 128;
   unsigned int height = 128;
   unsigned char* data = new unsigned char[4 * width * height];

   int error = lodepng_decode32_file(&data, &width, &height, "./meshes/textures/splosion.png");
   if (error)
   {
      qDebug("Error loading texture: %d (%s)", error, lodepng_error_text(error));
   }

   gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);

   
   delete [] data;
}

/**
 ******************************************************************************
 *
 * \brief            High-level drawing commands
 * @{
 ******************************************************************************
 */
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

   glTranslatev(cameraPosition_);

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
   return;
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
      Mesh& mesh = meshForType(typeOf(module));

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
      if (explosion->explodingObjectType() == NullType)
      {
         continue;
      }

      double timeline = explosion->expansion();
      double alpha = 1.0;
      if (timeline > 0.6)
      {
         alpha = (1.0 - timeline) / 0.4;
      }

      glColor4f(0.3, 0.3, 0.3, alpha);

      glPushMatrix();

      glTranslatev(explosion->position());
      glRotateq(explosion->orientation());

      meshForType(explosion->explodingObjectType()).renderExplodingVerts(timeline * 2.0);

      glPopMatrix();
   }

   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textures_[0]);

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE);

   glDisable(GL_COLOR_MATERIAL);

   glDepthMask(GL_FALSE);

   foreach(Explosion* explosion, world_.items().all<Explosion*>())
   {
      double alpha = explosion->glow();
      double scale = explosion->size();
      glColor4f(1.0, 0.75, 0.25, 0.4 * alpha);

      foreach(Vector frag, explosion->fragments())
      {
         drawExplosionFragment(explosion, frag, scale);
      }

      glColor4f(1.0, 0.75, 0.25, 0.2 * alpha);
      drawExplosionFragment(explosion, Vector(0, 0, 0.01), scale * 15.0);
      drawExplosionFragment(explosion, Vector(0, 0, 0.01), scale * 30.0);
   }

   glDisable(GL_TEXTURE_2D);
   glDepthMask(GL_TRUE);
}

void RenderCore::drawExplosionFragment(Explosion* explosion, const Vector frag, double scale)
{
   glPushMatrix();

   Vector position = frag + explosion->position();
   glTranslatev(position);

   glBillboard();

   glScalef(scale, scale, scale);
   glRotatef(0.5, frag.x, frag.y, frag.z);
   glBegin(GL_QUADS);

   glTexCoord2d(0.0, 0.0); glVertex2d(-1.0, -1.0);
   glTexCoord2d(1.0, 0.0); glVertex2d(1.0, -1.0);
   glTexCoord2d(1.0, 1.0); glVertex2d(1.0, 1.0);
   glTexCoord2d(0.0, 1.0); glVertex2d(-1.0, 1.0);

   glEnd();

   glPopMatrix();
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
   return (position - cameraPosition_).magnitude() > 45;
}

Mesh& RenderCore::meshForType(ObjectType type)
{
   Mesh& mesh =   typeIs(type, Engine)         ? Mesh::ENGINE
                : typeIs(type, FlightComputer) ? Mesh::FLIGHT_COMPUTER
                : typeIs(type, Weapon)         ? Mesh::WEAPON
                : typeIs(type, Structure)      ? Mesh::STRUCT
                : typeIs(type, Gyro)           ? Mesh::GYRO
                : Mesh::DEFLECTOR;

   return mesh;
}


//! @}