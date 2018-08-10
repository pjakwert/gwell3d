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
// @(#)Classes.C	1.12 7/21/99
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#include "Geometry.h"
#include "Affichage.h"
#include "GeometryUtils.h"
#include "EPSRender.h"
#include "BSPTree.h"

using namespace std;

double EGALITY_EPS 		= 0.0001 ;
double LINE_EGALITY_EPS = 0.0001 ;

const int min_depth = 2 ;

//----------------------------------------------------------------------------//

void DescendreSegPts(BSPNode *fils, ListeDeSegments *Ls, ListeDePoints *Lp)
{
	ListeDeSegments *L = Ls ;

	while(L != NULL)
	{
		fils->Insert(L->cour) ;
		L = L->suiv ;
	}

	ListeDePoints *M = Lp ;

	while(M != NULL)
	{
		fils->Insert(M->cour) ;
		M = M->suiv ;
	}
}

//----------------------------------------------------------------------------//

void deleteAllList(ListeDeSegments *S)
{
	if(S != NULL)
	{
		deleteAllList(S->suiv) ;
		delete S ;
	}
}

void CompleteDeleteAllList(ListeDeSegments *S)
{
	if(S != NULL)
	{
		CompleteDeleteAllList(S->suiv) ;
		delete S->cour ;
		delete S ;
	}
}

void deleteAllList(ListeDePoints *S)
{
	if(S != NULL)
	{
		deleteAllList(S->suiv) ;
		delete S ;
	}
}

void CompleteDeleteAllList(ListeDePoints *S)
{
	if(S != NULL)
	{
		CompleteDeleteAllList(S->suiv) ;
		delete S->cour ;
		delete S ;
	}
}

//----------------------------------------------------------------------------//

void BSPNode::RecursDelete()
{
	if(polygone != NULL)
		delete polygone ;

	CompleteDeleteAllList(seg_plus) ;
	CompleteDeleteAllList(seg_moins) ;
	CompleteDeleteAllList(pts_plus) ;
	CompleteDeleteAllList(pts_moins) ;

	if(fils_moins != NULL)
	{
		fils_moins->RecursDelete() ;
		delete fils_moins ;
	}

	if(fils_plus != NULL)
	{
		fils_plus->RecursDelete() ;
		delete fils_plus ;
	}
}

int BSPNode::Classify(Feedback3Dcolor *P)
{
	double Z = P->X() * a + P->Y() * b + P->Z() * c - d ;

	if(Z > EGALITY_EPS)
		return 1 ;
	else
		return -1 ;
}

void BSPNode::Classify(Segment *S, Segment * & moins_, Segment * & plus_)
{
	double Z1 = S->P1.X() * a + S->P1.Y() * b + S->P1.Z() * c - d ;
	double Z2 = S->P2.X() * a + S->P2.Y() * b + S->P2.Z() * c - d ;

	int s1, s2 ;

	if(Z1 < -LINE_EGALITY_EPS)
		s1 = -1 ;
	else if(Z1 > EGALITY_EPS)
		s1 = 1 ;
	else 
		s1 = 0 ;

	if(Z2 < -LINE_EGALITY_EPS)
		s2 = -1 ;
	else if(Z2 > EGALITY_EPS)
		s2 = 1 ;
	else 
		s2 = 0 ;

	if(s1 == -s2)
	{
		if(s1 == 0)
		{
			moins_ = S ;
			plus_  = NULL ;
			return ;
		}
		else
		{
			double t = fabs(Z1/(Z2 - Z1)) ;

			if((t < 0.0)||(t > 1.0))
			{
#ifdef DEBUGEPSRENDER
//				printf("BSPNode::Classify Segment: Error. Incorrect value t=%1.5lf\n",t) ;
#endif

				if(t > 1.0) t = 0.999 ;
				if(t < 0.0) t = 0.001 ;
			}

			double x = (1-t) * S->P1.X() + t * S->P2.X() ;
			double y = (1-t) * S->P1.Y() + t * S->P2.Y() ;
			double z = (1-t) * S->P1.Z() + t * S->P2.Z() ;

			double red   = (1-t) * S->P1.Red()   + t * S->P2.Red()   ;
			double green = (1-t) * S->P1.Green() + t * S->P2.Green() ;
			double blue  = (1-t) * S->P1.Blue()  + t * S->P2.Blue()  ;
			double alpha = (1-t) * S->P1.Alpha() + t * S->P2.Alpha() ;

			Feedback3Dcolor newVertex(x,y,z,red,green,blue,alpha) ;

			if(s1 > 0)
			{
				plus_  = new Segment(S->P1, newVertex) ;
				moins_ = new Segment(newVertex, S->P2) ;
			}
			else
			{
				plus_  = new Segment(newVertex, S->P2) ;
				moins_ = new Segment(S->P1, newVertex) ;
			}

			delete S ;
			return ;
		}
	}
	else if(s1 == s2)
	{
		if(s1 == -1)
		{
			moins_ = S ;
			plus_ = NULL ;
			return ;
		}
		else
		{
			moins_ = NULL ;
			plus_  = S ;
			return ;
		}
	}
	else if(s1 == 0)
	{
		if(s2 > 0)
		{
			moins_ = NULL ;
			plus_  = S ;
			return ;
		}
		else
		{
			moins_ = S ;
			plus_  = NULL ;
			return ;
		}
	}
	else if(s2 == 0)
	{
		if(s1 > 0)
		{
			moins_ = NULL ;
			plus_  = S ;
			return ;
		}
		else
		{
			moins_ = S ;
			plus_  = NULL ;
			return ;
		}
	}
	else
		printf("BSPNode::Classify: unexpected classification case !!\n") ;
}

