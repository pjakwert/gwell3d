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

#include "vec.h"

// Most of the methods are declared inline in vec.h

using namespace qglviewer;
using namespace std;

/*! Projects on the axis whose direction is dir (and that passes through the origin).
  \attention The axis direction vector must be normalized. This is checked if the library was compiled with the "debug" qt \p CONFIG flag. */
void Vec::projectOnAxis (const Vec& dir)
{
#ifndef QT_NO_DEBUG
  // We assume dir is normalized
  if (fabs(1.0-dir.norm()) > 1.0E-6)
    qWarning("Vec::projectOnAxis : axis direction is not normalized (norm=%f).", dir.norm());
#endif
  const float dot = x*dir.x + y*dir.y + z*dir.z ;
  x = dot*dir.x;
  y = dot*dir.y;
  z = dot*dir.z;
}

/*! Projects on the plane whose normal is n and that passes through the origin.
  \attention The plane normal vector must be normalized. This is checked in the debug library release. */
void Vec::projectOnPlane(const Vec& n)
{
#ifndef QT_NO_DEBUG
  // We assume dir is normalized
  if (fabs(1.0-n.norm()) > 1.0E-6)
    qWarning("Vec::projectOnPlane : plane normal is not normalized (norm=%f).", n.norm());
#endif
  const float dot = x*n.x + y*n.y + z*n.z ;

  x -= dot*n.x;
  y -= dot*n.y;
  z -= dot*n.z;
}

/*! Creates an XML QDomElement that represents the Vec. \p name is the name of the
 QDomElement tag. You need to provide the QDomDocument \p doc that will hold the resulting
 element. Typical usage would be:
 \code
 QDomDocument doc("myDocument");
 Vec sunPos;
 // ...
 anyNode.addElement(sunPos.domElement("sunPosition", doc));
 // ...
 \endcode
 Use initFromDOMElement() to restore the Vec state from the resulting domElement.

 See also Quaternion::domElement(), Camera::domElement(), KeyFrameInterpolator::domElement()... */
QDomElement Vec::domElement(const QString& name, QDomDocument& doc) const
{
  QDomElement de = doc.createElement(name);
  de.setAttribute("x", QString::number(x));
  de.setAttribute("y", QString::number(y));
  de.setAttribute("z", QString::number(z));
  return de;
}

/*! Restore the Vec state from a QDomElement created by domElement(). The QDomElement must contain
  the \e x, \e y and \e z attributes, otherwise these fields are set to 0.0. */
void Vec::initFromDOMElement(const QDomElement& de)
{
  setValue((de.attribute("x", "0.0")).toFloat(),(de.attribute("y", "0.0")).toFloat(),(de.attribute("z", "0.0")).toFloat());
}

ostream& operator<<(ostream& o, const Vec& v)
{
  return o << v.x << '\t' << v.y << '\t' << v.z;
}

