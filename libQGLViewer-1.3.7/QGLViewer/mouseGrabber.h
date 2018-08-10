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

#ifndef QGLVIEWER_MOUSE_GRABBER_H
#define QGLVIEWER_MOUSE_GRABBER_H

#include "config.h"
#include "qevent.h"

class QGLViewer;

namespace qglviewer {
  class Camera;
  
  /*! \brief Abstract class for mouse interactive objects.

  MouseGrabber are object which react to the mouse cursor, usually when it get close to them. Their
  actual behavior is arbitrary and has to be defined in a derived class : this class only provides a
  common interface for all these objects.

  All the created MouseGrabber objects are grouped in a MouseGrabberPool(). All the QGLViewers parse
  this pool, calling all the MouseGrabbers' checkIfGrabsMouse() functions to determine if one of the
  MouseGrabber grabsMouse(). Individual MouseGrabbers can be removed from this pool using
  removeFromMouseGrabberPool() if you want to (temporarily) disable them.

  When a MouseGrabber grabsMouse(), it becomes the QGLViewer::mouseGrabber(). All the mouse
  events (mousePressEvent(), mouseReleaseEvent(), mouseMoveEvent(), mouseDoubleClickEvent() and
  wheelEvent()) are then transmitted to the QGLViewer::mouseGrabber() instead of being normally
  processed.

  checkIfGrabsMouse() is still called after each mouse motion to check if the QGLViewer::mouseGrabber()
  still grabs the mouse.

  In order to make MouseGrabber react to mouse events, the mouse tracking option has to be
  activated in the QGLViewer which wants to use MouseGrabbers:
  \code
  init() { setMouseTracking(true); }
  \endcode
  Call \c QGLWidget::hasMouseTracking() to get the current state of this flag.
  
  The \p camera parameter of the different functions is a pointer to the Camera used by the
  QGLViewer which calls the MouseGrabber. It can be used to compute 2D to 3D coordinates conversion
  using Camera::projectedCoordinatesOf() and Camera::unprojectedCoordinatesOf().
  
  Very complex behaviors can be implemented using this framework: auto-selected objects (no need to
  press a key to use them), automatic drop-down menus, 3D GUI, spinners using the wheelEvent(), and
  whatever your imagination creates.

  See the <a href="../examples/mouseGrabber.html">mouseGrabber example</a> for an illustration. Note
  that ManipulatedFrame are MouseGrabber : see the <a href="../examples/keyFrames.html">keyFrame
  example</a> for an illustration. Every created ManipulatedFrame is hence inserted in the
  MouseGrabberPool() (note however that ManipulatedCameraFrame are \e not inserted).
  
  Here is for instance a draft version of a movableObject class. Instances of these class can freely
  be moved on screen using the mouse. A possible application would be movable post-it-like notes.

  \code
  class movableObject : public MouseGrabber
  {
    movableObject() : posX(0), posY(0), moved(false) {};

    void checkIfGrabsMouse(int x, int y, const qglviewer::Camera* const)
    {
      // Active in a region of 5 pixel. Criterion should depend on object's shape.
      setGrabsMouse( sqrt((x-posX)*(x-posX) + (y-posY)*(y-posY)) < 5 );
    }

    void mousePressEvent(QMouseEvent *, Camera* const)   { moved = true; }
    void mouseReleaseEvent(QMouseEvent *, Camera* const) { moved = false; }
    
    void mouseMoveEvent(QMouseEvent *e, Camera* const)
    {
      if (moved)
      {
        posX = e->x();
        posY = e->y();
      }
    }

    void draw()
    {
      if (grabsMouse())
        if (moved)
	  // Object being moved, maybe a transparent display
        else
	  // Visual feedback (highlight) : object ready to be grabbed 
      else
        // Normal display
    }
  };
  \endcode
  \nosubgrouping */
  class QGLVIEWER_EXPORT MouseGrabber
  {
#ifndef DOXYGEN
    friend class ::QGLViewer;
#endif

  public:
    MouseGrabber();
    /*! Virtual destructor. Removes object from the MouseGrabberPool(). */
    virtual ~MouseGrabber() { MouseGrabber::MouseGrabberPool_.removeRef(this); };
    
