#ifndef LISTQUE_HH
#define LISTQUE_HH

/*!
 * \file  listque.hh
 * Plik zawiera definicje zestawu wzorc�w listy dwukierunkowej.
 * W sk�ad tego zestawu wchodzi wzorzec dla pojedynczego elementu 
 * listy (\link ListItem ListItem\endlink), wzorzec zarz�dcy
 * listy (\link List List\endlink), wzorzec iteratora udost�pniaj�cego
 * kolejne elementy listy z mo�liwo�ci� przeprowadzenia ich modyfikacji
 * (\link List::VariaIterator List::VariaIterator\endlink), wzrozec 
 * iteroratora
 * udost�pniaj�cego kolejne elementy listy z ochron� przed wprowadzeniem
 * do nich jakichkolwiek zmian 
 * (\link List::ConstIterator List::ConstIterator\endlink).
 * \author Bogdan Kreczmer
 * \date   1995
 * \version 1.0.7
 */

/*! 
 * Identyfikator klasy List (patrz opis metody 
 *  \link ListItem::InherTypeID InherTypeID\endlink).
 */
#define ID_ITEMLIST    -2
/*! 
 * Identyfikator klasy List (patrz opis metody 
 *  \link List::InherTypeID InherTypeID\endlink).
 */
#define ID_LIST        -1


#ifdef __GNUG__
#pragma interface
#pragma implementation
#endif




#define  GET_FIRST(x)         ((x=First()) == 0L)
#define  GET_FIRST_RETURN(x)  if (GET_FIRST(x))  return;
#define  FOR_LISTS(xFld,x)    for (x=xFld.First(); x != 0L; x=x->Next())
/*!
 *  Makro to s�u�y do u�atwienia pisania p�tli bezpo�redniego przeg��dania
 *  listy.
 *
 * Przyk�ad wykorzystania:
 * \code
 *  ListaLiczb<int,0> ListaLiczb;
 *  
 *  ListItem<int,0> *Elem;
 *  FOR_LIST(Elem) {
 *    ...                 // Tutaj cos robimy z poszczeg�lnymi elementami
 *    Elem->JakasMetoda() // listy, np. wywo�ujemy jak�� metod�.
 *  }
 * \endcode
 */
#define  FOR_LIST(x)          for (x=First(); x != 0L; x=x->Next())









template <class ItemType, int ID, class ListType>
class List;



/*!
 *  Wzorzec elementu listy dwukierunkowej z zarz�dc�. Podstawow�
 *  w�asno�ci� tego elementu jest samoczynne usuni�cie si� z listy
 *  w momencie jego destrukcji.
 *  \param  ItemInher - nazwa klasy dziedzicz�cej dany wzorzec ListItem<>,
 *  \param  ID       - parametr indetyfikuj�cy typ,
 *  \param  ListType - nazwa klasy dziedzicz�cej wzorzec List<>.
 */
template <class ItemType, int ID = 0, class ListType = void>
class ListItem {
  /*!
   * Klasa elementu listy jest zaprzyja�niona z klas� zarz�dcy ze 
   * wzgl�du na konieczno�� wykonywania operacji na jego polach prywatynch
   * w przypadku destrukcji lub wy��czania z listy danego elementu.
   */
  friend class List <ItemType,ID,ListType>;
 
  /*!
   *  Operator przypisania jest uczyniony operatorem prywatnym ze wzgl�du
   *  na to, aby uniemo�liwi� realizacj� tej operacji.
   *  Wykonanie jej dla elementu nale��cego ju� do jakie� listy
   *  oznacza�oby utrat� sp�jno�ci struktury danych.
   */
  ListItem<ItemType,ID,ListType> &operator = (const ListItem<ItemType,ID,ListType>&)
                                                                   { return *this; }

  /*!
   *  Operator kopiuj�cy jest uczyniony operatorem prywatnym ze wzgl�du
   *  na to, aby uniemo�liwi� realizacj� tej operacji.
   *  Wykonanie jej dla elementu nale��cego ju� do jakie� listy
   *  oznacza�oby utrat� sp�jno�ci struktury danych.
   */
  ListItem(const ListItem<ItemType,ID,ListType>&) {}


 protected:

  /*!
   *  Pole zawiera wska�nik na nast�pny element w kolejce.
   */
  ItemType          *  _next;

  /*!
   *  Pole zawiera wska�nik na poprzedni element w kolejce.
   */
  ItemType          *  _prev;

  /*!
   *  Pole zawiera wska�nik na zarz�dc� listy, do kt�rej nale�y
   *  dany element.
   */
  List <ItemType,ID,ListType>*  _root;


       /*!
        * Inicjuje dany element jako pierwszy element listy.
        * W przypadku gdy dany element nale�y ju� do jakiej� listy, to najpierw
        * powi�zania z ni� zostaj� usuni�te.
        * Przy ustawianiu w nowej li�cie nie jest sprawdzane czy zarz�dca 
        * wskazuje na jaka� element listy.
        *
        * \param  pLst  - wska�nik na zarz�dc� nowej listy, w kt�rej dany 
	*                element ma by� pierwszym jej elementem.
	* \return wska�nik na samego siebie (\e this).
	*/
       ItemType* InitAsFirst(List <ItemType,ID,ListType> const *pLst);

      public:

         /*!
          *  Udost�pnia identyfikator klasy dziedzicz�cej klas� ListItem.
          *  \warning W klasach dziedzicz�cych ten szablon, reimplementacja 
          *           tej metody powinna zwraca� warto�� wi�ksz� od zera.
          *           Warto�ci niedodatnie s� zarezerowane.
          */
        virtual int InherTypeID() const { return ID_ITEMLIST; }

         /*!
	  *  Udost�pnia wska�nik do zarz�dcy listy, do kt�rej nale�y
	  *  ten element.
	  */
        List <ItemType,ID,ListType> * Root() { return _root; }


         /*!
	  *  Udost�pnia wska�nik do obiektu, kt�ry dziedziczy zarz�dc�
	  *  listy. Udost�pniony obiekt jest modyfikowalny.
	  */  
        ListType * RootInher() { return (ListType*)_root; }


         /*!
	  *  Udost�pnia wska�nik do obiektu, kt�ry dziedziczy zarz�dc�
	  *  listy. Udost�pniony obiekt jest sta�y.
	  */  
        const ListType * RootInher() const { return (const ListType *)_root; }

         /*!
	  *  Udost�pnia wska�nik do obiektu, kt�ry dziedziczy zarz�dc�
	  *  listy. Udost�pniony obiekt jest sta�y.
	  */  
        const ListType * ConRootInher() const {return (const ListType *)_root;}

         /*!
	  *  Udost�pnia wska�nik do nast�pnego elementu listy.
	  */
        ItemType* Next(){ return _next; }

         /*!
	  *  Udost�pnia wska�nik do poprzedniego elementu listy.
	  */
        ItemType* Prev(){ return _prev; }

         /*!
	  *  Udost�pnia wska�nik do zarz�dcy listy, do kt�rej nale�y
	  *  ten element.
	  */
        List <ItemType,ID,ListType> const * Root() const { return _root; }

