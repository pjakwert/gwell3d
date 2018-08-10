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

#include "camera.h"
#include "qglviewer.h"

// #include <GL/glu.h> has been moved to config.h for configuration simplification

using namespace std;
using namespace qglviewer;

/*! Default values are given to the camera parameters : sceneCenter=(0,0,0),
  sceneRadius=1.0, camera type = PERSPECTIVE, default stereo parameters, .... */
Camera::Camera()
  : screenWidth_(600), screenHeight_(400), fieldOfView_(M_PI/4.0), zNearCoef_(0.001),
    type_(PERSPECTIVE), cameraPathIsEdited_(false), lastActivatedKFNumber_(0)
{
  interpolationKfi_ = new KeyFrameInterpolator;
  setFrame(new ManipulatedCameraFrame());

  setSceneRadius(1.0);
  setSceneCenter(Vec(0.0, 0.0, 0.0));
  revolveAroundPoint_ = sceneCenter();
  
  orthoCoef_ = tan(fieldOfView() / 2.0);
  setIODist(0.062);
  setDistanceToScreen(0.5);
  setPhysicalScreenWidth(0.4);  
  setDistanceToZeroParallaxPlane(sceneRadius() / tan(fieldOfView()/2.0));
  
  for (unsigned short i=0; i<nbPaths(); ++i)
    kfi_[i] = NULL;

  for (unsigned short j=0; j<16; ++j)
    modelViewMatrix_[j] = ((j%5 == 0) ? 1.0 : 0.0);

  frame()->setRotateAroundCenter();
}

/*! Virtual destructor. Current frame() is deleted. */
Camera::~Camera()
{
  delete frame_;
  delete interpolationKfi_;
}

/*! Set internal width and height values. Called by the QGLViewer when it is resized.*/
void Camera::setWindowWidthAndHeight(int w, int h)
{
  screenWidth_  = w;
  screenHeight_ = h;
}

/*! Returns the zNear value used by the projection matrix. This value is fitted to sceneCenter() and
sceneRadius() in order to ensure an optimal z sampling:
\code
float coef = sqrt(2.0); // so that a 1x1 grid fits
if (cameraPathIsEdited())
  coef = 5.0;
zNear = distanceToSceneCenter() - coef*sceneRadius();

// Prevents negative or null zNear values.
if (zNear < zNearCoef() * sceneRadius())
   switch (type())
   {
   case Camera::PERSPECTIVE : zNear = zNearCoef() * sceneRadius(); break;
   case Camera::ORTHO       : zNear = 0.0; break;
   }
\endcode

Returned value is clipped when the camera is inside the scene sphere to prevent negative or too
small zNear() values (see setZNearCoef()).

The \p coef of 5.0 in front of \p sceneRadius() is used to prevent a clipping of the camera paths
when QGLViewer::cameraPathIsEdited().

\attention The value is always positive and is the opposite of the camera frame actual value
(always negative). This is done in order to fit the \p gluPerspective positive standard. */
float Camera::zNear() const
{
  float coef = sqrt(2.0); // so that a 1x1 grid fits
  if (cameraPathIsEdited())
    coef = 5.0;
  float z = distanceToSceneCenter() - coef*sceneRadius();
  
  // Prevents negative or null zNear values.
  if (z < zNearCoef() * sceneRadius())
    switch (type())
    {
    case Camera::PERSPECTIVE : z = zNearCoef() * sceneRadius(); break;
    case Camera::ORTHO       : z = 0.0; break;
    }
  return z;
}

/*! Returns the zFar value used by the projection matrix. This value is fitted to sceneCenter() and
sceneRadius() in order to ensure an optimal z sampling:
\code
  float coef = sqrt(2.0); // so that a 1x1 grid fits
  if (cameraPathIsEdited())
    coef = 5.0;
  zFar=distanceToSceneCenter() + coef*sceneRadius();
\endcode

The \p coef of 5.0 in front of \p sceneRadius() is used to prevent a clipping of the camera paths
when QGLViewer::cameraPathIsEdited().

\attention The value is always positive and is the opposite of the camera frame actual value which
is always negative. This is done in order to fit the \p gluPerspective positive standard. */
float Camera::zFar() const
{
  float coef = sqrt(2.0); // so that a 1x1 grid fits
  if (cameraPathIsEdited())
    coef = 5.0;
  return distanceToSceneCenter() + coef*sceneRadius();
}

/*! Defines the camera type. Supported types are defined by the Type() enum.
loadProjectionMatrix() will create the camera accordingly. Use type() to get the current value.
\code
myViewer.camera()->setType(qglviewer::Camera::ORTHO);
myViewer.camera()->showEntireScene();
\endcode
In ORTHO mode, the fieldOfView() is meaningless and the width and height of the camera frustum
are inferred from the distance to the revolveAroundPoint() (see getOrthoWidthHeight()). */
void Camera::setType(Type type)
{
  // make ORTHO frustum fit PERSPECTIVE (at least in plane normal to viewDirection(), passing through RAP)
  if (type == Camera::ORTHO)
    orthoCoef_ = tan(fieldOfView()/2.0);
  type_ = type;
}

/*! Changes the ManipulatedCameraFrame that defines the position and orientation of the camera. If you
simply want to move the camera, use setPosition() and setOrientation() or one of the camera
positioning functions : lookAt(), fitSphere(), fitBoundingBox(), showEntireScene()...

If you want to save camera positions, there's no real need to call this function either. Use
addKeyFrame() and playKeyFramePath() for this.

This function is actually mainly useful if you derive the ManipulatedCameraFrame class and want
to use an instance of your new class to move the camera.

A \p NULL frame pointer will silently be ignored. The calling function is responsible for
deleting the previous frame() pointer if needed in order to prevent memory leaks :
\code
delete camera()->frame();
camera()->setFrame(myManipulatedCameraFrame());
\endcode */
void Camera::setFrame(ManipulatedCameraFrame* const f)
{
  if (!f)
    return;
  frame_ = f;
  interpolationKfi_->setFrame(frame());
}

/*! Returns the distance from the camera center to sceneCenter(), \e projected along the camera Z
  axis. Used by zNear() and zFar() to optimize the Z range. */
float Camera::distanceToSceneCenter() const
{
  return fabs((frame()->coordinatesOf(sceneCenter())).z);
}


/*! Returns the half width \p w and half height \p h of the camera frustum. These results are only
  valid when the Camera is in ORTHO type(). Results are expressed in openGL units. These values are
  used by loadProjectionMatrix() to define the \p glOrtho( -w, w, -h, h, zNear(), zFar() )
  projection matrix. */
void Camera::getOrthoWidthHeight(GLdouble& w, GLdouble& h) const
{
  const float dist = orthoCoef_ * fabs(cameraCoordinatesOf(revolveAroundPoint()).z);
  //#CONNECTION# fitScreenRegion
  w = dist * ((aspectRatio() < 1.0) ? 1.0 : aspectRatio());
  h = dist * ((aspectRatio() < 1.0) ? 1.0/aspectRatio() : 1.0);
}

/*! Load the current camera GL_PROJECTION matrix. Default method set camera according to
 fieldOfView(), and window aspect ratio in PERSPECTIVE type(). See getOrthoWidthHeight() for ORTHO
 type().

 Uses zNear() and zFar() which are determined from sceneRadius() and sceneCenter() so that
 they best fit the scene size.
 
 Camera type is returned by type(), and is set with setType().
 
 When \p reset is \p true (default), it clears the previous projection matrix by calling \p
 glLoadIdentity before setting the matrix. Setting \p reset to \p false is usefull for GL_SELECT
 mode, to combine the matrix with a picking matrix.
 
 getProjectionMatrix() returns the 4x4 projection matrix.
  
 \attention glMatrixMode is set to GL_PROJECTION
 \attention makeCurrent() must be called by every calling method. */
