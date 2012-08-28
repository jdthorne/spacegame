
#ifndef OPENGLCORE_H
#define OPENGLCORE_H

// Qt
#include <QGLWidget>
#include <QTimer>
#include <QTime>

#include <Ship.h>

class OpenGlCore : public QGLWidget
{
   Q_OBJECT

public:
   OpenGlCore();

public:
   virtual void initializeGL();
   virtual void resizeGL(int w, int h);
   virtual void paintGL();

private slots:
   void handleTimeout();

private:
   QTimer timer_;

   Ship testShip_;

   QTime time_;
   int frames_;
};

#endif
