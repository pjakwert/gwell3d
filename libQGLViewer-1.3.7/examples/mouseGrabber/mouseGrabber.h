#include <QGLViewer/qglviewer.h>

class CameraPathPlayer : public qglviewer::MouseGrabber
{
public:
  CameraPathPlayer(int nb) : pathNb(nb) {};  
  void checkIfGrabsMouse(int x, int y, const qglviewer::Camera* const camera);
  int yPos() { return 25*pathNb + 25; };
  
protected:
  void mousePressEvent(QMouseEvent* const, qglviewer::Camera* const camera) { camera->playKeyFramePath(pathNb); };

private:
  int pathNb;
};


class Viewer : public QGLViewer
{
protected :
  virtual void init();
  virtual void draw();
  virtual QString helpString() const;

  void displayPlayers();
  void updatePlayers();
  
private:
  CameraPathPlayer** player_;
};
