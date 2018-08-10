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

#include <stdio.h>

#include "GeometryUtils.h"

using namespace std;

//  Calcule l'intersection de la demi-droite [(x+t,y), t>0] avec le
// segment [(x1,y1), (x2,y2)].

bool IntersectDemiDroite(	FLOAT x,FLOAT y, 
							FLOAT P2x,FLOAT P2y,
							FLOAT Q2x,FLOAT Q2y,
							FLOAT I_EPS)
{
	if(fabs(Q2y - P2y) < fabs(I_EPS))
	{
		if((P2y > y+I_EPS)||(P2y < y-I_EPS))
			return false ;

		FLOAT tx = (x - P2x)/(Q2x-P2x) ;
		FLOAT ty = (y - P2x)/(Q2x-P2x) ;

		if( ((tx < -I_EPS)&&(ty < -I_EPS))
		  ||((tx > 1+I_EPS)&&(ty < 1+I_EPS)))
			return false ;

		return true ;
	}

	FLOAT a2 = -(Q2y - P2y) ;
	FLOAT b2 =  (Q2x - P2x) ;
	FLOAT c2 =  P2x*a2+P2y*b2 ;

	FLOAT t2 = (c2 - b2*y-a2*x)/a2 ;

	if(t2 < - I_EPS)
		return false ;

	FLOAT Ix = x+t2 ;
	FLOAT Iy = y ;

	FLOAT t ;

	if(Q2y != P2y)
		t = (Iy - P2y)/(Q2y - P2y) ;
	else if(Q2x != P2x)
		t = (Ix - P2x)/(Q2x - P2x) ;
	else
	{
		printf("IntersectDemiDroite: Warning: null segment\n") ;
		return false ;
	}

	if((t < -I_EPS)||(t > 1+I_EPS))
		return false ;

	return true ;
}

bool IntersectSegments2D(	FLOAT P1x,FLOAT P1y, 
							FLOAT Q1x,FLOAT Q1y, 
							FLOAT P2x,FLOAT P2y, 
							FLOAT Q2x,FLOAT Q2y,
							FLOAT I_EPS,
							Vect2 *I)
{
	FLOAT a2 = -(Q2y - P2y) ;
	FLOAT b2 =  (Q2x - P2x) ;
	FLOAT c2 =  P2x*a2+P2y*b2 ;

	FLOAT a1 = -(Q1y - P1y) ;
	FLOAT b1 =  (Q1x - P1x) ;
	FLOAT c1 =  P1x*a1+P1y*b1 ;

	FLOAT d2 = a2*(Q1x-P1x)+b2*(Q1y-P1y) ;
	FLOAT d1 = a1*(Q2x-P2x)+b1*(Q2y-P2y) ;

	if((fabs(d2) <= I_EPS)||(fabs(d1) <= I_EPS))	// les segments sont paralleles
	{
		if(fabs(a2*P1x + b2*P1y - c2) >= I_EPS)
			return false ;

		FLOAT tP2,tQ2 ;

		if(P2x != Q2x)
		{
			tP2 = (P1x-P2x)/(Q2x-P2x) ;
			tQ2 = (Q1x-P2x)/(Q2x-P2x) ;
		}
		else if(P2y != Q2y)
		{
			tP2 = (P1y-P2y)/(Q2y-P2y) ;
			tQ2 = (Q1y-P2y)/(Q2y-P2y) ;
		}
		else
		{
			printf("IntersectSegments2D:: Error ! One segment has length 0\n") ;
			printf("This special case is not treated yet.\n") ;
			return false ;
		}

		if( ((tP2 < -I_EPS)&&(tQ2 < -I_EPS))
		  ||((tP2 > 1+I_EPS)&&(tQ2 < 1+I_EPS)))
			return false ;

		if(I != NULL)
			*I = Vect2(tP2*(Q1x-P1x)+P1x,tP2*(Q1y-P1y)+P1y) ;

		return true ;
	}
	else
	{
		FLOAT t2 = (c2 - a2*P1x - b2*P1y)/d2 ;
		FLOAT t1 = (c1 - a1*P2x - b1*P2y)/d1 ;

		if((t2 > 1+I_EPS)||(t2 < -I_EPS)||(t1 > 1+I_EPS)||(t1 < -I_EPS))
			return false ;

		if(I != NULL)
			*I = Vect2(t1*(Q2x-P2x)+P2x,t1*(Q2y-P2y)+P2y) ;

		return true ;
	}
}

