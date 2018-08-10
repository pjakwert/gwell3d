#ifndef VINODEADDRESS_HH
#define VINODEADDRESS_HH

/*!
 * \file vinodeaddress.hh
 * Plik zawiera definicj� klasy ViNodeAddress. Obiekty tej klasy wykorzystywane
 * s� do tworzenia adres�w w�z��w w strukturze drzewiastej tworzonej
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
 *  Znak wykorzystywany jako separator w adresie w�z�a.
 */
#define  NA_SEPARATOR   '.'

/*!
 *  Napis identyfikuj�cy korze� struktury drzewiastej.
 *  Jest on przewidziany do usuni�cia i zast�pienia znakiem separatora.
 */
#define  NA_ROOT        "ROOT"

/*!
 * Znak przewidziany do sygnalizowania b��du w przypadku niemo�no�ci
 * ustalenia adresu danego w�z�a.
 */
#define  NA_ERROR       "?"

/*
 *  .Etykieta1.Etykieta2.Etykieta3. ... .EtykietaN
 *   0    1        2         3              N
 *   ^
 *   Root
 */

/*!
 * Klasa udost�pnia u�atwienia tworzenia adres�w poszczeg�lnych w�z��w
 * struktury drzewiastej.
 *
 *  Sk�adnia adresu:
 *
 *  .Etykieta1.Etykieta2.Etykieta3. ... .EtykietaN
 *
 * Pierwsza kropka odpowiada scenie. Nast�puj�ce po sobie etykiety
 * s� nazwami kolejnych w�z��w (ViNTreeNode, nazwy przechowywane
 * s� w polu: \link ViNTreeNode::_IndivName 
 *                  ViNTreeNode::_IndivName\endlink)
 * "le��cych" na tej samej ga��zi drzewa.
 * 
 * Konstrukcja adresu nawi�zuje do lokalizaji pliku w drzewie katalogu
 * lub adres�w Horna (w tym ostatnim przypadku nawi�zanie to jest ju�
 * znacznie bardziej "lu�ne").
 */
class ViNodeAddress: public ExtString {
  /*!
   * Pole pomocnicze wykorzystywane przy pobieraniu
   * kolejnych etykiet w�z��w z pe�nego adresu.
   */
  int _No;

 public:
  /*!
   * Inicjalizuje adres jako �a�cuch pusty.
   */
  ViNodeAddress(): _No(1) {}
  /*!
   *  Inicjalizuje adres przekazanym �a�cuchem znak�w.
   *  \param Address - ci�g znak�w, kt�ry musi by� prawid�ow� form�
   *                   adresu.
   */
  ViNodeAddress(const char *Address): ExtString(Address), _No(1) {}

  /*!
   *  Inicjalizuje adres przekazanym �a�cuchem znak�w.
   *  \param Address - ci�g znak�w, kt�ry musi by� prawid�ow� form�
   *                   adresu.
   */
  ViNodeAddress(const ExtString &Address): ExtString(Address), _No(1) {}




  /*!
   *  Udost�pnia robocz� warto�� indeksu wykorzystywan� przez metody
   *  \link ViNodeAddress::GetFirstLabel GetFirstLabel\endlink oraz
   *  \link ViNodeAddress::GetNextLabel GetNextLabel\endlink.
   *  Chwilowa warto�� indeksu jest przechowywana w polu
   *  \link ViNodeAddress::_No _No\endlink.
   *
   *  Metoda \b GetAuxNo ma charakter pomocniczy.
   */
  int GetAuxNo() const { return _No; }

  /*!
   *  Podstawia jako adres dany ci�g znak�w.
   *  \param Str - ci�g znak�w, kt�ry ma by� podstawiony jako adres w�z�a.
   */
  ViNodeAddress &operator = (char const * const Str);
  /*!
   *  Podstawia jako adres ci�g sk�adaj�cy si� z jednego znaku.
   *  \param c - znak, kt�ry ma by� podstawiony jako adres w�z�a.
   */
  ViNodeAddress &operator = (char const c);

