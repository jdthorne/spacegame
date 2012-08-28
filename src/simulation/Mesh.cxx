
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QGLWidget>

#include <Mesh.h>

Mesh::Mesh(const QString& name)
{
   QString filename = "./meshes/" + name + ".mesh";

   QFile file(filename);
   file.open(QIODevice::ReadOnly);

   QTextStream fileReader(&file);   

   Face face;
   while (!fileReader.atEnd())
   {
      QString line = fileReader.readLine();

      if (line.length() > 1)
      {
         double x = line.split(" ")[0].toDouble();
         double y = line.split(" ")[1].toDouble();
         double z = line.split(" ")[2].toDouble();

         Vector point = Vector(x, y, z);
         face.vertices_.append(point);
      }
      else if (face.vertices_.count() == 3)
      {
         Vector aToB = (face.vertices_[0] - face.vertices_[1]);
         Vector aToC = (face.vertices_[0] - face.vertices_[2]);

         face.normal_ = aToB.cross(aToC);
         faces_.append(face);

         face = Face();
      }
   }
}

double toDeg(double rad)
{
   return (rad * 180) / 3.1415926535;
}

void Mesh::render(const Vector& position, const Quaternion& rotation)
{
   glPushMatrix();
   glTranslatef(position.x, position.y, position.z);

   double angle = rotation.angle();
   if (angle > 0.000001)
   {
      Vector axis = rotation.axis();
      glRotatef(toDeg(angle), axis.x, axis.y, axis.z);
   }

   glBegin(GL_TRIANGLES);
   foreach (Face f, faces_)
   {
      foreach (Vector v, f.vertices_)
      {
         glNormal3f(f.normal_.x, f.normal_.y, f.normal_.z);
         glVertex3f(v.x, v.y, v.z);
      }
   }
   glEnd();

   glPopMatrix();
}
