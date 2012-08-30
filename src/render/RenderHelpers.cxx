
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