void BSPNode::Classify(Polygone *P, Polygone * & moins_, Polygone * & plus_)
{
	static int Signs[100] ;
	static double Zvals[100] ;

	moins_ = NULL ;
	plus_ = NULL ;

	if(P == NULL)
	{
		printf("BSPNode::Classify: Error. Null polygon.\n") ;
		return ;
	}

	int n = P->NbVertices() ;

	int Smin = 1 ;
	int Smax = -1 ;

	// On classe les sommets en fonction de leur signe

	for(int i=0;i<n;i++)
	{
		double Z = P->Vertex(i).X * a + P->Vertex(i).Y * b + P->Vertex(i).Z * c - d ;

		if(Z < -EGALITY_EPS)
			Signs[i] = -1 ;
		else if(Z > EGALITY_EPS)
			Signs[i] = 1 ;
		else 
			Signs[i] = 0 ;
			
		Zvals[i] = Z ;

		if(Smin > Signs[i]) Smin = Signs[i] ;
		if(Smax < Signs[i]) Smax = Signs[i] ;
	}

	// Polygone inclus dans le plan

	if((Smin == 0)&&(Smax == 0))
	{
		moins_ = P ;
		plus_  = NULL ;
		return ;
	}
	
	// Polygone tout positif

	if(Smin == 1)
	{
		plus_  = P ;
		moins_ = NULL ;
		return ;
	}

	// Polygone tout negatif
	
	if(Smax == -1) 
	{
		plus_ = NULL ;
		moins_ = P ;
		return ;
	}

	if((Smin == -1)&&(Smax == 0))
	{
		plus_ = NULL ;
		moins_ = P ;
		return ;
	}

	if((Smin == 0)&&(Smax == 1))
	{
		plus_ = P ;
		moins_ = NULL ;
		return ;
	}

	// Reste le cas Smin = -1 et Smax = 1. Il faut couper

	static Feedback3Dcolor Ps[100] ;
	static Feedback3Dcolor Ms[100] ;

	int nPs = 0 ;
	int nMs = 0 ;

	// On teste la coherence des signes.

	int nZero = 0 ;
	int nconsZero = 0 ;
	
	for(int j=0;j<n;j++)
	{
		if(Signs[j] == 0)
		{
			nZero++ ;
			
			if(Signs[(j+1)%n] == 0)
				nconsZero++ ;
		}
	}

	if((nZero > 2)||(nconsZero > 0))
	{
		// Ils y a des imprecisions numeriques dues au fait que le poly estpres du plan.

		moins_ = P ;
		plus_  = NULL ;
		return ;
	}

	int dep=0 ;

	while(Signs[dep] == 0) dep++ ;

	int prev_sign = Signs[dep] ;

	for(int k=1;k<=n;k++)
	{
		int sign = Signs[(k+dep)%n] ;

		if(sign == prev_sign)
		{
			if(sign == 1)
				Ps[nPs++] = P->Sommet3Dcolor((k+dep)%n) ;

			if(sign == -1)
				Ms[nMs++] = P->Sommet3Dcolor((k+dep)%n) ;
		}
		else if(sign == -prev_sign)
		{
			//  Il faut effectuer le calcul en utilisant les memes valeurs que pour le calcul des signes,
			// sinon on risque des incoherences dues aux imprecisions numeriques.

			double Z1 = Zvals[((k+dep)-1)%n] ;
			double Z2 = Zvals[(k+dep)%n] ;

			double t = fabs(Z1/(Z2 - Z1)) ;

			if((t < 0.0)||(t > 1.0))
			{
				if(t > 1.0) t = 0.999 ;
				if(t < 0.0) t = 0.001 ;
			}

			double x = (1-t) * P->Vertex(((k+dep)-1)%n).X + t * P->Vertex((k+dep)%n).X ;
			double y = (1-t) * P->Vertex(((k+dep)-1)%n).Y + t * P->Vertex((k+dep)%n).Y ;
			double z = (1-t) * P->Vertex(((k+dep)-1)%n).Z + t * P->Vertex((k+dep)%n).Z ;

			double red   = (1-t) * P->Sommet3Dcolor(((k+dep)-1)%n).Red()   + t * P->Sommet3Dcolor((k+dep)%n).Red()   ;
			double green = (1-t) * P->Sommet3Dcolor(((k+dep)-1)%n).Green() + t * P->Sommet3Dcolor((k+dep)%n).Green() ;
			double blue  = (1-t) * P->Sommet3Dcolor(((k+dep)-1)%n).Blue()  + t * P->Sommet3Dcolor((k+dep)%n).Blue()  ;
			double alpha = (1-t) * P->Sommet3Dcolor(((k+dep)-1)%n).Alpha() + t * P->Sommet3Dcolor((k+dep)%n).Alpha() ;

			Feedback3Dcolor newVertex(x,y,z,red,green,blue,alpha) ;

			Ps[nPs++] = newVertex ;
			Ms[nMs++] = newVertex ;

			if(sign == 1)
				Ps[nPs++] = P->Sommet3Dcolor((k+dep)%n) ;

			if(sign == -1)
				Ms[nMs++] = P->Sommet3Dcolor((k+dep)%n) ;

			prev_sign = sign ;
		} // prev_sign != 0 donc necessairement sign = 0. Le sommet tombe dans le plan
		else 
		{
			Feedback3Dcolor newVertex = P->Sommet3Dcolor((k+dep)%n) ;

			Ps[nPs++] = newVertex ;
			Ms[nMs++] = newVertex ;

			prev_sign = -prev_sign ;
		}
	}

	if((nPs > 100)||(nMs > 100))
		printf("BSPNode::Classify: Error. nPs = %d, nMs = %d.\n",nPs,nMs) ;

	if(nPs < 3)
		printf("BSPNode::Classify: Error. nPs = %d.\n",nPs) ;

	if(nMs < 3)
		printf("BSPNode::Classify: Error. nMs = %d.\n",nMs) ;
	
	// Les polygones sont convexes, car OpenGL les clip lui-meme.

	//  Si les parents ne sont pas degeneres, plus et moins ne le
	// sont pas non plus.

	plus_  = new Polygone(Ps,nPs) ;
	moins_ = new Polygone(Ms,nMs) ;

	delete  P ;
}

