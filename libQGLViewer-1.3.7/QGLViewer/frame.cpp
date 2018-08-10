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

#include "frame.h"
#include <math.h>

using namespace qglviewer;
using namespace std;


/*! Creates a default frame. Positioned in (0,0,0), with an identity rotation (0,0,0,1). The
  referenceFrame() is set to \c NULL (meaning world coordinate system). No attached constraint. */
Frame::Frame()
  : constraint_(NULL), referenceFrame_(NULL)
{}

/*! Creates an initialized frame, with a position and an orientation. The
  reference frame is set to NULL (meaning world coordinate system). */
Frame::Frame(const Vec& pos, const Quaternion& orien)
  : t_(pos), q_(orien), constraint_(NULL), referenceFrame_(NULL)
{}

/*! operator= : referenceFrame() and constraint() pointers are copied. */
Frame& Frame::operator=(const Frame& f)
{
  setTranslation(f.translation());
  setRotation(f.rotation());
  setConstraint(f.constraint());
  setReferenceFrame(f.referenceFrame());
  return *this;
}

/*! Copy constructor. translation(), rotation(), constraint() and referenceFrame() are copied. */
Frame::Frame(const Frame& f)
  : QObject(), t_(f.translation()), q_(f.rotation()), constraint_(f.constraint()), referenceFrame_(f.referenceFrame()) 
{}

/////////////////////////////// MATRICES //////////////////////////////////////

/*! Returns the current 4x4 frame matrix. Can be used with \p glMultMatrixd(fr.matrix()) or \p
  glLoadMatrixd(fr.matrix()). This matrix only represents the \e local transformation (see
  referenceFrame() for frame composition). Use getWorldMatrix() or worldMatrix() to have the full
  frame transformation matrix (i.e. from the world coordinate system).

  worldMatrix() and matrix() will return identical results when the frame is not composed
  (referenceFrame() == NULL). See also getMatrix().

  \attention The matrix is given in OpenGL format (row-major order) and is the transpose of the
  actual mathematical European representation. See the difference between Quaternion::getMatrix()
  and Quaternion::getRotationMatrix().

  \attention The result is only valid until the next call to matrix(), getMatrix(), worldMatrix()
  or getWorldMatrix(). Use it immediately (as in \c glLoadMatrixd(fr.matrix()) or \c glLoadMatrixd(fr.matrix())) or
  store it in an other variable. Consider using getMatrix() if needed.

  \note The scaling factor of the 4x4 matrix is set to 1.0. */
const GLdouble* Frame::matrix() const
{
  static GLdouble m[4][4];
  getMatrix(m);
  return (const GLdouble*)(m);
}

/*! double[4][4] parameter version of matrix(). See also getWorldMatrix() and worldMatrix(). This
function is very similar to Quaternion::getMatrix(), it simply includes the Frame translation in the
last line.
  
\note The scaling factor of the 4x4 matrix is set to 1.0. */
void Frame::getMatrix(GLdouble m[4][4]) const
{
  q_.getMatrix(m);

  m[3][0] = t_[0];
  m[3][1] = t_[1];
  m[3][2] = t_[2];
}

/*! double[16] parameter version of matrix(). See also getWorldMatrix() and worldMatrix(). This
function is very similar to Quaternion::getMatrix(), it simply includes the Frame translation in the
last line. */
void Frame::getMatrix(GLdouble m[16]) const
{
  q_.getMatrix(m);

  m[12] = t_[0];
  m[13] = t_[1];
  m[14] = t_[2];
}

Frame Frame::inverse() const
{
  Frame fr(-(q_.inverseRotate(t_)), q_.inverse());
  fr.setReferenceFrame(referenceFrame());
  return fr;
}

void Frame::worldInvert()
{
  t_=-(orientation().inverseRotate(position()));
  q_=orientation().inverse();
  setReferenceFrame(NULL);
  emit modified();
}

/*! Returns the current 4x4 frame \e inverse matrix. This matrix only represents the \e local \e
  inverse transformation (see referenceFrame() for frame composition). Use getWorldInverseMatrix()
  or worldInverseMatrix() to have the full frame inverse transformation matrix (i.e. from the world
  coordinate system).

  worldInverseMatrix() and inverseMatrix() will return identical results when the frame is not composed
  (referenceFrame() == NULL). See also getInverseMatrix().

  \attention The matrix is given in OpenGL format (row-major order) and is the transpose of the
  actual mathematical European representation. See the difference between Quaternion::getMatrix()
  and Quaternion::getRotationMatrix().

  \attention The result is only valid until the next call to inverseMatrix(), getInverseMatrix(),
  worldInverseMatrix() or getWorldInverseMatrix(). Use it immediately or store it in an other
  variable. Consider using getInverseMatrix() in that case.

  \note The scaling factor of the 4x4 matrix is set to 1.0. */
const GLdouble* Frame::inverseMatrix() const
{
  static GLdouble m[4][4];
  getInverseMatrix(m);
  return (const GLdouble*)(m);
}

