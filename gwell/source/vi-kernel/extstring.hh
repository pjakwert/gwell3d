#ifndef EXTSTRING_HH
#define EXTSTRING_HH

/*! \file extstring.hh
 *  Plik zawiera definicjê klasy ExtString (Extended String). Jest to
 *  nak³adka na standardowa klasê std::string.
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
 *  nak³adka na standardow± klasê std::string.
 */
class ExtString: public std::string {
  /*!
   *  Metoda pomocnicza. Dopisuje zawarto¶æ strumienia do obiektu \b *this.
   *  \param ostrm - strumieñ z którego zawarto¶æ jest przepisywana 
   *  do \b *this.
   *  \return referencjê do \b *this.
   */
  ExtString &Add(const std::ostringstream &ostrm); 

   /*!
    * Sprawdza, czy od i-tej pozycji do koñca ³añcuch zawiera tylko
    * bia³e znaki.
    */
  int IsSpaceToEnd(size_type i) const;
 public:

  /*!
   *  Dokonuje porównania dwóch ³añcuchów znakowych w sensie ³añcuchów
   *  jêzyka C.
   * \param Str - wska¼nik na ³añcuch w sensie jêzyka \b C.
   * \pre  \f$ Str \ne NULL\f$ oraz \b *this nie jest obiektem pustym.
   * \retval true - gdy ³añcuchy s± indentyczne.
   * \retval false - w przyapadku przeciwnym.
   */
  bool operator == (const char *Str) const;


  /*!
   *  Dokonuje porównania dwóch ³añcuchów znakowych w sensie ³añcuchów
   *  jêzyka C++. W przypadku, gdy ³añcuchy s± ró¿ne zwracana jest warto¶æ
   *  \p true.
   */
  bool operator != (const char *Str) const { return !(*this == Str); }

  /*!
   *  Dokonuje porównania dwóch ³añcuchów znakowych w sensie ³añcuchów
   *  jêzyka C++.
   */
  bool operator == (const std::string &Str) const;
  /*!
   *  Dokonuje porównania dwóch ³añcuchów znakowych w sensie ³añcuchów
   *  jêzyka C++. W przypadku, gdy ³añcuchy s± ró¿ne zwracana jest warto¶æ
   *  \p true.
   */
  bool operator != (const std::string &Str) const { return !(*this == Str); }

  /*!
   *  Dokonuje porównania dwóch ³añcuchów znakowych w sensie ³añcuchów
   *  jêzyka C++.
   */
  bool operator == (const ExtString &Str) const
                               { return *this == *(const std::string*)&Str; }


   /*!
    * Wykonuje operacjê podstawienia, tzn. kopiuje ³añcuch znaków zawarty
    * w obiekcie \e Str. 
    * \param Str - (\b in) obiekt, którego zawarto¶æ (tablica znaków)
    *               ma zostaæ przekiowany do obiektu \b this.
    */
  ExtString &operator = (const std::string &Str);

   /*!
    * Wykonuje operacjê podstawienia, tzn. kopiuje ³añcuch znaków wskazany 
    * przez \e Str.
    */
  ExtString &operator = (char const * const Str);

   /*!
    * Wykonuje operacjê podstawienia pojedynczego znaku, tzn.
    * tworzy ³añcuch znakowy sk³adaj±cy siê z jednego znaku przekazanego
    * przez parametr \e c.
    */
  ExtString &operator = (char const c);

   /*!
    * Wykonuje operacjê dopisania ³añcucha znaków wskazanego
    * przez \e Str.
    */
  ExtString &operator << (char const * const Str);

   /*!
    * Wykonuje operacjê dopisania pojedynczego znaku udostêpnionego
    * przez parametr \e c.
    */
  ExtString &operator << (char const c);

   /*!
    * Wykonuje operacjê dopisania pojedynczej liczby typu int.
    */
  ExtString &operator << (int val);

