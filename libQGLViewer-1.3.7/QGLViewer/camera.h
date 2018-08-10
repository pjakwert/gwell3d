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

#ifndef QGLVIEWER_CAMERA_H
#define QGLVIEWER_CAMERA_H

#include "manipulatedCameraFrame.h"
#include "keyFrameInterpolator.h"

namespace qglviewer {
  /*! \brief An OpenGL camera, with positioning tools.

  A Camera defines some intrinsic camera parameters, such as fieldOfView(), position(),
  viewDirection(), upVector()... It also provides useful positioning tools that ease its placement :
  showEntireScene(), fitSphere(), fitBoundingBox(),, ...

  The type() of the Camera can be ORTHO or PERSPECTIVE (see Type()). fieldOfView() is meaningless in ORTHO.

  The position() and orientation() of the Camera are defined by a ManipulatedCameraFrame that can be
  retrieved with frame(). These functions are just a convenient interface for the associated Frame
  functions. This also means that the Camera frame() can be attached to a Frame::referenceFrame()
  which enable complex Camera setups.

  Different camera displacements can be performed using the mouse. The list of possible actions is
  defined by the QGLViewer::MouseAction enum. Use QGLViewer::setMouseBinding() to attach a
  specific action to an arbitrary mouse button-state key binding. These actions are detailed in the 
  <a href="../mouse.html">mouse page</a>.

  The default button binding are : QGLViewer::ROTATE (left), QGLViewer::ZOOM (middle)
  and QGLViewer::TRANSLATE (right). With this configuration, the camera \e observes a scene
  and rotates around its revolveAroundPoint(). You can switch between this mode and a walkthrough
  mode using the QGLViewer::CAMERA_MODE shortcut key (see QGLViewer::setShortcutKey() and
  QGLViewer::toggleCameraMode()).

  The near and far planes of the Camera are determined from the QGLViewer::sceneRadius() and
  QGLViewer::sceneCenter() by the zNear() and zFar() functions. Reasonable values on the scene
  extends hence have to be provided to the QGLViewer in order for the Camera to correctly display
  the scene. High level positioning functions can then be automated (showEntireScene(),
  centerScene()...). Once again, see the <a href="../mouse.html">mouse page</a> for details.

  A Camera holds 12 KeyFrameInterpolator that can be used to save camera positions and paths.
  Default key binding associates these paths to the F[1-12] keys, see the
  <a href="../shortcuts.html">shortcut page</a> for more information.

  Use cameraCoordinatesOf() ans worldCoordinatesOf() to convert to and from the Camera frame()
  coordinate system. projectedCoordinatesOf() and unprojectedCoordinatesOf() will convert from
  screen to 3D coordinates. convertClickToLine() is very useful for analytical object selection.

  Stereo display is possible on machines with quad buffer capabilities (with PERSPECTIVE type()
  only). Test the <a href="../examples/stereoViewer.html">stereoViewer example</a> to check.
  \nosubgrouping */
  class QGLVIEWER_EXPORT Camera : public QObject
  {
#ifndef DOXYGEN
    friend class ::QGLViewer;
#endif 

    Q_OBJECT        // must include this if you use Qt signals/slots
      
  public:
    Camera();
    virtual ~Camera();

    /*! The type of camera used by the QGLViewer, set by setType(). This type will be use in loadProjectionMatrix().
    \see setFieldOfView, setSceneRadius, type, setType, loadProjectionMatrix */
    enum Type { PERSPECTIVE, ORTHO };

    /*! @name Position and orientation of the camera */
    //@{
  public:    
    /*! Returns the camera position (the eye), defined in the world coordinate system. Use
    setPosition() to set the camera position. Other convenient functions are showEntireScene(),
    fitBoundingBox() or fitSphere(). Actually returns \p frame()->position(). */
    Vec position() const { return frame()->position(); };
    /*! Returns the camera current orientation, defined in the world coordinate system. Actually
    returns \p frame()->orientation(). Use setOrientation(), setUpVector() or lookAt() to set the
    camera orientation. */
    Quaternion orientation() const { return frame()->orientation(); };

