#include <iostream>
#include <values.h>
#include <cmath>
#include "plain3f.hh"
#include "line3f.hh"
#include "halfline3f.hh"
#include "vector3.hh"

using namespace std;



bool Plain3f::ComputePlain3f( Vector3f const &V0, 
                          Vector3f const &V1, 
                          Vector3f const &V2
                        )
{  
   _NVct = (V1-V0)*(V2-V1);  
   //   cerr << " Plain3f: " << V0 << " " << V1 << " " << V2 << endl;
   if (!NormalizeVct()) return false;
   _D = -(V0 & _NVct);
   return true;
}



/*=============================================================================
 * Wyznacza jedn� ze wsp�rz�dnych punktu plaszczyzny na podstawie 
 * pozosta�ych. 
 * Jezeli jest to niemo�liwe (p�aszczyzna jest r�wnoleg�a do YOZ), to 
 * zwracana jest warto�� MAXFLOAT
 */
float Plain3f::X(float y, float z) const
{
  return sgn(_NVct.x) ? -(_NVct.y*y+_NVct.z*z-_D)/_NVct.x : MAXFLOAT;
}


/*=============================================================================
 * Analogicznie jak wy�ej.
 */
float Plain3f::Y(float x, float z) const
{
  return sgn(_NVct.y) ? -(_NVct.x*x+_NVct.z*z-_D)/_NVct.y : MAXFLOAT;
}


/*=============================================================================
 * Analogicznie jak wy�ej.
 */
float Plain3f::Z(float x, float y) const
{
  return sgn(_NVct.z) ? -(_NVct.x*x+_NVct.y*y-_D)/_NVct.z : MAXFLOAT;
}



/*=============================================================================
 * Dokonuje normalizacji wektora _NVct  
 */
bool Plain3f::NormalizeVct() 
{  
  float d = _NVct & _NVct;
  if (!sgn(d)) {
    cerr << "!!! Plain3f::NormalizeVct" << endl;
    cerr << "!!!  Proba normalizacji zerowego wektora." << endl;
    return false;
  }
  _NVct /= sqrt(d);
  return true;
}


/*======================================================================
 * Metoda wyznacza punkt przeciecia linii prostej z dan� p�aszczyzn�.
 *
 * PRE:  Ln - zawiera opis linii prostej.
 *
 * POST (zwraca warto��):
 *     true  - gdy istnieje punkt przeci�cia.
 *            Pnt - zawiera wsp�rz�dne punktu przeci�cia.
 *              t - warto�� dla parametrycznego opisu prostej, ktora to
 *                  warto�� wyznacza dany punkt.
 *     false - gdy nie istnieje punkt przeci�cia.
 *            Pnt - zawarto�� obiektu nie ulega zmianie.
 */
bool Plain3f::CrossPoint4Line(Line3f const &Ln, Vector3f &Pnt, float &t) const
{
  float AA = Ln.A() & GetNVct();
  if (!sgn(AA)) return false;
  Ln.Point(t = -((Ln.B() & GetNVct()) + GetD())/AA, Pnt);
  return true;
}







/*======================================================================
 * Metoda wyznacza punkt przeci�cia p�prostej z dan� p�aszczyzn�.
 *
 * PRE:  Ln - zawiera opis linii p�prostej.
 *
 * POST (zwraca warto��):
 *     true  - gdy istnieje punkt przeci�cia.
 *            Pnt - zawiera wsp�rz�dne punktu przeci�cia.
 *              t - zawiera warto�� parametru okre�laj�cego po�o�enie
 *                  punktu na p�prostej. Warto�� ta musi by� dodatnia.
 *     false - gdy nie istnieje punkt przeci�cia.
 *            Pnt - zawarto�� obiektu nie ulega zmianie.
 */
bool Plain3f::CrossPoint4HalfLine( HalfLine3f const &Ln, 
                                   Vector3f         &Pnt, 
                                   float            &t
                                 )const
{
  float AA = Ln.A() & GetNVct();
  if (!sgn(AA)) return false;
  t = -((Ln.B() & GetNVct()) + GetD())/AA;
  if (sgn(t) != 1) return false;
  Ln.Point(t, Pnt);
  return true;
}


