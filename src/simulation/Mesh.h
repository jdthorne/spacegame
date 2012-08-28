
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

private:
   Mesh(const QString filename, const Vector color);

public:
   void render(const Vector position, const Quaternion rotation);

   static Mesh& byName(const QString name);

private:
   QString name_;
   Vector color_;
   QList<Face> faces_;
};

#endif
