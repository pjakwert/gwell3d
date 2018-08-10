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

#include "keyFrameInterpolator.h"
#include "frame.h"
#include <math.h>

using namespace qglviewer;
using namespace std;

KeyFrameInterpolator::KeyFrame::KeyFrame(const Frame& fr, const float t)
  : time_(t), frame_(NULL)
{
  p_ = fr.position();
  q_ = fr.orientation();
}

KeyFrameInterpolator::KeyFrame::KeyFrame(const Frame* fr, const float t)
  : time_(t), frame_(fr)
{
  updateValuesFromPointer();
}

void KeyFrameInterpolator::KeyFrame::updateValuesFromPointer()
{
  p_ = frame_->position();
  q_ = frame_->orientation();
}

void KeyFrameInterpolator::KeyFrame::computeTangent(const KeyFrame* const prev, const KeyFrame* const next)
{
  tgP_ = 0.5 * (next->position() - prev->position());
  tgQ_ = Quaternion::squadTangent(prev->orientation(), q_, next->orientation());
}

void KeyFrameInterpolator::KeyFrame::flipOrientation(const Quaternion& prev)
{
  if (Quaternion::dot(prev, q_) < 0.0)
    q_.negate();
}
 
/*! Creates a KeyFrameInterpolator, which will drive the \p fr frame. See setFrame() for details on
  the associated frame \p fr.

  Use addKeyFrame() to define the key frames.
  Default interpolationTime() is 0.0, and interpolationSpeed() is 1.0.

  See the <a href="../examples/keyFrames.html">keyFrames</a> example for an illustration. */
KeyFrameInterpolator::KeyFrameInterpolator(Frame* fr)
  : period_(40), interpolationTime_(0.0), interpolationSpeed_(1.0), interpolationStarted_(false),
    closedPath_(false), loopInterpolation_(false), pathIsValid_(false), valuesAreValid_(true), currentFrameValid_(false)
{
  setFrame(fr);
  keyFrame_.setAutoDelete(true);
  for (int i=0; i<4; ++i)
    currentFrame_[i] = new QPtrListIterator<KeyFrame>(keyFrame_);  
  connect(&timer_, SIGNAL(timeout()), SLOT(update()));
}

/*! Virtual destructor. Releases allocated memory. */
KeyFrameInterpolator::~KeyFrameInterpolator()
{
  stopInterpolation();
  for (int i=0; i<4; ++i)
    delete currentFrame_[i];
  keyFrame_.clear();
}

/*! Creates an XML QDomElement that represents the KeyFrameInterpolator. \p name is the name of the
 QDomElement tag. You need to provide the QDomDocument \p doc that will hold the resulting element.

 Use initFromDOMElement() to restore the KeyFrameInterpolator state from the resulting domElement.

 See also Camera::domElement(), Frame::domElement()...

 If you want to save the KeyFrameInterpolator \p kfi in a file, use
 \code
 QDomDocument doc( "myKFI" );
 doc.appendChild( kfi.domElement("KFI", doc) );
 ofstream file( "myKFI.xml" );
 file << doc.toString();
 \endcode
 Note that the Camera::keyFrameInterpolator() are automatically saved by QGLViewer::saveToFile()
 when a QGLViewer is closed (default shortcut key is Escape).
 
 Use the following code to retrieve the KeyFrameInterpolator \p kfi from the saved file:
 \code
 // Load DOM from file
 QDomDocument doc;
 QFile f("myKFI.xml");
 f.open(IO_ReadOnly);
 doc.setContent(&f);
 f.close();
 // Parse the DOM tree
 QDomElement main=doc.documentElement();
 kfi.initFromDOMElement(main);
 \endcode
 
 \attention For KeyFrames defined by pointers, only the \e values of the pointed Frame are saved.
 See Frame::domElement().
 \attention Only the KeyFrames are saved, you still need to define the attached frame() with
 setFrame(). */
