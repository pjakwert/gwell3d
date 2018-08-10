#include "select.h"
#include <math.h>

using namespace std;

static void drawSpiral(const bool specialColor = false)
{
  const float nbSteps = 100.0;
  glBegin(GL_QUAD_STRIP);
  for (float i=0; i<nbSteps; ++i)
    {
      if (specialColor)
	glColor3f((nbSteps-i)/nbSteps, .8 , i/nbSteps/2.0);
      else
	glColor3f((nbSteps-i)/nbSteps, .2 , i/nbSteps);
      float angle = i/4.0;
      float c = cos(angle);
      float s = sin(angle);
      float r1 = 0.5 - i/(3.f*nbSteps);
      float r2 = 0.3 - i/(3.f*nbSteps);
      float alt = i/nbSteps - 0.5;
      const float nor = .5;
      const float up = sqrt(1.0-nor*nor);
      glNormal3f(nor*c, nor*s, up);
      glVertex3f(r2*c, r2*s, alt+0.05);
      glVertex3f(r1*c, r1*s, alt);
    }
  glEnd();
}

void Viewer::drawWithNames()
{
  // Draw spirals, pushing a name (id) for each of them
  const int nb = 10;
  for (int i=0; i<nb; ++i)
    {
      glPushMatrix();      
      glTranslatef(cos(2.0*i*M_PI/nb), sin(2.0*i*M_PI/nb), 0.);

      glPushName(i);
      drawSpiral();
      glPopName();
      
      glPopMatrix();
    }
}

void Viewer::postSelection(int x, int y)
{
  // Compute orig and dir, used to draw a representation of the intersecting line
  camera()->convertClickToLine(x, y, orig, dir);

  // Find the selectedPoint coordinates, using camera()->pointUnderPixel().
  bool found;
  selectedPoint = camera()->pointUnderPixel(x, y, found);
  selectedPoint -= 0.01*dir; // Small offset to make point clearly visible.
  // Note that "found" is different from (selectedObjectId()>=0) because of the selectWindowSize().

  if (selectedName() == -1)
    qWarning("No object selected under pixel " + QString::number(x) + "," + QString::number(y));
  else
    qWarning("Spiral number " + QString::number(selectedName()) + " selected under pixel " + QString::number(x) + "," + QString::number(y));
}

void Viewer::init()
{
  restoreFromFile();

  glLineWidth(3.0);
  glPointSize(10.0);

  help();
}

void Viewer::draw()
{
  // Draw ten spirals
  const int nb = 10;
  for (int i=0; i<nb; ++i)
    {
      glPushMatrix();      
      glTranslatef(cos(2.0*i*M_PI/nb), sin(2.0*i*M_PI/nb), 0.0);
      drawSpiral(i == selectedName());
      glPopMatrix();
    }

  // Draw the intersection line
  glBegin(GL_LINES);
  glVertex3fv(orig.address());
  glVertex3fv((orig + 100.0*dir).address());
  glEnd();

  // Draw (approximated) intersection point on selected object
  if (selectedName() >= 0)
    {
      glColor3f(0.9, 0.2, 0.1);
      glBegin(GL_POINTS);
      glVertex3fv(selectedPoint.address());
      glEnd();
    }
}

QString Viewer::helpString() const
{
  QString text("<h2>S e l e c t</h2>");
  text += "Left click while pressing the <b>Shift</b> key to select an object of the scene.<br>";
  text += "You only have to define the <i>drawWithNames</i> function to add object selection in your viewer.<br>";
  text += "Selection is performed using the OpenGL <i>GL_SELECT</i> render mode.<br>";
  text += "A line is drawn between the selected point and the camera selection position. ";
  text += "using <i>convertClickToLine()</i>, a useful function for analytical intersections.<br>";
  text += "Feel free to cut and paste this implementation in your own applications.";
  return text;
}
