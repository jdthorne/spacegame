
// Qt
#include <QApplication>
#include <QString>

// Space Game
#include <stdio.h>
#include <Vector.h>
#include <OpenGlCore.h>

int main(int argc, char** argv)
{
   QApplication app(argc, argv);

   OpenGlCore core;
   core.show();

   return app.exec();
}

