#ifndef SYNTAXINTER_HH
#define SYNTAXINTER_HH

/*! \file sxinterp.hh
 *  Plik zawiera definicj� klasy SyntaxInter, kt�ra zawiera u�atwienia
 *  do odczytu i interpretacji sk�adni napis�w znakowych.
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
 * Identyfikator b��du dotycz�cego niemo�no�ci odczytu strumienia
 * w sytuacji, gdy oczekuje si�, �e jego odczyt musi by� mo�liwy.
 */
#define ERRNUM_SX__CANNOT_READ_STREAM   1000
/*!
 * Komunikat b��du dotycz�cego niemo�no�ci odczytu strumienia
 * w sytuacji, gdy oczekuje si�, �e jego odczyt musi by� mo�liwy.
 */
#define ERRMSG_SX__CANNOT_READ_STREAM  \
              "Brak mo�liwo�ci odczytu strumienia wej�ciowego."


/*!
 * Identyfikator b��du wyst�puj�cego, gdy oczekiwane jest wyst�pienie
 * s�owa natomiast napotkany znak nie jest znakiem, kt�ry m�g�by rozpoczyna�
 * s�owo.
 */
#define ERRNUM_SX__START_NO_KEYWORD     1001
/*!
 * Komunikat b��du wyst�puj�cego, gdy oczekiwane jest wyst�pienie
 * s�owa natomiast napotkany znak nie jest znakiem, kt�ry m�g�by rozpoczyna�
 * s�owo.
 */
#define ERRMSG_SX__START_NO_KEYWORD  "Oczekiwane jest wyst�pienie jednego"\
                " ze s��w kluczowych:\n"\
                "%s\n"\
                " podczas gdy napotkany zosta� znak '%c', kt�ry nie mo�e"\
                " by� pocz�tkiem s�owa."
/*!
 * Indentyfikator b��du wyst�puj�cego, gdy nie znaleziono �adnego s�owa
 * podczas gdy oczekiwane jest jego wyst�pienie.
 */
#define ERRNUM_SX__EMPTY_WORD          1002
/*!
 * Komunikat b��du wyst�puj�cego, gdy nie znaleziono �adnego s�owa
 * podczas gdy oczekiwane jest jego wyst�pienie.
 */
#define ERRMSG_SX__EMPTY_WORD  "Nie znaleziono �adnego s�owa pomimo,"\
                               " �e jest oczekiwane."

/*!
 * Indentyfikator b��du wyst�puj�cego, gdy znalezione s�owo nie jest
 * �adnym z oczekiwanych s��w kluczowych.
 */
#define ERRNUM_SX__NO_KEYWORD          1002
/*!
 * Komunikat b��du wyst�puj�cego, gdy znalezione s�owo nie jest
 * �adnym z oczekiwanych s��w kluczowych.
 */
#define ERRMSG_SX__NO_KEYWORD "Znalezione s�owo '%s' nie jest �adnym "\
                   "z oczekiwanych s��w kluczowych.\n"\
                   "Oczekiwanie s�owa kluczowe to: %s"

/*!
 * Indentyfikator b��du wyst�puj�cego, gdy napotkano inny znak ni�
 * oczekiwany.
 */
#define ERRNUM_SX__UNEXP_CHAR          1003
/*!
 * Komunikat b��du wyst�puj�cego, gdy napotkano inny znak ni�
 * oczekiwany.
 */
#define ERRMSG_SX__UNEXP_CHAR  "Napotkany zosta� znak '%c' podczas gdy "\
                  "oczekiwanym znakiem jest '%c'"


/*!
 * Indentyfikator b��du wyst�puj�cego, gdy strumien zosta� wyczerpany i
 * nie napotkano oczekiwanego znaku.
 */
#define ERRNUM_SX__UNEXP_END            1004
/*!
 * Komunikat b��du wyst�puj�cego, gdy strumien zosta� wyczerpany i
 * nie napotkano oczekiwanego znaku.
 */
#define ERRMSG_SX__UNEXP_END  "Napotkano koniec strumienia, gdy"\
                              " oczekiwano znaku '%c'"

