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

#ifndef QGLVIEWER_KEY_FRAME_INTERPOLATOR_H
#define QGLVIEWER_KEY_FRAME_INTERPOLATOR_H

#include <qobject.h>
#include <qtimer.h>

#include "quaternion.h"

namespace qglviewer {
  class Camera;
  class Frame;
  /*! \brief A key frame interpolator.
   
  KeyFrameInterpolator implements a classical interpolation of key Frames, using a smooth
  Catmull-Rom interpolation. See the <a href="../examples/keyFrames.html">keyFrames</a> example for
  an illustration of the class.

  Use addKeyFrame() to define the keyframes and then call startInterpolation(). The frame()
  associated with the interpolator (using the constructor or with setFrame()) will then be updated
  over time. frame() should be a pointer to one of the Frame of your application, the one that you
  want the KeyFrameInterpolator to drive:
  \code
  // The KeyFrameInterpolator must be given the Frame that it will drive over time. 
  KeyFrameInterpolator kfi( new Frame() );

  init()
  {
    kfi.addKeyFrame( Frame( Vec(1,0,2), Quaternion() ) );
    kfi.addKeyFrame( new Frame( Vec(2,1,0), Quaternion() ) );
    // ...and so on for all the Key Frames.

    // Ask for a display update after each update of the KeyFrameInterpolator
    connect(&kfi, SIGNAL(interpolated()), SLOT(updateGL()));
    
    kfi.startInterpolation();
  }

  draw()
  {
    kfi.drawPath();
    glPushMatrix();
    // Recover kfi associated frame with kfi.frame(), and use its matrix 
    glMultMatrixd( kfi.frame()->matrix() );
      // Draw your object here. Its position and orientation will be interpolated.
    glPopMatrix();
  }
  \endcode
  
  The interpolation can loop (setLoopInterpolation()) and the keyFrame path can be closed
  (setClosedPath()) (not yet implemented). The current interpolation time (interpolationTime()) and
  speed (interpolationSpeed()) can also be tuned.

  The keyFrames are defined by a Frame and a time, expressed in seconds. If the keyFrame is defined
  using a \e pointer to a Frame, the keyFrame path will automatically be updated if the Frame is
  modified (see the Frame::modified() signal).

  The time has to be monotonously increasing over keyFrames. When interpolationSpeed() equals 1.0,
  these times correspond to actual user' seconds during the interpolation (provided that your
  QGLViewer::draw() function is fast enough).

  Note that a Camera has 12 attached KeyFrameInterpolator binded to the F1-F12 keys. Press Alt+F\e x
  to define a new keyFrame for path \e x. Pressing F\e x plays/pause path interpolation. See the
  <a href="../shortcuts.html">shortcuts page</a> for details.

  When interpolated, the KeyFrameInterpolator emits an interpolated() signal, which should be connected to
  the viewer's updateGL() slot. See the interpolated() documentation for details.
  
  \nosubgrouping */
  // todo closedPath, insertKeyFrames, deleteKeyFrame, replaceKeyFrame
  class QGLVIEWER_EXPORT KeyFrameInterpolator : public QObject
  {
    Q_OBJECT
    
  public:
    KeyFrameInterpolator(Frame* fr=NULL);
    virtual ~KeyFrameInterpolator();

  signals:
    /*! This signal is emitted whenever the frame() state is interpolated. Connect this signal to
    any object that should be notified.

    This signal should especially be connected to your viewer updateGL() slot, so that the display
    is updated after every update of the KeyFrameInterpolator frame(). Use code like this :
    \code
    connect(myKeyFrameInterpolator, SIGNAL(interpolated()), SLOT(updateGL()));
    \endcode

    Note that every QGLViewer::camera() holds several KeyFrameInterpolator and that their
    interpolated() signals are automatically connected to the viewer's updateGL() slot.

    When several viewers display the same scene, it may be interesting to update \e all the viewers
    when a KeyFrameInterpolator (and probably hence an object) is interpolated. Simply use this code
    to achieve this behavior:
    \code
    QGLViewer::connectSignalToAllViewers(myKeyFrameInterpolator, SIGNAL(interpolated()));
    \endcode

    See also the ManipulatedFrame::manipulated() and SpinningFrame::spinned() signals documentations. */
    void interpolated();

