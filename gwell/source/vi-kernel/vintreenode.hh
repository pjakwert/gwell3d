#ifndef VIPOLYHHIERLIST_HH
#define VIPOLYHHIERLIST_HH

/*! \file vintreenode.hh
 *  Plik zawiera definicj� klasy \link ViNTreeNode ViNTreeNode\endlink,
 *  kt�ra jest sercem struktury drzewiastej pozwlaj�cej modelowa� otwarte
 *  �a�cuchy kinematyczne.
 *
 *  \author  Bogdan Kreczmer
 *  \date    2003.11
 */


#ifdef __GNUG__
#pragma interface
#pragma implementation
#endif


#include "extstring.hh"
#include "listque.hh"
#include "figqueues-id.h"
#include "extstring.hh"
#include "vivalidflags.hh"
#include "matrixh3f.hh"
#include "baseiterator.hh"
#include "vikinemctrl.hh"
#include "vimatrix3f.hh"


class MatrixH3f;
class ViElemePolyh;
class ViNodeAddress;
class OutlineBox3f;
class ViNodeDescr;
class ViElemePolyh;
class ViMultiPolyh;

/*!
 * Identyfikator dla klasy ViNTreeNode.
 */
#define IT_MULTITREENODE    -1

/*!
 * Identyfikuje klas� pochodn� ViElemePolyh wzgl�dem klasy bazowej
 * ViNTreeNode. Klasa ViElemePolyh reimplementuje metod�
 * \link ViNTreeNode::GetInheritorType GetInheritorType\endlink.
 */
#define  IT_ELEMEPOLYH       1
/*!
 * Identyfikuje klas� pochodn� ViMultiPolyh wzgl�dem klasy bazowej
 * ViNTreeNode. Klasa ViMultiPolyh reimplementuje metod�
 * \link ViNTreeNode::GetInheritorType GetInheritorType\endlink.
 */
#define  IT_MULTIPOLYH       2
/*!
 * Identyfikuje klas� pochodn� ViScenePolyhList wzgl�dem klasy bazowej
 * ViNTreeNode. Klasa ViMultiPolyh reimplementuje metod�
 * \link ViNTreeNode::GetInheritorType GetInheritorType\endlink.
 */
#define  IT_SCENEPOLYHLIST   3


/*!
 *  Definicja typu ma znaczenie pomocnicze. Reprezentuje on
 *  zarz�dc� listy potomk�w danego w�z�a n-drzewa.
 *  Klasa okre�lana nazw� tego typu jest dziedziczona
 *  przez klas� ViNTreeNode.
 */
typedef List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>  ViDescList;

/*!
 *  Definicja typu ma znaczenie pomocnicze. Reprezentuje on
 *  zarz�dc� kolejki element�w interfejsu sterowania zwi�zanych
 *  z dan� bry��. Klasa okre�lana nazw� tego typu jest dziedziczona
 *  przez klas� ViNTreeNode.
 *  Programista nie powinien odwo�ywa� si� bezpo�rednio
 *  do metod tej listy. Konstrukcja jest wprowadzona dla zachowania
 *  integralno�ci struktury danych.
 */
typedef List<ViKinemCtrlItem,ID_KINEMCTRL_NTREENODE> ViCtrlInterfList;

/*!
 * Klasa ta jest podstaw� drzewiastej struktury powi�za� obiekt�w klas,
 * kt�re j� dziedzicz� (tzn. \link ViElemePolyh ViElemePolyh\endlink,
 *  \link ViMultiPolyh ViMultiPolyh\endlink)
 *
 * Jako podklasy zdefiniowane s� klasy iterator�w
 * ViNTreeNode::ConPolyhIter i ViNTreeNode::VarPolyhIter.
 * Umo�liwiaj� one przegl�d ca�ego drzewa powi�za� obiekt�w w porz�dku
 * \e preorder.
 * Pierwsza z wymienionych klas udost�pnia przegl�dane obiekty w trybie
 * \e sta�ym, za� drugi w trybie \e modyfikacji.
 * Opisywane iteratory tworzone s� przez metody 
 * \link ViNTreeNode::ConBegin_PolyhHierList
 *                   ConBegin_PolyhHierList\endlink i
 * \link ViNTreeNode::VarBegin_PolyhHierList
 *                   VarBegin_PolyhHierList\endlink.
 *
 * Przyk�ad u�ycia iteratora ViNTreeNode::ConBegin_Polyh:
 * \code
 * void PolyhHierListIteration(ViMultiPolyh const &MPolyh)
 * {
 *  for (ViNTreeNode::ConPolyhIter Iter = MPolyh.ConBegin_PolyhHierList();
 *         Iter; ++Iter) {
 *     cout << " Jadro obiektu:" << Iter->GetName() 
 *          << "  Adres wezla: " << Iter->GetNodeAddress() << endl;
 *  }
 * }
 * \endcode
 */
