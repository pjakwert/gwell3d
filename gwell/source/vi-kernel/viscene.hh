#ifndef VISCENE_HH
#define VISCENE_HH

/*! \file viscene.hh
 *  Plik zawiera definicj� klasy \link ViScene ViScene\endlink reprezentuj�c�
 *  pojedyncz� scen�.
 *
 * \author  Bogdan Kreczmer
 * \date    2004.03
 */

#ifdef __GNUG__
#pragma interface
#endif


#include "listque.hh"
#include "extstring.hh"
#include "vipattepolyhlib.hh"
#include "vimultipolyh.hh"
#include "vipatteliblist.hh"
#include "viscenepolyhlist.hh"
#include "viexception.hh"
#include "viexception.hh"
#include <iostream>
//class ViException_Patte;

namespace Vi {

  /*!
   *  Definicja tego typu wyliczeniowego pozwala na rozr�nienie
   *  listy bry� zwyk�ych i specjalnych.
   */
  typedef  enum { LT_Norm, LT_Spec } MultiPolyhListType;

};


/*!
 *  Klasa reprezentuje pojedyncz� scen�. Jest przystosowana do tego aby by�
 *  elementem kolejki (dziedziczy wzorzec \link ListItem ListItem\endlink).
 *  Potencjalnie wi�c mo�na tworzy� zbi�r scen.
 *  
 *  Klasa dysponuje iteratorami pozwalaj�cymi przegl�da� bry�y z�o�one
 *  zar�wno specjalne jaki i normalne.
 *  
 *  Przyk�ad korzystania z iteratora:
 *  \code
 *  void SceneMultiPolyhIteration(ViScene const &Scene)
 *  {
 *    for (ViScene::ConMultiPolyhIter Iter = Scene.ConBegin_NormMultiPolyh();
 *         Iter; ++Iter) {
 *       cout << " Bryla zlozona: " << Iter->GetName() 
 *            << "        Adres wezla: " << Iter->GetNodeAddress() << endl;
 *    }
 *    cout << endl;
 *  }
 *  \endcode
 */
class ViScene: public ListItem<ViScene,0> {


  /*!
   * Nazwa sceny.
   */
  ExtString _SceneName;


 protected:

   /*!
    *  Zarz�dca kolejki obiekt�w wzorcowych. Jedna scena mo�e zawiera�
    *  wiele bibliotek. Ka�da z bibliotek jest identyfikowana poprzez
    *  swoj� nazw� (\link ViPattePolyhLib::_LibName _LibName\endlink).
    */
  ViPatteLibList  _PattePolyhLib_List;

   /*!
    *  Pole jest zarz�dc� kolejki zwyk�ych bry� z�o�onych,
    *  tzn. bry� modeluj�cych obiekty znajduj�ce si� na scenie.
    */
  ViScenePolyhList   _NormMultiPolyh;

   /*!
    *  Pole jest zarz�dc� kolejki specjalnych bry� z�o�onych
    *  (np. obiekty reprezntuj�ce �wiat�a, sufit, pod�og� itd.).
    */
  ViScenePolyhList   _SpecMultiPolyh;

  /*!
   * \if brief_private_fields
   *  \brief Obrys wszystkich bry� sceny.
   * \endif
   *
   *  Pole reprezentuje obrys we wsp�rz�dnych globalnych
   *  wszystkich bry� danej sceny (specjalnych i normalnych).
   */
   OutlineBox3f      _GlbOutlineBox;

 public:

  /*!
   * \if brief_public_methods
   *  \brief Udost�pnia obrys wszystkich bry� sceny.
   * \endif
   *
   * Metoda udost�pnia obrys we wsp�rz�dnych globalnych
   *  wszystkich bry� danej listy. Obrys udost�pniany jest w trybie modyfikacji. 
   */
  OutlineBox3f  &GetOutlineBox() { return _GlbOutlineBox; }

  /*!
   * \if brief_public_methods
   *  \brief Udost�pnia obrys wszystkich bry� sceny.
   * \endif
   *
   * Metoda udost�pnia obrys we wsp�rz�dnych globalnych
   *  wszystkich bry� danej listy. Obrys udost�pniany jest w trybie sta�ym. 
   */
  const OutlineBox3f &GetOutlineBox() const { return _GlbOutlineBox; }


  /*!
   *  Usuwa z danej sceny wszystkie bry�y normalne.
   *  Obiekty modeluj�ce bry�y z�o�one s� niszczone.
   */
  void DeleteAllNormMultiPolyh() 
   {_NormMultiPolyh.List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>::CancelList();}
  /*!
   *  Usuwa z danej sceny wszystkie bry�y specjalne.
   *  Obiekty modeluj�ce bry�y z�o�one s� niszczone.
   */
  void DeleteAllSpecMultiPolyh() 
   {_SpecMultiPolyh.List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>::CancelList();}
  /*!
   *  Usuwa z danej sceny wszystkie bry�y z�o�one, zar�wno specjalne
   *  jak te� normalne.
   *  Obiekty modeluj�ce bry�y z�o�one s� niszczone.
   */
  void DeleteAllMultiPolyh() 
         { DeleteAllNormMultiPolyh();  DeleteAllSpecMultiPolyh(); }


  /*!
   *  Typ pomocniczy zdefiniowany dla umo�liwienia odwo�ywania
   *  si� do typu macierzystego poprzez skr�con� nazw�.
   *  Obiekt tej klasy umo�liwia iteracj� bibliotek obiekt�w wzorcowych
   *  dla danej sceny. Biblioteki 
   *  (obiekty klasy ViPattePolyhLib) udost�pniane s� jako obiekty sta�e.
   *  
   *  Przyklad wykorzystania:
   * \code
   *  ViScene  Scene;
   *    . . .
   *  // Wy�wietla nazwy wszystkich bibliotek dla danej sceny.
   * for (ViScene::ConLibIterator Iter = Scene.ConBegin_Lib(); Iter; Iter++) {
   *   cout << "Biblioteka: " << Iter->GetLibName() << endl;
   * }
   * \endcode
   */
  typedef ViPatteLibList::ConLibIterator  ConLibIterator;

