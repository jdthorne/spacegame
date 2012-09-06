
// Qt
#include <QApplication>
#include <QCoreApplication>
#include <QString>

// Space Game
#include <stdio.h>
#include <OpenGlCore.h>
#include <Profile.h>
#include <ExplosionDev.h>
#include <EndlessBattle.h>
#include <OfflineCore.h>
#include <SpacegameCore.h>
#include <ctime>

int main(int argc, char** argv)
{
   if (OfflineCore::isSimMode(argc, argv))
   {
      OfflineCore::runSimulation(new EndlessBattle());
   }
   else
   {
      SpacegameCore::runSpacegame(argc, argv);
   }

   Profile::printTimingInformation();
}

