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

#include "manipulatedCameraFrame.h"
#include "qglviewer.h"
#include "camera.h"

using namespace qglviewer;
using namespace std;

/*! Creates a default ManipulatedCameraFrame. Created object is removeFromMouseGrabberPool(). */
ManipulatedCameraFrame::ManipulatedCameraFrame()
  : flyUpVector_(0.0, 1.0, 0.0)
{
  setFlySpeed(0.0);

  connect(&flyTimer_, SIGNAL(timeout()), SLOT(updateFrameInFlyMode()));

  removeFromMouseGrabberPool();
}


////////////////////////////////////////////////////////////////////////////////

/*! Called for continuous frame motion in fly mode (see QGLViewer::MOVE_FORWARD). Emits
  manipulated(). */
void ManipulatedCameraFrame::updateFrameInFlyMode()
{
  static Vec flyDisp(0.0, 0.0, 0.0);
  switch (action_)
    {
    case QGLViewer::MOVE_FORWARD:
      flyDisp.z = -flySpeed();
      translate(inverseTransformOf(flyDisp));
      break;
    case QGLViewer::MOVE_BACKWARD:
      flyDisp.z = flySpeed();
      translate(inverseTransformOf(flyDisp));
      break;
    default:
      break;
    }
    
  emit manipulated();
}

/*! This function will be called by the camera when the camera orientation is changed, so that the
flyUpVector (private) is changed accordingly. You should not need to call this function. */
void ManipulatedCameraFrame::updateFlyUpVector()
{
  flyUpVector_ = inverseTransformOf(Vec(0.0, 1.0, 0.0));
}

////////////////////////////////////////////////////////////////////////////////
//          S t a t e   s a v i n g   a n d   r e s t o r i n g               //
////////////////////////////////////////////////////////////////////////////////

/*! Creates an XML QDomElement that represents the ManipulatedCameraFrame. Add to
ManipulatedFrame::domElement() the ManipulatedCameraFrame specific informations. \p name is the name
of the QDomElement tag. You need to provide the QDomDocument \p doc that will hold the resulting
element.

Use initFromDOMElement() to restore the ManipulatedCameraFrame state from the resulting domElement. */
QDomElement ManipulatedCameraFrame::domElement(const QString& name, QDomDocument& doc) const
{
  QDomElement de = doc.createElement(name);
  de.setAttribute("FlySpeed", QString::number(flySpeed()));
  de.appendChild(flyUpVector().domElement("flyUpVector", doc));
  de.appendChild(ManipulatedFrame::domElement("ManipulatedFrame", doc));

  return de;
}

/*! Restore the ManipulatedCameraFrame state from a QDomElement created by domElement(). See also
Frame::initFromDOMElement(). */
void ManipulatedCameraFrame::initFromDOMElement(const QDomElement& de)
{
  setFlySpeed((de.attribute("FlySpeed", "0.0")).toFloat());
  QDomElement child=de.firstChild().toElement();
  while(!child.isNull())
    {
      if (child.tagName() == "flyUpVector")
	flyUpVector_.initFromDOMElement(child);

      if (child.tagName() == "ManipulatedFrame")
	ManipulatedFrame::initFromDOMElement(child);

      child = child.nextSibling().toElement();
    }
}


////////////////////////////////////////////////////////////////////////////////
//                 M o u s e    h a n d l i n g                               //
////////////////////////////////////////////////////////////////////////////////

// Protected function used to handle mouse events
void ManipulatedCameraFrame::startAction(int ma, bool withConstraint)
{
  ManipulatedFrame::startAction(ma, withConstraint);
  
  switch (action_)
    {
    case QGLViewer::MOVE_FORWARD:
    case QGLViewer::MOVE_BACKWARD:
      flyTimer_.start(10);
      break;
    default:
      break;
    }
}