QDomElement KeyFrameInterpolator::domElement(const QString& name, QDomDocument& doc) const
{
  QDomElement de = doc.createElement(name);
  int count = 0;
  for (KeyFrame* kf = keyFrame_.first(); kf; kf = keyFrame_.next() )
    {
      Frame fr(kf->position(), kf->orientation());
      QDomElement kfNode = fr.domElement("KeyFrame", doc);
      kfNode.setAttribute("Index", QString::number(count));
      kfNode.setAttribute("Time",  QString::number(kf->time()));
      de.appendChild(kfNode);
      ++count;
    }
  de.setAttribute("NbKF", QString::number(keyFrame_.count()));
  de.setAttribute("Time", QString::number(interpolationTime()));
  de.setAttribute("Speed", QString::number(interpolationSpeed()));
  de.setAttribute("ClosedPath", (closedPath()?"true":"false"));
  de.setAttribute("Loop", (loopInterpolation()?"true":"false"));
  return de;
}

/*! Restore the KeyFrameInterpolator state from a QDomElement created by domElement().
  See also Camera::initFromDOMElement(), Frame::initFromDOMElement().

  \attention For KeyFrames defined by pointers, only the \e values of the pointed Frame are saved.
  \attention Only the KeyFrames are saved, you still need to define the attached frame() with setFrame(). */
void KeyFrameInterpolator::initFromDOMElement(const QDomElement& de)
{
  keyFrame_.clear();
  QDomElement child=de.firstChild().toElement();
  while(!child.isNull())
    {
      if (child.tagName() == "KeyFrame")
	{
	  Frame fr;
	  fr.initFromDOMElement(child);
	  float time = (child.attribute("Time", "0.0")).toFloat();
	  addKeyFrame(fr, time);
	}

      child = child.nextSibling().toElement();
    }
  setInterpolationTime((de.attribute("Time", "0.0")).toFloat());
  setInterpolationSpeed((de.attribute("Speed", "1.0")).toFloat());
  setClosedPath((de.attribute("ClosedPath", "false") == "true")?true:false);
  setLoopInterpolation((de.attribute("Loop", "false") == "true")?true:false);
  
  // setFrame(NULL);
  pathIsValid_ = false;
  valuesAreValid_ = false;
  stopInterpolation();
  period_ = 40;
  currentFrameValid_ = false;
}


/*! Interpolates frame() for the next interpolationTime() (defined by interpolationPeriod()). This
  internal function is called by a timer when startInterpolation() is called. It is publicly
  provided for your debugging purpose only. stopInterpolation() is called when interpolationTime()
  reaches the first or last keyFrameTime(), unless loopInterpolation() is \p true. */
void KeyFrameInterpolator::update()
{
  interpolateAtTime(interpolationTime_);
  
  interpolationTime_ += interpolationSpeed_ * period_ / 1000.0;

  if (interpolationTime_ > keyFrame_.getLast()->time())
    {
      if (loopInterpolation_)
	setInterpolationTime(keyFrame_.getFirst()->time() + interpolationTime_ - keyFrame_.getLast()->time());
      else
	{
	  interpolationTime_ = keyFrame_.getLast()->time();
	  stopInterpolation();
	}
      emit finished();
    }
  else
    if (interpolationTime_ < keyFrame_.getFirst()->time())
      {
	if (loopInterpolation_)
	  setInterpolationTime(keyFrame_.getLast()->time() - keyFrame_.getFirst()->time() + interpolationTime_);
	else
	  {
	    interpolationTime_ = keyFrame_.getFirst()->time();
	    stopInterpolation();
	  }
	emit finished();
      }
}



