
// Qt
#include <QApplication>
#include <QCoreApplication>
#include <QString>

// Space Game
#include <stdio.h>
#include <Vector.h>
#include <OpenGlCore.h>

bool isSimMode(int argc, char** argv)
{
   for (int i = 0; i < argc; i++)
   {
      if (QString(argv[i]) == "--sim")
      {
         return true;
      }
   }
   return false;
}

int main(int argc, char** argv)
{
   if (isSimMode(argc, argv))
   {
      qDebug("Simulating 500 frames...");
      World world;
      world.addShip();
      for (int frame = 0; frame < 500; frame++)
      {
         world.simulate();
      }
      qDebug("Done!");
      return 0;
   }

   QApplication app(argc, argv);

   OpenGlCore* core = new OpenGlCore();
   core->show();

   app.exec();
}

