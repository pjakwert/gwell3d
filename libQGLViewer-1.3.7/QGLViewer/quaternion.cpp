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

#include "quaternion.h"
#include <stdlib.h> // RAND_MAX

// All the methods are declared inline in Quaternion.h
using namespace qglviewer;
using namespace std;

Quaternion::Quaternion(const Vec& from, const Vec& to)
{
  const float epsilon = 1E-10;

  const float fromSqNorm = from.sqNorm();
  const float toSqNorm   = to.sqNorm();
  // Identity Quaternion when one vector is null
  if ((fromSqNorm < epsilon) || (toSqNorm < epsilon))
    {
      q[0]=q[1]=q[2]=0.0;
      q[3]=1.0;
    }
  else
    {
      Vec axis = cross(from, to);
      const float axisSqNorm = axis.sqNorm();

      // Aligned vectors, pick any axis, not aligned with from or to
      if (axisSqNorm < epsilon)
	{
	  axis = Vec(1.0, 0.0, 0.0);
	  if (axis*from < 0.1*sqrt(fromSqNorm))
	    axis = Vec(0.0, 1.0, 0.0);
	}
      
      double angle = asin(sqrt(axisSqNorm / fromSqNorm / toSqNorm));
  
      if (from*to < 0.0)
	angle = M_PI-angle;
      
      setAxisAngle(axis, angle);
    }
}

//! Vec v is applied the inverse Quaternion rotation (inverseRotate() * rotate() is the identity).
Vec Quaternion::inverseRotate(const Vec& v) const
{
  const double q00 = 2.0l * q[0] * q[0];
  const double q11 = 2.0l * q[1] * q[1];
  const double q22 = 2.0l * q[2] * q[2];

  const double q01 = 2.0l * q[0] * q[1];
  const double q02 = 2.0l * q[0] * q[2];
  const double q03 = 2.0l * q[0] * q[3];

  const double q12 = 2.0l * q[1] * q[2];
  const double q13 = 2.0l * q[1] * q[3];

  const double q23 = 2.0l * q[2] * q[3];

  return Vec((1.0 - q11 - q22)*v[0] + (      q01 + q23)*v[1] + (      q02 - q13)*v[2],
	     (      q01 - q23)*v[0] + (1.0 - q22 - q00)*v[1] + (      q12 + q03)*v[2],
	     (      q02 + q13)*v[0] + (      q12 - q03)*v[1] + (1.0 - q11 - q00)*v[2] );
}

//! Vec \p v is rotated by the Quaternion rotation (see also inverseRotate()).
Vec Quaternion::rotate(const Vec& v) const
{
  const double q00 = 2.0l * q[0] * q[0];
  const double q11 = 2.0l * q[1] * q[1];
  const double q22 = 2.0l * q[2] * q[2];

  const double q01 = 2.0l * q[0] * q[1];
  const double q02 = 2.0l * q[0] * q[2];
  const double q03 = 2.0l * q[0] * q[3];

  const double q12 = 2.0l * q[1] * q[2];
  const double q13 = 2.0l * q[1] * q[3];

  const double q23 = 2.0l * q[2] * q[3];
  
  return Vec((1.0 - q11 - q22)*v[0] + (      q01 - q23)*v[1] + (      q02 + q13)*v[2],
	     (      q01 + q23)*v[0] + (1.0 - q22 - q00)*v[1] + (      q12 - q03)*v[2],
	     (      q02 - q13)*v[0] + (      q12 + q03)*v[1] + (1.0 - q11 - q00)*v[2] );
}

/*! Set the Quaternion from a (supposedly correct) 3x3 rotation matrix.

  Use setFromRotatedBase() a fill the three columns of the matrix with your basis vectors in order to 
  to set a Quaternion from the three axis of a rotated frame.  */
void Quaternion::setFromRotationMatrix(const float m[3][3])
{
  // First, find largest diagonal in matrix:
  int i = 2;
  if (m[0][0] > m[1][1])
    {
      if (m[0][0] > m[2][2])
	{
	  i = 0;
	} 
    }
  else
    {
      if (m[1][1] > m[2][2])
	{
	  i = 1;
	}
    }
  
  if (m[0][0]+m[1][1]+m[2][2] > m[i][i])
    {
      // Compute w first:
      q[3] = sqrt(m[0][0]+m[1][1]+m[2][2]+1.0)/2.0;
      // And compute other values:
      q[0] = (m[2][1]-m[1][2])/(4.0*q[3]);
      q[1] = (m[0][2]-m[2][0])/(4.0*q[3]);
      q[2] = (m[1][0]-m[0][1])/(4.0*q[3]);
    }
  else
    {
      // Compute x, y, or z first:
      int j = (i+1)%3; 
      int k = (i+2)%3;

      // Compute first value:
      q[i] = sqrt(m[i][i]-m[j][j]-m[k][k]+1.0)/2.0;

      // And the others:
      q[j] = (m[i][j]+m[j][i])/(4.0*q[i]);
      q[k] = (m[i][k]+m[k][i])/(4.0*q[i]);

      q[3] = (m[k][j]-m[j][k])/(4.0*q[i]);
    }
}

