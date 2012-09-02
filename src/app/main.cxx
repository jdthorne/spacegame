
// Qt
#include <QApplication>
#include <QCoreApplication>
#include <QString>

// Space Game
#include <stdio.h>
#include <OpenGlCore.h>
#include <ExplosionDev.h>
#include <BattleDev.h>
#include <OfflineCore.h>
#include <SpacegameCore.h>
#include <ctime>

int main(int argc, char** argv)
{
   if (OfflineCore::isSimMode(argc, argv))
   {
      OfflineCore::runSimulation(new BattleDev());
   }
   else
   {
      SpacegameCore::runSpacegame(argc, argv);
   }
}

