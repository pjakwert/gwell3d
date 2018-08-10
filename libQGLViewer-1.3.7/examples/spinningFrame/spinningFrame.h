#include <QGLViewer/qglviewer.h>

class Engine
{
public :
  Engine();
  void draw();
  
protected :
  // The axis spinning frame of the conrod
  qglviewer::SpinningFrame axisFrame_;
  qglviewer::SpinningFrame conrodFrame_;
  
private:
  void drawCone(const float zMin,const float zMax, const float r1, const float r2, const float nbSub);
  void drawCylinder(const float zMin,const float zMax, const float r1, const float r2, const float nbSub);
};


class Viewer : public QGLViewer
{
protected :
  virtual void draw();
  virtual void init();  
  virtual QString helpString() const;

private :
  Engine engine;
};
