#ifndef STRPRINTF_HH
#define STRPRINTF_HH

/*!
 * \file strprintf.hh
 * \author Bogdan Kreczmer
 * \date  2004.03.24
 *
 *  Plik zawiera definicjê klasy StrPrintf.
 */

#ifdef __GNUG__
#pragma interface
#endif


#include <string>

/*!
 *  Klasa ta pe³ni rolê pomocnicz± w procesie budowy komunikatów 
 *  o b³êdach. Jest ona równie¿ przejawem têsknoty autora za metod±
 *  printf dla klasy string i formatowaniu wydruku zgodnie z "C" :(
 */
class StrPrintf: public std::string {

 public:
  /*!
   *  Inicjalizacja obiektu jako ³añcucha pustego.
   */
  StrPrintf() {}
  /*!
   *  Inicjalizacja obiektu z pocz±tkow± zawarto¶ci±.
   */ 
  StrPrintf(const char *Msg): std::string(Msg) {}
  /*!
   * W aktualnym ³añcuchu szuka sekwencji %i i po jej znalezieniu
   * wstawia w to miejsce warto¶æ liczbow± podan± jako argument.
   * Operacja jest wykonywana tylko dla pierwszej znalezionej sekwecji
   * formatuj±cej. Je¶li nie zostanie ona znaleziona, to nie ³±ñcuch
   * nie ulega zmianie.
   * \param Arg - warto¶æ liczbowa, która ma byæ wstawiona do ³añcucha.
   * \return referencjê do samego siebie (\e *this).
   */
  StrPrintf & operator << (int Arg);

  /*!
   * W aktualnym ³añcuchu szuka sekwencji %u i po jej znalezieniu
   * wstawia w to miejsce warto¶æ liczbow± podan± jako argument.
   * Operacja jest wykonywana tylko dla pierwszej znalezionej sekwecji
   * formatuj±cej. Je¶li nie zostanie ona znaleziona, to nie ³±ñcuch
   * nie ulega zmianie.
   * \param Arg - warto¶æ liczbowa, która ma byæ wstawiona do ³añcucha.
   * \return referencjê do samego siebie (\e *this).
   */
  StrPrintf & operator << (unsigned int Arg);  

  /*!
   * W aktualnym ³añcuchu szuka sekwencji %s i po jej znalezieniu
   * wstawia w to miejsce ³±ñcuch znaków podany jako argument.
   * Operacja jest wykonywana tylko dla pierwszej znalezionej sekwecji
   * formatuj±cej. Je¶li nie zostanie ona znaleziona, to nie ³±ñcuch
   * nie ulega zmianie.
   * \param Str - ³añcuch znaków, która ma byæ wstawiona do ³añcucha.
   * \return referencjê do samego siebie (\e *this).
   */
  StrPrintf & operator << (const char* Str);

  /*!
   * W aktualnym ³añcuchu szuka sekwencji %c i po jej znalezieniu
   * wstawia w to miejsce znak podany jako argument.
   * Operacja jest wykonywana tylko dla pierwszej znalezionej sekwecji
   * formatuj±cej. Je¶li nie zostanie ona znaleziona, to nie ³±ñcuch
   * nie ulega zmianie.
   * \param Ch - znak, która ma byæ wstawiona do ³añcucha.
   * \return referencjê do samego siebie (\e *this).
   */
  StrPrintf & operator << (char Ch);

  /*!
   * W aktualnym ³añcuchu szuka sekwencji %f i po jej znalezieniu
   * wstawia w to miejsce warto¶æ liczbow± podan± jako argument.
   * Operacja jest wykonywana tylko dla pierwszej znalezionej sekwecji
   * formatuj±cej. Je¶li nie zostanie ona znaleziona, to nie ³±ñcuch
   * nie ulega zmianie.
   * \param Arg - warto¶æ liczbowa, która ma byæ wstawiona do ³añcucha.
   * \return referencjê do samego siebie (\e *this).
   */
  StrPrintf & operator << (float Arg);

  /*!
   * W aktualnym ³añcuchu szuka sekwencji %g i po jej znalezieniu
   * wstawia w to miejsce warto¶æ liczbow± podan± jako argument.
   * Operacja jest wykonywana tylko dla pierwszej znalezionej sekwecji
   * formatuj±cej. Je¶li nie zostanie ona znaleziona, to nie ³±ñcuch
   * nie ulega zmianie.
   * \param Arg - warto¶æ liczbowa, która ma byæ wstawiona do ³añcucha.
   * \return referencjê do samego siebie (\e *this).
   */
  StrPrintf & operator << (double Arg);

  /*!
   * Przeci±¿enie tego operatora jest realizuje identyczn± operacjê jak
   * przeci±¿enie operatora 
   * << dla \e int.
   */
  StrPrintf & operator , (int Arg) { return *this << Arg; }
  /*!
   * Przeci±¿enie tego operatora jest realizuje identyczn± operacjê jak
   * przeci±¿enie operatora 
   * << dla \e unsigned \e int.
   */
  StrPrintf & operator , (unsigned int Arg) { return *this << Arg; }
  /*!
   * Przeci±¿enie tego operatora jest realizuje identyczn± operacjê jak
   * przeci±¿enie operatora 
   * << dla \e char.
   */
  StrPrintf & operator , (char Arg) { return *this << Arg; }

  /*!
   * Przeci±¿enie tego operatora jest realizuje identyczn± operacjê jak
   * przeci±¿enie operatora 
   * << dla \e char.
   */
  StrPrintf & operator , (unsigned char Arg) { return *this << (char)Arg; }

  /*!
   * Przeci±¿enie tego operatora jest realizuje identyczn± operacjê jak
   * przeci±¿enie operatora 
   * << dla \e const \e char*.
   */
  StrPrintf & operator , (const char *Arg) { return *this << Arg; }
  /*!
   * Przeci±¿enie tego operatora jest realizuje identyczn± operacjê jak
   * przeci±¿enie operatora 
   * << dla \e float.
   */
  StrPrintf & operator , (float Arg) { return *this << Arg; }
  /*!
   * Przeci±¿enie tego operatora jest realizuje identyczn± operacjê jak
   * przeci±¿enie operatora 
   * << dla \e double.
   */
  StrPrintf & operator , (double Arg) { return *this << Arg; }

  /*!
   * Zapewnia domy¶ln± konwersjê do ³añcucha znaków w sensie jêzyka C.
   */
  operator const char* () { return c_str(); }
};

#endif
