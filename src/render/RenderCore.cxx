
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
#include <Camera.h>

#include <Engine.h>
#include <FlightComputer.h>
#include <Weapon.h>
#include <Gyro.h>
#include <Structure.h>

#include <Bullet.h>
#include <Explosion.h>

#include <glut.h>

using namespace RenderHelpers;

RenderCore::RenderCore()
   : world_(NULL)
{
   World world;

   for (int i = 0; i < 500; i++)
   {
      Vector direction = world.randomVector(-1.0, 1.0).normalized();
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
void RenderCore::render(const World& world, const Camera& camera)
{
   world_ = &world;
   camera_ = &camera;

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   setupCamera();

   drawStars();
   drawBasicMeshes();
   drawEffects();
}

void RenderCore::setupCamera()
{
   Quaternion look = camera_->orientation();
   glRotateq(look);
   glTranslatev(camera_->position() * -1);
}

void RenderCore::drawStars()
{
   glPushMatrix();
   glDisable(GL_LIGHTING);

   glPointSize(2.0);
   glColor3f(1.0, 1.0, 1.0);

   glTranslatev(camera_->position());

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

   foreach(Ship* ship, world_->ships())
   {
      drawShip(*ship);
   }

   glDisable(GL_LIGHTING);
}

void RenderCore::drawEffects()
{
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE);
   glDepthMask(GL_FALSE);

   drawExplosions();  
   drawBullets();  
   drawEngineFlares();

   glDepthMask(GL_TRUE);
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
   double distance = (camera_->position() - ship.position()).magnitude();
   bool shitty = (distance > 15);
 
   Color teamRed = Color(1.0, 0.0, 0.0, 1.0);
   Color teamBlue = Color(0.0, 0.0, 1.0, 1.0);

   Color teamColor = (ship.team() == 0 ? teamRed : teamBlue);

   glPushMatrix();
   glTranslatev(ship.position());
   glRotateq(ship.orientation());

   foreach (Module* module, ship.modules())
   {
      bool isColored = objectIs(module, FlightComputer) || objectIs(module, Structure);
      Color color = isColored ? teamColor : Color(1, 1, 1, 1);
      glColorc(Color(0.2, 0.2, 0.2, 1.0) * color);

      glPushMatrix();
      glTranslatev(module->position());
      glRotateq(module->orientation());

      meshForType(typeOf(module)).renderRawVerts(shitty);

      glPopMatrix();
   }

   glPopMatrix();
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
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   foreach(Explosion* explosion, world_->items().all<Explosion*>())
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

   glBlendFunc(GL_SRC_ALPHA, GL_ONE);

   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textures_[0]);

   foreach(Explosion* explosion, world_->items().all<Explosion*>())
   {
      double alpha = explosion->glow();
      double scale = explosion->size();

      glColorc(Color::glowForTeam(explosion->team(), 0.4 * alpha));
      foreach(Vector frag, explosion->fragments())
      {
         drawExplosionFragment(explosion, frag, scale);
      }

      glColorc(Color::glowForTeam(explosion->team(), 0.2 * alpha));
      drawExplosionFragment(explosion, Vector(0, 0, 0.01), scale * 15.0);
      drawExplosionFragment(explosion, Vector(0, 0, 0.01), scale * 30.0);
   }

   glDisable(GL_TEXTURE_2D);
}

void RenderCore::drawExplosionFragment(Explosion* explosion, const Vector frag, double scale)
{
   Vector position = frag + explosion->position();
   glSphere(position, scale);
}

void RenderCore::drawBullets()
{
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textures_[0]);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE);

   foreach(Bullet* bullet, world_->items().all<Bullet*>())
   {
      glColorc(Color::glowForTeam(bullet->team(), 0.1));
      glSphere(bullet->position(), 2.0);

      glColorc(Color::glowForTeam(bullet->team(), 1.0));
      glSphere(bullet->position(), 0.2);
   }

   glDisable(GL_TEXTURE_2D);
}

void RenderCore::drawEngineFlares()
{
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE);

   foreach(Ship* ship, world_->ships())
   {
      foreach(Engine* engine, ship->modules().all<Engine*>())
      {
         Color color = Color(0.25, 0.75, 1.0, engine->glow());
         Q_UNUSED(color);
         //Mesh::THRUST.render(engine->absolutePosition(), engine->absoluteOrientation(), 1.0, shittyRange(engine->absolutePosition()), color);
      }
   }

   glDisable(GL_BLEND);
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
   return (position - camera_->position()).magnitude() > 90;
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