  /*!
   *  Typ pomocniczy zdefiniowany dla umo�liwienia odwo�ywania
   *  si� do typu macierzystego poprzez skr�con� nazw�.
   *  Obiekt tej klasy umo�liwia iteracj� bibliotek obiekt�w wzorcowych
   *  dla danej sceny. Biblioteki 
   *  (obiekty klasy ViPattePolyhLib) udost�pniane s� jako obiekty modyfikowalne.
   *  
   *  Przyklad wykorzystania:
   *  \code
   *   ViScene  Scene;
   *     . . .
   *   // Zmienia nazwy bibliotek (normalnie nie nale�y tego robi�).
   *  int i=0;
   *  for (ViScene::VarLibIterator Iter = Scene.Begin_Lib(); Iter; Iter++) {
   *    ExtString  Nazwa("bib");
   *    Nazwa << i++;
   *    Iter->SetLibName(Nazwa);
   *  }
   *  \endcode
   */
  typedef ViPatteLibList::VarLibIterator  VarLibIterator;

   /*!
    *  Definiuje skr�con� nazw� do typu iteratora kolejki obiekt�w z�o�onych.
    *  Iterator ten udost�pnia iterowane obiekty w trybie \b sta�ym.
    */
  typedef ViScenePolyhList::ConMultiPolyhIter  ConMultiPolyhIter;

   /*!
    *  Definiuje skr�con� nazw� do typu iteratora kolejki obiekt�w z�o�onych.
    *  Iterator ten udost�pnia iterowane obiekty w trybie \b modyfikowacji.
    */
  typedef ViScenePolyhList::VarMultiPolyhIter  VarMultiPolyhIter;


  /*!
   *  Jest to szablon klasy bazowej dla klas iterator�w bry� wzorcowych.
   *  \param  LibIterType - typ iteratora bibliotek obiekt�w wzorcowych. 
   *                 Dopuszczalne warto�ci: ConLibIterator, VarLibIterator.
   *  \param  PatIterType - typ iteratora obiekt�w wzorcowych.
   *                 Dopuszczalne warto�ci: ViPattePolyhLib::ConPatteIter,
   *                                        ViPattePolyhLib::VarPatteIter.
   *  \param  ParenType - nazwa klasy pochodnej.
   *  \param  PolyhType - nazwa typu obiektu wzorcowego.
   *                 Dopuszczalne warto�ci: ViPattePolyh, const ViPattePolyh.
   */
  template <class LibIterType, class PatIterType, class ParentType, 
            class PolyhType>
  class PatteIter {
   protected:
    /*!
     * Roboczy iterator bibliotek.
     */ 
    LibIterType  _LibIter;
    /*!
     * Roboczy iterator obiekt�w wzorcowych dla pojedynczej biblioteki.
     */
    PatIterType  _PatIter;
    /*!
     *  Przechowuje informacj� o tym, czy iteracja realizowana jest tylko
     *  dla jednej biblioteki czy te� dla wszystkich.
     */
    bool  _OnlyOne;
    /*!
     *  Status ostatniej operacji (in/de)krementacji.
     *  Warto�� \e true oznacza, �e operacja si� powiod�a i nast�pny element
     *  kolejki jest dost�pny. W przypadku przeciwnym pole ma warto�� 
     *  \e false.
     */
    bool  _OpStatus;
   public:

    /*!
     *  Inicjalizuje obiekt wpisuj�c do pola 
     *  \link PatteIter::_OpStatus PatteIter::_OpStatus\endlink warto��
     *  \p true.
     */
    PatteIter() { _OpStatus = true; }
    /*!
     *  Destruktor jest wirtualny ze wzgl�du na obecno�� metod wirtualnych.
     */
    virtual ~PatteIter() {}
    /*!
     * Konwerter udost�pnia status ostatniej operacji (in/de)krementacji
     * (warto�� pola 
     *   \link ViScene::VarNormPatteIter::_OpStatus _OpStatus\endlink).
     */
    operator bool () const { return _OpStatus; }

    /*!
     *  Powoduje przej�cie do poprzedniej bry�y wzorcowej (o ile jest
     *  dost�pna). 
     *  \post Je�eli operacja zako�czy�a si� sukcesem (istnia� poprzedni
     *     element kolejki), to do pola 
     *     \link ViScene::VarNormPatteIter::_OpStatus _OpStatus\endlink
     *     wpisana zostaje warto�� \p true. W przypadku przeciwnym wpisana
     *     zostaje warto�� \p false.
     */
    virtual ParentType &operator --() = 0;

    /*!
     *  Powoduje przej�cie do nast�pnej bry�y wzorcowej (o ile jest
     *  dost�pna).
     *  \post Je�eli operacja zako�czy�a si� sukcesem (istnia� poprzedni
     *     element kolejki), to do pola 
     *     \link ViScene::VarNormPatteIter::_OpStatus _OpStatus\endlink
     *     wpisana zostaje warto�� \p true. W przypadku przeciwnym wpisana
     *     zostaje warto�� \p false.
     */
    virtual ParentType &operator ++() = 0;
    /*!
     *  Powoduje przej�cie do nast�pnej bry�y wzorcowej (o ile jest
     *  dost�pna).
     *  \warning Stosowanie tego operatora nie jest zalecane, gdy�
     *           jest "wolniejszy" od operatora przedrostkowego.
     *  \post Je�eli operacja zako�czy�a si� sukcesem (istnia� poprzedni
     *     element kolejki), to do pola 
     *     \link ViScene::VarNormPatteIter::_OpStatus _OpStatus\endlink
     *     wpisana zostaje warto�� \p true. W przypadku przeciwnym wpisana
     *     zostaje warto�� \p false.
     */
    ParentType &operator ++(int) { return ++*this; }

    /*!
     *  Powoduje przej�cie do poprzedniej bry�y wzorcowej (o ile jest
     *  dost�pna). 
     *  \warning Stosowanie tego operatora nie jest zalecane, gdy�
     *           jest "wolniejszy" od operatora przedrostkowego.
     *  \post Je�eli operacja zako�czy�a si� sukcesem (istnia� poprzedni
     *     element kolejki), to do pola 
     *     \link ViScene::VarNormPatteIter::_OpStatus _OpStatus\endlink
     *     wpisana zostaje warto�� \p true. W przypadku przeciwnym wpisana
     *     zostaje warto�� \p false.
     */
    ParentType &operator --(int) { return --*this; }