    /*! @name Mouse detection */
    //@{
  public:
    /*! This is the core function of the MouseGrabber. It has to be overloaded and defined in your
    derived classes. Its goal is to update the grabsMouse() flag according to the mouse current
    positon, using setGrabsMouse().

    grabsMouse() should be set to \c true when the mouse cursor is close enough to the MouseGrabber
    position (or whatever is appropriate). It also \e must be set to \c false as soon as the mouse
    cursor leaves this region in order to release the mouse focus for the other parts of the
    application.
    
    A typical implementation will look like:
    \code
    // (posX,posY) is the position of the MouseGrabber on screen (origin in the \e upper left corner).
    // Here, distance to mouse must be less than 10 pixels to activate the MouseGrabber.
    setGrabsMouse( sqrt((x-posX)*(x-posX) + (y-posY)*(y-posY)) < 10);
    \endcode

    If the MouseGrabber position is defined in 3D. Project it on screen and then compare the
    projected coordinates:
    \code
    Vec proj = camera->projectedCoordinatesOf(myObject->frame()->position());
    setGrabsMouse((fabs(x-proj.x) < 5) && (fabs(y-proj.y) < 2));
    \endcode
    
    More complex behavior can be obtained using extra flags, for instance related to
    mousePressEvent() and mouseReleaseEvent(). See the detailed description section and the
    <a href="../examples/mouseGrabber.html">mouseGrabber example</a>. */
    virtual void checkIfGrabsMouse(int x, int y, const Camera* const camera) = 0;

    /*! Returns \p true when the MouseGrabber grabs the mouse and hence receives all the
    QGLViewer's mouse events. This flag is set with setGrabsMouse() by the checkIfGrabsMouse()
    function. */
    bool grabsMouse() { return grabsMouse_; };
    
  protected:
    /*! The protected method is used to define the grabsMouse() flag. See the grabsMouse() and
    the checkIfGrabsMouse() documentations. */
    void setGrabsMouse(const bool flag) { grabsMouse_ = flag; };
    //@}


    /*! @name MouseGrabber pool */
    //@{
  public:
    /*! This list contains all the created MouseGrabber. Used by the QGLViewer to
    check if any of them grabsMouse() using checkIfGrabsMouse().

    You should not have to directly use this list. In case you want to, use code like:
    \code
    QPtrListIterator<MouseGrabber> it(MouseGrabber::MouseGrabberPool());
    for (MouseGrabber* mg; (mg = it.current()) != NULL; ++it)
      mg->anyAction(); // possible dynamic_cast here.
    \endcode */
    static const QPtrList<MouseGrabber>& MouseGrabberPool() { return MouseGrabber::MouseGrabberPool_; };

    /*! Returns \c true if the MouseGrabber is currently in the MouseGrabberPool(). Default value is
      \p true. When set to false using removeFromMouseGrabberPool(), the MouseGrabber is no
      longer checkIfGrabsMouse() by QGLViewers. See also addInMouseGrabberPool(). */
    bool isInMouseGrabberPool() const { return MouseGrabber::MouseGrabberPool_.findRef( this ) != -1; };
    void addInMouseGrabberPool();
    void removeFromMouseGrabberPool();
    void clearMouseGrabberPool(bool autoDelete = false);
    //@}


    /*! @name Mouse event handlers
    The different functions called by the QGLViewer when the MouseGrabber grabsMouse(). */
    //@{
  protected:
    /*! See the associated QGLWidget documentation. The MouseGrabber will probably start an action
    or change its state when a mouse button is pressed. See the detailed description section for an example. */
    virtual void mousePressEvent(QMouseEvent* const, Camera* const) {};
    /*! See the associated QGLWidget documentation. See also mousePressEvent(). */
    virtual void mouseDoubleClickEvent(QMouseEvent* const, Camera* const) {};
    /*! See the associated QGLWidget documentation. A probable use of this function will be to
    desactivate the MouseGrabber. See the detailed description section for an example. */
    virtual void mouseReleaseEvent(QMouseEvent* const, Camera* const) {};
    /*! See the associated QGLWidget documentation. Probably useful to update the state of the
    MouseGrabber between a mousePressEvent() and a mouseReleaseEvent(). See the detailed
    description section for an example. */
    virtual void mouseMoveEvent(QMouseEvent* const, const Camera* const) {};
    /*! See the associated QGLWidget documentation. Can be useful to implement spinners. */
    virtual void wheelEvent(QWheelEvent* const, const Camera* const) {};
    //@}

  private:
    // Copy constructor and opertor= are declared private and undefined
    // Prevents everyone from trying to use them
    MouseGrabber(const MouseGrabber&);
    MouseGrabber& operator=(const MouseGrabber&);

    bool grabsMouse_;
    
    // Q G L V i e w e r   p o o l
    static QPtrList<MouseGrabber> MouseGrabberPool_;
  };

} // namespace qglviewer

#endif // QGLVIEWER_MOUSE_GRABBER_H