   /*!
    * Udost�pnia pierwsz� etykiet� z ca�ego adresu.
    * \param Lb - zapisywana jest w niej udost�pniana etykieta.
    * \post 
    *  Udost�pniona etykieta (o ile istnieje) zapisana zostaje do 
    *  parametru \e Lb. Ponadto do pola \link ViNodeAddress::_No _No\endlink
    *  wpisana zostaje warto�� 1.
    * \retval 0 - je�li zostje znaleziona pierwsza etykieta i 
    *             zostanie ona udost�pniona.
    * \retval -1 - gdy �a�cuch jest pusty (b��d).
    * \retval -2 - gdy pierwszy znak jest r�ny do separatora (b��d)
    * \retval -4 - gdy nie ma pierwszej etykiety.
    */
  int GetFirstLabel(ExtString &Lb);

   /*!
    * Udost�pnia nast�pn� etykiet� z danego adresu. Metoda ta wraz z metod�
    * \link ViNodeAddress::GetFirstLabel GetFirstLabel\endlink daje mo�liwo��
    * iterowania kolejnych etykiet (tzn. nazw w�z��w po�rednich) z pe�nego
    *  adresu w�z�a.
    * \param NodeLabel - udost�pnia wynik dzia�ania metody, tzn
    *               wyekstrahowan� kolejn� etykiet� z adresu
    *                   (o ile okaza�o to si� to mo�liwe).
    * \retval 0 - etykieta zosta�a wyekstrahowana. Operacja zako�czy�a si�
    *             powodzeniem,
    * \retval -1 - nie mo�na by�o wydoby� etykiety, gdy� adres jest pustym
    *             ���cuchem znakowym,
    * \retval -2 - pierwszy znak w adresie nie jest znakiem separator,
    * \retval -4 - adres jest kr�tszy ni� indeks ��danej etykiety.
    */
  int GetNextLabel(ExtString &NodeLabel);

   /*!
    * Udost�pnia i-t� etykiet� z danego adresu.
    * \param Idx - numer udost�pnianej etykiety (numeracja jest od 0,
    *              przy czym zerow� etykiet� jest etykieta korzenia 
    *              calej struktury - w tej chwili jest to etykieta pusta).
    *              Tak wi�c etykiety nale��ce
    *              do poszczeg�lnych obiekt�w zaczynaj� si� od nr 1.
    * \param NodeLabel - udost�pnia wynik dzia�ania metody, tzn
    *               wyekstrahowan� i-t� etykiet� z adresu
    *                   (o ile okaza�o to si� to mo�liwe).
    * \retval 0 - etykieta zosta�a wyekstrahowana. Operacja zako�czy�a si�
    *             powodzeniem,
    * \retval -1 - nie mo�na by�o wydoby� etykiety, gdy� adres jest pustym
    *             ���cuchem znakowym,
    * \retval -2 - pierwszy znak w adresie nie jest znakiem separator,
    * \retval -4 - adres jest kr�tszy ni� indeks ��danej etykiety.
    */
  int GetLabel_ith(unsigned int Idx, ExtString &NodeLabel) const;

   /*!
    *  Dokonuje ekstrakcji �cie�ki z pe�nego adresu w�z�a bez ostatniego
    *  separatora, tzn. znaku '.' . Przez �cie�k�
    *  adres bez ostatniej etykiety w�z�a. �cie�ka jest wi�c zako�czona
    *  separatorem.
    *  \param  Path - (out) zawiera wynik dzia�ania metody (o ile zako�czy�o
    *              si� ono powodzeniem).
    *  \retval  0 - operacja zako�czy�a si� powodzeniem, wyekstrahowana
    *              �cie�ka umieszczona zosta�a w \e Path,
    *  \retval -1 - gdy �a�cuch pusty,
    *  \retval -2 - adres nie rozpoczyna si� od znaku '.' .
    */
  int ExtractWithoutLast(ExtString &Path) const;

   /*!
    *  Dokonuje ekstrakcji �cie�ki z pe�nego adresu w�z�a. Przez �cie�k�
    *  adres bez ostatniej etykiety w�z�a. �cie�ka jest wi�c zako�czona
    *  separatorem.
    *  \param  Path - (out) zawiera wynik dzia�ania metody (o ile zako�czy�o
    *              si� ono powodzeniem).
    *  \retval  0 - operacja zako�czy�a si� powodzeniem, wyekstrahowana
    *              �cie�ka umieszczona zosta�a w \e Path,
    *  \retval -1 - gdy �a�cuch pusty,
    *  \retval -2 - adres nie rozpoczyna si� od znaku '.' .
    */
  int ExtractPath(ExtString &Path) const;