         /*!
	  *  Udost�pnia wska�nik do nast�pnego elementu listy.
	  */
        ItemType const *Next() const { return _next; };

         /*!
	  *  Udost�pnia wska�nik do poprzedniego elementu listy.
	  */
        ItemType const *Prev() const { return _prev; };

        ItemType* PlaceBehind( ItemType *New);
        ItemType* PlaceAhead( ItemType  *New);

        void MoveBehind();
        void MoveAhead();


         /*!
	  *  Usuwa element z listy, do kt�rej dany element nale�y.
	  *  Nast�pnie do wszystkich p�l wska�nikowych wpisuje warto�� NULL.
          *  Oznacza to brak nast�pnika i poprzednika oraz brak powi�zania
	  *  z jakimkolwiek zarz�dc� listy.
	  */
        void  RemoveFromList();

         /*!
	  *  Wpisuje do wszystkich p�l wska�nikowych warto�ci NULL.
	  *  \warning Je�li obiekty jest w��czony do listy, to nale�y 
	  *    wywo�a� metod� 
	  *  \link ListItem::RemoveFromList RemoveFromList\endlink. 
	  *  Wpisze ona r�wnie� warto�ci NULL. Wcze�niej jednak zapewni
	  *  poprawne od��czenie elementu z listy.
	  */
        void  Clear() { _next = _prev = 0L;  _root = 0L; }

         /*!
	  *  Ustawia adres do zarz�dcy listy.
	  *  \param  Rt - wska�nik do nowego zarz�dcy listy.
	  *  \pre \e Rt musi zawiera� wska�nik do zarz�dcy listy,
	  *     do kt�rej nale�y element, dla kt�rego wywo�ywana jest
	  *     ta metoda lub zostanie do tej listy do��czony w operacji
	  *     bezpo�rednio lub po�rednio nast�puj�cej po niej.
	  *  \post
	  *     Zostaje zmieniony adres do zarz�dcy listy
	  *     (warto�� pola \link ListItem::_root _root\endlink).
	  *     Operacja ta mo�e prowadzi� do chwilowej niesp�jno�ci
	  *     struktur danych.
	  */
        void  SetRoot(List<ItemType,ID,ListType> *Rt) { _root = Rt; }

         /*!
	  *  Tworzy i inicjalizuje obiekt wska�nikami o warto�ci NULL. 
	  */
        ListItem();
         /*!
	  * W trakcie destrukcji element listy jest od��czany z listy.
	  * Sprawdza r�wnie� czy by� na pocz�tku lub na ko�cu listy i 
	  * w zale�no�ci od tego modyfikuje dosy�acze dla swojego zarz�dcy.
	  * Destruktor ten zapewnia zachowanie integralno�ci struktury listy.
	  */
        virtual ~ListItem();
};







template <class ItemType, int ID, class ListType>
inline
ListItem <ItemType,ID,ListType>::ListItem()
{
  ListItem<ItemType,ID,ListType>::_next=0L;
  ListItem<ItemType,ID,ListType>::_prev=0L;
  ListItem<ItemType,ID,ListType>::_root=0L; 
}




template <class ItemType, int ID, class ListType>
inline
ListItem <ItemType,ID,ListType>::~ListItem()
{
 if (_root) {
  if ((ListItem <ItemType,ID,ListType>*)
         (_root->List <ItemType,ID,ListType>::First()) == this)
                           _root->List <ItemType,ID,ListType>::SetFirst(_next);
  if ((ListItem <ItemType,ID,ListType>*)
         (_root->List <ItemType,ID,ListType>::Last())  == this)
                           _root->List <ItemType,ID,ListType>::SetLast(_prev);
 }
 if (_prev) _prev->ListItem<ItemType,ID,ListType>::_next = _next;
 if (_next) _next->ListItem<ItemType,ID,ListType>::_prev = _prev;
}




template <class ItemType, int ID, class ListType>
inline
ItemType* ListItem <ItemType,ID,ListType>::
                        InitAsFirst(List <ItemType,ID,ListType> const *pList)
{
  if (_root) RemoveFromList();
  _root = (List <ItemType,ID,ListType> *) pList;
  _next = _prev = 0L;
  return (ItemType*) this;
}




/*!
 * Wzorzec zarz�dcy listy dwukierunkowej. Zarz�dca daje dost�p do pierwszego
 * i ostatniego elementu listy. Przegl�danie listy jest mo�liwe z 
 * wykorzystaniem metod umo�liwiaj�cych przej�cie po kolei do poszczeg�lnych
 * element�w lub z wykorzystniem iteratora. Poni�ej przedstawione jest to
 * w dw�ch przyk�adach.
 *
 * \param  ItemType - nazwa klasy dziedzicz�cej wzorzec ListItem<>,
 * \param  ID       - parametr indetyfikuj�cy typ,
 * \param  ListType - nazwa klasy dziedzicz�cej wzorzec List<>.
 *
 * Bezpo�rednie przegl�danie listy:
 * \code
 *   List<int,0>  ListaLiczb;
 *   
 *   for (List<int,0> *Elem = ListaLiczb.First(); 
 *        Elem;
 *        Elem = Elem->Next()) {
 *     ...  // Tutaj co� robimy z poszczeg�lnymi elementami listy
 *     ...  // i mo�emy te elementy modyfikowa�.
 *    }
 *
 *   for (const List<int,0> *Elem = ListaLiczb.First(); 
 *        Elem;
 *        Elem = Elem->Next()) {
 *     ...  // Tutaj co� robimy z poszczeg�lnymi elementami listy.
 *     ...  // Teraz nie mo�emy je ju� modyfikowa�.
 *    }
 * \endcode
 *
 * Przegl�danie z wykorzystaniem iterator�w:
 * \code
 *   List<int,0>  ListaLiczb;
 *   
 *   for (List<int,0>::VariaIterator *Iter = ListaLiczb.Begin(); 
 *        Iter;
 *        ++Iter) {
 *     ...  // Tutaj co� robimy z poszczeg�lnymi elementami listy
 *     ...  // i mo�emy te elementy modyfikowa�.
 *
 *     Iter->JakasMetodaElementu();  // np. wywo�ujemy metod� dla tego 
 *                                   // elementu.
 *    }
 *
 *   for (List<int,0>::ConstIterator *Iter = ListaLiczb.Begin(); 
 *        Iter;
 *        ++Iter) {
 *     ...  // Tutaj co� robimy z poszczeg�lnymi elementami listy
 *     ...  // i mo�emy te elementy modyfikowa�.
 *
 *     Iter->JakasMetodaElementu();  // np. wywo�ujemy metod� dla tego 
 *                                   // elementu.
 *    }
 * \endcode
 */
template <class ItemType, int ID = 0, class ListType = void> 
class List {
 private:
  /*!
   *  Operator przypisania jest uczyniony operatorem prywatnym ze wzgl�du
   *  na to, aby uniemo�liwi� realizacj� tej operacji.
   *  Wykonanie jej dla elementu nale��cego ju� do jakie� listy
   *  oznacza�oby utrat� sp�jno�ci struktury danych.
   */
  List<ItemType,ID,ListType> &operator = (const List<ItemType,ID,ListType>&)
                                                                   { return *this; }

