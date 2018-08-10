#include "screenCoordSystem.h"
#include <stdio.h>
#include <stdlib.h> // RAND_MAX

using namespace qglviewer;
using namespace std;

void Viewer::init()
{
  for (int i=0; i<nbSaucers; i++)
    {
      Vec pos;
      pos.x = rand() / static_cast<float>(RAND_MAX) - 0.5;
      pos.y = rand() / static_cast<float>(RAND_MAX) - 0.5;
      pos.z = rand() / static_cast<float>(RAND_MAX) - 0.5;

      Quaternion ori(Vec(static_cast<float>(rand()) / RAND_MAX,
			  static_cast<float>(rand()) / RAND_MAX,
			  static_cast<float>(rand()) / RAND_MAX),
		      rand() / static_cast<float>(RAND_MAX) * M_PI);
      
      saucerPos[i].setPosition(pos);
      saucerPos[i].setOrientation(ori);
      
      saucerColor[i].x = rand() / static_cast<float>(RAND_MAX);
      saucerColor[i].y = rand() / static_cast<float>(RAND_MAX);
      saucerColor[i].z = rand() / static_cast<float>(RAND_MAX);
    }

  restoreFromFile();
  help();
}

QString Viewer::helpString() const
{
  QString text("<h2>S c r e e n C o o r d S y s t e m</h2>");
  text += "This example illustrates the <i>startScreenCoordinatesSystem()</i> function ";
  text += "which enables a GL drawing directly into the screen coordinate system.<br>";
  text += "The arrows are drawned using this method. The screen projection coordinates ";
  text += "of the objects is determined using <i>camera()->projectedCoordinatesOf()</i>, ";
  text += "thus <i>attaching</i> the 2D arrow to a 3D object";
  return text;
}

void Viewer::drawCone(const float zMin,const float zMax, const float r1, const float r2) const
{
  static const float nbSub = 32;
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

void Viewer::drawSaucer() const
{
  drawCone(-0.014, -0.01, 0.015, 0.03);
  drawCone(-0.01, 0.0, 0.03, 0.04);
  drawCone(0.0, 0.02, 0.05, 0.03);
  drawCone(0.02, 0.023, 0.03, 0.0);
}

void Viewer::draw()
{
  // Draw 3D flying saucers
  // Qt 2.3 with VS 6.0 : declare "int i;" here, and remove "int" from the following "for"
  for (int i=0; i<nbSaucers; i++)
    {
      glPushMatrix();
      glMultMatrixd(saucerPos[i].matrix());
      glColor3fv(saucerColor[i].address());
      drawSaucer();
      glPopMatrix();
    }
  
  // Compute projected coordinates
  int projX[nbSaucers];
  int projY[nbSaucers];
  for (int i=0; i<nbSaucers; i++)
    {
      Vec projectedPos = camera()->projectedCoordinatesOf(saucerPos[i].position());
      projX[i] = (int)(projectedPos.x);
      projY[i] = (int)(projectedPos.y);
    }
  
  // Draw the arrows
  glColor3fv(foregroundColor().address());
  startScreenCoordinatesSystem();
  for (int i=0; i<nbSaucers; i++)
    {
      glBegin(GL_LINE_LOOP);
      glVertex2i(projX[i]-50, projY[i]);
      glVertex2i(projX[i]-20, projY[i]-4);
      glVertex2i(projX[i]-15, projY[i]);
      glVertex2i(projX[i]-20, projY[i]+4);
      glEnd();  
    }
  stopScreenCoordinatesSystem();

  // Draw text id
  for (int i=0; i<nbSaucers; i++)
    drawText(projX[i]-60, projY[i]+4, QString::number(i));
}


