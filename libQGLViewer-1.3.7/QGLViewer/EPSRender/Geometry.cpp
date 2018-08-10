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

#include "stdlib.h"
#include "Geometry.h"
#include "Affichage.h"

using namespace std;

Primitive::Primitive()
	: normal(0.0,0.0,0.0)
{
	vibility = 1 ;
	C = 0 ;
}

FLOAT Primitive::Get_I_EPS(Primitive *P) const
{
	if((P->NbVertices() > 2)&&(NbVertices() > 2))
		return -I_EPS ;

	if(P->NbVertices() == NbVertices())
		return -I_EPS ;
	else
		return I_EPS ;
}

Vect3 Primitive::VerticalProjectPointOnSupportPlane(const Vect3 & P) const
{
	if(Normal().Z == 0.0)
		return Vect3(P.X,P.Y,-FLT_MAX) ;
	else
		return Vect3(P.X,P.Y,(C - Normal().X*P.X - Normal().Y*P.Y)/Normal().Z) ;
}

void Feedback3Dcolor::DrawItem(unsigned char R,unsigned char G,unsigned char B)
{
	glColor3ub(R,G,B) ;

	glBegin(GL_POINTS) ;
	glVertex3f(x,y,-z) ;
	glEnd() ;
}

void Segment::InitNormal()
{
	// look for an orthogonal vector
	Vect3 dir(-(P2.Y()-P1.Y()),P2.X()-P1.X(),0.0) ;

	if(dir.NormInf() == 0.0)
	{
		double t = 2.0 * M_PI * rand() / RAND_MAX;// any vector in z=0 plane is ok
		dir = Vect3(cos(t),sin(t),0.0) ;			// let's put some random here.
	}
	else
		dir.Normalize() ;				// normalize it

	//  Using the following schemes instead of normal=dir
	// avoids getting normal.Z = 0.0, which produces bugs. However, when
	// normal.Z=0.0, we should turn the segment into a point.

	normal = dir ^ ((Vect3)P2 - (Vect3)P1) ;

	if(normal.NormInf() == 0.0)
		normal = Vect3(0.0,0.0,1.0) ;

	if(normal.Z < 0.0)
		normal *= -1.0 ;

	normal.Normalize() ;
	C = normal*P1 ;
}

void Segment::DrawItem(unsigned char R,unsigned char G,unsigned char B)
{
	glColor3ub(R,G,B) ;

	glBegin(GL_LINES) ;

	glVertex3f(P1.X(),P1.Y(),-P1.Z()) ;
	glVertex3f(P2.X(),P2.Y(),-P2.Z()) ;

	glEnd() ;
}

int Segment::NbVertices() const
{
	return 2 ;
}

Vect3 Segment::Vertex(int i) const
{
	if(i == 0)
		return Vect3(P1.X(),P1.Y(),P1.Z()) ;

	if(i == 1)
		return Vect3(P2.X(),P2.Y(),P2.Z()) ;

	fprintf(stderr,"Segment::Vertex: inconsistency error !\n") ;
	return Vect3(P1.X(),P1.Y(),P1.Z()) ;
}

int Feedback3Dcolor::NbVertices() const
{
	return 1 ;
}

Vect3 Feedback3Dcolor::Vertex(int i) const
{
	if(i != 0)
		fprintf(stderr,"Feedback3Dcolor::Vertex: inconsistency error !\n") ;

	return Vect3(x,y,z) ;
}

Vect3 Polygone::Vertex(int i) const
{
	return Vect3(vertices[i].X(),vertices[i].Y(),vertices[i].Z()) ;
}

void Polygone::DrawItem(unsigned char R,unsigned char G,unsigned char B)
{
	glColor3ub(R,G,B) ;

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL) ;

	glBegin(GL_POLYGON) ;

	for(int i=0;i<nVertex;i++)
		glVertex3f(vertices[i].X(),vertices[i].Y(),-vertices[i].Z()) ;

	glEnd() ;
}

