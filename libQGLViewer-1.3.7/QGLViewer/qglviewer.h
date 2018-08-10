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

#ifndef QGLVIEWER_QGLVIEWER_H
#define QGLVIEWER_QGLVIEWER_H

#include "camera.h"
#include <qgl.h>

namespace qglviewer {
  class MouseGrabber;
}

/*! \brief An OpenGL viewer based on QGLWidget.

 A QGLViewer is a 3D OpenGL viewer based on the Qt's QGLWidget. It includes many classical viewer
 functionalities, such as a camera trackball, manipulated objects, snapshot saving and much
 <a href="../features.html">more</a>. Its main goal is to enable the very fast development of new 3D
 applications.

 In order to display a scene, you simply have to derive the draw() function (or use the drawNeeded()
 signal, see below) and to provide the openGL orders that define your scene. New users should read the
 <a href="../intro.html">introduction page</a> to get familiar with important notions such as
 sceneRadius() and sceneCenter().

 Try the numerous simple <a href="../examples/index.html">examples</a> to discover the possibilities
 and understand how it works. See also the Qt's QGLWidget documentation for details about inherited
 methods such as QGLWidget::setAutoBufferSwap() or QGLWidget::swapBuffers().

 <h3>Instantiation</h3>

 To use it, you can derive a class from it and overload the draw() virtual method.
 See the <a href="../examples/simpleViewer.html">simpleViewer</a> example for an introduction.
 \code
 // The Viewer class inherits from QGLViewer and overloads the draw function.
 class Viewer : public QGLViewer
 {
   protected:
   virtual void draw();
   {
     // Your OpenGL drawing code goes here...
   }
 };
 \endcode 
 A complete <a href="../commented.html">commented example</a> is also available.
 
 An other method is to connect your drawing methods to the signals emitted by the QGLViewer
 (clean callback mechanism). See the <a href="../examples/callback.html">callback</a> example for a complete example.
 \code
 // A Scene class holds the scene data and provides a drawScene function.
 class Scene : public QObject
 {
   Q_OBJECT // Needed in order to use the Qt signals/slots mechanism
  
   public:
     Scene(const QGLViewer* const v);
  
   public slots:
     void drawScene();
 };

 Scene::Scene(const QGLViewer* const viewer)
 {
   // Connect the viewer signal to our draw function slot
   connect(viewer, SIGNAL(drawNeeded()), SLOT(drawScene()));
 }
 \endcode
\nosubgrouping */
class QGLVIEWER_EXPORT QGLViewer : public QGLWidget
{
  Q_OBJECT        // must include this if you use Qt signals/slots
  
// #ifndef DOXYGEN
  // Q_PROPERTY(QString snapshotFilename READ snapshotFilename WRITE setSnapshotFilename)
// #endif
    
public:
  QGLViewer(QWidget* parent=NULL, const char* name=0,
	    const QGLWidget* shareWidget=0, WFlags flags=0);
  
  QGLViewer(const QGLFormat& format, QWidget* parent=0,const char* name=0,
	    const QGLWidget* shareWidget=0, WFlags flags=0);

  virtual ~QGLViewer();
  
  /*! @name Viewer colors */
  //@{
public:
  /*!\p Returns the current background color of the viewer. The \p x, \p y and \p z of the result
  represent the red, green and blue color components. Use setBackgroundColor() to define the
  background color.

  This function is provided for convenience as the background color is an OpenGL state variable set
  with \c glClearColor() (see setBackgroundColor()). However, this internal representation has the
  advantage that it is saved (resp. restored) with saveToFile() (resp. restoreFromFile()) as it is
  part of the domElement().

  Default value is (0.2, 0.2, 0.2) (dark gray). Each color component ranges between 0.0 and 1.0 (see
  the \p glColor3f() documentation). You may have to change foregroundColor() accordingly (see
  setForegroundColor()). See also the QGLWidget::qglColor() and QGLWidget::qglClearColor() documentations.
  
  \attention If you directly use \p glClearColor() instead of setBackgroundColor(), the result of
  this function will be erroneous. Consider using a \p glGet() to retrieve the actual current
  value in that case. */
  qglviewer::Vec backgroundColor() const { return backgroundColor_; };
  /*! Same as backgroundColor(), but result is returned as three floats. */
  void getBackgroundColor(float& r, float& g, float& b) const;
  /*! The current viewer foreground color. This color is used to display the FPS text (see
  setDisplayFPS()), camera paths (see qglviewer::Camera::drawAllPaths() and editCameraPath()), XY
  grid (see drawGrid() and setDrawGrid()) and the visual hints (see drawVisualHints()).

  Default value is (0.7, 0.7, 0.7). Each color component ranges between 0.0 and 1.0 (see the \p
  glColor3f() documentation). This value should be changed in conjunction with the backgroundColor()
  (see setBackgroundColor()).

  See also the QGLWidget::qglColor() and QGLWidget::qglClearColor() documentations. */
  qglviewer::Vec foregroundColor() const { return foregroundColor_; };
  /*! Same as foregroundColor(), but result is returned as three floats. */
  void getForegroundColor(float& r, float& g, float& b) const;
public slots:
  /*! Defines the background color of the viewer: backgroundColor() is modified and \p
  glClearColor(color.x, color.y, color.z, 1.0) is called. See also setForegroundColor() and the
  QGLWidget::qglColor() and QGLWidget::qglClearColor() documentations. */
  void setBackgroundColor(const qglviewer::Vec& color) { backgroundColor_ = color; glClearColor(color.x, color.y, color.z, 1.0); };
  /*! Same as setBackgroundColor(), but with float parameters. */
  void setBackgroundColor(float r, float g, float b) { setBackgroundColor(qglviewer::Vec(r, g ,b)); };
  /*! Defines the color that is used to draw viewer hints. See foregroundColor() for details. See
  also setBackgroundColor() and the QGLWidget::qglColor() and QGLWidget::qglClearColor()
  documentations. */
  /*! Same as setBackgroundColor, but with a QColor attribute. */
  void setBackgroundColor(const QColor &c) { setBackgroundColor(c.red(), c.green(), c.blue()); };
  void setForegroundColor(const qglviewer::Vec& color) { foregroundColor_ = color; };
  /*! Same as setForegroundColor(), but with float parameters. */
  void setForegroundColor(float r, float g, float b) { setForegroundColor(qglviewer::Vec(r, g ,b)); };;
  /*! Same as setForegroundColor, but with a QColor attribute. */
  void setForegroundColor(const QColor &c) { setForegroundColor(c.red(), c.green(), c.blue()); };
  //@}
  
