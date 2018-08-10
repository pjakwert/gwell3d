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

//
// @(#)Classes.h	1.7 7/21/99
//

#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "../config.h"

#include "Liste.h"
#include "GeometryUtils.h"
#include "Functions.h"

class Feedback3Dcolor ;
class Primitive ;

extern double I_EPS ;
// extern void spewSortedFeedback(FILE * file, GLint size, GLFLOAT * buffer, int, int, int DrawMode, int format) ;
extern GLfloat pointSize;
extern void ProduitVect(double,double,double,double,double,double,double&,double&,double&) ;
extern void getsigns(const Vect3,const FLOAT,const Primitive *,int * &,FLOAT * &,int &,int &,FLOAT) ;

#define EPS_SMOOTH_LINE_FACTOR 0.06  /* Lower for better smooth lines. */

extern double LINE_EGALITY_EPS ;
extern double EGALITY_EPS ;
extern double FLAT_POLYGON_EPS ;

class Primitive
{
	public:
		Primitive() ;

		virtual void DrawItem(unsigned char,unsigned char,unsigned char) = 0 ;
		virtual int IsAPolygon() { return 0 ; }

		inline void SetVisibility(int v) { vibility = v ; }
		inline int GetVisibility()  { return vibility ; }

		virtual FLOAT Get_I_EPS(Primitive *) const ;
		virtual Feedback3Dcolor Sommet3Dcolor(int) const =0 ;
		Vect3 VerticalProjectPointOnSupportPlane(const Vect3 &) const ;
		void IntersectPrimitiveWithSupportPlane(Primitive *,int[],FLOAT[],Vect3 *&,Vect3 *&) ;
		virtual Vect3 Vertex(int) const = 0 ;
		virtual int NbVertices() const = 0 ;
		virtual void spew(FILE *,int,int,int) const ;
		const Vect3& Normal() const { return normal ; }
		FLOAT Const() const { return C ; }
		virtual void Split(Vect3,FLOAT,Primitive * &,Primitive * &) = 0 ;

		inline FLOAT Equation(const Vect3& p) { return p*normal-C ; }
		void GetSigns(Primitive *,int * &,FLOAT * &,int &,int &,FLOAT) ;

	protected:
		virtual void spewEPS(FILE *,int) const = 0 ;
		virtual void spewFIG(FILE *,int,int) const = 0 ;
		virtual void InitNormal() = 0 ;

		int vibility ;
		FLOAT C ;
		Vect3 normal ;
} ;

class Feedback3Dcolor: public Primitive 
{
    public:
		virtual void DrawItem(unsigned char,unsigned char,unsigned char) ;

		Feedback3Dcolor(): x(0.0), y(0.0), z(0.0), red(0.0), green(0.0), blue(0.0), alpha(0.0) {}
		Feedback3Dcolor(float _x, float _y, float _z, float _r, float _g, float _b, float _a)
			:x(_x), y(_y), z(_z), red(_r), green(_g), blue(_b), alpha(_a) 
			{ InitNormal() ; }

		Feedback3Dcolor(GLfloat *loc)
		{
			x = loc[0] ;
			y = loc[1] ;
			z = loc[2] ;
			red   = loc[3] ;
			green = loc[4] ;
			blue  = loc[5] ;
			alpha = loc[6] ;

			InitNormal() ;
		}

		virtual Feedback3Dcolor Sommet3Dcolor(int) const { return *this ; }
		virtual void Split(Vect3,FLOAT,Primitive * &,Primitive * &) ;
		FLOAT X() const { return x ; }
		FLOAT Y() const { return y ; }
		FLOAT Z() const { return z ; }
		FLOAT Red() const { return red ; }
		FLOAT Green() const { return green ; }
		FLOAT Blue() const { return blue ; }
		FLOAT Alpha() const { return alpha ; }

		inline Feedback3Dcolor operator+(const Feedback3Dcolor & v) const 
		{ 
			return Feedback3Dcolor(x+v.x,y+v.y,z+v.z,red+v.red,green+v.green,blue+v.blue,alpha+v.alpha) ;
		}
		inline Feedback3Dcolor operator*(const FLOAT & f) const 
		{ 
			return Feedback3Dcolor(x*f,y*f,z*f,red*f,green*f,blue*f,alpha*f) ;
		}

		virtual Vect3 Vertex(int) const ;
		operator Vect3() const { return Vect3(x,y,z) ; }
		virtual int NbVertices() const ;
		virtual void InitNormal() ;

