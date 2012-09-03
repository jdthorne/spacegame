#ifndef RENDERHELPERS
#define RENDERHELPERS

// Qt
#include <QString>

// Spacegame
#include <Color.h>
#include <Quaternion.h>
#include <Vector.h>

namespace RenderHelpers
{
   void glRotateq(const Quaternion quat);
   void glTranslatev(const Vector vertex);
   void glVertexv(const Vector vertex);
   void glNormalv(const Vector vertex);
   void glColorc(const Color color);

   void glSphere(const Vector position, double scale);

   void glBillboard();
}

#endif
