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

#ifndef _VECTS_H_
#define _VECTS_H_

#include <iostream>
#include <math.h>
#include "../config.h"
#include "Functions.h"

template<class T> class T_Vect2;
template<class T> class NormalizedT_Vect3;

template<class T> class T_Vect3
{
	public:
		T_Vect3() { X = 0.0 ; Y = 0.0 ; Z = 0.0 ; }
		T_Vect3(const T_Vect3<T>& v) { X = v.X ; Y = v.Y ; Z = v.Z ; }
 		T_Vect3(const T_Vect2<T>&, T) ;
		T_Vect3(T x,T y, T z) { X = x ; Y = y ; Z = z ; }
		T_Vect3(const NormalizedT_Vect3<T>& v) { X = v.X ; Y = v.Y ; Z = v.Z ; }

		T X,Y,Z ;

		inline void Set(const T& x,const T& y,const T& z) { X = x ; Y = y ; Z = z ; }

		inline T Norm() 	const 	{ return sqrt( Norm2() ) ; }
		inline T Norm2() 	const 	{ return X*X + Y*Y + Z*Z ; }

		T NormInf() const 	{ 
			float max = ((fabs(X) > fabs(Y)) ? fabs(X) : fabs(Y));
			return ((max > fabs(Z)) ? max : fabs(Z)) ; 
		}

		inline void Normalize() 
		{
       		T d = X*X+Y*Y+Z*Z ;

			if(d == 0.0)
			{
				std::cerr << "Vect3::Normalize: trying to normalize null vector !" << std::endl ;
#ifdef DEBUG
				DumpCore() ;
#endif
			}
			else
			{
				d = sqrt(d) ;

				X /= d ;
				Y /= d ;
				Z /= d ;
			}
		}

		inline NormalizedT_Vect3<T> Normalized() const ;

		inline const T_Vect3<T>& operator=(const T_Vect3<T> & v) 
		{ 
			if(this != &v) 
			{ 
				X = v.X ; 
				Y = v.Y ; 
				Z = v.Z ; 
			} 
			return *this ; 
		}
		inline void operator*=(const T & v) { X *= v ; Y *= v ; Z *= v ; }
		inline void operator+=(const T_Vect3<T> & v) { X += v.X ; Y += v.Y ; Z += v.Z ; }
		inline void operator-=(const T_Vect3<T> & v) { X -= v.X ; Y -= v.Y ; Z -= v.Z ; }
		inline bool operator==(const T_Vect3<T> & v) const { return (X==v.X)&&(Y==v.Y)&&(Z==v.Z) ; }
		inline T_Vect3<T> operator+(const T_Vect3<T> & v) const { return T_Vect3<T>(X+v.X,Y+v.Y,Z+v.Z) ; }
		inline T_Vect3 operator-(const T_Vect3<T> & v) const { return T_Vect3<T>(X-v.X,Y-v.Y,Z-v.Z) ; }
		inline T_Vect3<T> operator-() const { return T_Vect3<T>(-X,-Y,-Z) ; }
		inline T_Vect3<T> operator*(const T & v) const { return T_Vect3<T>(X*v,Y*v,Z*v) ; }
		inline T_Vect3<T> operator/(const T & v) const { return T_Vect3<T>(X/v,Y/v,Z/v) ; }
		inline T operator*(const T_Vect3<T> & v) const { return X*v.X+Y*v.Y+Z*v.Z ; }
		inline T operator*(const NormalizedT_Vect3<T>& v1) const ;
		inline T_Vect3<T> operator^(const T_Vect3<T> & v) const { return T_Vect3<T>(	Y*v.Z-Z*v.Y, Z*v.X-X*v.Z, X*v.Y-Y*v.X) ; }

		inline friend T_Vect3<T> operator*(const T v, const T_Vect3<T> & a) { return a*v ; }

		friend inline std::ostream& operator<< (std::ostream& s, const T_Vect3& v) 
		{
			return s << " (" << v.X << " , " << v.Y << " , " << v.Z << ")" ;
		}

		inline void operator/=(const T & v) { X /= v ; Y /= v ; Z /= v ; }

		static const T_Vect3 Null;
} ;

template<class T> const T_Vect3<T> T_Vect3<T>::Null = T_Vect3<T>(0.0,0.0,0.0) ;

