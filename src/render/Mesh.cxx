
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QGLWidget>

#include <Mesh.h>
#include <Color.h>
#include <RenderHelpers.h>

using namespace RenderHelpers;

Mesh& Mesh::ENGINE = *(new Mesh("engine", Color(0.5, 0.5, 0.5, 1.0)));
Mesh& Mesh::FLIGHT_COMPUTER = *(new Mesh("computer", Color(0.5, 0.5, 0.5, 1.0)));
Mesh& Mesh::GYRO = *(new Mesh("gyro", Color(0.5, 0.5, 0.5, 1.0)));
Mesh& Mesh::WEAPON = *(new Mesh("weapon", Color(0.5, 0.5, 0.5, 1.0)));
Mesh& Mesh::STRUCT = *(new Mesh("structure", Color(0.5, 0.5, 0.5, 1.0)));

Mesh& Mesh::DEFLECTOR = *(new Mesh("deflector", Color(1.0, 0.2, 0.2, 1.0)));
Mesh& Mesh::EXPLOSION = *(new Mesh("explosion", Color(1.0, 0.5, 0.25, 0.5)));
Mesh& Mesh::THRUST = *(new Mesh("engine-thrust", Color(0, 0.75, 1.0, 0.5)));

Mesh::Mesh(const QString name, const Color color)
   : name_(name)
   , color_(color)
   , faceData_(new QVector<Vector>())
   , faceLoData_(new QVector<Vector>())
{
   
   loadFileIntoFaces(name, faceData_);
   loadFileIntoFaces(name + "-lo", faceLoData_);
}

void Mesh::loadFileIntoFaces(QString name, QVector<Vector>* list)
{
   QString filename = "./meshes/" + name + ".mesh";

   QFile file(filename);
   file.open(QIODevice::ReadOnly);

   QTextStream fileReader(&file);   

   QList<Vector> verts;

   while (!fileReader.atEnd())
   {
      QString line = fileReader.readLine();

      if (line.length() > 1)
      {
         double x = line.split(" ")[0].toDouble();
         double y = line.split(" ")[1].toDouble();
         double z = line.split(" ")[2].toDouble();

         Vector point = Vector(x, y, z);
         verts.append(point);
      }
      else if (verts.count() == 3)
      {
         Vector aToB = (verts[0] - verts[1]);
         Vector aToC = (verts[0] - verts[2]);

         Vector normal = aToB.cross(aToC);
         normal.normalize();

         list->append(normal);
         list->append(verts[0]);
         list->append(verts[1]);
         list->append(verts[2]);

         verts.clear();
      }
      else
      {
         //qDebug("Error: %s.mesh: Encountered an unexpected number of verts: %d", 
         // qPrintable(name), face.vertices_.count());
         verts.clear();
      }
   }

   file.close();
}

void Mesh::render(const Vector position, const Quaternion rotation, double scale, bool shitty, Color colorModifier)
{
   glPushMatrix();

   glTranslatev(position);
   glRotateq(rotation);
   glScalef(scale, scale, scale);

   glColor4f(color_.r * colorModifier.r, 
             color_.g * colorModifier.g, 
             color_.b * colorModifier.b, 
             color_.a * colorModifier.a);

   renderRawVerts(shitty);

   glPopMatrix();
}

void Mesh::renderRawVerts(bool shitty)
{
   glBegin(GL_TRIANGLES);
   QVector<Vector>& data = *(shitty ? faceLoData_ : faceData_);

   int i = 0;
   while (i < data.count())
   {
      glNormalv(data[i++]);
      glVertexv(data[i++]);
      glVertexv(data[i++]);
      glVertexv(data[i++]);
   }
   glEnd();
}