void BSPNode::Insert(Polygone *P)
{
	Polygone *side_plus = NULL, *side_moins = NULL ;

	// 1 - Check on which size the polygon is, possibly split.

	Classify(P,side_moins,side_plus) ;

	// 2 - Insert polygons

	if(side_plus != NULL)
	{
		if(fils_plus == NULL)
		{
			fils_plus = new BSPNode(side_plus) ;

			DescendreSegPts(fils_plus, seg_plus, pts_plus) ;

			deleteAllList(seg_plus) ;
			deleteAllList(pts_plus) ;

			seg_plus = NULL ;
			pts_plus = NULL ;
		}
		else
			fils_plus->Insert(side_plus) ;
	}
		
	if(side_moins != NULL)
	{
		if(fils_moins == NULL)
		{
			fils_moins = new BSPNode(side_moins) ;

			DescendreSegPts(fils_moins, seg_moins, pts_moins) ;

			deleteAllList(seg_moins) ;
			deleteAllList(pts_moins) ;

			seg_moins = NULL ;
			pts_moins = NULL ;
		}
		else
			fils_moins->Insert(side_moins) ;
	}
}

unsigned long int BSPNode::RecursCountElements()
{
	unsigned long int res = 0 ;

	if(fils_moins != NULL)
		res += fils_moins->RecursCountElements() ;

	if(fils_plus != NULL)
		res += fils_plus->RecursCountElements() ;

	if(polygone != 0)
		res++ ;

	for(ListeDeSegments *it  = seg_plus;  (it  != NULL); it =it ->suiv)	res++ ;
	for(ListeDeSegments *it2 = seg_moins; (it2 != NULL); it2=it2->suiv) res++ ;
	for(ListeDePoints   *it3 = pts_plus;  (it3 != NULL); it3=it3->suiv)	res++ ;
	for(ListeDePoints   *it4 = pts_plus;  (it4 != NULL); it4=it4->suiv)	res++ ;

	return res ;
}

