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

#include "spinningFrame.h"

#if QT_VERSION < 300
# include "qglviewer.h" // Needed to connectSignalToAllViewers.
#endif

using namespace qglviewer;
using namespace std;

/*! Constructor sets default values : isSpinning() is \p false and updateInterval() is set to 40. */
SpinningFrame::SpinningFrame()
  : isSpinning_(false), updateInterval_(40), rotatesAroundCenter_(false), frozenOrientation_(false)
{
  connect(&timer_, SIGNAL(timeout()), SLOT(updateFrame()));

#if QT_VERSION < 300 
  // Qt 2.3 has problems with inherited signals.
  // Instead of connecting spinned only to the right viewer, connect it to all.
  QGLViewer::connectSignalToAllViewers(this, SIGNAL(spinned()));
#endif
}

/*! Update the Frame orientation (and possibly position), according to the SpinningFrame parameters.
  Emits spinned(). */
void SpinningFrame::updateFrame()
{
  if (rotatesAroundCenter())
    if (orientationIsFrozen())
      setPosition(Quaternion(inverseTransformOf(spinningQuaternion().axis()), spinningQuaternion().angle()).
		  rotate(position()-rotationCenter())+rotationCenter());
    else
      rotateAroundPoint(spinningQuaternion(), rotationCenter());
  else
    rotate(spinningQuaternion());
  
  emit spinned();
}


/*! Starts the spinning of the frame. Use stopSpinning() to stop.
  
\p msec milliseconds will separate each update of the SpinningFrame position and orientation.
When no interval is specified, the previous updateInterval() is used, otherwise updateInterval()
is set to \p msecs.

See the <a href="../examples/spinningFrame.html">spinningFrame</a> example for an illustration. */
void SpinningFrame::startSpinning(const int msecs)
{
  if (msecs >= 0)
    setUpdateInterval(msecs);
  timer_.start(updateInterval());
  isSpinning_ = true;
}


/*! Creates an XML QDomElement that represents the SpinningFrame. Add to Frame::domElement() the
  SpinningFrame specific informations. \p name is the name of the QDomElement tag. You need to
  provide the QDomDocument \p doc that will hold the resulting element.

  Use initFromDOMElement() to restore the SpinningFrame state from the resulting domElement. */
QDomElement SpinningFrame::domElement(const QString& name, QDomDocument& doc) const
{
  QDomElement de = doc.createElement(name);
  de.setAttribute("UpdateInterval", QString::number(updateInterval()));
  de.setAttribute("RAP", (rotatesAroundCenter()?"true":"false"));
  de.setAttribute("frozen", (orientationIsFrozen()?"true":"false"));
  de.appendChild(rotationCenter().domElement("RotationCenter", doc));
  de.appendChild(spinningQuaternion().domElement("SpinningQuaternion", doc));
  de.appendChild(Frame::domElement("Frame", doc));

  return de;
}

/*! Restore the SpinningFrame state from a QDomElement created by domElement(). See also
  Frame::initFromDOMElement(). */
void SpinningFrame::initFromDOMElement(const QDomElement& de)
{
  freezeOrientation((de.attribute("frozen", "false") == "true")?true:false);
  setRotateAroundCenter((de.attribute("RAP", "false") == "true")?true:false);
  setUpdateInterval((de.attribute("UpdateInterval", "40")).toInt());
  
  QDomElement child=de.firstChild().toElement();
  while(!child.isNull())
    {
      if (child.tagName() == "Frame")
	Frame::initFromDOMElement(child);

      if (child.tagName() == "SpinningQuaternion")
	spinningQuaternion_.initFromDOMElement(child);
	      
      if (child.tagName() == "RotationCenter")
	rotationCenter_.initFromDOMElement(child);

      child = child.nextSibling().toElement();
    }
  
  stopSpinning();
}