/*! Move the camera frame according to the mouse motion. The camera is given as an argument so that
its parameters (width and height of the window, fieldOfView) are available in order to fit the mouse
motion and the display. Emits manipulated(). */
void ManipulatedCameraFrame::mouseMoveEvent(QMouseEvent* const e, const Camera* const camera)
{
  // #CONNECTION# QGLViewer::mouseMoveEvent does the updateGL.
  if (action_ != QGLViewer::NO_MOUSE_ACTION)
    {
      if (action_ == QGLViewer::ZOOM_ON_REGION)
	{
	  prevX_ = e->x();
	  prevY_ = e->y();
	}
      else
	{
	  switch (action_)
	    {
	    case QGLViewer::TRANSLATE:
	      {
		Vec trans(static_cast<float>(prevX_ - e->x()), static_cast<float>(e->y() - prevY_), 0.0);
		// Scale to fit the screen mouse displacement
		switch (camera->type())
		  {
		  case Camera::PERSPECTIVE :
		    trans *= 2.0 * tan(camera->fieldOfView()/2.0) *
		      fabs((camera->frame()->coordinatesOf(camera->revolveAroundPoint())).z) / camera->screenHeight();
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
		translate(inverseTransformOf(translationSensitivity()*trans));
		break;
	      }
	  
	    case QGLViewer::MOVE_BACKWARD:
	      {
		Quaternion rot = quaternionFromThetaPhi(e->x(), e->y(), camera);
		rotate(rot);
		translate(inverseTransformOf(Vec(0.0, 0.0, flySpeed())));
		break;
	      }

	    case QGLViewer::MOVE_FORWARD:
	      {
		Quaternion rot = quaternionFromThetaPhi(e->x(), e->y(), camera);
		rotate(rot);
		//#CONNECTION# wheelEvent MOVE_FORWARD case
		translate(inverseTransformOf(Vec(0.0, 0.0, -flySpeed())));
		break;
	      }

	    case QGLViewer::ZOOM:
	      {
		//#CONNECTION# wheelEvent() ZOOM case
		float coef = QMAX(camera->distanceToSceneCenter(), 0.2f*camera->sceneRadius());
		Vec trans(0.0, 0.0, -coef * (e->y() - prevY_) / camera->screenHeight());
		translate(inverseTransformOf(trans));
		break;
	      }
	  
	    case QGLViewer::LOOK_AROUND: 
	      {
		Quaternion rot = quaternionFromThetaPhi(e->x(), e->y(), camera);
		rotate(rot);
		break;
	      }
	  
	    case QGLViewer::ROTATE:
	      {
		Vec trans = camera->projectedCoordinatesOf(camera->revolveAroundPoint());
		Quaternion rot = quaternionFromDeformedBall(e->x(), e->y(), trans[0], trans[1], camera);
		rotateAroundPoint(rot, camera->revolveAroundPoint());
		//#CONNECTION# These two functions should go together (spinning detection and activation)
		computeMouseSpeed(e);
		setSpinningQuaternion(rot);
		break;
	      }
	    
	    case QGLViewer::SCREEN_ROTATE:
	      {
		Vec trans = camera->projectedCoordinatesOf(camera->revolveAroundPoint());

		const float angle = atan2(e->y() - trans[1], e->x() - trans[0]) - atan2(prevY_-trans[1], prevX_-trans[0]);
	    
		Quaternion rot(Vec(0.0, 0.0, 1.0), angle);
		rotateAroundPoint(rot, camera->revolveAroundPoint());
		updateFlyUpVector();
		//#CONNECTION# These two functions should go together (spinning detection and activation)
		computeMouseSpeed(e);
		setSpinningQuaternion(rot);
		break;
	      }

	    case QGLViewer::SCREEN_ROTATE_BOTTOM:
	      {
		const float angle = M_PI * (e->x() - prevX_) / camera->screenWidth();
		Quaternion rot(Vec(0.0, 0.0, 1.0), angle);
		rotate(rot);
		setSpinningQuaternion(rot);
		updateFlyUpVector();
		break;
	      }
	  
	    case QGLViewer::SCREEN_TRANSLATE:
	      {
		Vec trans;
		int dir = mouseOriginalDirection(e);
		if (dir == 1)
		  trans.setValue(static_cast<float>(prevX_ - e->x()), 0.0, 0.0);
		else if (dir == -1)
		  trans.setValue(0.0, static_cast<float>(e->y() - prevY_), 0.0);

		switch (camera->type())
		  {
		  case Camera::PERSPECTIVE :
		    trans *= 2.0 * tan(camera->fieldOfView()/2.0) *
		      fabs((camera->frame()->coordinatesOf(camera->revolveAroundPoint())).z) / camera->screenHeight();
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

		translate(inverseTransformOf(translationSensitivity()*trans));
		break;
	      }

	    case QGLViewer::ZOOM_ON_REGION:
	    case QGLViewer::NO_MOUSE_ACTION:
	      break;
	    }

	  prevX_ = e->x();
	  prevY_ = e->y();
	  emit manipulated();
	}
    }
}

/*! When the user releases the mouse button, the manipulatedFrame action is stopped. */
void ManipulatedCameraFrame::mouseReleaseEvent(QMouseEvent* const e, Camera* const camera)
{
  if ((action_ == QGLViewer::MOVE_FORWARD) || (action_ == QGLViewer::MOVE_BACKWARD))
    flyTimer_.stop();

  if (action_ == QGLViewer::ZOOM_ON_REGION)
    camera->fitScreenRegion(pressX_, pressY_, e->x(), e->y());
  
  ManipulatedFrame::mouseReleaseEvent(e, camera);
}

/*! The wheel behavior depends on the wheel binded action. Current possible actions are ZOOM,
MOVE_FORWARD, MOVE_BACKWARD. See QGLViewer::setWheelBinding() to customize the binding.

ZOOM speeds depends on wheelSensitivity() while MOVE_FORWARD and MOVE_BACKWARD depend on flySpeed().

Depending on your system configuration, you may have to actually \e press the wheel while
wheeling. */
void ManipulatedCameraFrame::wheelEvent(QWheelEvent* const e, const Camera* const camera)
{
  //#CONNECTION# QGLViewer::setWheelBinding, ManipulatedFrame::wheelEvent.
  switch (action_)
    {
    case QGLViewer::ZOOM:
      {
	const float wheelSensitivityCoef = 8E-4f;
	//#CONNECTION# mouseMoveEvent() ZOOM case
	const float coef = QMAX(camera->distanceToSceneCenter(), 0.2f*camera->sceneRadius());
	Vec trans(0.0, 0.0, coef * e->delta() * wheelSensitivity() * wheelSensitivityCoef);
	translate(inverseTransformOf(trans));
	emit manipulated();
	break;
      }
    case QGLViewer::MOVE_FORWARD:
    case QGLViewer::MOVE_BACKWARD:
      //#CONNECTION# mouseMoveEvent() MOVE_FORWARD case
      translate(inverseTransformOf(Vec(0.0, 0.0, 0.2*flySpeed()*e->delta())));
      emit manipulated();
      break;
    default:
      break;
    }
  action_ = QGLViewer::NO_MOUSE_ACTION;
}

////////////////////////////////////////////////////////////////////////////////

/*! Set lastQuat according to the mouse motion. Simple Theta,Phi inferred from the X,flyUpVector() axis. */
Quaternion ManipulatedCameraFrame::quaternionFromThetaPhi(const int x, const int y, const Camera* const camera)
{
  const Quaternion rotX(Vec(1.0, 0.0, 0.0), rotationSensitivity()*static_cast<float>(prevY_-y)/camera->screenHeight());
  const Quaternion rotY(transformOf(flyUpVector()), rotationSensitivity()*static_cast<float>(prevX_-x)/camera->screenWidth());
  return rotY * rotX;
}