void BSPNode::RecursGetPrimitives(Primitive **tab, unsigned long int & cour)
{
	if(fils_plus != NULL)
		fils_plus->RecursGetPrimitives(tab, cour) ;

	for(ListeDeSegments *it1 = seg_plus;  (it1 != NULL); it1=it1->suiv)	
		tab[cour++] = it1->cour ;

	if(polygone != NULL)
		tab[cour++] = polygone ;

	if(fils_moins != NULL)
		fils_moins->RecursGetPrimitives(tab, cour) ;

	for(ListeDeSegments *it2 = seg_moins;  (it2 != NULL); it2=it2->suiv)	
		tab[cour++] = it2->cour ;
}

void BSPNode::Insert(Feedback3Dcolor *P)
{
	int res = Classify(P) ;

	if(res == -1)
	{
		if(fils_moins == NULL)
			pts_moins = new ListeDePoints(P, pts_moins) ;
		else
			fils_moins->Insert(P) ;
	}
	if(res == 1)
	{
		if(fils_plus == NULL)
			pts_plus = new ListeDePoints(P, pts_plus) ;
		else
			fils_plus->Insert(P) ;
	}
}

void BSPNode::Insert(Segment *S)
{
	Segment *side_plus = NULL, *side_moins = NULL ;

	Classify(S,side_moins,side_plus) ;

	if(side_plus != NULL)
	{
		if(fils_plus == NULL)
			seg_plus = new ListeDeSegments( side_plus, seg_plus ) ;
		else
			fils_plus->Insert(side_plus) ;
	}

	if(side_moins != NULL)
	{
		if(fils_moins == NULL)
			seg_moins = new ListeDeSegments( side_moins, seg_moins ) ;
		else
			fils_moins->Insert(side_moins) ;
	}
}

BSPNode::BSPNode(Polygone *P)
{
	polygone = P ;

	P->InitEquation(a,b,c,d) ;

	fils_moins = NULL ;
	fils_plus  = NULL ;

	seg_moins = NULL ;
	seg_plus  = NULL ;
	pts_moins = NULL ;
	pts_plus  = NULL ;
}

int BSPNode::Render(ListeDeSegments *L,FILE * file,int DrawMode, int format,int & depth)
{
	int rendu = 0 ;

	while(L != NULL)
	{
		if(L->cour->GetVisibility() == 1)
		{
			L->cour->spew(file,DrawMode,format,depth) ;
			rendu++ ;
		}

		L = L->suiv ;
	}

	if(rendu > 0)
		if(depth > min_depth)
			depth-- ;

	return rendu ;
}

int BSPNode::Render(ListeDePoints *L,FILE * file,int DrawMode, int format, int & depth)
{
	int vu = 0 ;

	while(L != NULL)
	{
		if(L->cour->GetVisibility() == 1)
		{
			vu++ ;
			L->cour->spew(file,DrawMode,format,depth) ;
		}

		L = L->suiv ;
	}

	if(vu >= 1)
		if(depth > min_depth)
			depth-- ;

	return vu ;
}