    void getPosition(float& x, float& y, float& z) const;
    void getOrientation(float& q0, float& q1, float& q2, float& q3) const;

     public slots:
    /*! Set the camera position (the eye), defined in the world coordinate system. The current
    camera position can be obtained from position(). */
    void setPosition(const Vec& pos) { frame()->setPosition(pos); };
    /*! Same as setPosition(), but with float parameters. */
    void setPosition(float x, float y, float z) { setPosition(Vec(x,y,z)); };

    void setOrientation(const Quaternion& q);
    /*! Same as setOrientation(), but with float parameters. */
    void setOrientation(float q0, float q1, float q2, float q3) { setOrientation(Quaternion(q0,q1,q2,q3)); };
    void setOrientation(float theta, float phi);

    void setCameraFromProjectionMatrix(const float* const m);
    //@}

    
    /*! @name Positioning tools */
    //@{
  public slots:
    void showEntireScene();

    void fitBoundingBox(const Vec& m, const Vec& M);

    void fitSphere(const Vec& center, float radius);
    /*! Same as fitSphere(), but with float parameters. */
    void fitSphere(float x, float y, float z, float r) { fitSphere(Vec(x,y,z), r); };

    void lookAt(const Vec& target);
    /*! Same as lookAt(), but with float parameters. */
    void lookAt(float x, float y, float z) { lookAt(Vec(x,y,z)); };

    void centerScene();

    void setUpVector(const Vec& up, bool noMove = true);
    void fitScreenRegion(int xa, int ya, int xb, int yb);
    
    void setFOVToFitScene();
  public: // Doxygen thinks it is too smart
    /*! Same as setUpVector(), but with float parameters. */
    void setUpVector(float x, float y, float z, bool noMove = true) { setUpVector(Vec(x,y,z), noMove); };
    
  public slots:
    void interpolateToZoomOnPixel(int x, int y);
    void interpolateToFitScene();
    //@}

    
    /*! @name Intrinsic parameters */
    //@{
  public:
    /*! Returns the vertical field of view of the camera (in radians). Value is set using setFieldOfView(), default value is pi/4 radians. */
    float fieldOfView() const { return fieldOfView_; };

    /*! Returns the horizontal (X camera frame direction) field of view used by the camera (in
    radians). Value is set using setHorizontalFieldOfView() or setFieldOfView(). The values
    are always linked by :
    \code
    horizontalFieldOfView() = 2.0 * atan ( tan(fieldOfView()/2.0) * aspectRatio() ).
    \endcode */
    float horizontalFieldOfView() const { return 2.0 * atan ( tan(fieldOfView()/2.0) * aspectRatio() ); };

    /*! Returns the current fly speed of the camera. This function is identical to
    ManipulatedCameraFrame::flySpeed(). The flySpeed() is only meaningful when the mouse bindings
    are set to QGLViewer::MOVE_FORWARD or QGLViewer::MOVE_BACKWARD (see
    QGLViewer::setMouseBinding() and the <a href="../mouse.html">mouse page</a>.

    Set with setFlySpeed(). Set to 0.5% of the sceneRadius in setSceneRadius(). */
    float flySpeed() const { return frame()->flySpeed(); };

    /*! Returns the type of the camera used by the QGLViewer. Set by setType().
    Supported types are defined by the Type() enum. Used by loadProjectionMatrix().*/
    Type type() const { return type_; };