void Camera::loadProjectionMatrix(bool reset) const
{
  // WARNING : makeCurrent must be called by every calling function
  glMatrixMode(GL_PROJECTION);

  if (reset)
    glLoadIdentity();

  switch (type_)
    {
    case Camera::PERSPECTIVE:
      gluPerspective( 180.0*fieldOfView()/M_PI, aspectRatio(), zNear(), zFar() );
      break;
    
    case Camera::ORTHO:
      {
	GLdouble w, h;
	getOrthoWidthHeight(w,h);
	glOrtho( -w, w, -h, h, zNear(), zFar() );
	break;
      }
    }
}

/*! Load the current camera GL_PROJECTION matrix for Stereo mode.
 Only PERSPECTIVE camera type() case is handled.
 
 Uses zNear() and zFar() which are determined from sceneRadius() and sceneCenter() so that
 they best fit the scene size.
 
 Uses distanceToZeroParallaxPlane(), IODist(), and  physicalScreenWidth() to compute
 cameras offset for stereovision, as well as asymmetric frustums 
  
 Camera type is returned by type(), and is set with setType().
 
 When \p leftBuffer is \p true (default), computes the projection matrix
 for left camera (right camera otherwise).
 
 getProjectionMatrix() will always return the 4x4 \b mono projection matrix.
 \attention glMatrixMode is set to GL_PROJECTION
 \attention makeCurrent() must be called by every calling method. */
void Camera::loadProjectionMatrixStereo(bool leftBuffer) const
{
  float left, right, bottom, top;
  float  screenHalfWidth, halfWidth, side, shift, delta;
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  switch(type_)
    {
    case Camera::PERSPECTIVE:
      // compute half width of screen,
      // corresponding to zero parallax plane to deduce decay of cameras
      screenHalfWidth = distanceToZeroParallaxPlane() * tan(horizontalFieldOfView() / 2.0);
      shift = screenHalfWidth * IODist() / physicalScreenWidth();
      // should be * current y  / y total
      // to take into account that the window doesn't cover the entire screen

      // compute half width of "view" at znear and the delta corresponding to
      // the shifted camera to deduce what to set for asymmetric frustums
      halfWidth = zNear() * tan(horizontalFieldOfView() / 2.0);
      delta  = shift * zNear() / distanceToZeroParallaxPlane();
      side   = leftBuffer ? -1.0 : 1.0;
      
      left   = -halfWidth + side * delta;
      right  =  halfWidth + side * delta;
      top    = halfWidth / aspectRatio();
      bottom = -top;
      glFrustum(left, right, bottom, top, zNear(), zFar() );
      break;

    case Camera::ORTHO:
      qWarning("Camera::setProjectionMatrixStereo : Stereo not available with Ortho mode");
      break;
    }
}

/*! Set \p m to the current projection matrix. \p m is an array of 16 floats.
  See also getProjectionMatrix(GLdouble m[16]).
 \attention \p glMatrixMode is set to \p GL_PROJECTION. */
void Camera::getProjectionMatrix(GLfloat m[16]) const
{
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  loadProjectionMatrix();
  glGetFloatv(GL_PROJECTION_MATRIX, m);
  glPopMatrix();
}

/*! This function is provided for convenience, in case you want to work with double instead of
 floats, see getProjectionMatrix(GLfloat m[16]) for explanations. */
void Camera::getProjectionMatrix(GLdouble m[16]) const
{
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  loadProjectionMatrix();
  glGetDoublev(GL_PROJECTION_MATRIX, m);
  glPopMatrix();
}

/*! Computes the model view matrix associated with the camera state. Called by loadModelViewMatrix()
  before each drawing. You need to call this function if you use the model view matrix \e out of the
  main drawing loop (unlikely), for a (un) projectedCoordinatesOf() or a getModelViewMatrix() for
  instance. */
void Camera::computeModelViewMatrix() const
{
  const Quaternion q = frame()->orientation();

  const double q00 = 2.0l * q[0] * q[0];
  const double q11 = 2.0l * q[1] * q[1];
  const double q22 = 2.0l * q[2] * q[2];

  const double q01 = 2.0l * q[0] * q[1];
  const double q02 = 2.0l * q[0] * q[2];
  const double q03 = 2.0l * q[0] * q[3];

  const double q12 = 2.0l * q[1] * q[2];
  const double q13 = 2.0l * q[1] * q[3];

  const double q23 = 2.0l * q[2] * q[3];

  modelViewMatrix_[0] = 1.0l - q11 - q22;
  modelViewMatrix_[1] =        q01 - q23;
  modelViewMatrix_[2] =        q02 + q13;
  modelViewMatrix_[3] = 0.0l;
   
  modelViewMatrix_[4] =        q01 + q23;
  modelViewMatrix_[5] = 1.0l - q22 - q00;
  modelViewMatrix_[6] =        q12 - q03;
  modelViewMatrix_[7] = 0.0l;
   
  modelViewMatrix_[8] =        q02 - q13;
  modelViewMatrix_[9] =        q12 + q03;
  modelViewMatrix_[10] = 1.0l - q11 - q00;
  modelViewMatrix_[11] = 0.0l;

  const Vec t = q.inverseRotate(frame()->position());

  modelViewMatrix_[12] = -t.x;
  modelViewMatrix_[13] = -t.y;
  modelViewMatrix_[14] = -t.z;
  modelViewMatrix_[15] = 1.0l;
}

/*! Loads the current camera GL_MODELVIEW matrix.
 
 When \p reset is \p true (default), it clears the previous projection matrix
 by calling \c glLoadMatrixd. Setting \p reset to \p false simply calls \c glMultMatrixd
 (might be useful for some applications).
 
 getModelViewMatrix() returns the current 4x4 model view matrix.
 
 \attention glMatrixMode is set to GL_MODELVIEW
 
 \attention makeCurrent() must be called by every calling method if this function is used out of
  the main drawing loop (i.e. not in QGLViewer::draw() or in QGLViewer::preDraw()). */
void Camera::loadModelViewMatrix(bool reset) const
{
  // WARNING : makeCurrent must be called by every calling function
  glMatrixMode(GL_MODELVIEW);
  computeModelViewMatrix();
  if (reset)
    glLoadMatrixd(modelViewMatrix_);
  else
    glMultMatrixd(modelViewMatrix_);
}


/*! Loads the GL_MODELVIEW matrix for stereo mode. It clears the previous modelview matrix by
 calling \c glLoadIdentity before setting the matrix. When \p leftBuffer is \p true (resp. false),
 it performs a left (resp. right) buffer translation by modifying the translation term directly in
 the modelView matrix.
 
 \attention glMatrixMode is set to \c GL_MODELVIEW
 
 \attention makeCurrent() must be called by every calling method if this function is used out of the
  main drawing loop (i.e. not in QGLViewer::draw() or in QGLViewer::preDraw()).. */
