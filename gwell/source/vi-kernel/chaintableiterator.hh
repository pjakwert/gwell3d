#ifndef CHAINTABLEITERATOR_HH
#define CHAINTABLEITERATOR_HH
/*!
 * \file  chaintableiterator.hh
 * Plik zawiera definicje szablonu iteratora ChainTableIterator
 * Szablon ten przeznaczony jest do iterowania tablic w wyniku, której to
 * iteracji
 * tworz± siê struktury po¶rednie, które nie wystêpuj± jawnie w ¿adnej
 * tablicy. 
 * \author Bogdan Kreczmer
 * \date   2004.03.29
 */

#include "inditableiterator.hh"

/*!
 * Szablon przeznaczony jest do iterowania niejawnych tablic, w wyniku
 * której to iteracji
 * tworz± siê struktury po¶rednie, które nie wystêpuj± jawnie w ¿adnej
 * tablicy.
 *  \param OwnerType - typ obiektu, dla którego wywo³any zostaje ten iterator.
 *  \param ElemType - typ elementów uzyskiwanych z po¶redniego dostêpu
 *              poprzez interowan± tablicê,
 *  \param FieldType - typ struktury po¶redniej,
 *  \param ID - indentyfikator umo¿liwiaj±cy rozro¿nienie nazw typów, w
 *            przypadku gdy pierwszy parametr dla dwóch typów jest identyczny.
 */
template <class OwnerType, class ElemType, int ID = 0>
class ChainTableIterator: public IndiTableIterator<void,ElemType,ID> {
 protected:

   /*!
    * Wska¼nik na w³a¶ciela danego iteratoro. Jest on konieczny, aby
    * mo¿na by³o odpowiednio ini
    */
   OwnerType  *_pOwner;
   /*!
    * Pole struktury po¶redniej otrzymywanej na podstawie danych 
    * z iterowanej tablicy.
    */
   ElemType  _Field;
   /*!
    * Metoda jest wywo³ywana po ka¿dorazowej iteracji i aktualizuje
    * pole \link ChainTableIterator::_Field _Field\endlink.
    */ 
   virtual void UpdateField() = 0;

   /*!
    * Metoda jest wywo³ywana po zainicjalizwaniu iteratora oraz
    * przy wykonywaniu operacji 
    * \link ChainTableIterator::Reset Reset\endlink.
    * Metoda inicjalizuje pole \link ChainTableIterator::_Field _Field\endlink.
    *
    * \warning Metoda ta musi byæ wywo³ana w konstruktorze klasy pochodnej, gdy
    *          spe³nione s± ju¿ wszystkie warunki do poprawnej inicjalizacji
    *          tego pola.
    */ 
  virtual void InitField() = 0;

 public:


   /*!
    *  Inicjalizuje iterator kojarz±c go z dan± tablic±.
    *  \param  pOwner - wska¼nik do obiektu, dla którego wywo³ywany jest
    *                  ten iterator,
    *  \param  No - ilo¶æ elementów tablicy,
    *  \param  Idx - warto¶æ pocz±tkowa indeksu.
    *  \pre  \f$ 0 \le  Idx <  No \f$;
    *  \post Je¿eli warto¶æ \e Idx nie spe³nia warunku pocz±tkowego,
    *      to zg³aszany jest wyj±tek 
    *      \link ViException_OutOfRange ViException_OutOfRange\endlink
    *     przez konstruktor szablon IndiTableIterator.
    *      Jako numer b³êdu ma warto¶æ 
    *  \link vierrors.hh::ERRNUM_TABITER_BADINIT 
    *                                        ERRNUM_TABITER_BADINIT\endlink,
    *   za¶ jako numer pomocniczy: 2.
    *      W przypadku przeciwnym pole
    *      \link IndiTableIterator::_OpStatus _OpStatus\endlink
    *     dziedziczone z IndiTableIterator
    *        inicjalizowane jest warto¶ci± \p true.
    *  inicjalizacji pola  
    *  \link ChainTableIterator::_Field _Field\endlink.
    */
  ChainTableIterator(  OwnerType     *pOwner, 
                       unsigned int    No, 
                       unsigned int    Idx = 0 ):
    IndiTableIterator<void,ElemType,ID>(No,(void*)0L,Idx), _pOwner(pOwner)
     { }

   /*!
    *  Inicjalizuje iterator kojarz±c go z dan± tablic±.
    *  \param  No - ilo¶æ elementów tablicy,
    *  \param  pOwner - wska¼nik do obiektu, dla którego wywo³ywany jest
    *                  ten iterator,
    *  \param  Idx - warto¶æ pocz±tkowa indeksu.
    *  \pre  \f$ 0 \le  Idx <  No \f$;
    *  \post Je¿eli warto¶æ \e Idx nie spe³nia warunku pocz±tkowego,
    *      to zg³aszany jest wyj±tek 
    *      \link ViException_OutOfRange ViException_OutOfRange\endlink
    *     przez konstruktor szablon IndiTableIterator.
    *      Jako numer b³êdu ma warto¶æ 
    *  \link vierrors.hh::ERRNUM_TABITER_BADINIT 
    *                                        ERRNUM_TABITER_BADINIT\endlink,
    *   za¶ jako numer pomocniczy: 2.
    *      W przypadku przeciwnym pole
    *      \link IndiTableIterator::_OpStatus _OpStatus\endlink
    *     dziedziczone z IndiTableIterator
    *        inicjalizowane jest warto¶ci± \p true.
    *  inicjalizacji pola  
    *  \link ChainTableIterator::_Field _Field\endlink. \n
    *  W konstruktorze tym dla pola
    *  \link ChainTableIterator::_Field _Field\endlink wywo³any zostaje
    *  konstruktor ElemType(OwnerType &,unsigned int).
    */
  ChainTableIterator(  unsigned int    No,
                       OwnerType     *pOwner, 
                       unsigned int    Idx = 0 ):
    IndiTableIterator<void,ElemType,ID>(No,(void*)0L,Idx), _pOwner(pOwner),
    _Field(*pOwner,Idx)
     { }

