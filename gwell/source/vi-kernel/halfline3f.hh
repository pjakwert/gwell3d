#ifndef HALFLINE3D_H
#define HALFLINE3D_H

/*!
 * \file halfline3f.hh
 * Plik zawiera definicj� klasy Line3f.
 * \author Bogdan Kreczmer
 * \date   2003.11
 */


#ifdef __GNUG__
#pragma interface
#endif


#include "line3f.hh"


/*!
 * Klasa reprezentuje p�prost� w 3D. Reprezentowana jest ona 
 * poprzez wsp�czynniki jego r�wnania parametrycznego:
 *    \f[ X =  \_A*t + \_B \f]
 * gdzie \e _A jest jej wektorem kierunowym, za� \e _B jej pocz�tkiem.
 */
class HalfLine3f: public Line3f {
 public:
   /*!
    * Sprawdzaja czy wsp�rz�dne punkt�w na p�prostej mog� mie�
    * warto�ci wzd�u� osi OX w przedziale \e x_min, \e x_max (bez brzegu).
    * \param x_min - dolne ograniczenie dopuszczalnych warto�ci
    * \param x_max - g�rne ograniczenie dopuszczalnych warto�ci.
    * \pre \e x_min <= \e x_max
    * \retval true - je�eli istniej� punkty, kt�rych wsp�rz�dne
    *                \e x-owe mieszcz� si� w zadanym przedziale.
    * \retval false - w przypadku przeciwnym.
    */
  bool InX(float x_min, float x_max) const;
   /*!
    * Sprawdzaja czy wsp�rz�dne punkt�w na p�prostej mog� mie�
    * warto�ci wzd�u� osi OY w przedziale \e y_min, \e y_max (bez brzegu).
    * \param y_min - dolne ograniczenie dopuszczalnych warto�ci
    * \param y_max - g�rne ograniczenie dopuszczalnych warto�ci.
    * \pre \e y_min <= \e y_max
    * \retval true - je�eli istniej� punkty, kt�rych wsp�rz�dne
    *                \e y-owe mieszcz� si� w zadanym przedziale.
    * \retval false - w przypadku przeciwnym.
    */
  bool InY(float y_min, float y_max) const;
   /*!
    * Sprawdzaja czy wsp�rz�dne punkt�w na p�prostej mog� mie�
    * warto�ci wzd�u� osi OZ w przedziale \e z_min, \e z_max (bez brzegu).
    * \param z_min - dolne ograniczenie dopuszczalnych warto�ci
    * \param z_max - g�rne ograniczenie dopuszczalnych warto�ci.
    * \pre \e z_min <= \e z_max
    * \retval true - je�eli istniej� punkty, kt�rych wsp�rz�dne
    *                \e z-owe mieszcz� si� w zadanym przedziale.
    * \retval false - w przypadku przeciwnym.
    */
  bool InZ(float z_min, float z_max) const;

   /*!
    * Sprawdza czy p�prosta przecina prostopad�o�cian, tzn czy ma punkty 
    * wsp�lne z jego wn�trzem. Rozpatrywany jest tylko prostopad�o�cian,
    * kt�rego �cianki r�wnoleg�e s�, odpowiednio do p�aszczyzn OXY, OXZ,
    * OYX.
    * \param Min - wsp�rz�dne wierzcho�ka, kt�rego warto�ci wsp�rz�dnych
    *              wzd�u� poszczeg�lnych osi s� najmniejsze spo�r�d
    *              wszystkich wierzcho�k�w.
    * \param Max - wsp�rz�dne wierzcho�ka, kt�rego warto�ci wsp�rz�dnych
    *              wzd�u� poszczeg�lnych osi s� najwi�ksze spo�r�d
    *              wszystkich wierzcho�k�w.
    * \pre \f$ Min.x \le Max.x, Min.y \le Max.y, Min.z \le Max.z  \f$
    * \retval true - je�li p�prosta przecina prostopad�o�cian,
    * \retval false - w przypadku przeciwnym.
    */
  bool IsHalfLineCrossBox( Vector3f const &Min, Vector3f const &Max) const;
  /*!
   * Inicjalizuje parametry r�wnania p�prostej jako zerowe.
   */
  HalfLine3f() {}
  /*!
   *  Inicjalizuje warto�ci wsp�czynnik�w r�wnania p�prostej
   *  warto�ciami udost�pnianymi przez parametry wywo�ania.
   *  \param A - udost�pnione przez ten parametr warto�ci 
   *            inicjalizuj� wsp�rz�dne wektora kierunkowego p�prostej.
   *  \param B - udost�pnione przez ten parametr warto�ci 
   *            inicjalizuj� wsp�rz�dne punktu zaczepienia p�prostej.
   *  \pre \f$ A \ne 0 \f$.
   */
  HalfLine3f(Vector3f const &A, Vector3f const &B): Line3f(A,B) {}
  /*!
   *  Inicjalizuje warto�ci wsp�czynnik�w r�wnania p�prostej
   *  na podstawie wsp�rz�dnych dw�ch punkt�w, przez kt�re ta 
   *  prosta ma przechodzi�.
   *  \param Po - wsp�rz�dne pierwszego punktu.
   *  \param Pn - wsp�rz�dne drugiego punktu.
   *  \pre \f$ Po \ne Pn \f$
   *  \post Jako punkt pocz�tku p�prostej przyjmuje si�
   *        punkt \e Po.
   */
  HalfLine3f(Vector3f const &Po, Vector3f const &Pn, int):
        Line3f(Po,Pn,0) {}
};

#endif
