#include <QGLViewer/qglviewer.h>

class Viewer : public QGLViewer
{
protected :
  virtual void init();
  virtual void draw();
  virtual QString helpString() const;

private :
  void drawSaucer() const;
  void drawCone(const float zMin,const float zMax, const float r1, const float r2) const;

#if QT_VERSION < 300
# define nbSaucers 10
#else
  static const int nbSaucers = 10;
#endif
  qglviewer::Frame saucerPos[nbSaucers];
  qglviewer::Vec saucerColor[nbSaucers];
};