/*! Starts the interpolation process. A timer will be started with a period defined by \p msecs. The
  timer calls update() to update the frame() position and orientation. Use stopInterpolation() to
  stop interpolation, and setInterpolationTime() to change the interpolationTime().
  interpolationIsStarted() will be \p true until stopInterpolation() is called.

  If interpolationTime() is greater than the last keyFrameTime(), it is reset to the first
  keyFrameTime() and interpolation starts from there (natural behavior).
  
  If \p msecs is negative (default with no parameter), the current interpolationPeriod() will be
  used (default is 25Hz, see setInterpolationPeriod()), otherwise interpolationPeriod() will be set
  to \p msecs.

  You may also be interested in QGLViewer::animate() and QGLViewer::startAnimation().

  See the <a href="../examples/keyFrames.html">keyFrames</a> example for an illustration.
  
  \attention The keyFrames must be defined \e before you startInterpolation(), or else the
  interpolation will naturally immediately stop. */
void KeyFrameInterpolator::startInterpolation(const int msecs)
{
  if (msecs >= 0)
    setInterpolationPeriod(msecs);

  if (!keyFrame_.isEmpty())
    {
      if (interpolationTime() >= keyFrame_.getLast()->time())
	setInterpolationTime(keyFrame_.getFirst()->time());
      timer_.start(period_);
      interpolationStarted_ = true;
      update();
    }
}


/*! Stops an interpolation started with startInterpolation(). */
void KeyFrameInterpolator::stopInterpolation()
{
  timer_.stop();
  interpolationStarted_ = false;
}


/*! interpolationTime() is reset to the keyFrameTime() associated with the first keyFrame and
  interpolation is stopped (not much more than stopInterpolation() and setInterpolationTime()). */
void KeyFrameInterpolator::resetInterpolation()
{
  stopInterpolation();
  if (!keyFrame_.isEmpty())
    setInterpolationTime(keyFrame_.getFirst()->time());
}


/*! Same as the reference version of addKeyFrame(), but with a pointer to a frame. \p NULL pointers
  are silently ignored.
  
  See the <a href="../examples/keyFrames.html">keyFrames</a> example for an illustration. */
void KeyFrameInterpolator::addKeyFrame(const Frame* fr)
{
  float time;
  if (keyFrame_.isEmpty())
    time = 0.0;
  else
    time = keyFrame_.getLast()->time() + 1.0;

  addKeyFrame(fr, time);
}


/*! Same as the reference version of addKeyFrame(), but with a pointer to a frame. \p NULL pointers
  are silently ignored. */
void KeyFrameInterpolator::addKeyFrame(const Frame* fr, const float time)
{
  if (!fr)
    return;

  if (keyFrame_.isEmpty())
    interpolationTime_ = time;
  
  if ( (!keyFrame_.isEmpty()) && (keyFrame_.getLast()->time() > time) )
    qWarning("Error in KeyFrameInterpolator::addKeyFrame : time is not monotone");
  else
    keyFrame_.append(new KeyFrame(fr, time));
#if QT_VERSION < 300
  qWarning("Qt version 2.3 has problems with inherited signals, pointers to Frames are not supported in addKeyFrame.");
#else
  connect(fr, SIGNAL(modified()), SLOT(invalidateValues()));
#endif
  valuesAreValid_ = false;
  pathIsValid_ = false;
  currentFrameValid_ = false;
  resetInterpolation();
}


/*! Defines a new keyFrame. Same as addKeyFrame() with a keyFrameTime() specification, except that
  the time is automatically set as previous keyFrameTime() + 1 second.

  See the <a href="../examples/keyFrames.html">keyFrames</a> example for an illustration. */
void KeyFrameInterpolator::addKeyFrame(const Frame& fr)
{
  float time;
  if (keyFrame_.isEmpty())
    time = 0.0;
  else
    time = keyFrame_.getLast()->time() + 1.0;

  addKeyFrame(fr, time);
}


/*! Defines a new keyFrame, and the associated time (in seconds) that will be used to rhythm the
  interpolation. The keyFrameTime() have to be monotonously increasing over keyFrames. */
