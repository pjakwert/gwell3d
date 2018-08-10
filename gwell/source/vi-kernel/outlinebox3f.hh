#ifndef OUTLINEBOX3F_HH
#define OUTLINEBOX3F_HH

/*!
 * \file outlinebox3f.hh
 *  Plik zawiera definicj� szablonu klasy OutlineBox3f. Wykorzystywana
 *  jest ona do wyznaczania prostopad�o�ciennego obrysu bry�y lub zbioru
 *  bry�. Wsp�rz�dne wierzcho�k�w zapisywane s� w zmiennych typu float.
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
 *  Klasa ta jest wykorzystywany do tworzenia prostopa�o�ciennego
 *  obrysu bry�y lub zbior�w bry�. Prostopad�o�cian jest tworzony
 *  w ten spos�b, �e jego poszczeg�lne �ciany r�wnoleg�e s� 
 *  do jednej z p�aszczyzn OXY, OXZ lub OYX. Wsp�rz�dne wierzcho�k�w
 *  obrysu zapisywane s� w zmiennych typu float.
 */
class  OutlineBox3f: public OutlineBox3<float> { 

  public:

    /*!
     *  Sprawdza, czy p�prosta ma przecina dany obrys prostopad�o�cienny.
     *  \param Ln - wsp�rz�dne p�prostej.
     *  \retval true - je�li p�prosta ma cz�� wsp�n� z danym obrysem.
     *  \retval false - w przypadku przeciwnym.
     */
   bool IsCommonPart( const HalfLine3f &Ln ) const;
};

#endif
