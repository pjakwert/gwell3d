#ifndef VIMULTIPOLYH_HH
#define VIMULTIPOLYH_HH

/*!
 *  \file vimultipolyh.hh
 *  \author Bogdan Kreczmer
 *  \date   2004.02
 *
 *  Plik zawiera definicjê klasy ViMultiPolyh, która odpowiedzialna jest
 *  za modelowanie obiektów z³o¿onych z bry³ elementarnych.
 */


#ifdef __GNUG__
#pragma interface
#endif




#include "vintreenode.hh"
#include "twostageiter.hh"
#include "vihierarchyline.hh"
 //==================
 // Ten include jest jeszcze z base/
 //
#include "figqueues-id.h"
#include "outlinebox3f.hh"

// Te stale byc moze trzeba bedzie zmodyfikowac
#define IDOBJECT     11
#define IDDEVICE     12
#define IDRANGE      13

class ViElemePolyh;
        

/*! \class ViMultiPolyh
 * Obiekty tej klasy \e ViMultiPolyh (Complex Polyhedron)
 * reprezentuja zbiory wieloscianów elementarnych modelujacych
 * czê¶ci poszczególnych obiektów na scienie.
 *
 * Klasa zawiera definicjê iteratora bry³ elementarnych
 * (klasa ViMultiPolyh::ConElemePolyhIter).
 *
 *  Przyk³ad korzystania z iteratora:
 *  \code
 * void ElemePolyhIteration(ViMultiPolyh const &MPolyh)
 * {
 *  for (ViMultiPolyh::ConElemePolyhIter Iter = MPolyh.ConBegin_ElemePolyh();
 *       Iter; ++Iter) {
 *   cout << " Bryla elementarna:" << Iter->GetName() << "  Adres wezla: " 
 *        << Iter->GetNodeAddress() << endl;
 *  }
 * }
 * \endcode
 */