  public slots:
    /*! Defines the vertical field of view of the camera (in radians). Also used to fit the scene and
    mouse translations. fieldOfView() returns the current value. The default value is pi/4 radians.
    loadProjectionMatrix() uses this value to define the camera.

    The field of view corresponds the one used in \p gluPerspective (see manual). It sets the Y
    (vertical) aperture of the camera. The X (horizontal) angle is inferred from the window aspect
    ratio (see aspectRatio() and horizontalFieldOfView()).

    Use setFOVToFitScene() to adapt the fieldOfView(). This is not the normal way of zooming in or
    out. All the other positioning camera function (showEntireScene(), fitSphere()...) \e move the
    camera instead of changing its fieldOfView().

    distanceToZeroParallaxPlane() is set to sceneRadius() / tan(fieldOfView()/2) (used only for stereo
    mode, see QGLViewer::setStereoDisplay(), setSceneRadius() and setDistanceToZeroParallaxPlane()). */
    void setFieldOfView(float f) { fieldOfView_ = f; setDistanceToZeroParallaxPlane(sceneRadius() / tan(f/2.0)); };

    /*! Defines the horizontal field of view of the camera (in radians). Actually calls
    setFieldOfView() scaled by 1/aspectRatio(). 
  
    loadProjectionMatrixStereo() uses this value to define the camera offset and frustum. */
    void setHorizontalFieldOfView(float hfov) { setFieldOfView( 2.0 * atan (tan(hfov / 2.0) / aspectRatio()) ); };
    
    /*! When the camera associated mouse action is QGLViewer::MOVE_FORWARD or
    QGLViewer::MOVE_BACKWARD, tunes the speed of the displacement. Current value is given by
    flySpeed(). See the <a href="../mouse.html">mouse page</a> for details.
    
    \attention This value is modified by setSceneRadius(). */
    void setFlySpeed(float s) { frame()->setFlySpeed(s); };
    void setType(Type type);
    //@}

    
    /*! @name Associated parameters */
    //@{
  public:
    virtual float zNear() const;
    virtual float zFar()  const;
    /*! Returns the coefficient which is used to set zNear() when the camera is inside the
    sceneRadius() sphere. Set with setZNearCoef(). Only meaningful when camera type is
    Camera::PERSPECTIVE. */
    float zNearCoef() const { return zNearCoef_; };
    void getOrthoWidthHeight(GLdouble& w, GLdouble& h) const;

    /*! Returns the currents camera aspect ratio (screenWidth() / screenHeight()), determined from the QGLViewer window size. */
    float aspectRatio() const { return static_cast<float>(screenWidth_)/static_cast<float>(screenHeight_); };
    /*! Returns the current width (in pixels) of the camera screen. See also QGLWidget::width() */
    int screenWidth() const { return screenWidth_; };
    /*! Returns the current height (in pixels) of the camera screen. See also QGLWidget::height(). */
    int screenHeight() const { return screenHeight_; };
    float pixelGLRatio(const Vec& pos);

    float distanceToSceneCenter() const;
    
    Vec upVector() const;
    void getUpVector(float& x, float& y, float& z) const;

    /*! Returns the normalized view direction of the camera (negative Z axis), defined in the world coordinate system. */
    Vec viewDirection() const { return frame()->inverseTransformOf(Vec(0.0, 0.0, -1.0)); };
    void getViewDirection(float& x, float& y, float& z) const;
    
    Vec pointUnderPixel(const int x, const int y, bool& found);

    /*! \p true when the camera is being manipulated with the mouse.
    Useful for switching to fast draw mode. See QGLViewer::fastDraw(). */
    bool isManipulated() const { return frame()->isManipulated(); };

    void getViewport(GLint viewport[4]) const;
    
  public slots:
    /*! This value is used when the camera is \e inside the sceneRadius(), sceneCenter() sphere. The
    zNear() value is then set to zNearCoef() * sceneRadius(). Default value is 0.001, which is
    appropriate for walkthrough applications. In case you need a high dynamic ZBuffer precision, you
    can increase this value (~0.1). A lower value will prevent clipping of very close objects at the
    expense of a worst Z precision. */
    void setZNearCoef(float coef) { zNearCoef_ = coef; };

