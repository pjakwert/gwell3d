#ifndef VIPATTEADDRESS_HH
#define VIPATTEADDRESS_HH

/*! \file vipatteaddress.hh
 *  Plik zawiera definicjê klasy ViNodeAddress reprezentuj±c±
 *  adres bry³y wzorcowej w zbiorze bibliotek.
 *
 * \author  Bogdan Kreczmer
 * \date    2004.08
 */

#ifdef __GNUG__
#pragma interface
#endif


#include "extstring.hh"


/*!
 * Definiuje ³añcuch znaków, który pe³ni rolê separatora
 * w adresie bry³y elementarnej.
 */
#define PA_PATTEADDRSEP  "::"

/*!
 *  Definiuje ³añcuch znaków, który umo¿liwia identyfikacjê typu 
 *  \e normalny
 *  bry³y wzorcowej. £añcuch ten wykorzystywany jest do tworzenia
 *  pe³nej nazwy bry³y. Jest on jednocze¶nie nazw± w³asn± listy
 *  przechowuj±cej bry³y danego typu.
 *  Specyfikuje ona nazwê biblioteki, z której
 *  pochodzi,
 *  typ (normalny, lub specjalny) oraz nazwê w³asn± bry³y.
 *  Pe³ne nazwy wykorzystywane s± tylko w zapisie bry³y z³o¿onej
 *  do pliku (patrz 
 *  \ref  przyklad_zapisu_bryly_zlozonej "przyk³ad opisu bry³y z³o¿onej",
 *  pe³n± nazwa bry³y wzorcowej wystêpuje po s³owie kluczowym 
 *  \e PatternPolyhedronName).\n
 *  Sk³adnia pe³nej nazwy by³y ma postaæ:
   \verbatim
      nazwa_biblioteki::{Spec | Norm}::nazwa_w³asna
   \endverbatim
 */
#define PA_TYPE_NORM    "Norm"

/*!
 *  Definiuje ³añcuch znaków, który umo¿liwia identyfikacjê typu 
 *  \e specjalnego
 *  bry³y wzorcowej. £añcuch ten wykorzystywany jest do tworzenia
 *  pe³nej nazwy bry³y. Jest on jednocze¶nie nazw± w³asn± listy
 *  przechowuj±cej bry³y danego typu.
 *  Specyfikuje ona nazwê biblioteki, z której
 *  pochodzi,
 *  typ (normalny, lub specjalny) oraz nazwê w³asn± bry³y.
 *  Pe³ne nazwy wykorzystywane s± tylko w zapisie bry³y z³o¿onej
 *  do pliku (patrz 
 *  \ref   przyklad_zapisu_bryly_zlozonej "przyk³ad opisu bry³y z³o¿onej",
 *  pe³n± nazwa bry³y wzorcowej wystêpuje po s³owie kluczowym 
 *  \e PatternPolyhedronName).\n
 *  Sk³adnia pe³nej nazwy by³y ma postaæ:
   \verbatim
      nazwa_biblioteki::{Spec | Norm}::nazwa_w³asna
   \endverbatim
 */
#define PA_TYPE_SPEC    "Spec"


/*!
 * Niniejsza klasa dostarcza udogodnieñ w manipulowaniu pe³nym adresem
 * bry³y wzorcowej. Sam adres jest rozumiany jako ci±g znakowy zawieraj±cy
 * nazwê biblioteki, w której znajduje siê bry³a, typ bry³y oraz jej
 * nazwê w³asn±. Omawiany adres ma nastêpuj±c± sk³adniê
 * \code
 *   nazwa_biblioteki::typ_bry³y::nazwa_bry³y
 * \endcode
 * gdzie \e typ_bry³y = { NORM | SPEC }.
 *
 * Przyk³ad pe³nej nazwy:
 * \code
 *   biblioteka_testowa::Norm::CYLINDER_6
 * \endcode
 */
class ViPatteAddress: public ExtString {
  public:

  /*!
   *  Inicjalizuje obiekt ³añcuchem znaków, który powinien
   *  byæ (ale nie musi) poprawn± postaci± adresu bry³y
   *  wzorcowej.
   */
  ViPatteAddress( const char *Addr ): ExtString(Addr) {}
  /*!
   *  Inicjalizuje obiekt jako pusty (bez ¿adnego ³añcucha znaków).
   */
  ViPatteAddress() {}
  /*!
   *  Sprawdza czy sk³adnia adresu bry³y wzorcowej jest poprawna.
   */
  bool IsAddrOK() const;
  /*!
   *  Udostêpnia z adresu nazwê bibioteki, w której jest dana bry³a.
   *  \param LName - (\b out) po zakoñczeniu dzia³ania parametr zawiera
   *                 nazwê biblioteki, w której jest dana bry³a.
   *  \retval true - je¶li operacja ekstrakcji nazwy wykonana zosta³a
   *                 poprawnie.
   *  \retval false - w przypadku przeciwnym.
   */
  bool GetLibraryName( std::string &LName ) const;
  /*!
   *  Udostêpnia z adresu nazwê bibioteki, w której jest dana bry³a.
   *  \return W przypadku gdy operacja nie powiedzie siê, zwracany jest
   *          obiekty pusty (tzn metoda \e empty klasy \b string zwraci
   *          warto¶æ \p true). Je¿eli natomiast nazwa zostanie poprawnie
   *          wyekstrahowana to zwracana jest ona jako ³añcuch znaków.
   */
  std::string GetLibraryNameStr() const;

  /*!
   * Udostêpnia z adresu nazwê typu bry³y wzorcowej.
   * \param Type - (\b out) po zakoñczeniu dzia³ania zawiera nazwê typu
   *               bry³y wzorcowej.
   *  \retval true - je¶li operacja ekstrakcji nazwy wykonana zosta³a
   *                 poprawnie.
   *  \retval false - w przypadku przeciwnym.
   */
  bool GetPatteType( std::string &Type ) const;
  /*!
   *  Udostêpnia z adresu nazwê typ bry³y.
   *  \return W przypadku gdy operacja nie powiedzie siê, zwracany jest
   *          obiekty pusty (tzn metoda \e empty klasy \b string zwraci
   *          warto¶æ \p true). Je¿eli natomiast nazwa zostanie poprawnie
   *          wyekstrahowana to zwracana jest ona jako ³añcuch znaków.
   */
  std::string GetPatteTypeStr() const;

  /*!
   * Udostêpnia z adresu nazwê bry³y wzorcowej.
   *  \param PName - (\b out) po zakoñczeniu dzia³ania zawiera nazwê 
   *               bry³y wzorcowej.
   *  \retval true - je¶li operacja ekstrakcji nazwy wykonana zosta³a
   *                 poprawnie.
   *  \retval false - w przypadku przeciwnym.
   */
  bool GetPatteName( std::string &PName ) const;
  /*!
   *  Udostêpnia z adresu nazwê bry³y wzorcowej.
   *  \return W przypadku gdy operacja nie powiedzie siê, zwracany jest
   *          obiekty pusty (tzn metoda \e empty klasy \b string zwraci
   *          warto¶æ \p true). Je¿eli natomiast nazwa zostanie poprawnie
   *          wyekstrahowana to zwracana jest ona jako ³añcuch znaków.
   */
  std::string GetPatteNameStr() const;
   
};

#endif
