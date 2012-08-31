
// Qt
#include <QGLWidget>

// Spacegame
#include <RenderHelpers.h>

double toDeg(double rad)
{
   return (rad * 180) / 3.1415926535;
}

void RenderHelpers::glRotateq(const Quaternion quat)
{
   double angle = quat.angle();
   if (angle > 0.000001)
   {
      Vector axis = quat.axis();
      glRotatef(toDeg(angle), axis.x, axis.y, axis.z);
   }
}

void RenderHelpers::glVertexv(const Vector vertex)
{
   glVertex3f(vertex.x, vertex.y, vertex.z);
}

void RenderHelpers::glTranslatev(const Vector vertex)
{
   glTranslatef(vertex.x, vertex.y, vertex.z);
}

void RenderHelpers::glNormalv(const Vector vertex)
{
   glNormal3f(vertex.x, vertex.y, vertex.z);
}

void RenderHelpers::glBillboard()
{
   float modelView[16];
   glGetFloatv(GL_MODELVIEW_MATRIX, modelView);

   for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++)
   {
      modelView[i*4 + j] = (i == j ? 1.0 : 0.0);
   }
   glLoadMatrixf(modelView);
}