    /*!
     * Konwerter ten zwraca adres aktualnego elementu kolejki.
     */
    operator PolyhType* () const { return _PatIter; }

    /*!
     * Udost�pnia referencj� do aktualnego elementu kolejki.
     */
    PolyhType &operator  *() const { return *_PatIter; }
 
    /*!
     * Udost�pnia wska�nik do aktualnego elementu kolejki.
     */
    PolyhType *operator ->() const { return _PatIter; }

  };





  /*!
   *  Umo�liwia iterowanie zwyk�ych obiekt�w wzorcowych bez potrzeby jawnego
   *  odwo�ywania si� do kolejki bibliotek zawieraj�cych te obiekty.
   *  Iterator udost�pnia obiekty w trybie modyfikacji.
   */
  class VarNormPatteIter:
          public PatteIter<VarLibIterator,ViPattePolyhLib::VarPatteIter,
                           VarNormPatteIter,ViPattePolyh> {
   public:
  /*!
    * Inicjalizuje interator do przegl�dania wszystkich bibliotek,
    * lub jednej wybranej.
    * \param  LibList - zarz�dca listy bibliotek obiekt�w elementarnych,
    * \param  LibName - nazwa biblioteki.
    * \post Je�eli \e LibName = \p NULL, to iterator zostanie zainicjowany
    *        do przegl�dania wszystkich bibliotek. W przypadku przeciwnym
    *        zostanie on zainicjalizowany do przegl�dania wybranej biblioteki.
    *        Je�eli biblioteka o podanej nazwie nie istnieje, to zg�aszany
    *        jest wyj�tek 
    *        \link ViException_OutOfRange ViException_OutOfRange\endlink.
    */
    VarNormPatteIter(ViPatteLibList &LibList, const char *LibName = 0L);
   /*!
    *  Powoduje przej�cie do nast�pnej bry�y wzorcowej (o ile jest
    *  dost�pna).
    *  \post Je�eli operacja zako�czy�a si� sukcesem (istnia� poprzedni
    *     element kolejki), to do pola 
    *     \link ViScene::VarNormPatteIter::_OpStatus _OpStatus\endlink
    *     wpisana zostaje warto�� \p true. W przypadku przeciwnym wpisana
    *     zostaje warto�� \p false.
    */
    VarNormPatteIter &operator ++();
   /*!
    *  Powoduje przej�cie do poprzedniej bry�y wzorcowej (o ile jest
    *  dost�pna).
    *  \post Je�eli operacja zako�czy�a si� sukcesem (istnia� poprzedni
    *     element kolejki), to do pola 
    *     \link ViScene::VarNormPatteIter::_OpStatus
    *                              _OpStatus\endlink wpisana zostaje
    *     warto�� \p true. W przypadku przeciwnym wpisana zostaje
    *     warto�� \p false.
    */
    VarNormPatteIter &operator --();

    /*!
     *  Ustawia wska�nik roboczy na pierwszy element kolejki.
     */
    void Reset();
  };



  /*!
   *  Umo�liwia iterowanie zwyk�ych obiekt�w wzorcowych bez potrzeby jawnego
   *  odwo�ywania si� do kolejki bibliotek zawieraj�cych te obiekty.
   *  Iterator udost�pnia obiekty jako sta�e.
   */
  class ConNormPatteIter:
      public PatteIter<ConLibIterator,ViPattePolyhLib::ConPatteIter,
                       ConNormPatteIter,const ViPattePolyh>  {
   public:

   /*!
    * Inicjalizuje interator do przegl�dania wszystkich bibliotek,
    * lub jednej wybranej.
    * \param  LibList - zarz�dca listy bibliotek obiekt�w elementarnych,
    * \param  LibName - nazwa biblioteki.
    * \post Je�eli \e LibName = \p NULL, to iterator zostanie zainicjowany
    *        do przegl�dania wszystkich bibliotek. W przypadku przeciwnym
    *        zostanie on zainicjalizowany do przegl�dania wybranej biblioteki.
    *        Je�eli biblioteka o podanej nazwie nie istnieje, to zg�aszany
    *        jest wyj�tek 
    *        \link ViException_OutOfRange ViException_OutOfRange\endlink.
    */
    ConNormPatteIter(const ViPatteLibList &LibList, const char *LibName = 0L);

   /*!
    *  Powoduje przej�cie do nast�pnej bry�y wzorcowej (o ile jest
    *  dost�pna).
    *  \post Je�eli operacja zako�czy�a si� sukcesem (istnia� poprzedni
    *     element kolejki), to do pola 
    *     \link ViScene::ConNormPatteIter::_OpStatus _OpStatus\endlink
    *     wpisana zostaje warto�� \p true. W przypadku przeciwnym wpisana
    *     zostaje warto�� \p false.
    */
    ConNormPatteIter &operator ++();
   /*!
    *  Powoduje przej�cie do poprzedniej bry�y wzorcowej (o ile jest
    *  dost�pna).
    *  \post Je�eli operacja zako�czy�a si� sukcesem (istnia� poprzedni
    *     element kolejki), to do pola 
    *     \link ViScene::ConNormPatteIter::_OpStatus
    *                              _OpStatus\endlink wpisana zostaje
    *     warto�� \p true. W przypadku przeciwnym wpisana zostaje
    *     warto�� \p false.
    */
    ConNormPatteIter &operator --();

    /*!
     *  Ustawia wska�nik roboczy na pierwszy element kolejki.
     */
    void Reset();
  };