    /*! This signal is emitted when the interpolation reaches the last keyFrameTime(). Use
    startInterpolation() to start the interpolation and you will be warned with this signal when the
    interpolation is finished.

    \note A call to stopInterpolation() will not emit this signal. If loopInterpolation() is
    activated, the signal is emitted each time the interpolation loops back to first keyFrame.

    \note If the interpolationSpeed() is negative, finished() is emitted when interpolationTime()
    reaches the first keyFrameTime(). */    
    void finished();

  public:
    /*! @name Key Frames */
    //@{
    /*! Set the frame that will be associated with the KeyFrameInterpolator. Current frame is in frame().

    The Frame you associate with a KeyFrameInterpolator is usually one of your application Frame,
    that you would like to interpolate. You will then setFrame() to a pointer to your Frame. */
    void setFrame(Frame* fr) { frame_ = fr; };
    /*! The frame that is associated and modified by the KeyFrameInterpolator. Set using setFrame()
    or with the KeyFrameInterpolator() constructor. */
    Frame* frame() const { return frame_; };

    void addKeyFrame(const Frame& fr);
    void addKeyFrame(const Frame& fr, const float time);

    void addKeyFrame(const Frame* fr);
    void addKeyFrame(const Frame* fr, const float time);

    void deletePath();

    /*! Number of keyFrames used in the interpolation. Use addKeyFrame() to add new keyFrames. */
    int numberOfKeyFrames() const { return keyFrame_.count(); };
    
    Frame keyFrame(const int i) const;
    Vec keyFramePosition(const int i) const;
    Quaternion keyFrameOrientation(const int i) const;
    float keyFrameTime(const int i) const;
    //@}
  
    /*! @name Interpolation parameters */
    //@{
    /*! Current interpolation time, updated when interpolationIsStarted() is true. Can be set
    directly with setInterpolationTime() or interpolateAtTime(). */
    float interpolationTime() const { return interpolationTime_; };
    /*! Set the current interpolation time. See also interpolationTime().

    \attention The frame() is not affected by this method. Use this function to define the
    starting time of a future interpolation (see startInterpolation()). Use interpolateAtTime() to
    actually interpolate at a given time. */
    void setInterpolationTime(const float time) { interpolationTime_ = time; };

    /*! Returns the current interpolation speed. Default value is 1.0, which means that the times
    associated with the keyFrames (see keyFrameTime() and addKeyFrame()), expressed in seconds,
    will be respected during the interpolation (see startInterpolation()), provided that your
    display is fast enough.
      
    A negative value will result in a reverse interpolation of the keyFrames. */
    float interpolationSpeed() const { return interpolationSpeed_; };
    /*! Set the interpolation speed. Negative values are possible. See interpolationSpeed(). */
    void setInterpolationSpeed(const float speed) { interpolationSpeed_ = speed; };

    /*! Returns the current interpolation period, expressed in milliseconds. This period will be
    added to the interpolationTime() at each update(), when interpolationIsStarted() is \p true. */
    int interpolationPeriod() const { return period_; };
    /*! Set the interpolationPeriod(). */
    void setInterpolationPeriod(const int msecs) { period_ = msecs; };
    
    /*! Whether or not (default) the interpolation will be played in (infinite) loop when
    startInterpolation() is called (until stopInterpolation() is called). When \p false, the
    interpolation will stop when interpolationTime() reaches the last keyFrames associated time
    (see keyFrameTime()).

    Use setClosedPath() to create a closed path with the keyFrames. */
    bool loopInterpolation() const { return loopInterpolation_; };
    /*! Set the loopInterpolation() value. */
    void setLoopInterpolation(const bool loop=true) { loopInterpolation_ = loop; };

