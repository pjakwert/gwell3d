#ifndef VIPATTTLIBLIST_HH
#define VIPATTTLIBLIST_HH

/*!
 * \file  vipatteliblist.hh
 * \author Bogdan Kreczmer
 * \date   2004.03.22
 *
 *  Plik zawiera definicjê klasy ViPatteLibList bêd±c± list± bibliotek
 *  obiektów wzorcowych.
 */


#ifdef __GNUG__
#pragma interface
#endif


#include "listque.hh"
#include "vipattepolyhlib.hh"

/*!
 *  Typ pomocniczy zdefiniowany dla umo¿liwienia odwo³ywania
 *  siê do typu macierzystego poprzez skrócon± nazwê.
 *
 *  Obiekt tej klasy tworzy kolejkê bibliotek obiektów wzorcowych.
 */
class ViPatteLibList: public List<ViPattePolyhLib,0> {
  public:
  /*!
   *  Typ pomocniczy zdefiniowany dla umo¿liwienia odwo³ywania
   *  siê do typu macierzystego poprzez skrócon± nazwê.
   *  Obiekt tej klasy umo¿liwia iteracjê bibliotek obiektów wzorcowych
   *  dla danej sceny. Biblioteki udostêpniane s± jako obiekty sta³e.
   *  
   *  Przyklad wykorzystania:
   *  \code
   *   ViPatteLibList  LibList;
   *     . . .
   *   // Wy¶wietla nazwy wszystkich bibliotek dla danej sceny.
   *  for (ViPatteLibList::ConLibIterator Iter = LibList.ConBegin();
   *         Iter; Iter++) {
   *    cout << "Biblioteka: " << Iter->GetLibName() << endl;
   *  }
   *  \endcode
   */
  typedef List<ViPattePolyhLib,0>::ConstIterator  ConLibIterator;

  /*!
   *  Typ pomocniczy zdefiniowany dla umo¿liwienia odwo³ywania
   *  siê do typu macierzystego poprzez skrócon± nazwê.
   *  Obiekt tej klasy umo¿liwia iteracjê bibliotek obiektów wzorcowych
   *  dla danej sceny. Biblioteki udostêpniane s± jako obiekty modyfikowalne.
   *  
   *  Przyklad wykorzystania:
   *  \code
   *   ViPatteLibList  LibList;
   *     . . .
   *   // Zmienia nazwy bibliotek (normalnie nie nale¿y tego robiæ).
   *  int i=0;
   *  for (ViPatteLibList::VarLibIterator Iter = LibList.Begin();
   *       Iter; Iter++) {
   *    ExtString  Nazwa("bib");
   *    Nazwa << i++;
   *    Iter->SetLibName(Nazwa);
   *  }
   *  \endcode
   */
  typedef List<ViPattePolyhLib,0>::VariaIterator  VarLibIterator;


  /*!
   *  Szuka biblioteki o zadanej nazwie.
   *  \param LibName - zawiera nazwê szukanej bibioteki.
   *  \return adres znalezionej biblioteki lub \p NULL.
   */
  const ViPattePolyhLib *FindPattePolyhLib(const char *LibName) const;


 /*!
  * Wyszukuje w zadanej bibliotece lub we wszystkich bibliotekach danej
  * sceny modelu zwyk³ej bry³y wzorcowej o podanej nazwie.
  * \param  Name - nazwa bry³y wzorcowej,
  * \param  LibName - nazaw biblioteki.
  * \post Je¿eli \e LibName == \p NULL, to szukanie realizowane jest
  *       we wszystkich bibliotekach danej sceny. W przypadku przeciwnym
  *       szukanie realizowane jest tylko w bibliotece, której nazwa
  *       podana zosta³a poprzez parametr \e LibName.
  * \return
  *  wska¼nik na znaleziony obiekt, \p NULL - w przypadku przeciwnym.
  * \exception ViException_Patte - zg³aszany jest w przypadku, gdy
  *      w danej scenie nie istnieje bibliotek o podanej nazwie.
  *     Wyj±tek zg³aszany jest z kodem b³êdu ERRNUM_PATTE__NO_SUCH_LIBRARY.
  */
  const ViPattePolyh *FindNormPattePolyh( const char *Name, 
                                          const char *LibName = 0L
                                        ) const throw(ViException_Patte);


  /*!
   * Wyszukuje w zadanej bibliotece lub we wszystkich bibliotekach danej
   * sceny modelu specjalnej bry³y wzorcowej o podanej nazwie.
   * \param  Name - nazwa bry³y wzorcowej,
   * \param  LibName - nazaw biblioteki.
   * \post Je¿eli \e LibName == \p NULL, to szukanie realizowane jest
   *       we wszystkich bibliotekach danej sceny. W przypadku przeciwnym
   *       szukanie realizowane jest tylko w bibliotece, której nazwa
   *       podana zosta³a poprzez parametr \e LibName.
   * \return
   *  wska¼nik na znaleziony obiekt, \p NULL - w przypadku przeciwnym.
   * \exception ViException_Patte - zg³aszany jest w przypadku, gdy
   *      w danej scenie nie istnieje bibliotek o podanej nazwie.
   *     Wyj±tek zg³aszany jest z kodem b³êdu ERRNUM_PATTE__NO_SUCH_LIBRARY.
   */
  const ViPattePolyh *FindSpecPattePolyh(  const char *Name,
                                                    const char *LibName
                                                 ) const
                                             throw(ViException_Patte);


  /*!
   * Wyszukuje w zadanej bibliotece lub we wszystkich bibliotekach danej
   * sceny modelu zwyk³ej bry³y wzorcowej o podanej nazwie.
   * Szukana bry³a adresowana jest pe³n± nazw± w formacie:\n
   *
   * \code
   *   nazwa_biblioteki::typ_bry³y::nazwa_bry³y
   * \endcode
   * gdzie \e typ_bry³y = { NORM | SPEC }.
   *
   * Przyk³ad pe³nej nazwy:
   * \code
   *   biblioteka_testowa::Norm::CYLINDER_6
   * \endcode
   *
   * Pierwsza czê¶æ adresu (tzn. \e nazwa_biblioteki) mo¿e zostaæ 
   * zast±piona znakiem '*'. Wówczas szukanie realizowane jest
   * we wszystkich bibliotekach danej sceny. W pozosta³ych sk³adnich
   * musz± wyst±piæ tylko nazwy. Nazwa mo¿e sk³adaæ siê z liter
   * znaku '_' i cyfr. Ponadto nazwa nie mo¿e rozpoczynaæ siê
   * cyfr±.
   * \param FullName - pe³na nazwa adresuj±ca bry³ê.
   * \pre Nazwa adresowa musi mieæ poprawn± postaæ, tzn musi zawieraæ
   *      trzy podane wcze¶niej sk³adniki.
   * \return wska¼nik na bry³ê je¶li zosta³a znaleziona. W przypadku
   *         przeciwnym zwracany jest adres \p NULL.
   * \exception ViException_Patte - wyj±tek ten jest zg³aszany
   *                gdy przekazana nazwa ma niepoprawn± postaæ.
   *            Wyj±tek ten zg³aszany jest z kodem
   *            \p ERRNUM_SYNTAX__BAD_PATTE_ADDR.
   * \exception ViException_Patte - zg³aszany jest w przypadku, gdy
   *  w danej scenie nie istnieje bibliotek o podanej nazwie.
   *  Wyj±tek zg³aszany jest z kodem b³êdu ERRNUM_PATTE__NO_SUCH_LIBRARY.
   */
  const ViPattePolyh *FindPattePolyh( const char *FullName ) const
             throw (ViException_Patte);

};



#endif