/*! double[4][4] parameter version of inverseMatrix(). See also getWorldInverseMatrix() and
worldInverseMatrix(). This function is very similar to Quaternion::getInverseMatrix(), it simply
includes the negated inverse rotated Frame translation in the last line.
  
\note The scaling factor of the 4x4 matrix is set to 1.0. */
void Frame::getInverseMatrix(GLdouble m[4][4]) const
{
  inverse().getMatrix(m);
}

/*! double[16] parameter version of inverseMatrix(). See also getWorldInverseMatrix() and
worldInverseMatrix(). This function is very similar to Quaternion::getInverseMatrix(), it simply
includes the negated inverse rotated Frame translation in the last line. */
void Frame::getInverseMatrix(GLdouble m[16]) const
{
  inverse().getMatrix(m);
}


/*! Returns the 4x4 frame matrix, defined in the world coordinate system. Can be used with \p
  glMultMatrixd(fr.worldMatrix()) or \p glLoadMatrixd(fr.worldMatrix()). This matrix represents the
  \e global transformation from the world coordinate system to the frame coordinate system,
  including the entire frame composition chain (see referenceFrame() for frame composition). Use
  getMatrix() or matrix() to have the \e local frame transformation matrix (i.e. the translation()
  and rotation() part). See also worldInverseMatrix().

  worldMatrix() and matrix() will return identical results when the frame is not composed
  (referenceFrame() == NULL). See also getWorldMatrix() and getWorldInverseMatrix().

  \attention The matrix is given in OpenGL format (row-major order) and is the transpose of the
  actual mathematical European representation.

  \attention The result is only valid until the next call to matrix(), getMatrix(), worldMatrix()
  or getWorldMatrix(). Use it immediately (as in \c glLoadMatrixd(fr.worldMatrix()) or \c glLoadMatrixd(fr.worldMatrix())) or
  store it in an other variable. Consider using getWorldMatrix() in that case. */
const GLdouble* Frame::worldMatrix() const
{
  static Frame fr;
  fr.setTranslation(position());
  fr.setRotation(orientation());
  return fr.matrix();
}

/*! float[4][4] parameter version of worldMatrix(). See also getMatrix() and matrix(). */
void Frame::getWorldMatrix(GLdouble m[4][4]) const
{
  const GLdouble* mat = worldMatrix();
  for (int i=0; i<4; ++i)
    for (int j=0; j<4; ++j)
      m[i][j] = mat[i*4+j];
}

/*! Returns the 4x4 frame \e inverse matrix, defined in the world coordinate system. This matrix is
  simply the inverse of worldMatrix(). worldInverseMatrix() and inverseMatrix() are actually
  identical when the Frame has no (i.e. \c NULL) referenceFrame().

  \attention The matrix is given in OpenGL format (row-major order) and is the transpose of the
  actual mathematical European representation.

  \attention The result is only valid until the next call to inverseMatrix() or
  getWorldInverseMatrix(). Use it immediately or store it in an other variable. Consider using
  getWorldInverseMatrix() in that case. */
const GLdouble* Frame::worldInverseMatrix() const
{
  return worldInverse().matrix();
}

/*! float[4][4] parameter version of worldInverseMatrix(). See also getInverseMatrix() and inverseMatrix(). */
void Frame::getWorldInverseMatrix(GLdouble m[4][4]) const
{
  worldInverse().getMatrix(m);
}

/*! float[16] parameter version of worldInverseMatrix(). See also getInverseMatrix() and inverseMatrix(). */
void Frame::getWorldInverseMatrix(GLdouble m[16]) const
{
  worldInverse().getMatrix(m);
}

/*! Set the frame state from a matrix representation. Matrix has to be a proper row-major order
transformation representation (rotation is in the upper left 3x3 matrix, while translation is on the
last line). matrix() returns the current matrix value.

\attention A Frame does \e not handle a scale factor. The possible scaling in \p m will be ignored
by this method. */
void Frame::setFromMatrix(const float m[4][4])
{
  if ( fabs(m[3][3]) < 1E-8)
    {
      qWarning("Frame::setFromMatrix : Null homogeneous coefficient");
      return;
    }

  float rot[3][3];
  for (int i=0; i<3; ++i)
    {
      t_[i] = m[3][i] / m[3][3];
      for (int j=0; j<3; ++j)
	rot[i][j] = m[i][j] / m[3][3];
    }
  q_.setFromRotationMatrix(rot);
  emit modified();
}


//////////////////// SET AND GET LOCAL TRANSLATION AND ROTATION ///////////////////////////////


/*! Set the current translation of the frame. Same as setTranslation(), but with \p float parameters.
 translation() returns the current frame position. */
void Frame::setTranslation(const float x, const float y, const float z)
{
  setTranslation(Vec(x, y, z));
}

/*! Get the current local translation of the frame (same as translation()). See also setTranslation().*/
void Frame::getTranslation(float& x, float& y, float& z) const
{
  const Vec t = translation();
  x = t[0];
  y = t[1];
  z = t[2];
}

/*! Set the current rotation of the frame.
  Parameters are the rotation Quaternion float values.
  Get current rotation with rotation(). */