  /*! @name Display of visual hints */
  //@{
public:
  /*! Returns \c true if the world axis is drawn by the viewer. Set by setDrawAxis() or toggleDrawAxis(). */
  bool axisIsDrawn() const { return drawAxis_; };
public slots:
  /*! Set the state of the axisIsDrawn(). World axis is drawn or not. See also toggleDrawAxis(). */
  void setDrawAxis(bool f=true) { drawAxis_ = f; emit axisDrawn(f); if (initializationStage_==3) updateGL(); };
  /*! Toggle the state of axisIsDrawn(). A world axis is drawn or not (default DRAW_AXIS shortcut
  key is 'A'). See also setDrawAxis(). */
  void toggleDrawAxis() { setDrawAxis(!drawAxis_); };

public:
  /*! Returns \c true if a grid is drawn by the viewer. Set by setDrawGrid() or toggleDrawGrid(). */
  bool gridIsDrawn() const { return drawGrid_; };
public slots:
  /*! Set the state of the gridIsDrawn(). A XY grid is drawn or not. See also toggleDrawGrid(). */
  void setDrawGrid(bool f=true) { drawGrid_ = f; emit gridDrawn(f); if (initializationStage_==3) updateGL(); };
  /*! Toggle the state of gridIsDrawn() flag. A XY grid is drawn or not (default DRAW_GRID shortcut
  key is 'G'). See also setDrawGrid(). */
  void toggleDrawGrid() { setDrawGrid(!drawGrid_); };

public:
  /*! Returns \c true if a displayFPS() is called by the viewer. Set by setDisplayFPS() or
  toggleDisplayFPS(). See currentFPS().*/
  bool fpsIsDisplayed() const { return displayFPS_; };
public slots:
  /*! Set the state of fpsIsDisplayed(). displayFPS() is called or not. See also toggleDisplayFPS()
  and currentFPS(). */
  void setDisplayFPS(bool f=true) { displayFPS_ = f; emit fpsDisplayed(f); if (initializationStage_==3) updateGL(); };
  /*! Toggle the state of fpsIsDisplayed(). displayFPS() is called or not (default DISPLAY_FPS
  shortcut key is 'F'). See also setDisplayFPS() and currentFPS(). */
  void toggleDisplayFPS() { setDisplayFPS(!displayFPS_); };

public:
  /*! Returns \c true if displayZBuffer() is called by the viewer. Set by setDisplayZBuffer() or
  toggleDisplayZBuffer(). */
  bool zBufferIsDisplayed() const { return displayZBuffer_; };
public slots:
  /*! Set the state of zBufferIsDisplayed(). displayZBuffer() is called or not. See also toggleDisplayZBuffer(). */
  void setDisplayZBuffer(bool f=true) { displayZBuffer_ = f; emit zBufferDisplayed(f); if (initializationStage_==3) updateGL(); };
  /*! Toggle the state of zBufferIsDisplayed(). displayZBuffer() is called or not (default
  DISPLAY_Z_BUFFER shortcut key is 'Z'). See also setDisplayZBuffer(). */
  void toggleDisplayZBuffer() { setDisplayZBuffer(!displayZBuffer_); };
  
public:
  /*! Returns \c true if drawText() and draw3DText() actually display text. Set by setEnableText()
  or toggleEnableText(). Convenient to remove all the possibly displayed text with a single key. */
  bool textIsEnabled() const { return enableText_; };
public slots:
  /*! Set the state of textIsEnabled() : drawText() and draw3DText() actually draw text or not
  (default is yes). See also toggleEnableText(). */
  void setEnableText(bool f=true) { enableText_ = f; emit textEnabled(f); if (initializationStage_==3) updateGL(); };
  /*! Toggle the state of textIsEnabled() : drawText() and draw3DText() actually draw text or not
  (default is yes) (default ENABLE_TEXT shortcut key is '?'). See also setEnableText(). */
  void toggleEnableText() { setEnableText(!enableText_); };

public:
  /*! Returns \c true if the camera paths are being edited in the viewer. Set by editCameraPath() or
  toggleCameraPathEditor() (default \c EDIT_CAMERA_PATHS shortcut key is 'C'). Default value is \p
  false.

  When cameraPathIsEdited(), the camera paths that are defined are displayed using
  qglviewer::Camera::drawAllPaths(). qglviewer::Camera::zNear() and qglviewer::Camera::zFar() are
  modified so that the paths are not clipped. zBuffer precision is highly affected. */
  bool cameraPathIsEdited() const { return camera()->cameraPathIsEdited(); }
public slots:
  void editCameraPath(bool edit=true);
  /*! Start/stop the edition of the camera paths (default EDIT_CAMERA_PATHS shortcut key is 'C').
    See cameraPathIsEdited(). See also editCameraPath(). */
  void toggleCameraPathEditor() { editCameraPath(!cameraPathIsEdited()); };
  //@}


