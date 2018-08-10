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

#include "manipulatedFrame.h"
#include "qglviewer.h"
#include "camera.h"

using namespace qglviewer;
using namespace std;

/*! Creates a default manipulatedFrame. Translation is (0,0,0), with an identity rotation (0,0,0,1). */
ManipulatedFrame::ManipulatedFrame()
  : action_(QGLViewer::NO_MOUSE_ACTION), keepsGrabbingMouse_(false)
{
  setRotationSensitivity(1.0);
  setTranslationSensitivity(1.0);
  setSpinningSensitivity(0.3);
  setWheelSensitivity(1.0);
}


////////////////////////////////////////////////////////////////////////////////

/*! Default implementation of the MouseGrabber main function. MouseGrabber::grabsMouse() is set to
\p true when the mouse is within a 10 pixels region around the Camera::projectedCoordinatesOf()
position().

See the <a href="../examples/mouseGrabber.html">mouseGrabber example</a> for an illustration. */
void ManipulatedFrame::checkIfGrabsMouse(int x, int y, const Camera* const camera)
{
  const int thresold = 10;
  const Vec proj = camera->projectedCoordinatesOf(position());
  setGrabsMouse(keepsGrabbingMouse_ || ((fabs(x-proj.x) < thresold) && (fabs(y-proj.y) < thresold)));
}

////////////////////////////////////////////////////////////////////////////////
//          S t a t e   s a v i n g   a n d   r e s t o r i n g               //
////////////////////////////////////////////////////////////////////////////////

/*! Creates an XML QDomElement that represents the ManipulatedFrame. Add to
SpinningFrame::domElement() the ManipulatedFrame specific informations. \p name is the name of the
QDomElement tag. You need to provide the QDomDocument \p doc that will hold the resulting element.

Use initFromDOMElement() to restore the ManipulatedFrame state from the resulting domElement. */
QDomElement ManipulatedFrame::domElement(const QString& name, QDomDocument& doc) const
{
  QDomElement de = doc.createElement(name);
  de.setAttribute("rotSens", QString::number(rotationSensitivity()));
  de.setAttribute("transSens", QString::number(translationSensitivity()));
  de.setAttribute("spinSens", QString::number(spinningSensitivity()));
  de.appendChild(SpinningFrame::domElement("SpinningFrame", doc));

  return de;
}

/*! Restore the ManipulatedFrame state from a QDomElement created by domElement(). See also
Frame::initFromDOMElement(). */
void ManipulatedFrame::initFromDOMElement(const QDomElement& de)
{
  setRotationSensitivity((de.attribute("rotSens", "1.0")).toFloat());
  setTranslationSensitivity((de.attribute("transSens", "1.0")).toFloat());
  setSpinningSensitivity((de.attribute("spinSens", "0.3")).toFloat());

  QDomElement child=de.firstChild().toElement();
  while(!child.isNull())
    {
      if (child.tagName() == "SpinningFrame")
	SpinningFrame::initFromDOMElement(child);
      
      child = child.nextSibling().toElement();
    }
  
  action_ = QGLViewer::NO_MOUSE_ACTION;
  keepsGrabbingMouse_ = false;
}


////////////////////////////////////////////////////////////////////////////////
//                 M o u s e    h a n d l i n g                               //
////////////////////////////////////////////////////////////////////////////////

/*! \p True when the ManipulatedFrame is being manipulated with the mouse. Can be used to
  manually simulate the QGLViewer::fastDraw() function. Used by QGLViewer. */
bool ManipulatedFrame::isManipulated() const
{
  return action_ != QGLViewer::NO_MOUSE_ACTION;
}

#ifndef DOXYGEN
// Protected function used to handle mouse events
void ManipulatedFrame::startAction(int ma, bool withConstraint)
{
  action_ = (QGLViewer::MouseAction)(ma);
  withConstraint_ = withConstraint;

  switch (action_)
    {
    case QGLViewer::ROTATE:
    case QGLViewer::SCREEN_ROTATE:
      mouseSpeed_ = 0.0;
      stopSpinning();
      break;

    case QGLViewer::SCREEN_TRANSLATE:
      dirIsFixed_ = false;
      break;

    default:
      break;
    }
}

/*! Updates mouse speed, measured in pixels/msecs. Should be called by any function which wants to
use mouse speed. Currently used to start spinning in mouseReleaseEvent(). */
void ManipulatedFrame::computeMouseSpeed(const QMouseEvent* const e)
{
  const int deltaX = (e->x() - prevX_);
  const int deltaY = (e->y() - prevY_);
  float dist = sqrt(static_cast<float>(deltaX*deltaX + deltaY*deltaY));
  delay_ = last_move_time.restart();
  mouseSpeed_ = dist/delay_;	  
}