template<class T> class NormalizedT_Vect3
{
	public:
		NormalizedT_Vect3() { X=1.0 ; Y=0.0 ; Z=0.0 ; }
		NormalizedT_Vect3(const NormalizedT_Vect3& v) { X=v.X ; Y=v.Y ; Z=v.Z ; }

		explicit NormalizedT_Vect3(const T_Vect3<T>& v) 
		{ 
			X=v.X ; 
			Y=v.Y ; 
			Z=v.Z ; 
#ifdef DEBUG
			if(fabs(v.X*v.X+v.Y*v.Y+v.Z*v.Z - 1.0) > 0.0001)
				std::cout << "Trying to affect non normed vector !! (Error = " 
					<< fabs(v.X*v.X+v.Y*v.Y+v.Z*v.Z - 1.0) << ")" << std::endl ;
#endif
		}

		NormalizedT_Vect3(const T& theta,const T& phi)
		{
			T sin_theta = sin(theta) ;
			T cos_theta = cos(theta) ;
			T sin_phi   = sin(phi  ) ;
			T cos_phi   = cos(phi  ) ;

			X = cos_theta * cos_phi ;
			Y = cos_theta * sin_phi ;
			Z = sin_theta ;
		}

		inline void Normalize() {}
		inline const NormalizedT_Vect3& Normalized() const { return *this ; }

		inline T Norm2() const { return 1.0 ; }
		inline T Norm()  const { return 1.0 ; }
		inline NormalizedT_Vect3 operator-() const { return NormalizedT_Vect3(-X,-Y,-Z) ; }
		inline T operator*(const T_Vect3<T>& v1) const { return X*v1.X+Y*v1.Y+Z*v1.Z ; }
		inline T_Vect3<T> operator*(const T & v) const { return T_Vect3<T>(X*v,Y*v,Z*v) ; }
		inline T_Vect3<T> operator/(const T & v) const { return T_Vect3<T>(X/v,Y/v,Z/v) ; }

		inline T_Vect3<T> operator+(const NormalizedT_Vect3& v) const { return T_Vect3<T>(X+v.X,Y+v.Y,Z+v.Z) ; }
		inline T_Vect3<T> operator-(const NormalizedT_Vect3& v) const { return T_Vect3<T>(X-v.X,Y-v.Y,Z-v.Z) ; }

		template<class U> friend T_Vect3<U> operator^(const NormalizedT_Vect3<U>&,const NormalizedT_Vect3<U>&) ;
		friend inline std::ostream& operator<< (std::ostream& s, const NormalizedT_Vect3& v) 
		{
			return s << " (" << v.X << " , " << v.Y << " , " << v.Z << ")" ;
		}

		T X,Y,Z ;

	protected:
		NormalizedT_Vect3(T x,T y,T z)
		{
#ifdef DEBUG
			if(fabs(x*x+y*y+z*z - 1.0) > 0.000001)
				std::cerr << "Error: un-normalized vector constructed !" << std::endl ;
#endif
			X = x ;
			Y = y ;
			Z = z ;
		}

		friend NormalizedT_Vect3<T> T_Vect3<T>::Normalized() const ;
};

template<class T> NormalizedT_Vect3<T> T_Vect3<T>::Normalized() const 
{
	T n = Norm() ;

	return NormalizedT_Vect3<T>(X/n,Y/n,Z/n) ;
}

template<class T> T_Vect3<T> operator^(const NormalizedT_Vect3<T>& v1,const NormalizedT_Vect3<T>& v2) 
{
	return T_Vect3<T>(v1.Y*v2.Z - v1.Z*v2.Y,
							v1.Z*v2.X - v1.X*v2.Z,
							v1.X*v2.Y - v1.Y*v2.X);
}

