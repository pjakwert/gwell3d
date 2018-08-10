#ifndef SYNTAXINTER_HH
#define SYNTAXINTER_HH

/*! \file sxinterp.hh
 *  Plik zawiera definicjê klasy SyntaxInter, która zawiera u³atwienia
 *  do odczytu i interpretacji sk³adni napisów znakowych.
 *
 *  \author  Bogdan Kreczmer
 *  \date    2004.08.16
 */


#ifdef __GNUG__
#pragma interface
#endif

#include <sstream>
#include "listque.hh"
#include "bexception.hh"

/*!
 * Identyfikator b³êdu dotycz±cego niemo¿no¶ci odczytu strumienia
 * w sytuacji, gdy oczekuje siê, ¿e jego odczyt musi byæ mo¿liwy.
 */
#define ERRNUM_SX__CANNOT_READ_STREAM   1000
/*!
 * Komunikat b³êdu dotycz±cego niemo¿no¶ci odczytu strumienia
 * w sytuacji, gdy oczekuje siê, ¿e jego odczyt musi byæ mo¿liwy.
 */
#define ERRMSG_SX__CANNOT_READ_STREAM  \
              "Brak mo¿liwo¶ci odczytu strumienia wej¶ciowego."


/*!
 * Identyfikator b³êdu wystêpuj±cego, gdy oczekiwane jest wyst±pienie
 * s³owa natomiast napotkany znak nie jest znakiem, który móg³by rozpoczynaæ
 * s³owo.
 */
#define ERRNUM_SX__START_NO_KEYWORD     1001
/*!
 * Komunikat b³êdu wystêpuj±cego, gdy oczekiwane jest wyst±pienie
 * s³owa natomiast napotkany znak nie jest znakiem, który móg³by rozpoczynaæ
 * s³owo.
 */
#define ERRMSG_SX__START_NO_KEYWORD  "Oczekiwane jest wyst±pienie jednego"\
                " ze s³ów kluczowych:\n"\
                "%s\n"\
                " podczas gdy napotkany zosta³ znak '%c', który nie mo¿e"\
                " byæ pocz±tkiem s³owa."
/*!
 * Indentyfikator b³êdu wystêpuj±cego, gdy nie znaleziono ¿adnego s³owa
 * podczas gdy oczekiwane jest jego wyst±pienie.
 */
#define ERRNUM_SX__EMPTY_WORD          1002
/*!
 * Komunikat b³êdu wystêpuj±cego, gdy nie znaleziono ¿adnego s³owa
 * podczas gdy oczekiwane jest jego wyst±pienie.
 */
#define ERRMSG_SX__EMPTY_WORD  "Nie znaleziono ¿adnego s³owa pomimo,"\
                               " ¿e jest oczekiwane."

/*!
 * Indentyfikator b³êdu wystêpuj±cego, gdy znalezione s³owo nie jest
 * ¿adnym z oczekiwanych s³ów kluczowych.
 */
#define ERRNUM_SX__NO_KEYWORD          1002
/*!
 * Komunikat b³êdu wystêpuj±cego, gdy znalezione s³owo nie jest
 * ¿adnym z oczekiwanych s³ów kluczowych.
 */
#define ERRMSG_SX__NO_KEYWORD "Znalezione s³owo '%s' nie jest ¿adnym "\
                   "z oczekiwanych s³ów kluczowych.\n"\
                   "Oczekiwanie s³owa kluczowe to: %s"

/*!
 * Indentyfikator b³êdu wystêpuj±cego, gdy napotkano inny znak ni¿
 * oczekiwany.
 */
#define ERRNUM_SX__UNEXP_CHAR          1003
/*!
 * Komunikat b³êdu wystêpuj±cego, gdy napotkano inny znak ni¿
 * oczekiwany.
 */
#define ERRMSG_SX__UNEXP_CHAR  "Napotkany zosta³ znak '%c' podczas gdy "\
                  "oczekiwanym znakiem jest '%c'"


