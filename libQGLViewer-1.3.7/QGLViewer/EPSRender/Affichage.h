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
// @(#)Affichage.h	1.3 6/24/99
//

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "../config.h"

class Segment ;
class Polygone ;
class Feedback3Dcolor ;

extern void spewPrimitiveEPS(Feedback3Dcolor *,FILE *,int) ;
extern void spewPrimitiveEPS(Segment *,FILE *,int) ;
extern void spewPrimitiveEPS(Polygone *,FILE *,int) ;
extern void spewPrimitiveFIG(Feedback3Dcolor *,FILE *,int,int) ;

extern void spewPrimitiveFIG(Segment *,FILE *,int,int) ;
extern void spewPrimitiveFIG(Polygone *,FILE *,int,int) ;
extern void spewSortedFeedback(FILE *,GLint,GLfloat *,int,int,int,int,float) ;

#define FORMAT_EPS 0
#define FORMAT_FIG 1

extern int sizeX ;
extern int sizeY ;

#endif
