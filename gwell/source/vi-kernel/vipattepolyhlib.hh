#ifndef VIPATTPOLYHLIB_HH
#define VIPATTPOLYHLIB_HH

/*!
 * \file  vipattepolyhlib.hh
 * \author Bogdan Kreczmer
 * \date   2004.03
 *
 *  Plik zawiera definicj� klasy ViPattePolyhLib stanowi�c� bibliotek� obiekt�w
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
 *  Klasa pomocnicza dla listy obiekt�w wzorcowych.
 */
class ViPattePolyhList: public List<ViPattePolyh,0> {
  /*!
   *  Zawiera nazw� listy. Aktualnie przewidywane nazwy: Norm, Spec;
   */
  ExtString _ListName;
   /*!
    * Referencja do obiektu, kt�rego polem jest ten obiekt.
    */
  ViPattePolyhLib &_Owner;
 public:
   /*!
    * Inicjalizuje obiekt.
    * \param  Or - referencja  do obiektu, kt�rego polem jest tworzony
    *              obiekt.
    * \param  Name - nazwa listy.
    */
   ViPattePolyhList(ViPattePolyhLib &Or, const char* Name): 
         _ListName(Name), _Owner(Or) {}
   /*!
    * Udost�pnia referencj� do obiektu, kt�rego polem jest ten obiekt.
    */
   ViPattePolyhLib const &GetOwner() const { return _Owner; }
  /*!
   * Udost�pnia nazw� listy.
   */
   const char *GetListName() const { return _ListName; }
  /*!
   * Udost�pnia nazw� biblioteki, w sk�ad kt�rej wchodzi dana lista.
   */
   const ExtString &GetLibName() const;



};


/*!
 *  Obiek klasy ViPattePolyhLib zarz�dza zbiorem bry� elementarnych
 *  (obiekty klasy ViPattePolyh).
 */
class ViPattePolyhLib: public ListItem<ViPattePolyhLib,0>  {

    /*!
     * Nazwa biblioteki obiekt�w wzorcowych. Wystepuje ona wewn�trz pliku
     * zawieraj�cego opis ca�ej biblioteki.
     */
    ExtString  _LibName;

  public:

  /*!
   *  Typ pomocniczy zdefiniowany dla umo�liwienia odwo�ywania
   *  si� do typu macierzystego poprzez skr�con� nazw�.
   *  Obiekt tej klasy umo�liwia iteracj� bry� wzorcowych 
   *  (obiekty klasy ViPattePolyh)
   *  dla danej biblioteki. Obiekty modeluj�ce bry�y wzorcowe
   *  udost�pniane s� jako obiekty sta�e.
   *
   *  Przyklad wykorzystania:
   *  \code
   *     . . .
   *   // Wy�wietla nazwy wszystkich bry� normalnej  dla biblioteki.
   *  for (ViPattePolyhLib::ConPatteIter Iter = Scene.ConBegin_NormPolyh();
   *       Iter; 
   *       Iter++) {
   *    cout << "Bryla0: " << Iter->Name() << endl;
   *  }
   *  \endcode
   */
  typedef ViPattePolyhList::ConstIterator  ConPatteIter;

  /*!
   *  Typ pomocniczy zdefiniowany dla umo�liwienia odwo�ywania
   *  si� do typu macierzystego poprzez skr�con� nazw�.
   *  Obiekt tej klasy umo�liwia iteracj� bry� wzorcowych 
   *  (obiekty klasy ViPattePolyh)
   *  dla danej biblioteki. Obiekty modeluj�ce bry�y wzorcowe
   *  udost�pniane s� jako obiekty modyfikowalne.
   *
   *  Przyklad wykorzystania:
   *  \code
   *     . . .
   *   // Wy�wietla nazwy wszystkich bry� normalnej  dla biblioteki.
   *  for (ViPattePolyhLib::VarPatteIter Iter = Scene.VarBegin_NormPolyh();
   *       Iter; 
   *       Iter++) {
   *    cout << "Bryla0: " << Iter->Name() << endl;
   *  }
   *  \endcode
   */
  typedef ViPattePolyhList::VariaIterator  VarPatteIter;


 
    /*!
     * Zbi�r bry� zwyk�ych wykorzystywanych do modelowania obiekt�w.
     */
   ViPattePolyhList _NormPattePolyh;
    /*!
     * Zbi�r bry� specjalnych niewykorzystywanych przy modelowaniu obiekt�w,
     * np. rysunek uk�adu wsp�rz�dnych, pod�oga itp.
     */
   ViPattePolyhList _SpecPattePolyh;