  /*!
   *  Operator kopiuj�cy jest uczyniony operatorem prywatnym ze wzgl�du
   *  na to, aby uniemo�liwi� realizacj� tej operacji.
   *  Wykonanie jej dla elementu nale��cego ju� do jakie� listy
   *  oznacza�oby utrat� sp�jno�ci struktury danych.
   */
  List(const ListItem<ItemType,ID,ListType>&) {}


 protected:
  ItemType *_first; /*!< Wska�nik na pierwszy element listy                  */
  ItemType *_last;  /*!< Wska�nik na ostatni element listy                   */

 public:

    /*!
     *  Udost�pnia identyfikator klasy dziedzicz�cej klase List.
     *  \warning W klasach dziedzicz�cych ten szablon, reimplementacja 
     *           tej metody powinna zwraca� warto�� wi�ksz� od zera.
     *           Warto�ci niedodatnie s� zarezerowane.
     */
   virtual int InherTypeID() const { return ID_LIST; }

   /*!
    * Uodst�pnia wska�nik na pierwszy element listy. Poprzez
    * udost�pniony wska�nik element ten mo�e by� modyfikowany.
    */
  ItemType *First() { return _first; };

   /*!
    * Uodst�pnia wska�nik na ostatni element listy. Poprzez
    * udost�pniony wska�nik element ten mo�e by� modyfikowany.
    */
  ItemType *Last()  { return _last;  };

   /*!
    * Uodst�pnia wska�nik na pierwszy element listy. 
    * Wskazywany element nie mo�e by� modyfikowany.
    */
  ItemType const *First() const { return _first; };

   /*!
    * Uodst�pnia wska�nik na ostatni element listy. 
    * Wskazywany element nie mo�e by� modyfikowany.
    */
  ItemType const *Last()  const { return _last;  };

  /*!
   *  Metoda pozwala stwierdzi� czy lista jest pusta.
   *  \retval true - je�li lista jest pusta,
   *  \retval false - w przypadku przeciwnym.
   */
  bool IsEmpty() const { return First() == 0L; }

  /*!
   *  Metoda pozwala stwierdzi� czy lista zawiera jaki� element.
   *  \retval true - je�li lista zawiera przynajmniej jeden element,
   *  \retval false - w przypadku przeciwnym.
   */
  bool IsAny() const { return First(); }

   /*!
    *  Udost�pnia wska�nik do obiektu, kt�ry dziedziczy zarz�dc�
    *  listy. Udost�pniony obiekt nie modyfikowalny.
    */  
  ListType * Inher() { return (ListType*)this; }

   /*!
    *  Udost�pnia wska�nik do obiektu, kt�ry dziedziczy zarz�dc�
    *  listy. Udost�pniony obiekt jest sta�y.
    */  
  const ListType * Inher() const { return (const ListType *)this; } 


 

   /*!
    *  Udost�pnia wska�nik do obiektu, kt�ry dziedziczy zarz�dc�
    *  listy. Udost�pniony obiekt jest sta�y.
    */  
  const ListType * ConInher() const { return (const ListType *)this; } 

   /*!
    * Ustawia dany obiekt jak pierwszy element listy.
    * \param Fst - wska�nik na obiekt, kt�ry ma by� pierwszym
    *              elementem listy.
    * \pre \e Fst._prev == NULL
    * \post 
    *   Jako pierwszy element listy zostaje ustawiony obiekt, dla kt�rego
    *   wska�nik dost�pny jest w \e Fst. U�ycie metody mo�e prowadzi�
    *   do chwilowej niespojno�ci struktury danych. Aby zapobiec 
    *   niesp�jno�ci nale�y po jej wywo�aniu lub
    *   przed w ka�dym elemencie listy zmieni� wska�nik na 
    *   jej zarz�dc�.
    */
  void SetFirst(ItemType *Fst) { _first = Fst; }

   /*!
    * Ustawia dany obiekt jak ostatni  element listy.
    * \param Lst - wska�nik na obiekt, kt�ry ma by� ostatnim
    *              elementem listy.
    * \pre \e Lst._prev == NULL
    * \post 
    *   Jako ostatni element listy zostaje ustawiony obiekt, dla kt�rego
    *   wska�nik dost�pny jest w \e Lst. U�ycie metody mo�e prowadzi�
    *   do chwilowej niespojno�ci struktury danych. Aby zapobiec 
    *   niesp�jno�ci nale�y po jej wywo�aniu lub
    *   przed w ka�dym elemencie listy zmieni� wska�nik na 
    *   jej zarz�dc�.
    */
  void SetLast(ItemType *Lst)  { _last = Lst; }

   /*!
    * Usuwa (poprzez destrukcj�) dany element z listy, o ile kolejka,
    * do kt�rej nale�y ten element jest zarz�dzana przez tego zarz�dc�.
    * \param Elem - wska�nik na element, kt�ry ma zosta� usuni�ty.
    * \retval true - gdy dany element nale�a� do listy tego zarz�dcy
    *             i zosta� z niej usuni�ty poprzez destrukcj�.
    * \retval false - gdy dany element nie nale�a� do listy tego zarz�dcy,
    *              �adna operacja na tym elemencie listy nie zosta�a
    *              wykonana. Warto�� ta jest r�wnie� zwracana w przypadku,
    *              gdy \e Elem == \p NULL.
    */
  bool  CancelItem(ItemType *Elem);

   /*!
    * Usuwa i niszczy wszystkie elementy listy.
    */
  void   CancelList();


  ItemType* AddToHead(ItemType *);
  ItemType* AddToTail(ItemType *);


   /*!
    *  Inicjalizuje dany element listy jako pierwszy i jedyny dla danego
    *  zarz�dcy.
    *  \param   pItem - wska�nik na element listy.
    *  \pre Zarz�dca nie mo�e mie� w�asnej koleki.
    *       Je�eli ma, to przed t� operacj� musi ona by� usuni�ta.
    *  \return warto�� wska�nika \p Item.
    *  \post Element wskazywany przez \p Item staje si� pierwszym i jedynym
    *        elementem listy danego zarz�dcy. W trakcie dzia�anie metody
    *        zmianie ulegaj� warto�ci p�l \link List::_first _first\endlink
    *        i \link List::_last _last\endlink.
    */
  ItemType* InitAsFirst(ItemType *pItem);

   /*!
    * Inicjalizuje list� wpisuj�c w pole wskazuj�ce na pierwszy element
    * (\link List::_first _first\endlink) i ostatni 
    * (\link List::_last _last\endlink) adres NULL.
    */
  void   InitList() { _first=_last=0L; };

   /*!
    * Zwraca ilo�� wszystkich element�w listy.
    */
  int    Number() const;

