#include <QMouseEvent>

#include <OpenGlCore.h>
#include <Quaternion.h>
#include <Simulation.h>
#include <RenderCore.h>
#include <WorldItem.h>
#include <CameraSidebar.h>
#include <Camera.h>
#include <Ship.h>
#include <glut.h>
#include <math.h>


#define FPS_SAMPLE_FRAMES 240.0

OpenGlCore::OpenGlCore(QWidget* parent)
   : QGLWidget(parent)
   , timer_(this)
   , simulation_(NULL)
   , renderCore_(new RenderCore())
   , frames_(FPS_SAMPLE_FRAMES)
   , xStart_(0)
   , yStart_(0)
   , renderReady_(true)
{
   setMouseTracking(true);
   time_.start();

   connect(&timer_, SIGNAL(timeout()), this, SLOT(handleTimeout()));
   timer_.start(1000 / 60);

   setFocusPolicy(Qt::StrongFocus);
}

void OpenGlCore::loadSimulation(Simulation* simulation)
{
   simulation_ = simulation;
}

OpenGlCore::~OpenGlCore()
{
}  

void OpenGlCore::initializeGL()
{
   renderCore_->initialize();
}

void OpenGlCore::resizeGL(int w, int h)
{
   glViewport(0, 0, w, h);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   gluPerspective(55.0f, (GLfloat)w/(GLfloat)h, 0.1f, 5000.0f);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void OpenGlCore::paintGL()
{
   if (!renderReady_)
   {  
      return;
   }

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   if (simulation_ == NULL)
   {
      return;
   }

   renderCore_->render(simulation_->world());
   renderReady_ = false;
}

void OpenGlCore::handleTimeout()
{
   if (renderReady_)
   {
      return;
   }

   calculateFramerate();

   if (simulation_ != NULL)
   {
      simulation_->simulate();

      renderReady_ = true;
   }

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
   if (event->buttons() == Qt::LeftButton)
   {
      double deltaX = ((double)(event->x() - xStart_) / width());
      double deltaY = ((double)(event->y() - yStart_) / height());

      Quaternion xRotation = Quaternion(deltaX * -5, Vector(0, 1, 0));
      Quaternion yRotation = Quaternion(deltaY * +5, Vector(1, 0, 0));

      simulation_->world().camera().addUserOrientation(xRotation * yRotation);
   }

   xStart_ = event->x();
   yStart_ = event->y();
}

void OpenGlCore::wheelEvent(QWheelEvent* event)
{
   simulation_->world().camera().addZoom(event->delta() * 0.025);
}

void OpenGlCore::mousePressEvent(QMouseEvent* event)
{
}
void OpenGlCore::mouseReleaseEvent(QMouseEvent* event)
{

}

void OpenGlCore::keyPressEvent(QKeyEvent* event)
{
   simulation_->world().camera().focusOnRandomItem();
}