bool IntersectSegments2D(const Vect3 & P1,const Vect3 & Q1,
						 const Vect3 & P2,const Vect3 & Q2,
						 const FLOAT I_EPS, Vect2 & I)
{
	return IntersectSegments2D(	P1.X,P1.Y,Q1.X,Q1.Y,
								P2.X,P2.Y,Q2.X,Q2.Y,
								I_EPS,&I) ;
}

// Calcule deux vecteurs L et M pour que (L,M,N) doit orthonorme direct.

void MakeCoordinateSystem(Vect3 & L, Vect3 & M, const Vect3 & N)
{
	if((N.X==0.0)&&(N.Y==0.0))
	{
		M = Vect3(0,1,0) ;
	}
	else
		M = Vect3(-N.Y,N.X,0.0) ;

	M.Normalize() ;

	L = M^N ;
}

// Projete un point du plan d'equation Nx-C=0 dans
// un systeme de coordonnees orthonorme (L,M,N) 2D du plan

void ProjectPoint(	const Vect3 & L,const Vect3 & M,const Vect3 & N,
					FLOAT C,const Vect3 & P,FLOAT & X,FLOAT & Y)
{
	Vect3 V = P-C*N ;

	X = V*L ;
	Y = V*M ;
}

PointToPolygonPosition ComparePoint2DToPolygon(FLOAT x,FLOAT y,const FLOAT *SommetsProjetes,int nb,FLOAT I_EPS)
{
	int nbInt = 0 ;

	for(int i=0;i<nb;i++)			//  Regarde si (x,y) est a l'interieur
	{								// ou a l'exterieur du polygone.

		if(IntersectDemiDroite(x,y,SommetsProjetes[2*i],SommetsProjetes[2*i+1],
						 		SommetsProjetes[2*((i+1)%nb)],SommetsProjetes[2*((i+1)%nb)+1],I_EPS))
			nbInt++ ;
	}

	if((nbInt % 2) == 1)
		return Point_INSIDE ;
	else
		return Point_OUTSIDE ;
}

SegmentToPolygonPosition CompareSegmentToPolygon(const Vect3 & P,const Vect3 & Q,const Vect3 & L,const Vect3 & M,const Vect3 & N,FLOAT C,const FLOAT *SommetsProjetes,int nb,Vect3 & Int,FLOAT I_EPS)
{
	FLOAT d = N*Q-N*P ;

	if(fabs(d) <= I_EPS)					// Cas ou [P,Q] est parallele au plan du polygone
	{
		if(fabs(N*P - C) <= I_EPS)			// P et Q sont dans le plan.
		{
			FLOAT Px,Py,Qx,Qy ;

			ProjectPoint(L,M,N,C,P,Px,Py) ;		// Projection de I dans le plan
			PointToPolygonPosition PinPol = ComparePoint2DToPolygon(Px,Py,SommetsProjetes,nb,I_EPS) ;	

			ProjectPoint(L,M,N,C,Q,Qx,Qy) ;		// Projection de I dans le plan
			PointToPolygonPosition QinPol = ComparePoint2DToPolygon(Qx,Qy,SommetsProjetes,nb,I_EPS) ;	

			if((PinPol == Point_INSIDE) && (QinPol == Point_INSIDE)) // [P,Q] est a l'interieur du polygone
				return Segment_PARALLEL_INSIDE ;

			for(int i=0;i<nb;i++)
				if(IntersectSegments2D(Px,Py,Qx,Qy,SommetsProjetes[2*i],SommetsProjetes[2*i+1],
									 SommetsProjetes[2*((i+1)%nb)],SommetsProjetes[2*((i+1)%nb)+1],I_EPS))
					return Segment_PARALLEL_CROSS ;

			return Segment_PARALLEL_OUTSIDE ;
		}
		else
		{
			if(N*P - C > 0.0)			// P et Q sont au dessus
				return Segment_UPPER ;
			else
				return Segment_BELOW ;
		}
	}
	else								// Cas general
	{
		FLOAT t = (C - N*P)/d ;
		Vect3 I = (1-t)*P + t*Q ;		// Point d'intersection
		Int = I ;

		if(t < -I_EPS)
			return Segment_BELOW ;

		if(t > 1+I_EPS)
			return Segment_UPPER ;

		FLOAT x,y ;
		ProjectPoint(L,M,N,C,I,x,y) ;		// Projection de I dans le plan

		PointToPolygonPosition pos = ComparePoint2DToPolygon(x,y,SommetsProjetes,nb,I_EPS) ;

		if(pos == Point_INSIDE)
			return Segment_INTERSECT_INSIDE ;
		else
			return Segment_INTERSECT_OUTSIDE ;
	}
}

