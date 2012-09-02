
// Qt

// Spacegame
#include <OfflineCore.h>
#include <World.h>
#include <Simulation.h>

OfflineCore::OfflineCore()
{

}

OfflineCore::~OfflineCore()
{
}

bool OfflineCore::isSimMode(int argc, char** argv)
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

void OfflineCore::runSimulation(Simulation* simulation)
{
   int frames = 50000.0;

   qDebug("Simulating %d frames...", frames);
   clock_t start = clock();

   clock_t delta = clock();
   for (int frame = 0; frame < frames; frame++)
   {
      simulation->simulate();

      if (frame % 240 == 0)
      {
         double timePassed = (double)(clock() - delta) / CLOCKS_PER_SEC;

         qDebug(" => Running at %.5ffps (%d objects)", (240 / timePassed), simulation->world().items().count());
         delta = clock();
      }
   }

   clock_t end = clock();
   double seconds = (double)(end - start) / CLOCKS_PER_SEC;

   qDebug("Simulated at %.5ffps; %d ships remain", (frames / seconds), simulation->world().ships().count());
}