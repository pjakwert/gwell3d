/*---------------------------------------------------------------------------
 *  \file viface.cpp
 *  \author Bogdan Kreczmer
 *  \date   2004.01
 *
 *   Zawiera implementacj� metod klasy ViFace.
 */

#ifdef __GNUG__
#pragma implementation
#endif



#include <cstring>
#include <iostream>
#include "viface.hh"
#include "vipattepolyh.hh"
#include "viedge.hh"
#include "viexception.hh"
#include "vierrors.hh"

using namespace std;


std::ostream &operator  << (std::ostream &ostrm, ViFace const &Face)
{
  int i = 0;
  
  cout << "Scianka: " << Face.GetMyIdx()+1 << endl;
  for (ViFace::ConEdgeIter Iter = Face.ConBegin_Edge(); Iter; ++Iter) {
    cout << Face.GetPrintPrefix() << ++i << "  " << *Iter << endl;
  }
  (*((ViFace*)&Face)).ResetPrintPrefix();
  return ostrm;
}




//==========================================================================
//-------------------- ViFace::ConTriaIterator -----------------------------


ViFace::ConTriaIter::ConTriaIter( const ViFace *pFace,
                                  unsigned int No, 
                                  unsigned int Idx ):  
 ChainTableIterator<const ViFace,const ViTriangle3f>
                                                     (pFace,No,Idx)
{
  if (Idx < 2)  throw ViException_OutOfRange(ERRNUM_FACE_IDXBELOW2,
                                               MSG(ERRMSG_FACE_IDXBELOW2),Idx);
  InitField();
}


void ViFace::ConTriaIter::InitField()
{
  (*(ViTriangle3f*)&_Field).Set(_pOwner->GetFaceVtx(0),
                                _pOwner->GetFaceVtx(_Idx-1),
                                _pOwner->GetFaceVtx(_Idx));
}


void ViFace::ConTriaIter::UpdateField()
{
  (*(ViTriangle3f*)&_Field).Vtx1() = _pOwner->GetFaceVtx(_Idx-1);
  (*(ViTriangle3f*)&_Field).Vtx1() = _pOwner->GetFaceVtx(_Idx);
}

//-------------------- ViFace::ConTriaIterator -----------------------------
//==========================================================================



unsigned int ViFace::GetMyIdx() const
{
  return this - _Owner.GetFacesTab();
}


const char *ViFace::GetName() const
{
  return _Owner.GetName();
}



void ViFace::DestroyEdgesSet()
{
  if (!_EdgesSet) return;
  for (int idx = 0; idx < GetEdgesNo(); idx++) delete _EdgesSet[idx];
  delete [] _EdgesSet;
  _EdgesSet = 0L;
}


int err=0;
char const *Name = 0L;

void ViFace::InitEdgesSet()
{
  if (err && (Name != GetName())) {
     cout << endl << "!!!!!!!! Blad w: " <<   GetName() << endl;
     exit(1);
  }


  if (!GetEdgesNo()) return;
  DestroyEdgesSet();

  const ViEdge *pEdge;
  _EdgesSet = new (ViFaceEdge*)[GetEdgesNo()];
  for (unsigned int idx = 0; idx < GetEdgesNo(); ++idx) {
      pEdge = GetPolyhEdge(idx);
      if (!pEdge) {
        throw ViException_DataInconsistence(ERRNUM_FACE_NOEDGE,
                     (MSG(ERRMSG_FACE_NOEDGE),idx+1,GetMyIdx()+1,
                      GetName(),GetVtxIdx(idx)+1,
                      GetVtxIdx(idx +1 == GetEdgesNo() ? 0: idx+1)+1,
                      GetName(),GetVtxIdx(idx)+1,
                      GetVtxIdx(idx +1 == GetEdgesNo() ? 0: idx+1)+1));
      }
                
      if ((pEdge->GetRightFace() == this) && 
          (pEdge->GetLeftFace() == this))
                           {  cout << " Dziwna krawedz ????" << endl; }
      _EdgesSet[idx] = (pEdge->GetRightFace() == this) ?
	new ViFaceEdge(*this,pEdge->GetFirstVtx(),pEdge->GetFirstVtxIdx(),
                             pEdge->GetSecondVtx(),pEdge->GetSecondVtxIdx(),
                             pEdge->GetLeftFace(),pEdge->GetLeftFaceIdx()) :
	new ViFaceEdge(*this,pEdge->GetSecondVtx(),pEdge->GetSecondVtxIdx(),
      		             pEdge->GetFirstVtx(),pEdge->GetFirstVtxIdx(),
                             pEdge->GetRightFace(),pEdge->GetRightFaceIdx());
  }  
  if (err) { Name = GetName(); return; }
}