/*!
 *  Indentyfikator b��du wyst�puj�cego, gdy wyst�puje b��d wczytania liczby
 *  typu integer.
 */
#define ERRNUM_SX__FAIL_INT             1005
/*!
 *  Komunikat b��du wyst�puj�cego, gdy wyst�puje b��d wczytania liczby
 *  typu integer.
 */
#define ERRMSG_SX__FAIL_INT   "Wyst�pi� b��d przy pr�bie wczytania liczby "\
                              " typu ca�kowitoliczbowego."

/*!
 *  Indentyfikator b��du wyst�puj�cego, gdy wyst�puje b��d wczytania liczby
 *  typu float.
 */
#define ERRNUM_SX__FAIL_FLOAT           1006
/*!
 *  Komunikat b��du wyst�puj�cego, gdy wyst�puje b��d wczytania liczby
 *  typu float.
 */
#define ERRMSG_SX__FAIL_FLOAT  "Wyst�pi� b��d przy pr�bie wczytania "\
                               " liczby typu float."

/*!
 *  Indentyfikator b��du wyst�puj�cego, gdy zbi�r oczekiwanych s��w 
 *  kluczowych jest pusty.
 */
#define ERRNUM_SX__NO_KEYWORDS          1007
/*!
 *  Komunikat b��du wyst�puj�cego, gdy zbi�r oczekiwanych s��w kluczowych
 *  jest pusty.
 */
#define ERRMSG_SX__NO_KEYWORDS  "W strumieniu wej�ciowym szukane jest "\
                      "s�owo kluczow podczas gdy ich zbi�r jest pusty."

/*!
 * Numer b��du zg�szanego w przypadku gdy nie zosta�o odczytane �adne s�owo
 * pomimo tego, �e powinno zosta� znalezione w strumieniu wej�ciowym.
 * Odpowiada mu komunikat zdefiniowany przez sta��
 * \link sxinterp.hh::ERRMSG_SX__NO_WORD ERRMSG_SX__NO_WORD\endlink.
 */
#define ERRNUM_SX__NO_WORD              1008
/*!
 * Komunikat b��du zg�szanego w przypadku gdy nie zosta�o odczytane �adne
 * s�owo
 * pomimo tego, �e powinno zosta� znalezione w strumieniu wej�ciowym.
 */
#define ERRMSG_SX__NO_WORD "Nie zosta�o odczytane �adne s�owo pomimo "\
                           "tego, �e oczekiwano jego odczytu. %s"



/*! 
 *  W przestrzeni nazw Sx znajduj� si� dodatkow struktury
 *  wykorzystywane przy analizie syntaktycznej tekstu.
 */
namespace Sx {
  /*!
   *  Klasa definiuje wyj�tki zg�aszane przez metody klas z przestrzeni
   *  nazw \link Sx Sx\endlink wykorzystywanych przez klas� 
   *  SxException. S� one u�ywane do analizy syntaktycznej 
   *  zapis�w w postaci �a�cuch�w znakowych.
   */
  class Exception: public Ba::Exception {
   public:
   /*!
    *  Inicjalizuje informacje o b��dzie.
    *  \param Err - numer b��du,
    *  \param Msg - komunikat b��du,
    *  \param AuxID - pomocniczy identyfikator dla okre�lenia miejsca
    *                 wyst�pienia b��du (inicjalizuje pole
    *                 \link ViException::_ErrAuxID _ErrAuxID\endlink).
    */
    Exception(int Err = -1, const char *Msg = 0L, int AuxID = 0): 
        Ba::Exception(Err,Msg,AuxID) {}
  };


  /*!
   *  Klasa wi��e ze sob� s�owo kluczowe oraz jego identyfikator.
   */
  class KeyPair: public ListItem<KeyPair> {
      /*!
       *  Pole zawiera informacj� o tym ile razy zosta�o napotkane
       *  dane s�owo.
       */
      int          _No;
      /*!
       *  Pole zawiera tre�� s�owa kluczowego.
       */
      std::string  _Keyword;
      /*!
       *  Pole zawiera identyfikator skojarzony z danym s�owem.
       */
      int          _ID;

