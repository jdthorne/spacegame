
#ifndef OPENGLCORE_H
#define OPENGLCORE_H

// Qt
#include <QGLWidget>
#include <QTimer>
#include <QTime>

// Spacegame
#include <Vector.h>
#include <Quaternion.h>

class Simulation;
class RenderCore;
class Camera;

class OpenGlCore : public QGLWidget
{
   Q_OBJECT

public:
   OpenGlCore(QWidget* parent);
   virtual ~OpenGlCore();

   void loadSimulation(Simulation* simulation);
   Camera& camera();

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

   Camera* camera_;

   Simulation* simulation_;
   RenderCore* renderCore_;

   QTime time_;
   int frames_;

   double xStart_;
   double yStart_;
   double distance_;
};

#endif