void ViFace::InitNormVect()
{
  Vector3f  V1 = GetFaceEdge(0).GetSndVtx();
  Vector3f  V_D0 = V1 - GetFaceEdge(0).GetFstVtx();
  Vector3f  V_D1;

  for (int idx = 1; idx < GetEdgesNo(); ++idx) {
    V_D1 = GetFaceEdge(idx).GetSndVtx() - V1;
    if (!(_NormVct = V_D0 * V_D1).IsZero()) { _NormVct.Normalize(); return; }
  }
  throw ViException_WrongComputation(ERRNUM_FACE_NORVCT,
                       (MSG(ERRMSG_FACE_NORVCT),GetMyIdx(),GetName()));  
}



/*!
 * Udost�pnienia indeks obiektu w tablicy, kt�ra znajduje si� w obiekcie
 * klasy ViPattePolyh.
 */
unsigned int ViFace::GetFaceIdx() const
{
  return this - _Owner.GetFacesTab();
}



/*!
 * Udost�pnienia wybran� kraw�dz danej �cianki. Kraw�dzie numerowane s� od
 * 0 do n-1, przy czym kraw�dz numer 0, to kraw�dz prowadzona mi�dzy 
 * wierzcho�kiem nr 0 i 1. Udost�pniana kraw�d� jest "surow�" kraw�dzi�
 * wielo�cianu bez orientacji zgodnej z orientacj� danej �cianki.
 * 
 * Je�eli potrzebne jest uzyskanie kraw�dzi z informacj� o jej orientacji
 * wzgl�dem danej �cianki, to nale�y u�y� metody
 * \link ViFace::GetFaceEdge GetFaceEdge\endlink.
 *
 * \warning Implementacja tej metody ma by� zast�piona w przysz�o�ci przez 
 *        bardziej efektywny kod.
 */
ViEdge const *ViFace::GetPolyhEdge(unsigned int Idx) const
{
  if (Idx >= GetVtxNo()) return 0L;
  unsigned int FstVtxIdx = GetVtxIdx(Idx);
  unsigned int SndVtxIdx = GetVtxIdx(Idx == GetVtxNo()-1 ? 0 : Idx+1);
  ViEdgeIterator EIter = _Owner.InitEdgeIterator();

  while (EIter) {
    if (EIter()->GetFirstVtxIdx() == FstVtxIdx &&
        EIter()->GetSecondVtxIdx() == SndVtxIdx) return EIter();
    if (EIter()->GetFirstVtxIdx() == SndVtxIdx &&
        EIter()->GetSecondVtxIdx() == FstVtxIdx) return EIter();
    ++EIter;
  }
  return 0L;
}



