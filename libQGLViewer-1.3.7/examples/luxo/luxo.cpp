#include "luxo.h"
#include <math.h>

using namespace qglviewer;
using namespace std;

//////////////////////////////////  V i e w e r  ////////////////////////////////////////

QString Viewer::helpString() const
{
  QString text("<h2>L u x o  �</h2>");
  text += "This example illustrates several functionnalities of QGLViewer, ";
  text += "showing how easy it is to create a moderately complex application.<br>";
  text += "The famous luxo� lamp (�Pixar) can interactively be manipulated ";
  text += "with the mouse. <b>Shift</b> left click on an a part of the lamp to select it, ";
  text += "and then move it with the mouse. Select the background to move the camera, or ";
  text += "press the <b>Control</b> key (the default shortcut modifier keys have been swapped).<br>";
  text += "A simpler object selection example is given in <i>select</i>. ";
  text += "A simpler frame displacement example is given in <i>manipulatedFrame</i>. ";
  text += "A simpler constrained frame example is given in <i>constrainedFrame</i>.<br>";
  text += "Feel free to use this code as the starting point of a multiple frame manipulation application.";
  return text;
}

void Viewer::initSpotLight()
{
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_LIGHT1);
  glLoadIdentity();

  // Light default parameters
  GLfloat spot_dir[3]       = {0.0, 0.0, 1.0};
  GLfloat light_ambient[4]  = {0.5, 0.5, 0.5, 1.0};
  GLfloat light_specular[4] = {1.0, 1.0, 1.0, 1.0};
  GLfloat light_diffuse[4]  = {3.0, 3.0, 1.0, 1.0};
  
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_dir);
  glLightf( GL_LIGHT1, GL_SPOT_EXPONENT,  3.0);
  glLightf( GL_LIGHT1, GL_SPOT_CUTOFF,    50.0);
  glLightf( GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.5);
  glLightf( GL_LIGHT1, GL_LINEAR_ATTENUATION, 1.0);
  glLightf( GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 1.5);
  glLightfv(GL_LIGHT1, GL_AMBIENT,  light_ambient);
  glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse);
}

void Viewer::init()
{
  restoreFromFile();

  // Make camera the default manipulated frame.
  setManipulatedFrame( camera()->frame() );

  // Preserve CAMERA bindings, see setMouseStateKey documentation.
  setMouseStateKey(QGLViewer::CAMERA, Qt::AltButton);
  // The frames can be move without any key pressed
  setMouseStateKey(QGLViewer::FRAME, Qt::NoButton);
  // The camera can always be moved with the Control key.
  setMouseStateKey(QGLViewer::CAMERA, Qt::ControlButton);

  initSpotLight();

  help();
}

void Viewer::draw()
{
  // Draw the ground
  glColor3f(.4,.4,.4);
  const float nbPatches = 100;
  glNormal3f(0.0,0.0,1.0);
  for (int j=0; j<nbPatches; ++j)
    {
      glBegin(GL_QUAD_STRIP);
      for (int i=0; i<=nbPatches; ++i)
	{
	  glVertex2f((2*i/nbPatches-1.0), (2*j/nbPatches-1.0));
	  glVertex2f((2*i/nbPatches-1.0), (2*(j+1)/nbPatches-1.0));
	}
      glEnd();
    }

  luxo.draw();
}

void Viewer::drawWithNames()
{
  // Render scene with objects ids
  luxo.draw(true);
}

void Viewer::postSelection(int, int)
{
  if (selectedName() == -1)
    {
      // Camera will be the default frame is no object is selected.
      setManipulatedFrame( camera()->frame() );
      luxo.setSelectedFrameNumber(4); // dummy value
    }
  else
    {
      setManipulatedFrame(luxo.frame(selectedName()));
      luxo.setSelectedFrameNumber(selectedName());
    }
}

//////////////////////////////////  L u x o ////////////////////////////////////////