/*!
 * Indentyfikator b³êdu wystêpuj±cego, gdy strumien zosta³ wyczerpany i
 * nie napotkano oczekiwanego znaku.
 */
#define ERRNUM_SX__UNEXP_END            1004
/*!
 * Komunikat b³êdu wystêpuj±cego, gdy strumien zosta³ wyczerpany i
 * nie napotkano oczekiwanego znaku.
 */
#define ERRMSG_SX__UNEXP_END  "Napotkano koniec strumienia, gdy"\
                              " oczekiwano znaku '%c'"

/*!
 *  Indentyfikator b³êdu wystêpuj±cego, gdy wystêpuje b³±d wczytania liczby
 *  typu integer.
 */
#define ERRNUM_SX__FAIL_INT             1005
/*!
 *  Komunikat b³êdu wystêpuj±cego, gdy wystêpuje b³±d wczytania liczby
 *  typu integer.
 */
#define ERRMSG_SX__FAIL_INT   "Wyst±pi³ b³±d przy próbie wczytania liczby "\
                              " typu ca³kowitoliczbowego."

/*!
 *  Indentyfikator b³êdu wystêpuj±cego, gdy wystêpuje b³±d wczytania liczby
 *  typu float.
 */
#define ERRNUM_SX__FAIL_FLOAT           1006
/*!
 *  Komunikat b³êdu wystêpuj±cego, gdy wystêpuje b³±d wczytania liczby
 *  typu float.
 */
#define ERRMSG_SX__FAIL_FLOAT  "Wyst±pi³ b³±d przy próbie wczytania "\
                               " liczby typu float."

/*!
 *  Indentyfikator b³êdu wystêpuj±cego, gdy zbiór oczekiwanych s³ów 
 *  kluczowych jest pusty.
 */
#define ERRNUM_SX__NO_KEYWORDS          1007
/*!
 *  Komunikat b³êdu wystêpuj±cego, gdy zbiór oczekiwanych s³ów kluczowych
 *  jest pusty.
 */
#define ERRMSG_SX__NO_KEYWORDS  "W strumieniu wej¶ciowym szukane jest "\
                      "s³owo kluczow podczas gdy ich zbiór jest pusty."

/*!
 * Numer b³êdu zg³szanego w przypadku gdy nie zosta³o odczytane ¿adne s³owo
 * pomimo tego, ¿e powinno zostaæ znalezione w strumieniu wej¶ciowym.
 * Odpowiada mu komunikat zdefiniowany przez sta³±
 * \link sxinterp.hh::ERRMSG_SX__NO_WORD ERRMSG_SX__NO_WORD\endlink.
 */
#define ERRNUM_SX__NO_WORD              1008
/*!
 * Komunikat b³êdu zg³szanego w przypadku gdy nie zosta³o odczytane ¿adne
 * s³owo
 * pomimo tego, ¿e powinno zostaæ znalezione w strumieniu wej¶ciowym.
 */
#define ERRMSG_SX__NO_WORD "Nie zosta³o odczytane ¿adne s³owo pomimo "\
                           "tego, ¿e oczekiwano jego odczytu. %s"



/*! 
 *  W przestrzeni nazw Sx znajduj± siê dodatkow struktury
 *  wykorzystywane przy analizie syntaktycznej tekstu.
 */
namespace Sx {
  /*!
   *  Klasa definiuje wyj±tki zg³aszane przez metody klas z przestrzeni
   *  nazw \link Sx Sx\endlink wykorzystywanych przez klasê 
   *  SxException. S± one u¿ywane do analizy syntaktycznej 
   *  zapisów w postaci ³añcuchów znakowych.
   */
  class Exception: public Ba::Exception {
   public:
   /*!
    *  Inicjalizuje informacje o b³êdzie.
    *  \param Err - numer b³êdu,
    *  \param Msg - komunikat b³êdu,
    *  \param AuxID - pomocniczy identyfikator dla okre¶lenia miejsca
    *                 wyst±pienia b³êdu (inicjalizuje pole
    *                 \link ViException::_ErrAuxID _ErrAuxID\endlink).
    */
    Exception(int Err = -1, const char *Msg = 0L, int AuxID = 0): 
        Ba::Exception(Err,Msg,AuxID) {}
  };


