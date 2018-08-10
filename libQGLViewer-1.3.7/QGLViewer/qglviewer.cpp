/****************************************************************************

 This file is part of the QGLViewer library
 Copyright (C) 2002-2004  Gilles Debunne (Gilles.Debunne@imag.fr)
 Version 1.3.7 Release 1. Packaged on Friday April 30, 2004.

 http://artis.imag.fr/Members/Gilles.Debunne/QGLViewer

 libQGLViewer is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 libQGLViewer is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with libQGLViewer; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*****************************************************************************/

#include "qglviewer.h"
#include "camera.h"
#include "keyFrameInterpolator.h"

#include <qapplication.h>
#include <qfileinfo.h>
#include <qdatetime.h>
#include <qmessagebox.h>
#include <qtabdialog.h>
#include <qtimer.h>

#if QT_VERSION >= 300
# include <qdesktopwidget.h>
# include <qtextedit.h>
#else
# include <qtextview.h>
typedef QTextView QTextEdit;
#endif

using namespace std;
using namespace qglviewer;

// Static private variable
QPtrList<QGLViewer> QGLViewer::QGLViewerPool_;

/*! \mainpage

QGLViewer is an open source C++ library which enables you to quickly start the development of a new 3D
application. It is designed for 3D developers, who can very easily display and move around a 3D
scene by simply providing the OpenGL orders that define their 3D geometry. The viewer provides some
useful classical functionalities such as a camera trackball, screenshot saving, manipulated frames
with possible constraints, stereo display...

QGLViewer is \e not a 3D viewer that can be used directly to view 3D scenes in various formats, it
is actually more likely to be the starting point for the coding of such a viewer.

See the <a href="../index.html">project main page</a> for details on the project and installation
steps. */

void QGLViewer::defaultConstructor()
{
  //      - - -  W A R N I N G  - - -
  // This function should not call initializeGL(). Otherwise, as we are in the
  // base class constructor, the user-defined init() would never be called.
  // The different QGLViewer::setXXX are hence protected, so that updateGL is not called.
  // initializationStage_ tries to enforce this. The different constructor code should then be EMPTY.
  initializationStage_ = 0;

  QGLViewer::QGLViewerPool_.append(this);
  
  camera_ = new Camera();
  setCamera(camera());
  
  setFocusPolicy(QWidget::StrongFocus);
  
  setDefaultShortcutKeys();
  setDefaultMouseBindings();

  setSnapshotFilename("snapshot");
  setSnapshotFormat("JPEG");
  setSnapshotCounter(0);

  fpsTime_.start();
  fpsCounter_		= 0;
  f_p_s_		= 0.0;
  AxisDL_ 		= 0;     // Uninitialized
  GridDL_ 		= 0;     // Uninitialized
  CameraDL_ 		= 0;     // Uninitialized
  visualHint_		= 0;
  // prevPos_ is not initialized since pos() is not meaningful here. It will be set by setFullScreen().

  manipulatedFrame_ = NULL;
  manipulatedFrameIsACamera_ = false;
  mouseGrabberIsAManipulatedFrame_ = false;
  mouseGrabberIsAManipulatedCameraFrame_ = false;
  setMouseGrabber(NULL);
  
  setSceneRadius(1.0);
  showEntireScene();
  
  // Default values
  setDrawAxis(false);
  setDrawGrid(false);
  setDisplayFPS(false);
  setDisplayZBuffer(false);
  setEnableText(true);
  setStereoDisplay(false);
  setFullScreen(false);
  
  animationTimerId_ = 0;
  stopAnimation();
  setAnimationPeriod(40); // 25Hz

  selectBuffer_ = NULL;
  setSelectBufferSize(256);
  setSelectRegionSize(4);
  setSelectedName(-1);
  
  // Set stereo screen coefficients according to screen ratio:
  // 4/3 and 16/9 => monitor
  // 3x4/3 => Reality center configuration
  QDesktopWidget screen; 
  if (fabs((float)screen.width() / (float)screen.height()) > 2.0)
    {
      // Reality Center configuration
      camera()->setDistanceToScreen(4.0);
      camera()->setPhysicalScreenWidth(10.0);
    }
  
  initializationStage_ = 1;
}

/*! Set default display flags, initializes camera and other parameters.
  Calls the QGLWidget constructor with the same parameters.
  Calls qglviewer::Camera::setDistanceToScreen(4.0) and qglviewer::Camera::setPhysicalScreenWidth(10.0) when
  screen aspect ratio > 2 (Reality Center).

  See the Qt::QGLWidget associated constructor documentation for details on the parameters. */
QGLViewer::QGLViewer(QWidget *parent, const char *name, const QGLWidget * shareWidget, WFlags flags)
  : QGLWidget( parent,name,shareWidget,flags )
{
  // Read the defaultConstructor warning !!
  defaultConstructor();
}

/*! Same as QGLViewer(), but a Qt::QGLFormat can be provided (used for stereo display in the
  <a href="../examples/stereoViewer.html">stereoViewer</a> example. */
QGLViewer::QGLViewer(const QGLFormat& format, QWidget *parent, const char *name, const QGLWidget * shareWidget, WFlags flags)
  : QGLWidget( format,parent,name,shareWidget,flags )
{
  // Read the defaultConstructor warning !!
  defaultConstructor();
}

/*! Virtual destructor. Removes object from QGLViewerPool() and releases allocated memory. */
QGLViewer::~QGLViewer()
{
  QGLViewer::QGLViewerPool_.removeRef(this);
  delete[] keyFrameKey_;
  // The Camera cannot be deleted since it can now be used by an other viewer
}

/*! Initialization of the GL context, creation of some viewer display lists. Calls init() at the
  end.

  \attention The initial QGLViewer GL state does \e not follow the openGL standards.
  Actually, to make beginners' life easier and to simplify the examples, the following flags are defined :

  \code
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);
  \endcode

  If you port an existing application to QGLViewer and your display changes, you probably want to
  disable these flags (in init()) to get back to a standard openGL state.
  
  init() is called at the end, and the openGL flags can be re-defined there. This function should
  not be overloaded. Use init() for viewer initialization. In case of overloading, you should call
  QGLViewer::initializeGL() at the beginning of your new initializeGL() function (display list
  creation). */
void QGLViewer::initializeGL()
{
  if (initializationStage_ == 0)
    qWarning("Internal debug : initializeGL() is called in QGLViewer constructor. Please send a bug report.");

  initializationStage_ = 2;
  
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);  
  glEnable(GL_COLOR_MATERIAL);  

  // Default colors
  setForegroundColor(Vec(0.7, 0.7, 0.7));
  setBackgroundColor(Vec(0.2, 0.2, 0.2));

  // Axis, grid...
  createDisplayLists();
  
  // Clear the buffer where we're going to draw
  if (format().stereo())
    {
      glDrawBuffer(GL_BACK_RIGHT);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glDrawBuffer(GL_BACK_LEFT);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
  else 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Calls user defined function. Default emits a signal.
  init();

  // Give time to glInit to finish and then call setFullScreen().
  if (isFullScreen())
    QTimer::singleShot( 100, this, SLOT(delayedFullScreen()) );
  
  initializationStage_ = 3;
}

/*! The paint method. Calls preDraw(), draw() (or fastDraw()) and postDraw() in that order.
  Should not be overloaded. Overload the internal functions instead.
 
  If you choose to overload, the \c GL_Context must not be changed between two successive calls to
  draw(), so that the user can feel free to set his/her openGL flags once for all.
 
  If viewer displaysInStereo(), calls preDrawStereo(flag), draw(), postDraw(), first with flag = \c
  true and then flag = \c false to draw successively in left and right buffers. */
void QGLViewer::paintGL()
{
  if (displaysInStereo())
    {
      for (int view=1; view>=0; --view)
	{
	  // Clears screen, set model view matrix with shifted matrix for ith buffer
	  preDrawStereo(view);
	  // Used defined function. Default is empty
	  if (camera()->isManipulated())
	    fastDraw();
	  else
	    draw();
	  postDraw();
	}
    }
  else
    {
      // Clears screen, set model view matrix...
      preDraw();
      // Used defined function. Default is empty
      if (camera()->isManipulated())
	fastDraw();
      else
	draw();
      // Add visual hints : axis, camera, grid...
      postDraw();
    }
}

/*! Called before draw(). Default behavior clears screen and set the projection and model view matrices :
  \code
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    

  // GL_PROJECTION matrix
  camera()->loadProjectionMatrix();
  // GL_MODELVIEW matrix
  camera()->loadModelViewMatrix();
  \endcode

Emits the drawNeeded() signal once this is done. Mainly useful if you choose not to use derivation
to create your own viewer. See the <a href="../examples/callback.html">callback</a> example for
details*/
void QGLViewer::preDraw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    

  // GL_PROJECTION matrix
  camera()->loadProjectionMatrix();
  // GL_MODELVIEW matrix
  camera()->loadModelViewMatrix();

  emit drawNeeded();
}

/*! Done after draw(). Default behavior displays axis, grid, FPS... when the respective flags are
  enabled. The GLContext (color, LIGHTING, BLEND...) should \e not be changed by this function, so
  that in draw(), you can rely on the OpenGL context. Respect this convention (by pushing/popping
  the different attributes) if you overload this function. Assumes the \c GL_PROJECTION matrix was not
  changed by draw(), reset the \c GL_MODELVIEW matrix. */
void QGLViewer::postDraw()
{
  // Reset model view matrix to world coordinates origin
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  camera()->loadModelViewMatrix();
  // TODO restore model loadProjectionMatrixStereo

  // Save OpenGL state
  glPushAttrib(GL_ALL_ATTRIB_BITS);

  // Set neutral GL state
  glDisable(GL_TEXTURE_1D);
  glDisable(GL_TEXTURE_2D);
#ifdef GL_TEXTURE_3D  // OpenGL 1.2 Only...
  glDisable(GL_TEXTURE_3D);
#endif
  
  glDisable(GL_TEXTURE_GEN_Q);
  glDisable(GL_TEXTURE_GEN_R);
  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);

#ifdef GL_RESCALE_NORMAL  // OpenGL 1.2 Only...
  glEnable(GL_RESCALE_NORMAL);
#endif

  glDisable(GL_COLOR_MATERIAL);
  glColor3fv(foregroundColor().address());

  if (cameraPathIsEdited())
    camera()->drawAllPaths();

  // Revolve Around Point, line in Screen rotation mode
  drawVisualHints();

  // Scale hints according to sceneRadius.
  glScalef(camera()->sceneRadius(), camera()->sceneRadius(), camera()->sceneRadius());
  if (gridIsDrawn()) drawGrid();
  if (axisIsDrawn()) glCallList(AxisDL_); // Direct call, with a size of 1 scaled by the sceneRadius().
  if (zBufferIsDisplayed()) displayZBuffer();

  // FPS computation
  const unsigned int maxCounter = 25;
  if (++fpsCounter_ == maxCounter)
    {
      f_p_s_ = 1000.0 * maxCounter / fpsTime_.restart();
      fpsCounter_ = 0 ;
    }

  // Restore foregroundColor
  float color[4];
  color[0] = foregroundColor().x;
  color[1] = foregroundColor().y;
  color[2] = foregroundColor().z;
  color[3] = 1.0;
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
  glDisable(GL_LIGHTING);

  if (fpsIsDisplayed()) displayFPS();

  // Restore GL state
  glPopAttrib();
  glPopMatrix();
}

/*! Called before draw() (instead of preDraw()) when viewer displaysInStereo(). Same as preDraw()
  except that the glDrawBuffer() is set to \c GL_BACK_LEFT or \c GL_BACK_RIGHT depending on \p
  leftBuffer. */
void QGLViewer::preDrawStereo(bool leftBuffer)
{  
  // Set buffer to draw in
  // Seems that SGI and Crystal Eyes are not synchronized correctly !
  // That's why we don't draw in the appropriate buffer...
  // Yes it's tricky, but it works
  if (!leftBuffer)
    glDrawBuffer(GL_BACK_LEFT);
  else
    glDrawBuffer(GL_BACK_RIGHT);

  // Clear the buffer where we're going to draw
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // GL_PROJECTION matrix
  camera()->loadProjectionMatrixStereo(leftBuffer);
  // GL_MODELVIEW matrix
  camera()->loadModelViewMatrixStereo(leftBuffer);
  
  emit drawNeeded();
}

/*! Fast draw of the scene. Called instead of draw() when the camera is manipulated. Useful for
  interactive displacements in a complex scene. Default behavior calls draw(). See the
  <a href="../examples/fastDraw.html">fastDraw</a> example for an illustration. */
void QGLViewer::fastDraw()
{
  draw();
}


/*! Start (default, \p edit=\p true) or stop (\p edit=\p false) the edition of the camera paths. See
also toggleCameraPathEditor(). */
void QGLViewer::editCameraPath(bool edit)
{
  camera()->editCameraPath(edit);
  emit cameraPathEdited(edit);
  if (initializationStage_==3)
    updateGL();
}


// Key bindings. 0 means not defined 
void QGLViewer::setDefaultShortcutKeys()
{
  // S t a n d a r d   s h o r t c u t   k e y s
  setShortcutKey(DRAW_AXIS	   , Qt::Key_A,        Qt::NoButton);
  setShortcutKey(DRAW_GRID	   , Qt::Key_G,        Qt::NoButton);
  setShortcutKey(DISPLAY_FPS	   , Qt::Key_F,        Qt::NoButton);
  setShortcutKey(DISPLAY_Z_BUFFER  , Qt::Key_Z,        Qt::NoButton);
  setShortcutKey(ENABLE_TEXT	   , Qt::Key_Question, Qt::ShiftButton);
  setShortcutKey(EXIT		   , Qt::Key_Escape,   Qt::NoButton);
  setShortcutKey(SAVE_SCREENSHOT   , Qt::Key_S,        Qt::ControlButton);
  setShortcutKey(CAMERA_MODE	   , Qt::Key_Space,    Qt::NoButton);
  setShortcutKey(FULL_SCREEN	   , Qt::Key_Return,   Qt::AltButton);
  setShortcutKey(STEREO		   , Qt::Key_S,        Qt::NoButton);
  setShortcutKey(ANIMATION	   , Qt::Key_Return,   Qt::NoButton);
  setShortcutKey(HELP		   , Qt::Key_H,        Qt::NoButton);
  setShortcutKey(EDIT_CAMERA_PATHS , Qt::Key_C,        Qt::NoButton);

  // K e y f r a m e s   s h o r t c u t   k e y s
  keyFrameKey_ = new Qt::Key[camera()->nbPaths()];
  setKeyFrameKey(0, Qt::Key_F1);
  setKeyFrameKey(1, Qt::Key_F2);
  setKeyFrameKey(2, Qt::Key_F3);
  setKeyFrameKey(3, Qt::Key_F4);
  setKeyFrameKey(4, Qt::Key_F5);
  setKeyFrameKey(5, Qt::Key_F6);
  setKeyFrameKey(6, Qt::Key_F7);
  setKeyFrameKey(7, Qt::Key_F8);
  setKeyFrameKey(8, Qt::Key_F9);
  setKeyFrameKey(9, Qt::Key_F10);
  setKeyFrameKey(10,Qt::Key_F11);
  setKeyFrameKey(11,Qt::Key_F12);

  setAddKeyFrameStateKey(Qt::AltButton);
  setPlayKeyFramePathStateKey(Qt::NoButton);
}

// M o u s e   b e h a v i o r
void QGLViewer::setDefaultMouseBindings()
{
  const Qt::ButtonState frameStateKey = Qt::ControlButton;
  //#CONNECTION# toggleCameraMode()
  for (int handler=0; handler<2; ++handler)
    {
      MouseHandler mh = (MouseHandler)(handler);
      Qt::ButtonState state = Qt::NoButton;
      if (mh == FRAME)
	state = frameStateKey;
      
      setMouseBinding(state | Qt::LeftButton,  mh, ROTATE);
      setMouseBinding(state | Qt::MidButton,   mh, ZOOM);
      setMouseBinding(state | Qt::RightButton, mh, TRANSLATE);
  
      setMouseBinding(state | Qt::LeftButton  | Qt::MidButton,  mh, SCREEN_ROTATE);
      setMouseBinding(state | Qt::RightButton | Qt::MidButton,  mh, SCREEN_TRANSLATE);

      setWheelBinding(state, mh, ZOOM);
    }

  setMouseBinding(Qt::ShiftButton | Qt::MidButton, CAMERA, ZOOM_ON_REGION);

  // S e l e c t
  setMouseBinding(Qt::ShiftButton | Qt::LeftButton, SELECT);

  // D o u b l e   c l i c k
  setMouseBinding(Qt::LeftButton,  ALIGN_CAMERA,      true);
  setMouseBinding(Qt::MidButton,   SHOW_ENTIRE_SCENE, true);
  setMouseBinding(Qt::RightButton, CENTER_SCENE,      true);

  setMouseBinding(frameStateKey | Qt::LeftButton,  ALIGN_FRAME,  true);
  setMouseBinding(frameStateKey | Qt::RightButton, CENTER_FRAME, true);

  // S p e c i f i c   d o u b l e   c l i c k s
  setMouseBinding(Qt::LeftButton,  RAP_FROM_PIXEL, true, Qt::RightButton);
  setMouseBinding(Qt::RightButton, RAP_IS_CENTER,  true, Qt::LeftButton);
  setMouseBinding(Qt::LeftButton,  ZOOM_ON_PIXEL,  true, Qt::MidButton);
  setMouseBinding(Qt::RightButton, ZOOM_TO_FIT,    true, Qt::MidButton);
}

