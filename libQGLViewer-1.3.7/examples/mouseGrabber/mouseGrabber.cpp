#include "mouseGrabber.h"

using namespace qglviewer;
using namespace std;

void CameraPathPlayer::checkIfGrabsMouse(int x, int y, const Camera* const)
{
  // Rectangular activation array - May have to be tune depending on your default font size
  setGrabsMouse((x < 80) && (y<yPos()) && ((yPos()-y) < 16));
}

void Viewer::displayPlayers()
{
  for (int i=0; i<camera()->nbPaths(); ++i)
    {
      CameraPathPlayer* cpp = player_[i];
      if (cpp)
	{
	  QString s;
	  if (cpp->grabsMouse())
	    {
	      glColor3f(1,1,1);
	      if (camera()->keyFrameInterpolator(i)->numberOfKeyFrames() > 1)
		s = "Play path F" + QString::number(i+1);
	      else
		s = "Restore pos F" + QString::number(i+1);
	    }
	  else
	    {
	      glColor3f(0.6, 0.6, 0.6);
	      if (camera()->keyFrameInterpolator(i)->numberOfKeyFrames() > 1)
		s = "Path F" + QString::number(i+1);
	      else
		s = "Pos F" + QString::number(i+1);
	    }
	  glDisable(GL_LIGHTING);
	  drawText(10, cpp->yPos()-3, s);
	}
    }
}


void Viewer::updatePlayers()
{
  for (int i=0; i<camera()->nbPaths(); ++i)
    {
      // Check if CameraPathPlayer is still valid
      if ((player_[i]) && (!camera()->keyFrameInterpolator(i)))
	{
	  delete player_[i];
	  player_[i] = NULL;
	}
      // Or add it if needed
      if ((camera()->keyFrameInterpolator(i)) && (!player_[i]))
	player_[i] = new CameraPathPlayer(i);
    }
}


void Viewer::init()
{  
  // Absolutely needed for MouseGrabber
  setMouseTracking(true);

  // In order to make the manipulatedFrame displacements clearer
  setDrawAxis();

  // Initialize the CameraPathPlayer MouseGrabber array
  player_ = new CameraPathPlayer*[camera()->nbPaths()];
  for (int i=0; i<camera()->nbPaths(); ++i)
    player_[i] = NULL;

  setManipulatedFrame(new ManipulatedFrame());
  
  restoreFromFile();

  help();
}


void Viewer::draw()
{
  glMultMatrixd(manipulatedFrame()->matrix());

  // Visual feedback for the manipulatedFrame grab.
  if (manipulatedFrame()->grabsMouse())
    drawAxis(0.9);
  else
    drawAxis(0.7);

  // Draw a spiral
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

  updatePlayers();
  displayPlayers();
}


QString Viewer::helpString() const
{
  QString text("<h2>M o u s e G r a b b e r </h2>");
  text += "This example illustrates the use of <i>MouseGrabber</i>, which is an abstract ";
  text += "class for objects that react (usually when the mouse hovers over them).<br><br>";
  text += "Define new camera paths (or positions) using <b>Alt</b>+[<b>F1</b>-<b>F12</b>]. ";
  text += "New <i>MouseGrabbers</i> are created and displayed in the left corner. ";
  text += "Note how they react to the mouse, and click them to play the associated path.<br><br>";
  text += "<i>ManipulatedFrame</i>, such as the one which defines the spiral position, are ";
  text += "also <i>MouseGrabbers</i>. When the mouse is close to the axis origin, the <i>ManipulatedFrame</i> ";
  text += "will react to mouse click, as if the <b>Control</b> key was pressed. This is very convenient ";
  text += "to intuitively move scene objects (such as lights) without any key or GUI interaction.<br><br>";
  text += "Note that <i>setMouseTracking()</i> must be enabled to enable <i>MouseGrabbers</i>.";
  return text;
}