  /*!
   *  Klasa wi±¿e ze sob± s³owo kluczowe oraz jego identyfikator.
   */
  class KeyPair: public ListItem<KeyPair> {
      /*!
       *  Pole zawiera informacjê o tym ile razy zosta³o napotkane
       *  dane s³owo.
       */
      int          _No;
      /*!
       *  Pole zawiera tre¶æ s³owa kluczowego.
       */
      std::string  _Keyword;
      /*!
       *  Pole zawiera identyfikator skojarzony z danym s³owem.
       */
      int          _ID;

     public:
      /*!
       * Inicjalizuje obiekt wstawiaj±c dane s³owo kluczowe oraz skojarzony
       * z nim identyfikator. Ilo¶æ odczytu s³ow ze strumienia zostaje
       * zanicjalizowana na warto¶æ 0.
       * \param Str - zawiera s³owo kluczowe.
       * \param ID  - zawiera identyfikator skojarzony z danym s³owem
       *              kluczowym.
       */
      KeyPair(const char *Str, int ID) {_Keyword = Str;  _ID = ID; _No = 0;}

      /*!
       *  Udostêpnia tre¶æ s³owa kluczowego.
       */
      const std::string &Keyword() const { return _Keyword; }
      /*!
       * Udostêpnia identyfikator skojrzaony z danym s³owem kluczowym.
       */
      int          ID() const { return _ID; }
      /*!
       *  Powoduje inkrementacjê licznika napotkañ danego s³owa kluczowego,
       *  które nast±pi³o w trakcie odczytu strumienia wej¶ciowego.
       */
      void IncEncounterNo() { ++_No; }
      /*!
       *  Udostêpnia warto¶æ licznika napotkañ danego s³owa kluczowego,
       *  które nast±pi³o w trakcie odczytu strumienia wej¶ciowego.
       */
      int GetEncounterNo() const { return _No; }
  };

  /*!
   * Klasa reprezentuje listê s³ów kluczowych. Obiektami tej klasy
   * s± jednocze¶nie elementami stosu list s³ów kluczowych
   */
  class KeywordList: public ListItem<KeywordList>, 
                     public List<KeyPair> {
     /*!
      * Pole to zawiera informacjê, czy pêtla przegl±dania s³ów kluczowych
      * mo¿e automatycznie zakoñczyæ siê po napotkaniu wszystkich
      * s³ów kluczowych.
      */
      bool _CanEndAfterMeetingAll;
     public:
    /*!
     *  Inicjalizuje obiekt.
     *  \param CanEndAfterMeetingAll - warto¶æ \p true tego parametru
     *          zezwoli na automatyczne przerwanie pêtli szukania 
     *          w strumieniu wej¶ciowym kolejnych s³ów kluczowych.
     */
     KeywordList( bool CanEndAfterMeetingAll = false ) 
                     {  _CanEndAfterMeetingAll = CanEndAfterMeetingAll; }
      ~KeywordList() {}
     /*!
      * Udostêpnia wszystkie s³owa kluczowe. Ka¿de z nich odzielone
      * jest od pozosta³ych przecinkiem.
      * \param Keywords - (\b out) po zakonczeniu dzia³ania metody
      *                zawiera zbiór s³ów kluczowych znajduj±cych
      *                siê w danej li¶cie.
      */
     void GetAllKeywords(std::string  &Keywords);
     /*!
      * Udostêpnia informacjê, czy wszystkie s³owa kluczowe znajduj±ce siê
      * na li¶cie zosta³y ju¿ napotkane w trakcie odczytu.
      * \retval true - je¶li wszystkie s³owa kluczowe znajduj±ce siê na
      *                li¶cie zosta³y ju¿ napotkane. Warto¶æ ta jest 
      *           zwracana równie¿ w przypadku, gdy lista jest pusta.
      * \retval false - w przypadku przeciwnym.
      */
     bool AllKeywordsWereVisited() const;
     /*!
      * Zwraca informacjê, czy pêtla szukania kolejnych s³ów kluczowych
      * w strumieniu wej¶ciowym musi byæ kontynuowana, czy te¿ mo¿e zostaæ
      * ju¿ przerwana.
      * \retval true - je¶li pêtla szukania s³ów kluczowych mo¿e zostaæ
      *                przerwana.
      * \retval false - w przypadku przeciwnym.
      */
     bool ShouldLoopBeContinued() const;
    /*!
     * Metoda zezwala na samoczynne zakoñczenie pêtli szukania s³ów
     * kluczowych
     * w przypadku, gdy ka¿de s³owo z tego zbioru ju¿ wyst±pi³o.
     */
     void AllowEndAfterMeetingAll() { _CanEndAfterMeetingAll = true; }
    /*!
     * Metoda zabrania na samoczynne zakoñczenie pêtli szukania s³ów 
     * kluczowych
     * w przypadku, gdy ka¿de s³owo z tego zbioru ju¿ wyst±pi³o.
     */
     void ForbidEndAfterMeetingAll() { _CanEndAfterMeetingAll = false; }
  };

  
  class MultiStack: protected List<KeywordList> {
    /*!
     *  Pole to sygnalizuje inicjalizacje nowej kolejki
     *  s³ów kluczowych. Je¿eli pole to zwiera warto¶æ
     *  \p true, to ka¿da operacja dodania nowej pary
     *  s³owa kluczowego i indeksu bêdzie tworzy³a nowy 
     *  element kolejki.
     */
     bool _InitNewQueue;