void QGLViewer::getBackgroundColor(float& r, float& g, float& b) const
{
  r = backgroundColor().x;
  g = backgroundColor().y;
  b = backgroundColor().z;
}

void QGLViewer::getForegroundColor(float& r, float& g, float& b) const
{
  r = foregroundColor().x;
  g = foregroundColor().y;
  b = foregroundColor().z;
}

/*! Associate a new qglviewer::Camera to the viewer.

You should only use this method when you derive a new class from Camera and want to use one of its
instances instead of the original class.

It you simply want to save and restore Camera positions, use qglviewer::Camera::addKeyFrame() and
qglviewer::Camera::playKeyFramePath() instead.

This method will silently ignore NULL \p c pointers. The calling method is responsible for deleting
the previous camera pointer, if that is intended, in order to prevent memory leaks:
\code
delete camera();
setCamera(myCamera);
\endcode

All the \p c qglviewer::Camera::keyFrameInterpolator()
qglviewer::KeyFrameInterpolator::interpolated() signals are connected to the viewer updateGL() slot.
The connections with the previous viewer's camera are removed.

The sceneRadius() and sceneCenter() of the new \p c camera are set to the current QGLViewer values. */
void QGLViewer::setCamera(Camera* const c)
{
  if (!c)
    return;

  c->setSceneRadius(sceneRadius());
  c->setSceneCenter(sceneCenter());
  c->setWindowWidthAndHeight(width(),height());

#if QT_VERSION >= 300 // Qt 2.3 has problems with inherited signals.
  // Disconnect current camera to this viewer.
  disconnect(camera()->frame(), SIGNAL(manipulated()), this, SLOT(updateGL()));
  disconnect(camera()->frame(), SIGNAL(spinned()), this, SLOT(updateGL()));
    
  // Connect camera frame to this viewer.
  connect(c->frame(), SIGNAL(manipulated()), SLOT(updateGL()));
  connect(c->frame(), SIGNAL(spinned()), SLOT(updateGL()));
#endif

  connectAllCameraKFIInterpolated(false);
  camera_ = c;
  connectAllCameraKFIInterpolated();
}

void QGLViewer::connectAllCameraKFIInterpolated(bool connection)
{
  for (int i=0; i<camera()->nbPaths(); ++i)
    if (camera()->keyFrameInterpolator(i))
      if (connection)
	connect(camera()->keyFrameInterpolator(i), SIGNAL(interpolated()), SLOT(updateGL()));
      else
	disconnect(camera()->keyFrameInterpolator(i), SIGNAL(interpolated()), this, SLOT(updateGL()));

  if (connection)
    connect(camera()->interpolationKfi_, SIGNAL(interpolated()), SLOT(updateGL()));
  else
    disconnect(camera()->interpolationKfi_, SIGNAL(interpolated()), this, SLOT(updateGL()));
}

QWidget* QGLViewer::rootWidget() const
{
  QWidget* rootWidget_ = const_cast<QGLViewer*>(this);
  while (rootWidget_->parentWidget())
    rootWidget_ = rootWidget_->parentWidget();
  return rootWidget_;
}

/*! float version of sceneCenter(). */
void QGLViewer::getSceneCenter(float& x, float& y, float& z) const
{
  Vec sc = sceneCenter();
  x = sc.x;
  y = sc.y;
  z = sc.z;
}


/*! Displays an XYZ axis, with a given size (default is 1.0). The axis position and orientation only
  depends on the current modelview matrix state. This code will display a translated and rotated
  axis (with respect to the world coordinates system, that can be displayed using the DRAW_AXIS shortcut
  key. Default key is 'A').
  \code
  glPushMatrix();
  glTranslatef(x,y,z);
  glRotatef(90.,0.,1.,0.);
  drawAxis(0.2);
  glPopMatrix();
  \endcode
  Use the following code to display the current position and orientation of a qglviewer::Frame :
  \code
  glPushMatrix();
  glMultMatrixd(frame.matrix());
  drawAxis(0.2);
  glPopMatrix();
  \endcode
  
  \note The current matrix mode should be \c GL_MODELVIEW. */
void QGLViewer::drawAxis(float size)
{
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glDisable(GL_COLOR_MATERIAL);
#ifdef GL_RESCALE_NORMAL  // OpenGL 1.2 Only...
  glEnable(GL_RESCALE_NORMAL);
#endif
  glPushMatrix();
  glScalef(size, size, size);
  glColor3fv(foregroundColor().address());
  glCallList(AxisDL_);
  glPopMatrix();
  glPopAttrib();
}

/*! This debugging function draws a representation of \p light. The drawing depends on the type of
  light (spot, directional...). Typically used in your draw function:
  \code
  drawLight(GL_LIGHT0)
  \endcode

  Optionnal parameter \p scale (default 1.0f) rescales the light representation. For instance, to
  get a size twice bigger:  
  \code
  drawLight(GL_LIGHT0, 2.0f)
  \endcode
  Note that this size is already proportional to the scene radius.
  
  See the <a href="../examples/drawLight.html">drawLight</a> example for an illustration. */
void QGLViewer::drawLight(GLenum light, float scale) const
{
  static GLUquadric* quadric = gluNewQuadric();

  const float r = camera()->sceneRadius()*scale / 30.0;
  GLboolean lightIsOn;
  glGetBooleanv(light,&lightIsOn);
  if (lightIsOn)
    {
      float p[4];
      glGetLightfv(light, GL_POSITION, p);
      if (p[3] != 0.0)
	{
	  GLfloat cutoff;
	  glGetLightfv(light, GL_SPOT_CUTOFF, &cutoff);
	  if (cutoff != 180.0)
	    {
	      GLfloat d[4];
	      glGetLightfv(light, GL_SPOT_DIRECTION, d);
	      glPushMatrix();
	      glLoadIdentity();
	      glDisable(GL_LIGHTING);
	      glBegin(GL_LINES);
	      glVertex3f(p[0]/p[3],p[1]/p[3],p[2]/p[3]);
	      glVertex3f(p[0]/p[3]+10.0*r*d[0],
			 p[1]/p[3]+10.0*r*d[1],
			 p[2]/p[3]+10.0*r*d[2]);
	      glEnd();
	      glEnable(GL_LIGHTING);
	      glPopMatrix();
	    }
	  //      else
	  {
	    glPushMatrix();
	    glLoadIdentity();
	    glTranslatef(p[0]/p[3],p[1]/p[3],p[2]/p[3]);
	    glDisable(GL_LIGHTING);
	    gluSphere(quadric, r, 10, 10);
	    glEnable(GL_LIGHTING);
	    glPopMatrix();
	  }
	}
      else
	{
	  glDisable(GL_LIGHTING);
	  glBegin(GL_LINES);
	  glVertex3fv(camera()->sceneCenter().address());
	  const float l = 5.0 * camera()->sceneRadius();
	  glVertex3f(l*p[0], l*p[1], l*p[2]);
	  glEnd();
	  glEnable(GL_LIGHTING);
	}
    }
}


/*! Displays the current z-buffer in grey levels for debugging purposes. Note that it hides the
  normal display. Frame rate is slowed down because of the z-buffer reading and writing. */
void QGLViewer::displayZBuffer() const
{
  // Clearly not optimal, but much robust
  GLuint* z_buffer = new GLuint[width()*height()];
  
  glReadPixels(0,0,width(),height(),GL_DEPTH_COMPONENT,GL_UNSIGNED_BYTE,z_buffer);
  // Raster position may have been changed by calls to renderText().
  const Vec origin = camera()->unprojectedCoordinatesOf(Vec(1, height()-1, 0.01));  
  glRasterPos3fv(origin.address());
  glDrawPixels(width(),height(),GL_LUMINANCE,GL_UNSIGNED_BYTE,z_buffer);

  delete[] z_buffer;
}

/*! Draws a \p text at position \p x, \p y (expressed in screen coordinates pixels, origin in the
  upper left corner of the window). Can be called in draw() to easily display some information on
  the screen.

  This procedure calls QGLWidget::renderText() if your Qt version is at least 3.1, otherwise it uses
  GLUT. The default QApplication::font() is used to render the text when no \p fnt is specified. Use
  QApplication::setFont() to define the default font. Only the font size (set with
  QFont::setPixelSize() or QFont::setPointSize()) is taken into with the GLUT version.

  \attention \c GL_LIGHTING should be disabled by the calling function so that colors are properly
  rendered (with the renderText version).

  This function can be used in conjunction with the qglviewer::Camera::projectedCoordinatesOf() function to
  display a text attached to an object. In your draw() function call:
  \code
  qglviewer::Vec screenPos = camera()->projectedCoordinatesOf(myFrame.position());
  drawText((int)screenPos[0], (int)screenPos[1], "My Object");
  \endcode
  See the <a href="../examples/screenCoordSystem.html">screenCoordSystem</a> example for an illustration.

  QGLWidget::renderText() (Qt >= 3.1) performs a similar action. It exists in a 2D (pixel
  coordinates) and a 3D (classical coordinates) version. Use this QGLWidget::renderText(x,y,z, str)
  function to draw a text that faces the camera, located at a specific 3D location (no need to
  convert to screen coordinates).
  
  The \c GL_MODELVIEW and \c GL_PROJECTION matrices are not modified by this function.

  Text is displayed only when textIsEnabled() is \c true (default). Use toggleEnableText() or
  setEnableText() to change this value (default ENABLE_TEXT shortcut key is '?'). This mechanism
  allows the user to conveniently remove all the displayed text with a shortcut key. Set the
  shortcut key to 0 if you want to forbid this behavior (see setShortcutKey()).

  See also the draw3DText() and displayFPS() functions.

  \note Each call to drawText() changes the camera projection matrix and restores it back (using
  startScreenCoordinatesSystem() and stopScreenCoordinatesSystem() with Qt < 3.1). If you call this
  function several times and it slows down your frame rate, consider factorizing the context
  changes. You may also want to try the Qt image overlay mechanism which may be more efficient when
  your text does not change over time).

  \note The Qt minimum version that disables glut is set by QT_VERSION_WITHOUT_GLUT in config.h.
  Default value is Qt 3.1. */
void QGLViewer::drawText(int x, int y, const QString& text, const QFont& fnt)
{
  if (!textIsEnabled())
    return;
 
#if QT_VERSION < QT_VERSION_WITHOUT_GLUT
  const GLfloat font_scale = 119.05f - 33.33f; // see glutStrokeCharacter man page

  startScreenCoordinatesSystem();

  // Anti-aliassed characters
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glDisable(GL_LIGHTING);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_LINE_SMOOTH);
  glLineWidth(1.0);

  glTranslatef((GLfloat)x, (GLfloat)y, 0.0);
  const GLfloat scale = ((fnt.pixelSize()>0)?fnt.pixelSize():fnt.pointSize()) / font_scale;
  glScalef(scale, -scale, scale);

  for (uint i=0; i<text.length(); ++i)
    glutStrokeCharacter(GLUT_STROKE_ROMAN, text.at(i));

  glPopAttrib();
  
  stopScreenCoordinatesSystem();
  
#else

# if QT_VERSION < 0x030300
  // Fix bug with antialiassed fonts on nVidia driver
  QFont newFont(fnt);
  newFont.setStyleStrategy(QFont::PreferBitmap);
  renderText(x, y, text, newFont);
# else
  renderText(x, y, text, fnt);
# endif
  
#endif
}

/*! \deprecated
Similar to drawText(), but the text is handled as a classical 3D object of the scene.

Although useful, this function is deprecated with recent Qt versions. Indeed, Qt renders text as
pixmaps that cannot be orientated. However, when GLUT is used instead of Qt (when your Qt version is
lower than 3.1, see QT_VERSION_WITHOUT_GLUT in config.h) orientated characters are possible and this
function will work.

\p pos and \p normal respectly represent the 3D coordinate of the text and the normal to the text
plane. They are expressed with respect to the \e current \c GL_MODELVIEW matrix.


If you want your text to always face the camera (normal parallel to camera()->viewDirection), use
QGLWidget::renderText(x,y,z).

See the <a href="../examples/draw3DText.html">draw3DText</a> example for an illustration. */
void QGLViewer::draw3DText(const Vec& pos, const Vec& normal, const QString& text, GLfloat height)
{
#if QT_VERSION < QT_VERSION_WITHOUT_GLUT
  if (!textIsEnabled())
    return;

  glMatrixMode(GL_MODELVIEW) ;
  glPushMatrix() ;

  const GLfloat font_scale = (119.05f - 33.33f) / 8; // see glutStrokeCharacter man page
  // const GLfloat font_scale = (119.05f - 33.33f) * 15.0f; // see glutStrokeCharacter man page

  static GLfloat lineWidth;
  glGetFloatv(GL_LINE_WIDTH, &lineWidth);
  
  glTranslatef(pos.x, pos.y, pos.z);
  glMultMatrixd(Quaternion(Vec(0.0, 0.0, 1.0), normal).matrix());

  glLineWidth(2.0);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glEnable(GL_LINE_SMOOTH);

  const GLfloat scale = height / font_scale;
  glScalef(scale, scale, scale);

  for (uint i=0; i<text.length(); ++i)
    glutStrokeCharacter(GLUT_STROKE_ROMAN, text.at(i));

  glLineWidth(lineWidth);

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix() ;
#else
  static bool displayed = false;

  if (!displayed)
    {
      qWarning("draw3DText is not supported with Qt >= 3.1.");
      qWarning("Use QGLWidget::renderText() instead,");
      qWarning("or use the glut glutStrokeCharacter() function.");
      displayed = true;
    }

  // prevents compilation warnings because of unused parameters
  if (pos.x>0 && normal.y<0 && text.isNull() && height == 0.0)
    qWarning("Eastern egg");
#endif
}

/*! Display the frame rate in the corner of the window. The frame rate is computed as an average and
  updateGL() must be called in a loop in order to have a meaningful value (this is the case when
  animationIsStarted()). The FPS display can be toggled with toggleDisplayFPS() (Default shortcut
  key is 'F', see DISPLAY_FPS) or with setDisplayFPS(). Use QApplication::setFont() to define the
  FPS font (see drawText()). Get current application (averaged) frame rate with currentFPS(). */
void QGLViewer::displayFPS()
{
  static QString fpsString;
  
  if (f_p_s_ < 10.0)
    fpsString.sprintf("%.1fHz", f_p_s_);
  else
    fpsString.sprintf("%.0fHz", f_p_s_);

  drawText(10, int(1.5*((QApplication::font().pixelSize()>0)?QApplication::font().pixelSize():QApplication::font().pointSize())), fpsString);
}

/*! Use this function when you want to start drawing directly with the 2D screen coordinates system
  in your draw() function. Once this function has been called, the \p x, \p y coordinates correspond
  to the screen coordinates. The projection matrix is orthographic and \c glMatrixMode is set to \c
  GL_MODELVIEW.

  The coordinates origin (0,0) is in the upper left corner of the window by default. This follows
  the Qt standards and make it easier to directly use \c QMouseEvent pos(). However, setting \p
  upward to \c true places the origin in the \e lower left corner, thus following the GL and
  mathematical standards. It is always possible to switch between the two representations using \c
  newY = \c height() - \c y.

  \attention The select() function is sensitive to the orientation of the coordinates system
  (convertion between screen and GL coordinates). The \p upward coordinate system will not be
  compatible with the "classical" select() implementation (see the
  <a href="../examples/select.html">select</a> example), and you should convert the y coordinate using
  \c newY = \c height() - \c y before calling select().
  
  Use qglviewer::Camera::projectedCoordinatesOf() to compute the 2D projection on screen of a 3D
  point (results have an origin in the upper left corner). See the
  <a href="../examples/screenCoordSystem.html">screenCoordSystem</a> example for an illustration.

  You may want to change gl state when drawing in 2D, such as for instance :
  \code
  startScreenCoordinatesSystem();

  // Disable lighting to enforce colors
  glDisable(GL_LIGHTING);

  // Enable blending to prevent aliassed lines
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glEnable(GL_LINE_SMOOTH);

  // And so on ...
  glDisable(GL_DEPTH_TEST);
  glLineWidth(1.0);

  // Your drawing code goes here

  // Restore (or not) previous gl state here
    
  stopScreenCoordinatesSystem();
  \endcode

  You need to call stopScreenCoordinatesSystem() at the end of the drawing block to restore the
  previous camera matrix. */
