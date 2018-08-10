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

#include "vifaceedge.hh"
#include "viface.hh"



std::ostream &operator  << (std::ostream &ostrm, ViFaceEdge const &FEdge)
{
  return ostrm << "[" << FEdge.GetFstVtx() << ",  " 
               << FEdge.GetSndVtx() << "]";
}

const Vector3f &ViFaceEdge::FaceNormVect() const
{
  return GetFace().GetNormVect();
}


Vector3f ViFaceEdge::FaceNormVect_Neighbor() const
{
  if (GetNeighborFace()) return GetNeighborFace()->GetNormVect();
  return Vector3f();
}