     public:
      /*!
       * Inicjalizuje obiekt wstawiaj�c dane s�owo kluczowe oraz skojarzony
       * z nim identyfikator. Ilo�� odczytu s�ow ze strumienia zostaje
       * zanicjalizowana na warto�� 0.
       * \param Str - zawiera s�owo kluczowe.
       * \param ID  - zawiera identyfikator skojarzony z danym s�owem
       *              kluczowym.
       */
      KeyPair(const char *Str, int ID) {_Keyword = Str;  _ID = ID; _No = 0;}

      /*!
       *  Udost�pnia tre�� s�owa kluczowego.
       */
      const std::string &Keyword() const { return _Keyword; }
      /*!
       * Udost�pnia identyfikator skojrzaony z danym s�owem kluczowym.
       */
      int          ID() const { return _ID; }
      /*!
       *  Powoduje inkrementacj� licznika napotka� danego s�owa kluczowego,
       *  kt�re nast�pi�o w trakcie odczytu strumienia wej�ciowego.
       */
      void IncEncounterNo() { ++_No; }
      /*!
       *  Udost�pnia warto�� licznika napotka� danego s�owa kluczowego,
       *  kt�re nast�pi�o w trakcie odczytu strumienia wej�ciowego.
       */
      int GetEncounterNo() const { return _No; }
  };

  /*!
   * Klasa reprezentuje list� s��w kluczowych. Obiektami tej klasy
   * s� jednocze�nie elementami stosu list s��w kluczowych
   */
  class KeywordList: public ListItem<KeywordList>, 
                     public List<KeyPair> {
     /*!
      * Pole to zawiera informacj�, czy p�tla przegl�dania s��w kluczowych
      * mo�e automatycznie zako�czy� si� po napotkaniu wszystkich
      * s��w kluczowych.
      */
      bool _CanEndAfterMeetingAll;
     public:
    /*!
     *  Inicjalizuje obiekt.
     *  \param CanEndAfterMeetingAll - warto�� \p true tego parametru
     *          zezwoli na automatyczne przerwanie p�tli szukania 
     *          w strumieniu wej�ciowym kolejnych s��w kluczowych.
     */
     KeywordList( bool CanEndAfterMeetingAll = false ) 
                     {  _CanEndAfterMeetingAll = CanEndAfterMeetingAll; }
      ~KeywordList() {}
     /*!
      * Udost�pnia wszystkie s�owa kluczowe. Ka�de z nich odzielone
      * jest od pozosta�ych przecinkiem.
      * \param Keywords - (\b out) po zakonczeniu dzia�ania metody
      *                zawiera zbi�r s��w kluczowych znajduj�cych
      *                si� w danej li�cie.
      */
     void GetAllKeywords(std::string  &Keywords);
     /*!
      * Udost�pnia informacj�, czy wszystkie s�owa kluczowe znajduj�ce si�
      * na li�cie zosta�y ju� napotkane w trakcie odczytu.
      * \retval true - je�li wszystkie s�owa kluczowe znajduj�ce si� na
      *                li�cie zosta�y ju� napotkane. Warto�� ta jest 
      *           zwracana r�wnie� w przypadku, gdy lista jest pusta.
      * \retval false - w przypadku przeciwnym.
      */
     bool AllKeywordsWereVisited() const;
     /*!
      * Zwraca informacj�, czy p�tla szukania kolejnych s��w kluczowych
      * w strumieniu wej�ciowym musi by� kontynuowana, czy te� mo�e zosta�
      * ju� przerwana.
      * \retval true - je�li p�tla szukania s��w kluczowych mo�e zosta�
      *                przerwana.
      * \retval false - w przypadku przeciwnym.
      */
     bool ShouldLoopBeContinued() const;
    /*!
     * Metoda zezwala na samoczynne zako�czenie p�tli szukania s��w
     * kluczowych
     * w przypadku, gdy ka�de s�owo z tego zbioru ju� wyst�pi�o.
     */
     void AllowEndAfterMeetingAll() { _CanEndAfterMeetingAll = true; }
    /*!
     * Metoda zabrania na samoczynne zako�czenie p�tli szukania s��w 
     * kluczowych
     * w przypadku, gdy ka�de s�owo z tego zbioru ju� wyst�pi�o.
     */
     void ForbidEndAfterMeetingAll() { _CanEndAfterMeetingAll = false; }
  };

  
  class MultiStack: protected List<KeywordList> {
    /*!
     *  Pole to sygnalizuje inicjalizacje nowej kolejki
     *  s��w kluczowych. Je�eli pole to zwiera warto��
     *  \p true, to ka�da operacja dodania nowej pary
     *  s�owa kluczowego i indeksu b�dzie tworzy�a nowy 
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
      * Zwraca informacj�, czy p�tla szukania kolejnych s��w kluczowych
      * w strumieniu wej�ciowym musi by� kontynuowana, czy te� mo�e zosta�
      * ju� przerwana.
      * \retval true - je�li p�tla szukania s��w kluczowych mo�e zosta�
      *                przerwana. 
      * \retval false - w przypadku przeciwnym. Mo�e to nast�pi�, gdy
      *                bie��cy zbi�r s��w kluczowych jest pusty lub
      *                gdy wszystkie s�owa z danego zbioru zosta�y ju�
      *                napotkane w strumieniu wej�ciowym.
      */

