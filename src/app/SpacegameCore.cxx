
// Qt
#include <QApplication>

// Spacegame
#include <SpacegameCore.h>
#include <OpenGlCore.h>
#include <ExplosionDev.h>

SpacegameCore::SpacegameCore()
{

}

SpacegameCore::~SpacegameCore()
{
}

void SpacegameCore::runSpacegame(int argc, char** argv)
{
   QApplication app(argc, argv);

   OpenGlCore* core = new OpenGlCore();
   core->loadSimulation(new ExplosionDev());
   core->resize(1280, 720);
   core->show();

   app.exec();
}

