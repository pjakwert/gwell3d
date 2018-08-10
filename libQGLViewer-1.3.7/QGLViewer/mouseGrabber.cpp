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

#include "mouseGrabber.h"

using namespace qglviewer;

// Static private variable
QPtrList<MouseGrabber> MouseGrabber::MouseGrabberPool_;

/*! Adds the created MouseGrabber in the MouseGrabberPool(). grabsMouse() set to \c false. */
MouseGrabber::MouseGrabber()
  : grabsMouse_(false)
{
  addInMouseGrabberPool();
}

/*! Adds the MouseGrabber in the MouseGrabberPool(). Note that all MouseGrabber are automatically
added in the MouseGrabberPool() by the constructor. Trying to add a MouseGrabber that already
isInMouseGrabberPool() has no effect.

Use removeFromMouseGrabberPool() to remove the MouseGrabber from the list, so that it is no longer
tested with checkIfGrabsMouse() by the QGLViewer. Use isInMouseGrabberPool() to know the current
state of the MouseGrabber. */
void MouseGrabber::addInMouseGrabberPool()
{
  if (!isInMouseGrabberPool())
    MouseGrabber::MouseGrabberPool_.append(this);
}

/*! Removes the MouseGrabber from the MouseGrabberPool(). See addInMouseGrabberPool() for details.
Removing a MouseGrabber that is not in MouseGrabberPool() has no effect. */
void MouseGrabber::removeFromMouseGrabberPool()
{
  if (isInMouseGrabberPool())
    MouseGrabber::MouseGrabberPool_.removeRef(this);
}

/*! Clears the mouseGrabberPool(). Consider using QGLViewer::setMouseTracking(false) to disable all
mouse grabbers.

When \p autoDelete is set to \c true, all the MouseGrabbers themselves are actually deleted (use
this only if you're sure of what you do). */
void MouseGrabber::clearMouseGrabberPool(bool autoDelete)
{
  MouseGrabber::MouseGrabberPool_.setAutoDelete(autoDelete);
  MouseGrabber::MouseGrabberPool_.clear();
}
