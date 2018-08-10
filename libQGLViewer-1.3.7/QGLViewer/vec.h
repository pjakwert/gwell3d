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

#ifndef QGLVIEWER_VEC_H
#define QGLVIEWER_VEC_H

#include <math.h>
#include <iostream>
#include <qdom.h>
#include "qapplication.h"

// Included by all files as vec.h is at the end of the include hierarchy
#include "config.h" // Specific configuration options.

namespace qglviewer {

  /*! \brief A 3D point and vector class.
    
    Vec is a QGLViewer internal class, used to represent 3D positions and 3D vectors. It is part of
    the \p qglviewer namespace. You can use it in your programs by specifying \p qglviewer::Vec, or
    by using the qglviewer namespace : \code using namespace qglviewer; \endcode

    \p Vec implements a universal explicit converter, based on the [] \p operator.
    Everywhere a \p const \p Vec& argument is expected, you can use your own 3D point type
    instead, as long as it implements the [] operator :
    \code
    float operator[] (const int i) const { respectively return x, y or z for i=0, 1 or 2 };
    \endcode

    The following code is hence valid :
    \code
    // class myVector implements the [] operator
    myVector mv;
    fr.setPosition( qglviewer::Vec(mv) );
    // or if you use namespace qglviewer
    fr.setPosition( Vec(mv) );
    \endcode

    When Vec is used as a return value, a classical float[3] version of the function is always available.

    You can also convert a Vec result to your own class, using code such as :
    \code
    qglviewer::Vec sc = sceneCenter();
    myVector.setX(sc.x);    // or sc[0]
    myVector.setY(sc.y);    // or sc[1]
    myVector.setZ(sc.z);    // or sc[2]
    \endcode
    See also the Quaternion and the Frame documentation.
    \nosubgrouping */
  class QGLVIEWER_EXPORT Vec
  {
  public:
    //! The internal data representation is public. One can use v.x, v.y, v.z.
    float x, y, z;

    /*! @name Setting Vec values */
    //@{
    //! Default constructor. Default value is (0,0,0).
    explicit Vec() : x(0.0), y(0.0), z(0.0) {}

    //! Standard constructor with the x,y and z values.
    explicit Vec(const float X, const float Y, const float Z) : x(X), y(Y), z(Z) {}

    /*! Universal explicit converter from any class to Vec. You can use your own vector class everywhere
    a \p const \p Vec& parameter is required, as long as it implements the [] operator.
    \code
      // Declared in class MyVec
      float operator[](int i) const { return (x, y or z); }

      // Then you can use
      MyVec v(...);
      camera()->setPosition( qglviewer::Vec(v) );
    \endcode
    */
    template <class C>
    explicit Vec(const C& c) : x(c[0]), y(c[1]), z(c[2]) {}

    // ! Copy constructor
    // explicit Vec(const Vec& v) : x(v.x), y(v.y), z(v.z) {}

    //! Classical = operator
    Vec& operator=(const Vec& v)
    {
      x = v.x;   y = v.y;   z = v.z;
      return *this;
    }

    //! Set the current value. Faster than using operator equal with a temporary Vec(x,y,z).
    void setValue(const float X, const float Y, const float Z)
    { x=X; y=Y; z=Z; }
    
    // Universal equal operator which allows the use of any type in place of Vec,
    // as long as the [] operator is implemented (v[0]=v.x, v[1]=v.y, v[2]=v.z).
    // template <class C>
    // Vec& operator=(const C& c)
    // {
    // x=c[0]; y=c[1]; z=c[2];
    // return *this;
    // }
    //@}
    
    /*! @name Access values */
    //@{
    //! Bracket operator, with a constant return value
    float operator[](int i) const { return (&x)[i]; }

    //! Bracket operator, returns an l-value
    float& operator[](int i) { return (&x)[i]; }

    //! The memory address of the vector. Useful as an argument for glVertex3fv, glNormal3fv...
    const float* address() const { return &x; };

    //! Dereferencing operator that returns the memory address of the vector. Same as address().
    operator const float*() const { return &x; };
    //@}

    /*! @name Calculus */
    //@{
    //! Returns the sum of the two vectors.
    friend Vec operator+(const Vec &a, const Vec &b)
    {
      return Vec(a.x+b.x, a.y+b.y, a.z+b.z);
    }

    //! Returns the difference of the two vectors.
    friend Vec operator-(const Vec &a, const Vec &b)
    {
      return Vec(a.x-b.x, a.y-b.y, a.z-b.z);
    }

