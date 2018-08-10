#ifndef VIPATTPOLYHLIB_HH
#define VIPATTPOLYHLIB_HH

/*!
 * \file  vipattepolyhlib.hh
 * \author Bogdan Kreczmer
 * \date   2004.03
 *
 *  Plik zawiera definicjê klasy ViPattePolyhLib stanowi±c± bibliotekê obiektów
 *  wzorcowych.
 */



#ifdef __GNUG__
#pragma interface
#pragma implementation
#endif

class ViPattePolyh;


#include "listque.hh"
#include "extstring.hh"
#include "vipattepolyh.hh"



class ViPattePolyhLib;


/*!
 *  Klasa pomocnicza dla listy obiektów wzorcowych.
 */
class ViPattePolyhList: public List<ViPattePolyh,0> {
  /*!
   *  Zawiera nazwê listy. Aktualnie przewidywane nazwy: Norm, Spec;
   */
  ExtString _ListName;
   /*!
    * Referencja do obiektu, którego polem jest ten obiekt.
    */
  ViPattePolyhLib &_Owner;
 public:
   /*!
    * Inicjalizuje obiekt.
    * \param  Or - referencja  do obiektu, którego polem jest tworzony
    *              obiekt.
    * \param  Name - nazwa listy.
    */
   ViPattePolyhList(ViPattePolyhLib &Or, const char* Name): 
         _ListName(Name), _Owner(Or) {}
   /*!
    * Udostêpnia referencjê do obiektu, którego polem jest ten obiekt.
    */
   ViPattePolyhLib const &GetOwner() const { return _Owner; }
  /*!
   * Udostêpnia nazwê listy.
   */
   const char *GetListName() const { return _ListName; }
  /*!
   * Udostêpnia nazwê biblioteki, w sk³ad której wchodzi dana lista.
   */
   const ExtString &GetLibName() const;



};


/*!
 *  Obiek klasy ViPattePolyhLib zarz±dza zbiorem bry³ elementarnych
 *  (obiekty klasy ViPattePolyh).
 */
class ViPattePolyhLib: public ListItem<ViPattePolyhLib,0>  {

    /*!
     * Nazwa biblioteki obiektów wzorcowych. Wystepuje ona wewn±trz pliku
     * zawieraj±cego opis ca³ej biblioteki.
     */
    ExtString  _LibName;

  public:

  /*!
   *  Typ pomocniczy zdefiniowany dla umo¿liwienia odwo³ywania
   *  siê do typu macierzystego poprzez skrócon± nazwê.
   *  Obiekt tej klasy umo¿liwia iteracjê bry³ wzorcowych 
   *  (obiekty klasy ViPattePolyh)
   *  dla danej biblioteki. Obiekty modeluj±ce bry³y wzorcowe
   *  udostêpniane s± jako obiekty sta³e.
   *
   *  Przyklad wykorzystania:
   *  \code
   *     . . .
   *   // Wy¶wietla nazwy wszystkich bry³ normalnej  dla biblioteki.
   *  for (ViPattePolyhLib::ConPatteIter Iter = Scene.ConBegin_NormPolyh();
   *       Iter; 
   *       Iter++) {
   *    cout << "Bryla0: " << Iter->Name() << endl;
   *  }
   *  \endcode
   */
  typedef ViPattePolyhList::ConstIterator  ConPatteIter;

