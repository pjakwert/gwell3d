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

#ifndef GEOMETRY_UTILS_H
#define GEOMETRY_UTILS_H

#include "Vects.h"
#define FLOAT double 
#define GLFLOAT GLdouble 
typedef T_Vect3<double> Vect3 ;
typedef T_Vect3<double> DVect3 ;
typedef T_Vect2<double> Vect2 ;

//  Teste si le segment [P2,Q2] et la demi-droite ([x+t,y], t>0) se 
// rencontrent a I_EPS pres.

extern bool IntersectDemiDroite(FLOAT x,FLOAT y,
								FLOAT P2x,FLOAT P2y,
								FLOAT Q2x,FLOAT Q2y,
								FLOAT I_EPS) ;

// Teste si les segments [P1,Q1] et [P2,Q2] se rencontrent a I_EPS pres.

extern bool IntersectSegments2D(FLOAT P1x,FLOAT P1y,
								FLOAT Q1x,FLOAT Q1y,
								FLOAT P2x,FLOAT P2y,
								FLOAT Q2x,FLOAT Q2y,
								FLOAT I_EPS,Vect2* =NULL) ;

extern bool IntersectSegments2D(const Vect3 & P1,const Vect3 & Q1,
								const Vect3 & P2,const Vect3 & Q2,
								const FLOAT I_EPS, Vect2 & I) ;

// Projete un point du plan d'equation Nx-C=0 dans
// le systeme de coordonnees orthonorme (L,M,N) 2D du plan

extern void ProjectPoint(  const Vect3 & L,const Vect3 & M,const Vect3 & N,
							FLOAT C,const Vect3 & P,FLOAT & X,FLOAT & Y) ;

// Calcule deux vecteurs L et M pour que (L,M,N) doit orthonorme direct.

extern void MakeCoordinateSystem(Vect3 & L, Vect3 & M, const Vect3 & N) ;

typedef enum { Point_INSIDE, Point_OUTSIDE } PointToPolygonPosition ;

typedef
enum { 	Segment_PARALLEL_INSIDE, 
		Segment_PARALLEL_OUTSIDE, 
		Segment_PARALLEL_CROSS, 
		Segment_INTERSECT_INSIDE, 
		Segment_INTERSECT_OUTSIDE, 
		Segment_UPPER, 
		Segment_BELOW } SegmentToPolygonPosition ;

extern SegmentToPolygonPosition CompareSegmentToPolygon(const Vect3 & P,
														const Vect3 & Q,
														const Vect3 & L,
														const Vect3 & M,
														const Vect3 & N,
														FLOAT C,
														const FLOAT *SomProj,
														int nb,
														Vect3 &,
														FLOAT I_EPS) ;

#endif
