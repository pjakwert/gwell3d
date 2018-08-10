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
// %W% %G%
//

#define ITEM_BUFFER_MAX_SIZE_X  800
#define ITEM_BUFFER_MAX_SIZE_Y  600

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#if (!defined(WIN32) && !defined(__APPLE__))
#include "OffScreen.h"
#endif

#include "Affichage.h"
#include "Geometry.h"
#include "BSPTree.h"
#include "EPSRender.h"
#include "VisibilityGraph.h"
#include "BSPTree.h"
#include "Functions.h"

using namespace std;
using namespace EpsRenderer;

int sizeX = 0 ;
int sizeY = 0 ;

int FigCoordX(float x)
{
  float MaxX = 12000 ;
  float MaxY = MaxX * sizeY/(float)sizeX ;

  if(MaxY > 7000)
    {
      MaxX *= 7000/(float)MaxY ;
      MaxY = 7000 ;
    }

  return int(0.5f + x/sizeX*MaxX) ;
}

int FigCoordY(float y)
{
  float MaxX = 12000 ;
  float MaxY = MaxX * sizeY/(float)sizeX ;

  if(MaxY > 7000)
    {
      MaxX *= 7000/(float)MaxY ;
      MaxY = 7000 ;
    }

  return int(0.5f + (1.0 - y/sizeY)*MaxY) ;
}

int FigGrayScaleIndex(float red, float green, float blue) 
{
  float intensity = 0.3*red+0.6*green+0.1*blue ;

  return int(intensity * 20.0) ;
}

void Feedback3Dcolor::spewEPS(FILE * file, int DrawMode) const
{
  if(DrawMode == EPS_BLACK_AND_WHITE)
    fprintf(file, "%g %g %g setrgbcolor\n", 0.0,0.0,0.0);
  else
    fprintf(file, "%g %g %g setrgbcolor\n", Red(), Green(), Blue());

  fprintf(file, "%g %g %g 0 360 arc fill\n\n", X(), Y(), pointSize / 2.0);
}

void Feedback3Dcolor::spewFIG(FILE * file, int, int depth) const
{
  fprintf(file, "2 1 0 5 0 7 %d 0 -1 0.000 0 1 -1 0 0 1\n",depth) ;

  fprintf(file, "\t %d %d\n",FigCoordX(X()),FigCoordY(Y())) ;
}

void Segment::spewEPS(FILE * file, int DrawMode) const
{
  GLfloat dx, dy, dr, dg, db, absR, absG, absB, colormax;
  int steps;
  GLfloat xstep=0.0, ystep=0.0, rstep=0.0, gstep=0.0, bstep=0.0;
  GLfloat xnext=0.0, ynext=0.0, rnext=0.0, gnext=0.0, bnext=0.0, distance=0.0;

  dr = P2.Red()   - P1.Red();
  dg = P2.Green() - P1.Green();
  db = P2.Blue()  - P1.Blue();

  if (dr != 0 || dg != 0 || db != 0) 
    {
      /* Smooth shaded line. */

      dx = P2.X() - P1.X();
      dy = P2.Y() - P1.Y();

      distance = sqrt(dx * dx + dy * dy);

      absR = fabs(dr);
      absG = fabs(dg);
      absB = fabs(db);

      colormax = Max(absR, Max(absG, absB));
      steps = int(0.5f + Max(1.0, colormax * distance * EPS_SMOOTH_LINE_FACTOR));

      xstep = dx / steps;
      ystep = dy / steps;

      rstep = dr / steps;
      gstep = dg / steps;
      bstep = db / steps;

      xnext = P1.X();
      ynext = P1.Y();
      rnext = P1.Red();
      gnext = P1.Green();
      bnext = P1.Blue();

      /* Back up half a step; we want the end points to be
	 exactly the their endpoint colors. */

      xnext -= xstep / 2.0;
      ynext -= ystep / 2.0;
      rnext -= rstep / 2.0;
      gnext -= gstep / 2.0;
      bnext -= bstep / 2.0;
    } 
  else 
    {
      /* Single color line. */
      steps = 0;
    }

  if(DrawMode == EPS_BLACK_AND_WHITE)
    fprintf(file, "%g %g %g setrgbcolor\n", 0.0,0.0,0.0);
  else
    fprintf(file, "%g %g %g setrgbcolor\n", P1.Red(), P1.Green(), P1.Blue());

  fprintf(file, "%g %g moveto\n", P1.X(), P1.Y());

  for (int i = 0; i < steps; i++) 
    {
      xnext += xstep;
      ynext += ystep;
      rnext += rstep;
      gnext += gstep;
      bnext += bstep;
      fprintf(file, "%g %g lineto stroke\n", xnext, ynext);

      if(DrawMode == EPS_BLACK_AND_WHITE)
	fprintf(file, "%g %g %g setrgbcolor\n", 0.0,0.0,0.0);
      else
	fprintf(file, "%g %g %g setrgbcolor\n", rnext, gnext, bnext);

      fprintf(file, "%g %g moveto\n", xnext, ynext);
    }
  fprintf(file, "%g %g lineto stroke\n", P2.X(), P2.Y());
}

