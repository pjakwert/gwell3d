#ifndef VISCENE_HH
#define VISCENE_HH

/*! \file viscene.hh
 *  Plik zawiera definicjê klasy \link ViScene ViScene\endlink reprezentuj±c±
 *  pojedyncz± scenê.
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
   *  Definicja tego typu wyliczeniowego pozwala na rozró¿nienie
   *  listy bry³ zwyk³ych i specjalnych.
   */
  typedef  enum { LT_Norm, LT_Spec } MultiPolyhListType;

};


/*!
 *  Klasa reprezentuje pojedyncz± scenê. Jest przystosowana do tego aby byæ
 *  elementem kolejki (dziedziczy wzorzec \link ListItem ListItem\endlink).
 *  Potencjalnie wiêc mo¿na tworzyæ zbiór scen.
 *  
 *  Klasa dysponuje iteratorami pozwalaj±cymi przegl±daæ bry³y z³o¿one
 *  zarówno specjalne jaki i normalne.
 *  
 *  Przyk³ad korzystania z iteratora:
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
    *  Zarz±dca kolejki obiektów wzorcowych. Jedna scena mo¿e zawieraæ
    *  wiele bibliotek. Ka¿da z bibliotek jest identyfikowana poprzez
    *  swoj± nazwê (\link ViPattePolyhLib::_LibName _LibName\endlink).
    */
  ViPatteLibList  _PattePolyhLib_List;

   /*!
    *  Pole jest zarz±dc± kolejki zwyk³ych bry³ z³o¿onych,
    *  tzn. bry³ modeluj±cych obiekty znajduj±ce siê na scenie.
    */
  ViScenePolyhList   _NormMultiPolyh;

   /*!
    *  Pole jest zarz±dc± kolejki specjalnych bry³ z³o¿onych
    *  (np. obiekty reprezntuj±ce ¶wiat³a, sufit, pod³ogê itd.).
    */
  ViScenePolyhList   _SpecMultiPolyh;

  /*!
   * \if brief_private_fields
   *  \brief Obrys wszystkich bry³ sceny.
   * \endif
   *
   *  Pole reprezentuje obrys we wspó³rzêdnych globalnych
   *  wszystkich bry³ danej sceny (specjalnych i normalnych).
   */
   OutlineBox3f      _GlbOutlineBox;

 public:

  /*!
   * \if brief_public_methods
   *  \brief Udostêpnia obrys wszystkich bry³ sceny.
   * \endif
   *
   * Metoda udostêpnia obrys we wspó³rzêdnych globalnych
   *  wszystkich bry³ danej listy. Obrys udostêpniany jest w trybie modyfikacji. 
   */
  OutlineBox3f  &GetOutlineBox() { return _GlbOutlineBox; }

  /*!
   * \if brief_public_methods
   *  \brief Udostêpnia obrys wszystkich bry³ sceny.
   * \endif
   *
   * Metoda udostêpnia obrys we wspó³rzêdnych globalnych
   *  wszystkich bry³ danej listy. Obrys udostêpniany jest w trybie sta³ym. 
   */
  const OutlineBox3f &GetOutlineBox() const { return _GlbOutlineBox; }


  /*!
   *  Usuwa z danej sceny wszystkie bry³y normalne.
   *  Obiekty modeluj±ce bry³y z³o¿one s± niszczone.
   */
  void DeleteAllNormMultiPolyh() 
   {_NormMultiPolyh.List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>::CancelList();}
  /*!
   *  Usuwa z danej sceny wszystkie bry³y specjalne.
   *  Obiekty modeluj±ce bry³y z³o¿one s± niszczone.
   */
  void DeleteAllSpecMultiPolyh() 
   {_SpecMultiPolyh.List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>::CancelList();}
  /*!
   *  Usuwa z danej sceny wszystkie bry³y z³o¿one, zarówno specjalne
   *  jak te¿ normalne.
   *  Obiekty modeluj±ce bry³y z³o¿one s± niszczone.
   */
  void DeleteAllMultiPolyh() 
         { DeleteAllNormMultiPolyh();  DeleteAllSpecMultiPolyh(); }


  /*!
   *  Typ pomocniczy zdefiniowany dla umo¿liwienia odwo³ywania
   *  siê do typu macierzystego poprzez skrócon± nazwê.
   *  Obiekt tej klasy umo¿liwia iteracjê bibliotek obiektów wzorcowych
   *  dla danej sceny. Biblioteki 
   *  (obiekty klasy ViPattePolyhLib) udostêpniane s± jako obiekty sta³e.
   *  
   *  Przyklad wykorzystania:
   * \code
   *  ViScene  Scene;
   *    . . .
   *  // Wy¶wietla nazwy wszystkich bibliotek dla danej sceny.
   * for (ViScene::ConLibIterator Iter = Scene.ConBegin_Lib(); Iter; Iter++) {
   *   cout << "Biblioteka: " << Iter->GetLibName() << endl;
   * }
   * \endcode
   */
  typedef ViPatteLibList::ConLibIterator  ConLibIterator;

  /*!
   *  Typ pomocniczy zdefiniowany dla umo¿liwienia odwo³ywania
   *  siê do typu macierzystego poprzez skrócon± nazwê.
   *  Obiekt tej klasy umo¿liwia iteracjê bibliotek obiektów wzorcowych
   *  dla danej sceny. Biblioteki 
   *  (obiekty klasy ViPattePolyhLib) udostêpniane s± jako obiekty modyfikowalne.
   *  
   *  Przyklad wykorzystania:
   *  \code
   *   ViScene  Scene;
   *     . . .
   *   // Zmienia nazwy bibliotek (normalnie nie nale¿y tego robiæ).
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
    *  Definiuje skrócon± nazwê do typu iteratora kolejki obiektów z³o¿onych.
    *  Iterator ten udostêpnia iterowane obiekty w trybie \b sta³ym.
    */
  typedef ViScenePolyhList::ConMultiPolyhIter  ConMultiPolyhIter;

   /*!
    *  Definiuje skrócon± nazwê do typu iteratora kolejki obiektów z³o¿onych.
    *  Iterator ten udostêpnia iterowane obiekty w trybie \b modyfikowacji.
    */
  typedef ViScenePolyhList::VarMultiPolyhIter  VarMultiPolyhIter;


  /*!
   *  Jest to szablon klasy bazowej dla klas iteratorów bry³ wzorcowych.
   *  \param  LibIterType - typ iteratora bibliotek obiektów wzorcowych. 
   *                 Dopuszczalne warto¶ci: ConLibIterator, VarLibIterator.
   *  \param  PatIterType - typ iteratora obiektów wzorcowych.
   *                 Dopuszczalne warto¶ci: ViPattePolyhLib::ConPatteIter,
   *                                        ViPattePolyhLib::VarPatteIter.
   *  \param  ParenType - nazwa klasy pochodnej.
   *  \param  PolyhType - nazwa typu obiektu wzorcowego.
   *                 Dopuszczalne warto¶ci: ViPattePolyh, const ViPattePolyh.
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
     * Roboczy iterator obiektów wzorcowych dla pojedynczej biblioteki.
     */
    PatIterType  _PatIter;
    /*!
     *  Przechowuje informacjê o tym, czy iteracja realizowana jest tylko
     *  dla jednej biblioteki czy te¿ dla wszystkich.
     */
    bool  _OnlyOne;
    /*!
     *  Status ostatniej operacji (in/de)krementacji.
     *  Warto¶æ \e true oznacza, ¿e operacja siê powiod³a i nastêpny element
     *  kolejki jest dostêpny. W przypadku przeciwnym pole ma warto¶æ 
     *  \e false.
     */
    bool  _OpStatus;
   public:

    /*!
     *  Inicjalizuje obiekt wpisuj±c do pola 
     *  \link PatteIter::_OpStatus PatteIter::_OpStatus\endlink warto¶æ
     *  \p true.
     */
    PatteIter() { _OpStatus = true; }
    /*!
     *  Destruktor jest wirtualny ze wzglêdu na obecno¶æ metod wirtualnych.
     */
    virtual ~PatteIter() {}
    /*!
     * Konwerter udostêpnia status ostatniej operacji (in/de)krementacji
     * (warto¶æ pola 
     *   \link ViScene::VarNormPatteIter::_OpStatus _OpStatus\endlink).
     */
    operator bool () const { return _OpStatus; }

    /*!
     *  Powoduje przej¶cie do poprzedniej bry³y wzorcowej (o ile jest
     *  dostêpna). 
     *  \post Je¿eli operacja zakoñczy³a siê sukcesem (istnia³ poprzedni
     *     element kolejki), to do pola 
     *     \link ViScene::VarNormPatteIter::_OpStatus _OpStatus\endlink
     *     wpisana zostaje warto¶æ \p true. W przypadku przeciwnym wpisana
     *     zostaje warto¶æ \p false.
     */
    virtual ParentType &operator --() = 0;

    /*!
     *  Powoduje przej¶cie do nastêpnej bry³y wzorcowej (o ile jest
     *  dostêpna).
     *  \post Je¿eli operacja zakoñczy³a siê sukcesem (istnia³ poprzedni
     *     element kolejki), to do pola 
     *     \link ViScene::VarNormPatteIter::_OpStatus _OpStatus\endlink
     *     wpisana zostaje warto¶æ \p true. W przypadku przeciwnym wpisana
     *     zostaje warto¶æ \p false.
     */
    virtual ParentType &operator ++() = 0;
    /*!
     *  Powoduje przej¶cie do nastêpnej bry³y wzorcowej (o ile jest
     *  dostêpna).
     *  \warning Stosowanie tego operatora nie jest zalecane, gdy¿
     *           jest "wolniejszy" od operatora przedrostkowego.
     *  \post Je¿eli operacja zakoñczy³a siê sukcesem (istnia³ poprzedni
     *     element kolejki), to do pola 
     *     \link ViScene::VarNormPatteIter::_OpStatus _OpStatus\endlink
     *     wpisana zostaje warto¶æ \p true. W przypadku przeciwnym wpisana
     *     zostaje warto¶æ \p false.
     */
    ParentType &operator ++(int) { return ++*this; }

    /*!
     *  Powoduje przej¶cie do poprzedniej bry³y wzorcowej (o ile jest
     *  dostêpna). 
     *  \warning Stosowanie tego operatora nie jest zalecane, gdy¿
     *           jest "wolniejszy" od operatora przedrostkowego.
     *  \post Je¿eli operacja zakoñczy³a siê sukcesem (istnia³ poprzedni
     *     element kolejki), to do pola 
     *     \link ViScene::VarNormPatteIter::_OpStatus _OpStatus\endlink
     *     wpisana zostaje warto¶æ \p true. W przypadku przeciwnym wpisana
     *     zostaje warto¶æ \p false.
     */
    ParentType &operator --(int) { return --*this; }

    /*!
     * Konwerter ten zwraca adres aktualnego elementu kolejki.
     */
    operator PolyhType* () const { return _PatIter; }

    /*!
     * Udostêpnia referencjê do aktualnego elementu kolejki.
     */
    PolyhType &operator  *() const { return *_PatIter; }
 
    /*!
     * Udostêpnia wska¼nik do aktualnego elementu kolejki.
     */
    PolyhType *operator ->() const { return _PatIter; }

  };





  /*!
   *  Umo¿liwia iterowanie zwyk³ych obiektów wzorcowych bez potrzeby jawnego
   *  odwo³ywania siê do kolejki bibliotek zawieraj±cych te obiekty.
   *  Iterator udostêpnia obiekty w trybie modyfikacji.
   */
  class VarNormPatteIter:
          public PatteIter<VarLibIterator,ViPattePolyhLib::VarPatteIter,
                           VarNormPatteIter,ViPattePolyh> {
   public:
  /*!
    * Inicjalizuje interator do przegl±dania wszystkich bibliotek,
    * lub jednej wybranej.
    * \param  LibList - zarz±dca listy bibliotek obiektów elementarnych,
    * \param  LibName - nazwa biblioteki.
    * \post Je¿eli \e LibName = \p NULL, to iterator zostanie zainicjowany
    *        do przegl±dania wszystkich bibliotek. W przypadku przeciwnym
    *        zostanie on zainicjalizowany do przegl±dania wybranej biblioteki.
    *        Je¿eli biblioteka o podanej nazwie nie istnieje, to zg³aszany
    *        jest wyj±tek 
    *        \link ViException_OutOfRange ViException_OutOfRange\endlink.
    */
    VarNormPatteIter(ViPatteLibList &LibList, const char *LibName = 0L);
   /*!
    *  Powoduje przej¶cie do nastêpnej bry³y wzorcowej (o ile jest
    *  dostêpna).
    *  \post Je¿eli operacja zakoñczy³a siê sukcesem (istnia³ poprzedni
    *     element kolejki), to do pola 
    *     \link ViScene::VarNormPatteIter::_OpStatus _OpStatus\endlink
    *     wpisana zostaje warto¶æ \p true. W przypadku przeciwnym wpisana
    *     zostaje warto¶æ \p false.
    */
    VarNormPatteIter &operator ++();
   /*!
    *  Powoduje przej¶cie do poprzedniej bry³y wzorcowej (o ile jest
    *  dostêpna).
    *  \post Je¿eli operacja zakoñczy³a siê sukcesem (istnia³ poprzedni
    *     element kolejki), to do pola 
    *     \link ViScene::VarNormPatteIter::_OpStatus
    *                              _OpStatus\endlink wpisana zostaje
    *     warto¶æ \p true. W przypadku przeciwnym wpisana zostaje
    *     warto¶æ \p false.
    */
    VarNormPatteIter &operator --();

    /*!
     *  Ustawia wska¼nik roboczy na pierwszy element kolejki.
     */
    void Reset();
  };



  /*!
   *  Umo¿liwia iterowanie zwyk³ych obiektów wzorcowych bez potrzeby jawnego
   *  odwo³ywania siê do kolejki bibliotek zawieraj±cych te obiekty.
   *  Iterator udostêpnia obiekty jako sta³e.
   */
  class ConNormPatteIter:
      public PatteIter<ConLibIterator,ViPattePolyhLib::ConPatteIter,
                       ConNormPatteIter,const ViPattePolyh>  {
   public:

   /*!
    * Inicjalizuje interator do przegl±dania wszystkich bibliotek,
    * lub jednej wybranej.
    * \param  LibList - zarz±dca listy bibliotek obiektów elementarnych,
    * \param  LibName - nazwa biblioteki.
    * \post Je¿eli \e LibName = \p NULL, to iterator zostanie zainicjowany
    *        do przegl±dania wszystkich bibliotek. W przypadku przeciwnym
    *        zostanie on zainicjalizowany do przegl±dania wybranej biblioteki.
    *        Je¿eli biblioteka o podanej nazwie nie istnieje, to zg³aszany
    *        jest wyj±tek 
    *        \link ViException_OutOfRange ViException_OutOfRange\endlink.
    */
    ConNormPatteIter(const ViPatteLibList &LibList, const char *LibName = 0L);

   /*!
    *  Powoduje przej¶cie do nastêpnej bry³y wzorcowej (o ile jest
    *  dostêpna).
    *  \post Je¿eli operacja zakoñczy³a siê sukcesem (istnia³ poprzedni
    *     element kolejki), to do pola 
    *     \link ViScene::ConNormPatteIter::_OpStatus _OpStatus\endlink
    *     wpisana zostaje warto¶æ \p true. W przypadku przeciwnym wpisana
    *     zostaje warto¶æ \p false.
    */
    ConNormPatteIter &operator ++();
   /*!
    *  Powoduje przej¶cie do poprzedniej bry³y wzorcowej (o ile jest
    *  dostêpna).
    *  \post Je¿eli operacja zakoñczy³a siê sukcesem (istnia³ poprzedni
    *     element kolejki), to do pola 
    *     \link ViScene::ConNormPatteIter::_OpStatus
    *                              _OpStatus\endlink wpisana zostaje
    *     warto¶æ \p true. W przypadku przeciwnym wpisana zostaje
    *     warto¶æ \p false.
    */
    ConNormPatteIter &operator --();

    /*!
     *  Ustawia wska¼nik roboczy na pierwszy element kolejki.
     */
    void Reset();
  };




  /*!
   *  Umo¿liwia iterowanie specjalnych obiektów wzorcowych bez potrzeby 
   *  jawnego odwo³ywania siê do kolejki bibliotek zawieraj±cych te obiekty.
   *  Iterator udostêpnia obiekty w trybie modyfikacji.
   */
  class VarSpecPatteIter:
          public PatteIter<VarLibIterator,ViPattePolyhLib::VarPatteIter,
                           VarSpecPatteIter,ViPattePolyh> {
   public:

   /*!
    * Inicjalizuje interator do przegl±dania wszystkich bibliotek,
    * lub jednej wybranej.
    * \param  LibList - zarz±dca listy bibliotek obiektów elementarnych,
    * \param  LibName - nazwa biblioteki.
    * \post Je¿eli \e LibName = \p NULL, to iterator zostanie zainicjowany
    *        do przegl±dania wszystkich bibliotek. W przypadku przeciwnym
    *        zostanie on zainicjalizowany do przegl±dania wybranej biblioteki.
    *        Je¿eli biblioteka o podanej nazwie nie istnieje, to zg³aszany
    *        jest wyj±tek 
    *        \link ViException_OutOfRange ViException_OutOfRange\endlink.
    */
    VarSpecPatteIter(ViPatteLibList &LibList, const char *LibName = 0L);

   /*!
    *  Powoduje przej¶cie do nastêpnej bry³y wzorcowej (o ile jest
    *  dostêpna).
    *  \post Je¿eli operacja zakoñczy³a siê sukcesem (istnia³ poprzedni
    *     element kolejki), to do pola 
    *     \link ViScene::VarSpecPatteIter::_OpStatus _OpStatus\endlink
    *     wpisana zostaje warto¶æ \p true. W przypadku przeciwnym wpisana
    *     zostaje warto¶æ \p false.
    */
    VarSpecPatteIter &operator ++();

   /*!
    *  Powoduje przej¶cie do poprzedniej bry³y wzorcowej (o ile jest
    *  dostêpna).
    *  \post Je¿eli operacja zakoñczy³a siê sukcesem (istnia³ poprzedni
    *     element kolejki), to do pola 
    *     \link ViScene::VarSpecPatteIter::_OpStatus
    *                              _OpStatus\endlink wpisana zostaje
    *     warto¶æ \p true. W przypadku przeciwnym wpisana zostaje
    *     warto¶æ \p false.
    */
    VarSpecPatteIter &operator --();

    /*!
     *  Ustawia wska¼nik roboczy na pierwszy element kolejki.
     */
    void Reset();
  };



  /*!
   *  Umo¿liwia iterowanie specjalnych obiektów wzorcowych bez potrzeby jawnego
   *  odwo³ywania siê do kolejki bibliotek zawieraj±cych te obiekty.
   *  Iterator udostêpnia obiekty jako sta³e.
   */
  class ConSpecPatteIter:
      public PatteIter<ConLibIterator,ViPattePolyhLib::ConPatteIter,
                       ConSpecPatteIter,const ViPattePolyh>  {
   public:
   /*!
    * Inicjalizuje interator do przegl±dania wszystkich bibliotek,
    * lub jednej wybranej.
    * \param  LibList - zarz±dca listy bibliotek obiektów elementarnych,
    * \param  LibName - nazwa biblioteki.
    * \post Je¿eli \e LibName = \p NULL, to iterator zostanie zainicjowany
    *        do przegl±dania wszystkich bibliotek. W przypadku przeciwnym
    *        zostanie on zainicjalizowany do przegl±dania wybranej biblioteki.
    *        Je¿eli biblioteka o podanej nazwie nie istnieje, to zg³aszany
    *        jest wyj±tek 
    *        \link ViException_OutOfRange ViException_OutOfRange\endlink.
    */
    ConSpecPatteIter(const ViPatteLibList &LibList, const char *LibName = 0L);

   /*!
    *  Powoduje przej¶cie do nastêpnej bry³y wzorcowej (o ile jest
    *  dostêpna).
    *  \post Je¿eli operacja zakoñczy³a siê sukcesem (istnia³ poprzedni
    *     element kolejki), to do pola 
    *     \link ViScene::ConSpecPatteIter::_OpStatus _OpStatus\endlink
    *     wpisana zostaje warto¶æ \p true. W przypadku przeciwnym wpisana
    *     zostaje warto¶æ \p false.
    */
    ConSpecPatteIter &operator ++();

   /*!
    *  Powoduje przej¶cie do poprzedniej bry³y wzorcowej (o ile jest
    *  dostêpna).
    *  \post Je¿eli operacja zakoñczy³a siê sukcesem (istnia³ poprzedni
    *     element kolejki), to do pola 
    *     \link ViScene::ConSpecPatteIter::_OpStatus
    *                              _OpStatus\endlink wpisana zostaje
    *     warto¶æ \p true. W przypadku przeciwnym wpisana zostaje
    *     warto¶æ \p false.
    */
    ConSpecPatteIter &operator --();

    /*!
     *  Ustawia wska¼nik roboczy na pierwszy element kolejki.
     */
    void Reset();
  };




   /*!
    *  Inicjalizuje scenê, jako scenê bez nazwy.
    */
  ViScene(): _SceneName("") {}

   /*!
    *  Destruktor jest wirtualny dla zapewnienie zgodno¶ci przy 
    *  dziedziczeniu (klasa, która ma metody wirtualne powinna mieæ
    *  równie¿ wirtualny destruktor).
    */
  virtual ~ViScene() {}

  /*!
   *  Udostêpnia referencjê do listy bibliotek bry³ elementarnych
   *  skojarzonych z dan± scen±.
   */
  const ViPatteLibList &GetList_PatteLibs() const
                                    { return _PattePolyhLib_List; }


  /*!
   *  Udostêpnia referencjê do pola listy normalnych bry³ z³o¿onych.
   */
  const ViScenePolyhList& GetList_NormMultiPolyh() const 
                                           { return _NormMultiPolyh;}

  /*!
   *  Udostêpnia referencjê do pola listy normalnych bry³ z³o¿onych.
   *  Referencja udostêpniana jest w trybie modyfikacji.
   */
  ViScenePolyhList&  UseList_NormMultiPolyh()  { return _NormMultiPolyh;}


  /*!
   *  Udostêpnia referencjê do pola listy specjalnych bry³ z³o¿onych.
   *  \warning Metoda ta ma w nazwie literowkê i w nastêpnej wersji
   *   biblioteki zostanie wycofana. Zamiast niej nale¿y u¿ywaæ metody
   *   \link ViScene::GetList_SpecMultiPolyh 
   *             ViScene::GetList_SpecMultiPolyh\endlink;
   */
  const ViScenePolyhList& GetList_SepcMultiPolyh() const 
                                                { return _SpecMultiPolyh;}

  /*!
   *  Udostêpnia referencjê do pola listy specjalnych bry³ z³o¿onych.
   */
  const ViScenePolyhList& GetList_SpecMultiPolyh() const 
                                                { return _SpecMultiPolyh;}


  /*!
   *  Udostêpnia referencjê do pola listy specjalnych bry³ z³o¿onych.
   *  Referencja udostêpniana jest w trybie modyfikacji.
   */
  ViScenePolyhList&  UseList_SpecMultiPolyh()  { return _SpecMultiPolyh;}




  /*!
   *  Udostêpnia referencjê do pola listy specjalnych bry³ z³o¿onych.
   *  \warning U¿ywanie tej metody nie jest zalecane, gdy¿ zostanie ona
   *  usuniêta nowszej wersji biblioteki. Nale¿y korzystaæ z metody
   *  \link ViScene GetList_SepcMultiPolyh\endlink.
   */
  const ViScenePolyhList& GetSpecMultiPolyh() const { return _SpecMultiPolyh;}

  /*!
   *  Udostêpnia referencjê do pola listy specjalnych bry³ z³o¿onych.
   *  Referencja udostêpniana jest w trybie modyfikacji.
   *  \warning  U¿ywanie tej metody nie jest zalecane, gdy¿ zostanie ona 
   *   usuniêta nowszej wersji biblioteki. Nale¿y korzystaæ z metody
   *   \link ViScene GetList_SepcMultiPolyh\endlink.
   */
  ViScenePolyhList&  UseSpecMultiPolyh()  { return _SpecMultiPolyh;}




   /*!
    *  Udostêpnia nazwê sceny.   
    */
  ExtString const &GetSceneName() const { return _SceneName; }

   /*!
    *  Zmienia nazwê sceny.
    */
  void SetSceneName(char const *Name) { _SceneName = Name; }


  ViMultiPolyh *AddNormMultiPolyh(ViMultiPolyh *pMPolyh)
        { return  _NormMultiPolyh.AddMultiPolyh(pMPolyh); }

  ViMultiPolyh *AddSpecMultiPolyh(ViMultiPolyh *pMPolyh)
        { return  _SpecMultiPolyh.AddMultiPolyh(pMPolyh); }

    /*!
     *  Szuka biblioteki obiektów wzorcowych o zadanej nazwie.
     * \param LibName - nazwa biblioteki obiektów wzorcowych. 
     *                   Nazwa biblioteki brana jest
     *                   z pliku zawieraj±cego opis bibioteki.
     * \return wska¼nik do biblioteki. Je¿eli biblioteka o podanej nazwie
     *         nie istnieje, to zwracany jest wska¼nik \p NULL.
     */
  const ViPattePolyhLib *FindPattePolyhLib(const char *LibName) const
                    { return _PattePolyhLib_List.FindPattePolyhLib(LibName); }

  /*!
   * Udostêpnia wêze³
   * z hierarchicznego modelu sceny z listy bry³ normalnych na podstawie adresu
   * tego¿ wêz³a w ca³ej strukturze.
   * Udostêpniany wêze³ mo¿e byæ bry³± z³o¿on± lub elementarn±.
   * Za konwersjê do w³a¶ciwej klasy pochodnej danego wêz³a odpowiada
   * programista.
   * \param  Addr - adres wêz³a. Jego sk³adnia musi byæ zgodna z wymaganiami
   *                przedstaionymi w opisie klasy ViNodeAddress.
   * \return wska¼nik znalezionego wêz³a. Wska¼nik na wêze³ udostêpniany jest
   *         jest w trybie sta³ym. Je¶li danemu adresowi nie odpowiada\
   *         ¿aden wêze³, wówczas zwracana jest warto¶æ \p NULL. 
   */
  const ViNTreeNode *FindNormPolyh_Con(const ViNodeAddress &Addr) const;

  /*!
   * Udostêpnia wêze³
   * z hierarchicznego modelu sceny z listy bry³ normalnych na podstawie adresu
   * tego¿ wêz³a w ca³ej strukturze.
   * Udostêpniany wêze³ mo¿e byæ bry³± z³o¿on± lub elementarn±.
   * Za konwersjê do w³a¶ciwej klasy pochodnej danego wêz³a odpowiada
   * programista.
   * \param  Addr - adres wêz³a. Jego sk³adnia musi byæ zgodna z wymaganiami
   *                przedstaionymi w opisie klasy ViNodeAddress.
   * \return wska¼nik znalezionego wêz³a. Wska¼nik na wêze³ udostêpniany jest
   *         jest w trybie sta³ym. Je¶li danemu adresowi nie odpowiada\
   *         ¿aden wêze³, wówczas zwracana jest warto¶æ \p NULL. 
   */
  ViNTreeNode *FindNormPolyh_Var(const ViNodeAddress &Addr)
    { return (ViNTreeNode*) FindNormPolyh_Con(Addr); }


  /*!
   * Udostêpnia wêze³
   * z hierarchicznego modelu sceny z listy bry³ specjalnych na podstawie adresu
   * tego¿ wêz³a w ca³ej strukturze.
   * Udostêpniany wêze³ mo¿e byæ bry³± z³o¿on± lub elementarn±.
   * Za konwersjê do w³a¶ciwej klasy pochodnej danego wêz³a odpowiada
   * programista.
   * \param  Addr - adres wêz³a. Jego sk³adnia musi byæ zgodna z wymaganiami
   *                przedstaionymi w opisie klasy ViNodeAddress.
   * \return wska¼nik znalezionego wêz³a. Wska¼nik na wêze³ udostêpniany jest
   *         jest w trybie sta³ym. Je¶li danemu adresowi nie odpowiada\
   *         ¿aden wêze³, wówczas zwracana jest warto¶æ \p NULL. 
   */
  const ViNTreeNode *FindSpecPolyh_Con(const ViNodeAddress &Addr) const;

  /*!
   * Udostêpnia wêze³
   * z hierarchicznego modelu sceny z listy bry³ specjalnych na podstawie adresu
   * tego¿ wêz³a w ca³ej strukturze.
   * Udostêpniany wêze³ mo¿e byæ bry³± z³o¿on± lub elementarn±.
   * Za konwersjê do w³a¶ciwej klasy pochodnej danego wêz³a odpowiada
   * programista.
   * \param  Addr - adres wêz³a. Jego sk³adnia musi byæ zgodna z wymaganiami
   *                przedstaionymi w opisie klasy ViNodeAddress.
   * \return wska¼nik znalezionego wêz³a. Wska¼nik na wêze³ udostêpniany jest
   *         jest w trybie sta³ym. Je¶li danemu adresowi nie odpowiada\
   *         ¿aden wêze³, wówczas zwracana jest warto¶æ \p NULL. 
   */
  ViNTreeNode *FindSpecPolyh_Var(const ViNodeAddress &Addr)
    { return (ViNTreeNode*) FindSpecPolyh_Con(Addr); }

  

  /*!
   *  Wylicza wspó³rzêdne globalne wierzcho³ków i dane pomocnicze (wektory 
   *  normalne ¶cianek, obrysy bry³ elementarnych i z³o¿onych) dla 
   *  bry³ specjalnych.
   */
  void ComputeGlbVtx_SpecPolyh() { _SpecMultiPolyh.ComputeGlbVtx(); }

  /*!
   *  Wylicza wspó³rzêdne globalne wierzcho³ków i dane pomocnicze (wektory 
   *  normalne ¶cianek, obrysy bry³ elementarnych i z³o¿onych) dla 
   *  bry³ normalnych.
   */
  void ComputeGlbVtx_NormPolyh() { _NormMultiPolyh.ComputeGlbVtx(); }

  /*!
   *  Wylicza wspó³rzêdne globalne wierzcho³ków i dane pomocnicze (wektory 
   *  normalne ¶cianek, obrysy bry³ elementarnych i z³o¿onych) dla 
   *  bry³ normalnych i specjalnych oraz obrys ca³ej sceny.
   */
  void ComputeGlbVtx();

  /*!
   *  Czyta zawarto¶æ biblioteki z pliku. Nazwa biblioteki musi byæ inna
   *  ni¿ nazwy bibliotek ju¿ wczytanych.
   *  \param  FileName - (\b in) nazwa pliku zawieraj±cego opis wczytywanej 
   *                          biblioteki,
   *  \param  ErrMsg - (\b out) w przypadku wyst±pienia b³êdów sk³adni we 
   *                   wczytywanym
   *                   pliku, zwiera on komunikat o b³êdzie,
   *  \param  pLibName - (\b out) je¶li warto¶æ wska¼nika jest ró¿na od 
   *                    \p NULL, to w przypadku poprawnie zakoñczonego wczytania
   *                   pliku, w obiekcie tym umieszczana zostaj nazwa 
   *                   wczytanej biblioteki. 
   *  \pre \e FileName nie mo¿e zawieraæ wska¼nika \p NULL.
   *  \retval 0 - operacja wczytania zosta³a zakoñczona poprawnie,
   */
  int ReadPatteLib( const char *FileName, 
                    ExtString  &ErrMsg, 
                    ExtString  *pLibName = 0L
                  );

   /*!
    * Dodaje now± bibliotekê obiektów wzorcowych.
    * \param  pPPLib - wska¼nik na now± bibliotekê obiektów wzorcowych.
    * \post Nowa biblioteka dodawana jest zawsze na pocz±tek kolejki.
    * \return Je¿eli w zbiorze bibliotek nie ma ju¿ biblioteki o tej
    *          samej nazwie, to jest ona dodawana i zwrócony zostaje
    *          wska¼nik na dodan± bibliotekê. W przypadku przeciwnym
    *          operacja nie jest wykonana i zwracana jest adres 0L.
    *          Warto¶æ ta jest równie¿ zwracana w przypadku, gdy
    *          \e pPPLib == 0L.
    */
  ViPattePolyhLib *AddPattePolyhLib(ViPattePolyhLib *pPPLib);


 /*!
  * Wyszukuje w zadanej bibliotece lub we wszystkich bibliotekach danej
  * sceny modelu zwyk³ej bry³y wzorcowej o podanej nazwie.
  * \param  Name - nazwa bry³y wzorcowej,
  * \param  LibName - nazaw biblioteki.
  * \post Je¿eli \e LibName == \p NULL, to szukanie realizowane jest
  *       we wszystkich bibliotekach danej sceny. W przypadku przeciwnym
  *       szukanie realizowane jest tylko w bibliotece, której nazwa
  *       podana zosta³a poprzez parametr \e LibName.
  * \return
  *  wska¼nik na znaleziony obiekt, \p NULL - w przypadku przeciwnym.
  * \exception ViException_Patte - zg³aszany jest w przypadku, gdy
  *      w danej scenie nie istnieje bibliotek o podanej nazwie.
  *     Wyj±tek zg³aszany jest z kodem b³êdu ERRNUM_PATTE__NO_SUCH_LIBRARY.
  */
  const ViPattePolyh *FindNormPattePolyh( const char *Name, 
                                          const char *LibName = 0L
                                        ) const throw(ViException_Patte);

  /*!
   * Wyszukuje w zadanej bibliotece lub we wszystkich bibliotekach danej
   * sceny modelu specjalnej bry³y wzorcowej o podanej nazwie.
   * \param  Name - nazwa bry³y wzorcowej,
   * \param  LibName - nazaw biblioteki.
   * \post Je¿eli \e LibName == \p NULL, to szukanie realizowane jest
   *       we wszystkich bibliotekach danej sceny. W przypadku przeciwnym
   *       szukanie realizowane jest tylko w bibliotece, której nazwa
   *       podana zosta³a poprzez parametr \e LibName.
   * \return
   *  wska¼nik na znaleziony obiekt, \p NULL - w przypadku przeciwnym.
   * \exception ViException_Patte - zg³aszany jest w przypadku, gdy
   *      w danej scenie nie istnieje bibliotek o podanej nazwie.
   *     Wyj±tek zg³aszany jest z kodem b³êdu ERRNUM_PATTE__NO_SUCH_LIBRARY.
   */
  const ViPattePolyh *FindSpecPattePolyh( const char *Name,
                                          const char *LibName = 0L
		                        ) const
                                           throw(ViException_Patte);

  /*!
   * Wyszukuje w zadanej bibliotece lub we wszystkich bibliotekach danej
   * sceny modelu zwyk³ej bry³y wzorcowej o podanej nazwie.
   * Szukana bry³a adresowana jest pe³n± nazw± w formacie:\n
   *
   * \code
   *   nazwa_biblioteki::typ_bry³y::nazwa_bry³y
   * \endcode
   * gdzie \e typ_bry³y = { NORM | SPEC }.
   *
   * Przyk³ad pe³nej nazwy:
   * \code
   *   biblioteka_testowa::Norm::CYLINDER_6
   * \endcode
   *
   * Pierwsza czê¶æ adresu (tzn. \e nazwa_biblioteki) mo¿e zostaæ 
   * zast±piona znakiem '*'. Wówczas szukanie realizowane jest
   * we wszystkich bibliotekach danej sceny. W pozosta³ych sk³adnich
   * musz± wyst±piæ tylko nazwy. Nazwa mo¿e sk³adaæ siê z liter
   * znaku '_' i cyfr. Ponadto nazwa nie mo¿e rozpoczynaæ siê
   * cyfr±.
   * \param FullName - pe³na nazwa adresuj±ca bry³ê.
   * \pre Nazwa adresowa musi mieæ poprawn± postaæ, tzn musi zawieraæ
   *      trzy podane wcze¶niej sk³adniki.
   * \return wska¼nik na bry³ê je¶li zosta³a znaleziona. W przypadku
   *         przeciwnym zwracany jest adres \p NULL.
   * \exception ViException_Patte - wyj±tek ten jest zg³aszany
   *                gdy przekazana nazwa ma niepoprawn± postaæ.
   *            Wyj±tek ten zg³aszany jest z kodem
   *            \p ERRNUM_SYNTAX__BAD_PATTE_ADDR.
   * \exception ViException_Patte - zg³aszany jest w przypadku, gdy
   *  w danej scenie nie istnieje bibliotek o podanej nazwie.
   *  Wyj±tek zg³aszany jest z kodem b³êdu ERRNUM_PATTE__NO_SUCH_LIBRARY.
   */
  const ViPattePolyh *FindPattePolyh( const char *FullName ) const
             throw (ViException_Patte);

  /*!
   *  Metoda czyta ze strumienia wej¶ciowego opis bry³y z³o¿onej,
   *  tworzy j± i umieszcza na scenie.
   *  \param istrm - strumieñ wej¶ciowy,
   *  \param fun - funkcja tworz±ca obiekt o nazwie, która przekazana
   *               zostanie do niej za pomoc± parametru \e ClassName.
   *  \pre Dla danej sceny musz± byæ wczytane biblioteki bry³ elementarnych
   *       wykorzystywane w opisie danej bry³y z³o¿onej.
   *  \retval 0 - je¶li odczyt opisu i utworzenie bry³y zakoñczy³y siê
   *              powdzeniem.
   */
  int ReadMultiPolyh( std::istream &istrm, 
                      ViNTreeNode *(*fun)(const char *ClassName) = 0L
                    );


  //----------------- Iteratory bibliotek ----------------------------------

   /*!
    * Udostêpnia iterator do bibliotek obiektów wzorcowych
    * (obiekty klasy ViPattePolyhLib). Udostêpniane
    * biblioteki s± zabezpieczone przed modyfikacj±. Metoda przewidziana
    * jest do wywo³ywania dla obiektu sta³ego (\b const).
    */
  ConLibIterator Begin_Lib() const { return _PattePolyhLib_List.Begin(); }

   /*!
    * Udostêpnia iterator do bibliotek obiektów wzorcowych
    * (obiekty klasy ViPattePolyhLib). Udostêpniane
    * biblioteki s± zabezpieczone przed modyfikacj±. Metoda mo¿e byæ
    * wywo³ywana dla obiektów \b const i obiektów modyfikowalnych.
    */
  ConLibIterator ConBegin_Lib() const
                                   {return _PattePolyhLib_List.ConBegin();}

   /*!
    * Udostêpnia iterator do bibliotek obiektów wzorcowych. Udostêpniane
    * biblioteki mog± byæ modyfikowane.
    */
  VarLibIterator Begin_Lib() { return _PattePolyhLib_List.Begin(); }

  //--------------- Iteratory zwyk³ych obiektów wzorcowych -----------------
   /*!
    *  Udostêpnia iterator zwyk³ych obiektów wzorcowych. Udostêpniane
    *  obiekty s± modyfikowalne.
    *  \param LibName - nazwa biblioteki.
    *  \post Je¿eli \e LibName = \p NULL, to iterator zostanie udostêpniony
    *    iterator do przegl±dania wszystkich bibliotek. W przypadku przeciwnym
    *    zostanie udostêpniony iterator do przegl±dania wybranej biblioteki.
    *    Je¿eli biblioteka o podanej nazwie nie istnieje, to zg³aszany
    *        jest wyj±tek 
    *        \link ViException_OutOfRange ViException_OutOfRange\endlink. 
    */
  VarNormPatteIter Begin_NormPatte(const char *LibName = 0) 
            { return VarNormPatteIter(_PattePolyhLib_List,LibName); }

   /*!
    *  Udostêpnia iterator zwyk³ych obiektów wzorcowych. Udostêpniane
    *  obiekty jako sta³e.
    *  \param LibName - nazwa biblioteki.
    *  \post Je¿eli \e LibName = \p NULL, to iterator zostanie udostêpniony
    *    iterator do przegl±dania wszystkich bibliotek. W przypadku przeciwnym
    *    zostanie udostêpniony iterator do przegl±dania wybranej biblioteki.
    *    Je¿eli biblioteka o podanej nazwie nie istnieje, to zg³aszany
    *        jest wyj±tek 
    *        \link ViException_OutOfRange ViException_OutOfRange\endlink. 
    */
  ConNormPatteIter Begin_NormPatte(const char *LibName = 0) const
            { return ConNormPatteIter(_PattePolyhLib_List,LibName); }

   /*!
    *  Udostêpnia iterator zwyk³ych obiektów wzorcowych. Udostêpniane
    *  obiekty jako sta³e.
    *  \param LibName - nazwa biblioteki.
    *  \post Je¿eli \e LibName = \p NULL, to iterator zostanie udostêpniony
    *    iterator do przegl±dania wszystkich bibliotek. W przypadku przeciwnym
    *    zostanie udostêpniony iterator do przegl±dania wybranej biblioteki.
    *    Je¿eli biblioteka o podanej nazwie nie istnieje, to zg³aszany
    *        jest wyj±tek 
    *        \link ViException_OutOfRange ViException_OutOfRange\endlink. 
    */
   ConNormPatteIter ConBegin_NormPatte(const char *LibName = 0) const
            { return ConNormPatteIter(_PattePolyhLib_List,LibName); }



  //--------------- Iteratory specjalnych obiektów wzorcowych ----------------
   /*!
    *  Udostêpnia iterator specjalnych obiektów wzorcowych. Udostêpniane
    *  obiekty s± modyfikowalne.
    *  \param LibName - nazwa biblioteki.
    *  \post Je¿eli \e LibName = \p NULL, to iterator zostanie udostêpniony
    *    iterator do przegl±dania wszystkich bibliotek. W przypadku przeciwnym
    *    zostanie udostêpniony iterator do przegl±dania wybranej biblioteki.
    *    Je¿eli biblioteka o podanej nazwie nie istnieje, to zg³aszany
    *        jest wyj±tek 
    *        \link ViException_OutOfRange ViException_OutOfRange\endlink. 
    */
  VarSpecPatteIter Begin_SpecPatte(const char *LibName = 0) 
            { return VarSpecPatteIter(_PattePolyhLib_List,LibName); }

   /*!
    *  Udostêpnia iterator specjalnych obiektów wzorcowych. Udostêpniane
    *  obiekty jako sta³e.
    *  \param LibName - nazwa biblioteki.
    *  \post Je¿eli \e LibName = \p NULL, to iterator zostanie udostêpniony
    *    iterator do przegl±dania wszystkich bibliotek. W przypadku przeciwnym
    *    zostanie udostêpniony iterator do przegl±dania wybranej biblioteki.
    *    Je¿eli biblioteka o podanej nazwie nie istnieje, to zg³aszany
    *        jest wyj±tek 
    *        \link ViException_OutOfRange ViException_OutOfRange\endlink. 
    */
  ConSpecPatteIter Begin_SpecPatte(const char *LibName = 0) const
             { return ConSpecPatteIter(_PattePolyhLib_List,LibName); }

   /*!
    *  Udostêpnia iterator specjalnych obiektów wzorcowych. Udostêpniane
    *  obiekty jako sta³e.
    *  \param LibName - nazwa biblioteki.
    *  \post Je¿eli \e LibName = \p NULL, to iterator zostanie udostêpniony
    *    iterator do przegl±dania wszystkich bibliotek. W przypadku przeciwnym
    *    zostanie udostêpniony iterator do przegl±dania wybranej biblioteki.
    *    Je¿eli biblioteka o podanej nazwie nie istnieje, to zg³aszany
    *        jest wyj±tek 
    *        \link ViException_OutOfRange ViException_OutOfRange\endlink. 
    */
  ConSpecPatteIter ConBegin_SpecPatte(const char *LibName = 0) const
             { return ConSpecPatteIter(_PattePolyhLib_List,LibName); }
  /*!
   * Udostêpnia iterator normalnych bry³ z³o¿onych. 
   * Iterowane obiekty udostêpniane s± w trybie \e sta³ym.
   *
   *  Przyk³ad korzystania z iteratora:
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
   * Udostêpnia iterator normalnych bry³ z³o¿onych. 
   * Iterowane obiekty udostêpniane s± w trybie \e modyfikacji.
   *
   * Przyk³ad korzystania z iteratora:
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
   * Udostêpnia iterator specjalnych bry³ z³o¿onych. 
   * Iterowane obiekty udostêpniane s± w trybie \e sta³ym.
   *
   * Przyk³ad korzystania z iteratora:
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
   * Udostêpnia iterator specjalnych bry³ z³o¿onych. 
   * Iterowane obiekty udostêpniane s± w trybie \e modyfikacji.
   *
   *  Przyk³ad korzystania z iteratora:
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