void KeyFrameInterpolator::addKeyFrame(const Frame& fr, const float time)
{
  if (keyFrame_.isEmpty())
    interpolationTime_ = time;
  
  if ( (!keyFrame_.isEmpty()) && (keyFrame_.getLast()->time() > time) )
    qWarning("Error in KeyFrameInterpolator::addKeyFrame : time is not monotone");
  else
    keyFrame_.append(new KeyFrame(fr, time));
  
  valuesAreValid_ = false;
  pathIsValid_ = false;
  currentFrameValid_ = false;
  resetInterpolation();
}

/*! Remove all keyFrames from the path. The numberOfKeyFrames() is set to 0. */
void KeyFrameInterpolator::deletePath()
{
  stopInterpolation();
  keyFrame_.clear();
  pathIsValid_ = false;
  valuesAreValid_ = false;
  currentFrameValid_ = false;
}

/*! Draws the path that will be used to interpolate the frame().

  \p mask controls what is drawn on the path : if (mask & 1) (default), the position path is drawn.
  If (mask & 2), a camera representation is regularly drawn and if (mask & 4), an oriented axis is
  regularly drawn.

  \code
  drawPath();  // Simply draws the interpolation path
  drawPath(3); // Draws path and cameras
  drawPath(7); // Draws path, cameras and axis
  drawPath(5); // Draws path and axis
  \endcode
 
  When camera or axis is drawn, \p nbFrames controls the number of objects (axis or camera)
  drawn between two successive keyFrames. When \p nbFrames=1, only the path Key Frames are
  drawn. \p nbFrames=2 also draws the intermediate orientation, etc. The maximum value is 30. \p
  nbFrames should divide 30 so that an object is drawn for each Key Frame. Default value is 6.
 
  \p scale (default=1.0) controls the scaling of the camera and axis drawing. A value of
  QGLViewer::sceneRadius() should give good results.

  The color of the path is the one of the current \p glColor(). 

  See the <a href="../examples/keyFrames.html">keyFrames</a> example for an illustration.

  This function actually call drawPathModifyGLState(), but saves and restores the GL state before
  and after. */
void KeyFrameInterpolator::drawPath(const int mask, int nbFrames, const float scale)
{
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  drawPathModifyGLState(mask, nbFrames, scale);
  glPopAttrib();
}

/*! Same as drawPath(), but the GL state is modified : GL_LIGHTING is disabled and line width set to
  2. This function should only be used for efficiency reasons (as is done by QGLViewer::postDraw()).
  Prefer calling drawPath(), which preserves the GL state, for debugging purpose. */