    /*! Whether or not (default) the path defined by the keyFrames is a closed loop. When \p true,
    the last and the first KeyFrame are linked by a new spline segment. 
    \todo Not yet implemented and specified.
      
    Use setLoopInterpolation() to create a continuous animation over the entire path.
    \attention The closed path feature is not yet implemented. */
    bool closedPath() const { return closedPath_; };
    /*! Set the closedPath() value. \attention The closed path feature is not yet implemented. */
    void setClosedPath(const bool closed=true) { closedPath_ = closed; };
    //@}

    
    /*! @name Interpolation */
    //@{
    virtual void interpolateAtTime(const float time);
    void startInterpolation(const int msecs = -1);
    void stopInterpolation();
    void resetInterpolation();

    /*! Returns \p true when the interpolation is being processed (after a call to
    startInterpolation()). Set to \p false by stopInterpolation(). See also
    toggleInterpolation(). */
    bool interpolationIsStarted() const { return interpolationStarted_; };
    /*! Calls startInterpolation() or stopInterpolation(), depending on interpolationIsStarted(). */
    void toggleInterpolation() { if (interpolationIsStarted()) stopInterpolation(); else startInterpolation(); };
    //@}
    
    /*! @name Path drawing */
    //@{
  public:
    virtual void drawPath(const int mask=1, int nbFrames=6, const float scale=1.0f);
    virtual void drawPathModifyGLState(const int mask, int nbFrames, const float scale);
    //@}

  public:
    /*! @name XML representation */
    //@{
    virtual QDomElement domElement(const QString& name, QDomDocument& doc) const;
    virtual void initFromDOMElement(const QDomElement& de);
    //@}
    
  public slots:
    virtual void update();
      
  private slots:
    virtual void invalidateValues() { valuesAreValid_ = false; pathIsValid_ = false; splineCacheIsValid_ = false; };
    
  private:
    // Copy constructor and opertor= are declared private and undefined
    // Prevents everyone from trying to use them
    KeyFrameInterpolator(const KeyFrameInterpolator& kfi);
    KeyFrameInterpolator& operator=(const KeyFrameInterpolator& kfi);

    void updateCurrentKeyFrameForTime(const float time);
    void updateModifiedFrameValues();
    void updateSplineCache();

    // Internal private KeyFrame representation
    class KeyFrame
    {
    public:
      KeyFrame(const Frame& fr, const float t);
      KeyFrame(const Frame* fr, const float t);

      Vec position() const { return p_; }
      Quaternion orientation() const { return q_; }
      Vec tgP() const { return tgP_; }
      Quaternion tgQ() const { return tgQ_; }
      float time() const { return time_; }
      const Frame* frame() const { return frame_; }
      void updateValuesFromPointer();
      void flipOrientation(const Quaternion& prev);
      void computeTangent(const KeyFrame* const prev, const KeyFrame* const next);
    private:
      Vec p_, tgP_;
      Quaternion q_, tgQ_;
      float time_;
      const Frame* const frame_;
    };

    // K e y F r a m e s
    mutable QPtrList<KeyFrame> keyFrame_;
    // 4 succesive frames. interpolationTime_ is between index 1 and 2.
    QPtrListIterator<KeyFrame>* currentFrame_[4];
    QValueVector<Frame> path_;
    
    // A s s o c i a t e d   f r a m e
    Frame* frame_;
    
    // R h y t h m
    QTimer timer_;
    int period_;
    float interpolationTime_;
    float interpolationSpeed_;
    bool interpolationStarted_;

    // M i s c
    bool closedPath_;
    bool loopInterpolation_;

    // C a c h e  v a l u e s   a n d   f l a g s
    bool pathIsValid_;
    bool valuesAreValid_;
    bool currentFrameValid_;
    bool splineCacheIsValid_;
    Vec v1, v2;
  };
  
} // namespace qglviewer

#endif // QGLVIEWER_KEY_FRAME_INTERPOLATOR_H