    /*! Defines the camera aspectRatio().

    \attention When a Camera is attached to a QGLViewer (using QGLViewer::setCamera()), the Camera
    screenWidth() and screenHeight() (and hence aspectRatio()) are automatically set and updated
    from the QGLViewer window dimensions. This function then becomes useless and non effective.

    However, when the Camera positioning functions are used to create a shadow map, as seen from a
    virtual light source, this function is needed, since the aspectRatio() of the Camera is used to
    create the projection matrix (see loadProjectionMatrix()). See the (soon available) shadowMap
    example for an illustration.

    \note If you need an aspectRatio() that does not correspond to your viewer window dimensions,
    overload loadProjectionMatrix() or multiply the created GL_PROJECTION matrix by a scaled
    diagonal matrix in your QGLViewer::draw() function. */
    void setAspectRatio(float ar) { screenWidth_=int(100.0*ar); screenHeight_=100; };
    //@}

    
    /*! @name Revolve Around Point */
    //@{
 public slots:
    void setRevolveAroundPoint(const Vec& rap);
    /*! float version of setRevolveAroundPoint(). */
    void setRevolveAroundPoint(float x, float y, float z) { setRevolveAroundPoint(Vec(x,y,z)); };
    bool setRevolveAroundPointFromPixel(int x, int y);
    
  public:    
    /*! With QGLViewer::ROTATE mouse binding, this is the point the camera revolves
    around (defined in world coordinate system). Default value is the sceneCenter().
    \attention setSceneCenter() changes this value. */
    Vec revolveAroundPoint() const { return revolveAroundPoint_; };
    void getRevolveAroundPoint(float& x, float& y, float& z) const;
    //@}

    
    /*! @name Paths
    A camera path is defined by a KeyFrameInterpolator. You can interactively addKeyFrame() to a
    given path using the default QGLViewer shortcut: Alt-F[1-12] (see QGLViewer::setKeyFrameKey()).
    Use playKeyFramePath() to make the camera follow the path (default shortcut is F[1-12]). */
    //@{
   public:
    /*! Returns the number of camera paths that can be defined. This is the maximum number of
    KeyFrameInterpolator that can be saved (index range is 0..\p nbPaths()-1), but some of them
    may not be \e defined (keyFrameInterpolator() will return \c NULL). */
    int nbPaths() const { return nbPaths_; };

    KeyFrameInterpolator* keyFrameInterpolator(unsigned short i) const;

public slots:
    void setKeyFrameInterpolator(unsigned short i, KeyFrameInterpolator* const kfi);

    virtual void addKeyFrame(unsigned short i);
    virtual void playKeyFramePath(unsigned short i);
    virtual void deleteKeyFramePath(unsigned short i);
    virtual void resetKeyFramePath(unsigned short i);

    virtual void drawAllPaths();
    //@}

    
    /*! @name Associated frame */
    //@{
  public:
    /*! The ManipulatedCameraFrame attached to the camera and which defines its position and orientation. See setFrame(). */
    ManipulatedCameraFrame* frame() const { return frame_; };
  public slots:
    void setFrame(ManipulatedCameraFrame* const f);
    //@}
 

    /*! @name OpenGL associated matrices */
    //@{
  public:
    virtual void loadProjectionMatrix(bool reset=true) const;
    virtual void loadProjectionMatrixStereo(bool leftBuffer=true) const;
    virtual void loadModelViewMatrix(bool reset=true) const;
    virtual void loadModelViewMatrixStereo(bool leftBuffer=true) const;

