#ifndef EXTSTRING_HH
#define EXTSTRING_HH

/*! \file extstring.hh
 *  Plik zawiera definicj� klasy ExtString (Extended String). Jest to
 *  nak�adka na standardowa klas� std::string.
 *  \author Bogdan Kreczmer
 *  \date   2003.04.23
 *  \version 1.0.3
 */

//=================================================================
//  Klasa napisu.
//
//  wer. 1.0.2
//       2003.04.23
//

#ifdef __GNUG__
#pragma interface
#endif
#include <string>

/*!
 *  Klasa ExtString (Extended String). Jest to
 *  nak�adka na standardow� klas� std::string.
 */
class ExtString: public std::string {
  /*!
   *  Metoda pomocnicza. Dopisuje zawarto�� strumienia do obiektu \b *this.
   *  \param ostrm - strumie� z kt�rego zawarto�� jest przepisywana 
   *  do \b *this.
   *  \return referencj� do \b *this.
   */
  ExtString &Add(const std::ostringstream &ostrm); 

   /*!
    * Sprawdza, czy od i-tej pozycji do ko�ca �a�cuch zawiera tylko
    * bia�e znaki.
    */
  int IsSpaceToEnd(size_type i) const;
 public:

  /*!
   *  Dokonuje por�wnania dw�ch �a�cuch�w znakowych w sensie �a�cuch�w
   *  j�zyka C.
   * \param Str - wska�nik na �a�cuch w sensie j�zyka \b C.
   * \pre  \f$ Str \ne NULL\f$ oraz \b *this nie jest obiektem pustym.
   * \retval true - gdy �a�cuchy s� indentyczne.
   * \retval false - w przyapadku przeciwnym.
   */
  bool operator == (const char *Str) const;


  /*!
   *  Dokonuje por�wnania dw�ch �a�cuch�w znakowych w sensie �a�cuch�w
   *  j�zyka C++. W przypadku, gdy �a�cuchy s� r�ne zwracana jest warto��
   *  \p true.
   */
  bool operator != (const char *Str) const { return !(*this == Str); }

  /*!
   *  Dokonuje por�wnania dw�ch �a�cuch�w znakowych w sensie �a�cuch�w
   *  j�zyka C++.
   */
  bool operator == (const std::string &Str) const;
  /*!
   *  Dokonuje por�wnania dw�ch �a�cuch�w znakowych w sensie �a�cuch�w
   *  j�zyka C++. W przypadku, gdy �a�cuchy s� r�ne zwracana jest warto��
   *  \p true.
   */
  bool operator != (const std::string &Str) const { return !(*this == Str); }

  /*!
   *  Dokonuje por�wnania dw�ch �a�cuch�w znakowych w sensie �a�cuch�w
   *  j�zyka C++.
   */
  bool operator == (const ExtString &Str) const
                               { return *this == *(const std::string*)&Str; }


   /*!
    * Wykonuje operacj� podstawienia, tzn. kopiuje �a�cuch znak�w zawarty
    * w obiekcie \e Str. 
    * \param Str - (\b in) obiekt, kt�rego zawarto�� (tablica znak�w)
    *               ma zosta� przekiowany do obiektu \b this.
    */
  ExtString &operator = (const std::string &Str);

   /*!
    * Wykonuje operacj� podstawienia, tzn. kopiuje �a�cuch znak�w wskazany 
    * przez \e Str.
    */
  ExtString &operator = (char const * const Str);

   /*!
    * Wykonuje operacj� podstawienia pojedynczego znaku, tzn.
    * tworzy �a�cuch znakowy sk�adaj�cy si� z jednego znaku przekazanego
    * przez parametr \e c.
    */
  ExtString &operator = (char const c);

   /*!
    * Wykonuje operacj� dopisania �a�cucha znak�w wskazanego
    * przez \e Str.
    */
  ExtString &operator << (char const * const Str);

   /*!
    * Wykonuje operacj� dopisania pojedynczego znaku udost�pnionego
    * przez parametr \e c.
    */
  ExtString &operator << (char const c);