  /*! @name Scene related values */
  //@{
public:
  /*! Returns the scene radius (used by the camera() to set qglviewer::Camera::zNear() and
  qglviewer::Camera::zFar()). The entire scene must be included in a sphere of radius sceneRadius(),
  centered on sceneCenter().

  This function is equivalent to camera()->sceneRadius(). */
  float sceneRadius() const { return camera()->sceneRadius(); }
  
public slots:
  /*! Scene radius is used by the camera to scale axis and grid display, and to optimally set
  qglviewer::Camera::zNear() and qglviewer::Camera::zFar(). The entire scene must be included in a
  sphere centered on sceneCenter(), with radius sceneRadius(). Current value can be retrieved from
  sceneRadius().

  You will typically use this function in QGLViewer::init() :
  \code
  setSceneRadius(3.0);
  showEntireScene();
  \endcode

  The default sceneRadius() is 1.0. See also setSceneCenter() and setSceneBoundingBox(). The camera()
  qglviewer::Camera::flySpeed() is set to 1% of this value by this function.
   
  \attention If you want to retrieve z-buffer depth from the frame buffer (using \p
  glReadPixel(GL_DEPTH_COMPONENT)), you should provide tight bounds on the sceneRadius(). See also
  qglviewer::Camera::setZNearCoef(), qglviewer::Camera::zNear(), qglviewer::Camera::zFar().*/
  void setSceneRadius(float r) { camera()->setSceneRadius(r); }

public:
  /*! Scene should be included in a sphere centered on this point. Simply calls
    qglviewer::Camera::sceneCenter(). Set using setSceneCenter(). */
  qglviewer::Vec QGLViewer::sceneCenter() const { return camera()->sceneCenter(); }
  
  void getSceneCenter(float& x, float& y, float& z) const;

public slots:
  /*! Set the center of the scene, defined in world coordinates. The entire scene should be
  include in a sphere of radius sceneRadius(), centered on sceneCenter().
  Default value is (0,0,0), the world coordinate system origin.
  
  This method should typically be called in the init() function, when the drawn scene is not
  centered on the world origin (so that sceneRadius(), qglviewer::Camera::zNear() and qglviewer::Camera::zFar() can be
  tightly fitted to the scene). It should normally not be modified after. See also setSceneBoundingBox().
  \code
  void Viewer::init()
    setSceneCenter(10,20,0);
    setSceneRadius(3.0);
    showEntireScene();
  }
  \endcode
  
  The qglviewer::Camera::revolveAroundPoint() has a different meaning, and is probably the value you
  want to change while the program is running (see qglviewer::Camera::setRevolveAroundPoint()).
  
  \attention The qglviewer::Camera::revolveAroundPoint() is set to the sceneCenter() value by this method. */
  void setSceneCenter(const qglviewer::Vec& sc) { camera()->setSceneCenter(sc); }
  
  /*! float version of setSceneCenter(). */
  void setSceneCenter(float x, float y, float z) { setSceneCenter(qglviewer::Vec(x,y,z)); };

  /*! Convenient way to call setSceneCenter() and setSceneRadius() from a Bounding Box of the scene. Equivalent to :
    \code
    setSceneCenter((m+M)/2.0);
    setSceneRadius(0.5*(M-m).norm());
    \endcode */
  void setSceneBoundingBox(const qglviewer::Vec& m, const qglviewer::Vec& M) { camera()->setSceneBoundingBox(m,M); }

  /*! Set camera so that the entire scene is visible. This method should be called in init(),
    usually after setSceneRadius(), setSceneCenter() or qglviewer::Camera::setType().

    This function simply calls qglviewer::Camera::showEntireScene(). It is called in the QGLViewer
    constructor, but with default scene parameters (sceneRadius() = 1.0, sceneCenter()=0,0,0 and
    qglviewer::Camera::type=PERSPECTIVE) that may not correspond to your scene. That is the reason why
    you should call it in init(), or use restoreFromFile() instead.*/
  void showEntireScene() { camera()->showEntireScene(); if (initializationStage_==3) updateGL(); }

public:
  /*! Same as setSceneBoundingBox(), with float[3] parameters. */
  void setSceneBoundingBox(const float m[3], const float M[3]) { setSceneBoundingBox(qglviewer::Vec(m),qglviewer::Vec(M)); };
  /*! Returns the current viewer frame rate, as displayed by displayFPS() (see setDisplayFPS() and
  toggleDisplayFPS()).

  This function is useful for true real-time applications that may adapt the computational load
  according to frame rate evolution in order to maintain a given frequency.
  
  Note that for stability reasons this value is averaged over 25 frames, and hence will only change
  every 25 draw. As Qt redraws the window only when needed, this value is meaningful only when
  startAnimation() is called, when you use qglviewer::Camera::playKeyFramePath() or when the camera is
  manipulated with the mouse, so that draw() is called in a loop. */
  float currentFPS() { return f_p_s_; };
  //@}

  /*! @name Associated objects */
  //@{
public:
  /*! The camera that is used by the viewer. See the qglviewer::Camera documentation for
  a complete description of the available functions. */
  qglviewer::Camera* camera() const { return camera_; };

