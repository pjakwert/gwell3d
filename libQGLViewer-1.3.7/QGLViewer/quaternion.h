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

#ifndef QGLVIEWER_QUATERNION_H
#define QGLVIEWER_QUATERNION_H

#include "vec.h"
#include <math.h>
#include <iostream>

namespace qglviewer {
  /*! \brief A Quaternion 3D rotation class.
  
  A Quaternion is a clean representation of a 3D rotation matrix or of an orientation. In this
  implementation, the Quaternion are supposed to be normalized, so that the inverse() is actually
  a conjugate function.

  Many tools are provided define a 3D rotation (constructors, setAxisAngle(),
  setFromRotationMatrix(), setFromRotatedBase()...). Apply the rotation to 3D points using rotate()
  and inverseRotate(). Also consider the Frame coordinate system conversion functions like
  Frame::coordinatesOf() and Frame::coordinatesOfFrom().

  The Quaternion corresponding to a rotation vector \p v, with an angle \p
  alpha is :
  \code
  {q[0],q[1],q[2]} = sin(alpha/2) * {v[0],v[1],v[2]}
  q[3] = cos(alpha/2)
  \endcode

  Quaternion is a QGLViewer internal class. It is part of the \p qglviewer namespace.
  You can use it in your programs by specifying \p qglviewer::Quaternion, or by using
  the qglviewer namespace :
  \code
  using namespace qglviewer;
  \endcode
  See also the Vec and the Frame documentation.
  \nosubgrouping */

class QGLVIEWER_EXPORT Quaternion
{
public:
  /*! @name Defining a Quaternion */
  //@{
  //! Default Quaternion, a null rotation
  explicit Quaternion()
  { q[0]=q[1]=q[2]=0.0;  q[3]=1.0; }

  //! Simple constructor with any axis and angle (in radians)
  explicit Quaternion(const Vec& axis, const double angle)
  {
    setAxisAngle(axis, angle);
  }

  //! Constructor with normalized axis, cos & sin of half angle
  explicit Quaternion(const Vec& v, const double sin_ha, const double cos_ha)
  {
    q[0] = v[0]*sin_ha ;
    q[1] = v[1]*sin_ha ;
    q[2] = v[2]*sin_ha ;
    q[3] = cos_ha ;
  }
  
  //! Constructor from the values of a Quaternion.
  explicit Quaternion(const double q0, const double q1, const double q2, const double q3)
  { q[0]=q0;    q[1]=q1;    q[2]=q2;    q[3]=q3; }

  //! Constructs a Quaternion that will rotate from the \p from direction to the \p to direction.
  explicit Quaternion(const Vec& from, const Vec& to);

  //! Equal operator
  Quaternion& operator=(const Quaternion& Q)
  {
    for (int i=0; i<4; ++i)
      q[i] = Q.q[i];
    return (*this);
  }

  //! Copy constructor
  Quaternion(const Quaternion& Q)
  { for (int i=0; i<4; ++i) q[i] = Q.q[i]; }
  
  //! To reset a Quaternion to the rotation of axis \p v and angle \p angle (in radians)
  void setAxisAngle(const Vec& v, const double angle)
  {
    const double norm = v.norm();
    if (norm < 1E-9)
      {
	// Null rotation
	q[0] = 0.0;      q[1] = 0.0;      q[2] = 0.0;      q[3] = 1.0;
      }
    else
      {
	const double sin_half_angle = sin(angle / 2.0);
	q[0] = sin_half_angle*v[0]/norm;
	q[1] = sin_half_angle*v[1]/norm;
	q[2] = sin_half_angle*v[2]/norm;
	q[3] = cos(angle / 2.0);
      }
  }

  //! Set the current Quaternion value.
  void setValue(const double q0, const double q1, const double q2, const double q3)
  { q[0]=q0;    q[1]=q1;    q[2]=q2;    q[3]=q3; }

  void setFromRotationMatrix(const float m[3][3]);
  void setFromRotatedBase(const Vec& X,
			  const Vec& Y,
			  const Vec& Z);
  //@}

  
  /*! @name Access values */
  //@{
  Vec axis() const;  
  float angle() const;
  void getAxisAngle(Vec& axis, float& angle) const;

  //! Bracket operator, with a constant return value
  double operator[](int i) const { return q[i]; }

  //! Bracket operator, returns an l-value
  double& operator[](int i) { return q[i]; }
  //@}


