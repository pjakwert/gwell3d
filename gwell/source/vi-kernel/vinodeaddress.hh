#ifndef VINODEADDRESS_HH
#define VINODEADDRESS_HH

/*!
 * \file vinodeaddress.hh
 * Plik zawiera definicjê klasy ViNodeAddress. Obiekty tej klasy wykorzystywane
 * s± do tworzenia adresów wêz³ów w strukturze drzewiastej tworzonej
 * w oparciu obiekty klasy ViElemePolyh i ViMultiPolyh.
 * \author Bogdan Kreczmer
 * \date   2003.10
 */

#ifdef __GNUG__
#pragma interface
#endif

#include <iostream>
#include "extstring.hh"



/*!
 *  Znak wykorzystywany jako separator w adresie wêz³a.
 */
#define  NA_SEPARATOR   '.'

/*!
 *  Napis identyfikuj±cy korzeñ struktury drzewiastej.
 *  Jest on przewidziany do usuniêcia i zast±pienia znakiem separatora.
 */
#define  NA_ROOT        "ROOT"

/*!
 * Znak przewidziany do sygnalizowania b³êdu w przypadku niemo¿no¶ci
 * ustalenia adresu danego wêz³a.
 */
#define  NA_ERROR       "?"

/*
 *  .Etykieta1.Etykieta2.Etykieta3. ... .EtykietaN
 *   0    1        2         3              N
 *   ^
 *   Root
 */

/*!
 * Klasa udostêpnia u³atwienia tworzenia adresów poszczególnych wêz³ów
 * struktury drzewiastej.
 *
 *  Sk³adnia adresu:
 *
 *  .Etykieta1.Etykieta2.Etykieta3. ... .EtykietaN
 *
 * Pierwsza kropka odpowiada scenie. Nastêpuj±ce po sobie etykiety
 * s± nazwami kolejnych wêz³ów (ViNTreeNode, nazwy przechowywane
 * s± w polu: \link ViNTreeNode::_IndivName 
 *                  ViNTreeNode::_IndivName\endlink)
 * "le¿±cych" na tej samej ga³êzi drzewa.
 * 
 * Konstrukcja adresu nawi±zuje do lokalizaji pliku w drzewie katalogu
 * lub adresów Horna (w tym ostatnim przypadku nawi±zanie to jest ju¿
 * znacznie bardziej "lu¼ne").
 */
class ViNodeAddress: public ExtString {
  /*!
   * Pole pomocnicze wykorzystywane przy pobieraniu
   * kolejnych etykiet wêz³ów z pe³nego adresu.
   */
  int _No;

 public:
  /*!
   * Inicjalizuje adres jako ³añcuch pusty.
   */
  ViNodeAddress(): _No(1) {}
  /*!
   *  Inicjalizuje adres przekazanym ³añcuchem znaków.
   *  \param Address - ci±g znaków, który musi byæ prawid³ow± form±
   *                   adresu.
   */
  ViNodeAddress(const char *Address): ExtString(Address), _No(1) {}

  /*!
   *  Inicjalizuje adres przekazanym ³añcuchem znaków.
   *  \param Address - ci±g znaków, który musi byæ prawid³ow± form±
   *                   adresu.
   */
  ViNodeAddress(const ExtString &Address): ExtString(Address), _No(1) {}




  /*!
   *  Udostêpnia robocz± warto¶æ indeksu wykorzystywan± przez metody
   *  \link ViNodeAddress::GetFirstLabel GetFirstLabel\endlink oraz
   *  \link ViNodeAddress::GetNextLabel GetNextLabel\endlink.
   *  Chwilowa warto¶æ indeksu jest przechowywana w polu
   *  \link ViNodeAddress::_No _No\endlink.
   *
   *  Metoda \b GetAuxNo ma charakter pomocniczy.
   */
  int GetAuxNo() const { return _No; }

  /*!
   *  Podstawia jako adres dany ci±g znaków.
   *  \param Str - ci±g znaków, który ma byæ podstawiony jako adres wêz³a.
   */
  ViNodeAddress &operator = (char const * const Str);
  /*!
   *  Podstawia jako adres ci±g sk³adaj±cy siê z jednego znaku.
   *  \param c - znak, który ma byæ podstawiony jako adres wêz³a.
   */
  ViNodeAddress &operator = (char const c);

