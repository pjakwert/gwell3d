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

#ifndef QGLVIEWER_MANIPULATED_FRAME_H
#define QGLVIEWER_MANIPULATED_FRAME_H

#include "spinningFrame.h"
#include "mouseGrabber.h"

#include <qstring.h>
#include <qtimer.h>
#include <qdatetime.h>

namespace qglviewer {
  /*! \brief A Frame that can be rotated and translated with the mouse.
     
  A ManipulatedFrame is a local coordinate system (a Frame) that can be moved in the 3D scene using
  the mouse. The ManipulatedFrame converts the mouse motion in a translation and orientation update.
  You can then use the ManipulatedFrame to move an object or a point in the scene.

  A ManipulatedFrame is attached to a QGLViewer using QGLViewer::setManipulatedFrame():
  \code
  init() { setManipulatedFrame( new ManipulatedFrame() ); }

  draw()
  {
    glPushMatrix();
    glMultMatrixd(manipulatedFrame()->matrix());
    // draw the manipulated object here
    glPopMatrix();
  }
  \endcode
  You have to press the QGLViewer::FRAME state key (default is \c Control) to move the
  QGLViewer::manipulatedFrame().
  
  The <a href="../examples/manipulatedFrame.html">manipulatedFrame</a> example details a complete
  application. See the <a href="../mouse.html">mouse page</a> for a description of the mouse button
  bindings.
  
  <h3>Inherited functionalities</h3>
  
  A ManipulatedFrame is an overloaded instance of a Frame. The powerful coordinate system
  transformation functions (Frame::coordinatesOf(), Frame::transformOf(), ...) can hence be applied
  to a ManipulatedFrame.

  A ManipulatedFrame is also a SpinningFrame, and you can make the ManipulatedFrame spin is you
  release the rotation mouse button while moving the mouse fast enough (see spinningSensitivity()).

  Finally, a ManipulatedFrame is a MouseGrabber. If the mouse cursor gets within a distance of 10
  pixels from the projected position of the ManipulatedFrame, the ManipulatedFrame becomes the new
  QGLViewer::mouseGrabber(). It can then be manipulated directly, without any specific state key,
  object selection or GUI intervention. This is very convenient to directly move some objects of the
  scene (typically a light). See the <a href="../examples/mouseGrabber.html">mouseGrabber</a>
  example as an illustration. Note that QWidget::setMouseTracking() needs to be enabled in order to
  use this feature (see the MouseGrabber documentation).

  <h3>Advanced functionalities</h3>
  
  A QGLViewer can handle at most one ManipulatedFrame at a time. If you want to move several objects
  in the scene, you simply have to keep a list of the different ManipulatedFrames, and to activate
  the right one (using setManipulatedFrame()), for instance according to an object selection (see the
  <a href="../examples/luxo.html">luxo</a> example).
    
  When the ManipulatedFrame is being manipulated using the mouse (mouse pressed and not yet
  released), isManipulated() returns \c true, and it might be checked for a specific action (as in
  QGLViewer::fastDraw()).

  The ManipulatedFrame also emits a manipulated() signal each time its state is modified with the
  mouse. This signal is automatically connected to the viewer's updateGL() slot, when the
  ManipulatedFrame is attached to a viewer using QGLViewer::setManipulatedFrame(). See the
  manipulated() documentation for details.

  Combined with the object selection (see the <a href="../examples/select.html">select</a> example),
  the MouseGrabber properties and a dynamic update of the scene, the ManipulatedFrame introduces a
  great reactivity in your applications.
  \nosubgrouping */
  class QGLVIEWER_EXPORT ManipulatedFrame : public SpinningFrame, public MouseGrabber
  {
#ifndef DOXYGEN
    friend class Camera;
    friend class ::QGLViewer;
#endif

    Q_OBJECT

  public:
    ManipulatedFrame();
    /*! Virtual destructor. Empty. */
    virtual ~ManipulatedFrame() {};
    
    signals:
    /*! This signal is emitted whenever the frame is manipulated (i.e. rotated or translated) using
    the mouse. Connect this signal to any object that should be notified.

    Note that this signal is automatically connected to the viewer's updateGL() slot, when the
    ManipulatedFrame is attached to a viewer using QGLViewer::setManipulatedFrame(), which is
    probably all you need.

    However, when you have several viewers that display the same scene, it may be interesting to
    update \e all the viewers when a ManipulatedFrame (hence an object) is manipulated in any of
    these viewers. Simply use this code to achieve this behavior:
    \code
    QGLViewer::connectSignalToAllViewers(myManipulatedFrame, SIGNAL(manipulated()));
    \endcode

    See also the KeyFrameInterpolator::interpolated() and SpinningFrame::spinned() signals documentations. */
    void manipulated();

