#include "draw3DText.h"
#include <stdio.h>

using namespace qglviewer;
using namespace std;

void Viewer::init()
{
  const float c = cos(M_PI/3.0);
  const float s = sin(M_PI/3.0);

  vertices[0].setValue(c+2.0*s, s, 0.0);
  vertices[1].setValue(-c-2.0*s, s, 0.0);
  vertices[2].setValue(c+2.0*s, -s, 0.0);
  vertices[3].setValue(-c-2.0*s, -s, 0.0);
  vertices[4].setValue(0.0, 2.0*s+c,  s);
  vertices[5].setValue(0.0, -2.0*s-c,  s);
  vertices[6].setValue(0.0, 2.0*s+c, -s);
  vertices[7].setValue(0.0, -2.0*s-c, -s);
  vertices[8].setValue(-c-s,  -c-s, c+s);
  vertices[9].setValue(-c-s,  c+s,  c+s);
  vertices[10].setValue(-c-s, -c-s, -c-s);
  vertices[11].setValue(-c-s, c+s,  -c-s);
  vertices[12].setValue(c+s, -c-s, c+s);
  vertices[13].setValue(c+s, c+s,  c+s);
  vertices[14].setValue(c+s, -c-s, -c-s);
  vertices[15].setValue(c+s, c+s,  -c-s);
  vertices[16].setValue(-s, 0.0, -2.0*s-c);
  vertices[17].setValue(s, 0.0, -2.0*s-c);
  vertices[18].setValue(-s, 0.0, 2.0*s+c);
  vertices[19].setValue(s, 0.0, 2.0*s+c);

  static short array[12][5] = {
    { 0, 13, 19, 12, 2 },
    { 0, 2, 14, 17, 15 } ,
    { 0, 15, 6, 4, 13 } ,
    { 6, 15, 17, 16, 11 } ,
    { 4, 6, 11, 1, 9 } ,
    { 11, 16, 10, 3, 1 } ,
    { 16, 17, 14, 7, 10 } ,
    { 10, 7, 5, 8, 3 } ,
    { 5, 12, 19, 18, 8 } ,
    { 12, 5, 7, 14, 2 } ,
    { 18, 19, 13, 4, 9 } ,
    { 1, 3, 8, 18, 9 } };

  for (int i=0; i<12; ++i)
    {
      normal[i].setValue(0.0, 0.0, 0.0);
      for (int j=0; j<5; ++j)
	{
	  indexes[i][j] = array[i][j];
	  normal[i] += vertices[indexes[i][j]];
	}
      normal[i].normalize();

      // Center digits on faces
      Quaternion rot(Vec(0.0, 0.0, 1.0), normal[i]);
      if (i<9)
	center[i] = 1.92*normal[i] + rot.rotate(Vec(-0.4, -0.4, 0.0));
      else
	center[i] = 1.92*normal[i] + rot.rotate(Vec(-0.7, -0.4, 0.0));
    }

  restoreFromFile();

  glLineWidth(10.0);
  setSceneRadius(3.0);
  showEntireScene();
  
  help();
}

QString Viewer::helpString() const
{
  QString text("<h2>d r a w 3 D T e x t</h2>");
  text += "This example illustrates the <i>draw3DText()</i> function which " ;
  text += "draws a text in 3D space, with a given normal and position.<br><br>";
  text += "<i>draw3DText()</i> is no longer supported since libQGLViewer version 1.3.5. ";
  text += "Use GLUT to draw text using 3D lines.";
  return text;
}


void Viewer::draw()
{    
  glEnable(GL_LIGHTING);
  int i,j;
  for (i=0; i<12; ++i)
    {
      glColor3f(.8,.2,.8);
      glNormal3fv(normal[i].address());
      glBegin(GL_POLYGON);
      for (j=0; j<5; ++j)
	glVertex3fv(vertices[indexes[i][j]].address());
      glEnd();

      glColor3f(.5,.1,.5);
      glBegin(GL_LINE_LOOP);
      for (j=0; j<5; ++j)
	glVertex3fv((1.01*vertices[indexes[i][j]]).address());
      glEnd();
    }

  glDisable(GL_LIGHTING);
  glColor3f(0.9, 0.9, 0.9);
  for (i=0; i<12; ++i)
    draw3DText(center[i], normal[i], QString::number(i+1));
}