   /*!
    * Wykonuje operacjê dopisania pojedynczej liczby typu unsigned int.
    */
  ExtString &operator << (unsigned int val);

   /*!
    * Wykonuje operacjê dopisania pojedynczej liczby typu long int.
    */
  ExtString &operator << (long int val);

   /*!
    * Wykonuje operacjê dopisania pojedynczej liczby typu unsigned long int.
    */
  ExtString &operator << (unsigned long int val);

   /*!
    * Wykonuje operacjê dopisania pojedynczej liczby float.
    */
  ExtString &operator << (float val);


   /*!
    * Wykonuje operacjê dopisania pojedynczej liczby double.
    */
  ExtString &operator << (double val);


   /*!
    * Udostêpnia zawarto¶æ w postaci ³añcucha znaków w sensie jêzyka C.
    *
    * Operatora nie nale¿y stosowaæ. Przeznaczony jest on
    * do usuniêcia. Jego wprowadzenie podyktowane jest konieczno¶ci±
    * zachowania zgodno¶ci z poprzednia wersj±.
    *
    */
  char const * operator () () const { return c_str(); }

   /*!
    * Konwerter udostêpnia zawarto¶æ w postaci ³añcucha znaków
    * w sensie jêzyka C.
    */
  operator char const * () const { return c_str(); }

  /*!
   * Sprawdza czy ³añcuch jest pusty.
   * \retval true - je¶li ³añcuch jest pusty,
   * \retval false - w przypadku przeciwnym.
   */
  bool IsEmpty() const { return empty(); }

  /*!
   *  Sprawdza czy w danym tablicy znaków skojarzonej z danym obiektem
   *  mo¿na znale¼æ zadany znak.
   *  \param c - szukany znak.
   *  \retval true - je¶li znak zostanie znaleziony,
   *  \retval false - w przypadku przeciwnym.
   */
  bool IsInString(char c) const { return find(c) != std::string::npos; }

   /*!
    * Zmienia wszystkie litery w ³añcuchu na ma³e.
    */
  void ToLower();

  /*!
   *  Dodaje do koñca ³añcucha znaków spacje.
   *  \param No - ilo¶æ spacji, które maj± byæ dodane na koniec
   *              ³añcucha znaków.
   */
  void AddSpace(unsigned int No);
   /*!
    * Usuwa znaki bia³e z przodu i ty³u ³añcucha.
    */
  void RemoveSpace();

   /*!
    * Sprawdza czy ³añcuch znaków zawiera tylko znaki bia³e lub jest pusty,
    * czy te¿ nie.
    * \retval true - gdy tekst zawiera tylko znaki bia³e lub gdy jest to
    *                ³añcuch pusty.
    * \retval false - w przypadku przeciwnym.
    */
  bool IsEmptyText() const;

  /*!
   *  Znajduje miejsce w tablicy znakowej, od którego rozpoczyna siê
   *  nastêpna linia.
   *  \param  Idx - (\b in) wskazuje miejsce, od którego nale¿y szukaæ nowej
   *          linii.
   *  \return warto¶æ indeksu znaku w ³añcuchu, od którego rozpoczyna siê 
   *          nastêpna linia. Je¿eli takiej linii nie ma, to zwraca
   *          warto¶æ \p std::string::npos.
   */
  std::string::size_type SkipLine( std::string::size_type Idx ) const;

