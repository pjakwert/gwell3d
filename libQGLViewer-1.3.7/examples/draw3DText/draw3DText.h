#include <QGLViewer/qglviewer.h>

class Viewer : public QGLViewer
{
protected :
  virtual void draw();
  virtual void init();
  virtual QString helpString() const;
  
private :
  qglviewer::Vec vertices[20];
  short indexes[12][5];
  qglviewer::Vec center[12];
  qglviewer::Vec normal[12];
};
