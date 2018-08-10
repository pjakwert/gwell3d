#ifndef VIPOLYHHIERLIST_HH
#define VIPOLYHHIERLIST_HH

/*! \file vintreenode.hh
 *  Plik zawiera definicjê klasy \link ViNTreeNode ViNTreeNode\endlink,
 *  która jest sercem struktury drzewiastej pozwlaj±cej modelowaæ otwarte
 *  ³añcuchy kinematyczne.
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
 * Identyfikuje klasê pochodn± ViElemePolyh wzglêdem klasy bazowej
 * ViNTreeNode. Klasa ViElemePolyh reimplementuje metodê
 * \link ViNTreeNode::GetInheritorType GetInheritorType\endlink.
 */
#define  IT_ELEMEPOLYH       1
/*!
 * Identyfikuje klasê pochodn± ViMultiPolyh wzglêdem klasy bazowej
 * ViNTreeNode. Klasa ViMultiPolyh reimplementuje metodê
 * \link ViNTreeNode::GetInheritorType GetInheritorType\endlink.
 */
#define  IT_MULTIPOLYH       2
/*!
 * Identyfikuje klasê pochodn± ViScenePolyhList wzglêdem klasy bazowej
 * ViNTreeNode. Klasa ViMultiPolyh reimplementuje metodê
 * \link ViNTreeNode::GetInheritorType GetInheritorType\endlink.
 */
#define  IT_SCENEPOLYHLIST   3


/*!
 *  Definicja typu ma znaczenie pomocnicze. Reprezentuje on
 *  zarz±dcê listy potomków danego wêz³a n-drzewa.
 *  Klasa okre¶lana nazw± tego typu jest dziedziczona
 *  przez klasê ViNTreeNode.
 */
typedef List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>  ViDescList;

/*!
 *  Definicja typu ma znaczenie pomocnicze. Reprezentuje on
 *  zarz±dcê kolejki elementów interfejsu sterowania zwi±zanych
 *  z dan± bry³±. Klasa okre¶lana nazw± tego typu jest dziedziczona
 *  przez klasê ViNTreeNode.
 *  Programista nie powinien odwo³ywaæ siê bezpo¶rednio
 *  do metod tej listy. Konstrukcja jest wprowadzona dla zachowania
 *  integralno¶ci struktury danych.
 */
typedef List<ViKinemCtrlItem,ID_KINEMCTRL_NTREENODE> ViCtrlInterfList;