/*! Return 1 if mouse motion was started horizontally and -1 if it was more vertical. Returns 0 if
this could not be determined yet (perfect diagonal motion, rare). */
int ManipulatedFrame::mouseOriginalDirection(const QMouseEvent* const e)
{
  static bool horiz = true; // Two simultaneous manipulatedFrame require two mice !
	    
  if (!dirIsFixed_)
    {
      dirIsFixed_ = abs(e->x() - pressX_) != abs(e->y() - pressY_);
      horiz = abs(e->x() - pressX_) > abs(e->y() - pressY_);
    }

  if (dirIsFixed_)
    if (horiz)
      return 1;
    else 
      return -1;
  else
    return 0;
}
#endif // DOXYGEN

/*! The mouse behavior depends on which button is pressed. See the <a href="../mouse.html">QGLViewer
mouse page</a> for details. */
void ManipulatedFrame::mousePressEvent(QMouseEvent* const e, Camera* const)
{
  if (grabsMouse())
    keepsGrabbingMouse_ = true;
  
#if QT_VERSION >= 300
  if (action_ == QGLViewer::NO_MOUSE_ACTION)
    e->ignore();
#endif

  prevX_ = pressX_ = e->x();
  prevY_ = pressY_ = e->y();
}

/*! Move the manipulated frame according to the mouse motion. The camera is given as an argument so
that its parameters (width and height of the window, fieldOfView) are available in order to fit the
mouse motion and the display. Emits manipulated(). */
void ManipulatedFrame::mouseMoveEvent(QMouseEvent* const e, const Camera* const camera)
{
  if (action_ != QGLViewer::NO_MOUSE_ACTION)
    {
      switch (action_)
	{
	case QGLViewer::TRANSLATE:
	  {
	    Vec trans(static_cast<float>(e->x() - prevX_), static_cast<float>(prevY_ - e->y()), 0.0);
	    // Scale to fit the screen mouse displacement
	    switch (camera->type())
	      {
	      case Camera::PERSPECTIVE :
		trans *= 2.0 * tan(camera->fieldOfView()/2.0) * fabs((camera->frame()->coordinatesOf(position())).z) / camera->screenHeight();
		break;
	      case Camera::ORTHO :
		{
		  GLdouble w,h;
		  camera->getOrthoWidthHeight(w, h);
		  trans[0] *= 2.0 * w / camera->screenWidth();
		  trans[1] *= 2.0 * h / camera->screenHeight();
		  break;
		}
	      }
	    // Transform to world coordinate system.
	    trans = camera->frame()->orientation().rotate(translationSensitivity()*trans);
	    // And then down to frame
	    if (referenceFrame()) trans = referenceFrame()->transformOf(trans);
	    translate(trans);
	    break;
	  }

	case QGLViewer::ZOOM:
	  {
	    //#CONNECTION# wheelEvent ZOOM case
	    Vec trans(0.0, 0.0, (camera->position()-position()).norm() * (e->y() - prevY_) / camera->screenHeight());

	    trans = camera->frame()->orientation().rotate(trans);
	    if (referenceFrame())
	      trans = referenceFrame()->transformOf(trans);
	    translate(trans);
	    break;
	  }
	  
	case QGLViewer::SCREEN_ROTATE:
	  {
	    Vec trans = camera->projectedCoordinatesOf(position());

	    const double prev_angle = atan2(prevY_-trans[1], prevX_-trans[0]);
	    const double      angle = atan2(e->y()-trans[1], e->x()-trans[0]);

	    const Vec axis = transformOf(camera->frame()->inverseTransformOf(Vec(0.0, 0.0, -1.0)));
	    Quaternion rot(axis, angle-prev_angle);
	    rotate(rot);
	    //#CONNECTION# These two functions should go together (spinning detection and activation)
	    computeMouseSpeed(e);
	    setSpinningQuaternion(rot);
	    break;
	  }
	  
	case QGLViewer::SCREEN_TRANSLATE:
	  {
	    Vec trans;
	    int dir = mouseOriginalDirection(e);
	      if (dir == 1)
		trans.setValue(static_cast<float>(e->x() - prevX_), 0.0, 0.0);
	      else if (dir == -1)
		trans.setValue(0.0, static_cast<float>(prevY_ - e->y()), 0.0);

	    switch (camera->type())
	      {
	      case Camera::PERSPECTIVE :
		trans *= 2.0 * tan(camera->fieldOfView()/2.0) * fabs((camera->frame()->coordinatesOf(position())).z) / camera->screenHeight();
		break;
	      case Camera::ORTHO :
		{
		  GLdouble w,h;
		  camera->getOrthoWidthHeight(w, h);
		  trans[0] *= 2.0 * w / camera->screenWidth();
		  trans[1] *= 2.0 * h / camera->screenHeight();
		  break;
		}
	      }
	    // Transform to world coordinate system.
	    trans = camera->frame()->orientation().rotate(translationSensitivity()*trans);
	    // And then down to frame
	    if (referenceFrame())
	      trans = referenceFrame()->transformOf(trans);

	    translate(trans);	    
	    break;
	  }
	  
	case QGLViewer::ROTATE:
	  {
	    Vec trans = camera->projectedCoordinatesOf(position());
	    Quaternion rot = quaternionFromDeformedBall(e->x(), e->y(), trans[0], trans[1], camera);
	    trans = Vec(-rot[0], -rot[1], -rot[2]);
	    trans = camera->frame()->orientation().rotate(trans);
	    trans = transformOf(trans);
	    rot[0] = trans[0];
	    rot[1] = trans[1];
	    rot[2] = trans[2];
	    rotate(rot);
	    //#CONNECTION# These two functions should go together (spinning detection and activation)
	    computeMouseSpeed(e);
	    setSpinningQuaternion(rot);
	    break;
	  }
	default:
	  qWarning("ManipulatedFrame::mouseMoveEvent : unhandled mouse action");
	}
      
      prevX_ = e->x();
      prevY_ = e->y();
      emit manipulated();
    }
}