   /*!
    * Wykonuje operacj� dopisania pojedynczej liczby typu int.
    */
  ExtString &operator << (int val);

   /*!
    * Wykonuje operacj� dopisania pojedynczej liczby typu unsigned int.
    */
  ExtString &operator << (unsigned int val);

   /*!
    * Wykonuje operacj� dopisania pojedynczej liczby typu long int.
    */
  ExtString &operator << (long int val);

   /*!
    * Wykonuje operacj� dopisania pojedynczej liczby typu unsigned long int.
    */
  ExtString &operator << (unsigned long int val);

   /*!
    * Wykonuje operacj� dopisania pojedynczej liczby float.
    */
  ExtString &operator << (float val);


   /*!
    * Wykonuje operacj� dopisania pojedynczej liczby double.
    */
  ExtString &operator << (double val);


   /*!
    * Udost�pnia zawarto�� w postaci �a�cucha znak�w w sensie j�zyka C.
    *
    * Operatora nie nale�y stosowa�. Przeznaczony jest on
    * do usuni�cia. Jego wprowadzenie podyktowane jest konieczno�ci�
    * zachowania zgodno�ci z poprzednia wersj�.
    *
    */
  char const * operator () () const { return c_str(); }

   /*!
    * Konwerter udost�pnia zawarto�� w postaci �a�cucha znak�w
    * w sensie j�zyka C.
    */
  operator char const * () const { return c_str(); }

  /*!
   * Sprawdza czy �a�cuch jest pusty.
   * \retval true - je�li �a�cuch jest pusty,
   * \retval false - w przypadku przeciwnym.
   */
  bool IsEmpty() const { return empty(); }

  /*!
   *  Sprawdza czy w danym tablicy znak�w skojarzonej z danym obiektem
   *  mo�na znale�� zadany znak.
   *  \param c - szukany znak.
   *  \retval true - je�li znak zostanie znaleziony,
   *  \retval false - w przypadku przeciwnym.
   */
  bool IsInString(char c) const { return find(c) != std::string::npos; }

   /*!
    * Zmienia wszystkie litery w �a�cuchu na ma�e.
    */
  void ToLower();

  /*!
   *  Dodaje do ko�ca �a�cucha znak�w spacje.
   *  \param No - ilo�� spacji, kt�re maj� by� dodane na koniec
   *              �a�cucha znak�w.
   */
  void AddSpace(unsigned int No);
   /*!
    * Usuwa znaki bia�e z przodu i ty�u �a�cucha.
    */
  void RemoveSpace();

   /*!
    * Sprawdza czy �a�cuch znak�w zawiera tylko znaki bia�e lub jest pusty,
    * czy te� nie.
    * \retval true - gdy tekst zawiera tylko znaki bia�e lub gdy jest to
    *                �a�cuch pusty.
    * \retval false - w przypadku przeciwnym.
    */
  bool IsEmptyText() const;

  /*!
   *  Znajduje miejsce w tablicy znakowej, od kt�rego rozpoczyna si�
   *  nast�pna linia.
   *  \param  Idx - (\b in) wskazuje miejsce, od kt�rego nale�y szuka� nowej
   *          linii.
   *  \return warto�� indeksu znaku w �a�cuchu, od kt�rego rozpoczyna si� 
   *          nast�pna linia. Je�eli takiej linii nie ma, to zwraca
   *          warto�� \p std::string::npos.
   */
  std::string::size_type SkipLine( std::string::size_type Idx ) const;