   /*!
    *  Ekstrahuje z pe�nego adresu ostatni� etykiet�
    *  
    * \param NodeLabel - udost�pnia wynik dzia�ania metody, tzn
    *               wyekstrahowan� ostatni� etykiet� z adresu
    *                   (o ile okaza�o to si� to mo�liwe).
    * \retval 0 - etykieta zosta�a wyekstrahowana. Operacja zako�czy�a si�
    *             powodzeniem,
    * \retval -4 - adres jest kr�tszy ni� indeks ��danej etykiety.
    */
  int ExtractLastLabel(ExtString &NodeLabel) const;

  /*!
   *  Dodaje etykiet� do adresu poprzedzaj�c j� separatorem, o ile adres
   *  nie jest ju� nim zako�czony (tzn. nie jest �cie�k�). 
   *  \param Label - etykieta dodawana do dotyczasowego adresu.
   *  \post Nowa etykieta zostaj dodana adresu towrz�c adres w�z�a
   *        o etykiecie przezkazanej przez \e Label.
   */
  int AddLabel(char const *Label);
  /*!
   *  Wyznacza d�ugo�� adresu, tzn. ilo�� etykiet co r�wnowa�ne jest
   *  g��bo�ci w strukturze drzewiastej, na kt�rej umieszczony jest
   *  w�ze� o tym adresie. D�ugo�� adresu liczona jest poprzez zliczanie
   *  separator�w + 1. Je�eli na ko�cu adresu dopisany jest separator, po
   *  kt�rym nie nast�puje etykieta w�z�a, to nie b�dzie on liczony.
   *
   * Poni�ej znajduje si� przyk�ad liczenia d�ugo�ci adresu:
   \verbatim
     Address: ""                 D�ugo�� = 0
     Address: "."                D�ugo�� = 1
     Address: ".aaa.bbb.ccc"     D�ugo�� = 4
     Address: "xxx.aaa.bbb.ccc"  D�ugo�� = 4
   \endverbatim
   *  W drugim i trzecim przyk�adzie zerowa etykieta jest pusta, niemniej stanowi
   *  r�wnie� element adresu.
   *  \return d�ugo�� adresu. 
   */
  unsigned int AddressLength() const;
  /*!
   *  Sprawdza czy adres nie jest zako�czony separatorem.
   *  \retval true - je�li jest zako�czony separatorem, tzn. znakiem '.' .
   *  \retval false - w przypadku przeciwnym.
   */
  bool IsSeparatorAtEnd() const;
  /*!
   *  Sprawdza, czy adres dost�pny poprzez parametr \e Addr jest pocz�tkiem
   *  adresu zawartego w obiekcie, dla kt�rego metoda ta zosta�a wywo�ana.
   *  \param Addr - adres, dla kt�rego realizowane jest sprawdzenie.
   *  \retval true - je�li \e Addr zawiera adres, kt�ry jest pocz�tkiem lub
   *                 jest idenyczny z adresem jaki jest zawarty w obiekcie,
   *                 dla kt�rego wywo�ano t� metod�.
   *  \retval false - w przypadku przeciwnym.
   */
  bool IsHeadOf(ViNodeAddress const &Addr) const;
  /*!
   *  Dokonuje ekstrackji pocz�tku adresu o d�ugo�ci podanej przez parametr
   *  \e Len. 
   *  \param Len - (\b in) d�ugo�� adresu od jego pocz�tku, kt�ry ma by�
   *               wyekstrahowany z adresu dotychczasowego.
   *  \param Addr - (\b out) zawiera wynik przeprowadzonej operacji, o ile
   *                operacja ta oka�e si� mo�liwa do wykonania.
   *  \retval 0 - operacja zako�czy�a si� powodzeniem, wynik dzia�ania 
   *            zosta� umieszczony w parametrze \e Addr.
   *  \retval -1 - adres jest �a�cuchem pustym. Parametrowi \e Addr zostaje
   *               przypisany �a�cuch pusty.
   *  \retval -2 - parametr \e Len ma warto�� 0. Parametrowi \e Addr zostaje
   *               przypisany �a�cuch pusty.
   *  \retval -3 - adres jest kr�tszy ni� podana d�ugo�� w parametrze 
   *               \e Len. Ca�y adres zostaje przypisany parametrowi
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
 *  Wy�wietla na wej�cie standardowe zawarto�� adresu w�z�a.
 */
inline
std::ostream &operator << (std::ostream &ostm, ViNodeAddress const &NodeAddress)
{  return ostm << NodeAddress.c_str(); }

#endif