void Frame::setRotation(const float x, const float y, const float z, const float a)
{
  setRotation(Quaternion(x, y, z, a));
}

/*! Get the current rotation of the frame (same as rotation()).
  Parameters are the rotation Quaternion values.
  See also setRotation() and setRotationAxisAngle(). */
void Frame::getRotation(float& x, float& y, float& z, float& a) const
{
  const Quaternion q = rotation();
  x = q[0];
  y = q[1];
  z = q[2];
  a = q[3];
}

/*! Set the current rotation of the frame.
  Parameters are the rotation axis vector and its angle (in radians). */
void Frame::setRotationAxisAngle(const float x, const float y, const float z, const float a)
{
  setRotation(Quaternion(Vec(x, y, z), a));
}

/*! Same as translate() but with a float[3] parameter.
  \p t can be modified to fit translation constraint(). */
void Frame::translate(float t[3])
{
  Vec T(t);
  translate(T);
  for (int i=0; i<3; ++i)
    t[i] = T[i];
}


/*! Same as translate() but with const float parameter. The actual translation may differ from the
  given parameters in order to satisfy the constraint(). Use the non-const version to get the
  filtered values back. */
void Frame::translate(const float x, const float y, const float z)
{
  Vec t(x,y,z);
  translate(t);
}

/*! Same as translate() but with float parameters. Parameters are modified to satisfy translation
  constraints (see constraint()). See also the non-const parameters version of this version, if you
  are not interested in the filtered values. */
void Frame::translate(float& x, float& y, float& z)
{
  Vec t(x,y,z);
  translate(t);
  x = t[0];
  y = t[1];
  z = t[2];
}

/*! Translate the frame of \p t. The actual applied translation may differ from \p t as the
  constraint will filter \p t (see constraint()). Use the non-const version of translate() to
  get back the filtered translation value. */
void Frame::translate(const Vec& t)
{
  Vec tbis = t;
  translate(tbis);
}

/*! Translate the frame of \p t. \p t may be modified to satisfy translation constraint().
  Use setConstraint() to (un)set the translation constraints. Emits the modified() signal. */
void Frame::translate(Vec& t)
{
  if (constraint())
    constraint()->constrainTranslation(t, this);
  t_ += t;
  emit modified();
}


/*! Same as rotate(), but parameter is given as a float[4].
  Quaternion \p q may be modified to satisfy rotation constraint(). */ 
void Frame::rotate(float q[4])
{
  Quaternion Q(q[0], q[1], q[2], q[3]);
  rotate(Q);
  for (unsigned short i=0; i<3; ++i)
    q[i] = Q[i];
}

/*! Same as rotate(), but with float parameters (Quaternion values).
  Parameters may be modified to satisfy rotation constraint(). See also the const parameter version of this function. */ 
void Frame::rotate(float& x, float& y, float& z, float& a)
{
  Quaternion q(x,y,z,a);
  rotate(q);
  x = q[0];
  y = q[1];
  z = q[2];
  a = q[3];
}

/*! Same as rotate(), but with float parameters (Quaternion values). Actual rotation may differ from
  these values in order to satisfy the rotation constraint(). Use the non-const parameter version of
  this function to get the filtered values back. */
void Frame::rotate(const float x, const float y, const float z, const float a)
{
  Quaternion q(x,y,z,a);
  rotate(q);
}

/*! Compose current frame rotation with \p q (R = R*q). The actual rotation may differ from \p q in
  order to satisfy the rotation constraint(). Consider using the non-const parameter version of this
  function to get the filtered values back. */
void Frame::rotate(const Quaternion& q)
{
  Quaternion qbis = q;
  rotate(qbis);
}

/*! Compose current frame rotation with \p q (R = R*q). \p q may be modified to satisfy rotation
  constraint(). Use setConstraint() to (un)set rotational constraints. Emits the modified() signal. */ 
void Frame::rotate(Quaternion& q)
{
  if (constraint())
    constraint()->constrainRotation(q, this);
  q_ *= q;
  q_.normalize(); // Prevents numerical drift
  emit modified();
}

/*! Same as rotate(), but position() is modified as if the Frame was rotated of \p q around the point
  \p p. Emits the modified() signal

  If the frame is constrained (see setConstraint()), \p q is first constrained using
  Constraint::constrainRotation(). The translation which results from the filtered rotation around
  \p is then computed and filtered using Constraint::constrainTranslation(). */
void Frame::rotateAroundPoint(Quaternion& q, const Vec& p)
{
  if (constraint())
    constraint()->constrainRotation(q, this);
  q_ *= q;
  q_.normalize(); // Prevents numerical drift
  Vec trans = p + Quaternion(inverseTransformOf(q.axis()), q.angle()).rotate(position()-p) - t_;
  if (constraint())
    constraint()->constrainTranslation(trans, this);
  t_ += trans;
  emit modified();
}

/*! Same as rotateAroundPoint(), but the rotation Quaternion is \p const. Note however that the actual
  rotation may differ according to local constraints. */
void Frame::rotateAroundPoint(const Quaternion& q, const Vec& p)
{
  Quaternion qbis = q;
  rotateAroundPoint(qbis, p);
}


