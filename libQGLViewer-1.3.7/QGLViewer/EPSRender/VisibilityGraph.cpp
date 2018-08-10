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

#include <stdlib.h>
#include <assert.h>

#include "gpc.h"
#include "Geometry.h"
#include "GeometryUtils.h"
#include "Affichage.h"

#include "BSPTree.h"
#include "VisibilityGraph.h"

using namespace std;

double I_EPS 				= 0.00001 ;
double SIGNS_I_EPS		= 0.0001 ;
double FLAT_POLYGON_EPS	= 0.0001 ;

#ifdef DEBUG_VISIBILITYGRAPH
int GraphNode::ID = 0 ;
#endif

void VisibilityBSPNode::RecursDelete()
{
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

void Primitive::GetSigns(Primitive *P,int * & signs,FLOAT * & zvals,int & Smin,int & Smax,FLOAT S)
{
	if(((P->NbVertices() <= 2)||(NbVertices() <= 2))&&(P->NbVertices() != NbVertices()))
		getsigns(Normal(),C,P,signs,zvals,Smin,Smax,SIGNS_I_EPS * S) ;
	else
		getsigns(Normal(),C,P,signs,zvals,Smin,Smax,I_EPS * S) ;
}

bool VisibilityBSPNode::SimplePositionTest(	int Signs[],int n,int Smin,int Smax,bool indep,
											XYZRelativePosition & r_pos,
											BSPPosition & pos) 
{
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

	if((Smin == 0)&&(Smax == 0)) // Polygone inclus dans le plan
	{
//		if(graph_node->GetPrimitive()->NbVertices() > 2)
//		{
			pos = BSP_LOWER ;
			if(indep) r_pos = Primitive_INDEPENDENT ; else r_pos = Primitive_LOWER ;
			return true ;
//		}
//		else 
//		{
//			pos = BSP_UPPER ;
//			if(indep) r_pos = Primitive_INDEPENDENT ; else r_pos = Primitive_UPPER ;
//			return true ;
//		}
	}
	
	if(Smin == 1) // Polygone tout positif
	{
		pos = BSP_UPPER ;

		if(indep)
			r_pos = Primitive_INDEPENDENT ;
		else
			r_pos = Primitive_UPPER ;

		return true ;
	}

	if(Smax == -1) // Polygone tout negatif
	{
		pos = BSP_LOWER ;

		if(indep)
			r_pos = Primitive_INDEPENDENT ;
		else
			r_pos = Primitive_LOWER ;

		return true ;
	}

	if((Smin == -1)&&(Smax == 0))
	{
		pos = BSP_LOWER ;
		if(indep) r_pos = Primitive_INDEPENDENT ; else r_pos = Primitive_LOWER ;
		return true ;
	}

	if((Smin == 0)&&(Smax == 1))
	{
		pos = BSP_UPPER ;
		if(indep) r_pos = Primitive_INDEPENDENT ; else r_pos = Primitive_UPPER ;
		return true ;
	}

	// On teste la coherence des signes.

	if((nZero > 2)||(nconsZero > 0))
	{
		// Ils y a des imprecisions numeriques dues au fait que le poly est pres du plan.

		pos = BSP_LOWER ;

		if(indep)
			r_pos = Primitive_INDEPENDENT ;
		else
			r_pos = Primitive_LOWER ;

		return true ;
	}

	return false ; // on n'est pas arrive a conclure
}

void VisibilityBSPNode::InvertPosition(XYZRelativePosition & r_pos)
{
	switch(r_pos)
	{
		case Primitive_UPPER: 	r_pos = Primitive_LOWER ;
								break ;
		case Primitive_LOWER: 	r_pos = Primitive_UPPER ;
								break ;
		case Primitive_INDEPENDENT:
		case Primitive_INTERSECT:
								break ;
		default:				
			printf("Error fRRg58ffF !\n") ;
			break ;
	}
}

// Teste si un point est exterieur a un polygone convexe. Plus I_EPS est grand plus il faut etre 
// loin pour que ca soit faux. EPS=0 correspond au polygone lui-meme. Pour EPS<0, des points exterieurs
// et pres de la frontiere sont declares interieurs.
// Plus I_EPS est grand, plus l'ensemble des points consideres comme interieur est dilate.

bool IsPointOutOfProjectionOfPrimitive(const Vect3 & p,const Primitive *Q, const FLOAT I_EPS)
{
	int nq = Q->NbVertices() ;
	FLOAT MaxZ = -FLT_MAX ;
	FLOAT MinZ =  FLT_MAX ;

	for(int j=0;j<nq;j++)  				//  Regarde si P.(x,y) est a l'interieur
	{                               	// ou a l'exterieur du polygone.
		Vect3 q1(Q->Vertex(j)) ;
		Vect3 q2(Q->Vertex((j+1)%nq)) ;

		FLOAT Z = ((q1-p)^(q2-p)).Z ;

		MinZ = Min(Z,MinZ) ;
		MaxZ = Max(Z,MaxZ) ;
	}

	if((MaxZ < -I_EPS*I_EPS)||(MinZ > I_EPS*I_EPS))
		return false ;

	return true ;
}

bool IntersectionSegments(	FLOAT P1x,FLOAT P1y,FLOAT Q1x,FLOAT Q1y,
							FLOAT P2x,FLOAT P2y,FLOAT Q2x,FLOAT Q2y,FLOAT I_EPS,
							FLOAT & t1,FLOAT & t2)
{
	FLOAT a2 = -(Q2y - P2y) ;
	FLOAT b2 =  (Q2x - P2x) ;
	FLOAT c2 =  P2x*a2+P2y*b2 ;

	FLOAT a1 = -(Q1y - P1y) ;
	FLOAT b1 =  (Q1x - P1x) ;
	FLOAT c1 =  P1x*a1+P1y*b1 ;

	FLOAT d2 = a2*(Q1x-P1x)+b2*(Q1y-P1y) ;
	FLOAT d1 = a1*(Q2x-P2x)+b1*(Q2y-P2y) ;

	if((fabs(d2) <= fabs(I_EPS))||(fabs(d1) <= fabs(I_EPS)))	// les segments sont paralleles
	{
		if(fabs(a2*P1x + b2*P1y - c2) >= I_EPS)
			return false ;

		FLOAT tP1,tQ1 ;

		if(P1x != Q1x)
		{
			tP1 = (P2x-P1x)/(Q1x-P1x) ;
			tQ1 = (Q2x-P1x)/(Q1x-P1x) ;
		}
		else if(P1y != Q1y)
		{
			tP1 = (P2y-P1y)/(Q1y-P1y) ;
			tQ1 = (Q2y-P1y)/(Q1y-P1y) ;
		}
		else
		{
#ifdef DEBUG_VISIBILITYGRAPH
			printf("IntersectSegments2D:: Error ! One segment has length 0\n") ;
			printf("This special case is not treated yet.\n") ;
#endif
			return false ;
		}

		FLOAT tPQM = Max(tP1,tQ1) ;
		FLOAT tPQm = Min(tP1,tQ1) ;

		if(( tPQM < -I_EPS) || (tPQm > 1.0+I_EPS))
			return false ;

		if(tPQm > 0.0) 
		{
			t1 = tPQm ; 
			t2 = 0.0 ;
		}
		else 
		{
			t1 = 0.0 ;
			if(P2x != Q2x) 
				t2 = (P1x-P2x)/(Q2x-P2x) ;
			else if(P2y != Q2y) 
				t2 = (P1y-P2y)/(Q2y-P2y) ;
			else
			{
				printf("IntersectSegments2D:: Error ! One segment has length 0\n") ;
				printf("This special case is not treated yet.\n") ;
				return false ;
			}
		}

		return true ;
	}
	else
	{
		t2 = (c1 - a1*P2x - b1*P2y)/d1 ;
		t1 = (c2 - a2*P1x - b2*P1y)/d2 ;

		if((t2 > 1+I_EPS)||(t2 < -I_EPS)||(t1 > 1+I_EPS)||(t1 < -I_EPS))
			return false ;

		return true ;
	}
}

// Renvoie true si P et Q sont independants. Si non, position_clue contient
// la position de Q par rapport a P. Cette valeur n'est coherente QUE si 
// P et Q sont en position non-intersect / cross-plane
 
bool Independance(Primitive *P,Primitive *Q,XYZRelativePosition & position_clue) 
{
	int np = P->NbVertices() ;
	int nq = Q->NbVertices() ;

	if((P->NbVertices() <= 2)&&(Q->NbVertices() <= 2))	// marche tant que les segments et les points
		return true ;									// sont inseres apres les polygones.

	position_clue = Primitive_UNKNOWN ;
	bool res = true ;

	Vect3 MinP(FLT_MAX,FLT_MAX,FLT_MAX) ;
	Vect3 MinQ(FLT_MAX,FLT_MAX,FLT_MAX) ;
	Vect3 MaxP(-FLT_MAX,-FLT_MAX,-FLT_MAX) ;
	Vect3 MaxQ(-FLT_MAX,-FLT_MAX,-FLT_MAX) ;

	for(int i=0;i<np;i++)
	{
		MinP = VectorMin(MinP, P->Vertex(i)) ;
		MaxP = VectorMax(MaxP, P->Vertex(i)) ;
	}
	for(int j=0;j<nq;j++)
	{
		MinQ = VectorMin(MinQ,Q->Vertex(j)) ;
		MaxQ = VectorMax(MaxQ,Q->Vertex(j)) ;
	}

	if(MinP.X > MaxQ.X) return true ;
	if(MinP.Y > MaxQ.Y) return true ;
	if(MaxP.X < MinQ.X) return true ;
	if(MaxP.Y < MinQ.Y) return true ;

	FLOAT EpsTest = P->Get_I_EPS(Q) ;

	// les boites anglobantes s'intersectent. On teste plus profond.

	for(int k=0;k<np;k++)
	{
		Vect3 p1(P->Vertex(k)) ;
		Vect3 p2(P->Vertex((k+1)%np)) ;

		for(int j=0;j<nq;j++)
		{
			Vect3 q1(Q->Vertex(j)) ;
			Vect3 q2(Q->Vertex((j+1)%nq)) ;

			FLOAT tp,tq ;

			if(IntersectionSegments(p1.X,p1.Y,p2.X,p2.Y,q1.X,q1.Y,q2.X,q2.Y,EpsTest,tp,tq))
			{
				FLOAT zp = p1.Z + tp*(p2.Z - p1.Z) ;
				FLOAT zq = q1.Z + tq*(q2.Z - q1.Z) ;

				// intersection entre aretes.

				if(zp > zq+I_EPS)
				{
					position_clue = Primitive_LOWER ;
					return false ;
				}
				if(zp < zq-I_EPS)
				{
					position_clue = Primitive_UPPER ;
					return false ;
				}
			}
		}
	}

	// inclusion de la projection de Q des points de P

	for(int l=0;l<np;l++)
		if(!IsPointOutOfProjectionOfPrimitive(P->Vertex(l),Q,-P->Get_I_EPS(Q)))
		{
			FLOAT e = Q->Equation(P->Vertex(l)) ;

			if(e < -I_EPS)
			{
				position_clue = Primitive_UPPER ;
				return false ;
			}
			else if(e > I_EPS)
			{
				position_clue = Primitive_LOWER ;
				return false ;
			}
			else
				res = false ;
		}

	for(int m=0;m<nq;m++)
		if(!IsPointOutOfProjectionOfPrimitive(Q->Vertex(m),P,-P->Get_I_EPS(Q)))
		{
			FLOAT e = P->Equation(Q->Vertex(m)) ;

			if(e < -I_EPS)
			{
				position_clue = Primitive_LOWER ;
				return false ;
			}
			else if(e > I_EPS)
			{
				position_clue = Primitive_UPPER ;
				return false ;
			}
			else
				res = false ;
		}

	// Normalement on ne devrait pas atterir ici.
	// pas besoin de mettre a jour position_clue dans ce cas.
	
	if(position_clue == Primitive_UNKNOWN)
	{
		if(P->NbVertices() < Q->NbVertices())
			position_clue = Primitive_UPPER ;
		else
			position_clue = Primitive_LOWER ;
	}

	return res ;
}

static Vect3 GetDirectionVector(const Vect3 & p1,const Vect3 & p2,const Vect3 & p3,const Vect3 & p4)
{
	Vect3 res(p2-p1) ;

	if((p3-p1).NormInf() > res.NormInf()) res = p3-p1 ;
	if((p4-p1).NormInf() > res.NormInf()) res = p4-p1 ;
	if((p3-p2).NormInf() > res.NormInf()) res = p3-p2 ;
	if((p4-p2).NormInf() > res.NormInf()) res = p4-p2 ;
	if((p4-p3).NormInf() > res.NormInf()) res = p4-p3 ;

	return res ;
}

static void GetTValuesOnLine( const Vect3 & p1,const Vect3 & p2,const Vect3 & p3,const Vect3 & p4,
						FLOAT & t1, FLOAT & t2, FLOAT & t3, FLOAT & t4) 
{
	Vect3 v = GetDirectionVector(p1,p2,p3,p4) ;

	t1 = 0.0 ;
	t2 = (p2-p1)*v ;
	t3 = (p3-p1)*v ;
	t4 = (p4-p1)*v ;
}

//  This procedure can be called with I_EPS < 0, which represents under-estimated
// intersections. This avoids too much useless intersections. The old version
// (commented since Aug.5.02) had a bug: when the two intervals are equal, there
// should be an intersection whatever the precision I_EPS !
//  It is supposed that t1 <= t2 and t3 <= t4

bool IntersectIntervalles(const FLOAT t1,const FLOAT t2,const FLOAT t3,const FLOAT t4,FLOAT I_EPS)
{
	if(t4 < t1-I_EPS) return false ;
	if(t3 > t2+I_EPS) return false ;

	return true ;
}

void VisibilityBSPNode::Classify(Primitive *P, XYZRelativePosition & r_pos, BSPPosition & pos,
											const VisibilityGraph *vg) 
{
	int *Signs ;
	FLOAT *Zvals ;
	int Smin,Smax ;
	XYZRelativePosition position_clue ;
	Vect3 *p1 ;
	Vect3 *p2 ;

#ifdef DEBUG_VISIBILITYGRAPH
	if((graph_node->GetPrimitive()->NbVertices() <= 2)&&(P->NbVertices() > 2))
		printf("VisibilityBSPNode::Classify: Unexpected dangerous case detected !!\n") ;
#endif

	bool indep = Independance(graph_node->GetPrimitive(),P,position_clue) ;

	graph_node->GetPrimitive()->GetSigns(P,Signs,Zvals,Smin,Smax,vg->ZDepth()) ;

	if(SimplePositionTest(Signs,P->NbVertices(),Smin,Smax,indep,r_pos,pos))
		return ;

	pos = BSP_CROSS_PLANE ;

	if(indep)
	{
		r_pos = Primitive_INDEPENDENT ;
		return ;
	}
	else
		graph_node->GetPrimitive()->IntersectPrimitiveWithSupportPlane(P,Signs,Zvals,p1,p2) ;

	// Cela modifie Signs, et donc on doit faire le IntersectPrimitive avant.

	P->GetSigns(graph_node->GetPrimitive(),Signs,Zvals,Smin,Smax,vg->ZDepth()) ;
	BSPPosition tmp ; // la valeur importe peu

	if(SimplePositionTest(Signs,graph_node->GetPrimitive()->NbVertices(),Smin,Smax,indep,r_pos,tmp))
	{
		InvertPosition(r_pos) ;

		if(p1 != NULL) delete p1 ;
		if(p2 != NULL) delete p2 ;
		return ;
	}

	// Reste le cas ou chacun rencontre le plan de l'autre. On calcule les
	// segments d'intersection et on regarde s'ils se rencontrent.

	Vect3 *p3 ;
	Vect3 *p4 ;

	P->IntersectPrimitiveWithSupportPlane(graph_node->GetPrimitive(),Signs,Zvals,p3,p4) ;

	pos = BSP_CROSS_PLANE ;
	FLOAT t1,t2,t3,t4 ;
	GetTValuesOnLine(*p1,*p2,*p3,*p4,t1,t2,t3,t4) ;

	if(t2-t1 < 0) { FLOAT tmp = t2 ; t2 = t1 ; t1 = tmp ; }
	if(t4-t3 < 0) { FLOAT tmp = t3 ; t3 = t4 ; t4 = tmp ; }

	FLOAT M = Max(t2,t4) ;
	FLOAT m = Min(t1,t3) ;
	FLOAT f = (M != m)? M-m: 1.0 ;

	t1 = (t1-m)/f ;
	t2 = (t2-m)/f ;
	t3 = (t3-m)/f ;
	t4 = (t4-m)/f ;

	if(IntersectIntervalles(t1,t2,t3,t4,-I_EPS))
		r_pos = Primitive_INTERSECT ;
	else
		r_pos = position_clue ;

	if(p3 != NULL) delete p3 ;
	if(p4 != NULL) delete p4 ;
}

void Primitive::IntersectPrimitiveWithSupportPlane(	Primitive *P,int Signs[], FLOAT Zvals[],
													Vect3 * & p1, Vect3 * & p2)
{
	int n=P->NbVertices() ;
	int dep=0 ;
	p1 = NULL ;
	p2 = NULL ;
	while(Signs[dep] == 0) dep++ ;

	int prev_sign = Signs[dep] ;

	for(int i=1;i<=n;i++)
	{
		int sign = Signs[(i+dep)%n] ;

		if(sign == -prev_sign)
		{
			//  Il faut effectuer le calcul en utilisant les memes valeurs que pour le calcul des signes,
			// sinon on risque des incoherences dues aux imprecisions numeriques.

			double Z1 = Zvals[((i+dep)-1)%n] ;
			double Z2 = Zvals[(i+dep)%n] ;

			double t = fabs(Z1/(Z2 - Z1)) ;

			if(t > 1.0) t = 1.0 ;
			if(t < 0.0) t = 0.0 ;

			double x = (1-t) * P->Vertex(((i+dep)-1)%n).X + t * P->Vertex((i+dep)%n).X ;
			double y = (1-t) * P->Vertex(((i+dep)-1)%n).Y + t * P->Vertex((i+dep)%n).Y ;
			double z = (1-t) * P->Vertex(((i+dep)-1)%n).Z + t * P->Vertex((i+dep)%n).Z ;

			Vect3 *newVertex = new Vect3(x,y,z) ;

			if(p1 == NULL)
				p1 = newVertex ;
			else if(p2 == NULL)
				p2 = newVertex ;
			else
			{
				delete newVertex ;
				printf("Error 443237FFggjkF !\n") ;
			}

			prev_sign = sign ;
		} 
		else if(sign != prev_sign) 	//  Prev_sign != 0 donc necessairement sign = 0. 
		{							// le sommet tombe dans le plan
			Vect3 *newVertex = new Vect3(P->Vertex((i+dep)%n)) ;

			if(p1 == NULL)
				p1 = newVertex ;
			else if(p2 == NULL)
				p2 = newVertex ;
			else
			{
				delete newVertex ;
				printf("Error 44ffG7FFggjkF !\n") ;
			}

			prev_sign = -prev_sign ;
		}
	}
}

void IntersectPrimitiveWithSegment2D(const Primitive *P, const Primitive *S,SecuredArray<Vect2> & pts,int & nb)
{
	// Vect3 p1,p2 ;
	int n=0 ;
	Vect3 last_p(FLT_MAX,FLT_MAX,FLT_MAX) ;

	Vect3 P2 = S->Vertex(0) ;
	Vect3 Q2 = S->Vertex(1) ;

	if(!IsPointOutOfProjectionOfPrimitive(P2,P,-I_EPS))
	{
		pts.AddElem(nb++,P2) ;
		last_p = P2 ;
		n++ ;
	}
	if(!IsPointOutOfProjectionOfPrimitive(Q2,P,-I_EPS))
	{
		pts.AddElem(nb++,Q2) ;
		last_p = Q2 ;
		n++ ;
	}

	if(n == 2)
		return ;

	for(int i=0;i<P->NbVertices();i++)
	{
		Vect3 P1(P->Vertex(i)) ;
		Vect3 Q1(P->Vertex((i+1)%P->NbVertices())) ;

		FLOAT t1,t2 ;

		if(IntersectionSegments(P1.X,P1.Y,Q1.X,Q1.Y,
								P2.X,P2.Y,Q2.X,Q2.Y,I_EPS,t1,t2))
		{
			Vect3 p(P2+t2*(Q2-P2)) ;
			if((last_p - p).NormInf() > I_EPS)
			{
				pts.AddElem(nb++,p) ;
				n++ ;
				last_p = p ;
			}

			if(n == 2)
				return ;
		}
	}
#ifdef DEBUG_VISIBILITYGRAPH
	if((n != 2)&&(P->NbVertices() > 2))
		printf("IntersectPrimitiveWithSegment2D: Warning: %d intersection points !\n",n) ;
#endif
}

// Calcule les points d'intersection 2D entre P et Q et les range
// dans pts.
void GraphNode::AddIntersectionProjectedPoints(const Primitive *P,const Primitive *Q,
												SecuredArray<Vect2> & pts,int & nb)
{
	if(P->NbVertices() < 3)
	{
		IntersectPrimitiveWithSegment2D(Q,P,pts,nb) ;
		return ;
	}

	if(Q->NbVertices() < 3)
	{
		IntersectPrimitiveWithSegment2D(P,Q,pts,nb) ;
		return ;
	}

	gpc_polygon subject_p, clip_p, result;

	subject_p.contour = new gpc_vertex_list() ;
	subject_p.contour[0].num_vertices = P->NbVertices() ;
	subject_p.contour[0].vertex = new gpc_vertex[P->NbVertices()] ;
	subject_p.num_contours = 1 ;
	subject_p.hole = new int ;

	clip_p.contour = new gpc_vertex_list() ;
	clip_p.contour[0].num_vertices = Q->NbVertices() ;
	clip_p.contour[0].vertex = new gpc_vertex[Q->NbVertices()] ;
	clip_p.num_contours = 1 ;
	clip_p.hole = new int ;

	for(int i=0;i<P->NbVertices();i++)
	{
		subject_p.contour[0].vertex[i].x = P->Vertex(i).X ;
		subject_p.contour[0].vertex[i].y = P->Vertex(i).Y ;
	}

	for(int j=0;j<Q->NbVertices();j++)
	{
		clip_p.contour[0].vertex[j].x = Q->Vertex(j).X ;
		clip_p.contour[0].vertex[j].y = Q->Vertex(j).Y ;
	}

	gpc_polygon_clip(GPC_INT, &subject_p, &clip_p, &result);

//	FILE *fp = fopen("subject_p.txt","w") ;
//	FILE *fq = fopen("clip_p.txt","w") ;
//	gpc_write_polygon(fp,0,&subject_p) ;
//	gpc_write_polygon(fq,0,&clip_p) ;
//	fclose(fp) ;
//	fclose(fq) ;

	if(result.num_contours > 1)
		cerr << "AddIntersectionProjectedPoints: convexity error !" << endl ;

	if(result.num_contours > 0)
		for(int i=0;i<result.contour[0].num_vertices;i++)
			pts.AddElem(nb++,Vect2(result.contour[0].vertex[i].x,result.contour[0].vertex[i].y)) ;

	gpc_free_polygon(&subject_p);
	gpc_free_polygon(&clip_p);
	gpc_free_polygon(&result);
}

#ifdef DEBUG_VISIBILITYGRAPH
void testIntersectSegments()
{
	Feedback3Dcolor pPoints[4] ;
	Feedback3Dcolor qPoints[4] ;

	pPoints[0] = Feedback3Dcolor(0,0,0,0,0,0,0) ;
	pPoints[1] = Feedback3Dcolor(1,0,0,0,0,0,0) ;
	pPoints[2] = Feedback3Dcolor(1,1,0,0,0,0,0) ;
	pPoints[3] = Feedback3Dcolor(0,1,0,0,0,0,0) ;

	qPoints[0] = Feedback3Dcolor(-0.5, 0.5,0,0,0,0,0) ;
	qPoints[1] = Feedback3Dcolor( 0.5,-0.2,0,0,0,0,0) ;
	qPoints[2] = Feedback3Dcolor( 1.5, 0.5,0,0,0,0,0) ;
	qPoints[3] = Feedback3Dcolor(0,1,0,0,0,0,0) ;

	Polygone P(pPoints,4) ;
	Polygone Q(qPoints,3) ;
	int nb = 0 ;

	SecuredArray<Vect2> pts(10) ;

	GraphNode::AddIntersectionProjectedPoints(&P,&Q,pts,nb) ;

	for(int i=0;i<nb;i++)
		printf("%d: %1.3f %1.3f\n",i,pts[i].X,pts[i].Y) ;
}
#endif

// Decoupe P en P_plus et P_moins. P_plus est du cote de leftP et P_moins de celui de rightP

void GraphNode::SplitPrimitive(const Primitive *leftP,const Primitive *rightP,
								Primitive *P,Primitive *& P_plus,Primitive *& P_moins)
{
	SecuredArray<Vect2> leftPoints(3) ;
	SecuredArray<Vect2> rightPoints(3) ;

	P_plus = NULL ;
	P_moins = NULL ;

	int nb_left_points = 0 ;
	int nb_right_points = 0 ;

	AddIntersectionProjectedPoints(leftP,P,leftPoints,nb_left_points) ;
	AddIntersectionProjectedPoints(rightP,P,rightPoints,nb_right_points) ;

	if(nb_right_points == 0)
		return ;

	if(nb_left_points == 0)
	{
#ifdef DEBUG_VISIBILITYGRAPH
		printf("GraphNode::SplitPrimitive. Error: inconsistency !\n") ;
#endif
		return ;
	}

	if(P->NbVertices() == 2)
	{
		if((nb_left_points != 2)||(nb_right_points != 2))
		{
			if(nb_left_points == 1)
				leftPoints.AddElem(1,leftPoints[0]) ;

			if(nb_right_points == 1)
				rightPoints.AddElem(1,rightPoints[0]) ;
#ifdef DEBUG_VISIBILITYGRAPH
			printf("GraphNode::SplitPrimitive: strange case !!\n") ;
#endif
		}

		Vect3 p1(leftPoints[0],0.0) ;
		Vect3 p2(leftPoints[1],0.0) ;
		Vect3 p3(rightPoints[0],0.0) ;
		Vect3 p4(rightPoints[1],0.0) ;

		FLOAT t1,t2,t3,t4 ;

		GetTValuesOnLine(p1,p2,p3,p4,t1,t2,t3,t4) ;

		if(t2-t1 < 0) { FLOAT tmp = t2 ; t2 = t1 ; t1 = tmp ; Vect3 Tmp = p2 ; p2 = p1 ; p1 = Tmp ; }
		if(t4-t3 < 0) { FLOAT tmp = t3 ; t3 = t4 ; t4 = tmp ; Vect3 Tmp = p4 ; p4 = p3 ; p3 = Tmp ; }

#ifdef DEBUG_VISIBILITYGRAPH
		cout << "p1,p2,p3,p4 = " << p1 << " " << p2 << " " << p3 << " " << p4 << endl ;
		cout << "t1,t2,t3,t4 = " << t1 << " " << t2 << " " << t3 << " " << t4 << endl ;
#endif
		Vect2 v = GetDirectionVector(p1,p2,p3,p4) ;
		if(v.NormInf() == 0.0)
			return ;
		else
			v.Normalize() ;

		FLOAT C ;
		if(t2 <= t3)
			C = v*0.5*(p2+p3) ;
		else
			C = v*0.5*(p1+p4) ;

		if(v*leftPoints[0]-C < 0)
		{
			v *= -1.0 ;
			C *= -1.0 ;
		}

		P->Split(Vect3(v,0.0),C,P_plus,P_moins) ;
		return ;
	}

	// Le second est convexe dans l'ordre des points. On l'utilise donc comme generateur
	// des directions.

	int Sgn = 0 ;

	for(int i=0;i<nb_right_points;++i)
	{
		double f = ((rightPoints[(i+2)%nb_right_points] - rightPoints[(i+1)%nb_right_points])
				     ^(rightPoints[i] - rightPoints[(i+1)%nb_right_points])).Z ;

		if(f < -I_EPS*I_EPS)
		{
			Sgn = -1 ;
			break ;
		}
		if(f > I_EPS*I_EPS)
		{
			Sgn = 1 ;
			break ;
		}
	}

	if(Sgn != 0)
		for(int k=0;k<nb_right_points;k++)
		{
			Vect2 d_k((rightPoints[(k+1)%nb_right_points] - rightPoints[k]).T()) ;

			if(d_k.NormInf() != 0.0)
			{
				d_k.Normalize() ;

				FLOAT c(d_k * rightPoints[k]) ;

				FLOAT min = FLT_MAX ;
				FLOAT max =-FLT_MAX ;

				for(int l=0;l<nb_left_points;l++)
				{
					FLOAT val = d_k * leftPoints[l] - c ;
					min = Min(val,min) ;
					max = Max(val,max) ;
				}

				if(((Sgn < 0)&&(min >= -I_EPS)) || ((Sgn > 0)&&(max <= I_EPS))) // on a trouve
				{
					Vect3 v(d_k,0.0) ;
					FLOAT C(d_k * (rightPoints[k] + ((Sgn > 0)?max:min)/2.0*d_k)) ;

					// il faut s'arranger pour que P_plus tombe du cote de leftPoints. On joue donc sur v:
					if(d_k*leftPoints[0]-C < I_EPS)
					{
						v *= -1.0 ;
						C *= -1.0 ;
					}

					P->Split(v,C,P_plus,P_moins) ;

					return ;
				}
			}
		}

	Vect2 v(rightPoints[0]-leftPoints[0]) ;
	FLOAT C = v * (rightPoints[0] + 0.5*(Vect2)(leftPoints[0]-rightPoints[0])) ;
	if(v*leftPoints[0]-C < 0)
		v *= -1.0 ;
#ifdef DEBUG_VISIBILITYGRAPH
	cout << "GraphNode::SplitPrimitive: Error ! Could not find correct separating line !" << endl ;

	for(int i=0;i<nb_left_points;++i) 
		printf("%f %f %s\n",leftPoints[i].X,leftPoints[i].Y ,((i==0)?" moveto":" lineto")) ;
	for(int i=0;i<nb_right_points;++i) 
		printf("%f %f %s\n",rightPoints[i].X,rightPoints[i].Y ,((i==0)?" moveto":" lineto")) ;
#endif

	P->Split(Vect3(v,0.0),C,P_plus,P_moins) ;
}

void GraphNode::SplitGraphNodePlus(GraphNode *SprecNode,VisibilityGraph *vg,GraphNode *gn,GraphNode *& gn_plus)
{
	Primitive *P_plus ;
	Primitive *P_moins ;

	SplitPrimitive(SprecNode->GetPrimitive(),GetPrimitive(),gn->GetPrimitive(),P_moins,P_plus) ;

	if((P_plus == NULL)||(P_moins == NULL))
		gn_plus = NULL ;
	else
	{
		gn_plus = vg->GetNewNode(P_plus) ;

		delete gn->GetPrimitive() ;
		gn->SetPrimitive(P_moins) ;
	}
}

void GraphNode::SplitGraphNodeMoins(GraphNode *SprecNode,VisibilityGraph *vg,GraphNode *gn,GraphNode *& gn_moins)
{
	Primitive *P_plus ;
	Primitive *P_moins ;

	SplitPrimitive(SprecNode->GetPrimitive(),GetPrimitive(),gn->GetPrimitive(),P_plus,P_moins) ;

	// P_moins n'est jamais null, mais on teste qd meme.

	if((P_plus == NULL)||(P_moins == NULL))
		gn_moins = NULL ;
	else
	{
		gn_moins = vg->GetNewNode(P_moins) ;

		delete gn->GetPrimitive() ;
		gn->SetPrimitive(P_plus) ;
	}
}

#ifdef DEBUG_VISIBILITYGRAPH
static int global_depth = 0 ;
#endif

void VisibilityBSPNode::Insert(GraphNode *gn,VisibilityGraph *vg)
{
	//  r_pos: Classification par rapport a la verticale
	// la reponse est Primitive_INDEPENDENT, Primitive_INTERSECT, 
	// Primitive_UPPER ou Primitive_LOWER.
	//  pos: Classification par rapport au plan de coupe du BSP
	// la reponse est BSP_CROSS_PLANE, BSP_UPPER ou BSP_LOWER.

	XYZRelativePosition r_pos ;
	BSPPosition pos ;
	
#ifdef DEBUG_VISIBILITYGRAPH
	for(int h=0;h<2*global_depth;h++) printf(" ") ;
	printf("VisibilityBSPNode %d inserting GraphNode %d\n",graph_node->id,gn->id) ;

	if((graph_node->id == 2)&&(gn->id == 3))
		cout << "here" << endl ;
#endif

	Classify(gn->GetPrimitive(),r_pos,pos,vg) ;

#ifdef DEBUG_VISIBILITYGRAPH
	for(int h=0;h<2*global_depth;h++) printf(" ") ;
	printf("Classification: %s (v_graph) / %s (BSP)\n",VisibilityGraph::GetPositionName(r_pos),
																		BSPTree::GetPositionName(pos)) ;
//	for(int h=0;h<2*global_depth;h++) printf(" ") ;
//	printf("self Precedences: ") ;
//	graph_node->PrintPrecedences() ;
//	for(int h=0;h<2*global_depth;h++) printf(" ") ;
//	printf("Node Precedences: ") ;
//	gn->PrintPrecedences() ;
#endif

	Insert(gn,vg,r_pos,pos) ;
}

bool VisibilityBSPNode::testPrecedence(GraphNode *g1,GraphNode *g2,
													GraphNode * & begin_cycle,GraphNode * & end_cycle)
{
	//  Cette constante est utilisee comme marqueur pour eviter de visiter
	// plusieurs fois un GraphNode. Comme on veut pas mettre a jour la flag
	// de visite pour tous les graph nodes, on change de marqueur a chaque
	// traversee. C'est donc plus efficace qu'un tableau. 

	static unsigned int CurrentMark = 1 ;

	if(CurrentMark == 0)
		cerr << "Warning: mark skew !!" << endl ;

	return g1->HasPrecedence(g2,begin_cycle,end_cycle,CurrentMark++) ;
}

void VisibilityBSPNode::Insert(GraphNode *gn,VisibilityGraph *vg,XYZRelativePosition r_pos,BSPPosition pos) 
{
  GraphNode *gn_plus = NULL ;
  GraphNode *gn_moins = NULL ;

#ifdef DEBUG_VISIBILITYGRAPH
  global_depth++ ;
#endif
  GraphNode *first_node_of_cycle = NULL ;
  GraphNode *last_node_of_cycle = NULL ;

  switch(r_pos)
    {
      // !! le near plane (z=0) est devant. Il faut donc rendre en premier les z les plus grands.

    case Primitive_UPPER: if(testPrecedence(gn,graph_node,first_node_of_cycle,last_node_of_cycle))
      //if(gn->HasPrecedence(graph_node,first_node_of_cycle,last_node_of_cycle))	// C.f B6.86
      {
	// Recupere parmi les precedents *strictes* de gn, ceux qui ont comme
	// precedent graph_node.
#ifdef DEBUG_VISIBILITYGRAPH
	for(int h=0;h<2*global_depth;h++) printf(" ") ;
	printf("Splitting %d\n",gn->id) ;
#endif
	// Decoupe gn en deux. Le nouveau gn correspond a la partie du fond.
	graph_node->SplitGraphNodePlus(first_node_of_cycle,vg,gn,gn_plus) ;

	if(gn_plus == NULL)
	  {
	    gn_plus = gn ;
	    gn_plus->RemovePrecedence(first_node_of_cycle) ;
	    first_node_of_cycle->RemoveAncestor(gn_plus) ;
	    gn = NULL ;
	  }
	else
	  {
	    gn_plus->GetPrecedences(gn,first_node_of_cycle) ;	
	    gn_plus->GetAncestors(gn,graph_node) ;
	  }

	graph_node->UpdatePrecedenceInfo(gn_plus) ;
#ifdef DEBUG_VISIBILITYGRAPH
	for(int h=0;h<2*global_depth;h++) printf(" ") ;
	printf("Created %d (%d vertices), Prec:",gn_plus->id,gn_plus->GetPrimitive()->NbVertices()) ;
	gn_plus->PrintPrecedences() ;
	for(int h=0;h<2*global_depth;h++) printf(" ") ;
	printf("self Precedences: ") ;
	graph_node->PrintPrecedences() ;
	for(int h=0;h<2*global_depth;h++) printf(" ") ;
	printf("Node Precedences: ") ;
	if(gn != NULL) gn->PrintPrecedences() ;
#endif
	if(gn_plus != NULL) Insert(gn_plus,vg,Primitive_UPPER,pos) ;
	if(gn != NULL) Insert(gn,vg,Primitive_INDEPENDENT,pos) ;
	return ;
      }
    else
      graph_node->UpdatePrecedenceInfo(gn) ;
      break ;

      // Recupere parmi les precedents de graph_node, ceux qui ont comme
      // precedent *strictes* gn.

    case Primitive_LOWER: if(testPrecedence(graph_node,gn,first_node_of_cycle,last_node_of_cycle))
      //	if(graph_node->HasPrecedence(gn,first_node_of_cycle,last_node_of_cycle))
      {
#ifdef DEBUG_VISIBILITYGRAPH
	for(int h=0;h<2*global_depth;h++) printf(" ") ;
	printf("Splitting %d\n",gn->id) ;
#endif
	//  Decoupe gn en deux. Le nouveau gn correspond a la partie du fond,
	// il garde le meme numero Id et ses relations avec les autres n'ont
	// donc pas a etre changees. gn_moins est le nouveau bout de gn qui 
	// doit rester devant.

	graph_node->SplitGraphNodeMoins(last_node_of_cycle,vg,gn,gn_moins) ;

	//  Si gn_moins est null cela signifie qu'il n'y a pas d'intersection entre
	// les polygones qui fond le conflit et gn. On passe donc gn devant en donnant
	// sa valeur a gn_moins.

	if(gn_moins == NULL)
	  {
	    gn_moins = gn ;
	    gn_moins->RemoveAncestor(last_node_of_cycle) ;
	    last_node_of_cycle->RemovePrecedence(gn_moins) ;
	    gn = NULL ;
	  }
	else
	  {
	    gn_moins->GetAncestors(gn,last_node_of_cycle) ;
	    gn_moins->GetPrecedences(gn,graph_node) ;
	  }

	gn_moins->UpdatePrecedenceInfo(graph_node) ;
#ifdef DEBUG_VISIBILITYGRAPH
	for(int h=0;h<2*global_depth;h++) printf(" ") ;
	printf("Created %d (%d vertices) Prec:",gn_moins->id,gn_moins->GetPrimitive()->NbVertices()) ;
	gn_moins->PrintPrecedences() ;
	for(int h=0;h<2*global_depth;h++) printf(" ") ;
	printf("self Precedences: ") ;
	graph_node->PrintPrecedences() ;
	for(int h=0;h<2*global_depth;h++) printf(" ") ;
	printf("Node Precedences: ") ;
	if(gn != NULL) gn->PrintPrecedences() ;
#endif
	if(gn_moins != NULL) Insert(gn_moins,vg,Primitive_LOWER,pos) ;
	if(gn != NULL) Insert(gn,vg,Primitive_INDEPENDENT,pos) ;
	return ;
      }
    else
      gn->UpdatePrecedenceInfo(graph_node) ;
      break ;
								
    case Primitive_INTERSECT: // traiter a part les cycles de longueur 2
      {
	Primitive *P_plus,*P_moins ;
	gn->GetPrimitive()->Split(graph_node->GetPrimitive()->Normal(),graph_node->GetPrimitive()->Const(),P_plus,P_moins) ;

	if(P_plus != NULL)
	  {
	    delete(gn->GetPrimitive()) ;
	    gn->SetPrimitive(P_plus) ;
	    gn_plus = gn ;
	  }

	if(P_moins != NULL)
	  {
	    gn_moins = vg->GetNewNode(P_moins) ;
	    gn_moins->GetPrecedences(gn,graph_node) ;				// !! l'ordre est primordial !
	    gn_moins->GetAncestors(gn,graph_node) ;				// !! l'ordre est primordial !
	    //										gn_moins->UpdatePrecedenceInfo(graph_node) ;
	  }

	//									graph_node->UpdatePrecedenceInfo(gn) ;
#ifdef DEBUG_VISIBILITYGRAPH
	if(gn_moins != NULL)
	  {
	    for(int h=0;h<2*global_depth;h++) printf(" ") ;
	    printf("Created %d (%d vertices), Prec:",gn_moins->id,gn_moins->GetPrimitive()->NbVertices()) ;
	    gn_moins->PrintPrecedences() ;
	  }
#endif
#ifdef DEBUG_VISIBILITYGRAPH
	for(int h=0;h<2*global_depth;h++) printf(" ") ;
	printf("self Precedences: ") ;
	graph_node->PrintPrecedences() ;
	for(int h=0;h<2*global_depth;h++) printf(" ") ;
	printf("Node Precedences: ") ;
	gn->PrintPrecedences() ;
#endif
	Insert(gn_moins,vg,Primitive_LOWER,BSP_LOWER) ;
	Insert(gn_plus,vg,Primitive_UPPER,BSP_UPPER) ;
#ifdef DEBUG_VISIBILITYGRAPH
	global_depth-- ;
#endif
	return ;
      }
      break ;
    case Primitive_INDEPENDENT:
#ifdef DEBUG_VISIBILITYGRAPH
      for(int h=0;h<2*global_depth;h++) printf(" ") ;
      printf("self Precedences: ") ;
      graph_node->PrintPrecedences() ;
      for(int h=0;h<2*global_depth;h++) printf(" ") ;
      printf("Node Precedences: ") ;
      gn->PrintPrecedences() ;
#endif
      break ;
    default:
      printf("switch(r_pos): unrecognized case !\n") ;
    }

  if(gn != NULL) BSPInsert(pos,gn,vg) ;
  if(gn_moins != NULL) BSPInsert(pos,gn_moins,vg) ;
  if(gn_plus != NULL) BSPInsert(pos,gn_plus,vg) ;

#ifdef DEBUG_VISIBILITYGRAPH
  global_depth-- ;
#endif
}

void VisibilityBSPNode::BSPInsert(const BSPPosition pos, GraphNode *g,VisibilityGraph *vg)
{
	switch(pos)
	{
		case BSP_LOWER: {
							if(fils_moins == NULL)
								fils_moins = new VisibilityBSPNode(g) ;
							else
								fils_moins->Insert(g,vg) ;
						}
						break ;

		case BSP_UPPER:	{
							if(fils_plus == NULL)
								fils_plus = new VisibilityBSPNode(g) ;
							else
								fils_plus->Insert(g,vg) ;
						}
						break ;

		case BSP_CROSS_PLANE:
						{
							if(fils_moins == NULL)
								fils_moins = new VisibilityBSPNode(g) ;
							else
								fils_moins->Insert(g,vg) ;

							if(fils_plus == NULL)
								fils_plus = new VisibilityBSPNode(g) ;
							else
								fils_plus->Insert(g,vg) ;
						}
						break ;
		default:
			printf("switch(pos): unrecognized case !\n") ;
	}
}

VisibilityBSPNode::VisibilityBSPNode(GraphNode *P)
{
	graph_node = P ;

	fils_moins = NULL ;
	fils_plus  = NULL ;
}

GraphNode::GraphNode(Primitive *p): P(p),nb_prec(0),nb_ans(0),mark(0),nb_strict_prec(0)  
{
#ifdef DEBUG_VISIBILITYGRAPH
	id = ID++ ;
#endif
}

void GraphNode::GetAncestors(GraphNode *g,GraphNode *h)
{
	GraphNode *next ;

	int i=0 ;
	while((next = g->GetNextAncestorNode(i)) != NULL)
		if(next != h)
		{
			AddToAncestors(next) ;
			next->AddToStrictPreceeding(this) ;
		}
}

void GraphNode::GetPrecedences(GraphNode *g,GraphNode *h)
{
	GraphNode *next ;

	int i=0 ;
	while((next = g->GetNextStrictPrecedenceNode(i)) != NULL)
		if(next != h)
		{
			AddToStrictPreceeding(next) ;
			next->AddToAncestors(this) ;
		}
}

void GraphNode::UpdatePrecedenceInfo(GraphNode *p)
{
#ifdef DEBUG_VISIBILITYGRAPH
	for(int i=0;i<nb_strict_prec;i++)
		if(StrictPrecedenceTab[i] == p)
			printf("GraphNode::UpdatePrecedenceInfo: Warning: already present node %d in strict prec tab of %d !\n",p->id,id) ;
#endif

	AddToStrictPreceeding(p) ;
	p->AddToAncestors(this) ;
}

void GraphNode::RemoveAncestor(GraphNode *p)
{
	for(int i=0;i<nb_ans;i++)
		if(AncestorTab[i] == p)
		{
			AncestorTab[i] = AncestorTab[nb_ans-1] ;
			nb_ans-- ;
			i-- ;
		}
}

void GraphNode::RemovePrecedence(GraphNode *p)
{
	for(int i=0;i<nb_strict_prec;i++)
		if(StrictPrecedenceTab[i] == p)
		{
			StrictPrecedenceTab[i] = StrictPrecedenceTab[nb_strict_prec-1] ;
			nb_strict_prec-- ;
			i-- ;
		}
}

void GraphNode::AddToAncestors(GraphNode *p) 
{ 
	for(int i=0;i<nb_ans;i++)
		if(AncestorTab[i] == p)
			return ;

	AncestorTab.AddElem(nb_ans++,p) ; 
}
void GraphNode::AddToStrictPreceeding(GraphNode *p) 
{ 
	for(int i=0;i<nb_strict_prec;i++)
		if(StrictPrecedenceTab[i] == p)
			return ;

	StrictPrecedenceTab.AddElem(nb_strict_prec++,p) ; 
}

bool GraphNode::HasStrictPrecedence(const GraphNode *p) const
{
	for(int i=0;i<nb_strict_prec;i++)
		if(StrictPrecedenceTab[i] == p)
			return true ;

	return false ;
}

// Cherche recursivement si le noeud a p comme precedent. Si oui, il renvoie le parent et le fils
// direct de p dans la chaine ce noeud.

bool GraphNode::HasPrecedence(GraphNode *p,GraphNode * & begin_cycle,GraphNode * & end_cycle,
										unsigned int current_mark) 
{
	if(mark == current_mark)
		return false ;

	for(int i=0;i<nb_strict_prec;i++)
		if(StrictPrecedenceTab[i] == p)
		{
			end_cycle = this ;
			begin_cycle = p ;
			return true ;
		}
#ifdef DEBUG_VISIBILITYGRAPH
		else if(StrictPrecedenceTab[i] == NULL)
		{
			cout << "Error in precedence tab of GraphNode " << id << " : tab has size " << nb_strict_prec << " and value is null at " << i << endl ;
			return false ;
		}
#endif
		else if(StrictPrecedenceTab[i]->HasPrecedence(p,begin_cycle,end_cycle,current_mark))
		{
			begin_cycle = StrictPrecedenceTab[i] ;
			return true ;
		}

	mark = current_mark ;
	return false ;
}

#ifdef DEBUG_VISIBILITYGRAPH
void GraphNode::PrintPrecedences() const
{
	for(int i=0;i<nb_strict_prec;i++)
		printf(" %d",StrictPrecedenceTab[i]->id) ; 

	printf(" (Strict)") ;

	for(int i=0;i<nb_prec;i++)
		printf(" %d",PrecedenceTab[i]->id) ; 

	printf(" (large)") ;

	for(int i=0;i<nb_ans;i++)
		printf(" %d",AncestorTab[i]->id) ; 

	printf(" (anc)\n") ;
}
#endif

//----------------------------------------------------------------------------//

void Polygone::InitNormal()
{
	FLOAT anglemax = 0.0 ;
	Vect3 normalmax(0.0,0.0,0.0) ;
	FLOAT v12norm = (Vertex(1)-Vertex(0)).Norm() ;

	for(int i=0;i<nVertex;i++)
	{
		DVect3 v1(Vertex(i)) ;
		DVect3 v2(Vertex((i+1)%nVertex)) ;
		DVect3 v3(Vertex((i+2)%nVertex)) ;

		Vect3 normal_tmp((v3-v2)^(v1-v2)) ;

		FLOAT v32norm = (v3-v2).Norm() ;

		if(normal_tmp.Z < 0)
			normal_tmp *= -1.0 ;

		if((v32norm > 0.0)&&(v12norm > 0.0))
		{
			double anglemaxtmp = normal_tmp.Norm()/v32norm/v12norm ;
			
			if(anglemaxtmp > anglemax)
			{
				anglemax = anglemaxtmp ;
				normalmax = normal_tmp ;
			}
		}
//		cout << v1-v2 << endl ;
//		cout << v3-v2 << endl ;
//		cout << "Normal " << i << " = " << normal << endl ;
//		cout << "Coef = " << normal.NormInf() / (v1-v2).NormInf() / (v3-v2).NormInf() << endl ;

		v12norm = v32norm ;

		if(anglemax > FLAT_POLYGON_EPS)	// slight optimization
			break ;
	}

	normal = normalmax ;
	anglefactor = anglemax ;

	if(normal.NormInf() != 0.0)
		normal.Normalize() ;

	C = normal*Vertex(0) ;
}

void Feedback3Dcolor::InitNormal()
{
	// choose a normal for which z != 0
	Vect3 dir(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX,1.0) ;
	dir.Normalize() ;
	normal = dir ;

#ifdef A_VIRER
	// this never happens
	if(normal.Z < 0.0)
		normal *= -1.0 ;
#endif

	C = normal*Vect3(x,y,z) ;
}

void Polygone::CheckInfoForPositionOperators()
{
	if(SommetsProjetes == NULL)
	{
		C = Vect3(Vertex(0)) * Normal() ;

		MakeCoordinateSystem(L, M, Normal()) ;
		SommetsProjetes = new FLOAT[2*NbVertices()] ;

		for(int jj=0;jj<NbVertices();jj++)
			ProjectPoint(L,M,Normal(),C,Vertex(jj),SommetsProjetes[2*jj],SommetsProjetes[2*jj+1]) ;
	}
}

GraphNode *GraphNode::GetNextStrictPrecedenceNode(int& i)
{
	if(i < nb_strict_prec)
		return StrictPrecedenceTab[i++] ;
	else
		return NULL ;
}

GraphNode *GraphNode::GetNextAncestorNode(int& i)
{
	if(i < nb_ans)
		return AncestorTab[i++] ;
	else
		return NULL ;
}

GraphNode *GraphNode::GetNextPrecedenceNode(int& i)
{
	if(i < nb_prec)
		return PrecedenceTab[i++] ;
	else
		return NULL ;
}

GraphNode *VisibilityGraph::GetNewNode(Primitive *P)
{
	GraphNode *res = new GraphNode(P) ;
	GraphNodes.AddElem(NbNodes++, res) ;

	return res ;
}

void VisibilityGraph::Insert(Primitive *P)
{
	GraphNode *g = GetNewNode(P) ;
#ifdef DEBUG_VISIBILITYGRAPH
	global_depth = 0 ;
	printf("VisibilityGraph %08x inserting Primitive %08x, GraphNode #%d\n",this,P,g->id) ;
#endif

	if(RootNode == NULL)
		RootNode = new VisibilityBSPNode(g) ;
	else
		RootNode->Insert(g,this) ;
}

VisibilityGraph::VisibilityGraph()
{
#ifdef DEBUG_VISIBILITYGRAPH
	GraphNode::ID = 0 ;
#endif
	NbNodes = 0 ;
	RootNode = NULL ;
}

void VisibilityGraph::GetPrimitiveTab(Primitive**& tab, long int & nb) const
{
	nb = NbNodes ;
	tab = new Primitive *[NbNodes] ;

	for(int i=0;i<NbNodes;i++)
		tab[i] = GraphNodes[i]->GetPrimitive() ;
}

// a coder en fonction des priorites.

#ifdef DEBUG_EPSRENDER
void VisibilityGraph::Render(FILE *f,int drm, int format)
#else
void VisibilityGraph::Render(FILE *,int, int)
#endif
{
#ifdef DEBUG_VISIBILITYGRAPH
	printf("VisibilityGraph: Rendering %d primitives.\n",NbNodes) ;

	printf("State of all primitives:\n") ;
	for(int i=0;i<NbNodes;i++)
	{
		printf("Node % 2d: ",GraphNodes[i]->id) ;
		GraphNodes[i]->PrintPrecedences() ;
	}
#endif

	for(int i=0;i<NbNodes;i++)
		GraphNodes[i]->SetRenderingState(NOT_RENDERED) ;

#ifdef DEBUG_VISIBILITYGRAPH
	printf("Rendering order:") ;
#endif
	//  Appelle le rendu dans l'ordre de indique par le BSP. Chaque primitive est
	// de plus rendue en conformite avec ses priorites strictes par le sous appel de
	// VisiblityGraph::RecursRender()
	

#ifdef DEBUG_EPSRENDER
	printf("\n") ;
	int depth = 999 ;
	int nbConflicts = 0 ;
	int nbprims = RootNode->RecursRenderBackToFront(f,drm,format,depth,nbConflicts) ;
	printf("VisibilityGraph: %d primitives rendered, %d conflicts detected.\n",nbprims,nbConflicts) ;
#endif
}

int VisibilityBSPNode::RecursRenderBackToFront(FILE *f,int drm,int format,int& depth,int& nbc)
{
	int res = 0 ;

	if(fils_plus != NULL)
		res += fils_plus->RecursRenderBackToFront(f,drm,format,depth,nbc) ;

	res += VisibilityGraph::RecursRender(graph_node,f,drm,format,depth,nbc) ;

	if(fils_moins != NULL)
		res += fils_moins->RecursRenderBackToFront(f,drm,format,depth,nbc) ;

	return res ;
}

//  Effectue le rendu d'une primitive en respectant les priorites calculees 
// dans le graph de precedence.
int VisibilityGraph::RecursRender(GraphNode *Gn,FILE *f,int drm, int format,int& depth,int& nbConflicts)
{
	int res = 0 ;

	if(Gn->GetRenderingState() == RENDERED)
		return res ;

	GraphNode *next ;
	int i=0 ;

	Gn->SetRenderingState(WAITING) ;

	while((next = Gn->GetNextStrictPrecedenceNode(i)) != NULL)
	{
		if(next->GetRenderingState() == WAITING)	// il faudrait couper.
			nbConflicts++ ;
		else
			res += RecursRender(next,f,drm,format,depth,nbConflicts) ;
	}

	if(Gn->GetPrimitive()->GetVisibility() == 1)
	{
		Gn->GetPrimitive()->spew(f,drm,format,depth) ;
		res++ ;
	}

	Gn->SetRenderingState(RENDERED) ;

	if(depth > 0) depth-- ;
#ifdef DEBUG_VISIBILITYGRAPH
	printf(" %d",Gn->id) ;
#endif

	return res ;
}

#ifdef DEBUG_VISIBILITYGRAPH
const char *VisibilityGraph::GetPositionName(XYZRelativePosition p)
{
	const char *Pnames[] = { "Unknown","Lower","Upper","Independent","Intersect" } ;

	return Pnames[p] ;
}
#endif
