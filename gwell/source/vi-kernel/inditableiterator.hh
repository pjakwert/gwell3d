#ifndef INDITABLEITERATOR_HH
#define INDITABLEITERATOR_HH

/*!  
 * \file inditableiterator.hh
 * \author  Bogdan Kreczmer
 * \date    2004.03.23
 *
 *  Plik zawiera definicj� szablonu klas
 *   \link IndiTableIterator IndiTableIterator\endlink
 *  (Indirect Table Iterator)
 *  umo�liwiaj�cej przechodzedzenie po kolejnych elementach tablic
 *  stanowi�cej po�rednie odwo�anie do element�w w innej tablicy.
 */



#ifdef __GNUG__
#pragma interface
#endif



#include "vierrors.hh"
#include "viexception.hh"

/*!
 *  Szablon jest przeznaczony do definiowania iterator�w dla struktur danych
 *  opartych na tablicach z po�rednim dost�pem do element�w docelowych
 *  poprzez te tablice.
 *  \param TabType - typ element�w tablicy,
 *  \param ElemType - typ element�w uzyskiwanych z po�redniego dost�pu
 *              poprzez interowan� tablic�,
 *  \param ID - indentyfikator umo�liwiaj�cy rozro�nienie nazw typ�w, w
 *            przypadku gdy pierwszy parametr dla dw�ch typ�w jest identyczny.
 */
template <class TabType, class ElemType, int ID = 0>
class IndiTableIterator {
 protected:
  int        _No;  /*!< Ilo�� element�w tablicy.                            */
   /*!
    * Warto�� indeksu nadana w momencie inicjalizacji iteratora. Jest to 
    * p�niej wykorzystywane przez metod� 
    * \link IndiTableIterator::Reset Reset\endlink.
    */
  int      _Idx_o; 
  int      _Idx; /*!< Indeks bie��cego elementu wskazywanego przez iterator */
  TabType *_BasePtr;   /*!< Wska�nik na pocz�tek tablicy.                   */
    /*!
     *  Status ostatniej operacji (in/de)krementacji.
     *  Warto�� \e true oznacza, �e operacja si� powiod�a i nast�pny element
     *  kolejki jest dost�pny. W przypadku przeciwnym pole ma warto�� 
     *  \e false.
     */
  bool      _OpStatus;

 public:
   IndiTableIterator(unsigned int No, TabType *Tab, int Idx = 0 );
   /*!
    * Jedynie po to, aby by� destruktor wirtualny.
    */
   virtual ~IndiTableIterator() {}

   /*!
    *  Konwerter udost�pnia warto�� pola 
    *  \link IndiTableIterator::_OpStatus _OpStatus\endlink
    *  okre�laj�c� stan ostatniej operacji.
    */
   operator bool () const { return _OpStatus; }
   /*!
    *  Operator przedrostkowy.
    *  Realizuje operacj� cofni�cia si� do poprzedniego elementu 
    *  tablicy.
    *  \post Je�eli operacja dekrementacji nie spowoduje wyj�cia poza
    *     zakres tablicy, to jest ona wykonywana (dekrementowane jest
    *     pole \link IndiTableIterator::_Idx _Idx\endlink) i polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink przypisana zostaje
    *     warto�� \p true.
    *     W przypadku przeciwnym pole 
    *     \link IndiTableIterator::_Idx _Idx\endlink
    *     nie zostaje zmodyfikowane, za� polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink przypisywana jest
    *     warto�� \p false.
    */
   IndiTableIterator &operator -- ()
    {
      _OpStatus = (--_Idx < 0) ? ( ++_Idx, false ) : true;
      return *this;
    }

   /*!
    *  Operator postfiksowy.
    *  \warning Je�eli nie jest to konieczne, to nie nale�y go u�ywa�.
    *            Jest wolniejszy od operatora prefiksowego.
    *
    *  Realizuje operacj� cofni�cia si� do poprzedniego elementu 
    *  tablicy.
    *  \post Je�eli operacja dekrementacji nie spowoduje wyj�cia poza
    *     zakres tablicy, to jest ona wykonywana (dekrementowane jest
    *     pole \link IndiTableIterator::_Idx _Idx\endlink) i polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink przypisana
    *     zostaje warto�� \p true. W przypadku przeciwnym pole 
    *     \link IndiTableIterator::_Idx _Idx\endlink
    *     nie zostaje zmodyfikowane, za� polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink przypisywana jest
    *     warto�� \p false.
    */
   IndiTableIterator &operator -- (int)
    {
      return --*this;
    }