/*! Same as setFromRotationMatrix(), but the input are the three orthogonal
  axis of a rotated basis: \p X, \p Y and \p Z. */
void Quaternion::setFromRotatedBase(const Vec& X, const Vec& Y, const Vec& Z)
{
  float m[3][3];
  float normX = X.norm();
  float normY = Y.norm();
  float normZ = Z.norm();

  for (int i=0; i<3; ++i)
    {
      m[i][0] = X[i] / normX;
      m[i][1] = Y[i] / normY;
      m[i][2] = Z[i] / normZ;
    }
  setFromRotationMatrix(m);
}

/*! Returns the axis and the angle (in radians) of the rotation represented by the Quaternion.
 See also axis() and angle(). */
void Quaternion::getAxisAngle(Vec& axis, float& angle) const
{
  angle = 2.0*acos(q[3]);
  axis = Vec(q[0], q[1], q[2]);
  const float sinus = axis.norm();
  if (sinus > 1E-8)
    axis /= sinus;
  
  if (angle > M_PI)
    {
      angle = 2.0*M_PI - angle;
      axis = -axis;
    }
}

/*! Returns the axis of the rotation represented by the Quaternion.
The axis may be null for an identity rotation. See also angle() and getAxisAngle(). */
Vec Quaternion::axis() const
{
  Vec res = Vec(q[0], q[1], q[2]);
  const float sinus = res.norm();
  if (sinus > 1E-8)
    res /= sinus;
  return (acos(q[3]) <= M_PI/2.0) ? res : -res;
}

/*! Returns the angle (in radians) of the rotation represented by the Quaternion.
  See also axis() and getAxisAngle().
 \note Returned value is in the range [0-pi]. Larger rotational angles are
 obtained by inverting the axis direction. See also axis(). */
float Quaternion::angle() const
{
  const float angle = 2.0 * acos(q[3]);
  return (angle <= M_PI) ? angle : 2.0*M_PI - angle;
}

/*! Creates an XML QDomElement that represents the Quaternion. \p name is the name of the
 QDomElement tag. You need to provide the QDomDocument \p doc that will hold the resulting
 element. Typical usage would be:
 \code
 QDomDocument doc("myDocument");
 Quaternion sunQuat;
 // ...
 anyNode.addElement(sunQuat.domElement("sunOrientation", doc));
 // ...
 \endcode
 Use initFromDOMElement() to restore the Quaternion state from the resulting domElement.

 See also Vec::domElement(), Camera::domElement(), KeyFrameInterpolator::domElement()... */
QDomElement Quaternion::domElement(const QString& name, QDomDocument& doc) const
{
  QDomElement de = doc.createElement(name);
  de.setAttribute("q0", QString::number(q[0]));
  de.setAttribute("q1", QString::number(q[1]));
  de.setAttribute("q2", QString::number(q[2]));
  de.setAttribute("q3", QString::number(q[3]));
  return de;
}

/*! Restore the Quaternion state from a QDomElement created by domElement(). The QDomElement must
  contain the \e q0, \e q1 , \e q2 and \e q3 attributes, otherwise these fields are set to 0.0,
  0.0, 0.0, 1.0 (identity Quaternion) . */
void Quaternion::initFromDOMElement(const QDomElement& de)
{
  setValue((de.attribute("q0", "0.0")).toDouble(), (de.attribute("q1", "0.0")).toDouble(),
	   (de.attribute("q2", "0.0")).toDouble(), (de.attribute("q3", "1.0")).toDouble());
}

/*! Returns the Quaternion associated 4x4 OpenGL rotation matrix. Can be used with \p
  glMultMatrixd(q.matrix()) or \p glLoadMatrixd(q.matrix()).
 \code
 Vec From,To;
 // Set the From and To directions
 ...
 // Computes a Quaternion which transform From in To
 Quaternion q(From, To);
 // Rotates the current openGL matrix.
 glMultMatrixd(q.matrix());
 \endcode

 See also getMatrix(), getRotationMatrix() and inverseMatrix().
 
 \attention The matrix is given in OpenGL format (row-major order) and is the transpose of the
 actual mathematical European representation. Consider using getRotationMatrix() instead.

 \attention The result is only valid until the next call to matrix(). Use it immediately (as in \c
 glLoadMatrixd(q.matrix()) or \c glLoadMatrixd(q.matrix())) or store it in an other variable.
 Consider using getMatrix() if needed. */
