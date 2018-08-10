#include <QGLViewer/qglviewer.h>

class Luxo
{
public :
  Luxo();

  void draw(const bool names=false);

  qglviewer::ManipulatedFrame* frame(const unsigned short i) { return frame_[i]; }
  void setSelectedFrameNumber(const unsigned short nb) { selected = nb; }
  
private :
  // The four articulations of the lamp
  qglviewer::ManipulatedFrame* frame_[4];
  // Used to draw the selected element in a different color
  unsigned short selected;

  void drawCone(const float zMin,const float zMax, const float r1, const float r2, const float nbSub);
  void drawBase();
  void drawArm();
  void drawCylinder();
  void setColor(const unsigned short nb);
  void drawHead();
};


class Viewer : public QGLViewer
{
protected :
  virtual void draw();
  virtual void init();
  virtual void drawWithNames();
  virtual void postSelection(int x, int y);
  virtual QString helpString() const;

  void initSpotLight();

private :
  Luxo luxo;
};

