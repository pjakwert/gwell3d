#ifndef BASEITERATOR_HH
#define BASEITERATOR_HH

/*!  
 * \file baseiterator.hh
 * \author  Bogdan Kreczmer
 * \date    2004.03.23
 *
 *  Plik zawiera definicj� szablonu klas
 *  BaseIterator 
 *  umo�liwiaj�cej przechodzedzenie po kolejnych elementach
 *  iterowanego zbioru.
 *  Szablon stanowi podstaw� do konstrukjci dalszych iterator�w.
 */



#ifdef __GNUG__
#pragma interface
#endif



#include "vierrors.hh"
#include "viexception.hh"

/*!
 *  Szablon jest przeznaczony do definiowania iterator�w.
 *  \param TabType - typ element�w tablicy,
 *  \param ElemType - typ element�w uzyskiwanych z po�redniego dost�pu
 *              poprzez interowan� tablic�,
 *  \param ID - indentyfikator umo�liwiaj�cy rozro�nienie nazw typ�w, w
 *            przypadku gdy pierwszy parametr dla dw�ch typ�w jest identyczny.
 */
template <class IteratorType, class ElemType, int ID = 0>
class BaseIterator {
   /*!
    *  Status ostatniej operacji (in/de)krementacji.
    *  Warto�� \e true oznacza, �e operacja si� powiod�a i nast�pny element
    *  kolejki jest dost�pny. W przypadku przeciwnym pole ma warto�� 
    *  \e false.
    */
  bool      _OpStatus;
   /*!
    *  Przechowuje warto�� pocz�tkow� statusu operacji.
    */
  bool      _InitStatus;
 protected:
  /*!
   *  Nadaje nowa warto�� polu statusu operacji.
   *  \param val - nowa warto�� dla pola statusu operacji.
   *  \post Do pola \link BaseIterator::_OpStatus _OpStatus\endlink
   *        wpisana zostaje nowa warto��.
   */
  void SetStatus(bool val) { _OpStatus = val; }


  /*!
   *  Podstawia now� warto�� do pola statusu operacji i 
   *  zwraca iterator.
   *  \param val - nowa warto�� dla pola statusu operacji.
   *  \post Do pola \link BaseIterator::_OpStatus _OpStatus\endlink
   *        wpisana zostaje nowa warto��.
   *  \return referencj� do samego siebie (\b *this).
   */
  IteratorType &Iter_SetStatus(bool val) 
                           { _OpStatus = val;  return *(IteratorType*)this; }
 public:
   BaseIterator();
   /*!
    * Jedynie po to, aby by� destruktor wirtualny.
    */
   virtual ~BaseIterator() {}

  /*!
   *  Przypisuje warto�� statusu po zainicjowaniu iteratora.
   *  Metoda ta jest przeznaczona do stosowania w szablonach pochodnych
   *  iterator�w. Nie jest zalecane jej u�ywanie na poziomie aplikacji.
   */
  void SetInit() { _InitStatus = _OpStatus; }

   /*!
    *  Przywraca pocz�tkowy stan operatora.
    */
  void Reset() { _OpStatus = _InitStatus; }

   /*!
    *  Konwerter udost�pnia warto�� pola 
    *  \link BaseIterator::_OpStatus _OpStatus\endlink
    *  okre�laj�c� stan ostatniej operacji.
    */
   operator bool () const { return _OpStatus; }

   /*!
    *  Udost�pnia warto�� pola statusu operacji (pole 
    *  \link BaseIterator::_OpStatus _OpStatus\endlink)
    */
   bool GetStatus() const { return _OpStatus; }  

   /*!
    *  Operator postfiksowy.
    *  \warning Je�eli nie jest to konieczne, to nie nale�y go u�ywa�.
    *            Jest wolniejszy od operatora prefiksowego.
    *            Operator iteracji prefiksowej musi by� zaimplementowany
    *            w klasie pochodnej.
    *
    *  Realizuje operacj� cofni�cia si� do poprzedniego elementu.
    */
   IteratorType &operator -- (int) { return --*(IteratorType*)this; }


   /*!
    *  Operator postfiksowy.
    *  \warning Je�eli nie jest to konieczne, to nie nale�y go u�ywa�.
    *            Jest wolniejszy od operatora prefiksowego.
    *            Operator iteracji prefiksowej musi by� zaimplementowany
    *            w klasie pochodnej.
    *
    *  Realizuje operacj� przej�cia w prz�d si� do nast�pnego elementu.
    */
   IteratorType &operator ++ (int) { return ++*(IteratorType*)this; }

   /*!
    *  Konwerter udost�pnia wska�nik bie�ego iterowanego elementu.
    */
   virtual operator ElemType* () const = 0;
   /*!
    *  Udost�pnia referencj� do bie��cego iterowanego elementu.
    */
   ElemType& operator *  () const { return *this->operator ElemType*(); }
   /*!
    *   Udost�pnia wska�nik na bie��cy iterowany element.
    */
   ElemType* operator -> () const { return this->operator ElemType*(); }

   /*!
    *  Udost�pnia wska�nik na bie��cy iterowany element.
    */
   ElemType* Get() const { return this->operator ElemType*(); }
};



/*!
 *  Inicjalizuje iterator ustawiaj�c status operacji na warto�� \p true
 *   (pole \link BaseIterator::_OpStatus _OpStatus\endlink).
 */
template <class TabType, class ElemType, int ID>
BaseIterator<TabType,ElemType,ID>::BaseIterator()
{
  _OpStatus = true;  SetInit();
}
#endif
