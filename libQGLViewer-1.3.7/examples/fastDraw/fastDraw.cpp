#include "fastDraw.h"

using namespace std;
using namespace qglviewer;

void Viewer::init()
{
  // Increase the material shininess, so that the difference between
  // the two versions of the spiral is more visible.
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0);
  GLfloat specular_color[4] = { 0.8, 0.8, 0.8, 1.0 };
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  specular_color);

  restoreFromFile();
  help();
}

static void drawSpiral(bool simplified = false)
{
  int nbSteps = 600;
  int nbSub = 50;
  if (simplified)
    {
      nbSteps = 60;
      nbSub = 2;
    }
  
  for (float n=0; n<nbSub; ++n)
    {
      glBegin(GL_QUAD_STRIP);
      for (float i=0.0; i<nbSteps; ++i)
	{
	  float ratio = i/nbSteps;
	  float angle = 21.0*ratio;
	  float radius = 1.0 - 0.5*ratio;
	  
	  Vec center(radius*cos(angle), ratio-0.5, radius*sin(angle));

	  for (unsigned short j=0; j<2; ++j)
	    {
	      float delta = 3.0*(n+j)/nbSub;
	      Vec shift(cos(angle)*cos(delta), sin(delta), sin(angle)*cos(delta));
	  
	      glColor3f(1-ratio, (n+j)/nbSub , ratio);
	      glNormal3fv(shift.address());
	      glVertex3fv((center+0.2*shift).address());
	    }
	}
      glEnd();
    }
}

void Viewer::draw()
{
  drawSpiral();
}

void Viewer::fastDraw()
{
  drawSpiral(true);
}

QString Viewer::helpString() const
{
  QString text("<h2>F a s t D r a w</h2>");
  text += "The <i>fastDraw()</i> function is called instead of <i>draw()</i> when the camera is manipulated, ";
  text += "thus allowing interactive displacements even with very complex scenes, as soon as you provide a fast drawing function.";
  return text;
}
