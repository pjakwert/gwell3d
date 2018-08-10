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

#ifndef QGLVIEWER_SPINNING_FRAME_H
#define QGLVIEWER_SPINNING_FRAME_H

#include "frame.h"

#include <qstring.h>
#include <qtimer.h>

namespace qglviewer {
  /*! \brief A Frame that can have its orientation (and possibly its position)
  updated at a regular time interval.

  A SpinningFrame is useful to animate some objects of the scene :
  \code
  init()
  {
    sf = new SpinningFrame();
    // Update display after each update of the SpinningFrame
    connect(sf, SIGNAL(spinned()), SLOT(updateGL()));
    // Rotation around the Z axis, with a increment of 0.04 radian.
    sf->setSpinningQuaternion(Quaternion(Vec(0,0,1), 0.04));
    sf->startSpinning();
  }

  draw()
  {
    glPushMatrix();
    glMultMatrixd(sf->matrix());
    // Draw your spinning object here.
    glPopMatrix();
  }
  \endcode

  When rotatesAroundCenter() is \p true, the SpinningFrame will rotate around the rotationCenter()
  (defined in the world coordinate system). Use setRotateAroundCenter() and setRotationCenter() to
  change these values.

  Additionally, when rotatesAroundCenter() is \p true, you can freeze the Frame orientation using
  freezeOrientation(). The Frame will then describe circles around the rotationCenter(), but its
  orientation will remain unchanged.

  See the <a href="../examples/spinningFrame.html">spinningFrame</a> example for an illustration.
    
  The spinningQuaternion() axis is always defined in the SpinningFrame coordinate system. You may
  want to use Frame::transformOfFrom() to convert this axis from an other Frame.

  The ManipulatedFrame and ManipulatedCameraFrame classes both derive from this class and can hence
  have a continuous spinning motion (by default, this happens when the mouse button is released
  while moving the mouse quickly enough, see ManipulatedFrame::setSpinningSensitivity()). 

  When spinning, the SpinningFrame emits a spinned() signal, which should usually be connected to
  the viewer's updateGL() slot, so that successive updates of the SpinningFrame orientation are all
  displayed. See the spinned() documentation for details.
  \nosubgrouping */
  class QGLVIEWER_EXPORT SpinningFrame : public Frame
  {
    Q_OBJECT

  public:
    SpinningFrame();
    /*! Virtual destructor. Empty. */
    virtual ~SpinningFrame() {};
    
    signals:
    /*! This signal is emitted whenever the frame is spinning. Connect this signal to any object
    that should be notified, and especially the viewer(s) :
    \code
    connect(mySpinningFrame, SIGNAL(spinned()), myViewer, SLOT(updateGL()));
    \endcode

    Use QGLViewer::connectSignalToAllViewers() to connect this signal to \e all the viewers.

    Note that for every QGLViewer, its QGLViewer::manipulatedFrame() and its QGLViewer::camera()
    Camera::frame() \e are SpinningFrame. For these, the spinned() signal is automatically connected
    to the QGLViewer updateGL() slot.

    See also the ManipulatedFrame::manipulated() and KeyFrameInterpolator::interpolated() signals documentations. */
    void spinned();
    
  public:
    virtual QDomElement domElement(const QString& name, QDomDocument& doc) const;
    virtual void initFromDOMElement(const QDomElement& de);

    /*! @name Spinning parameters */
    //@{    
  public slots:

    /*! Defines the current spinningQuaternion(). */
    void setSpinningQuaternion(const Quaternion& q) { spinningQuaternion_ = q; };
    
    /*! Defines the current rotationCenter(). This value will be used only when rotatesAroundCenter()
      is \p true. */
    void setRotationCenter(const Vec& center) { rotationCenter_ = center; };
    void setRotateAroundCenter(const bool rac=true) { rotatesAroundCenter_ = rac; };
    void freezeOrientation(const bool fo=true) { frozenOrientation_ = fo; };
    
  public:
    /*! This is the incremental rotation that will be applied to the SpinningFrame orientation,
      every updateInterval() milliseconds, when the SpinningFrame isSpinning(). Default value is a
      null rotation. Use setSpinningQuaternion() to define this value.

      More complex rotation motion can be achieved using the rotationCenter() and
      freezeOrientation(). See the <a href="#_details">Detailed Description</a> section. */
    Quaternion spinningQuaternion() const { return spinningQuaternion_; };
    
    /*! Current spinning rotation center. Set using setRotationCenter().

    See the <a href="#_details">Detailed Description</a> section for more explanations. */
    Vec rotationCenter() const { return rotationCenter_; };
    bool rotatesAroundCenter() const { return rotatesAroundCenter_; }
    bool orientationIsFrozen() const { return frozenOrientation_; };
    //@}


    /*! @name Timer configuration */
    //@{
  public slots:
    virtual void startSpinning(const int msecs = -1);
    /*! Stops the spinning which was initiated with startSpinning(). */
    virtual void stopSpinning()  { timer_.stop();  isSpinning_ = false; };
    /*! Defines the update interval, defined in milliseconds. Default value is 40. Get current value
      from updateInterval().

      \attention A change of the updateInterval() will not be taken into account until next
      call to startSpinning(). */
    void setUpdateInterval(const int msecs) { updateInterval_ = msecs; };
  public:
    /*! \p True when the SpinningFrame is spinning. updateInterval() returns the update interval. */
    bool isSpinning() const { return isSpinning_; };
    /*! Returns the current update interval of the SpinningFrame. See isSpinning() to know if the
      Frame is actually spinning. This value can be set with setUpdateInterval() or with
      startSpinning(). */
    int updateInterval() const { return updateInterval_; };
    //@}
    
  protected slots:
    void updateFrame();

  private:
    // Copy constructor and opertor= are declared private and undefined.
    // Prevents anyone from trying to use them.
    SpinningFrame(const SpinningFrame& sf);
    SpinningFrame& operator=(const SpinningFrame& sf);
  
    // T i m e r
    bool isSpinning_;
    QTimer timer_;
    int updateInterval_; // in msecs

    // S p i n n i n g   p a r a m a t e r s
    Quaternion spinningQuaternion_;
    Vec rotationCenter_;
    bool rotatesAroundCenter_;
    bool frozenOrientation_;
  };

} // namespace qglviewer

#endif // QGLVIEWER_SPINNING_FRAME_H
