
#ifndef MESH_H
#define MESH_H

#include <QList>

#include <Vector.h>
#include <Quaternion.h>

struct Face
{
   Vector normal_;
   QList<Vector> vertices_;
};

class Mesh
{

public:
   Mesh(const QString& filename);

   void render(const Vector& position, const Quaternion& rotation);

private:
   QList<Face> faces_;
};

#endif