    /*! @name Manipulation sensitivity */
    //@{    
  public slots:
    /*! Defines the influence of a mouse displacement on the frame rotation (default value is 1.0).
      See rotationSensitivity(). */
    void setRotationSensitivity(const float s) { rotSensitivity_ = s; };
    /*! Defines the influence of a mouse displacement on the frame translation. Default value is
    1.0. See translationSensitivity(). */
    void setTranslationSensitivity(const float s) { transSensitivity_ = s; };
    /*! Defines the spinningSensitivity(). Default value is 0.3 (pixels per milliseconds). */
    void setSpinningSensitivity(const float s) { spinningSensitivity_ = s; };
    /*! Defines the wheelSensitivity(). Default value is 1.0. */
    void setWheelSensitivity(const float s) { wheelSensitivity_ = s; };
  public:
    /*! Returns the current rotationSensitivity() as defined by setRotationSensitivity(). Default value is 1.0 */
    float rotationSensitivity() const { return rotSensitivity_; };
    /*! Returns the current translationSensitivity() as defined by setTranslationSensitivity()
      (default value is 1.0).

    \note You should not have to modify this value as the frame translation is computed so that
    the frame exactly matches the mouse trajectory, which is an intuitive behavior.

    \note When the manipulated frame is used to move a \e Camera (see the ManipulatedCameraFrame
     class documentation), after zooming on a small region of your scene, the camera may translate
     too fast. For a camera, it is the Camera::revolveAroundPoint() that exactly matches the mouse
     displacement. Hence, instead of changing the translationSensitivity() to solve the problem, you
     simply have to (temporarily) set the Camera::revolveAroundPoint() to a point of the small
     region of your scene (see the <a href="../mouse.html">mouse page</a> for the RAP_FROM_PIXEL
     mouse binding, default is a double click on left button while pressing right button). */
    float translationSensitivity() const { return transSensitivity_; };
    /*! Returns the minimum mouse speed required to make the Frame spin when the mouse button is
    released. Mouse speed is expressed in pixels per milliseconds. Default value is 0.3 (300 pixels
    per second). Use setSpinningSensitivity() to tune this value. A higher value will make auto
    spinning more difficult (a value of 100.0 means forbid spinning in practice). */
    float spinningSensitivity() const { return spinningSensitivity_; };
    /*! Current wheel sensitivity. Default value is 1.0. Defined using setWheelSensitivity().

    A higher value will make the wheel action more effective (usually means a faster zoom). */
    float wheelSensitivity() const { return wheelSensitivity_; };
    //@}
    
  public:
    /*! @name Current state */
    //@{
    bool isManipulated() const;
    //@}

  public:
    /*! @name XML representation */
    //@{    
    virtual QDomElement domElement(const QString& name, QDomDocument& doc) const;
    virtual void initFromDOMElement(const QDomElement& de);
    //@}    
    
    /*! @name Mouse event handlers */
    //@{
  protected:
    virtual void mousePressEvent(QMouseEvent* const, Camera* const);
    virtual void mouseReleaseEvent(QMouseEvent* const, Camera* const);
    virtual void mouseMoveEvent(QMouseEvent* const, const Camera* const);
    virtual void wheelEvent(QWheelEvent* const, const Camera* const camera);
    //@}

    /*! @name Mouse Grabber implementation */
    //@{
    void checkIfGrabsMouse(int x, int y, const Camera* const camera); 
    //@}
    
#ifndef DOXYGEN 
  protected:
    Quaternion quaternionFromDeformedBall(const int x, const int y, const float cx, const float cy, const Camera* const camera);    

    int action_; // Should be a QGLViewer::MouseAction, but include loop
    bool withConstraint_;

    virtual void startAction(int ma, bool withConstraint=true); // int is really a QGLViewer::MouseAction
    void computeMouseSpeed(const QMouseEvent* const e);    
    int mouseOriginalDirection(const QMouseEvent* const e);

    // Previous mouse position, used for incremental updates.
    int prevX_,  prevY_;
    // Mouse press position
    int pressX_, pressY_;  
#endif // DOXYGEN
    
  private:
    // Copy constructor and opertor= are declared private and undefined
    // Prevents everyone from trying to use them
    ManipulatedFrame(const ManipulatedFrame& mf);
    ManipulatedFrame& operator=(const ManipulatedFrame& mf);

    // Sensitivity
    float rotSensitivity_;
    float transSensitivity_;
    float spinningSensitivity_;
    float wheelSensitivity_;
  
    // Mouse speed and spinning
    QTime last_move_time;
    float mouseSpeed_; 
    int delay_; 

    // Whether the SCREEN_TRANS direction (horizontal or vertical) is fixed or not.
    bool dirIsFixed_;

    // MouseGrabber
    bool keepsGrabbingMouse_;
  };

} // namespace qglviewer

#endif // QGLVIEWER_MANIPULATED_FRAME_H