  /*! @name Calculus */
  //@{
  /*! Returns the composition of the two rotations (mind the order !).
    \attention For efficiency reasons, the resulting Quaternion is not normalized.
    You may normalize() the quaternion after each application in case of numerical drift. */
  friend const Quaternion operator*(const Quaternion& a, const Quaternion& b)
  {
    return Quaternion (a.q[3]*b.q[0] + b.q[3]*a.q[0] + a.q[1]*b.q[2] - a.q[2]*b.q[1],
		       a.q[3]*b.q[1] + b.q[3]*a.q[1] + a.q[2]*b.q[0] - a.q[0]*b.q[2],
		       a.q[3]*b.q[2] + b.q[3]*a.q[2] + a.q[0]*b.q[1] - a.q[1]*b.q[0],
		       a.q[3]*b.q[3] - b.q[0]*a.q[0] - a.q[1]*b.q[1] - a.q[2]*b.q[2]);
  }

  /*! Quaternion is composed with \p q.
    \attention For efficiency reasons, the resulting Quaternion is not normalized.
    You may normalize() the quaternion after each application in case of numerical drift. */
  Quaternion& operator*=(const Quaternion &q)
  {
    *this = (*this)*q;
    return *this;
  }

  //! Same as a.rotate(b)
  friend const Vec operator*(const Quaternion& a, const Vec& b)
  {
    return a.rotate(b);
  }
  
  Vec inverseRotate(const Vec& v) const;
  Vec rotate(const Vec& v) const;
  //@}


  /*! @name Inversion */
  //@{
  /*! Returns the inverse of the Quaternion (axis() is negated), which represents the opposite
   orientation. The original Quaternion is \e not modified. Use invert() to actually modify the
   Quaternion. */
  Quaternion inverse() const { return Quaternion(-q[0], -q[1], -q[2], q[3]); }

  /*! Inverse the Quaternion (same rotation angle, but opposite axis). The new orientation is the
    inverse (in the mathematical sense) of the previous one. The rotation represented by this
    Quaternion is now the inverse rotation. See also inverse(). */
  void invert() { q[0] = -q[0]; q[1] = -q[1]; q[2] = -q[2]; }

  /*! Negate all the coefficients of the Quaternion. The axis and angle are negated. However, the
  result of axis() and angle() are unchanged, as it is just an other representation of the same
  Quaternion (see angle(), which always returns a value in [0,pi]). Useful for Quaternion
  interpolation, so that the spherical interpolation takes the shortest path. See also slerp(),
  squad(), dot(). */
  void negate() { invert(); q[3] = -q[3]; }

  /*! Normalize the Quaternion. Should not need to be called as we only deal with unit Quaternion.
    Useful to prevent numerical drifts, especially with small rotational increments. */
  double normalize()
  {
    const double norm = sqrt(q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]);
    for (int i=0; i<4; ++i)
      q[i] /= norm;
    return norm;
  }
  //@}

  
  /*! @name Associated matrix */
  //@{
  const GLdouble* matrix() const;
  void getMatrix(GLdouble m[4][4]) const;
  void getMatrix(GLdouble m[16]) const;

  void getRotationMatrix(float m[3][3]) const;

  const GLdouble* inverseMatrix() const;
  void getInverseMatrix(GLdouble m[4][4]) const;
  void getInverseMatrix(GLdouble m[16]) const;

  void getInverseRotationMatrix(float m[3][3]) const;
  //@}

  
  /*! @name Slerp rotation interpolation */
  //@{
  static Quaternion slerp(const Quaternion& a, const Quaternion& b, float t, bool allowFlip=true);
  static Quaternion squad(const Quaternion& a, const Quaternion& tgA, const Quaternion& tgB, const Quaternion& b, float t);
  /*! Return a[0]*b[0] + a[1]*b[1] + a[2]*b[2] + a[3]*b[3]. See also negate() and slerp(). */
  static double dot(const Quaternion& a, const Quaternion& b) { return a[0]*b[0] + a[1]*b[1] + a[2]*b[2] + a[3]*b[3]; }

  Quaternion log();
  Quaternion exp();
  static Quaternion lnDif(const Quaternion& a, const Quaternion& b);
  static Quaternion squadTangent(const Quaternion& a, const Quaternion& b, const Quaternion& c);
  //@}

  /*! @name Random orientation */
  //@{
  static Quaternion randomOrientation();
  //@}
  
  /*! @name XML representation */
  //@{  
  QDomElement domElement(const QString& name, QDomDocument& doc) const;  
  void initFromDOMElement(const QDomElement& de);
  //@}

private: 
  //! The internal data representation is private, use operator[] to acces values.
  double q[4];
};

} // namespace

std::ostream& operator<<(std::ostream& o, const qglviewer::Quaternion&);

#endif // QGLVIEWER_QUATERNION_H