  /*!
   *  Typ pomocniczy zdefiniowany dla umo¿liwienia odwo³ywania
   *  siê do typu macierzystego poprzez skrócon± nazwê.
   *  Obiekt tej klasy umo¿liwia iteracjê bry³ wzorcowych 
   *  (obiekty klasy ViPattePolyh)
   *  dla danej biblioteki. Obiekty modeluj±ce bry³y wzorcowe
   *  udostêpniane s± jako obiekty modyfikowalne.
   *
   *  Przyklad wykorzystania:
   *  \code
   *     . . .
   *   // Wy¶wietla nazwy wszystkich bry³ normalnej  dla biblioteki.
   *  for (ViPattePolyhLib::VarPatteIter Iter = Scene.VarBegin_NormPolyh();
   *       Iter; 
   *       Iter++) {
   *    cout << "Bryla0: " << Iter->Name() << endl;
   *  }
   *  \endcode
   */
  typedef ViPattePolyhList::VariaIterator  VarPatteIter;


 
    /*!
     * Zbiór bry³ zwyk³ych wykorzystywanych do modelowania obiektów.
     */
   ViPattePolyhList _NormPattePolyh;
    /*!
     * Zbiór bry³ specjalnych niewykorzystywanych przy modelowaniu obiektów,
     * np. rysunek uk³adu wspó³rzêdnych, pod³oga itp.
     */
   ViPattePolyhList _SpecPattePolyh;

    /*!
     * Inicjalizuje kolejki bry³ zwyk³ych (pole 
     *  \link ViPattePolyhLib::_NormPattePolyh _NormPattePolyh\endlink) oraz
     * bry³ specjalnych (pole  
     *  \link ViPattePolyhLib::_SpecPattePolyh _SpecPattePolyh\endlink) jako
     * kolejki puste.
     */
  ViPattePolyhLib();
   ~ViPattePolyhLib();

    /*!
     *  Udostêpnia nazwê biblioteki elementów wzorcowych.
     */
  const ExtString &GetLibName() const { return _LibName; }

    /*!
     *  Udostêpnia nazwê biblioteki elementów wzorcowych.
     */
  const ExtString &GetLibName_str() const { return _LibName; }

    /*!
     *  Nadaje now± nazwê bibliotece obiektów wzorcowych.
     */
  void SetLibName(const char *Name) { _LibName = Name; }


    /*!
     * Dodaje do kolejki bry³ zwyk³ych now± bry³ê wzorcow±.
     * \param pPolyh - wsk¼nik na obiekty modeluj±cy bry³ê 
     *           wzorcow±.
     * \pre Obiekt wskazywany przez parametr \e pPolyh
     *      musi byæ wcze¶niej utworzony w sposób dynamiczny.
     * \retval pPolyh - warto¶æ przekazana jako parametr, która
     *         jest teraz interpretowana jako wska¼nikiem na dodany obiekt.
     * \retval NULL - je¶li dodanie do kolejki nie powiod³o siê
     *              (brak wymaganej ilo¶ci pamiêci).
     */
  ViPattePolyh *AddNormPattePolyh(ViPattePolyh *pPolyh=0L);

    /*!
     * Dodaje do kolejki bry³ spacjalnych now± bry³ê wzorcow±.
     * \param pPolyh - wsk¼nik na obiekty modeluj±cy bry³ê 
     *           wzorcow±.
     * \pre Obiekt wskazywany przez parametr \e pPolyh
     *      musi byæ wcze¶niej utworzony w sposób dynamiczny.
     * \retval pPolyh - warto¶æ przekazana jako parametr, która
     *         jest teraz interpretowana jako wska¼nikiem na dodany obiekt.
     * \retval NULL - je¶li dodanie do kolejki nie powiod³o siê
     *              (brak wymaganej ilo¶ci pamiêci).
     */
  ViPattePolyh *AddSpecPattePolyh(ViPattePolyh *pPolyh=0L);

   /*!
    * Wyszukuje w kolejce zwyk³ych bry³ wzorcowych obiekt, który jest wzorcem
    * bry³y o podanej nazwie.
    * \param  Name - nazwa bry³y wzorcowej.
    * \return
    *  wska¼nik na znaleziony obiekt, \e NULL - w przypadku przeciwnym.
    */
  const ViPattePolyh *FindNormPattePolyh(const char *Name) const;

   /*!
    * Wyszukuje w kolejce specjalnych bry³ wzorcowych obiekt, który jest 
    * wzorcem bry³y o podanej nazwie.
    * \param  Name - nazwa bry³y wzorcowej.
    * \return
    *  wska¼nik na znaleziony obiekt, \e NULL - w przypadku przeciwnym.
    */
  const ViPattePolyh *FindSpecPattePolyh(const char *Name) const;



