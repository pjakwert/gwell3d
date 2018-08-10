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
 *  Plik zawiera definicjê klasy ViNodeDescr. Obiekty tej klasy wykorzystywane
 *  s± w funkcjach i metodach odczytu z plików opisów bry³.
 * \author Bogdan Kreczmer
 * \date   2004.08
 */


/*!
 * Obiekty tej klasy przeznaczone s± do przechowywania 
 * opisu pojedynczego wêz³a. Udostêpnia ona metody pozwalaj±ce
 * wydobyæ z opisu informacje o dotycz±ce parametrów inicjalizacji
 * dla poszczególnych klas hierarchi dziedziczenia obiektu 
 * tworz±cego dany wêze³.
 */
class ViNodeDescr: public ExtString {
  /*!
   * Pole ma znaczenie robocze. Jest wykorzystywane do szukania kolejnych
   * sekcji opisu inicjalizacji dla dziedziczonej klasy. 
   * Pole to wskazuje aktualne miejsce w ³añcuchu.
   */
   std::string::size_type  _SecIdx;
   
  /*!
   * Szuka pierwsz± sekcjê opisu inicjalizacji dla dziedziczonej klasy.
   */
   bool FindFirstSecBeg() const;
  /*!
   * Szuka nastêpn± sekcjê opisu inicjalizacji dla kolejnej dziedziczonej
   * klasy. Nastêpna sekcja szukana jest wzglêdem wskazywnego miejsca
   * przez indeks \link ViNodeDescr::_SecIdx _SecIdx\endlink.
   * \warning  Je¶li szukanie ma byæ przeprowadzone od pocz±tku danego
   *           ³añcucha, to najpierw nale¿y wywo³aæ metodê
   *           \link ViNodeDescr::FindFirstSecBeg FindFirstSecBeg\endlink.
   */
   bool FindNextSecBeg() const;
  /*!
   * Szuka nastêpn± liniê koñcz±c± dany opis inicjalizacji dla kolejnej
   * dziedziczonej
   * klasy. Nastêpna sekcja szukana jest wzglêdem wskazywnego miejsca
   * przez indeks \link ViNodeDescr::_SecIdx _SecIdx\endlink.
   * \warning  Je¶li szukanie ma byæ przeprowadzone od pocz±tku danego
   *           ³añcucha, to najpierw nale¿y wywo³aæ metodê
   *           \link ViNodeDescr::FindFirstSecBeg FindFirstSecBeg\endlink.
   */
   bool FindNextSecEnd() const;


  /*!
   * Udostêpnia warto¶æ indeksu sekcji inicjalizacji dziedziczonej klasy.
   */
   std::string::size_type GetSecIdx() const { return _SecIdx; }

 public:
  /*!
   * Zwraca pozycjê pierwszego "bia³ego" znaku od nastêpnej pozycji 
   * za t±, która wskazywana jest 
   * przez pole \link ViNodeDescr::_SecIdx _SecIdx\endlink.
   * \retval true - gdy przej¶cie do znaku bia³ego powiod³o siê.
   *         Polu  \link ViNodeDescr::_SecIdx _SecIdx\endlink zostaje 
   *         przypisana warto¶æ indeksu tego znaku.
   * \retval false - w przypadku przeciwnym. Warto¶æ pola 
   *           \link ViNodeDescr::_SecIdx _SecIdx\endlink nie ulega
   *           zmianie. 
   */
  bool GoToSpaceChar() const;
  /*!
   * Inicjalizuje roboczy indeks szukania sekcji opisu warto¶ci± 0.
   */
  ViNodeDescr() {  _SecIdx = 0; }

  /*!
   * Podstawia dany ³añcuch jako now± warto¶æ obiektu.
   */
  ViNodeDescr &operator = (const char *str); 
  /*!
   *  Podaje informacje o ilo¶ci opisów poszczególnych inicjalizacji
   *  klas wchodz±cych w hierarchiê dziedziczenia.
   *  obiektu tworz±cego dany wêze³.
   */ 
   int ClassesNum() const;
  /*!
   *  Udostêpnia opis parametrów opisu inicjalizacji danej klasy
   *  wchodz±cej w hierarchiê dziedziczenia danego obiektu.
   *  \param  Idx - (\b in) indeks danej klasy wchodz±cej hierarchiê 
   *            dziedziczenia
   *            klasy obiektu tworz±cego dany wêze³. Numeracja rozpoczyna siê
   *            od 0 (dla klasy bazowej). Finalnej klasie pochodnej
   *            odpowiada numer 
   *           \link ViNodeDescr::ClassesNum  ClassesNum\endlink - 1.
   *
   *  \param   Desc - (\b out) zawiera wyekstrahowany opis wybranej klasy.
   *  \pre    \e Idx musi mi byæ mniejszy od warto¶ci zwracanej przez
   *             metodê \link ViNodeDescr::ClassesNum  ClassesNum\endlink.
   *  \retval true - gdy opis takiej klasy zosta³ poprawnie udostêpniony.
   *  \retval false - gdy nie znaleziono opisu dla klasy o podanym indeksie.
   */
   bool GetClassDescr(unsigned int Idx, ExtString &Desc) const;

  /*!
   *  Udostêpnia opis parametrów opisu inicjalizacji danej klasy
   *  wchodz±cej w hierarchiê dziedziczenia danego obiektu.
   *  \param  ClassName - (\b in) wskazuje na ³añcuch znaków stanowi±cy
   *                nazwê klasy wchodz±cej hierarchiê dziedziczenia
   *                dla obiektu tworz±cego dany wêze³.
   *  \param  Desc - (\b out) zawiera wyekstrahowany opis wybranej klasy.
   *  \retval true - gdy opis takiej klasy zosta³ poprawnie udostêpniony.
   *  \retval false - gdy nie znaleziono opisu dla klasy o podanej nazwie.
   */
   bool GetClassDescr(const char *ClassName, ExtString &Desc) const;
 
  /*!
   * Udostêpnia nazwê wybranej klasy wchodz±cej w hierarchiê dziedziczenia
   * klasy obiektu tworz±cego dany wêze³.
   *  \param  Idx - (\b in) indeks danej klasy wchodz±cej hierarchiê 
   *                dziedziczenia klasy obiektu tworz±cego dany wêze³. 
   *           Numeracja rozpoczyna siê
   *           od 0 (dla klasy bazowej). Finalnej klasie pochodnej
   *           odpowiada numer 
   *          \link ViNodeDescr::ClassesNum  ClassesNum\endlink - 1.
   *  \param ClassName - (\b out) zawiera nazwê klasy o podanym indeksie
   *                    (je¿eli operacja powiod³a siê). 
   *  \retval true - gdy opis takiej klasy zosta³ poprawnie udostêpniony.
   *  \retval false - gdy nie znaleziono opisu dla klasy o podanej nazwie.
   *  \post Metoda nie zmienia warto¶ci pola
   *        \link ViNodeDescr::ClassesNum  ClassesNum\endlink.
   */
   bool GetClassName(unsigned int Idx, ExtString &ClassName) const;
  /*!
   * Udostêpnia nazwê finalnej klasy pochodnej.
   * \param ClassName - (\b out) po poprawnym zakoñczeniu dzia³ania zawiera
   *                    nazwê finalnej klasy pochodnej.
   * \retval true - je¶li opis ma poprawn± sk³adniê i znaleziona zosta³a
   *                (oraz przepisana do \e ClassName) nazwa klasy.
   * \retval false - w przypadku przeciwnym.
   */
   bool GetTopClassName(ExtString &ClassName) const;
};

#endif
