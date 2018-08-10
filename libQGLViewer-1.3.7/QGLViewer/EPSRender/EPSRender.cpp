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
// @(#)EPSRender.C	1.16 12/27/00
//

/* Copyright (c) Mark J. Kilgard, 1997. */

/* This program is freely distributable without licensing fees 
   and is provided without guarantee or warrantee expressed or 
   implied. This program is -not- in the public domain. */

/* Example showing how to use OpenGL's feedback mode to capture
   transformed vertices and output them as Encapsulated PostScript.
   Handles limited hidden surface removal by sorting and does
   smooth shading (albeit limited due to PostScript). */

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "Functions.h"
#include "Affichage.h"
#include "EPSRender.h"
#include "BSPTree.h"
#include "VisibilityGraph.h"

#define FORMAT_EPS 0
#define FORMAT_FIG 1

using namespace std;
using namespace EpsRenderer ;

#define EPS_SMOOTH_LINE_FACTOR 0.06  /* Lower for better smooth lines. */

/* OpenGL's GL_3D_COLOR feedback vertex format. */

int blackBackground = 0;  /* Initially use a white background. */
int lighting = 0;       /* Initially disable lighting. */
int polygonMode = 1;    /* Initially show wireframe. */
int object = 1;         /* Initially show the torus. */

GLfloat angle = 0.0;    /* Angle of rotation for object. */
int moving, begin;      /* For interactive object rotation. */
int size = 1;           /* Size of lines and points. */

/* How many feedback buffer GLfloats each of the three objects need. */
int objectComplexity[3] =
{6000, 14000, 380000};  /* Teapot requires ~1.5 megabytes for
                           its feedback results! */

/* Write contents of one vertex to stdout. */

void print3DcolorVertex(GLint size, GLint * count,
  GLfloat * buffer)
{
  int i;

  printf("  ");
  for (i = 0; i < 7; i++) {
    printf("%4.2f ", buffer[size - (*count)]);
    *count = *count - 1;
  }
  printf("\n");
}

void printBuffer(GLint size, GLfloat * buffer)
{
  GLint count;
  int token, nvertices;

  count = size;
  while (count) {
    token = int(buffer[size - count]);
    count--;
    switch (token) 
	 {
   	 case GL_PASS_THROUGH_TOKEN:
   	   printf("GL_PASS_THROUGH_TOKEN\n");
   	   printf("  %4.2f\n", buffer[size - count]);
   	   count--;
   	   break;
   	 case GL_POINT_TOKEN:
   	   printf("GL_POINT_TOKEN\n");
   	   print3DcolorVertex(size, &count, buffer);
   	   break;
   	 case GL_LINE_TOKEN:
   	   printf("GL_LINE_TOKEN\n");
   	   print3DcolorVertex(size, &count, buffer);
   	   print3DcolorVertex(size, &count, buffer);
   	   break;
   	 case GL_LINE_RESET_TOKEN:
   	   printf("GL_LINE_RESET_TOKEN\n");
   	   print3DcolorVertex(size, &count, buffer);
   	   print3DcolorVertex(size, &count, buffer);
   	   break;
   	 case GL_POLYGON_TOKEN:
   	   printf("GL_POLYGON_TOKEN\n");
   	   nvertices = int(buffer[size - count]) ;
   	   count--;
   	   for (; nvertices > 0; nvertices--) 
   	     print3DcolorVertex(size, &count, buffer);
    }
  }
}

GLfloat pointSize;

