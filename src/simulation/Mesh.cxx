
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QGLWidget>

#include <Mesh.h>

Mesh::Mesh(QString filename)
{
   QFile file(filename);
   file.open(QIODevice::ReadOnly);

   QTextStream fileReader(&file);   
   while (!fileReader.atEnd())
   {
      QString line = fileReader.readLine();

      if (line.length() > 1)
      {
         double x = line.split(" ")[0].toDouble();
         double y = line.split(" ")[1].toDouble();
         double z = line.split(" ")[2].toDouble();

         Vector point = Vector(x, y, z);
         vertices_.append(point);
      }
   }
}

void Mesh::render()
{
   foreach (Vector v, vertices_)
   {
      double intensity = (0.3 * v.z) + (0.3 * v.x) + 0.4;
      glColor3f(intensity, intensity, intensity);

      glVertex3f(v.x, v.y, v.z);
   }
}
