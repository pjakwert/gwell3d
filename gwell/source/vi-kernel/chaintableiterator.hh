#ifndef CHAINTABLEITERATOR_HH
#define CHAINTABLEITERATOR_HH
/*!
 * \file  chaintableiterator.hh
 * Plik zawiera definicje szablonu iteratora ChainTableIterator
 * Szablon ten przeznaczony jest do iterowania tablic w wyniku, kt�rej to
 * iteracji
 * tworz� si� struktury po�rednie, kt�re nie wyst�puj� jawnie w �adnej
 * tablicy. 
 * \author Bogdan Kreczmer
 * \date   2004.03.29
 */

#include "inditableiterator.hh"

/*!
 * Szablon przeznaczony jest do iterowania niejawnych tablic, w wyniku
 * kt�rej to iteracji
 * tworz� si� struktury po�rednie, kt�re nie wyst�puj� jawnie w �adnej
 * tablicy.
 *  \param OwnerType - typ obiektu, dla kt�rego wywo�any zostaje ten iterator.
 *  \param ElemType - typ element�w uzyskiwanych z po�redniego dost�pu
 *              poprzez interowan� tablic�,
 *  \param FieldType - typ struktury po�redniej,
 *  \param ID - indentyfikator umo�liwiaj�cy rozro�nienie nazw typ�w, w
 *            przypadku gdy pierwszy parametr dla dw�ch typ�w jest identyczny.
 */
template <class OwnerType, class ElemType, int ID = 0>
class ChainTableIterator: public IndiTableIterator<void,ElemType,ID> {
 protected:

   /*!
    * Wska�nik na w�a�ciela danego iteratoro. Jest on konieczny, aby
    * mo�na by�o odpowiednio ini
    */
   OwnerType  *_pOwner;
   /*!
    * Pole struktury po�redniej otrzymywanej na podstawie danych 
    * z iterowanej tablicy.
    */
   ElemType  _Field;
   /*!
    * Metoda jest wywo�ywana po ka�dorazowej iteracji i aktualizuje
    * pole \link ChainTableIterator::_Field _Field\endlink.
    */ 
   virtual void UpdateField() = 0;

   /*!
    * Metoda jest wywo�ywana po zainicjalizwaniu iteratora oraz
    * przy wykonywaniu operacji 
    * \link ChainTableIterator::Reset Reset\endlink.
    * Metoda inicjalizuje pole \link ChainTableIterator::_Field _Field\endlink.
    *
    * \warning Metoda ta musi by� wywo�ana w konstruktorze klasy pochodnej, gdy
    *          spe�nione s� ju� wszystkie warunki do poprawnej inicjalizacji
    *          tego pola.
    */ 
  virtual void InitField() = 0;

 public:


   /*!
    *  Inicjalizuje iterator kojarz�c go z dan� tablic�.
    *  \param  pOwner - wska�nik do obiektu, dla kt�rego wywo�ywany jest
    *                  ten iterator,
    *  \param  No - ilo�� element�w tablicy,
    *  \param  Idx - warto�� pocz�tkowa indeksu.
    *  \pre  \f$ 0 \le  Idx <  No \f$;
    *  \post Je�eli warto�� \e Idx nie spe�nia warunku pocz�tkowego,
    *      to zg�aszany jest wyj�tek 
    *      \link ViException_OutOfRange ViException_OutOfRange\endlink
    *     przez konstruktor szablon IndiTableIterator.
    *      Jako numer b��du ma warto�� 
    *  \link vierrors.hh::ERRNUM_TABITER_BADINIT 
    *                                        ERRNUM_TABITER_BADINIT\endlink,
    *   za� jako numer pomocniczy: 2.
    *      W przypadku przeciwnym pole
    *      \link IndiTableIterator::_OpStatus _OpStatus\endlink
    *     dziedziczone z IndiTableIterator
    *        inicjalizowane jest warto�ci� \p true.
    *  inicjalizacji pola  
    *  \link ChainTableIterator::_Field _Field\endlink.
    */
  ChainTableIterator(  OwnerType     *pOwner, 
                       unsigned int    No, 
                       unsigned int    Idx = 0 ):
    IndiTableIterator<void,ElemType,ID>(No,(void*)0L,Idx), _pOwner(pOwner)
     { }