const GLdouble* Quaternion::matrix() const
{
  static GLdouble m[4][4];
  getMatrix(m);
  return (const GLdouble*)(m);
}

/*! double[4][4] parameter version of matrix(). See also getInverseMatrix() and Frame::getMatrix(). */
void Quaternion::getMatrix(GLdouble m[4][4]) const
{
  const double q00 = 2.0l * q[0] * q[0];
  const double q11 = 2.0l * q[1] * q[1];
  const double q22 = 2.0l * q[2] * q[2];

  const double q01 = 2.0l * q[0] * q[1];
  const double q02 = 2.0l * q[0] * q[2];
  const double q03 = 2.0l * q[0] * q[3];

  const double q12 = 2.0l * q[1] * q[2];
  const double q13 = 2.0l * q[1] * q[3];

  const double q23 = 2.0l * q[2] * q[3];

  m[0][0] = 1.0l - q11 - q22;
  m[1][0] =        q01 - q23;
  m[2][0] =        q02 + q13;

  m[0][1] =        q01 + q23;
  m[1][1] = 1.0l - q22 - q00;
  m[2][1] =        q12 - q03;

  m[0][2] =        q02 - q13;
  m[1][2] =        q12 + q03;
  m[2][2] = 1.0l - q11 - q00;
  
  m[0][3] = 0.0l;
  m[1][3] = 0.0l;
  m[2][3] = 0.0l;
  
  m[3][0] = 0.0l;
  m[3][1] = 0.0l;
  m[3][2] = 0.0l;
  m[3][3] = 1.0l;
}

/*! double[16] parameter version of matrix(). See also getInverseMatrix() and Frame::getMatrix(). */
void Quaternion::getMatrix(GLdouble m[16]) const
{
  static GLdouble mat[4][4];
  getMatrix(mat);
  int count = 0;
  for (int i=0; i<4; ++i)
    for (int j=0; j<4; ++j)
      m[count++] = mat[i][j]; 
}

/*! \p m is set to the 3x3 rotation matrix associated with the Quaternion.

  \attention This is the classical mathematical rotation matrix. The openGL format uses its
  transposed version. See also matrix(), getInverseRotationMatrix() and getMatrix(). */
void Quaternion::getRotationMatrix(float m[3][3]) const
{
  static GLdouble mat[4][4];
  getMatrix(mat);
  for (int i=0; i<3; ++i)
    for (int j=0; j<3; ++j)
      // Beware of transposition
      m[i][j] = mat[j][i];
}

/*! Returns the associated 4x4 OpenGL \e inverse rotation matrix. This is simply the matrix() of the
  inverse().

  \attention The matrix is given in OpenGL format (row-major order) and is the transpose of the
  actual mathematical European representation. Consider using getInverseRotationMatrix() instead.

  \attention The result is only valid until the next call to inverseMatrix(). Use it immediately (as
  in \c glLoadMatrixd(q.inverseMatrix()) or store it in an other variable. Consider using
  getInverseMatrix() if needed. */
const GLdouble* Quaternion::inverseMatrix() const
{
  static GLdouble m[4][4];
  getInverseMatrix(m);
  return (const GLdouble*)(m);
}

/*! double[4][4] parameter version of inverseMatrix(). See also getMatrix(). */
void Quaternion::getInverseMatrix(GLdouble m[4][4]) const
{
  inverse().getMatrix(m);
}

/*! double[16] parameter version of inverseMatrix(). See also getMatrix(). */
void Quaternion::getInverseMatrix(GLdouble m[16]) const
{
  inverse().getMatrix(m);
}

/*! \p m is set to the 3x3 \e inverse rotation matrix associated with the Quaternion.

 \attention This is the classical mathematical rotation matrix. The openGL format uses its
 transposed version. See inverseMatrix() and getInverseMatrix(). */
void Quaternion::getInverseRotationMatrix(float m[3][3]) const
{
  static GLdouble mat[4][4];
  getInverseMatrix(mat);
  for (int i=0; i<3; ++i)
    for (int j=0; j<3; ++j)
      // Beware of transposition
      m[i][j] = mat[j][i];
}


/*! Returns the slerp interpolation of Quaternion \p a and \p b, at time \p t (in [0,1]).
 Result is \a when \p t=0 and \b when \p t=1.

 When \p allowFlip is \p true (default) the slerp interpolation will always use the "shortest path"
 between the Quaternions' orientations, by "flipping" the source Quaternion if needed. */