   /*!
    *  Udost�pnia element i-ty element z listy. Udost�pnione 
    *  elementy mog� by� modyfikowane.
    *  \param Idx - numer udost�pnianego elementu.
    *  \return wska�nik do elementu listy, kt�ry jest w niej
    *          na pozycji \e Idx. Je�eli element�w listy jest mniej
    *          ni� \e Idx, to zwracany jest adres \p NULL.
    */
  ItemType* At(unsigned int Idx);

   /*!
    *  Udost�pnia element i-ty element z listy. Udost�pnione 
    *  elementy nie mog� by� modyfikowane.
    *  \param Idx - numer udost�pnianego elementu.
    *  \return wska�nik do elementu listy, kt�ry jest w niej
    *          na pozycji \e Idx. Je�eli element�w listy jest mniej
    *          ni� \e Idx, to zwracany jest adres \p NULL.
    */
  ItemType const *At(unsigned int Idx) const;

   /*!
    * Przesuwa kolejk� od jednego zarz�dcy do drugiego zmieniaj�c w ten
    * spos�b zarz�dc� danej listy.
    * \param  Lst - zarz�dca listy, kt�rego kolejka ma by� "przesuni�ta"
    *               do zarz�dcy \e *this.
    * \post Je�eli zarz�dca \e *this
    *       mia� jak�� w�asn� kolejk�, to zostaje ona usuni�ta przez 
    *       destrukcj�. Na jej miejsce zostaje on powi�zany z kolejk�, 
    *       dla kt�rej
    *       dotychczasowym zarz�dc� by� \e Lst. Po wykonaniu tej operacji
    *       zarz�dca \e Lst nie jest powi�zany z �adn� kolejk�. 
    */
  void  MoveListFrom(List<ItemType,ID,ListType> &Lst);

   /*!
    *  Od��cza zarz�dc� od jego listy. Modyfikowane s� tylko pola
    *  zarz�dcy. Metoda nie zmienia p�l element�w listy w szczeg�lno�ci
    *  nie s� modyfikowane pola \link ListItem::_root _root\endlink.
    *  \return wska�nik na pocz�tek, z kt�r� zerwane zostaje po��czenie.
    */
  ItemType *RejectList() { ItemType *p = _first; _first=_last=NULL; return p;}

   /*!
    * Inicjalizuje pola \link List::_first _first\endlink i
    * \link List::_last _last\endlink adresami \p NULL.
    */
  List()            { _first=_last=0L; };
   /*!
    * Usuwa ca�� kolejk�, kt�r� zarz�dza.
    */
  virtual ~List()   { CancelList(); };



  /*!
   *  Wzorzec klasy iterotora jest wzorowany na analogicznych wzorcach
   *  wprowadzonych przez Bjarne Stroustrupa (jednak nie jest on w 
   *  pe�ni zgodny ze schematem proponowanym przez Stroustrupa).
   * 
   *
   * Przegl�danie z wykorzystaniem iterator�w:
   * \code
   *   List<int,0>  ListaLiczb;
   *   
   *   for (List<int,0>::VariaIterator *Iter = ListaLiczb.Begin(); 
   *        Iter;
   *        ++Iter) {
   *     ...  // Tutaj co� robimy z poszczeg�lnymi elementami listy
   *     ...  // i mo�emy te elementy modyfikowa�.
   *
   *     Iter->JakasMetodaElementu();  // np. wywo�ujemy metod� dla tego 
   *                                   // elementu.
   *    }
   *
   *   for (List<int,0>::ConstIterator *Iter = ListaLiczb.Begin(); 
   *        Iter;
   *        ++Iter) {
   *     ...  // Tutaj co� robimy z poszczeg�lnymi elementami listy
   *     ...  // i mo�emy te elementy modyfikowa�.
   *
   *     Iter->JakasMetodaElementu();  // np. wywo�ujemy metod� dla tego 
   *                                   // elementu.
   *    }
   * \endcode
   */
 class VariaIterator {
  protected:
    /*!
     * Pole zawiera wska�nik na pierwszy element, dla kt�rego iterator
     * zosta� zanicjalizowany (patrz konstruktor
     *  \link List::VariaIterator::VariaIterator VariaIterator\endlink).
     */
   ItemType        *_Fst;
    /*!
     * Jest to wska�nik roboczy. Jego warto�� jest zmieniana przez operacje
     * inkrementacji i dekrementacji.
     */
   ItemType        *_Wrk;   
    /*!
     *  Status ostatniej operacji (in/de)krementacji.
     *  Warto�� \e true oznacza, �e operacja si� powiod�a i nast�pny element
     *  listy jest dost�pny. W przypadku przeciwnym pole ma warto�� \e false.
     */
   bool         _OpStatus;

    /*!
     * Udost�pnia nast�pny element listy. Wykorzystana jest przez operatory
     * iteruj�ce kolejk�.
     */
   virtual ItemType  *Next() 
          { return (ItemType*) _Wrk->ListItem<ItemType,ID,ListType>::Next(); }

    /*!
     * Udost�pnia poprzedni element listy. Wykorzystana jest przez operatory
     * iteruj�ce kolejk�.
     */
   virtual ItemType  *Prev() 
          { return (ItemType*) _Wrk->ListItem<ItemType,ID,ListType>::Prev(); }
  public:

    /*! 
     * Inicjalizuje wszystkie pola iteratora.
     * \param Fst - wska�nik na element, kt�ry ma by� traktowany jako
     *              pierwszy element listy.
     * \post
     * Pole wskazuj�ce na pierwszy element
     *  (\link List::VariaIterator::_Fst _Fst\endlink) oraz pole robcze
     *  (\link List::VariaIterator::_Wrk _Wrk\endlink) sa incjalizowane
     *  wska�nikiem przekazywanym jako parametr. Pole okre�laj�ce poporawno��
     *  wykonania ostatniej operacji 
     *  (\link List::VariaIterator::_OpStatus _OpStatus\endlink)
     *  jest inicjalizowane warto�ci� 
     *  \e true, o ile \e Fst != NULL. W przeciwnym przypadku inicjalizowane
     *  jest warto�ci� \e false.
     */
   VariaIterator(const ItemType *Fst);
    /*!
     * Inicjalizuje pola iteratora wska�nikami \p NULL. Do pola
     * \link List::VariaIterator::_OpStatus _OpStatus\endlink wpisana zostaje
     * warto�� \p false. 
     *
     * Po utworzeniu iteratora w ten spos�b dla jego poprawnego przygotowania
     * do pracy nale�y u�y� metody 
     * \link List::VariaIterator::Init Init\endlink.
     */
   VariaIterator() { _Wrk = _Fst = 0L;  _OpStatus = false; }
   virtual ~VariaIterator() {}

   /*! 
     * Inicjalizuje wszystkie pola iteratora.
     * \param Fst - wska�nik na element, kt�ry ma by� traktowany jako
     *              pierwszy element listy.
     * \post
     * Pole wskazuj�ce na pierwszy element
     *  (\link List::VariaIterator::_Fst _Fst\endlink) oraz pole robcze
     *  (\link List::VariaIterator::_Wrk _Wrk\endlink) sa incjalizowane
     *  wska�nikiem przekazywanym jako parametr. Pole okre�laj�ce poporawno��
     *  wykonania ostatniej operacji 
     *  (\link List::VariaIterator::_OpStatus _OpStatus\endlink)
     *  jest inicjalizowane warto�ci� 
     *  \e true, o ile \e Fst != NULL. W przeciwnym przypadku inicjalizowane
     *  jest warto�ci� \e false.
     */
   void Init(ItemType *Fst);

