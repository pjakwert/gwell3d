#ifndef LINE3F_H
#define LINE3F_H

/*!
 * \file line3f.hh
 * Plik zawiera definicj� klasy Line3f.
 * \author Bogdan Kreczmer
 * \date   2003.11
 */


#ifdef __GNUG__
#pragma interface
#endif

#include "vector3f.hh"


  /*!
   * Klasa reprezentuje prost� w 3D. Reprezentowana jest ona 
   * poprzez wsp�czynniki jego r�wnania parametrycznego:
   *    \f[ X =  \_A*t + \_B \f]
   * gdzie \e _A jest jej wektorem kierunowym, za� \e _B jej pocz�tkiem.
   */
class Line3f {
 protected:

   /*!
    * Wsp�czynniki kierunkowy w prametrycznym opisie prostej.
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
   *  Udost�pnia wektor kierunkowy prostej.
   */
  Vector3f const &A() const { return _A; }
  /*!
   *  Udost�pnia punkt zaczepienia prostej.
   */
  Vector3f const &B() const { return _B; }
  /*!
   *  Udost�pnia wektor kierunkowy prostej w trybie modyfikacji.
   */
  Vector3f &A() { return _A; }
  /*!
   *  Udost�pnia punkt zaczepienia prostej.
   */
  Vector3f &B() { return _B; }
  /*!
   *  Nadaje now� warto�� wektorowi kierunkowemu prostej.
   *  \param  A - nowa warto�� dla wektora kierunkowego.
   *  \post Nowa warto�� zostaje wpisana \link Line3f::_A _A\endlink.
   */
  void SetA(Vector3f const &A) { _A = A; }
  /*!
   *  Nadaje nowe warto�ci wsp�czynnikom r�wnania prostej.
   *  \param A - nowa warto�� wsp�rz�dnych wektora kierunkowego,
   *  \param B - nowa warto�� wsp�rz�dnych punktu zaczepienia.
   *  \post Modyfikacji ulegaj� zawarto�ci p�l
   *   \link Line3f::_A _A\endlink oraz \link Line3f::_B _B\endlink
   */
  void SetLineParameters(Vector3f const &A, Vector3f const &B){_A=A; _B=B;}
  /*!
   *  Wyznacza nowe r�wnianie prostej na podstawie wsp�rz�dnych dw�ch
   *  punkt�w, przez kt�re ta prosta ma przechodzi�.
   *  \param Po - wsp�rz�dne pierwszego punktu.
   *  \param Pn - wsp�rz�dne drugiego punktu.
   *  \pre \f$ Po \ne Pn \f$
   *  \post Modyfikacji ulegaj� zawarto�ci p�l
   *   \link Line3f::_A _A\endlink oraz \link Line3f::_B _B\endlink
   */
  void SetLineBetweenPoints(Vector3f const &Po, Vector3f const &Pn);


   /*!
    * Metoda zmienia kierunek wektora _A na przeciwny.
    */
  void Inverse() { _A.Inverse(); }

   /*!
    * Normalizuje wsp�czynnik kierunkowy prostej (pole \e _A). 
    */
  void Normalize();

   /*!
    * Metoda wyznacza punkt na prostej zgodnie z r�wnaniem:
    *
    *    \f[ X =  \_A*t + \_B \f]
    * \param t - wsp�czynnik dla r�wnania paramterycznego prostej.
    * \return obiekt zawieraj�cy wsp�rz�dne wyznaczonego punktu.
    */
  Vector3f Point(float t) const;

   /*!
    * Metoda wyznacza punkt na prostej zgodnie z r�wnaniem:
    *
    *   \f[ X =  \_A*t + \_B \f]
    * \param t - wsp�czynnik r�wnania paramterycznego prostej.
    * \param Pnt - wsp�rz�dne wyznaczonego punktu.
    * \pre  t - wsp�czynnik dla r�wnania paramterycznego prostej.
    * \retval
    *   Pnt - wyliczone wsp�rz�dne punktu.
    */
  void Point(float t, Vector3f &Pnt) const;