void ProduitVect(double x1, double y1, double z1, 
				double x2, double y2, double z2, 
				double &x, double &y, double &z)
{
    x = y1*z2 - y2*z1 ;
    y = z1*x2 - z2*x1 ;
    z = x1*y2 - x2*y1 ;
}

Feedback3Dcolor Polygone::Sommet3Dcolor(int id) const { return vertices[id] ; }

Polygone::~Polygone()
{
	if(SommetsProjetes != NULL)
		delete[] SommetsProjetes ;
	if(vertices != NULL)
		delete[] vertices ;
}

Polygone::Polygone(Feedback3Dcolor v[],int nv)
	: N(0.0,0.0,0.0),M(0.0,0.0,0.0),L(0.0,0.0,0.0)
{
	SommetsProjetes = NULL ;
	vertices = new Feedback3Dcolor[nv] ;
	nVertex = nv ;
	anglefactor = 0.0 ;

	for(int i=0;i<nVertex;i++)
		vertices[i] = v[i] ;

	InitNormal() ;
}

Polygone::Polygone(GLfloat *loc,int nv)
	: N(0.0,0.0,0.0),M(0.0,0.0,0.0),L(0.0,0.0,0.0)
{
	SommetsProjetes = NULL ;
	vertices = new Feedback3Dcolor[nv] ;
	nVertex = nv ;
	anglefactor = 0.0 ;

	for(int i=0;i<nVertex;i++)
		vertices[i] = Feedback3Dcolor(loc+7*i) ;

	InitNormal() ;
}

#ifdef A_VIRER
void Polygone::AddVertex(Feedback3Dcolor Pt)
{
	vertices[nVertex] = Pt ;
	nVertex++ ;

	if(nVertex >= nbmaxvertex)
	{
		Feedback3Dcolor *v2 = new Feedback3Dcolor[2*nbmaxvertex] ;
		
		for(int i=0;i<nbmaxvertex;i++)
			v2[i] = vertices[i] ;

		Feedback3Dcolor *tmp = vertices ;

		vertices = v2 ;

		delete[] tmp ;
		nbmaxvertex *= 2 ;
	}
}
#endif

void Primitive::spew(FILE *f,int drm,int format,int depth) const
{
	if(format == FORMAT_EPS)
		spewEPS(f,drm) ;
	else
		spewFIG(f,drm,depth) ;
}

void Polygone::InitEquation(double & a, double & b, double & c, double & d)
{
	a = 0.0 ;
	b = 0.0 ;
	c = 0.0 ;

	int j = 0 ;

	while( (j < nVertex)&&(a==0.0)&&(b==0.0)&&(c==0.0) )
	{
		ProduitVect(Vertex((j+2)%nVertex).X - Vertex((j+1)%nVertex).X,
					Vertex((j+2)%nVertex).Y - Vertex((j+1)%nVertex).Y,
					Vertex((j+2)%nVertex).Z - Vertex((j+1)%nVertex).Z,
					Vertex(j).X - Vertex((j+1)%nVertex).X,
					Vertex(j).Y - Vertex((j+1)%nVertex).Y,
					Vertex(j).Z - Vertex((j+1)%nVertex).Z,
					a,b,c) ;
		j++ ;
	}

	if((a==0.0)&&(b==0.0)&&(c==0.0))
	{
		int ind = nVertex ;

		for(int i=0;i<nVertex;i++)
			if((Vertex(i).X != Vertex((i+1)%nVertex).X)
			 ||(Vertex(i).Y != Vertex((i+1)%nVertex).Y)
			 ||(Vertex(i).Z != Vertex((i+1)%nVertex).Z))
			{
				ind = i ;
				i = nVertex ;
			}

		if(ind < nVertex)	// the polygon is a true segment
		{
			if((Vertex((ind+1)%nVertex).X != Vertex(ind).X)
			 ||(Vertex((ind+1)%nVertex).Y != Vertex(ind).Y))
			{
				a = - Vertex((ind+1)%nVertex).Y + Vertex(ind).Y ;
				b =   Vertex((ind+1)%nVertex).X - Vertex(ind).X ;
				c =   0 ;
			}
			else
			{
				a = - Vertex((ind+1)%nVertex).Z + Vertex(ind).Z ;
				b =   0 ;
				c =   Vertex((ind+1)%nVertex).X - Vertex(ind).X ;
			}
		}
		else				// the polygon is a point
		{
			a = 1.0 ;
			b = 0.0 ;
			c = 0.0 ;
		}
	}

	double D = sqrt(a*a+b*b+c*c) ;

	if(c < 0.0)
	{
		a = -a/D ;
		b = -b/D ;
		c = -c/D ;
	}
	else
	{
		a = a/D ;
		b = b/D ;
		c = c/D ;
	}

	d = a * Vertex(0).X + b * Vertex(0).Y + c * Vertex(0).Z ;
}