int BSPNode::Render(FILE * file,int DrawMode, int format,int & depth)
{
	// debug

	int res = 0 ;

	if(fils_plus != NULL)
	{
		res += fils_plus->Render(file,DrawMode, format, depth) ;

		if((seg_plus != NULL)||(pts_plus != NULL))
			printf("BSPNode::Render: inconsistency error !\n") ;
	}

	if((seg_plus != NULL)||(pts_plus != NULL))
	{
		res += Render(seg_plus,file,DrawMode, format, depth) ;
		res += Render(pts_plus,file,DrawMode, format, depth) ;
	}

	if(polygone->GetVisibility() == 1)
	{
		polygone->spew(file, DrawMode,format, depth) ;

		res++ ;
		if(depth > min_depth)
			depth -- ;
	}

	if(fils_moins != NULL)
	{
		res += fils_moins->Render(file,DrawMode,format, depth) ;

		if((seg_moins != NULL)||(pts_moins != NULL))
			printf("BSPNode::Render: inconsistency error !\n") ;
	}

	if((seg_moins != NULL)||(pts_moins != NULL))
	{
		res += Render(seg_moins,file,DrawMode,format, depth) ;
		res += Render(pts_moins,file,DrawMode,format, depth) ;
	}

	return res ;
}

//----------------------------------------------------------------------------//

BSPTree::~BSPTree()
{
	if(Root != NULL)
	{
		Root->RecursDelete() ;
		delete Root ;
	}

	CompleteDeleteAllList(pts_list) ;
	CompleteDeleteAllList(seg_list) ;
}

BSPTree::BSPTree()
{
	pts_list = NULL ;
	seg_list = NULL ;

	Root = NULL ;
}

void BSPTree::Insert(Feedback3Dcolor *P)
{
	if(Root == NULL)
		pts_list = new ListeDePoints(P,pts_list) ;
	else
		Root->Insert(P) ;
}

void BSPTree::Insert(Segment *S)
{
	if(Root == NULL)
		seg_list = new ListeDeSegments(S,seg_list) ;
	else
		Root->Insert(S) ;
}

void BSPTree::Insert(Polygone *P)
{
	if(Root == NULL)
	{
		Root = new BSPNode(P) ;

		DescendreSegPts(Root, seg_list, pts_list) ;

		deleteAllList(seg_list) ;
		deleteAllList(pts_list) ;

		seg_list = NULL ;
		pts_list = NULL ;
	}
	else
		Root->Insert(P) ;
}

void BSPTree::GetPrimitiveTab(Primitive ** & tab, long int & num) const
{
	if(Root == NULL)
	{
		num = 0 ;

		for(ListeDeSegments *it1 = seg_list; it1 != NULL; it1=it1->suiv) num++ ;
		for(ListeDePoints   *it2 = pts_list; it2 != NULL; it2=it2->suiv) num++ ;

		tab = new Primitive *[num] ;
		int tmp = 0 ;

		for(ListeDeSegments *it3 = seg_list; it3 != NULL; it3=it3->suiv) tab[tmp++] = it3->cour ;
		for(ListeDePoints *it4 = pts_list; it4 != NULL; it4=it4->suiv) tab[tmp++] = it4->cour ;
	}
	else
	{
		num = Root->RecursCountElements() ;

		tab = new Primitive *[num] ;
		unsigned long int cour = 0 ;

		Root->RecursGetPrimitives(tab, cour) ;
#ifdef DEBUGEPSRENDER
		if(cour != num)
			printf("GetPrimitiveTab:: Something's wrong !!") ;
#endif
	}
}

void BSPTree::Render(FILE *f,int drm, int format)
{
	int depth = 999 ;
	int nbprims = 0 ;

	if(Root != NULL)
		nbprims += Root->Render(f,drm,format,depth) ;

	ListeDeSegments *L = seg_list ;

	while(L != NULL)
	{
		if(L->cour->GetVisibility() == 1)
		{
			L->cour->spew(f,drm,format,min_depth) ;
			nbprims++ ;
		}

		L = L->suiv ;
	}

	ListeDePoints *M = pts_list ;

	while(M != NULL)
	{
		if(M->cour->GetVisibility() == 1)
		{
			M->cour->spew(f,drm,format,min_depth) ;
			nbprims++ ;
		}
		
		M = M->suiv ;
	}
#ifdef DEBUGEPSRENDER
	printf("BSPTree: Rendered %d primitives.\n",nbprims) ;
#endif
}

#ifdef DEBUGEPSRENDER
const char *BSPTree::GetPositionName(BSPPosition p)
{
	const char *Pnames[] = { "Cross plane","Upper","Lower" } ;

	return Pnames[p] ;
}
#endif
