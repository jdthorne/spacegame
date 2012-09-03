
// Qt
#include <QApplication>

// Spacegame
#include <SpacegameCore.h>
#include <MainWindow.h>
#include <ExplosionDev.h>
#include <BattleDev.h>

SpacegameCore::SpacegameCore()
{

}

SpacegameCore::~SpacegameCore()
{
}

void SpacegameCore::runSpacegame(int argc, char** argv)
{
   QApplication app(argc, argv);

   MainWindow* window = new MainWindow();
   window->loadSimulation(new BattleDev());
   window->resize(1280, 720);
   window->show();

   app.exec();
}

