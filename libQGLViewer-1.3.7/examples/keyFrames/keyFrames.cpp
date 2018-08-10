#include "keyFrames.h"

using namespace qglviewer;
using namespace std;

Viewer::Viewer()
  : nbKeyFrames(4)
{
  restoreFromFile();

  // myFrame is the Frame that will be interpolated.
  Frame* myFrame = new Frame();

  // Set myFrame as the KeyFrameInterpolator interpolated Frame.
  kfi_.setFrame(myFrame);
  kfi_.setLoopInterpolation();

  // An array of manipulated (key) frames.
  keyFrame_ = new ManipulatedFrame*[nbKeyFrames];
  
  // Create an initial path
  for (int i=0; i<nbKeyFrames; i++)
    {
      keyFrame_[i] = new ManipulatedFrame();
      keyFrame_[i]->setPosition(-1.0 + 2.0*i/(nbKeyFrames-1), 0.0, 0.0);
      kfi_.addKeyFrame(keyFrame_[i]);
    }

  connect(&kfi_, SIGNAL(interpolated()), SLOT(updateGL()));

  kfi_.startInterpolation();

  currentKF_ = 0;
  setManipulatedFrame(keyFrame_[currentKF_]);

  // Save CAMERA binding. See setMouseStateKey() documentation.
  setMouseStateKey(QGLViewer::CAMERA, Qt::AltButton);
  setMouseStateKey(QGLViewer::FRAME,  Qt::NoButton);
  setMouseStateKey(QGLViewer::CAMERA, Qt::ControlButton);

  // Enable direct frame manipulation when the mouse hovers.
  setMouseTracking(true);
    
  help();
}

QString Viewer::helpString() const
{
  QString text("<h2>K e y F r a m e s</h2>");
  text += "A frame is animated using a <i>KeyFrameInterpolator</i>.<br>";
  text += "Use the left and right arrows to change the manipulated frame.<br>";
  text += "<b>+/-</b> changes the interpolation speed.<br>";
  text += "<b>Return</b> starts-stops the interpolation.<br>";
  text += "Press <b>Control</b> to move the camera.";
  return text;
}

void Viewer::keyPressEvent(QKeyEvent *e)
{
  switch (e->key())
    {
    case Qt::Key_Left :
      currentKF_ = (currentKF_+nbKeyFrames-1) % nbKeyFrames;
      setManipulatedFrame(keyFrame_[currentKF_]);
      updateGL();
      break;
    case Qt::Key_Right :
      currentKF_ = (currentKF_+1) % nbKeyFrames;
      setManipulatedFrame(keyFrame_[currentKF_]);
      updateGL();
      break;
    case Qt::Key_Return :
      if (e->state() != shortcutStateKey(FULL_SCREEN))
	kfi_.toggleInterpolation();
      else
	QGLViewer::keyPressEvent(e);
      break;
    case Qt::Key_Plus :
      kfi_.setInterpolationSpeed(kfi_.interpolationSpeed()+0.25);
      break;
    case Qt::Key_Minus :
      kfi_.setInterpolationSpeed(kfi_.interpolationSpeed()-0.25);
      break;
    // case Qt::Key_C :
      // kfi_.setClosedPath(!kfi_.closedPath());
      // break;
    default:
      QGLViewer::keyPressEvent(e);
    }
}

void Viewer::draw()
{
  glPushMatrix();
  glMultMatrixd(kfi_.frame()->matrix());
  drawAxis(0.3);
  glPopMatrix();

  kfi_.drawPath(5, 30);

  for (int i=0; i<nbKeyFrames; ++i)
    {
      glPushMatrix();
      glMultMatrixd(kfi_.keyFrame(i).matrix());
      if ((i == currentKF_) || (keyFrame_[i]->grabsMouse()))
	drawAxis(0.4);
      else
	drawAxis(0.2);
      glPopMatrix();
    }
}