   /*!
    *  Inicjalizuje iterator kojarz�c go z dan� tablic�.
    *  \param  No - ilo�� element�w tablicy,
    *  \param  pOwner - wska�nik do obiektu, dla kt�rego wywo�ywany jest
    *                  ten iterator,
    *  \param  Idx - warto�� pocz�tkowa indeksu.
    *  \pre  \f$ 0 \le  Idx <  No \f$;
    *  \post Je�eli warto�� \e Idx nie spe�nia warunku pocz�tkowego,
    *      to zg�aszany jest wyj�tek 
    *      \link ViException_OutOfRange ViException_OutOfRange\endlink
    *     przez konstruktor szablon IndiTableIterator.
    *      Jako numer b��du ma warto�� 
    *  \link vierrors.hh::ERRNUM_TABITER_BADINIT 
    *                                        ERRNUM_TABITER_BADINIT\endlink,
    *   za� jako numer pomocniczy: 2.
    *      W przypadku przeciwnym pole
    *      \link IndiTableIterator::_OpStatus _OpStatus\endlink
    *     dziedziczone z IndiTableIterator
    *        inicjalizowane jest warto�ci� \p true.
    *  inicjalizacji pola  
    *  \link ChainTableIterator::_Field _Field\endlink. \n
    *  W konstruktorze tym dla pola
    *  \link ChainTableIterator::_Field _Field\endlink wywo�any zostaje
    *  konstruktor ElemType(OwnerType &,unsigned int).
    */
  ChainTableIterator(  unsigned int    No,
                       OwnerType     *pOwner, 
                       unsigned int    Idx = 0 ):
    IndiTableIterator<void,ElemType,ID>(No,(void*)0L,Idx), _pOwner(pOwner),
    _Field(*pOwner,Idx)
     { }

   /*!
    *  Konwerter udost�pnia wska�nik na bie��cy element tablicy.
    */
   virtual operator ElemType* () const { return &_Field; }
   /*!
    *  Udost�pnia referencj� do bie��cego elementu tablicy.
    */
   virtual ElemType &operator *  () const { return _Field; }
   /*!
    *  Konwerter udost�pnia wska�nik na bie��cy element tablicy.
    */
   virtual ElemType *operator -> () const { return &_Field; }

   /*!
    *  Operator przedrostkowy.
    *  Realizuje operacj� przej�cia w prz�d si� do nast�pnego elementu 
    *  tablicy.
    *  \post Je�eli operacja inkrementacji nie spowoduje wyj�cia poza
    *     zakres tablicy, to jest ona wykonywana (inkrementowane jest
    *     pole \link IndiTableIterator::_Idx _Idx\endlink dziedziczone
    *     z IndiTableIterator) i polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink (pole dziedziczone
    *     z IndiTableIterator) przypisana
    *     zostaje warto�� \p true. W przypadku przeciwnym pole 
    *     \link IndiTableIterator::_Idx _Idx\endlink
    *     nie zostaje zmodyfikowane, za� polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink przypisywana jest
    *     warto�� \p false.
    */
    ChainTableIterator &operator ++ ()
     { 
       if (!IndiTableIterator<void,ElemType,ID>::operator++()) return *this;
       InitField();
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
    *     pole \link IndiTableIterator::_Idx _Idx\endlink dziedziczone
    *     z IndiTableIterator) i polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink (pole dziedziczone
    *     z IndiTableIterator) przypisana
    *     zostaje warto�� \p true. W przypadku przeciwnym pole 
    *     \link IndiTableIterator::_Idx _Idx\endlink
    *     nie zostaje zmodyfikowane, za� polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink przypisywana jest
    *     warto�� \p false.
    */
    ChainTableIterator &operator ++ (int)
     { 
       return ++*this;
     }



   /*!
    *  Operator przedrostkowy.
    *  Realizuje operacj� przej�cia w ty� si� do poprzedniego elementu 
    *  tablicy.
    *  \post Je�eli operacja dekrementacji nie spowoduje wyj�cia poza
    *     zakres tablicy, to jest ona wykonywana (dekrementowane jest
    *     pole \link IndiTableIterator::_Idx _Idx\endlink dziedziczone
    *     z IndiTableIterator) i polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink (pole dziedziczone
    *     z IndiTableIterator) przypisana
    *     zostaje warto�� \p true. W przypadku przeciwnym pole 
    *     \link IndiTableIterator::_Idx _Idx\endlink
    *     nie zostaje zmodyfikowane, za� polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink przypisywana jest
    *     warto�� \p false.
    */
    ChainTableIterator &operator -- ()
     { 
       if (!IndiTableIterator<void,ElemType,ID>::operator--()) return *this;
       InitField();
       return *this;
     }


   /*!
    *  Operator postfiksowy.
    *  \warning Je�eli nie jest to konieczne, to nie nale�y go u�ywa�.
    *            Jest wolniejszy od operatora prefiksowego.
    *
    *  Realizuje operacj� przej�cia w ty� si� do poprzedniego elementu 
    *  tablicy.
    *  \post Je�eli operacja dekrementacji nie spowoduje wyj�cia poza
    *     zakres tablicy, to jest ona wykonywana (dekrementowane jest
    *     pole \link IndiTableIterator::_Idx _Idx\endlink dziedziczone
    *     z IndiTableIterator) i polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink (pole dziedziczone
    *     z IndiTableIterator) przypisana
    *     zostaje warto�� \p true. W przypadku przeciwnym pole 
    *     \link IndiTableIterator::_Idx _Idx\endlink
    *     nie zostaje zmodyfikowane, za� polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink przypisywana jest
    *     warto�� \p false.
    */
    ChainTableIterator &operator -- (int)
     { 
       return --*this;
     }


   /*!
    * Sprowadza interator do stanu pocz�tkowego, tzn. takiego jaki by�
    * w momencie jego utowrzenia.
    */ 
   void Reset() { IndiTableIterator<void,ElemType,ID>::Reset(); InitField(); }

};

#endif