  /*!
   *  Zwraca pozycj� pierwszego znaku, kt�ry nie jest znakiem "bia�ym"
   *  lub jest jednym ze znak�w ze zbioru terminator�w.
   *  \param Idx - (\b in) indeks znaku, do kt�rego rozpoczyna si�
   *               poszukiwanie znaku r�nego od znaku bia�ego lub
   *               b�d�cego jednym z terminator�w tablicy znak�w.
   *  \param TermChars - (\b in) zbi�r znak�w. Wyst�pienie jednego z tych
   *                     znak�w powoduje zaprzestanie dalszego szukania.
   *  \return pozycj� znaku r�nego od znaku bi��ego lub znaku b�d�cego
   *          jednym z terminator�w. Je�eli �aden z tych znak�w nie
   *          zostanie znaleziony, to zwracana jest warto�� 
   *          \p string::npos.
   */
  std::string::size_type SkipSpace( std::string::size_type Idx,
                                    const char *           TermChars = "\0"
                                  ) const;
  /*!
   * Zwraca pozycj� pierwszego "bia�ego" znaku od zadanej pozycji.
   * \param  Idx - wskazuje miejsce, od kt�rego nale�y szuka� pierwszego
   *               "bia�ego" znaku.
   * \return warto�� indeksu pierwszego napotkanego bia�ego znaku.
   *         Je�eli znak taki nie zosta� znaleziony, to zwaracana jest
   *         warto�� \p std::string::npos.
   */
  std::string::size_type GoToSpaceChar(std::string::size_type Idx) const;

  /*!
   * Zwraca pozycj� pierwszego niebia�ego znaku od zadanej pozycji.
   * \param  Idx - wskazuje miejsce, od kt�rego nale�y szuka� pierwszego
   *               "niebia�ego" znaku.
   * \return warto�� indeksu pierwszego napotkanego niebia�ego znaku.
   *         Je�eli znak taki nie zosta� znaleziony, to zwaracana jest
   *         warto�� \p std::string::npos.
   */
  std::string::size_type GoToNotSpaceChar(std::string::size_type Idx) const;

  /*!
   *  Ekstrahuje ci�g znak�w, kt�ry nie jest rozdzielony "bia�ymi" znakami.
   *  Prowadz�ce "bia�e" znaki s� pomijane.
   *  \param Idx - (\b in) indeks znaku, do kt�rego rozpoczyna si�
   *               poszukiwanie ci�gu znak�w.
   *  \param Str - (\b out) wyekstrahowany ci�g znak�w.
   *  \param TermChars - (\b in) zbi�r znak�w. Wyst�pienie jednego z tych
   *                     znak�w powoduje zaprzestanie dalszego szukania.
   * \retval n - indeks nast�pnego znaku za znalezionym ci�giem.
   * \retval string::npos - w przypadku, gdy szukany ci�g znak�w nie zosta�
   *                 znaleziony. 
   */
  std::string::size_type GetNotSpacedString(  
                            std::string::size_type Idx, 
                            ExtString  &           Str,
			    const char *           TermChars = "\n\0"
                         ) const;
   /*!
    * Usuwa ostatnia lini� je�li sk�ada si� ona tylko z bia�ych
    * znak�w.
    * \retval true - je�li operacja usuni�cia zosta�a wykonana (�a�cuch zosta�
    *                zmodyfikowany),
    * \retval false - w przypadku przeciwnym. 
    */
  bool RemoveLastEmptyLine();

   /*!
    * Usuwa koniec linii z ko�ca tekstu.
    * \retval true - gdy operacja zosta�a wykonana (�a�cuch zosta�
    *                zmodyfikowany),
    * \retval false - w przypadku przeciwnym.
    */
  bool RemoveNewLineFromEnd();

   /*!
    * Usuwa puste linie z ko�ca tekstu. Znak przej�cia do nowej linii
    * w ostatniej linii nie zostaje usuni�ty.
    * \retval true - gdy operacja zosta�a wykonana (�a�cuch zosta�
    *                zmodyfikowany),
    * \retval false - w przypadku przeciwnym.
    */
  bool RemoveEmptyTail();

   /*!
    * Usuwa puste linie z ko�ca tekstu i znak przej�cia do nowej
    * linii z ko�ca tekstu.
    * \retval true  - gdy operacja zosta�a wykonana (�a�cuch zosta�
    *                zmodyfikowany),
    * \retval false - w przypadku przeciwnym.
    */
  bool RemoveEmptyTailAndLastNL();
 