static const char *gouraudtriangleEPS[] =
{
  "/bd{bind def}bind def /triangle { aload pop   setrgbcolor  aload pop 5 3",
  "roll 4 2 roll 3 2 roll exch moveto lineto lineto closepath fill } bd",
  "/computediff1 { 2 copy sub abs threshold ge {pop pop pop true} { exch 2",
  "index sub abs threshold ge { pop pop true} { sub abs threshold ge } ifelse",
  "} ifelse } bd /computediff3 { 3 copy 0 get 3 1 roll 0 get 3 1 roll 0 get",
  "computediff1 {true} { 3 copy 1 get 3 1 roll 1 get 3 1 roll 1 get",
  "computediff1 {true} { 3 copy 2 get 3 1 roll  2 get 3 1 roll 2 get",
  "computediff1 } ifelse } ifelse } bd /middlecolor { aload pop 4 -1 roll",
  "aload pop 4 -1 roll add 2 div 5 1 roll 3 -1 roll add 2 div 3 1 roll add 2",
  "div 3 1 roll exch 3 array astore } bd /gouraudtriangle { computediff3 { 4",
  "-1 roll aload 7 1 roll 6 -1 roll pop 3 -1 roll pop add 2 div 3 1 roll add",
  "2 div exch 3 -1 roll aload 7 1 roll exch pop 4 -1 roll pop add 2 div 3 1",
  "roll add 2 div exch 3 -1 roll aload 7 1 roll pop 3 -1 roll pop add 2 div 3",
  "1 roll add 2 div exch 7 3 roll 10 -3 roll dup 3 index middlecolor 4 1 roll",
  "2 copy middlecolor 4 1 roll 3 copy pop middlecolor 4 1 roll 13 -1 roll",
  "aload pop 17 index 6 index 15 index 19 index 6 index 17 index 6 array",
  "astore 10 index 10 index 14 index gouraudtriangle 17 index 5 index 17",
  "index 19 index 5 index 19 index 6 array astore 10 index 9 index 13 index",
  "gouraudtriangle 13 index 16 index 5 index 15 index 18 index 5 index 6",
  "array astore 12 index 12 index 9 index gouraudtriangle 17 index 16 index",
  "15 index 19 index 18 index 17 index 6 array astore 10 index 12 index 14",
  "index gouraudtriangle 18 {pop} repeat } { aload pop 5 3 roll aload pop 7 3",
  "roll aload pop 9 3 roll 4 index 6 index 4 index add add 3 div 10 1 roll 7",
  "index 5 index 3 index add add 3 div 10 1 roll 6 index 4 index 2 index add",
  "add 3 div 10 1 roll 9 {pop} repeat 3 array astore triangle } ifelse } bd",
  NULL
};

void NormalizePrimitiveCoordinates(GLfloat * & loc,GLfloat MaxSize,GLfloat zmin,GLfloat zmax)
{
	int token;
	int nvertices, i;

	token = int(*loc) ;
	loc++;

	switch (token) 
	{
		case GL_LINE_RESET_TOKEN:
		case GL_LINE_TOKEN:
		{
		    for (i = 0; i < 2; i++) 
				(loc+7*i)[2] = ((loc+7*i)[2] - zmin)/(zmax-zmin)*MaxSize ;

		    loc += 14;          /* Each vertex element in the feedback
                           buffer is 7 GLfloats. */
		    break;
		}
		case GL_POLYGON_TOKEN:
		{
			nvertices = int(*loc) ;
			loc++;

        	for (i = 0; i < nvertices; i++) 
				(loc+7*i)[2] = ((loc+7*i)[2] - zmin)/(zmax-zmin)*MaxSize ;

			loc += nvertices * 7;  /* Each vertex element in the
           		                   feedback buffer is 7 GLfloats. */
		    break;
		}
		case GL_POINT_TOKEN:
		{
			loc[2] = (loc[2] - zmin)/(zmax-zmin)*MaxSize ;

   			loc += 7;           /* Each vertex element in the feedback
                           buffer is 7 GLfloats. */
    		break;
		}
	  default:
   			 /* XXX Left as an excersie to the reader. */
			    printf("Incomplete implementation.  Unexpected token (%d).\n", token);
	}
}