      bool ShouldLoopBeContinued() const
        {  return First() ? First()->ShouldLoopBeContinued() : false; }
  };
};

/*!
 *  Klasa SxInterp (Syntax Interpreter) zawiera u�atwienia dla odczytu 
 *  i interpretacji sk�adni napis�w znakowych.
 */
class SxInterp: public std::istringstream, public Sx::MultiStack {
  /*!
   * Pole zawiera numer linii, w ktorej realizowany jest odczyt.
   */
   int  _LineNo;
  /*!
   * Pole przechowuje znak, kt�ry pe�ni rol� lewego nawiasu.
   * Nawiasy wykorzystywane s� przy zbiorczym podawaniu warto�ci,
   * np. wektora.\n
   * Warto�� -1 w tym polu oznacza brak znaku.
   */
   char _Parenthesis_Left;
  /*!
   * Pole przechowuje znak, kt�ry pe�ni rol� prawego nawiasu.
   * Nawiasy wykorzystywane s� przy zbiorczym podawaniu warto�ci,
   * np. wektora.\n
   * Warto�� -1 w tym polu oznacza brak znaku.
   */
   char _Parenthesis_Right;
  /*!
   * Pole przechowuje znak, kt�ry pe�ni rol� separatora przy podawaniu
   * zbiorczym warto�ci, np. warto�ci dla wektora.\n
   * Warto�� -1 w tym polu oznacza brak znaku.
   */
   char _Numbers_Separator;

  /*!
   *  Odczytuje ze strumienia bia�e znaki. Rozpoznaje ko�ce linii
   *  i aktualizuje numer czytanej linii.
   */
   void EatWhite();

