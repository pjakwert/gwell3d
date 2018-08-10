#ifndef VIPATTTLIBLIST_HH
#define VIPATTTLIBLIST_HH

/*!
 * \file  vipatteliblist.hh
 * \author Bogdan Kreczmer
 * \date   2004.03.22
 *
 *  Plik zawiera definicj� klasy ViPatteLibList b�d�c� list� bibliotek
 *  obiekt�w wzorcowych.
 */


#ifdef __GNUG__
#pragma interface
#endif


#include "listque.hh"
#include "vipattepolyhlib.hh"

/*!
 *  Typ pomocniczy zdefiniowany dla umo�liwienia odwo�ywania
 *  si� do typu macierzystego poprzez skr�con� nazw�.
 *
 *  Obiekt tej klasy tworzy kolejk� bibliotek obiekt�w wzorcowych.
 */
class ViPatteLibList: public List<ViPattePolyhLib,0> {
  public:
  /*!
   *  Typ pomocniczy zdefiniowany dla umo�liwienia odwo�ywania
   *  si� do typu macierzystego poprzez skr�con� nazw�.
   *  Obiekt tej klasy umo�liwia iteracj� bibliotek obiekt�w wzorcowych
   *  dla danej sceny. Biblioteki udost�pniane s� jako obiekty sta�e.
   *  
   *  Przyklad wykorzystania:
   *  \code
   *   ViPatteLibList  LibList;
   *     . . .
   *   // Wy�wietla nazwy wszystkich bibliotek dla danej sceny.
   *  for (ViPatteLibList::ConLibIterator Iter = LibList.ConBegin();
   *         Iter; Iter++) {
   *    cout << "Biblioteka: " << Iter->GetLibName() << endl;
   *  }
   *  \endcode
   */
  typedef List<ViPattePolyhLib,0>::ConstIterator  ConLibIterator;

  /*!
   *  Typ pomocniczy zdefiniowany dla umo�liwienia odwo�ywania
   *  si� do typu macierzystego poprzez skr�con� nazw�.
   *  Obiekt tej klasy umo�liwia iteracj� bibliotek obiekt�w wzorcowych
   *  dla danej sceny. Biblioteki udost�pniane s� jako obiekty modyfikowalne.
   *  
   *  Przyklad wykorzystania:
   *  \code
   *   ViPatteLibList  LibList;
   *     . . .
   *   // Zmienia nazwy bibliotek (normalnie nie nale�y tego robi�).
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
   *  \param LibName - zawiera nazw� szukanej bibioteki.
   *  \return adres znalezionej biblioteki lub \p NULL.
   */
  const ViPattePolyhLib *FindPattePolyhLib(const char *LibName) const;


 /*!
  * Wyszukuje w zadanej bibliotece lub we wszystkich bibliotekach danej
  * sceny modelu zwyk�ej bry�y wzorcowej o podanej nazwie.
  * \param  Name - nazwa bry�y wzorcowej,
  * \param  LibName - nazaw biblioteki.
  * \post Je�eli \e LibName == \p NULL, to szukanie realizowane jest
  *       we wszystkich bibliotekach danej sceny. W przypadku przeciwnym
  *       szukanie realizowane jest tylko w bibliotece, kt�rej nazwa
  *       podana zosta�a poprzez parametr \e LibName.
  * \return
  *  wska�nik na znaleziony obiekt, \p NULL - w przypadku przeciwnym.
  * \exception ViException_Patte - zg�aszany jest w przypadku, gdy
  *      w danej scenie nie istnieje bibliotek o podanej nazwie.
  *     Wyj�tek zg�aszany jest z kodem b��du ERRNUM_PATTE__NO_SUCH_LIBRARY.
  */
  const ViPattePolyh *FindNormPattePolyh( const char *Name, 
                                          const char *LibName = 0L
                                        ) const throw(ViException_Patte);


  /*!
   * Wyszukuje w zadanej bibliotece lub we wszystkich bibliotekach danej
   * sceny modelu specjalnej bry�y wzorcowej o podanej nazwie.
   * \param  Name - nazwa bry�y wzorcowej,
   * \param  LibName - nazaw biblioteki.
   * \post Je�eli \e LibName == \p NULL, to szukanie realizowane jest
   *       we wszystkich bibliotekach danej sceny. W przypadku przeciwnym
   *       szukanie realizowane jest tylko w bibliotece, kt�rej nazwa
   *       podana zosta�a poprzez parametr \e LibName.
   * \return
   *  wska�nik na znaleziony obiekt, \p NULL - w przypadku przeciwnym.
   * \exception ViException_Patte - zg�aszany jest w przypadku, gdy
   *      w danej scenie nie istnieje bibliotek o podanej nazwie.
   *     Wyj�tek zg�aszany jest z kodem b��du ERRNUM_PATTE__NO_SUCH_LIBRARY.
   */
  const ViPattePolyh *FindSpecPattePolyh(  const char *Name,
                                                    const char *LibName
                                                 ) const
                                             throw(ViException_Patte);


  /*!
   * Wyszukuje w zadanej bibliotece lub we wszystkich bibliotekach danej
   * sceny modelu zwyk�ej bry�y wzorcowej o podanej nazwie.
   * Szukana bry�a adresowana jest pe�n� nazw� w formacie:\n
   *
   * \code
   *   nazwa_biblioteki::typ_bry�y::nazwa_bry�y
   * \endcode
   * gdzie \e typ_bry�y = { NORM | SPEC }.
   *
   * Przyk�ad pe�nej nazwy:
   * \code
   *   biblioteka_testowa::Norm::CYLINDER_6
   * \endcode
   *
   * Pierwsza cz�� adresu (tzn. \e nazwa_biblioteki) mo�e zosta� 
   * zast�piona znakiem '*'. W�wczas szukanie realizowane jest
   * we wszystkich bibliotekach danej sceny. W pozosta�ych sk�adnich
   * musz� wyst�pi� tylko nazwy. Nazwa mo�e sk�ada� si� z liter
   * znaku '_' i cyfr. Ponadto nazwa nie mo�e rozpoczyna� si�
   * cyfr�.
   * \param FullName - pe�na nazwa adresuj�ca bry��.
   * \pre Nazwa adresowa musi mie� poprawn� posta�, tzn musi zawiera�
   *      trzy podane wcze�niej sk�adniki.
   * \return wska�nik na bry�� je�li zosta�a znaleziona. W przypadku
   *         przeciwnym zwracany jest adres \p NULL.
   * \exception ViException_Patte - wyj�tek ten jest zg�aszany
   *                gdy przekazana nazwa ma niepoprawn� posta�.
   *            Wyj�tek ten zg�aszany jest z kodem
   *            \p ERRNUM_SYNTAX__BAD_PATTE_ADDR.
   * \exception ViException_Patte - zg�aszany jest w przypadku, gdy
   *  w danej scenie nie istnieje bibliotek o podanej nazwie.
   *  Wyj�tek zg�aszany jest z kodem b��du ERRNUM_PATTE__NO_SUCH_LIBRARY.
   */
  const ViPattePolyh *FindPattePolyh( const char *FullName ) const
             throw (ViException_Patte);

};



#endif