void Camera::loadModelViewMatrixStereo(bool leftBuffer) const
{
  // WARNING : makeCurrent must be called by every calling function
  glMatrixMode(GL_MODELVIEW);

  float halfWidth = distanceToZeroParallaxPlane() * tan(horizontalFieldOfView() / 2.0);
  float shift     = halfWidth * IODist() / physicalScreenWidth(); // * y actuel / y total
  
  computeModelViewMatrix();
  if (leftBuffer)
    modelViewMatrix_[12] -= shift;
  else
    modelViewMatrix_[12] += shift;
  glLoadMatrixd(modelViewMatrix_);  
}


/*! Set \p m to the current \e camera model view matrix. This modelView matrix is usually \e not the
 one you would get from a \p glGetFloatv(GL_MODELVIEW_MATRIX). Instead, it only represents the
 Camera to world coordinate system transformation matrix. As soon as you modify the
 \p GL_MODELVIEW_MATRIX in your QGLViewer::draw() function, the two matrices differ.
 
 This matrix actually represents the state of the \p GL_MODELVIEW_MATRIX after
 QGLViewer::preDraw(), at the beginning of QGLViewer::draw().
 
 \attention If you call this function out of the classical drawing loop (QGLViewer::draw() or
 QGLViewer::postDraw()), you need to call computeModelViewMatrix() before this function, so that
 the model view matrix is properly updated.
 
 \attention The result is an openGL 4x4 matrix, which is given in \e column-major order (see \p
 glMultMatrix man page for details).
 
 See also getModelViewMatrix(GLdouble m[16]) and loadModelViewMatrix(). */
void Camera::getModelViewMatrix(GLfloat m[16]) const
{
  for (unsigned short i=0; i<16; ++i)
    m[i] = static_cast<float>(modelViewMatrix_[i]);
}


/*! This function is provided for convenience, in case you want to work with double instead of
 floats, see getModelViewMatrix(GLfloat m[16]) for explanations. */
void Camera::getModelViewMatrix(GLdouble m[16]) const
{
  for (unsigned short i=0; i<16; ++i)
    m[i] = modelViewMatrix_[i];
}

/*! Scene radius (see sceneRadius()) scales axis and grid display and is used by zNear() and zFar().
Should be set according to the displayed scene radius. This value is updated by the
QGLViewer::setSceneRadius().

distanceToZeroParallaxPlane() is set to sceneRadius()/tan(fieldOfView()/2) (used only for stereo
mode, see QGLViewer::setStereoDisplay(), setFieldOfView() and setDistanceToZeroParallaxPlane()).

See also setSceneBoundingBox(). */
void Camera::setSceneRadius(float r)
{
  if (r <= 0.0)
    {
      qWarning("Scene radius must be positive - Ignoring");
      return;
    }
  
  sceneRadius_ = r;
  
  setDistanceToZeroParallaxPlane(sceneRadius_ / tan(fieldOfView()/2.0));
  
  frame()->setFlySpeed(0.01*r);
}

/*! Similar to setSceneRadius() and setSceneCenter(), but the scene limits are defined by a bounding box. */
void Camera::setSceneBoundingBox(const Vec& m, const Vec& M)
{
  setSceneCenter((m+M)/2.0);
  setSceneRadius(0.5*(M-m).norm());
}

/*! Same as position(), but with float parameters. */
void Camera::getPosition(float& x, float& y, float& z) const
{
  Vec r = position();
  x = r[0];
  y = r[1];
  z = r[2];
}
  
/*! Same as setSceneCenter(), but with \p float parameters. */
void Camera::setSceneCenter(float x, float y, float z)
{
  setSceneCenter(Vec(x,y,z));
}

/*! Changes the sceneCenter value (used for zNear() and zFar()).
 This value is set from QGLViewer::setSceneCenter().
 \attention revolveAroundPoint() is set to sceneCenter() by this method. */
void Camera::setSceneCenter(const Vec& sc)
{
  sceneCenter_ = sc;
  setRevolveAroundPoint(sceneCenter());
}

/*! Changes the revolveAroundPoint(), which defines the position (in world coordinates) of the 3D
  point the camera revolves around in QGLViewer::ROTATE mode. Current value can be get from
  revolveAroundPoint(). Default value is sceneCenter(), which default value is (0,0,0).
  
  The zNear() and zFar() values are fitted to the scene, which will be entirely visible if
  revolveAroundPoint() is located inside a sceneRadius() sphere centered on sceneCenter().
  
  The camera position and orientation are not modified so that the image displayed by the camera
  is not affected by the revolveAroundPoint() change.
  \attention This value is modified by setSceneCenter(). */
void Camera::setRevolveAroundPoint(const Vec& rap)
{
  const float prevDist = fabs(cameraCoordinatesOf(revolveAroundPoint()).z);
  revolveAroundPoint_ = rap;

  // orthoCoef_ is used to compensate for changes of the RevolveAroundPoint, so that the image does
  // not change when the RevolveAroundPoint is changed in ORTHO mode.
  const float newDist = fabs(cameraCoordinatesOf(revolveAroundPoint()).z);
  // Prevents division by zero when rap is set to camera position
  if ((prevDist > 1E-5) && (newDist > 1E-5))
    orthoCoef_ *= prevDist / newDist;
}

/*! float version of revolveAroundPoint(). */
void Camera::getRevolveAroundPoint(float& x, float& y, float& z) const
{
  Vec rap = revolveAroundPoint();
  x = rap.x;
  y = rap.y;
  z = rap.z;
}

/*! Returns the pixel to GL unit ratio. A line of \c n * pixelGLRatio() GL units, located at
  position \p pos in the world coordinates system, will be projected with a length of \c n pixels on
  screen. Use this function to scale objects so that they have a constant pixel size on screen.

  The following code will draw a 20 pixel line, starting at sceneCenter() and always directed along
  the screen vertical direction.
  \code
  glBegin(GL_LINES);
  glVertex3fv(sceneCenter().address());
  glVertex3fv((sceneCenter() + 20*pixelGLRatio(sceneCenter())*upVector()).address());
  glEnd();
  \endcode
  
  \attention The resulting value is only valid for a given Camera and a given \p pos. It
  also naturally depends on the current screen height (see screenHeight()). */
float Camera::pixelGLRatio(const Vec& pos)
{
  switch (type())
    {
    case Camera::PERSPECTIVE :
      return 2.0 * fabs((frame()->coordinatesOf(pos)).z) * tan(fieldOfView()/2.0) / screenHeight();
      break;
    case Camera::ORTHO :
      {
	GLdouble w, h;
	getOrthoWidthHeight(w,h);
	return 2.0 * h / screenHeight();
	break;
      }
    }
  // Bad compilers complain
  return 0.0;
}

/*! The revolveAroundPoint() is set to the point located at pixel (x,y) on screen.

Returns \p true if a pointUnderPixel() was found. If no point was found under the pixel, the
revolveAroundPoint() is unchanged.

This function is called when you press the right mouse button and then double click the left button.
See <a href="../mouse.html">mouse page</a> for details. */
bool Camera::setRevolveAroundPointFromPixel(int x, int y)
{
  bool found;
  Vec point = pointUnderPixel(x,y, found);
  if (found)
    setRevolveAroundPoint(point);
  return found;
}


/*! setSceneCenter() to the result of pointUnderPixel() (if a point was found). 

  Returns \p true if a pointUnderPixel() was found and sceneCenter() was changed. */
bool Camera::setSceneCenterFromPixel(int x, int y)
{
  bool found;
  Vec point = pointUnderPixel(x,y, found);
  if (found)
    setSceneCenter(point);
  return found;
}