   /*!
    *  Operator przedrostkowy.
    *  Realizuje operacj� przej�cia w prz�d si� do nast�pnego elementu 
    *  tablicy.
    *  \post Je�eli operacja inkrementacji nie spowoduje wyj�cia poza
    *     zakres tablicy, to jest ona wykonywana (inkrementowane jest
    *     pole \link IndiTableIterator::_Idx _Idx\endlink) i polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink przypisana
    *     zostaje warto�� \p true. W przypadku przeciwnym pole 
    *     \link IndiTableIterator::_Idx _Idx\endlink
    *     nie zostaje zmodyfikowane, za� polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink przypisywana jest
    *     warto�� \p false.
    */
   IndiTableIterator &operator ++ ()
    {
      _OpStatus = (++_Idx >= _No) ? ( --_Idx, false ) : true;
      return *this;
    }

   /*!
    *  Operator postfiksowy.
    *  \warning Je�eli nie jest to konieczne, to nie nale�y go u�ywa�.
    *            Jest wolniejszy od operatora prefiksowego.
    *
    *  Realizuje operacj� przej�cia w prz�d si� do nast�pnego elementu 
    *  tablicy.
    *  \post Je�eli operacja inkrementacji nie spowoduje wyj�cia poza
    *     zakres tablicy, to jest ona wykonywana (inkrementowane jest
    *     pole \link IndiTableIterator::_Idx _Idx\endlink) i polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink przypisana
    *     zostaje warto�� \p true. W przypadku przeciwnym pole 
    *     \link IndiTableIterator::_Idx _Idx\endlink
    *     nie zostaje zmodyfikowane, za� polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink przypisywana jest
    *     warto�� \p false.
    */
   IndiTableIterator &operator ++ (int)
    {
      return ++*this;
    }

   /*!
    *  Konwerter udost�pnia wska�nik na bie��cy element tablicy.
    */
   virtual operator ElemType* () const = 0;
   /*!
    *  Udost�pnia referencj� do bie��cego elementu tablicy.
    */
   virtual ElemType& operator *  () const { return *(ElemType*)this; }
   /*!
    *  Konwerter udost�pnia wska�nik na bie��cy element tablicy.
    */
   virtual ElemType* operator -> () const { return (ElemType*)this; }
    /*!
     *  Udost�pnia indeks bie��cego elementu tablicy (wskazywanego przez 
     *  iterator).
     */
   int Index() const { return _Idx; }
   /*!
    * Sprowadza interator do stanu pocz�tkowego, tzn. takiego jaki by�
    * w momencie jego utowrzenia.
    */
   void Reset() { _Idx = _Idx_o; }   
};



/*!
 *  Inicjalizuje iterator kojarz�c go z dan� tablic�.
 *  \param  No - ilo�� element�w tablicy,
 *  \param  Tab - wska�nik na pocz�tek tablicy,
 *  \param  Idx - warto�� pocz�tkowa indeksu.
 *  \pre \e Tab != \p NULL, 0 <= \e Idx < \e No;
 *  \post Je�eli warto�� \e Idx nie spe�nia warunku pocz�tkowego,
 *      to zg�aszany jest wyj�tek 
 *      \link ViException_OutOfRange ViException_OutOfRange\endlink.
 *      Jako numer b��du ma warto�� 
 *   \link vierrors.hh::ERRNUM_TABITER_BADINIT ERRNUM_TABITER_BADINIT\endlink,
 *   za� jako numer pomocniczy: 2.
 *      W przypadku przeciwnym pole
 *      \link IndiTableIterator::_OpStatus _OpStatus\endlink
 *        inicjalizowane jest warto�ci� \p true.
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