  /*!
   *  Umo�liwia iterowanie specjalnych obiekt�w wzorcowych bez potrzeby 
   *  jawnego odwo�ywania si� do kolejki bibliotek zawieraj�cych te obiekty.
   *  Iterator udost�pnia obiekty w trybie modyfikacji.
   */
  class VarSpecPatteIter:
          public PatteIter<VarLibIterator,ViPattePolyhLib::VarPatteIter,
                           VarSpecPatteIter,ViPattePolyh> {
   public:

   /*!
    * Inicjalizuje interator do przegl�dania wszystkich bibliotek,
    * lub jednej wybranej.
    * \param  LibList - zarz�dca listy bibliotek obiekt�w elementarnych,
    * \param  LibName - nazwa biblioteki.
    * \post Je�eli \e LibName = \p NULL, to iterator zostanie zainicjowany
    *        do przegl�dania wszystkich bibliotek. W przypadku przeciwnym
    *        zostanie on zainicjalizowany do przegl�dania wybranej biblioteki.
    *        Je�eli biblioteka o podanej nazwie nie istnieje, to zg�aszany
    *        jest wyj�tek 
    *        \link ViException_OutOfRange ViException_OutOfRange\endlink.
    */
    VarSpecPatteIter(ViPatteLibList &LibList, const char *LibName = 0L);

   /*!
    *  Powoduje przej�cie do nast�pnej bry�y wzorcowej (o ile jest
    *  dost�pna).
    *  \post Je�eli operacja zako�czy�a si� sukcesem (istnia� poprzedni
    *     element kolejki), to do pola 
    *     \link ViScene::VarSpecPatteIter::_OpStatus _OpStatus\endlink
    *     wpisana zostaje warto�� \p true. W przypadku przeciwnym wpisana
    *     zostaje warto�� \p false.
    */
    VarSpecPatteIter &operator ++();

   /*!
    *  Powoduje przej�cie do poprzedniej bry�y wzorcowej (o ile jest
    *  dost�pna).
    *  \post Je�eli operacja zako�czy�a si� sukcesem (istnia� poprzedni
    *     element kolejki), to do pola 
    *     \link ViScene::VarSpecPatteIter::_OpStatus
    *                              _OpStatus\endlink wpisana zostaje
    *     warto�� \p true. W przypadku przeciwnym wpisana zostaje
    *     warto�� \p false.
    */
    VarSpecPatteIter &operator --();

    /*!
     *  Ustawia wska�nik roboczy na pierwszy element kolejki.
     */
    void Reset();
  };



  /*!
   *  Umo�liwia iterowanie specjalnych obiekt�w wzorcowych bez potrzeby jawnego
   *  odwo�ywania si� do kolejki bibliotek zawieraj�cych te obiekty.
   *  Iterator udost�pnia obiekty jako sta�e.
   */
  class ConSpecPatteIter:
      public PatteIter<ConLibIterator,ViPattePolyhLib::ConPatteIter,
                       ConSpecPatteIter,const ViPattePolyh>  {
   public:
   /*!
    * Inicjalizuje interator do przegl�dania wszystkich bibliotek,
    * lub jednej wybranej.
    * \param  LibList - zarz�dca listy bibliotek obiekt�w elementarnych,
    * \param  LibName - nazwa biblioteki.
    * \post Je�eli \e LibName = \p NULL, to iterator zostanie zainicjowany
    *        do przegl�dania wszystkich bibliotek. W przypadku przeciwnym
    *        zostanie on zainicjalizowany do przegl�dania wybranej biblioteki.
    *        Je�eli biblioteka o podanej nazwie nie istnieje, to zg�aszany
    *        jest wyj�tek 
    *        \link ViException_OutOfRange ViException_OutOfRange\endlink.
    */
    ConSpecPatteIter(const ViPatteLibList &LibList, const char *LibName = 0L);

   /*!
    *  Powoduje przej�cie do nast�pnej bry�y wzorcowej (o ile jest
    *  dost�pna).
    *  \post Je�eli operacja zako�czy�a si� sukcesem (istnia� poprzedni
    *     element kolejki), to do pola 
    *     \link ViScene::ConSpecPatteIter::_OpStatus _OpStatus\endlink
    *     wpisana zostaje warto�� \p true. W przypadku przeciwnym wpisana
    *     zostaje warto�� \p false.
    */
    ConSpecPatteIter &operator ++();

   /*!
    *  Powoduje przej�cie do poprzedniej bry�y wzorcowej (o ile jest
    *  dost�pna).
    *  \post Je�eli operacja zako�czy�a si� sukcesem (istnia� poprzedni
    *     element kolejki), to do pola 
    *     \link ViScene::ConSpecPatteIter::_OpStatus
    *                              _OpStatus\endlink wpisana zostaje
    *     warto�� \p true. W przypadku przeciwnym wpisana zostaje
    *     warto�� \p false.
    */
    ConSpecPatteIter &operator --();

    /*!
     *  Ustawia wska�nik roboczy na pierwszy element kolejki.
     */
    void Reset();
  };




   /*!
    *  Inicjalizuje scen�, jako scen� bez nazwy.
    */
  ViScene(): _SceneName("") {}

   /*!
    *  Destruktor jest wirtualny dla zapewnienie zgodno�ci przy 
    *  dziedziczeniu (klasa, kt�ra ma metody wirtualne powinna mie�
    *  r�wnie� wirtualny destruktor).
    */
  virtual ~ViScene() {}

  /*!
   *  Udost�pnia referencj� do listy bibliotek bry� elementarnych
   *  skojarzonych z dan� scen�.
   */
  const ViPatteLibList &GetList_PatteLibs() const
                                    { return _PattePolyhLib_List; }


  /*!
   *  Udost�pnia referencj� do pola listy normalnych bry� z�o�onych.
   */
  const ViScenePolyhList& GetList_NormMultiPolyh() const 
                                           { return _NormMultiPolyh;}

  /*!
   *  Udost�pnia referencj� do pola listy normalnych bry� z�o�onych.
   *  Referencja udost�pniana jest w trybie modyfikacji.
   */
  ViScenePolyhList&  UseList_NormMultiPolyh()  { return _NormMultiPolyh;}


  /*!
   *  Udost�pnia referencj� do pola listy specjalnych bry� z�o�onych.
   *  \warning Metoda ta ma w nazwie literowk� i w nast�pnej wersji
   *   biblioteki zostanie wycofana. Zamiast niej nale�y u�ywa� metody
   *   \link ViScene::GetList_SpecMultiPolyh 
   *             ViScene::GetList_SpecMultiPolyh\endlink;
   */
  const ViScenePolyhList& GetList_SepcMultiPolyh() const 
                                                { return _SpecMultiPolyh;}

  /*!
   *  Udost�pnia referencj� do pola listy specjalnych bry� z�o�onych.
   */
  const ViScenePolyhList& GetList_SpecMultiPolyh() const 
                                                { return _SpecMultiPolyh;}


