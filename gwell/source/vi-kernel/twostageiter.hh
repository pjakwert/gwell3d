#ifndef TWOSTAGEITER_HH
#define TWOSTAGEITER_HH

/*!  
 * \file twostageiter.hh
 * \author  Bogdan Kreczmer
 * \date    2004.04.09
 *
 *  Plik zawiera definicj� szablonu klas
 *  TwoStageIter (iterator dwustopniowy)
 *  umo�liwiaj�cej przechodzedzenie po kolejnych elementach
 *  korzystaj�c z iteratora po�redniego.
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
 *  \param InitType - typ obiektu dla kt�rego inicjalizowany jest
 *                    iterator pomocniczy,
 *  \param AuxIterType - typ iteratora pomocniczego,
 *  \param ID - indentyfikator umo�liwiaj�cy rozro�nienie nazw typ�w, w
 *            przypadku gdy pierwszy parametr dla dw�ch typ�w jest identyczny.
 */
template <class IteratorType, class ElemType, 
          class InitType, class AuxIterType, int ID = 0>
class TwoStageIter: public BaseIterator<IteratorType,ElemType> {
 protected:
  /*!
   * Pole pomocniczego iteratora.
   */
   AuxIterType _AuxIter;
   /*!
    *  Metoda zwraca warto�� okre�laj�c� czy dla danego ustawienia
    *  iteratora pomocniczego wskazywany przez niego obiekt spe�nia 
    *  �adane kryterium. Pozwala to filtrowa� zbi�r iterowanych obiekt�w
    *  i udost�pnia� tylko te, kt�re spe�niaj� zadane kryterium.
    *  Metoda musi by� zaimplementowana w klasie pochodnej.
    */
   virtual bool IsOK_AuxIter() const = 0;
 public:
   /*============================================
    * Inicjalizuje iterator dla danego obiektu.
    */
   TwoStageIter(InitType &);

   void Init();

   /*!
    * Jedynie po to, aby by� destruktor wirtualny.
    */
   virtual ~TwoStageIter() {}

   /*!
    *  Operator prefiksowy. 
    *  Realizuje operacj� cofni�cia si� do poprzedniego elementu
    *  spe�niaj�cego zadane kryterium.
    */
   IteratorType &operator -- () 
    { 
      InitType *pElem = _AuxIter.Get();
      while (--_AuxIter) {
       if (IsOK_AuxIter()) { SetStatus(true);  return *(IteratorType*)this; }
      }
      _AuxIter.Set(pElem);
      SetStatus(false);
      return *(IteratorType*)this; 
    }

   /*!
    *  Operator prefiksowy. 
    *  Realizuje operacj� przej�cia do nast�pnego elementu spe�niaj�cego
    *  zadane kryterium.
    */
   IteratorType &operator ++ () 
    { 
      InitType *pElem = _AuxIter.Get();
      while (++_AuxIter) {
       if (IsOK_AuxIter()) { SetStatus(true);  return *(IteratorType*)this; }
      }
      _AuxIter.Set(pElem);
      SetStatus(false);
      return *(IteratorType*)this; 
    }

   /*!
    *  Przywraca pocz�tkowy stan operatora.
    */  
   void Reset() { _AuxIter.Reset(); SetStatus(_AuxIter.GetStatus()); }
};




/*!
 *  Inicjalizuje iterator dla danego obiektu.
 *  \param  Obj - referencja do obiektu, dla kt�rego ma zosta� zaincjalizowany
 *                iterator pomocniczy.
 */
template <class IteratorType, class ElemType, 
          class InitType, class AuxIterType, int ID>
inline
TwoStageIter<IteratorType,ElemType,InitType,AuxIterType,ID>::TwoStageIter(
							      InitType &Obj):
  _AuxIter(Obj) {}



/*!
 *  Inicjalizuje iterator dla danego obiektu ustawiaj�c go (o ile jest to
 *  mo�liwe) na pierwszy element spe�niaj�cy zadane kryterium.
 *  Metoda ta powinna zosta� wywo�ana w klasie pochodnej od razu po utworzeniu
 *  obiektu z klasy bazowej definiowanej przez niniejszy szablon.
 *  \post Je�eli w wzbiorze iterowanych element�w mo�e zosta� znaleziony
 *         taki element, dla kt�rego spe�nione jest kryterium selekcji
 *      dost�pne poprzez metod�
 *      \link TwoStageIter::IsOK_AuxIter IsOK_AuxIter\endlink,
 *     to iterator zostaje ustawiony na to pole, a statusowi operacji
 *   przypisana jest warto�� \p true.
 *   W przypadku przeciwnym iterator ustawiany jest na pierwszy dost�pny
 *   element, a statusowi operacji przypisana zostaje warto�� \p false.
 */
template <class IteratorType, class ElemType, 
          class InitType, class AuxIterType, int ID>
inline
void TwoStageIter<IteratorType,ElemType,InitType,AuxIterType,ID>::Init()
{
  InitType *pElem = _AuxIter.Get();
  while (_AuxIter) {
    if (IsOK_AuxIter()) { SetStatus(true);  _AuxIter.SetInit();  return; }
    ++_AuxIter;
  }
  _AuxIter.Set(pElem);
  _AuxIter.SetInit();
  SetStatus(false);
}
#endif