void KeyFrameInterpolator::drawPathModifyGLState(const int mask, int nbFrames, const float scale)
{
  const int nbSteps = 30;
  if (!pathIsValid_)
    {
      path_.clear();
      path_.reserve(nbSteps*keyFrame_.count());
      
      if (keyFrame_.isEmpty())
	return;

      if (!valuesAreValid_)
	updateModifiedFrameValues();

      if (keyFrame_.getFirst() == keyFrame_.getLast())
	path_.push_back(Frame(keyFrame_.getFirst()->position(), keyFrame_.getFirst()->orientation()));
      else
	{
	  static Frame fr;
	  KeyFrame* kf_[4];
	  kf_[0] = keyFrame_.first();
	  kf_[1] = kf_[0];
	  kf_[2] = keyFrame_.next();
	  kf_[3] = keyFrame_.next();
	  bool exit = false;
	  while (kf_[2])
	    {
	      if (!kf_[3])
		{
		  exit = true;
		  kf_[3] = kf_[2];
		}
	      
	      Vec diff = kf_[2]->position() - kf_[1]->position();
	      Vec v1 = 3.0 * diff - 2.0 * kf_[1]->tgP() - kf_[2]->tgP();
	      Vec v2 = -2.0 * diff + kf_[1]->tgP() + kf_[2]->tgP();

	      // cout << kf_[0]->time() << " , " << kf_[1]->time() << " , " << kf_[2]->time() << " , " << kf_[3]->time() << endl;
	      for (int step=0; step<nbSteps; ++step)
		{
		  float alpha = step / static_cast<float>(nbSteps);
		  fr.setPosition(kf_[1]->position() + alpha * (kf_[1]->tgP() + alpha * (v1+alpha*v2)));
		  fr.setOrientation(Quaternion::squad(kf_[1]->orientation(), kf_[1]->tgQ(), kf_[2]->tgQ(), kf_[2]->orientation(), alpha));
		  path_.push_back(fr);
		}

	      if (exit)
		break;
	      
	      // Shift	  
	      kf_[0] = kf_[1];
	      kf_[1] = kf_[2];
	      kf_[2] = kf_[3];
	      kf_[3] = keyFrame_.next();
	    }
	  // Add last KeyFrame
	  path_.push_back(Frame(kf_[2]->position(), kf_[2]->orientation()));
	}
      pathIsValid_ = true;
    }

  if (mask)
    {
      glDisable(GL_LIGHTING);
      glLineWidth(2);

      if (mask & 1)
	{
	  glBegin(GL_LINE_STRIP);
	  for (QValueVector<Frame>::const_iterator pnt=path_.begin(), end=path_.end(); pnt!=end; ++pnt)
	    glVertex3fv((*pnt).position().address());
	  glEnd();
	}
      if (mask & 6)
	{
	  int count = 0;
	  if (nbFrames > nbSteps)
	    nbFrames = nbSteps;
	  float goal = 0.0f;
	  for (QValueVector<Frame>::const_iterator pnt=path_.begin(), end=path_.end(); pnt!=end; ++pnt)
	    if ((count++) >= goal)
	      {
		goal += nbSteps / static_cast<float>(nbFrames);
		glPushMatrix();
		glMultMatrixd((*pnt).matrix());
		const float scaling = scale / 10.0;
		glScalef(scaling, scaling, scaling);
		// Tricky : QGLViewer creates its display lists BEFORE the user, in a fresh
		// GL context. Their numbering is hence fixed. 3 corresponds to the cameraDL.
		// Any viewer calling this function will hence have its own display list used !!
		if (mask & 2) glCallList(3);
		if (mask & 4) glCallList(1);
		glPopMatrix();
	      }
	}
    }
}

void KeyFrameInterpolator::updateModifiedFrameValues()
{
  Quaternion prevQ = keyFrame_.getFirst()->orientation();
  KeyFrame* kf;
  for (kf = keyFrame_.first(); kf; kf=keyFrame_.next())
    {
      if (kf->frame())
	kf->updateValuesFromPointer();
      kf->flipOrientation(prevQ);
      prevQ = kf->orientation();      
    }

  KeyFrame* prev = keyFrame_.getFirst();
  kf = keyFrame_.first();
  while (kf)
    {
      KeyFrame* next = keyFrame_.next();
      if (next)
	kf->computeTangent(prev, next);
      else
	kf->computeTangent(prev, kf);
      prev = kf;
      kf = next;
    }
  valuesAreValid_ = true;
}

/*! Returns the keyFrame position of keyFrame number \p i. No index verification is performed. See
  also keyFrameOrientation(), keyFrameTime() and numberOfKeyFrames(). */
Vec KeyFrameInterpolator::keyFramePosition(const int i) const
{
  return keyFrame_.at(i)->position();
}

/*! Returns the keyFrame orientation of keyFrame number \p i. No index verification is performed.
See also keyFramePosition(), keyFrameTime() and numberOfKeyFrames(). */
Quaternion KeyFrameInterpolator::keyFrameOrientation(const int i) const
{
  return keyFrame_.at(i)->orientation();
}

Frame KeyFrameInterpolator::keyFrame(const int i) const
{
  Frame fr(keyFrame_.at(i)->position(), keyFrame_.at(i)->orientation());
  return fr;
}

/*! Returns the time associated with the keyframe number \p i. See also keyFramePosition(),
  keyFrameOrientation() and addKeyFrame(). */