    protected:
      void CreateNewKeySet(bool CanEndAfterMeetingAll = false);
      void DeleteFirst() { if (First()) delete First(); }
    public:
      MultiStack() { _InitNewQueue = false; }

      MultiStack & operator ()(const char *Str, int ID);
     /*!
      * Zwraca informacjê, czy pêtla szukania kolejnych s³ów kluczowych
      * w strumieniu wej¶ciowym musi byæ kontynuowana, czy te¿ mo¿e zostaæ
      * ju¿ przerwana.
      * \retval true - je¶li pêtla szukania s³ów kluczowych mo¿e zostaæ
      *                przerwana. 
      * \retval false - w przypadku przeciwnym. Mo¿e to nast±piæ, gdy
      *                bie¿±cy zbiór s³ów kluczowych jest pusty lub
      *                gdy wszystkie s³owa z danego zbioru zosta³y ju¿
      *                napotkane w strumieniu wej¶ciowym.
      */

      bool ShouldLoopBeContinued() const
        {  return First() ? First()->ShouldLoopBeContinued() : false; }
  };
};

/*!
 *  Klasa SxInterp (Syntax Interpreter) zawiera u³atwienia dla odczytu 
 *  i interpretacji sk³adni napisów znakowych.
 */
class SxInterp: public std::istringstream, public Sx::MultiStack {
  /*!
   * Pole zawiera numer linii, w ktorej realizowany jest odczyt.
   */
   int  _LineNo;
  /*!
   * Pole przechowuje znak, który pe³ni rolê lewego nawiasu.
   * Nawiasy wykorzystywane s± przy zbiorczym podawaniu warto¶ci,
   * np. wektora.\n
   * Warto¶æ -1 w tym polu oznacza brak znaku.
   */
   char _Parenthesis_Left;
  /*!
   * Pole przechowuje znak, który pe³ni rolê prawego nawiasu.
   * Nawiasy wykorzystywane s± przy zbiorczym podawaniu warto¶ci,
   * np. wektora.\n
   * Warto¶æ -1 w tym polu oznacza brak znaku.
   */
   char _Parenthesis_Right;
  /*!
   * Pole przechowuje znak, który pe³ni rolê separatora przy podawaniu
   * zbiorczym warto¶ci, np. warto¶ci dla wektora.\n
   * Warto¶æ -1 w tym polu oznacza brak znaku.
   */
   char _Numbers_Separator;

