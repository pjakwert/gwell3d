#ifndef LINE3F_H
#define LINE3F_H

/*!
 * \file line3f.hh
 * Plik zawiera definicjê klasy Line3f.
 * \author Bogdan Kreczmer
 * \date   2003.11
 */


#ifdef __GNUG__
#pragma interface
#endif

#include "vector3f.hh"


  /*!
   * Klasa reprezentuje prost± w 3D. Reprezentowana jest ona 
   * poprzez wspó³czynniki jego równania parametrycznego:
   *    \f[ X =  \_A*t + \_B \f]
   * gdzie \e _A jest jej wektorem kierunowym, za¶ \e _B jej pocz±tkiem.
   */
class Line3f {
 protected:

   /*!
    * Wspó³czynniki kierunkowy w prametrycznym opisie prostej.
    *
    *    \f[ X =  \_A*t + \_B \f]
    */
  Vector3f _A;

   /*!
    * Punkt zerowy (\e t=0) prostej w jej parametrycznym opisie.
    *
    *    \f[ X =  \_A*t +  \_B \f]
    */
  Vector3f _B;

    
 public:
  /*!
   *  Udostêpnia wektor kierunkowy prostej.
   */
  Vector3f const &A() const { return _A; }
  /*!
   *  Udostêpnia punkt zaczepienia prostej.
   */
  Vector3f const &B() const { return _B; }
  /*!
   *  Udostêpnia wektor kierunkowy prostej w trybie modyfikacji.
   */
  Vector3f &A() { return _A; }
  /*!
   *  Udostêpnia punkt zaczepienia prostej.
   */
  Vector3f &B() { return _B; }
  /*!
   *  Nadaje now± warto¶æ wektorowi kierunkowemu prostej.
   *  \param  A - nowa warto¶æ dla wektora kierunkowego.
   *  \post Nowa warto¶æ zostaje wpisana \link Line3f::_A _A\endlink.
   */
  void SetA(Vector3f const &A) { _A = A; }
  /*!
   *  Nadaje nowe warto¶ci wspó³czynnikom równania prostej.
   *  \param A - nowa warto¶æ wspó³rzêdnych wektora kierunkowego,
   *  \param B - nowa warto¶æ wspó³rzêdnych punktu zaczepienia.
   *  \post Modyfikacji ulegaj± zawarto¶ci pól
   *   \link Line3f::_A _A\endlink oraz \link Line3f::_B _B\endlink
   */
  void SetLineParameters(Vector3f const &A, Vector3f const &B){_A=A; _B=B;}
  /*!
   *  Wyznacza nowe równianie prostej na podstawie wspó³rzêdnych dwóch
   *  punktów, przez które ta prosta ma przechodziæ.
   *  \param Po - wspó³rzêdne pierwszego punktu.
   *  \param Pn - wspó³rzêdne drugiego punktu.
   *  \pre \f$ Po \ne Pn \f$
   *  \post Modyfikacji ulegaj± zawarto¶ci pól
   *   \link Line3f::_A _A\endlink oraz \link Line3f::_B _B\endlink
   */
  void SetLineBetweenPoints(Vector3f const &Po, Vector3f const &Pn);


   /*!
    * Metoda zmienia kierunek wektora _A na przeciwny.
    */
  void Inverse() { _A.Inverse(); }

   /*!
    * Normalizuje wspó³czynnik kierunkowy prostej (pole \e _A). 
    */
  void Normalize();

   /*!
    * Metoda wyznacza punkt na prostej zgodnie z równaniem:
    *
    *    \f[ X =  \_A*t + \_B \f]
    * \param t - wspó³czynnik dla równania paramterycznego prostej.
    * \return obiekt zawieraj±cy wspó³rzêdne wyznaczonego punktu.
    */
  Vector3f Point(float t) const;