//////////////////// SET AND GET WORLD POSITION AND ORIENTATION ///////////////////////////////


/*! Same as setPosition(), but with \p float parameters. */
void Frame::setPosition(const float x, const float y, const float z)
{
  setPosition(Vec(x, y, z));
}

/*! Set the position of the origin of the frame, with respect to the world coordinate system. Use
setTranslation() to defined to local frame translation (with respect to the reference frame). See
also position(), orientation() and setPositionWithConstraint(). */
void Frame::setPosition(const Vec& t)
{
  if (referenceFrame())
    setTranslation(referenceFrame()->coordinatesOf(t));
  else
    setTranslation(t);
}

/*! Same as successive calls to setPosition() and then setOrientation().

Only one modified() signal is emitted, which is convenient if this signal is connected to a viewer
updateGL() slot. See also setTranslationAndRotation() and
setPositionAndOrientationWithConstraint(). */
void Frame::setPositionAndOrientation(const Vec& p, const Quaternion& q)
{
  if (referenceFrame())
    {
      t_ = referenceFrame()->coordinatesOf(p);
      q_ = referenceFrame()->orientation().inverse() * q;
    }
  else
    {
      t_ = p;
      q_ = q;
    }
  emit modified();
}


/*! Same as successive calls to setPosition() and then setOrientation().

Only one modified() signal is emitted, which is convenient if this signal is connected to a viewer
updateGL() slot. See also setPositionAndOrientation() and
setTranslationAndRotationWithConstraint(). */
void Frame::setTranslationAndRotation(const Vec& t, const Quaternion& q)
{
  t_ = t;
  q_ = q;
  emit modified();
}


/*! Get the current position of the frame (same as position()). See also setPosition().*/
void Frame::getPosition(float& x, float& y, float& z) const
{
  Vec p = position();
  x = p.x;
  y = p.y;
  z = p.z;
}

/*! Same as setOrientation(), but with float parameters. */
void Frame::setOrientation(const float x, const float y, const float z, const float a)
{
  setOrientation(Quaternion(x, y, z, a));
}

/*! Set the current orientation of the frame (with respect to the world coordinate system). See
  orientation() and setOrientationWithConstraint(). */
void Frame::setOrientation(const Quaternion& q)
{
  if (referenceFrame())
    setRotation(referenceFrame()->orientation().inverse() * q);
  else
    setRotation(q);
}

/*! Get the current orientation of the frame (same as orientation()).
  Parameters are the orientation Quaternion values.
  See also setOrientation() and setOrientationAxisAngle(). */
void Frame::getOrientation(float& q0, float& q1, float& q2, float& q3) const
{
  Quaternion o = orientation();
  q0 = o[0];
  q1 = o[1];
  q2 = o[2];
  q3 = o[3];
}

/*! Returns the current frame orientation (defined with respect to the world coordinate system). See setOrientation(). */
Quaternion Frame::orientation() const
{
  Quaternion res = rotation();
  Frame* fr  = referenceFrame();
  while (fr != NULL)
    {
      res = fr->rotation() * res;
      fr  = fr->referenceFrame();
    }
  return res;
}

/*! Set the current orientation of the frame.
  Parameters are the rotation axis vector and its angle (in radians). */
void Frame::setOrientationAxisAngle(const float x, const float y, const float z, const float a)
{
  setOrientation(Quaternion(Vec(x, y, z), a));
}


////////////////////// C o n s t r a i n t   V e r s i o n s  //////////////////////////

/*! Same as setTranslation(), but the possible constraint() of the Frame is enforced. \p t is
modified to satisfy the constraint. Emits the modified() signal. */
void Frame::setTranslationWithConstraint(Vec& t)
{
  Vec deltaT = t - translation();
  if (constraint())
    constraint()->constrainTranslation(deltaT, this);

  setTranslation(translation() + deltaT);
  t = translation();
}

/*! Same as setRotation(), but the possible constraint() of the Frame is enforced. \p q is
modified to satisfy the constraint. Emits the modified() signal. */
void Frame::setRotationWithConstraint(Quaternion& q)
{
  Quaternion deltaQ = rotation().inverse() * q;
  if (constraint())
    constraint()->constrainRotation(deltaQ, this);

  // Prevent numerical drift
  deltaQ.normalize();

  setRotation(rotation() * deltaQ);
  q_.normalize();
  q = rotation();
}

/*! Same as setTranslationAndRotation(), but the possible constraint() of the Frame is enforced.
\p t and \p q are modified to satisfy the constraint. Emits the modified() signal. */
void Frame::setTranslationAndRotationWithConstraint(Vec& t, Quaternion& q)
{
  Vec deltaT = t - translation();
  Quaternion deltaQ = rotation().inverse() * q;
  
  if (constraint())
    {
      constraint()->constrainTranslation(deltaT, this);
      constraint()->constrainRotation(deltaQ, this);
    }

  // Prevent numerical drift
  deltaQ.normalize();
  
  t_ += deltaT;
  q_ *= deltaQ;
  q_.normalize();
  
  t = translation();
  q = rotation();
  
  emit modified();
}

