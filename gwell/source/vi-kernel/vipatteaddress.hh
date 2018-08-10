#ifndef VIPATTEADDRESS_HH
#define VIPATTEADDRESS_HH

/*! \file vipatteaddress.hh
 *  Plik zawiera definicj� klasy ViNodeAddress reprezentuj�c�
 *  adres bry�y wzorcowej w zbiorze bibliotek.
 *
 * \author  Bogdan Kreczmer
 * \date    2004.08
 */

#ifdef __GNUG__
#pragma interface
#endif


#include "extstring.hh"


/*!
 * Definiuje �a�cuch znak�w, kt�ry pe�ni rol� separatora
 * w adresie bry�y elementarnej.
 */
#define PA_PATTEADDRSEP  "::"

/*!
 *  Definiuje �a�cuch znak�w, kt�ry umo�liwia identyfikacj� typu 
 *  \e normalny
 *  bry�y wzorcowej. �a�cuch ten wykorzystywany jest do tworzenia
 *  pe�nej nazwy bry�y. Jest on jednocze�nie nazw� w�asn� listy
 *  przechowuj�cej bry�y danego typu.
 *  Specyfikuje ona nazw� biblioteki, z kt�rej
 *  pochodzi,
 *  typ (normalny, lub specjalny) oraz nazw� w�asn� bry�y.
 *  Pe�ne nazwy wykorzystywane s� tylko w zapisie bry�y z�o�onej
 *  do pliku (patrz 
 *  \ref  przyklad_zapisu_bryly_zlozonej "przyk�ad opisu bry�y z�o�onej",
 *  pe�n� nazwa bry�y wzorcowej wyst�puje po s�owie kluczowym 
 *  \e PatternPolyhedronName).\n
 *  Sk�adnia pe�nej nazwy by�y ma posta�:
   \verbatim
      nazwa_biblioteki::{Spec | Norm}::nazwa_w�asna
   \endverbatim
 */
#define PA_TYPE_NORM    "Norm"

/*!
 *  Definiuje �a�cuch znak�w, kt�ry umo�liwia identyfikacj� typu 
 *  \e specjalnego
 *  bry�y wzorcowej. �a�cuch ten wykorzystywany jest do tworzenia
 *  pe�nej nazwy bry�y. Jest on jednocze�nie nazw� w�asn� listy
 *  przechowuj�cej bry�y danego typu.
 *  Specyfikuje ona nazw� biblioteki, z kt�rej
 *  pochodzi,
 *  typ (normalny, lub specjalny) oraz nazw� w�asn� bry�y.
 *  Pe�ne nazwy wykorzystywane s� tylko w zapisie bry�y z�o�onej
 *  do pliku (patrz 
 *  \ref   przyklad_zapisu_bryly_zlozonej "przyk�ad opisu bry�y z�o�onej",
 *  pe�n� nazwa bry�y wzorcowej wyst�puje po s�owie kluczowym 
 *  \e PatternPolyhedronName).\n
 *  Sk�adnia pe�nej nazwy by�y ma posta�:
   \verbatim
      nazwa_biblioteki::{Spec | Norm}::nazwa_w�asna
   \endverbatim
 */
#define PA_TYPE_SPEC    "Spec"


/*!
 * Niniejsza klasa dostarcza udogodnie� w manipulowaniu pe�nym adresem
 * bry�y wzorcowej. Sam adres jest rozumiany jako ci�g znakowy zawieraj�cy
 * nazw� biblioteki, w kt�rej znajduje si� bry�a, typ bry�y oraz jej
 * nazw� w�asn�. Omawiany adres ma nast�puj�c� sk�adni�
 * \code
 *   nazwa_biblioteki::typ_bry�y::nazwa_bry�y
 * \endcode
 * gdzie \e typ_bry�y = { NORM | SPEC }.
 *
 * Przyk�ad pe�nej nazwy:
 * \code
 *   biblioteka_testowa::Norm::CYLINDER_6
 * \endcode
 */
class ViPatteAddress: public ExtString {
  public:

  /*!
   *  Inicjalizuje obiekt �a�cuchem znak�w, kt�ry powinien
   *  by� (ale nie musi) poprawn� postaci� adresu bry�y
   *  wzorcowej.
   */
  ViPatteAddress( const char *Addr ): ExtString(Addr) {}
  /*!
   *  Inicjalizuje obiekt jako pusty (bez �adnego �a�cucha znak�w).
   */
  ViPatteAddress() {}
  /*!
   *  Sprawdza czy sk�adnia adresu bry�y wzorcowej jest poprawna.
   */
  bool IsAddrOK() const;
  /*!
   *  Udost�pnia z adresu nazw� bibioteki, w kt�rej jest dana bry�a.
   *  \param LName - (\b out) po zako�czeniu dzia�ania parametr zawiera
   *                 nazw� biblioteki, w kt�rej jest dana bry�a.
   *  \retval true - je�li operacja ekstrakcji nazwy wykonana zosta�a
   *                 poprawnie.
   *  \retval false - w przypadku przeciwnym.
   */
  bool GetLibraryName( std::string &LName ) const;
  /*!
   *  Udost�pnia z adresu nazw� bibioteki, w kt�rej jest dana bry�a.
   *  \return W przypadku gdy operacja nie powiedzie si�, zwracany jest
   *          obiekty pusty (tzn metoda \e empty klasy \b string zwraci
   *          warto�� \p true). Je�eli natomiast nazwa zostanie poprawnie
   *          wyekstrahowana to zwracana jest ona jako �a�cuch znak�w.
   */
  std::string GetLibraryNameStr() const;

  /*!
   * Udost�pnia z adresu nazw� typu bry�y wzorcowej.
   * \param Type - (\b out) po zako�czeniu dzia�ania zawiera nazw� typu
   *               bry�y wzorcowej.
   *  \retval true - je�li operacja ekstrakcji nazwy wykonana zosta�a
   *                 poprawnie.
   *  \retval false - w przypadku przeciwnym.
   */
  bool GetPatteType( std::string &Type ) const;
  /*!
   *  Udost�pnia z adresu nazw� typ bry�y.
   *  \return W przypadku gdy operacja nie powiedzie si�, zwracany jest
   *          obiekty pusty (tzn metoda \e empty klasy \b string zwraci
   *          warto�� \p true). Je�eli natomiast nazwa zostanie poprawnie
   *          wyekstrahowana to zwracana jest ona jako �a�cuch znak�w.
   */
  std::string GetPatteTypeStr() const;

  /*!
   * Udost�pnia z adresu nazw� bry�y wzorcowej.
   *  \param PName - (\b out) po zako�czeniu dzia�ania zawiera nazw� 
   *               bry�y wzorcowej.
   *  \retval true - je�li operacja ekstrakcji nazwy wykonana zosta�a
   *                 poprawnie.
   *  \retval false - w przypadku przeciwnym.
   */
  bool GetPatteName( std::string &PName ) const;
  /*!
   *  Udost�pnia z adresu nazw� bry�y wzorcowej.
   *  \return W przypadku gdy operacja nie powiedzie si�, zwracany jest
   *          obiekty pusty (tzn metoda \e empty klasy \b string zwraci
   *          warto�� \p true). Je�eli natomiast nazwa zostanie poprawnie
   *          wyekstrahowana to zwracana jest ona jako �a�cuch znak�w.
   */
  std::string GetPatteNameStr() const;
   
};

#endif