  //----------------- Iteratory ----------------------------------------------

   /*!
    *  Udostêpnia iterator zwyk³ych obiektów wzorcowych. Udostêpniane
    *  obiekty s± sta³e.
    *  \warning Nie zaleca siê u¿ywanie niniejszych iteratorów. S± one
    *           przeznaczone do usuniêcia. Zamiast nich zalecena jest
    *           u¿ywanie iteratorów 
    *  \link ViPattePolyhLib::ConBegin_NormPatte
    *        ViPattePolyhLib::ConBegin_NormPatte\endlink.
    */
  ConPatteIter Begin_NormPatte() const { return _NormPattePolyh.ConBegin(); }


   /*!
    *  Udostêpnia iterator zwyk³ych obiektów wzorcowych. Udostêpniane
    *  obiekty s± modyfikowalne.
    *  \warning Nie zaleca siê u¿ywanie niniejszych iteratorów. S± one
    *           przeznaczone do usuniêcia. Zamiast nich zalecena jest
    *           u¿ywanie iteratorów 
    *  \link ViPattePolyhLib::VarBegin_NormPatte
    *        ViPattePolyhLib::VarBegin_NormPatte\endlink.
    */
  VarPatteIter Begin_NormPatte() { return _NormPattePolyh.Begin(); }


   /*!
    *  Udostêpnia iterator zwyk³ych obiektów wzorcowych
    *  (obiekty klasy ViPattePolyh). Udostêpniane
    *  obiekty s± sta³e.
    */
  ConPatteIter ConBegin_NormPatte() const {return _NormPattePolyh.ConBegin();}


   /*!
    *  Udostêpnia iterator zwyk³ych obiektów wzorcowych
    *  (obiekty klasy ViPattePolyh). Udostêpniane
    *  obiekty s± modyfikowalne.
    */
  VarPatteIter VarBegin_NormPatte() {return _NormPattePolyh.Begin();}


   /*!
    *  Udostêpnia iterator specjalnych obiektów wzorcowych. Udostêpniane
    *  obiekty s± modyfikowalne.
    *  \warning Nie zaleca siê u¿ywanie niniejszych iteratorów. S± one
    *           przeznaczone do usuniêcia. Zamiast nich zalecena jest
    *           u¿ywanie iteratorów 
    *  \link ViPattePolyhLib::VarBegin_SpecPatte
    *        ViPattePolyhLib::VarBegin_SpcePatte\endlink.
    */
  VarPatteIter Begin_SpecPatte() { return _SpecPattePolyh.Begin(); }

   /*!
    *  Udostêpnia iterator specjalnych obiektów wzorcowych. Udostêpniane
    *  obiekty s± sta³e.
    *  \warning Nie zaleca siê u¿ywanie niniejszych iteratorów. S± one
    *           przeznaczone do usuniêcia. Zamiast nich zalecena jest
    *           u¿ywanie iteratorów 
    *  \link ViPattePolyhLib::ConBegin_SpecPatte
    *        ViPattePolyhLib::ConBegin_SpcePatte\endlink.
    */
  ConPatteIter Begin_SpecPatte() const { return _SpecPattePolyh.ConBegin(); }

   /*!
    *  Udostêpnia iterator specjalnych obiektów wzorcowych
    *  (obiekty klasy ViPattePolyh).  Udostêpniane
    *  obiekty s± sta³e.
    */
  ConPatteIter ConBegin_SpecPatte() const {return _SpecPattePolyh.ConBegin();}

   /*!
    *  Udostêpnia iterator specjalnych obiektów wzorcowych
    *  (obiekty klasy ViPattePolyh).  Udostêpniane
    *  obiekty s± modyfikowalne.
    */
  VarPatteIter VarBegin_SpecPatte() {return _SpecPattePolyh.Begin();}

};


inline
const ExtString &ViPattePolyhList::GetLibName() const
{
  return GetOwner().GetLibName();
}



#endif
