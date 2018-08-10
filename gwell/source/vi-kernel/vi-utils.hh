#ifndef  VI_UTILS_HH
#define  VI_UTILS_HH

#include <cmath>
#include "vector3f.hh"

/*!
 * Makro przelicza radiany na stopnie.
 */
#define RAD2DEG(x) ((180*x)/M_PI)
/*!
 * Makro przelicza stopnie na radiany.
 */
#define DEG2RAD(x) ((M_PI*x)/180)

/*!
 *  Realizuje konwersjê warto¶ci sk³adowych wektora wyra¿onych
 *  w stopniach na warto¶ci wyra¿one w radianach.
 *  \param V - (\b in/\b out) wektor konwertowanych warto¶ci k±towych.
 */
inline
Vector3f &convert_deg2rad(Vector3f &V)
{
  return V.Set(DEG2RAD(V.x),DEG2RAD(V.y),DEG2RAD(V.z));
}

/*!
 *  Realizuje konwersjê warto¶ci sk³adowych wektora wyra¿onych
 *  w radianach na warto¶ci wyra¿one w stopniach.
 *  \param V - (\b in/\b out) wektor konwertowanych warto¶ci k±towych.
 */
inline
Vector3f &convert_rad2deg(Vector3f &V)
{
  return V.Set(RAD2DEG(V.x),RAD2DEG(V.y),RAD2DEG(V.z));
}


/*!
 *  Wyznacza wektor warto¶ci sk³adowych wyra¿onych w radianach
 *  na podstawie wektora warto¶ci wyra¿onych w stopniach.
 *  \param V - (\b in) wektor warto¶ci k±towych wyra¿onych w stopniach
 *            na podstawie których obliczany jest wektor warto¶ci 
 *            k±towych wyra¿onych w radianach.
 *  \return wektor warto¶ci wyra¿onych w radianach.
 */
inline 
Vector3f compute_deg2rad(const Vector3f &V)
{
  Vector3f V_tmp = V;  convert_deg2rad(V_tmp);  return V_tmp; 
}


/*!
 *  Wyznacza wektor warto¶ci sk³adowych wyra¿onych w stopniach
 *  na podstawie wektora warto¶ci wyra¿onych w radianach.
 *  \param V - (\b in) wektor warto¶ci k±towych wyra¿onych w radianach
 *            na podstawie których obliczany jest wektor warto¶ci 
 *            k±towych wyra¿onych w stopniach.
 *  \return wektor warto¶ci wyra¿onych w stopniach.
 */
inline 
Vector3f compute_rad2deg(const Vector3f &V)
{
  Vector3f V_tmp = V;  convert_rad2deg(V_tmp);  return V_tmp; 
}

#endif
