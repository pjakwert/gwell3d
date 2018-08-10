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

#ifndef QGLVIEWER_MANIPULATED_CAMERA_FRAME_H
#define QGLVIEWER_MANIPULATED_CAMERA_FRAME_H

#include "manipulatedFrame.h"

namespace qglviewer {
  /*! \brief A Camera Frame that can be rotated and translated with the mouse.
     
  A ManipulatedCameraFrame is a specialization of a ManipulatedFrame, designed for associated Camera
  frames. All mouse motions are basically interpreted in a negated way: when the mouse goes to the
  right, the ManipulatedFrame translation goes to the right, while the ManipulatedCameraFrame
  has to go to the \e left, so that the \e scene seems to move to the right.

  See the <a href="../mouse.html">mouse page</a> for a description of the possible displacements
  that can be performed using the mouse.
  
  The ManipulatedFrame::isManipulated() function is used to call QGLViewer::fastDraw() instead of
  QGLViewer::draw() for interactive scene displays when the camera is manipulated (see the
  <a href="../examples/fastDraw.html">fastDraw</a> example).

  A ManipulatedCameraFrame can be used as the QGLViewer::manipulatedFrame() (for instance, with two
  viewers, it is possible to manipulate the first viewer camera is the second viewer). In that case,
  the mouse response will be the one of a ManipulatedFrame, as one would expect.
  
  ManipulatedCameraFrame are not automatically added to the MouseGrabber::MouseGrabberPool() as
  ManipulatedFrame are.
  \nosubgrouping */
  class QGLVIEWER_EXPORT ManipulatedCameraFrame : public ManipulatedFrame
  {
#ifndef DOXYGEN
    friend class Camera;
    friend class ::QGLViewer;
#endif

    Q_OBJECT

  public:
    ManipulatedCameraFrame();
    /*! Virtual destructor. Empty. */
    virtual ~ManipulatedCameraFrame() {};

    /*! @name Fly parameters */
    //@{    
  public slots:
    /*! When a QGLViewer::MOVE_FORWARD or QGLViewer::MOVE_BACKWARD action is produced
    by the mouse, this value tunes the speed of the displacement. Current value is given by
    flySpeed(). See the <a href="../mouse.html">mouse page</a> and QGLViewer::setMouseBinding() for
    details. */
    void setFlySpeed(const float s) { flySpeed_ = s; };

    /*! Defines the fly up vector (used in MOVE_FORWARD and MOVE_BACKWARD mode), defined in the
      world coordinate system. See flyUpVector(). */
    void setFlyUpVector(const Vec& up) { flyUpVector_ = up; };

  public:
    /*! Returns the current fly speed set with setFlySpeed(). Set according to the
    QGLViewer::sceneRadius() in QGLViewer::setSceneRadius(). */
    float flySpeed() const { return flySpeed_; };

    /*! Return the up vector used in QGLViewer::MOVE_FORWARD and
    QGLViewer::MOVE_BACKWARD modes. This vector is normal to the displacement horizontal
    plane. Horizontal displacements of the mouse rotates the frame around this vector. It is
    expressed in the world coordinate system. Vertical displacements of the mouse rotate around the
    Camera \c Y axis. */
    Vec flyUpVector() const { return flyUpVector_; };
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
    virtual void mouseReleaseEvent(QMouseEvent* const, Camera* const);
    virtual void mouseMoveEvent(QMouseEvent* const, const Camera* const);
    virtual void wheelEvent(QWheelEvent* const, const Camera* const camera);
    //@}
    
  protected slots:
    void updateFrameInFlyMode();
    
  protected:
    void updateFlyUpVector();
    Quaternion quaternionFromThetaPhi(const int x, const int y, const Camera* const camera);
    virtual void startAction(int ma, bool withConstraint=true); // int is really a QGLViewer::MouseAction
    
  private:
    // Copy constructor and opertor= are declared private and undefined
    // Prevents everyone from trying to use them
    ManipulatedCameraFrame(const ManipulatedCameraFrame& mf);
    ManipulatedCameraFrame& operator=(const ManipulatedCameraFrame& mf);

    // Internal state values
    float flySpeed_;                     // Speed in fly mode, set by the camera
    Vec flyUpVector_;
    QTimer flyTimer_;
  };

} // namespace qglviewer

#endif // QGLVIEWER_MANIPULATED_CAMERA_FRAME_H
