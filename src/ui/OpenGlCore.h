
#ifndef OPENGLCORE_H
#define OPENGLCORE_H

// Qt
#include <QGLWidget>
#include <QTimer>
#include <QTime>

#include <World.h>
#include <RenderCore.h>

class OpenGlCore : public QGLWidget
{
   Q_OBJECT

public:
   OpenGlCore();
   virtual ~OpenGlCore();

public:
   virtual void initializeGL();
   virtual void resizeGL(int w, int h);
   virtual void paintGL();

protected:
   virtual void mouseMoveEvent(QMouseEvent* event);

private slots:
   void handleTimeout();

private:
   void calculateFramerate();

private:
   QTimer timer_;

   World world_;
   RenderCore renderCore_;

   QTime time_;
   int frames_;

   double xRotation_;
   double yRotation_;
};

#endif
