#include <QMouseEvent>

#include <OpenGlCore.h>
#include <Quaternion.h>
#include <glut.h>
#include <math.h>


#define FPS_SAMPLE_FRAMES 240.0

OpenGlCore::OpenGlCore()
   : timer_(this)
   , world_()
   , renderCore_(world_)
   , frames_(FPS_SAMPLE_FRAMES)
   , xRotation_(0)
   , yRotation_(0)
   , distance_(10)
{
   setMouseTracking(true);
   time_.start();

   connect(&timer_, SIGNAL(timeout()), this, SLOT(handleTimeout()));
   timer_.start(1000 / 60);
}

OpenGlCore::~OpenGlCore()
{
   qDebug("Destroyed!");
}  

void OpenGlCore::initializeGL()
{
   renderCore_.initialize();
}

void OpenGlCore::resizeGL(int w, int h)
{
   glViewport(0, 0, w, h);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   gluPerspective(90.0f, (GLfloat)w/(GLfloat)h, 0.1f, 5000.0f);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void OpenGlCore::paintGL()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //if (world_.hasRemainingShips())
   //{
      //WorldItem& focus = world_.focusItem();
      Vector focusPoint = Vector(0, 0, 0);

      xRotation_ = qBound(-0.5, xRotation_, +0.5);
      yRotation_ = qBound(-0.5, yRotation_, +0.5);
      distance_ = qBound(1.0, distance_, 100.0);

      Quaternion xQuat = Quaternion(M_PI * 4 * xRotation_, Vector(0, 1, 0));
      Quaternion yQuat = Quaternion(M_PI * yRotation_, Vector(1, 0, 0));
      Quaternion userOrientation = xQuat * yQuat;

      Vector cameraDistance = Vector(0, 0, distance_);
      Vector cameraOffset = cameraDistance.rotate(userOrientation);

      cameraPosition_ = focusPoint + cameraOffset;

      Vector cameraFocusPoint = focusPoint;

      Vector positionToFocus = (cameraPosition_ - cameraFocusPoint).normalized();
      cameraOrientation_ = Vector(0, 0, 1).rotationTo(positionToFocus);
   //}

   renderCore_.render(cameraPosition_, cameraOrientation_);
}

void OpenGlCore::handleTimeout()
{
   calculateFramerate();

   if (world_.hasRemainingShips())
   {
      Ship* ship = world_.ships()[0];
      ship->lockToTestBench();
   }

   world_.simulate();

   update();
}

void OpenGlCore::calculateFramerate()
{
  if (frames_ <= 0)
   {
      qDebug("Current framerate: %f", (FPS_SAMPLE_FRAMES / (time_.elapsed() / 1000.0)));

      time_.start();
      frames_ = FPS_SAMPLE_FRAMES;
   }
   frames_--;
}

void OpenGlCore::mouseMoveEvent(QMouseEvent* event)
{
   xRotation_ = ((double)event->x() / width()) - 0.5;
   yRotation_ = ((double)event->y() / height()) - 0.5;
}

void OpenGlCore::wheelEvent(QWheelEvent* event)
{
   distance_ -= (event->delta() * 0.025);
}


#include <Bullet.h>
void OpenGlCore::mousePressEvent(QMouseEvent* event)
{
   if (!world_.hasRemainingShips())
   {
      Ship* newShip = Ship::createSwarmer(world_, Vector(0, 0, 0), 0);
      world_.addItem(newShip);
      return;
   }

   Vector randomness = world_.randomVector(-0.02, 0.02);
   Bullet* bullet = new Bullet(world_, NULL, Vector(0, 40, 40), Vector(0, -1, -1) + randomness, 1);

   world_.addItem(bullet);
}