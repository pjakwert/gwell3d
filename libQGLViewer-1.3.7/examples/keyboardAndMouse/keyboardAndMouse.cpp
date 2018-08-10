#include "keyboardAndMouse.h"
#include <qpopupmenu.h>
#include <qcursor.h>
#include <qmap.h>
#include <math.h>

using namespace std;

// Draws a spiral
void Viewer::draw()
{
  const float nbSteps = 80.0;

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
      glColor3f(fabs(c), 0.2, fabs(s));
      glNormal3f(nor*c, up, nor*s);
      glVertex3f(r1*c, alt, r1*s);
      glVertex3f(r2*c, alt+0.05, r2*s);
    }
  glEnd();
}

void Viewer::init()
{
  // Restore previous viewer state.
  restoreFromFile();

  
  /////////////////////////////////////////////////////
  //       Keyboard shortcut customization           //
  //      Changes standard action key bindings       //
  /////////////////////////////////////////////////////

  // Define 'CTRL+Q' as the new exit shortcut (default was 'Escape')
  setShortcutKey(QGLViewer::EXIT, Qt::Key_Q, Qt::ControlButton);

  // Set 'Control' as the FPS toggle state key (default was 'F' and becomes 'CTRL+F')
  setShortcutStateKey(QGLViewer::DISPLAY_FPS, Qt::ControlButton);

  // Disable Z-Buffer toggle shortcut (default was 'Z')
  setShortcutKey(QGLViewer::DISPLAY_Z_BUFFER, 0);


  
  /////////////////////////////////////////////////////
  //         Mouse bindings customization            //
  //     Changes standard action mouse bindings      //
  /////////////////////////////////////////////////////

  // Left and right buttons together make a camera zoom : emulates a mouse third button if needed.
  setMouseBinding(Qt::LeftButton | Qt::RightButton, CAMERA, ZOOM);

  // Alt+left button translates the camera (since right button will popup a menu).
  setMouseBinding(Qt::AltButton | Qt::LeftButton, CAMERA, TRANSLATE);

  // Disable previous TRANSLATE mouse binding (and remove it from help mouse tab).
  setMouseBinding(Qt::RightButton, NO_CLICK_ACTION);

  // Define Control+Shift+Right button as selection shortcut
  setMouseBinding(Qt::ControlButton | Qt::ShiftButton | Qt::RightButton, SELECT);

  // Alt + mouse wheel MOVE_FORWARD the camera.
  setWheelBinding(Qt::AltButton, CAMERA, MOVE_FORWARD);

  // Display the help window. The help window tabs are automatically updated when you define new
  // standard key or mouse bindings (as is done above). Use shortcutBindingsString() and
  // mouseBindingsString() to add the description of your own new actions.
  help();
}


///////////////////////////////////////////////
//      Define new key bindings : F & W      //
///////////////////////////////////////////////

void Viewer::keyPressEvent(QKeyEvent *e)
{  
  // Get event state key
  const Qt::ButtonState state = (Qt::ButtonState)(e->state() & Qt::KeyButtonMask);
  // Bug in Qt : use 0x0f00 instead of Qt::KeyButtonMask with Qt versions < 3.1

  // A simple switch on e->key() is not sufficient if we want to take state key into account.
  // With a switch, it would have been impossible to separate 'F' from 'CTRL+F'.
  // That's why we use imbricated if...else and a "handled" boolean.
  bool handled = false;
  if ((e->key()==Qt::Key_W) && (state==Qt::NoButton))
    {
      wireframe_ = !wireframe_;
      if (wireframe_)
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      else
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      handled = true;
      updateGL();
    }
  else
    if ((e->key()==Qt::Key_F) && (state==Qt::NoButton))
      {
	flatShading_ = !flatShading_;
	if (flatShading_)
	  glShadeModel(GL_FLAT);
	else
	  glShadeModel(GL_SMOOTH);
	handled = true;
	updateGL();
      }
  // and so on with other else if.

  if (!handled)
    QGLViewer::keyPressEvent(e);
}


///////////////////////////////////////////////////////////
//             Define new mouse bindings                 //
//   A camera viewpoint menu binded on right button      //
///////////////////////////////////////////////////////////

void Viewer::mousePressEvent(QMouseEvent* e)
{
  if ((e->button() == Qt::RightButton) && (e->state() == Qt::NoButton))
    {
      QPopupMenu menu( this );
      menu.insertItem("Camera positions");
      menu.insertSeparator();

      QMap<int, int> menuMap;
      bool atLeastOne = false;
      for (unsigned short i=0; i<camera()->nbPaths(); ++i)
	if (camera()->keyFrameInterpolator(i))
	  {
	    atLeastOne = true;
	    if (camera()->keyFrameInterpolator(i)->numberOfKeyFrames() == 1)
	      menuMap[menu.insertItem("Position "+QString::number(i+1))] = i; 
	    else
	      menuMap[menu.insertItem("Path "+QString::number(i+1))] = i;
	  }

      if (!atLeastOne)
	{
	  menu.insertItem("No position defined");
	  menu.insertItem("Use to Alt+Fx to define one");
	}

      menu.setMouseTracking( true );
      int select = menu.exec( QCursor::pos() );

      if (atLeastOne && select != -1)
	camera()->playKeyFramePath(menuMap[select]);
    }
  else
    QGLViewer::mousePressEvent(e);
}

QString Viewer::helpString() const
{
  QString text("<h2>K e y b o a r d A n d M o u s e</h2>");
  text += "This example illustrates the mouse and key bindings customization.<br>";
  text += "Use setKeyFrameKey() to change standard action key bindings (axis, grid or fps display, exit...).<br>";
  text += "Use setMouseBinding() and setWheelBinding() to change standard action mouse bindings ";
  text += "(camera rotation, translation, object selection...).<br><br>";
  text += "If you want to define <b>new</b> key or mouse actions, you need to overload keyPressEvent() and/or ";
  text += "mouse(Press|Move|Release)Event to define and bind your own new actions.<br><br>";
  text += "Finally, overload shortcutBindingsString() and mouseBindingsString() to update the help window binding tabs.<br>";
  text += "See those tabs for the complete current bindings.<br>";
  text += "By the way, exit shortcut has been binded to <b>CTRL+Q</b>";
  return text;
}

// Add specific custom bindings to help window tabs
QString Viewer::mouseBindingsString() const
{
  QString text("The right mouse button opens a popup menu that displays the defined camera positions and paths.<br><br>");
  text += "The other mouse bindings are :<br>";
  text += QGLViewer::mouseBindingsString();
  return text;
}

QString Viewer::shortcutBindingsString() const
{
  QString text("Press '<b>W</b> to toggle wire frame display<br>");
  text += "Press '<b>F</b> to toggle flat shading display<br><br>";
  text += "The other standard actions are binded to:<br>";
  text += QGLViewer::shortcutBindingsString();
  return text;
}

