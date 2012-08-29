#include <QMouseEvent>

#include <OpenGlCore.h>
#include <Quaternion.h>
#include <glut.h>
#include <math.h>


#define FPS_SAMPLE_FRAMES 240.0

OpenGlCore::OpenGlCore()
   : timer_(this)
   , frames_(FPS_SAMPLE_FRAMES)
   , xRotation_(0)
   , yRotation_(0)
{
   setMouseTracking(true);
   time_.start();

   connect(&timer_, SIGNAL(timeout()), this, SLOT(handleTimeout()));
   timer_.start(1000 / 240);
}

OpenGlCore::~OpenGlCore()
{
   qDebug("Destroyed!");
}  

void OpenGlCore::initializeGL()
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

   //glAlphaFunc(GL_ALWAYS, 0.0);

   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

   //glEnable(GL_BLEND);
   //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

   /*

   //Vector cameraFocusPoint = world_.focusItem().position();
   Vector cameraFocusPoint = Vector();


   Vector cameraPosition = cameraFocusPoint + cameraOffset;
   */

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   if (world_.hasRemainingShips())
   {
      WorldItem& focus = world_.focusItem();

      xRotation_ = qBound(-0.5, xRotation_, +0.5);
      yRotation_ = qBound(-0.5, yRotation_, +0.5);

      Quaternion xQuat = Quaternion(M_PI * 4 * xRotation_, Vector(0, 1, 0));
      Quaternion yQuat = Quaternion(M_PI * yRotation_, Vector(1, 0, 0));
      Quaternion cameraOrientation = xQuat * yQuat;

      Vector cameraDistance = Vector(0, 0, 10);
      Vector cameraOffset = cameraDistance.rotate(cameraOrientation);
      Vector cameraPosition = focus.position() + cameraOffset;

      Vector cameraFocusPoint = focus.position(); //(Vector(0, 0, -1).rotate(focus.orientation()));

      gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z,
                cameraFocusPoint.x, cameraFocusPoint.y, cameraFocusPoint.z,
                0.0, -1.0, 0.0);
   }

   world_.render();
}

void OpenGlCore::handleTimeout()
{
   calculateFramerate();

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
