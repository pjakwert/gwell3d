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

#ifndef _SECUREDARRAY_H_
#define _SECUREDARRAY_H_

#include "Functions.h"

//  Tableau d'elements dont on ne connait pas la taille a l'avance.
// La taille est re-allouee si necessaire. On ne peut ajouter des elements
// qu'a la fin et un test est effectue chaque fois qu'on sort des bornes.

template<class T> class SecuredArray
{
	public:
		// AutoInit evite le teste qui detecte la lecture des 
		// trucs non initialises. Ca allege la memoire.

		SecuredArray(const unsigned int = 1,bool AutoInit = false) ;
		SecuredArray(const SecuredArray<T> &) ;
		~SecuredArray() ;

		//  These two methods should only be used to modify already 
		// existing elements. If not the element is not marked as 
		// initialised, and an error will be reported !

		T & Elem(const unsigned int) const ;
		inline T & operator[](const unsigned int i) const { return Elem(i) ; }
		inline SecuredArray<T>& operator=(const SecuredArray<T> &) ;

		//  This is the correct way to initialize an element, because
		// it sets it to be initialized and prevent further errors.

		void SetElem(const unsigned int, const T&) ;
		void AddElem(const unsigned int, const T&) ;

		void Clear(const unsigned int) ;
		void Reset() ;
		void DoubleSize() ;
		inline unsigned int Size() const { return max_size ; }
		int Exists(const unsigned int i) const ;
		void SetInitialized(const unsigned int i) { exists[i] = true ; }

	protected:
		T *array ;
		bool *exists ;

		unsigned int max_size ;	
		bool auto_init ;
} ;

template<class T> inline SecuredArray<T>::SecuredArray(const unsigned int s,bool AutoInit)
{
	auto_init = AutoInit ;

	if(s == 0)
	{
		array = new T[1] ;
		if(AutoInit)
			exists = NULL ;
		else
			exists = new bool[1] ;
		max_size = 1 ;
	}
	else
	{
		array = new T[s] ;

		if(array == NULL)
		{
			std::cerr << "Out of memory in secured array, while allocating for size " << s << std::endl ;
#ifdef DEBUG
			DumpCore() ;
#endif
		}

		max_size = s ;
		if(AutoInit)
			exists = NULL ;
		else
		{
			exists = new bool[s] ;

			if(exists == NULL)
			{
				std::cerr << "Out of memory in secured array, while allocating for size " << s << std::endl ;
#ifdef DEBUG
				DumpCore() ;
#endif
			}
		}
	}

	if(!AutoInit)
		for(unsigned int i=0;i<max_size;i++)
			exists[i] = false ;
}

template<class T> inline SecuredArray<T>::SecuredArray(const SecuredArray<T> & A)
{
	auto_init = A.auto_init ;
	max_size = A.max_size ;
	array = new T[max_size] ;

	for(unsigned int i=0;i<max_size;i++)
		array[i] = A.array[i] ;

	if(auto_init)
		exists = NULL ;
	else
	{
		exists = new bool[max_size] ;

		for(unsigned int i=0;i<max_size;i++)
			exists[i] = A.exists[i] ;
	}
}

template<class T> inline SecuredArray<T>::~SecuredArray()
{
	if(array != NULL)
		delete[] array ;

	if(exists != NULL)
		delete[] exists ;
}

template<class T> inline void SecuredArray<T>::AddElem(const unsigned int i,const T& E)
{
	while(i >= max_size)
		DoubleSize() ;

	SetElem(i,E) ;
}

template<class T> inline void SecuredArray<T>::SetElem(const unsigned int i,const T& E)
{
	if(i >= max_size)
	{
		std::cerr << "Out of array bounds (i=" << i << ") in SecuredArray<>::SetElem !!!" << std::endl ;
#ifdef DEBUG
		DumpCore() ;
#endif
	}
	else
	{
		array[i] = E ;

		if(!auto_init) exists[i] = true ;
	}
}

template<class T> inline void SecuredArray<T>::Reset()
{
	for(int i=0;i<max_size;i++)
		exists[i] = false ;
}

template<class T> inline void SecuredArray<T>::Clear(const unsigned int i)
{
#ifdef DEBUG
	if(i >= max_size)
	{
		std::cerr << "Out of array bounds (i=" << i << ") in SecuredArray<>::Clear !!!" << std::endl ;
		DumpCore() ;
	}
	else 
#endif
		if(!auto_init)
			exists[i] = false ;
}

template<class T> inline int SecuredArray<T>::Exists(const unsigned int i) const
{
	if(auto_init)
		return true ;
#ifdef DEBUG
	if(i >= max_size)
	{
		std::cerr << "Out of array bounds (i=" << i << ") in SecuredArray<>::Exists !!!" << std::endl ;
		DumpCore() ;
		return false ;
	}
#endif

	return exists[i] ;
}

template<class T> inline T & SecuredArray<T>::Elem(const unsigned int i) const
{
#ifdef DEBUG
	if(i >= max_size)
	{
		std::cerr << "Out of array bounds (i=" << i << ") in SecuredArray<>::Elem !!!" << std::endl ;
		DumpCore() ;
	}

	if((!auto_init)&&(exists[i] != true))
		std::cerr << "Uninitialized memory read (i=" << i << ") in SecuredArray<>::Elem !!!" << std::endl ;
//		DumpCore() ;
#endif

	return array[i] ;
}

template<class T> inline SecuredArray<T>& SecuredArray<T>::operator=(const SecuredArray<T> & A)
{
	if(this == &A)
		return *this ;

	if(max_size != A.max_size)
	{
		max_size = A.max_size ;

		if(array != NULL) delete[] array ;

		array = new T[max_size] ;
	}

	auto_init = A.auto_init ;

	if((exists != NULL)&&(auto_init))
	{
		delete[] exists ;
		exists = NULL ;
	}

	if(!auto_init)
		exists = new bool[max_size] ;

	for(unsigned int i=0;i<max_size;i++)
	{
		array[i] = A.array[i] ;

		if(!auto_init)
			exists[i] = A.exists[i] ;
	}

	return *this ;
}

template<class T> inline void SecuredArray<T>::DoubleSize()
{
	T *tmp = new T[2*max_size] ;
	bool *tmp2 = 0;

	if(!auto_init)
		tmp2 = new bool[2*max_size] ;

	for(unsigned int i=0;i<max_size;i++)
	{
		tmp[i] = array[i] ;

		if(!auto_init)
		{
			tmp2[i] = exists[i] ;
			tmp2[i+max_size] = false ;
		}
	}

	max_size = max_size*2 ;

	delete[] array ;
	array = tmp ;

	if(!auto_init)
	{
		delete[] exists ;
		exists = tmp2 ;
	}
}

#endif
