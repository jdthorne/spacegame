
// Qt
#include <QApplication>
#include <QCoreApplication>
#include <QString>

// Space Game
#include <stdio.h>
#include <Vector.h>
#include <OpenGlCore.h>
#include <ctime>

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
      int frames = 5000.0;

      qDebug("Simulating %d frames...", frames);
      clock_t start = clock();

      World world;
      for (int frame = 0; frame < frames; frame++)
      {
         world.simulate();
      }

      clock_t end = clock();
      double seconds = (double)(end - start) / CLOCKS_PER_SEC;

      qDebug("Simulated at %.5ffps; %d ships remain", (frames / seconds), world.ships().count());
      return 0;
   }

   QApplication app(argc, argv);

   OpenGlCore* core = new OpenGlCore();
   core->resize(1280, 720);
   core->show();

   app.exec();
}