  /*!
   *  Sprawdza czy na ko�cu �a�cucha znak�w (w sensie j�zyka C) jest 
   *  znak NL, czy te� nie.
   *  \retval true - je�li na ko�cu �a�cucha znak�w jest znak NL.
   *  \retval false - je�li �a�cuch jest pusty lub nia ma na jego 
   *                  ko�cu znaku NL.
   */
  bool IsNewLineAtEnd() const;
 
   /*!
    * Powoduje przekopiowanie do Trg pierwszej linii.
    * \param Trg - do niego sk�adowany jest wynik operacji,
    * \param IncludingNL - okre�la czy przekopiowana linia ma zawiera� znak
    *              przej�cia do nowej linii (\e true), czy te� nie (\e false).
    * \retval  0 - je�li istnieje linia tekstu (niekoniecznie zako�czona
    *            znakiem przej�cia do nowej linii) i zosta�a ona
    *            przekopiowana do \e Trg. Do przekopiowanej linii do��czany
    *            jest znak przej�cia do nowej linii je�li 
    *            \e IncludingNL = \e true.
    * \retval  -1 - w przypadku przeciwnym.
    *
    */
  int ExtractFirstLineFor(ExtString &Trg, bool IncludingNL=false) const;


   /*!
    * Powoduje przekopiowanie do Trg linii o numerze wskazanym przez \e Idx.
    * Numeracja linii rozpoczyna si� od 0.
    * \param Idx - numer przekopiowanej linii,
    * \param Trg - do niego sk�adowany jest wynik operacji,
    * \param IncludingNL - okre�la czy przekopiowana linia ma zawiera� znak
    *              przej�cia do nowej linii (\e true), czy te� nie (\e false).
    * \retval  0 - je�li istnieje linia tekstu (niekoniecznie zako�czona
    *            znakiem przej�cia do nowej linii) o podanym numerze 
    *            i zosta�a ona
    *            przekopiowana do \e Trg. Do przekopiowanej linii do��czany
    *            jest znak przej�cia do nowej linii je�li 
    *            \e IncludingNL = \e true.
    * \retval  -1 - w przypadku przeciwnym.
    *
    */
  int ExtractLineFor(  unsigned int  Idx, 
                       ExtString  &Trg, 
                       bool IncludingNL=false
                    ) const;

   /*!
    *  Znajduje indeks nast�pnego znaku po i-tym wyst�pieniu zadanego znaku.
    *  \param C - zadany znaku dla kt�rego szukana jest okre�lona wielokrotno��
    *             wyst�pie�.
    *  \param No - ilo�� wyst�pie� znaku przekazywanego przez parametr \c C.
    *  \retval string::npos - je�li �a�cuchu nie ma zadanej wielokrotno�ci
    *          znak�w.
    *  \retval indeks - warto�� indeksu  nast�pnego znaku po i-tym (\e No)
    *                   wyst�pieniu zadanego znaku (\e C).
    */
  size_type FindBehind_ith(char C, unsigned int No = 0) const;

   /*!
    *  Szuka i-tego wyst�pienia danego �a�cucha.
    *  \param Str - szukany �a�cuch znak�w.
    *  \param Idx - numer wyst�pienia poszukiwanej sekwencji.
    *  \pre \e Idx - mo�e mie� warto�ci 1, 2, ... .
    *                W przypadku warto�ci 0 przyjmuje si�, �e zwracana
    *                jest informacja o braku znalezienia danego �a�cucha.
    *  \return indeks znalezionej i-tej sekwencji znak�w. W przypadku
    *          gdy sekwencja taka nie zosta�a znaleziona w og�le lub
    *          i-ty raz, zwracana jest warto�� \p string::npos.
    *          Podobnie dzieje si� je�li \e Str = \p NULL lub
    *          \e Str = "".
    */
  size_type Find_ith(const char *Str, unsigned int Idx) const;