    /*!
     * Inicjalizuje kolejki bry� zwyk�ych (pole 
     *  \link ViPattePolyhLib::_NormPattePolyh _NormPattePolyh\endlink) oraz
     * bry� specjalnych (pole  
     *  \link ViPattePolyhLib::_SpecPattePolyh _SpecPattePolyh\endlink) jako
     * kolejki puste.
     */
  ViPattePolyhLib();
   ~ViPattePolyhLib();

    /*!
     *  Udost�pnia nazw� biblioteki element�w wzorcowych.
     */
  const ExtString &GetLibName() const { return _LibName; }

    /*!
     *  Udost�pnia nazw� biblioteki element�w wzorcowych.
     */
  const ExtString &GetLibName_str() const { return _LibName; }

    /*!
     *  Nadaje now� nazw� bibliotece obiekt�w wzorcowych.
     */
  void SetLibName(const char *Name) { _LibName = Name; }


    /*!
     * Dodaje do kolejki bry� zwyk�ych now� bry�� wzorcow�.
     * \param pPolyh - wsk�nik na obiekty modeluj�cy bry�� 
     *           wzorcow�.
     * \pre Obiekt wskazywany przez parametr \e pPolyh
     *      musi by� wcze�niej utworzony w spos�b dynamiczny.
     * \retval pPolyh - warto�� przekazana jako parametr, kt�ra
     *         jest teraz interpretowana jako wska�nikiem na dodany obiekt.
     * \retval NULL - je�li dodanie do kolejki nie powiod�o si�
     *              (brak wymaganej ilo�ci pami�ci).
     */
  ViPattePolyh *AddNormPattePolyh(ViPattePolyh *pPolyh=0L);

    /*!
     * Dodaje do kolejki bry� spacjalnych now� bry�� wzorcow�.
     * \param pPolyh - wsk�nik na obiekty modeluj�cy bry�� 
     *           wzorcow�.
     * \pre Obiekt wskazywany przez parametr \e pPolyh
     *      musi by� wcze�niej utworzony w spos�b dynamiczny.
     * \retval pPolyh - warto�� przekazana jako parametr, kt�ra
     *         jest teraz interpretowana jako wska�nikiem na dodany obiekt.
     * \retval NULL - je�li dodanie do kolejki nie powiod�o si�
     *              (brak wymaganej ilo�ci pami�ci).
     */
  ViPattePolyh *AddSpecPattePolyh(ViPattePolyh *pPolyh=0L);

   /*!
    * Wyszukuje w kolejce zwyk�ych bry� wzorcowych obiekt, kt�ry jest wzorcem
    * bry�y o podanej nazwie.
    * \param  Name - nazwa bry�y wzorcowej.
    * \return
    *  wska�nik na znaleziony obiekt, \e NULL - w przypadku przeciwnym.
    */
  const ViPattePolyh *FindNormPattePolyh(const char *Name) const;

   /*!
    * Wyszukuje w kolejce specjalnych bry� wzorcowych obiekt, kt�ry jest 
    * wzorcem bry�y o podanej nazwie.
    * \param  Name - nazwa bry�y wzorcowej.
    * \return
    *  wska�nik na znaleziony obiekt, \e NULL - w przypadku przeciwnym.
    */
  const ViPattePolyh *FindSpecPattePolyh(const char *Name) const;