   /*!
    * Udostêpnia pierwsz± etykietê z ca³ego adresu.
    * \param Lb - zapisywana jest w niej udostêpniana etykieta.
    * \post 
    *  Udostêpniona etykieta (o ile istnieje) zapisana zostaje do 
    *  parametru \e Lb. Ponadto do pola \link ViNodeAddress::_No _No\endlink
    *  wpisana zostaje warto¶æ 1.
    * \retval 0 - je¶li zostje znaleziona pierwsza etykieta i 
    *             zostanie ona udostêpniona.
    * \retval -1 - gdy ³añcuch jest pusty (b³±d).
    * \retval -2 - gdy pierwszy znak jest ró¿ny do separatora (b³±d)
    * \retval -4 - gdy nie ma pierwszej etykiety.
    */
  int GetFirstLabel(ExtString &Lb);

   /*!
    * Udostêpnia nastêpn± etykietê z danego adresu. Metoda ta wraz z metod±
    * \link ViNodeAddress::GetFirstLabel GetFirstLabel\endlink daje mo¿liwo¶æ
    * iterowania kolejnych etykiet (tzn. nazw wêz³ów po¶rednich) z pe³nego
    *  adresu wêz³a.
    * \param NodeLabel - udostêpnia wynik dzia³ania metody, tzn
    *               wyekstrahowan± kolejn± etykietê z adresu
    *                   (o ile okaza³o to siê to mo¿liwe).
    * \retval 0 - etykieta zosta³a wyekstrahowana. Operacja zakoñczy³a siê
    *             powodzeniem,
    * \retval -1 - nie mo¿na by³o wydobyæ etykiety, gdy¿ adres jest pustym
    *             ³±ñcuchem znakowym,
    * \retval -2 - pierwszy znak w adresie nie jest znakiem separator,
    * \retval -4 - adres jest krótszy ni¿ indeks ¿±danej etykiety.
    */
  int GetNextLabel(ExtString &NodeLabel);

   /*!
    * Udostêpnia i-t± etykietê z danego adresu.
    * \param Idx - numer udostêpnianej etykiety (numeracja jest od 0,
    *              przy czym zerow± etykiet± jest etykieta korzenia 
    *              calej struktury - w tej chwili jest to etykieta pusta).
    *              Tak wiêc etykiety nale¿±ce
    *              do poszczególnych obiektów zaczynaj± siê od nr 1.
    * \param NodeLabel - udostêpnia wynik dzia³ania metody, tzn
    *               wyekstrahowan± i-t± etykietê z adresu
    *                   (o ile okaza³o to siê to mo¿liwe).
    * \retval 0 - etykieta zosta³a wyekstrahowana. Operacja zakoñczy³a siê
    *             powodzeniem,
    * \retval -1 - nie mo¿na by³o wydobyæ etykiety, gdy¿ adres jest pustym
    *             ³±ñcuchem znakowym,
    * \retval -2 - pierwszy znak w adresie nie jest znakiem separator,
    * \retval -4 - adres jest krótszy ni¿ indeks ¿±danej etykiety.
    */
  int GetLabel_ith(unsigned int Idx, ExtString &NodeLabel) const;

   /*!
    *  Dokonuje ekstrakcji ¶cie¿ki z pe³nego adresu wêz³a bez ostatniego
    *  separatora, tzn. znaku '.' . Przez ¶cie¿kê
    *  adres bez ostatniej etykiety wêz³a. ¦cie¿ka jest wiêc zakoñczona
    *  separatorem.
    *  \param  Path - (out) zawiera wynik dzia³ania metody (o ile zakoñczy³o
    *              siê ono powodzeniem).
    *  \retval  0 - operacja zakoñczy³a siê powodzeniem, wyekstrahowana
    *              ¶cie¿ka umieszczona zosta³a w \e Path,
    *  \retval -1 - gdy ³añcuch pusty,
    *  \retval -2 - adres nie rozpoczyna siê od znaku '.' .
    */
  int ExtractWithoutLast(ExtString &Path) const;

   /*!
    *  Dokonuje ekstrakcji ¶cie¿ki z pe³nego adresu wêz³a. Przez ¶cie¿kê
    *  adres bez ostatniej etykiety wêz³a. ¦cie¿ka jest wiêc zakoñczona
    *  separatorem.
    *  \param  Path - (out) zawiera wynik dzia³ania metody (o ile zakoñczy³o
    *              siê ono powodzeniem).
    *  \retval  0 - operacja zakoñczy³a siê powodzeniem, wyekstrahowana
    *              ¶cie¿ka umieszczona zosta³a w \e Path,
    *  \retval -1 - gdy ³añcuch pusty,
    *  \retval -2 - adres nie rozpoczyna siê od znaku '.' .
    */
  int ExtractPath(ExtString &Path) const;

