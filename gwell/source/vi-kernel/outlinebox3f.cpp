/*
 * File:	outlinebox3.cpp
 * Purpose:     Wyznaczanie obrysu prostopadloscianowego danego obiektu
 * Author:	Bogdan Kreczmer
 * Created:	styczen 2004
 * Updated:
 * Copyright:	(c) 2004, Bogdan Kreczmer
 */


#ifdef __GNUG__
#pragma implementation
#endif


#include "outlinebox3f.hh"
#include "halfline3f.hh"


bool OutlineBox3f::IsCommonPart( const HalfLine3f &Ln ) const
{
  return Ln.IsHalfLineCrossBox(_OutMin,_OutMax);
}