void ComputePrimitiveBB(GLfloat * & loc,GLfloat & xmin,GLfloat & xmax,GLfloat & ymin,GLfloat & ymax, GLfloat & zmin,GLfloat & zmax)
{
	int token;
	int nvertices, i;

	token = int(*loc) ;
	loc++;

	switch (token) 
	{
		case GL_LINE_RESET_TOKEN:
		case GL_LINE_TOKEN:
		{
		    for (i = 0; i < 2; i++) 
			{
				Feedback3Dcolor f(loc+7*i) ;

				if(f.X() < xmin) xmin = f.X() ;
				if(f.Y() < ymin) ymin = f.Y() ;
				if(f.Z() < zmin) zmin = f.Z() ;
				if(f.X() > xmax) xmax = f.X() ;
				if(f.Y() > ymax) ymax = f.Y() ;
				if(f.Z() > zmax) zmax = f.Z() ;
		    }

		    loc += 14;          /* Each vertex element in the feedback
                           buffer is 7 GLfloats. */
		    break;
		}
		case GL_POLYGON_TOKEN:
		{
			nvertices = int(*loc) ;
			loc++;

        	for (i = 0; i < nvertices; i++) 
			{
				Feedback3Dcolor f(loc+7*i) ;

				if(f.X() < xmin) xmin = f.X() ;
				if(f.Y() < ymin) ymin = f.Y() ;
				if(f.Z() < zmin) zmin = f.Z() ;
				if(f.X() > xmax) xmax = f.X() ;
				if(f.Y() > ymax) ymax = f.Y() ;
				if(f.Z() > zmax) zmax = f.Z() ;
			}

			loc += nvertices * 7;  /* Each vertex element in the
           		                   feedback buffer is 7 GLfloats. */
		    break;
		}
		case GL_POINT_TOKEN:
		{
			Feedback3Dcolor f(loc) ;

			if(f.X() < xmin) xmin = f.X() ;
			if(f.Y() < ymin) ymin = f.Y() ;
			if(f.Z() < zmin) zmin = f.Z() ;
			if(f.X() > xmax) xmax = f.X() ;
			if(f.Y() > ymax) ymax = f.Y() ;
			if(f.Z() > zmax) zmax = f.Z() ;

   			loc += 7;           /* Each vertex element in the feedback
                           buffer is 7 GLfloats. */
    		break;
		}
	  default:
   			 /* XXX Left as an excersie to the reader. */
			    printf("Incomplete implementation.  Unexpected token (%d).\n", token);
	}
}

void NormalizeBufferCoordinates(GLint size, GLfloat * buffer,
						GLfloat MaxSize, GLfloat zmin,GLfloat zmax)
{
	GLfloat *loc, *end;

	if(zmax == zmin)
	{
#ifdef DEBUGEPSRENDER
		printf("Warning: zmin = zmax in NormalizePrimitiveCoordinates\n") ;
#endif
		return ;
	}

	loc = buffer;
	end = buffer + size;

	while (loc < end) 
		NormalizePrimitiveCoordinates(loc,MaxSize,zmin,zmax);
}

void ComputeBufferBB(GLint size, GLfloat * buffer,
						GLfloat & xmin, GLfloat & xmax, 
						GLfloat & ymin, GLfloat & ymax,
						GLfloat & zmin, GLfloat & zmax)
{
	GLfloat *loc, *end;

	loc = buffer;
	end = buffer + size;

	while (loc < end) 
		ComputePrimitiveBB(loc,xmin,xmax,ymin,ymax,zmin,zmax);
}

typedef struct _DepthIndex {
  GLfloat *ptr;
  GLfloat depth;
} DepthIndex;

#define EPS_GOURAUD_THRESHOLD 0.1  /* Lower for better (slower) smooth shading. */

