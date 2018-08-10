/*------------------------------------------------------------------------
 * \file viscene.cpp
 *  Plik zawiera implementacjê metod klasy \link ViScene ViScene\endlink
 *  reprezentuj±c± pojedyncz± scenê.
 *
 * \author  Bogdan Kreczmer
 * \date    2004.03
 */

#ifdef __GNUG__
#pragma implementation
#endif

#include <string>
#include "viscene.hh"
#include "vielemepolyh.hh"
#include "vi-readpattepolyhlib.hh"
#include "viexception.hh"
#include "vipattepolyhlib.hh"
#include "vipatteaddress.hh"

// Znak komentarza pojedynczej linii.
#define CC_COMMENTSINGLELINE  '#'



/*!
 * \fn ViMultiPolyh *ViScene::AddNormMultiPolyh(ViMultiPolyh *pMPolyh)
 * \if brief_public_methods
 *  \brief  Dodaje model obiektu do zbioru obiektów zwyk³ych.
 * \endif
 *
 * Dodaje model obiektu do zbioru obiektów zwyk³ych.
 * \param pMPolyh - wska¼nik na model obiektu.
 * \post Nowym model obiektu dodany zostaje zawsze na koniec
 *       kolejki obiektów zwyk³ych.
 * \return wska¼nik na dodany obiekt.
 *  \exception ViException - jest zg³aszany z kodem 
 *        \link vierrors.hh::ERRMSG_POLYH__IS_NODE_ALREADY
 *                     ERRMSG_POLYH__IS_NODE_ALREADY\endlink,
 *         w sytuacji, gdy nastêpuje próba dodania do sceny 
 *         bry³y z³o¿onej do listy bry³, w której jest ju¿
 *         bry³a o tej samej nazwie.
 */

/*!
 * \fn ViMultiPolyh *ViScene::AddSpecMultiPolyh(ViMultiPolyh *pMPolyh)
 * \if brief_public_methods
 *  \brief  Dodaje model obiektu do zbioru obiektów specjalnych.
 * \endif
 *
 * Dodaje model obiektu do zbioru obiektów specjalnych.
 * \param pMPolyh - wska¼nik na model obiektu.
 * \post Nowym model obiektu dodany zostaje zawsze na koniec
 *       kolejki obiektów specjalnych.
 * \return wska¼nik na dodany obiekt.
 *  \exception ViException - jest zg³aszany z kodem 
 *        \link vierrors.hh::ERRMSG_POLYH__IS_NODE_ALREADY
 *                     ERRMSG_POLYH__IS_NODE_ALREADY\endlink,
 *         w sytuacji, gdy nastêpuje próba dodania do sceny 
 *         bry³y z³o¿onej do listy bry³, w której jest ju¿
 *         bry³a o tej samej nazwie.
 */


int ViScene::ReadMultiPolyh( std::istream    &istrm, 
                             ViNTreeNode *(*fun)(const char *ClassName)
                           )
{
  ExtString  Line;

  while (getline(istrm,Line)) {
    Line.RemoveSpace();
    if (Line.IsEmpty()) continue;
    if (Line.at(0) == CC_COMMENTSINGLELINE) continue;
    break;
  }
  return 0;
}



//===========================================================================
//.....................  VarNormPatteIter  ..................................

const ViPattePolyh * ViScene::FindPattePolyh( const char *FullName ) const
                 throw (ViException_Patte)
{
  ViPatteAddress  PattAddr = FullName;

  if (!PattAddr.IsAddrOK()) 
      throw ViException_Patte(ERRNUM_SYNTAX__BAD_PATTE_ADDR,
			      (MSG(ERRMSG_SYNTAX__BAD_PATTE_ADDR),FullName));

  ExtString   LibName, PatteType, PatteName;

  PattAddr.GetLibraryName(LibName);
  PattAddr.GetPatteType(PatteType);
  PattAddr.GetPatteName(PatteName);
  
  if (PatteType == PA_TYPE_NORM) {
     return FindNormPattePolyh(PatteName, LibName == "*" ? 0L : LibName.c_str());
  }
  return FindSpecPattePolyh(PatteName, LibName == "*" ? 0L : LibName.c_str());
}


const ViNTreeNode *ViScene::FindNormPolyh_Con(const ViNodeAddress &Addr) const
{
  return GetList_NormMultiPolyh().GetNodeUsingAddress(Addr);
}



const ViNTreeNode *ViScene::FindSpecPolyh_Con(const ViNodeAddress &Addr) const
{
  return GetList_SpecMultiPolyh().GetNodeUsingAddress(Addr);
}


void ViScene::VarNormPatteIter::Reset()
{
  if (_OnlyOne) {
    _PatIter.Reset();
    return;
  }

  _LibIter.Reset();
  _PatIter = _LibIter->Begin_NormPatte();
}