/*!
 * Metoda udost�pnia �ciank�, kt�ra s�siaduje z dan� �ciank� wzd�u� kraw�dzi
 * o numerze 'No', przy czym kraw�dzie numerowane s� od 0 do n-1, gdzie
 * 'n' to ilo�� wszystkich kraw�dzi. Ich numeracja jest zgodna z 
 * numeracj� kolejnych wierzcho�k�w (w kierunku przeciwnym do kierunku ruchu
 * zegara) wzd�u� obowodu �cianki.
 * \warning W og�lnym przypadku dopuszczalne s� bry�y, kt�re nie s� zamkni�te,
 *        a wi�c niekt�re kraw�dzie mog� nale�e� do jednej �cianki lub do
 *        �adnej (obiekty "druciane").
 *
 * \param  No - numer s�siaduj�cej �cianki. Numer ten musi by� z przedzia�u
 *            warto�ci ca�kowitych [0,n-1], gdzie 'n' to ilo�� wszystkich 
 *            kraw�dzi.
 *
 * \post
 *  Zwracany jest wska�nik na s�siaduj�c� �ciank�. Je�eli taka �cianka nie
 *  istnieje lub 'No' jest spoza dopuszczalnego przedzia�u, to zwracany jest
 *  adres 0L.
 */
ViFace const *ViFace::GetNeighbor(unsigned int No) const
{
  ViEdge const *wEdge = GetPolyhEdge(No);

  if (!wEdge) return 0L;

  unsigned int FaceIdx = GetFaceIdx();

  return (wEdge->GetLeftFaceIdx() == FaceIdx) ? wEdge->GetRightFace() :
                                                wEdge->GetLeftFace();
}



/*!
 * Metoda alokuje tablice dla numer�w wierzcho�k�w le��cych na obwodzie
 * danej �cianki.
 *
 * \param  NodeNo - ilo�� wierzcho�k�w danej �cianki.
 *
 * \retval 0 - gdy przydzielenie pami�ci dla tablicy powiod�o si�.
 * \retval -1 - gdy przydzielenie pami�ci dla tablicy nie powiod�o si�.
 */
int ViFace::CreateNodeTable(unsigned int NodeNo)
{
  if (_NodeSet) delete [] _NodeSet;

  _NodeSet = new unsigned int[NodeNo + 1];
  if (!_NodeSet) return -1;
  *_NodeSet = NodeNo;
  return 0;
}


/*!
 * Udost�pnia wsp�rz�dne wierzcho�ka danej �cianki.
 * Porz�dek wierzcho�k�w na obowdzie �cianki jest zgodny z ruchem
 * wskaz�wek zegara.
 *
 * \param  VtxNo - numer wierzcho�ka �cianki. Kolejne wierzcho�ki
 *         numerowane s� od 0. Numer wierzcho�ka musi by� prawid�owy,
 *          tzn. 
 *       \f$ 0 \le  VtxNo < N_{max} \f$,
 *        gdzie \f$ N_{max}\f$, to warto�� dost�pna poprzez metod�
 *       \link ViFace::GetVtxNo GetVtxNo\endlink.
 *
 * \pre  Pole \link ViFace::_NodeSet _NodeSet\endlink - musi by� prawd�owo 
 *       zainicjalizowane.
 *
 * \post Zwracana jest referancja do danego wierzcho�ka.
 *       Je�eli numer wierzcho�ka b�dzie poza dopuszczalnym przedzia�em,
 *       to dzia�anie programu b�dzie nieokre�lone.
 */ 
Vector3f const &ViFace::GetFaceVtx(unsigned int VtxNo) const
{
  return _Owner.GetPattePolyhVtx(GetVtxIdx(VtxNo));
}



/*!
 * Udost�pnia wsp�rz�dne wierzcho�ka danej �cianki.
 *
 * \param  VtxIdx - numer wierzcho�ka �cianki. Kolejne wierzcho�ki
 *               numerowane s� od 0.
 * \pre Pole \link ViFace::_NodeSet _NodeSet\endlink
 *       musi by� prawd�owo zainicjowane.
 *
 * \return Zwracana jest referancja do danego wierzcho�ka.
 * \post Je�li numer wierzcho�ka nie by� prawid�owy, to zg�aszany
 *       jest wyj�tek ViException_OutOfRange.
 */ 