void Segment::spewFIG(FILE * file, int, int depth) const
{
  GLfloat dx, dy, dr, dg, db, absR, absG, absB, colormax;
  int steps;
  GLfloat xstep, ystep, rstep, gstep, bstep;
  GLfloat xnext, ynext, rnext, gnext, bnext, distance;

  dr = P2.Red()   - P1.Red();
  dg = P2.Green() - P1.Green();
  db = P2.Blue()  - P1.Blue();

  if (dr != 0 || dg != 0 || db != 0) 
    {
      /* Smooth shaded line. */

      dx = P2.X() - P1.X();
      dy = P2.Y() - P1.Y();

      distance = sqrt(dx * dx + dy * dy);

      absR = fabs(dr);
      absG = fabs(dg);
      absB = fabs(db);

      colormax = Max(absR, Max(absG, absB));
      steps = int(0.5f + Max(1.0, colormax * distance * EPS_SMOOTH_LINE_FACTOR));

      xstep = dx / steps;
      ystep = dy / steps;

      rstep = dr / steps;
      gstep = dg / steps;
      bstep = db / steps;

      xnext = P1.X();
      ynext = P1.Y();
      rnext = P1.Red();
      gnext = P1.Green();
      bnext = P1.Blue();

      /* Back up half a step; we want the end points to be
	 exactly the their endpoint colors. */

      xnext -= xstep / 2.0;
      ynext -= ystep / 2.0;
      rnext -= rstep / 2.0;
      gnext -= gstep / 2.0;
      bnext -= bstep / 2.0;
    } 
  else 
    {
      /* Single color line. */
      steps = 0;
    }

  fprintf(file,"2 1 0 1 0 7 %d 0 -1 0.000 0 0 -1 0 0 2\n",depth) ;
  fprintf(file,"\t %d %d",FigCoordX(P1.X()),FigCoordY(P1.Y())) ;

  fprintf(file, " %d %d\n", FigCoordX(P2.X()), FigCoordY(P2.Y())) ;
}

