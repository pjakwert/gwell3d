#ifndef STRPRINTF_HH
#define STRPRINTF_HH

/*!
 * \file strprintf.hh
 * \author Bogdan Kreczmer
 * \date  2004.03.24
 *
 *  Plik zawiera definicj� klasy StrPrintf.
 */

#ifdef __GNUG__
#pragma interface
#endif


#include <string>

/*!
 *  Klasa ta pe�ni rol� pomocnicz� w procesie budowy komunikat�w 
 *  o b��dach. Jest ona r�wnie� przejawem t�sknoty autora za metod�
 *  printf dla klasy string i formatowaniu wydruku zgodnie z "C" :(
 */
class StrPrintf: public std::string {

 public:
  /*!
   *  Inicjalizacja obiektu jako �a�cucha pustego.
   */
  StrPrintf() {}
  /*!
   *  Inicjalizacja obiektu z pocz�tkow� zawarto�ci�.
   */ 
  StrPrintf(const char *Msg): std::string(Msg) {}
  /*!
   * W aktualnym �a�cuchu szuka sekwencji %i i po jej znalezieniu
   * wstawia w to miejsce warto�� liczbow� podan� jako argument.
   * Operacja jest wykonywana tylko dla pierwszej znalezionej sekwecji
   * formatuj�cej. Je�li nie zostanie ona znaleziona, to nie ���cuch
   * nie ulega zmianie.
   * \param Arg - warto�� liczbowa, kt�ra ma by� wstawiona do �a�cucha.
   * \return referencj� do samego siebie (\e *this).
   */
  StrPrintf & operator << (int Arg);

  /*!
   * W aktualnym �a�cuchu szuka sekwencji %u i po jej znalezieniu
   * wstawia w to miejsce warto�� liczbow� podan� jako argument.
   * Operacja jest wykonywana tylko dla pierwszej znalezionej sekwecji
   * formatuj�cej. Je�li nie zostanie ona znaleziona, to nie ���cuch
   * nie ulega zmianie.
   * \param Arg - warto�� liczbowa, kt�ra ma by� wstawiona do �a�cucha.
   * \return referencj� do samego siebie (\e *this).
   */
  StrPrintf & operator << (unsigned int Arg);  

  /*!
   * W aktualnym �a�cuchu szuka sekwencji %s i po jej znalezieniu
   * wstawia w to miejsce ���cuch znak�w podany jako argument.
   * Operacja jest wykonywana tylko dla pierwszej znalezionej sekwecji
   * formatuj�cej. Je�li nie zostanie ona znaleziona, to nie ���cuch
   * nie ulega zmianie.
   * \param Str - �a�cuch znak�w, kt�ra ma by� wstawiona do �a�cucha.
   * \return referencj� do samego siebie (\e *this).
   */
  StrPrintf & operator << (const char* Str);

  /*!
   * W aktualnym �a�cuchu szuka sekwencji %c i po jej znalezieniu
   * wstawia w to miejsce znak podany jako argument.
   * Operacja jest wykonywana tylko dla pierwszej znalezionej sekwecji
   * formatuj�cej. Je�li nie zostanie ona znaleziona, to nie ���cuch
   * nie ulega zmianie.
   * \param Ch - znak, kt�ra ma by� wstawiona do �a�cucha.
   * \return referencj� do samego siebie (\e *this).
   */
  StrPrintf & operator << (char Ch);

  /*!
   * W aktualnym �a�cuchu szuka sekwencji %f i po jej znalezieniu
   * wstawia w to miejsce warto�� liczbow� podan� jako argument.
   * Operacja jest wykonywana tylko dla pierwszej znalezionej sekwecji
   * formatuj�cej. Je�li nie zostanie ona znaleziona, to nie ���cuch
   * nie ulega zmianie.
   * \param Arg - warto�� liczbowa, kt�ra ma by� wstawiona do �a�cucha.
   * \return referencj� do samego siebie (\e *this).
   */
  StrPrintf & operator << (float Arg);

  /*!
   * W aktualnym �a�cuchu szuka sekwencji %g i po jej znalezieniu
   * wstawia w to miejsce warto�� liczbow� podan� jako argument.
   * Operacja jest wykonywana tylko dla pierwszej znalezionej sekwecji
   * formatuj�cej. Je�li nie zostanie ona znaleziona, to nie ���cuch
   * nie ulega zmianie.
   * \param Arg - warto�� liczbowa, kt�ra ma by� wstawiona do �a�cucha.
   * \return referencj� do samego siebie (\e *this).
   */
  StrPrintf & operator << (double Arg);

  /*!
   * Przeci��enie tego operatora jest realizuje identyczn� operacj� jak
   * przeci��enie operatora 
   * << dla \e int.
   */
  StrPrintf & operator , (int Arg) { return *this << Arg; }
  /*!
   * Przeci��enie tego operatora jest realizuje identyczn� operacj� jak
   * przeci��enie operatora 
   * << dla \e unsigned \e int.
   */
  StrPrintf & operator , (unsigned int Arg) { return *this << Arg; }
  /*!
   * Przeci��enie tego operatora jest realizuje identyczn� operacj� jak
   * przeci��enie operatora 
   * << dla \e char.
   */
  StrPrintf & operator , (char Arg) { return *this << Arg; }

  /*!
   * Przeci��enie tego operatora jest realizuje identyczn� operacj� jak
   * przeci��enie operatora 
   * << dla \e char.
   */
  StrPrintf & operator , (unsigned char Arg) { return *this << (char)Arg; }

  /*!
   * Przeci��enie tego operatora jest realizuje identyczn� operacj� jak
   * przeci��enie operatora 
   * << dla \e const \e char*.
   */
  StrPrintf & operator , (const char *Arg) { return *this << Arg; }
  /*!
   * Przeci��enie tego operatora jest realizuje identyczn� operacj� jak
   * przeci��enie operatora 
   * << dla \e float.
   */
  StrPrintf & operator , (float Arg) { return *this << Arg; }
  /*!
   * Przeci��enie tego operatora jest realizuje identyczn� operacj� jak
   * przeci��enie operatora 
   * << dla \e double.
   */
  StrPrintf & operator , (double Arg) { return *this << Arg; }

  /*!
   * Zapewnia domy�ln� konwersj� do �a�cucha znak�w w sensie j�zyka C.
   */
  operator const char* () { return c_str(); }
};

#endif
