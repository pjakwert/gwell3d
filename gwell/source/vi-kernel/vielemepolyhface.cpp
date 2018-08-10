#ifdef __GNUG__
#pragma implementation
#endif

#include <iostream>
#include "vector3f.hh"
#include "vielemepolyhface.hh"
#include "vielemepolyh.hh"
#include "viface.hh"
#include "viexception.hh"


using namespace std;





std::ostream &operator  << (std::ostream &ostrm, ViElemePolyhFace const &Face)
{
  int i = 0;
  
  cout << "Scianka: " << Face.GetMyIdx()+1 << endl;
  for (ViElemePolyhFace::ConEdgeIter Iter = Face.ConBegin_GlbEdge(); 
       Iter; ++Iter)
         cout << Face.GetPrintPrefix() << ++i << "  " << *Iter << endl;

  (*((ViElemePolyhFace*)&Face)).ResetPrintPrefix();
  return ostrm;
}



ViElemePolyhFace::ConEdgeIter::ConEdgeIter(ViElemePolyhFace const *pFace, 
                                           unsigned int             Idx ):
  IndiTableIterator<const ViElemePolyhFaceEdge* const, 
                    const ViElemePolyhFaceEdge>
                  (pFace->GetEdgesNo(),pFace->GetGlbEdgesTab(),Idx) {}



//==========================================================================
//--------------------  ViElemePolyhFace::ConTriaIterator ------------------


ViElemePolyhFace::ConTriaIter::ConTriaIter( const ViElemePolyhFace *pFace,
                                            unsigned int            No, 
                                            unsigned int            Idx ):  
 ChainTableIterator<const ViElemePolyhFace,const ViTriangle3f>
                                                     (pFace,No,Idx)
{
  if (Idx < 2)  throw ViException_OutOfRange(ERRNUM_ELEMEFACE_IDXBELOW2,
                                        MSG(ERRMSG_ELEMEFACE_IDXBELOW2),Idx);
  
  InitField();
}



void ViElemePolyhFace::ConTriaIter::InitField()
{
  (*(ViTriangle3f*)&_Field).Set(_pOwner->GlbVtx(0),
                                _pOwner->GlbVtx(_Idx-1),
                                _pOwner->GlbVtx(_Idx));
}


void ViElemePolyhFace::ConTriaIter::UpdateField()
{
  (*(ViTriangle3f*)&_Field).Vtx1() = _pOwner->GlbVtx(_Idx-1);
  (*(ViTriangle3f*)&_Field).Vtx1() = _pOwner->GlbVtx(_Idx);
}

//-------------------- ViElemePolyhFace::ConTriaIterator -------------------
//==========================================================================






unsigned int ViElemePolyhFace::GetMyIdx() const
{
  return this - _Owner.GetGlbFacesTab();
}





/*============================================================================
 *  Na podstawie wsp�rz�dnych globalnych wierzcho�k�w wyznacza r�wnanie
 *  p�aszczyzny dla �cianki (r�wnie� wektor normalny).
 */
bool ViElemePolyhFace::ComputePlain3f()
{
  if (GetVtxNo() < 3) {
    cerr << "!!! ViElemePolyhFace::ComputePlain3f" << endl;
    cerr << "!!!   Wierzcholkow jest mniej niz 3." << endl;
    return false;
  }
  return _FacePlain3f.ComputePlain3f(GlbVtx(0),GlbVtx(1),GlbVtx(2));
}


/*============================================================================
 * Udost�pnia ilo�� wierzcho�k�w danej �cianki.
 */
unsigned int ViElemePolyhFace::GetVtxNo() const
{
 return _PattFigFace.GetVtxNo();
}


/*============================================================================
 * Udost�pnia wsp�rz�dne danego wierzcho�ka w uk�adzie globalnym.
 *
 *  PRE:  No - numer wierzcho�ka, numeracja rozpoczyna si� od 0. Ilo��
 *             wszystkich wierzcho�k�w dost�pna jest poprzez GetVtxNo.
 *             Numer wierzcho�ka musi nale�e� do zbioru 0, ... , GetVtxNo()-1.
 *             Je�eli nie b�dzie, to spe�nione mo�e powsta� b��d fatalny.
 *
 *  POST: zwraca wsp�rz�dne danego wierzcho�ka w uk�adzie wsp�rz�dnych
 *        globalnych.
 */
Vector3f const &ViElemePolyhFace::GlbVtx(unsigned int No) const
{
 return _Owner.GlbVtx(_PattFigFace.GetVtxIdx(No));
}



unsigned int ViElemePolyhFace::GetEdgesNo() const 
{ 
   return _PattFigFace.GetEdgesNo(); 
}



ViElemePolyhFace::ViElemePolyhFace(ViElemePolyh &Polyh):
  _Owner(Polyh), 
  _PattFigFace(*Polyh.GetPattFace(ViElemePolyh::IncFacesCount()))
{  _PrintPrefix = 0L; 
   _GlbEdgesSet = 0L;
   InitGlbEdgesSet();
}


/*!
 *  \pre Zak�ada si� �e pole \link ViElemePolyhFace::_GlbEdgesSet
 *       _GlbEdgesSet\endlink nie zawiera�o wska�nika na przydzielon�
 *       wcze�niej pami��.
 */
void ViElemePolyhFace::InitGlbEdgesSet() 
{
  ViElemePolyh const &Polyh = Owner_ElemePolyh();

  if (!GetEdgesNo()) return;
  if (_GlbEdgesSet) DestroyGlbEdgesSet();

  const ViElemePolyhEdge *pEdge;

  _GlbEdgesSet = new (ViElemePolyhFaceEdge*)[Polyh.GetEdgesNo()];
 
  for (unsigned int idx = 0;  idx < GetEdgesNo(); ++idx ) { 
    _GlbEdgesSet[idx] =
      new ViElemePolyhFaceEdge(*this,_PattFigFace.GetFaceEdge(idx));
  }  
}



void ViElemePolyhFace::DestroyGlbEdgesSet()
{
  if (!_GlbEdgesSet) return;
  for (int i = 0; i < GetEdgesNo(); i++) {
    if (_GlbEdgesSet[i]) delete _GlbEdgesSet[i] ;
  }
  delete [] _GlbEdgesSet;
  _GlbEdgesSet = 0L;
}