DEFPOLYHCLASS(ViMultiPolyh,ViNTreeNode),
                      public ListItem<ViMultiPolyh,IDOBJECT> { //__________
   /*!
    * Metoda jest reimplementacj± metody wirtualnej z klasy 
    * \link ViNTreeNode::GetInheritorType 
    *       ViNTreeNode::GetInheritorType\endlink.
    * Warto¶æ przez ni± zwracana identyfikuje klasê pochodn±.
    * \retval IT_MULTIPOLYH -  warto¶æ identyfikatora dla klasy ViMultiPolyh
    *    (patrz definicja symbolu
    *       \link vintreenode.hh::IT_MULTIPOLYH IT_MULTIPOLYH\endlink).
    */
   int GetInheritorType() const { return IT_MULTIPOLYH; };

  protected:

    /*!
     *  Wierzcho³ki w³a¶ciwego lokalnego uk³adu wspó³rzêdnych wielo¶cianu 
     *  Jest to struktura pomocnicza stworzona z my¶l± o wizualizacji.
     *  
     *  Kolejne elementy tablicy odpowiadaj± punktom: 
     *                                0 - O, 1 - X, 2 - Y, 3 - Z.
     */
   Vector3f         _IndividualCoord[4];


   /*!
     *  Zawiera wspó³rzêdne prostopad³o¶cianu bêd±cego obrysem danego zbioru
     *  bry³ elementarnych.
     *  (w uk³adzie wspó³rzêdnych globalnych). Prostopad³o¶cian tworzony jest
     *  w ten sposób, ¿e jego poszczególne ¶cianki s± równoleg³e do p³aszczyzn
     *  OXY, OXZ, OYZ.
     */
   OutlineBox3f            _GlbOutlineBox;


   /*!
    * \if brief_private_fileds
    *   \brief Zarz±dca kolejki elementów interfejsu sterowania
    * \endif
    *
    * Pole stanowi zarz±dcê kolejki elementów interfejsu do sterowania
    * wybranymi parametrami macierzy transformacji poszczególnych obiektów.
    * W efekcie mo¿na otrzymaæ w ten sposób zbiór kontrolowanych wspó³rzêdnych
    * wewnêtrznych danej struktury geometrycznej.
    */
   ViKinemCtrlSet  _CtrlInterface;





   /*!
    *  Udostêpnia dane dotycz±ce prostopad³o¶ciennego obrysu bry³y
    *  (pole \link ViMultiPolyh::_GlbOutlineBox _GlbOutlineBox\endlink).
    *  Udostêpniane dane mog± byæ modyfikowalne.
    */
   OutlineBox3f &GetOutlineBox_var() { return _GlbOutlineBox; }


  public:
  /*!
   *  Udostêpnia referencjê do podklasy, która zawiera pola i 
   *  metody umo¿liwiaj±ce manipulacjê lokalizacj± danego elementu
   *  w li¶cie (patrz opis szablonu ListItem) bry³
   *  klasyfikowanych jako np. narzêdzia, magazyny, wiertarki itd. 
   *  Metoda ta jest wprowadzona, aby omin±æ problem niejednoznaczno¶ci
   *  odwo³ywania siê do metoda dziedziczonego szablonu ListItem.
   *
   *  Metoda zwraca referencjê w trybie modyfikacji.
   */
   ListItem<ViMultiPolyh,IDOBJECT> &ObjectTypeListItemField()
                                                   { return *this; }


  /*!
   *  Udostêpnia referencjê do podklasy, która zawiera pola i 
   *  metody umo¿liwiaj±ce manipulacjê lokalizacj± danego elementu
   *  w li¶cie (patrz opis szablonu ListItem) bry³
   *  klasyfikowanych jako np. narzêdzia, magazyny, wiertarki itd. 
   *  Metoda ta jest wprowadzona, aby omin±æ problem niejednoznaczno¶ci
   *  odwo³ywania siê do metoda dziedziczonego szablonu ListItem.
   *
   *  Metoda zwraca referencjê w trybie sta³ym.
   */
   const ListItem<ViMultiPolyh,IDOBJECT> &ObjectTypeListItemField() const
                                                   { return *this; }


  /*!
   *  Iterator definiowany przez klasê ElemePolyhIter jest przeznaczony
   *  do iterowania bry³ elementarnych (obiekty klasy ViElemePolyh)
   *  wchodz±cych w sk³ad danej bry³y z³o¿onej (obiekt klasy ViMultiPolyh).
   *  Je¿eli elementem danej bry³y z³o¿onej jest inna bry³a z³o¿ona, to
   *  jej bry³y elementarne bêd± iterowane, jak te¿ bry³y elementarnej jej
   *  sk³adników bêd±cych bry³ami z³o¿onymi.
   *
   *  Przyk³ad korzystania z iteratora:
   * \code
   * void ElemePolyhIteration(ViMultiPolyh const &MPolyh)
   * {
   *  for (ViMultiPolyh::ConElemePolyhIter Iter = MPolyh.ConBegin_ElemePolyh();
   *       Iter; ++Iter) {
   *   cout << " Bryla elementarna:" << Iter->GetName() << "  Adres wezla: " 
   *        << Iter->GetNodeAddress() << endl;
   *  }
   * }
   * \endcode
   *  
   */
   class ConElemePolyhIter:  
      public TwoStageIter <ConElemePolyhIter,const ViElemePolyh,
                         const ViNTreeNode,ViNTreeNode::ConPolyhIter> {

      /*!
       *  Sprawdza czy pomocniczy iterator wskazuje na obiekt klasy
       *  ViElemePolyh.
       *  \retval true - je¶li pomocniczy iterator wskazuje na obiekt klasy
       *                 ViElemePolyh,
       *  \retval false - w przypadku przeciwnym.
       */
      bool IsOK_AuxIter() const 
             { return _AuxIter->GetInheritorType() == IT_ELEMEPOLYH;}
     public:
      /*!
       *  Dokonuje konwersji do wska¼nika na bie¿±cy iterowany element.
       */
      operator const ViElemePolyh *() const 
             { return (const ViElemePolyh*) _AuxIter.Get(); }
      /*!
       *  Inicjalizuje iterator bry³ elementarnych dla danej bry³y z³o¿onej.
       *  \param MPolyh - referencja do bry³y z³o¿onej, dla której ma
       *                  byæ zainicjalizowany iterator.
       */
      ConElemePolyhIter(ViMultiPolyh const &MPolyh):
           TwoStageIter <ConElemePolyhIter,const ViElemePolyh,
                  const ViNTreeNode,ViNTreeNode::ConPolyhIter>(MPolyh)
        { Init(); }
   }; //--------------- ConElemePolyhIter -----------------------------------



 /*!
  *  Iterator definiowany przez klasê ElemePolyhIter jest przeznaczony
  *  do iterowania bry³ elementarnych (obiekty klasy ViElemePolyh)
  *  wchodz±cych w sk³ad danej bry³y z³o¿onej (obiekt klasy ViMultiPolyh).
  *  Je¿eli elementem danej bry³y z³o¿onej jest inna bry³a z³o¿ona, to
  *  jej bry³y elementarne bêd± iterowane, jak te¿ bry³y elementarnej jej
  *  sk³adników bêd±cych bry³ami z³o¿onymi.
  *
  *  Iterator udostêpnia bry³y elementarne w trybie modyfikacji.
  *
  *  Przyk³ad korzystania z iteratora:
  *  \code
  *  void ElemePolyhIteration(ViMultiPolyh const &MPolyh)
  *  {
  *   for (ViMultiPolyh::ConElemePolyhIter Iter = MPolyh.ConBegin_ElemePolyh();
  *        Iter; ++Iter) {
  *    cout << " Bryla elementarna:" << Iter->GetName() << "  Adres wezla: " 
  *         << Iter->GetNodeAddress() << endl;
  *   }
  *  }
  *  \endcode
  */
   class VarElemePolyhIter:  
      public TwoStageIter <VarElemePolyhIter,ViElemePolyh,
                           ViNTreeNode,ViNTreeNode::VarPolyhIter> {

      /*!
       *  Sprawdza czy pomocniczy iterator wskazuje na obiekt klasy
       *  ViElemePolyh.
       *  \retval true - je¶li pomocniczy iterator wskazuje na obiekt klasy
       *                 ViElemePolyh,
       *  \retval false - w przypadku przeciwnym.
       */
      bool IsOK_AuxIter() const 
             { return _AuxIter->GetInheritorType() == IT_ELEMEPOLYH;}
     public:
      /*!
       *  Dokonuje konwersji do wska¼nika na bie¿±cy iterowany element.
       */
      operator ViElemePolyh *() const 
             { return (ViElemePolyh*) _AuxIter.Get(); }
      /*!
       *  Inicjalizuje iterator bry³ elementarnych dla danej bry³y z³o¿onej.
       *  \param MPolyh - referencja do bry³y z³o¿onej, dla której ma
       *                  byæ zainicjalizowany iterator.
       */ 
      VarElemePolyhIter(ViMultiPolyh &MPolyh):
           TwoStageIter <VarElemePolyhIter,ViElemePolyh,
                         ViNTreeNode,ViNTreeNode::VarPolyhIter>(MPolyh)
        { Init(); }
   }; //--------------- VarElemePolyhIter ------------------------------------



    /*!
     *  Udostêpnia wspó³rzêdne (w uk³adzie wspó³rzêdnych globalnych) 
     *  punktu zaczepienia w³a¶ciwego lokalnego uk³adu wspó³rzêdnych bry³y.
     */
   Vector3f const &IndivCoord_O() const { return _IndividualCoord[0]; }

    /*!
     *  Udostêpnia referencjê (mo¿liwa jest modyfikacja) wspó³rzêdnej
     *  (w uk³adzie wspó³rzêdnych globalnych)
     *  punktu zaczepienia w³a¶ciwego lokalnego uk³adu wspó³rzêdnych bry³y.
     */
   Vector3f       &IndivCoord_O() { return _IndividualCoord[0]; }

    /*!
     *  Udostêpnia wspó³rzêdne (w uk³adzie wspó³rzêdnych globalnych) 
     *  punktu koñca wektora
     *  osi \e OX w³a¶ciwego lokalnego uk³adu wspó³rzêdnych bry³y.
     */
   Vector3f const &IndivCoord_X() const { return _IndividualCoord[1]; }

    /*!
     *  Udostêpnia referencjê (mo¿liwa jest modyfikacja) wspó³rzêdnej
     *  (w uk³adzie wspó³rzêdnych globalnych)
     *  punktu koñca wektora
     *  osi \e OX w³a¶ciwego lokalnego uk³adu wspó³rzêdnych bry³y.
     */
   Vector3f       &IndivCoord_X() { return _IndividualCoord[1]; }


    /*!
     *  Udostêpnia wspó³rzêdne (w uk³adzie wspó³rzêdnych globalnych) 
     *  punktu koñca wektora
     *  osi \e OY w³a¶ciwego lokalnego uk³adu wspó³rzêdnych bry³y.
     */
   Vector3f const &IndivCoord_Y() const { return _IndividualCoord[2]; }

    /*!
     *  Udostêpnia referencjê (mo¿liwa jest modyfikacja) wspó³rzêdnej
     *  (w uk³adzie wspó³rzêdnych globalnych)
     *  punktu koñca wektora
     *  osi \e OY w³a¶ciwego lokalnego uk³adu wspó³rzêdnych bry³y.
     */
   Vector3f       &IndivCoord_Y() { return _IndividualCoord[2]; }


    /*!
     *  Udostêpnia wspó³rzêdne (w uk³adzie wspó³rzêdnych globalnych) 
     *  punktu koñca wektora
     *  osi \e OZ w³a¶ciwego lokalnego uk³adu wspó³rzêdnych bry³y.
     */
   Vector3f const &IndivCoord_Z() const { return _IndividualCoord[3]; }

    /*!
     *  Udostêpnia referencjê (mo¿liwa jest modyfikacja) wspó³rzêdnej
     *  (w uk³adzie wspó³rzêdnych globalnych)
     *  punktu koñca wektora
     *  osi \e OZ w³a¶ciwego lokalnego uk³adu wspó³rzêdnych bry³y.
     */
   Vector3f       &IndivCoord_Z() { return _IndividualCoord[3]; }



    /*!
     *  Inicjalizuje wierzcho³ki w³a¶ciwego lokalne uk³adu wspó³rzêdnych.
     *  Punkt zaczepienia ukladu ustawiany jest na wspó³rzêdne (0,0,0), za¶
     *  koñce wektorów osi otrzymuj± wspó³rzêdne (Axis_Lenght,0,0), 
     *  (0,Axis_Lenght,0), (0,0,Axis_Lenght).
     */
   void  InitIndivCoord(float Axis_Length=10);


    /*!
     *  Oblicza globalne 
     *  wspó³rzêdne globalne wierzcho³ków w³a¶ciwego lokalnego uk³adu
     *  wspó³rzêdnych
     *  (pole \link ViMultiPolyh::_IndividualCoord 
     *                                       _IndividualCoord\endlink).
     *  \param M - macierz transformacji z w³a¶ciwego lokalnego uk³adu 
     *         wspó³rzêdnych bry³y do uk³adu globalnego.
     *  \post Obliczone zostaj± warto¶ci wspó³rzêdnych globalnych
     *         wierzcho³ków
     *  w³a¶ciwego lokalnego uk³adu wspó³rzêdnych
     *  (pole \link ViMultiPolyh::_IndividualCoord 
     *                                     _IndividualCoord\endlink).
     */
   void  ComputeCoordGlbVtx(MatrixH3f const &M);



  //---------------- Metody dla iteratorów ---------------------------------
  /*!
   *  Tworzy iterator do przegl±dania wszystkich bry³ elementarnych danej
   *  bry³y z³o¿onej.
   *
   *  Przyk³ad korzystania z iteratora:
   * \code
   * void ElemePolyhIteration(ViMultiPolyh const &MPolyh)
   * {
   *  for (ViMultiPolyh::ConElemePolyhIter Iter = MPolyh.ConBegin_ElemePolyh();
   *       Iter; ++Iter) {
   *   cout << " Bryla elementarna:" << Iter->GetName() << "  Adres wezla: " 
   *        << Iter->GetNodeAddress() << endl;
   *  }
   * }
   * \endcode
   */
   ConElemePolyhIter ConBegin_ElemePolyh() const 
                                        { return ConElemePolyhIter(*this); }


  //---------------- Metody dla iteratorów ---------------------------------
  /*!
   *  Tworzy iterator do przegl±dania wszystkich bry³ elementarnych danej
   *  bry³y z³o¿onej. Iterowane obiekty udostêpniane s± w trybie modyfikacji.
   *
   *  Przyk³ad korzystania z iteratora:
   *  \code
   * void ElemePolyhIteration(ViMultiPolyh &MPolyh)
   * {
   *  for (ViMultiPolyh::VarElemePolyhIter Iter = MPolyh.VarBegin_ElemePolyh();
   *        Iter; ++Iter) {
   *   cout << " Bryla elementarna:" << Iter->GetName() << "  Adres wezla: " 
   *         << Iter->GetNodeAddress() << endl;
   *  }
   * }
   * \endcode
   */
   VarElemePolyhIter VarBegin_ElemePolyh()
                                        { return VarElemePolyhIter(*this); }





   /*!
    *  Metoda udostêpnia informacjê czy zosta³y zdefiniowane jakie¶ elementy
    *  dla interfejsu sterowania.
    */
   bool IsCtrlInterface() const { return _CtrlInterface.IsAny(); }

   /*!
    *  Metoda udostêpnia referencjê do pola definiuj±cego interfejs sterownia.
    *  Referencja udostêpniana jest w trybie sta³ym.
    */
   const ViKinemCtrlSet& GetCtrlInterface() const { return _CtrlInterface; }
   /*!
    *  Metoda udostêpnia referencjê do pola definiuj±cego interfejs sterownia.
    *  Referencja udostêpniana jest w trybie modyfikacji.
    */
   ViKinemCtrlSet& UseCtrlInterface() { return _CtrlInterface; }

   ViKinemCtrlItem *AddCtrlInterface( ViNTreeNode     *pPolyh,
                                      ViMatrix3f          &Mtx,
                                      Vi::TransformType    TransfType,
                                      Vi::Coord3DType      Coord,
                                      TransOrder           TOrder = TO_Before,
                                      Vi::MetricUnit       Unit = Vi::MU_NONE
                                    );                                         


   /*!
    *  Udostêpnia dane dotycz±ce prostopad³o¶ciennego obrysu bry³y
    *  (pole \link ViMultiPolyh::_GlbOutlineBox _GlbOutlineBox\endlink).
    *  Udostêpniane dane nie mog± byæ modyfikowalne.
    *
    *  Metoda ta ma identyczne dzia³anie jak metoda 
    *  \link ViMultiPolyh::GlbOlnBox GlbOlneBox\endlink.
    *  Zalecane jest stosowanie metody 
    *  \link ViMultiPolyh::GlbOlnBox GlbOlneBox\endlink, gdy¿ 
    *  metoda \link ViMultiPolyh::GetOutlineBox GetOutlineBox\endlink
    *  przewidzaiana jest do usuniêcia.
    */
   const OutlineBox3f &GetOutlineBox() const { return _GlbOutlineBox; }

 


   /*! 
    *  Udostêpnia dane dotycz±ce prostopad³o¶ciennego obrysu bry³y
    *  (pole \link ViMultiPolyh::_GlbOutlineBox _GlbOutlineBox\endlink).
    *  Udostêpniane dane nie mog± byæ modyfikowalne.
    *
    *  Metoda ta ma identyczne dzia³anie jak metoda 
    *  \link ViMultiPolyh::GetOutlineBox GetOutlineBox\endlink.
    *  Zosta³a ona wprowadzona aby ujednoliciæ nazywnictwo z klas±
    *  ViElemePolyh. Zalecane jest stosowanie tej metody
    *  zamiast metody \link ViMultiPolyh::GetOutlineBox GetOutlineBox\endlink. 
    */
   OutlineBox3f const &GlbOlnBox() const { return _GlbOutlineBox; }




  /*!
   *  Wylicza wspó³rzêdne globalne wierzcho³ków wszystkich bry³ modelowanych
   *  przez obiekty klasy \link ViElemePolyh ViElemePolyh\endlink, dla 
   *  których obiekt ten jest wspólnym "korzeniem".
   *  Wyznacza równie¿ wspólny prostopad³o¶cienny
   *  obrys (jest on dostêpny poprzez metodê
   *  \link ViMultiPolyh::GetOutlineBox GetOutlineBox\endlink).
   *
   *  \retval 0 - je¶li obliczenia zosta³y przeprowadzone poprawnie.
   *  \retval <0 - w przypadku przeciwnym.
   */
   int ComputeHierAllGlbVtx();


   /*!
    * Metoda zapisuje parametry opisu bry³y zwi±zane tylko z klas±
    * ViElemePolyh (bez klasy bazowej).
    * \param Descr - (\b out) wpisywany jest do tego parametru opis
    *                bry³y.
    * \pre Nie jest gwarantowane, ¿e parametr \e Descr jest pusty.
    *      Dlatego te¿ nale¿y przed wszelkimi wpisami "wyczy¶ciæ" go,
    *      tzn. nale¿y wywo³aæ metodê clear().
    */
   void WriteDescriptionTo(ExtString &Descr) const;


   /*!
    *  Metoda na podstawie opisu parametrów charakterystycznych dla danej
    *  klasy (bez uwzglêdnienia parametrów dziedziczonych) inicjalizuje
    *  odpowiednie pola (przyk³ad sk³adni opisu mo¿na znale¼æ na stronie
    *  \ref odczyt-param "Odczyt parametrów opisu bry³y").
    *  Metoda \e InitWithDesc wykorzystywana jest przez funkcje odczytu
    *  z pliku opisu bry³y i tworzenia oraz inicjalizacji obiektów 
    *  sk³adowych.
    *  \param Descr - (\b in) opis prarametrów charakterystycznych dla danej
    *          klasy (z wy³±czeniem parametrów dziedziczonych).
    */
   void InitWithDescr( const ExtString &Descr );



   /*!
    * Metoda tworzy opis ca³ej bry³y z³o¿onej.
    * \param  ostrm - (\b out) strumieñ wyj¶ciowy, na który kierowany jest
    *                generowany opis ca³ej bry³y z³o¿onej, tzn.
    *                opisy wszystkich jej komponentów.
    *  \param  AType - okre¶la rodzaj k±tów rotacji parametryzuj±cych
    *                podmacierz rotacji dla tranformacji od uk³adu wspó³rzêdnych
    *                rodzica.\n
    *                W tej chwili
    *                obs³ugiwane s± k±ty Eulera oraz k±ty rotacji 
    *                wokó³ osi OX, OY, OZ.
    * \param  AUnit - okre¶la w jakich jednostkach maj± byæ zapisane warto¶ci
    *                k±tów.
    * \param  Margin - ilo¶æ spacji jak± maj± byæ poprzedzone poszczególne
    *                linie opisu parametrów.
    * \param  Margin - ilo¶æ spacji jak± maj± byæ poprzedzone poszczególne
    *                linie opisu parametrów.
    * \retval true - je¿eli opis zosta³ zakoñczony poprawnie.
    * \retval false - gdy utworzenie opisu okaza³o siê niemo¿liwe.
    */
   bool WriteMultiPolyhTo(
                      ostream                 &ostrm, 
                      MatrixH3f::AnglesType    AType      = MatrixH3f::AT_Euler,
                      AngleUnit                AUnit      = AU_Deg,
                      unsigned int             Margin     = 0 
		   ) const;

   /*!
    * Metoda zapisuje opis ca³ej bry³y z³o¿onej do pliku.
    * \param  FileName - (\b in) nazwa pliku, do którego zapisany zostanie
    *                opis bry³y z³o¿onej, tzn.
    *                opisy wszystkich jej komponentów.
    *  \param  AType - okre¶la rodzaj k±tów rotacji parametryzuj±cych
    *                podmacierz rotacji dla tranformacji od uk³adu wspó³rzêdnych
    *                rodzica.\n
    *                W tej chwili
    *                obs³ugiwane s± k±ty Eulera oraz k±ty rotacji 
    *                wokó³ osi OX, OY, OZ.
    * \param  AUnit - okre¶la w jakich jednostkach maj± byæ zapisane warto¶ci
    *                k±tów.
    * \param  Margin - ilo¶æ spacji jak± maj± byæ poprzedzone poszczególne
    *                linie opisu parametrów.
    * \param  Margin - ilo¶æ spacji jak± maj± byæ poprzedzone poszczególne
    *                linie opisu parametrów.
    * \retval 0 - je¿eli opis zosta³ zakoñczony poprawnie.
    * \retval -1 - gdy otwarcie pliku do zapisu okaza³o siê niemo¿liwe.
    * \retval -2 - gdy utworzenie opisu okaza³o siê niemo¿liwe.
    */
   int WriteMultiPolyhToFile(
                      const char *             FileName, 
                      MatrixH3f::AnglesType    AType      = MatrixH3f::AT_Euler,
                      AngleUnit                AUnit      = AU_Deg,
                      unsigned int             Margin     = 0 
		   ) const;


   bool WriteCtrlInterfaceTo(  ostream      &ostrm,
                               unsigned int  Margin
                            ) const;


   /*!
    *  Inicjalizuje obiekt nadaj±c mu nazwê i resetuj±c wszystkie flagi.
    * \param Name - nazwa obiektu.
    * \post Nazwa obiektu zapisana zostaje w polu 
    *   \link ViNTreeNode::_IndivName _IndivName\endlink
    *  dziedziczonego z klasy  ViNTreeNode.
    *  Ponadto stan wszystkich flag zostaje zresetowany.
    */
   ViMultiPolyh(char const *Name = "noname") { SetName(Name); }
   ~ViMultiPolyh() {}
};

#endif
