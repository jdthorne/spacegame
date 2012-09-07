#ifndef MAINWINDOW
#define MAINWINDOW

// Qt
#include <QString>
#include <QMainWindow>

// Spacegame
#include <OpenGlCore.h>
#include <CameraSidebar.h>

/**
 ******************************************************************************
 *
 * \brief            MainWindow
 *
 ******************************************************************************
 */
class MainWindow : public QMainWindow
{

public:
   MainWindow();
   ~MainWindow();

public:
   void loadSimulation(Simulation* simulation);

private: // helpers

private: // members
   QWidget* widget_;
   OpenGlCore* core_;

   QLayout* rightSidebarLayout_;
   QWidget* rightSidebar_;
};

#endif
