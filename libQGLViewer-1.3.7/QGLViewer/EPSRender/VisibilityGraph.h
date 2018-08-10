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

#ifndef _VISIBILITYGRAPH_H_
#define _VISIBILITYGRAPH_H_

#include "Geometry.h"
#include "SecuredArray.h"

class GraphNode ;
class VisibilityGraph ;

typedef enum { 	Primitive_UNKNOWN,
		Primitive_LOWER,Primitive_UPPER,
		Primitive_INDEPENDENT,Primitive_INTERSECT } XYZRelativePosition ;

class VisibilityBSPNode
{
	public:
		VisibilityBSPNode(GraphNode *) ;

		void RecursDelete() ;
		void Insert(GraphNode *,VisibilityGraph *) ;
		void Insert(GraphNode *,VisibilityGraph *,XYZRelativePosition,BSPPosition) ;
		int RecursRenderBackToFront(FILE *,int,int,int&,int&) ;

	protected:
		VisibilityBSPNode *fils_moins ;
		VisibilityBSPNode *fils_plus ;

		bool testPrecedence(GraphNode *,GraphNode *,GraphNode *&,GraphNode *&) ;
		void Classify(Primitive *, XYZRelativePosition &, BSPPosition &,const VisibilityGraph *) ;
		void BSPInsert(const BSPPosition, GraphNode *,VisibilityGraph *) ;

		void InvertPosition(XYZRelativePosition &) ;
		bool SimplePositionTest(int[],int,int,int,bool,
								XYZRelativePosition &,BSPPosition &) ;

		GraphNode *graph_node ;
} ;

class VisibilityBSPTree
{
	public:
		VisibilityBSPTree() ;
		~VisibilityBSPTree() ;

		void Insert(Primitive *) ;
		void Render(FILE *, int,int) ;

	protected:
		VisibilityBSPNode *Root ;
} ;

typedef enum { NOT_RENDERED, RENDERED, WAITING } RenderingState ;

class GraphNode
{
	public:
		GraphNode(Primitive *) ;

		void AddPrecedence(GraphNode *) ;
		bool HasPrecedence(GraphNode *,GraphNode *&,GraphNode *&,unsigned int) ;
//		bool RemoveConflict(const GraphNode *p) ;
		bool HasStrictPrecedence(const GraphNode *) const ;
		Primitive *GetPrimitive() { return P ; }
		void SetPrimitive(Primitive *p) { P = p ; }

		GraphNode *GetNextPrecedenceNode(int &) ;
		GraphNode *GetNextStrictPrecedenceNode(int &) ;
		GraphNode *GetNextAncestorNode(int &) ;

		void SetRenderingState(RenderingState RS) { rs = RS ; }
		RenderingState GetRenderingState() { return rs ; }
	
		void GetPrecedences(GraphNode *,GraphNode *) ;
		void GetAncestors(GraphNode *,GraphNode *) ;
		void AddToAncestors(GraphNode *) ;
		void RemovePrecedence(GraphNode *) ;
		void RemoveAncestor(GraphNode *) ;
		void AddToStrictPreceeding(GraphNode *) ;
		void AddToPreceeding(GraphNode *) ;

		void UpdatePrecedenceInfo(GraphNode *) ;

		void SplitPrimitive(const Primitive *,const Primitive *, Primitive*,
							Primitive *&, Primitive *&) ;

#ifdef DEBUG_VISIBILITYGRAPH
		void PrintPrecedences() const ;
		int id ;
		static int ID ;
#endif
		static void AddIntersectionProjectedPoints(const Primitive *,const Primitive *,
									SecuredArray<Vect2> &,int &) ;

		void SplitGraphNodePlus(GraphNode *,VisibilityGraph *,GraphNode *,GraphNode *&) ;
		void SplitGraphNodeMoins(GraphNode *,VisibilityGraph *,GraphNode *,GraphNode *&) ;

		const SecuredArray<GraphNode *> & GSP_BeginCycle(GraphNode *,int & ) ;
		const SecuredArray<GraphNode *> & GSP_EndCycle(GraphNode *,int & ) ;
	protected:
		Primitive *P ;
		SecuredArray<GraphNode *> AncestorTab ;
		SecuredArray<GraphNode *> PrecedenceTab ;
		SecuredArray<GraphNode *> StrictPrecedenceTab ;
		int nb_prec ;
		int nb_ans ;
		unsigned int mark ;
		int nb_strict_prec ;
		int depth ;
		RenderingState rs ;
} ;

class VisibilityGraph: public OrderingStructure
{
	public:
		VisibilityGraph() ;
		virtual ~VisibilityGraph() {};

		virtual void Insert(Polygone *P) { Insert((Primitive *)P) ; }
		virtual void Insert(Segment *S)  { Insert((Primitive *)S) ; } 
		virtual void Insert(Feedback3Dcolor *P)  { Insert((Primitive *)P) ; }

		virtual void Render(FILE *, int,int) ;

		GraphNode *GetNewNode(Primitive *) ;

		virtual void GetPrimitiveTab(Primitive ** &, long int &) const ;

		void Insert(Primitive *) ;
		void SuppressNode(GraphNode *) ;
		static int RecursRender(GraphNode *,FILE *,int,int,int&,int&) ;

#ifdef DEBUG_VISIBILITYGRAPH
		static const char *GetPositionName(XYZRelativePosition) ;
#endif

	protected:
		void UpdateVisibilityRelations(int) ;

		SecuredArray<GraphNode *> GraphNodes ;
		int NbNodes ;

		VisibilityBSPNode *RootNode ;
} ;

#endif
