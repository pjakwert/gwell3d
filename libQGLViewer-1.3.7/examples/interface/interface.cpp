#include "interface.h"
#include <math.h>

// Constructor must call the base class constructor.
Viewer::Viewer(QWidget *parent,const char *name)
  : QGLViewer(parent, name)
{
  restoreFromFile();
  help();
}

void Viewer::draw()
{
  // Draws a spiral
  const float nbSteps = 500.0;
  glBegin(GL_QUAD_STRIP);
  for (float i=0; i<nbSteps; ++i)
    {
      float ratio = i/nbSteps;
      float angle = 21.0*ratio;
      float c = cos(angle);
      float s = sin(angle);
      float r1 = 1.0 - 0.8*ratio;
      float r2 = 0.8 - 0.8*ratio;
      float alt = ratio - 0.5;
      const float nor = .5;
      const float up = sqrt(1.0-nor*nor);
      glColor3f(1-ratio, .2 , ratio);
      glNormal3f(nor*c, up, nor*s);
      glVertex3f(r1*c, alt, r1*s);
      glVertex3f(r2*c, alt+0.05, r2*s);
    }
  glEnd();
}

void Viewer::init()
{
  restoreFromFile();
}

QString Viewer::helpString() const
{
  QString text("<h2>I n t e r f a c e</h2>");
  text += "A GUI can be added to a QGLViewer widget using Qt's <i>designer</i>. ";
  text += "All the available QGLViewer signals and slots are listed in a <b>qglviewer.cw</b> file, ";
  text += "located in the QGLViewer <i>include</i> directory.";
  return text;
}