   /*!
    * Wylicza wsp�rz�dne punktu na prostej dla zadanej jego 
    * \e x-owej wsp�rz�dnej.
    * \param x - (\b in) wsp�rz�dna x-owa, dla kt�rej wyliczane s� pozosta�e
    *            wsp�rz�dne punktu le��cego na tej prostej.
    * \param Pnt - (\b out) zawiera wynikowe wsp�rz�dne wyznaczonego
    *              punktu.
    * \retval true - gdy wyliczenie wsp�rz�dnych punktu o podanej wsp�rz�dnej
    *              \e x-owej by�o mo�liwe. Wynik przekazany jest poprzez
    *              parametr \e Pnt.
    * \retval false - w przypadku przeciwnym.
    */
  bool PointX(float x, Vector3f &Pnt) const;
   /*!
    * Wylicza wsp�rz�dne punktu na prostej dla zadanej jego 
    * \e y-owej wsp�rz�dnej.
    * \param y - (\b in) wsp�rz�dna y-owa, dla kt�rej wyliczane s� pozosta�e
    *            wsp�rz�dne punktu le��cego na tej prostej.
    * \param Pnt - (\b out) zawiera wynikowe wsp�rz�dne wyznaczonego
    *              punktu.
    * \retval true - gdy wyliczenie wsp�rz�dnych punktu o podanej wsp�rz�dnej
    *              \e y-owej by�o mo�liwe. Wynik przekazany jest poprzez
    *              parametr \e Pnt.
    * \retval false - w przypadku przeciwnym.
    */
  bool PointY(float y, Vector3f &Pnt) const;
   /*!
    * Wylicza wsp�rz�dne punktu na prostej dla zadanej jego 
    * \e z-owej wsp�rz�dnej.
    * \param z - (\b in) wsp�rz�dna z-owa, dla kt�rej wyliczane s� pozosta�e
    *            wsp�rz�dne punktu le��cego na tej prostej.
    * \param Pnt - (\b out) zawiera wynikowe wsp�rz�dne wyznaczonego
    *              punktu.
    * \retval true - gdy wyliczenie wsp�rz�dnych punktu o podanej wsp�rz�dnej
    *              \e z-owej by�o mo�liwe. Wynik przekazany jest poprzez
    *              parametr \e Pnt.
    * \retval false - w przypadku przeciwnym.
    */
  bool PointZ(float z, Vector3f &Pnt) const;

  /*!
   * Inicjalizuje parametry r�wnania prostej jako zerowe.
   */
  Line3f() {}
  /*!
   *  Inicjalizuje warto�ci wsp�czynnik�w r�wnania prostej
   *  warto�ciami udost�pnianymi przez parametry wywo�ania.
   *  \param A - udost�pnione przez ten parametr warto�ci 
   *            inicjalizuj� wsp�rz�dne wektora kierunkowego prostej.
   *  \param B - udost�pnione przez ten parametr warto�ci 
   *            inicjalizuj� wsp�rz�dne punktu zaczepienia prostej.
   *  \pre \f$ A \ne 0 \f$.
   */
  Line3f(Vector3f const &A, Vector3f const &B): _A(A), _B(B) {}
  /*!
   *  Inicjalizuje warto�ci wsp�czynnik�w r�wnania prostej
   *  na podstawie wsp�rz�dnych dw�ch punkt�w, przez kt�re ta 
   *  prosta ma przechodzi�.
   *  \param Po - wsp�rz�dne pierwszego punktu.
   *  \param Pn - wsp�rz�dne drugiego punktu.
   *  \pre \f$ Po \ne Pn \f$
   *  \post Jako punkt pocz�tku p�prostej przyjmuje si�
   *        punkt \e Po.
   */
  Line3f(Vector3f const &Po, Vector3f const &Pn, int );
};

#endif
