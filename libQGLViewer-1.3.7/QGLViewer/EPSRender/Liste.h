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

#ifndef _LISTE_H_
#define _LISTE_H_

template<class T> class Liste
{
	public:
		Liste(T E, Liste<T> *L) { cour = E ; suiv = L ; }

		inline const T & Cour() const { return cour ; }
		inline Liste<T> *Suiv() const { return suiv ; }

		void SetSuiv(Liste<T> *L) { suiv = L ; }
		void SetCour(const T & P) { cour = P ; }

		~Liste() { if(suiv != NULL) delete suiv ; }

	protected:
		T cour ;
		Liste<T> *suiv ;
} ;

#endif