  /*!
   *  Odczytuje ze strumienia bia³e znaki. Rozpoznaje koñce linii
   *  i aktualizuje numer czytanej linii.
   */
   void EatWhite();

  public:  
   /*!
    *  Inicjalizuje strumieñ wyj¶ciowy przekazanym przez parametr napisem.
    *  \param Str - zawiera napis, który ma byæ doczytany i interpretowany.
    */
    SxInterp(const std::string &Str);
   /*!
    * Udostêpnia stos list s³ów kluczowych i skojarzonych z nimi
    * indeksów. Implementacja stosu realizowana jest poprzez 
    * dziedziczony klasê
    * \link Sx::MultiStack  Sx::MultiStack\endlink.
    *
    * Metoda udostêpnia wspomniany stos w trybie modyfikacji.
    */
    Sx::MultiStack &Stack() { return (*(MultiStack*)this); }
   /*!
    * Udostêpnia stos list s³ów kluczowych i skojarzonych z nimi
    * indeksów. Implementacja stosu realizowana jest poprzez 
    * dziedziczony klasê
    * \link Sx::MultiStack  Sx::MultiStack\endlink.
    *
    * Metoda udostêpnia wspomniany stos w trybie sta³ym.
    */
    const Sx::MultiStack &Stack() const { return (*(MultiStack*)this); }
   /*!
    *  Tworzy nowy element kolejki dla kolejnego zbioru s³ów kluczowych
    *  i inicjalizuje sposób zakoñczenia przegl±dania tej kolejki.
    *  \param CanEndAfterMeetingAll - warto¶æ \p true tego parametru
    *          zezwoli na automatyczne przerwanie pêtli szukania 
    *          w strumieniu wej¶ciowym kolejnych s³ów kluczowych.
    */
    Sx::MultiStack &Push(bool CanEndAfterMeetingAll = false)  
             { CreateNewKeySet(CanEndAfterMeetingAll); return Stack(); }
   /*!
    *  Ustawia znaki separatorów dla operacji wczytywania warto¶ci typu
    *  wektor.
    *  \param ParL - (\b in) znak lewego nawiasu.
    *  \param Sep  - (\b in) znak separatora.
    *  \param ParR - (\b in) znak prawego nawiasu.
    */
    void SetVectorSep(char ParL, char Sep, char ParR )
     {
       _Parenthesis_Left = ParL;
       _Numbers_Separator = Sep;
       _Parenthesis_Right = ParR; 
     }
   /*!
    *  Usuwa ze stosu pierwsz± listê s³ów kluczowych i skojrzonych z nimi 
    *  indeksami. W przypadku gdy stos jest pusty, realizacja operacji
    *  nie dokonuje ¿adnych zmian.
    */
    void Pop() { DeleteFirst(); }
   /*!
    *  Pobiera nastêpne s³owo ze strumienia i sprawdza czy jest ono 
    *  identyczne z jakim¶ ze s³ów znajduj±cych siê w bie¿±cej kolejce
    *  s³ów, które s± oczekiwane.
    *  Je¿eli tak, to zwraca jego indeks. W przypadku przeciwnym zg³asza
    *  wyj±tek.
    *  \exception Sx::Exception - mo¿e byæ zg³aszany jest z kodami b³êdu:
    *   \li \link sxinterp.hh::ERRNUM_SX__NO_KEYWORDS 
    *             ERRNUM_SX__NO_KEYWORDS\endlink - gdy brak listy ze s³owami
    *             kluczowymi.
    *   \li \link sxinterp.hh::ERRNUM_SX__START_NO_KEYWORD
    *             ERRNUM_SX__START_NO_KEYWORD\endlink - gdy napotkany znak
    *             nie mo¿e byæ pocz±tkiem ¿adnego s³owa kluczowego.
    *   \li \link sxinterp.hh::ERRNUM_SX__NO_KEYWORD
    *                              ERRNUM_SX__NO_KEYWORD\endlink
    *             - gdy znalezione s³owo nie jest ¿adnym z oczekiwanych
    *               s³ów kluczowych.
    *   \li \link sxinterp.hh::ERRNUM_SX__NO_WORD
    *                              ERRNUM_SX__NO_WORD\endlink -
    *             gdy nie znaleziono ¿adnego s³owa.
    */
   int GetNextKeyword(); // throw (Sx::Exception);

