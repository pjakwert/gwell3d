#ifndef VINODEDESCR_HH
#define VINODEDESCR_HH

#ifdef __GNUG__
#pragma interface
#endif


#include <iostream>
#include <string>
#include "extstring.hh"

/*!
 * \file vinodedescr.hh
 *  Plik zawiera definicj� klasy ViNodeDescr. Obiekty tej klasy wykorzystywane
 *  s� w funkcjach i metodach odczytu z plik�w opis�w bry�.
 * \author Bogdan Kreczmer
 * \date   2004.08
 */


/*!
 * Obiekty tej klasy przeznaczone s� do przechowywania 
 * opisu pojedynczego w�z�a. Udost�pnia ona metody pozwalaj�ce
 * wydoby� z opisu informacje o dotycz�ce parametr�w inicjalizacji
 * dla poszczeg�lnych klas hierarchi dziedziczenia obiektu 
 * tworz�cego dany w�ze�.
 */
class ViNodeDescr: public ExtString {
  /*!
   * Pole ma znaczenie robocze. Jest wykorzystywane do szukania kolejnych
   * sekcji opisu inicjalizacji dla dziedziczonej klasy. 
   * Pole to wskazuje aktualne miejsce w �a�cuchu.
   */
   std::string::size_type  _SecIdx;
   
  /*!
   * Szuka pierwsz� sekcj� opisu inicjalizacji dla dziedziczonej klasy.
   */
   bool FindFirstSecBeg() const;
  /*!
   * Szuka nast�pn� sekcj� opisu inicjalizacji dla kolejnej dziedziczonej
   * klasy. Nast�pna sekcja szukana jest wzgl�dem wskazywnego miejsca
   * przez indeks \link ViNodeDescr::_SecIdx _SecIdx\endlink.
   * \warning  Je�li szukanie ma by� przeprowadzone od pocz�tku danego
   *           �a�cucha, to najpierw nale�y wywo�a� metod�
   *           \link ViNodeDescr::FindFirstSecBeg FindFirstSecBeg\endlink.
   */
   bool FindNextSecBeg() const;
  /*!
   * Szuka nast�pn� lini� ko�cz�c� dany opis inicjalizacji dla kolejnej
   * dziedziczonej
   * klasy. Nast�pna sekcja szukana jest wzgl�dem wskazywnego miejsca
   * przez indeks \link ViNodeDescr::_SecIdx _SecIdx\endlink.
   * \warning  Je�li szukanie ma by� przeprowadzone od pocz�tku danego
   *           �a�cucha, to najpierw nale�y wywo�a� metod�
   *           \link ViNodeDescr::FindFirstSecBeg FindFirstSecBeg\endlink.
   */
   bool FindNextSecEnd() const;


  /*!
   * Udost�pnia warto�� indeksu sekcji inicjalizacji dziedziczonej klasy.
   */
   std::string::size_type GetSecIdx() const { return _SecIdx; }

 public:
  /*!
   * Zwraca pozycj� pierwszego "bia�ego" znaku od nast�pnej pozycji 
   * za t�, kt�ra wskazywana jest 
   * przez pole \link ViNodeDescr::_SecIdx _SecIdx\endlink.
   * \retval true - gdy przej�cie do znaku bia�ego powiod�o si�.
   *         Polu  \link ViNodeDescr::_SecIdx _SecIdx\endlink zostaje 
   *         przypisana warto�� indeksu tego znaku.
   * \retval false - w przypadku przeciwnym. Warto�� pola 
   *           \link ViNodeDescr::_SecIdx _SecIdx\endlink nie ulega
   *           zmianie. 
   */
  bool GoToSpaceChar() const;
  /*!
   * Inicjalizuje roboczy indeks szukania sekcji opisu warto�ci� 0.
   */
  ViNodeDescr() {  _SecIdx = 0; }

