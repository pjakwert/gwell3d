#ifndef DIRETABLEITERATOR_HH
#define DIRETABLEITERATOR_HH

/*!  
 * \file diretableiterator.hh
 * \author  Bogdan Kreczmer
 * \date    2004.03.23
 *
 *  Plik zawiera definicjê szablonu klas
 *   \link DireTableIterator DireTableIterator\endlink
 *  (Direct Table Iterator)
 *  umo¿liwiaj±cej przechodzedzenie po kolejnych elementach tablic.
 */


#ifdef __GNUG__
#pragma interface
#endif



#include "vierrors.hh"
#include "viexception.hh"

/*!
 *  Szablon jest przeznaczony do definiowania iteratorów dla struktur danych
 *  opartych na tablicach.
 *  \param TabType - typ elementów tablicy,
 *  \param ID - indentyfikator umo¿liwiaj±cy rozro¿nienie nazw typów, w 
 *             przypadku gdy pierwszy parametr dla dwóch typów jest 
 *             identyczny.
 */
template <class TabType, int ID = 0>
class DireTableIterator {
  int        _No;  /*!< Ilo¶æ elementów tablicy.                            */
   /*!
    * Warto¶æ indeksu nadana w momencie inicjalizacji iteratora. Jest to 
    * pó¼niej wykorzystywane przez metodê 
    * \link DireTableIterator::Reset Reset\endlink.
    */
  int      _Idx_o; 
  int      _Idx; /*!< Indeks bie¿±cego elementu wskazywanego przez iterator */
  TabType *_BasePtr;   /*!< Wska¼nik na pocz±tek tablicy.                   */
    /*!
     *  Status ostatniej operacji (in/de)krementacji.
     *  Warto¶æ \p true oznacza, ¿e operacja siê powiod³a i nastêpny element
     *  kolejki jest dostêpny. W przypadku przeciwnym pole ma warto¶æ 
     *  \p false.
     */
  bool      _OpStatus;

  public:
   DireTableIterator(unsigned int No, TabType *Tab, int Idx = 0 )
                                            throw (ViException_OutOfRange);
   /*!
    *  Konwerter udostêpnia warto¶æ pola 
    *  \link DireTableIterator::_OpStatus _OpStatus\endlink
    *  okre¶laj±c± stan ostatniej operacji.
    */
   operator bool () const { return _OpStatus; }
   /*!
    *  Operator przedrostkowy.
    *  Realizuje operacjê cofniêcia siê do poprzedniego elementu 
    *  tablicy.
    *  \post Je¿eli operacja dekrementacji nie spowoduje wyj¶cia poza
    *     zakres tablicy, to jest ona wykonywana (dekrementowane jest
    *     pole \link DireTableIterator::_Idx _Idx\endlink) i polu 
    *     \link DireTableIterator::_OpStatus _Status\endlink przypisana 
    *     zostaje warto¶æ \p true. W przypadku przeciwnym pole 
    *     \link DireTableIterator::_Idx _Idx\endlink
    *     nie zostaje zmodyfikowane, za¶ polu 
    *     \link DireTableIterator::_OpStatus _Status\endlink przypisywana jest
    *     warto¶æ \p false.
    */
   DireTableIterator &operator -- ()
    {
      _OpStatus = (--_Idx < 0) ? ( ++_Idx, false ) : true;
      return *this;
    }

   /*!
    *  Operator postfiksowy.
    *  \warning Je¿eli nie jest to konieczne, to nie nale¿y go u¿ywaæ.
    *            Jest wolniejszy od operatora prefiksowego.
    *
    *  Realizuje operacjê cofniêcia siê do poprzedniego elementu 
    *  tablicy.
    *  \post Je¿eli operacja dekrementacji nie spowoduje wyj¶cia poza
    *     zakres tablicy, to jest ona wykonywana (dekrementowane jest
    *     pole \link DireTableIterator::_Idx _Idx\endlink) i polu 
    *     \link DireTableIterator::_OpStatus _Status\endlink przypisana 
    *     zostaje warto¶æ \p true. W przypadku przeciwnym pole 
    *     \link DireTableIterator::_Idx _Idx\endlink nie zostaje 
    *     zmodyfikowane, za¶ polu 
    *     \link DireTableIterator::_OpStatus _Status\endlink przypisywana jest
    *     warto¶æ \p false.
    */
   DireTableIterator &operator -- (int)
    {
      return --*this;
    }