ViScene::VarNormPatteIter & ViScene::VarNormPatteIter::operator ++()
{
  while (!++_PatIter) {
    if (_OnlyOne) { _OpStatus = false; return *this; }
    if (!++_LibIter) { _OpStatus = false; return *this; }
    _PatIter = _LibIter->Begin_NormPatte();
  }
  _OpStatus = true;
  return *this;
}


ViScene::VarNormPatteIter & ViScene::VarNormPatteIter::operator --()
{
  while (!--_PatIter) {
    if (_OnlyOne) { _OpStatus = false; return *this; }
    if (!--_LibIter) { _OpStatus = false; return *this; }
    _PatIter = _LibIter->Begin_NormPatte();
  }
  _OpStatus = true;
  return *this;
}



ViScene::VarNormPatteIter::VarNormPatteIter( ViPatteLibList &LibList, 
                                             const char     *LibName
                                           )
{ 
  _OnlyOne = LibName ? true : false;
  ViPattePolyhLib *pLib;
  if (_OnlyOne) {
     if (!(pLib = (ViPattePolyhLib *) LibList.FindPattePolyhLib(LibName))) 
                                    throw ViException_OutOfRange();
     _LibIter.Init(pLib);
  } else {
     if (pLib = LibList.First()) {
       _LibIter.Init(pLib);
       _PatIter = _LibIter->Begin_NormPatte();
     }
  }
}

//.....................  VarNormPatteIter  ..................................
//===========================================================================








//===========================================================================
//.....................  ConNormPatteIter  ..................................

void ViScene::ConNormPatteIter::Reset()
{
  if (_OnlyOne) {
    _PatIter.Reset();
    return;
  }

  _LibIter.Reset();
  _PatIter = _LibIter->Begin_NormPatte();
}


ViScene::ConNormPatteIter & ViScene::ConNormPatteIter::operator ++()
{
  while (!++_PatIter) {
    if (_OnlyOne) { _OpStatus = false; return *this; }
    if (!++_LibIter) { _OpStatus = false; return *this; }
    _PatIter = _LibIter->Begin_NormPatte();
  }
  _OpStatus = true;
  return *this;
}


ViScene::ConNormPatteIter & ViScene::ConNormPatteIter::operator --()
{
  while (!--_PatIter) {
    if (_OnlyOne) { _OpStatus = false; return *this; }
    if (!--_LibIter) { _OpStatus = false; return *this; }
    _PatIter = _LibIter->Begin_NormPatte();
  }
  _OpStatus = true;
  return *this;
}



ViScene::ConNormPatteIter::ConNormPatteIter( const ViPatteLibList &LibList, 
                                             const char           *LibName
                                           )
{ 
  _OnlyOne = LibName ? true : false;
  const ViPattePolyhLib *pLib;
  if (_OnlyOne) {
     if (!(pLib = (ViPattePolyhLib *) LibList.FindPattePolyhLib(LibName))) 
                                    throw ViException_OutOfRange();
     _LibIter.Init(pLib);
  } else {
     if (pLib = LibList.First()) {
       _LibIter.Init(pLib);
       _PatIter = _LibIter->Begin_NormPatte();
     }
  }
}

//.....................  ConNormPatteIter  ..................................
//===========================================================================















//===========================================================================
//.....................  VarSpecPatteIter  ..................................

void ViScene::VarSpecPatteIter::Reset()
{
  if (_OnlyOne) {
    _PatIter.Reset();
    return;
  }

  _LibIter.Reset();
  _PatIter = _LibIter->Begin_SpecPatte();
}


ViScene::VarSpecPatteIter & ViScene::VarSpecPatteIter::operator ++()
{
  while (!++_PatIter) {
    if (_OnlyOne) { _OpStatus = false; return *this; }
    if (!++_LibIter) { _OpStatus = false; return *this; }
    _PatIter = _LibIter->Begin_SpecPatte();
  }
  _OpStatus = true;
  return *this;
}


ViScene::VarSpecPatteIter & ViScene::VarSpecPatteIter::operator --()
{
  while (!--_PatIter) {
    if (_OnlyOne) { _OpStatus = false; return *this; }
    if (!--_LibIter) { _OpStatus = false; return *this; }
    _PatIter = _LibIter->Begin_SpecPatte();
  }
  _OpStatus = true;
  return *this;
}



ViScene::VarSpecPatteIter::VarSpecPatteIter( ViPatteLibList &LibList, 
                                             const char     *LibName
                                           )
{ 
  _OnlyOne = LibName ? true : false;
  ViPattePolyhLib *pLib;
  if (_OnlyOne) {
     if (!(pLib = (ViPattePolyhLib *) LibList.FindPattePolyhLib(LibName))) 
                                    throw ViException_OutOfRange();
     _LibIter.Init(pLib);
  } else {
     if (pLib = LibList.First()) {
       _LibIter.Init(pLib);
       _PatIter = _LibIter->Begin_SpecPatte();
     }
  }
}

//.....................  VarSpecPatteIter  ..................................
//===========================================================================