class ViNTreeNode: 
       public ViDescList,
       public ListItem<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>,
       public List<ViKinemCtrlItem,ID_KINEMCTRL_NTREENODE>,
       protected ViValidFlags
 {
   friend class ViKinemCtrlItem;

   /*!
    *  Klasa ta pe�ni rol� pomocnicz� i grupuje struktury danych
    *  wykorzystywane na etapie zapisywania parametr�w opisu bry�y
    *  do bufora znakowego.
    */
   class ParamDescrBuff {
     /*!
      *  Bufor znakowy wykorzystywany do zapisu wybranych parametr�w.
      */
      ExtString _Buffer;
     /*!
      *  Przechowuje informacj� o typie k�t�w opisuj�cych macierz
      *  rotacji.
      */
      MatrixH3f::AnglesType    _AngType;
     /*!
      *  Przechowuje informacj� o rodzaju jednostek, w kt�rych wyra�one
      *  s� k�ty (stopnie lub radiany).
      */
      AngleUnit                _AngUnit;

    public:

     /*!
      *  Udost�pnia zawarto�� bufora znakowego.
      */
      const char *Get() const { return _Buffer; }
     /*!
      *  Udost�pnia bufor znakowy do modyfikacji.
      */
      ExtString&  Use() { return _Buffer; }
     /*!
      * Zmienia informacj� o typie k�t�w rotacji.
      * \param AType - nowa warto�� dla okre�lenia typ�w k�t�w rotacji.
      * \post Do pola 
      *   \link ViNTreeNode::ParamDescrBuff::_AngType _AngType\endlink
      *   wpisana zostaje nowa warto�� przekazana przez parametr \e AType.
      */
     void SetAngType(MatrixH3f::AnglesType AType) { _AngType = AType; }
     /*!
      * Udost�pnia warto�� pola
      * \link ViNTreeNode::ParamDescrBuff::_AngType _AngType\endlink 
      * okre�laj�c� typ k�t�w rotacji.
      */
     MatrixH3f::AnglesType GetAngType() const { return _AngType; }

     /*!
      * Zmienia informacj� o rodzaju jednostek, w kt�rych wyra�one
      * s� k�ty.
      * \param AUnit - nowa warto�� dla okre�lenia typ�w k�t�w rotacji.
      * \post Do pola 
      *   \link ViNTreeNode::ParamDescrBuff::_AngUnit _AngUnit\endlink
      *   wpisana zostaje nowa warto�� przekazana przez parametr \e AUnit.
      */
     void SetAngUnit(AngleUnit AUnit) { _AngUnit = AUnit; }
     /*!
      * Udost�pnia warto�� pola
      * \link ViNTreeNode::ParamDescrBuff::_AngUnit _AngUnit\endlink 
      * okre�laj�c� rodzaj jednostek k�t�w rotacji.
      */
     AngleUnit GetAngUnit() const { return _AngUnit; }

     /*!
      *  Inicjalizuje zawarto�� bufora znakowego jako pust�, 
      *  typ k�t�w jako k�ty Eulera oraz jednostki, w kt�rych
      *  wyra�one s� k�ty jako stopnie.
      */
      ParamDescrBuff() { _AngType = MatrixH3f::AT_Euler;  _AngUnit = AU_Deg; }
   };

   /*!
    *  Pole jest wykorzystywane jako bufor w operacjach zapisu.
    */
   static ParamDescrBuff _TmpBuff;

   /*!
    * Pole przechowuje nazw� w�z�a. S�u�y ona do jej 
    * identyfikacji. Powinna ona by� unikalna
    * w ramach danej �cie�ki drzewiastej struktury obiektu
    * z�o�onego. Stanowi ona nazw� w�z�a w tej strukturze
    *
    * Nie zak�ada si�, �e wym�g ten musi by�
    * bezwzgl�dnie spe�niony. Jednak jego niespe�nienie mo�e
    * prowadzi� do niejednoznaczno�ci przy zewn�trznych poleceniach
    * manipulowania bry��. 
    */
  ExtString  _IndivName;

   /*!
    *  Zawiera macierz transformacji do uk�adu wsp�rz�dnych rodzica, tzn.
    *  w�z�a w strukturze drzewiastej, kt�ry znajduje si� bezpo�rednio
    *  nad w�z�em, kt�ry jest rozwa�anym tu obiektem.
    */
  ViMatrix3f  _Transf2ParentCoord; 


   /*!
    *  Metoda umo�liwia udost�pnia bufor zapisu dla operacji modyfikacji
    *  jego zawarto�ci.
    *  Metoda przeznaczona ona jest do wykorzystania przy operacjach zapisu
    *  i odczytu plik�w z opisem bry�.
    */
   static ExtString &UseBuff() { return _TmpBuff.Use(); }


 protected:

   void BindWithCtrlInterfaceItem(ViKinemCtrlItem *pCItem);

   /*!
    * Uniewa�nia flag� dla struktur zale�nych do wsp�rz�dnych wierzcho�k�w
    * dla dowolnego widoku. Operacja wykonywana tylko dla danego w�z�a.
    */
   void ValidFlag_ResetDependedOnViewVtx() { VF_ResetDependedOnViewVtx(); }


   /*!
    *  Metoda umo�liwia zapisanie tekstu do bufora.
    *  Przeznaczona ona jest do wykorzystania przy operacjach zapisu
    *  i odczytu plik�w z opisem bry�.
    *  \param Str - �a�cuch znak�w, kt�ry ma by� zapisany do bufora.
    */
   static void WriteToBuff(const char *Str) { _TmpBuff.Use() << Str; }

   /*!
    *  Metoda umo�liwia udost�pnia bufor zapisu.
    *  Przeznaczona ona jest do wykorzystania przy operacjach zapisu
    *  i odczytu plik�w z opisem bry�.
    */
   static ExtString const &GetBuff() { return _TmpBuff.Use(); }


   /*!
    *  Metoda zapisuje parametry bry�y, kt�re przechowywane s� w obiekcie
    *  klas ViNTreeNode. Klasy dziedzicz�ce ViNTreeNode musz� 
    *  r�wnie� implementowa� metod� o tej nazwie. Oczekuje si�, �e zapis
    *  parametr�w rozpoczyna si� od pierwszej kolumny. Wiersze tekstu
    *  rozdzielane s� znakiem przej�cia do nowej linii.\n
    *  Zapis parametr�w musi objemowa� tylko i wy��cznie parametry zwi�zane
    *  z definicj� danej klasy, a nie klas bazowych.
    *  \param  Descr - (\b out) do bufora wpisywany jest zestaw parametr�w
    *                 opisuj�cych dan� bry��.
    */
   void WriteDescriptionTo(ExtString &Descr) const;

   /*!
    *  Metoda jest przeznaczona do zainicjalizowania zapisu zapisu 
    *  wszystkich parametr�w opisu bry�y. Jest ona redefiniowana w ka�dej
    *  z klas dziedzicz�cych klas� ViNTreeNode zdefiniowanych
    *  poprzez makro 
    *  \link vihierarchyline.hh::DEFPOLYHCLASS DEFPOLYHCLASS\endlink.
    *  Metoda \e WriteAllParamToBuff jest automatycznie redefiniowana
    *  poprzez zastosowanie szablonu ViHierarchyLine.
    *  \see vihierarchyline.hh::DEFPOLYHCLASS
    *  \see  ViHierarchyLine::WriteAllParamToBuff
    *  \param Margin - wielko�� lewego marginesu (ilo�� spacji jaka 
    *                 ma by� wstawiona przed zapisem ka�dej z linii
    *                 opisu parametr�w).
    */
   virtual void WriteAllParamToBuff(unsigned int Margin) const { }

 public:


   /*!
    * Udost�pnia pierwszego potomka. Jest on udost�pniany w trybie 
    * modyfikacji.
    *
    * Metoda realizuej bezpo�redni dost�p do listy potomk�w z pomini�ciem 
    * iterator�w.
    */
   ViNTreeNode *FirstDesc() 
     { return List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>::First(); }

   /*!
    * Udost�pnia pierwszego potomka. Jest on udost�pniany w trybie sta�ym.
    *
    * Metoda realizuej bezpo�redni dost�p do listy potomk�w z pomini�ciem 
    * iterator�w.
    */
   const ViNTreeNode *FirstDesc() const
     { return List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>::First(); }
   /*!
    *  Udost�pnia nast�pnego potomka z listy w�z��w, do kt�rej nale�y dany
    *  w�ze�.
    *  Potomek udost�pniany jest w trybie modyfikacji.
    *
    * Metoda realizuej bezpo�redni dost�p do listy potomk�w z pomini�ciem 
    * iterator�w.
    */
   ViNTreeNode *NextNode() 
     { return ListItem<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>::Next(); }

   /*!
    *  Udost�pnia nast�pnego potomka z listy w�z��w, do kt�rej nale�y dany
    *  w�ze�.
    *  Potomek udost�pniany jest w trybie sta�ym.
    *
    * Metoda realizuej bezpo�redni dost�p do listy potomk�w z pomini�ciem 
    * iterator�w.
    */
   const ViNTreeNode *NextNode() const
     { return ListItem<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>::Next(); }



  /*!
   *  Udost�pnia referencj� do podklasy, kt�ra zawiera pola i 
   *  metody umo�liwiaj�ce manipulacj� lokalizacj� danego elementu
   *  w li�cie (patrz opis szablonu ListItem). Metoda ta na poziomie
   *  klasy ViNTreeNode nie ma zastosowania. Przydaje si� ona
   *  w klasach, kt�re dziedzicz� klas� ViNTreeNode oraz dodatkowa
   *  samodzieln� klas� utworzon� z szablonu ListItem (tak jest np.
   *  w przypadku klasy ViMultiPolyh).
   *  W takich sytuacjach metoda ta umo�liwia omini�cie 
   *  niejednoznaczon�ci przy odwo�ywaniu si� do metod szablon�w ListItem.
   *
   *  Metoda zwraca referencj� w trybie modyfikacji.
   */
   ListItem<ViNTreeNode,IDPRIMITIVE,ViNTreeNode> &
                              PolyhHierListItemField() { return *this; }


  /*!
   *  Udost�pnia referencj� do podklasy, kt�ra zawiera pola i 
   *  metody umo�liwiaj�ce manipulacj� lokalizacj� danego elementu
   *  w li�cie (patrz opis szablonu ListItem). Metoda ta na poziomie
   *  klasy ViNTreeNode nie ma zastosowania. Przydaje si� ona
   *  w klasach, kt�re dziedzicz� klas� ViNTreeNode oraz dodatkowa
   *  samodzieln� klas� utworzon� z szablonu ListItem (tak jest np.
   *  w przypadku klasy ViMultiPolyh).
   *  W takich sytuacjach metoda ta umo�liwia omini�cie 
   *  niejednoznaczon�ci przy odwo�ywaniu si� do metod szablon�w ListItem.
   *
   *  Metoda zwraca referencj� w trybie modyfikacji.
   */
   const ListItem<ViNTreeNode,IDPRIMITIVE,ViNTreeNode> &
                             PolyhHierListItemField() const { return *this; }

  /*!
   *  Zwraca nazw� klasy pochodnej. Metoda wykorzystywana jest
   *  przez metody zapisu parametr�w bry�y do oznaczania i identyfikacji
   *  poszczeg�lnych sekcji zapisu.
   */
   const char *GetClassName() const { return "ViNTreeNode"; }

  /*!
   *  Zwraca nazw� finalnej klasy danego obiektu. Przy tworzeniu
   *  w�asnej klasy metody tej nie nale�y reimplementowa�.
   *  Jest ona automatycznie reimplementowana przez zastosowanie
   *  makra \link vihierarchyline.hh::DEFPOLYHCLASS DEFPOLYHCLASS\endlink.
   */
   virtual const char *GetFinalClassName() const { return GetClassName(); }


  /*!
   *  Udost�pnia identyfikator klasy obiektu. Indentyfikator ten pozwala
   *  rozpozna� klas� pochod� w przypadku, gdy do dyspozycji jest tylko
   *  wska�nik na obiekt klasy ViNTreeNode. Klasy pochodne, kt�re mog�
   *  by� w ten spos�b rozpoznane to: ViElemePolyh, ViMultiPolyh oraz
   *  ViScenePolyhList.\n
   *  Identyfikatory tych klas s� zwracane r�wnie� wtedy, gdy s� one 
   *  dziedziczone przez inne klasy. Jest to podyktowane konieczno�ci�
   *  istnienia mo�liwo�ci stwierdzenia, z kt�rej z wymienionych wcze�niej
   *  podstawowych klas dla biblioteki VIONA, zosta�a wprowadzona dana
   *  klasa.
   *
   *  Dla w�asnych tworzonych klas do jej identyfikacji mo�na u�y� 
   *  reimplementacji metody
   *  \link ViNTreeNode::GetFinalClassID GetFinalClassID()\endlink. 
   */
   int GetViClassID() const;


   /*!
    * Metoda umo�liwia odpowiednie przetworzenie i sk�adowanie opis�w
    * parametr�w generowanych przez metody \b WriteDescripTo z ka�dej
    * z klas wchodz�cych w hierarchi� dziedziczenia klasy ViHierarchyLine.
    * \warning Metoda ta nie mo�e by� nadpisywana w innych w innych
    *           klasach pochodnych dziedzicz�cych klas� ViNTreeNode.
    * \param Margin - (\b in) wielko�� lewego marginesu, kt�ry ma by�
    *              zachowany przy zapsie poszczeg�lnych linii opisu
    *              parametr�w bry�y.
    * \param ParamDescr - zawiera parametry opisu bry�y wygenerowane przez
    *              dan� klas�.
    * \param TypeName - (\b in) zawiera nazw� klasy, na poziomie kt�rej 
    *              wygenerowany
    *              zosta� przekazywany opis parametr�w bry�y.
    * \param ObjPtr - (\b in) wska�nik na obiekt przekazuj�cy dany opis
    *              parametr�w bry�y.
    */
   void AddDescripToBuff( unsigned int       Margin,
                          ExtString const   &ParamDescr, 
                          const std::string &TypeName,
                          void const        *ObjPtr
                        ) const;

   /*!
    *  Metoda realizuje zapis parametr�w do bufora.
    *  Metoda ta jest przeci��ana przy zastosowaniu szablonu ViHierarchyLine.
    *  Szablon ten s�u�y do dziedzieczenia klasy bazowej 
    *  i umo�liwienie utowrzenie odpowiedniego ci�gu wywo�a� metod 
    *  dla ka�dej z klas bazowych zgodnie z hierarchi� dziedziczenia.
    *  Przyk�ad dziedzieczenia klas bazowych z wykorzystaniem szablonu
    *  ViHierarchyLine mo�na znale�� w kontsturkcji klas
    *  ViElemePolyh i ViMultiPolyh.
    * \param Margin - wielko�� lewego marginesu, kt�ry ma by� zachowany
    *              przy zapsie poszczeg�lnych linii opisu parametr�w 
    *              bry�y.
    */
   void WriteDescripToBuff( unsigned int           Margin,
                            const ViNTreeNode  *
                          ) const;



   /*!
    *  Udost�pnia list� bezpo�rednich potok�w danego n-drzewa.
    *  Lista udost�pniana jest w trybie sta�ym.
    */
   const ViDescList &GetDescList() const { return *((const ViDescList*)this);}

   /*!
    *  Udost�pnia list� bezpo�rednich potok�w danego n-drzewa.
    *  Lista udost�pniana jest w trybie modyfikacji.
    */
   ViDescList &UseDescList() { return *((ViDescList*)this);}

   /*!
    * Usuwa wszystkich potomk�w danego w�z�a.
    */
   void DeleteAllDesc() {  UseDescList().CancelList(); }



  /*!
   *  Metoda ma znaczenie pomocnicze. Jest ona podstaw� hierarchii wywo�a� 
   *  metod interpretacji opis�w parametr�w dla poszczeg�lnych klas wchodz�cych
   *  w hierarchiczn� struktur� dziedziczenia.
   *  \param Descr - (\b in) zawiera opis inicjalicji ca�ego w�z�a. W opisie 
   *           musz� znajdowa� si� sekcje opisu inicjalizacji poszczeg�lnych
   *           klas wchodz�cych w sk�ad hierarchii dziedziczenia
   *           klasy pochodnej, kt�rej obiektem ma by� dany w�ze�.
   *  \param pNode - ma znaczenie pomocnicze. Pozwala na rozr�nienie 
   *           przeci��onej metody i jednoznacznego jej zwi�zania z dan�
   *           klas�.
   */
   void InterpretParamDescr( const ViNodeDescr &  Descr, 
                             const ViNTreeNode *pNode
                           );
   /*!
    *  Metoda ta jest definiowana w szablonie ViHierarchyLine 
    *  (patrz \link ViHierarchyLine::InterpretParamDescr   
    *  ViHierarchyLine::InterpretParamDescr\endlink ) i
    *  odpowiedzialna jest za wywo�anie metod interpretuj�cych
    *  zapis parametr�w inicjalizacji obiektu dla klas wchodz�cych 
    *  w hierarchi� dziedziczenia klasy ViNTreeNode
    *  (w hierarchii tej pomijane s� pomocnicze szablony klas ViHierarchyLine).
    *  Ze wzgl�du na to, �e klasa ViNTreeNode nie dziedziczy szablonu
    *  ViHierarchyLine, metoda ta musi by� jawnie zdefiniowana w tej klasie.
    *
    *  Metoda \b InterpretParamDescr realizuje analogiczne operacje jak jej
    *  odpowiednik zdefiniowany w szablonie ViHierarchyLine.
    *  Efektem dzia�ania tej metody jest wowo�anie kolejnych metod 
    *  interepretuj�cych zapis parametr�w charakterystycznych dla 
    *  poszczeg�lnych
    *  klas. Wywo�ania nast�puj� pocz�wszy do obiektu klasy bazowej, 
    *  na obiekcie klasy finalnej ko�cz�c. Metoda ta odpowiedzialna
    *  jest r�wnie� za wydobycie z opisu danego w�z�a (przez w�ze� rozumiany
    *  jest pojedynczy element wchodz�cy w struktur� hierarchiczn� bry�y
    *  z�o�onej) tego opisu,
    *  kt�ry dotyczy odpowiedniej klasy.
    *  \param Descr - zawiera opis w�z�a.
    *  \exception ViException_Syntax - jest zg�aszany z kodem b��du w
    *        przypadku, ERRMSG_SYNTAX__NO_CLASS_DESCR, gdy w opisie danego
    *        w�z�a nie znaleziono opisu dla danej klasy.
    *          
    */  
   virtual void InterpretParamDescr(const ViNodeDescr &  Descr);


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
   *  \exception ViException_Syntax - mo�e by� zg�oszony z kodami b��d�w:
   *   \li  \link sxinterp.hh::ERRNUM_SX__UNEXP_CHAR 
   *                       ERRNUM_SX__UNEXP_CHAR\endlink - gdy napotkany zosta�
   *                inny znaku ni� oczekiwany.
   *   \li \link sxinterp.hh::ERRNUM_SX__FAIL_FLOAT
   *             ERRNUM_SX__FAIL_FLOAT\endlink - w przypadku niemo�no�ci
   *             wczytania liczby typu \e float.
   *   \li \link sxinterp.hh::ERRNUM_SX__FAIL_INT ERRNUM_SX__FAIL_INT\endlink -
   *             w przypadku niemo�no�ci wczytania liczby typu \e integer.
   *   \li \link sxinterp.hh::ERRNUM_SX__NO_KEYWORDS 
   *             ERRNUM_SX__NO_KEYWORDS\endlink - gdy brak listy ze s�owami
   *             kluczowymi.
   *   \li \link sxinterp.hh::ERRNUM_SX__START_NO_KEYWORD
   *             ERRNUM_SX__START_NO_KEYWORD\endlink - gdy napotkany znak
   *             nie mo�e by� pocz�tkiem �adnego s�owa kluczowego.
   *   \li \link sxinterp.hh::ERRNUM_SX__NO_KEYWORD
   *                                            ERRNUM_SX__NO_KEYWORD\endlink
   *             - gdy znalezione s�owo nie jest �adnym z oczekiwanych
   *               s��w kluczowych.
   *   \li \link sxinterp.hh::ERRNUM_SX__NO_WORD ERRNUM_SX__NO_WORD\endlink -
   *             gdy nie znaleziono �adnego s�owa.
   */
   void InitWithDescr( const ExtString &Descr );



   /*!
    *  Szablon uniwersalnego iteratora dla ViNTreeNode.
    *  \param BaseListType - klasa utworzona z szablonu List,
    *  \param BaseItemType - klasa utworzona z szablonu ListItem.
    */
   template <class IterType, class ElemType, class BaseListType, class BaseItemType>
   class UniPolyhIter: 
      public BaseIterator<IterType,ElemType> { //-------
     protected:
      /*!
       * Wska�nik na obiekt, dla kt�rego iterator ten zosta�
       * zainicjalizowany.
       */
      ElemType *_IniPtr;
      /*!
       * Wska�nik na na aktualnie iterowany obiekt.
       */
      ElemType *_CurPtr;
     public:
      /*!
       *  Ustawia iterator na dany element.
       *  \param  pElem - wska�nik na nowy element.
       *  \post   Do pola 
       *    \link ViNTreeNode::ConPolyhIter::_CurPtr _CurPtr\endlink
       *    przepisany zostaje adres udost�pniony przez parametr \e pElem.
       *  \warning Metoda ta nie powinna by� stosowana z du�� rozwag�.
       */
      void Set(ElemType *pElem) { _CurPtr = pElem; }

      /*!
       *  Przywraca stan pocz�tkowy iteratora.
       */
      void Reset() { _CurPtr = _IniPtr; }

      /*!
       * Inicjalizuje iterator dla danego elementu klasy ViNTreeNode.
       * \param PHLst - referencja do w�z�a struktury drzewiastej, dla
       *                kt�rego b�dzie zainicjalizowany iterator.
       */
      UniPolyhIter(ElemType &PHLst): _IniPtr(&PHLst) { Reset();}

       /*!
	*  Powoduje przej�cie do nast�pnego elementu w strukturze drzewiastej.
	*  Przegl�danie struktury realizowane jest w porz�dku \e preorder.
	*/
      UniPolyhIter &operator ++ () 
        {
          if (_CurPtr->BaseListType::First()) { // Id� w d� drzewa.
                 _CurPtr = _CurPtr->BaseListType::First();  return Iter_SetStatus(true);
          }
          if (_IniPtr == _CurPtr)  return Iter_SetStatus(false);
          if (_CurPtr->Next())  { // Id� do nast�pnego w�z�a na tym poziomie.
                 _CurPtr = _CurPtr->BaseItemType::Next();   return Iter_SetStatus(true);
          }

          ElemType *pPHLst = _CurPtr->RootInher();  // Idz w gore.

          while (_IniPtr != pPHLst) { // Czy doszedl do punktu startu.
           if (pPHLst->BaseItemType::Next()) {
                 _CurPtr = pPHLst->BaseItemType::Next();  return Iter_SetStatus(true); 
           }
           pPHLst = pPHLst->RootInher();
	  }
          return Iter_SetStatus(false);
        }

       /*!
	* Powoduje przej�cie do poprzedniego elementu w strukturze drzewiastej.
	* Przegl�danie struktury realizowane jest w porz�dku \e preorder.
	*/
      UniPolyhIter &operator -- () 
        {
          if (_CurPtr == _IniPtr) return Iter_SetStatus(false);
          if (!_CurPtr->BaseItemType::Prev()) { 
            _CurPtr = _CurPtr->RootInher();  return Iter_SetStatus(false);
	  }
          ElemType *pPHLst = _CurPtr->BaseItemType::Prev();          
          while (pPHLst->BaseListType::Last()) pPHLst = pPHLst->BaseListType::Last(); 
          _CurPtr = pPHLst;
          return Iter_SetStatus(true);
	}

  };

   /*!
    *  Klasa ta definiuje iterator pozwalaj�cy przegl�da� wszyskie
    *  obiekty ViNTreeNode. Ich wzajemnie po��czenia 
    *  tworz� struktur� drzewiast�. Dzi�ki temu, �e s� one dziedziczone
    *  przez obiekty klasy ViElemePolyh i ViMultiPolyh, pozwalaj� tym
    *  samym na tworzenie struktury drzewiastej obiekt�w tych klas.
    *
    * Przyk�ad u�ycia iteratora:
    * \code
    * void PolyhHierListIteration(ViMultiPolyh const &MPolyh)
    * {
    *  for (ViNTreeNode::ConPolyhIter Iter = MPolyh.ConBegin_PolyhHierList();
    *         Iter; ++Iter) {
    *     cout << " Jadro obiektu:" << Iter->GetName() 
    *          << "  Adres wezla: " << Iter->GetNodeAddress() << endl;
    *  }
    * }
    * \endcode
    */
   class ConPolyhIter: 
      public UniPolyhIter<ConPolyhIter,ViNTreeNode const,
                          List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>,
                          ListItem<ViNTreeNode,IDPRIMITIVE,ViNTreeNode> > { //---

     public:


      /*!
       * Inicjalizuje iterator dla danego elementu klasy ViNTreeNode.
       * \param PHLst - referencja do w�z�a struktury drzewiastej, dla
       *                kt�rego b�dzie zainicjalizowany iterator.
       */
      ConPolyhIter(ViNTreeNode const &PHLst): 
	UniPolyhIter<ConPolyhIter,const ViNTreeNode,
                  List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>,
                  ListItem<ViNTreeNode,IDPRIMITIVE,ViNTreeNode> > (PHLst) {}


      /*!
       *  Konwerter udost�pnia wska�nik bie�ego iterowanego elementu.
       */
      operator ViNTreeNode const* () const;
   };  //------------------ ConPolyhIter -------------------------------------


   /*!
    *  Klasa ta definiuje iterator pozwalaj�cy przegl�da� wszyskie
    *  obiekty ViNTreeNode. Ich wzajemnie po��czenia 
    *  tworz� struktur� drzewiast�. Dzi�ki temu, �e s� one dziedziczone
    *  przez obiekty klasy ViElemePolyh i ViMultiPolyh, pozwalaj� tym
    *  samym na tworzenie struktury drzewiastej obiekt�w tych klas.
    *  Przegl�dane obiekty udost�pniane s� w trybie modyfikacji.
    *
    * Przyk�ad u�ycia iteratora:
    * \code
    * void PolyhHierListIteration(ViMultiPolyh &MPolyh)
    * {
    *  for (ViNTreeNode::VarPolyhIter Iter = MPolyh.VarBegin_PolyhHierList();
    *         Iter; ++Iter) {
    *     cout << " Jadro obiektu:" << Iter->GetName() 
    *          << "  Adres wezla: " << Iter->GetNodeAddress() << endl;
    *  }
    * }
    * \endcode
    */
   class VarPolyhIter: public UniPolyhIter<VarPolyhIter,ViNTreeNode,
                          List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>,
                          ListItem<ViNTreeNode,IDPRIMITIVE,ViNTreeNode> > { //---
     public:
      /*!
       * Inicjalizuje iterator dla danego elementu klasy ViNTreeNode.
       * \param PHLst - referencja do w�z�a struktury drzewiastej, dla
       *                kt�rego b�dzie zainicjalizowany iterator.
       */
      VarPolyhIter(ViNTreeNode &PHLst): 
              UniPolyhIter<VarPolyhIter,ViNTreeNode,
                   List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>,
                   ListItem<ViNTreeNode,IDPRIMITIVE,ViNTreeNode> >(PHLst) {}
      /*!
       *  Konwerter udost�pnia wska�nik bie�ego iterowanego elementu.
       */
     operator ViNTreeNode * () const { return (ViNTreeNode*)_CurPtr; }
   };  //------------------ VarPolyhIter -------------------------------------



   /*!
    * Inicjalizuje obiekt nadaj�c mu nazw� i resetuj�c wszystkie flagi.
    * \param Name - nazwa obiektu.
    * \post Nazwa obiektu zapisana zostaje w polu 
    *   \link ViNTreeNode::_IndivName _IndivName\endlink,
    *   stan wszystkich flag zostaje zresetowany.
    */
   ViNTreeNode(char const *Name = "noname");
   ~ViNTreeNode() {};


   bool ShouldCallForClassDescr(const char *) const { return true; }

   /*!
    *  Udost�pnia wska�nik do zarz�dcy sceny, kt�ry jest jest polem 
    *  w klasie ViScene. W przypadku gdy obiekt nie jest do��czony
    *  do sceny, zwraca adres \p NULL.
    */
   ViNTreeNode const *GetRoot_Scene() const;

   /*!
    *  Udost�pnia wska�nik do zarz�dcy sceny, kt�ry jest jest polem 
    *  w klasie ViScene. W przypadku gdy obiekt nie jest do��czony
    *  do sceny, zwraca adres \p NULL.
    */
   ViNTreeNode *GetRoot_Scene() 
   { return 
      (ViNTreeNode *)(*(ViNTreeNode const*)this).GetRoot_Scene();
   }

  /*!
   * Udost�pnia warto�� okre�laj�c� typ k�t�w rotacji.
   */
   static MatrixH3f::AnglesType GetAngType() { return _TmpBuff.GetAngType();} 

  /*!
   * Udost�pnia warto�� 
   * okre�laj�c� rodzaj jednostek k�t�w rotacji.
   */
   static AngleUnit  GetAngUnit() { return _TmpBuff.GetAngUnit(); }


   /*!
    * Metoda umo�liwia sprawdzenie czy dany w�ze� ma jakiegokolwiek 
    * potomka (w sensie struktury drzewiastej).
    * \retval true - gdy w�ze� ma potomka,
    * \retval false - w przypadku przeciwnym.
    */
   bool IsDescendant() const 
     { return  List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>::IsAny(); }

    /*====================================================================
     * Uniewa�nia flag� wa�no�ci oblicze� dla wsp�rz�dnych globalnych 
     * i struktur od nich zale�nych.
     */
   void ValidFlag_ResetGlbVtx(bool ForAllObjectFamily = true); 

    /*!
     * Ustawia wa�no�� flagi dla wsp�rz�dnych globalnych i uniewa�nia
     * flagi dla dodatkowych struktur od nich zale�nych.
     * Jako dodatkowe struktury rozumie si� struktury zwi�zane z poszczeg�lnymi
     * widokami definiowanymi w klasach pochodnych poza j�drem reprezentacji
     * geometrycznej obiekt�w.
     * \param  ForAllObjectFamily - Je�li \p true (domy�lnie), to ustawian 
     *            jest  flaga VFLAG_TEST_DESCENDANTS dla wszystkich kolejnych
     *            przodk�w danego w�z�a. Je�li \p false, to flagi resetowane
     *            s� tylko dla danego obiektu elementarnego.
     * \post Ustawiona zostaje flaga GLB_VTX,
     *     uniewa�nione zostaj� flagi (w danym w�zle i dla wszystkich widok�w):
     *     VIEW_VTX,  RECT_OUT, FACE_POLY, FACE_RGN, FACE_VIEW_RGN
     */
   void ValidFlag_SetGlbVtx(bool ForAllObjectFamily = true); 



  /*!
   * Ustawia wa�no�� flagi dla wsp�rz�dnych globalnych i uniewa�nia
   * flagi dla struktur od nich zale�nych.   Akcja ta jest realizowana
   * dla danego w�z�a i wszystkich jego potomk�w.
   *
   * \param  ForAllObjectFamily - Je�li true (domy�lnie), to ustawian jest flaga 
   *                             VFLAG_TEST_DESCENDANTS dla wszystkich kolejnych
   *                             przodk�w danego w�z�a.
   *                             Je�li false, to flagi resetowane s� tylko dla
   *                             danego obiektu elementarnego.
   * \post Ustawiona zostaje flaga
   *         GLB_VTX,
   *       Uniewa�nione zostaj� flagi (w danym w�zle i dla wszystkich widok�w):
   *         VIEW_VTX,  RECT_OUT, FACE_POLY, FACE_RGN, FACE_VIEW_RGN
   */
   void ValidFlag_Set4All_GlbVtx(bool ForAllObjectFamily = true); 


  /*!
   *  Uniewa�nia flag� dla  globalnych wsp�rz�dnych wierzho�k�w. Prowadzi to
   *  do uniewa�nienia r�wnie� flag zwi�zanych ze struktrami pochodnymi,
   *  np. wsp�rz�dne wierzcho�k�w dla widok�w, obrys bry�y. Akcja ta jest 
   *  realizowana dla danego w�z�a i wszystkich jego potomk�w.
   *
   *  \param  ForAllObjectFamily - Je�li true (domy�lnie), to ustawian jest 
   *                     flaga VFLAG_TEST_DESCENDANTS dla wszystkich kolejnych
   *                     przodk�w danego w�z�a.
   *                     Je�li false, to flagi resetowane s� tylko dla
   *                     danego obiektu elementarnego.
   *
   *  \post Uniewa�nione zostaj� flagi:
   *       GLB_VTX, VIEW_VTX,  RECT_OUT, FACE_POLY, FACE_RGN, FACE_VIEW_RGN
   */
   void ValidFlag_Reset4All_GlbVtx(bool ForAllObjectFamily = true); 


    /*!
     * Uniewa�nia flag� dla struktur pomoczniczych zale�nych od wsp�rz�dnych
     * globalnych. Metoda wywo�ywana przez ValidFlag_ResetGlbVtx. Metoda 
     * przeznaczona do reimplementacji do resetowania flag dla widok�w.
     * Reimplementacja tej metody musi by� zrealizowana w klasie pochodnej.
     */
   virtual void ValidFlag_ResetAuxDependedOnGlbVtx() {}




  /*!
   *  Uniewa�nia flag� dla wsp�rz�dnych dla danego widoku. Prowadzi to
   *  do uniewa�nienia r�wnie� flag zwi�zanych ze struktrami pochodnymi,
   *  np. wsp�rz�dne wierzcho�k�w dla widok�w, obrys bry�y. Akcja ta jest 
   *  realizowana dla danego w�z�a i wszystkich jego potomk�w.
   *  Metoda wyo�uje dla ka�dego w�z�a metod� 
   *  \link ViNTreeNode::ValidFlag_ResetViewVtx 
   *        ValidFlag_ResetViewVtx\endlink, kt�ra jest metod� wirtulan� i 
   *  powinna by� reimplementowana w klasach pochodnych, kt�re powi�zane
   *  s� zestrukturami danych dla poszczeg�lnych widok�w.
   *
   *  \param  NView - numer widoku.
   *  \param  ForAllObjectFamily - je�li \p true (domy�lnie), to ustawiana jest
   *                    flaga VFLAG_TEST_DESCENDANTS dla wszystkich kolejnych
   *                    przodk�w danego w�z�a.
   *                    Je�li false, to flagi resetowane s� tylko dla
   *                    danego obiektu elementarnego.
   *
   *  \post Uniewa�nione zostaj� flagi:
   *       VIEW_VTX,  RECT_OUT, FACE_POLY, FACE_RGN, FACE_VIEW_RGN
   */
   void ValidFlag_Reset4All_ViewVtx(int NView, bool ForAllObjectFamily = true);


    /*!
     * Uniewa�nia flag� dla danego widoku dla struktur zale�nych od
     * wsp�rz�dnych wierzcho�k�w dla danego widoku.
     * Metoda ta powinna by� reimplementowana w klasach pochodnych
     * zawieraj�cych struktury danych zwi�zanych z poszczeg�lnymi widokami.
     * Na poziomie klasy ViNTreeNode metoda ta nie realizuje �adnej akcji.
     * \param  ViewNr - numer widoku,
     * \param  ForAllObjectFamily - decyduje o tym, czy akcja ma by� 
     *             przeprowadzona r�wnie� dla wszystkich w�z��w pochodnych
     *             (warto�� \p true, jest to warto�� domy�lna tego parametry),
     *             czy te� tylko dla danego w�z�a.
     */
   virtual void ValidFlag_ResetViewVtx
                       (int ViewNr, bool ForAllObjectFamily = true) {};


    /*!
     * Ustawia flag� swojego przodka, kt�ra informuje, �e dane przynajmniej 
     * jednego z potomk�w musz� by� zaaktualizowane.
     */
   void ValidFlag_SetTestDescants4Acestor(bool SetForAllAncestor=true); 


    /*!
     * Ustawia flag�, kt�ra informuje �e dane obliczeniowe przynajmniej 
     * jednego z potomk�w musz� by� zaaktualizowane.
     */
   void ValidFlag_SetTestDescants() { VF_SetTestDescants(); }


    /*!
     * Resetuje (uniewa�nia) wszystkie flagi tylko dla danego
     * obiektu elementarnego.
     */
   void ValidFlag_ResetAll() { VF_ResetAll(); }


    /*!
     * Zwraca \p true gdy flaga jest ustawiona, co oznacza, �e wyliczone
     * wcze�niej wsp�rz�dne globalne s� wci�� aktualne. W przeciwnym 
     * przypadku zwraca warto�� \p false.
     */
   bool IsFlagValid_GlbVtx()      const { return IsVF_GlbVtx(); }

    /*!
     * Zwraca \p true gdy flaga jest ustawiona, co oznacza, �e wyliczony
     * wcze�niej obrys prostopad�o�cienny (we wsp�rz�dnych
     * globalnych) danej bry�y (je�eli klas� pochodn� jest ViElemePolyh)
     * lub zbioru byry� (je�eli klas� pochodn� jest ViMultiPolyh)
     *  jest wci�� aktualny.
     * W przeciwnym przypadku zwraca warto�� \p false.
     */
   bool IsFlagValid_RectOutlineBox3f() const {return IsVF_RectOutlineBox3f();}

    /*!
     * Zwraca \p true gdy flaga jest ustawiona, co oznacza, �e wyliczone
     * wcze�niej wsp�rz�dne dla wszystkich widok�w s� wci�� aktualne.
     * W przeciwnym przypadku zwraca warto�� \p false.
     */
   bool IsFlagValid_ViewVtx()     const { return IsVF_ViewVtx(); }

   /*!
    *  Metoda jest zasz�o�ci� i przewidziana jest do usuni�cia. Nie
    *  nale�y z niej korzysta�.
    */
  virtual bool IsFlagValid_ViewVtx(int NView) const { return true; };

   /*!
    * Udost�pnia wska�nik do w�z�a b�d�cego rodzicem (w sensie struktury 
    * drzewiastej) w�z�a, dla kt�rego wywo�ywana jest niniejsza metoda.
    */
  ViNTreeNode *GetParentNode();

  const ViElemePolyh *GetAncestor_ElemePolyh() const;
  ViElemePolyh *UseAncestor_ElemePolyh()
                { return (ViElemePolyh*) GetAncestor_ElemePolyh(); }

  const ViMultiPolyh *GetAncestor_MultiPolyh() const;
  ViMultiPolyh *UseAncestor_MultiPolyh()
                { return (ViMultiPolyh*) GetAncestor_MultiPolyh(); }



   /*!
    * Udost�pnia wska�nik do w�z�a b�d�cego rodzicem (w sensie struktury 
    * drzewiastej) w�z�a, dla kt�rego wywo�ywana jest niniejsza metoda.
    * Udost�pniowny wska�nik nie pozwala modyfikowa� wskazywanego obiektu.
    */
  const ViNTreeNode *GetParentNode() const;

   /*!
    * Metoda udost�pnia nazw� w�z�a (warto�� pola 
    * \link ViNTreeNode::_IndivName _IndivName\endlink). Nazwa ta stanowi
    * cz�� pe�nego adresu w�z�a w strukturze drzewiastej, kt�rej elementem
    * jest dany w�ze�m (patrz opis pola 
    * \link ViNTreeNode::_IndivName _IndivName\endlink).
    * \return Udost�pnia �a�cuch znak�w (w sensie j�zyka C) stanowi�cy nazw�
    *         w�z�a.
    */
  char const *NodeName() const {return _IndivName(); }

   /*!
    * Metoda nadaje now� nazw� danem u w�z�owi (modyfikuje warto�� pola 
    * \link ViNTreeNode::_IndivName _IndivName\endlink). Nazwa ta stanowi
    * cz�� pe�nego adresu w�z�a w strukturze drzewiastej, kt�rej elementem
    * jest dany w�ze�m (patrz opis pola 
    * \link ViNTreeNode::_IndivName _IndivName\endlink).
    * \param Name - nawa nazwa dla danego w�z�a.
    * \pre \e Name != \p NULL
    * \post W polu \link ViNTreeNode::_IndivName _IndivName\endlink
    *       zostaje wpisana nowa nazwa udost�pniona poprzez parametr \e Name
    *       (zawarto�� �a�cucha dost�pnego porzez ten parametr zostaje 
    *       skompiowana).
    */
  void SetNodeName(char const *Name ) { _IndivName = Name; }

   /*!
    * Metoda udost�pnia nazw� w�z�a (warto�� pola 
    * \link ViNTreeNode::_IndivName _IndivName\endlink). Nazwa ta stanowi
    * cz�� pe�nego adresu w�z�a w strukturze drzewiastej, kt�rej elementem
    * jest dany w�ze�m (patrz opis pola 
    * \link ViNTreeNode::_IndivName _IndivName\endlink).
    * \return Udost�pnia �a�cuch znak�w (w sensie j�zyka C) stanowi�cy nazw� 
    *         w�z�a.
    * \warning Metoda ta uznana jest jako zasz�o�� i przewidziana jest do 
    *        usuni�cia.
    *        Z tego wzgl�du nie nale�y jej wykorzystywa�. Zamiast niej nale�y
    *        pos�ugiwa� si� metod� 
    *        \link ViNTreeNode::NodeName NodeName\endlink.
    */
  char const *GetName() const { return _IndivName(); }

   /*!
    * Metoda udost�pnia referencje do pola  
    * \link ViNTreeNode::_IndivName _IndivName\endlink. 
    * Zawiera ono nazw� w�z�a. Nazwa ta stanowi
    * cz�� pe�nego adresu w�z�a w strukturze drzewiastej, kt�rej elementem
    * jest dany w�ze�m (patrz opis pola 
    * \link ViNTreeNode::_IndivName _IndivName\endlink).
    * \return referencj� pozwalaj�c� modyfikowa� zawarto�� pola
    *      \link ViNTreeNode::_IndivName _IndivName\endlink.
    * \warning Metoda ta uznana jest jako zasz�o�� i przewidziana jest do 
    *   usuni�cia. Z tego wzgl�du nie nale�y jej wykorzystywa�. Zamiast niej 
    *   nale�y pos�ugiwa� si� metod� 
    *   \link ViNTreeNode::SetNodeName SetNodeName\endlink.
    */
  ExtString &UseName() { return _IndivName; }

   /*!
    * Metoda nadaje now� nazw� danem u w�z�owi (modyfikuje warto�� pola 
    * \link ViNTreeNode::_IndivName _IndivName\endlink). 
    * Nazwa ta stanowi
    * cz�� pe�nego adresu w�z�a w strukturze drzewiastej, kt�rej elementem
    * jest dany w�ze�m (patrz opis pola 
    * \link ViNTreeNode::_IndivName _IndivName\endlink).
    * \param Name - nawa nazwa dla danego w�z�a.
    * \pre \e Name != \p NULL
    * \post W polu \link ViNTreeNode::_IndivName _IndivName\endlink
    *       zostaje wpisana nowa nazwa udost�pniona poprzez parametr \e Name
    *       (zawarto�� �a�cucha dost�pnego porzez ten parametr zostaje 
    *       skompiowana).
    * \warning  Metoda ta uznana jest jako zasz�o�� i przewidziana jest do 
    *        usuni�cia. Z tego wzgl�du nie nale�y jej wykorzystywa�. Zamiast
    *        niej nale�y pos�ugiwa� si� metod� 
    *        \link ViNTreeNode::SetNodeName SetNodeName\endlink.
    */
  void SetName(char const *Name ) { _IndivName = Name; }

   /*!
    * Metoda udost�pnia nazw� w�z�a (warto�� pola 
    * \link ViNTreeNode::_IndivName _IndivName\endlink).
    * Nazwa ta stanowi
    * cz�� pe�nego adresu w�z�a w strukturze drzewiastej, kt�rej elementem
    * jest dany w�ze�m (patrz opis pola 
    * \link ViNTreeNode::_IndivName _IndivName\endlink).
    * \warning Nie jest zalecane pos�ugiwanie si� t� metod�. Preperowana
    *    jest metoda \link ViNTreeNode::NodeName NodeName\endlink.
    *    Wykorzystanie jej jest usprawiedliwione tylko w przypadku, gdy
    *    potrzebna jest referencja do obiektu ExtString.
    */
  ExtString const &IndivName() const { return _IndivName; }
   //=======================================================================
   // Metoda pozwala na otrzymanie macierzy transformacji do uk�adu
   //  wsp�rz�dnych globalnych danej sceny.
  int  GetMtx2GlbCoord(MatrixH3f &Mtx) const;
  int  GetMtx2RootCoord(MatrixH3f &Mtx) const; 
  int  GetMtx2LocalRootCoord(MatrixH3f &Mtx) const; 

   //=======================================================================
   // Metoda pozwala na otrzymanie macierzy transformacji z uk�adu
   // wsp�rz�dnych obiektu, kt�ry jest korzeniem ca�ego drzewa 
  int  GetMtxRoot2GlbCoord(MatrixH3f &Mtx) const;
   /*!
    * Umo�liwia zmian� nowych warto�ci dla macierzy transformacji
    * wsp�rz�dnych
    * dla danego w�z�a struktury �a�cucha kinematycznego do uk�adu 
    * wsp�rz�dnych rodzice tego w�z�a.
    * \param Mtx - nowe warto�ci macierzy transformacji.
    */
  void SetMtx2ParentCoord(MatrixH3f const &Mtx);
   /*!
    * Udost�pnia macierz transformacji do uk�adu wsp�rz�dnych rodzica
    * hierarchicznej strukturze drzewa.
    */
  ViMatrix3f const &Mtx2ParentCoord() const { return _Transf2ParentCoord; }
   /*!
    * Udost�pnia macierz transformacji do uk�adu wsp�rz�dnych rodzica
    * hierarchicznej strukturze drzewa z mo�liwo�ci� zmian.
    */
  ViMatrix3f &UseMtx2ParentCoord() { return _Transf2ParentCoord; }


  /*!
   * Szuka w swojej li�cie bezpo�rednich potomk�w w�z�a o zadanej nazwie.
   * \param Name - nazwa szukanego w�z�a.
   * \return wska�nik na pierwszego bezpo�redniego potomka, kt�rego nazwa
   *         jest zgodna z nazw� przekazan� przez parametr. Zwracany 
   *         wska�nik jest wska�nikiem do obiektu sta�ego.
   *         W przypadku braku
   *         takiego potomka zwracany jest adres \p NULL.
   *        
   */
  ViNTreeNode const *SeekNodeInLayer(char const *Name) const;

  /*!
   * Szuka w swojej li�cie bezpo�rednich potomk�w w�z�a o zadanej nazwie.
   * \param Name - nazwa szukanego w�z�a.
   * \return wska�nik na pierwszego bezpo�redniego potomka, kt�rego nazwa
   *         jest zgodna z nazw� przekazan� przez parametr. Zwracany wska�nik
   *         jest wska�nikiem do obiektu modyfikowalnego.
   *         W przypadku braku
   *         takiego potomka zwracany jest adres \p NULL.
   *        
   */
  ViNTreeNode       *SeekNodeInLayer(char const *Name)
   { return (ViNTreeNode*) 
             (*(ViNTreeNode const*)this).SeekNodeInLayer(Name);
   }

  /*!
   * Szuka w�z�a traktuj�c adres podany przez parametr jako adres wzgl�dem
   * w�z�a dla kt�rego metoda ta zosta�a wywo�ana, o ile pierwszym znakiem
   * nie jest znak separatora. W przeciwnym przypadku szukanie realizowane
   * jest od korzenia ca�ej struktury drzewiastej (tzn. do listy bry�
   * z�o�onych danej sceny).
   * \param NodeAddr  - pe�na �cie�ka adresu w�z�a (wzg��dem korzenia lub
   *                    lokalnego w�z�a).
   * \pre \e NodeAddr != \p NULL.
   * \return wska�nik do obiektu o obiektu o podanym adresie lub wska�nik
   *         \p NULL je�li obiekt tak nie istnieje.
   */
  ViNTreeNode const *SeekNodeAlongPath(char const *NodeAddr ) const;

  /*!
   * Szuka w�z�a traktuj�c adres podany przez parametr jako adres wzgl�dem
   * w�z�a dla kt�rego metoda ta zosta�a wywo�ana, o ile pierwszym znakiem
   * nie jest znak separatora. W przeciwnym przypadku szukanie realizowane
   * jest od korzenia ca�ej struktury drzewiastej (tzn. do listy bry�
   * z�o�onych danej sceny).
   * \param NodeAddr  - pe�na �cie�ka adresu w�z�a (wzg��dem korzenia lub
   *                    lokalnego w�z�a).
   * \pre \e NodeAddr != \p NULL.
   * \return wska�nik do obiektu o obiektu o podanym adresie lub wska�nik
   *         \p NULL je�li obiekt tak nie istnieje.
   *        Udost�pniany obiekt poprzez zwr�cony wska�nik jest modyfikowalny.
   *         
   */
  ViNTreeNode *SeekNodeAlongPath(char const *NodeAddr)
   { return (ViNTreeNode*) 
             (*(ViNTreeNode const*)this).SeekNodeAlongPath(NodeAddr);
   }

  
  int WalkAlongTree_PreOrder( 
                        int (*Fun)(ViElemePolyh const *, void *, int Level),
                        void *pData = 0,
                        int  Level = 0
                      ) const;

  /*!
   *  Zapisuje do strumienia \e ostrm informacje dotycz�ce danego w�z�a
   *  (macierze transformacji, etykiety, adres w�z�a itd.).
   *  \param  ostrm - otwarty strumie� wyj�ciowy, ze wzgl�du na hierarchi�
   *                  dziedziczenia klas w bibliotece standardowej mo�e to
   *                  by� r�wnie� strumie� klasy \b ofstream.
   *  \param  AType - okre�la rodzaj k�t�w rotacji parametryzuj�cych
   *                podmacierz rotacji dla tranformacji od uk�adu wsp�rz�dnych
   *                rodzica.\n
   *                W tej chwili
   *                obs�ugiwane s� k�ty Eulera oraz k�ty rotacji 
   *                wok� osi OX, OY, OZ.
   *  \param  AUnit - okre�la w jakich jednostkach maj� by� zapisane warto�ci
   *                k�t�w.
   *  \param  Margin - ilo�� spacji jak� maj� by� poprzedzone poszczeg�lne
   *                linie opisu parametr�w.
   *  \retval true - gdy w trakcie zapisu nie wyst�pi� �aden b��d,
   *  \retval false - w przypadku przeciwnym.
   *  
   *  
   *   Format zapisu:
   *   \verbatim
        Node__Begin
         ClassSection__Begin:  ViNTreeNode
           NodeName:  xxxxxx
           NodeAddress:  .xxx.xxx.xxxx.xxx
           Transf2Parent
             Angles { Euler | XYZ } { Deg | Rad }: ( k�t1, k�t2, k�t3 )
             Translation: ( sk�adowa_x, sk�adowa_y, sk�adowa_z )
             Scale: ( skala_x, skala_y, skala_z )
          ClsasSection__End
          ClassSection__Begin: nazwa_klasy1
               ...
               ... Custom Parameters ...
          ClassSection__End
          ClassSection__Begin: nazwa_klasy2
               ...
               ... Custom Parameters ...
          ClassSection__End
           ...
        Node_End
       \endverbatim
   *  Przyk�ad wygenerowanego opisu obiektu znajduje si�
   *  w sekcji \ref wlasna_bryla__zapis.
   */
  bool WriteNodeDescriptionTo( 
                ostream                 &ostrm, 
                MatrixH3f::AnglesType    AType      = MatrixH3f::AT_Euler,
		AngleUnit                AUnit      = AU_Deg,
                unsigned int             Margin     = 0 
              ) const;
  
   /*
  int WalkAlongPattePolyhTree( 
               int (*Fun)(ViElemePolyh const *, MatrixH3f const *, int Level),
               MatrixH3f const *pMtx = 0L,
               int  Level = 0
             ) const;
   */
  /*!
   *  Metoda przechodzi po ca�ej strukturze drzewiastej poczynaj�c od w�z�a,
   *  dla kt�rego zosta�a wywo�ana. Chodz�c po tej strukurze wywo�uje dla niej
   *  funkcj�, kt�ra przekazywana jest jako parametr wywo�ania tej metody.
   *  Przechodzenie nast�puje w porz�dku preorder.
   *
   *  \param  Fun - funkcja, kt�ra jest wywo�ywana dla ka�dego w�z�a.
   *          Parametrami tej funkcji jest wska�nik na dany obiekt modeluj�cy
   *          bry�� elementarn� (obiekt klasy 
   *          \link ViElemePolyh ViElemePolyh\endlink.
   *          Drugim parametrem jest jest macierz transformacji.
   *          Schodz�c coraz ni�ej wzd�u� ga��zi drzewa macierz ta jest 
   *          przemna�ana przez kolejne macierze tranforamcji ze ws�rz�dnych
   *          lokalnych danego w�z�a do wsp�rz�dnych jego rodzica.
   *          W ten spos�b na ka�dym poziomie funkcja \e Fun otrzymuje macierz
   *          przekszta�cenia wsp�rz�dnych danego elementu do wsp�rz�dnych
   *          w�z�a, dla kt�rego metoda ta zosta�a wywo�ana.
   *          Trzecim parametrem jest warto�� okre�laj�ca poziom zag��bienia
   *          w strukturze drzewa. Pocz�tkowa warto�� tego parametru jest
   *          brana z warto�ci parametru \e Level.
   *  \param  pMtx  - wska�nik na macierz transformacji do zadanego uk�adu
   *                  wsp�rz�dnych.
   *  \param  Level - poziom zag��bienia w strukturze drzewiastej. Warto��
   *                 parametru pokazuje na jakiej g��boko�ci jest dany w�ze�.
   *
   *  \pre
   *    Dla w�z�a, dla kt�rego wywo�ana jest bezpo�rednio ta metoda, warto�� 
   *    parametru \e Level musi by� r�wna 0.
   *  \post
   *    Metoda przechodzi po wszystkich obiektach klasy 
   *    \link ViElemePolyh ViElemePolyh\endlink i wywo�uje dla nich funkcj�
   *     \e Fun. 
   */
  int WalkAlongPattePolyhTree(
                               int (*Fun)(ViElemePolyh const *pNode_i, 
                                          MatrixH3f    const *pMtx_i, 
                                          int Level_i
                                         ),
                               MatrixH3f const *pMtx,
                               int Level 
			       ) const;

  /*!
   *  Metoda przechodzi po ca�ej strukturze drzewiastej poczynaj�c od w�z�a,
   *  dla kt�rego zosta�a wywo�ana. Chodz�c po tej strukurze wywo�uje dla niej
   *  funkcj�, kt�ra przekazywana jest jako parametr wywo�ania tej metody.
   *  Przechodzenie nast�puje w porz�dku preorder. Metoda ma mo�liwo��
   *  modyfikowania wierzcho�k�w przez kt�re przechodzi.
   *
   *  \param  Fun - funkcja, kt�ra jest wywo�ywana dla ka�dego w�z�a.
   *          Parametrami tej funkcji jest wska�nik na dany obiekt modeluj�cy
   *          bry�� elementarn� (obiekt klasy 
   *          \link ViElemePolyh ViElemePolyh\endlink.
   *          Drugim parametrem jest jest macierz transformacji.
   *          Schodz�c coraz ni�ej wzd�u� ga��zi drzewa macierz ta jest 
   *          przemna�ana przez kolejne macierze tranforamcji ze ws�rz�dnych
   *          lokalnych danego w�z�a do wsp�rz�dnych jego rodzica.
   *          W ten spos�b na ka�dym poziomie funkcja \e Fun otrzymuje macierz
   *          przekszta�cenia wsp�rz�dnych danego elementu do wsp�rz�dnych
   *          w�z�a, dla kt�rego metoda ta zosta�a wywo�ana.
   *          Trzecim parametrem jest warto�� okre�laj�ca poziom zag��bienia
   *          w strukturze drzewa. Pocz�tkowa warto�� tego parametru jest
   *          brana z warto�ci parametru \e Level.
   *  \param  pMtx  - wska�nik na macierz transformacji do zadanego uk�adu
   *                  wsp�rz�dnych.
   *  \param  Level - poziom zag��bienia w strukturze drzewiastej. Warto��
   *                 parametru pokazuje na jakiej g��boko�ci jest dany w�ze�.
   *
   *  \pre
   *    Dla w�z�a, dla kt�rego wywo�ana jest bezpo�rednio ta metoda, warto�� 
   *    parametru \e Level musi by� r�wna 0.
   *  \post
   *    Metoda przechodzi po wszystkich obiektach klasy 
   *    \link ViElemePolyh ViElemePolyh\endlink i wywo�uje dla nich funkcj�
   *     \e Fun. 
   */
  int WalkAlongPattePolyhTree( 
               int (*Fun)(ViElemePolyh *, MatrixH3f const *, int Level),
               MatrixH3f const *pMtx = 0L,
               int  Level = 0
             );


  int WalkAlongPattePolyhTree( 
      int (*Fun)(ViElemePolyh *, OutlineBox3f &, MatrixH3f const *, int Level),
      OutlineBox3f        &Oln,
      MatrixH3f const *pMtx = 0L,
      int  Level = 0
    );

     //----------------------------------------------------------------------
     // Metoda przeznaczona do wykonywania metod z rodziny ValidFlag_...
     //
  int WalkAlongPattePolyhTree( 
            void (ViNTreeNode::*Method)(bool val),
            bool ForAllObjectFamily = true,
            int  Level = 0
          );

  int WalkAlongPattePolyhTree_IB( 
            void (ViNTreeNode::*Method)(int, bool val),
            int  NView,
            bool ForAllObjectFamily = true,
            int  Level = 0
          );

   /*!
    *  Udost�pnia adres danego w�z�a w strukturze drzewiastej bry� z�o�onych
    *  \param NodeAddr - obiekt ten po zako�czeniu dzia�ania metody zawiera
    *             wyznaczony adres w�z�a.
    *  \return wska�nik do �a�cucha znak�w z obiektu \e NodeAddr.
    */
  char const *GetNodeAddress( ViNodeAddress &NodeAddr ) const;

   /*!
    *  Udost�pnia adres danego w�z�a w strukturze drzewiastej bry� z�o�onych
    *  \return obiekt zawieraj�cy adres w�z�a w drzewie.
    */
   ViNodeAddress GetNodeAddress() const;

   /*!
    *  Udost�pnia adres rodzica danego w�z�a w strukturze drzewiastej bry� 
    *  z�o�onych
    *  \param NodePath - obiekt ten po zako�czeniu dzia�ania metody zawiera
    *             wyznaczony adres rodzica danego w�z�a.
    *  \return wska�nik do �a�cucha znak�w z obiektu \e NodePath.
    */
  char const *GetNodePath( ViNodeAddress &NodePath ) const;

  int MoveBranchTo(ViNTreeNode *pNode);
  int MoveBranchFromParentToRoot();
   /*!
    *  Usuwa w�ze� reprezentowany przez obiekt, dla kt�rego wywo�ana
    *  zosta�a niniejsza metoda, z listy potomk�w swojego rodzica.
    */ 
  void DetachNode() { RemoveFromList(); }
   /*!
    *  Dodaje nowy element do swojej listy. Odpowiada to dodaniu nowego
    *  potomka do rodzica (rodzicem jest obiekt, dla kt�rego wywo�ana
    *  zostaja metoda AddNode). Dodawany element mo�e mie� swoj� w�asn�
    *  kolejk� (zbi�r potomk�w). W tym przypadku operacja ta mo�e by�
    *  interpretowana jako dodanie nowego podrzewa.
    *  \param pNode - wska�nik na dodany nowy element (b�dzie on nowym
    *                 potomkiem dla w�z�a reprezentowanego przez obiekty
    *                 \b *this.
    *  \return wska�nik na dodany element.
    *  \post  Obiekt wskazywany przez \e pNode zostaje umieszczony na
    *         ko�cu kolejki potomk�w danego w�z�a.
    *         
    */
  ViNTreeNode *AddNode(ViNTreeNode *pNode);
   /*!
    * Metoda udost�pnia obiekt, kt�ry jest korzeniem dla ca�ej struktury.
    * Obiekt taki powinien by� elementem listy wielobok�w z�o�onych
    * danej sceny.
    * Udost�pniony wska�nik pozwala modyfikowa� ten obiekt.
    */
  ViNTreeNode *GetTreeRoot();
   /*!
    * Metoda udost�pnia obiekt, kt�ry jest korzeniem dla ca�ej struktury.
    * Obiekt taki powinien by� elementem listy wielobok�w z�o�onych
    * danej sceny.
    */
  ViNTreeNode const *GetTreeRoot() const;
   /*!
    * Metoda ta w klasie pochodnej musi by� reimplementowana.
    * Zwraca� ona musi warto�� pozwalaj�c� jednoznacznie zidentyfikowa�
    * klas� pochodn�. 
    * \warning Metoda GetInheritorType  jest reimplementowana w kasach
    * pochodnych ViElemePolyh, ViMultiPolyh i ViScenePolyhList. 
    * Nie powinna ona by� 
    * reimplementowana w �adnych innych klasach pochodnych.
    */
  virtual int GetInheritorType() const { return IT_MULTITREENODE; };

  /*!
   *  Metoda ta pozwala otrzyma� identyfikator finalnej klasy pochodnej
   *  wzgl�dem klasy ViNTreeNode. Udost�pniany identyfikator
   *  pozwala rozpozna� klas� pochod� w przypadku, gdy do dyspozycji jest
   *  tylko wska�nik na obiekt klasy ViNTreeNode.
   *
   *  Metoda przeznaczona jest do reimplementacji we w�asnych klasach
   *  pochodnych, kt�re definiuje programista. Zak�ada si�, �e 
   *  przedzia� od -1000 do 1000 w��cznie jest zarezerwowany dla
   *  biblioteki VIONA.
   *  Przy w�asnej reimplementacji tej metody jako zwracany identyfikator
   *  nale�y wi�c u�y� warto�ci spoza tego przedzia�u.
   */
  virtual int GetFinalClassID() const { return GetInheritorType(); }

   /*!
    *  Metoda ma charakter roboczy i wykorzystywana jest na potrzeby
    *  debugowania programu.
    */
  virtual void const *GetAddr() const  { return this; };

   //======================= Iteratory ===============================
   /*!
    *  Tworzy iterator do przegl�dania struktury drzewiastej, kt�rej
    *  w�z�em jest dany obiekt (dla kt�rego zosta�a wywo�ana ta metoda).
    *  Przegl�d drzewa realizowany jest w porz�dku preorder.
    *
    * Przyk�ad u�ycia iteratora:
    * \code
    * void PolyhHierListIteration(ViMultiPolyh const &MPolyh)
    * {
    *   for (ViNTreeNode::ConPolyhIter Iter = MPolyh.ConBegin_PolyhHierList();
    *         Iter; ++Iter) {
    *     cout << " Jadro obiektu:" << Iter->GetName() 
    *          << "  Adres wezla: " << Iter->GetNodeAddress() << endl;
    *  }
    * }
    * \endcode
    */
   ViNTreeNode::ConPolyhIter ConBegin_PolyhHierList() const
                                         { return ConPolyhIter(*this); }


   /*!
    *  Tworzy iterator do przegl�dania struktury drzewiastej, kt�rej
    *  w�z�em jest dany obiekt (dla kt�rego zosta�a wywo�ana ta metoda).
    *  Przegl�d drzewa realizowany jest w porz�dku preorder.
    *  Przegl�dane obiekty udost�pniane s� w trybie modyfikacji.
    *
    * Przyk�ad u�ycia iteratora:
    * \code
    * void PolyhHierListIteration(ViMultiPolyh &MPolyh)
    * {
    *   for (ViNTreeNode::VarPolyhIter Iter = MPolyh.VarBegin_PolyhHierList();
    *         Iter; ++Iter) {
    *     cout << " Jadro obiektu:" << Iter->GetName() 
    *          << "  Adres wezla: " << Iter->GetNodeAddress() << endl;
    *  }
    * }
    * \endcode
    */
   ViNTreeNode::VarPolyhIter VarBegin_PolyhHierList()
                                         { return VarPolyhIter(*this); }
};  


inline
ViNTreeNode *ViNTreeNode::AddNode(ViNTreeNode *pNode) 
{ 
  return List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>::AddToTail(pNode); 
} 


inline
ViNTreeNode *ViNTreeNode::GetParentNode() 
{ 
  return (ViNTreeNode*)  
             ListItem<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>::Root(); 
}


inline
ViNTreeNode const *ViNTreeNode::GetParentNode() const
{ 
  return (ViNTreeNode const *) 
             ListItem<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>::Root(); 
}

inline
ViNTreeNode::ConPolyhIter::operator ViNTreeNode const* () const
            { return _CurPtr; }

inline
int ViNTreeNode::GetViClassID() const { return GetInheritorType(); }

#endif