/*! Same as setPosition(), but the possible constraint() of the Frame is enforced. \p p is
modified to satisfy the constraint. Emits the modified() signal. */
void Frame::setPositionWithConstraint(Vec& p)
{
  if (referenceFrame())
    p = referenceFrame()->coordinatesOf(p);

  setTranslationWithConstraint(p);
}

/*! Same as setOrientation(), but the possible constraint() of the Frame is enforced. \p q is
modified to satisfy the constraint. Emits the modified() signal. */
void Frame::setOrientationWithConstraint(Quaternion& q)
{
  if (referenceFrame())
    q = referenceFrame()->orientation().inverse() * q;

  setRotationWithConstraint(q);
}

/*! Same as setPositionAndOrientation() but the position and orientation increments are filtered by
the possible constraint(). \p p and \p q are modified to satisfy the constraint. Emits the modified() signal. */
void Frame::setPositionAndOrientationWithConstraint(Vec& p, Quaternion& q)
{
  if (referenceFrame())
    {
      p = referenceFrame()->coordinatesOf(p);
      q = referenceFrame()->orientation().inverse() * q;
    }
  setTranslationAndRotationWithConstraint(p, q);
}


///////////////////////////// REFERENCE FRAMES ///////////////////////////////////////

/*! Set the current reference frame. The frame then becomes a "child" of the referenceFrame(),
  meaning that its position and orientation are defined with respect to the referenceFrame(). */
void Frame::setReferenceFrame(Frame* const fr)
{
  if (settingAsReferenceFrameWillCreateALoop(fr))
    qWarning("Frame::setReferenceFrame : referenceFrame creates a loop in frame hierarchy");
  
  referenceFrame_ = fr;
};

/*! Returns \p true if setting \p fr as the reference frame would create a loop in the frame hierarchy. */
bool Frame::settingAsReferenceFrameWillCreateALoop(Frame* const fr)
{
  Frame* f = fr;
  while (f != NULL)
    {
      if (f == this)
	return true;
      f = f->referenceFrame();
    }
  return false;
}

///////////////////////// FRAME TRANSFORMATIONS OF 3D POINTS //////////////////////////////

/*! This returns the \e frame coordinates of a point \p src defined in the \e world coordinate
  system (converts from world to frame).
 
  If \p src is actually a vector, use the vector equivalent function transformOf() where only the
  rotational part of the transformation is taken into account.
 
  inverseCoordinatesOf() performs the inverse transformation.

  See the <a href="../examples/frameTransform.html">frameTransform</a> example for an illustration. */
Vec Frame::coordinatesOf(const Vec& src) const
{
  if (referenceFrame())
    return localCoordinatesOf(referenceFrame()->coordinatesOf(src));
  else
    return localCoordinatesOf(src);
}

/*! This returns the \e world coordinates of the point whose position in the \e frame coordinate
  system is \p src (converts from frame to world).

  If \p src is actually a vector, use the vector equivalent function inverseTransformOf() where only the
  rotational part of the transformation is taken into account.
 
  coordinatesOf() performs the inverse transformation.

  See the <a href="../examples/frameTransform.html">frameTransform</a> example for an illustration. */
Vec Frame::inverseCoordinatesOf(const Vec& src) const
{
  Frame* fr  = const_cast<Frame*>(this);
  Vec    res = src;
  while (fr != NULL)
    {
      res = fr->localInverseCoordinatesOf(res);
      fr  = fr->referenceFrame();
    }
  return res;
}

/*! Returns the \e frame coordinates of a point \p src defined in the reference frame (default is
  the world coordinates system, see referenceFrame()) (converts from reference frame to frame
  coordinates).

  If \p src is actually a vector, use the vector equivalent function localTransformOf() where only the
  rotational part of the transformation is taken into account.
  
  localInverseCoordinatesOf() performs the inverse transformation. */
Vec Frame::localCoordinatesOf(const Vec& src) const
{
  return rotation().inverseRotate(src - translation());
}

/*! Returns the \e reference frame coordinates (default is the world coordinates system, see
 referenceFrame()) of a point \p src defined in the \e frame coordinate system (converts from
 frame to reference frame coordinates).

 If \p src is actually a vector, use the vector equivalent function localInverseTransformOf() where
 only the rotational part of the transformation is taken into account.
 
 localCoordinatesOf() performs the inverse transformation. */
Vec Frame::localInverseCoordinatesOf(const Vec& src) const
{
  return rotation().rotate(src) + translation();
}

/*! This returns the \e frame coordinate system coordinates of the point whose position in the \p from
  coordinate system is \p src (converts from \p from to \e frame). \p from and the frame do not need to
  be located in the same branch of the frame tree hierarchy.

  If \p src is actually a vector, use the vector equivalent function transformOfFrom() where only the
  rotational part of the transformation is taken into account.
 
  coordinatesOfIn() performs the inverse transformation. */
Vec Frame::coordinatesOfFrom(const Vec& src, const Frame* from) const
{
  if (this == from)
    return src;
  else
    if (referenceFrame())
      return localCoordinatesOf(referenceFrame()->coordinatesOfFrom(src, from));
    else
      return localCoordinatesOf(from->inverseCoordinatesOf(src));
}

