
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QGLWidget>

#include <Mesh.h>

QMap<QString, Mesh*> MESH_LIST;

Mesh::Mesh(const QString name, const Color color)
   : name_(name)
   , color_(color)
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
      else
      {
         //qDebug("Error: %s.mesh: Encountered an unexpected number of verts: %d", qPrintable(name), face.vertices_.count());
         face = Face();
      }
   }
   qDebug("Loaded '%s' with %d faces", qPrintable(name), faces_.count());
}

Mesh& Mesh::byName(const QString name)
{
   if (MESH_LIST.count() == 0)
   {
      Color grey = { 0.2, 0.2, 0.2, 1.0 };
      Color orange = { 1.0, 0.75, 0.0, 1.0 };
      Color transparentBlue = { 0.25, 0.25, 1.0, 0.1 };

      MESH_LIST["computer"] = new Mesh("computer", grey);
      MESH_LIST["engine"] = new Mesh("engine", grey);
      MESH_LIST["gyro"] = new Mesh("gyro", grey);
      MESH_LIST["weapon"] = new Mesh("weapon", grey);

      MESH_LIST["engine-thrust"] = new Mesh("engine-thrust", orange);

      MESH_LIST["deflector"] = new Mesh("deflector", transparentBlue);
      MESH_LIST["explosion"] = new Mesh("deflector", orange);

      //Vector flame = Vector(0.2, 0.8, 1.0);
      //MESH_LIST["engine-thrust"] = new Mesh("engine-thrust", flame);
   }

   return *(MESH_LIST[name]);
}

double toDeg(double rad)
{
   return (rad * 180) / 3.1415926535;
}

void Mesh::render(const Vector position, const Quaternion rotation, double scale)
{
   glPushMatrix();
   glTranslatef(position.x, position.y, position.z);

   double angle = rotation.angle();
   if (angle > 0.000001)
   {
      Vector axis = rotation.axis();
      glRotatef(toDeg(angle), axis.x, axis.y, axis.z);
   }

   glScalef(scale, scale, scale);

   //GLfloat color[] = { color_.r, color_.g, color_.b, 0.01 };
   //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
   glColor4f(color_.r, color_.g, color_.b, color_.a);

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

void Mesh::renderLine(const Vector start, const Vector end, double alpha)
{
   glColor4f(0.25, 0.75, 1.0, alpha);
   glVertex3f(start.x, start.y, start.z);
   glVertex3f(end.x, end.y, end.z);
}