Quaternion Quaternion::slerp(const Quaternion& a, const Quaternion& b, float t, bool allowFlip)
{
  float cosAngle = Quaternion::dot(a, b);

  float c1, c2;
  // Linear interpolation for close orientations
  if ((1.0 - fabs(cosAngle)) < 0.01) 
    {
      c1 = 1.0 - t;
      c2 = t;
    }
  else 
    { 
      // Spherical interpolation
      float angle    = acos(fabs(cosAngle));
      float sinAngle = sin(angle);
      c1 = sin(angle * (1.0 - t)) / sinAngle;
      c2 = sin(angle * t) / sinAngle;
    }
  
  // Use the shortest path
  if (allowFlip && (cosAngle < 0.0))
    c1 = -c1;
  
  return Quaternion(c1*a[0] + c2*b[0], c1*a[1] + c2*b[1], c1*a[2] + c2*b[2], c1*a[3] + c2*b[3]);
}

/*! Returns the slerp interpolation of the two Quaternion \p a and \p b, at time \p t (in [0,1]).
  The resulting Quaternion is "between" \p a and \p b (result is \p a when t=0 and is \b when \p
  t=1). The interpolation tangent are defined by \p tgA and \p tgB (see squadTangent()). */
Quaternion Quaternion::squad(const Quaternion& a, const Quaternion& tgA, const Quaternion& tgB, const Quaternion& b, float t)
{
  Quaternion ab = Quaternion::slerp(a, b, t);
  Quaternion tg = Quaternion::slerp(tgA, tgB, t, false);
  return Quaternion::slerp(ab, tg, 2.0*t*(1.0-t), false);
}

/*! Returns the logarithm of the Quaternion. See also exp(). */ 
Quaternion Quaternion::log()
{
  float len = sqrt(q[0]*q[0] + q[1]*q[1] + q[2]*q[2]);
 
  if (len < 1E-6)
    return Quaternion(q[0], q[1], q[2], 0.0);
  else
    {
      float coef = acos(q[3]) / len;
      return Quaternion(q[0]*coef, q[1]*coef, q[2]*coef, 0.0);
    }
} 
 
/*! Returns the exponential of the Quaternion. See also log(). */ 
Quaternion Quaternion::exp()
{
  float theta = sqrt(q[0]*q[0] + q[1]*q[1] + q[2]*q[2]);
 
  if (theta < 1E-6)
    return Quaternion(q[0], q[1], q[2], cos(theta));
  else
    {
      float coef = sin(theta) / theta; 
      return Quaternion(q[0]*coef, q[1]*coef, q[2]*coef, cos(theta));
    }
}

/*! Returns log(a. inverse() * b). Useful for squadTangent(). */
Quaternion Quaternion::lnDif(const Quaternion& a, const Quaternion& b)
{
  Quaternion dif = a.inverse()*b;
  dif.normalize();
  return dif.log();
}

/*! Returns a tangent Quaternion, which enables a smooth spline interpolation of Quaternion with squad(). */ 
Quaternion Quaternion::squadTangent(const Quaternion& a, const Quaternion& b, const Quaternion& c)
{
  Quaternion l1 = Quaternion::lnDif(b,a);
  Quaternion l2 = Quaternion::lnDif(b,c);
  Quaternion e;
  for (int i=0; i<4; ++i)
    e.q[i] = -0.25 * (l1.q[i] + l2.q[i]);
  e = b*(e.exp());

  // if (Quaternion::dot(e,b) < 0.0)
    // e.negate();

  return e;
}

ostream& operator<<(ostream& o, const Quaternion& Q)
{
  return o << Q[0] << '\t' << Q[1] << '\t' << Q[2] << '\t' << Q[3];
}

/*! Returns a random unit Quaternion. A randomly directed unit vector can then be computed using :
\code
Vec randomDir = Quaternion::randomOrientation() * Vec(1.0, 0.0, 0.0); // or any other Vec
\endcode

\note This function uses rand() to create pseudo-random numbers and the random number generator can
be initialized using srand().*/
Quaternion Quaternion::randomOrientation()
{
  // The rand() function is not very portable and may not be available on your system.
  // Add the appropriate include or replace by an other random function in case of problem.
  double seed = rand()/(float)RAND_MAX;
  double r1 = sqrt(1.0 - seed);
  double r2 = sqrt(seed);
  double t1 = 2.0 * M_PI * (rand()/(float)RAND_MAX);
  double t2 = 2.0 * M_PI * (rand()/(float)RAND_MAX);
  return Quaternion(sin(t1)*r1, cos(t1)*r1, sin(t2)*r2, cos(t2)*r2);
}