/*! This returns the \p in coordinate system coordinates of the point whose position in the \e frame
 coordinate system is \p src (converts from frame to \p in). \p in and the frame do not need to be
 located in the same branch of the frame tree hierarchy.

 If \p src is actually a vector, use the vector equivalent function transformOfIn() where only the
 rotational part of the transformation is taken into account.
 
 coordinatesOfFrom() performs the inverse transformation. */
Vec Frame::coordinatesOfIn(const Vec& src, const Frame* in) const
{
  Frame* fr  = const_cast<Frame*>(this);
  Vec    res = src;
  while ((fr != NULL) && (fr != in))
    {
      res = fr->localInverseCoordinatesOf(res);
      fr  = fr->referenceFrame();
    }

  if (fr != in)
    // in was not found in the branch of this, res is now expressed in the world
    // coordinate system. Simply convert to in coordinate system.
    res = in->coordinatesOf(res);

  return res;
} 
    
////// float[3] versions

/*! Same as coordinatesOf(), but with float parameters. */
void Frame::getCoordinatesOf(const float src[3], float res[3]) const
{
  Vec r = coordinatesOf(Vec(src));
  for (int i=0; i<3 ; ++i)
    res[i] = r[i];
}

/*! Same as inverseCoordinatesOf(), but with float parameters. */
void Frame::getInverseCoordinatesOf(const float src[3], float res[3]) const
{
  Vec r = inverseCoordinatesOf(Vec(src));
  for (int i=0; i<3 ; ++i)
    res[i] = r[i];
}

/*! Same as localCoordinatesOf(), but with float parameters. */
void Frame::getLocalCoordinatesOf(const float src[3], float res[3]) const
{
  Vec r = localCoordinatesOf(Vec(src));
  for (int i=0; i<3 ; ++i)
    res[i] = r[i];
}

  /*! Same as localInverseCoordinatesOf(), but with float parameters. */
void Frame::getLocalInverseCoordinatesOf(const float src[3], float res[3]) const
{
  Vec r = localInverseCoordinatesOf(Vec(src));
  for (int i=0; i<3 ; ++i)
    res[i] = r[i];
}

/*! Same as coordinatesOfIn(), but with float parameters. */
void Frame::getCoordinatesOfIn(const float src[3], float res[3], const Frame* in) const
{
  Vec r = coordinatesOfIn(Vec(src), in);
  for (int i=0; i<3 ; ++i)
    res[i] = r[i];
}

/*! Same as coordinatesOfFrom(), but with float parameters. */
void Frame::getCoordinatesOfFrom(const float src[3], float res[3], const Frame* from) const
{
  Vec r = coordinatesOfFrom(Vec(src), from);
  for (int i=0; i<3 ; ++i)
    res[i] = r[i];
}


///////////////////////// FRAME TRANSFORMATIONS OF VECTORS //////////////////////////////

/*! This returns the \e frame transform of a vector \p src defined in the \e world coordinate
  system (converts from world to frame).

 For vectors, only the rotational part of the transformation is taken into account, see
 coordinatesOf() for the point equivalent function.
 
 inverseTransformOf() performs the inverse transformation. */
Vec Frame::transformOf(const Vec& src) const
{
  if (referenceFrame())
    return localTransformOf(referenceFrame()->transformOf(src));
  else
    return localTransformOf(src);
}

/*! This returns the \e world transform of the vector whose coordinates in the \e frame coordinate
 system is \p src (converts from frame to world).

 For vectors, only the rotational part of the transformation is taken into account, see
 inverseCoordinatesOf() for the point equivalent function.
 
 transformOf() performs the inverse transformation. */
Vec Frame::inverseTransformOf(const Vec& src) const
{
  Frame* fr  = const_cast<Frame*>(this);
  Vec    res = src;
  while (fr != NULL)
    {
      res = fr->localInverseTransformOf(res);
      fr  = fr->referenceFrame();
    }
  return res;
}

/*! Returns the \e frame transform of a vector \p src defined in the reference frame (default is
  the world coordinates system, see referenceFrame()) (converts from reference frame to frame).

  For vectors, only the rotational part of the transformation is taken into account, see
  localCoordinatesOf() for the point equivalent function.
 
  localInverseTransformOf() performs the inverse transformation. */
Vec Frame::localTransformOf(const Vec& src) const
{
  return rotation().inverseRotate(src);
}

/*! Returns the \e reference frame transform (default is the world coordinates system, see
  referenceFrame()) of a vector \p src defined in the \e frame coordinate system (converts from
  frame to reference frame).

  For vectors, only the rotational part of the transformation is taken into account, see
  localCoordinatesOf() for the point equivalent function.
 
  localTransformOf() performs the inverse transformation. */
Vec Frame::localInverseTransformOf(const Vec& src) const
{
  return rotation().rotate(src);
}

