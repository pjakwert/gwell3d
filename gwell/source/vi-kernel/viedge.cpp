#include "viedge.hh"
#include "viface.hh"
#include "vipattepolyh.hh"

/*--------------------------------------------------------------------------
 * \file viedge.cpp
 *  Plik zawiera implementacj� metod klasy ViEdge. Obiekty tej klasy
 *  reprezentuj� kraw�dzie bry�y
 *  elementarnej, kt�ra modelowana jest� przez klas� ViPattePolyh.
 *  Obiekty klasy ViEdge nie stanowi�  bezpo�redniej reprezentacji kraw�dzi
 *  �cianki bry�y, gdy� nie
 *  uwzgl�dnia orientacji danej �cianki. Tak� reprezentacj� zapewniaj�
 *  obiekty klasy  ViFaceEdge.
 * \author Bogdan Kreczmer
 * \date   2003.10
 */


std::ostream &operator  << (std::ostream &ostrm, ViEdge const &Edge)
{
  return ostrm << "(" << Edge.GetFirstVtx() << ",  " 
               << Edge.GetSecondVtx() << ")";
}



/*============================================================================
 * Udost�pnia wskaznik do prawej �cianki.
 */
ViFace const *ViEdge::GetRightFace() const
{
 return GetRightFaceIdx() == ET_NULLFACE ? 0L : 
                              _Owner.GetFacesTab()+GetRightFaceIdx();
}

/*============================================================================
 * Udost�pnia wskaznik do lewej �cianki.
 */
ViFace const *ViEdge::GetLeftFace() const
{
  return GetLeftFaceIdx() == ET_NULLFACE ? 0L :
                              _Owner.GetFacesTab()+GetLeftFaceIdx();
}

/*============================================================================
 * Udost�pnia referencj� do pierwszego wierzcho�ka.
 */
Vector3f const &ViEdge::GetFirstVtx() const
{
  return _Owner.GetPattePolyhVtx(GetFirstVtxIdx());
}

/*============================================================================
 * Udost�pnia referencj� do drugiego wierzcho�ka.
 */
Vector3f const &ViEdge::GetSecondVtx() const
{
  return _Owner.GetPattePolyhVtx(GetSecondVtxIdx());
}



 bool ViEdge::IsVisible(const Vector3f &ViewVct) const 
  { 
    if (!IsRightFace() && !IsLeftFace()) return true;
    if (IsRightFace()) 
      if (sgn(GetRightFace()->GetNormVect() & ViewVct) == -1) 
	return true;
    if (IsLeftFace()) 
      if (sgn(GetLeftFace()->GetNormVect() & ViewVct) == -1) 
	return true;    
    return false;
  }