void Polygone::spewEPS(FILE * file, int DrawMode) const
{
  int nvertices;
  GLfloat red, green, blue;
  int smooth;

  nvertices = NbVertices() ;

  Feedback3Dcolor vertex(Sommet3Dcolor(0)) ;

  if (nvertices > 0) 
    {
      red   = vertex.Red();
      green = vertex.Green();
      blue  = vertex.Blue();

      smooth = 0;

      for(int i = 1; i < nvertices; i++) 
	{
	  if((red != Sommet3Dcolor(i).Red()) || (green != Sommet3Dcolor(i).Green()) || (blue != Sommet3Dcolor(i).Blue()))
	    {
	      smooth = 1;
	      break;
	    }
	}

      if((smooth)&&(DrawMode != EPS_BLACK_AND_WHITE))
	{
	  /* Smooth shaded polygon; varying colors at vetices. */
	  /* Break polygon into "nvertices-2" triangle fans. */

	  for (int j = 0; j < nvertices - 2; j++) 
	    {
	      fprintf(file, "[%g %g %g %g %g %g]", Sommet3Dcolor(0).X(), Sommet3Dcolor(j + 1).X(), Sommet3Dcolor(j + 2).X(), Sommet3Dcolor(0).Y(), Sommet3Dcolor(j + 1).Y(), Sommet3Dcolor(j + 2).Y());

	      fprintf(file, " [%g %g %g] [%g %g %g] [%g %g %g] gouraudtriangle\n",
		      Sommet3Dcolor(0).Red(), Sommet3Dcolor(0).Green(), Sommet3Dcolor(0).Blue(),
		      Sommet3Dcolor(j + 1).Red(), Sommet3Dcolor(j + 1).Green(), Sommet3Dcolor(j + 1).Blue(),
		      Sommet3Dcolor(j + 2).Red(), Sommet3Dcolor(j + 2).Green(), Sommet3Dcolor(j + 2).Blue());
	    }
	} 
      else 
	{
	  /* Flat shaded polygon; all vertex colors the same. */

	  fprintf(file, "newpath\n");

	  if(DrawMode == EPS_BLACK_AND_WHITE)
	    fprintf(file, "%g %g %g setrgbcolor\n", 1.0,1.0,1.0);
	  else
	    fprintf(file, "%g %g %g setrgbcolor\n", red, green, blue);

	  /* Draw a filled triangle. */

	  fprintf(file, "%g %g moveto\n", Sommet3Dcolor(0).X(), Sommet3Dcolor(0).Y());

	  for (int i = 1; i < nvertices; i++) 
	    fprintf(file, "%g %g lineto\n", Sommet3Dcolor(i).X(), Sommet3Dcolor(i).Y());

	  fprintf(file, "closepath fill\n\n");
	}
    }
}

void Polygone::spewFIG(FILE * file, int DrawMode, int depth) const
{
  int nvertices;
  GLfloat red, green, blue;

  nvertices = NbVertices() ;

  // Feedback3Dcolor vertex(Sommet3Dcolor(0)) ;

  if (nvertices > 0) 
    {
      red   = 0 ;
      green = 0 ;
      blue  = 0 ;

      for(int i = 0; i < nvertices; i++) 
	{
	  red   += Sommet3Dcolor(i).Red() ;
	  green += Sommet3Dcolor(i).Green() ;
	  blue  += Sommet3Dcolor(i).Blue() ;
	}

      red   /= nvertices ;
      green /= nvertices ;
      blue  /= nvertices ;

      //		int   intensity_val = FigGrayScaleIndex(red,green,blue) ;

      /* Flat shaded polygon; all vertex colors the same. */

      if(DrawMode == EPS_BLACK_AND_WHITE)
	fprintf(file, "2 3 0 0 0 7 %d 0 20 0.000 0 0 -1 0 0 %d\n",depth,nvertices+1);
      else
	fprintf(file, "2 3 0 0 0 7 %d 0 %d 0.000 0 0 -1 0 0 %d\n",depth,FigGrayScaleIndex(red,green,blue),nvertices+1);

      /* Draw a filled triangle. */

      fprintf(file, "\t") ;

      for (int j = 0; j < nvertices; j++) 
	fprintf(file, " %d %d", FigCoordX(Sommet3Dcolor(j).X()), FigCoordY(Sommet3Dcolor(j).Y()));

      fprintf(file, " %d %d\n",FigCoordX(Sommet3Dcolor(0).X()), FigCoordY(Sommet3Dcolor(0).Y()));
    }
}