  public:  
   /*!
    *  Inicjalizuje strumie� wyj�ciowy przekazanym przez parametr napisem.
    *  \param Str - zawiera napis, kt�ry ma by� doczytany i interpretowany.
    */
    SxInterp(const std::string &Str);
   /*!
    * Udost�pnia stos list s��w kluczowych i skojarzonych z nimi
    * indeks�w. Implementacja stosu realizowana jest poprzez 
    * dziedziczony klas�
    * \link Sx::MultiStack  Sx::MultiStack\endlink.
    *
    * Metoda udost�pnia wspomniany stos w trybie modyfikacji.
    */
    Sx::MultiStack &Stack() { return (*(MultiStack*)this); }
   /*!
    * Udost�pnia stos list s��w kluczowych i skojarzonych z nimi
    * indeks�w. Implementacja stosu realizowana jest poprzez 
    * dziedziczony klas�
    * \link Sx::MultiStack  Sx::MultiStack\endlink.
    *
    * Metoda udost�pnia wspomniany stos w trybie sta�ym.
    */
    const Sx::MultiStack &Stack() const { return (*(MultiStack*)this); }
   /*!
    *  Tworzy nowy element kolejki dla kolejnego zbioru s��w kluczowych
    *  i inicjalizuje spos�b zako�czenia przegl�dania tej kolejki.
    *  \param CanEndAfterMeetingAll - warto�� \p true tego parametru
    *          zezwoli na automatyczne przerwanie p�tli szukania 
    *          w strumieniu wej�ciowym kolejnych s��w kluczowych.
    */
    Sx::MultiStack &Push(bool CanEndAfterMeetingAll = false)  
             { CreateNewKeySet(CanEndAfterMeetingAll); return Stack(); }
   /*!
    *  Ustawia znaki separator�w dla operacji wczytywania warto�ci typu
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
    *  Usuwa ze stosu pierwsz� list� s��w kluczowych i skojrzonych z nimi 
    *  indeksami. W przypadku gdy stos jest pusty, realizacja operacji
    *  nie dokonuje �adnych zmian.
    */
    void Pop() { DeleteFirst(); }
   /*!
    *  Pobiera nast�pne s�owo ze strumienia i sprawdza czy jest ono 
    *  identyczne z jakim� ze s��w znajduj�cych si� w bie��cej kolejce
    *  s��w, kt�re s� oczekiwane.
    *  Je�eli tak, to zwraca jego indeks. W przypadku przeciwnym zg�asza
    *  wyj�tek.
    *  \exception Sx::Exception - mo�e by� zg�aszany jest z kodami b��du:
    *   \li \link sxinterp.hh::ERRNUM_SX__NO_KEYWORDS 
    *             ERRNUM_SX__NO_KEYWORDS\endlink - gdy brak listy ze s�owami
    *             kluczowymi.
    *   \li \link sxinterp.hh::ERRNUM_SX__START_NO_KEYWORD
    *             ERRNUM_SX__START_NO_KEYWORD\endlink - gdy napotkany znak
    *             nie mo�e by� pocz�tkiem �adnego s�owa kluczowego.
    *   \li \link sxinterp.hh::ERRNUM_SX__NO_KEYWORD
    *                              ERRNUM_SX__NO_KEYWORD\endlink
    *             - gdy znalezione s�owo nie jest �adnym z oczekiwanych
    *               s��w kluczowych.
    *   \li \link sxinterp.hh::ERRNUM_SX__NO_WORD
    *                              ERRNUM_SX__NO_WORD\endlink -
    *             gdy nie znaleziono �adnego s�owa.
    */
   int GetNextKeyword(); // throw (Sx::Exception);

   /*!
    *  Pomija znaki bia�e i pobiera ze strumienia znakowego nast�pne 
    *  s�owo.
    *  \param  Word - (\b out) po zako�czeniu dzia�ania zawiera pobrane
    *                 s�owo.
    *  \param  WordAddChars - (\b in) zawiera zbi�r dodatkowych znak�w, 
    *             kt�re mog� wchodzi� w sk�ad s�owa i jednocze�nie je
    *             rozpoczyna�. W sk�ad tego zbioru znak�w nie mog� 
    *             wchodzi� znaki bia�e.\n
    *             Domy�lnie s�owo rozpoczyna si� liter� lub znakiem '_' i
    *             mo�e zawiera� cyfry. Ka�dy inny znak traktowany jest 
    *             jako znak ko�ca s�owa.
    */
    void GetWord(std::string &Word, const char *WordAddChars = 0L);

   /*!
    *  Wczytuje ze strumienia wej�ciowego liczb� typu \e int.
    *  \param Val - (\b out) po wykonanej operacji zawiera
    *               wczytan� liczb�.
    *  \exception Sx::Exception jest zg�aszany w przypadku niemo�no�ci
    *             wczytania liczby.
    *             Obiekt klasy Sx::Exception zglaszany jest
    *                z kodem 
    * \link sxinterp.hh::ERRNUM_SX__FAIL_INT ERRNUM_SX__FAIL_INT\endlink
    */
   void GetNum( int &Val ); // throw (Sx::Exception);

