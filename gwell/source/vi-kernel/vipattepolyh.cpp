#ifdef __GNUG__
#pragma implementation
#endif

/*-------------------------------------------------------------------------  
 *  \file vipattepolyh.cpp
 *  \author  Bogdan Kreczmer
 *  \date    2004.02
 *  Plik zawiera implementacjê metod klasy ViPattePolyh
 *  modeluj±cej bry³y wzorcowe.
 */

#include <iostream>
using namespace std;
#include "vipattepolyh.hh"
#include "extstring.hh"
#include "viedge.hh"
#include "viface.hh"
#include "vipattepolyhlib.hh"



//==========================================================================
//........................... ViPattePolyh  ............................



const ViPattePolyhList *ViPattePolyh::GetPatteList() const
{
  return (const ViPattePolyhList *)Root();
}


const ViPattePolyhLib *ViPattePolyh::GetPatteLib() const
{
  if (!Root()) return 0L;
  return &GetPatteList()->GetOwner();
}

const char *ViPattePolyh::GetListName() const 
{ 
  if (!GetPatteList()) return "?";
  return GetPatteList()->GetListName(); 
}

const char *ViPattePolyh::GetLibName() const 
{ 
  if (!GetPatteList()) return "?";
  return GetPatteList()->GetLibName(); 
}



void ViPattePolyh::InitFacesData()
{
  for (unsigned int i = 0; i < GetFacesNo(); i++) {
   UseFace(i)->InitEdgesSet();
   UseFace(i)->InitNormVect(); 
  }
}




/*==========================================================================
 * Ustawia ID coloru krawêdzi.
 */
bool ViPattePolyh::SetEdgeColorID( unsigned int EdgeIdx, unsigned int Color)
{
  if (EdgeIdx >= GetEdgesNo()) return false;
  _Edges[EdgeIdx].SetColorID(Color);
  return true;
}


/*==========================================================================
 * Metoda tworzy tablicê ¶cianek. Je¿eli wcze¶niej by³a ju¿ utworzona
 * taka tablica, to j± usuwa. Je¶li wszystko powiodlo siê to 
 * zwraca warto¶æ true.
 */
bool ViPattePolyh::CreateFacesTab( unsigned int Size )
{
  if (_Faces) delete [] _Faces;
  _Faces = new ViFace[_FacesNo = Size](*this);
  return _Faces;
}

/*==========================================================================
 *  Metody udostêpniaj± ¶ciankê
 *
 */
ViFace *ViPattePolyh::UseFace(unsigned int Idx) 
{
  return Idx >= _FacesNo ? 0L : _Faces+Idx; 
}


ViFace const *ViPattePolyh::GetFigFace(unsigned int Idx) const
{ 
  return Idx >= _FacesNo ? 0L : _Faces+Idx; 
}




/*=============================================================================
 * Przydziela pamiêæ dla tablicy krawêdzi. Je¶li przydzia³ pamiêci
 * nie powiedzie siê, to zwraca false. W przeciwnym przypadku true.
 */
bool ViPattePolyh::CreateEdgesTable(unsigned int Number)
{
  if (_Edges) delete [] _Edges;
  _Edges = new ViEdge[_EdgesNo = Number](*this);
  return _Edges;
}



/*=============================================================================
 * Ustawia indeksy wierzcho³ków krawêdzi, jednocze¶nie powoduje
 * ustawienie numerów ¶cianek s±siednich ¶cianek jako ET_NULLFACE.
 */
bool ViPattePolyh::SetEdgeVtx( unsigned int EdgeIdx,
                         unsigned int FrtVtxIdx,
                         unsigned int SndVtxIdx
                       )
{
  if (EdgeIdx >= _EdgesNo) return false;
  ViEdge &Edge = _Edges[EdgeIdx];
  Edge.SetVtxIdx(FrtVtxIdx,SndVtxIdx);
  Edge.SetFacesIdx(ET_NULLFACE,ET_NULLFACE);
  return true;
}




/*=============================================================================
 * Inicjuje iterator do przegladania wszystkich krawêdzi. Aktualna informacja
 * wskazuj±ca przyk³ad jego wykorzystania znajduje siê w pliku base/viedge.hh
 */
ViEdgeIterator ViPattePolyh::InitEdgeIterator() const
{
  return ViEdgeIterator(_EdgesNo,_Edges);
}


/*=============================================================================
 * Przypisuje warto¶ci wspó³rzêdnych wierzcho³kowi o numerze Idx.
 */
bool ViPattePolyh::SetVtx(unsigned int Idx, Vector3f const &Vtx)
{
  if (Idx >= _VertexNo) return false;
  _Vertex[Idx] = Vtx;
  return true;
}



/*=============================================================================
 * Przydziela pamiêæ dla tablicy wierzcho³ków. Je¶li przydzia³ pamiêci
 * nie powiedzie siê, to zwraca false. W przeciwnym przypadku true.
 *
 */
bool ViPattePolyh::CreateVertexTable(unsigned int Number)
{
  if (_Vertex) delete [] _Vertex;
  _Vertex = new Vector3f[_VertexNo = Number];
  return _Vertex;
}



ViPattePolyh::ViPattePolyh(void): _Name(*new ExtString)
{ 
  _VertexNo = _EdgesNo = _FacesNo = 0;
  _Vertex = 0L;  _Edges = 0L;  _Faces = 0L;
};


ViPattePolyh::~ViPattePolyh(void)
   { if (_Vertex) delete[] _Vertex;
     if (_Edges)  delete[] _Edges;
     if (_Faces)  delete[] _Faces;
   };



void ViPattePolyh::SetName(char const *Name)
{
  _Name = Name;
}

//........................... ViPattePolyh  ................................
//==========================================================================