void spewWireFrameEPS(FILE * file, int SortMethod, GLint size, GLfloat * buffer, 
							char *creator,int DrawMode, int EPSMode,int VisibilityOptimisation, 
							int ClearBG, int TightenBB)
{
	GLfloat clearColor[4], viewport[4];
	GLfloat lineWidth;
	int i;

	/* Read back a bunch of OpenGL state to help make the EPS
   		consistent with the OpenGL clear color, line width, point
   		size, and viewport. */

	glGetFloatv(GL_VIEWPORT, viewport);
	glGetFloatv(GL_COLOR_CLEAR_VALUE, clearColor);
	glGetFloatv(GL_LINE_WIDTH, &lineWidth);
	glGetFloatv(GL_POINT_SIZE, &pointSize);

	lineWidth /= (float)Max(viewport[2] - viewport[0],viewport[3]-viewport[1]) ;

	sizeX = int(0.5f + viewport[2]-viewport[0]) ;
	sizeY = int(0.5f + viewport[3]-viewport[1]) ;

	/* Emit EPS header. */

	fputs("%!PS-Adobe-2.0 EPSF-2.0\n", file);

	/* Notice %% for a single % in the fprintf calls. */

	fprintf(file, "%%%%Creator: %s (using OpenGL feedback)\n", creator);

	GLfloat xmin = FLT_MAX ;
	GLfloat ymin = FLT_MAX ;
	GLfloat zmin = FLT_MAX ;
	GLfloat xmax = -FLT_MAX ;
	GLfloat ymax = -FLT_MAX ;
	GLfloat zmax = -FLT_MAX ;

	ComputeBufferBB(size, buffer, xmin,xmax,ymin,ymax,zmin,zmax) ;

#ifdef DEBUGEPSRENDER
	printf("Buffer bounding box: %f %f %f %f %f %f\n",xmin,xmax,ymin,ymax,zmin,zmax) ;
#endif
	float Zdepth = Max(ymax-ymin,xmax-xmin) ;
	NormalizeBufferCoordinates(size,buffer,Zdepth,zmin,zmax) ;

#ifdef DEBUGEPSRENDER
	ComputeBufferBB(size, buffer, xmin,xmax,ymin,ymax,zmin,zmax) ;
	printf("New bounding box: %f %f %f %f %f %f\n",xmin,xmax,ymin,ymax,zmin,zmax) ;
#endif
	if(TightenBB == EPS_TIGHTEN_BBOX)
	{
		if(xmin > xmax)
		{
			printf("EPSRender: Error. Void bounding box in x !\n") ;
			xmin = xmax = 0 ;
		}

		if(ymin > ymax)
		{
			printf("EPSRender: Error. Void bounding box in y !\n") ;
			ymin = ymax = 0 ;
		}

		fprintf(file, "%%%%BoundingBox: %g %g %g %g\n", xmin,ymin,xmax,ymax);
	}
	else
		fprintf(file, "%%%%BoundingBox: %g %g %g %g\n", viewport[0], viewport[1], viewport[2], viewport[3]);

	fputs("%%EndComments\n", file);
	fputs("\n", file);
	fputs("gsave\n", file);
	fputs("\n", file);

	fputs("%\n",file) ;
	fputs("% Contributors:\n",file) ;
	fputs("%\n",file) ;
	fputs("%   Frederic Delhoume (delhoume@ilog.fr):\n",file) ;
	fputs("%        Original Postcript library with average depth sorting,\n",file) ;
	fputs("%        Gouraud triangle PostScript fragment\n", file);
	fputs("%\n",file) ;
	fputs("%   Cyril Soler       (csoler@imag.fr):\n",file) ;
	fputs("%        BSP Sort,\n",file) ;
	fputs("%        Item buffer culling,\n",file) ;
	fputs("%        Xfig3.2 (and EPS) format\n", file);
	fputs("%\n\n",file) ;

	fprintf(file, "/threshold %g def\n", EPS_GOURAUD_THRESHOLD);

	for (i = 0; gouraudtriangleEPS[i]; i++) 
		fprintf(file, "%s\n", gouraudtriangleEPS[i]);

	fprintf(file, "\n%g setlinewidth\n\n", lineWidth);

	/* Clear the background like OpenGL had it. */

	if(ClearBG == EPS_CLEAR_BG)
	{
		if(DrawMode == EPS_BLACK_AND_WHITE)
			fprintf(file, "%g %g %g setrgbcolor\n", 1.0,1.0,1.0);
		else
			fprintf(file, "%g %g %g setrgbcolor\n", clearColor[0], clearColor[1], clearColor[2]);

		fprintf(file, "%g %g %g %g rectfill\n\n",viewport[0],viewport[1],viewport[2],viewport[3]);
	}

	spewSortedFeedback(file, size, buffer, DrawMode,FORMAT_EPS,VisibilityOptimisation,SortMethod,Zdepth);

	/* Emit EPS trailer. */

	fputs("grestore\n\n", file);

	if(EPSMode == EPS_PS)
		fputs("showpage\n", file) ;
	else
	{
  		fputs("% uncomment next line to be able to print to a printer.\n", file);
		fputs("% showpage\n", file) ;
	}

	fclose(file);
}

