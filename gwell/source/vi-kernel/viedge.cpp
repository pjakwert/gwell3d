#include "viedge.hh"
#include "viface.hh"
#include "vipattepolyh.hh"

/*--------------------------------------------------------------------------
 * \file viedge.cpp
 *  Plik zawiera implementacjê metod klasy ViEdge. Obiekty tej klasy
 *  reprezentuj± krawêdzie bry³y
 *  elementarnej, która modelowana jest± przez klasê ViPattePolyh.
 *  Obiekty klasy ViEdge nie stanowi±  bezpo¶redniej reprezentacji krawêdzi
 *  ¶cianki bry³y, gdy¿ nie
 *  uwzglêdnia orientacji danej ¶cianki. Tak± reprezentacjê zapewniaj±
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
 * Udostêpnia wskaznik do prawej ¶cianki.
 */
ViFace const *ViEdge::GetRightFace() const
{
 return GetRightFaceIdx() == ET_NULLFACE ? 0L : 
                              _Owner.GetFacesTab()+GetRightFaceIdx();
}

/*============================================================================
 * Udostêpnia wskaznik do lewej ¶cianki.
 */
ViFace const *ViEdge::GetLeftFace() const
{
  return GetLeftFaceIdx() == ET_NULLFACE ? 0L :
                              _Owner.GetFacesTab()+GetLeftFaceIdx();
}

/*============================================================================
 * Udostêpnia referencjê do pierwszego wierzcho³ka.
 */
Vector3f const &ViEdge::GetFirstVtx() const
{
  return _Owner.GetPattePolyhVtx(GetFirstVtxIdx());
}

/*============================================================================
 * Udostêpnia referencjê do drugiego wierzcho³ka.
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