   /*!
    * Konwerter udost�pnia status ostatniej operacji (in/de)krementacji
    * (warto�� pola 
    *   \link List::VariaIterator::_OpStatus _OpStatus\endlink).
    */
   operator bool () const { return _OpStatus; }

    /*!
     *  Powoduje przej�cie do poprzedniego elementu listy (o ile jest
     *  dost�pny).
     *  \post Je�eli operacja zako�czy�a si� sukcesem (istnia� poprzedni
     *         element listy), to do pola 
     *         \link VariaIterator::_OpStatus _OpStatus\endlink wpisana zostaje
     *         warto�� \p true. W przypadku przeciwnym wpisana zostaje
     *         warto�� \p false.
     */
   VariaIterator  &operator -- ();

    /*!
     *  Powoduje przej�cie do poprzedniego elementu listy (o ile jest
     *  dost�pny).
     *  \post Je�eli operacja zako�czy�a si� sukcesem (istnia� poprzedni
     *         element listy), to do pola 
     *         \link VariaIterator::_OpStatus _OpStatus\endlink wpisana zostaje
     *         warto�� \p true. W przypadku przeciwnym wpisana zostaje
     *         warto�� \p false.
     */
   VariaIterator  &operator -- (int);

    /*!
     *  Powoduje przej�cie do nast�pnego elementu listy (o ile jest
     *  dost�pny).
     *  \post Je�eli operacja zako�czy�a si� sukcesem (istnia� poprzedni
     *         element listy), to do pola 
     *         \link VariaIterator::_OpStatus _OpStatus\endlink wpisana zostaje
     *         warto�� \p true. W przypadku przeciwnym wpisana zostaje
     *         warto�� \p false.
     */
   VariaIterator  &operator ++ ();

    /*!
     *  Powoduje przej�cie do nast�pnego elementu listy (o ile jest
     *  dost�pny).
     *  \post Je�eli operacja zako�czy�a si� sukcesem (istnia� poprzedni
     *         element listy), to do pola 
     *         \link VariaIterator::_OpStatus _OpStatus\endlink wpisana zostaje
     *         warto�� \p true. W przypadku przeciwnym wpisana zostaje
     *         warto�� \p false.
     */
   VariaIterator  &operator ++ (int);

    /*!
     * Konwerter ten zwraca adres aktualnego elementu listy.
     */
   operator ItemType* () const { return _Wrk; }

    /*!
     * Zwraca adres aktualnego elementu listy.
     */
   ItemType* Get() const { return _Wrk; }

    /*!
     * Udost�pnia referencj� do aktualnego elementu listy.
     */
   ItemType &operator  *() const { return *_Wrk; }

    /*!
     * Udost�pnia wska�nik do aktualnego elementu listy.
     */
   ItemType *operator ->() const { return _Wrk; }

    /*!
     *  Ustawia wska�nik roboczy na pierwszy element listy.
     */
   void Reset() { _Wrk = _Fst; }
 };


  /*!
   * Iterator sta�y listy. Udost�pnia on kolejne elementy listy.
   * Udost�pniane elementy nie mog� podega� zmianom.
   *
   * Przegl�danie z wykorzystaniem iterator�w:
   * \code
   *   List<int,0>  ListaLiczb;
   *   
   *   for (List<int,0>::VariaIterator *Iter = ListaLiczb.Begin(); 
   *        Iter;
   *        ++Iter) {
   *     ...  // Tutaj co� robimy z poszczeg�lnymi elementami listy
   *     ...  // i mo�emy te elementy modyfikowa�.
   *
   *     Iter->JakasMetodaElementu();  // np. wywo�ujemy metod� dla tego 
   *                                   // elementu.
   *    }
   *
   *   for (List<int,0>::ConstIterator *Iter = ListaLiczb.Begin(); 
   *        Iter;
   *        ++Iter) {
   *     ...  // Tutaj co� robimy z poszczeg�lnymi elementami listy
   *     ...  // i mo�emy te elementy modyfikowa�.
   *
   *     Iter->JakasMetodaElementu();  // np. wywo�ujemy metod� dla tego 
   *                                   // elementu.
   *    }
   * \endcode
   */
  class ConstIterator {
   protected:
    /*!
     * Pole zawiera wska�nik na pierwszy element, dla kt�rego iterator
     * zosta� zanicjalizowany (patrz konstruktor
     *  \link List::ConstIterator::ConstIterator ConstIterator\endlink).
     */
    const ItemType  *_Fst;  /*!< Wska�nik na pierwszy element.               */
    /*!
     * Jest to wska�nik roboczy. Jego warto�� jest zmieniana przez operacje
     * inkrementacji i dekrementacji.
     */
    const ItemType  *_Wrk;
    /*!
     *  Status ostatniej operacji (in/de)krementacji.
     *  Warto�� \e true oznacza, �e operacja si� powiod�a i nast�pny element
     *  listy jest dost�pny. W przypadku przeciwnym pole ma warto�� \e false.
     */
    bool         _OpStatus;

    /*!
     * Udost�pnia nast�pny element listy. Wykorzystana jest przez operatory
     * iteruj�ce kolejk�.
     */
    virtual const ItemType *Next() 
              {return (ItemType*)_Wrk->ListItem<ItemType,ID,ListType>::Next();}

    /*!
     * Udost�pnia poprzedni element listy. Wykorzystana jest przez operatory
     * iteruj�ce kolejk�.
     */
    virtual const ItemType *Prev() 
              {return (ItemType*)_Wrk->ListItem<ItemType,ID,ListType>::Prev();}
   public:

    /*! 
     * Inicjalizuje wszystkie pola iteratora.
     * \param Fst - wska�nik na element, kt�ry ma by� traktowany jako
     *              pierwszy element listy.
     * \post
     * Pole wskazuj�ce na pierwszy element
     *  (\link List::ConstIterator::_Fst _Fst\endlink) oraz pole robcze
     *  (\link List::ConstIterator::_Wrk _Wrk\endlink) sa incjalizowane
     *  wska�nikiem przekazywanym jako parametr. Pole okre�laj�ce poporawno��
     *  wykonania ostatniej operacji 
     *  (\link List::ConstIterator::_OpStatus _OpStatus\endlink)
     *  jest inicjalizowane warto�ci� 
     *  \e true, o ile \e Fst != NULL. W przeciwnym przypadku inicjalizowane
     *  jest warto�ci� \e false.
     */
    ConstIterator(const ItemType *Fst);

    /*!
     * Inicjalizuje pola iteratora wska�nikami \p NULL. Do pola
     * \link List::ConstIterator::_OpStatus _OpStatus\endlink 
     * wpisana zostaje warto��
     * \p false. 
     *
     * Po utworzeniu iteratora w ten spos�b dla jego poprawnego przygotowania
     * do pracy nale�y u�y� metody 
     * \link List::ConstIterator::Init Init\endlink.
     */
    ConstIterator() { _Wrk = _Fst = 0L;  _OpStatus = false; }
    virtual ~ConstIterator() {}