Vector3f const &ViFace::SGetFaceVtx(unsigned int VtxIdx) const 
                                       throw (ViException_OutOfRange)
{
  if (VtxIdx > GetVtxNo()) 
    throw ViException_OutOfRange(ERRNUM_FACE_VTXNO,
                (MSG(ERRMSG_FACE_VTXNO),_Owner.GetName(),GetVtxNo(),VtxIdx));
  return _Owner.GetPattePolyhVtx(GetVtxIdx(VtxIdx));
}

/*!
 * Metoda inicjuje tablice numer�w wierzho�k�w. 
 * \param Tab - wska�nik na tablic� z nowymi numerami wierzcho�k�w.
 * \pre  \e Tab - Tablica musi mie� dok�adnie tak� sam� struktur� jak tablica
 *             wierzcho�k�w w klasie ViFace.
 *
 * \retval 0 - je�eli istnieje tablica _NodeSet, to zawarto�� Tab 
 *             zostaje do niej przepisana.
 * \warning NIE JEST SPRAWDZANY ROZMIAR PRZYDZIELONEGO WCZE�NIEJ OBSZARU.
 *
 * \retval -1 - je�eli tablica 
 *              \link ViFace::_NodeSet _NodeSet\endlink  == NULL, 
 *              to nie jest podejmowana 
 *              �adna akcja.
 */
int ViFace::InitNodeIndexTable(unsigned int *Tab )
{
  if (!_NodeSet) return -1;
  for (int ex=0; ex <= *Tab; ex++) _NodeSet[ex] = Tab[ex];
  return 0;
}



/*!
 * Metoda ��czy dzia�ania metod 
 * \link ViFace::CreateNodeTable CreateNodeTable\endlink i 
 * \link ViFace::InitNodeIndexTable InitNodeIndexTable\endlink,
 * tzn. alokuje tablice dla numer�w wierzcho�k�w le��cych na obwodzie
 * danej �cianki oraz inicjalizuje j�.
 * Wyznacza r�wnie� wektor normalny. 
 * \param Tab - tablica z nowymi numerami wierzcho�k�w.
 * \pre
 *   \e  Tab - tablica musi mie� dok�adnie tak� sam� struktur� jak tablica
 *             wierzcho�k�w w klasie ViFace.
 *
 *        Musi by� r�wnie� zainicjalizowana tablica wierzcho�k�w
 *      (ViPattePolyh::_Vertex) w obiekcie macierzystym klasy ViPattePolyh,
 *      z kt�rym ten obiekt jest powi�zany.
 *
 * \retval 0 - je�eli alokacja pami�ci powiod�a si�, to zawarto�� \e Tab
 *             zostaje przepisana do \link ViFace::_NodeSet _NodeSet\endlink.
 * \retval -1 - gdy alokacja pami�ci nie powiod�a si�.
 * \post  Je�eli nie mo�e zosta� wyliczony wektor normalny, to zg�aszany
 *        jest wyj�tek  ViException_WrongComputation.
 */
int ViFace::CreateAndInitNodeIndexTable(unsigned int *Tab )
{
  if (CreateNodeTable(*Tab)) return -1;
  return InitNodeIndexTable(Tab);
}



/*!
 * Metoda realizuje dealokacje i alokacje pamieci dla przepisywanych
 * struktur.
 */
ViFace &ViFace::operator = (ViFace const &F)
{
  if (_NodeSet) delete [] _NodeSet;
  // Obsluga musi byc zmieniona po zmianie struktury danych
  _NodesNo = F.GetVtxNo();
  _NodeSet = new (unsigned int) [F.GetVtxNo()+1];
  memcpy(_NodeSet,F._NodeSet,sizeof(unsigned int)*(F.GetVtxNo()+1));
  return *this;
}


/*!
 * Zwalnia pamie� przydzielon� na tablic� wierzcho�k�w i kraw�dzi.
 */
ViFace::~ViFace() 
{ 
  if (_NodeSet!=0L)  delete [] _NodeSet; 
  DestroyEdgesSet();
}
