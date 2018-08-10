#ifndef VIMULTIPOLYH_HH
#define VIMULTIPOLYH_HH

/*!
 *  \file vimultipolyh.hh
 *  \author Bogdan Kreczmer
 *  \date   2004.02
 *
 *  Plik zawiera definicj� klasy ViMultiPolyh, kt�ra odpowiedzialna jest
 *  za modelowanie obiekt�w z�o�onych z bry� elementarnych.
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
 * reprezentuja zbiory wieloscian�w elementarnych modelujacych
 * cz�ci poszczeg�lnych obiekt�w na scienie.
 *
 * Klasa zawiera definicj� iteratora bry� elementarnych
 * (klasa ViMultiPolyh::ConElemePolyhIter).
 *
 *  Przyk�ad korzystania z iteratora:
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
    * Metoda jest reimplementacj� metody wirtualnej z klasy 
    * \link ViNTreeNode::GetInheritorType 
    *       ViNTreeNode::GetInheritorType\endlink.
    * Warto�� przez ni� zwracana identyfikuje klas� pochodn�.
    * \retval IT_MULTIPOLYH -  warto�� identyfikatora dla klasy ViMultiPolyh
    *    (patrz definicja symbolu
    *       \link vintreenode.hh::IT_MULTIPOLYH IT_MULTIPOLYH\endlink).
    */
   int GetInheritorType() const { return IT_MULTIPOLYH; };

  protected:

    /*!
     *  Wierzcho�ki w�a�ciwego lokalnego uk�adu wsp�rz�dnych wielo�cianu 
     *  Jest to struktura pomocnicza stworzona z my�l� o wizualizacji.
     *  
     *  Kolejne elementy tablicy odpowiadaj� punktom: 
     *                                0 - O, 1 - X, 2 - Y, 3 - Z.
     */
   Vector3f         _IndividualCoord[4];


   /*!
     *  Zawiera wsp�rz�dne prostopad�o�cianu b�d�cego obrysem danego zbioru
     *  bry� elementarnych.
     *  (w uk�adzie wsp�rz�dnych globalnych). Prostopad�o�cian tworzony jest
     *  w ten spos�b, �e jego poszczeg�lne �cianki s� r�wnoleg�e do p�aszczyzn
     *  OXY, OXZ, OYZ.
     */
   OutlineBox3f            _GlbOutlineBox;


   /*!
    * \if brief_private_fileds
    *   \brief Zarz�dca kolejki element�w interfejsu sterowania
    * \endif
    *
    * Pole stanowi zarz�dc� kolejki element�w interfejsu do sterowania
    * wybranymi parametrami macierzy transformacji poszczeg�lnych obiekt�w.
    * W efekcie mo�na otrzyma� w ten spos�b zbi�r kontrolowanych wsp�rz�dnych
    * wewn�trznych danej struktury geometrycznej.
    */
   ViKinemCtrlSet  _CtrlInterface;





   /*!
    *  Udost�pnia dane dotycz�ce prostopad�o�ciennego obrysu bry�y
    *  (pole \link ViMultiPolyh::_GlbOutlineBox _GlbOutlineBox\endlink).
    *  Udost�pniane dane mog� by� modyfikowalne.
    */
   OutlineBox3f &GetOutlineBox_var() { return _GlbOutlineBox; }


  public:
  /*!
   *  Udost�pnia referencj� do podklasy, kt�ra zawiera pola i 
   *  metody umo�liwiaj�ce manipulacj� lokalizacj� danego elementu
   *  w li�cie (patrz opis szablonu ListItem) bry�
   *  klasyfikowanych jako np. narz�dzia, magazyny, wiertarki itd. 
   *  Metoda ta jest wprowadzona, aby omin�� problem niejednoznaczno�ci
   *  odwo�ywania si� do metoda dziedziczonego szablonu ListItem.
   *
   *  Metoda zwraca referencj� w trybie modyfikacji.
   */
   ListItem<ViMultiPolyh,IDOBJECT> &ObjectTypeListItemField()
                                                   { return *this; }


  /*!
   *  Udost�pnia referencj� do podklasy, kt�ra zawiera pola i 
   *  metody umo�liwiaj�ce manipulacj� lokalizacj� danego elementu
   *  w li�cie (patrz opis szablonu ListItem) bry�
   *  klasyfikowanych jako np. narz�dzia, magazyny, wiertarki itd. 
   *  Metoda ta jest wprowadzona, aby omin�� problem niejednoznaczno�ci
   *  odwo�ywania si� do metoda dziedziczonego szablonu ListItem.
   *
   *  Metoda zwraca referencj� w trybie sta�ym.
   */
   const ListItem<ViMultiPolyh,IDOBJECT> &ObjectTypeListItemField() const
                                                   { return *this; }


  /*!
   *  Iterator definiowany przez klas� ElemePolyhIter jest przeznaczony
   *  do iterowania bry� elementarnych (obiekty klasy ViElemePolyh)
   *  wchodz�cych w sk�ad danej bry�y z�o�onej (obiekt klasy ViMultiPolyh).
   *  Je�eli elementem danej bry�y z�o�onej jest inna bry�a z�o�ona, to
   *  jej bry�y elementarne b�d� iterowane, jak te� bry�y elementarnej jej
   *  sk�adnik�w b�d�cych bry�ami z�o�onymi.
   *
   *  Przyk�ad korzystania z iteratora:
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
       *  \retval true - je�li pomocniczy iterator wskazuje na obiekt klasy
       *                 ViElemePolyh,
       *  \retval false - w przypadku przeciwnym.
       */
      bool IsOK_AuxIter() const 
             { return _AuxIter->GetInheritorType() == IT_ELEMEPOLYH;}
     public:
      /*!
       *  Dokonuje konwersji do wska�nika na bie��cy iterowany element.
       */
      operator const ViElemePolyh *() const 
             { return (const ViElemePolyh*) _AuxIter.Get(); }
      /*!
       *  Inicjalizuje iterator bry� elementarnych dla danej bry�y z�o�onej.
       *  \param MPolyh - referencja do bry�y z�o�onej, dla kt�rej ma
       *                  by� zainicjalizowany iterator.
       */
      ConElemePolyhIter(ViMultiPolyh const &MPolyh):
           TwoStageIter <ConElemePolyhIter,const ViElemePolyh,
                  const ViNTreeNode,ViNTreeNode::ConPolyhIter>(MPolyh)
        { Init(); }
   }; //--------------- ConElemePolyhIter -----------------------------------



 /*!
  *  Iterator definiowany przez klas� ElemePolyhIter jest przeznaczony
  *  do iterowania bry� elementarnych (obiekty klasy ViElemePolyh)
  *  wchodz�cych w sk�ad danej bry�y z�o�onej (obiekt klasy ViMultiPolyh).
  *  Je�eli elementem danej bry�y z�o�onej jest inna bry�a z�o�ona, to
  *  jej bry�y elementarne b�d� iterowane, jak te� bry�y elementarnej jej
  *  sk�adnik�w b�d�cych bry�ami z�o�onymi.
  *
  *  Iterator udost�pnia bry�y elementarne w trybie modyfikacji.
  *
  *  Przyk�ad korzystania z iteratora:
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
       *  \retval true - je�li pomocniczy iterator wskazuje na obiekt klasy
       *                 ViElemePolyh,
       *  \retval false - w przypadku przeciwnym.
       */
      bool IsOK_AuxIter() const 
             { return _AuxIter->GetInheritorType() == IT_ELEMEPOLYH;}
     public:
      /*!
       *  Dokonuje konwersji do wska�nika na bie��cy iterowany element.
       */
      operator ViElemePolyh *() const 
             { return (ViElemePolyh*) _AuxIter.Get(); }
      /*!
       *  Inicjalizuje iterator bry� elementarnych dla danej bry�y z�o�onej.
       *  \param MPolyh - referencja do bry�y z�o�onej, dla kt�rej ma
       *                  by� zainicjalizowany iterator.
       */ 
      VarElemePolyhIter(ViMultiPolyh &MPolyh):
           TwoStageIter <VarElemePolyhIter,ViElemePolyh,
                         ViNTreeNode,ViNTreeNode::VarPolyhIter>(MPolyh)
        { Init(); }
   }; //--------------- VarElemePolyhIter ------------------------------------



    /*!
     *  Udost�pnia wsp�rz�dne (w uk�adzie wsp�rz�dnych globalnych) 
     *  punktu zaczepienia w�a�ciwego lokalnego uk�adu wsp�rz�dnych bry�y.
     */
   Vector3f const &IndivCoord_O() const { return _IndividualCoord[0]; }

    /*!
     *  Udost�pnia referencj� (mo�liwa jest modyfikacja) wsp�rz�dnej
     *  (w uk�adzie wsp�rz�dnych globalnych)
     *  punktu zaczepienia w�a�ciwego lokalnego uk�adu wsp�rz�dnych bry�y.
     */
   Vector3f       &IndivCoord_O() { return _IndividualCoord[0]; }

    /*!
     *  Udost�pnia wsp�rz�dne (w uk�adzie wsp�rz�dnych globalnych) 
     *  punktu ko�ca wektora
     *  osi \e OX w�a�ciwego lokalnego uk�adu wsp�rz�dnych bry�y.
     */
   Vector3f const &IndivCoord_X() const { return _IndividualCoord[1]; }

    /*!
     *  Udost�pnia referencj� (mo�liwa jest modyfikacja) wsp�rz�dnej
     *  (w uk�adzie wsp�rz�dnych globalnych)
     *  punktu ko�ca wektora
     *  osi \e OX w�a�ciwego lokalnego uk�adu wsp�rz�dnych bry�y.
     */
   Vector3f       &IndivCoord_X() { return _IndividualCoord[1]; }


    /*!
     *  Udost�pnia wsp�rz�dne (w uk�adzie wsp�rz�dnych globalnych) 
     *  punktu ko�ca wektora
     *  osi \e OY w�a�ciwego lokalnego uk�adu wsp�rz�dnych bry�y.
     */
   Vector3f const &IndivCoord_Y() const { return _IndividualCoord[2]; }

    /*!
     *  Udost�pnia referencj� (mo�liwa jest modyfikacja) wsp�rz�dnej
     *  (w uk�adzie wsp�rz�dnych globalnych)
     *  punktu ko�ca wektora
     *  osi \e OY w�a�ciwego lokalnego uk�adu wsp�rz�dnych bry�y.
     */
   Vector3f       &IndivCoord_Y() { return _IndividualCoord[2]; }


    /*!
     *  Udost�pnia wsp�rz�dne (w uk�adzie wsp�rz�dnych globalnych) 
     *  punktu ko�ca wektora
     *  osi \e OZ w�a�ciwego lokalnego uk�adu wsp�rz�dnych bry�y.
     */
   Vector3f const &IndivCoord_Z() const { return _IndividualCoord[3]; }

    /*!
     *  Udost�pnia referencj� (mo�liwa jest modyfikacja) wsp�rz�dnej
     *  (w uk�adzie wsp�rz�dnych globalnych)
     *  punktu ko�ca wektora
     *  osi \e OZ w�a�ciwego lokalnego uk�adu wsp�rz�dnych bry�y.
     */
   Vector3f       &IndivCoord_Z() { return _IndividualCoord[3]; }



    /*!
     *  Inicjalizuje wierzcho�ki w�a�ciwego lokalne uk�adu wsp�rz�dnych.
     *  Punkt zaczepienia ukladu ustawiany jest na wsp�rz�dne (0,0,0), za�
     *  ko�ce wektor�w osi otrzymuj� wsp�rz�dne (Axis_Lenght,0,0), 
     *  (0,Axis_Lenght,0), (0,0,Axis_Lenght).
     */
   void  InitIndivCoord(float Axis_Length=10);


    /*!
     *  Oblicza globalne 
     *  wsp�rz�dne globalne wierzcho�k�w w�a�ciwego lokalnego uk�adu
     *  wsp�rz�dnych
     *  (pole \link ViMultiPolyh::_IndividualCoord 
     *                                       _IndividualCoord\endlink).
     *  \param M - macierz transformacji z w�a�ciwego lokalnego uk�adu 
     *         wsp�rz�dnych bry�y do uk�adu globalnego.
     *  \post Obliczone zostaj� warto�ci wsp�rz�dnych globalnych
     *         wierzcho�k�w
     *  w�a�ciwego lokalnego uk�adu wsp�rz�dnych
     *  (pole \link ViMultiPolyh::_IndividualCoord 
     *                                     _IndividualCoord\endlink).
     */
   void  ComputeCoordGlbVtx(MatrixH3f const &M);



  //---------------- Metody dla iterator�w ---------------------------------
  /*!
   *  Tworzy iterator do przegl�dania wszystkich bry� elementarnych danej
   *  bry�y z�o�onej.
   *
   *  Przyk�ad korzystania z iteratora:
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


  //---------------- Metody dla iterator�w ---------------------------------
  /*!
   *  Tworzy iterator do przegl�dania wszystkich bry� elementarnych danej
   *  bry�y z�o�onej. Iterowane obiekty udost�pniane s� w trybie modyfikacji.
   *
   *  Przyk�ad korzystania z iteratora:
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
    *  Metoda udost�pnia informacj� czy zosta�y zdefiniowane jakie� elementy
    *  dla interfejsu sterowania.
    */
   bool IsCtrlInterface() const { return _CtrlInterface.IsAny(); }

   /*!
    *  Metoda udost�pnia referencj� do pola definiuj�cego interfejs sterownia.
    *  Referencja udost�pniana jest w trybie sta�ym.
    */
   const ViKinemCtrlSet& GetCtrlInterface() const { return _CtrlInterface; }
   /*!
    *  Metoda udost�pnia referencj� do pola definiuj�cego interfejs sterownia.
    *  Referencja udost�pniana jest w trybie modyfikacji.
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
    *  Udost�pnia dane dotycz�ce prostopad�o�ciennego obrysu bry�y
    *  (pole \link ViMultiPolyh::_GlbOutlineBox _GlbOutlineBox\endlink).
    *  Udost�pniane dane nie mog� by� modyfikowalne.
    *
    *  Metoda ta ma identyczne dzia�anie jak metoda 
    *  \link ViMultiPolyh::GlbOlnBox GlbOlneBox\endlink.
    *  Zalecane jest stosowanie metody 
    *  \link ViMultiPolyh::GlbOlnBox GlbOlneBox\endlink, gdy� 
    *  metoda \link ViMultiPolyh::GetOutlineBox GetOutlineBox\endlink
    *  przewidzaiana jest do usuni�cia.
    */
   const OutlineBox3f &GetOutlineBox() const { return _GlbOutlineBox; }

 


   /*! 
    *  Udost�pnia dane dotycz�ce prostopad�o�ciennego obrysu bry�y
    *  (pole \link ViMultiPolyh::_GlbOutlineBox _GlbOutlineBox\endlink).
    *  Udost�pniane dane nie mog� by� modyfikowalne.
    *
    *  Metoda ta ma identyczne dzia�anie jak metoda 
    *  \link ViMultiPolyh::GetOutlineBox GetOutlineBox\endlink.
    *  Zosta�a ona wprowadzona aby ujednolici� nazywnictwo z klas�
    *  ViElemePolyh. Zalecane jest stosowanie tej metody
    *  zamiast metody \link ViMultiPolyh::GetOutlineBox GetOutlineBox\endlink. 
    */
   OutlineBox3f const &GlbOlnBox() const { return _GlbOutlineBox; }




  /*!
   *  Wylicza wsp�rz�dne globalne wierzcho�k�w wszystkich bry� modelowanych
   *  przez obiekty klasy \link ViElemePolyh ViElemePolyh\endlink, dla 
   *  kt�rych obiekt ten jest wsp�lnym "korzeniem".
   *  Wyznacza r�wnie� wsp�lny prostopad�o�cienny
   *  obrys (jest on dost�pny poprzez metod�
   *  \link ViMultiPolyh::GetOutlineBox GetOutlineBox\endlink).
   *
   *  \retval 0 - je�li obliczenia zosta�y przeprowadzone poprawnie.
   *  \retval <0 - w przypadku przeciwnym.
   */
   int ComputeHierAllGlbVtx();


   /*!
    * Metoda zapisuje parametry opisu bry�y zwi�zane tylko z klas�
    * ViElemePolyh (bez klasy bazowej).
    * \param Descr - (\b out) wpisywany jest do tego parametru opis
    *                bry�y.
    * \pre Nie jest gwarantowane, �e parametr \e Descr jest pusty.
    *      Dlatego te� nale�y przed wszelkimi wpisami "wyczy�ci�" go,
    *      tzn. nale�y wywo�a� metod� clear().
    */
   void WriteDescriptionTo(ExtString &Descr) const;


   /*!
    *  Metoda na podstawie opisu parametr�w charakterystycznych dla danej
    *  klasy (bez uwzgl�dnienia parametr�w dziedziczonych) inicjalizuje
    *  odpowiednie pola (przyk�ad sk�adni opisu mo�na znale�� na stronie
    *  \ref odczyt-param "Odczyt parametr�w opisu bry�y").
    *  Metoda \e InitWithDesc wykorzystywana jest przez funkcje odczytu
    *  z pliku opisu bry�y i tworzenia oraz inicjalizacji obiekt�w 
    *  sk�adowych.
    *  \param Descr - (\b in) opis prarametr�w charakterystycznych dla danej
    *          klasy (z wy��czeniem parametr�w dziedziczonych).
    */
   void InitWithDescr( const ExtString &Descr );



   /*!
    * Metoda tworzy opis ca�ej bry�y z�o�onej.
    * \param  ostrm - (\b out) strumie� wyj�ciowy, na kt�ry kierowany jest
    *                generowany opis ca�ej bry�y z�o�onej, tzn.
    *                opisy wszystkich jej komponent�w.
    *  \param  AType - okre�la rodzaj k�t�w rotacji parametryzuj�cych
    *                podmacierz rotacji dla tranformacji od uk�adu wsp�rz�dnych
    *                rodzica.\n
    *                W tej chwili
    *                obs�ugiwane s� k�ty Eulera oraz k�ty rotacji 
    *                wok� osi OX, OY, OZ.
    * \param  AUnit - okre�la w jakich jednostkach maj� by� zapisane warto�ci
    *                k�t�w.
    * \param  Margin - ilo�� spacji jak� maj� by� poprzedzone poszczeg�lne
    *                linie opisu parametr�w.
    * \param  Margin - ilo�� spacji jak� maj� by� poprzedzone poszczeg�lne
    *                linie opisu parametr�w.
    * \retval true - je�eli opis zosta� zako�czony poprawnie.
    * \retval false - gdy utworzenie opisu okaza�o si� niemo�liwe.
    */
   bool WriteMultiPolyhTo(
                      ostream                 &ostrm, 
                      MatrixH3f::AnglesType    AType      = MatrixH3f::AT_Euler,
                      AngleUnit                AUnit      = AU_Deg,
                      unsigned int             Margin     = 0 
		   ) const;

   /*!
    * Metoda zapisuje opis ca�ej bry�y z�o�onej do pliku.
    * \param  FileName - (\b in) nazwa pliku, do kt�rego zapisany zostanie
    *                opis bry�y z�o�onej, tzn.
    *                opisy wszystkich jej komponent�w.
    *  \param  AType - okre�la rodzaj k�t�w rotacji parametryzuj�cych
    *                podmacierz rotacji dla tranformacji od uk�adu wsp�rz�dnych
    *                rodzica.\n
    *                W tej chwili
    *                obs�ugiwane s� k�ty Eulera oraz k�ty rotacji 
    *                wok� osi OX, OY, OZ.
    * \param  AUnit - okre�la w jakich jednostkach maj� by� zapisane warto�ci
    *                k�t�w.
    * \param  Margin - ilo�� spacji jak� maj� by� poprzedzone poszczeg�lne
    *                linie opisu parametr�w.
    * \param  Margin - ilo�� spacji jak� maj� by� poprzedzone poszczeg�lne
    *                linie opisu parametr�w.
    * \retval 0 - je�eli opis zosta� zako�czony poprawnie.
    * \retval -1 - gdy otwarcie pliku do zapisu okaza�o si� niemo�liwe.
    * \retval -2 - gdy utworzenie opisu okaza�o si� niemo�liwe.
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
    *  Inicjalizuje obiekt nadaj�c mu nazw� i resetuj�c wszystkie flagi.
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