  /*!
   *  Zwraca pozycjê pierwszego znaku, który nie jest znakiem "bia³ym"
   *  lub jest jednym ze znaków ze zbioru terminatorów.
   *  \param Idx - (\b in) indeks znaku, do którego rozpoczyna siê
   *               poszukiwanie znaku ró¿nego od znaku bia³ego lub
   *               bêd±cego jednym z terminatorów tablicy znaków.
   *  \param TermChars - (\b in) zbiór znaków. Wyst±pienie jednego z tych
   *                     znaków powoduje zaprzestanie dalszego szukania.
   *  \return pozycjê znaku ró¿nego od znaku bi±³ego lub znaku bêd±cego
   *          jednym z terminatorów. Je¿eli ¿aden z tych znaków nie
   *          zostanie znaleziony, to zwracana jest warto¶æ 
   *          \p string::npos.
   */
  std::string::size_type SkipSpace( std::string::size_type Idx,
                                    const char *           TermChars = "\0"
                                  ) const;
  /*!
   * Zwraca pozycjê pierwszego "bia³ego" znaku od zadanej pozycji.
   * \param  Idx - wskazuje miejsce, od którego nale¿y szukaæ pierwszego
   *               "bia³ego" znaku.
   * \return warto¶æ indeksu pierwszego napotkanego bia³ego znaku.
   *         Je¿eli znak taki nie zosta³ znaleziony, to zwaracana jest
   *         warto¶æ \p std::string::npos.
   */
  std::string::size_type GoToSpaceChar(std::string::size_type Idx) const;

  /*!
   * Zwraca pozycjê pierwszego niebia³ego znaku od zadanej pozycji.
   * \param  Idx - wskazuje miejsce, od którego nale¿y szukaæ pierwszego
   *               "niebia³ego" znaku.
   * \return warto¶æ indeksu pierwszego napotkanego niebia³ego znaku.
   *         Je¿eli znak taki nie zosta³ znaleziony, to zwaracana jest
   *         warto¶æ \p std::string::npos.
   */
  std::string::size_type GoToNotSpaceChar(std::string::size_type Idx) const;

  /*!
   *  Ekstrahuje ci±g znaków, który nie jest rozdzielony "bia³ymi" znakami.
   *  Prowadz±ce "bia³e" znaki s± pomijane.
   *  \param Idx - (\b in) indeks znaku, do którego rozpoczyna siê
   *               poszukiwanie ci±gu znaków.
   *  \param Str - (\b out) wyekstrahowany ci±g znaków.
   *  \param TermChars - (\b in) zbiór znaków. Wyst±pienie jednego z tych
   *                     znaków powoduje zaprzestanie dalszego szukania.
   * \retval n - indeks nastêpnego znaku za znalezionym ci±giem.
   * \retval string::npos - w przypadku, gdy szukany ci±g znaków nie zosta³
   *                 znaleziony. 
   */
  std::string::size_type GetNotSpacedString(  
                            std::string::size_type Idx, 
                            ExtString  &           Str,
			    const char *           TermChars = "\n\0"
                         ) const;
   /*!
    * Usuwa ostatnia liniê je¶li sk³ada siê ona tylko z bia³ych
    * znaków.
    * \retval true - je¶li operacja usuniêcia zosta³a wykonana (³añcuch zosta³
    *                zmodyfikowany),
    * \retval false - w przypadku przeciwnym. 
    */
  bool RemoveLastEmptyLine();

   /*!
    * Usuwa koniec linii z koñca tekstu.
    * \retval true - gdy operacja zosta³a wykonana (³añcuch zosta³
    *                zmodyfikowany),
    * \retval false - w przypadku przeciwnym.
    */
  bool RemoveNewLineFromEnd();

   /*!
    * Usuwa puste linie z koñca tekstu. Znak przej¶cia do nowej linii
    * w ostatniej linii nie zostaje usuniêty.
    * \retval true - gdy operacja zosta³a wykonana (³añcuch zosta³
    *                zmodyfikowany),
    * \retval false - w przypadku przeciwnym.
    */
  bool RemoveEmptyTail();

   /*!
    * Usuwa puste linie z koñca tekstu i znak przej¶cia do nowej
    * linii z koñca tekstu.
    * \retval true  - gdy operacja zosta³a wykonana (³añcuch zosta³
    *                zmodyfikowany),
    * \retval false - w przypadku przeciwnym.
    */
  bool RemoveEmptyTailAndLastNL();
 