  /*! Returns the current manipulated frame, which can be moved with the mouse. Default mouse
  bindings make the ManipulatedFrame move when the \c Control key is pressed. Use setMouseBinding()
  to define your own bindings.
    
  Returns \c NULL when no frame has been associated with the viewer (with setManipulatedFrame()).
  See the <a href="../examples/manipulatedFrame.html">manipulatedFrame</a> example for an
  illustration. */
  qglviewer::ManipulatedFrame* manipulatedFrame() const { return manipulatedFrame_; };
  
public slots:
  void setCamera(qglviewer::Camera* const c);
  void setManipulatedFrame(qglviewer::ManipulatedFrame* fr);
  //@}

  
  /*! @name State of the viewer */
  //@{
public:
  /*! Returns the aspect ratio of the GL widget.  That is the ratio between its
  width and height (see the Qt QGLWidget documentation). */
  float aspectRatio() const { return static_cast<float>(width())/static_cast<float>(height()); };
  /*! Returns \c true if the viewer is in fullScreen mode. Set by setFullScreen() or toggleFullScreen(). */
  bool isFullScreen() const { return fullScreen_; };
  /*! Returns \c true if the viewer displays in stereo. Set by setStereoDisplay() or toggleStereoDisplay(). Default value is \c false. */ 
  bool displaysInStereo() const { return stereo_; }  

public slots:
  void setFullScreen(bool fs=true);
  void toggleFullScreen();
  void setStereoDisplay(bool s=true);
  /*! Toggle the state of displaysInStereo() (default STEREO shortcut key is 'S'). See setStereoDisplay() for details.

  See the <a href="../examples/stereoViewer.html">stereoViewer</a> example for an illustration. */
  void toggleStereoDisplay() { setStereoDisplay(!stereo_); };
  virtual void toggleCameraMode();
  //@}

  
  /*! @name Display functions */
  //@{
public:
  void drawAxis(float scale=1.0f);
  /*! Displays a XY grid of size 1, centered on (0,0,0). The calling function should set the \p GL_MODELVIEW matrix and scale
  factor before calling this function.

  \attention The GL state is modified by this function: \p GL_LIGHTING is disabled and line width
  is set to 1. */
  void drawGrid() { glCallList(GridDL_); };

  virtual void startScreenCoordinatesSystem(bool upward = false) const;
  virtual void stopScreenCoordinatesSystem() const;

  void drawText(int x, int y, const QString& text, const QFont& fnt=QFont());
  void draw3DText(const qglviewer::Vec& pos, const qglviewer::Vec& normal, const QString& string, GLfloat height=0.1f);

protected:
  virtual void drawLight(GLenum light, float scale = 1.0f) const;
  virtual void displayFPS();
  virtual void displayZBuffer() const;
  
private:
  /*! Eps renderer callback function. */
  virtual void drawVectorial() { makeCurrent(); paintGL(); };
  
#ifndef DOXYGEN // Hidden
  friend void drawVectorial(void* param);
#endif
  //@}

  
  /*! @name Mouse grabber */
  //@{
public:
  /*! Returns the current MouseGrabber, or \c NULL if no MouseGrabber is currently under the mouse
  cursor. When qglviewer::MouseGrabber::grabsMouse(), the different mouse events are sent to the
  mouseGrabber() (see mousePressEvent(), mouseMoveEvent(), and related functions.)

  You may use setMouseGrabber() to define a qglviewer::MouseGrabber, but mouseMoveEvent() already
  does it, using qglviewer::MouseGrabber::checkIfGrabsMouse() to determine if a MouseGrabber is
  currently under the mouse cursor. See the <a href="../examples/mouseGrabber.html">mouseGrabber</a>
  example for an illustration.

  In order to use mouseGrabber, you need to enable mouse tracking so that mouseMoveEvent() is
  called even when no mouse button is pressed. Add this in init() or in your viewer constructor:
  \code
  setMouseTracking(true);
  \endcode
  Note that the default behavior is to \e disable mouse tracking. Use QWidget::hasMouseTracking() to
  get current value. */
  qglviewer::MouseGrabber* mouseGrabber() const { return mouseGrabber_; };

public slots:
  void setMouseGrabber(qglviewer::MouseGrabber* mg);
  //@}


  /*! @name Snapshots */
  //@{
public:  
  /*! Returns the current snapshot filename. Set by setSnapshotFilename(). Used in saveSnapshot(). */
  const QString& snapshotFilename() const { return snapshotFilename_; };
  /*! Returns the current snapshot file format. Defined from the File Dialog window or with
  setSnapshotFormat(). Default value is "JPEG". */
  const QString& snapshotFormat() const { return snapshotFormat_; };
  /*! The current value of the counter used to name snapshots in saveSnapshot() when \p automatic is
  \c true. Set using setSnapshotCounter(). Default value is 0, and it is incremented after each \p
  automatic snapshot. See saveSnapshot() for details. */
  int snapshotCounter() const { return snapshotCounter_; };
  
public slots:
  // Qt 2.3 does not support double default value parameters
  // Uncomment the following line (and comment the next one) with Qt 2.3
  // void saveSnapshot(bool automatic, bool overwrite);
  void saveSnapshot(bool automatic=false, bool overwrite=false);
  
  void setSnapshotFilename(const QString& n);
  /*! Defines the snapshot file format. This format will be used by saveSnapshot() in automatic
  mode. In non-automatic mode, this will be the default format of the saveAs dialog box.

  The available formats are those handled by Qt. Classical values are \c "JPEG" (default
  snapshotFormat()), \c "PNG", \c "PPM, \c "BMP". Use the following code to get the actual list:
  \code
   QStringList formatList = QImage::outputFormatList();
   for (QStringList::Iterator it = formatList.begin(); it != formatList.end(); ++it)
     cout << (*it) << endl;
  \endcode

  If the library was compiled with the EPSRender option, three additional vectorial formats are
  available: \c "EPS", \c "PS" and \c "XFIG".

  \attention No verification is performed on the provided format validity. The next call to
  saveSnapshot() may fail if the format string is not supported by the Qt QImage class. */
  void setSnapshotFormat(const QString& f) { snapshotFormat_ = f; };
  /*! Defines the new snapshotCounter() value. */
  void setSnapshotCounter(const int c) { snapshotCounter_ = c; };
  //@}