    /*! 
     * Inicjalizuje wszystkie pola iteratora.
     * \param Fst - wska�nik na element, kt�ry ma by� traktowany jako
     *              pierwszy element listy.
     * \post
     * Pole wskazuj�ce na pierwszy element
     *  (\link List::ConstIterator::_Fst _Fst\endlink) oraz pole robcze
     *  (\link List::ConstIterator::_Wrk _Wrk\endlink) sa incjalizowane
     *  wska�nikiem przekazywanym jako parametr. Pole okre�laj�ce poporawno��
     *  wykonania ostatniej operacji 
     *  (\link List::ConstIterator::_OpStatus _OpStatus\endlink)
     *  jest inicjalizowane warto�ci� 
     *  \e true, o ile \e Fst != NULL. W przeciwnym przypadku inicjalizowane
     *  jest warto�ci� \e false.
     */
   void Init(const ItemType *Fst);

    /*!
     *  Udost�pnia status (\link ConstIterator::_OpStatus _OpStatus \endlink)
     *  wykonania ostatniej operacji inkrementacji lub
     *  dekrementacji.
     */
    operator bool () const { return _OpStatus; }

    /*!
     *  Powoduje przej�cie do poprzedniego elementu listy (o ile jest
     *  dost�pny).
     *  \post Je�eli operacja zako�czy�a si� sukcesem (istnia� poprzedni
     *         element listy), to do pola 
     *         \link List::ConstIterator::_OpStatus _OpStatus\endlink
     *         wpisana zostaje
     *         warto�� \p true. W przypadku przeciwnym wpisana zostaje
     *         warto�� \p false.
     */
    ConstIterator &operator -- ();

    /*!
     *  Powoduje przej�cie do poprzedniego elementu listy (o ile jest
     *  dost�pny).
     *  \post Je�eli operacja zako�czy�a si� sukcesem (istnia� poprzedni
     *         element listy), to do pola 
     *         \link List::ConstIterator::_OpStatus _OpStatus\endlink
     *         wpisana zostaje
     *         warto�� \p true. W przypadku przeciwnym wpisana zostaje
     *         warto�� \p false.
     */
    ConstIterator &operator -- (int);

    /*!
     *  Powoduje przej�cie do nast�pnego elementu listy (o ile jest
     *  dost�pny).
     *  \post Je�eli operacja zako�czy�a si� sukcesem (istnia� poprzedni
     *         element listy), to do pola 
     *         \link List::ConstIterator::_OpStatus _OpStatus\endlink
     *         wpisana zostaje
     *         warto�� \p true. W przypadku przeciwnym wpisana zostaje
     *         warto�� \p false.
     */
    ConstIterator &operator ++ ();

    /*!
     *  Powoduje przej�cie do nast�pnego elementu listy (o ile jest
     *  dost�pny).
     *  \post Je�eli operacja zako�czy�a si� sukcesem (istnia� poprzedni
     *         element listy), to do pola 
     *         \link List::ConstIterator::_OpStatus _OpStatus\endlink
     *         wpisana zostaje
     *         warto�� \p true. W przypadku przeciwnym wpisana zostaje
     *         warto�� \p false.
     */
    ConstIterator &operator ++ (int);

    /*!
     * Konwerter ten zwraca adres aktualnego elementu listy.
     */
    operator const ItemType* () const { return _Wrk; }

    /*!
     * Konwerter ten zwraca adres aktualnego elementu listy.
     */
    const ItemType* Get() const { return _Wrk; }

    /*!
     * Udost�pnia referencj� do aktualnego elementu listy.
     */
    const ItemType &operator  *() const { return *_Wrk; }

    /*!
     * Udost�pnia wska�nik do aktualnego elementu listy.
     */
    const ItemType *operator ->() const { return _Wrk; }

    /*!
     *  Ustawia wska�nik roboczy na pierwszy element listy.
     */
    void Reset() { _Wrk = _Fst; }
  };

  /*!
   *  Udost�pnia iterator, kt�ry wskazuje na pierwszy element listy.
   *  Dost�pne poprzez niego elementy mog� podlega� modyfikacji.
   */
  VariaIterator Begin() { return VariaIterator(First()); }

  /*!
   *  Udost�pnia iterator, kt�ry wskazuje na pierwszy element listy.
   *  Dost�pne poprzez niego elementy nie mog� podlega� modyfikacji.
   */
  ConstIterator Begin() const { return ConstIterator(First()); }


  /*!
   *  Udost�pnia iterator, kt�ry wskazuje na pierwszy element listy.
   *  Dost�pne poprzez niego elementy mog� podlega� modyfikacji.
   *  Metoda jest synonimem metody
   *  \link List::Begin List::Begin\endlink.
   */
  VariaIterator VarBegin() { return VariaIterator(First()); }


  /*!
   *  Udost�pnia iterator, kt�ry wskazuje na pierwszy element listy.
   *  Dost�pne poprzez niego elementy nie mog� podlega� modyfikacji.
   *  Metoda musi by� stosowana w przypadku, gdy obiekt zadeklarowany
   *  jest bez modyfikatora \b const. W takiej sytuacji wskazanie metody,
   *  kt�ra jest rodzaju \b const musi by� jawne.
   */
  ConstIterator ConBegin() const { return ConstIterator(First()); }
};  //======================== List ========================================




template <class ItemType, int ID, class ListType>
inline
void List<ItemType,ID,ListType>::VariaIterator::Init(ItemType *Fst)
{
 _Fst = (ItemType*)Fst;   _Wrk = (ItemType*)Fst;
 _OpStatus = (_Fst != 0L); 
}




template <class ItemType, int ID, class ListType>
inline
List<ItemType,ID,ListType>::VariaIterator::VariaIterator(const ItemType *Fst): 
    _Fst((ItemType*)Fst), _Wrk((ItemType*)Fst)
{ 
 _OpStatus = (_Fst != 0L); 
}


template <class ItemType, int ID, class ListType>
inline
typename List<ItemType,ID,ListType>::VariaIterator &
                List<ItemType,ID,ListType>::VariaIterator::operator -- () 
{ 
  if ((_OpStatus = (_Wrk != 0L))) return *this;
  _OpStatus = Prev() ? (_Wrk = Prev(), true) : false;
  return *this;
}




template <class ItemType, int ID, class ListType>
inline
typename List<ItemType,ID,ListType>::VariaIterator &
                List<ItemType,ID,ListType>::VariaIterator::operator -- (int) 
{ 
  return --*this;
}


template <class ItemType, int ID, class ListType>
inline
typename List<ItemType,ID,ListType>::VariaIterator &
                List<ItemType,ID,ListType>::VariaIterator::operator ++ ()
{ 
  if (!(_OpStatus = (_Wrk != 0L))) return *this; 
  _OpStatus = (Next() ? (_Wrk = Next(), true) : false);
  return *this;
}