  /*!
   *  Sprawdza czy na koñcu ³añcucha znaków (w sensie jêzyka C) jest 
   *  znak NL, czy te¿ nie.
   *  \retval true - je¶li na koñcu ³añcucha znaków jest znak NL.
   *  \retval false - je¶li ³añcuch jest pusty lub nia ma na jego 
   *                  koñcu znaku NL.
   */
  bool IsNewLineAtEnd() const;
 
   /*!
    * Powoduje przekopiowanie do Trg pierwszej linii.
    * \param Trg - do niego sk³adowany jest wynik operacji,
    * \param IncludingNL - okre¶la czy przekopiowana linia ma zawieraæ znak
    *              przej¶cia do nowej linii (\e true), czy te¿ nie (\e false).
    * \retval  0 - je¶li istnieje linia tekstu (niekoniecznie zakoñczona
    *            znakiem przej¶cia do nowej linii) i zosta³a ona
    *            przekopiowana do \e Trg. Do przekopiowanej linii do³±czany
    *            jest znak przej¶cia do nowej linii je¶li 
    *            \e IncludingNL = \e true.
    * \retval  -1 - w przypadku przeciwnym.
    *
    */
  int ExtractFirstLineFor(ExtString &Trg, bool IncludingNL=false) const;


   /*!
    * Powoduje przekopiowanie do Trg linii o numerze wskazanym przez \e Idx.
    * Numeracja linii rozpoczyna siê od 0.
    * \param Idx - numer przekopiowanej linii,
    * \param Trg - do niego sk³adowany jest wynik operacji,
    * \param IncludingNL - okre¶la czy przekopiowana linia ma zawieraæ znak
    *              przej¶cia do nowej linii (\e true), czy te¿ nie (\e false).
    * \retval  0 - je¶li istnieje linia tekstu (niekoniecznie zakoñczona
    *            znakiem przej¶cia do nowej linii) o podanym numerze 
    *            i zosta³a ona
    *            przekopiowana do \e Trg. Do przekopiowanej linii do³±czany
    *            jest znak przej¶cia do nowej linii je¶li 
    *            \e IncludingNL = \e true.
    * \retval  -1 - w przypadku przeciwnym.
    *
    */
  int ExtractLineFor(  unsigned int  Idx, 
                       ExtString  &Trg, 
                       bool IncludingNL=false
                    ) const;

   /*!
    *  Znajduje indeks nastêpnego znaku po i-tym wyst±pieniu zadanego znaku.
    *  \param C - zadany znaku dla którego szukana jest okre¶lona wielokrotno¶æ
    *             wyst±pieñ.
    *  \param No - ilo¶æ wyst±pieñ znaku przekazywanego przez parametr \c C.
    *  \retval string::npos - je¶li ³añcuchu nie ma zadanej wielokrotno¶ci
    *          znaków.
    *  \retval indeks - warto¶æ indeksu  nastêpnego znaku po i-tym (\e No)
    *                   wyst±pieniu zadanego znaku (\e C).
    */
  size_type FindBehind_ith(char C, unsigned int No = 0) const;

   /*!
    *  Szuka i-tego wyst±pienia danego ³añcucha.
    *  \param Str - szukany ³añcuch znaków.
    *  \param Idx - numer wyst±pienia poszukiwanej sekwencji.
    *  \pre \e Idx - mo¿e mieæ warto¶ci 1, 2, ... .
    *                W przypadku warto¶ci 0 przyjmuje siê, ¿e zwracana
    *                jest informacja o braku znalezienia danego ³añcucha.
    *  \return indeks znalezionej i-tej sekwencji znaków. W przypadku
    *          gdy sekwencja taka nie zosta³a znaleziona w ogóle lub
    *          i-ty raz, zwracana jest warto¶æ \p string::npos.
    *          Podobnie dzieje siê je¿li \e Str = \p NULL lub
    *          \e Str = "".
    */
  size_type Find_ith(const char *Str, unsigned int Idx) const;