  /*! @name Animation */
  //@{
public:
  /*! Return true when the animation loop is started, i.e. viewer calls animate() and draw(). See
  startAnimation() and animate(). You should override this method if your scene contains animated
  elements (KeyFrameInterpolator driven objects excepted). */
  bool animationIsStarted() const { return animationStarted_; };
  /*! The animation loop period, in milliseconds. See startAnimation() and animate(). */
  int animationPeriod() const { return animationPeriod_; };

public slots:
  /*! Set the period (in milliseconds) between the calls to animate(). Default is 40 msecs (25 Hz).
  The frame rate (DISPLAY_FPS default binding is 'F') will be set accordingly, provided that your
  animate() function is fast enough. */
  void setAnimationPeriod(int msecs) { animationPeriod_ = msecs; };
  virtual void startAnimation();
  virtual void stopAnimation();
  /*! Calls startAnimation() or stopAnimation(), depending on animationIsStarted(). */
  void toggleAnimationMode() { if (animationIsStarted()) stopAnimation(); else startAnimation(); };

  /*! Scene animation function. Once startAnimation() has been called, an infinite loop calls animate() and draw().

  See the <a href="../examples/animation.html">animation</a> example for an illustration. */
  virtual void animate() { emit animateNeeded(); };
  //@}

public:
signals:
  /*! Signal emitted by the default QGLViewer::init() function. Connect this signal to the functions
  that need to be called before any drawing (if any), to initialize your viewer.
  
  Use this signal-slot mechanism ONLY IF you don't inherit your viewer from QGLViewer
  (in that case, simply overload the init() function). */
  void viewerInitialized();

  /*! Signal emitted by the default QGLViewer::draw() function. Connect this signal to your main
  drawing function. preDraw() is called \e before this signal is emitted and will call
  qglviewer::Camera::loadProjectionMatrix() and qglviewer::Camera::loadModelViewMatrix() to set the
  viewing matrices. postDraw() will be called \e after this signal is answered. pre (resp. post)
  draw can be tuned by adding code at the beginning (resp. end) of your draw slot. See the
  <a href="../examples/callback.html">callback</a> example for an illustration.
  
  You can check whether the camera is manipulated to call a fast draw version :
  \code
  if (viewer.camera()->isManipulated())
    fastDrawMethod();
  else
    normalDrawMethod();
  \endcode
  
  Use this signal-slot mechanism ONLY IF you don't inherit your viewer from QGLViewer (in that
  case, simply overload the draw() and fastDraw() function).

  See the <a href="../examples/fastDraw.html">fastDraw</a> example for an illustration. */
  void drawNeeded();

  /*! Signal emitted by the default QGLViewer::animate() function. Connect this signal to your scene
  animation function.
  
  Use this signal-slot mechanism ONLY IF you don't inherit your viewer from QGLViewer
  (in that case, simply overload the animate() function). */
  void animateNeeded();

  /*! Signal emitted by the default QGLViewer::help() function. Connect this signal to your own help
  function.
  
  Use this signal-slot mechanism ONLY IF you don't inherit your viewer from QGLViewer
  (in that case, simply overload the help() function). */
  void helpRequired();

  /*! This signal is emitted whenever axisIsDrawn() changes value. This can be done with setDrawAxis() or toggleDrawAxis(). */
  void axisDrawn(bool on);
  /*! This signal is emitted whenever gridIsDrawn() changes value. This can be done with setDrawGrid() or toggleDrawGrid(). */
  void gridDrawn(bool on);
  /*! This signal is emitted whenever fpsIsDisplayed() changes value. This can be done with setDisplayFPS() or toggleDisplayFPS(). */
  void fpsDisplayed(bool on);
  /*! This signal is emitted whenever zBufferIsDisplayed() changes value. This can be done with setDisplayZBuffer() or toggleDisplayZBuffer(). */
  void zBufferDisplayed(bool on);
  /*! This signal is emitted whenever textIsEnabled() changes value. This can be done with setEnableText() or toggleEnableText(). */
  void textEnabled(bool on);
  /*! This signal is emitted whenever cameraPathIsEdited() changes value. This can be done with editCameraPath() or toggleCameraPathEditor(). */
  void cameraPathEdited(bool on);
  /*! This signal is emitted whenever displaysInStereo() changes value. This can be done with setStereoDisplay() or toggleStereoDisplay(). */
  void stereoChanged(bool on);
  /*! Signal emitted when select() is called. Connect this signal to your selection drawing
    function. Use this signal-slot mechanism ONLY IF you don't inherit your viewer from QGLViewer
    (in that case, simply overload the select() or the drawWithNames() functions). See select() for
    more details. */
  void pointSelected(const QMouseEvent* e);
                                                      
  /*! @name Help window */
  //@{ 
public:
  /*! helpString() is displayed in the help window main tab. This window is created by the help()
    function when the HELP_KEY (default is 'H') is pressed. Overload this function to define your
    own help string, which should shortly describe your application and explains how it works.
    Rich-text (HTML) tags can be used.
  \code
  QString myViewer::helpString() const
  {
    QString text("<h2>M y V i e w e r</h2>");
    text += "Displays a <b>Scene</b> using openGL. Move the camera using the mouse.";
    return text;
  }
  \endcode

  Default value is QString::null, which means that the associated tab in the help window is removed.
  
  See also mouseBindingsString() and shortcutBindingsString(). */
  virtual QString helpString() const { return QString::null; };