  /*!
   * Podstawia dany �a�cuch jako now� warto�� obiektu.
   */
  ViNodeDescr &operator = (const char *str); 
  /*!
   *  Podaje informacje o ilo�ci opis�w poszczeg�lnych inicjalizacji
   *  klas wchodz�cych w hierarchi� dziedziczenia.
   *  obiektu tworz�cego dany w�ze�.
   */ 
   int ClassesNum() const;
  /*!
   *  Udost�pnia opis parametr�w opisu inicjalizacji danej klasy
   *  wchodz�cej w hierarchi� dziedziczenia danego obiektu.
   *  \param  Idx - (\b in) indeks danej klasy wchodz�cej hierarchi� 
   *            dziedziczenia
   *            klasy obiektu tworz�cego dany w�ze�. Numeracja rozpoczyna si�
   *            od 0 (dla klasy bazowej). Finalnej klasie pochodnej
   *            odpowiada numer 
   *           \link ViNodeDescr::ClassesNum  ClassesNum\endlink - 1.
   *
   *  \param   Desc - (\b out) zawiera wyekstrahowany opis wybranej klasy.
   *  \pre    \e Idx musi mi by� mniejszy od warto�ci zwracanej przez
   *             metod� \link ViNodeDescr::ClassesNum  ClassesNum\endlink.
   *  \retval true - gdy opis takiej klasy zosta� poprawnie udost�pniony.
   *  \retval false - gdy nie znaleziono opisu dla klasy o podanym indeksie.
   */
   bool GetClassDescr(unsigned int Idx, ExtString &Desc) const;

  /*!
   *  Udost�pnia opis parametr�w opisu inicjalizacji danej klasy
   *  wchodz�cej w hierarchi� dziedziczenia danego obiektu.
   *  \param  ClassName - (\b in) wskazuje na �a�cuch znak�w stanowi�cy
   *                nazw� klasy wchodz�cej hierarchi� dziedziczenia
   *                dla obiektu tworz�cego dany w�ze�.
   *  \param  Desc - (\b out) zawiera wyekstrahowany opis wybranej klasy.
   *  \retval true - gdy opis takiej klasy zosta� poprawnie udost�pniony.
   *  \retval false - gdy nie znaleziono opisu dla klasy o podanej nazwie.
   */
   bool GetClassDescr(const char *ClassName, ExtString &Desc) const;
 
  /*!
   * Udost�pnia nazw� wybranej klasy wchodz�cej w hierarchi� dziedziczenia
   * klasy obiektu tworz�cego dany w�ze�.
   *  \param  Idx - (\b in) indeks danej klasy wchodz�cej hierarchi� 
   *                dziedziczenia klasy obiektu tworz�cego dany w�ze�. 
   *           Numeracja rozpoczyna si�
   *           od 0 (dla klasy bazowej). Finalnej klasie pochodnej
   *           odpowiada numer 
   *          \link ViNodeDescr::ClassesNum  ClassesNum\endlink - 1.
   *  \param ClassName - (\b out) zawiera nazw� klasy o podanym indeksie
   *                    (je�eli operacja powiod�a si�). 
   *  \retval true - gdy opis takiej klasy zosta� poprawnie udost�pniony.
   *  \retval false - gdy nie znaleziono opisu dla klasy o podanej nazwie.
   *  \post Metoda nie zmienia warto�ci pola
   *        \link ViNodeDescr::ClassesNum  ClassesNum\endlink.
   */
   bool GetClassName(unsigned int Idx, ExtString &ClassName) const;
  /*!
   * Udost�pnia nazw� finalnej klasy pochodnej.
   * \param ClassName - (\b out) po poprawnym zako�czeniu dzia�ania zawiera
   *                    nazw� finalnej klasy pochodnej.
   * \retval true - je�li opis ma poprawn� sk�adni� i znaleziona zosta�a
   *                (oraz przepisana do \e ClassName) nazwa klasy.
   * \retval false - w przypadku przeciwnym.
   */
   bool GetTopClassName(ExtString &ClassName) const;
};

#endif