template <class ItemType, int ID, class ListType>
inline
typename List<ItemType,ID,ListType>::VariaIterator &
               List<ItemType,ID,ListType>::VariaIterator::operator ++ (int)
{ 
  return ++*this;
}




template <class ItemType, int ID, class ListType>
inline
List<ItemType,ID,ListType>::ConstIterator::ConstIterator(const ItemType *Fst):
    _Fst((ItemType*)Fst), _Wrk((ItemType*)Fst)
{ 
 _OpStatus = (_Fst != 0L); 
}


template <class ItemType, int ID, class ListType>
inline
void List<ItemType,ID,ListType>::ConstIterator::Init(const ItemType *Fst) 
{
 _Fst = (ItemType*)Fst;   _Wrk = (ItemType*)Fst;
 _OpStatus = (_Fst != 0L); 
}




template <class ItemType, int ID, class ListType>
inline
typename List<ItemType,ID,ListType>::ConstIterator &
                 List<ItemType,ID,ListType>::ConstIterator::operator -- () 
{ 
  if ((_OpStatus = (_Wrk != 0L))) return *this;
  _OpStatus = Prev() ? (_Wrk = Prev(), true) : false;
  return *this;
}




template <class ItemType, int ID, class ListType>
inline
typename List<ItemType,ID,ListType>::ConstIterator  &
                 List<ItemType,ID,ListType>::ConstIterator::operator -- (int) 
{ 
  return --*this;
}


template <class ItemType, int ID, class ListType>
inline
typename List<ItemType,ID,ListType>::ConstIterator &
                 List<ItemType,ID,ListType>::ConstIterator::operator ++ ()
{ 
  if (!(_OpStatus = (_Wrk != 0L))) return *this; 
  _OpStatus =( Next() ? (_Wrk = Next(), true) : false);
  return *this;
}


template <class ItemType, int ID, class ListType>
inline
typename List<ItemType,ID,ListType>::ConstIterator &
                 List<ItemType,ID,ListType>::ConstIterator::operator ++ (int)
{ 
  return ++*this;
}



template <class ItemA, int ID, class ListType>
void List <ItemA,ID,ListType>::MoveListFrom( List<ItemA,ID,ListType> &MLst )
{
 ListItem<ItemA,ID,ListType> *pItem;                      

 List<ItemA,ID,ListType>::CancelList();
 List<ItemA,ID,ListType>::_first = MLst.List<ItemA,ID,ListType>::_first;
 List<ItemA,ID,ListType>::_last = MLst.List<ItemA,ID,ListType>::_last;
 MLst.List<ItemA,ID,ListType>::RejectList();
 for (pItem = List<ItemA,ID,ListType>::_first;
      pItem != NULL; pItem = pItem->ListItem<ItemA,ID,ListType>::Next())
                         pItem->ListItem<ItemA,ID,ListType>::SetRoot(this);
}



template <class Item,int ID, class ListType>
inline
Item  *List<Item,ID,ListType>::InitAsFirst(Item *pItem) 
{
 return _first = _last = pItem->ListItem <Item,ID,ListType>::InitAsFirst(this);
}


template <class Item,int ID, class ListType>
inline
Item* List <Item,ID,ListType>::At(unsigned int Idx)
{
  Item *pItem = _first;

  for (; pItem && Idx;  pItem = pItem->Next(), Idx--);
  return pItem;
}



template <class Item,int ID, class ListType>
inline
Item const * List <Item,ID,ListType>::At(unsigned int Idx) const
{
  Item const *pItem = _first;

  for (; pItem && Idx;  pItem = pItem->Next(), Idx--);
  return pItem;
}



template <class Item,int ID, class ListType>
inline
int List <Item,ID,ListType>::Number() const
{
  int No = 0;
 
  for (Item const *pItem = _first;  
       pItem;  
       pItem = pItem->ListItem<Item,ID,ListType>::Next(), No++);
  return No;
}




/*---------------------------------------------------------------------------
 * An item of the queue is removed.
 *
 * Environment:   ItemA ** Elem,
 *                ItemA  * workPointer,
 *                ItemA  * fixedPointer,
 *
 * PRE:            no preconditions
 * POST: return 0  - if workPointer = 0L (the queue is empty).
 *       return 1  - if an element of the queue is removed. Other results:
 *                 if the element has been the last in the queue,
 *                 workPointer and fixedPointer is set to 0L. In other
 *                 case the element pointed by workPointer is removed from
 *                 the queue and the workPointer IS SET TO the NEXT element.
 *                 If fixedPointer points to the element being removed, it
 *                 will be set to the PREVIOUS element.
 *
 *    Pointers of the element are modified by the destructor of ListItem.
 *    The old version !!!
 */

// template <class ItemA>
// void  List <ItemA>:

template <class Item,int ID, class ListType>
inline
void ListItem <Item,ID,ListType>::RemoveFromList()
{
 if (!_root)  return;

 if (!_prev)  _root->List <Item,ID,ListType>::SetFirst(_next);
 if (!_next)  _root->List <Item,ID,ListType>::SetLast(_prev);
 if (_prev)   _prev->ListItem <Item,ID,ListType>::_next = _next;
 if (_next)   _next->ListItem <Item,ID,ListType>::_prev = _prev;
 _root = 0L;
 _next = _prev = 0L;
}



/*! 
 *  Umieszcza nowy element listy za elementem, dla kt�rego
 *  wywo�ana zostaje ta metoda.
 *  \param  LItem - wska�nik na nowy element listy.
 *  \post
 *    Do listy do��czony zostaje nowy element, do kt�rego wska�nik
 *    dost�pny jest poprzez parametr \e New. Element ten do��czony
 *    zostaje za elementem, dla kt�rego wywo�ana zosta�a ta metoda.
 *    Je�eli element wskazywany przez \e New by� wcze�niej do��czony
 *    do innej listy, to przed operacj� do��czenia dokonywane jest
 *    jego wy��czenie z wcze�niejszej listy.
 *
 *  Schemat realizacji operacji:
 * \image html list-behind1.gif "Sytuacja przed wykonaniem metody \b PlaceBehind" width=5cm
 * \image html list-behind2.gif "Sytuacja po wykonaniu metody \b PlaceBehind" width=5cm
 * \image latex list-behind1.eps "Sytuacja przed wykonaniem metody \b PlaceBehind" width=5cm
 * \image latex list-behind2.eps "Sytuacja po wykonaniu metody \b PlaceBehind" width=5cm
 */
template <class Item, int ID, class ListType>
inline
Item* ListItem <Item,ID,ListType>::PlaceBehind( Item *LItem )
{ 
  if (LItem->ListItem <Item,ID,ListType>::_root) 
                          LItem->ListItem <Item,ID,ListType>::RemoveFromList();
  LItem->ListItem <Item,ID,ListType>::_root = _root;
  LItem->ListItem <Item,ID,ListType>::_prev = _prev;
  LItem->ListItem <Item,ID,ListType>::_next = (Item *) this;
  if (_prev)  { _prev->ListItem <Item,ID,ListType>::_next = LItem; }
  else { if (_root) _root->List <Item,ID,ListType>::SetFirst(LItem); }
  
  return _prev = LItem;
}