  virtual QString mouseBindingsString() const;
  virtual QString shortcutBindingsString() const;
  
public slots:
  virtual void help();
  //@}

protected:
  virtual void resizeGL( int w, int h );

  virtual void initializeGL();

  /*! Initialization of the viewer. This function will be called before the first drawing and you
  can overload it to initialize some of the GL flags. The original function is empty and hence does
  not need to be called.

  Can be used to set the camera (qglviewer::Camera::setPosition(),
  qglviewer::Camera::setFieldOfView(), ...) or to make the camera fit the scene (see
  qglviewer::Camera::showEntireScene()).

  OpenGL flags should also be (re)defined here. Some default flags are set in initializeGL(): only
  the \c glEnable(GL_COLOR_MATERIAL) and \c glEnable(GL_LIGHTING) are not set to their OpenGL
  default value. Use this function to set your own openGL flags.

  \attention You should not call updateGL() (or any function that calls it) in this function, as it
  will create an infinite loop (this comes from the Qt initializeGL() function). The different
  QGLViewer set function (setDrawGrid(), setDrawAxis()...) are protected against this problem and
  can safely be called.

   \attention This function should only be used for viewer dependent initializations (camera, openGL
   state). Other data initializations (program parameters parsing, scene dependent
   initializations...) should be made in a separate function, called by your \p main or any other
   initialization function. On the other hand, all the openGL specific initializations \e must be
  done in this function: the openGL context is not yet available in your viewer constructor. */
  virtual void init() { emit viewerInitialized(); };

  virtual void paintGL();

  virtual void preDraw();  
  virtual void preDrawStereo(bool leftBuffer=true);
  
  /*! The core function of the viewer, called to draw the scene.

  If you build a class that inherits from QGLViewer, this is the function you want to overload. See
  the <a href="../examples/simpleViewer.html">simpleViewer</a> example for an illustration.

  If you choose to use a callback mechanism instead, connect the drawNeeded() signal to your own
  draw function (signal emitted by preDraw()). See the
  <a href="../examples/callback.html">callback</a> example for details.

  \attention The GL_PROJECTION matrix must not be modified by this function, so that the viewer
  hints (axis, grid, FPS...) that are displayed in postDraw() are correctly displayed. Use push/pop
  or call camera()->loadProjectionMatrix() at the end of draw() if you need to change the projection
  matrix (unlikely). The GL_MODELVIEW matrix, on the other hand, can be modified and left in a
  different state as it will be reloaded in postDraw() anyhow. */
  virtual void draw() {};
  virtual void fastDraw();
  virtual void postDraw();
  
  /*! Recursively call QWidget::parentWidget() until the root widget is found. */
  QWidget* rootWidget() const;
    
  /*! @name Mouse and keyboard handlers */
  //@{
protected:
  virtual void mousePressEvent(QMouseEvent *);
  virtual void mouseDoubleClickEvent(QMouseEvent *);
  virtual void mouseReleaseEvent(QMouseEvent *);
  virtual void mouseMoveEvent(QMouseEvent *);
  virtual void wheelEvent(QWheelEvent *);
  virtual void timerEvent(QTimerEvent *);
  virtual void closeEvent(QCloseEvent *);
  virtual void keyPressEvent(QKeyEvent *);
  //@}

  /*! @name Object selection */
  //@{
public:
  virtual void select(const QMouseEvent* e);
  virtual void select(int x, int y);
  
  virtual void beginSelection(int x, int y);
  /*! This function is called by select() and is originally empty. You should overload it to draw
    the different elements of your scene you want to be able to select. The default select()
    implementation relies on the \c GL_SELECT, and requires the drawing of each element within \c
    glPushName() \c glPopName() block. A typical usage would be (see the
    <a href="../examples/select.html">select</a> example):
    \code
    void Viewer::drawWithNames()
    {
      for (int i=0; i<nbObjects; ++i)
      {
        glPushName(i);
	object(i)->draw();
	glPopName();
      }
    }
    \endcode

    The resulting selected name is retrieved by endSelection(), which setSelectedName() (a value of
    -1 means no selection). Use selectedName() to update your selection, probably in the
    postSelection() method. */
  virtual void drawWithNames() {};
  virtual void endSelection(int x, int y);
  /*! This method is called at the end of the select() procedure. It should finalyse the selection
    process and update the data structure/interface/computation/display... according to the newly
    selected entity.

    The default implementation is empty. Overload this method if needed, and use selectedName() to
    retrieve the selected entity name (returns -1 if no object was selectable under the mouse
    cursor). See the <a href="../examples/select.html">select</a> example for an illustration. */
  virtual void postSelection(int, int) {};

  /*! Returns the name (an integer value) of the entity that was last selected by select(). This
    value is set by endSelection(). See the select() documentation for details.

  As a convention, this function returns -1 if the selectBuffer() was empty, meaning that no object
  was selected. Note that this function returns the same value until setSelectedName() is called,
  which should only be done by endSelection(), and hence only when a selection is performed using
  select().

  Before the first call to select(), the return value is -1. */
  int selectedName() { return selectedObjectId_; };
  /*! Set the selectedName() value. Called by endSelection() during a selection. */
  void setSelectedName(int id) { selectedObjectId_=id; };

  /*! Returns the current selectBuffer() size. Use setSelectBufferSize() to change this value.
    Default value is 256. This size should be over estimated to prevent a buffer overflow when many
    objects are drawned under the mouse cursor. The default value should however fit most
    applications. See the select() documentation for details. See also selectRegionSize(). */
  int selectBufferSize() { return selectBufferSize_; };
  void setSelectBufferSize(int size);

