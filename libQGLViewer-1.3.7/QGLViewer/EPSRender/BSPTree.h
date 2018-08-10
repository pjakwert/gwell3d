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

#ifndef _BSPTREE_H_
#define _BSPTREE_H_

#include "Geometry.h"

typedef enum { BSP_CROSS_PLANE, BSP_UPPER, BSP_LOWER } BSPPosition ;

class BSPNode
{
	public:
		BSPNode(Polygone *) ;

		void RecursDelete() ;

		double a,b,c,d ;

		BSPNode *fils_moins ;
		BSPNode *fils_plus ;

		ListeDeSegments *seg_plus ;
		ListeDeSegments *seg_moins ;

		ListeDePoints *pts_plus ;
		ListeDePoints *pts_moins ;

		Polygone *polygone ;

		int Render(FILE *, int,int,int &) ;
		int Render(ListeDePoints *,FILE *,int,int,int &) ;
		int Render(ListeDeSegments *,FILE *,int,int,int &) ;

		unsigned long int RecursCountElements() ;
		void RecursGetPrimitives(Primitive **, unsigned long int &) ;

		void Insert(Polygone *) ;
		void Insert(Segment *) ;
		void Insert(Feedback3Dcolor *) ;

		void Classify(Polygone *, Polygone * &, Polygone * &) ;
		void Classify(Segment *, Segment * &, Segment * &) ;
		int  Classify(Feedback3Dcolor *) ;
} ;

class BSPTree: public OrderingStructure
{
	public:
		BSPTree() ;
		virtual ~BSPTree() ;

		virtual void Insert(Polygone *) ;
		virtual void Insert(Segment *) ;
		virtual void Insert(Feedback3Dcolor *) ;

		virtual void Render(FILE *, int,int) ;

		virtual void GetPrimitiveTab(Primitive ** &, long int &) const ;
#ifdef DEBUGEPSRENDER
		static const char *GetPositionName(BSPPosition) ;
#endif

	protected:
		BSPNode *Root ;
		ListeDePoints *pts_list ;
		ListeDeSegments *seg_list ;
} ;

#endif
