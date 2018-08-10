#include "drawLight.h"
#include <math.h>

using namespace std;

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

  drawLight(GL_LIGHT0);

  const GLfloat pos1[4]		  = {0.5,0.5,0.0,1.0};
  const GLfloat spot_dir1[3]  	  = {-1.0, -1.0, 0.0};
  glLightfv(GL_LIGHT1, GL_POSITION, pos1);
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_dir1);
  drawLight(GL_LIGHT1, 2.0); // Draw this light twice bigger

  const GLfloat pos2[4]		  = {-0.5,0.5,0.0,1.0};
  const GLfloat spot_dir2[3]  	  = {1.0, 1.0, 1.0};
  glLightfv(GL_LIGHT2, GL_POSITION, pos2);
  glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_dir2);
  drawLight(GL_LIGHT2);
}

void Viewer::init()
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Light0 is the default ambient light
  glEnable(GL_LIGHT0);

  // Light1 is a spot light
  glEnable(GL_LIGHT1);
  const GLfloat light_ambient[4]  = {0.5, 0.5, 0.5, 1.0};
  const GLfloat light_specular[4] = {1.0, 1.0, 1.0, 1.0};
  const GLfloat light_diffuse[4]  = {3.0, 3.0, 1.0, 1.0};

  glLightf( GL_LIGHT1, GL_SPOT_EXPONENT,  3.0);
  glLightf( GL_LIGHT1, GL_SPOT_CUTOFF,    50.0);
  glLightf( GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.5);
  glLightf( GL_LIGHT1, GL_LINEAR_ATTENUATION, 1.0);
  glLightf( GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 1.5);
  glLightfv(GL_LIGHT1, GL_AMBIENT,  light_ambient);
  glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse);

  // Light2 is a classical directionnal light
  glEnable(GL_LIGHT2);
  const GLfloat light_ambient2[4]  = {0.5, 0.5, 0.5, 1.0};
  const GLfloat light_specular2[4] = {1.0, 0.0, 0.0, 1.0};
  const GLfloat light_diffuse2[4]  = {0.0, 3.0, 0.0, 1.0};

  glLightfv(GL_LIGHT2, GL_AMBIENT,  light_ambient2);
  glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular2);
  glLightfv(GL_LIGHT2, GL_DIFFUSE,  light_diffuse2);

  restoreFromFile();
  help();
}

QString Viewer::helpString() const
{
  QString text("<h2>D r a w L i g h t</h2>");
  text += "The <i>drawLight()</i> function displays a representation of the OpenGL lights ";
  text += "of your scene. This is convenient for debugging your light setup.";
  return text;
}
