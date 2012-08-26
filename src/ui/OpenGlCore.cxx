#include <OpenGlCore.h>
#include <glut.h>

OpenGlCore::OpenGlCore()
   : depth_(-6.0)
   , testMesh_("./meshes/engine.mesh")
{
   connect(&timer_, SIGNAL(timeout()), this, SLOT(handleTimeout()));

   timer_.start(1000 / 60);
}

void OpenGlCore::initializeGL()
{
   glShadeModel(GL_SMOOTH);
   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
   glClearDepth(1.0f);

   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);

   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void OpenGlCore::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, (GLfloat)w/(GLfloat)h, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
 }

void OpenGlCore::paintGL()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glTranslatef(-1.5f, 0.0f, depth_); 
   glRotatef(depth_ * 25, 1.0, 0.0, 0.0);
   glBegin(GL_TRIANGLES);                      // Drawing Using Triangles

   testMesh_.render();

   glEnd();                            // Finished Drawing The Triangle
}  

void OpenGlCore::handleTimeout()
{
   depth_ -= 0.1;
   qDebug("Depth: %f", depth_);
   update();
}