   /*!
    *  Kopiuje od elementu wskazanego przez pBeg
    *  kolejnych 'Size' elementów. Metoda jest nak³adk± na metodê assign.
    *  Jest ona zasz³o¶ci± przewidzian± do usuniêcia w nastêpnych wersjach
    *  tego modu³u.
    *  \param pBeg - wska¼nik na pocz±tek ³añcucha,
    *  \param Size - ilo¶æ przekopiowywanych znaków.
    *  \post Do obiektu przekopiowana zostaje zadana ilo¶æ
    *        elementów tablicy znakowej wskazywanej przez pBeg.
    *  \return referencja na samego siebie.
    */
  ExtString &Copy(char const *pBeg, unsigned int Size);

   /*!
    *  Kopiuje od pierwszego wskazanego przez pBeg do ostatniego
    *  wskazanego przez pEnd. Kopiowanie realizowane jest
    *  ³±cznie z ostatnim znakiem wskazywanym przez pEnd.
    *  Jest ona zasz³o¶ci± przewidzian± do usuniêcia w nastêpnych wersjach
    *  tego modu³u.
    *  \param pBeg - wska¼nik na pocz±tek tablicy znakowej,
    *  \param pEnd - wska¼nik na koniec tablicy znakowej.
    *  \post Do obiektu przekopiowana zostaje wskazany fragment
    *        tablicy znakowej.
    *  \return referencja na samego siebie.
    */
  ExtString &Copy(char const *pBeg, char const *pEnd);

   /*!
    * Inicjalizuje ³añcuch jako ³añcuch pusty.
    */
  ExtString() {}

   /*!
    * Inicjalizuje ³añcuch jako ³añcuch zawieraj±cy napis dostêpny poprzez
    * parametr \e Name.
    * \param Name - ³añcuch znaków.
    * \post
    *   Do utworzonego obiektu przekopiowany zostaje ³añcuch znaków 
    *   (w sensie jêzyka C) udostêpniony poprzez parametr \e Name.
    */
  ExtString(char const *Name);
};


/*!
 * Operacja porównania ³añcucha w sensie jêzyka \b C i zawarto¶ci
 * obiektu klasy ExtString. Operacja zdefiniowana w celu zachowania
 * przemienno¶ci operacji porówniania.
 * \param CStr - wska¼nik na ³añcuch w sensie jêzyka \b C.
 * \param ExStr - referencja do obiektu, z którego wydobywany
 *               jest ³añcuch znaków w sensie jêzyka \b C w celu
 *               prównania z \e CStr.
 * \pre  \f$ CStr \ne NULL\f$ oraz \e ExStr nie jest obiektem pustym.
 * \retval true - gdy ³añcuchy s± indentyczne.
 * \retval false - w przyapadku przeciwnym.
 */
inline
bool operator == (const char *CStr, const ExtString &ExStr)
{
  return ExStr == CStr;
}



/*!
 * Operacja porównania ³añcucha w sensie jêzyka \b C i zawarto¶ci
 * obiektu klasy ExtString. Operacja zdefiniowana w celu zachowania
 * przemienno¶ci operacji porówniania.
 * \param CStr - wska¼nik na ³añcuch w sensie jêzyka \b C.
 * \param ExStr - referencja do obiektu, z którego wydobywany
 *               jest ³añcuch znaków w sensie jêzyka \b C w celu
 *               prównania z \e CStr.
 * \pre  \f$ CStr \ne NULL\f$ oraz \e ExStr nie jest obiektem pustym.
 * \retval false - gdy ³añcuchy s± indentyczne.
 * \retval true - w przyapadku przeciwnym.
 */
inline
bool operator != (const char *CStr, const ExtString &ExStr)
{
  return !(ExStr == CStr);
}



/*!
 *  Wy¶wietla na wej¶cie standardowe zawarto¶æ ³añcucha znaków w sensie
 *  jêzyka C.
 */
inline
std::ostream &operator << (std::ostream &ostm, ExtString const &str)
{  return ostm << str.c_str(); }


#endif
