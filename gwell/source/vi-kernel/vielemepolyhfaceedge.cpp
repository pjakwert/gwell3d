/*----------------------------------------------------------------------------
 * \file  vifaceedge.cpp
 * \author	Bogdan Kreczmer
 * \date	2003.03.24
 *
 * Plik zawiera implementacjê metod klasy \link ViFaceEdge ViFaceEdge\endlink
 * modeluj±cej krawêdzie zwi±zane z dan± ¶ciank± i maj±ce w³a¶ciw±
 * orientacjê wzglêdem tej ¶cianki. Czego nie gwarantuj± obiekty
 * klasy ViEdge.
 */



#ifdef __GNUG__
#pragma implementation
#endif

#include "vielemepolyh.hh"
#include "vielemepolyhfaceedge.hh"
#include "vielemepolyhface.hh"
#include "viface.hh"

#define USE(x)  (*(x*)this)

std::ostream &operator  << ( std::ostream              &ostrm, 
                             ViElemePolyhFaceEdge const &FEdge )
{
  return ostrm << "[" << FEdge.GetFstVtx() << ",  " 
               << FEdge.GetSndVtx() << "]";
}



ViElemePolyhFaceEdge::ViElemePolyhFaceEdge( const ViElemePolyhFace    &Owner, 
                                            const ViFaceEdge & Edge
		                          ):
     _Owner(Owner), 
     _PatteFaceEdge(Edge),
     _FstVtx(Owner.Owner_ElemePolyh().GlbVtx(Edge.GetFstVtxIdx())), 
     _SndVtx(Owner.Owner_ElemePolyh().GlbVtx(Edge.GetSndVtxIdx())), 
     _pNeighborFace(Owner.Owner_ElemePolyh().
                          GetElemeFace(Edge.GetNeighborIdx())) {}

/*!
 * Metoda inicjalizuje pole, które zale¿y od innych struktur tworzonych
 * dynamicznych. Polem tym jest
 * \link ViElemePolyhFaceEdge::_pNeighborFace _pNeighborFace\endlink.
 */
void ViElemePolyhFaceEdge::PostInit()
{
  _pNeighborFace = _Owner.Owner_ElemePolyh().
                              GetElemeFace(_PatteFaceEdge.GetNeighborIdx());
}






const Vector3f &ViElemePolyhFaceEdge::FaceNormVect() const
{
  return GetFace().GetNormVect();
}


Vector3f ViElemePolyhFaceEdge::FaceNormVect_Neighbor() const
{
  if (GetNeighborFace()) return GetNeighborFace()->GetNormVect();
  return Vector3f();
}