void QGLViewer::startScreenCoordinatesSystem(bool upward) const
{
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  if (upward)
    glOrtho( 0, width(), 0, height(), -1, 1 );
  else
    glOrtho( 0, width(), height(), 0, -1, 1 );
  
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
}

/*! This function closes the screen coordinates drawing block that was started by
  startScreenCoordinatesSystem(). The \c GL_MODELVIEW and \c GL_PROJECTION matrices modified in
  startScreenCoordinatesSystem() are restored. \c glMatrixMode is set to \c GL_MODELVIEW.
  
  \attention Calling this function when no startScreenCoordinatesSystem() was called will probably
  result in a crash. */
void QGLViewer::stopScreenCoordinatesSystem() const
{
  glMatrixMode(GL_PROJECTION); 
  glPopMatrix();

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix(); 
}

/*! Overloading of the timer function. Calls animate() (if animationIsStarted()) and then draw(), at
  a frequency set by setAnimationPeriod(). */
void QGLViewer::timerEvent(QTimerEvent *)
{
  if (animationIsStarted())
    animate();
  updateGL();
}

/*! Start the animation loop. animate() and draw() will be called in a loop. The loop frequency is
defined by animationPeriod() (default is 40 msecs=25Hz). See also stopAnimation() and animate().

See the <a href="../examples/animation.html">animation</a> example for illustration.

You may also be interested in qglviewer::KeyFrameInterpolator::startInterpolation(). */
void QGLViewer::startAnimation()
{
  animationTimerId_ = startTimer(animationPeriod());
  animationStarted_ = true;
}

/*! Stop an animation started with startAnimation() or toggleAnimationMode(). */
void QGLViewer::stopAnimation()
{
  animationStarted_ = false;
  killTimer(animationTimerId_);
}

/*! Save the viewer current state using saveToFile() and then call QGLWidget::closeEvent(). */
void QGLViewer::closeEvent(QCloseEvent *e)
{
  // Also done for EXIT in keyPressEvent().
  // When the user clicks on the window close (x) button :
  // - If the viewer is a top level window, closeEvent saves to file.
  // - Otherwise, nothing happen :(
  // When the user press the EXIT shortcut key :
  // - If the viewer is a top level window, saveToFile() is also called
  // - Otherwise, closeEvent is NOT called and keyPressEvent does the job.
  saveToFile();
  QGLWidget::closeEvent(e);
}

/*! Simple wrapper function : calls \c select(e->x(), e->y()).

  Emits \c pointSelected(e) which is useful only if you rely on the Qt signal-slot mechanism and you
  did not overload QGLViewer. If you choose to derive your own viewer class, simply overload
  select() (or probably simply drawWithNames(), see the <a href="../examples/select.html">select</a>
  example) to implement your selection mechanism. */
void QGLViewer::select(const QMouseEvent* e)
{
  // For those who don't derive but rather rely on the signal-slot mechanism.
  emit pointSelected(e);
  select(e->x(), e->y());
}

/*! This function performs a selection in the scene from pixel coordinates. It is called when the
  user clicks on the SELECT ClickAction binded button(s) (default is Shift-LeftButton).

  This function successively calls four other functions:
  \code
  beginSelection(x,y);
  drawWithNames();
  endSelection(x,y);
  postSelection(x,y);
  \endcode

  The default implementation of these functions is as follows (see the functions' documentation for more details) :
  \arg beginSelection() sets the \c GL_SELECT mode with the appropriate picking matrices.
  
  \arg drawWithNames() is empty and should be overloaded to draw your scene with glPushNames() calls.
  
  \arg endSelection() restores \c GL_RENDER mode and set in selectedName() the closer picked object, or -1 if not object was picked.
  
  \arg postSelection() is empty and can be overloaded for possible signal/display/interface update.

  \c The GL_SELECT mode works as follows : a square frustum (see selectRegionSize()) is created
  around the mouse cursor by beginSelection(). The scene objects are then drawned by drawWithNames()
  which pushes a name (an integer value) before each of them. The names of the objects that draw
  something in the selection region are recorded in the selectBuffer(). endSelection() then analyses
  this buffer and setSelectedName() to the name corresponding to the closest object. postSelection()
  can then be used to update the data structure according to this selection. See the
  glSelectBuffer() man page for details on this mechanism.
  
  This default implementation is quite limited: only the closer object is selected, and only one
  level of names can be pushed. However, this reveals sufficient in many cases and you usually only
  have to overload drawWithNames() and maybe postSelection(). See the <a
  href="../examples/select.html">select</a> example for an illustration.

  If you need a more complex selection process (such as a point, edge or triangle selection, which
  is easier with a 2 or 3 levels heap, and which requires a finer depth sorting to priviledge point
  over edge and edges over triangles), overload the endSelection() method. Use
  setSelectRegionSize(), setSelectBufferSize() to tune the select buffer configuration.

  \p x and \p y are the pixel coordinates (origin in the upper left corner) where the selection
  occurs. Use qglviewer::Camera::convertClickToLine() to transform these coordinates in a 3D ray if
  you want to perform an analytical intersection.

  Use setMouseBinding() to customize mouse bindings. See also selectBuffer(), selectBufferSize(), selectRegionSize(). */
void QGLViewer::select(int x, int y)
{
  beginSelection(x,y);
  drawWithNames();
  endSelection(x,y);
  postSelection(x,y);
}
  
/*! This method should prepare the selection. It is called by select() before drawWithNames().

  The default implementation uses the \c GL_SELECT mode to perform a selection. It uses
  selectBuffer() and selectBufferSize() to define a \c glSelectBuffer(). The \c GL_PROJECTION is
  then set using gluPickMatrix(), with a window selection size defined by selectRegionSize().
  Finally, the \c GL_MODELVIEW matrix is set to the world coordinate sytem using
  qglviewer::Camera::loadModelViewMatrix().

  You should have to redefine this function (if you use the \c GL_SELECT mode to perform your
  selection), since this code is fairly classical and can be tuned using setSelectBufferSize() and
  setSelectRegionSize(). You are more likely to overload endSelection() if you want to use a more
  complex select buffer structure. */
void QGLViewer::beginSelection(int x, int y)
{  
  // Make openGL context current (may be needed with several viewers ?)
  makeCurrent();
    
  // Prepare the selection mode
  glSelectBuffer(selectBufferSize(), selectBuffer());
  glRenderMode(GL_SELECT);
  glInitNames();

  // Loads the matrices
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  GLint viewport[4];
  camera()->getViewport(viewport);
  gluPickMatrix(x, y, selectRegionSize(), selectRegionSize(), viewport);

  // loadProjectionMatrix() first resets the GL_PROJECTION matrix with a glLoadIdentity().
  // The false parameter prevents this and hence multiplies the matrices.
  camera()->loadProjectionMatrix(false);
  // Reset the original (world coordinates) modelview matrix
  camera()->loadModelViewMatrix();
}

/*! This method is called by select() after scene elements were drawned by drawWithNames(). It
  should analyse the selection result to determine which object is actually selected.

  The default implementation relies on \c GL_SELECT mode (see beginSelection()). It assumes that
  names were pushed and popped in drawWithNames(), and analyses the selectBuffer() to find the name
  that corresponds to the closer (z min) object. It then setSelectedName() to this value, or to -1
  if the selectBuffer() is empty (no object under the mouse cursor). Use selectedName() (probably in
  the postSelection() method) to retrieve this value and update your data structure accordingly.

  This default implementation, although sufficient for many cases is however limited and you may
  have to overload this method. This will be the case if drawWithNames() uses several push levels in
  the name heap. A more precise depth selection, for instance priviledging points over edges and
  triangles to avoir z precision problems, will also require an overloading. A typical
  implementation will look like:
  \code
  glFlush();

  // Get the number of objects that were seen through the pick matrix frustum. Reset GL_RENDER mode.
  GLint nbHits = glRenderMode(GL_RENDER);

  if (nbHits <= 0)
    setSelectedName(-1);
  else
    {
      // Interpret results : each object created values in the selectBuffer().
      // See the glSelectBuffer() man page for details on the buffer structure.
      // The following code depends on your selectBuffer() structure.
      for (int i=0; i<nbHits; ++i)
       if ((selectBuffer())[i*4+1] < zMin)
         setSelectedName((selectBuffer())[i*4+3])
    }
  \endcode */
void QGLViewer::endSelection(int, int)
{
  // Flush GL buffers
  glFlush();

  // Get the number of objects that were seen through the pick matrix frustum. Reset GL_RENDER mode.
  GLint nbHits = glRenderMode(GL_RENDER);

  if (nbHits <= 0)
    setSelectedName(-1);
  else
    {
      // Interpret results : each object created 4 values in the selectBuffer().
      // hits[4*i+1] is the object minimum depth value, while hits[4*i+3] is the id pushed on the stack.
      // Of all the objects that were projected in the pick region, we select the closest one (zMin comparison).
      // This code needs to be modified if you use several stack levels. See glSelectBuffer() man page.
      GLuint zMin = (selectBuffer())[1];
      setSelectedName((selectBuffer())[3]);
      for (int i=1; i<nbHits; ++i)
	if ((selectBuffer())[i*4+1] < zMin)
	  {
	    zMin = (selectBuffer())[i*4+1];
	    setSelectedName((selectBuffer())[i*4+3]);
	  }
    }
}

/*! Changes the selectBufferSize(). The previous selectBuffer() is deleted and a new one created. */
void QGLViewer::setSelectBufferSize(int size)
{
  if (selectBuffer_)
    delete[] selectBuffer_;
  selectBufferSize_ = size; 
  selectBuffer_ = new GLuint[selectBufferSize()];
}


void QGLViewer::performClickAtion(ClickAction ca, const QMouseEvent* const e)
{
  switch (ca)
    {
    case NO_CLICK_ACTION :
      break;
    case ZOOM_ON_PIXEL :
      camera()->interpolateToZoomOnPixel(e->x(), e->y());
      break;
    case ZOOM_TO_FIT :
      camera()->interpolateToFitScene();
      break;
    case SELECT :
      select(e);
      updateGL();
      break;
    case RAP_FROM_PIXEL :
      if (camera()->setRevolveAroundPointFromPixel(e->x(), e->y()))
	{
	  setVisualHintsMask(1);
	  updateGL();
	}
      break;
    case RAP_IS_CENTER :
      camera()->setRevolveAroundPoint(sceneCenter());
      setVisualHintsMask(1);
      updateGL();
      break;
    case CENTER_FRAME :
      if (manipulatedFrame())
	manipulatedFrame()->projectOnLine(camera()->position(), camera()->viewDirection());
      break;
    case CENTER_SCENE :
      camera()->centerScene();
      break;
    case SHOW_ENTIRE_SCENE :
      camera()->showEntireScene();
      break;
    case ALIGN_FRAME :
      if (manipulatedFrame())
	manipulatedFrame()->alignWithFrame(camera()->frame());
      break;
    case ALIGN_CAMERA :
      camera()->frame()->alignWithFrame(NULL, true);
      break;
    }
}

/*! When the user clicks on the mouse:
  \arg if a mouseGrabber() is defined, qglviewer::MouseGrabber::mousePressEvent() is called,
  \arg otherwise, the camera() or the manipulatedFrame() interprets the mouse displacements, depending
  on current mouse bindings.

  See the <a href="../mouse.html">QGLViewer mouse page</a> for a complete description of mouse
  bindings. If you need to implement a scene object selection with the mouse, see the
  <a href="../examples/select.html">select</a> example and qglviewer::Camera::convertClickToLine().

  Classical mouse binding customization can be achieved using setMouseBinding() and
  setWheelBinding().

  See the mouseMoveEvent() documentation for an example of more complex mouse behavior
  customization.

  \note When the mouseGrabber() is a manipulatedFrame(), the modifier keys are not taken into
  account. This allows for a direct manipulation of the manipulatedFrame() when the mouse hovers,
  which is probably what is expected. */
void QGLViewer::mousePressEvent(QMouseEvent* e)
{
  if (mouseGrabber())
    {
      if (mouseGrabberIsAManipulatedFrame_)
	{
	  for (QMap<Qt::ButtonState, MouseActionPrivate>::ConstIterator it=mouseBinding_.begin(), end=mouseBinding_.end(); it!=end; ++it)
	    if ((it.data().handler == FRAME) && ((it.key() & Qt::MouseButtonMask) == (e->stateAfter() & Qt::MouseButtonMask)))
	      {
#if QT_VERSION < 300
		ManipulatedFrame* mf = static_cast<ManipulatedFrame*>(mouseGrabber());
#else
		ManipulatedFrame* mf = dynamic_cast<ManipulatedFrame*>(mouseGrabber());
#endif
		if (mouseGrabberIsAManipulatedCameraFrame_)
		  {
		    mf->ManipulatedFrame::startAction(it.data().action, it.data().withConstraint);
		    mf->ManipulatedFrame::mousePressEvent(e, camera());
		  }
		else
		  {
		    mf->startAction(it.data().action, it.data().withConstraint);
		    mf->mousePressEvent(e, camera());
		  }
		break;
	      }
	}
      else
	mouseGrabber()->mousePressEvent(e, camera());
      updateGL();
    }
  else
    {
      //#CONNECTION# mouseDoubleClickEvent has the same structure
      ClickActionPrivate cap;
      cap.doubleClick = false;
      cap.buttonState = (Qt::ButtonState)((e->state() & Qt::KeyButtonMask) |
					  ((e->stateAfter() & Qt::MouseButtonMask) & (~(e->state() & Qt::MouseButtonMask))));
      cap.buttonBefore = (Qt::ButtonState)(e->state() & Qt::MouseButtonMask);
      const QMap<ClickActionPrivate, ClickAction>::ConstIterator ca = clickBinding_.find(cap);
      if (ca != clickBinding_.end())
	performClickAtion(ca.data(), e);
      else
	{
	  //#CONNECTION# wheelEvent has the same structure
	  const QMap<Qt::ButtonState, MouseActionPrivate>::ConstIterator map = mouseBinding_.find(e->stateAfter());
	  if (map != mouseBinding_.end())
	    switch (map.data().handler)
	      {
	      case CAMERA :
		camera()->frame()->startAction(map.data().action, map.data().withConstraint);
		camera()->frame()->mousePressEvent(e, camera());
		if (map.data().action == SCREEN_ROTATE)
		  updateGL();
		break;
	      case FRAME :
		if (manipulatedFrame())
		  {
		    if (manipulatedFrameIsACamera_)
		      {
			manipulatedFrame()->ManipulatedFrame::startAction(map.data().action, map.data().withConstraint);
			manipulatedFrame()->ManipulatedFrame::mousePressEvent(e, camera());
		      }
		    else
		      {
			manipulatedFrame()->startAction(map.data().action, map.data().withConstraint);
			manipulatedFrame()->mousePressEvent(e, camera());
		      }
		    if (map.data().action == SCREEN_ROTATE)
		      updateGL();
		  }
		break;
	      }
#if QT_VERSION >= 300
	  else
	    e->ignore();
#endif
	}
    }
}

/*! Maintaining a button pressed while moving the mouse updates the camera or the manipulated frame.
  The different possible actions (see MouseAction) are binded to mouse
  buttons using setMouseBinding().

  If you want to define your \e own mouse behavior, do something like this :
  \code
  void Viewer::mousePressEvent(QMouseEvent* e)
  {
  // Qt::KeyButtonMask separates the Control/Alt/Shift state key from the mouse (left/middle/right) buttons
  if ((e->state() & Qt::KeyButtonMask) == (Your personal Qt::ShiftButton/Qt::ControlButton/Qt::AltButton combination))
    myMouseBehavior = true;
  else
    QGLViewer::mousePressEvent(e);
  }

  void Viewer::mouseMoveEvent(QMouseEvent *e)
  {
  if (myMouseBehavior)
    // Use e->x() and e->y() as you want...
  else
    QGLViewer::mouseMoveEvent(e);
  }

  void Viewer::mouseReleaseEvent(QMouseEvent* e)
  {
  if (myMouseBehavior)
    myMouseBehavior = false;
  else
    QGLViewer::mouseReleaseEvent(e);
  }
  \endcode

 Many other event handlers can be customized : mouseDoubleClickEvent(), wheelEvent(),
 mouseReleaseEvent()... See the Qt::QWidget protected members documentation for a complete list. */