    virtual void getProjectionMatrix(GLdouble m[16]) const;
    virtual void getProjectionMatrix(GLfloat m[16]) const;
    virtual void getModelViewMatrix(GLdouble m[16]) const; 
    virtual void getModelViewMatrix(GLfloat m[16]) const;
    virtual void computeModelViewMatrix() const;
    //@}

    
    /*! @name World to Camera coordinate systems
    Methods to go from the world to the camera coordinate systems, and vice-versa. Simply an
    interface for the Frame equivalent functions. */
    //@{
  public:
    void getCameraCoordinatesOf(const float src[3], float res[3]) const;
    /*! Returns the camera frame coordinates of a point \p src defined in world coordinates.
    worldCoordinatesOf() performs the inverse transformation. */
    Vec cameraCoordinatesOf(const Vec& src) const { return frame()->coordinatesOf(src); };
    void getWorldCoordinatesOf(const float src[3], float res[3]) const;
    /*! Returns the world coordinates of the point whose position is \p src, defined in the camera
    coordinate system. cameraCoordinatesOf() performs the inverse transformation. */
    Vec worldCoordinatesOf(const Vec& src) const { return frame()->inverseCoordinatesOf(src); };
    //@}

    
    /*! @name 2D screen to 3D world coordinate systems
    Methods to go from the 2D screen to the 3D world coordinate systems, and vice-versa. */
    //@{  
  public:
    Vec projectedCoordinatesOf(const Vec& src) const;
    void getProjectedCoordinatesOf(const float src[3], float res[3]) const;
    Vec unprojectedCoordinatesOf(const Vec& src) const;
    void getUnprojectedCoordinatesOf(const float src[3], float res[3]) const;
    void convertClickToLine(int x, int y, float orig[3], float dir[3]) const;
    void convertClickToLine(int x, int y, Vec& orig, Vec& dir) const;
    //@}

        
    /*! @name Stereo mode parameters */
    //@{
  public slots:
    /*! Defines the real inter-ocular distance (in meters). The default value used is 0.062m,
    which fits most people. 
  
    loadProjectionMatrixStereo() uses this value to define the camera offset and frustum */ 
    void setIODist(float iod) { IODist_ = iod; };

    /*! Defines the distance in real world between the observer eyes and the screen -monitor or projection
    wall- in meters. Default value is 0.5m. 
  
    loadProjectionMatrixStereo() uses this value to define the camera offset and frustum.

    distanceToScreen() and distanceToZeroParallaxPlane() represent the same distance.
    distanceToScreen() is expressed in physical real units, while distanceToZeroParallaxPlane() is
    expressed in openGL virtual world units. Use their ratio to convert distances between these
    worlds. */ 
    void setDistanceToScreen(float dts) { distanceToScreen_ = dts; };

    /*! Defines the distance in virtual world between the viewpoint and the plane where the
    horizontal parallax is null, that is to say where the stereo left and right images are
    superimposed. This distance is also referred as the focus distance.
       
    loadProjectionMatrixStereo() uses this value to define the camera offset and frustum.

    distanceToScreen() and distanceToZeroParallaxPlane() represent the same distance.
    distanceToScreen() is expressed in physical real units, while distanceToZeroParallaxPlane() is
    expressed in openGL virtual world units. Use their ratio to convert distances between these
    worlds.
    
    \attention This value is modified by QGLViewer::setSceneRadius(), setSceneRadius() and
    setFieldOfView(). When one of these values is modified, distanceToZeroParallaxPlane() is set to
    sceneRadius() / tan(fieldOfView()/2). */
    void setDistanceToZeroParallaxPlane(float dtz) { distanceToZeroParallaxPlane_ = dtz; };

    /*! Defines the width of the real screen (in meters). Typically 0.4m (default value) for a monitor
    and 10m for the cylindrical wall in Reality Center.
  
    loadProjectionMatrixStereo() uses this value to define the camera offset and frustum. */ 
    void setPhysicalScreenWidth(float sw) { physicalScreenWidth_ = sw; };
  public:
    /*! Returns the inter-ocular distance used for stereo (in meters). Value set using setIODist() */
    float IODist() const { return IODist_; };

    /*! Returns the physical distance to screen (used for stereo mode only). Value is set using
    setDistanceToScreen(). */
    float distanceToScreen() const { return distanceToScreen_; };

    /*! Returns the distance to 0 parallax plane (used for stereo mode only). Value is set using
    setDistanceToZeroParallaxPlane() */
    float distanceToZeroParallaxPlane() const { return distanceToZeroParallaxPlane_; };

    /*! Returns the physical screen width (used for stereo mode only). Value is set using
    setPhysicalScreenWidth() */
    float physicalScreenWidth() const { return physicalScreenWidth_; };
    //@}