   /*!
    *  Operator przedrostkowy.
    *  Realizuje operacjê przej¶cia w przód siê do nastêpnego elementu 
    *  tablicy.
    *  \post Je¿eli operacja inkrementacji nie spowoduje wyj¶cia poza
    *     zakres tablicy, to jest ona wykonywana (inkrementowane jest
    *     pole \link DireTableIterator::_Idx _Idx\endlink) i polu 
    *     \link DireTableIterator::_OpStatus _Status\endlink przypisana
    *     zostaje warto¶æ \p true. W przypadku przeciwnym pole 
    *     \link DireTableIterator::_Idx _Idx\endlink
    *     nie zostaje zmodyfikowane, za¶ polu 
    *     \link DireTableIterator::_OpStatus _Status\endlink przypisywana jest
    *     warto¶æ \p false.
    */
   DireTableIterator &operator ++ ()
    {
      _OpStatus = (++_Idx >= _No) ? ( --_Idx, false ) : true;
      return *this;
    }

   /*!
    *  Operator postfiksowy.
    *  \warning Je¿eli nie jest to konieczne, to nie nale¿y go u¿ywaæ.
    *            Jest wolniejszy od operatora prefiksowego.
    *
    *  Realizuje operacjê przej¶cia w przód siê do nastêpnego elementu 
    *  tablicy.
    *  \post Je¿eli operacja inkrementacji nie spowoduje wyj¶cia poza
    *     zakres tablicy, to jest ona wykonywana (inkrementowane jest
    *     pole \link DireTableIterator::_Idx _Idx\endlink) i polu 
    *     \link DireTableIterator::_OpStatus _Status\endlink przypisana
    *     zostaje warto¶æ \p true. W przypadku przeciwnym pole 
    *     \link DireTableIterator::_Idx _Idx\endlink
    *     nie zostaje zmodyfikowane, za¶ polu 
    *     \link DireTableIterator::_OpStatus _Status\endlink przypisywana jest
    *     warto¶æ \p false.
    */
   DireTableIterator &operator ++ (int)
    {
      return ++*this;
    }


   /*!
    *  Konwerter udostêpnia wska¼nik na bie¿±cy element tablicy.
    */
  virtual operator TabType* () const { return _BasePtr+_Idx; }
   /*!
    *  Udostêpnia referencjê do bie¿±cego elementu tablicy.
    */
   virtual TabType &operator *  () const { return *(_BasePtr+_Idx); }
   /*!
    *  Operator wy³uskiwania udostêpnia wska¼nik na bie¿±cy element tablicy.
    */
   virtual TabType *operator -> () const { return _BasePtr+_Idx; }
  
   /*!
    * Udostêpnia wska¼nik na bie¿±cy element tablicy.
    */
   TabType *Get() const { return _BasePtr+_Idx; }

    /*!
     *  Udostêpnia indeks bie¿±cego elementu tablicy (wskazywanego przez 
     *  iterator).
     */
   int Index() const { return _Idx; }
   /*!
    * Sprowadza interator do stanu pocz±tkowego, tzn. takiego jaki by³
    * w momencie jego utowrzenia.
    */
   void Reset() { _Idx = _Idx_o; }   
};



/*!
 *  Inicjalizuje iterator kojarz±c go z dan± tablic±.
 *  \param  No - ilo¶æ elementów tablicy,
 *  \param  Tab - wska¼nik na pocz±tek tablicy,
 *  \param  Idx - warto¶æ pocz±tkowa indeksu.
 *  \pre \e Tab != \p NULL, 0 <= \e Idx < \e No;
 *  \post Je¿eli warto¶æ \e Idx nie spe³nia warunku pocz±tkowego,
 *      to zg³aszany jest wyj±tek 
 *      \link ViException_OutOfRange ViException_OutOfRange\endlink.
 *      Jako numer b³êdu ma warto¶æ 
 *   \link vierrors.hh::ERRNUM_TABITER_BADINIT ERRNUM_TABITER_BADINIT\endlink,
 *    za¶ jako numer pomocniczy: 1.
 *      W przypadku przeciwnym pole
 *      \link IndiTableIterator::_OpStatus _OpStatus\endlink
 *        inicjalizowane jest warto¶ci± \p true.
 */
template <class TabType, int ID>
DireTableIterator<TabType,ID>::DireTableIterator( unsigned int  No, 
                                                  TabType      *Tab,
                                                  int           Idx
                                                )
  throw (ViException_OutOfRange)
{
  _No = No;  _BasePtr = Tab;  _Idx_o = _Idx = Idx; 
  if ((Idx < 0) || ((int)No <= Idx))  
    throw ViException_OutOfRange(ERRNUM_TABITER_BADINIT,
                                 ERRMSG_TABITER_BADINIT,1);
   _OpStatus = true;
}
#endif
