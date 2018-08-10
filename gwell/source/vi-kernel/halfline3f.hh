#ifndef HALFLINE3D_H
#define HALFLINE3D_H

/*!
 * \file halfline3f.hh
 * Plik zawiera definicjê klasy Line3f.
 * \author Bogdan Kreczmer
 * \date   2003.11
 */


#ifdef __GNUG__
#pragma interface
#endif


#include "line3f.hh"


/*!
 * Klasa reprezentuje pó³prost± w 3D. Reprezentowana jest ona 
 * poprzez wspó³czynniki jego równania parametrycznego:
 *    \f[ X =  \_A*t + \_B \f]
 * gdzie \e _A jest jej wektorem kierunowym, za¶ \e _B jej pocz±tkiem.
 */
class HalfLine3f: public Line3f {
 public:
   /*!
    * Sprawdzaja czy wspó³rzêdne punktów na pó³prostej mog± mieæ
    * warto¶ci wzd³u¿ osi OX w przedziale \e x_min, \e x_max (bez brzegu).
    * \param x_min - dolne ograniczenie dopuszczalnych warto¶ci
    * \param x_max - górne ograniczenie dopuszczalnych warto¶ci.
    * \pre \e x_min <= \e x_max
    * \retval true - je¿eli istniej± punkty, których wspó³rzêdne
    *                \e x-owe mieszcz± siê w zadanym przedziale.
    * \retval false - w przypadku przeciwnym.
    */
  bool InX(float x_min, float x_max) const;
   /*!
    * Sprawdzaja czy wspó³rzêdne punktów na pó³prostej mog± mieæ
    * warto¶ci wzd³u¿ osi OY w przedziale \e y_min, \e y_max (bez brzegu).
    * \param y_min - dolne ograniczenie dopuszczalnych warto¶ci
    * \param y_max - górne ograniczenie dopuszczalnych warto¶ci.
    * \pre \e y_min <= \e y_max
    * \retval true - je¿eli istniej± punkty, których wspó³rzêdne
    *                \e y-owe mieszcz± siê w zadanym przedziale.
    * \retval false - w przypadku przeciwnym.
    */
  bool InY(float y_min, float y_max) const;
   /*!
    * Sprawdzaja czy wspó³rzêdne punktów na pó³prostej mog± mieæ
    * warto¶ci wzd³u¿ osi OZ w przedziale \e z_min, \e z_max (bez brzegu).
    * \param z_min - dolne ograniczenie dopuszczalnych warto¶ci
    * \param z_max - górne ograniczenie dopuszczalnych warto¶ci.
    * \pre \e z_min <= \e z_max
    * \retval true - je¿eli istniej± punkty, których wspó³rzêdne
    *                \e z-owe mieszcz± siê w zadanym przedziale.
    * \retval false - w przypadku przeciwnym.
    */
  bool InZ(float z_min, float z_max) const;

   /*!
    * Sprawdza czy pó³prosta przecina prostopad³o¶cian, tzn czy ma punkty 
    * wspólne z jego wnêtrzem. Rozpatrywany jest tylko prostopad³o¶cian,
    * którego ¶cianki równoleg³e s±, odpowiednio do p³aszczyzn OXY, OXZ,
    * OYX.
    * \param Min - wspó³rzêdne wierzcho³ka, którego warto¶ci wspó³rzêdnych
    *              wzd³u¿ poszczególnych osi s± najmniejsze spo¶ród
    *              wszystkich wierzcho³ków.
    * \param Max - wspó³rzêdne wierzcho³ka, którego warto¶ci wspó³rzêdnych
    *              wzd³u¿ poszczególnych osi s± najwiêksze spo¶ród
    *              wszystkich wierzcho³ków.
    * \pre \f$ Min.x \le Max.x, Min.y \le Max.y, Min.z \le Max.z  \f$
    * \retval true - je¶li pó³prosta przecina prostopad³o¶cian,
    * \retval false - w przypadku przeciwnym.
    */
  bool IsHalfLineCrossBox( Vector3f const &Min, Vector3f const &Max) const;
  /*!
   * Inicjalizuje parametry równania pó³prostej jako zerowe.
   */
  HalfLine3f() {}
  /*!
   *  Inicjalizuje warto¶ci wspó³czynników równania pó³prostej
   *  warto¶ciami udostêpnianymi przez parametry wywo³ania.
   *  \param A - udostêpnione przez ten parametr warto¶ci 
   *            inicjalizuj± wspó³rzêdne wektora kierunkowego pó³prostej.
   *  \param B - udostêpnione przez ten parametr warto¶ci 
   *            inicjalizuj± wspó³rzêdne punktu zaczepienia pó³prostej.
   *  \pre \f$ A \ne 0 \f$.
   */
  HalfLine3f(Vector3f const &A, Vector3f const &B): Line3f(A,B) {}
  /*!
   *  Inicjalizuje warto¶ci wspó³czynników równania pó³prostej
   *  na podstawie wspó³rzêdnych dwóch punktów, przez które ta 
   *  prosta ma przechodziæ.
   *  \param Po - wspó³rzêdne pierwszego punktu.
   *  \param Pn - wspó³rzêdne drugiego punktu.
   *  \pre \f$ Po \ne Pn \f$
   *  \post Jako punkt pocz±tku pó³prostej przyjmuje siê
   *        punkt \e Po.
   */
  HalfLine3f(Vector3f const &Po, Vector3f const &Pn, int):
        Line3f(Po,Pn,0) {}
};

#endif