/*! This returns the \e frame coordinate system transform of the vector whose coordinates in the \p from
 coordinate system is \p src (converts from \p from to \e frame). \p from and the frame do not need to
 be located in the same branch of the frame tree hierarchy.

 For vectors, only the rotational part of the transformation is taken into account, see
 coordinatesOfFrom() for the point equivalent function.
 
 transformOfIn() performs the inverse transformation. */
Vec Frame::transformOfFrom(const Vec& src, const Frame* from) const
{
  if (this == from)
    return src;
  else
    if (referenceFrame())
      return localTransformOf(referenceFrame()->transformOfFrom(src, from));
    else
      return localTransformOf(from->inverseTransformOf(src));
}

/*! This returns the \p in coordinate system transform of the vector whose coordinates in the \e frame
  coordinate system is \p src (converts from frame to \p in). \p in and the frame do not need to be
  located in the same branch of the frame tree hierarchy.

  For vectors, only the rotational part of the transformation is taken into account, see
  coordinatesOfIn() for the point equivalent function.
 
  transformOfFrom() performs the inverse transformation. */
Vec Frame::transformOfIn(const Vec& src, const Frame* in) const
{
  Frame* fr  = const_cast<Frame*>(this);
  Vec    res = src;
  while ((fr != NULL) && (fr != in))
    {
      res = fr->localInverseTransformOf(res);
      fr  = fr->referenceFrame();
    }

  if (fr != in)
    // in was not found in the branch of this, res is now expressed in the world
    // coordinate system. Simply convert to in coordinate system.
    res = in->transformOf(res);

  return res;
}

/////////////////  float[3] versions  //////////////////////

/*! Same as transformOf(), but with float parameters. */
void Frame::getTransformOf(const float src[3], float res[3]) const
{
  Vec r = transformOf(Vec(src));
  for (int i=0; i<3 ; ++i)
    res[i] = r[i];
}

/*! Same as inverseTransformOf(), but with float parameters. */
void Frame::getInverseTransformOf(const float src[3], float res[3]) const
{
  Vec r = inverseTransformOf(Vec(src));
  for (int i=0; i<3 ; ++i)
    res[i] = r[i];
}

/*! Same as localTransformOf(), but with float parameters. */
void Frame::getLocalTransformOf(const float src[3], float res[3]) const
{
  Vec r = localTransformOf(Vec(src));
  for (int i=0; i<3 ; ++i)
    res[i] = r[i];
}

  /*! Same as localInverseTransformOf(), but with float parameters. */
void Frame::getLocalInverseTransformOf(const float src[3], float res[3]) const
{
  Vec r = localInverseTransformOf(Vec(src));
  for (int i=0; i<3 ; ++i)
    res[i] = r[i];
}

/*! Same as transformOfIn(), but with float parameters. */
void Frame::getTransformOfIn(const float src[3], float res[3], const Frame* in) const
{
  Vec r = transformOfIn(Vec(src), in);
  for (int i=0; i<3 ; ++i)
    res[i] = r[i];
}

/*! Same as transformOfFrom(), but with float parameters. */
void Frame::getTransformOfFrom(const float src[3], float res[3], const Frame* from) const
{
  Vec r = transformOfFrom(Vec(src), from);
  for (int i=0; i<3 ; ++i)
    res[i] = r[i];
}

////////////////////////////      STATE      //////////////////////////////

/*! Creates an XML QDomElement that represents the Frame. \p name is the name of the
 QDomElement tag. You need to provide the QDomDocument \p doc that will hold the resulting
 element. Typical usage would be:
 \code
 QDomDocument doc("myDocument");
 Frame sunFrame;
 // ...
 anyNode.addElement(sunFrame.domElement("sunFrame", doc));
 // ...
 \endcode
 Use initFromDOMElement() to restore the Frame state from the resulting domElement.

 See also Camera::domElement(), KeyFrameInterpolator::domElement()...

 \attention The constraint() and referenceFrame() are not (yet) saved in the domElement. */
QDomElement Frame::domElement(const QString& name, QDomDocument& doc) const
{
  // TODO : use translation and rotation instead when referenceFrame is coded...
  QDomElement de = doc.createElement(name);
  de.appendChild(position().domElement("position", doc));
  de.appendChild(orientation().domElement("orientation", doc));
  return de;
}

/*! Restore the Frame state from a QDomElement created by domElement(). See
  Vec::initFromDOMElement() and Quaternion::initFromDOMElement() for details.

  \attention The constraint() and referenceFrame() are not (yet) restored from the domElement. */
void Frame::initFromDOMElement(const QDomElement& de)
{
  // TODO : use translation and rotation instead when referenceFrame is coded...
  QDomElement child=de.firstChild().toElement();
  while(!child.isNull())
    {
      if (child.tagName() == "position")
	{
	  Vec pos;
	  pos.initFromDOMElement(child);
	  setPosition(pos);
	}
      if (child.tagName() == "orientation")
	{
	  Quaternion ori;
	  ori.initFromDOMElement(child);
	  setOrientation(ori);
	}

      child = child.nextSibling().toElement();
    }
}

/////////////////////////////////   ALIGN   /////////////////////////////////