void DrawItemBuffer(long numberOfPrimitives, Primitive **PrimitiveTab,int,int Gsize,int Bsize) 
{
  int R = 0 ;
  int G = 0 ;
  int B = 1 ;

  glDisable(GL_CULL_FACE) ;
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL) ;

  for(long k=0;k<numberOfPrimitives;k++)
    {
      if(PrimitiveTab[k]->GetVisibility() == 1)
	PrimitiveTab[k]->DrawItem((unsigned char)R,(unsigned char)G,(unsigned char)B) ;

      B++ ;
      if(B > Bsize - 1)
	{
	  G++ ;
	  B = 0 ;
	}

      if(G > Gsize - 1)
	{
	  R++ ;
	  G = 0 ;
	}
    }

  glFlush() ;
}

void StencilOptimize(long numberOfPrimitives, Primitive **PrimitiveTab, int SizeX, int SizeY,int Rsize,int Gsize,int Bsize)
{
  GLint depth = 0 ;
  glGetIntegerv(GL_STENCIL_BITS, &depth) ;

  if(depth < 8)
    {
      printf("StencilOptimize: To few stencil planes (only %d found). Optimisation canceled.\n", (int) depth) ;
      return ;
    }

  glClearColor(1.0,1.0,1.0,0.0) ;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;

  glEnable(GL_STENCIL_TEST);

  glStencilFunc (GL_GEQUAL, 255, 255) ;
  glStencilOp (GL_KEEP, GL_KEEP, GL_INCR) ;

  // Draw only primitives that passed the preceding optimixation.

  DrawItemBuffer(numberOfPrimitives, PrimitiveTab,Rsize,Gsize,Bsize) ;

  int NbOrig = 0 ;

  for(long i=0;i<numberOfPrimitives;i++)
    {
      if(PrimitiveTab[i]->GetVisibility() == 1)
	NbOrig++ ;

      PrimitiveTab[i]->SetVisibility(0) ;
    }

  // Read pixels in the Item buffer

  GLint drBuff ;
  glGetIntegerv(GL_DRAW_BUFFER, &drBuff) ;
  glReadBuffer(drBuff) ;
  glPixelStorei(GL_PACK_ALIGNMENT, 1) ;

  unsigned char *Pixels = new unsigned char[3*SizeX*SizeY] ;

  glReadPixels( 0, 0, SizeX, SizeY, GL_RGB, GL_UNSIGNED_BYTE, Pixels);

  // Read pixels in the Stencil buffer

  unsigned char *Stencil = new unsigned char[SizeX*SizeY] ;
  glReadPixels( 0, 0, SizeX, SizeY, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, Stencil);

  // 4 - Declare as visible only primitives that mask something in the background.
		
  for(int j=0;j<SizeX*SizeY;j++)
    {
      long int PrimitiveIdentifier = (Pixels[3*j] * 256 + Pixels[3*j+1])*256 + Pixels[3*j+2] - 1 ;
      unsigned char StencilValue = Stencil[j] ;

      if(PrimitiveIdentifier < numberOfPrimitives)
	if((StencilValue > 1)||(!(PrimitiveTab[PrimitiveIdentifier]->IsAPolygon())))
	  PrimitiveTab[PrimitiveIdentifier]->SetVisibility(1) ;
    }

  glDisable(GL_STENCIL_TEST) ;

  // Count culled primitives

  unsigned long int NbLeft = 0 ;

  for(long k=0;k<numberOfPrimitives;k++)
    if(PrimitiveTab[k]->GetVisibility() == 1)
      NbLeft++ ;
#ifdef DEBUGEPSRENDER
  printf("  True masking optimization: % 5d primitives kept among % 5d (% 1.2lf %% discarded).\n",NbLeft, NbOrig, (NbOrig - NbLeft)*100.0/NbOrig) ;
#endif
}

