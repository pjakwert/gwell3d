#include "spinningFrame.h"
#include <math.h>

using namespace qglviewer;
using namespace std;

///////////////////////   E n g i n e   ///////////////////////////////

Engine::Engine()
{
  // Rotation around the Z axis. 0.04 radians increment.
  axisFrame_.setSpinningQuaternion(Quaternion(Vec(0,0,1), 0.04));

  // Same as axisFrame_, but with a rotationCenter
  conrodFrame_.setSpinningQuaternion(axisFrame_.spinningQuaternion());
  // Default rotation center is the world origin. Kept unchanged.
  conrodFrame_.setRotateAroundCenter();
  // The conrodFrame_ position is excentered to define the rotation radius.
  conrodFrame_.setPosition(Vec(0.4, 0.0, 0.0));

  // As the two spinningFrame are synchronized, there is not need to connect the two spinned()
  // signals to the updateGL() slot. We connect the axisFrame_ spinned signal only.
  QGLViewer::connectSignalToAllViewers(&axisFrame_, SIGNAL(spinned()));

  // Default update interval is 40 milliseconds.
  axisFrame_.startSpinning();
  conrodFrame_.startSpinning();
}

void Engine::draw()
{
  // axisFrame_
  glColor3f(.6, .4, .4);
  glPushMatrix(); 
  glMultMatrixd(axisFrame_.matrix());
  drawCylinder(-0.3, 0.1, 0.1, 0.1, 50);
  glRotatef(90, 0.0, 1.0, 0.0);
  drawCone(0, 0.4, 0.1, 0.05, 50);
  glPopMatrix();

  // conrodFrame_
  glColor3f(.4, .6, .4);
  glPushMatrix(); 
  glMultMatrixd(conrodFrame_.matrix());  
  drawCylinder(-0.1, 0.4, 0.05, 0.05, 50);
  drawCylinder(0.1, 0.3, 0.1, 0.1, 50);
  glPopMatrix();

  // Other parts
  glColor3f(.8, .8, .8);
  Vec p = conrodFrame_.position();
  const float L = 0.5;
  float angle = atan2(p.x, L);
  glTranslatef(0., 0.1 + p.y + L*cos(angle), .18);
  glRotatef(-90, 1.0, 0.0, 0.0);
  drawCylinder(0.0, 0.3, 0.15, 0.15, 50);

  glRotatef(180+180*angle/M_PI, 0.0,-1.0,0.0);
  drawCone(0.0, 1.1*L, 0.04, 0.04, 50);
}

// Draws a closed cylinder using drawCone()
void Engine::drawCylinder(const float zMin,const float zMax, const float r1, const float r2, const float nbSub)
{
  float cap = 0.05 * (zMax - zMin);
  drawCone(zMin-cap, zMin, 0.0, r1, nbSub);
  drawCone(zMin, zMax, r1, r2, nbSub);
  drawCone(zMax, zMax+cap, r2, 0.0, nbSub);
}

// Draws a truncated cone aligned with the Z axis.
void Engine::drawCone(const float zMin,const float zMax, const float r1, const float r2, const float nbSub)
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

///////////////////////   V i e w e r   ///////////////////////
void Viewer::init()
{
  restoreFromFile();
  camera()->lookAt(0.0, 0.5, 0.0);
  help();
}

void Viewer::draw()
{
  engine.draw();
}

QString Viewer::helpString() const
{
  QString text("<h2>S p i n n i n g F r a m e</h2>");
  text += "The main axis is animated using a <i>SpinningFrame</i> (red). ";
  text += "An other <i>SpinningFrame</i> is used for the conrod (green), ";
  text += "but a rotation center is defined, creating this circular motion. ";
  text += "<i>SpinningFrame</i> are convenient to animate rotating scene objects.";
  return text;
}