/*! Change the camera fieldOfView() so that the entire scene (defined by QGLViewer;;sceneCenter()
and QGLViewer::sceneRadius()) would be visible from the current camera position(). The position()
and orientation() of the camera are not modified and you have to properly orientate the camera in
order to actually \e see the scene (see lookAt()). See also showEntireScene() and fitSphere().

This function is especially useful for \e shadow \e maps computation. Use the camera positioning
tools (setPosition(), lookAt()) to position a camera at the light position. Use setFOVToFitScene()
to define an optimal fieldOfView() for this camera, so that the shadow map resolution is optimally
used.

\code
  // The light camera needs size hints in order to optimize FOV
  light_camera->setSceneRadius(sceneRadius());
  light_camera->setSceneCenter(sceneCenter());

  // Place the light camera.
  light_camera->setPosition(light_frame->position());
  light_camera->lookAt(sceneCenter());
  light_camera->setFOVToFitScene();
\endcode

Use a viewer QGLViewer::displayZBuffer() function to actually see the computed shadow map. See the
shadowMap contribution example for a practical implementation.

\attention The fieldOfView() is clamped to M_PI/2.0. It happens when the camera is at a distance
lower than sqrt(2) * sceneRadius() from the sceneCenter(). This behavior is especially useful for
shadow map computation in order to optimize the shadow map resolution, although it may miss some
parts of the scene. */
void Camera::setFOVToFitScene()
{
  const float dist = (position() - sceneCenter()).norm();
  if (dist > sqrt(2.0)*sceneRadius())
    setFieldOfView(2.0 * asin(sceneRadius() / dist));
  else
    setFieldOfView(M_PI / 2.0);
}

/*! Make the camera zoom on the selected pixel (if an object is actually drawn in this pixel, see
pointUnderPixel()). A KeyFrameInterpolator is created and animates the camera on a one second path
that brings the camera closer to the selected pixel. See also interpolateToFitScene().

This function is called when you press the middle mouse button and then double click the left
button. See <a href="../mouse.html">mouse page</a> for details. */
void Camera::interpolateToZoomOnPixel(int x, int y)
{
  const float coef = 0.1f;
  
  bool found;
  Vec target = pointUnderPixel(x, y, found);

  if (!found)
    return;

  if (interpolationKfi_->interpolationIsStarted())
    interpolationKfi_->stopInterpolation();

  interpolationKfi_->deletePath();
  interpolationKfi_->addKeyFrame(*(frame()));

  interpolationKfi_->addKeyFrame(Frame(0.3*frame()->position() + 0.7*target, frame()->orientation()), 0.4);

  // Small hack : attach a temporary frame to take advantage of lookAt without modifying current frame
  static ManipulatedCameraFrame* tempFrame = new ManipulatedCameraFrame();
  ManipulatedCameraFrame* const originalFrame = frame();
  tempFrame->setPosition(coef*frame()->position() + (1.0-coef)*target);
  tempFrame->setOrientation(frame()->orientation());
  setFrame(tempFrame);
  lookAt(target);
  setFrame(originalFrame);

  interpolationKfi_->addKeyFrame(*(tempFrame), 1.0);
  
  interpolationKfi_->startInterpolation();
}

/*! Inperpolates the camera position on a one second KeyFrameInterpolator path stating from the
current position, so that at the end the entire scene is visible and fits in screen (see
showEntireScene()). See also interpolateToZoomOnPixel().

This function is called when you press the middle mouse button and then double click the right
button. See <a href="../mouse.html">mouse page</a> for details. */
void Camera::interpolateToFitScene()
{
  if (interpolationKfi_->interpolationIsStarted())
    interpolationKfi_->stopInterpolation();

  interpolationKfi_->deletePath();
  interpolationKfi_->addKeyFrame(*(frame()));

  // Small hack : attach a temporary frame to take advantage of lookAt without modifying current frame
  static ManipulatedCameraFrame* tempFrame = new ManipulatedCameraFrame();
  ManipulatedCameraFrame* const originalFrame = frame();
  tempFrame->setPosition(frame()->position());
  tempFrame->setOrientation(frame()->orientation());
  setFrame(tempFrame);
  showEntireScene();
  setFrame(originalFrame);

  interpolationKfi_->addKeyFrame(*(tempFrame));
  
  interpolationKfi_->startInterpolation();
}

/*! Returns the coordinates of the 3D point located at pixel (x,y) on screen (origin in the \e upper
  left corner). Calls a \c glReadPixel to get the pixel depth and applies an
  unprojectedCoordinatesOf() to the result. \p found indicates whether a point was found or not
  (i.e. background pixel, result's depth is zFar() in that case).

  \attention The precision of the ZBuffer highly depends on how tight to your scene are the
  zNear() and zFar() values. Imprecision may result along the viewing direction otherwise. See
  QGLViewer::setSceneCenter(), QGLViewer::setSceneRadius() and setZNearCoef(). */