void QGLViewer::mouseMoveEvent(QMouseEvent* e)
{
  if (mouseGrabber())
    {
      mouseGrabber()->checkIfGrabsMouse(e->x(), e->y(), camera());
      if (mouseGrabber()->grabsMouse())
	if (mouseGrabberIsAManipulatedCameraFrame_)
#if QT_VERSION < 300
	  (static_cast<ManipulatedFrame*>(mouseGrabber()))->ManipulatedFrame::mouseMoveEvent(e, camera());
#else
	  (dynamic_cast<ManipulatedFrame*>(mouseGrabber()))->ManipulatedFrame::mouseMoveEvent(e, camera());
#endif
	else
	  mouseGrabber()->mouseMoveEvent(e, camera());
      else
	setMouseGrabber(NULL);
      updateGL();
    }
  
  if (!mouseGrabber())
    {
      //#CONNECTION# mouseReleaseEvent has the same structure
      if (camera()->isManipulated())
	{
	  camera()->frame()->mouseMoveEvent(e, camera());
	  // #CONNECTION# manipulatedCameraFrame::mouseMoveEvent specific if at the beginning
	  if (camera()->frame()->action_ == ZOOM_ON_REGION)
	    updateGL();
	}
      else // !
	if ((manipulatedFrame()) && (manipulatedFrame()->isManipulated()))
	  if (manipulatedFrameIsACamera_)
	    manipulatedFrame()->ManipulatedFrame::mouseMoveEvent(e, camera());
	  else
	    manipulatedFrame()->mouseMoveEvent(e, camera());
	else
	  if (hasMouseTracking())
	    {
	      QPtrListIterator<MouseGrabber> it(MouseGrabber::MouseGrabberPool());
	      for (MouseGrabber* mg; (mg = it.current()); ++it)
		{
		  mg->checkIfGrabsMouse(e->x(), e->y(), camera());
		  if (mg->grabsMouse())
		    {
		      setMouseGrabber(mg);
		      updateGL();
		      break;
		    }
		}
	    }
    }
  
#if QT_VERSION < 300
  // Patch for manipulated signal problem with Qt 2.3
  // Better than to connect manipulated() with all viewers, as had to be done with spinned().
  updateGL();
#endif
}

/*! When the user releases the mouse button, the camera (or the manipulatedFrame) action is stopped.

See the mouseMoveEvent() documentation for an example of mouse behavior customization. */
void QGLViewer::mouseReleaseEvent(QMouseEvent* e)
{
  if (mouseGrabber())
    {
      if (mouseGrabberIsAManipulatedCameraFrame_)
#if QT_VERSION < 300
	(static_cast<ManipulatedFrame*>(mouseGrabber()))->ManipulatedFrame::mouseReleaseEvent(e, camera());
#else
	(dynamic_cast<ManipulatedFrame*>(mouseGrabber()))->ManipulatedFrame::mouseReleaseEvent(e, camera());
#endif
      else
	mouseGrabber()->mouseReleaseEvent(e, camera());
      mouseGrabber()->checkIfGrabsMouse(e->x(), e->y(), camera());
      if (!(mouseGrabber()->grabsMouse()))
	setMouseGrabber(NULL);
      // updateGL();
    }
  else
    //#CONNECTION# mouseMoveEvent has the same structure
    if (camera()->isManipulated())
      {
	// bool updateGLNeeded = ((camera()->frame()->action_ == ZOOM_ON_REGION) ||
			       // (camera()->frame()->action_ == SCREEN_ROTATE));
	camera()->frame()->mouseReleaseEvent(e, camera());
	// if (updateGLNeeded)
	// Needed in all cases because of fastDraw().
	// updateGL();
      }
    else
      if ((manipulatedFrame()) && (manipulatedFrame()->isManipulated()))
	{
	  // bool updateGLNeeded = (manipulatedFrame()->action_ == SCREEN_ROTATE);
	  if (manipulatedFrameIsACamera_)
	    manipulatedFrame()->ManipulatedFrame::mouseReleaseEvent(e, camera());
	  else
	    manipulatedFrame()->mouseReleaseEvent(e, camera());
	  // if (updateGLNeeded)
	    // updateGL();
	}
#if QT_VERSION >= 300
      else
	e->ignore();
#endif
  
  // Not absolutely needed (see above commented code for the optimal version), but may reveal
  // useful for specific applications.
  updateGL();
}

/*! The wheel associated event is controled using setWheelBinding(). Default behavior simulates a
  ZOOM action. See the <a href="../mouse.html">QGLViewer mouse page</a> and
  setWheelBinding() for details.

  Depending on your system configuration, you may have to actually \e press the wheel while wheeling. */
void QGLViewer::wheelEvent(QWheelEvent* e)
{
  if (mouseGrabber())
    {
      if (mouseGrabberIsAManipulatedFrame_)
	{
	  for (QMap<Qt::ButtonState, MouseActionPrivate>::ConstIterator it=wheelBinding_.begin(), end=wheelBinding_.end(); it!=end; ++it)
	    if (it.data().handler == FRAME)
	      {
#if QT_VERSION < 300
		ManipulatedFrame* mf = static_cast<ManipulatedFrame*>(mouseGrabber());
#else
		ManipulatedFrame* mf = dynamic_cast<ManipulatedFrame*>(mouseGrabber());
#endif
		if (mouseGrabberIsAManipulatedCameraFrame_)
		  {
		    mf->ManipulatedFrame::startAction(it.data().action, it.data().withConstraint);
		    mf->ManipulatedFrame::wheelEvent(e, camera());
		  }
		else
		  {
		    mf->startAction(it.data().action, it.data().withConstraint);
		    mf->wheelEvent(e, camera());
		  }
		break;
	      }
	}
      else
	mouseGrabber()->wheelEvent(e, camera());
      updateGL();
    }
  else
    {
      //#CONNECTION# mousePressEvent has the same structure
      const QMap<Qt::ButtonState, MouseActionPrivate>::ConstIterator map = wheelBinding_.find(e->state());
      if (map != wheelBinding_.end())
	switch (map.data().handler)
	  {
	  case CAMERA :
	    camera()->frame()->startAction(map.data().action, map.data().withConstraint);
	    camera()->frame()->wheelEvent(e, camera());
	    break;
	  case FRAME :
	    if (manipulatedFrame())
	      if (manipulatedFrameIsACamera_)
		{
		  manipulatedFrame()->ManipulatedFrame::startAction(map.data().action, map.data().withConstraint);
		  manipulatedFrame()->ManipulatedFrame::wheelEvent(e, camera());
		}
	      else
		{
		  manipulatedFrame()->startAction(map.data().action, map.data().withConstraint);
		  manipulatedFrame()->wheelEvent(e, camera());
		}
	    break;
	  }
#if QT_VERSION >= 300
      else
	e->ignore();
#endif
    }

#if QT_VERSION < 300
  // Patch for manipulated signal problem with Qt 2.3
  // Better than to connect manipulated() with all viewers, as had to be done with spinned().
  updateGL();
#endif
}

/*! The behavior of the mouse double click depends on the current mouse binding. See
setMouseBinding() and the <a href="../mouse.html">QGLViewer mouse page</a>. */
void QGLViewer::mouseDoubleClickEvent(QMouseEvent* e)
{
  if (mouseGrabber())
    mouseGrabber()->mouseDoubleClickEvent(e, camera());
  else
    {
      //#CONNECTION# mousePressEvent has the same structure
      ClickActionPrivate cap;
      cap.doubleClick = true;
      // Warning : with Qt < 3.1, the definition of Qt::KeyButtonMask is erroneous
      cap.buttonState = (Qt::ButtonState)((e->state() & Qt::KeyButtonMask) |
					  ((e->stateAfter() & Qt::MouseButtonMask) & (~(e->state() & Qt::MouseButtonMask))));
      cap.buttonBefore = (Qt::ButtonState)(e->state() & Qt::MouseButtonMask);
      const QMap<ClickActionPrivate, ClickAction>::ConstIterator ca = clickBinding_.find(cap);
      if (ca != clickBinding_.end())
	performClickAtion(ca.data(), e);
#if QT_VERSION >= 300
      else
	e->ignore();
#endif
    }
  updateGL();
}

/*! Activates stereo mode (resp. switch back to mono when \p flag is false). Checks if the display
  system is able to handle stereovision using QGLWidget::format(). Should be called in init() or
  toggled with the STEREO shortcut key (default key is 'S', see toggleStereoDisplay() and
  setShortcutKey()). Get current value from displaysInStereo().
 
  The QGLViewer instance must be created with a stereo format to handle stereovision:
  \code
  QGLFormat format;
  format.setStereoDisplay( TRUE );
  QGLViewer viewer(format);
  \endcode
  See the <a href="../examples/stereoViewer.html">stereoViewer</a> example.

  The stereo parameters are defined by the camera(). See qglviewer::Camera::setIODist(),
  qglviewer::Camera::setDistanceToScreen(), qglviewer::Camera::setDistanceToZeroParallaxPlane() and
  qglviewer::Camera::setPhysicalScreenWidth(). */