/*! Align the Frame with an other Frame, so that two of their axis are parallel.

If the X, Y and Z axis of the Frame is almost parallel to any of the X, Y, or Z axis of \p fr, the
Frame is rotated so that these two axis actually become parallel.

If, after this first rotation, two other axis are also almost parallel, a second alignment is
performed. The two frames then have identical orientations, up to rotations of 90 degrees.

\p threshold measure how close two axis must be to be aligned. It is compared with the absolute
values of the dot product of the normalized axis.

When \p move is set to \p true, the frame position will also be affected by the alignment. The new
position is such that the \p fr's position() is identical to the previous one (as computed with
coordinatesOf()).

\p fr may be NULL and then represents the world coordinate system (same convention than for the
referenceFrame()).

ManipulatedFrame::mouseDoubleClickEvent() calls this function when the left mouse button is double
clicked. */
void Frame::alignWithFrame(const Frame* const fr, bool move, float threshold)
{
  Vec directions[2][3];
  for (int d=0; d<3; ++d)
    {
      Vec dir((d==0)? 1.0 : 0.0, (d==1)? 1.0 : 0.0, (d==2)? 1.0 : 0.0);
      if (fr)
	directions[0][d] = fr->inverseTransformOf(dir);
      else
	directions[0][d] = dir;
      directions[1][d] = inverseTransformOf(dir);
    }

  float maxProj = 0.0f;
  float proj;
  unsigned short index[2];
  for (int i=0; i<3; ++i)
    for (int j=0; j<3; ++j)
      if ( (proj=fabs(directions[0][i]*directions[1][j])) >= maxProj )
	{
	  index[0] = i;
	  index[1] = j;
	  maxProj  = proj;
	}

  Frame old;
  old=*this;
  
  float coef = directions[0][index[0]] * directions[1][index[1]];
  if (fabs(coef) >= threshold)
    {
      const Vec axis = cross(directions[0][index[0]], directions[1][index[1]]);
      float angle = asin(axis.norm());
      if (coef >= 0.0)
	angle = -angle;
      setOrientation(Quaternion(axis, angle) * orientation());

      // Try to align an other axis direction 
      unsigned short d = (index[1]+1) % 3;
      Vec dir((d==0)? 1.0 : 0.0, (d==1)? 1.0 : 0.0, (d==2)? 1.0 : 0.0);
      dir = inverseTransformOf(dir);

      float max = 0.0f;
      for (int i=0; i<3; ++i)
	{
	  float proj = fabs(directions[0][i]*dir);
	  if (proj > max)
	    {
	      index[0] = i;
	      max = proj;
	    }
	}
      
      if (max >= threshold)
	{
	  const Vec axis = cross(directions[0][index[0]], dir);
	  float angle = asin(axis.norm());
	  if (directions[0][index[0]] * dir >= 0.0)
	    angle = -angle;
	  setOrientation(Quaternion(axis, angle) * orientation());
	}
    }

  Vec center;
  if (fr)
    center = fr->position();

  if (move)
    setPosition(center - orientation().rotate(old.coordinatesOf(center)));
}

/*! Translates the frame so that its position is on the line defined by \p origin and \p axis. Simply
   uses an orthogonal projection. */
void Frame::projectOnLine(const Vec& origin, const Vec& dir)
{
  const Vec shift = origin - position();
  Vec proj = shift;
  proj.projectOnAxis(dir);
  translate(shift-proj);
}

/////////////////////////////////   DISPLAY   /////////////////////////////////


/*!
  Draws a visual representation of the frame constraints.
  Size is 1.0 and glScalef should be called before. */
/*
void Frame::drawConstraints() const
{
  //    if (displayFrame)
  //      {
  // glPushAttrib(GL_ALL_ATTRIB_BITS);
  // glPushMatrix();
  // glEnable(GL_BLEND);
  // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  // glCullFace(GL_BACK);
  // glEnable(GL_CULL_FACE);

  switch (action_)
    {
    case Frame::ROTATION:
      glPushMatrix();
      glLineWidth(3.0);
      switch (rotConstraint_)
	{
	case Frame::NONE:
	  // Draw circles around the 3 axis
	  glColor4f(0.0,0.0,1.0,1.0);
	  drawer_.drawCircle();
	  glRotatef(90.0,1.0,0.0,0.0);
	  glColor4f(0.0,1.0,0.0,1.0);
	  drawer_.drawCircle();
	  glRotatef(90.0,0.0,1.0,0.0);
	  glColor4f(1.0,0.0,0.0,1.0);
	  drawer_.drawCircle();
	  break;
	case Frame::WORLD_AXIS:
	  glColor3f(1.0,1.0,0.0);
	  glLineWidth(4.0);
	  glRotatef(acos(rotConstraintAxis_[2])*180.0/M_PI,
		    -rotConstraintAxis_[1],rotConstraintAxis_[0], 0.0);
	  drawer_.drawArrow();
	  break;
	}
      glPopMatrix();
      break;
    case Frame::ZOOM:
      break;
    case Frame::TRANSLATION:
      break;
    case Frame::NO_MOUSE_ACTION:
      break;
    }
  glPopMatrix();
  // glPopAttrib();
  //      }
} */