  public:
    /*! @name XML representation */
    //@{
    virtual QDomElement domElement(const QString& name, QDomDocument& doc) const;
    virtual void initFromDOMElement(const QDomElement& de);
    //@}


    /*! @name Scene radius and center */
    //@{
  public:  
    /*! Returns the scene radius used by the camera. Used to set the camera near and far planes (see
    zNear() and zFar()). This value is modifed by QGLViewer::setSceneRadius(), which simply calls
    setSceneRadius(). */
    float sceneRadius() const { return sceneRadius_; };

    /*! Returns the position of the scene center. This value is set setSceneCenter(), which is
    called by QGLViewer::setSceneCenter(). Default is 0,0,0 (world origin). */
    Vec sceneCenter() const { return sceneCenter_; };

    void setSceneRadius(float r);
    void setSceneBoundingBox(const Vec& m, const Vec& M);
    void setSceneCenter(const Vec& sc);
    void setSceneCenter(float x, float y, float z);
    bool setSceneCenterFromPixel(int x, int y);
    //@}


    
    /*! @name Internal methods */
    //@{
  protected:  
    /*! Returns \c true if the camera paths are being edited in the viewer. Set by
    QGLViewer::editCameraPath() or QGLViewer::toggleCameraPathEditor(). See
    QGLViewer::cameraPathIsEdited() for details. */
    bool cameraPathIsEdited() const { return cameraPathIsEdited_; };

  protected slots :
    /*! Starts or stops the edition of the camera paths. Called by QGLViewer::editCameraPath() and
    QGLViewer::toggleCameraPathEditor(). Get current value with cameraPathIsEdited(). */
    void editCameraPath(bool edit) { cameraPathIsEdited_ = edit; };

    /*! Update a copy of the QGLViewer window dimensions. Called by the QGLViewer when it is resized.

    You should not call this function directly, as the QGLViewer does it. However, if your Camera is
    used \e outside of a QGLViewer (offscreen rendering, shadow maps), you need to provide the
    screen width and height (see screenWidth() and screenHeight()) in order to define the camera
    aspectRatio() which is used to define the projection matrix in loadProjectionMatrix(). */
    void setWindowWidthAndHeight(int w, int h);
    //@}


  private:
    // Copy constructor and opertor= are declared private and undefined
    // Prevents everyone from trying to use them
    Camera(const Camera& v);
    Camera& operator=(const Camera& v);

    // F r a m e
    ManipulatedCameraFrame* frame_;
    
    // C a m e r a   p a r a m e t e r s
    int screenWidth_, screenHeight_;  // size of the window, in pixels
    float fieldOfView_;
    float sceneRadius_;
    float zNearCoef_;
    float orthoCoef_;
    Vec sceneCenter_;
    Vec revolveAroundPoint_;
    Type type_; // PERSPECTIVE or ORTHO
    mutable GLdouble modelViewMatrix_[16]; // Buffered model view matrix.

    bool cameraPathIsEdited_; // camera path edition mode
    
    // S t e r e o   p a r a m e t e r s 
    float IODist_;			// inter-ocular distance
    float distanceToScreen_;		// in meters
    float distanceToZeroParallaxPlane_;	// in scene units
    float physicalScreenWidth_;		// in meters

    // P o i n t s   o f   V i e w s   a n d   K e y F r a m e s 
    enum { nbPaths_ = 12 };
    KeyFrameInterpolator* kfi_[nbPaths_];
    unsigned short lastActivatedKFNumber_; // Prevents two simultaneous path interpolations
    KeyFrameInterpolator* interpolationKfi_;
  };


////////////////////// Deprecated functions /////////////////
// #define __WHERE__ "In file "<<__FILE__<<", line n°"<<__LINE__<< ", use "
// #define orientationAxisAngle(x,y,z,a) 	{ std::cout << __WHERE__ << "getOrientationAxisAngle()." << std::endl; exit(0); }

} // namespace qglviewer

#endif // QGLVIEWER_CAMERA_H