template<class U> class T_Vect2
{
	public:
		T_Vect2() { X = 0.0 ; Y = 0.0 ; }
		T_Vect2(const T_Vect3<U> & V) { X = V.X ; Y = V.Y ; }
		T_Vect2(float x,float y,float=0.0) { X = x ; Y = y ; }
		float X,Y ;

		U Norm() 	const 	{ return sqrt(X*X+Y*Y) ; }
		U Norm2() 	const 	{ return X*X+Y*Y ; }
		U NormInf() const       { return (fabs(X)>fabs(Y)) ? fabs(X) : fabs(Y) ; }

		inline virtual void Set(const float& x,const float& y) { X = x ; Y = y ; }

		void Normalize() 
		{ 
			float d = sqrt(X*X+Y*Y) ; 
			if(d > 0.0) 
			{ 
				X /= d ; 
				Y /= d ; 
			} 
			else 
			{ 
				std::cerr << "Vect2::Normalize: Null vector !" << std::endl ;
#ifdef DEBUG
				DumpCore();
#endif
			}
		}
		inline bool operator==(const T_Vect2<U> & v) const { return (X==v.X)&&(Y==v.Y) ; }
		inline T_Vect2<U>& operator=(const T_Vect2<U> & v) 
		{ 
			if(this != &v)
			{
				X = v.X ; 
				Y = v.Y ; 
			}
			return *this ; 
		}
		inline void operator*=(const float & v) { X *= v ; Y *= v ; }
		inline void operator+=(const T_Vect2<U> & v) { X += v.X ; Y += v.Y ; }
		inline void operator-=(const T_Vect2<U> & v) { X -= v.X ; Y -= v.Y ; }
		inline T_Vect2<U> operator+(const T_Vect2<U> & v) const { return T_Vect2<U>(X+v.X,Y+v.Y) ; }
		inline T_Vect2<U> operator-(const T_Vect2<U> & v) const { return T_Vect2<U>(X-v.X,Y-v.Y) ; }
		inline T_Vect2<U> operator-() const { return T_Vect2<U>(-X,-Y) ; }
		inline T_Vect2<U> operator*(const float & v) const { return T_Vect2<U>(X*v,Y*v) ; }
		inline T_Vect2<U> operator/(const float & v) const { return T_Vect2<U>(X/v,Y/v) ; }
		inline float operator*(const T_Vect2<U> & v) const { return X*v.X+Y*v.Y ; }
		inline T_Vect3<U> operator^(const T_Vect2<U> & v) const { return T_Vect3<U>(0.0,0.0, X*v.Y-Y*v.X) ; }

		inline friend T_Vect2<U> operator*(const float v, const T_Vect2<U> & a) { return a*v ; }
		inline T_Vect2<U> T() const { return T_Vect2<U>(-Y,X) ; }
		template<class T> friend T_Vect2<T> VectorMin(const T_Vect2<T> &, const T_Vect2<T> &) ;
		template<class T> friend T_Vect2<T> VectorMax(const T_Vect2<T> &, const T_Vect2<T> &) ;
		inline void operator/=(const float & v) { X /= v ; Y /= v ; }
		inline T_Vect2<U> Rot(double ct,double st) { return T_Vect2<U>(ct*X-st*Y,st*X+ct*Y) ; }
		friend inline std::ostream& operator<< (std::ostream& s, const T_Vect2& v) 
		{
			return s << " (" << v.X << " , " << v.Y << ")" ;
		}
} ;

// Specialize the Min/Max templates to work on vectors :

template<class T> T_Vect3<T> VectorMin(const T_Vect3<T> & v1, const T_Vect3<T> & v2)
{
	return T_Vect3<T>(Min(v1.X,v2.X),Min(v1.Y,v2.Y),Min(v1.Z,v2.Z)) ;
}
template<class T> T_Vect3<T> VectorMax(const T_Vect3<T> & v1, const T_Vect3<T> & v2)
{
	return T_Vect3<T>(Max(v1.X,v2.X),Max(v1.Y,v2.Y),Max(v1.Z,v2.Z)) ;
}
template<class T> T_Vect2<T> VectorMin(const T_Vect2<T> & v1, const T_Vect2<T> & v2)
{
	return T_Vect2<T>(Min(v1.X,v2.X),Min(v1.Y,v2.Y)) ;
}
template<class T> T_Vect2<T> VectorMax(const T_Vect2<T> & v1, const T_Vect2<T> & v2)
{
	return T_Vect2<T>(Max(v1.X,v2.X),Max(v1.Y,v2.Y)) ;
}

template<class T> inline T_Vect3<T>::T_Vect3(const T_Vect2<T>& V,T val)
{
	X = V.X ;
	Y = V.Y ;
	Z = val ;
}

template<class T>	inline T T_Vect3<T>::operator*(const NormalizedT_Vect3<T>& v1) const 
{ 
	return X*v1.X+Y*v1.Y+Z*v1.Z ; 
}

#endif