void spewWireFrameFIG(FILE * file, int SortMethod, GLint size, GLfloat * buffer, char *,int DrawMode, int,int VisibilityOptimisation, int)
{
	GLfloat clearColor[4], viewport[4];
	GLfloat lineWidth;

	GLfloat xmin = FLT_MAX ;
	GLfloat ymin = FLT_MAX ;
	GLfloat zmin = FLT_MAX ;
	GLfloat xmax = -FLT_MAX ;
	GLfloat ymax = -FLT_MAX ;
	GLfloat zmax = -FLT_MAX ;

	ComputeBufferBB(size, buffer, xmin,xmax,ymin,ymax,zmin,zmax) ;

#ifdef DEBUGEPSRENDER
	printf("Buffer bounding box: %f %f %f %f %f %f\n",xmin,xmax,ymin,ymax,zmin,zmax) ;
#endif
	float Zdepth = Max(ymax-ymin,xmax-xmin) ;
	NormalizeBufferCoordinates(size,buffer,Zdepth,zmin,zmax) ;

	/* Read back a bunch of OpenGL state to help make the EPS
   		consistent with the OpenGL clear color, line width, point
   		size, and viewport. */

	glGetFloatv(GL_VIEWPORT, viewport);
	glGetFloatv(GL_COLOR_CLEAR_VALUE, clearColor);
	glGetFloatv(GL_LINE_WIDTH, &lineWidth);
	glGetFloatv(GL_POINT_SIZE, &pointSize);

	lineWidth /= (float)Max(viewport[2] - viewport[0],viewport[3]-viewport[1]) ;

	/* Emit EPS header. */

	fputs("#FIG 3.2\nPortrait\nCenter\nInches\nLetter\n100.00\nSingle\n0\n1200 2\n",file) ;

	sizeX = int(0.5f + viewport[2] - viewport[0]) ;
	sizeY = int(0.5f + viewport[3] - viewport[1]) ;

	spewSortedFeedback(file, size, buffer, DrawMode, FORMAT_FIG,VisibilityOptimisation,SortMethod,Zdepth);

	/* Emit EPS trailer. */

	fclose(file);
}

void EpsRenderer::EPSRender(int & size, int SortMethod, const char *filename, RenderCB render, 
					void *params, int & error,int DrawMode, int EPSMode,
					int VisibilityOptimisation, int ClearBG, int TightenBB)
{
#ifdef DEBUGEPSRENDER
	QTimer timer ;
#endif

	GLfloat *feedbackBuffer = NULL ;
	GLint returned = -1 ;
	FILE *file;

	if(size == 0)
		size = 1000 ;

	error = 0 ;

	int nb_renders = 0 ;

#ifdef DEBUGEPSRENDER
	timer.start() ;
#endif

	while(returned < 0)
	{
		size *= 4 ;

		if(feedbackBuffer != NULL)
			delete[] feedbackBuffer ;

  		feedbackBuffer = new GLfloat[size] ;

		if(feedbackBuffer == NULL)
		{
			error = EPSRENDER_OUT_OF_MEMORY ;
			return ;
		}

  		glFeedbackBuffer(size, GL_3D_COLOR, feedbackBuffer);
		glRenderMode(GL_FEEDBACK);
  		render(params);
  		returned = glRenderMode(GL_RENDER);

		nb_renders++ ;
	}

#ifdef DEBUGEPSRENDER
	cout << "Feeback buffer read time: " << timer.elapsed() << " msecs" << endl ;
#endif

	if(SortMethod != EPS_DONT_SORT)
	{
		GLint depth_bits ;
		glGetIntegerv(GL_DEPTH_BITS, &depth_bits) ;

		EGALITY_EPS 		= 2.0/(1 << depth_bits) ;
		LINE_EGALITY_EPS 	= 2.0/(1 << depth_bits) ;
	}

	size = returned ;

  	if(filename) 
	{
		file = fopen(filename, "w");

		if (file) 
		{
			if(EPSMode == EPS_FIG)
				spewWireFrameFIG(file, SortMethod, returned, feedbackBuffer, "libEPSRender", DrawMode, EPSMode,VisibilityOptimisation, ClearBG);
			else
				spewWireFrameEPS(file, SortMethod, returned, feedbackBuffer, "libEPSRender", DrawMode, EPSMode,VisibilityOptimisation, ClearBG, TightenBB) ;
		}
		else 
			error = EPSRENDER_CANNOT_OPEN_FILE ;
    }
	else
		error = EPSRENDER_FILENAME_NOT_VALID ;

  delete[] feedbackBuffer ;
}