#if (!defined(WIN32) && !defined(__APPLE__))
void CullPolygonsUsingItemBuffer(OrderingStructure *OrderStruct, int DrawMode)
{
  // 0 - Save context to be able to get back to it afterward.

  Display *saveDisp = glXGetCurrentDisplay() ;
  GLXContext saveCtx = glXGetCurrentContext() ;
  GLXDrawable saveDrawable = glXGetCurrentDrawable() ;

	// 1 - allocate an offscreen area for the item buffer

  static OFFSCREEN::OffScreenArea *ItemBuffer = NULL ;
	
  if(ItemBuffer == NULL)
    {
      ItemBuffer = new OFFSCREEN::OffScreenArea ;
      if(!ItemBuffer->AllocateOffScreenArea(ITEM_BUFFER_MAX_SIZE_X,ITEM_BUFFER_MAX_SIZE_Y))
	{
	  printf("Warning: Could not allocate offscreen area for visibility optimization. \n") ;
	  printf("         This may be a problem with your graphics card driver.\n") ;
	  printf("         No optimization will be done.\n") ;
	  return ;
	}
    }

  float scale_x = ITEM_BUFFER_MAX_SIZE_X/(float)sizeX ;
  float scale_y = ITEM_BUFFER_MAX_SIZE_Y/(float)sizeY ;

  float scale = Min(scale_x,scale_y) ;

  int SIZE_X = (int)floor(scale*sizeX) ;
  int SIZE_Y = (int)floor(scale*sizeY) ;

	// 2 - Render the primitives in the item buffer.

  glFlush() ;
  ItemBuffer->MakeCurrent() ;

  glEnable(GL_DEPTH_TEST) ;
  glDepthFunc(GL_LEQUAL) ;

  int v ;
  glGetIntegerv(GL_DEPTH_BITS, &v) ;

  if(v < 5)
    {
      printf("Warning: could only allocate Offscreen area with %d bits. This will be to small for optimize.\n",v) ;
      return ;
    }

  glClearColor(1.0,1.0,1.0,0.0) ;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;

  glMatrixMode(GL_PROJECTION) ;
  glLoadIdentity() ;
  glOrtho(0,sizeX,0,sizeY,-1,OrderStruct->ZDepth()+1) ;

  glMatrixMode(GL_MODELVIEW) ;
  glLoadIdentity() ;

  glViewport(0,0,SIZE_X,SIZE_Y) ;

  Primitive **PrimitiveTab = NULL ;
  long int numberOfPrimitives ;

  OrderStruct->GetPrimitiveTab(PrimitiveTab, numberOfPrimitives) ;

  int Rbts = 0 ;
  int Gbts = 0 ;
  int Bbts = 0 ;

  glGetIntegerv(GL_RED_BITS,   &Rbts) ;
  glGetIntegerv(GL_GREEN_BITS, &Gbts) ;
  glGetIntegerv(GL_BLUE_BITS,  &Bbts) ;

  int Rsize = 1 << Rbts ;
  int Gsize = 1 << Gbts ;
  int Bsize = 1 << Bbts ;

  if(Rsize*Gsize*Bsize < numberOfPrimitives)
    {
      printf("CullPolygonsUsingItemBuffer: insufficient colors in offscreen buffer.\n") ;
      printf("   Red = %d, Green = %d, Blue = %d\n",Rbts,Gbts,Bbts) ;
      printf("   This makes only %d possible colors for %ld primitives in item buffer.\n", Rsize*Gsize*Bsize, numberOfPrimitives) ;
      printf(" Optimisation process canceled.\n") ;
      return ;
    }

  // Draw all primitives in the item buffer

  for(long i=0;i<numberOfPrimitives;i++)
    PrimitiveTab[i]->SetVisibility(1) ;

  DrawItemBuffer(numberOfPrimitives, PrimitiveTab,Rsize,Gsize,Bsize) ;

  // 3 - Read the item buffer information

  int drBuff ;
  glGetIntegerv(GL_DRAW_BUFFER, &drBuff) ;
  glReadBuffer(drBuff) ;
  glPixelStorei(GL_PACK_ALIGNMENT, 1) ;

  unsigned char *Pixels = new unsigned char[3*SIZE_X*SIZE_Y] ;

  glReadPixels( 0, 0, SIZE_X, SIZE_Y, GL_RGB, GL_UNSIGNED_BYTE, Pixels);

#ifdef DEBUGEPSRENDER
  ImageIO::SaveImage("ItemBuffer.rgb",SIZE_X,SIZE_Y,Pixels,ImageIO::SGI_RGB) ;
#endif
  // 4 - Declare as visible only primitives that appear in the item buffer.

  for(long j=0;j<numberOfPrimitives;j++)
    PrimitiveTab[j]->SetVisibility(0) ;
		
  for(int k=0;k<SIZE_X*SIZE_Y;k++)
    {
      long int PrimitiveIdentifier = (Pixels[3*k] * 256 + Pixels[3*k+1])*256 + Pixels[3*k+2] - 1 ;

      if(PrimitiveIdentifier < numberOfPrimitives)
	PrimitiveTab[PrimitiveIdentifier]->SetVisibility(1) ;
    }

  unsigned long int nbCulled = 0 ;

  for(long l=0;l<numberOfPrimitives;l++)
    if(PrimitiveTab[l]->GetVisibility() == 0)
      nbCulled++ ;
#ifdef DEBUGEPSRENDER
  printf("  Visibility optimization:   % 5d primitives kept among % 5d (% 1.2lf %% discarded).\n",numberOfPrimitives - nbCulled, numberOfPrimitives, nbCulled*100.0/numberOfPrimitives) ;
#endif

  if(DrawMode == EPS_BLACK_AND_WHITE)
    StencilOptimize(numberOfPrimitives,PrimitiveTab,SIZE_X,SIZE_Y,Rsize,Gsize,Bsize) ;

  glXMakeCurrent(saveDisp, saveDrawable, saveCtx) ;

  //	delete ItemBuffer ;
  delete[] PrimitiveTab ;
  delete[] Pixels ;
}
#endif // WIN32 && APPLE

