#ifndef OUTLINEBOX3F_HH
#define OUTLINEBOX3F_HH

/*!
 * \file outlinebox3f.hh
 *  Plik zawiera definicjê szablonu klasy OutlineBox3f. Wykorzystywana
 *  jest ona do wyznaczania prostopad³o¶ciennego obrysu bry³y lub zbioru
 *  bry³. Wspó³rzêdne wierzcho³ków zapisywane s± w zmiennych typu float.
 *
 *  \author Bogdan Kreczmer
 *  \date   2004.02
 */



/*
 * File:	outlinebox3.hh
 * Purpose:     Wyznaczanie obrysu prostopadloscianowego danego obiektu
 * Author:	Bogdan Kreczmer
 * Created:	styczen 2004
 * Updated:
 * Copyright:	(c) 2004, Bogdan Kreczmer
 */


#include "outlinebox3.hh"

class HalfLine3f;


/*!
 *  Klasa ta jest wykorzystywany do tworzenia prostopa³o¶ciennego
 *  obrysu bry³y lub zbiorów bry³. Prostopad³o¶cian jest tworzony
 *  w ten sposób, ¿e jego poszczególne ¶ciany równoleg³e s± 
 *  do jednej z p³aszczyzn OXY, OXZ lub OYX. Wspó³rzêdne wierzcho³ków
 *  obrysu zapisywane s± w zmiennych typu float.
 */
class  OutlineBox3f: public OutlineBox3<float> { 

  public:

    /*!
     *  Sprawdza, czy pó³prosta ma przecina dany obrys prostopad³o¶cienny.
     *  \param Ln - wspó³rzêdne pó³prostej.
     *  \retval true - je¶li pó³prosta ma czê¶æ wspó³n± z danym obrysem.
     *  \retval false - w przypadku przeciwnym.
     */
   bool IsCommonPart( const HalfLine3f &Ln ) const;
};

#endif
