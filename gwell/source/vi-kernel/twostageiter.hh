#ifndef TWOSTAGEITER_HH
#define TWOSTAGEITER_HH

/*!  
 * \file twostageiter.hh
 * \author  Bogdan Kreczmer
 * \date    2004.04.09
 *
 *  Plik zawiera definicjê szablonu klas
 *  TwoStageIter (iterator dwustopniowy)
 *  umo¿liwiaj±cej przechodzedzenie po kolejnych elementach
 *  korzystaj±c z iteratora po¶redniego.
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
 *  \param InitType - typ obiektu dla którego inicjalizowany jest
 *                    iterator pomocniczy,
 *  \param AuxIterType - typ iteratora pomocniczego,
 *  \param ID - indentyfikator umo¿liwiaj±cy rozro¿nienie nazw typów, w
 *            przypadku gdy pierwszy parametr dla dwóch typów jest identyczny.
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
    *  Metoda zwraca warto¶æ okre¶laj±c± czy dla danego ustawienia
    *  iteratora pomocniczego wskazywany przez niego obiekt spe³nia 
    *  ¿adane kryterium. Pozwala to filtrowaæ zbiór iterowanych obiektów
    *  i udostêpniaæ tylko te, które spe³niaj± zadane kryterium.
    *  Metoda musi byæ zaimplementowana w klasie pochodnej.
    */
   virtual bool IsOK_AuxIter() const = 0;
 public:
   /*============================================
    * Inicjalizuje iterator dla danego obiektu.
    */
   TwoStageIter(InitType &);

   void Init();

   /*!
    * Jedynie po to, aby by³ destruktor wirtualny.
    */
   virtual ~TwoStageIter() {}

   /*!
    *  Operator prefiksowy. 
    *  Realizuje operacjê cofniêcia siê do poprzedniego elementu
    *  spe³niaj±cego zadane kryterium.
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
    *  Realizuje operacjê przej¶cia do nastêpnego elementu spe³niaj±cego
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
    *  Przywraca pocz±tkowy stan operatora.
    */  
   void Reset() { _AuxIter.Reset(); SetStatus(_AuxIter.GetStatus()); }
};




/*!
 *  Inicjalizuje iterator dla danego obiektu.
 *  \param  Obj - referencja do obiektu, dla którego ma zostaæ zaincjalizowany
 *                iterator pomocniczy.
 */
template <class IteratorType, class ElemType, 
          class InitType, class AuxIterType, int ID>
inline
TwoStageIter<IteratorType,ElemType,InitType,AuxIterType,ID>::TwoStageIter(
							      InitType &Obj):
  _AuxIter(Obj) {}



/*!
 *  Inicjalizuje iterator dla danego obiektu ustawiaj±c go (o ile jest to
 *  mo¿liwe) na pierwszy element spe³niaj±cy zadane kryterium.
 *  Metoda ta powinna zostaæ wywo³ana w klasie pochodnej od razu po utworzeniu
 *  obiektu z klasy bazowej definiowanej przez niniejszy szablon.
 *  \post Je¿eli w wzbiorze iterowanych elementów mo¿e zostaæ znaleziony
 *         taki element, dla którego spe³nione jest kryterium selekcji
 *      dostêpne poprzez metodê
 *      \link TwoStageIter::IsOK_AuxIter IsOK_AuxIter\endlink,
 *     to iterator zostaje ustawiony na to pole, a statusowi operacji
 *   przypisana jest warto¶æ \p true.
 *   W przypadku przeciwnym iterator ustawiany jest na pierwszy dostêpny
 *   element, a statusowi operacji przypisana zostaje warto¶æ \p false.
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
