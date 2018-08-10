#ifdef __GNUG__
#pragma implementation
#endif

#include "vector3f.hh"
#include "halfline3f.hh"


#include <iostream>
using namespace std;

inline
bool IsInside(float Dir, float Xi, float Xo, float Xn)
{
  switch (sgn(Dir)) {
   case -1: 
     if (Xi < Xo) return false;
     return true;

   case  0:
     if ((Xo < Xi) && (Xi < Xn)) return true;
     return false;

   case  1:
     if (Xn < Xi) return false;
     return true;
  }
  return false;
}


/*==========================================================================
 * Metoda sprawdzaja czy wspó³rzêdne punktów na prostej mog± mieæ
 * warto¶ci wzd³u¿ osi OX w przedziale x_min, x_max.
 */
bool HalfLine3f::InX(float x_min, float x_max) const
{
  return IsInside(_A.x,_B.x,x_min,x_max);
}


bool HalfLine3f::InY(float y_min, float y_max) const
{
  return IsInside(_A.y,_B.y,y_min,y_max);
}


bool HalfLine3f::InZ(float z_min, float z_max) const
{
  return IsInside(_A.x,_B.z,z_min,z_max);
}



/*=============================================================================
 *
 *  Sprawdza czy pó³prosta przecina sze¶cian.
 */
bool HalfLine3f::IsHalfLineCrossBox(  Vector3f const &Min, 
                                      Vector3f const &Max
                                   ) const
{
 if (!InX(Min.x,Max.x) || !InY(Min.y,Max.y) || !InZ(Min.z,Max.z)) {
   return false;
 }

   // Czy punkt B jest wewn±trz prostopad³o¶ianu 
 if (_B.IsInside(Min,Max)) return true;

 Vector3f Pnt;

 if (_B.x < Min.x) {
      // Czy jest przeciêcie ¶cianki w kierunku dodatnim osi OX.
    PointX(Min.x,Pnt);
    if (Pnt.InY(Min.y,Max.y) && Pnt.InZ(Min.z,Max.z)) return true;
 } else {
      // Czy jest przeciêcie ¶cianki w kierunku ujemnym osi OX.
    PointX(Max.x,Pnt);
    if (Pnt.InY(Min.y,Max.y) && Pnt.InZ(Min.z,Max.z)) return true;
 }

 if (_B.y < Min.y) {
    PointY(Min.y,Pnt);
    if (Pnt.InX(Min.x,Max.x) && Pnt.InZ(Min.z,Max.z)) return true;
 } else {
    PointY(Max.y,Pnt);
    if (Pnt.InX(Min.x,Max.x) && Pnt.InZ(Min.z,Max.z)) return true;
 }

 if (_B.z < Min.z) {
    PointZ(Min.z,Pnt);
    if (Pnt.InX(Min.x,Max.x) && Pnt.InY(Min.y,Max.y)) return true;
 } else {
    PointZ(Max.z,Pnt);
    if (Pnt.InX(Min.x,Max.x) && Pnt.InY(Min.y,Max.y)) return true;
 }
 return false;
}
