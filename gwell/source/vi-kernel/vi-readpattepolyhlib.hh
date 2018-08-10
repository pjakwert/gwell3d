#ifndef VI_READPATTPOLYH_HH
#define VI_READPATTPOLYH_HH
/*!
 * \file  vi-readpattepolyhlib.hh
 * Plik zawiera nag��wek funkcji realizuj�cej odczyt wielo�cian�w wzorcowych.
 * \author	Bogdan Kreczmer
 * \date	Maj 1995
 */


#ifdef __GNUG__
#pragma interface
#endif

class ViPattePolyhLib;
class ExtString;

/*!
 * Funkcji realizuj�cej odczyt wielo�cian�w wzorcowych.
 * \param  PPolyhSet - wska�nik na obiekt, w kt�ry pe�ni rol�
 *                   zarz�dcy kolejki bry� wzorcowych.
 * \param  FileName  - nazwa pliku, w kt�rym znajduje si� biblioteka
 *                   obiekt�w wzorcowych,
 * \param  ErrMsg - w przpadku wyst�pienia b��du odczytu w obiekcie
 *                  tym zostanie umieszczony komunkat b��du.
 * \retval  0 - je�li odczyt przebieg� poprawnie,
 * \retval  <0 - w przypadku przeciwnym.
 * \post
 *   Je�li odczy przebieg� poprawnie, to \e pPPolyhSet to zawiera
 *   kolejk� obiekt�w wzorcowych. W przypadku przeciwnym w \e ErrMsg
 *   umieszczany jest komunikat o b�edzie sk�adni o ile b�ad zosta�
 *   poprawnie zidentyfikowany.
 */
int ReadPatternPolyhedronLib(ViPattePolyhLib  &PPolyhSet,
                           char const         *FileName,
                           ExtString          &ErrMsg
                          );
#endif
 
