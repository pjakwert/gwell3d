#include "constrainedCamera.h"

using namespace qglviewer;
using namespace std;

static AxisPlaneConstraint::Type nextTranslationConstraintType(const AxisPlaneConstraint::Type& type)
{
  switch (type)
    {
    case AxisPlaneConstraint::FREE  : return AxisPlaneConstraint::PLANE; break;
    case AxisPlaneConstraint::PLANE : return AxisPlaneConstraint::AXIS;  break;
    case AxisPlaneConstraint::AXIS  : return AxisPlaneConstraint::FORBIDDEN;  break;
    case AxisPlaneConstraint::FORBIDDEN   : return AxisPlaneConstraint::FREE; break;
    default : return AxisPlaneConstraint::FREE;
    }
}

static AxisPlaneConstraint::Type nextRotationConstraintType(const AxisPlaneConstraint::Type& type)
{
  switch (type)
    {
    case AxisPlaneConstraint::FREE  : return AxisPlaneConstraint::AXIS; break;
    case AxisPlaneConstraint::PLANE : return AxisPlaneConstraint::FREE; break;
    case AxisPlaneConstraint::AXIS  : return AxisPlaneConstraint::FORBIDDEN;  break;
    case AxisPlaneConstraint::FORBIDDEN   : return AxisPlaneConstraint::FREE; break;
    default : return AxisPlaneConstraint::FREE;
    }
}

void Viewer::changeConstraint()
{
  unsigned short previous = activeConstraint;
  activeConstraint = (activeConstraint+1)%2;

  constraints[activeConstraint]->setTranslationConstraintType(constraints[previous]->translationConstraintType());
  constraints[activeConstraint]->setTranslationConstraintDir (constraints[previous]->translationConstraintDir());
  constraints[activeConstraint]->setRotationConstraintType   (constraints[previous]->rotationConstraintType());
  constraints[activeConstraint]->setRotationConstraintDir    (constraints[previous]->rotationConstraintDir());

  camera()->frame()->setConstraint(constraints[activeConstraint]);
}

void Viewer::init()
{
  restoreFromFile();

  constraints[0] = new WorldConstraint();

  // Note that a CameraConstraint(camera) would produce the same results:
  // A CameraConstraint is a LocalConstraint when applied to the camera frame ! 
  constraints[1] = new LocalConstraint();

  transDir = 0;
  rotDir   = 0;
  activeConstraint = 0;

  camera()->frame()->setConstraint(constraints[activeConstraint]);

  setDrawAxis();

  help();
}

void Viewer::draw()
{
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
  
  displayText();
}

void Viewer::keyPressEvent(QKeyEvent *e)
{
  switch (e->key())
    {
    case Qt::Key_G : transDir = (transDir+1)%3; break;
    case Qt::Key_D : rotDir   = (rotDir+1)%3;   break;      
    case Qt::Key_Space: changeConstraint();     break;
    case Qt::Key_T :
      constraints[activeConstraint]->setTranslationConstraintType(nextTranslationConstraintType(constraints[activeConstraint]->translationConstraintType()));
      break;
    case Qt::Key_R :
      constraints[activeConstraint]->setRotationConstraintType(nextRotationConstraintType(constraints[activeConstraint]->rotationConstraintType()));
      break;
    default:
      QGLViewer::keyPressEvent(e);
    }

  Vec dir(0.0,0.0,0.0);
  dir[transDir] = 1.0;
  constraints[activeConstraint]->setTranslationConstraintDir(dir);

  dir = Vec(0.0,0.0,0.0);
  dir[rotDir] = 1.0;
  constraints[activeConstraint]->setRotationConstraintDir(dir);

  updateGL();
}

void Viewer::displayType(const AxisPlaneConstraint::Type type, const int x, const int y, const char c)
{
  char text[12];
  switch (type)
    {
    case AxisPlaneConstraint::FREE:  sprintf(text, "FREE (%c)", c);  break;
    case AxisPlaneConstraint::PLANE: sprintf(text, "PLANE (%c)", c); break;
    case AxisPlaneConstraint::AXIS:  sprintf(text, "AXIS (%c)", c);  break;
    case AxisPlaneConstraint::FORBIDDEN:   sprintf(text, "FORBIDDEN (%c)", c);   break;            
    }
  drawText(x, y, text);
}

void Viewer::displayDir(const unsigned short dir, const int x, const int y, const char c)
{
  char text[6];
  switch (dir)
    {
    case 0:  sprintf(text, "X (%c)", c);  break;
    case 1:  sprintf(text, "Y (%c)", c);  break;
    case 2:  sprintf(text, "Z (%c)", c);  break;
    }
  drawText(x, y, text);
}

void Viewer::displayText()
{
  glColor3fv(foregroundColor().address());
  glDisable(GL_LIGHTING);
  drawText(10,height()-30, "TRANSLATION :");
  displayDir(transDir, 190, height()-30, 'G');
  displayType(constraints[activeConstraint]->translationConstraintType(), 10, height()-60, 'T');
  
  drawText(width()-220,height()-30, "ROTATION");
  displayDir(rotDir, width()-100, height()-30, 'D');
  displayType(constraints[activeConstraint]->rotationConstraintType(), width()-220, height()-60, 'R');

  switch (activeConstraint)
    {
    case 0 : drawText(20,20, "Constraint direction defined w/r to WORLD (SPACE)"); break;
    case 1 : drawText(20,20, "Constraint direction defined w/r to CAMERA (SPACE)"); break;
    }
}

QString Viewer::helpString() const
{
  QString text("<h2>C o n s t r a i n e d C a m e r a</h2>");
  text += "The camera frame can be constrained to limit the camera displacements.<br>";
  text += "Try the different translation (press <b>G</b> and <b>T</b>) and rotation ";
  text += "(<b>D</b> and <b>R</b>) constraints while moving the frame with the mouse. ";
  text += "The constraints can be defined with respect to various coordinates ";
  text += "systems : press <b>Space</b> to switch.<br>";
  text += "You can easily define your own constraints to create a specific camera constraint.";
  return text;
}

