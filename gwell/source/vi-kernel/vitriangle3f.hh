#ifndef VITRIANGLE3F_HH
#define VITRIANGLE3F_HH

/*! \file vitriangle3f.hh
 *  Plik zawiera definicj� typu ViTriangle3f. Wykorzystyny jest on
 *  do rozbijania dowolnej �cianki reprezentowanej przez wielobok wypuk�y
 *  na zbi�r tr�jk�t�w. Wsp�rz�dne wierzcho�k�w zapisywane  s� jako
 *  warto�ci typu float.
 *  \author  Bogdan Kreczmer
 *  \date    2004.03.27
 */



#ifdef __GNUG__
#pragma interface
#endif


#include "vitriangle3.hh"


/*! Zmienne tego typu  wykorzystyne s�
 *  do rozbijania dowolnej �cianki reprezentowanej przez wielobok wypuk�y
 *  na zbi�r tr�jk�t�w. Wsp�rz�dne wierzcho�k�w zapisywane  s� jako
 *  warto�ci typu float.
 */
typedef ViTriangle3<float> ViTriangle3f;


#endif