  //----------------- Iteratory ----------------------------------------------

   /*!
    *  Udost�pnia iterator zwyk�ych obiekt�w wzorcowych. Udost�pniane
    *  obiekty s� sta�e.
    *  \warning Nie zaleca si� u�ywanie niniejszych iterator�w. S� one
    *           przeznaczone do usuni�cia. Zamiast nich zalecena jest
    *           u�ywanie iterator�w 
    *  \link ViPattePolyhLib::ConBegin_NormPatte
    *        ViPattePolyhLib::ConBegin_NormPatte\endlink.
    */
  ConPatteIter Begin_NormPatte() const { return _NormPattePolyh.ConBegin(); }


   /*!
    *  Udost�pnia iterator zwyk�ych obiekt�w wzorcowych. Udost�pniane
    *  obiekty s� modyfikowalne.
    *  \warning Nie zaleca si� u�ywanie niniejszych iterator�w. S� one
    *           przeznaczone do usuni�cia. Zamiast nich zalecena jest
    *           u�ywanie iterator�w 
    *  \link ViPattePolyhLib::VarBegin_NormPatte
    *        ViPattePolyhLib::VarBegin_NormPatte\endlink.
    */
  VarPatteIter Begin_NormPatte() { return _NormPattePolyh.Begin(); }


   /*!
    *  Udost�pnia iterator zwyk�ych obiekt�w wzorcowych
    *  (obiekty klasy ViPattePolyh). Udost�pniane
    *  obiekty s� sta�e.
    */
  ConPatteIter ConBegin_NormPatte() const {return _NormPattePolyh.ConBegin();}


   /*!
    *  Udost�pnia iterator zwyk�ych obiekt�w wzorcowych
    *  (obiekty klasy ViPattePolyh). Udost�pniane
    *  obiekty s� modyfikowalne.
    */
  VarPatteIter VarBegin_NormPatte() {return _NormPattePolyh.Begin();}


   /*!
    *  Udost�pnia iterator specjalnych obiekt�w wzorcowych. Udost�pniane
    *  obiekty s� modyfikowalne.
    *  \warning Nie zaleca si� u�ywanie niniejszych iterator�w. S� one
    *           przeznaczone do usuni�cia. Zamiast nich zalecena jest
    *           u�ywanie iterator�w 
    *  \link ViPattePolyhLib::VarBegin_SpecPatte
    *        ViPattePolyhLib::VarBegin_SpcePatte\endlink.
    */
  VarPatteIter Begin_SpecPatte() { return _SpecPattePolyh.Begin(); }

   /*!
    *  Udost�pnia iterator specjalnych obiekt�w wzorcowych. Udost�pniane
    *  obiekty s� sta�e.
    *  \warning Nie zaleca si� u�ywanie niniejszych iterator�w. S� one
    *           przeznaczone do usuni�cia. Zamiast nich zalecena jest
    *           u�ywanie iterator�w 
    *  \link ViPattePolyhLib::ConBegin_SpecPatte
    *        ViPattePolyhLib::ConBegin_SpcePatte\endlink.
    */
  ConPatteIter Begin_SpecPatte() const { return _SpecPattePolyh.ConBegin(); }

   /*!
    *  Udost�pnia iterator specjalnych obiekt�w wzorcowych
    *  (obiekty klasy ViPattePolyh).  Udost�pniane
    *  obiekty s� sta�e.
    */
  ConPatteIter ConBegin_SpecPatte() const {return _SpecPattePolyh.ConBegin();}

   /*!
    *  Udost�pnia iterator specjalnych obiekt�w wzorcowych
    *  (obiekty klasy ViPattePolyh).  Udost�pniane
    *  obiekty s� modyfikowalne.
    */
  VarPatteIter VarBegin_SpecPatte() {return _SpecPattePolyh.Begin();}

};


inline
const ExtString &ViPattePolyhList::GetLibName() const
{
  return GetOwner().GetLibName();
}



#endif