  /*!
   *  Udost�pnia referencj� do pola listy specjalnych bry� z�o�onych.
   *  Referencja udost�pniana jest w trybie modyfikacji.
   */
  ViScenePolyhList&  UseList_SpecMultiPolyh()  { return _SpecMultiPolyh;}




  /*!
   *  Udost�pnia referencj� do pola listy specjalnych bry� z�o�onych.
   *  \warning U�ywanie tej metody nie jest zalecane, gdy� zostanie ona
   *  usuni�ta nowszej wersji biblioteki. Nale�y korzysta� z metody
   *  \link ViScene GetList_SepcMultiPolyh\endlink.
   */
  const ViScenePolyhList& GetSpecMultiPolyh() const { return _SpecMultiPolyh;}

  /*!
   *  Udost�pnia referencj� do pola listy specjalnych bry� z�o�onych.
   *  Referencja udost�pniana jest w trybie modyfikacji.
   *  \warning  U�ywanie tej metody nie jest zalecane, gdy� zostanie ona 
   *   usuni�ta nowszej wersji biblioteki. Nale�y korzysta� z metody
   *   \link ViScene GetList_SepcMultiPolyh\endlink.
   */
  ViScenePolyhList&  UseSpecMultiPolyh()  { return _SpecMultiPolyh;}




   /*!
    *  Udost�pnia nazw� sceny.   
    */
  ExtString const &GetSceneName() const { return _SceneName; }

   /*!
    *  Zmienia nazw� sceny.
    */
  void SetSceneName(char const *Name) { _SceneName = Name; }


  ViMultiPolyh *AddNormMultiPolyh(ViMultiPolyh *pMPolyh)
        { return  _NormMultiPolyh.AddMultiPolyh(pMPolyh); }

  ViMultiPolyh *AddSpecMultiPolyh(ViMultiPolyh *pMPolyh)
        { return  _SpecMultiPolyh.AddMultiPolyh(pMPolyh); }

    /*!
     *  Szuka biblioteki obiekt�w wzorcowych o zadanej nazwie.
     * \param LibName - nazwa biblioteki obiekt�w wzorcowych. 
     *                   Nazwa biblioteki brana jest
     *                   z pliku zawieraj�cego opis bibioteki.
     * \return wska�nik do biblioteki. Je�eli biblioteka o podanej nazwie
     *         nie istnieje, to zwracany jest wska�nik \p NULL.
     */
  const ViPattePolyhLib *FindPattePolyhLib(const char *LibName) const
                    { return _PattePolyhLib_List.FindPattePolyhLib(LibName); }

  /*!
   * Udost�pnia w�ze�
   * z hierarchicznego modelu sceny z listy bry� normalnych na podstawie adresu
   * tego� w�z�a w ca�ej strukturze.
   * Udost�pniany w�ze� mo�e by� bry�� z�o�on� lub elementarn�.
   * Za konwersj� do w�a�ciwej klasy pochodnej danego w�z�a odpowiada
   * programista.
   * \param  Addr - adres w�z�a. Jego sk�adnia musi by� zgodna z wymaganiami
   *                przedstaionymi w opisie klasy ViNodeAddress.
   * \return wska�nik znalezionego w�z�a. Wska�nik na w�ze� udost�pniany jest
   *         jest w trybie sta�ym. Je�li danemu adresowi nie odpowiada\
   *         �aden w�ze�, w�wczas zwracana jest warto�� \p NULL. 
   */
  const ViNTreeNode *FindNormPolyh_Con(const ViNodeAddress &Addr) const;

  /*!
   * Udost�pnia w�ze�
   * z hierarchicznego modelu sceny z listy bry� normalnych na podstawie adresu
   * tego� w�z�a w ca�ej strukturze.
   * Udost�pniany w�ze� mo�e by� bry�� z�o�on� lub elementarn�.
   * Za konwersj� do w�a�ciwej klasy pochodnej danego w�z�a odpowiada
   * programista.
   * \param  Addr - adres w�z�a. Jego sk�adnia musi by� zgodna z wymaganiami
   *                przedstaionymi w opisie klasy ViNodeAddress.
   * \return wska�nik znalezionego w�z�a. Wska�nik na w�ze� udost�pniany jest
   *         jest w trybie sta�ym. Je�li danemu adresowi nie odpowiada\
   *         �aden w�ze�, w�wczas zwracana jest warto�� \p NULL. 
   */
  ViNTreeNode *FindNormPolyh_Var(const ViNodeAddress &Addr)
    { return (ViNTreeNode*) FindNormPolyh_Con(Addr); }


  /*!
   * Udost�pnia w�ze�
   * z hierarchicznego modelu sceny z listy bry� specjalnych na podstawie adresu
   * tego� w�z�a w ca�ej strukturze.
   * Udost�pniany w�ze� mo�e by� bry�� z�o�on� lub elementarn�.
   * Za konwersj� do w�a�ciwej klasy pochodnej danego w�z�a odpowiada
   * programista.
   * \param  Addr - adres w�z�a. Jego sk�adnia musi by� zgodna z wymaganiami
   *                przedstaionymi w opisie klasy ViNodeAddress.
   * \return wska�nik znalezionego w�z�a. Wska�nik na w�ze� udost�pniany jest
   *         jest w trybie sta�ym. Je�li danemu adresowi nie odpowiada\
   *         �aden w�ze�, w�wczas zwracana jest warto�� \p NULL. 
   */
  const ViNTreeNode *FindSpecPolyh_Con(const ViNodeAddress &Addr) const;

  /*!
   * Udost�pnia w�ze�
   * z hierarchicznego modelu sceny z listy bry� specjalnych na podstawie adresu
   * tego� w�z�a w ca�ej strukturze.
   * Udost�pniany w�ze� mo�e by� bry�� z�o�on� lub elementarn�.
   * Za konwersj� do w�a�ciwej klasy pochodnej danego w�z�a odpowiada
   * programista.
   * \param  Addr - adres w�z�a. Jego sk�adnia musi by� zgodna z wymaganiami
   *                przedstaionymi w opisie klasy ViNodeAddress.
   * \return wska�nik znalezionego w�z�a. Wska�nik na w�ze� udost�pniany jest
   *         jest w trybie sta�ym. Je�li danemu adresowi nie odpowiada\
   *         �aden w�ze�, w�wczas zwracana jest warto�� \p NULL. 
   */
  ViNTreeNode *FindSpecPolyh_Var(const ViNodeAddress &Addr)
    { return (ViNTreeNode*) FindSpecPolyh_Con(Addr); }

  

