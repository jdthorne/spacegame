
#ifndef MESH_H
#define MESH_H

#include <Vector.h>

class Mesh
{

public:
   Mesh(QString filename);

   void render();

private:
   QList<Vector> vertices_;
   
};

#endif