   /*!
    *  Ekstrahuje z pe³nego adresu ostatni± etykietê
    *  
    * \param NodeLabel - udostêpnia wynik dzia³ania metody, tzn
    *               wyekstrahowan± ostatni± etykietê z adresu
    *                   (o ile okaza³o to siê to mo¿liwe).
    * \retval 0 - etykieta zosta³a wyekstrahowana. Operacja zakoñczy³a siê
    *             powodzeniem,
    * \retval -4 - adres jest krótszy ni¿ indeks ¿±danej etykiety.
    */
  int ExtractLastLabel(ExtString &NodeLabel) const;

  /*!
   *  Dodaje etykietê do adresu poprzedzaj±c j± separatorem, o ile adres
   *  nie jest ju¿ nim zakoñczony (tzn. nie jest ¶cie¿k±). 
   *  \param Label - etykieta dodawana do dotyczasowego adresu.
   *  \post Nowa etykieta zostaj dodana adresu towrz±c adres wêz³a
   *        o etykiecie przezkazanej przez \e Label.
   */
  int AddLabel(char const *Label);
  /*!
   *  Wyznacza d³ugo¶æ adresu, tzn. ilo¶æ etykiet co równowa¿ne jest
   *  g³êbo¶ci w strukturze drzewiastej, na której umieszczony jest
   *  wêze³ o tym adresie. D³ugo¶æ adresu liczona jest poprzez zliczanie
   *  separatorów + 1. Je¿eli na koñcu adresu dopisany jest separator, po
   *  którym nie nastêpuje etykieta wêz³a, to nie bêdzie on liczony.
   *
   * Poni¿ej znajduje siê przyk³ad liczenia d³ugo¶ci adresu:
   \verbatim
     Address: ""                 D³ugo¶æ = 0
     Address: "."                D³ugo¶æ = 1
     Address: ".aaa.bbb.ccc"     D³ugo¶æ = 4
     Address: "xxx.aaa.bbb.ccc"  D³ugo¶æ = 4
   \endverbatim
   *  W drugim i trzecim przyk³adzie zerowa etykieta jest pusta, niemniej stanowi
   *  równie¿ element adresu.
   *  \return d³ugo¶æ adresu. 
   */
  unsigned int AddressLength() const;
  /*!
   *  Sprawdza czy adres nie jest zakoñczony separatorem.
   *  \retval true - je¶li jest zakoñczony separatorem, tzn. znakiem '.' .
   *  \retval false - w przypadku przeciwnym.
   */
  bool IsSeparatorAtEnd() const;
  /*!
   *  Sprawdza, czy adres dostêpny poprzez parametr \e Addr jest pocz±tkiem
   *  adresu zawartego w obiekcie, dla którego metoda ta zosta³a wywo³ana.
   *  \param Addr - adres, dla którego realizowane jest sprawdzenie.
   *  \retval true - je¶li \e Addr zawiera adres, który jest pocz±tkiem lub
   *                 jest idenyczny z adresem jaki jest zawarty w obiekcie,
   *                 dla którego wywo³ano tê metodê.
   *  \retval false - w przypadku przeciwnym.
   */
  bool IsHeadOf(ViNodeAddress const &Addr) const;
  /*!
   *  Dokonuje ekstrackji pocz±tku adresu o d³ugo¶ci podanej przez parametr
   *  \e Len. 
   *  \param Len - (\b in) d³ugo¶æ adresu od jego pocz±tku, który ma byæ
   *               wyekstrahowany z adresu dotychczasowego.
   *  \param Addr - (\b out) zawiera wynik przeprowadzonej operacji, o ile
   *                operacja ta oka¿e siê mo¿liwa do wykonania.
   *  \retval 0 - operacja zakoñczy³a siê powodzeniem, wynik dzia³ania 
   *            zosta³ umieszczony w parametrze \e Addr.
   *  \retval -1 - adres jest ³añcuchem pustym. Parametrowi \e Addr zostaje
   *               przypisany ³añcuch pusty.
   *  \retval -2 - parametr \e Len ma warto¶æ 0. Parametrowi \e Addr zostaje
   *               przypisany ³añcuch pusty.
   *  \retval -3 - adres jest krótszy ni¿ podana d³ugo¶æ w parametrze 
   *               \e Len. Ca³y adres zostaje przypisany parametrowi
   *               \e Addr.
   *  
   */
  int ExtractHead(unsigned Len, ViNodeAddress &Addr) const;
};



inline
bool ViNodeAddress::IsSeparatorAtEnd() const
{
  if (IsEmpty()) return false;
  return (*this)[length()-1] == NA_SEPARATOR;
}

/*!
 *  Wy¶wietla na wej¶cie standardowe zawarto¶æ adresu wêz³a.
 */
inline
std::ostream &operator << (std::ostream &ostm, ViNodeAddress const &NodeAddress)
{  return ostm << NodeAddress.c_str(); }

#endif