  /*!
   *  Wylicza wsp�rz�dne globalne wierzcho�k�w i dane pomocnicze (wektory 
   *  normalne �cianek, obrysy bry� elementarnych i z�o�onych) dla 
   *  bry� specjalnych.
   */
  void ComputeGlbVtx_SpecPolyh() { _SpecMultiPolyh.ComputeGlbVtx(); }

  /*!
   *  Wylicza wsp�rz�dne globalne wierzcho�k�w i dane pomocnicze (wektory 
   *  normalne �cianek, obrysy bry� elementarnych i z�o�onych) dla 
   *  bry� normalnych.
   */
  void ComputeGlbVtx_NormPolyh() { _NormMultiPolyh.ComputeGlbVtx(); }

  /*!
   *  Wylicza wsp�rz�dne globalne wierzcho�k�w i dane pomocnicze (wektory 
   *  normalne �cianek, obrysy bry� elementarnych i z�o�onych) dla 
   *  bry� normalnych i specjalnych oraz obrys ca�ej sceny.
   */
  void ComputeGlbVtx();

  /*!
   *  Czyta zawarto�� biblioteki z pliku. Nazwa biblioteki musi by� inna
   *  ni� nazwy bibliotek ju� wczytanych.
   *  \param  FileName - (\b in) nazwa pliku zawieraj�cego opis wczytywanej 
   *                          biblioteki,
   *  \param  ErrMsg - (\b out) w przypadku wyst�pienia b��d�w sk�adni we 
   *                   wczytywanym
   *                   pliku, zwiera on komunikat o b��dzie,
   *  \param  pLibName - (\b out) je�li warto�� wska�nika jest r�na od 
   *                    \p NULL, to w przypadku poprawnie zako�czonego wczytania
   *                   pliku, w obiekcie tym umieszczana zostaj nazwa 
   *                   wczytanej biblioteki. 
   *  \pre \e FileName nie mo�e zawiera� wska�nika \p NULL.
   *  \retval 0 - operacja wczytania zosta�a zako�czona poprawnie,
   */
  int ReadPatteLib( const char *FileName, 
                    ExtString  &ErrMsg, 
                    ExtString  *pLibName = 0L
                  );

   /*!
    * Dodaje now� bibliotek� obiekt�w wzorcowych.
    * \param  pPPLib - wska�nik na now� bibliotek� obiekt�w wzorcowych.
    * \post Nowa biblioteka dodawana jest zawsze na pocz�tek kolejki.
    * \return Je�eli w zbiorze bibliotek nie ma ju� biblioteki o tej
    *          samej nazwie, to jest ona dodawana i zwr�cony zostaje
    *          wska�nik na dodan� bibliotek�. W przypadku przeciwnym
    *          operacja nie jest wykonana i zwracana jest adres 0L.
    *          Warto�� ta jest r�wnie� zwracana w przypadku, gdy
    *          \e pPPLib == 0L.
    */
  ViPattePolyhLib *AddPattePolyhLib(ViPattePolyhLib *pPPLib);


 /*!
  * Wyszukuje w zadanej bibliotece lub we wszystkich bibliotekach danej
  * sceny modelu zwyk�ej bry�y wzorcowej o podanej nazwie.
  * \param  Name - nazwa bry�y wzorcowej,
  * \param  LibName - nazaw biblioteki.
  * \post Je�eli \e LibName == \p NULL, to szukanie realizowane jest
  *       we wszystkich bibliotekach danej sceny. W przypadku przeciwnym
  *       szukanie realizowane jest tylko w bibliotece, kt�rej nazwa
  *       podana zosta�a poprzez parametr \e LibName.
  * \return
  *  wska�nik na znaleziony obiekt, \p NULL - w przypadku przeciwnym.
  * \exception ViException_Patte - zg�aszany jest w przypadku, gdy
  *      w danej scenie nie istnieje bibliotek o podanej nazwie.
  *     Wyj�tek zg�aszany jest z kodem b��du ERRNUM_PATTE__NO_SUCH_LIBRARY.
  */
  const ViPattePolyh *FindNormPattePolyh( const char *Name, 
                                          const char *LibName = 0L
                                        ) const throw(ViException_Patte);

  /*!
   * Wyszukuje w zadanej bibliotece lub we wszystkich bibliotekach danej
   * sceny modelu specjalnej bry�y wzorcowej o podanej nazwie.
   * \param  Name - nazwa bry�y wzorcowej,
   * \param  LibName - nazaw biblioteki.
   * \post Je�eli \e LibName == \p NULL, to szukanie realizowane jest
   *       we wszystkich bibliotekach danej sceny. W przypadku przeciwnym
   *       szukanie realizowane jest tylko w bibliotece, kt�rej nazwa
   *       podana zosta�a poprzez parametr \e LibName.
   * \return
   *  wska�nik na znaleziony obiekt, \p NULL - w przypadku przeciwnym.
   * \exception ViException_Patte - zg�aszany jest w przypadku, gdy
   *      w danej scenie nie istnieje bibliotek o podanej nazwie.
   *     Wyj�tek zg�aszany jest z kodem b��du ERRNUM_PATTE__NO_SUCH_LIBRARY.
   */
  const ViPattePolyh *FindSpecPattePolyh( const char *Name,
                                          const char *LibName = 0L
		                        ) const
                                           throw(ViException_Patte);