   /*!
    *  Wczytuje ze strumienia wej�ciowego liczb� typu \b float.
    *  \param Val - (\b out) po wykonanej operacji zawiera
    *               wczytan� liczb�.
    *  \exception Sx::Exception jest zg�aszany w przypadku niemo�no�ci
    *             wczytania liczby.
    *             Obiekt klasy Sx::Exception zglaszany jest
    *                z kodem 
    * \link sxinterp.hh::ERRNUM_SX__FAIL_FLOAT
    *                       ERRNUM_SX__FAIL_FLOAT\endlink
    */
   void GetNum( float &Val ); // throw (Sx::Exception);
   /*!
    * Metoda umo�liwia wczytanie warto�ci typu \b float wektora 3D.
    * \param Val1 - (\b out) pierwsza sk�adowa.
    * \param Val2 - (\b out) druga sk�adowa.
    * \param Val3 - (\b out) trzecia sk�adowa.
    *  \exception Sx::Exception jest zg�aszany w przypadku niemo�no�ci
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
   *  Odczytuje znaki bia�e ze strumienia, a� do momentu napotkania 
   *  oczekiwanego znaku. Napotkanie innego niebia�ego znaku powoduje
   *  zg�oszenie wyj�tku.
   *  \param  Ch - oczekiwany znak, mo�e by� nim r�wnie� znak bia�y.
   *  \exception Sx::Exception jest zg�aszany w przypadku napotkania innego
   *                znaku ni� oczekiwany znak \e Ch.
   *                Obiekt klasy Sx::Exception zglaszany jest
   *                z kodem 
   * \link sxinterp.hh::ERRNUM_SX__UNEXP_CHAR 
   *                       ERRNUM_SX__UNEXP_CHAR\endlink
   */
   void LookForChar(char Ch); // throw (Sx::Exception);

   /*!
    * Zwraca informacj�, czy p�tla szukania kolejnych s��w kluczowych
    * w strumieniu wej�ciowym musi by� kontynuowana, czy te� mo�e zosta�
    * ju� przerwana.
    * \retval true - je�li p�tla szukania s��w kluczowych mo�e zosta�
    *                przerwana. 
    * \retval false - w przypadku przeciwnym. Mo�e to nast�pi�, gdy
    *                bie��cy zbi�r s��w kluczowych jest pusty lub
    *                gdy wszystkie s�owa z danego zbioru zosta�y ju�
    *                napotkane w strumieniu wej�ciowym.
    */
  bool ShouldLoopBeContinued() const 
                         {return Stack().ShouldLoopBeContinued();}
};


/*!
 *  Makro definiuje zmienne, kt�re wykorzystywane s� do realizacji
 *  p�tli analizy syntaktycznej i indeksowania znalezionych s��w.
 *  Indeks s�owa jest podstaw� wyboru odpowiedniej sekcji 
 *  \e case. 
 *
 *  Makro \b SXCMD_DEFINE_VAR zawiera definicj� zmiennych:
 *  \li \b bool \e SxContinueThisLoop - poprzez ni� realizowane jest
 *          sterowanie momentem zako�czenia danej p�tli.
 *  \li \b bool \e SxContinueAllLoops - w przypadku, gdy w danej metodzie
 *          jest kilka zagnie�d�onych p�tli, zmienna ta umo�liwia 
 *          przerwanie wykonywania wszystkich p�tli.
 *  \li \b char \e Key - wykorzystywana jest do przypisywania warto�ci
 *          indeksu odpowiadaj�cego danemu s�owu. Wykorzystywana ona
 *          jest nast�pnie w instrukcji \b switch do selekcji w�a�ciwej
 *          akcji zwi�zanej z danym s�owem.
 */
#define SXCMD_DEFINE_VAR     bool SxContinueThisLoop = true;\
                             bool SxContinueAllLoops = true;\
                             char Key;


/*!
 *  Powoduje zako�czenie wykonywania danej p�tli.
 */
#define SXCMD_BREAK_THIS_LOOP  SxContinueThisLoop = false;  break;
/*!
 *  Powoduje zako�czenie wykonywania wszystkich zagnie�d�onych p�tli
 *  w danej funkcji lub metodzie.
 */
#define SXCMD_BREAK_ALL_LOOPS  SxContinueAllLoops = false;  break;

