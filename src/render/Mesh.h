
#ifndef MESH_H
#define MESH_H

#include <QList>
#include <QVector>

#include <Vector.h>
#include <Quaternion.h>
#include <Color.h>

class Mesh
{

private:
   Mesh(const QString filename, const Color color);
   void loadFileIntoFaces(QString name, QVector<Vector>* list);

public: // These are the meshes you want
   static Mesh& ENGINE;
   static Mesh& FLIGHT_COMPUTER;
   static Mesh& GYRO;
   static Mesh& WEAPON;
   static Mesh& STRUCT;

   static Mesh& DEFLECTOR;
   static Mesh& EXPLOSION;
   static Mesh& THRUST;

public:
   void renderRawVerts(bool shitty);

   void renderExplodingVerts(double distance);

private:
   QString name_;
   Color color_;

   QVector<Vector>* faceData_;
   QVector<Vector>* faceLoData_;
};

#endif