	protected:
		virtual void spewEPS(FILE *,int) const ;
		virtual void spewFIG(FILE *,int,int) const ;
		GLFLOAT x;
		GLFLOAT y;
		GLFLOAT z;
		GLFLOAT red;
		GLFLOAT green;
		GLFLOAT blue;
		GLFLOAT alpha;
} ;

class Segment: public Primitive
{
	public:
		Segment(const Feedback3Dcolor & p1, const Feedback3Dcolor & p2): P1(p1), P2(p2) { InitNormal() ; } 

		virtual void DrawItem(unsigned char,unsigned char,unsigned char) ;
		virtual int NbVertices() const ;
		virtual Vect3 Vertex(int) const ;
		virtual Feedback3Dcolor Sommet3Dcolor(int i) const 
		{ 
#ifdef DEBUGEPSRENDER
			if((i < 0)||(i > 1))
				std::cout << "Unexpected sommet ID : " << i << "in Segment::Sommet3DColor." << std::endl ;
#endif
			return (i==1)?P2:P1 ; 
		}
		virtual void Split(Vect3,FLOAT,Primitive * &,Primitive * &) ;
		virtual void InitNormal() ;

		Feedback3Dcolor P1 ;
		Feedback3Dcolor P2 ;

	protected:
		virtual void spewEPS(FILE *,int) const ;
		virtual void spewFIG(FILE *,int,int) const ;
} ;

class ListeDePoints
{
	public:
		ListeDePoints(Feedback3Dcolor *P, ListeDePoints *L): cour(P), suiv(L) {}

		Feedback3Dcolor *cour ;
		ListeDePoints *suiv ;
} ;

class ListeDeSegments
{
	public:
		ListeDeSegments(Segment *S, ListeDeSegments *L): cour(S), suiv(L) {}

		Segment *cour ;
		ListeDeSegments *suiv ;
} ;

class Polygone: public Primitive
{
	public:
		Polygone(GLfloat *,int) ;
		Polygone(Feedback3Dcolor [],int) ;
		virtual ~Polygone() ;

		virtual void DrawItem(unsigned char,unsigned char,unsigned char) ;
		virtual int IsAPolygon() { return 1 ; }

		virtual void Split(Vect3,FLOAT,Primitive * &,Primitive * &) ;
		Feedback3Dcolor Sommet3Dcolor(int) const ;
		virtual Vect3 Vertex(int) const ;
		virtual int NbVertices() const { return nVertex ; }
		void InitEquation(double &,double &,double &,double &) ;
		FLOAT FlatFactor() const { return anglefactor ; }

	protected:
		virtual void spewEPS(FILE *,int) const ;
		virtual void spewFIG(FILE *,int,int) const ;
#ifdef A_VIRER
		void AddVertex(Feedback3Dcolor) ;
		int nbmaxvertex ;
#endif
		virtual void InitNormal() ;
		void CheckInfoForPositionOperators() ;

		Feedback3Dcolor *vertices ;
		FLOAT *SommetsProjetes ;
		Vect3 N,M,L ;
		FLOAT anglefactor ;		//  Determine a quel point un polygone est plat. 
										// Comparer a FLAT_POLYGON_EPS
		int nVertex ;
} ;

class OrderingStructure
{
	public:
		OrderingStructure(): zSize(1.0) {} 

		virtual void Insert(Polygone *) = 0 ;
		virtual void Insert(Segment *) = 0 ;
		virtual void Insert(Feedback3Dcolor *) = 0 ;

		virtual void Render(FILE *, int,int) = 0 ;

		virtual void GetPrimitiveTab(Primitive ** &, long int &) const = 0 ;

		void SetZDepth(FLOAT s) { zSize = s ; }
		FLOAT ZDepth() const { return zSize ; }

	protected:
		FLOAT zSize ;
} ;

class DontSortStructure: public OrderingStructure
{
	public:
		DontSortStructure() ;

		virtual void Insert(Polygone *) ;
		virtual void Insert(Segment *) ;
		virtual void Insert(Feedback3Dcolor *) ;

		virtual void Render(FILE *, int,int) ;

		virtual void GetPrimitiveTab(Primitive ** &, long int &) const ;

	protected:
		void InsertPrimitive(Primitive *) ;

		Liste<Primitive *> *liste_objets ;
		int nb_obj ;
		Liste<Primitive *> *end_list ;
} ;

#endif