void getsigns(const Vect3 v,const FLOAT C,const Primitive *P,int * & signs,FLOAT * & zvals,int & Smin,int & Smax,FLOAT I_EPS)
{
	static int Signs[100] ;
	static FLOAT Zvals[100] ;

	if(P == NULL)
	{
		printf("Primitive::GetSigns: Error. Null primitive.\n") ;
		return ;
	}

	int n = P->NbVertices() ;

	Smin = 1 ;
	Smax = -1 ;

	// On classe les sommets en fonction de leur signe

	FLOAT zmax = -FLT_MAX ;
	FLOAT zmin = FLT_MAX ;

	for(int i=0;i<n;i++)
	{
		double Z = P->Vertex(i) * v - C ;

		if(Z > zmax) zmax = Z ;
		if(Z < zmin) zmin = Z ;

		Zvals[i] = Z ;
	}

	for(int j=0;j<n;j++)
	{
		if(Zvals[j] < -I_EPS)
			Signs[j] = -1 ;
		else if(Zvals[j] > I_EPS)
			Signs[j] = 1 ;
		else 
			Signs[j] = 0 ;

		if(Smin > Signs[j]) Smin = Signs[j] ;
		if(Smax < Signs[j]) Smax = Signs[j] ;
	}

	signs = Signs ;
	zvals = Zvals ;
}

