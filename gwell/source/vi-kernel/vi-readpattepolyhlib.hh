#ifndef VI_READPATTPOLYH_HH
#define VI_READPATTPOLYH_HH
/*!
 * \file  vi-readpattepolyhlib.hh
 * Plik zawiera nag³ówek funkcji realizuj±cej odczyt wielo¶cianów wzorcowych.
 * \author	Bogdan Kreczmer
 * \date	Maj 1995
 */


#ifdef __GNUG__
#pragma interface
#endif

class ViPattePolyhLib;
class ExtString;

/*!
 * Funkcji realizuj±cej odczyt wielo¶cianów wzorcowych.
 * \param  PPolyhSet - wska¼nik na obiekt, w który pe³ni rolê
 *                   zarz±dcy kolejki bry³ wzorcowych.
 * \param  FileName  - nazwa pliku, w którym znajduje siê biblioteka
 *                   obiektów wzorcowych,
 * \param  ErrMsg - w przpadku wyst±pienia b³êdu odczytu w obiekcie
 *                  tym zostanie umieszczony komunkat b³êdu.
 * \retval  0 - je¶li odczyt przebieg³ poprawnie,
 * \retval  <0 - w przypadku przeciwnym.
 * \post
 *   Je¶li odczy przebieg³ poprawnie, to \e pPPolyhSet to zawiera
 *   kolejkê obiektów wzorcowych. W przypadku przeciwnym w \e ErrMsg
 *   umieszczany jest komunikat o b³edzie sk³adni o ile b³ad zosta³
 *   poprawnie zidentyfikowany.
 */
int ReadPatternPolyhedronLib(ViPattePolyhLib  &PPolyhSet,
                           char const         *FileName,
                           ExtString          &ErrMsg
                          );
#endif
 