   /*!
    * Metoda wyznacza punkt na prostej zgodnie z równaniem:
    *
    *   \f[ X =  \_A*t + \_B \f]
    * \param t - wspó³czynnik równania paramterycznego prostej.
    * \param Pnt - wspó³rzêdne wyznaczonego punktu.
    * \pre  t - wspó³czynnik dla równania paramterycznego prostej.
    * \retval
    *   Pnt - wyliczone wspó³rzêdne punktu.
    */
  void Point(float t, Vector3f &Pnt) const;

   /*!
    * Wylicza wspó³rzêdne punktu na prostej dla zadanej jego 
    * \e x-owej wspó³rzêdnej.
    * \param x - (\b in) wspó³rzêdna x-owa, dla której wyliczane s± pozosta³e
    *            wspó³rzêdne punktu le¿±cego na tej prostej.
    * \param Pnt - (\b out) zawiera wynikowe wspó³rzêdne wyznaczonego
    *              punktu.
    * \retval true - gdy wyliczenie wspó³rzêdnych punktu o podanej wspó³rzêdnej
    *              \e x-owej by³o mo¿liwe. Wynik przekazany jest poprzez
    *              parametr \e Pnt.
    * \retval false - w przypadku przeciwnym.
    */
  bool PointX(float x, Vector3f &Pnt) const;
   /*!
    * Wylicza wspó³rzêdne punktu na prostej dla zadanej jego 
    * \e y-owej wspó³rzêdnej.
    * \param y - (\b in) wspó³rzêdna y-owa, dla której wyliczane s± pozosta³e
    *            wspó³rzêdne punktu le¿±cego na tej prostej.
    * \param Pnt - (\b out) zawiera wynikowe wspó³rzêdne wyznaczonego
    *              punktu.
    * \retval true - gdy wyliczenie wspó³rzêdnych punktu o podanej wspó³rzêdnej
    *              \e y-owej by³o mo¿liwe. Wynik przekazany jest poprzez
    *              parametr \e Pnt.
    * \retval false - w przypadku przeciwnym.
    */
  bool PointY(float y, Vector3f &Pnt) const;
   /*!
    * Wylicza wspó³rzêdne punktu na prostej dla zadanej jego 
    * \e z-owej wspó³rzêdnej.
    * \param z - (\b in) wspó³rzêdna z-owa, dla której wyliczane s± pozosta³e
    *            wspó³rzêdne punktu le¿±cego na tej prostej.
    * \param Pnt - (\b out) zawiera wynikowe wspó³rzêdne wyznaczonego
    *              punktu.
    * \retval true - gdy wyliczenie wspó³rzêdnych punktu o podanej wspó³rzêdnej
    *              \e z-owej by³o mo¿liwe. Wynik przekazany jest poprzez
    *              parametr \e Pnt.
    * \retval false - w przypadku przeciwnym.
    */
  bool PointZ(float z, Vector3f &Pnt) const;

  /*!
   * Inicjalizuje parametry równania prostej jako zerowe.
   */
  Line3f() {}
  /*!
   *  Inicjalizuje warto¶ci wspó³czynników równania prostej
   *  warto¶ciami udostêpnianymi przez parametry wywo³ania.
   *  \param A - udostêpnione przez ten parametr warto¶ci 
   *            inicjalizuj± wspó³rzêdne wektora kierunkowego prostej.
   *  \param B - udostêpnione przez ten parametr warto¶ci 
   *            inicjalizuj± wspó³rzêdne punktu zaczepienia prostej.
   *  \pre \f$ A \ne 0 \f$.
   */
  Line3f(Vector3f const &A, Vector3f const &B): _A(A), _B(B) {}
  /*!
   *  Inicjalizuje warto¶ci wspó³czynników równania prostej
   *  na podstawie wspó³rzêdnych dwóch punktów, przez które ta 
   *  prosta ma przechodziæ.
   *  \param Po - wspó³rzêdne pierwszego punktu.
   *  \param Pn - wspó³rzêdne drugiego punktu.
   *  \pre \f$ Po \ne Pn \f$
   *  \post Jako punkt pocz±tku pó³prostej przyjmuje siê
   *        punkt \e Po.
   */
  Line3f(Vector3f const &Po, Vector3f const &Pn, int );
};

#endif