Vec Camera::pointUnderPixel(const int x, const int y, bool& found)
{
  float depth;
  // Qt uses upper corner for its origin while GL uses the lower corner.
  glReadPixels(x, screenHeight()-y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
  found = depth < 1.0;
  Vec point(x, y, depth);
  point = unprojectedCoordinatesOf(point);
  return point;
}

/*! Moves the camera so that the bounding box \p m,M is entirely visible, using fitSphere().
 
 \p m and \p M are two extremal corners of the Bounding Box. */
void Camera::fitBoundingBox(const Vec& m,const Vec& M)
{
  float diam = QMAX(fabs(M[1]-m[1]), fabs(M[0]-m[0]));
  diam = QMAX(fabs(M[2]-m[2]), diam);
  fitSphere(0.5*(m+M), 0.5*diam);
}

/*! Adjust the camera so that the entire scene is visible. The camera is \e translated to make the
  entire scene fit the window, its orientation() is unchanged. The scene is defined by the
  QGLViewer::sceneCenter() and QGLViewer::sceneRadius(). The fieldOfView() is \e not modified by
  this function.

  QGLViewer::showEntireScene() simply calls this function. See also setFOVToFitScene().

  You will typically use this function in QGLViewer::init():
  \code
  setSceneRadius(3.0);
  showEntireScene();
  \endcode
 
  You should orientate the camera \e before you call this function. See lookAt(), setOrientation()
  and setUpVector().

  By default the QGLViewer::sceneRadius() is 1.0, and the QGLViewer constructor calls this function.
  See also centerScene().

  ManipulatedCameraFrame::mouseDoubleClickEvent() calls this function after a middle button double
  click. */
void Camera::showEntireScene()
{
  fitSphere(sceneCenter(), sceneRadius());
}

/*! Move the camera so that the sceneCenter() is projected on the center of the window. The
orientation() and fieldOfView() are unchanged.

ManipulatedCameraFrame::mouseDoubleClickEvent() calls this function after a right button double
click.

See also showEntireScene().*/
void Camera::centerScene()
{
  frame()->projectOnLine(sceneCenter(), viewDirection());
}

/*! Set the camera orientation, so that it looks at point \p target (defined in the world coordinate
 system). The camera position is not modified. The camera is rotated so that the horizon is
 preserved. See also setOrientation(), showEntireScene(), setUpVector(), fitSphere() and
 fitBoundingBox(). */
void Camera::lookAt(const Vec& target)
{  
  const Vec zAxis = position() - target;
  if (zAxis.sqNorm() < 1E-10)
    // target is at current position
    return;
  
  Vec xAxis = upVector() ^ zAxis;
  if (xAxis.sqNorm() < 1E-10)
    {
      // target is aligned with upVector, this means a rotation around X axis
      // X axis is then unchanged, let's keep it !
      xAxis = frame()->inverseTransformOf(Vec(1.0, 0.0, 0.0));
    }

  Quaternion q;
  q.setFromRotatedBase(xAxis, zAxis^xAxis, zAxis);
  frame()->setOrientationWithConstraint(q);
}

/*! Moves the camera so that the sphere (\p center, \p radius) is visible and fits the window. The
 camera is \e translated so that the sphere fits the screen, its orientation() and fieldOfView() are
 unchanged. */
void Camera::fitSphere(const Vec& center, float radius)
{
  float distance = 0.0f;
  switch (type())
    {
    case Camera::PERSPECTIVE :
      {
	const float yview = radius / sin(fieldOfView()/2.0);
	const float xview = radius / sin(horizontalFieldOfView()/2.0);
	distance = QMAX(xview,yview);
	break;
      }
    case Camera::ORTHO :
      {
	distance = ((center-revolveAroundPoint()) * viewDirection()) + (radius / orthoCoef_);
	break;
      }
    }
  Vec newPos(center - distance * viewDirection());
  frame()->setPositionWithConstraint(newPos);
}

/*! Moves the camera so that the screen region defined by (\p xa, \p ya), (\p xb, \p yb) fits the
  screen. Parameters are expressed in pixels, with origin in the upper left corner.

  The camera is translated (its orientation() is unchanged) so that the input rectangle is entirely
  visible. Since the pixel coordinates only define a \e frustum in 3D, it's the intersection of the
  frustum with a plane (orthogonal to the viewDirection() and passing through the sceneCenter())
  that is used to define the 3D rectangle that is fitted. */
void Camera::fitScreenRegion(int xa, int ya, int xb, int yb)
{
  const Vec vd = viewDirection();
  const float distToPlane = distanceToSceneCenter();
  
  Vec orig, dir;
  convertClickToLine((xa+xb)/2, (ya+yb)/2, orig, dir); 
  Vec newCenter = orig + distToPlane / (dir*vd) * dir;
  
  convertClickToLine(xa, (ya+yb)/2, orig, dir);
  const Vec pointX = orig + distToPlane / (dir*vd) * dir;

  convertClickToLine((xa+xb)/2, ya, orig, dir);
  const Vec pointY = orig + distToPlane / (dir*vd) * dir;

  float distance = 0.0f;
  switch (type())
    {
    case Camera::PERSPECTIVE :
      {
	const float distX = (pointX-newCenter).norm() / sin(horizontalFieldOfView()/2.0);
	const float distY = (pointY-newCenter).norm() / sin(fieldOfView()/2.0);
	distance = QMAX(distX, distY);
	break;
      }
    case Camera::ORTHO :
      {
	const float dist = ((newCenter-revolveAroundPoint()) * vd);
	//#CONNECTION# getOrthoWidthHeight
	const float distX = (pointX-newCenter).norm() / orthoCoef_ / ((aspectRatio() < 1.0) ? 1.0 : aspectRatio());
	const float distY = (pointY-newCenter).norm() / orthoCoef_ / ((aspectRatio() < 1.0) ? 1.0/aspectRatio() : 1.0);
	distance = dist + QMAX(distX, distY);
	break;
      }
    }

  Vec newPos(newCenter - distance * vd);
  frame()->setPositionWithConstraint(newPos);
}

/*! Rotates the camera such that its up vector becomes \p up (defined in the world coordinate
 system). Only the orientation (not the position) of the camera is changed. The camera will be
 rotated around an axis orthogonal to \p up and to the current upVector() direction.

 Use this function in order to define the horizontal plane in fly mode
 (QGLViewer::MOVE_FORWARD or QGLViewer::MOVE_BACKWARD binding).
  
 However it might be interesting to compensate the orientation modification by a translation, so
 that the revolveAroundPoint() stays projected at the same position on screen. This is especially
 useful when the camera is an observer of the scene (default mouse binding) and it can be achieved
 when \p noMove is set to \p false. The default value for \p noMove is \p true, which results in an
 intuitive behavior when the camera is in a walkthrough fly mode (see QGLViewer::MOVE_FORWARD). */
void Camera::setUpVector(const Vec& up, bool noMove)
{
  Quaternion q(Vec(0.0, 1.0, 0.0), frame()->transformOf(up));

  if (!noMove)
    frame()->setPosition(revolveAroundPoint() - (frame()->orientation()*q).rotate(frame()->coordinatesOf(revolveAroundPoint())));

  frame()->rotate(q);

  // Useful in fly mode to keep the horizontal direction.
  frame()->updateFlyUpVector();
}

/*! Return the current up vector of the camera, defined in the world coordinate system. See also
  setUpVector().

  Simply returns :
  \code
  frame()->inverseTransformOf(Vec(0.0,1.0,0.0));
  \endcode */
Vec Camera::upVector() const
{
  return frame()->inverseTransformOf(Vec(0.0,1.0,0.0));
}

/*! Same as upVector(), but with float parameters. */
void Camera::getUpVector(float& x, float& y, float& z) const
{
  const Vec upVector_ = upVector();
  x = upVector_.x;
  y = upVector_.y;
  z = upVector_.z;
}

/*! Set the orientation of the camera using polar coordinates \p theta and \p phi (in radians). \p
  theta rotates around the camera Y axis, and \e then \p phi rotates around the camera X axis. \p
  theta = \p phi = 0 means that the camera is directed towards the world Z axis. See also
  setUpVector(). The position() of the camera is unchanged, you may want to call showEntireScene()
  after this function to move the camera.
 
 This function can be useful to create Quicktime VR panoramic sequences, see
 QGLViewer::saveSnapshot() for details. */
void Camera::setOrientation(float theta, float phi)
{
  Vec axis(0.0, 1.0, 0.0);
  const Quaternion rot1(axis, theta);
  axis = Vec(-cos(theta), 0., sin(theta));
  const Quaternion rot2(axis, phi);
  setOrientation(rot1 * rot2);
}

/*! Set the camera orientation, defined with respect to the world coordinate system. The current
 camera orientation can be obtained from orientation(). The camera position() is not modified by
 this function. See also lookAt() and setUpVector(). */
void Camera::setOrientation(const Quaternion& q)
{
  frame()->setOrientation(q);
  frame()->updateFlyUpVector();
}

/*! float version of orientation(). */
void Camera::getOrientation(float& q0, float& q1, float& q2, float& q3) const
{
  const Quaternion q = orientation();
  q0 = q[0];
  q1 = q[1];
  q2 = q[2];
  q3 = q[3];
}

void Camera::getViewDirection(float& x, float& y, float& z) const
{
  const Vec vd = viewDirection();
  x = vd.x;
  y = vd.y;
  z = vd.z;
}

// Compute a 3 by 3 determinant.
static float det(const float m00,const float m01,const float m02,
		 const float m10,const float m11,const float m12,
		 const float m20,const float m21,const float m22)
{
  return m00*m11*m22 + m01*m12*m20 + m02*m10*m21 - m20*m11*m02 - m10*m01*m22 - m00*m21*m12;
}

// Compute the index of element [i][j] in a float matrix[3][4].
static inline unsigned int ind(unsigned int i, unsigned int j)
{
  return (i*4+j);
}

/*! \e m is the projection matrix as used in vision algorithm. It has 3 lines and 4 columns. It
  transforms a point in the world homogeneous coordinate system (4 coordinates: \e sx, \e sy, \e sz
  and \e s) in a point in the screen homogeneous coordinate system (3 coordinates: \e sx, \e sy, and
  \e s, where \e x and \e y are the pixel coordinates on the screen).

  \e m is a pointer to the elements of the matrix ordered in line major order. If you define your
  matrix as a \p float \p matrix[3][4], you should call : \p
  setCameraFromProjectionMatrix(&(matrix[0][0]));

  This code was written by Sylvain Paris (Sylvain.Paris@imag.fr). */
void Camera::setCameraFromProjectionMatrix(const float* const m)
{
  // The 3 lines of the matrix are the normals to the planes x=0, y=0, z=0
  // in the camera CS. As we normalize them, we do not need the 4th coordinate.
  Vec line_0(m[ind(0,0)],m[ind(0,1)],m[ind(0,2)]);
  Vec line_1(m[ind(1,0)],m[ind(1,1)],m[ind(1,2)]);
  Vec line_2(m[ind(2,0)],m[ind(2,1)],m[ind(2,2)]);

  line_0.normalize();
  line_1.normalize();
  line_2.normalize();

  
  // The camera position is at (0,0,0) in the camera CS so it is the
  // intersection of the 3 planes. It can be seen as the kernel
  // of the 3x4 projection matrix. We calculate it through 4 dimensional
  // vectorial product. We go directly into 3D that is to say we directly
  // divide the first 3 coordinates by the 4th one.

  // We derive the 4 dimensional vectorial product formula from the
  // computation of a 4x4 determinant that is developped according to
  // its 4th column. This implies some 3x3 determinants.
  const Vec cam_pos = Vec(det(m[ind(0,1)],m[ind(0,2)],m[ind(0,3)],
			      m[ind(1,1)],m[ind(1,2)],m[ind(1,3)],
			      m[ind(2,1)],m[ind(2,2)],m[ind(2,3)]),
					  
			   -det(m[ind(0,0)],m[ind(0,2)],m[ind(0,3)],
				m[ind(1,0)],m[ind(1,2)],m[ind(1,3)],
				m[ind(2,0)],m[ind(2,2)],m[ind(2,3)]),
					  
			   det(m[ind(0,0)],m[ind(0,1)],m[ind(0,3)],
			       m[ind(1,0)],m[ind(1,1)],m[ind(1,3)],
			       m[ind(2,0)],m[ind(2,1)],m[ind(2,3)])) / 

    (-det(m[ind(0,0)],m[ind(0,1)],m[ind(0,2)],
	  m[ind(1,0)],m[ind(1,1)],m[ind(1,2)],
	  m[ind(2,0)],m[ind(2,1)],m[ind(2,2)]));

  
  // We compute the rotation matrix column by column.
  
  // GL Z axis is front facing.
  Vec column_2 = -line_2;  
  
  // X-axis is almost like line_0 but should be orthogonal to the Z axis.
  Vec column_0 = ((column_2^line_0)^column_2);
  column_0.normalize(); 

  // Y-axis is almost like line_1 but should be orthogonal to the Z axis.
  // Moreover line_1 is downward oriented as the screen CS.
  Vec column_1 = -((column_2^line_1)^column_2);
  column_1.normalize();

  float rot[3][3];
  rot[0][0] = column_0[0];
  rot[1][0] = column_0[1];
  rot[2][0] = column_0[2];
  
  rot[0][1] = column_1[0];
  rot[1][1] = column_1[1];
  rot[2][1] = column_1[2];

  rot[0][2] = column_2[0];
  rot[1][2] = column_2[1];
  rot[2][2] = column_2[2];


  // We compute the field of view

  // line_1^column_0 -> vector of intersection line between
  // y_screen=0 and x_camera=0 plane.
  // column_2*(...)  -> cos of the angle between Z vector et y_screen=0 plane
  // * 2 -> field of view = 2 * half angle

  // We need some intermediate values.
  Vec dummy = line_1^column_0;
  dummy.normalize();
  float fov = acos(column_2*dummy) * 2.0;

  // We set the camera.
  Quaternion q;
  q.setFromRotationMatrix(rot);
  setOrientation(q);
  setPosition(cam_pos[0],cam_pos[1],cam_pos[2]);
  setFieldOfView(fov);
}

///////////////////////// Camera to world transform ///////////////////////

/*! Same as cameraCoordinatesOf(), but the parameters are float[3] (\p src and \p res may be identical pointers). */
void Camera::getCameraCoordinatesOf(const float src[3], float res[3]) const
{
  Vec r = cameraCoordinatesOf(Vec(src));
  for (int i=0; i<3; ++i)
    res[i] = r[i];
}

/*! Same as worldCoordinatesOf(), but the parameters are float[3] (\p src and \p res may be identical pointers). */
void Camera::getWorldCoordinatesOf(const float src[3], float res[3]) const
{
  Vec r = worldCoordinatesOf(Vec(src));
  for (int i=0; i<3; ++i)
    res[i] = r[i];
}

/*! Fills \p viewport with current camera viewport. This function is mainly used in conjunction with
  \c gluProject, which requires such a viewport. Returned values are simply (0, 0, screenWidth(),
  screenHeight()).*/
void Camera::getViewport(GLint viewport[4]) const
{
  viewport[0] = 0;
  viewport[1] = screenHeight();
  viewport[2] = screenWidth();
  viewport[3] = -screenHeight();
}

/*! Returns the screen projected coordinates of a point \p src defined in the world coordinate
 system. See the \p gluProject man page for details. The x and y returned values are expressed in
 pixel, (0,0) being the \e upper left corner of the window.
 
 This method is not computationally optimized. If you call it several times with no change in the
 matrices, you should buffer the entire projection matrix (modelview, projection and then
 viewport) to speed-up the queries. See the \p gluProject man page for details.
 
 unprojectedCoordinatesOf() performs the inverse transformation.
 
 \attention When used in conjunction with QGLViewer::startScreenCoordinatesSystem(), the
 computations of the projected coordinates must be done \e before entering the screen coordinate
 mode, as the camera matrix is no longer a 3D projection in this mode. See the
 <a href="../examples/screenCoordSystem.html">screenCoordSystem</a> example.
 
 \attention If not used in QGLViewer::draw() or similar functions, call makeCurrent()
 and computeModelViewMatrix() before calling this function. */
Vec Camera::projectedCoordinatesOf(const Vec& src) const
{
  GLdouble x,y,z;
  GLdouble proj[16];
  glGetDoublev(GL_PROJECTION_MATRIX, proj);

  GLint viewport[4];
  getViewport(viewport);

  gluProject(src.x,src.y,src.z, modelViewMatrix_, proj, viewport,  &x,&y,&z);

  return Vec(x,y,z);
}

/*! float version of projectedCoordinatesOf() (\p src and \p res may be identical pointers). */
void Camera::getProjectedCoordinatesOf(const float src[3], float res[3]) const
{
  Vec r = projectedCoordinatesOf(Vec(src));
  for (int i=0; i<3; ++i)
    res[i] = r[i];
}

/*! Returns the world unprojected coordinates of a point \p src defined in the screen coordinate
system. The \p x and \p y input values are expressed in pixel, (0,0) being the \e upper left corner.
\p z is a depth value, between 0 and 1. See the \c gluUnProject man page for details.

This method is not computationally optimized. If you call it several times with no change in the
matrices, you should buffer the entire inverse projection matrix (modelview, projection and then
viewport) to speed-up the queries. See the \p gluUnProject man page for details.

projectedCoordinatesOf() performs the inverse transformation.

\attention If not used in QGLViewer::draw() or similar functions, call makeCurrent() and
computeModelViewMatrix() before calling this function. */
Vec Camera::unprojectedCoordinatesOf(const Vec& src) const
{
  GLdouble x,y,z;
  GLdouble proj[16];  
  glGetDoublev(GL_PROJECTION_MATRIX, proj);
  GLint viewport[4];
  getViewport(viewport);
  gluUnProject(src.x,src.y,src.z, modelViewMatrix_,  proj,  viewport,  &x,&y,&z);
  return Vec(x,y,z);
}

/*! Same as getUnprojectedCoordinatesOf(), but with float parameters (\p src and \p res may be identical pointers). */
void Camera::getUnprojectedCoordinatesOf(const float src[3], float res[3]) const
{
  Vec r = unprojectedCoordinatesOf(Vec(src));
  for (int i=0; i<3; ++i)
    res[i] = r[i];
}

/////////////////////////////////////  KFI /////////////////////////////////////////

/*! Returns the current KeyFrameInterpolator that defines the camera path number \p i.
   
If the path is not defined for this index, the method returns a \c NULL pointer.

The KeyFrameInterpolator::interpolated() signal of this keyFrameInterpolator() should be connected
to any object that should be notified when the frame is interpolated. The camera's associated viewer
(if any) should especially be connected. See the setKeyFrameInterpolator() documentation.

\attention index must be in the range 0..nbPaths()-1. */
KeyFrameInterpolator* Camera::keyFrameInterpolator(unsigned short i) const
{
  if (i>=nbPaths())
    {
      qWarning("Camera::keyFrameInterpolator : index %d out of range (0..%d).", i, nbPaths()-1);
      return NULL;
    }

  return kfi_[i];
}

/*! Changes the KeyFrameInterpolator that currently defines the camera path of index \p i. The
 previous keyFrameInterpolator() is lost and the pointer should be deleted by the calling function
 if needed.

 The KeyFrameInterpolator::interpolated() signal of \p kfi probably needs to be connected to the
 camera's associated viewer (if it exists), so that when the camera position is interpolated using
 \p kfi, every interpolation step updates the display.

 \code
 deleteKeyFramePath(3);
 setKeyFrameInterpolator(3, myKeyFrameInterpolator);
 connect(myKeyFrameInterpolator, SIGNAL(interpolated()), myViewer, SLOT(updateGL());
 \endcode

 The KeyFrameInterpolator::interpolated() signal can also be connected to \e all the viewers
 updateGL() slots:
 \code
 QGLViewer::connectSignalToAllViewers(myKeyFrameInterpolator, SIGNAL(interpolated()));
 \endcode

 \note These connections are automatically performed when a Camera is attached to a QGLViewer, or
 when a new KeyFrameInterpolator is defined using the key shortcuts (default is Alt F[1-12], see 
 the <a href="../shortcuts.html">QGLViewer shortcuts page</a> for details).
 
 \attention Index \p i must be in the range 0..nbPaths()-1. */
void Camera::setKeyFrameInterpolator(unsigned short i, KeyFrameInterpolator* const kfi)
{
  if (i>=nbPaths())
    qWarning("Camera::setKeyFrameInterpolator : index %d out of range (0..%d).", i, nbPaths()-1);
  else
    kfi_[i] = kfi;
}

/*! Adds the current camera frame as a key frame to the path number \p i. This function can also be
used if you simply want to save a camera point of view, as it is simply a key frame path made of
one key frame.

The default shortcut for this function is Alt-F[1-12]. Set QGLViewer::setKeyFrameKey() and
QGLViewer::setAddKeyFrameStateKey().
  
Use playKeyFramePath() to make the camera play the key frame path (resp. restore point of view). Use
deleteKeyFramePath() to clear the key frame path.

See also keyFrameInterpolator() and setKeyFrameInterpolator() to directly define a complete path. */
void Camera::addKeyFrame(unsigned short i)
{
  if (i>=nbPaths())
    {
      qWarning("Camera::addKeyFrame : index %d out of range (0..%d).", i, nbPaths()-1);
      return;
    }
  
  if (!kfi_[i])
    setKeyFrameInterpolator(i, new KeyFrameInterpolator(frame()));

  kfi_[i]->addKeyFrame(*(frame()));
}

/*! Make the camera follow the key frame path number \p i. The key Frames are defined using
addKeyFrame(). Use deleteKeyFramePath() to clear a path. This function silently ignores undefined
(empty) paths.

The default shortcut for this function is F[1-12]. Set QGLViewer::setKeyFrameKey() and
QGLViewer::setPlayKeyFramePathStateKey().

See also keyFrameInterpolator() and setKeyFrameInterpolator() to directly define a complete path. */
void Camera::playKeyFramePath(unsigned short i)
{
  if (i>=nbPaths())
    {
      qWarning("Camera::playFrameInterpolator : index %d out of range (0..%d).", i, nbPaths()-1);
      return;
    }
  
  if (kfi_[i] == NULL)
    return; // Undefined KF path, skip it.

  if (kfi_[i]->interpolationIsStarted())
    kfi_[i]->stopInterpolation();
  else
    {
      if ((i!=lastActivatedKFNumber_) &&
	  (kfi_[lastActivatedKFNumber_]) &&
	  (kfi_[lastActivatedKFNumber_]->interpolationIsStarted()))
	kfi_[lastActivatedKFNumber_]->resetInterpolation();
	
      kfi_[i]->startInterpolation();
    }
  
  lastActivatedKFNumber_ = i;
}

/*! If this keyFrame path is \e not being played (see playKeyFramePath() ), reset it to is its starting position (see
KeyFrameInterpolator::resetInterpolation()). If the path is played, simply stop interpolation. */
void Camera::resetKeyFramePath(unsigned short i)
{
  if (i>=nbPaths())
    {
      qWarning("Camera::resetKeyFramePath : index %d out of range (0..%d).", i, nbPaths()-1);
      return;
    }
  
  if (kfi_[i])
    if ((kfi_[i]->interpolationIsStarted()))
      kfi_[i]->stopInterpolation();
    else
      {
	kfi_[i]->resetInterpolation();
	kfi_[i]->interpolateAtTime(kfi_[i]->interpolationTime());
      }
}

/*! Deletes the KeyFrameInterpolator of index \p i. Use addKeyFrame() to define a key frame path.

The keyFrameInterpolator() KeyFrameInterpolator::interpolated() signal was probably connected to the
camera's viewer updateGL() slot, and you may want to disconnect it before deleting the
keyFrameInterpolator():
\code
disconnect(camera()->keyFrameInterpolator(i), SIGNAL(interpolated()), this, SLOT(updateGL()));
camera()->deleteKeyFramePath(i);
\endcode
*/
void Camera::deleteKeyFramePath(unsigned short i)
{
  if (i>=nbPaths())
    {
      qWarning("Camera::deleteKeyFramePath : index %d out of range (0..%d).", i, nbPaths()-1);
      return;
    }
  
  if (kfi_[i])
    {
      kfi_[i]->stopInterpolation();
      delete kfi_[i];
      kfi_[i] = NULL;
    }
}

/*! Draws the camera paths defined by the keyFrameInterpolator(). Simply calls
  KeyFrameInterpolator::drawPathModifyGLState() for all the defined path. See addKeyFrame() and
  setKeyFrameInterpolator() to define a path.

  The path color is the current \p glColor().
  
  \attention The GL state is modified by this function : see
  KeyFrameInterpolator::drawPathModifyGLState(). */
void Camera::drawAllPaths()
{
  for (int i=0; i<nbPaths(); ++i)
    if (kfi_[i])
      kfi_[i]->drawPathModifyGLState(3, 5, sceneRadius_);
}

////////////////////////////////////////////////////////////////////////////////

/*! Creates an XML QDomElement that represents the Camera. \p name is the name of the
 QDomElement tag. You need to provide the QDomDocument \p doc that will hold the resulting element.

 Use initFromDOMElement() to restore the Camera state from the resulting domElement.

 See also KeyFrameInterpolator::domElement(), Frame::domElement()...

 If you want to save the camera state in a file, use
 \code
  QDomDocument doc("myCAMERA");
  doc.appendChild( myCamera->domElement("Camera", doc) );
  ofstream file("myCamera.xml");
  file << doc.toString();
 \endcode
 Note that this is done automatically by QGLViewer::saveToFile() when a QGLViewer is closed (default shortcut key is Escape).
 
 Use the following code to retrieve state from the saved file:
 \code
 // Load DOM from file
 QDomDocument doc;
 QFile f("myCamera.xml");
 f.open(IO_ReadOnly);
 doc.setContent(&f);
 f.close();
 // Parse the DOM tree
 QDomElement main = doc.documentElement();
 myCamera->initFromDOMElement(main);
 \endcode */
QDomElement Camera::domElement(const QString& name, QDomDocument& doc) const
{
  QDomElement de = doc.createElement(name);
  QDomElement paramNode = doc.createElement("Parameters");
  paramNode.setAttribute("fieldOfView", QString::number(fieldOfView()));
  paramNode.setAttribute("zNearCoef", QString::number(zNearCoef()));
  paramNode.setAttribute("sceneRadius", QString::number(sceneRadius()));
  QString type = "Unknown";
  switch (type_)
    {
    case Camera::PERSPECTIVE : 	type = "PERSPECTIVE"; break;
    case Camera::ORTHO:		type = "ORTHO"; break;
    }
  paramNode.setAttribute("Type", type);
  de.appendChild(paramNode);
  
  de.appendChild(sceneCenter().domElement("SceneCenter", doc));
  
  de.appendChild(revolveAroundPoint().domElement("RevolveAroundPoint", doc));

  de.appendChild(frame()->domElement("ManipulatedCameraFrame", doc));
  
  QDomElement stereoNode = doc.createElement("Stereo");
  stereoNode.setAttribute("IODist", QString::number(IODist_));
  stereoNode.setAttribute("distToScreen", QString::number(distanceToScreen_));
  stereoNode.setAttribute("distToZPP", QString::number(distanceToZeroParallaxPlane_));
  stereoNode.setAttribute("physScreenWidth", QString::number(physicalScreenWidth_));
  de.appendChild(stereoNode);

  // KeyFrames
  for (unsigned short i=0; i<nbPaths(); ++i)
    if ( kfi_[i] != NULL )
      {
	QDomElement kfNode = kfi_[i]->domElement("KeyFrameInterpolator", doc);
	kfNode.setAttribute("Index", QString::number(i));
	de.appendChild(kfNode);
      }
      
  return de;
}

/*! Restore the Camera state from a QDomElement created by domElement().
See also KeyFrameInterpolator::initFromDOMElement(), Frame::initFromDOMElement(). */
void Camera::initFromDOMElement(const QDomElement& de)
{
  for (unsigned short i=0; i<nbPaths(); ++i)
    deleteKeyFramePath(i);
  
  QDomElement child=de.firstChild().toElement();
  while(!child.isNull())
    {
      if (child.tagName() == "Parameters")
	{
	  setFieldOfView((child.attribute("fieldOfView", "0.7854")).toFloat());
	  setZNearCoef((child.attribute("zNearCoef", "0.001")).toFloat());
	  setSceneRadius((child.attribute("sceneRadius", "1.0")).toFloat());
	  QString type = child.attribute("Type", "PERSPECTIVE");
	  if (type == "PERSPECTIVE") setType(Camera::PERSPECTIVE);
	  if (type == "ORTHO")       setType(Camera::ORTHO);
	}

      if (child.tagName() == "SceneCenter")
	{
	  Vec sc;
	  sc.initFromDOMElement(child);
	  setSceneCenter(sc);
	}

      if (child.tagName() == "RevolveAroundPoint")
	{
	  Vec rap;
	  rap.initFromDOMElement(child);
	  setRevolveAroundPoint(rap);
	}

      if (child.tagName() == "ManipulatedCameraFrame")
	frame()->initFromDOMElement(child);

      if (child.tagName() == "Stereo")
	{
	  setIODist((child.attribute("IODist", "0.062")).toFloat());
	  setDistanceToScreen((child.attribute("distToScreen", "0.5")).toFloat());
	  setDistanceToZeroParallaxPlane((child.attribute("distToZPP", "1.0")).toFloat());
	  setPhysicalScreenWidth((child.attribute("physScreenWidth", "0.4")).toFloat());
	}

      if (child.tagName() == "KeyFrameInterpolator")
	{
	  int index = (child.attribute("Index", "0")).toInt();
	  setKeyFrameInterpolator(index, new KeyFrameInterpolator(frame()));
	  if (kfi_[index])
	    kfi_[index]->initFromDOMElement(child);
	}

      child = child.nextSibling().toElement();
    }
}

/*! This function should be called by your selection function to transform a window x,y coordinate to
 a (world coordinates) half line, for analytical intersection process.

 The origin of the half line (eye position) is stored in \p orig, while \p dir contains the properly
 oriented and normalized direction of the half line.

 Typical usage would be:
 \code
 convertClickToLine(e->x(), e->y(), orig, dir);
 \endcode

 The \p x and \p y coordinates origin is in the window's \e upper left corner.
 
 See the <a href="../examples/select.html">select example</a> for an illustration. */
void Camera::convertClickToLine(int x, int y, Vec& orig, Vec& dir) const
{
  switch (type())
    {
    case Camera::PERSPECTIVE:
      orig = position();
      dir = Vec( ((2.0 * x / screenWidth()) - 1.0) * tan(fieldOfView()/2.0) * aspectRatio(),
		 ((2.0 * (screenHeight()-y) / screenHeight()) - 1.0) * tan(fieldOfView()/2.0),
		 -1.0 );
      dir = worldCoordinatesOf(dir) - orig;
      dir.normalize();
      break;
    
    case Camera::ORTHO:
      {
	GLdouble w,h;
	getOrthoWidthHeight(w,h);
	orig = Vec((2.0 * x / screenWidth() - 1.0)*w, -(2.0 * y / screenHeight() - 1.0)*h, 0.0);
	orig = worldCoordinatesOf(orig);
	dir = viewDirection();
	break;
      }
    }
}

/*! Same as convertClickToLine(), but the result is returned as float[3]. */
void Camera::convertClickToLine(int x, int y, float orig[3], float dir[3]) const
{
  Vec o, d;
  convertClickToLine(x, y, o, d);
  orig[0] = o.x;
  orig[1] = o.y;
  orig[2] = o.z;
  dir[0]  = d.x;
  dir[1]  = d.y;
  dir[2]  = d.z;
}