/*!
 * Makro wykorzystywane jest do zainicjalizowania p�tli analizy
 * syntakycznej. W p�tli tej sprawdzane jest wyst�pienie jednego z zadanych
 * s��w kluczowych.
 * \param Interp - zmienna klasy \b SyntaxInterp lub klasy pochodnej.
 * \param MacroKeywordList  - lista kluczy z indetyfikatorami.
 *                             Lista musi mie� posta�\n
 * \verbatim
    (SlowoKluczowe1,Indeks1)(SlowoKluczowe2,Indeks2)...(SlowoKluczoweN,IndeksN)
   \endverbatim
 * gdzie \e SlowoKluczoweK to �a�cuch znak�w w sensie j�zyka \b C, za�
 *        \e IndeksK to znak lub liczba typu \e integer.
 *
 * Przyk�ad wykorzystania makra:
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
 *      nale�y wcze�nij u�y� makra 
 *   \link sxinterp.hh::SXCMD_DEFINE_VAR 
 *         sxinterp.hh::SXCMD_DEFINE_VAR\endlink.
 */
#define SXCMD_START_LOOP(Interp, MacroKeywordList)                 \
    Interp.Push()MacroKeywordList;                                 \
    SxContinueThisLoop = true;                                     \
    while (Interp && SxContinueThisLoop && SxContinueAllLoops) {   \
      switch (Key=Interp.GetNextKeyword()) {

/*!
 * Makro inicjalizuje i organizuje p�tl� przeg�adani s��w kluczowych.
 * Pozwala na automatyczne zako�czenie p�tli w przypadku napotkania
 * wszystkich s��w kluczowych z danego zbioru.
 * \param Interp - musi to by� obiekt klasy SxInterp lub klasy pochodnej
 *            (np ViSynxInterp). Obiekt ten wst�pnie musi by� skojarzony
 *            z jakimi� opisem.
 * \param MacroKeywordList - zaiwiera list� s��w kluczowych i skojarzonych
 *            z nimi indeksami. Lista musi mie� posta�:
 * \verbatim
    (SlowoKluczowe1,Indeks1)(SlowoKluczowe2,Indeks2)...(SlowoKluczoweN,IndeksN)
   \endverbatim
 * gdzie \e SlowoKluczoweK to �a�cuch znak�w w sensie j�zyka \b C, za�
 *        \e IndeksK to znak lub liczba typu \e integer.
 *
 * Przyk�ad wykorzystania makra:
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
 *      nale�y wcze�nij u�y� makra 
 *   \link sxinterp.hh::SXCMD_DEFINE_VAR SXCMD_DEFINE_VAR\endlink.
 */
#define SXCMD_START_LOOP2END(Interp,MacroKeywordList)                    \
    Interp.Push(true)MacroKeywordList;                                   \
    SxContinueThisLoop = true;                                           \
    while (Interp.ShouldLoopBeContinued() && Interp && SxContinueThisLoop\
                                          && SxContinueAllLoops) {       \
      switch (Key=Interp.GetNextKeyword()) {


/*!
 * Makro to ko�czy p�tl� analizy syntaktcznej danego strumienia.
 * Powoduje r�wnie� usuni�cie ze stosu list� s��w kluczowych i skojarzonych
 * z ni� indeks�w, kt�ra to lista podana zosta�a w przy rozpocz�ciu 
 * p�tli (patrz opis makra 
 *  \link sxinterp.hh::SXCMD_START_LOOP2END 
 *        sxinterp.hh::SXCMD_START_LOOP2END\endlink).
 * \param Interp - musi to by� obiekt klasy SxInterp lub klasy pochodnej
 *            (np ViSynxInterp). Musi to by� ten sam obiek, kt�ry 
 *            wyst�pi� wcze�niej w makrze 
 *  \link sxinterp.hh::SXCMD_START_LOOP2END 
 *        sxinterp.hh::SXCMD_START_LOOP2END\endlink lub
 *  \link sxinterp.hh::SXCMD_START_LOOP SXCMD_START_LOOP\endlink.
 */
#define SXCMD_END_LOOP(Interp) }} Interp.Pop();  SxContinueThisLoop = true;




#endif