void Polygone::Split(Vect3 v,FLOAT C,Primitive * & P_plus,Primitive * & P_moins) 
{
	int *Signs ;
	FLOAT *Zvals ;

	P_plus = NULL ;
	P_moins = NULL ;

	int Smin = 1 ;
	int Smax = -1 ;

	getsigns(v,C,this,Signs,Zvals,Smin,Smax,0.0) ;

	int n = NbVertices() ;

	if((Smin == 0)&&(Smax == 0)) 	{ P_moins = this ; P_plus = NULL ; return ; }	// Polygone inclus dans le plan
	if(Smin == 1) 					{ P_plus = this ; P_moins = NULL ; return ; }	// Polygone tout positif
	if(Smax == -1) 					{ P_plus = NULL ; P_moins = this ; return ; }	// Polygone tout negatif

	if((Smin == -1)&&(Smax == 0)) { P_plus = NULL ; P_moins = this ; return ; }	// Polygone tout negatif ou null
	if((Smin == 0)&&(Smax == 1))  { P_plus = this ; P_moins = NULL ; return ; }	// Polygone tout positif ou null

	// Reste le cas Smin = -1 et Smax = 1. Il faut couper

	static Feedback3Dcolor Ps[100] ;
	static Feedback3Dcolor Ms[100] ;

	int nPs = 0 ;
	int nMs = 0 ;

	// On teste la coherence des signes.

	int nZero = 0 ;
	int nconsZero = 0 ;
	
	for(int i=0;i<n;i++)
	{
		if(Signs[i] == 0)
		{
			nZero++ ;
			
			if(Signs[(i+1)%n] == 0)
				nconsZero++ ;
		}
	}

	// Ils y a des imprecisions numeriques dues au fait que le poly estpres du plan.
	if((nZero > 2)||(nconsZero > 0)) { P_moins = this ; P_plus  = NULL ; return ; }

	int dep=0 ; while(Signs[dep] == 0) dep++ ;
	int prev_sign = Signs[dep] ;

	for(int j=1;j<=n;j++)
	{
		int sign = Signs[(j+dep)%n] ;

		if(sign == prev_sign)
		{
			if(sign ==  1) Ps[nPs++] = Sommet3Dcolor((j+dep)%n) ;
			if(sign == -1) Ms[nMs++] = Sommet3Dcolor((j+dep)%n) ;
		}
		else if(sign == -prev_sign)
		{
			//  Il faut effectuer le calcul en utilisant les memes valeurs que pour le calcul des signes,
			// sinon on risque des incoherences dues aux imprecisions numeriques.

			double Z1 = Zvals[((j+dep)-1)%n] ;
			double Z2 = Zvals[(j+dep)%n] ;

			double t = fabs(Z1/(Z2 - Z1)) ;

			if((t < 0.0)||(t > 1.0))
			{
				if(t > 1.0) t = 1.0 ;
				if(t < 0.0) t = 0.0 ;
			}

			double x = (1-t) * Vertex(((j+dep)-1)%n).X + t * Vertex((j+dep)%n).X ;
			double y = (1-t) * Vertex(((j+dep)-1)%n).Y + t * Vertex((j+dep)%n).Y ;
			double z = (1-t) * Vertex(((j+dep)-1)%n).Z + t * Vertex((j+dep)%n).Z ;

			double red   = (1-t)*Sommet3Dcolor(((j+dep)-1)%n).Red()  + t*Sommet3Dcolor((j+dep)%n).Red()   ;
			double green = (1-t)*Sommet3Dcolor(((j+dep)-1)%n).Green()+ t*Sommet3Dcolor((j+dep)%n).Green() ;
			double blue  = (1-t)*Sommet3Dcolor(((j+dep)-1)%n).Blue() + t*Sommet3Dcolor((j+dep)%n).Blue()  ;
			double alpha = (1-t)*Sommet3Dcolor(((j+dep)-1)%n).Alpha()+ t*Sommet3Dcolor((j+dep)%n).Alpha() ;

			Feedback3Dcolor newVertex(x,y,z,red,green,blue,alpha) ;

			Ps[nPs++] = newVertex ;
			Ms[nMs++] = newVertex ;

			if(sign == 1)
				Ps[nPs++] = Sommet3Dcolor((j+dep)%n) ;

			if(sign == -1)
				Ms[nMs++] = Sommet3Dcolor((j+dep)%n) ;

			prev_sign = sign ;
		} // prev_sign != 0 donc necessairement sign = 0. Le sommet tombe dans le plan
		else 
		{
			Feedback3Dcolor newVertex = Sommet3Dcolor((j+dep)%n) ;

			Ps[nPs++] = newVertex ;
			Ms[nMs++] = newVertex ;

			prev_sign = -prev_sign ;
		}
	}

	if((nPs > 100)||(nMs > 100)) printf("Primitive::Split: Error. nPs = %d, nMs = %d.\n",nPs,nMs) ;
	
	// on suppose pour l'instant que les polygones sont convexes

	if(nPs == 1)
		P_plus = new Feedback3Dcolor(Ps[0]) ;
	else if(nPs == 2)
		P_plus = new Segment(Ps[0],Ps[1]) ;
	else
		P_plus  = new Polygone(Ps,nPs) ;

	if(nMs == 1)
		P_moins = new Feedback3Dcolor(Ms[0]) ;
	else if(nPs == 2)
		P_moins = new Segment(Ms[0],Ms[1]) ;
	else
		P_moins = new Polygone(Ms,nMs) ;
}

void Feedback3Dcolor::Split(Vect3 v,FLOAT C,Primitive * & P_plus,Primitive * & P_moins)
{
	if(v*Vect3(*this)-C > 0.0)
	{
		P_plus = new Feedback3Dcolor(*this) ;
		P_moins = NULL ;
	}
	else
	{
		P_moins = new Feedback3Dcolor(*this) ;
		P_plus = NULL ;
	}
}