/*!
 * Klasa ta jest podstaw± drzewiastej struktury powi±zañ obiektów klas,
 * które j± dziedzicz± (tzn. \link ViElemePolyh ViElemePolyh\endlink,
 *  \link ViMultiPolyh ViMultiPolyh\endlink)
 *
 * Jako podklasy zdefiniowane s± klasy iteratorów
 * ViNTreeNode::ConPolyhIter i ViNTreeNode::VarPolyhIter.
 * Umo¿liwiaj± one przegl±d ca³ego drzewa powi±zañ obiektów w porz±dku
 * \e preorder.
 * Pierwsza z wymienionych klas udostêpnia przegl±dane obiekty w trybie
 * \e sta³ym, za¶ drugi w trybie \e modyfikacji.
 * Opisywane iteratory tworzone s± przez metody 
 * \link ViNTreeNode::ConBegin_PolyhHierList
 *                   ConBegin_PolyhHierList\endlink i
 * \link ViNTreeNode::VarBegin_PolyhHierList
 *                   VarBegin_PolyhHierList\endlink.
 *
 * Przyk³ad u¿ycia iteratora ViNTreeNode::ConBegin_Polyh:
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
    *  Klasa ta pe³ni rolê pomocnicz± i grupuje struktury danych
    *  wykorzystywane na etapie zapisywania parametrów opisu bry³y
    *  do bufora znakowego.
    */
   class ParamDescrBuff {
     /*!
      *  Bufor znakowy wykorzystywany do zapisu wybranych parametrów.
      */
      ExtString _Buffer;
     /*!
      *  Przechowuje informacjê o typie k±tów opisuj±cych macierz
      *  rotacji.
      */
      MatrixH3f::AnglesType    _AngType;
     /*!
      *  Przechowuje informacjê o rodzaju jednostek, w których wyra¿one
      *  s± k±ty (stopnie lub radiany).
      */
      AngleUnit                _AngUnit;

    public:

     /*!
      *  Udostêpnia zawarto¶æ bufora znakowego.
      */
      const char *Get() const { return _Buffer; }
     /*!
      *  Udostêpnia bufor znakowy do modyfikacji.
      */
      ExtString&  Use() { return _Buffer; }
     /*!
      * Zmienia informacjê o typie k±tów rotacji.
      * \param AType - nowa warto¶æ dla okre¶lenia typów k±tów rotacji.
      * \post Do pola 
      *   \link ViNTreeNode::ParamDescrBuff::_AngType _AngType\endlink
      *   wpisana zostaje nowa warto¶æ przekazana przez parametr \e AType.
      */
     void SetAngType(MatrixH3f::AnglesType AType) { _AngType = AType; }
     /*!
      * Udostêpnia warto¶æ pola
      * \link ViNTreeNode::ParamDescrBuff::_AngType _AngType\endlink 
      * okre¶laj±c± typ k±tów rotacji.
      */
     MatrixH3f::AnglesType GetAngType() const { return _AngType; }

     /*!
      * Zmienia informacjê o rodzaju jednostek, w których wyra¿one
      * s± k±ty.
      * \param AUnit - nowa warto¶æ dla okre¶lenia typów k±tów rotacji.
      * \post Do pola 
      *   \link ViNTreeNode::ParamDescrBuff::_AngUnit _AngUnit\endlink
      *   wpisana zostaje nowa warto¶æ przekazana przez parametr \e AUnit.
      */
     void SetAngUnit(AngleUnit AUnit) { _AngUnit = AUnit; }
     /*!
      * Udostêpnia warto¶æ pola
      * \link ViNTreeNode::ParamDescrBuff::_AngUnit _AngUnit\endlink 
      * okre¶laj±c± rodzaj jednostek k±tów rotacji.
      */
     AngleUnit GetAngUnit() const { return _AngUnit; }

     /*!
      *  Inicjalizuje zawarto¶æ bufora znakowego jako pust±, 
      *  typ k±tów jako k±ty Eulera oraz jednostki, w których
      *  wyra¿one s± k±ty jako stopnie.
      */
      ParamDescrBuff() { _AngType = MatrixH3f::AT_Euler;  _AngUnit = AU_Deg; }
   };

   /*!
    *  Pole jest wykorzystywane jako bufor w operacjach zapisu.
    */
   static ParamDescrBuff _TmpBuff;

   /*!
    * Pole przechowuje nazwê wêz³a. S³u¿y ona do jej 
    * identyfikacji. Powinna ona byæ unikalna
    * w ramach danej ¶cie¿ki drzewiastej struktury obiektu
    * z³o¿onego. Stanowi ona nazwê wêz³a w tej strukturze
    *
    * Nie zak³ada siê, ¿e wymóg ten musi byæ
    * bezwzglêdnie spe³niony. Jednak jego niespe³nienie mo¿e
    * prowadziæ do niejednoznaczno¶ci przy zewnêtrznych poleceniach
    * manipulowania bry³±. 
    */
  ExtString  _IndivName;

   /*!
    *  Zawiera macierz transformacji do uk³adu wspó³rzêdnych rodzica, tzn.
    *  wêz³a w strukturze drzewiastej, który znajduje siê bezpo¶rednio
    *  nad wêz³em, który jest rozwa¿anym tu obiektem.
    */
  ViMatrix3f  _Transf2ParentCoord; 


   /*!
    *  Metoda umo¿liwia udostêpnia bufor zapisu dla operacji modyfikacji
    *  jego zawarto¶ci.
    *  Metoda przeznaczona ona jest do wykorzystania przy operacjach zapisu
    *  i odczytu plików z opisem bry³.
    */
   static ExtString &UseBuff() { return _TmpBuff.Use(); }


 protected:

   void BindWithCtrlInterfaceItem(ViKinemCtrlItem *pCItem);

   /*!
    * Uniewa¿nia flagê dla struktur zale¿nych do wspó³rzêdnych wierzcho³ków
    * dla dowolnego widoku. Operacja wykonywana tylko dla danego wêz³a.
    */
   void ValidFlag_ResetDependedOnViewVtx() { VF_ResetDependedOnViewVtx(); }


   /*!
    *  Metoda umo¿liwia zapisanie tekstu do bufora.
    *  Przeznaczona ona jest do wykorzystania przy operacjach zapisu
    *  i odczytu plików z opisem bry³.
    *  \param Str - ³añcuch znaków, który ma byæ zapisany do bufora.
    */
   static void WriteToBuff(const char *Str) { _TmpBuff.Use() << Str; }

   /*!
    *  Metoda umo¿liwia udostêpnia bufor zapisu.
    *  Przeznaczona ona jest do wykorzystania przy operacjach zapisu
    *  i odczytu plików z opisem bry³.
    */
   static ExtString const &GetBuff() { return _TmpBuff.Use(); }


   /*!
    *  Metoda zapisuje parametry bry³y, które przechowywane s± w obiekcie
    *  klas ViNTreeNode. Klasy dziedzicz±ce ViNTreeNode musz± 
    *  równie¿ implementowaæ metodê o tej nazwie. Oczekuje siê, ¿e zapis
    *  parametrów rozpoczyna siê od pierwszej kolumny. Wiersze tekstu
    *  rozdzielane s± znakiem przej¶cia do nowej linii.\n
    *  Zapis parametrów musi objemowaæ tylko i wy³±cznie parametry zwi±zane
    *  z definicj± danej klasy, a nie klas bazowych.
    *  \param  Descr - (\b out) do bufora wpisywany jest zestaw parametrów
    *                 opisuj±cych dan± bry³ê.
    */
   void WriteDescriptionTo(ExtString &Descr) const;

   /*!
    *  Metoda jest przeznaczona do zainicjalizowania zapisu zapisu 
    *  wszystkich parametrów opisu bry³y. Jest ona redefiniowana w ka¿dej
    *  z klas dziedzicz±cych klasê ViNTreeNode zdefiniowanych
    *  poprzez makro 
    *  \link vihierarchyline.hh::DEFPOLYHCLASS DEFPOLYHCLASS\endlink.
    *  Metoda \e WriteAllParamToBuff jest automatycznie redefiniowana
    *  poprzez zastosowanie szablonu ViHierarchyLine.
    *  \see vihierarchyline.hh::DEFPOLYHCLASS
    *  \see  ViHierarchyLine::WriteAllParamToBuff
    *  \param Margin - wielko¶æ lewego marginesu (ilo¶æ spacji jaka 
    *                 ma byæ wstawiona przed zapisem ka¿dej z linii
    *                 opisu parametrów).
    */
   virtual void WriteAllParamToBuff(unsigned int Margin) const { }

 public:


   /*!
    * Udostêpnia pierwszego potomka. Jest on udostêpniany w trybie 
    * modyfikacji.
    *
    * Metoda realizuej bezpo¶redni dostêp do listy potomków z pominiêciem 
    * iteratorów.
    */
   ViNTreeNode *FirstDesc() 
     { return List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>::First(); }

   /*!
    * Udostêpnia pierwszego potomka. Jest on udostêpniany w trybie sta³ym.
    *
    * Metoda realizuej bezpo¶redni dostêp do listy potomków z pominiêciem 
    * iteratorów.
    */
   const ViNTreeNode *FirstDesc() const
     { return List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>::First(); }
   /*!
    *  Udostêpnia nastêpnego potomka z listy wêz³ów, do której nale¿y dany
    *  wêze³.
    *  Potomek udostêpniany jest w trybie modyfikacji.
    *
    * Metoda realizuej bezpo¶redni dostêp do listy potomków z pominiêciem 
    * iteratorów.
    */
   ViNTreeNode *NextNode() 
     { return ListItem<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>::Next(); }

   /*!
    *  Udostêpnia nastêpnego potomka z listy wêz³ów, do której nale¿y dany
    *  wêze³.
    *  Potomek udostêpniany jest w trybie sta³ym.
    *
    * Metoda realizuej bezpo¶redni dostêp do listy potomków z pominiêciem 
    * iteratorów.
    */
   const ViNTreeNode *NextNode() const
     { return ListItem<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>::Next(); }



  /*!
   *  Udostêpnia referencjê do podklasy, która zawiera pola i 
   *  metody umo¿liwiaj±ce manipulacjê lokalizacj± danego elementu
   *  w li¶cie (patrz opis szablonu ListItem). Metoda ta na poziomie
   *  klasy ViNTreeNode nie ma zastosowania. Przydaje siê ona
   *  w klasach, które dziedzicz± klasê ViNTreeNode oraz dodatkowa
   *  samodzieln± klasê utworzon± z szablonu ListItem (tak jest np.
   *  w przypadku klasy ViMultiPolyh).
   *  W takich sytuacjach metoda ta umo¿liwia ominiêcie 
   *  niejednoznaczon¶ci przy odwo³ywaniu siê do metod szablonów ListItem.
   *
   *  Metoda zwraca referencjê w trybie modyfikacji.
   */
   ListItem<ViNTreeNode,IDPRIMITIVE,ViNTreeNode> &
                              PolyhHierListItemField() { return *this; }


  /*!
   *  Udostêpnia referencjê do podklasy, która zawiera pola i 
   *  metody umo¿liwiaj±ce manipulacjê lokalizacj± danego elementu
   *  w li¶cie (patrz opis szablonu ListItem). Metoda ta na poziomie
   *  klasy ViNTreeNode nie ma zastosowania. Przydaje siê ona
   *  w klasach, które dziedzicz± klasê ViNTreeNode oraz dodatkowa
   *  samodzieln± klasê utworzon± z szablonu ListItem (tak jest np.
   *  w przypadku klasy ViMultiPolyh).
   *  W takich sytuacjach metoda ta umo¿liwia ominiêcie 
   *  niejednoznaczon¶ci przy odwo³ywaniu siê do metod szablonów ListItem.
   *
   *  Metoda zwraca referencjê w trybie modyfikacji.
   */
   const ListItem<ViNTreeNode,IDPRIMITIVE,ViNTreeNode> &
                             PolyhHierListItemField() const { return *this; }

  /*!
   *  Zwraca nazwê klasy pochodnej. Metoda wykorzystywana jest
   *  przez metody zapisu parametrów bry³y do oznaczania i identyfikacji
   *  poszczególnych sekcji zapisu.
   */
   const char *GetClassName() const { return "ViNTreeNode"; }

  /*!
   *  Zwraca nazwê finalnej klasy danego obiektu. Przy tworzeniu
   *  w³asnej klasy metody tej nie nale¿y reimplementowaæ.
   *  Jest ona automatycznie reimplementowana przez zastosowanie
   *  makra \link vihierarchyline.hh::DEFPOLYHCLASS DEFPOLYHCLASS\endlink.
   */
   virtual const char *GetFinalClassName() const { return GetClassName(); }


  /*!
   *  Udostêpnia identyfikator klasy obiektu. Indentyfikator ten pozwala
   *  rozpoznaæ klasê pochod± w przypadku, gdy do dyspozycji jest tylko
   *  wska¼nik na obiekt klasy ViNTreeNode. Klasy pochodne, które mog±
   *  byæ w ten sposób rozpoznane to: ViElemePolyh, ViMultiPolyh oraz
   *  ViScenePolyhList.\n
   *  Identyfikatory tych klas s± zwracane równie¿ wtedy, gdy s± one 
   *  dziedziczone przez inne klasy. Jest to podyktowane konieczno¶ci±
   *  istnienia mo¿liwo¶ci stwierdzenia, z której z wymienionych wcze¶niej
   *  podstawowych klas dla biblioteki VIONA, zosta³a wprowadzona dana
   *  klasa.
   *
   *  Dla w³asnych tworzonych klas do jej identyfikacji mo¿na u¿yæ 
   *  reimplementacji metody
   *  \link ViNTreeNode::GetFinalClassID GetFinalClassID()\endlink. 
   */
   int GetViClassID() const;


   /*!
    * Metoda umo¿liwia odpowiednie przetworzenie i sk³adowanie opisów
    * parametrów generowanych przez metody \b WriteDescripTo z ka¿dej
    * z klas wchodz±cych w hierarchiê dziedziczenia klasy ViHierarchyLine.
    * \warning Metoda ta nie mo¿e byæ nadpisywana w innych w innych
    *           klasach pochodnych dziedzicz±cych klasê ViNTreeNode.
    * \param Margin - (\b in) wielko¶æ lewego marginesu, który ma byæ
    *              zachowany przy zapsie poszczególnych linii opisu
    *              parametrów bry³y.
    * \param ParamDescr - zawiera parametry opisu bry³y wygenerowane przez
    *              dan± klasê.
    * \param TypeName - (\b in) zawiera nazwê klasy, na poziomie której 
    *              wygenerowany
    *              zosta³ przekazywany opis parametrów bry³y.
    * \param ObjPtr - (\b in) wska¼nik na obiekt przekazuj±cy dany opis
    *              parametrów bry³y.
    */
   void AddDescripToBuff( unsigned int       Margin,
                          ExtString const   &ParamDescr, 
                          const std::string &TypeName,
                          void const        *ObjPtr
                        ) const;

   /*!
    *  Metoda realizuje zapis parametrów do bufora.
    *  Metoda ta jest przeci±¿ana przy zastosowaniu szablonu ViHierarchyLine.
    *  Szablon ten s³u¿y do dziedzieczenia klasy bazowej 
    *  i umo¿liwienie utowrzenie odpowiedniego ci±gu wywo³añ metod 
    *  dla ka¿dej z klas bazowych zgodnie z hierarchi± dziedziczenia.
    *  Przyk³ad dziedzieczenia klas bazowych z wykorzystaniem szablonu
    *  ViHierarchyLine mo¿na znale¼æ w kontsturkcji klas
    *  ViElemePolyh i ViMultiPolyh.
    * \param Margin - wielko¶æ lewego marginesu, który ma byæ zachowany
    *              przy zapsie poszczególnych linii opisu parametrów 
    *              bry³y.
    */
   void WriteDescripToBuff( unsigned int           Margin,
                            const ViNTreeNode  *
                          ) const;



   /*!
    *  Udostêpnia listê bezpo¶rednich potoków danego n-drzewa.
    *  Lista udostêpniana jest w trybie sta³ym.
    */
   const ViDescList &GetDescList() const { return *((const ViDescList*)this);}

   /*!
    *  Udostêpnia listê bezpo¶rednich potoków danego n-drzewa.
    *  Lista udostêpniana jest w trybie modyfikacji.
    */
   ViDescList &UseDescList() { return *((ViDescList*)this);}

   /*!
    * Usuwa wszystkich potomków danego wêz³a.
    */
   void DeleteAllDesc() {  UseDescList().CancelList(); }



  /*!
   *  Metoda ma znaczenie pomocnicze. Jest ona podstaw± hierarchii wywo³añ 
   *  metod interpretacji opisów parametrów dla poszczególnych klas wchodz±cych
   *  w hierarchiczn± strukturê dziedziczenia.
   *  \param Descr - (\b in) zawiera opis inicjalicji ca³ego wêz³a. W opisie 
   *           musz± znajdowaæ siê sekcje opisu inicjalizacji poszczególnych
   *           klas wchodz±cych w sk³ad hierarchii dziedziczenia
   *           klasy pochodnej, której obiektem ma byæ dany wêze³.
   *  \param pNode - ma znaczenie pomocnicze. Pozwala na rozró¿nienie 
   *           przeci±¿onej metody i jednoznacznego jej zwi±zania z dan±
   *           klas±.
   */
   void InterpretParamDescr( const ViNodeDescr &  Descr, 
                             const ViNTreeNode *pNode
                           );
   /*!
    *  Metoda ta jest definiowana w szablonie ViHierarchyLine 
    *  (patrz \link ViHierarchyLine::InterpretParamDescr   
    *  ViHierarchyLine::InterpretParamDescr\endlink ) i
    *  odpowiedzialna jest za wywo³anie metod interpretuj±cych
    *  zapis parametrów inicjalizacji obiektu dla klas wchodz±cych 
    *  w hierarchiê dziedziczenia klasy ViNTreeNode
    *  (w hierarchii tej pomijane s± pomocnicze szablony klas ViHierarchyLine).
    *  Ze wzglêdu na to, ¿e klasa ViNTreeNode nie dziedziczy szablonu
    *  ViHierarchyLine, metoda ta musi byæ jawnie zdefiniowana w tej klasie.
    *
    *  Metoda \b InterpretParamDescr realizuje analogiczne operacje jak jej
    *  odpowiednik zdefiniowany w szablonie ViHierarchyLine.
    *  Efektem dzia³ania tej metody jest wowo³anie kolejnych metod 
    *  interepretuj±cych zapis parametrów charakterystycznych dla 
    *  poszczególnych
    *  klas. Wywo³ania nastêpuj± pocz±wszy do obiektu klasy bazowej, 
    *  na obiekcie klasy finalnej koñcz±c. Metoda ta odpowiedzialna
    *  jest równie¿ za wydobycie z opisu danego wêz³a (przez wêze³ rozumiany
    *  jest pojedynczy element wchodz±cy w strukturê hierarchiczn± bry³y
    *  z³o¿onej) tego opisu,
    *  który dotyczy odpowiedniej klasy.
    *  \param Descr - zawiera opis wêz³a.
    *  \exception ViException_Syntax - jest zg³aszany z kodem b³êdu w
    *        przypadku, ERRMSG_SYNTAX__NO_CLASS_DESCR, gdy w opisie danego
    *        wêz³a nie znaleziono opisu dla danej klasy.
    *          
    */  
   virtual void InterpretParamDescr(const ViNodeDescr &  Descr);


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
   *  \exception ViException_Syntax - mo¿e byæ zg³oszony z kodami b³êdów:
   *   \li  \link sxinterp.hh::ERRNUM_SX__UNEXP_CHAR 
   *                       ERRNUM_SX__UNEXP_CHAR\endlink - gdy napotkany zosta³
   *                inny znaku ni¿ oczekiwany.
   *   \li \link sxinterp.hh::ERRNUM_SX__FAIL_FLOAT
   *             ERRNUM_SX__FAIL_FLOAT\endlink - w przypadku niemo¿no¶ci
   *             wczytania liczby typu \e float.
   *   \li \link sxinterp.hh::ERRNUM_SX__FAIL_INT ERRNUM_SX__FAIL_INT\endlink -
   *             w przypadku niemo¿no¶ci wczytania liczby typu \e integer.
   *   \li \link sxinterp.hh::ERRNUM_SX__NO_KEYWORDS 
   *             ERRNUM_SX__NO_KEYWORDS\endlink - gdy brak listy ze s³owami
   *             kluczowymi.
   *   \li \link sxinterp.hh::ERRNUM_SX__START_NO_KEYWORD
   *             ERRNUM_SX__START_NO_KEYWORD\endlink - gdy napotkany znak
   *             nie mo¿e byæ pocz±tkiem ¿adnego s³owa kluczowego.
   *   \li \link sxinterp.hh::ERRNUM_SX__NO_KEYWORD
   *                                            ERRNUM_SX__NO_KEYWORD\endlink
   *             - gdy znalezione s³owo nie jest ¿adnym z oczekiwanych
   *               s³ów kluczowych.
   *   \li \link sxinterp.hh::ERRNUM_SX__NO_WORD ERRNUM_SX__NO_WORD\endlink -
   *             gdy nie znaleziono ¿adnego s³owa.
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
       * Wska¼nik na obiekt, dla którego iterator ten zosta³
       * zainicjalizowany.
       */
      ElemType *_IniPtr;
      /*!
       * Wska¼nik na na aktualnie iterowany obiekt.
       */
      ElemType *_CurPtr;
     public:
      /*!
       *  Ustawia iterator na dany element.
       *  \param  pElem - wska¼nik na nowy element.
       *  \post   Do pola 
       *    \link ViNTreeNode::ConPolyhIter::_CurPtr _CurPtr\endlink
       *    przepisany zostaje adres udostêpniony przez parametr \e pElem.
       *  \warning Metoda ta nie powinna byæ stosowana z du¿± rozwag±.
       */
      void Set(ElemType *pElem) { _CurPtr = pElem; }

      /*!
       *  Przywraca stan pocz±tkowy iteratora.
       */
      void Reset() { _CurPtr = _IniPtr; }

      /*!
       * Inicjalizuje iterator dla danego elementu klasy ViNTreeNode.
       * \param PHLst - referencja do wêz³a struktury drzewiastej, dla
       *                którego bêdzie zainicjalizowany iterator.
       */
      UniPolyhIter(ElemType &PHLst): _IniPtr(&PHLst) { Reset();}

       /*!
	*  Powoduje przej¶cie do nastêpnego elementu w strukturze drzewiastej.
	*  Przegl±danie struktury realizowane jest w porz±dku \e preorder.
	*/
      UniPolyhIter &operator ++ () 
        {
          if (_CurPtr->BaseListType::First()) { // Id¼ w dó³ drzewa.
                 _CurPtr = _CurPtr->BaseListType::First();  return Iter_SetStatus(true);
          }
          if (_IniPtr == _CurPtr)  return Iter_SetStatus(false);
          if (_CurPtr->Next())  { // Id¼ do nastêpnego wêz³a na tym poziomie.
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
	* Powoduje przej¶cie do poprzedniego elementu w strukturze drzewiastej.
	* Przegl±danie struktury realizowane jest w porz±dku \e preorder.
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
    *  Klasa ta definiuje iterator pozwalaj±cy przegl±daæ wszyskie
    *  obiekty ViNTreeNode. Ich wzajemnie po³±czenia 
    *  tworz± strukturê drzewiast±. Dziêki temu, ¿e s± one dziedziczone
    *  przez obiekty klasy ViElemePolyh i ViMultiPolyh, pozwalaj± tym
    *  samym na tworzenie struktury drzewiastej obiektów tych klas.
    *
    * Przyk³ad u¿ycia iteratora:
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
       * \param PHLst - referencja do wêz³a struktury drzewiastej, dla
       *                którego bêdzie zainicjalizowany iterator.
       */
      ConPolyhIter(ViNTreeNode const &PHLst): 
	UniPolyhIter<ConPolyhIter,const ViNTreeNode,
                  List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>,
                  ListItem<ViNTreeNode,IDPRIMITIVE,ViNTreeNode> > (PHLst) {}


      /*!
       *  Konwerter udostêpnia wska¼nik bie¿ego iterowanego elementu.
       */
      operator ViNTreeNode const* () const;
   };  //------------------ ConPolyhIter -------------------------------------


   /*!
    *  Klasa ta definiuje iterator pozwalaj±cy przegl±daæ wszyskie
    *  obiekty ViNTreeNode. Ich wzajemnie po³±czenia 
    *  tworz± strukturê drzewiast±. Dziêki temu, ¿e s± one dziedziczone
    *  przez obiekty klasy ViElemePolyh i ViMultiPolyh, pozwalaj± tym
    *  samym na tworzenie struktury drzewiastej obiektów tych klas.
    *  Przegl±dane obiekty udostêpniane s± w trybie modyfikacji.
    *
    * Przyk³ad u¿ycia iteratora:
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
       * \param PHLst - referencja do wêz³a struktury drzewiastej, dla
       *                którego bêdzie zainicjalizowany iterator.
       */
      VarPolyhIter(ViNTreeNode &PHLst): 
              UniPolyhIter<VarPolyhIter,ViNTreeNode,
                   List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>,
                   ListItem<ViNTreeNode,IDPRIMITIVE,ViNTreeNode> >(PHLst) {}
      /*!
       *  Konwerter udostêpnia wska¼nik bie¿ego iterowanego elementu.
       */
     operator ViNTreeNode * () const { return (ViNTreeNode*)_CurPtr; }
   };  //------------------ VarPolyhIter -------------------------------------



   /*!
    * Inicjalizuje obiekt nadaj±c mu nazwê i resetuj±c wszystkie flagi.
    * \param Name - nazwa obiektu.
    * \post Nazwa obiektu zapisana zostaje w polu 
    *   \link ViNTreeNode::_IndivName _IndivName\endlink,
    *   stan wszystkich flag zostaje zresetowany.
    */
   ViNTreeNode(char const *Name = "noname");
   ~ViNTreeNode() {};


   bool ShouldCallForClassDescr(const char *) const { return true; }

   /*!
    *  Udostêpnia wska¼nik do zarz±dcy sceny, który jest jest polem 
    *  w klasie ViScene. W przypadku gdy obiekt nie jest do³±czony
    *  do sceny, zwraca adres \p NULL.
    */
   ViNTreeNode const *GetRoot_Scene() const;

   /*!
    *  Udostêpnia wska¼nik do zarz±dcy sceny, który jest jest polem 
    *  w klasie ViScene. W przypadku gdy obiekt nie jest do³±czony
    *  do sceny, zwraca adres \p NULL.
    */
   ViNTreeNode *GetRoot_Scene() 
   { return 
      (ViNTreeNode *)(*(ViNTreeNode const*)this).GetRoot_Scene();
   }

  /*!
   * Udostêpnia warto¶æ okre¶laj±c± typ k±tów rotacji.
   */
   static MatrixH3f::AnglesType GetAngType() { return _TmpBuff.GetAngType();} 

  /*!
   * Udostêpnia warto¶æ 
   * okre¶laj±c± rodzaj jednostek k±tów rotacji.
   */
   static AngleUnit  GetAngUnit() { return _TmpBuff.GetAngUnit(); }


   /*!
    * Metoda umo¿liwia sprawdzenie czy dany wêze³ ma jakiegokolwiek 
    * potomka (w sensie struktury drzewiastej).
    * \retval true - gdy wêze³ ma potomka,
    * \retval false - w przypadku przeciwnym.
    */
   bool IsDescendant() const 
     { return  List<ViNTreeNode,IDPRIMITIVE,ViNTreeNode>::IsAny(); }

    /*====================================================================
     * Uniewa¿nia flagê wa¿no¶ci obliczeñ dla wspó³rzêdnych globalnych 
     * i struktur od nich zale¿nych.
     */
   void ValidFlag_ResetGlbVtx(bool ForAllObjectFamily = true); 

    /*!
     * Ustawia wa¿no¶æ flagi dla wspó³rzêdnych globalnych i uniewa¿nia
     * flagi dla dodatkowych struktur od nich zale¿nych.
     * Jako dodatkowe struktury rozumie siê struktury zwi±zane z poszczególnymi
     * widokami definiowanymi w klasach pochodnych poza j±drem reprezentacji
     * geometrycznej obiektów.
     * \param  ForAllObjectFamily - Je¶li \p true (domy¶lnie), to ustawian 
     *            jest  flaga VFLAG_TEST_DESCENDANTS dla wszystkich kolejnych
     *            przodków danego wêz³a. Je¶li \p false, to flagi resetowane
     *            s± tylko dla danego obiektu elementarnego.
     * \post Ustawiona zostaje flaga GLB_VTX,
     *     uniewa¿nione zostaj± flagi (w danym wêzle i dla wszystkich widoków):
     *     VIEW_VTX,  RECT_OUT, FACE_POLY, FACE_RGN, FACE_VIEW_RGN
     */
   void ValidFlag_SetGlbVtx(bool ForAllObjectFamily = true); 



  /*!
   * Ustawia wa¿no¶æ flagi dla wspó³rzêdnych globalnych i uniewa¿nia
   * flagi dla struktur od nich zale¿nych.   Akcja ta jest realizowana
   * dla danego wêz³a i wszystkich jego potomków.
   *
   * \param  ForAllObjectFamily - Je¶li true (domy¶lnie), to ustawian jest flaga 
   *                             VFLAG_TEST_DESCENDANTS dla wszystkich kolejnych
   *                             przodków danego wêz³a.
   *                             Je¶li false, to flagi resetowane s± tylko dla
   *                             danego obiektu elementarnego.
   * \post Ustawiona zostaje flaga
   *         GLB_VTX,
   *       Uniewa¿nione zostaj± flagi (w danym wêzle i dla wszystkich widoków):
   *         VIEW_VTX,  RECT_OUT, FACE_POLY, FACE_RGN, FACE_VIEW_RGN
   */
   void ValidFlag_Set4All_GlbVtx(bool ForAllObjectFamily = true); 


  /*!
   *  Uniewa¿nia flagê dla  globalnych wspó³rzêdnych wierzho³ków. Prowadzi to
   *  do uniewa¿nienia równie¿ flag zwi±zanych ze struktrami pochodnymi,
   *  np. wspó³rzêdne wierzcho³ków dla widoków, obrys bry³y. Akcja ta jest 
   *  realizowana dla danego wêz³a i wszystkich jego potomków.
   *
   *  \param  ForAllObjectFamily - Je¶li true (domy¶lnie), to ustawian jest 
   *                     flaga VFLAG_TEST_DESCENDANTS dla wszystkich kolejnych
   *                     przodków danego wêz³a.
   *                     Je¶li false, to flagi resetowane s± tylko dla
   *                     danego obiektu elementarnego.
   *
   *  \post Uniewa¿nione zostaj± flagi:
   *       GLB_VTX, VIEW_VTX,  RECT_OUT, FACE_POLY, FACE_RGN, FACE_VIEW_RGN
   */
   void ValidFlag_Reset4All_GlbVtx(bool ForAllObjectFamily = true); 


    /*!
     * Uniewa¿nia flagê dla struktur pomoczniczych zale¿nych od wspó³rzêdnych
     * globalnych. Metoda wywo³ywana przez ValidFlag_ResetGlbVtx. Metoda 
     * przeznaczona do reimplementacji do resetowania flag dla widoków.
     * Reimplementacja tej metody musi byæ zrealizowana w klasie pochodnej.
     */
   virtual void ValidFlag_ResetAuxDependedOnGlbVtx() {}




  /*!
   *  Uniewa¿nia flagê dla wspó³rzêdnych dla danego widoku. Prowadzi to
   *  do uniewa¿nienia równie¿ flag zwi±zanych ze struktrami pochodnymi,
   *  np. wspó³rzêdne wierzcho³ków dla widoków, obrys bry³y. Akcja ta jest 
   *  realizowana dla danego wêz³a i wszystkich jego potomków.
   *  Metoda wyo³uje dla ka¿dego wêz³a metodê 
   *  \link ViNTreeNode::ValidFlag_ResetViewVtx 
   *        ValidFlag_ResetViewVtx\endlink, która jest metod± wirtulan± i 
   *  powinna byæ reimplementowana w klasach pochodnych, które powi±zane
   *  s± zestrukturami danych dla poszczególnych widoków.
   *
   *  \param  NView - numer widoku.
   *  \param  ForAllObjectFamily - je¶li \p true (domy¶lnie), to ustawiana jest
   *                    flaga VFLAG_TEST_DESCENDANTS dla wszystkich kolejnych
   *                    przodków danego wêz³a.
   *                    Je¶li false, to flagi resetowane s± tylko dla
   *                    danego obiektu elementarnego.
   *
   *  \post Uniewa¿nione zostaj± flagi:
   *       VIEW_VTX,  RECT_OUT, FACE_POLY, FACE_RGN, FACE_VIEW_RGN
   */
   void ValidFlag_Reset4All_ViewVtx(int NView, bool ForAllObjectFamily = true);


    /*!
     * Uniewa¿nia flagê dla danego widoku dla struktur zale¿nych od
     * wspó³rzêdnych wierzcho³ków dla danego widoku.
     * Metoda ta powinna byæ reimplementowana w klasach pochodnych
     * zawieraj±cych struktury danych zwi±zanych z poszczególnymi widokami.
     * Na poziomie klasy ViNTreeNode metoda ta nie realizuje ¿adnej akcji.
     * \param  ViewNr - numer widoku,
     * \param  ForAllObjectFamily - decyduje o tym, czy akcja ma byæ 
     *             przeprowadzona równie¿ dla wszystkich wêz³ów pochodnych
     *             (warto¶æ \p true, jest to warto¶æ domy¶lna tego parametry),
     *             czy te¿ tylko dla danego wêz³a.
     */
   virtual void ValidFlag_ResetViewVtx
                       (int ViewNr, bool ForAllObjectFamily = true) {};


    /*!
     * Ustawia flagê swojego przodka, która informuje, ¿e dane przynajmniej 
     * jednego z potomków musz± byæ zaaktualizowane.
     */
   void ValidFlag_SetTestDescants4Acestor(bool SetForAllAncestor=true); 


    /*!
     * Ustawia flagê, która informuje ¿e dane obliczeniowe przynajmniej 
     * jednego z potomków musz± byæ zaaktualizowane.
     */
   void ValidFlag_SetTestDescants() { VF_SetTestDescants(); }


    /*!
     * Resetuje (uniewa¿nia) wszystkie flagi tylko dla danego
     * obiektu elementarnego.
     */
   void ValidFlag_ResetAll() { VF_ResetAll(); }


    /*!
     * Zwraca \p true gdy flaga jest ustawiona, co oznacza, ¿e wyliczone
     * wcze¶niej wspó³rzêdne globalne s± wci±¿ aktualne. W przeciwnym 
     * przypadku zwraca warto¶æ \p false.
     */
   bool IsFlagValid_GlbVtx()      const { return IsVF_GlbVtx(); }

    /*!
     * Zwraca \p true gdy flaga jest ustawiona, co oznacza, ¿e wyliczony
     * wcze¶niej obrys prostopad³o¶cienny (we wspó³rzêdnych
     * globalnych) danej bry³y (je¿eli klas± pochodn± jest ViElemePolyh)
     * lub zbioru byry³ (je¿eli klas± pochodn± jest ViMultiPolyh)
     *  jest wci±¿ aktualny.
     * W przeciwnym przypadku zwraca warto¶æ \p false.
     */
   bool IsFlagValid_RectOutlineBox3f() const {return IsVF_RectOutlineBox3f();}

    /*!
     * Zwraca \p true gdy flaga jest ustawiona, co oznacza, ¿e wyliczone
     * wcze¶niej wspó³rzêdne dla wszystkich widoków s± wci±¿ aktualne.
     * W przeciwnym przypadku zwraca warto¶æ \p false.
     */
   bool IsFlagValid_ViewVtx()     const { return IsVF_ViewVtx(); }

   /*!
    *  Metoda jest zasz³o¶ci± i przewidziana jest do usuniêcia. Nie
    *  nale¿y z niej korzystaæ.
    */
  virtual bool IsFlagValid_ViewVtx(int NView) const { return true; };

   /*!
    * Udostêpnia wska¼nik do wêz³a bêd±cego rodzicem (w sensie struktury 
    * drzewiastej) wêz³a, dla którego wywo³ywana jest niniejsza metoda.
    */
  ViNTreeNode *GetParentNode();

  const ViElemePolyh *GetAncestor_ElemePolyh() const;
  ViElemePolyh *UseAncestor_ElemePolyh()
                { return (ViElemePolyh*) GetAncestor_ElemePolyh(); }

  const ViMultiPolyh *GetAncestor_MultiPolyh() const;
  ViMultiPolyh *UseAncestor_MultiPolyh()
                { return (ViMultiPolyh*) GetAncestor_MultiPolyh(); }



   /*!
    * Udostêpnia wska¼nik do wêz³a bêd±cego rodzicem (w sensie struktury 
    * drzewiastej) wêz³a, dla którego wywo³ywana jest niniejsza metoda.
    * Udostêpniowny wska¼nik nie pozwala modyfikowaæ wskazywanego obiektu.
    */
  const ViNTreeNode *GetParentNode() const;

   /*!
    * Metoda udostêpnia nazwê wêz³a (warto¶æ pola 
    * \link ViNTreeNode::_IndivName _IndivName\endlink). Nazwa ta stanowi
    * czê¶æ pe³nego adresu wêz³a w strukturze drzewiastej, której elementem
    * jest dany wêze³m (patrz opis pola 
    * \link ViNTreeNode::_IndivName _IndivName\endlink).
    * \return Udostêpnia ³añcuch znaków (w sensie jêzyka C) stanowi±cy nazwê
    *         wêz³a.
    */
  char const *NodeName() const {return _IndivName(); }

   /*!
    * Metoda nadaje now± nazwê danem u wêz³owi (modyfikuje warto¶æ pola 
    * \link ViNTreeNode::_IndivName _IndivName\endlink). Nazwa ta stanowi
    * czê¶æ pe³nego adresu wêz³a w strukturze drzewiastej, której elementem
    * jest dany wêze³m (patrz opis pola 
    * \link ViNTreeNode::_IndivName _IndivName\endlink).
    * \param Name - nawa nazwa dla danego wêz³a.
    * \pre \e Name != \p NULL
    * \post W polu \link ViNTreeNode::_IndivName _IndivName\endlink
    *       zostaje wpisana nowa nazwa udostêpniona poprzez parametr \e Name
    *       (zawarto¶æ ³añcucha dostêpnego porzez ten parametr zostaje 
    *       skompiowana).
    */
  void SetNodeName(char const *Name ) { _IndivName = Name; }

   /*!
    * Metoda udostêpnia nazwê wêz³a (warto¶æ pola 
    * \link ViNTreeNode::_IndivName _IndivName\endlink). Nazwa ta stanowi
    * czê¶æ pe³nego adresu wêz³a w strukturze drzewiastej, której elementem
    * jest dany wêze³m (patrz opis pola 
    * \link ViNTreeNode::_IndivName _IndivName\endlink).
    * \return Udostêpnia ³añcuch znaków (w sensie jêzyka C) stanowi±cy nazwê 
    *         wêz³a.
    * \warning Metoda ta uznana jest jako zasz³o¶æ i przewidziana jest do 
    *        usuniêcia.
    *        Z tego wzglêdu nie nale¿y jej wykorzystywaæ. Zamiast niej nale¿y
    *        pos³ugiwaæ siê metod± 
    *        \link ViNTreeNode::NodeName NodeName\endlink.
    */
  char const *GetName() const { return _IndivName(); }

   /*!
    * Metoda udostêpnia referencje do pola  
    * \link ViNTreeNode::_IndivName _IndivName\endlink. 
    * Zawiera ono nazwê wêz³a. Nazwa ta stanowi
    * czê¶æ pe³nego adresu wêz³a w strukturze drzewiastej, której elementem
    * jest dany wêze³m (patrz opis pola 
    * \link ViNTreeNode::_IndivName _IndivName\endlink).
    * \return referencjê pozwalaj±c± modyfikowaæ zawarto¶æ pola
    *      \link ViNTreeNode::_IndivName _IndivName\endlink.
    * \warning Metoda ta uznana jest jako zasz³o¶æ i przewidziana jest do 
    *   usuniêcia. Z tego wzglêdu nie nale¿y jej wykorzystywaæ. Zamiast niej 
    *   nale¿y pos³ugiwaæ siê metod± 
    *   \link ViNTreeNode::SetNodeName SetNodeName\endlink.
    */
  ExtString &UseName() { return _IndivName; }

   /*!
    * Metoda nadaje now± nazwê danem u wêz³owi (modyfikuje warto¶æ pola 
    * \link ViNTreeNode::_IndivName _IndivName\endlink). 
    * Nazwa ta stanowi
    * czê¶æ pe³nego adresu wêz³a w strukturze drzewiastej, której elementem
    * jest dany wêze³m (patrz opis pola 
    * \link ViNTreeNode::_IndivName _IndivName\endlink).
    * \param Name - nawa nazwa dla danego wêz³a.
    * \pre \e Name != \p NULL
    * \post W polu \link ViNTreeNode::_IndivName _IndivName\endlink
    *       zostaje wpisana nowa nazwa udostêpniona poprzez parametr \e Name
    *       (zawarto¶æ ³añcucha dostêpnego porzez ten parametr zostaje 
    *       skompiowana).
    * \warning  Metoda ta uznana jest jako zasz³o¶æ i przewidziana jest do 
    *        usuniêcia. Z tego wzglêdu nie nale¿y jej wykorzystywaæ. Zamiast
    *        niej nale¿y pos³ugiwaæ siê metod± 
    *        \link ViNTreeNode::SetNodeName SetNodeName\endlink.
    */
  void SetName(char const *Name ) { _IndivName = Name; }

   /*!
    * Metoda udostêpnia nazwê wêz³a (warto¶æ pola 
    * \link ViNTreeNode::_IndivName _IndivName\endlink).
    * Nazwa ta stanowi
    * czê¶æ pe³nego adresu wêz³a w strukturze drzewiastej, której elementem
    * jest dany wêze³m (patrz opis pola 
    * \link ViNTreeNode::_IndivName _IndivName\endlink).
    * \warning Nie jest zalecane pos³ugiwanie siê t± metod±. Preperowana
    *    jest metoda \link ViNTreeNode::NodeName NodeName\endlink.
    *    Wykorzystanie jej jest usprawiedliwione tylko w przypadku, gdy
    *    potrzebna jest referencja do obiektu ExtString.
    */
  ExtString const &IndivName() const { return _IndivName; }
   //=======================================================================
   // Metoda pozwala na otrzymanie macierzy transformacji do uk³adu
   //  wspó³rzêdnych globalnych danej sceny.
  int  GetMtx2GlbCoord(MatrixH3f &Mtx) const;
  int  GetMtx2RootCoord(MatrixH3f &Mtx) const; 
  int  GetMtx2LocalRootCoord(MatrixH3f &Mtx) const; 

   //=======================================================================
   // Metoda pozwala na otrzymanie macierzy transformacji z uk³adu
   // wspó³rzêdnych obiektu, który jest korzeniem ca³ego drzewa 
  int  GetMtxRoot2GlbCoord(MatrixH3f &Mtx) const;
   /*!
    * Umo¿liwia zmianê nowych warto¶ci dla macierzy transformacji
    * wspó³rzêdnych
    * dla danego wêz³a struktury ³añcucha kinematycznego do uk³adu 
    * wspó³rzêdnych rodzice tego wêz³a.
    * \param Mtx - nowe warto¶ci macierzy transformacji.
    */
  void SetMtx2ParentCoord(MatrixH3f const &Mtx);
   /*!
    * Udostêpnia macierz transformacji do uk³adu wspó³rzêdnych rodzica
    * hierarchicznej strukturze drzewa.
    */
  ViMatrix3f const &Mtx2ParentCoord() const { return _Transf2ParentCoord; }
   /*!
    * Udostêpnia macierz transformacji do uk³adu wspó³rzêdnych rodzica
    * hierarchicznej strukturze drzewa z mo¿liwo¶ci± zmian.
    */
  ViMatrix3f &UseMtx2ParentCoord() { return _Transf2ParentCoord; }


  /*!
   * Szuka w swojej li¶cie bezpo¶rednich potomków wêz³a o zadanej nazwie.
   * \param Name - nazwa szukanego wêz³a.
   * \return wska¼nik na pierwszego bezpo¶redniego potomka, którego nazwa
   *         jest zgodna z nazw± przekazan± przez parametr. Zwracany 
   *         wska¼nik jest wska¼nikiem do obiektu sta³ego.
   *         W przypadku braku
   *         takiego potomka zwracany jest adres \p NULL.
   *        
   */
  ViNTreeNode const *SeekNodeInLayer(char const *Name) const;

  /*!
   * Szuka w swojej li¶cie bezpo¶rednich potomków wêz³a o zadanej nazwie.
   * \param Name - nazwa szukanego wêz³a.
   * \return wska¼nik na pierwszego bezpo¶redniego potomka, którego nazwa
   *         jest zgodna z nazw± przekazan± przez parametr. Zwracany wska¼nik
   *         jest wska¼nikiem do obiektu modyfikowalnego.
   *         W przypadku braku
   *         takiego potomka zwracany jest adres \p NULL.
   *        
   */
  ViNTreeNode       *SeekNodeInLayer(char const *Name)
   { return (ViNTreeNode*) 
             (*(ViNTreeNode const*)this).SeekNodeInLayer(Name);
   }

  /*!
   * Szuka wêz³a traktuj±c adres podany przez parametr jako adres wzglêdem
   * wêz³a dla którego metoda ta zosta³a wywo³ana, o ile pierwszym znakiem
   * nie jest znak separatora. W przeciwnym przypadku szukanie realizowane
   * jest od korzenia ca³ej struktury drzewiastej (tzn. do listy bry³
   * z³o¿onych danej sceny).
   * \param NodeAddr  - pe³na ¶cie¿ka adresu wêz³a (wzg³êdem korzenia lub
   *                    lokalnego wêz³a).
   * \pre \e NodeAddr != \p NULL.
   * \return wska¼nik do obiektu o obiektu o podanym adresie lub wska¼nik
   *         \p NULL je¶li obiekt tak nie istnieje.
   */
  ViNTreeNode const *SeekNodeAlongPath(char const *NodeAddr ) const;

  /*!
   * Szuka wêz³a traktuj±c adres podany przez parametr jako adres wzglêdem
   * wêz³a dla którego metoda ta zosta³a wywo³ana, o ile pierwszym znakiem
   * nie jest znak separatora. W przeciwnym przypadku szukanie realizowane
   * jest od korzenia ca³ej struktury drzewiastej (tzn. do listy bry³
   * z³o¿onych danej sceny).
   * \param NodeAddr  - pe³na ¶cie¿ka adresu wêz³a (wzg³êdem korzenia lub
   *                    lokalnego wêz³a).
   * \pre \e NodeAddr != \p NULL.
   * \return wska¼nik do obiektu o obiektu o podanym adresie lub wska¼nik
   *         \p NULL je¶li obiekt tak nie istnieje.
   *        Udostêpniany obiekt poprzez zwrócony wska¼nik jest modyfikowalny.
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
   *  Zapisuje do strumienia \e ostrm informacje dotycz±ce danego wêz³a
   *  (macierze transformacji, etykiety, adres wêz³a itd.).
   *  \param  ostrm - otwarty strumieñ wyj¶ciowy, ze wzglêdu na hierarchiê
   *                  dziedziczenia klas w bibliotece standardowej mo¿e to
   *                  byæ równie¿ strumieñ klasy \b ofstream.
   *  \param  AType - okre¶la rodzaj k±tów rotacji parametryzuj±cych
   *                podmacierz rotacji dla tranformacji od uk³adu wspó³rzêdnych
   *                rodzica.\n
   *                W tej chwili
   *                obs³ugiwane s± k±ty Eulera oraz k±ty rotacji 
   *                wokó³ osi OX, OY, OZ.
   *  \param  AUnit - okre¶la w jakich jednostkach maj± byæ zapisane warto¶ci
   *                k±tów.
   *  \param  Margin - ilo¶æ spacji jak± maj± byæ poprzedzone poszczególne
   *                linie opisu parametrów.
   *  \retval true - gdy w trakcie zapisu nie wyst±pi³ ¿aden b³±d,
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
             Angles { Euler | XYZ } { Deg | Rad }: ( k±t1, k±t2, k±t3 )
             Translation: ( sk³adowa_x, sk³adowa_y, sk³adowa_z )
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
   *  Przyk³ad wygenerowanego opisu obiektu znajduje siê
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
   *  Metoda przechodzi po ca³ej strukturze drzewiastej poczynaj±c od wêz³a,
   *  dla którego zosta³a wywo³ana. Chodz±c po tej strukurze wywo³uje dla niej
   *  funkcjê, która przekazywana jest jako parametr wywo³ania tej metody.
   *  Przechodzenie nastêpuje w porz±dku preorder.
   *
   *  \param  Fun - funkcja, która jest wywo³ywana dla ka¿dego wêz³a.
   *          Parametrami tej funkcji jest wska¼nik na dany obiekt modeluj±cy
   *          bry³ê elementarn± (obiekt klasy 
   *          \link ViElemePolyh ViElemePolyh\endlink.
   *          Drugim parametrem jest jest macierz transformacji.
   *          Schodz±c coraz ni¿ej wzd³u¿ ga³êzi drzewa macierz ta jest 
   *          przemna¿ana przez kolejne macierze tranforamcji ze wsó³rzêdnych
   *          lokalnych danego wêz³a do wspó³rzêdnych jego rodzica.
   *          W ten sposób na ka¿dym poziomie funkcja \e Fun otrzymuje macierz
   *          przekszta³cenia wspó³rzêdnych danego elementu do wspó³rzêdnych
   *          wêz³a, dla którego metoda ta zosta³a wywo³ana.
   *          Trzecim parametrem jest warto¶æ okre¶laj±ca poziom zag³êbienia
   *          w strukturze drzewa. Pocz±tkowa warto¶æ tego parametru jest
   *          brana z warto¶ci parametru \e Level.
   *  \param  pMtx  - wska¼nik na macierz transformacji do zadanego uk³adu
   *                  wspó³rzêdnych.
   *  \param  Level - poziom zag³êbienia w strukturze drzewiastej. Warto¶æ
   *                 parametru pokazuje na jakiej g³êboko¶ci jest dany wêze³.
   *
   *  \pre
   *    Dla wêz³a, dla którego wywo³ana jest bezpo¶rednio ta metoda, warto¶æ 
   *    parametru \e Level musi byæ równa 0.
   *  \post
   *    Metoda przechodzi po wszystkich obiektach klasy 
   *    \link ViElemePolyh ViElemePolyh\endlink i wywo³uje dla nich funkcjê
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
   *  Metoda przechodzi po ca³ej strukturze drzewiastej poczynaj±c od wêz³a,
   *  dla którego zosta³a wywo³ana. Chodz±c po tej strukurze wywo³uje dla niej
   *  funkcjê, która przekazywana jest jako parametr wywo³ania tej metody.
   *  Przechodzenie nastêpuje w porz±dku preorder. Metoda ma mo¿liwo¶æ
   *  modyfikowania wierzcho³ków przez które przechodzi.
   *
   *  \param  Fun - funkcja, która jest wywo³ywana dla ka¿dego wêz³a.
   *          Parametrami tej funkcji jest wska¼nik na dany obiekt modeluj±cy
   *          bry³ê elementarn± (obiekt klasy 
   *          \link ViElemePolyh ViElemePolyh\endlink.
   *          Drugim parametrem jest jest macierz transformacji.
   *          Schodz±c coraz ni¿ej wzd³u¿ ga³êzi drzewa macierz ta jest 
   *          przemna¿ana przez kolejne macierze tranforamcji ze wsó³rzêdnych
   *          lokalnych danego wêz³a do wspó³rzêdnych jego rodzica.
   *          W ten sposób na ka¿dym poziomie funkcja \e Fun otrzymuje macierz
   *          przekszta³cenia wspó³rzêdnych danego elementu do wspó³rzêdnych
   *          wêz³a, dla którego metoda ta zosta³a wywo³ana.
   *          Trzecim parametrem jest warto¶æ okre¶laj±ca poziom zag³êbienia
   *          w strukturze drzewa. Pocz±tkowa warto¶æ tego parametru jest
   *          brana z warto¶ci parametru \e Level.
   *  \param  pMtx  - wska¼nik na macierz transformacji do zadanego uk³adu
   *                  wspó³rzêdnych.
   *  \param  Level - poziom zag³êbienia w strukturze drzewiastej. Warto¶æ
   *                 parametru pokazuje na jakiej g³êboko¶ci jest dany wêze³.
   *
   *  \pre
   *    Dla wêz³a, dla którego wywo³ana jest bezpo¶rednio ta metoda, warto¶æ 
   *    parametru \e Level musi byæ równa 0.
   *  \post
   *    Metoda przechodzi po wszystkich obiektach klasy 
   *    \link ViElemePolyh ViElemePolyh\endlink i wywo³uje dla nich funkcjê
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
    *  Udostêpnia adres danego wêz³a w strukturze drzewiastej bry³ z³o¿onych
    *  \param NodeAddr - obiekt ten po zakoñczeniu dzia³ania metody zawiera
    *             wyznaczony adres wêz³a.
    *  \return wska¼nik do ³añcucha znaków z obiektu \e NodeAddr.
    */
  char const *GetNodeAddress( ViNodeAddress &NodeAddr ) const;

   /*!
    *  Udostêpnia adres danego wêz³a w strukturze drzewiastej bry³ z³o¿onych
    *  \return obiekt zawieraj±cy adres wêz³a w drzewie.
    */
   ViNodeAddress GetNodeAddress() const;

   /*!
    *  Udostêpnia adres rodzica danego wêz³a w strukturze drzewiastej bry³ 
    *  z³o¿onych
    *  \param NodePath - obiekt ten po zakoñczeniu dzia³ania metody zawiera
    *             wyznaczony adres rodzica danego wêz³a.
    *  \return wska¼nik do ³añcucha znaków z obiektu \e NodePath.
    */
  char const *GetNodePath( ViNodeAddress &NodePath ) const;

  int MoveBranchTo(ViNTreeNode *pNode);
  int MoveBranchFromParentToRoot();
   /*!
    *  Usuwa wêze³ reprezentowany przez obiekt, dla którego wywo³ana
    *  zosta³a niniejsza metoda, z listy potomków swojego rodzica.
    */ 
  void DetachNode() { RemoveFromList(); }
   /*!
    *  Dodaje nowy element do swojej listy. Odpowiada to dodaniu nowego
    *  potomka do rodzica (rodzicem jest obiekt, dla którego wywo³ana
    *  zostaja metoda AddNode). Dodawany element mo¿e mieæ swoj± w³asn±
    *  kolejkê (zbiór potomków). W tym przypadku operacja ta mo¿e byæ
    *  interpretowana jako dodanie nowego podrzewa.
    *  \param pNode - wska¼nik na dodany nowy element (bêdzie on nowym
    *                 potomkiem dla wêz³a reprezentowanego przez obiekty
    *                 \b *this.
    *  \return wska¼nik na dodany element.
    *  \post  Obiekt wskazywany przez \e pNode zostaje umieszczony na
    *         koñcu kolejki potomków danego wêz³a.
    *         
    */
  ViNTreeNode *AddNode(ViNTreeNode *pNode);
   /*!
    * Metoda udostêpnia obiekt, który jest korzeniem dla ca³ej struktury.
    * Obiekt taki powinien byæ elementem listy wieloboków z³o¿onych
    * danej sceny.
    * Udostêpniony wska¼nik pozwala modyfikowaæ ten obiekt.
    */
  ViNTreeNode *GetTreeRoot();
   /*!
    * Metoda udostêpnia obiekt, który jest korzeniem dla ca³ej struktury.
    * Obiekt taki powinien byæ elementem listy wieloboków z³o¿onych
    * danej sceny.
    */
  ViNTreeNode const *GetTreeRoot() const;
   /*!
    * Metoda ta w klasie pochodnej musi byæ reimplementowana.
    * Zwracaæ ona musi warto¶æ pozwalaj±c± jednoznacznie zidentyfikowaæ
    * klasê pochodn±. 
    * \warning Metoda GetInheritorType  jest reimplementowana w kasach
    * pochodnych ViElemePolyh, ViMultiPolyh i ViScenePolyhList. 
    * Nie powinna ona byæ 
    * reimplementowana w ¿adnych innych klasach pochodnych.
    */
  virtual int GetInheritorType() const { return IT_MULTITREENODE; };

  /*!
   *  Metoda ta pozwala otrzymaæ identyfikator finalnej klasy pochodnej
   *  wzglêdem klasy ViNTreeNode. Udostêpniany identyfikator
   *  pozwala rozpoznaæ klasê pochod± w przypadku, gdy do dyspozycji jest
   *  tylko wska¼nik na obiekt klasy ViNTreeNode.
   *
   *  Metoda przeznaczona jest do reimplementacji we w³asnych klasach
   *  pochodnych, które definiuje programista. Zak³ada siê, ¿e 
   *  przedzia³ od -1000 do 1000 w³±cznie jest zarezerwowany dla
   *  biblioteki VIONA.
   *  Przy w³asnej reimplementacji tej metody jako zwracany identyfikator
   *  nale¿y wiêc u¿yæ warto¶ci spoza tego przedzia³u.
   */
  virtual int GetFinalClassID() const { return GetInheritorType(); }

   /*!
    *  Metoda ma charakter roboczy i wykorzystywana jest na potrzeby
    *  debugowania programu.
    */
  virtual void const *GetAddr() const  { return this; };

   //======================= Iteratory ===============================
   /*!
    *  Tworzy iterator do przegl±dania struktury drzewiastej, której
    *  wêz³em jest dany obiekt (dla którego zosta³a wywo³ana ta metoda).
    *  Przegl±d drzewa realizowany jest w porz±dku preorder.
    *
    * Przyk³ad u¿ycia iteratora:
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
    *  Tworzy iterator do przegl±dania struktury drzewiastej, której
    *  wêz³em jest dany obiekt (dla którego zosta³a wywo³ana ta metoda).
    *  Przegl±d drzewa realizowany jest w porz±dku preorder.
    *  Przegl±dane obiekty udostêpniane s± w trybie modyfikacji.
    *
    * Przyk³ad u¿ycia iteratora:
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
