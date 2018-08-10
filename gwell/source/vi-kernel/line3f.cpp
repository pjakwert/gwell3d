#ifdef __GNUG__
#pragma implementation
#endif

#include <iostream>
#include <math.h>
#include "vector3.hh"
#include "line3f.hh"


using namespace std;


void Line3f::SetLineBetweenPoints(Vector3f const &Po, Vector3f const &Pn)
{
  _A = Pn - Po;
  _B = Po;
}


/*===========================================================================
 * Normalizuje wspó³czynnik kierunkowy prostej (pole _A). 
 */
void Line3f::Normalize()
{
  if (!sgn(_A.x) && !sgn(_A.y) && !sgn(_A.z)) {
    cerr << "!!! Line3f::Normalize" << endl;
    cerr << "!!!   Normalizacja wektora zerowego!" << endl;
    return;
  }
  _A = _A/sqrt(_A & _A);
}


Line3f::Line3f(Vector3f const &Po, Vector3f const &Pn, int )
{
  SetLineBetweenPoints(Po,Pn);
}


/*==================================================================
 * Metoda wyznacza punkt na prostej zgodnie z rownaniem:
 *    X = _A*t + _B
 */
Vector3f Line3f::Point(float t) const
{
  Vector3f Pnt = A()*t + B();
  return Pnt;
}


/*==================================================================
 * Metoda wyznacza punkt na prostej zgodnie z rownaniem:
 *    X = _A*t + _B
 */
void Line3f::Point(float t, Vector3f &Pnt) const
{
  Pnt = A()*t + B();
}



/*=============================================================================
 * Wylicza punkt na prostej, którego wspó³rzêdna x-owa równa siê 'x'.
 *
 * PRE:  x - wspó³rzêdna x-owa, dla której maj± byæ wyznaczone pozosta³e
 *           wspó³rzêdne punktu na prostej.
 *
 * POST (zwaraca warto¶æ): 
 *     true   - je¿eli wyznaczenie wspó³rzêdnych punktu by³o mo¿liwe.
 *         Pnt - zawiera wszystki wspó³rzêdne wyznaczonego punktu.
 *
 *     false  - je¿eli wyznaczenie wspó³rzêdnych punktów okaza³o siê 
 *              niemo¿liwe (gdy _A.x == 0).
 */
bool Line3f::PointX(float x, Vector3f &Pnt) const
{
  if (!sgn(_A.x)) return false;
  float t = (x-_B.x)/_A.x;
  Pnt.Set(x,_A.y*t+_B.y,_A.z*t+_B.z);
  return true;
}

/*=============================================================================
 * Analogicznie jak wy¿ej.
 */
bool Line3f::PointY(float y, Vector3f &Pnt) const
{
  if (!sgn(_A.y)) return false;
  float t = (y-_B.y)/_A.y;
  Pnt.Set(_A.x*t+_B.x,y,_A.z*t+_B.z);
  return true;
}


/*=============================================================================
 * Analogicznie jak wy¿ej.
 */
bool Line3f::PointZ(float z, Vector3f &Pnt) const
{
  if (!sgn(_A.z)) return false;
  float t = (z-_B.z)/_A.z;
  Pnt.Set(_A.x*t+_B.x,_A.y*t+_B.y,z);
  return true;
}