   /*!
    *  Konwerter udostêpnia wska¼nik na bie¿±cy element tablicy.
    */
   virtual operator ElemType* () const { return &_Field; }
   /*!
    *  Udostêpnia referencjê do bie¿±cego elementu tablicy.
    */
   virtual ElemType &operator *  () const { return _Field; }
   /*!
    *  Konwerter udostêpnia wska¼nik na bie¿±cy element tablicy.
    */
   virtual ElemType *operator -> () const { return &_Field; }

   /*!
    *  Operator przedrostkowy.
    *  Realizuje operacjê przej¶cia w przód siê do nastêpnego elementu 
    *  tablicy.
    *  \post Je¿eli operacja inkrementacji nie spowoduje wyj¶cia poza
    *     zakres tablicy, to jest ona wykonywana (inkrementowane jest
    *     pole \link IndiTableIterator::_Idx _Idx\endlink dziedziczone
    *     z IndiTableIterator) i polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink (pole dziedziczone
    *     z IndiTableIterator) przypisana
    *     zostaje warto¶æ \p true. W przypadku przeciwnym pole 
    *     \link IndiTableIterator::_Idx _Idx\endlink
    *     nie zostaje zmodyfikowane, za¶ polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink przypisywana jest
    *     warto¶æ \p false.
    */
    ChainTableIterator &operator ++ ()
     { 
       if (!IndiTableIterator<void,ElemType,ID>::operator++()) return *this;
       InitField();
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
    *     pole \link IndiTableIterator::_Idx _Idx\endlink dziedziczone
    *     z IndiTableIterator) i polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink (pole dziedziczone
    *     z IndiTableIterator) przypisana
    *     zostaje warto¶æ \p true. W przypadku przeciwnym pole 
    *     \link IndiTableIterator::_Idx _Idx\endlink
    *     nie zostaje zmodyfikowane, za¶ polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink przypisywana jest
    *     warto¶æ \p false.
    */
    ChainTableIterator &operator ++ (int)
     { 
       return ++*this;
     }



   /*!
    *  Operator przedrostkowy.
    *  Realizuje operacjê przej¶cia w ty³ siê do poprzedniego elementu 
    *  tablicy.
    *  \post Je¿eli operacja dekrementacji nie spowoduje wyj¶cia poza
    *     zakres tablicy, to jest ona wykonywana (dekrementowane jest
    *     pole \link IndiTableIterator::_Idx _Idx\endlink dziedziczone
    *     z IndiTableIterator) i polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink (pole dziedziczone
    *     z IndiTableIterator) przypisana
    *     zostaje warto¶æ \p true. W przypadku przeciwnym pole 
    *     \link IndiTableIterator::_Idx _Idx\endlink
    *     nie zostaje zmodyfikowane, za¶ polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink przypisywana jest
    *     warto¶æ \p false.
    */
    ChainTableIterator &operator -- ()
     { 
       if (!IndiTableIterator<void,ElemType,ID>::operator--()) return *this;
       InitField();
       return *this;
     }


   /*!
    *  Operator postfiksowy.
    *  \warning Je¿eli nie jest to konieczne, to nie nale¿y go u¿ywaæ.
    *            Jest wolniejszy od operatora prefiksowego.
    *
    *  Realizuje operacjê przej¶cia w ty³ siê do poprzedniego elementu 
    *  tablicy.
    *  \post Je¿eli operacja dekrementacji nie spowoduje wyj¶cia poza
    *     zakres tablicy, to jest ona wykonywana (dekrementowane jest
    *     pole \link IndiTableIterator::_Idx _Idx\endlink dziedziczone
    *     z IndiTableIterator) i polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink (pole dziedziczone
    *     z IndiTableIterator) przypisana
    *     zostaje warto¶æ \p true. W przypadku przeciwnym pole 
    *     \link IndiTableIterator::_Idx _Idx\endlink
    *     nie zostaje zmodyfikowane, za¶ polu 
    *     \link IndiTableIterator::_OpStatus _Status\endlink przypisywana jest
    *     warto¶æ \p false.
    */
    ChainTableIterator &operator -- (int)
     { 
       return --*this;
     }


   /*!
    * Sprowadza interator do stanu pocz±tkowego, tzn. takiego jaki by³
    * w momencie jego utowrzenia.
    */ 
   void Reset() { IndiTableIterator<void,ElemType,ID>::Reset(); InitField(); }

};

#endif
