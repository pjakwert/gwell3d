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

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <iostream>

#define DumpCore() { std::cerr << "Dumping core." << std::endl ; ((int *)0x0)[100000] = 10 ; }

#ifndef FLT_MAX
#define FLT_MAX 3.40282347E+38F
#endif
#ifndef FLT_MIN
#define FLT_MIN 1.17549435E-38F
#endif

template<class T> inline const T& Min(const T& a,const T& b) { return (a > b)? b: a ; }
template<class T> inline const T& Max(const T& a,const T& b) { return (b > a)? b: a ; }
template<class T> inline void Exchange(T& a,T& b) { T tmp = a ; a = b ; b = tmp ; }

#endif