bool CheckAndInsertPoint(Feedback3Dcolor *& P, OrderingStructure *S)
{
  S->Insert(P) ;
  return true ;
}

// Traitement des cas degeneres. Renvoie false si le segment est degenere.
bool CheckAndInsertSegment(Segment *& P, OrderingStructure *S)
{
  if((P->Vertex(0) - P->Vertex(1)).NormInf() < EGALITY_EPS)
    {
      Feedback3Dcolor *pp = new Feedback3Dcolor(P->Sommet3Dcolor(0)) ;
      CheckAndInsertPoint(pp,S) ;
      delete P ;
      P = NULL ;
      return false ;
    }

  S->Insert(P) ;
  return true ;
}

// Traitement des cas degeneres. Renvoie false si le polygone est degenere.
bool CheckAndInsertPolygon(Polygone *& P, OrderingStructure *S)
{
  if(P->NbVertices() != 3)
    {
      cout << "unexpected case: Polygon with " << P->NbVertices() << " vertices !" << endl ;
      return false ;
    }

  if(P->FlatFactor() < FLAT_POLYGON_EPS)
    {
      // On ne traite que le cas du triangle plat, vu qu'on est sur d'avoir un triangle

      int n = P->NbVertices() ;

      for(int i=0;i<n;++i)
	if( (P->Vertex(i) - P->Vertex((i+1)%n)).Norm() > EGALITY_EPS)
	  {
	    Segment *pp = new Segment(P->Sommet3Dcolor((i+1)%n),P->Sommet3Dcolor((i+2)%n)) ;
	    CheckAndInsertSegment(pp,S) ;
	    delete P ;
	    P = NULL ;

	    return false ;
	  }

      Feedback3Dcolor *pp = new Feedback3Dcolor(P->Sommet3Dcolor(0)) ;
      CheckAndInsertPoint(pp,S) ;
      delete P ;
      P = NULL ;
      return false ;
    }

  // No problem encountered.

  S->Insert(P) ;
  return true ;
}

#if (!defined(WIN32) && !defined(__APPLE__))
void spewSortedFeedback(FILE * file, GLint size, GLfloat * buffer, int DrawMode,int Format, 
			int VisibilityOptimisation,int SortMethod,float Zdepth)
