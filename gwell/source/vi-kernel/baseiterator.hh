#ifndef BASEITERATOR_HH
#define BASEITERATOR_HH

/*!  
 * \file baseiterator.hh
 * \author  Bogdan Kreczmer
 * \date    2004.03.23
 *
 *  Plik zawiera definicjê szablonu klas
 *  BaseIterator 
 *  umo¿liwiaj±cej przechodzedzenie po kolejnych elementach
 *  iterowanego zbioru.
 *  Szablon stanowi podstawê do konstrukjci dalszych iteratorów.
 */



#ifdef __GNUG__
#pragma interface
#endif



#include "vierrors.hh"
#include "viexception.hh"

/*!
 *  Szablon jest przeznaczony do definiowania iteratorów.
 *  \param TabType - typ elementów tablicy,
 *  \param ElemType - typ elementów uzyskiwanych z po¶redniego dostêpu
 *              poprzez interowan± tablicê,
 *  \param ID - indentyfikator umo¿liwiaj±cy rozro¿nienie nazw typów, w
 *            przypadku gdy pierwszy parametr dla dwóch typów jest identyczny.
 */
template <class IteratorType, class ElemType, int ID = 0>
class BaseIterator {
   /*!
    *  Status ostatniej operacji (in/de)krementacji.
    *  Warto¶æ \e true oznacza, ¿e operacja siê powiod³a i nastêpny element
    *  kolejki jest dostêpny. W przypadku przeciwnym pole ma warto¶æ 
    *  \e false.
    */
  bool      _OpStatus;
   /*!
    *  Przechowuje warto¶æ pocz±tkow± statusu operacji.
    */
  bool      _InitStatus;
 protected:
  /*!
   *  Nadaje nowa warto¶æ polu statusu operacji.
   *  \param val - nowa warto¶æ dla pola statusu operacji.
   *  \post Do pola \link BaseIterator::_OpStatus _OpStatus\endlink
   *        wpisana zostaje nowa warto¶æ.
   */
  void SetStatus(bool val) { _OpStatus = val; }


  /*!
   *  Podstawia now± warto¶æ do pola statusu operacji i 
   *  zwraca iterator.
   *  \param val - nowa warto¶æ dla pola statusu operacji.
   *  \post Do pola \link BaseIterator::_OpStatus _OpStatus\endlink
   *        wpisana zostaje nowa warto¶æ.
   *  \return referencjê do samego siebie (\b *this).
   */
  IteratorType &Iter_SetStatus(bool val) 
                           { _OpStatus = val;  return *(IteratorType*)this; }
 public:
   BaseIterator();
   /*!
    * Jedynie po to, aby by³ destruktor wirtualny.
    */
   virtual ~BaseIterator() {}

  /*!
   *  Przypisuje warto¶æ statusu po zainicjowaniu iteratora.
   *  Metoda ta jest przeznaczona do stosowania w szablonach pochodnych
   *  iteratorów. Nie jest zalecane jej u¿ywanie na poziomie aplikacji.
   */
  void SetInit() { _InitStatus = _OpStatus; }

   /*!
    *  Przywraca pocz±tkowy stan operatora.
    */
  void Reset() { _OpStatus = _InitStatus; }

   /*!
    *  Konwerter udostêpnia warto¶æ pola 
    *  \link BaseIterator::_OpStatus _OpStatus\endlink
    *  okre¶laj±c± stan ostatniej operacji.
    */
   operator bool () const { return _OpStatus; }

   /*!
    *  Udostêpnia warto¶æ pola statusu operacji (pole 
    *  \link BaseIterator::_OpStatus _OpStatus\endlink)
    */
   bool GetStatus() const { return _OpStatus; }  

   /*!
    *  Operator postfiksowy.
    *  \warning Je¿eli nie jest to konieczne, to nie nale¿y go u¿ywaæ.
    *            Jest wolniejszy od operatora prefiksowego.
    *            Operator iteracji prefiksowej musi byæ zaimplementowany
    *            w klasie pochodnej.
    *
    *  Realizuje operacjê cofniêcia siê do poprzedniego elementu.
    */
   IteratorType &operator -- (int) { return --*(IteratorType*)this; }


   /*!
    *  Operator postfiksowy.
    *  \warning Je¿eli nie jest to konieczne, to nie nale¿y go u¿ywaæ.
    *            Jest wolniejszy od operatora prefiksowego.
    *            Operator iteracji prefiksowej musi byæ zaimplementowany
    *            w klasie pochodnej.
    *
    *  Realizuje operacjê przej¶cia w przód siê do nastêpnego elementu.
    */
   IteratorType &operator ++ (int) { return ++*(IteratorType*)this; }

   /*!
    *  Konwerter udostêpnia wska¼nik bie¿ego iterowanego elementu.
    */
   virtual operator ElemType* () const = 0;
   /*!
    *  Udostêpnia referencjê do bie¿±cego iterowanego elementu.
    */
   ElemType& operator *  () const { return *this->operator ElemType*(); }
   /*!
    *   Udostêpnia wska¼nik na bie¿±cy iterowany element.
    */
   ElemType* operator -> () const { return this->operator ElemType*(); }

   /*!
    *  Udostêpnia wska¼nik na bie¿±cy iterowany element.
    */
   ElemType* Get() const { return this->operator ElemType*(); }
};



/*!
 *  Inicjalizuje iterator ustawiaj±c status operacji na warto¶æ \p true
 *   (pole \link BaseIterator::_OpStatus _OpStatus\endlink).
 */
template <class TabType, class ElemType, int ID>
BaseIterator<TabType,ElemType,ID>::BaseIterator()
{
  _OpStatus = true;  SetInit();
}
#endif
