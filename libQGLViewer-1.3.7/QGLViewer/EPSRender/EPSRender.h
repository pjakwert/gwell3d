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

//      This library implements the rendering of some OpenGL primitives
//     in Postscript or XFig3.2 format. The currently supported primitives 
//     are LINES, POINTS, POLYGONS. Others, as BITMAPS are discarded.
//      The depth ordering of the primitives is done using a BSP tree.
//     Optimisations methods use an item buffer through offscreen rendering. The
//     library must therfore be used with the offscreen library -lOffScreen.
//
// To use it
// ---------
//
//     call EPSRender using appropriate parameter values:
//
//	size:	 This is the size of the memory required by the algorithm. The first time, call
//	====	EPSRender with size=0 if you don't know and save the value after the call.
//			You can use it for next call and thus save some memory allocation time.
//
//  SortMethod:	 Three kinds of sorting are provided:
//	==========		
//                 EPS_DONT_SORT:     Primitives are spewed whatever their depth. No visibility is
//                                   therefore accounted for. Usefull for 2D drawings, because
//                                   the order of drawing the diff. primitives is still respected.
//                 EPS_BSP:           The library uses a bsp to cut and sort primitives. This 
//								     works fine except that many polygons are cut into small
//								     unnecessary triangles.
//                 EPS_OPTIMIZED_BSP: A BSP is used but only primitives that intersect or create
//                                   cycles are cut. Slower but gives better results. Not fully
//                                   debug yet.
//                  
//	==========	 No visibility is much faster, but loses hidden/visible 
//				relations. See codes below.
//
//	filename:	 Output file name. Not modified by the algorithm.
//  ========
//
//	TightenBB:	 Tight bounding box in ps or eps file to the contents of the image. 
//  =========	Produces no effect with fig output.
//
//	DrawFunc:	 A drawing callback containing OpenGL calls. This callback MUST NOT contain
//	========	any call to GLwMakeCurrent, GLxSwapBuffers, GLFinish, GLReadPixels ...
//				ONLY Drawing primitives.
//
//	params:		 A (void *) parameter passed to DrawFunc by EPSRender. Sometimes useful. to 
//  ======
//
//	EPSRender_Error:	Error state after EPSRender returned. See codes below.
//  ===============
//
//	DrawMode:	Use EPS_COLOR if you want to keep original colors. Using EPS_BLACK_AND_WHITE
//	========	makes all LINES and POINTS black and all polygons WHITE. See codes below.
//
//	EPSMode:	 Output format. XFig3.2 (EPS_FIG), Postscript (EPS_PS) and Encapsulated 
//	=======		postscript (EPS_EPS) are supported.
//
//	Optimization mode: for now, there is the following possibilities:
//  =================
//
//		EPS_NO_OPTIMIZATION:	 Renders every graphic primitives. Usefull for fig 
//								format when you	want to modify the figure.
//		
//		EPS_CULL_INVISIBLE_PRIMITIVES:	 Do not render faces and edges that lie behind other 
//									primitives	and consequently do not appear in the image.
//									This optimization requires offscreen rendering in a buffer
//									that provides a sufficient number of depth bits.
//
// BackGroundClear:   Includes a rectangle that clears the background in the output EPS and PS 
// ===============   files. This parameter has no effect in xfig format.
//
// BUGS
// ----
//			- The gl FeedBack mode does not work well with glPolygonOffset extension. You
//			 should preferably use glDepthRange to move polygons forward.
//
//			- On Onyx2-InfiniteReality, the feedback mode has some bugs that render polygons
//			 with depth 0. These polygons are consequently rendered in the front side of the
//			 image after beeing read in the feedBack buffer. This arrives very rarely, and
//			 may appear when rendering parallel polygons.
//
//			- The library itself has no bugs, of course...
//
// Version:
// -------
//
//           @(#)EPSRender.h	1.13 7/21/99
//

#ifndef _EPSRENDER_H_
#define _EPSRENDER_H_

namespace EpsRenderer 
{
	// Sorting codes

const int EPS_DONT_SORT      = 0 ;
const int EPS_BSP            = 1 ;
const int EPS_OPTIMIZED_BSP  = 2 ;

	// Background clearing codes

const int EPS_DONT_CLEAR_BG = 0 ;
const int EPS_CLEAR_BG      = 1 ;

	// Color mode codes

const int EPS_COLOR 			= 0 ;
const int EPS_BLACK_AND_WHITE = 1 ;

	// Format codes

const int EPS_PS  = 0 ;
const int EPS_EPS = 1 ;
const int EPS_FIG = 2 ;

	// Optimisation modes

const int EPS_NO_OPTIMIZATION 			= 0 ;
const int EPS_CULL_INVISIBLE_PRIMITIVES 	= 1 ;

	// Optimisation modes

const int EPS_TIGHTEN_BBOX 		= 	0 ;
const int EPS_NORMAL_BB				= 1 ;

	// Error codes

const int EPSRENDER_NO_ERROR           = 0 ;
const int EPSRENDER_OUT_OF_MEMORY      = 1 ;
const int EPSRENDER_CANNOT_OPEN_FILE   = 2 ;
const int EPSRENDER_FILENAME_NOT_VALID = 3 ;

	typedef void (*RenderCB)(void *) ;

	void EPSRender(	int &			size, 
			int			SortMethod, 
			const char *FileName, 
			RenderCB		DrawFunc, 
			void		  *params, 
			int &			EPSRender_Error, 
			int			DrawMode							= EPS_COLOR,
			int			EPSMode							= EPS_EPS,
			int			VisibilityOptimisation		= EPS_NO_OPTIMIZATION,
			int			BackGroundClear				= EPS_CLEAR_BG,
			int			TightenBB						= EPS_NORMAL_BB
			) ;

}
#endif