//===========================================================================
//.....................  ConSpecPatteIter  ..................................

void ViScene::ConSpecPatteIter::Reset()
{
  if (_OnlyOne) {
    _PatIter.Reset();
    return;
  }

  _LibIter.Reset();
  _PatIter = _LibIter->Begin_SpecPatte();
}


ViScene::ConSpecPatteIter & ViScene::ConSpecPatteIter::operator ++()
{
  while (!++_PatIter) {
    if (_OnlyOne) { _OpStatus = false; return *this; }
    if (!++_LibIter) { _OpStatus = false; return *this; }
    _PatIter = _LibIter->Begin_SpecPatte();
  }
  _OpStatus = true;
  return *this;
}



ViScene::ConSpecPatteIter & ViScene::ConSpecPatteIter::operator --()
{
  while (!--_PatIter) {
    if (_OnlyOne) { _OpStatus = false; return *this; }
    if (!--_LibIter) { _OpStatus = false; return *this; }
    _PatIter = _LibIter->Begin_SpecPatte();
  }
  _OpStatus = true;
  return *this;
}



ViScene::ConSpecPatteIter::ConSpecPatteIter( const ViPatteLibList &LibList, 
                                             const char           *LibName
                                           )
{ 
  _OnlyOne = LibName ? true : false;
  const ViPattePolyhLib *pLib;
  if (_OnlyOne) {
     if (!(pLib = (ViPattePolyhLib *) LibList.FindPattePolyhLib(LibName))) 
                                    throw ViException_OutOfRange();
     _LibIter.Init(pLib);
  } else {
     if (pLib = LibList.First()) {
       _LibIter.Init(pLib);
       _PatIter = _LibIter->Begin_SpecPatte(); 
     }
  }
}

//.....................  ConSpecPatteIter  ..................................
//===========================================================================



















    //========================================================================
    //  Dodaje now± bibliotekê obiektów wzorcowych.
    //
ViPattePolyhLib *ViScene::AddPattePolyhLib(ViPattePolyhLib *pPPLib)
{
  if (!pPPLib) return 0L;
  if (FindPattePolyhLib(pPPLib->GetLibName())) return 0L;
  return _PattePolyhLib_List.AddToHead(pPPLib);
}


   //=========================================================================
   //  Czyta zawartosc biblioteki z pliku.
   //
int ViScene::ReadPatteLib(  const char *FileName, 
                            ExtString  &ErrMsg, 
                            ExtString  *pLibName
                         )
{
  ViPattePolyhLib  *pPPolyhSet =  new ViPattePolyhLib;

  int err = ReadPatternPolyhedronLib(*pPPolyhSet,FileName,ErrMsg);
  if (err) return err;
  
  if (!AddPattePolyhLib(pPPolyhSet)) {
    delete pPPolyhSet;
    return -900;
  }
  if (pLibName) *pLibName = pPPolyhSet->GetLibName();

  return 0;
}





ViPattePolyh const *ViScene::FindNormPattePolyh( const char *Name, 
                                                 const char *LibName
                                               ) const
  throw(ViException_Patte)
{
  return _PattePolyhLib_List.FindNormPattePolyh(Name,LibName);
  /*
  if (LibName) {
     if  (ViPattePolyhLib const *pLib = FindPattePolyhLib(LibName)) 
          return pLib->FindNormPattePolyh(Name); 
     else throw ViException_Patte(ERRNUM_PATTE__NO_SUCH_LIBRARY,
                 (MSG(ERRMSG_PATTE__NO_SUCH_LIBRARY),Name,LibName));
  }

  const ViPattePolyh *PPolyh;

  for (ConLibIterator Iter = _PattePolyhLib_List.Begin(); Iter; ++Iter)
              if ((PPolyh = Iter->FindNormPattePolyh(Name))) return PPolyh;
  return 0L;
  */
}


    //======================================================================
    //  Szuka specjalnej bry³y wzorcowej w podanej biliotece lub we 
    // wszystkich.
const ViPattePolyh *ViScene::FindSpecPattePolyh( const char *Name,
                                                 const char *LibName
                                               ) const
  throw(ViException_Patte)
{
  //  return _PattePolyhLib_List.FindSpecPattePolyh(Name,LibName);
  /*
  if (LibName) {
     if  (ViPattePolyhLib const *pLib = FindPattePolyhLib(LibName)) 
          return pLib->FindSpecPattePolyh(Name); 
     else throw ViException_Patte(ERRNUM_PATTE__NO_SUCH_LIBRARY,
                 (MSG(ERRMSG_PATTE__NO_SUCH_LIBRARY),Name,LibName));
  }

  const ViPattePolyh *PPolyh;

  for (ConLibIterator Iter = _PattePolyhLib_List.Begin(); Iter; ++Iter)
              if ((PPolyh = Iter->FindSpecPattePolyh(Name))) return PPolyh;
  return 0L;
  */
}