void QGLViewer::setStereoDisplay(bool s)
{
  if (format().stereo()) 
    {
      stereo_ = s;
      if (!displaysInStereo())
	{
	  glDrawBuffer(GL_BACK_LEFT);
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	  glDrawBuffer(GL_BACK_RIGHT);
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
    }
  else
    if (s)
      QMessageBox::warning(this, "Stereo not supported", "Stereo is not supported on this display");
    else
      stereo_ = false;
  
  emit stereoChanged(stereo_);
  if (initializationStage_==3)
    updateGL();
}

/*! Viewer is toggled between normal and full screen mode (FULL_SCREEN shortcut key, default is
Alt-Enter, see the <a href="../shortcuts.html">QGLViewer shortcuts page</a>). See setFullScreen() and isFullScreen(). */
void QGLViewer::toggleFullScreen()
{
  setFullScreen(!isFullScreen());
}

/*! Viewer is set in full screen mode (\p fs = \c true, default) or not (\p fs = \c false). Get
current value with isFullScreen(). See also toggleFullScreen() and the STEREO shortcut key (default
is 'S', see the <a href="../shortcuts.html">QGLViewer shortcuts page</a>). */
void QGLViewer::setFullScreen(bool fs)
{
  fullScreen_ = fs;

  if (initializationStage_ != 3)
    return;

  QWidget* rootWidget_ = rootWidget();
  
  if (isFullScreen())
    {
      prevPos_ = rootWidget_->pos();
      rootWidget_->showFullScreen();
      rootWidget_->move(0,0);
    }
  else
    {
      rootWidget_->showNormal();
      rootWidget_->move(prevPos_);
    }
}

/*! Directly defines the QGLViewer's mouseGrabber(). You should not call this function directly as
mouseMoveEvent() already does it using qglviewer::MouseGrabber::checkIfGrabsMouse(). */
void QGLViewer::setMouseGrabber(MouseGrabber* mg)
{
  mouseGrabber_ = mg;
#if QT_VERSION < 300
  mouseGrabberIsAManipulatedFrame_       = true;
  mouseGrabberIsAManipulatedCameraFrame_ = false;
#else
  mouseGrabberIsAManipulatedFrame_       = (dynamic_cast<ManipulatedFrame*>(mouseGrabber()) != NULL);
  mouseGrabberIsAManipulatedCameraFrame_ = ((dynamic_cast<ManipulatedCameraFrame*>(mouseGrabber()) != NULL) &&
					    (mouseGrabber() != camera()->frame()));
#endif
}

static QString buttonStateKeyString(Qt::ButtonState s, bool noButton=false)
{
  QString result("");
  if (s & Qt::ControlButton) 	result += "Ctrl+";
  if (s & Qt::AltButton) 	result += "Alt+";
  if (s & Qt::ShiftButton) 	result += "Shift+";
#if QT_VERSION >= 300
  if (s & Qt::MetaButton) 	result += "Meta+";
#endif
  if (noButton && (s==Qt::NoButton)) result += "(no button)";
  return result;
}

static QString buttonStateButtonString(Qt::ButtonState s)
{
  QString result("");
  int nb = 0;
  if (s & Qt::LeftButton)    { result += "Left"; nb++; }
  if (s & Qt::MidButton)     { if (nb) result += " & "; result += "Middle"; nb++; }
  if (s & Qt::RightButton)   { if (nb) result += " & "; result += "Right"; nb++; }
  if (nb > 0) result += " button";
  if (nb > 1) result += "s";
  return result;
}

QString QGLViewer::mouseActionString(QGLViewer::MouseAction ma)
{
  switch (ma)
    {
    case QGLViewer::NO_MOUSE_ACTION : 	return QString("No action"); break;
    case QGLViewer::ROTATE: 		return QString("Rotates"); break;
    case QGLViewer::ZOOM: 		return QString("Zooms"); break;
    case QGLViewer::TRANSLATE: 		return QString("Translates"); break;
    case QGLViewer::MOVE_FORWARD: 	return QString("Moves forward"); break;
    case QGLViewer::LOOK_AROUND: 	return QString("Looks around"); break;
    case QGLViewer::MOVE_BACKWARD: 	return QString("Moves backward"); break;
    case QGLViewer::SCREEN_ROTATE: 	return QString("Screen rotates"); break;
    case QGLViewer::SCREEN_ROTATE_BOTTOM:return QString("Screen rotates bottom"); break;
    case QGLViewer::SCREEN_TRANSLATE: 	return QString("Screen translates"); break;
    case QGLViewer::ZOOM_ON_REGION: 	return QString("Zooms on region for"); break;
    }
  return QString::null;
}

QString QGLViewer::clickActionString(QGLViewer::ClickAction ca)
{
  switch (ca)
    {
    case QGLViewer::NO_CLICK_ACTION : 	return QString("No action");		break;
    case QGLViewer::ZOOM_ON_PIXEL : 	return QString("Zooms on pixel");	break;
    case QGLViewer::ZOOM_TO_FIT : 	return QString("Zooms to fit scene");	break;
    case QGLViewer::SELECT : 		return QString("Selects");		break;
    case QGLViewer::RAP_FROM_PIXEL : 	return QString("RAP from pixel");	break;
    case QGLViewer::RAP_IS_CENTER : 	return QString("RAP set to center");	break;
    case QGLViewer::CENTER_FRAME : 	return QString("Centers frame");	break;
    case QGLViewer::CENTER_SCENE : 	return QString("Centers scene");	break;
    case QGLViewer::SHOW_ENTIRE_SCENE : return QString("Shows entire scene");	break;
    case QGLViewer::ALIGN_FRAME : 	return QString("Aligns frame");		break;
    case QGLViewer::ALIGN_CAMERA : 	return QString("Aligns camera");	break;
    }
  return QString::null;
}

static QString keyString(const Qt::Key& key)
{
  switch (key)
    {
    case Qt::Key_Escape : 	return QString("Escape"); break;
    case Qt::Key_Tab : 		return QString("Tab"); break;
    case Qt::Key_Backtab : 	return QString("Backtab"); break;
    case Qt::Key_Backspace : 	return QString("Backspace"); break;
    case Qt::Key_Return : 	return QString("Return"); break;
    case Qt::Key_Enter : 	return QString("Enter"); break;
    case Qt::Key_Insert : 	return QString("Insert"); break;
    case Qt::Key_Delete : 	return QString("Delete"); break;
    case Qt::Key_Pause : 	return QString("Pause"); break;
    case Qt::Key_Print : 	return QString("Print"); break;
    case Qt::Key_SysReq : 	return QString("SysReq"); break;
    case Qt::Key_Home : 	return QString("Home"); break;
    case Qt::Key_End : 		return QString("End"); break;
    case Qt::Key_Left : 	return QString("Left"); break;
    case Qt::Key_Up : 		return QString("Up"); break;
    case Qt::Key_Right : 	return QString("Right"); break;
    case Qt::Key_Down : 	return QString("Down"); break;
    case Qt::Key_Prior : 	return QString("Prior"); break;
    case Qt::Key_Next : 	return QString("Next"); break;
    case Qt::Key_Shift : 	return QString("Shift"); break;
    case Qt::Key_Control : 	return QString("Control"); break;
    case Qt::Key_Meta : 	return QString("Meta"); break;
    case Qt::Key_Alt : 		return QString("Alt"); break;
    case Qt::Key_CapsLock : 	return QString("CapsLock"); break;
    case Qt::Key_NumLock : 	return QString("NumLock"); break;
    case Qt::Key_ScrollLock : 	return QString("ScrollLock"); break;
    case Qt::Key_F1  : 		return QString("F1");  break;
    case Qt::Key_F2  : 		return QString("F2");  break;
    case Qt::Key_F3  : 		return QString("F3");  break;
    case Qt::Key_F4  : 		return QString("F4");  break;
    case Qt::Key_F5  : 		return QString("F5");  break;
    case Qt::Key_F6  : 		return QString("F6");  break;
    case Qt::Key_F7  : 		return QString("F7");  break;
    case Qt::Key_F8  : 		return QString("F8");  break;
    case Qt::Key_F9  : 		return QString("F9");  break;
    case Qt::Key_F10 : 		return QString("F10"); break;
    case Qt::Key_F11 : 		return QString("F11"); break;
    case Qt::Key_F12 : 		return QString("F12"); break;
    case Qt::Key_Space : 	return QString("Space"); break;
    default : return QString(QChar(key));
    }
}

/*! Returns a QString that describes the application mouse bindings, and that will be displayed
  in one of the help() window tabs. Default value is a table that describes all the current mouse
  bindings. See setMouseBinding(), setWheelBinding() and the
  <a href="../mouse.html">QGLViewer mouse page</a> for details on mouse bindings.

  Overload this function to add your application specific mouse bindings. See
  shortcutBindingsString() for a complete example.

  A QString::null value will suppress the "Shortcuts" tab in help(). */
QString QGLViewer::mouseBindingsString() const
{
#if QT_VERSION < 300
  QString text("");
  const QString trtd("");
  const QString tdtr("<br>");
  const QString tdtd(" ");
#else
  QString text("<table>");
  const QString trtd("<tr><td>");
  const QString tdtr("</td></tr>");
  const QString tdtd("</td><td>");
#endif
  
  for (QMap<Qt::ButtonState, MouseActionPrivate>::ConstIterator it=mouseBinding_.begin(), end=mouseBinding_.end(); it != end; ++it)
    {
      text += trtd + "<b>" + buttonStateKeyString(it.key()) + buttonStateButtonString(it.key()) + "</b>" + tdtd;
      text += mouseActionString(it.data().action) + " ";
      switch (it.data().handler)
	{
	case CAMERA: text += "camera"; break;
	case FRAME:  text += "frame"; break;
	}
      if (!(it.data().withConstraint))
	text += "*"; 

      text += tdtr;
    }

  for (QMap<Qt::ButtonState, MouseActionPrivate>::ConstIterator itw=wheelBinding_.begin(), endw=wheelBinding_.end(); itw != endw; ++itw)
    {
      text += trtd + "<b>" + buttonStateKeyString(itw.key()) + buttonStateButtonString(itw.key()) + "wheel</b>" + tdtd;
      text += mouseActionString(itw.data().action) + " ";
      switch (itw.data().handler)
	{
	case CAMERA: text += "camera"; break;
	case FRAME:  text += "frame"; break;
	}
      if (!(itw.data().withConstraint))
	text += "*"; 

      text += tdtr;
    }

  for (QMap<ClickActionPrivate, ClickAction>::ConstIterator itca=clickBinding_.begin(), endca=clickBinding_.end(); itca != endca; ++itca)
    {
      text += trtd + "<b>";
      if (itca.key().buttonBefore != Qt::NoButton)
	text += buttonStateButtonString(itca.key().buttonBefore) + " + ";
      text += buttonStateKeyString(itca.key().buttonState) + buttonStateButtonString(itca.key().buttonState);
      if (itca.key().doubleClick)
	text += " double";
      text +=  " click</b>" + tdtd;
      text += clickActionString(itca.data());
      text += tdtr;
    }

#if QT_VERSION >= 300
  text += "</table>";
#endif
  return text;
}

/*! Returns a QString that describes the application shortcut bindings, and that will be displayed
  in one of the help() window tabs. Default value is a table that describes all the current key
  bindings. See setShortcutKey(), setShortcutStateKey() and the
  <a href="../shortcuts.html">QGLViewer shortcuts page</a> for details on shortcut bindings.

  Overload this function to add your application specific key bindings.
  \code
  QString myViewer::shortcutBindingsString() const
  {
    QString text("<table>");
    text += "<tr><td><b>Ctrl+O</b></td><td>Opens a new window</td></tr>";
    text += "<tr><td><b>W</b></td><td>Adds a watermelon</td></tr>";
    text += "</table>\n<hr>";

    // Add default key bindings
    text += QGLViewer::shortcutBindingsString();
    return text;
  }
  \endcode

  A QString::null value will suppress the "Shortcuts" tab in help(). */
QString QGLViewer::shortcutBindingsString() const
{
  QMap<ShortcutAction, QString> description;

  //#CONNECTION# ShortcutAction definition
  description[DISPLAY_FPS] = 	"Toggles the display of the FPS.";
  description[DISPLAY_Z_BUFFER]="Toggles the display of the z-buffer.";
  description[SAVE_SCREENSHOT]=	"Saves a screenshot.";
  description[FULL_SCREEN] = 	"Toggles full screen display";
  description[DRAW_AXIS] = 	"Toggles the display of the world axis.";
  description[DRAW_GRID] = 	"Toggles the display of the XY grid.";
  description[CAMERA_MODE] = 	"Changes camera mode (revolve or fly)";
  description[STEREO] = 	"Toggles stereo display";
  description[HELP] = 		"Opens this help window";
  description[ANIMATION] = 	"Starts/stops the animation";
  description[EDIT_CAMERA_PATHS]="Toggles camera path display"; // TODO change
  description[ENABLE_TEXT] = 	"Toggles the display of the text.";
  description[EXIT] = 		"Exits program";

#if QT_VERSION < 300
  QString message("");
  for (QMap<ShortcutAction, QString>::Iterator it=description.begin(), end=description.end(); it != end; ++it)
    if (shortcutKey_[it.key()] != 0)
      message += "<b>" + buttonStateKeyString(shortcutStateKey_[it.key()]) + keyString(shortcutKey_[it.key()]) + "</b> " + it.data() + "<br>";
#else
  QString message("<table>");
  for (QMap<ShortcutAction, QString>::Iterator it=description.begin(), end=description.end(); it != end; ++it)
    if (shortcutKey_[it.key()] != 0)
      message += "<tr><td><b>" + buttonStateKeyString(shortcutStateKey_[it.key()]) + keyString(shortcutKey_[it.key()])
	+ "</b></td><td>" + it.data() + "</td></tr>";
  message += "</table>";
#endif
 
  return message;
}


/*! This function is called when the user presses the HELP_KEY (default is H). It opens a modal help
  window that includes three tabs, which are respectively filled with the results of helpString(),
  shortcutBindingsString() and mouseBindingsString(). If one of these is QString::null, the
  associated tab is not created. Overload these functions to define you own help text. Rich
  html-like text can be used.

  Set the HELP_KEY shortcut key to 0 to disable the help window (see setShortcutKey()).

  The helpRequired() signal is emitted. */
void QGLViewer::help()
{
  QTabDialog* helpDialog = new QTabDialog(this, "Help window");
  const int width = 600;
#if QT_VERSION < 300
  // Problem : heightForWidth always return 0
  int height = 400;
#else
  int height = 0;
#endif

  QTextEdit** textEdits = new QTextEdit*[3];
  for (int i=0; i<3; ++i)
    {
      textEdits[i] = new QTextEdit(helpDialog);
#if QT_VERSION >= 300
      textEdits[i]->setReadOnly(true);
#endif
      textEdits[i]->setTextFormat(Qt::RichText);
      QString tab, text;
      switch (i)
	{
	case 0 : text = helpString();			tab = "&Help"; break;
	case 1 : text = shortcutBindingsString();	tab = "&Shortcuts"; break;
	case 2 : text = mouseBindingsString();		tab = "&Mouse"; break;
	default : break;
	}
      
      if (text == QString::null)
	delete textEdits[i];
      else
	{
	  textEdits[i]->append(text);
      
	  if (textEdits[i]->heightForWidth(width) > height)
	    height = textEdits[i]->heightForWidth(width);
	  helpDialog->addTab(textEdits[i], tab);
	}
    }
  
  helpDialog->show();
  if (height > 800)
    height = 800;
  // Take tabBar and button heights into account
  helpDialog->resize(width, height + 90);

  emit helpRequired();
}

/*! Key pressed callback function. Some default key bindings are implemented and can easily be
  redefined using setShortcutKey() and setShortcutStateKey(). See the
  <a href="../shortcuts.html">QGLViewer shortcuts page</a> for details and default values.

  Overload this function to implement a specific shortcut key binding for one of your application
  function. You should call the original function in the default case of your switch to preserve
  the default viewer key bindings :
  \code
  void Viewer::keyPressEvent(QKeyEvent *e)
  {
  switch (e->key())
  {
  case Qt::Key_R : reset(); updateGL(); break;
  // and so on...
  default: QGLViewer::keyPressEvent(e);
  }
  }
  \endcode

  Consider testing the modifier keys for more complex behaviors:
  \code
  const Qt::ButtonState state = (Qt::ButtonState)(e->state() & Qt::KeyButtonMask);
  if (state == Qt::AltButton)
  switch (e->key())
  {
  ...
  }
  else
  ...
  \endcode */
void QGLViewer::keyPressEvent(QKeyEvent *e)
{
  bool handled = false;
  const int key = e->key();
  const Qt::ButtonState state = (Qt::ButtonState)(e->state() & Qt::KeyButtonMask);

  /* */if ((key==shortcutKey_[DRAW_AXIS]) 	&& (state==shortcutStateKey_[DRAW_AXIS]))
    { handled=true; toggleDrawAxis();}
  else if ((key==shortcutKey_[DRAW_GRID]) 	&& (state==shortcutStateKey_[DRAW_GRID]))
    { handled=true; toggleDrawGrid(); }
  else if ((key==shortcutKey_[DISPLAY_FPS]) 	&& (state==shortcutStateKey_[DISPLAY_FPS]))
    { handled=true; toggleDisplayFPS(); }
  else if ((key==shortcutKey_[DISPLAY_Z_BUFFER])&& (state==shortcutStateKey_[DISPLAY_Z_BUFFER]))
    { handled=true; toggleDisplayZBuffer(); }
  else if ((key==shortcutKey_[ENABLE_TEXT]) 	&& (state==shortcutStateKey_[ENABLE_TEXT]))
    { handled=true; toggleEnableText(); }
  else if ((key==shortcutKey_[EXIT]) 		&& (state==shortcutStateKey_[EXIT]))
    { handled=true; saveToFileForAllViewers(); qApp->closeAllWindows(); }
  else if ((key==shortcutKey_[SAVE_SCREENSHOT]) && (state==shortcutStateKey_[SAVE_SCREENSHOT]))
    { handled=true; saveSnapshot(false, false); }
  else if ((key==shortcutKey_[CAMERA_MODE]) 	&& (state==shortcutStateKey_[CAMERA_MODE]))
    { handled=true; toggleCameraMode(); }
  else if ((key==shortcutKey_[FULL_SCREEN]) 	&& (state==shortcutStateKey_[FULL_SCREEN]))
    { handled=true; toggleFullScreen(); }
  else if ((key==shortcutKey_[STEREO]) 		&& (state==shortcutStateKey_[STEREO]))
    { handled=true; toggleStereoDisplay(); }
  else if ((key==shortcutKey_[ANIMATION]) 	&& (state==shortcutStateKey_[ANIMATION]))
    { handled=true; toggleAnimationMode(); }
  else if ((key==shortcutKey_[HELP]) 		&& (state==shortcutStateKey_[HELP]))
    { handled=true; help(); }
  else if ((key==shortcutKey_[EDIT_CAMERA_PATHS]) && (state==shortcutStateKey_[EDIT_CAMERA_PATHS]))
    { handled=true; toggleCameraPathEditor(); }

  static QTime doublePress;

  if (state == playKFStateKey_)
    {
      for (unsigned short i=0; i<camera()->nbPaths(); ++i)
	if (key == keyFrameKey_[i])
	  {
	    int elapsed = doublePress.restart();
	    if (elapsed < 250)
	      camera()->resetKeyFramePath(i);
	    else
	      camera()->playKeyFramePath(i);
	    handled=true;
	    updateGL();
	    break; // for loop
	  }
    }
  else if (state == addKFStateKey_)
    {
      for (unsigned short i=0; i<camera()->nbPaths(); ++i)
	if (key == keyFrameKey_[i])
	  {
	    int elapsed = doublePress.restart();
	    if (elapsed < 250)
	      {
		disconnect(camera()->keyFrameInterpolator(i), SIGNAL(interpolated()), this, SLOT(updateGL()));
		camera()->deleteKeyFramePath(i);
	      }
	    else
	      {
		bool nullBefore = (camera()->keyFrameInterpolator(i) == NULL);
		camera()->addKeyFrame(i);
		if (nullBefore)
		  connect(camera()->keyFrameInterpolator(i), SIGNAL(interpolated()), SLOT(updateGL()));
	      }
	    handled=true;
	    updateGL();
	    break; // for loop
	  }
    }

  if ((state == Qt::NoButton) || (e->state() == Qt::Keypad))
    {
      bool arrowPressed = true;
      switch (key)
	{
	case Qt::Key_Left  : camera()->frame()->translate(camera()->frame()->inverseTransformOf(Vec(-10.0*camera()->flySpeed(), 0.0, 0.0))); break;
	case Qt::Key_Right : camera()->frame()->translate(camera()->frame()->inverseTransformOf(Vec( 10.0*camera()->flySpeed(), 0.0, 0.0))); break;
	case Qt::Key_Up    : camera()->frame()->translate(camera()->frame()->inverseTransformOf(Vec(0.0,  10.0*camera()->flySpeed(), 0.0))); break;
	case Qt::Key_Down  : camera()->frame()->translate(camera()->frame()->inverseTransformOf(Vec(0.0, -10.0*camera()->flySpeed(), 0.0))); break;
	default: arrowPressed = false;
	}
      
      if (arrowPressed)
	{
	  updateGL();
	  handled = true;
	}
    }
  
  if (e->state() == Qt::Keypad)
    switch (key)
      {
      case Qt::Key_Plus  : camera()->setFlySpeed(camera()->flySpeed() * 1.5); handled = true; break;
      case Qt::Key_Minus : camera()->setFlySpeed(camera()->flySpeed() / 1.5); handled = true; break;
      default: break;
      }
    
  if (!handled)
    e->ignore();
}

/*! Called when the window size is modified.
  If you override this function, be very careful to call first the inherited method.
  \code
  void Viewer::resizeGL( int w, int h )
  {
  QGLViewer::resizeGL(w,h);
  // ...
  }
  \endcode */
void QGLViewer::resizeGL( int w, int h )
{
  QGLWidget::resizeGL(w,h);
  glViewport( 0, 0, GLint(w), GLint(h) );
  camera()->setWindowWidthAndHeight(width(),height());
}

////////////////////////////////////////////////////////////////////////////////
//              S h o r t c u t   k e y   d e f i n i t i o n                 //
////////////////////////////////////////////////////////////////////////////////
// Standard shortcut keys
/*! Defines the shortcut key (and optionnally the state key) associated with a given action of the
  viewer. All the possible \p action are defined by the QGLViewer::ShortcutAction enum.

  \p key is defined by the Qt::Key enum and is of the form Qt::Key_X (see the Qt documentation). Set
  the \p key to \p 0 to forbid the action shortcut. \p stateKey (optional) defines the state key
  (Alt, Control, ...) associated with this action, just like setShortcutStateKey().

  Use setShortcutStateKey() to define a shortcut state key and shortcutKey() to get the current
  value. See also setKeyFrameKey() and setMouseStateKey().

  For example, this code defines 'Ctrl-Alt-F' as the new toggleFullScreen() shortcut, 'Q' as the new
  \c EXIT shortcut key (state key unchanged) and forbids the toggleDisplayZBuffer() shortcut:
  \code
  setShortcutKey (QGLViewer::FULL_SCREEN, Qt::Key_F, Qt::AltButton | Qt::ControlButton);
  setShortcutKey (QGLViewer::EXIT, Qt::Key_Q);
  setShortcutKey (QGLViewer::DISPLAY_Z_BUFFER, 0);
  \endcode

  See the <a href="../shortcuts.html">QGLViewer shortcuts page</a> for details and default values.
  See the <a href="../examples/keyboardAndMouse.html">keyboardAndMouse</a> example for a practical
  illustration. */
void QGLViewer::setShortcutKey(ShortcutAction action, int key, int stateKey)
{
  shortcutKey_[action] = (Qt::Key)key;
  if (stateKey >= 0)
    shortcutStateKey_[action] = (Qt::ButtonState)stateKey;
}

/*! Defines the shortcut state key (Qt::AltButton, Qt::ShiftButton, Qt::ControlButton) that should be pressed while pressing a
  given action shortcutKey(). All the possible actions are defined by the ShortcutAction enum.

  The state key can be set to \p Qt::NoButton, \p Qt::ControlButton, \p Qt::ShiftButton, \p
  Qt::AltButton, or a combination of these (use the bit '|' operator, see setMouseStateKey()).

  For example, this code defines Ctrl-Alt-F as the new toggleFullScreen() shortcut:
  \code
  setShortcutKey      (QGLViewer::FULL_SCREEN, Qt::Key_F);
  setShortcutStateKey (QGLViewer::FULL_SCREEN, Qt::ControlButton | Qt::AltButton);
  \endcode
  
  Use setShortcutKey() to define the shortcut key and shortcutStateKey() to get the current value.
  See also setKeyFrameKey(), setAddKeyFrameStateKey(), setPlayKeyFramePathStateKey() and setMouseStateKey().

  See the <a href="../shortcuts.html">QGLViewer shortcuts page</a> for details and default
  values. */
void QGLViewer::setShortcutStateKey(ShortcutAction action, int buttonState)
{ shortcutStateKey_[action] = (Qt::ButtonState)(buttonState & Qt::KeyButtonMask); }

/*! Returns the current shortcut value as defined with setShortcutKey().
  \p action is defined by the QGLViewer::ShortcutAction enum.
  
  See the <a href="../shortcuts.html">QGLViewer shortcuts page</a> for details and default
  values. */
Qt::Key QGLViewer::shortcutKey(ShortcutAction action) const
{ return shortcutKey_[action]; }

/*! Returns the current shortcut state value as defined with setShortcutKey().
  \p action is defined by the QGLViewer::ShortcutAction enum.

  See the <a href="../shortcuts.html">QGLViewer shortcuts page</a> for details and default
  values. */
Qt::ButtonState QGLViewer::shortcutStateKey(ShortcutAction action) const
{ return shortcutStateKey_[action]; }


///////     Key Frames shortcut keys       ///////

/*! Defines the shortcut key associated with the camera Key Frame path of index \p nb. The number of
  available indexes is returned by qglviewer::Camera::nbPaths(). The default keys are F1..F12 for indexes
  0..11.

  Use setAddKeyFrameStateKey() and setPlayKeyFramePathStateKey() to define the state key that must
  be pressed with this key to add (or delete) or play the Key Frame.

  To delete a Key Frame path, quickly press twice the keyFrameKey() while pressing the addKeyFrameStateKey().
  Once a path has been delete, trying to re-play the path (using keyFrameKey() and playKeyFramePathStateKey())
  will do nothing until new key frames are added (using keyFrameKey() and addKeyFrameStateKey()).
  
  Use setShortcutKey() to define other shortcut keys.

  See the <a href="../shortcuts.html">QGLViewer shortcuts page</a> for details. */
void QGLViewer::setKeyFrameKey(int nb, int key)
{ keyFrameKey_[nb] = (Qt::Key)key; }

/*! Defines the shortcut state key (Qt::AltButton, Qt::ShiftButton, Qt::ControlButton) that must be pressed in conjunction with the
  keyFrameKey(i) to add a Key Frame to the camera Key Frame path of index \p i. Default state key is
  Qt::AltButton.

  The state key can be set to \p Qt::NoButton, \p Qt::ControlButton, \p Qt::ShiftButton, \p
  Qt::AltButton, or a combination of these (use the bit '|' operator, see setMouseStateKey()).

  Use setKeyFrameKey() to define the associated Key Frame key. See also
  setPlayKeyFramePathStateKey().

  See the <a href="../shortcuts.html">QGLViewer shortcuts page</a> for details. */
void QGLViewer::setAddKeyFrameStateKey(int buttonState)
{ addKFStateKey_ = (Qt::ButtonState)(buttonState & Qt::KeyButtonMask); }

/*! Defines the shortcut state key (Qt::AltButton, Qt::ShiftButton, Qt::ControlButton) that must be pressed in conjunction with the
  keyFrameKey(i) to start playing the camera Key Frame path of index \p i. Default state key is
  Qt::NoButton.
  
  The state key can be set to \p Qt::NoButton, \p Qt::ControlButton, \p Qt::ShiftButton, \p
  Qt::AltButton, or a combination of these (use the bit '|' operator, see setMouseStateKey()).

  Use setKeyFrameKey() to define the associated Key Frame key. See also
  setAddKeyFrameStateKey().

  See the <a href="../shortcuts.html">QGLViewer shortcuts page</a> for details. */
void QGLViewer::setPlayKeyFramePathStateKey(int buttonState)
{ playKFStateKey_ = (Qt::ButtonState)(buttonState & Qt::KeyButtonMask); }

/*! Returns the camera Key Frame path shortcut key for index \p nb. \p nb should not exceed qglviewer::Camera::nbPaths().
  Default values are F1..F12 for indexes 0..11. See setKeyFrameKey() for details.

  See also addKeyFrameStateKey() and playKeyFramePathStateKey().
  
  See the <a href="../shortcuts.html">QGLViewer shortcuts page</a> for details. */
Qt::Key QGLViewer::keyFrameKey(int nb) const
{ return keyFrameKey_[nb]; }

/*! Returns the state key (Qt::AltButton, Qt::ShiftButton, Qt::ControlButton) that must be pressed
  with the keyFrameKey() to \e add a KeyFrame to a camera KeyFrame path. Default value is
  Qt::AltButton. See setAddKeyFrameStateKey() for details.

  See also keyFrameKey() and playKeyFramePathStateKey().
  
  See the <a href="../shortcuts.html">QGLViewer shortcuts page</a> for details. */
Qt::ButtonState QGLViewer::addKeyFrameStateKey() const
{ return addKFStateKey_; }

/*! Returns the state key (Qt::AltButton, Qt::ShiftButton, Qt::ControlButton) that must be pressed
  with the keyFrameKey() to \e play a camera KeyFrame path. Default value is Qt::NoButton. See
  setPlayKeyFramePathStateKey() for details.

  See also keyFrameKey() and addKeyFrameStateKey().
  
  See the <a href="../shortcuts.html">QGLViewer shortcuts page</a> for details. */
Qt::ButtonState QGLViewer::playKeyFramePathStateKey() const
{ return playKFStateKey_; }



////////////////////////////////////////////////////////////////////////////////
//              M o u s e   b e h a v i o r   s t a t e   k e y s             //
////////////////////////////////////////////////////////////////////////////////
/*! Associate a given state key (Alt, Shift, Control or a combinaison of these) to a specific
  MouseHandler. \e All the mouse handler's associated bindings will then need the specified \p
  buttonState key to be activated.

  With this code,
  \code
  setMouseStateKey(QGLViewer::CAMERA, Qt::AltButton);
  setMouseStateKey(QGLViewer::FRAME,  Qt::NoButton);
  \endcode
  you will have to press the \c Alt key while pressing mouse buttons in order to move the camera, while
  no key will be needed to move the associated manipulatedFrame().

  This function is provided for convenience but its implementation is basic. Indeed, \e every action
  binded to \p mh has its state keys \e replaced by \p buttonState. If the MouseHandler had some
  actions binded to different state keys, this setting will be lost. You should consider using
  setMouseBinding() for finer tuning.

  The default binding configuration binds \p Qt::ControlButton to all the QGLViewer::FRAME actions and
  Qt::NoButton to QGLViewer::CAMERA actions. This function hence easily allows you to change the MouseHandler associated key.

  \attention This function calls setMouseBinding(), which ensures that only \e one action is binded to
  a given buttonState. If you want to \e swap the CAMERA and FRAME state keys, you have to use a
  temporary dummy buttonState (as when you are swapping two variables) or else the first call will
  overwrite the previous settings :
  \code
  // Associate FRAME with Alt (temporary value)
  setMouseStateKey(QGLViewer::FRAME, Qt::Alt);
  // Control is associated with CAMERA
  setMouseStateKey(QGLViewer::CAMERA, Qt::ControlButton);
  // And finally, FRAME can be associated with NoButton
  setMouseStateKey(QGLViewer::FRAME, Qt::NoButton);
  \endcode

  If you had started with :
  \code
  setMouseStateKey(QGLViewer::FRAME, Qt::NoButton);
  \endcode
  the FRAME bindings would have replaced \e all the previous CAMERA bindings (as CAMERA uses \c NoButton by default). A call to :
  \code
  setMouseStateKey(QGLViewer::CAMERA, Qt::ControlButton);
  \endcode
  would then have done nothing as no more actions are binded to the CAMERA.

  See the <a href="../mouse.html">QGLViewer mouse page</a> for details. */
void QGLViewer::setMouseStateKey(MouseHandler mh, int buttonState)
{
  QMap<Qt::ButtonState, MouseActionPrivate> newMouseBinding;
  QMap<Qt::ButtonState, MouseActionPrivate> newWheelBinding;

  QMap<Qt::ButtonState, MouseActionPrivate>::Iterator it;

  // First copy unchanged bindings.
  for (it = mouseBinding_.begin(); it != mouseBinding_.end(); ++it)
    if ((it.data().handler != mh) || (it.data().action == ZOOM_ON_REGION))
      newMouseBinding[it.key()] = it.data();

  for (it = wheelBinding_.begin(); it != wheelBinding_.end(); ++it)
    if (it.data().handler != mh)
      newWheelBinding[it.key()] = it.data();

  // Then, add modified bindings, that can overwrite the previous ones.
  const Qt::ButtonState state = (Qt::ButtonState)(buttonState & Qt::KeyButtonMask);
  
  for (it = mouseBinding_.begin(); it != mouseBinding_.end(); ++it)
    if ((it.data().handler == mh) && (it.data().action != ZOOM_ON_REGION))
      {
	Qt::ButtonState newState = (Qt::ButtonState)(state | (it.key() & Qt::MouseButtonMask)); 
	newMouseBinding[newState] = it.data();
      }

  for (it = wheelBinding_.begin(); it != wheelBinding_.end(); ++it)
    if (it.data().handler == mh)
      {
	Qt::ButtonState newState = (Qt::ButtonState)(state | (it.key() & Qt::MouseButtonMask)); 
	newWheelBinding[newState] = it.data();
      }
  

  // Same for button bindings
  QMap<ClickActionPrivate, ClickAction> newClickBinding_;

  for (QMap<ClickActionPrivate, ClickAction>::ConstIterator cb=clickBinding_.begin(), end=clickBinding_.end(); cb != end; ++cb)
    if (((mh==CAMERA) && ((cb.data() == CENTER_SCENE) || (cb.data() == ALIGN_CAMERA))) ||
	((mh==FRAME)  && ((cb.data() == CENTER_FRAME) || (cb.data() == ALIGN_FRAME))))
      {
	ClickActionPrivate cap;
	cap.doubleClick = cb.key().doubleClick;
	cap.buttonState = (Qt::ButtonState)(state | (cb.key().buttonState & Qt::MouseButtonMask));
	cap.buttonBefore = (Qt::ButtonState)((~(state) & cb.key().buttonBefore) & Qt::MouseButtonMask);
	newClickBinding_[cap] = cb.data();
      }
    else
      newClickBinding_[cb.key()] = cb.data();
 
  mouseBinding_ = newMouseBinding;
  wheelBinding_ = newWheelBinding;
  clickBinding_ = newClickBinding_;
}

/*! This function lets you associate any MouseAction to any Qt::ButtonState mouse
  button and state key combination. The receiver of the mouse events is a MouseHandler (\c CAMERA or
  \c FRAME).

  The list of all possible MouseAction, some binding examples and
  default bindings are provided in the <a href="../mouse.html">mouse page</a>.

  See the <a href="../examples/keyboardAndMouse.html">keyboardAndMouse</a> example for an illustration.
  
  The parameters should read : when the \p buttonState mouse button and state key are pressed,
  activate \p action on \p handler. If \p withConstraint is \c true (default), the constraint
  associated with the frame will be enforced.
  
  If no mouse button is specified in \p buttonState, the binding will be ignored. If an action was
  previously associated with this buttonState, it is silently overwritten (use mouseAction() to know
  if the buttonState is already binded).
  
  To discard a specific mouse binding, use code like:
  \code
  setMouseBinding(myButtonStateKeyCombo, myHandler, NO_MOUSE_ACTION);
  \endcode

  See also setMouseBinding() and setWheelBinding(). */
void QGLViewer::setMouseBinding(int buttonState, MouseHandler handler, MouseAction action, bool withConstraint)
{
  if ((handler == FRAME) && ((action == MOVE_FORWARD) || (action == MOVE_BACKWARD) ||
			     (action == SCREEN_ROTATE_BOTTOM) || (action == LOOK_AROUND) ||
			     (action == ZOOM_ON_REGION)))
    qWarning("Cannot bind " + mouseActionString(action) + " to FRAME");
  else
    if ((buttonState & Qt::MouseButtonMask) == 0)
      qWarning("No mouse button specified in setMouseBinding");
    else
      {
	MouseActionPrivate map;
	map.handler = handler;
	map.action  = action;
	map.withConstraint  = withConstraint;
	mouseBinding_.replace((Qt::ButtonState)(buttonState), map);
	
	ClickActionPrivate cap;
	cap.buttonState = (Qt::ButtonState)(buttonState);
	cap.doubleClick = false;
	cap.buttonBefore = Qt::NoButton;
	clickBinding_.remove(cap);
      }
}

/*! This function lets you associate any ClickAction to any Qt::ButtonState mouse
  button and state key combination.

  The list of all possible ClickAction, some binding examples and default bindings are provided in
  the <a href="../mouse.html">mouse page</a>. See the
  <a href="../examples/keyboardAndMouse.html">keyboardAndMouse</a> example for an illustration.

  The parameters should read : when the \p buttonState mouse button(s) is (are) pressed (possibly
  with Alt, Control, Shift or any combination of these; possibly with a \p doubleClick), perform \p
  action.

  If \p buttonBefore is specified (valid only when \p doubleClick is \c true), then these mouse
  buttons have to pressed \e before the double click occurs in order to perform \p action. For
  instance, with the default binding, pressing the right button, then double clicking on the left
  button will call RAP_FROM_PIXEL, which defines the new qglviewer::Camera::revolveAroundPoint() as
  the point under the mouse cursor (if any).
  
  If no mouse button is specified in \p buttonState, the binding will be ignored.

  To discard a specific action mouse binding, use code like:
  \code
  setMouseBinding(myButtonStateKeyCombo, NO_CLICK_ACTION);
  \endcode

  See also setMouseBinding() and setWheelBinding(). */
void QGLViewer::setMouseBinding(int buttonState, ClickAction action, bool doubleClick, int buttonBefore)
{
  if ((buttonBefore != Qt::NoButton) && (doubleClick == false))
    qWarning("An other button is meaningful only when doubleClick is true in setMouseBinding().");
  else
    if ((buttonState & Qt::MouseButtonMask) == 0)
      qWarning("No mouse button specified in setMouseBinding");
    else
      {
	ClickActionPrivate cap;
	cap.buttonState = (Qt::ButtonState)(buttonState);
	cap.doubleClick = doubleClick;
	cap.buttonBefore = (Qt::ButtonState)(buttonBefore & Qt::MouseButtonMask);
	clickBinding_.replace(cap, action);
	if ((!doubleClick) && (buttonBefore == Qt::NoButton))
	  mouseBinding_.remove((Qt::ButtonState)(buttonState));
      }
}

/*! Associates a MouseAction to a mouse wheel event. The wheel event is received
  by \p handler. This function is very similar to setMouseBinding(), but specific to the wheel.

  In the current implementation only MouseAction::ZOOM can be
  associated with FRAME.

  CAMERA can receive MouseAction::ZOOM and
  MouseAction::MOVE_FORWARD.

  See the <a href="../mouse.html">mouse page</a> for a list of all possible
  MouseAction, some binding examples and default bindings.
  See the <a href="../examples/keyboardAndMouse.html">keyboardAndMouse</a> example for an illustration.

  The difference between ZOOM and MOVE_FORWARD is that ZOOM speed depends on the distance to the
  object, while MOVE_FORWARD depends on qglviewer::ManipulatedCameraFrame::flySpeed(). */
void QGLViewer::setWheelBinding(int stateKey, MouseHandler handler, MouseAction action, bool withConstraint)
{
  //#CONNECTION# ManipulatedFrame::wheelEvent and ManipulatedCameraFrame::wheelEvent switches
  if ((action != ZOOM) && (action != MOVE_FORWARD) && (action != MOVE_BACKWARD))
    qWarning("Cannot bind " + mouseActionString(action) + " to wheel");
  else
    if ((handler == FRAME) && (action != ZOOM))
      qWarning("Cannot bind " + mouseActionString(action) + " to FRAME wheel");
    else
      {
	MouseActionPrivate map;
	map.handler = handler;
	map.action  = action;
	map.withConstraint  = withConstraint;
	Qt::ButtonState key = (Qt::ButtonState)(stateKey & Qt::KeyButtonMask);
	wheelBinding_.replace(key, map);
      }
}

/*! Returns the MouseAction currently associated with the
  Qt::ButtonState \p buttonState. If no action is associated, returns NO_MOUSE_ACTION.

  For instance, to know which motion corresponds to Alt-LeftButton, do:
  \code
  QGLViewer::MouseAction mm = mouseAction(Qt::AltButton | Qt::LeftButton);
  if (mm != NO_MOUSE_ACTION) ...
  \endcode

  Use mouseHandler() to know who (CAMERA or FRAME) will perform this motion. */
QGLViewer::MouseAction QGLViewer::mouseAction(int buttonState)
{
  Qt::ButtonState state = (Qt::ButtonState)(buttonState);
  if (mouseBinding_.find(state) != mouseBinding_.end())
    return mouseBinding_[state].action;
  else
    return NO_MOUSE_ACTION;
}

/*! Returns the MouseHandler currently associated with the Qt::ButtonState \p buttonState. If no
  action is associated, returns \c -1.

  For instance, to know which handler receives the Alt-LeftButton, do:
  \code
  int mh = mouseHandler(Qt::AltButton | Qt::LeftButton);
  if (mh == QGLViewer::CAMERA) ...
  \endcode

  Use mouseAction() to know which action (see the MouseAction enum) will be perform on this handler. */
int QGLViewer::mouseHandler(int buttonState)
{
  Qt::ButtonState state = (Qt::ButtonState)(buttonState);
  if (mouseBinding_.find(state) != mouseBinding_.end())
    return mouseBinding_[state].handler;
  else
    return -1;
}

/*! Returns the Qt::ButtonState (if any) that has to be used to activate action \p ma on handler \p
  mh (with constraint or not). If no Qt::ButtonState is associated, returns Qt::NoButton which is an
  impossible case since at least one mouse button has to be specified in setMouseBinding().

  To know which keys and mouse buttons have to be pressed to translate the camera, use tests like:
  \code
  Qt::ButtonState bs = mouseButtonState(QGLViewer::CAMERA, QGLViewer::TRANSLATE);
  if (bs & Qt::RightButton) ... // Right button needed to translate the camera
  if (bs & Qt::AltButton)   ... // Alt key needed
  if (bs & Qt::KeyButtonMask == Qt::NoButton) ... // No state key needed
  \endcode
  Note that current mouse bindings are displayed by one of the help window tabs (use the 'H' key).
*/
Qt::ButtonState QGLViewer::mouseButtonState(MouseHandler mh, MouseAction ma, bool withConstraint)
{
  for (QMap<Qt::ButtonState, MouseActionPrivate>::ConstIterator it=mouseBinding_.begin(), end=mouseBinding_.end(); it != end; ++it)
    if ( (it.data().handler == mh) && (it.data().action == ma) && (it.data().withConstraint == withConstraint) )
      return it.key();

  return Qt::NoButton;
}

/*! Same as mouseAction(), but for the wheel action. */
QGLViewer::MouseAction QGLViewer::wheelAction(int buttonState)
{
  Qt::ButtonState state = (Qt::ButtonState)(buttonState);
  if (wheelBinding_.find(state) != wheelBinding_.end())
    return wheelBinding_[state].action;
  else
    return NO_MOUSE_ACTION;
}

/*! Same as mouseHandler but for the wheel action. */
int QGLViewer::wheelHandler(int buttonState)
{
  Qt::ButtonState state = (Qt::ButtonState)(buttonState);
  if (wheelBinding_.find(state) != wheelBinding_.end())
    return wheelBinding_[state].handler;
  else
    return -1;
}

/*! Same as mouseButtonState(), but for the wheel.

\attention Returns -1 when no Qt::ButtonState was associated with this handler/action/withConstraint
value. mouseButtonState() returns Qt::NoButton is that case as it is an impossible value. */
int QGLViewer::wheelButtonState(MouseHandler mh, MouseAction ma, bool withConstraint)
{
  for (QMap<Qt::ButtonState, MouseActionPrivate>::ConstIterator it=wheelBinding_.begin(), end=wheelBinding_.end(); it != end; ++it)
    if ( (it.data().handler == mh) && (it.data().action == ma) && (it.data().withConstraint == withConstraint) )
      return it.key();

  return -1;
}


/*! Same as mouseAction(), but for the click action set using setMouseBinding(). */
QGLViewer::ClickAction QGLViewer::clickAction(int buttonState, bool doubleClick, int buttonBefore)
{
  ClickActionPrivate cap;
  cap.buttonState = (Qt::ButtonState)(buttonState);
  cap.doubleClick = doubleClick;
  cap.buttonBefore = (Qt::ButtonState)(buttonBefore & Qt::KeyButtonMask);
  if (clickBinding_.find(cap) != clickBinding_.end())
    return clickBinding_[cap];
  else
    return NO_CLICK_ACTION;
}

/*! Similar to mouseButtonState(), but for the click actions. Note that the results of the query are
  returned in the \p buttonState, \p doubleClick and \p buttonBefore parameters. If the ClickAction
  is not associated to any mouse button, \c Qt::NoButton is returned in \p buttonState. If several
  mouse buttons trigger in the ClickAction, one of them is returned. */
void QGLViewer::getClickButtonState(ClickAction ca, Qt::ButtonState& buttonState, bool& doubleClick, Qt::ButtonState& buttonBefore)
{
  for (QMap<ClickActionPrivate, ClickAction>::ConstIterator it=clickBinding_.begin(), end=clickBinding_.end(); it != end; ++it)
    if (it.data() == ca)
      {
	buttonState = it.key().buttonState;
	doubleClick = it.key().doubleClick;
	buttonBefore = it.key().buttonBefore;
	return;
      }

  buttonState = Qt::NoButton;
}

/*! Swaps between two predefined camera mouse bindings. This function is provided for backward
  compatibility since version 1.3.4.

  The first mode makes the camera observe the scene while revolving around the
  qglviewer::Camera::revolveAroundPoint(). The second mode is designed for walkthrough applications
  and simulates a flying camera.

  Practically, the three mouse buttons are respectly binded to :
  \arg In revolve mode : ROTATE, ZOOM, TRANSLATE.
  \arg In fly mode : MOVE_FORWARD, LOOK_AROUND, MOVE_BACKWARD.

  The current mode is determined by asking the current binding of ROTATE for the
  CAMERA (using mouseButtonState()). The state key that was previously used to move the camera is
  preserved.

  The \p CAMERA_MODE QGLViewer::shortcutKey() calls this function (\c space by default) */
void QGLViewer::toggleCameraMode()
{
  Qt::ButtonState bs = mouseButtonState(CAMERA, ROTATE);
  bool flyMode = (bs != Qt::NoButton);
  if (flyMode)
    bs = mouseButtonState(CAMERA, MOVE_FORWARD);
  Qt::ButtonState stateKey = (Qt::ButtonState)(bs & Qt::KeyButtonMask);

  //#CONNECTION# setDefaultMouseBindings()
  if (flyMode)
    {
      camera()->frame()->updateFlyUpVector();
      camera()->frame()->stopSpinning();

      setMouseBinding(stateKey | Qt::LeftButton,  CAMERA, MOVE_FORWARD);
      setMouseBinding(stateKey | Qt::MidButton,   CAMERA, LOOK_AROUND);
      setMouseBinding(stateKey | Qt::RightButton, CAMERA, MOVE_BACKWARD);
  
      setMouseBinding(stateKey | Qt::LeftButton  | Qt::MidButton,  CAMERA, SCREEN_ROTATE_BOTTOM);
      setMouseBinding(stateKey | Qt::RightButton | Qt::MidButton,  CAMERA, SCREEN_TRANSLATE);

      setWheelBinding(stateKey, CAMERA, MOVE_FORWARD);
    }
  else
    {
      camera()->frame()->flyTimer_.stop();
      
      setMouseBinding(stateKey | Qt::LeftButton,  CAMERA, ROTATE);
      setMouseBinding(stateKey | Qt::MidButton,   CAMERA, ZOOM);
      setMouseBinding(stateKey | Qt::RightButton, CAMERA, TRANSLATE);
  
      setMouseBinding(stateKey | Qt::LeftButton  | Qt::MidButton,  CAMERA, SCREEN_ROTATE);
      setMouseBinding(stateKey | Qt::RightButton | Qt::MidButton,  CAMERA, SCREEN_TRANSLATE);

      setWheelBinding(stateKey, CAMERA, ZOOM);
    }
}

////////////////////////////////////////////////////////////////////////////////
//              M a n i p u l a t e d   f r a m e s                           //
////////////////////////////////////////////////////////////////////////////////

/*! The frame \p fr becomes the new manipulated frame. The manipulated frame will be moved with the
mouse when the associated mouse bindings are used (default is when pressing the \c Control key with
any mouse button). Use setMouseBinding() to define new bindings.

You can use a manipulated frame to move an object in the scene. Your code will look like this (see
the <a href="../examples/manipulatedFrame.html">manipulatedFrame</a> example):
\code
 void Viewer::init() { setManipulatedFrame(new ManipulatedFrame()); }

 void draw()
 {
  glPushMatrix(); // Save state
  glMultMatrixd(manipulatedFrame()->matrix());
  // Your object drawing code goes here
  glPopMatrix();  // Restore previous state
 }
 \endcode

Since a camera() position is defined with a ManipulatedCameraFrame, a Camera frame can be given as a
manipulatedFrame(). This is useful for an application with several viewers, where the other viewers'
cameras are displayed and can be manipulated (with a direct feedback in the other viewer). Use code
like:
\code
setManipulatedFrame( otherQGLViewer->camera()->frame() );
\endcode
Defining the \e own viewer camera()->frame() as the manipulatedFrame() is possible and will result
in a classical camera manipulation. See the <a href="../examples/luxo.html">Luxo example</a> for an
illustration.

The value of the currently manipulated frame is retrieved with manipulatedFrame(). */
void QGLViewer::setManipulatedFrame(ManipulatedFrame* fr)
{
  if (manipulatedFrame())
    {
      manipulatedFrame()->stopSpinning();

#if QT_VERSION >= 300 // Qt 2.3 has problems with inherited signals.
      if (manipulatedFrame() != camera()->frame())
	{
	  disconnect(manipulatedFrame(), SIGNAL(manipulated()), this, SLOT(updateGL()));
	  disconnect(manipulatedFrame(), SIGNAL(spinned()), this, SLOT(updateGL()));
	}
#endif
    }
  
  manipulatedFrame_ = fr;

#if QT_VERSION >= 300
  // The dynamic_cast crashes with Qt 2.3
  manipulatedFrameIsACamera_ = ((manipulatedFrame() != camera()->frame()) &&
				(dynamic_cast<ManipulatedCameraFrame*>(manipulatedFrame()) != NULL));
#endif

  if (manipulatedFrame())
    {
#if QT_VERSION >= 300 // Qt 2.3 has problems with inherited signals.
      // Prevent multiple connections, that would result in useless display updates
      if (manipulatedFrame() != camera()->frame())
	{
	  connect(manipulatedFrame(), SIGNAL(manipulated()), SLOT(updateGL()));
	  connect(manipulatedFrame(), SIGNAL(spinned()), SLOT(updateGL()));
	}
#endif
    }
}

////////////////////////////////////////////////////////////////////////////////
//                          V i s u a l   H i n t s                           //
////////////////////////////////////////////////////////////////////////////////
/*! Draws viewer related visual hints.

Displays the new qglviewer::Camera::revolveAroundPoint() when it is changed. See the
<a href="../mouse.html">mouse page</a> for details. Also draws a line between
qglviewer::Camera::revolveAroundPoint() and mouse cursor when the camera is rotated around the
camera Z axis.

See also setVisualHintsMask() and resetVisualHints(). The hint color is foregroundColor().

\note These functions may become more interesting one day. The current design is too limited
and should be improved when other visual hints must be drawn. */
void QGLViewer::drawVisualHints()
{
  // Revolve Around point cross
  if (visualHint_ & 1)
    {
      const float size = 15.0;
      Vec proj = camera()->projectedCoordinatesOf(camera()->revolveAroundPoint());
      startScreenCoordinatesSystem();
      glDisable(GL_LIGHTING);
      glDisable(GL_DEPTH_TEST);
      glLineWidth(3.0);
      glBegin(GL_LINES);
      glVertex2f(proj.x - size, proj.y);
      glVertex2f(proj.x + size, proj.y);
      glVertex2f(proj.x, proj.y - size);
      glVertex2f(proj.x, proj.y + size);
      glEnd();
      glEnable(GL_DEPTH_TEST);
      stopScreenCoordinatesSystem();
    }

  // if (visualHint_ & 2)
    // drawText(80, 10, "Play");

  // Screen rotate line
  ManipulatedFrame* mf = NULL;
  Vec pnt;
  if (camera()->frame()->action_ == SCREEN_ROTATE)
    {
      mf = camera()->frame();
      pnt = camera()->revolveAroundPoint();
    }
  if (manipulatedFrame() && (manipulatedFrame()->action_ == SCREEN_ROTATE))
    {
      mf = manipulatedFrame();
      pnt = manipulatedFrame()->position();
    }

  if (mf)
    {
      pnt = camera()->projectedCoordinatesOf(pnt);
      startScreenCoordinatesSystem();
      glDisable(GL_LIGHTING);
      glDisable(GL_DEPTH_TEST);
      glLineWidth(3.0);
      glBegin(GL_LINES);
      glVertex2f(pnt.x, pnt.y);
      glVertex2f(mf->prevX_, mf->prevY_);
      glEnd();
      glEnable(GL_DEPTH_TEST);
      stopScreenCoordinatesSystem();
    }

  // Zoom on region : draw a rectangle
  if (camera()->frame()->action_ == ZOOM_ON_REGION)
    {
      startScreenCoordinatesSystem();
      glDisable(GL_LIGHTING);
      glDisable(GL_DEPTH_TEST);
      glLineWidth(2.0);
      glBegin(GL_LINE_LOOP);
      glVertex2i(camera()->frame()->pressX_, camera()->frame()->pressY_);
      glVertex2i(camera()->frame()->prevX_,  camera()->frame()->pressY_);
      glVertex2i(camera()->frame()->prevX_,  camera()->frame()->prevY_);
      glVertex2i(camera()->frame()->pressX_, camera()->frame()->prevY_);
      glEnd();
      glEnable(GL_DEPTH_TEST);
      stopScreenCoordinatesSystem();
    }
}

/*! Defines the mask that will be used to drawVisualHints(). The only available mask is currently 1,
corresponding to the display of the qglviewer::Camera::revolveAroundPoint(). resetVisualHints() is
automatically called after \p delay milliseconds (default is 2 seconds). */
void QGLViewer::setVisualHintsMask(int mask, int delay)
{
  visualHint_ = visualHint_ | mask;
  QTimer::singleShot(delay, this, SLOT(resetVisualHints()));
}

/*! Reset the mask used by drawVisualHints(). Called by setVisualHintsMask() after 2 seconds to reset the display. */
void QGLViewer::resetVisualHints()
{
  visualHint_ = 0;
}


////////////////////////////////////////////////////////////////////////////////
//       A x i s   a n d   G r i d   d i s p l a y   l i s t s                //
////////////////////////////////////////////////////////////////////////////////

// Draws a cone with nbSub subdivisions. Aligned with the Z axis
// Not computationally optimized. Should be used in a display list.
static void drawCone(const float radius, const float height, const int nbSub)
{
  Vec pos(radius, 0.0, 0.0);
  Vec prevNormal(1.0, 0.0, radius/height);
  Vec normal, newNormal;

  prevNormal.normalize();
  
  glBegin(GL_TRIANGLES);
  for (unsigned short i=1; i<=nbSub; ++i)
    {
      glNormal3fv(prevNormal.address());
      glVertex3fv(pos.address());

      normal.x = cos(2.0*M_PI*i/static_cast<float>(nbSub));
      normal.y = sin(2.0*M_PI*i/static_cast<float>(nbSub));
      normal.z = radius / height;

      pos.x = radius * normal.x;
      pos.y = radius * normal.y;
      
      normal.normalize();
      
      prevNormal = normal;
      glNormal3fv(prevNormal.address());
      glVertex3fv(pos.address());

      newNormal.x = prevNormal.x + normal.x;
      newNormal.y = prevNormal.y + normal.y;
      newNormal.z = 4.0*radius/height;
      newNormal.normalize();

      glNormal3fv(newNormal.address());
      glVertex3f(0.0, 0.0, height);
    }
  glEnd();
}

// Draws a cylinder with nbSub subdivisions. Aligned with the Z axis
// Not computationally optimized. Should be used in a display list.
static void drawCylinder(const float radius, const float length, const int nbSub)
{
  float prevX=radius, prevY=0.0f;
  float nx=1.0f, ny=0.0f;

  glBegin(GL_QUAD_STRIP);
  for (unsigned short i=1; i<=nbSub; ++i)
    {
      glNormal3f(nx, ny, 0.0);
      glVertex3f(prevX , prevY , length);
      glNormal3f(nx, ny, 0.0);
      glVertex3f(prevX , prevY , 0.0);

      nx = cos(2.0*M_PI*i/static_cast<float>(nbSub));
      ny = sin(2.0*M_PI*i/static_cast<float>(nbSub));

      prevX = radius * nx;
      prevY = radius * ny;
      
      glNormal3f(nx, ny, 0.0);
      glVertex3f(prevX , prevY , length);
      glNormal3f(nx, ny, 0.0);
      glVertex3f(prevX , prevY , 0.0);
    }
  glEnd();
}

static void createAxisDL(GLuint& dlNumber, const float length=1.0f, const int nbSub=8)
{
  const float coneHeight = length / 10.0;
  const float coneBase = length / 30.0;
  const float cylinderHeight = length - 0.7*coneHeight;
  const float cylinderBase = coneBase / 4.0;
  const float charWidth = length / 40.0;
  const float charHeight = length / 30.0;
  const float charShift = length + 0.4*coneHeight;

  if (dlNumber != 0)
    return; // DL already created

  dlNumber = glGenLists(1);
  glNewList(dlNumber, GL_COMPILE);

  glDisable(GL_LIGHTING);
  glLineWidth(2.0);
  
  glBegin(GL_LINES);
  // The X
  glVertex3f(charShift,  charWidth, -charHeight);
  glVertex3f(charShift, -charWidth,  charHeight);
  glVertex3f(charShift, -charWidth, -charHeight);
  glVertex3f(charShift,  charWidth,  charHeight);
  // The Y
  glVertex3f( charWidth, charShift, charHeight);
  glVertex3f(0.0,        charShift, 0.0);
  glVertex3f(-charWidth, charShift, charHeight);
  glVertex3f(0.0,        charShift, 0.0);
  glVertex3f(0.0,        charShift, 0.0);
  glVertex3f(0.0,        charShift, -charHeight);
  // The Z
  glVertex3f(-charWidth,  charHeight, charShift);
  glVertex3f( charWidth,  charHeight, charShift);
  glVertex3f( charWidth,  charHeight, charShift);
  glVertex3f(-charWidth, -charHeight, charShift);
  glVertex3f(-charWidth, -charHeight, charShift);
  glVertex3f( charWidth, -charHeight, charShift);
  glEnd();
  
  glEnable(GL_LIGHTING);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  float color[4];
  color[0] = 0.7;  color[1] = 0.7;  color[2] = 1.0;  color[3] = 1.0;
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
  drawCylinder(cylinderBase, cylinderHeight, nbSub);
  glTranslatef(0.0, 0.0, length-coneHeight); 
  drawCone(coneBase, coneHeight, nbSub);
  glTranslatef(0.0, 0.0, -length+coneHeight); 
  
  color[0] = 1.0;  color[1] = 0.7;  color[2] = 0.7;  color[3] = 1.0;
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
  glPushMatrix();
  glRotatef(90.0, 0.0, 1.0, 0.0);
  drawCylinder(cylinderBase, cylinderHeight, nbSub);
  glTranslatef(0.0, 0.0, length-coneHeight);
  drawCone(coneBase, coneHeight, nbSub);
  glPopMatrix();

  color[0] = 0.7;  color[1] = 1.0;  color[2] = 0.7;  color[3] = 1.0;
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
  glPushMatrix();
  glRotatef(-90.0, 1.0, 0.0, 0.0);
  drawCylinder(cylinderBase, cylinderHeight, nbSub);
  glTranslatef(0.0, 0.0, length-coneHeight);
  drawCone(coneBase, coneHeight, nbSub);
  glPopMatrix();

  glEndList();
}

static void createGridDL(GLuint& dlNumber, const float length=1.0f, const float width=1.0f, const float nbSub=10)
{
  if (dlNumber != 0)
    return; // DL already created

  dlNumber = glGenLists(1);
  glNewList(dlNumber, GL_COMPILE);

  glDisable(GL_LIGHTING);
  glLineWidth(1.0);
  
  glBegin(GL_LINES);
  for (int i=0; i<=nbSub; ++i)
    {
      glVertex2f(length*(2*i/nbSub-1.0), -width);
      glVertex2f(length*(2*i/nbSub-1.0), +width);
      glVertex2f(-length, width*(2*i/nbSub-1.0));
      glVertex2f( length, width*(2*i/nbSub-1.0));
    }
  glEnd();
  glEndList();
}

static void createCameraDL(GLuint& dlNumber)
{
  if (dlNumber != 0)
    return; // DL already created
  
  dlNumber = glGenLists(1);
  glNewList(dlNumber, GL_COMPILE);

  glDisable(GL_LIGHTING);
  glLineWidth(2.0);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glBegin(GL_LINE_STRIP);
  glVertex3f(-1.0, 1.0,-3.0);
  glVertex3f(-1.0,-1.0,-3.0);
  glVertex3f( 0.0, 0.0, 0.0);
  glVertex3f( 1.0,-1.0,-3.0);
  glVertex3f(-1.0,-1.0,-3.0);
  glEnd();
  glBegin(GL_LINE_STRIP);
  glVertex3f( 1.0,-1.0,-3.0);
  glVertex3f( 1.0, 1.0,-3.0);
  glVertex3f( 0.0, 0.0, 0.0);
  glVertex3f(-1.0, 1.0,-3.0);
  glVertex3f( 1.0, 1.0,-3.0);
  glEnd();
  
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  
  glBegin(GL_TRIANGLES);
  glVertex3f(-0.4, 1.0,-3.0);
  glVertex3f( 0.4, 1.0,-3.0);
  glVertex3f(-0.4, 1.2,-3.0);
  
  glVertex3f(-0.4, 1.2,-3.0);
  glVertex3f( 0.4, 1.0,-3.0);
  glVertex3f( 0.4, 1.2,-3.0);

  glVertex3f( 0.0, 1.5,-3.0);
  glVertex3f(-0.6, 1.2,-3.0);
  glVertex3f( 0.6, 1.2,-3.0);
  glEnd();
  glEndList();  
}

/*! Should be called by your Open GL application \e before any frame display function
  (drawAxis(), drawGrid()) is called and \e after the GL context is active.
  The QGLViewer::initializeGL() function is the perfect place for this initialization. */
void QGLViewer::createDisplayLists()
{
  createAxisDL(AxisDL_, 1.0, 8);
  createGridDL(GridDL_, 1.0, 1.0, 10);
  createCameraDL(CameraDL_);
}

////////////////////////////////////////////////////////////////////////////////
//       S t a t i c    m e t h o d s   :  Q G L V i e w e r   P o o l        //
////////////////////////////////////////////////////////////////////////////////

/*! Connect a signal to a signal or a slot of \e all the QGLViewers.

Typical usage would be:
\code
connectSignalToAllViewers(myScene, SIGNAL(needsRedisplay()));
\endcode

The default target signal is updateGL(), but any other signal/slot can be used. This function will
silently ignore the connections that cannot be established.

See also QGLViewerPool(), disconnectSignalToAllViewers() and updateGLForAllViewers(). */
void QGLViewer::connectSignalToAllViewers(const QObject* sender, const char* signal, const char* member)
{
  QPtrListIterator<QGLViewer> it(QGLViewer::QGLViewerPool());
  for (QGLViewer* viewer; (viewer = it.current()) != 0; ++it)
    connect(sender, signal, viewer, member);
}

/*! Disconnect a signal to a signal or a slot of \e all the QGLViewers.
  Used in conjunction with connectSignalToAllViewers().

  The default target signal is updateGL(), but any other signal/slot can be used. This function will
  silently ignore the connections that cannot be removed. See also updateGLForAllViewers(). */
void QGLViewer::disconnectSignalToAllViewers(const QObject* sender, const char* signal, const char* member)
{
  QPtrListIterator<QGLViewer> it(QGLViewer::QGLViewerPool());
  for (QGLViewer* viewer; (viewer = it.current()) != 0; ++it)
    disconnect(sender, signal, viewer, member);
}

/*! updateGL() is called on all the created QGLViewers. All the viewers will have their display updated.

See also QGLViewerPool(). Use connectSignalToAllViewers() and disconnectSignalToAllViewers() for more complex connections. */
void QGLViewer::updateGLForAllViewers()
{
  QPtrListIterator<QGLViewer> it(QGLViewer::QGLViewerPool());
  for (QGLViewer* viewer; (viewer = it.current()) != 0; ++it)
    if (viewer->initializationStage_ == 3)
      viewer->updateGL();
}

/*! saveToFile() is called on all the created QGLViewers using the QGLViewerPool().

See connectSignalToAllViewers() and disconnectSignalToAllViewers() for more complex connections. */
void QGLViewer::saveToFileForAllViewers()
{
  QPtrListIterator<QGLViewer> it(QGLViewer::QGLViewerPool());
  for (QGLViewer* viewer; (viewer = it.current()) != 0; ++it)
      viewer->saveToFile();
}

//////////////////////////////////////////////////////////////////////////
//       S a v e   s t a t e   b e t w e e n    s e s s i o n s         //
//////////////////////////////////////////////////////////////////////////
/*! Saves in \p fileName an XML representation of the QGLViewer state, obtained from domElement().
  Use restoreFromFile() to restore the viewer.

  If no \p filename is provided (default), the generated filename will be ".qglviewer.xml". If
  several viewers were created in this application, the files will be numbered (".qglviewer0.xml",
  ".qglviewer1.xml",... See QGLViewer::QGLViewerIndex()). Each viewer will then read back its own
  information in restoreFromFile(), provided that the viewers are created in the same order, which
  is usually the case.

  If \p filename is a directory, the file name is generated as above and saved in this directory.
  
  This function is called when a viewer is closed (default key is Escape). */
void QGLViewer::saveToFile(const QString& fileName)
{
  QDomDocument doc("QGLVIEWER");
  doc.appendChild(domElement("QGLViewer", doc));

  QString name;
  if ((fileName.isEmpty()) || (QFileInfo(fileName).isDir()))
    {
      if (QGLViewer::QGLViewerPool().count() == 1)
	name = ".qglviewer.xml";
      else
	name = ".qglviewer" + QString::number(QGLViewer::QGLViewerIndex(this)) + ".xml";
      if (QFileInfo(fileName).isDir())
	name = fileName + "/" + name;
    }
  else
    name = fileName;

  // Write the DOM tree to file
  QFile f(name);
  if (f.open(IO_WriteOnly) == true)
    {
      QString docString = doc.toString();
      f.writeBlock(docString, docString.length());  
      f.flush();  
      f.close();  
    }
  else
    QMessageBox::warning(this, "Save to file error", "Unable to save to file "+name+" in saveToFile().");
}

/*! Restores the QGLViewer from a state saved in \p fileName with saveToFile().

 If \p fileName is empty (default), the filename is automatically generated. A directory may also be
 provided as \p filename. See the saveToFile() documentation.
  
 You should define your manipulatedFrame() \e before you call this function, so that its previous
 state can be restored. Initialization code put \e after this function will override saved values.
 \code
 void Viewer::init()
 {
 // declaration of a manipulatedFrame, if any.
 restoreFromFile();
 // main init code goes here and overrides file savings
 }
 \endcode
  
 If you viewer starts with a black screen, remember that the mouse double clicks automatically fits
 the orientation, zoom and placement of the camera(). If sceneCenter() and sceneRadius() are properly
 defined, you no longer should have an empty screen. */
void QGLViewer::restoreFromFile(const QString& fileName)
{
  QString name;
  bool testFile = true;

  if ((fileName.isEmpty()) || (QFileInfo(fileName).isDir()))
    {
      name = ".qglviewer" + QString::number(QGLViewer::QGLViewerIndex(this)) + ".xml";

      if (QFileInfo(fileName).isDir())
	name = fileName + "/" + name;

      QFileInfo fileInfo(name);
      if (!fileInfo.isFile() || !fileInfo.isReadable() && (QGLViewer::QGLViewerIndex(this) == 0))
	{
	  testFile = false;
	  name = ".qglviewer.xml";
	  
	  if (QFileInfo(fileName).isDir())
	    name = fileName + "/" + name;
	}
    }
  else
    name = fileName;

  QFileInfo fileInfo(name);
  if (!fileInfo.isFile() || !fileInfo.isReadable())
    {
      if (testFile) // Prevents messages at the very first use
	QMessageBox::warning(this, "restoreFromFile problem", "Unable to open file "+name+" in restoreFromFile() to read QGLViewer state");
      return;
    }
  
  QDomDocument doc;
  
  // Read the DOM tree form file
  QFile f(name);
  if (f.open(IO_ReadOnly) == true)
    {
      doc.setContent(&f);
      f.close();
      // Parse the DOM tree
      QDomElement main = doc.documentElement();
      initFromDOMElement(main);
    }
  else
    QMessageBox::warning(this, "Open file error", "Unable to open file "+name+" in restoreFromFile().");
}

/*! Creates an XML QDomElement that represents the QGLViewer. \p name is the name of the
  QDomElement tag. You need to provide the QDomDocument \p doc that will hold the resulting element.

  Use initFromDOMElement() to restore the QGLViewer state from the resulting domElement.
  Merges the qglviewer::ManipulatedFrame::domElement(), qglviewer::Camera::domElement(), ... elements.

  \attention For the manipulatedFrame(), qglviewer::Frame::constraint() and
  qglviewer::Frame::referenceFrame() are not saved. See qglviewer::Frame::domElement(). */
QDomElement QGLViewer::domElement(const QString& name, QDomDocument& doc) const
{
  QDomElement de = doc.createElement(name);

  QDomElement stateNode = doc.createElement("State");
  stateNode.setAttribute("mouseTracking", (hasMouseTracking()?"true":"false"));
  stateNode.appendChild(foregroundColor().domElement("foregroundColor", doc));
  stateNode.appendChild(backgroundColor().domElement("backgroundColor", doc));
  stateNode.setAttribute("stereo", (displaysInStereo()?"true":"false"));
  de.appendChild(stateNode);
  
  QDomElement displayNode = doc.createElement("Display");
  displayNode.setAttribute("drawAxis",       (axisIsDrawn()?"true":"false"));
  displayNode.setAttribute("drawGrid",       (gridIsDrawn()?"true":"false"));
  displayNode.setAttribute("displayFPS",     (fpsIsDisplayed()?"true":"false"));
  displayNode.setAttribute("displayZBuffer", (zBufferIsDisplayed()?"true":"false"));
  displayNode.setAttribute("pathEditor",     (cameraPathIsEdited()?"true":"false"));
  displayNode.setAttribute("enableText",     (textIsEnabled()?"true":"false"));
  de.appendChild(displayNode);

  QDomElement geometryNode = doc.createElement("Geometry");
  geometryNode.setAttribute("fullScreen", (isFullScreen()?"true":"false"));
  if (isFullScreen())
    {
      geometryNode.setAttribute("prevPosX", QString::number(prevPos_.x()));
      geometryNode.setAttribute("prevPosY", QString::number(prevPos_.y()));
    }
  else
    {
      QWidget* rootWindow = rootWidget();
      geometryNode.setAttribute("width",  QString::number(rootWindow->width()));
      geometryNode.setAttribute("height", QString::number(rootWindow->height()));
      geometryNode.setAttribute("posX",   QString::number(rootWindow->pos().x()));
      geometryNode.setAttribute("posY",   QString::number(rootWindow->pos().y()));
    }
  de.appendChild(geometryNode);

  de.appendChild(camera()->domElement("Camera", doc));

  if (manipulatedFrame())
    de.appendChild(manipulatedFrame()->domElement("ManipulatedFrame", doc));
  
  return de;
}

/*! Restores the QGLViewer state from a QDomElement created by domElement().
  See also qglviewer::Camera::initFromDOMElement(), qglviewer::ManipulatedFrame::initFromDOMElement().

  \note isFullScreen() cannot be properly restored in constructor or in init(). It requires
  initializeGL() to be completed before. */
void QGLViewer::initFromDOMElement(const QDomElement& de)
{  
  QDomElement child=de.firstChild().toElement();
  while(!child.isNull())
    {
      if (child.tagName() == "State")
	{
	  setMouseTracking((child.attribute("mouseTracking", "false") == "true")?true:false);
	  setStereoDisplay((child.attribute("stereo", "false") == "true")?true:false);

	  QDomElement ch=child.firstChild().toElement();
	  while(!ch.isNull())
	    {
	      if (ch.tagName() == "foregroundColor")
		foregroundColor_.initFromDOMElement(ch);
	      if (ch.tagName() == "backgroundColor")
		backgroundColor_.initFromDOMElement(ch);
	      ch = ch.nextSibling().toElement();
	    }
	}
      
      if (child.tagName() == "Display")
	{
	  setDrawAxis((child.attribute("drawAxis", "false") == "true")?true:false);
	  setDrawGrid((child.attribute("drawGrid", "false") == "true")?true:false);
	  setDisplayFPS((child.attribute("displayFPS", "false") == "true")?true:false);
	  setDisplayZBuffer((child.attribute("displayZBuffer", "false") == "true")?true:false);
	  editCameraPath((child.attribute("pathEditor", "false") == "true")?true:false);
	  setEnableText((child.attribute("enableText", "true") == "true")?true:false);
	}

      if (child.tagName() == "Geometry")
	{
	  setFullScreen((child.attribute("fullScreen", "false") == "true")?true:false);
	  
	  if (isFullScreen())
	    {
	      prevPos_.setX((child.attribute("prevPosX", "0")).toInt());
	      prevPos_.setY((child.attribute("prevPosY", "0")).toInt());
	    }
	  else
	    {
	      QWidget* rootWindow = rootWidget();
      
	      int width  = (child.attribute("width",  "600")).toInt();
	      int height = (child.attribute("height", "400")).toInt();
	      rootWindow->resize(width, height);

	      QPoint pos;
	      pos.setX((child.attribute("posX", "0")).toInt());
	      pos.setY((child.attribute("posY", "0")).toInt());
	      rootWindow->move(pos);
	    }
	}

      if (child.tagName() == "Camera")
	{
	  connectAllCameraKFIInterpolated(false);
	  camera()->initFromDOMElement(child);
	  connectAllCameraKFIInterpolated();
	}

      if ((child.tagName() == "ManipulatedFrame") && (manipulatedFrame()))
	manipulatedFrame()->initFromDOMElement(child);

      child = child.nextSibling().toElement();
    }
}