   /*!
    *  Pomija znaki bia³e i pobiera ze strumienia znakowego nastêpne 
    *  s³owo.
    *  \param  Word - (\b out) po zakoñczeniu dzia³ania zawiera pobrane
    *                 s³owo.
    *  \param  WordAddChars - (\b in) zawiera zbiór dodatkowych znaków, 
    *             które mog± wchodziæ w sk³ad s³owa i jednocze¶nie je
    *             rozpoczynaæ. W sk³ad tego zbioru znaków nie mog± 
    *             wchodziæ znaki bia³e.\n
    *             Domy¶lnie s³owo rozpoczyna siê liter± lub znakiem '_' i
    *             mo¿e zawieraæ cyfry. Ka¿dy inny znak traktowany jest 
    *             jako znak koñca s³owa.
    */
    void GetWord(std::string &Word, const char *WordAddChars = 0L);

   /*!
    *  Wczytuje ze strumienia wej¶ciowego liczbê typu \e int.
    *  \param Val - (\b out) po wykonanej operacji zawiera
    *               wczytan± liczbê.
    *  \exception Sx::Exception jest zg³aszany w przypadku niemo¿no¶ci
    *             wczytania liczby.
    *             Obiekt klasy Sx::Exception zglaszany jest
    *                z kodem 
    * \link sxinterp.hh::ERRNUM_SX__FAIL_INT ERRNUM_SX__FAIL_INT\endlink
    */
   void GetNum( int &Val ); // throw (Sx::Exception);

   /*!
    *  Wczytuje ze strumienia wej¶ciowego liczbê typu \b float.
    *  \param Val - (\b out) po wykonanej operacji zawiera
    *               wczytan± liczbê.
    *  \exception Sx::Exception jest zg³aszany w przypadku niemo¿no¶ci
    *             wczytania liczby.
    *             Obiekt klasy Sx::Exception zglaszany jest
    *                z kodem 
    * \link sxinterp.hh::ERRNUM_SX__FAIL_FLOAT
    *                       ERRNUM_SX__FAIL_FLOAT\endlink
    */
   void GetNum( float &Val ); // throw (Sx::Exception);
   /*!
    * Metoda umo¿liwia wczytanie warto¶ci typu \b float wektora 3D.
    * \param Val1 - (\b out) pierwsza sk³adowa.
    * \param Val2 - (\b out) druga sk³adowa.
    * \param Val3 - (\b out) trzecia sk³adowa.
    *  \exception Sx::Exception jest zg³aszany w przypadku niemo¿no¶ci
    *             wczytania liczby typu \e float.
    *             Obiekt klasy Sx::Exception zglaszany jest
    *                z kodem 
    * \link sxinterp.hh::ERRNUM_SX__FAIL_FLOAT
    *                       ERRNUM_SX__FAIL_FLOAT\endlink
    */
   void GetVector( float &Val1, float &Val2, float &Val3 );
      //  throw (Sx::Exception);

   void GetLine( std::string &Line );


  /*!
   *  Odczytuje znaki bia³e ze strumienia, a¿ do momentu napotkania 
   *  oczekiwanego znaku. Napotkanie innego niebia³ego znaku powoduje
   *  zg³oszenie wyj±tku.
   *  \param  Ch - oczekiwany znak, mo¿e byæ nim równie¿ znak bia³y.
   *  \exception Sx::Exception jest zg³aszany w przypadku napotkania innego
   *                znaku ni¿ oczekiwany znak \e Ch.
   *                Obiekt klasy Sx::Exception zglaszany jest
   *                z kodem 
   * \link sxinterp.hh::ERRNUM_SX__UNEXP_CHAR 
   *                       ERRNUM_SX__UNEXP_CHAR\endlink
   */
   void LookForChar(char Ch); // throw (Sx::Exception);