float KeyFrameInterpolator::keyFrameTime(const int i) const { return keyFrame_.at(i)->time(); };

void KeyFrameInterpolator::updateCurrentKeyFrameForTime(const float time)
{
  // Assertion : times are sorted in monotone order.
  // Assertion : keyFrame_ is not empty

  // TODO : Special case for loops when closed is implemented !!
  if (!currentFrameValid_)
    // Recompute everything from scrach
    currentFrame_[1]->toFirst();

  while (currentFrame_[1]->current()->time() > time)
    {
      currentFrameValid_ = false;
      if (currentFrame_[1]->atFirst())
	break;
      --(*currentFrame_[1]);
    }

  if (!currentFrameValid_)
    *currentFrame_[2] = *currentFrame_[1];

  while (currentFrame_[2]->current()->time() < time)
    {
      currentFrameValid_ = false;
      if (currentFrame_[2]->atLast())
	break;
      ++(*currentFrame_[2]);
    }

  if (!currentFrameValid_)
    {
      *currentFrame_[1] = *currentFrame_[2];
      if ((!currentFrame_[1]->atFirst()) && (time < currentFrame_[2]->current()->time()))
	--(*currentFrame_[1]);
	
      *currentFrame_[0] = *currentFrame_[1];
      if (!currentFrame_[0]->atFirst())
	--(*currentFrame_[0]);
      
      *currentFrame_[3] = *currentFrame_[2];
      if (!currentFrame_[3]->atLast())
	++(*currentFrame_[3]);

      currentFrameValid_ = true;
      splineCacheIsValid_ = false;
    }
  
  // cout << "Time = " << time << " : " << currentFrame_[0]->current()->time() << " , " <<
  // currentFrame_[1]->current()->time() << " , " << currentFrame_[2]->current()->time() << " , " <<  currentFrame_[3]->current()->time() << endl;
}

void KeyFrameInterpolator::updateSplineCache()
{
  Vec delta = currentFrame_[2]->current()->position() - currentFrame_[1]->current()->position();
  v1 = 3.0 * delta - 2.0 * currentFrame_[1]->current()->tgP() - currentFrame_[2]->current()->tgP();
  v2 = -2.0 * delta + currentFrame_[1]->current()->tgP() + currentFrame_[2]->current()->tgP();
  splineCacheIsValid_ = true;
}

/*! Interpolate frame() for time \p time. interpolationTime() is set to \p time and frame() is set
  accordingly.

  If you simply want to change interpolationTime() but not the frame(), use setInterpolationTime()
  instead.

  Emits the interpolated() signal. */
void KeyFrameInterpolator::interpolateAtTime(const float time)
{
  setInterpolationTime(time);
  
  if ((keyFrame_.isEmpty()) || (!frame_))
    return;

  if (!valuesAreValid_)
    updateModifiedFrameValues();

  updateCurrentKeyFrameForTime(time);

  if (!splineCacheIsValid_)
    updateSplineCache();

  float alpha;
  float dt = currentFrame_[2]->current()->time() - currentFrame_[1]->current()->time();
  if (dt == 0.0)
    alpha = 0.0;
  else
    alpha = (time - currentFrame_[1]->current()->time()) / dt;

  // Linear interpolation - debug
  // Vec pos = alpha*(currentFrame_[2]->current()->position()) + (1.0-alpha)*(currentFrame_[1]->current()->position());
  Vec pos = currentFrame_[1]->current()->position() + alpha * (currentFrame_[1]->current()->tgP() + alpha * (v1+alpha*v2));
  Quaternion q = Quaternion::squad(currentFrame_[1]->current()->orientation(), currentFrame_[1]->current()->tgQ(),
				   currentFrame_[2]->current()->tgQ(), currentFrame_[2]->current()->orientation(), alpha);
  frame_->setPositionAndOrientationWithConstraint(pos, q);

  emit interpolated();
}
