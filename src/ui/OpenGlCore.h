
#ifndef OPENGLCORE_H
#define OPENGLCORE_H

// Qt
#include <QGLWidget>
#include <QTimer>
#include <QTime>

#include <World.h>
#include <RenderCore.h>

class Simulation;

class OpenGlCore : public QGLWidget
{
   Q_OBJECT

public:
   OpenGlCore();
   virtual ~OpenGlCore();

   void loadSimulation(Simulation* simulation);

public:
   virtual void initializeGL();
   virtual void resizeGL(int w, int h);
   virtual void paintGL();

protected:
   virtual void mouseMoveEvent(QMouseEvent* event);
   virtual void wheelEvent(QWheelEvent* event);
   virtual void mousePressEvent(QMouseEvent* event);
   virtual void mouseReleaseEvent(QMouseEvent* event);

private slots:
   void handleTimeout();

private:
   void calculateFramerate();

private:
   QTimer timer_;

   Vector cameraPosition_;
   Quaternion cameraOrientation_;

   Simulation* simulation_;
   RenderCore renderCore_;

   QTime time_;
   int frames_;

   bool mouseDown_;
   double xRotation_;
   double yRotation_;
   double distance_;
};

#endif
