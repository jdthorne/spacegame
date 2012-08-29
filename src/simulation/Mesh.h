
#ifndef MESH_H
#define MESH_H

#include <QList>

#include <Vector.h>
#include <Quaternion.h>
#include <Color.h>

struct Face
{
   Vector normal_;
   QList<Vector> vertices_;
};

class Mesh
{

private:
   Mesh(const QString filename, const Color color);
   void loadFileIntoFaces(QString name, QList<Face>* list_);

public:
   void render(const Vector position, const Quaternion rotation, double scale = 1.0);

   static Mesh& byName(const QString name);

   static void renderLine(const Vector start, const Vector end, double alpha);
   static bool shitty;

private:
   QString name_;
   Color color_;

   QList<Face>* faces_;
   QList<Face>* facesLo_;
};

#endif