Luxo::Luxo()
{
  for (unsigned short i=0; i<4; ++i)
    {
      frame_[i] = new ManipulatedFrame();
  
      // Creates a hierarchy of frames.
      if (i>0)
	frame(i)->setReferenceFrame(frame(i-1));
    }

  // Initialize frames
  frame(1)->setTranslation(Vec(0.0, 0.0, 0.08)); // Base height
  frame(2)->setTranslation(Vec(0.0, 0.0, 0.5));  // Arm length
  frame(3)->setTranslation(Vec(0.0, 0.0, 0.5));  // Arm length

  frame(1)->setRotation(Quaternion(Vec(1.0,0.0,0.0), 0.6));
  frame(2)->setRotation(Quaternion(Vec(1.0,0.0,0.0), -2.0));
  frame(3)->setRotation(Quaternion(Vec(1.0,-0.3,0.0), -1.7));

  // Set frame constraints
  WorldConstraint* baseConstraint = new WorldConstraint();
  baseConstraint->setTranslationConstraint(AxisPlaneConstraint::PLANE, Vec(0.0,0.0,1.0));
  baseConstraint->setRotationConstraint(AxisPlaneConstraint::AXIS, Vec(0.0,0.0,1.0));
  frame(0)->setConstraint(baseConstraint);

  LocalConstraint* XAxis = new LocalConstraint();
  XAxis->setTranslationConstraint(AxisPlaneConstraint::FORBIDDEN,  Vec(0.0,0.0,0.0));
  XAxis->setRotationConstraint   (AxisPlaneConstraint::AXIS, Vec(1.0,0.0,0.0));
  frame(1)->setConstraint(XAxis);
  frame(2)->setConstraint(XAxis);

  LocalConstraint* headConstraint = new LocalConstraint();
  headConstraint->setTranslationConstraint(AxisPlaneConstraint::FORBIDDEN, Vec(0.0,0.0,0.0));
  frame(3)->setConstraint(headConstraint);

  // Means camera is selected.
  selected = 4;
}

void Luxo::draw(const bool names)
{
  // Luxo's local frame
  glMultMatrixd(frame(0)->matrix());
    
  if (names) glPushName(0);
  setColor(0);
  drawBase();
  if (names) glPopName();
  
  if (names) glPushName(1);
  glMultMatrixd(frame(1)->matrix());
  setColor(1);
  drawCylinder();
  drawArm();
  if (names) glPopName();

  if (names) glPushName(2);
  glMultMatrixd(frame(2)->matrix());
  setColor(2);
  drawCylinder();
  drawArm();
  if (names) glPopName();

  if (names) glPushName(3);
  glMultMatrixd(frame(3)->matrix());
  setColor(3);
  drawHead();
  if (names) glPopName();

  // Add light
  const GLfloat pos[4] = {0.0,0.0,0.0,1.0};
  glLightfv(GL_LIGHT1, GL_POSITION, pos);
  GLfloat spot_dir[3]  = {0.0, 0.0, 1.0};
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_dir);
}

void Luxo::drawBase()
{
  drawCone(0.0,0.03, 0.15, 0.15, 30);
  drawCone(0.03,0.05, 0.15, 0.13, 30);
  drawCone(0.05,0.07, 0.13, 0.01, 30);
  drawCone(0.07,0.09, 0.01, 0.01, 10);
}

void Luxo::drawArm()
{
  glTranslatef(0.02, 0.0, 0.0);
  drawCone(0.0,0.5, 0.01, 0.01, 10);
  glTranslatef(-0.04, 0.0, 0.0);
  drawCone(0.0,0.5, 0.01, 0.01, 10);
  glTranslatef(0.02, 0.0, 0.0);
}

void Luxo::drawHead()
{
  drawCone(-0.02,0.06, 0.04, 0.04, 30);
  drawCone(0.06,0.15, 0.04, 0.17, 30);
  drawCone(0.15,0.17, 0.17, 0.17, 30);
}

void Luxo::drawCylinder()
{
  glPushMatrix();
  glRotatef(90, 0.0,1.0,0.0);
  drawCone(-0.05,0.05, 0.02, 0.02, 20);
  glPopMatrix();
}

void Luxo::setColor(const unsigned short nb)
{
  if (nb == selected)
    glColor3f(0.9, 0.9, 0.0);
  else
    glColor3f(0.9, 0.9, 0.9);
}

// Draws a truncated cone aligned with the Z axis.
void Luxo::drawCone(const float zMin,const float zMax, const float r1, const float r2, const float nbSub)
{
  float angle,c,s;
  Vec normal, p1, p2;
  glBegin(GL_QUAD_STRIP);
  for (unsigned short i=0; i<=nbSub; ++i)
    {
      angle = 2.0 * M_PI * i / nbSub;
      c = cos(angle);
      s = sin(angle);

      p1 = Vec(r1*c, r1*s, zMin);
      p2 = Vec(r2*c, r2*s, zMax);
      
      normal = cross(Vec(-s,c,0.0) , (p2-p1));
      normal.normalize();
      
      glNormal3fv(normal.address());
      glVertex3fv(p1.address());
      glVertex3fv(p2.address());
    }
  glEnd();
}