  /*!
   * Wyszukuje w zadanej bibliotece lub we wszystkich bibliotekach danej
   * sceny modelu zwyk�ej bry�y wzorcowej o podanej nazwie.
   * Szukana bry�a adresowana jest pe�n� nazw� w formacie:\n
   *
   * \code
   *   nazwa_biblioteki::typ_bry�y::nazwa_bry�y
   * \endcode
   * gdzie \e typ_bry�y = { NORM | SPEC }.
   *
   * Przyk�ad pe�nej nazwy:
   * \code
   *   biblioteka_testowa::Norm::CYLINDER_6
   * \endcode
   *
   * Pierwsza cz�� adresu (tzn. \e nazwa_biblioteki) mo�e zosta� 
   * zast�piona znakiem '*'. W�wczas szukanie realizowane jest
   * we wszystkich bibliotekach danej sceny. W pozosta�ych sk�adnich
   * musz� wyst�pi� tylko nazwy. Nazwa mo�e sk�ada� si� z liter
   * znaku '_' i cyfr. Ponadto nazwa nie mo�e rozpoczyna� si�
   * cyfr�.
   * \param FullName - pe�na nazwa adresuj�ca bry��.
   * \pre Nazwa adresowa musi mie� poprawn� posta�, tzn musi zawiera�
   *      trzy podane wcze�niej sk�adniki.
   * \return wska�nik na bry�� je�li zosta�a znaleziona. W przypadku
   *         przeciwnym zwracany jest adres \p NULL.
   * \exception ViException_Patte - wyj�tek ten jest zg�aszany
   *                gdy przekazana nazwa ma niepoprawn� posta�.
   *            Wyj�tek ten zg�aszany jest z kodem
   *            \p ERRNUM_SYNTAX__BAD_PATTE_ADDR.
   * \exception ViException_Patte - zg�aszany jest w przypadku, gdy
   *  w danej scenie nie istnieje bibliotek o podanej nazwie.
   *  Wyj�tek zg�aszany jest z kodem b��du ERRNUM_PATTE__NO_SUCH_LIBRARY.
   */
  const ViPattePolyh *FindPattePolyh( const char *FullName ) const
             throw (ViException_Patte);

  /*!
   *  Metoda czyta ze strumienia wej�ciowego opis bry�y z�o�onej,
   *  tworzy j� i umieszcza na scenie.
   *  \param istrm - strumie� wej�ciowy,
   *  \param fun - funkcja tworz�ca obiekt o nazwie, kt�ra przekazana
   *               zostanie do niej za pomoc� parametru \e ClassName.
   *  \pre Dla danej sceny musz� by� wczytane biblioteki bry� elementarnych
   *       wykorzystywane w opisie danej bry�y z�o�onej.
   *  \retval 0 - je�li odczyt opisu i utworzenie bry�y zako�czy�y si�
   *              powdzeniem.
   */
  int ReadMultiPolyh( std::istream &istrm, 
                      ViNTreeNode *(*fun)(const char *ClassName) = 0L
                    );


  //----------------- Iteratory bibliotek ----------------------------------

   /*!
    * Udost�pnia iterator do bibliotek obiekt�w wzorcowych
    * (obiekty klasy ViPattePolyhLib). Udost�pniane
    * biblioteki s� zabezpieczone przed modyfikacj�. Metoda przewidziana
    * jest do wywo�ywania dla obiektu sta�ego (\b const).
    */
  ConLibIterator Begin_Lib() const { return _PattePolyhLib_List.Begin(); }

   /*!
    * Udost�pnia iterator do bibliotek obiekt�w wzorcowych
    * (obiekty klasy ViPattePolyhLib). Udost�pniane
    * biblioteki s� zabezpieczone przed modyfikacj�. Metoda mo�e by�
    * wywo�ywana dla obiekt�w \b const i obiekt�w modyfikowalnych.
    */
  ConLibIterator ConBegin_Lib() const
                                   {return _PattePolyhLib_List.ConBegin();}

   /*!
    * Udost�pnia iterator do bibliotek obiekt�w wzorcowych. Udost�pniane
    * biblioteki mog� by� modyfikowane.
    */
  VarLibIterator Begin_Lib() { return _PattePolyhLib_List.Begin(); }

  //--------------- Iteratory zwyk�ych obiekt�w wzorcowych -----------------
   /*!
    *  Udost�pnia iterator zwyk�ych obiekt�w wzorcowych. Udost�pniane
    *  obiekty s� modyfikowalne.
    *  \param LibName - nazwa biblioteki.
    *  \post Je�eli \e LibName = \p NULL, to iterator zostanie udost�pniony
    *    iterator do przegl�dania wszystkich bibliotek. W przypadku przeciwnym
    *    zostanie udost�pniony iterator do przegl�dania wybranej biblioteki.
    *    Je�eli biblioteka o podanej nazwie nie istnieje, to zg�aszany
    *        jest wyj�tek 
    *        \link ViException_OutOfRange ViException_OutOfRange\endlink. 
    */
  VarNormPatteIter Begin_NormPatte(const char *LibName = 0) 
            { return VarNormPatteIter(_PattePolyhLib_List,LibName); }

   /*!
    *  Udost�pnia iterator zwyk�ych obiekt�w wzorcowych. Udost�pniane
    *  obiekty jako sta�e.
    *  \param LibName - nazwa biblioteki.
    *  \post Je�eli \e LibName = \p NULL, to iterator zostanie udost�pniony
    *    iterator do przegl�dania wszystkich bibliotek. W przypadku przeciwnym
    *    zostanie udost�pniony iterator do przegl�dania wybranej biblioteki.
    *    Je�eli biblioteka o podanej nazwie nie istnieje, to zg�aszany
    *        jest wyj�tek 
    *        \link ViException_OutOfRange ViException_OutOfRange\endlink. 
    */
  ConNormPatteIter Begin_NormPatte(const char *LibName = 0) const
            { return ConNormPatteIter(_PattePolyhLib_List,LibName); }

   /*!
    *  Udost�pnia iterator zwyk�ych obiekt�w wzorcowych. Udost�pniane
    *  obiekty jako sta�e.
    *  \param LibName - nazwa biblioteki.
    *  \post Je�eli \e LibName = \p NULL, to iterator zostanie udost�pniony
    *    iterator do przegl�dania wszystkich bibliotek. W przypadku przeciwnym
    *    zostanie udost�pniony iterator do przegl�dania wybranej biblioteki.
    *    Je�eli biblioteka o podanej nazwie nie istnieje, to zg�aszany
    *        jest wyj�tek 
    *        \link ViException_OutOfRange ViException_OutOfRange\endlink. 
    */
   ConNormPatteIter ConBegin_NormPatte(const char *LibName = 0) const
            { return ConNormPatteIter(_PattePolyhLib_List,LibName); }