void Segment::Split(Vect3 v,FLOAT C,Primitive * & P_plus,Primitive * & P_moins) 
{
	int *Signs ;
	FLOAT *Zvals ;

	P_plus = NULL ;
	P_moins = NULL ;

	int Smin = 1 ;
	int Smax = -1 ;

	getsigns(v,C,this,Signs,Zvals,Smin,Smax,0.0) ;

	int n = NbVertices() ;

	if((Smin == 0)&&(Smax == 0)) 	{ P_moins = this ; P_plus = NULL ; return ; }	// Polygone inclus dans le plan
	if(Smin == 1) 					{ P_plus = this ; P_moins = NULL ; return ; }	// Polygone tout positif
	if(Smax == -1) 					{ P_plus = NULL ; P_moins = this ; return ; }	// Polygone tout negatif

	if((Smin == -1)&&(Smax == 0)) { P_plus = NULL ; P_moins = this ; return ; }	// Polygone tout negatif ou null
	if((Smin == 0)&&(Smax == 1))  { P_plus = this ; P_moins = NULL ; return ; }	// Polygone tout positif ou null

	// Reste le cas Smin = -1 et Smax = 1. Il faut couper
	// On teste la coherence des signes.

	int nZero = 0 ;
	int nconsZero = 0 ;
	
	for(int i=0;i<n;i++)
	{
		if(Signs[i] == 0)
		{
			nZero++ ;
			
			if(Signs[(i+1)%n] == 0)
				nconsZero++ ;
		}
	}

	// Ils y a des imprecisions numeriques dues au fait que le poly estpres du plan.
	if((nZero > 2)||(nconsZero > 0)) { P_moins = this ; P_plus  = NULL ; return ; }

	double Z1 = Zvals[0] ;
	double Z2 = Zvals[1] ;

	double t = fabs(Z1/(Z2 - Z1)) ;

	if((t < 0.0)||(t > 1.0))
	{
		if(t > 1.0) t = 1.0 ;
		if(t < 0.0) t = 0.0 ;
	}

	Feedback3Dcolor newVertex = Sommet3Dcolor(0) * (1-t) + Sommet3Dcolor(1) * t ;

	if(Signs[0] < 0)
	{
		P_plus = new Segment(newVertex,Sommet3Dcolor(1)) ;
		P_moins = new Segment(Sommet3Dcolor(0),newVertex) ;
	}
	else
	{
		P_moins = new Segment(newVertex,Sommet3Dcolor(1)) ;
		P_plus = new Segment(Sommet3Dcolor(0),newVertex) ;
	}
}

DontSortStructure::DontSortStructure()
{
	liste_objets = NULL ;
	end_list = liste_objets ;
	nb_obj = 0 ;
}

void DontSortStructure::GetPrimitiveTab(Primitive ** & T, long int & s) const
{
	s = nb_obj ;

	T = new Primitive *[nb_obj] ;
	Liste<Primitive *> *cour = liste_objets ;
	int i=0 ;

	while(cour != NULL)
	{
		T[i++] = cour->Cour() ;
		cour = cour->Suiv() ;
	}
}

void DontSortStructure::Insert(Segment *P) 			{ InsertPrimitive(P) ; }
void DontSortStructure::Insert(Feedback3Dcolor *P) { InsertPrimitive(P) ; }
void DontSortStructure::Insert(Polygone *P) 			{ InsertPrimitive(P) ; }

// Insertion a la fin de la liste pour garder l'ordre des primitives !
//
void DontSortStructure::InsertPrimitive(Primitive *P)
{
	Liste<Primitive *> *new_node = new Liste<Primitive *>(P,NULL) ;

	if(end_list == NULL)
		liste_objets = new_node ;
	else
		end_list->SetSuiv(new_node) ;

	end_list = new_node ;

	nb_obj++ ;
}

void DontSortStructure::Render(FILE *f, int drmode,int format) 
{
	Liste<Primitive *> *cour = liste_objets ;
	int depth = 1 ;

	while(cour != NULL)
	{
		cour->Cour()->spew(f,drmode,format,depth) ;
		cour = cour->Suiv() ;
	}
}