    //! Unary minus operator
    friend Vec operator-(const Vec &a)
    {
      return Vec(-a.x, -a.y, -a.z);
    }

    //! Returns the product of the vector with a scalar.
    friend Vec operator*(const Vec &a, const float k)
    {
      return Vec(a.x*k, a.y*k, a.z*k);
    }

    //! Returns the product of the vector with a scalar.
    friend Vec operator*(float k, const Vec &a)
    {
      return Vec(a.x*k, a.y*k, a.z*k);
    }

    //! Returns the division of the vector with a scalar. If the library was compiled with the "debug" qt \p CONFIG flag, tests for null value.
    friend Vec operator/(const Vec &a, const float k)
    {
#ifndef QT_NO_DEBUG
      if (fabs(k) < 1.0E-10)
	qWarning("Vec::operator / : dividing by a null value");
#endif
      return Vec(a.x/k, a.y/k, a.z/k);
    }

    //! Comparison based on the squared norm of the difference vector, see operator==.
    friend bool operator!=(const Vec &a, const Vec &b)
    {
      return !(a==b);
    }

    //! Comparison based on the \e squared norm of the difference vector, epsilon=1E-10.
    friend bool operator==(const Vec &a, const Vec &b)
    {
      const float epsilon = 1.0E-10f;
      return (a-b).sqNorm() < epsilon;
    }

    //! Adds \p a to the vector.
    Vec& operator+=(const Vec &a)
    {
      x += a.x; y += a.y; z += a.z;
      return *this;
    }

    //! Subtracts \p a to the vector.
    Vec& operator-=(const Vec &a)
    {
      x -= a.x; y -= a.y; z -= a.z;
      return *this;
    }

    //! Multiply the vector by a scalar.
    Vec& operator*=(float k)
    {
      x *= k; y *= k; z *= k;
      return *this;
    }

    //! Divides the vector by a scalar. If the library was compiled with the "debug" qt \p CONFIG flag, tests for null value.
    Vec& operator/=(float k)
    {
#ifndef QT_NO_DEBUG
      if (fabs(k)<1.0E-10)
	qWarning("Vec::operator /= : dividing by a null value");
#endif
      x /= k; y /= k; z /= k;
      return *this;
    }

    //! Dot product.
    friend float operator*(const Vec &a, const Vec &b)
    {
      return a.x*b.x + a.y*b.y + a.z*b.z;
    }

    //! Cross product of the two vectors. Mind the order !
    friend Vec cross(const Vec &a, const Vec &b)
    {
      return Vec(a.y*b.z - a.z*b.y,
		 a.z*b.x - a.x*b.z,
		 a.x*b.y - a.y*b.x);
    }

    //! Cross product of the two vectors. See also cross().  
    friend Vec operator^(const Vec &a, const Vec &b)
    {
      return Vec(a.y*b.z - a.z*b.y,
		 a.z*b.x - a.x*b.z,
		 a.x*b.y - a.y*b.x);
    }
    //@}

    /*! @name Norm of the vector */
    //@{
    //! Returns the \e squared norm of the Vec.
    float sqNorm() const { return x*x + y*y + z*z; }

    //! Returns the norm of the vector.
    float norm() const { return sqrt(x*x + y*y + z*z); }

    //! Normalizes the Vec. Its previous norm is returned. If the library was compiled with the "debug" qt \p CONFIG flag, tests for null value.
    float normalize()
    {
      const float n = norm();
#ifndef QT_NO_DEBUG
      if (n < 1.0E-10)
	qWarning("Vec::normalize : normalizing a null vector");
#endif
      *this /= n;
      return n;
    }
      
    //! Returns a unitary (normalized) \e representation of the vector. The original Vec is not modified.
    Vec unit()
    {
      Vec v = *this;
      v.normalize();
      return v;
    }
    //@}
  
    /*! @name Vec projection */
    //@{
    void projectOnAxis(const Vec& dir);
    void projectOnPlane(const Vec& n);
    //@}

    /*! @name XML representation.
    These methods are used by higher level class (Camera, KeyFrameInterpolator...) to save and
    restore the state of the Vec they hold. */
    //@{
    QDomElement domElement(const QString& name, QDomDocument& doc) const;
    void initFromDOMElement(const QDomElement& de);
    //@}
  };
  
} // namespace

std::ostream& operator<<(std::ostream& o, const qglviewer::Vec&);
  
#endif // QGLVIEWER_VEC_H