  //--------------- Iteratory specjalnych obiekt�w wzorcowych ----------------
   /*!
    *  Udost�pnia iterator specjalnych obiekt�w wzorcowych. Udost�pniane
    *  obiekty s� modyfikowalne.
    *  \param LibName - nazwa biblioteki.
    *  \post Je�eli \e LibName = \p NULL, to iterator zostanie udost�pniony
    *    iterator do przegl�dania wszystkich bibliotek. W przypadku przeciwnym
    *    zostanie udost�pniony iterator do przegl�dania wybranej biblioteki.
    *    Je�eli biblioteka o podanej nazwie nie istnieje, to zg�aszany
    *        jest wyj�tek 
    *        \link ViException_OutOfRange ViException_OutOfRange\endlink. 
    */
  VarSpecPatteIter Begin_SpecPatte(const char *LibName = 0) 
            { return VarSpecPatteIter(_PattePolyhLib_List,LibName); }

   /*!
    *  Udost�pnia iterator specjalnych obiekt�w wzorcowych. Udost�pniane
    *  obiekty jako sta�e.
    *  \param LibName - nazwa biblioteki.
    *  \post Je�eli \e LibName = \p NULL, to iterator zostanie udost�pniony
    *    iterator do przegl�dania wszystkich bibliotek. W przypadku przeciwnym
    *    zostanie udost�pniony iterator do przegl�dania wybranej biblioteki.
    *    Je�eli biblioteka o podanej nazwie nie istnieje, to zg�aszany
    *        jest wyj�tek 
    *        \link ViException_OutOfRange ViException_OutOfRange\endlink. 
    */
  ConSpecPatteIter Begin_SpecPatte(const char *LibName = 0) const
             { return ConSpecPatteIter(_PattePolyhLib_List,LibName); }

   /*!
    *  Udost�pnia iterator specjalnych obiekt�w wzorcowych. Udost�pniane
    *  obiekty jako sta�e.
    *  \param LibName - nazwa biblioteki.
    *  \post Je�eli \e LibName = \p NULL, to iterator zostanie udost�pniony
    *    iterator do przegl�dania wszystkich bibliotek. W przypadku przeciwnym
    *    zostanie udost�pniony iterator do przegl�dania wybranej biblioteki.
    *    Je�eli biblioteka o podanej nazwie nie istnieje, to zg�aszany
    *        jest wyj�tek 
    *        \link ViException_OutOfRange ViException_OutOfRange\endlink. 
    */
  ConSpecPatteIter ConBegin_SpecPatte(const char *LibName = 0) const
             { return ConSpecPatteIter(_PattePolyhLib_List,LibName); }
  /*!
   * Udost�pnia iterator normalnych bry� z�o�onych. 
   * Iterowane obiekty udost�pniane s� w trybie \e sta�ym.
   *
   *  Przyk�ad korzystania z iteratora:
   * \code
   * void SceneMultiPolyhIteration(ViScene const &Scene)
   * {
   *   for (ViScene::ConMultiPolyhIter Iter = Scene.ConBegin_NormMultiPolyh();
   *        Iter; ++Iter) {
   *      cout << " Bryla zlozona: " << Iter->GetName() 
   *           << "        Adres wezla: " << Iter->GetNodeAddress() << endl;
   *   }
   *   cout << endl;
   * }
   * \endcode
   */
  ConMultiPolyhIter ConBegin_NormMultiPolyh() const
             { return _NormMultiPolyh.ConBegin_MultiPolyh(); }

  /*!
   * Udost�pnia iterator normalnych bry� z�o�onych. 
   * Iterowane obiekty udost�pniane s� w trybie \e modyfikacji.
   *
   * Przyk�ad korzystania z iteratora:
   * \code
   * void SceneMultiPolyhIteration(ViScene const &Scene)
   * {
   *   for (ViScene::VarMultiPolyhIter Iter = Scene.VarBegin_NormMultiPolyh();
   *        Iter; ++Iter) {
   *      cout << " Bryla zlozona: " << Iter->GetName() 
   *           << "        Adres wezla: " << Iter->GetNodeAddress() << endl;
   *   }
   *   cout << endl;
   * }
   * \endcode
   */
  VarMultiPolyhIter VarBegin_NormMultiPolyh()
             { return _NormMultiPolyh.VarBegin_MultiPolyh(); }


  /*!
   * Udost�pnia iterator specjalnych bry� z�o�onych. 
   * Iterowane obiekty udost�pniane s� w trybie \e sta�ym.
   *
   * Przyk�ad korzystania z iteratora:
   * \code
   * void SceneMultiPolyhIteration(ViScene const &Scene)
   * {
   *   for (ViScene::ConMultiPolyhIter Iter = Scene.ConBegin_SpecMultiPolyh();
   *        Iter; ++Iter) {
   *      cout << " Bryla zlozona: " << Iter->GetName() 
   *           << "        Adres wezla: " << Iter->GetNodeAddress() << endl;
   *   }
   *   cout << endl;
   * }
   * \endcode
   */
  ConMultiPolyhIter ConBegin_SpecMultiPolyh() const
             { return _SpecMultiPolyh.ConBegin_MultiPolyh(); }

  /*!
   * Udost�pnia iterator specjalnych bry� z�o�onych. 
   * Iterowane obiekty udost�pniane s� w trybie \e modyfikacji.
   *
   *  Przyk�ad korzystania z iteratora:
   * \code
   * void SceneMultiPolyhIteration(ViScene const &Scene)
   * {
   *   for (ViScene::VarMultiPolyhIter Iter = Scene.VarBegin_SpecMultiPolyh();
   *        Iter; ++Iter) {
   *      cout << " Bryla zlozona: " << Iter->GetName() 
   *           << "        Adres wezla: " << Iter->GetNodeAddress() << endl;
   *   }
   *   cout << endl;
   * }
   * \endcode
   */
  VarMultiPolyhIter VarBegin_SpecMultiPolyh()
             { return _SpecMultiPolyh.VarBegin_MultiPolyh(); }

};


inline
void ViScene::ComputeGlbVtx()
{
   ComputeGlbVtx_NormPolyh(); 
   ComputeGlbVtx_SpecPolyh();
   _GlbOutlineBox.Reset();
   _GlbOutlineBox.Join(GetList_NormMultiPolyh().GetOutlineBox());
   _GlbOutlineBox.Join(GetList_SpecMultiPolyh().GetOutlineBox());
}



#endif

