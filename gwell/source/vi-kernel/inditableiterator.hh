#ifndef INDITABLEITERATOR_HH
#define INDITABLEITERATOR_HH

/*!  
 * \file inditableiterator.hh
 * \author  Bogdan Kreczmer
 * \date    2004.03.23
 *
 *  Plik zawiera definicjê szablonu klas
 *   \link IndiTableIterator IndiTableIterator\endlink
 *  (Indirect Table Iterator)
 *  umo¿liwiaj±cej przechodzedzenie po kolejnych elementach tablic
 *  stanowi±cej po¶rednie odwo³anie do elementów w innej tablicy.
 */



#ifdef __GNUG__
#pragma interface
#endif



#include "vierrors.hh"
#include "viexception.hh"

/*!
 *  Szablon jest przeznaczony do definiowania iteratorów dla struktur danych
 *  opartych na tablicach z po¶rednim dostêpem do elementów docelowych
 *  poprzez te tablice.
 *  \param TabType - typ elementów tablicy,
 *  \param ElemType - typ elementów uzyskiwanych z po¶redniego dostêpu
 *              poprzez interowan± tablicê,
 *  \param ID - indentyfikator umo¿liwiaj±cy rozro¿nienie nazw typów, w
 *            przypadku gdy pierwszy parametr dla dwóch typów jest identyczny.
 */
template <class TabType, class ElemType, int ID = 0>
class IndiTableIterator {
 protected:
  int        _No;  /*!< Ilo¶æ elementów tablicy.                            */
   /*!
    * Warto¶æ indeksu nadana w momencie inicjalizacji iteratora. Jest to 
    * pó¼niej wykorzystywane przez metodê 
    * \link IndiTableIterator::Reset Reset\endlink.
    */
  int      _Idx_o; 
  int      _Idx; /*!< Indeks bie¿±cego elementu wskazywanego przez iterator */
  TabType *_BasePtr;   /*!< Wska¼nik na pocz±tek tablicy.                   */
    /*!
     *  Status ostatniej operacji (in/de)krementacji.
     *  Warto¶æ \e true oznacza, ¿e operacja siê powiod³a i nastêpny element
     *  kolejki jest dostêpny. W przypadku przeciwnym pole ma warto¶æ 
     *  \e false.
     */
  bool      _OpStatus;

 public:
   IndiTableIterator(unsigned int No, TabType *Tab, int Idx = 0 );
   /*!
    * Jedynie po to, aby by³ destruktor wirtualny.
    */
   virtual ~IndiTableIterator() {}

   /*!
    *  Konwerter udostêpnia warto¶æ pola 
    *  \link IndiTableIterator::_OpStatus _OpStatus\endlink
    *  okre¶laj±c± stan ostatniej operacji.
    */
   operator bool () const { return _OpStatus; }
   /*!
    *  Operator przedrostkowy.
    *  Realizuje operacjê cofniêcia siê do poprzedniego elementu 
    *  tablicy.
    *  \post Je¿eli operacja dekrementacji nie spowoduje wyj¶cia poza
    *     zakres tablicy, to jest ona wykonywana (dekrementowane jest
    *     pole \link IndiTableIterator::_Idx _Idx\endlink) i polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink przypisana zostaje
    *     warto¶æ \p true.
    *     W przypadku przeciwnym pole 
    *     \link IndiTableIterator::_Idx _Idx\endlink
    *     nie zostaje zmodyfikowane, za¶ polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink przypisywana jest
    *     warto¶æ \p false.
    */
   IndiTableIterator &operator -- ()
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
    *     pole \link IndiTableIterator::_Idx _Idx\endlink) i polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink przypisana
    *     zostaje warto¶æ \p true. W przypadku przeciwnym pole 
    *     \link IndiTableIterator::_Idx _Idx\endlink
    *     nie zostaje zmodyfikowane, za¶ polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink przypisywana jest
    *     warto¶æ \p false.
    */
   IndiTableIterator &operator -- (int)
    {
      return --*this;
    }

   /*!
    *  Operator przedrostkowy.
    *  Realizuje operacjê przej¶cia w przód siê do nastêpnego elementu 
    *  tablicy.
    *  \post Je¿eli operacja inkrementacji nie spowoduje wyj¶cia poza
    *     zakres tablicy, to jest ona wykonywana (inkrementowane jest
    *     pole \link IndiTableIterator::_Idx _Idx\endlink) i polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink przypisana
    *     zostaje warto¶æ \p true. W przypadku przeciwnym pole 
    *     \link IndiTableIterator::_Idx _Idx\endlink
    *     nie zostaje zmodyfikowane, za¶ polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink przypisywana jest
    *     warto¶æ \p false.
    */
   IndiTableIterator &operator ++ ()
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
    *     pole \link IndiTableIterator::_Idx _Idx\endlink) i polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink przypisana
    *     zostaje warto¶æ \p true. W przypadku przeciwnym pole 
    *     \link IndiTableIterator::_Idx _Idx\endlink
    *     nie zostaje zmodyfikowane, za¶ polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink przypisywana jest
    *     warto¶æ \p false.
    */
   IndiTableIterator &operator ++ (int)
    {
      return ++*this;
    }

   /*!
    *  Konwerter udostêpnia wska¼nik na bie¿±cy element tablicy.
    */
   virtual operator ElemType* () const = 0;
   /*!
    *  Udostêpnia referencjê do bie¿±cego elementu tablicy.
    */
   virtual ElemType& operator *  () const { return *(ElemType*)this; }
   /*!
    *  Konwerter udostêpnia wska¼nik na bie¿±cy element tablicy.
    */
   virtual ElemType* operator -> () const { return (ElemType*)this; }
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
 *   za¶ jako numer pomocniczy: 2.
 *      W przypadku przeciwnym pole
 *      \link IndiTableIterator::_OpStatus _OpStatus\endlink
 *        inicjalizowane jest warto¶ci± \p true.
 */
template <class TabType, class ElemType, int ID>
inline
IndiTableIterator<TabType,ElemType,ID>::IndiTableIterator( unsigned int  No, 
                                                           TabType      *Tab,
                                                           int           Idx
                                                         )
{
  _No = No;  _BasePtr = Tab;  _Idx_o = _Idx = Idx; 
  if ((Idx < 0) || ((int)No <= Idx))  
    throw ViException_OutOfRange(ERRNUM_TABITER_BADINIT,
                                 MSG(ERRMSG_TABITER_BADINIT),2);
  _OpStatus = true;
}
#endif