   /*!
    *  Kopiuje od elementu wskazanego przez pBeg
    *  kolejnych 'Size' element�w. Metoda jest nak�adk� na metod� assign.
    *  Jest ona zasz�o�ci� przewidzian� do usuni�cia w nast�pnych wersjach
    *  tego modu�u.
    *  \param pBeg - wska�nik na pocz�tek �a�cucha,
    *  \param Size - ilo�� przekopiowywanych znak�w.
    *  \post Do obiektu przekopiowana zostaje zadana ilo��
    *        element�w tablicy znakowej wskazywanej przez pBeg.
    *  \return referencja na samego siebie.
    */
  ExtString &Copy(char const *pBeg, unsigned int Size);

   /*!
    *  Kopiuje od pierwszego wskazanego przez pBeg do ostatniego
    *  wskazanego przez pEnd. Kopiowanie realizowane jest
    *  ��cznie z ostatnim znakiem wskazywanym przez pEnd.
    *  Jest ona zasz�o�ci� przewidzian� do usuni�cia w nast�pnych wersjach
    *  tego modu�u.
    *  \param pBeg - wska�nik na pocz�tek tablicy znakowej,
    *  \param pEnd - wska�nik na koniec tablicy znakowej.
    *  \post Do obiektu przekopiowana zostaje wskazany fragment
    *        tablicy znakowej.
    *  \return referencja na samego siebie.
    */
  ExtString &Copy(char const *pBeg, char const *pEnd);

   /*!
    * Inicjalizuje �a�cuch jako �a�cuch pusty.
    */
  ExtString() {}

   /*!
    * Inicjalizuje �a�cuch jako �a�cuch zawieraj�cy napis dost�pny poprzez
    * parametr \e Name.
    * \param Name - �a�cuch znak�w.
    * \post
    *   Do utworzonego obiektu przekopiowany zostaje �a�cuch znak�w 
    *   (w sensie j�zyka C) udost�pniony poprzez parametr \e Name.
    */
  ExtString(char const *Name);
};


/*!
 * Operacja por�wnania �a�cucha w sensie j�zyka \b C i zawarto�ci
 * obiektu klasy ExtString. Operacja zdefiniowana w celu zachowania
 * przemienno�ci operacji por�wniania.
 * \param CStr - wska�nik na �a�cuch w sensie j�zyka \b C.
 * \param ExStr - referencja do obiektu, z kt�rego wydobywany
 *               jest �a�cuch znak�w w sensie j�zyka \b C w celu
 *               pr�wnania z \e CStr.
 * \pre  \f$ CStr \ne NULL\f$ oraz \e ExStr nie jest obiektem pustym.
 * \retval true - gdy �a�cuchy s� indentyczne.
 * \retval false - w przyapadku przeciwnym.
 */
inline
bool operator == (const char *CStr, const ExtString &ExStr)
{
  return ExStr == CStr;
}



/*!
 * Operacja por�wnania �a�cucha w sensie j�zyka \b C i zawarto�ci
 * obiektu klasy ExtString. Operacja zdefiniowana w celu zachowania
 * przemienno�ci operacji por�wniania.
 * \param CStr - wska�nik na �a�cuch w sensie j�zyka \b C.
 * \param ExStr - referencja do obiektu, z kt�rego wydobywany
 *               jest �a�cuch znak�w w sensie j�zyka \b C w celu
 *               pr�wnania z \e CStr.
 * \pre  \f$ CStr \ne NULL\f$ oraz \e ExStr nie jest obiektem pustym.
 * \retval false - gdy �a�cuchy s� indentyczne.
 * \retval true - w przyapadku przeciwnym.
 */
inline
bool operator != (const char *CStr, const ExtString &ExStr)
{
  return !(ExStr == CStr);
}



/*!
 *  Wy�wietla na wej�cie standardowe zawarto�� �a�cucha znak�w w sensie
 *  j�zyka C.
 */
inline
std::ostream &operator << (std::ostream &ostm, ExtString const &str)
{  return ostm << str.c_str(); }


#endif