  /*! This size (in pixels) is used to define the selection window size created in beginSelection().
    A square frustum is then created with this side size around the mouse cursor, and the objects
    that will be drawned in this region by drawWithNames() will be recorded in the selectBuffer().
    endSelection() then analyses this buffer and setSelectedName() to the closest object name.

    The default value is 4, which is adapted to standard applications. A smaller value results in a
    more precise but the user has to be careful for small feature selection. */
  int selectRegionSize() { return selectRegionSize_; };
  /*! Changes the selectRegionSize(). Default value is 4 pixels. */
  void setSelectRegionSize(int size) { selectRegionSize_ = size; };

  /*! Returns a pointer to an array of \c GLuint. This buffer is used by the \c GL_SELECT mode in
    select() to perform object selection. The buffer size can be modified using
    setSelectBufferSize(). If you overload endSelection(), you will analyse the content of this
    buffer. See the glSelectBuffer() man page for details. */
  GLuint* selectBuffer() { return selectBuffer_; };
  //@}
  
  /*! @name Key customization */
  //@{
protected:
  /*! Defines the different actions that can directly be associated with a keyboard shortcut.
  Used by setShortcutKey(), setShortcutStateKey(), shortcutKey() and shortcutStateKey().

  See the <a href="../shortcuts.html">QGLViewer shortcuts page</a> for details. */
  enum ShortcutAction { DRAW_AXIS, DRAW_GRID, DISPLAY_FPS, DISPLAY_Z_BUFFER, ENABLE_TEXT, EXIT, SAVE_SCREENSHOT,
			CAMERA_MODE, FULL_SCREEN, STEREO, ANIMATION, HELP, EDIT_CAMERA_PATHS };
  //#CONNECTION# shortcutBindingsString
public:
  virtual void setShortcutKey(ShortcutAction action, int key, int stateKey = -1);
  Qt::Key shortcutKey(ShortcutAction action) const;

  virtual void setShortcutStateKey(ShortcutAction action, int buttonState);
  Qt::ButtonState shortcutStateKey(ShortcutAction action) const;

  // Key Frames shortcut keys
  virtual void setKeyFrameKey(int nb, int key);
  Qt::Key keyFrameKey(int nb) const;

  virtual void setAddKeyFrameStateKey(int buttonState);
  Qt::ButtonState addKeyFrameStateKey() const;

  virtual void setPlayKeyFramePathStateKey(int buttonState);
  Qt::ButtonState playKeyFramePathStateKey() const;
  //@}

  
  /*! @name Mouse behavior customization */
  //@{
protected:
  /*! Defines the different mouse handlers : Camera or Frame motion. Used by setMouseBinding() to
  define which handler receives the mouse displacements. See the <a href="../mouse.html">mouse page</a>
  for details. */
  enum MouseHandler { CAMERA, FRAME };

  /*! Defines the possible actions that can be binded to a mouse click. ClickAction are binded using
  setMouseBinding(). See the <a href="../mouse.html">mouse page</a> for details. */
  enum ClickAction { NO_CLICK_ACTION, ZOOM_ON_PIXEL, ZOOM_TO_FIT, SELECT, RAP_FROM_PIXEL, RAP_IS_CENTER,
		     CENTER_FRAME, CENTER_SCENE, SHOW_ENTIRE_SCENE, ALIGN_FRAME, ALIGN_CAMERA };

public:
  /*! Defines the possible actions that can be binded to a mouse motion (a click, followed by a
  mouse displacement). These actions may be applied to the camera() or to the manipulatedFrame()
  (see MouseHandler). Use setMouseBinding() to bind a mouse button to an action. See the
  <a href="../mouse.html">mouse page</a> for details. */
  enum MouseAction { NO_MOUSE_ACTION,
		     ROTATE, ZOOM, TRANSLATE,
		     MOVE_FORWARD, LOOK_AROUND, MOVE_BACKWARD,
		     SCREEN_ROTATE, SCREEN_ROTATE_BOTTOM,
		     SCREEN_TRANSLATE, ZOOM_ON_REGION };
  
  void setMouseStateKey(MouseHandler mh, int buttonState);

  void setMouseBinding(int buttonState, MouseHandler handler, MouseAction action, bool withConstraint=true);
  MouseAction mouseAction(int buttonState);
  int mouseHandler(int buttonState);
  Qt::ButtonState mouseButtonState(MouseHandler mh, MouseAction ma, bool withConstraint=true);

  void setMouseBinding(int buttonState, ClickAction action, bool doubleClick=false, int buttonBefore=Qt::NoButton);
  ClickAction clickAction(int buttonState, bool doubleClick, int buttonBefore);
  void getClickButtonState(ClickAction ca, Qt::ButtonState& buttonState, bool& doubleClick, Qt::ButtonState& buttonBefore);

  void setWheelBinding(int stateKey, MouseHandler handler, MouseAction action, bool withConstraint=true);
  MouseAction wheelAction(int buttonState);
  int wheelHandler(int buttonState);
  int wheelButtonState(MouseHandler mh, MouseAction ma, bool withConstraint=true);
  
private:
  static QString mouseActionString(QGLViewer::MouseAction ma);
  static QString clickActionString(QGLViewer::ClickAction ca);
  //@}

  
  /*! @name Save and restore viewer state */
  //@{
public:
  virtual void saveToFile(const QString& fileName="");
  virtual void restoreFromFile(const QString& fileName="");
  
  virtual QDomElement domElement(const QString& name, QDomDocument& doc) const;
  virtual void initFromDOMElement(const QDomElement& de);
  //@}