/*! 
 *  Umieszcza nowy element listy przed elementem, dla kt�rego
 *  wywo�ana zostaje ta metoda.
 *  \param  LItem - wska�nik na nowy element listy.
 *  \post
 *    Do listy do��czony zostaje nowy element, do kt�rego wska�nik
 *    dost�pny jest poprzez parametr \e New. Element ten do��czony
 *    zostaje przed elementem, dla kt�rego wywo�ana zosta�a ta metoda.
 *    Je�eli element wskazywany przez \e New by� wcze�niej do��czony
 *    do innej listy, to przed operacj� do��czenia dokonywane jest
 *    jego wy��czenie z wcze�niejszej listy.
 *
 *  Schemat realizacji operacji:
 * \image html list-behind1.gif "Sytuacja przed wykonaniem metody \b PlaceAhead" width=5cm
 * \image html list-ahead2.gif "Sytuacja po wykonaniu metody \b PlaceAhead" width=5cm
 * \image latex list-behind1.eps "Sytuacja przed wykonaniem metody \b PlaceAhead" width=5cm
 * \image latex list-ahead2.eps "Sytuacja po wykonaniu metody \b PlaceAhead" width=5cm

 */
template <class Item, int ID, class ListType>
inline
Item* ListItem <Item,ID,ListType>::PlaceAhead( Item *LItem)
{ 
  if (LItem->ListItem <Item,ID,ListType>::_root) 
                          LItem->ListItem <Item,ID,ListType>::RemoveFromList();
  LItem->ListItem <Item,ID,ListType>::_root = _root;
  LItem->ListItem <Item,ID,ListType>::_next = _next;
  LItem->ListItem <Item,ID,ListType>::_prev = (Item *) this;
  if (_next) _next->ListItem <Item,ID,ListType>::_prev = LItem;
  else { if (_root) _root->List <Item,ID,ListType>::SetLast(LItem); }
  return _next = LItem;
}


/*!
 *  Przesuwa dany element w li�cie przed poprzedni element, kt�ry
 *  z nim s�siaduje. W przypadku gdy element jest na pocz�tku
 *  listy, w�wczas nie jest podejmowana �adna akcja.
 *
 *  Schemat realizacji operacji:
 * \image html list-movebehind1.gif "Sytuacja przed wykonaniem metody \b MoveBehind" width=5cm
 * \image html list-movebehind2.gif "Sytuacja po wykonaniu metody \b MoveBehind" width=5cm
 * \image latex list-movebehind1.eps "Sytuacja przed wykonaniem metody \b MoveBehind" width=5cm
 * \image latex list-movebehind2.eps "Sytuacja po wykonaniu metody \b MoveBehind" width=5cm
 */
template <class ItemType, int ID, class ListType>
inline
void ListItem<ItemType,ID,ListType>::MoveBehind()
{
  if (!_prev) return;
  ListItem  *Item = _prev;
  RemoveFromList();
  Item->ListItem<ItemType,ID,ListType>::PlaceBehind((ItemType*)this);
}


/*!
 *  Przesuwa dany element w li�cie za nast�pny element, kt�ry
 *  z nim s�siaduje. W przypadku gdy element jest na pocz�tku
 *  listy, w�wczas nie jest podejmowana �adna akcja.
 *
 *  Schemat realizacji operacji:
 * \image html list-moveahead1.gif "Sytuacja przed wykonaniem metody \b MoveAhead" width=5cm
 * \image html list-moveahead2.gif "Sytuacja po wykonaniu metody \b MoveAhead" width=5cm
 * \image latex list-moveahead1.eps "Sytuacja przed wykonaniem metody \b MoveAhead" width=5cm
 * \image latex list-moveahead2.eps "Sytuacja po wykonaniu metody \b MoveAhead" width=5cm
 */
template <class ItemType, int ID, class ListType>
inline
void ListItem <ItemType,ID,ListType>::MoveAhead()
{
  if (!_next) return;
  ListItem  *Item = _next;
  RemoveFromList();
  Item->ListItem<ItemType,ID,ListType>::PlaceAhead((ItemType*)this);
}



template <class ItemA, int ID, class ListType>
inline
bool List <ItemA,ID,ListType>::CancelItem( ItemA *Elem )
{
 if (!Elem) return false;
 if (this != Elem->ListItem<ItemA,ID,ListType>::_root) return false;
 delete Elem;
 return true;
}




template <class ItemA, int ID, class ListType>
inline
void List<ItemA,ID,ListType>::CancelList()
{ 
  while (_first)  delete _first;
}




/*!
 * Dodaje nowy element do listy.
 *
 * \param Elem - wska�nik na dodawany element.
 * \post Dodany element zostaje umieszczony na pocz�tku listy.
 *       Powoduje to modyfikacje pola 
 *       \link List::_first _first\endlink zarz�dcy listy.
 * \return wska�nik na dodany element.
 */
template <class ItemA, int ID, class ListType>
inline
ItemA* List <ItemA,ID,ListType>::AddToHead(ItemA *Elem)
{
 if (!Elem) return 0L;
 if (Elem->Root()) Elem->RemoveFromList();
 if (!_first) InitAsFirst(Elem);
      else   _first->ListItem <ItemA,ID,ListType>::PlaceBehind(Elem);
 return Elem;
}


/*!
 * Dodaje nowy element do listy.
 *
 * \param Elem - wska�nik na dodawany element.
 * \post Dodany element zostaje umieszczony na ko�cu listy.
 *       Powoduje to zawsze modyfikacje pola 
 *       \link List::_last _last\endlink zarz�dcy listy.
 * \return wska�nik na dodany element.
 */
template <class ItemA, int ID, class ListType>
inline
ItemA* List <ItemA,ID,ListType>::AddToTail(ItemA *Elem)
{
 if (!Elem) return 0L;
 if (Elem->ListItem<ItemA,ID,ListType>::Root()) 
               Elem->ListItem<ItemA,ID,ListType>::RemoveFromList();
 if (!_first) InitAsFirst(Elem);
      else   _last->ListItem <ItemA,ID,ListType>::PlaceAhead(Elem);
 return Elem;
}


/*!
 *  Wzorzec funkcji szukania elementu w kolejce wg. zadanego kryterium.
 *  \param  ListObj - obiekt b�d�cy zarz�dc� listy dwukierunkowej
 *                    opeartej na szablonie \link List List \endlink.
 *  \param  Val     - warto�� wg. szukany jest zadany element.
 *  \param  Compare - funkcja definiuj�ca kryterium por�wnania dla
 *                    danego elementu.
 */
template <class ListType, class ItemType, typename SearchType>
ItemType *FindInList( ListType   &ListObj,
                      SearchType Val, 
                      bool Compare(SearchType, ItemType* )
                    )
{
 for (ItemType *Item = ListObj.First(); Item; Item = Item->Next()) {
   if (Compare(Val,Item)) return Item;
 }
 return 0L;
}


#endif