   /*!
    * Zwraca informacjê, czy pêtla szukania kolejnych s³ów kluczowych
    * w strumieniu wej¶ciowym musi byæ kontynuowana, czy te¿ mo¿e zostaæ
    * ju¿ przerwana.
    * \retval true - je¶li pêtla szukania s³ów kluczowych mo¿e zostaæ
    *                przerwana. 
    * \retval false - w przypadku przeciwnym. Mo¿e to nast±piæ, gdy
    *                bie¿±cy zbiór s³ów kluczowych jest pusty lub
    *                gdy wszystkie s³owa z danego zbioru zosta³y ju¿
    *                napotkane w strumieniu wej¶ciowym.
    */
  bool ShouldLoopBeContinued() const 
                         {return Stack().ShouldLoopBeContinued();}
};


/*!
 *  Makro definiuje zmienne, które wykorzystywane s± do realizacji
 *  pêtli analizy syntaktycznej i indeksowania znalezionych s³ów.
 *  Indeks s³owa jest podstaw± wyboru odpowiedniej sekcji 
 *  \e case. 
 *
 *  Makro \b SXCMD_DEFINE_VAR zawiera definicjê zmiennych:
 *  \li \b bool \e SxContinueThisLoop - poprzez ni± realizowane jest
 *          sterowanie momentem zakoñczenia danej pêtli.
 *  \li \b bool \e SxContinueAllLoops - w przypadku, gdy w danej metodzie
 *          jest kilka zagnie¿d¿onych pêtli, zmienna ta umo¿liwia 
 *          przerwanie wykonywania wszystkich pêtli.
 *  \li \b char \e Key - wykorzystywana jest do przypisywania warto¶ci
 *          indeksu odpowiadaj±cego danemu s³owu. Wykorzystywana ona
 *          jest nastêpnie w instrukcji \b switch do selekcji w³a¶ciwej
 *          akcji zwi±zanej z danym s³owem.
 */
#define SXCMD_DEFINE_VAR     bool SxContinueThisLoop = true;\
                             bool SxContinueAllLoops = true;\
                             char Key;


/*!
 *  Powoduje zakoñczenie wykonywania danej pêtli.
 */
#define SXCMD_BREAK_THIS_LOOP  SxContinueThisLoop = false;  break;
/*!
 *  Powoduje zakoñczenie wykonywania wszystkich zagnie¿d¿onych pêtli
 *  w danej funkcji lub metodzie.
 */
#define SXCMD_BREAK_ALL_LOOPS  SxContinueAllLoops = false;  break;

/*!
 * Makro wykorzystywane jest do zainicjalizowania pêtli analizy
 * syntakycznej. W pêtli tej sprawdzane jest wyst±pienie jednego z zadanych
 * s³ów kluczowych.
 * \param Interp - zmienna klasy \b SyntaxInterp lub klasy pochodnej.
 * \param MacroKeywordList  - lista kluczy z indetyfikatorami.
 *                             Lista musi mieæ postaæ\n
 * \verbatim
    (SlowoKluczowe1,Indeks1)(SlowoKluczowe2,Indeks2)...(SlowoKluczoweN,IndeksN)
   \endverbatim
 * gdzie \e SlowoKluczoweK to ³añcuch znaków w sensie jêzyka \b C, za¶
 *        \e IndeksK to znak lub liczba typu \e integer.
 *
 * Przyk³ad wykorzystania makra:
 *\code
  void  MojaBryla::InitWithDescr(const ExtString &Descr)
  {
    ViSynxInterp   Interp(Descr);
    SXCMD_DEFINE_VAR;

    SXCMD_START_LOOP2END(Interp,("Color",'C')("AuxiliaryMtx"));
     case 'C':
      Interp.LookForChar(':');
      Interp.GetNum(_Color);
      continue;
     case 'M':
      InitMtxFrom(Interp,_AuxMtx);
      continue;
    SXCMD_END_LOOP(Interp);
  }
  \endcode
 *
 * \pre Makro wymaga zdefiniowania zmiennych pomocniczych. W tym celu
 *      nale¿y wcze¶nij u¿yæ makra 
 *   \link sxinterp.hh::SXCMD_DEFINE_VAR 
 *         sxinterp.hh::SXCMD_DEFINE_VAR\endlink.
 */