  /*! @name Static methods for all the viewers

  All the created QGLViewers are stored in a QGLViewerPool(). These methods allow you to use this pool. */
  //@{
  public:
  /*! This QPtrList (see Qt documentation) holds all the created QGLViewer. If you need to apply a
  method to \e all the created viewers, use code like this:
  \code
  QPtrListIterator<QGLViewer> it(QGLViewer::QGLViewerPool());
  for (QGLViewer* viewer; (viewer = it.current()) != NULL; ++it)
    viewer->anyAction();
  \endcode
  Classical functions are allready implemented : connectSignalToAllViewers(),
  disconnectSignalToAllViewers() and updateGLForAllViewers(). See also QGLViewerIndex(). */
  static const QPtrList<QGLViewer>& QGLViewerPool() { return QGLViewerPool_; };
  /*! Returns the index of the QGLViewer \p v in the QGLViewerPool(). This index in unique and can
  be used to identify the different created QGLViewers (see saveToFile() for an application
  example). When a QGLViewer is deleted, all the next QGLViewers' indexes are shifted.
  
  Return -1 if the QGLViewer could not be found (which should not be possible). */
  static int  QGLViewerIndex(const QGLViewer* const v) { return QGLViewerPool_.find(v); };
  static void connectSignalToAllViewers(const QObject* sender, const char* signal, const char* member=SLOT(updateGL()));
  static void disconnectSignalToAllViewers(const QObject* sender, const char* signal, const char* member=SLOT(updateGL()));
  static void updateGLForAllViewers();
  static void saveToFileForAllViewers();
  //@}


  /*! @name Visual hints */
  //@{
  public:
  virtual void setVisualHintsMask(int mask, int delay = 2000);
  virtual void drawVisualHints();
    
  public slots:
  virtual void resetVisualHints();
  //@}
    
private slots:
  void delayedFullScreen() { move(prevPos_); setFullScreen(); };
  
private:
  // Copy constructor and opertor= are declared private and undefined
  // Prevents everyone from trying to use them
  QGLViewer(const QGLViewer& v);
  QGLViewer& operator=(const QGLViewer& v);

  // Set parameters to their default values. Called by the constructors.
  void defaultConstructor();

  // C a m e r a
  qglviewer::Camera* camera_;
  void connectAllCameraKFIInterpolated(bool connection=true);
  
  // C o l o r s
  qglviewer::Vec backgroundColor_, foregroundColor_;
  
  // D i s p l a y    f l a g s
  bool drawAxis_;	// world axis 
  bool drawGrid_;	// world XY grid
  bool displayFPS_;	// Frame Per Seconds
  bool displayZBuffer_; // Grey level z-buffer
  bool enableText_;	// drawText() actually draws text or not
  bool stereo_;		// stereo display
  bool fullScreen_;	// full screen mode
  QPoint prevPos_;	// Previous window position, used for full screen mode

  // A n i m a t i o n    p a r a m e t e r s
  bool animationStarted_; // animation mode started
  int animationPeriod_;   // period in msecs
  int animationTimerId_;
  
  // F P S    d i s p l a y 
  QTime fpsTime_;
  unsigned int fpsCounter_;
  float f_p_s_;
  
  // M a n i p u l a t e d    f r a m e 
  qglviewer::ManipulatedFrame* manipulatedFrame_;
  bool manipulatedFrameIsACamera_;
  qglviewer::MouseGrabber* mouseGrabber_;
  bool mouseGrabberIsAManipulatedFrame_;
  bool mouseGrabberIsAManipulatedCameraFrame_;
  
  // D i s p l a y    l i s t s
  GLuint AxisDL_, GridDL_, CameraDL_;
  void createDisplayLists();

  // S e l e c t i o n
  int selectRegionSize_;
  int selectBufferSize_;
  GLuint* selectBuffer_;
  int selectedObjectId_;

  // V i s u a l   h i n t s
  int visualHint_;

  // S h o r t c u t   k e y s 
  void setDefaultShortcutKeys();
  enum { nbShortcuts_ = 13 };
  Qt::Key         shortcutKey_[nbShortcuts_];
  Qt::ButtonState shortcutStateKey_[nbShortcuts_];

  // K e y   F r a m e s   s h o r t c u t s
  Qt::Key *keyFrameKey_;
  Qt::ButtonState addKFStateKey_, playKFStateKey_;

  // M o u s e   a c t i o n s
  struct MouseActionPrivate {
    MouseHandler handler;
    MouseAction action;
    bool withConstraint; 
  };

  // C l i c k   a c t i o n s
  class ClickActionPrivate {
  public:
    Qt::ButtonState buttonState;
    bool doubleClick;
    Qt::ButtonState buttonBefore;

    bool operator<(const ClickActionPrivate& cap) const
    {
      if (buttonState != cap.buttonState)
	return buttonState < cap.buttonState;
      else
	if (buttonBefore != cap.buttonBefore)
	  return buttonBefore < cap.buttonBefore;
	else
	  return doubleClick < cap.doubleClick;
    }
  };

  void setDefaultMouseBindings();
  void performClickAtion(ClickAction ca, const QMouseEvent* const e);
  QMap<Qt::ButtonState, MouseActionPrivate> mouseBinding_;
  QMap<Qt::ButtonState, MouseActionPrivate> wheelBinding_;
  QMap<ClickActionPrivate, ClickAction> clickBinding_;
  
  // S n a p s h o t s
  QString snapshotFilename_, snapshotFormat_;
  int snapshotCounter_;
  
  // Q G L V i e w e r   p o o l
  static QPtrList<QGLViewer> QGLViewerPool_;
  
  // I n t e r n a l   d e b u g
  int initializationStage_;
};

#endif // QGLVIEWER_QGLVIEWER_H