/*! When the user releases the mouse button, the manipulatedFrame action is stopped.

If the action was a rotation, a continuous spinning is possible if the speed of the
cursor is larger than spinningSensitivity() when the button is released. Press the rotate button
again to stop the spinning. */
void ManipulatedFrame::mouseReleaseEvent(QMouseEvent* const, Camera* const camera)
{
  keepsGrabbingMouse_ = false;
  
  if (((action_ == QGLViewer::ROTATE) || (action_ == QGLViewer::SCREEN_ROTATE)) && (mouseSpeed_ >= spinningSensitivity()))
    {
      setRotationCenter(camera->revolveAroundPoint());
      startSpinning(delay_);
    }

  action_ = QGLViewer::NO_MOUSE_ACTION;
}

/*! Using the wheel is equivalent to a ZOOM action. See QGLViewer::setWheelBinding() and
  setWheelSensitivity().

Depending on your system configuration, you may have to actually \e press the wheel while
wheeling. */
void ManipulatedFrame::wheelEvent(QWheelEvent* const e, const Camera* const camera)
{
  //#CONNECTION# QGLViewer::setWheelBinding
  if (action_ == QGLViewer::ZOOM)
    {
      const float wheelSensitivityCoef = 8E-4f;
      Vec trans(0.0, 0.0, -e->delta()*wheelSensitivity()*wheelSensitivityCoef*(camera->position()-position()).norm());

      //#CONNECTION# Cut-pasted from the mouseMoveEvent ZOOM case
      trans = camera->frame()->orientation().rotate(trans);
      if (referenceFrame())
	trans = referenceFrame()->transformOf(trans);
      translate(trans);
      emit manipulated();
    }
  action_ = QGLViewer::NO_MOUSE_ACTION;
}


////////////////////////////////////////////////////////////////////////////////

/*! Returns "pseudo-distance" from (x,y) to ball of radius size.
\arg for a point inside the ball, it is proportionnal to the euclidean distance to the ball
\arg for a point outside the ball, it is proportionnal to the inverse of this distance (tends to
zero) on the ball, the function is continuous. */
static float projectOnBall(const float x, const float y) 
{
  // If you change the size value, change angle computation in quaternionFromDeformedBall().
  const float size       = 1.0f;
  const float size2      = size*size;
  const float size_limit = size2*0.5;

  const float d = x*x + y*y;
  return d < size_limit ? sqrt(size2 - d) : size_limit/sqrt(d);
}

#ifndef DOXYGEN
/*! Returns a quaternion computed according to the mouse motion. Mouse positions are projected on a
deformed ball, centered on (cx,cy). */
Quaternion ManipulatedFrame::quaternionFromDeformedBall(const int x, const int y, const float cx, const float cy, const Camera* const camera)
{
  // Points on the deformed ball
  float px = rotationSensitivity() * (prevX_  - cx)	/ camera->screenWidth();
  float py = rotationSensitivity() * (cy - prevY_)	/ camera->screenHeight();
  float dx = rotationSensitivity() * (x - cx)		/ camera->screenWidth();
  float dy = rotationSensitivity() * (cy - y)		/ camera->screenHeight();

  const Vec p1(px, py, projectOnBall(px, py));
  const Vec p2(dx, dy, projectOnBall(dx, dy));
  // Approximation of rotation angle
  // Should be divided by the projectOnBall size, but it is 1.0
  const Vec axis = cross(p2,p1);
  const float angle = 2.0 * asin(sqrt(axis.sqNorm() / p1.sqNorm() / p2.sqNorm()));
  return Quaternion(axis, angle);
}
#endif // DOXYGEN