#define SXCMD_START_LOOP(Interp, MacroKeywordList)                 \
    Interp.Push()MacroKeywordList;                                 \
    SxContinueThisLoop = true;                                     \
    while (Interp && SxContinueThisLoop && SxContinueAllLoops) {   \
      switch (Key=Interp.GetNextKeyword()) {

/*!
 * Makro inicjalizuje i organizuje pêtlê przeg³adani s³ów kluczowych.
 * Pozwala na automatyczne zakoñczenie pêtli w przypadku napotkania
 * wszystkich s³ów kluczowych z danego zbioru.
 * \param Interp - musi to byæ obiekt klasy SxInterp lub klasy pochodnej
 *            (np ViSynxInterp). Obiekt ten wstêpnie musi byæ skojarzony
 *            z jakimi¶ opisem.
 * \param MacroKeywordList - zaiwiera listê s³ów kluczowych i skojarzonych
 *            z nimi indeksami. Lista musi mieæ postaæ:
 * \verbatim
    (SlowoKluczowe1,Indeks1)(SlowoKluczowe2,Indeks2)...(SlowoKluczoweN,IndeksN)
   \endverbatim
 * gdzie \e SlowoKluczoweK to ³añcuch znaków w sensie jêzyka \b C, za¶
 *        \e IndeksK to znak lub liczba typu \e integer.
 *
 * Przyk³ad wykorzystania makra:
 *\code
  void  MojaBryla::InitWithDescr(const ExtString &Descr)
  {
    ViSynxInterp   Interp(Descr);
    SXCMD_DEFINE_VAR;

    SXCMD_START_LOOP2END(Interp,("Color",'C')("AuxiliaryMtx"));
     case 'C':
      Interp.LookForChar(':');
      Interp.GetNum(_Color);
      continue;
     case 'M':
      InitMtxFrom(Interp,_AuxMtx);
      continue;
    SXCMD_END_LOOP(Interp);
  }
  \endcode
 *
 * \pre Makro wymaga zdefiniowania zmiennych pomocniczych. W tym celu
 *      nale¿y wcze¶nij u¿yæ makra 
 *   \link sxinterp.hh::SXCMD_DEFINE_VAR SXCMD_DEFINE_VAR\endlink.
 */
#define SXCMD_START_LOOP2END(Interp,MacroKeywordList)                    \
    Interp.Push(true)MacroKeywordList;                                   \
    SxContinueThisLoop = true;                                           \
    while (Interp.ShouldLoopBeContinued() && Interp && SxContinueThisLoop\
                                          && SxContinueAllLoops) {       \
      switch (Key=Interp.GetNextKeyword()) {


/*!
 * Makro to koñczy pêtlê analizy syntaktcznej danego strumienia.
 * Powoduje równie¿ usuniêcie ze stosu listê s³ów kluczowych i skojarzonych
 * z ni± indeksów, która to lista podana zosta³a w przy rozpoczêciu 
 * pêtli (patrz opis makra 
 *  \link sxinterp.hh::SXCMD_START_LOOP2END 
 *        sxinterp.hh::SXCMD_START_LOOP2END\endlink).
 * \param Interp - musi to byæ obiekt klasy SxInterp lub klasy pochodnej
 *            (np ViSynxInterp). Musi to byæ ten sam obiek, który 
 *            wyst±pi³ wcze¶niej w makrze 
 *  \link sxinterp.hh::SXCMD_START_LOOP2END 
 *        sxinterp.hh::SXCMD_START_LOOP2END\endlink lub
 *  \link sxinterp.hh::SXCMD_START_LOOP SXCMD_START_LOOP\endlink.
 */
#define SXCMD_END_LOOP(Interp) }} Interp.Pop();  SxContinueThisLoop = true;




#endif