#else
  void spewSortedFeedback(FILE * file, GLint size, GLfloat * buffer, int DrawMode,int Format, 
			  int ,int SortMethod,float Zdepth)
#endif
{
#ifdef DEBUGEPSRENDER
  QTimer timer ;
#endif

  int token;
  GLfloat *loc, *end;
  int nvertices ;
  int nb_lines = 0 ;
  int nb_polys = 0 ;
  int nb_points = 0 ;
  int nb_degenerated_lines = 0 ;
  int nb_degenerated_polys = 0 ;
  int nb_degenerated_points = 0 ;

  end = buffer + size;

  OrderingStructure *OrderStruct = NULL ;
  int nb_passes ;

#ifdef DEBUGEPSRENDER
  timer.start() ;
#endif

  switch(SortMethod)
    {
    case EPS_BSP: 				OrderStruct = new BSPTree ;
      nb_passes = 2 ;
      break ;
    case EPS_OPTIMIZED_BSP: OrderStruct = new VisibilityGraph ;
      nb_passes = 2 ;
      break ;
    default:
      OrderStruct = new DontSortStructure ;
      nb_passes = 1 ;
    }

  // Normalization for classification
	
  OrderStruct->SetZDepth(Zdepth) ;

  // In case of sorting, spew polygons first. Its better for cutting.
  // otherwise, just spew everything in the same order than read.

  for(int i=0;i<nb_passes;i++)
    {
      loc = buffer;
      while (loc < end) 
	{
	  token = int(0.5f + *loc) ;
	  loc++;
	  switch (token) 
	    {
	    case GL_LINE_TOKEN:
	    case GL_LINE_RESET_TOKEN:
	      if((i==1)||(nb_passes == 1))
		{
		  Segment *S = new Segment(Feedback3Dcolor(loc),Feedback3Dcolor(loc+7)) ;
		  if(!CheckAndInsertSegment(S,OrderStruct))
		    nb_degenerated_lines++ ;

		  nb_lines++ ;
		}
	      loc += 14;
	      break;
	
	    case GL_POLYGON_TOKEN:
	      nvertices = int(0.5f + *loc) ;
	      loc++;
	
	      if((i==0)||(nb_passes == 1))
		{
		  Polygone *P = new Polygone(loc,nvertices) ; 
	
		  if(!CheckAndInsertPolygon(P,OrderStruct))
		    nb_degenerated_polys++ ;

		  nb_polys++ ;
		}
	      loc += (7 * nvertices);
	      break ;
	
	    case GL_POINT_TOKEN:
	      if((i==1)||(nb_passes == 1))
		{
		  Feedback3Dcolor *Pt = new Feedback3Dcolor(loc) ;
	
		  if(!CheckAndInsertPoint(Pt,OrderStruct))
		    nb_degenerated_points++ ;

		  nb_points++ ;
		}
	      loc += 7;
	      break;
	    default:
	      break;
	    }
	}
    }

#ifdef DEBUGEPSRENDER
  cout << "Sorting time:             " << timer.restart() << " msecs" << endl ;
  printf("Normal:      % 8d lines, % 8d polygons and % 8d points read.\n",nb_lines,nb_polys,nb_points) ;
  printf("Degenerated: % 8d lines, % 8d polygons and % 8d points read.\n",nb_degenerated_lines,nb_degenerated_polys,nb_degenerated_points) ;
#endif

#if (!defined(WIN32) && !defined(__APPLE__))
  if(VisibilityOptimisation == EPS_CULL_INVISIBLE_PRIMITIVES)
    {
      CullPolygonsUsingItemBuffer(OrderStruct, DrawMode) ;
#ifdef DEBUGEPSRENDER
      cout << "Optimization time:         " << timer.restart() << " msecs" << endl ;
#endif
    }
#endif // WIN32 && APPLE

  OrderStruct->Render(file,DrawMode,Format) ;
#ifdef DEBUGEPSRENDER
  cout << "Rendering time:           " << timer.restart() << " secs" << endl ;
#endif
}
