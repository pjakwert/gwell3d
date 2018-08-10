/*------------------------------------------------------------------------
 * \file        matrixh3f.cpp
 * Plik zawiera implementacj� metod klasy MatrixH3f. Jest ona podstaw�
 * wszystkich transforacji mi�dzy poszczeg�lnymi uk�adami wsp�rz�dnych.
 * \author	Bogdan Kreczmer
 * \date        2004.01
 */

#ifdef __GNUG__
#pragma implementation
#endif

#include <iostream>
#include <cmath>
#include <cstring>
#include "extstring.hh"
#include "streamutils.hh"
#include "matrixh3f.hh"
#include "vi-keywords.hh"
#include "vi-utils.hh"
#include "keywords.h"
#include "sgn.hh"

//#define  TEST



/*! \fn MatrixH3f::GetAngInterp() const
 * \if matrixh3f_brief_desc 
 *  \brief Udost�pnia informacj� o interpretacji k�t�w rotacji.
 * \endif
 *
 * Udost�pnia warto�� pola \link MatrixH3f::_AngInterp _AngInterp\endlink
 * informuj�c� o sposobie interpretacji k�t�w rotacji, kt�re zapisane
 * s� w polu \link MatrixH3f::_RotAng _RotAng\endlink.
 */

/*! \fn MatrixH3f::GetTransOrder() const
 * \if matrixh3f_brief_desc 
 *  \brief Udost�pnia informacj� o interpretacji translacji.
 * \endif
 *
 * Udost�pnia informacj� dotycz�c� kolejno�ci translacji wzgl�dem
 * rotacji.
 */


/*! \class MatrixH3f
 * \if matrixh3f_brief_desc 
 *  \brief Klasa modeluje macierz transformacji dla wsp�rz�dnych
 *         jednorodnych.
 * \endif
 *
 * Klasa modeluje macierz transformacji dla wsp�rz�dnych jednorodnych.
 * Pozwala ona zadawa� transformacj� zar�wno poprzez podanie k�t�w Eulera
 * jak te� poprzez obroty wok� osi \e OX, \e OY, \e OZ.
 * Wektor translacji mo�e by� zadawany przed rotacj� lub po niej.
 *
 * Podstawow� cech� tej klasy jest to, �e pozwala ona odzyskiwa�
 * warto�ci k�t�w rotacji oraz wsp�rz�dne wektora translacji.
 * W takiej konwecji jaka w danym momencie jest potrzebna niezale�nie
 * od sposobu zadania parametr�w transformacji.
 *
 * Aby unikn�� ci�g�ych wylicze� parametr�w transformacji, ich warto�ci
 * s� przechowywane w odpowiednich polach. S� one aktualizowane tylko
 * wtedy gdy zachodzi taka potrzeba. Pozwala to zredukowa� ilo��
 * koniecznych oblicze�.
 */


/*! \fn const Vector3f& MatrixH3f::GetAng_Euler_Rad() const
 * \if matrixh3f_brief_desc 
 * \brief Udost�pnia k�ty Eulera w radianach.
 * \endif
 *
 * Udost�pnia k�ty Eulera dla danej macierzy transformacji.
 * Kolejne wsp�rz�dne wektora odpowiadaj� k�tom
 *  \f$\varphi\f$ (pierwszy obr�t - wok� osi \f$ OZ\f$),
 *  \f$\theta\f$ (drugi obr�t - wok� osi \f$ OY'\f$),
 *  \f$\psi\f$ (trzeci obr�t - wok� osi \f$ OZ''\f$).
 */


/*! \fn Vector3f MatrixH3f::GetAng_Euler_Deg() const
 * \if matrixh3f_brief_desc 
 * \brief Udost�pnia k�ty Eulera w stopniach.
 * \endif
 *
 * Udost�pnia k�ty Eulera dla danej macierzy transformacji.
 * Kolejne wsp�rz�dne wektora odpowiadaj� k�tom
 *  \f$\varphi\f$ (pierwszy obr�t - wok� osi \f$ OZ\f$),
 *  \f$\theta\f$ (drugi obr�t - wok� osi \f$ OY'\f$),
 *  \f$\psi\f$ (trzeci obr�t - wok� osi \f$ OZ''\f$).
 */

 /*!
  * \fn  Vector3f MatrixH3f::TakeAng_XYZ_Deg() const
  * \if matrixh3f_brief_desc 
  * \brief Metoda przeznaczona do debugowania.
  * \endif
  * 
  * Metoda wymusza wyliczenie k�t�w rotacji w reprezentacji \e XYZ
  * bezpo�rednio ze wsp�czynnik�w macierzy.
  * \warning Metoda ta przeznaczona jest do debugowania i nie powinna
  *   by� wykorzystywana we w�a�ciwej aplikacji, chyba �e programista
  *   wie na pewno co robi :).
  */

 /*!
  * \fn  Vector3f MatrixH3f::TakeAng_Euler_Deg() const
  * \if matrixh3f_brief_desc 
  * \brief Metoda przeznaczona do debugowania.
  * \endif
  * 
  * Metoda wymusza wyliczenie k�t�w rotacji w reprezentacji \e Euler
  * bezpo�rednio ze wsp�czynnik�w macierzy.
  * \warning Metoda ta przeznaczona jest do debugowania i nie powinna
  *   by� wykorzystywana we w�a�ciwej aplikacji, chyba �e programista
  *   wie na pewno co robi :).
  */



//----------------- MatrixH3f -----------------------------------------------
//-------- Metody publiczne: ................................................

/*! \fn  float MatrixH3f::GetScaleX() const 
 * \if matrixh3f_brief_desc 
 * \brief Udost�pnia skal� dla osi \e OX.
 * \endif
 *
 * Udost�pnia wsp�czynnik skali dla osi \e OX.
 * \return wp�czynnik skali dla osi \e OX.
 * \post Pole 
 *   \link MatrixH3f::_Valid_Scale  MatrixH3f::_Valid_Scale\endlink
 *   ma warto�� \p true.
 *
 * Uwaga: Pobieranie wsp�czynnik�w skali nie zale�y od
 *        kolejno�ci wykonanej translacji.
 */

/*!  \fn  float MatrixH3f::GetScaleY() const
 * \if matrixh3f_brief_desc 
 * \brief Udost�pnia skal� dla osi \e OY.
 * \endif
 *
 * Udost�pnia wsp�czynnik skali dla osi \e OY.
 * \return wp�czynnik skali dla osi \e OY.
 * \post Pole 
 *   \link MatrixH3f::_Valid_Scale  MatrixH3f::_Valid_Scale\endlink
 *   ma warto�� \p true.
 *
 * Uwaga: Pobieranie wsp�czynnik�w skali nie zale�y od
 *        kolejno�ci wykonanej translacji.
 */

/*! \fn  float MatrixH3f::GetScaleZ() const 
 * \if matrixh3f_brief_desc 
 * \brief Udost�pnia skal� dla osi \e OZ.
 * \endif
 *
 * Udost�pnia wsp�czynnik skali dla osi \e OZ.
 * \return wp�czynnik skali dla osi \e OZ.
 * \post Pole 
 *   \link MatrixH3f::_Valid_Scale  MatrixH3f::_Valid_Scale\endlink
 *   ma warto�� \p true.
 *
 * Uwaga: Pobieranie wsp�czynnik�w skali nie zale�y od
 *        kolejno�ci wykonanej translacji.
 */

/*! \fn void MatrixH3f::SetScale_TAfterR(float Sx, float Sy, float Sz)
 * \if matrixh3f_brief_desc 
 * \brief Ustawia now� skal� dla przypadku translacji po rotacji.
 * \endif
 *
 * Wstawia now� skal� przyjmuj�c, �e aktualne wsp�czynniki
 * macierzy przekszta�cenia jednorodnego odpowiadaj� przypadkowi,
 * gdy translacja jest realizowana po rotacji. W takim przypadku
 * operacja nie powoduje zmiany czwartej kolumny macierzy transformacji,
 * kt�ra w tej interpretacji odpowiada bezpo�rednio wektorowi translacji.
 * \param Sx - (\b in) wsp�czynnik skali dla osi \e OX.
 * \param Sy - (\b in) wsp�czynnik skali dla osi \e OY.
 * \param Sz - (\b in) wsp�czynnik skali dla osi \e OZ.
 * \pre �aden ze wsp�czynnik�w skali nie mo�e by� r�wny 0.
 *      Je�eli dla danej osi wcze�niej wsp�czynnik skali by� ustawiony
 *      na warto�� 0, to dla tej osi przeskalowanie nie jest realizowane.
 * \post Pole
 *  \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink
 *  ma warto�� \p true.
 */

/*! \fn  void MatrixH3f::SetScaleX_TAfterR(float Sx)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia now� skal� osi \e OX dla przypadku translacji po rotacji. 
 * \endif
 *
 * Wstawia now� skal� dla osi \e OX przyjmuj�c, �e aktualne wsp�czynniki
 * macierzy przekszta�cenia jednorodnego odpowiadaj� przypadkowi,
 * gdy translacja jest realizowana po rotacji. W takim przypadku
 * operacja nie powoduje zmiany czwartej kolumny macierzy transformacji,
 * kt�ra w tej interpretacji odpowiada bezpo�rednio wektorowi translacji.
 * \param Sx - (\b in) wsp�czynnik skali dla osi \e OX.
 * \pre Wsp�czynnik skali nie mo�e by� r�wny 0.
 *      Je�eli dla danej osi wcze�niej wsp�czynnik skali by� ustawiony
 *      na warto�� 0, to przeskalowanie nie jest realizowane.
 */

/*! \fn void MatrixH3f::SetScaleY_TAfterR(float Sy)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia now� skal� osi \e OY dla przypadku translacji po rotacji. 
 * \endif
 *
 * Wstawia now� skal� dla osi \e OY przyjmuj�c, �e aktualne wsp�czynniki
 * macierzy przekszta�cenia jednorodnego odpowiadaj� przypadkowi,
 * gdy translacja jest realizowana po rotacji. W takim przypadku
 * operacja nie powoduje zmiany czwartej kolumny macierzy transformacji,
 * kt�ra w tej interpretacji odpowiada bezpo�rednio wektorowi translacji.
 * \param Sy - (\b in) wsp�czynnik skali dla osi \e OY.
 * \pre Wsp�czynnik skali nie mo�e by� r�wny 0.
 *      Je�eli dla danej osi wcze�niej wsp�czynnik skali by� ustawiony
 *      na warto�� 0, to przeskalowanie nie jest realizowane.
 */

/*! \fn void MatrixH3f::SetScaleZ_TAfterR(float Sz)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia now� skal� osi \e OZ dla przypadku translacji po rotacji. 
 * \endif
 *
 * Wstawia now� skal� dla osi \e OZ przyjmuj�c, �e aktualne wsp�czynniki
 * macierzy przekszta�cenia jednorodnego odpowiadaj� przypadkowi,
 * gdy translacja jest realizowana po rotacji. W takim przypadku
 * operacja nie powoduje zmiany czwartej kolumny macierzy transformacji,
 * kt�ra w tej interpretacji odpowiada bezpo�rednio wektorowi translacji.
 * \param Sz - (\b in) wsp�czynnik skali dla osi \e OZ.
 * \pre Wsp�czynnik skali nie mo�e by� r�wny 0.
 *      Je�eli dla danej osi wcze�niej wsp�czynnik skali by� ustawiony
 *      na warto�� 0, to przeskalowanie nie jest realizowane.
 */


/*! \fn const Vector3f &MatrixH3f::GetTrans_TBeforeR() const
 * \if matrixh3f_brief_desc 
 *  \brief Udost�pnia wektor translacji dla przypadku translacji przed rotacj�
 * \endif
 *
 * Metoda udost�pnia wektor translacji traktowanej jako translacja
 * przed rotacj�, tzn.
 * \f[
      F = R \circ S \circ T
   \f]
 * Przed udost�pnieniem tych warto�ci metoda dokonuje aktualizacji
 * (o ile jest ona konieczna) warto�ci parametr�w na podstawie
 * warto�ci wsp�czynnik�w macierzy.
 */

/*! \fn void MatrixH3f::SetAng_XYZ_TBeforeR_Rad(const Vector3f &Angles)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia now� rotacj� w reprezentacji \e XYZ dla translacji
 *         przed rotacj�.
 * \endif
 *
 *  Nadaje nowe warto�ci k�tom rotacji danej transformacji
 *  w reprezentacji \e XYZ.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�t�w powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w radianach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = R \circ S \circ T
    \f]
 *  \param Angles - (\b in) wektor warto�ci k�t�w 
 *        odpowiednio \f$\alpha\f$ (rotacja wok� osi \f$ OX\f$).
 *        \f$\beta\f$ (rotacja wok� osi \f$ OY'\f$)
 *       oraz  \f$\gamma\f$ (rotacja wok� osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */


/*! \fn  void MatrixH3f::SetAng_XYZ_TBeforeR_Deg(float Ax, float Ay, float Az)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia now� rotacj� w reprezentacji \e XYZ dla translacji przed
 *         rotacj�.
 * \endif
 *
 *  Nadaje nowe warto�ci k�tom rotacji danej transformacji
 *  w reprezentacji \e XYZ.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�t�w powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w stopniach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = R \circ S \circ T
    \f]
 *  \param Ax - (\b in) warto�� k�ta \f$\alpha\f$ 
 *                     (rotacja wok� osi \f$ OX\f$).
 *  \param Ay - (\b in) warto�� k�ta \f$\beta\f$ 
 *                    (rotacja wok� osi \f$ OY'\f$).
 *  \param Az - (\b in) warto�� k�ta \f$\gamma\f$ 
 *                    (rotacja wok� osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */


/*! \fn void MatrixH3f::SetAng_XYZ_TAfterR_Rad( const Vector3f &Angles )
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia now� rotacj� w reprezentacji \e XYZ dla translacji
 *         po rotacji.
 * \endif
 *
 *  Nadaje nowe warto�ci k�tom rotacji danej transformacji
 *  w reprezentacji \e XYZ.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�t�w powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w radianach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Angles - (\b in) wektor warto�ci k�t�w 
 *        odpowiednio \f$\alpha\f$ (rotacja wok� osi \f$ OX\f$).
 *        \f$\beta\f$ (rotacja wok� osi \f$ OY'\f$)
 *       oraz  \f$\gamma\f$ (rotacja wok� osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */




/*! \fn void MatrixH3f::SetAng_XYZ_TAfterR_Deg( const Vector3f &Angles )
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia now� rotacj� w reprezentacji \e XYZ dla translacji
 *         po rotacji.
 * \endif
 *
 *  Nadaje nowe warto�ci k�tom rotacji danej transformacji
 *  w reprezentacji \e XYZ.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�t�w powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w stopniach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Angles - (\b in) wektor warto�ci k�t�w 
 *        odpowiednio \f$\alpha\f$ (rotacja wok� osi \f$ OX\f$).
 *        \f$\beta\f$ (rotacja wok� osi \f$ OY'\f$)
 *       oraz  \f$\gamma\f$ (rotacja wok� osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */







/*! \fn void MatrixH3f::SetAng_XYZ_TAfterR_Deg(float Ax, float Ay, float Az)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia now� rotacj� w reprezentacji \e XYZ dla translacji
 *         po rotacji.
 * \endif
 *
 *  Nadaje nowe warto�ci k�tom rotacji danej transformacji
 *  w reprezentacji \e XYZ.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�t�w powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w stopniach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Ax - (\b in) warto�� k�ta \f$\alpha\f$ 
 *                     (rotacja wok� osi \f$ OX\f$).
 *  \param Ay - (\b in) warto�� k�ta \f$\beta\f$ 
 *                    (rotacja wok� osi \f$ OY'\f$).
 *  \param Az - (\b in) warto�� k�ta \f$\psi\f$ 
 *                    (rotacja wok� osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */




/*! \fn  void MatrixH3f::SetAng_XYZoX_TAfterR_Deg(float Ax)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy pierwszy k�t rotacji w reprezentacji 
 *         \e XYZ dla translacji po rotacji.
 * \endif
 *
 *  Ustawia nowy pierwszy k�t rotacji w reprezentacji 
 *  \e XYZ dla translacji po rotacji.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�ta powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�� k�ta wyra�ona jest
 *  w stopniach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Ax - (\b in) warto�� k�ta \f$\alpha\f$ 
 *                     (rotacja wok� osi \f$ OX\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */



/*! \fn void MatrixH3f::SetAng_Euler_TBeforeR_Rad(const Vector3f &Angles)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowe k�ty rotacji Eulera
 *         dla translacji przed rotacj�.
 * \endif
 *
 *  Nadaje nowe warto�ci k�tom Eulera danej transformacji.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�t�w powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w radianach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F =  R \circ S \circ T
    \f]
 *  \param Angles - (\b in) wektor warto�ci k�t�w Eulera.
 *      jego kolejne wsp�rz�dne odpowiadaj� k�tom \f$\varphi\f$ 
 *                     (rotacja wok� osi \f$ OZ\f$),
 *     \f$\theta\f$ (rotacja wok� osi \f$ OY'\f$),
 *     \f$\psi\f$   (rotacja wok� osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */


/*! \fn  void MatrixH3f::SetAng_Euler_TBeforeR_Deg(float VPhi, 
                                                    float Theta, float Psi)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowe k�ty rotacji Eulera
 *         dla translacji przed rotacj�.
 * \endif
 *
 *  Nadaje nowe warto�ci k�tom Eulera danej transformacji.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�t�w powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w stopniach. Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F =  R \circ S \circ T
    \f]
 *  \param VPhi - (\b in) warto�� k�ta \f$\varphi\f$ 
 *                     (rotacja wok� osi \f$ OZ\f$).
 *  \param Theta - (\b in) warto�� k�ta \f$\theta\f$ 
 *                    (rotacja wok� osi \f$ OY'\f$).
 *  \param Psi - (\b in) warto�� k�ta \f$\psi\f$ 
 *                    (rotacja wok� osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */



/*!
 * \fn void MatrixH3f::SetAng_XYZoY_TAfterR_Rad(float Ay)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy drugi k�t rotacji w reprezentacji 
 *         \e XYZ dla translacji po rotacji.
 * \endif
 *
 *  Ustawia nowy drugi k�t rotacji w reprezentacji 
 *  \e XYZ dla translacji po rotacji.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�ta powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�� k�ta wyra�ona jest
 *  w radianach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Ay - (\b in) warto�� k�ta \f$\alpha\f$ 
 *                     (rotacja wok� osi \f$ OY'\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */


/*!
 * \fn void MatrixH3f::SetAng_XYZoY_TAfterR_Deg(float Ay)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy drugi k�t rotacji w reprezentacji 
 *         \e XYZ dla translacji po rotacji.
 * \endif
 *
 *  Ustawia nowy drugi k�t rotacji w reprezentacji 
 *  \e XYZ dla translacji po rotacji.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�ta powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�� k�ta wyra�ona jest
 *  w stopniach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Ay - (\b in) warto�� k�ta \f$\alpha\f$ 
 *                     (rotacja wok� osi \f$ OY'\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */


/*! \fn void MatrixH3f::SetAng_XYZoZ_TAfterR_Deg(float Az)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy trzeci k�t rotacji w reprezentacji 
 *         \e XYZ dla translacji po rotacji.
 * \endif
 *
 *  Ustawia nowy trzeci k�t rotacji w reprezentacji 
 *  \e XYZ dla translacji po rotacji.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�ta powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�� k�ta wyra�ona jest
 *  w stopniach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Az - (\b in) warto�� k�ta \f$\alpha\f$ 
 *                     (rotacja wok� osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */


/*! \fn  void MatrixH3f::SetAng_XYZoY_TBeforeR_Deg(float Ay)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy drugi k�t rotacji w reprezentacji 
 *         \e XYZ dla translacji przed rotacj�. 
 * \endif
 *
 *  Nadaje now� warto�� drugiemu k�towi rotacji danej transformacji
 *  w reprezentacji \e XYZ.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�t�w powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w stopniach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = R \circ S \circ T
    \f]
 *  \param Ay - (\b in) warto�� k�ta \f$\alpha\f$ 
 *                     (rotacja wok� osi \f$ OY'\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */



/*!\fn void MatrixH3f::SetAng_XYZoZ_TBeforeR_Deg(float Az)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy trzeci k�t rotacji w reprezentacji 
 *         \e XYZ dla translacji przed rotacj�. 
 * \endif
 *
 *  Nadaje now� warto�� trzeciemu k�towi rotacji danej transformacji
 *  w reprezentacji \e XYZ.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�t�w powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w stopniach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = R \circ S \circ T
    \f]
 *  \param Az - (\b in) warto�� k�ta \f$\alpha\f$ 
 *                     (rotacja wok� osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */



/*! \fn void MatrixH3f::AddAng_XYZ_TBeforeR_Rad( const Vector3f &d_Angles )
 * \if matrixh3f_brief_desc 
 *  \brief Dodaje do k�t�w rotacji w reprezentacji \e XYZ dla translacji
 *         przed rotacj�
 * \endif
 * 
 * Dodaje podane warto�ci do aktalnych warto�ci k�t�w rotacji 
 * w reprezentacji \e XYZ i aktualizuje
 * macierz transformacji. Warto�ci k�t�w wyra�one s� w radianach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = R \circ S \circ T
   \f]
 * \param d_Angles - (\b in) wektor warto�ci k�t�w rotacji w reprezentacji
 *               \e XYZ o kt�re maj� by� zwi�kszone aktualne k�ty rotacji
 *             dla danej transformacji. Kolejne wsp�rz�dne reprezentuj�
 *               odpowiednio \f$\Delta\alpha\f$ (obr�t wok� osi \f$ OX\f$),
 *              \f$\Delta\beta\f$ (obr�t wok� osi \f$ OY'\f$,
 *              \f$\Delta\gamma\f$ (obr�t wok� osi \f$ OZ''\f$).
 * \post Do k�t�w transformacji dodane zostaj� podane warto�ci
 *       oraz zostaje zaaktualizowana macierz wsp�czynnik�w transformacji.
 */


/*! \fn void MatrixH3f::AddAng_XYZ_TBeforeR_Deg( float d_Ax, float d_Ay, 
                                                  float d_Az )
 * \if matrixh3f_brief_desc 
 *  \brief Dodaje do k�t�w rotacji w reprezentacji \e XYZ dla translacji
 *         przed rotacj�
 * \endif
 *
 * Dodaje podane warto�ci do aktalnych warto�ci k�t�w rotacji 
 * w reprezentacji \e XYZ i aktualizuje
 * macierz transformacji. Warto�ci k�t�w wyra�one s� w stopniach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F =  R \circ S  \circ T
   \f]
 * \param d_Ax - (\b in) warto�� o kt�r� ma by� zwi�kszony k�t \f$\alpha\f$
 *               (obr�t wok� osi \f$ OX\f$).
 * \param d_Ay -  (\b in) warto�� o kt�r� ma by� zwi�kszony k�t \f$\beta\f$
 *               (obr�t wok� osi \f$ OY'\f$.
 * \param d_Az -  (\b in) warto�� o kt�r� ma by� zwi�kszony k�t \f$\gamma\f$
 *               (obr�t wok� osi \f$ OZ''\f$).
 * \post Do k�t�w transformacji dodane zostaj� podane warto�ci
 *       oraz zostaje zaaktualizowana macierz wsp�czynnik�w transformacji.
 */



/*! \fn MatrixH3f::SetAng_XYZoX_TBeforeR_Deg(float Ax)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy pierwszy k�t rotacji w reprezentacji 
 *         \e XYZ dla translacji przed rotacj�. 
 * \endif
 *
 *  Nadaje now� warto�� pierwszemu k�towi rotacji danej transformacji
 *  w reprezentacji \e XYZ.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�t�w powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w stopniach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = R \circ S \circ T
    \f]
 *  \param Ax - (\b in) warto�� k�ta \f$\alpha\f$ 
 *                     (rotacja wok� osi \f$ OX\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */



/*! \fn void MatrixH3f::SetAng_Euler_TAfterR_Rad(const Vector3f &Angles)
 * \if matrixh3f_brief_desc
 *  \brief Nadaje nowe warto�ci k�tom Eulera dla transformacji z translacj�
 *         po rotacji.
 * \endif
 *
 *  Nadaje nowe warto�ci k�tom Eulera danej transformacji.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�t�w powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w radianach. Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F =  T \circ R \circ S
    \f]
 *  \param Angles - (\b in) wektor warto�ci k�t�w Eulera.
 *      jego kolejne wsp�rz�dne odpowiadaj� k�tom \f$\varphi\f$ 
 *                     (rotacja wok� osi \f$ OZ\f$),
 *     \f$\theta\f$ (rotacja wok� osi \f$ OY'\f$),
 *     \f$\psi\f$   (rotacja wok� osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */



/*! \fn void MatrixH3f::SetAng_Auto_TAfterR_Rad( const Vector3f &Angles,
                                                 const Vector3f &Scale 
                                               )
 * \if matrixh3f_brief_desc
 *  \brief Nadaje nowe warto�ci k�tom rotacji zachowuj�c dotychczasow�
 *         interpretacj�.
 * \endif
 *
 *  Nadaje nowe warto�ci k�tom rotacji danej transformacji.
 *  Metoda interpretuje k�ty zgodnie z ich wcze�niejsz� interpretacj�,
 *  o kt�rej decyduje warto�� pola 
 *  \link MatrixH3f::_AngInterp _AngInterp\endlink.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�t�w powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w radianach. Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F =  T \circ R \circ S
    \f]
 *  \param Angles - (\b in) wektor warto�ci k�t�w rotacji.
 *              Ich interpretacja zale�y od dotychczasowej warto�ci
 *              pola \link MatrixH3f::_AngInterp _AngInterp\endlink.
 *  \param Scale - (\b in) wektor warto�ci skali dla poszczeg�lnych osi.
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */





/*! \fn void MatrixH3f::SetAng_EulerVPhi_TBeforeR_Deg(float VPhi)
 * \if matrixh3f_brief_desc
 *  \brief Ustawia warto�� k�ta Eulera \f$\varphi\f$ dla transformacji z translacj�
 *         przed rotacj�
 * \endif
 *
 *  Nadaje nowe warto�� k�ta Eulera \f$\varphi\f$ danej transformacji.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie warto�ci k�ta powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w stopniach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F =  R \circ S \circ T
    \f]
 *  \param VPhi - (\b in) warto�� k�ta \f$\varphi\f$ 
 *                     (rotacja wok� osi \f$ OZ\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */


/*! \fn void MatrixH3f::SetAng_EulerTheta_TBeforeR_Rad(float Theta)
 * \if matrixh3f_brief_desc
 *  \brief Ustawia warto�� k�ta Eulera \f$\theta\f$ dla transformacji
 *   z translacj� przed rotacj�
 * \endif
 *
 *  Nadaje nowe warto�� k�ta Eulera \f$\theta\f$ danej transformacji.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie warto�ci k�ta powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w radianach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F =  R \circ S \circ T
    \f]
 *  \param Theta - (\b in) warto�� k�ta \f$\theta\f$ 
 *                     (rotacja wok� osi \f$ OY'\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */

/*! \fn void MatrixH3f::SetAng_EulerTheta_TBeforeR_Deg(float Theta)
 * \if matrixh3f_brief_desc
 *  \brief Ustawia warto�� k�ta Eulera \f$\theta\f$ dla transformacji 
 *   z translacj� przed rotacj�
 * \endif
 *
 *  Nadaje nowe warto�� k�ta Eulera \f$\theta\f$ danej transformacji.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie warto�ci k�ta powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w stopniach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F =  R \circ S \circ T
    \f]
 *  \param Theta - (\b in) warto�� k�ta \f$\theta\f$ 
 *                     (rotacja wok� osi \f$ OY'\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */




/*! \fn void MatrixH3f::SetAng_EulerPsi_TBeforeR_Deg(float Psi)
 * \if matrixh3f_brief_desc
 *  \brief Ustawia warto�� k�ta Eulera \f$\psi\f$ dla transformacji z translacj�
 *         przed rotacj�
 * \endif
 *
 *  Nadaje nowe warto�� k�ta Eulera \f$\psi\f$ danej transformacji.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie warto�ci k�ta powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w stopniach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F =  R \circ S \circ T
    \f]
 *  \param Psi - (\b in) warto�� k�ta \f$\psi\f$ 
 *                     (rotacja wok� osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */


/*! \fn Vectore3f MatrixH3f::GetAng_XYZ_Deg() const 
 * \if matrixh3f_brief_desc 
 * \brief Udost�pnia k�ty w reprezentacji \e XYZ w stopniach.
 * \endif
 *
 * Udost�pnia k�ty obrotu wzgl�dem osi \f$ OX\f$, \f$ OY'\f$ oraz \f$ OZ''\f$
 * dla danej macierzy transformacji.
 * Kolejne wsp�rz�dne wektora odpowiadaj� k�tom
 *  \f$\alpha\f$ (pierwszy obr�t - wok� osi \f$ OX\f$),
 *  \f$\beta\f$ (drugi obr�t - wok� osi \f$ OY'\f$),
 *  \f$\gamma\f$ (trzeci obr�t - wok� osi \f$ OZ''\f$).
 * Udost�pniane warto�ci k�t�w wyra�one s� w stopniach.
 */



//===========================================================================
//..................  MatrixH3f::Parameters  ................................
//...........................................................................

/*! \class MatrixH3f::Parameters
 *  \brief Klasa zawiera parametry transformacji
 *
 * Klasa zawiera parametry transformacji dla macierzy przekszta�cenia
 * we wsp�rz�dnych jednorodnych (k�ty rotacji, wektor translacji i
 * skale wzd�u� osi OX, OY, OZ.
 */


/*! \fn  void MatrixH3f::Parameters::SetAngX_Rad(float ang)
 * \if matrixh3f_brief_desc 
 *  \brief Nadaje now� warto�� pierwszemu k�towi rotacji.
 * \endif
 *
 *  Podstawia now� warto�� k�ta rotacji wzgl�dem osi OX.
 *  K�t wyra�ony musi by� w radianach.  Warto�ci pozosta�ych k�t�w
 *  nie ulegaj� zmianie.
 *  \param ang - nowa warto�� rotacji wzgl�dem osi OX. 
 */



/*! \fn void MatrixH3f::Parameters::SetAng( const Vector3f  &Ang, 
                                            AngleUnit        AngUnit ) 
 * \if matrixh3f_brief_desc 
 *  \brief Nadaje nowe warto�ci k�tom rotacji.
 * \endif
 *
 *  Nadaje nowe warto�ci k�tom rotacji. Warto�ci k�t�w domy�lnie 
 *  wyra�one s� w radianach. Mo�na jednak wyrazi� je w stopniach.
 *  O tym w jakich jednostkach s� wyra�one k�ty decyduje
 *  parametr \e AngUnit.
 *  \param Ang - wektor nowych warto�ci k�t�w rotacji.
 *  \param AngUnit - zawiera informacj� o tym w jakich jednostkach s�
 *                   wyra�one k�ty.
 *  \post Nowe warto�ci k�t�w rotacji zostaj� wpisane do
 *        pola \link MatrixH3f::Parameters::_RotAng _RotAng\endlink.
 */


/*! \var MatrixH3f::Parameters::_AngInterp
 *  \brief Reprezentacja k�t�w rotacji
 *
 *  Okre�la czy warto�ci k�t�w rotacji w polu  
 *  \link Parameters::_RotAng  _RotAng\endlink nale�y interpretowa� jako
 *  k�ty Eulera (warto�� \p AT_Euler) czy te� jako k�ty obrotu 
 *  wzgl�dem osi OX, OY i OZ (warto�� \p AT_xyz).
 */

/*! \var MatrixH3f::Parameters::_TransOrder
 *
 *  \brief Porz�dek translacji wzgl�dem rotacji
 *
 * Warto�� pola okre�la czy parametry transformacji 
 * \link MatrixH3f::_Trans _Trans\endlink
 * odpowiada translacji po rotacji (\p true),
 * czy te� przed (\p false).
 */

/*! \var MatrixH3f::Parameters::_RotAng
 *  \brief K�ty rotacji
 *
 *  Kolejne wsp�rz�dne wektora zawieraj� warto�ci k�t�w rotacji 
 *  wzgl�dem osi OX, OY i OZ lub te� k�ty Eulera.
 *  Warto�ci k�t�w wyra�one s� w radianach.
 *
 *  Je�eli przyj�ta jest reprezentacja za pomoc� k�t�w Eulera,
 *  to kolejne wsp�rz�dne wektora zawieraj� k�ty:
 *  \f$ \varphi \f$ (obr�t wok� osi \f$ OZ\f$), \f$ \theta\f$
 *  (obr�t wok� chwilowej osi \f$ OY'\f$) oraz \f$\psi\f$
 *  (obr�t wok� chwilowej osi \f$ OZ''\f$).
 */

/*! \var MatrixH3f::Parameters::_Trans
 *  \brief  Wektor translacji.
 *
 *  Pole zawiera wektor translacji pocz�tku uk�adu wsp�rz�dnych.
 */

/*! \var MatrixH3f::Parameters::_Scale
 *  \brief Skala dla poszczeg�lnych osi \e OX, \e OY oraz \e OZ
 *
 *  Kolejne wsp�rz�dne wektora zawieraj� warto�ci wsp�czynnik�w
 *  skali dla poszczeg�lnych osi.
 */


/*! \fn void MatrixH3f::SetScale_TBeforeR(float Sx, float Sy, float Sz)
 * \brief Ustawia now� skal� dla przypadku translacji po rotacji.
 *
 * Ustawia now� skal� przyjmuj�c, �e aktualne wsp�czynniki
 * macierzy przekszta�cenia jednorodnego odpowiadaj� przypadkowi,
 * gdy translacja jest realizowana przed rotacj�. W takim przypadku
 * operacja nie powoduje zmiany czwartej kolumny macierzy transformacji,
 * kt�ra w tej interpretacji odpowiada bezpo�rednio wektorowi translacji.
 * \param Sx - (\b in) wsp�czynnik skali osi \e OX.
 * \param Sy - (\b in) wsp�czynnik skali osi \e OY.
 * \param Sz - (\b in) wsp�czynnik skali osi \e OZ.
 * \pre �aden ze wsp�czynnik�w skali nie mo�e by� r�wny 0.
 *      Je�eli dla danej osi wcze�niej wsp�czynnik skali by� ustawiony
 *      na warto�� 0, to dla tej osi przeskalowanie nie jest realizowane.
 * \post Pole
 *  \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink
 *  ma warto�� \p true.
 */



//--------------- MatrixH3f::Parameters ---------------------------------
//------ Metody publiczne: ..............................................

/*! \fn void MatrixH3f::Parameters::SetTrans(float x, float y, float z)
 *  Nadaje nowe wsp�rz�dnym wektora translacji.
 *  \param x - nowa warto�� wsp�rz�dnej \e x wektora translacji,
 *  \param y - nowa warto�� wsp�rz�dnej \e y wektora translacji,
 *  \param z - nowa warto�� wsp�rz�dnej \e z wektora translacji.
 *  \post Nowe warto�ci wsp�czynnik�w skali zostaj� wpisane do
 *        pola \link MatrixH3f::Parameters::_Trans _Trans\endlink.
 */

/*! \fn void MatrixH3f::Parameters::SetAngInterp(AnglesType ATyp)
 *  \brief Ustawia spos�b interpretacji k�t�w rotacji.
 *
 * Ustawia spos�b interpretacji k�t�w rotacji.
 * \param ATyp - nowa wartosc dla pola 
 * \link Parameters::_AngInterp _AngInterp\endlink informuj�ca o sposobie
 *  interpretacji k�t�w rotacji.
 * \post Zostaje zmodyfikowna warto�� pola 
 *  \link Parameters::_AngInterp _AngInterp\endlink.
 */

/*! \fn AnglesType MatrixH3f::Parameters::GetAngInterp() const
 *  \brief Udost�pnia typ reprezentacji k�t�w rotacji. 
 *
 * Udost�pnia warto�� pola \link Parameters::_AngInterp _AngInterp\endlink
 * informuj�c� o sposobie interpretacji k�t�w rotacji, kt�re zapisane
 * s� w polu \link Parameters::_RotAng _RotAng\endlink.
 */

/*! \fn Parameters &MatrixH3f::Parameters::SetTransType(TransOrder TOrder)
 * \brief Ustawia interpretacj� kolejno�ci translacji wzgl�dem rotacji.
 *
 * Wprowadza i zapami�tuje informacj� o kolejno�ci wykonania translacji, tzn.
 * czy wykonana zosta�a przed rotacj�, czy te� po.
 * \param TOrder - informacja o kolejno�ci wykonania translacji wzgl�dem rotacji.
 */


/*! \fn void MatrixH3f::Parameters::SetAng_Rad( float ax_rad, float ay_rad,
                                                                   float az_rad )
 *  \brief Nadaje nowe warto�ci k�tom rotacji
 *
 *  Nadaje nowe warto�ci k�tom rotacji. Warto�ci k�t�w 
 *  wyra�one s� w radianach.
 *  \param ax_rad - nowa warto�� pierwszego k�ta rotacji,
 *  \param ay_rad - nowa warto�� drugiego k�ta rotacji,
 *  \param az_rad - nowa warto�� trzeciego k�ta rotacji.
 *  \post Nowe warto�ci k�t�w rotacji zostaj� wpisane do
 *        pola \link MatrixH3f::Parameters::_RotAng _RotAng\endlink.
 */

/*! \fn void MatrixH3f::Parameters::SetAng( float ax, float ay, float az, 
                                                           AngleUnit AngUnit )
 *  \brief Nadaje nowe warto�ci k�t�w rotacji.
 *
 *  Nadaje nowe warto�ci k�t�w rotacji. Warto�ci k�t�w domy�lnie 
 *  wyra�one s� w radianach. Mo�na jednak wyrazi� je w stopniach.
 *  O tym w jakich jednostkach s� wyra�one k�ty decyduje
 *  parametr \e AngUnit.
 *  \param ax - nowa warto�� pierwszego k�ta rotacji,
 *  \param ay - nowa warto�� drugiego k�ta rotacji,
 *  \param az - nowa warto�� trzeciego k�ta rotacji.
 *  \param AngUnit - zawiera informacj� o tym w jakich jednostkach s�
 *                   wyra�one k�ty.
 *  \post Nowe warto�ci k�t�w rotacji zostaj� wpisane do
 *        pola \link MatrixH3f::Parameters::_RotAng _RotAng\endlink.
 */




namespace Vi {
  /*!
   *  Funkcja zwraca nazw� odpowiadaj�c� danej warto�ci typu
   *  \link matrixh3f.hh::TransOrder TransOrder\endlink.
   */
  const char *MakeString(TransOrder Val)
  {
    switch (Val) {
     case TO_Before: return KW__TO_BEFORE;
     case TO_After:  return KW__TO_AFTER;
    }
  }


  /*!
   *  Funkcja dokonuje konwersji nazwy warto�ci typu 
   * \link matrixh3f.hh::TransOrder TransOrder\endlink na warto�� 
   * tego typu.\n
   * Zestaw dopuszczalnych nazw zdefiniowany jest poprzez sta�e:
   *  \li \link vi-kewords.hh::KW__TO_BEFORE KW__TO_BEFORE\endlink
   *  \li \link vi-kewords.hh::KW__TO_AFTER KW__TO_AFTER\endlink
   * \param Name - nazwa warto�ci typu  
   *               \link matrixh3f.hh::TransOrder TransOrder\endlink
   * \exception ViException z kodem b��du \link
   *                 vierrors.hh::ERRNUM_TRANSORDER__IMPROPER_NAME
   *                 ERRNUM_TRANSORDER__IMPROPER_NAME\endlink
   *            w przypadku, gdy nazwa nie odpowiada �adnej z oczekiwanych
   *            nazw.
   */
  TransOrder String2TransOrder(const char *Name) throw(Ba::Exception)
  {
    if (!strcmp(Name,KW__TO_AFTER)) return TO_After;
    else if (!strcmp(Name,KW__TO_BEFORE)) return TO_Before;
    else throw Ba::Exception(ERRNUM_TRANSORDER__IMPROPER_NAME,
         (MSG(ERRMSG_TRANSORDER__IMPROPER_NAME),
	  Name,
         KW__TO_BEFORE", "KW__TO_AFTER"."));
  }
}








inline 
void AddAngle(float &Angle, float dA)
{
  Angle += dA;
  while (Angle >  2*M_PI) { Angle -= 2*M_PI; }
  while (Angle < -2*M_PI) { Angle += 2*M_PI; }
}



inline 
void AddAngle(Vector3f &Angle, Vector3f const &dA)
{
  AddAngle(Angle.X(),dA.X());
  AddAngle(Angle.Y(),dA.Y());
  AddAngle(Angle.Z(),dA.Z());
}


#define D_VERYSMALLPLUS  0.00001
/*!
 *  Sprawdza czy dana warto�� jest wi�ksza lub mniejsza od warto�ci 
 *  \link matrixh3f.cpp::D_VERYSMALLPLUS D_VERYSMALLPLUS\endlink.
 *  Je�eli nie, to podstawia warto��
 *  \link matrixh3f.cpp::D_VERYSMALLPLUS D_VERYSMALLPLUS\endlink.
 */
float MakeDT_0(float Val)
{
  return Val > D_VERYSMALLPLUS ? Val : 
         Val < -D_VERYSMALLPLUS ? Val : D_VERYSMALLPLUS;
}


/*!
 *  Powoduje, �e ka�da wsp�rz�dna wektora b�dzie wi�ksza 
 *  od \link matrixh3f.cpp::D_VERYSMALLPLUS D_VERYSMALLPLUS\endlink.
 */
Vector3f MakeDT_0(const Vector3f &V)
{
  return Vector3f(MakeDT_0(V.x),MakeDT_0(V.y),MakeDT_0(V.z));
}



std::ostream &operator << ( std::ostream                &ostr, 
                            MatrixH3f::AnglesType const &Val 
                          )
{
  switch (Val) {
   case MatrixH3f::AT_xyz:   ostr << "AT_xyz";    break;
   case MatrixH3f::AT_Euler: ostr << "AT_Euler";  break;
  }  
}



std::ostream &operator << ( std::ostream                &ostr, 
                            MatrixH3f::Parameters const &Param 
                          )
{
  ostr << std::endl;
  ostr << " -----------------------------" << std::endl;
  Vector3f  Ang(Param.GetAng1_Deg(),Param.GetAng2_Deg(),Param.GetAng2_Deg());

  ostr << "   Ang Type: " << Param.GetAngInterp() << endl;
  ostr << "   RotAn: " << Ang << endl;
  ostr << "   Trans: " << Param.GetTrans() << endl;
  ostr << "   Scale: " << Param.GetScale() << endl;
  ostr << " -----------------------------" << std::endl;
  return ostr;
}





//###########################################################################
//........................... MatrixH3f .....................................



/*!
 *  Aktualizuje zawarto�� pola 
 *  \link MatrixH3f::_Trans  _Trans\endlink traktuj�c wektor translacji
 *  jako translacj� po rotacji.
 *  \post Pole  \link MatrixH3f::_Trans  _Trans\endlink
 *    zwiera aktualn� warto�� wektora translacji wyliczonego
 *    na podstawie wsp�czynnik�w macierzy transformacji.
 *    Wektor translacji traktowany jest jako translacja po
 *    rotacji, tzn.
 * \f[
     F = R \circ S \circ T
   \f]
 *    Ponadto pola
 *    \link MatrixH3f::_Valid_Trans _Valid_Trans\endlink
 *     oraz 
 *    \link MatrixH3f::_Trans_Order _Trans_Order\endlink
 *    maj� warto�� \p TO_After.
 */
void MatrixH3f::UpdateParam_Trans_TAfterR()
{
  if ((_Trans_Order == TO_After) && _Valid_Trans)  return;
  MatrixRT3f::GetTrans_TAfterR(_Trans);
  ValidParam_Trans_TAfterR();
}


/*!
 *  Aktualizuje zawarto�� pola 
 *  \link MatrixH3f::_Trans  _Trans\endlink traktuj�c wektor translacji
 *  jako translacj� po rotacji.
 *  \post Pole  \link MatrixH3f::_Trans  _Trans\endlink
 *    zwiera aktualn� warto�� wektora translacji wyliczonego
 *    na podstawie wsp�czynnik�w macierzy transformacji.
 *    Wektor translacji traktowany jest jako translacja przed
 *    skalowaniem i rotacj�, tzn.
 * \f[
       F = T \circ R \circ S
   \f]
 * Ponadto pola
 *    \link MatrixH3f::_Valid_Trans _Valid_Trans\endlink
 *     oraz 
 *    \link MatrixH3f::_Trans_Order _Trans_Order\endlink
 *    maj� warto�� \p TO_Before.
 */
void MatrixH3f::UpdateParam_Trans_TBeforeR()
{
  if ((_Trans_Order == TO_Before) && _Valid_Trans)  return;
  MatrixRT3f::GetTrans_TBeforeR(_Trans);
  ValidParam_Trans_TBeforeR();
}



/*!
 *  \brief Udost�pnia wektor translacji dla przypadku translacji po rotacji
 *
 * Metoda udost�pnia wektor translacji traktowanej jako translacja
 * po rotacji, tzn.
 * \f[
       F = T \circ R \circ S
   \f]
 * Przed udost�pnieniem tych warto�ci metoda dokonuje aktualizacji
 * (o ile jest ona konieczna) warto�ci parametr�w na podstawie
 * warto�ci wsp�czynnik�w macierzy.
 */
const Vector3f &MatrixH3f::GetTrans_TAfterR() const
{
  USE(MatrixH3f).UpdateParam_Trans_TAfterR();
  return _Trans;
}




/*!
 * Nadaje now� warto�� wektorowi translacji.
 * Zak�ada si�, �e translacja ma by� wykonana przed skalowaniem i rotacj�,
 *  tzn.
 *  \f[
        F = R \circ S \circ T
    \f]
 * \param Tx - nowa warto�� wsp�rz�dnej \e x-owej wektora translacji.
 * \param Ty - nowa warto�� wsp�rz�dnej \e y-owej wektora translacji.
 * \param Tz - nowa warto�� wsp�rz�dnej \e z-owej wektora translacji.
 * \post Do pola \link MatrixH3f::_Trans _Trans\endlink zostaje wpisany
 *       nowy wektor translacji przekazany przez parametr \e T.
 *       Wpisany zostaje on r�wnie� do 4 kolumny macierzy wsp�czynnik�w
 *       transformacji (patrz opis pola 
 *       \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink)
 *       zachowuj�c aktualno��
 *       wylicze� wp�czynnik�w tej macierzy.
 *       
 *       Dzia�anie metody powoduje przypisanie polom 
 *    \link MatrixH3f::_Valid_Trans  MatrixH3f::_Valid_Trans\endlink
 *    oraz 
 *    \link MatrixH3f::_Trans_Order MatrixH3f::_Trans_Order \endlink
 *    warto�ci \p TO_Before.
 */
void  MatrixH3f::SetTrans_TBeforeR(float Tx, float Ty, float Tz)
{ 
  _Trans.Set(Tx,Ty,Tz); 
  MatrixRT3f::SetTrans_TBeforeR(Tx,Ty,Tz);
  ValidParam_Trans_TBeforeR();
}



/*!
 * Nadaje now� warto�� wektorowi translacji
 * Zak�ada si�, �e translacja ma by� wykonana po skalowanii i rotacji,
 *  tzn.
 *  \f[
          F = T \circ R \circ S
    \f]
 * \param T - nowa warto�� wektora translacji.
 * \post Do pola \link MatrixH3f::_Trans _Trans\endlink zostaje wpisany
 *       nowy wektor translacji przekazany przez parametr \e T.
 *       Wpisany zostaje on r�wnie� do 4 kolumny macierzy wsp�czynnik�w
 *       transformacji (patrz opis pola 
 *       \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink)
 *       zachowuj�c aktualno��
 *       wylicze� wp�czynnik�w tej macierzy.
 *       
 *       Dzia�anie metody powoduje przypisanie polom 
 *    \link MatrixH3f::_Valid_Trans  MatrixH3f::_Valid_Trans\endlink
 *    oraz 
 *    \link MatrixH3f::_Trans_Order MatrixH3f::_Trans_Order \endlink
 *    warto�ci \p TO_After.
 */
void MatrixH3f::SetTrans_TAfterR(Vector3f const &T)
{
  MatrixRT3f::SetTrans_TAfterR(_Trans = T);
  ValidParam_Trans_TAfterR();
}


/*!
 * Nadaje now� warto�� \e x-owej wsp�rz�dnej wektora translacji.
 * \param Tx - nowa warto�� \e x-owej wsp�rz�dnej wektora translacji.
 * \post Do pola \link MatrixH3f::_Trans _Trans\endlink 
 *       w miejsce \e x-owej wsp�rz�dnej zostaje wpisany
 *       nowa warto�� przekazana przez parametr \e Tx.
 *       Zostaje ona wpisana r�wnie� do odpowiedniego elementu
 *       4 kolumny macierzy wsp�czynnik�w
 *       transformacji (patrz opis pola 
 *       \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink)
 *       zachowuj�c aktualno��
 *       wylicze� wp�czynnik�w tej macierzy.
 *       
 *       Dzia�anie metody powoduje przypisanie polom 
 *    \link MatrixH3f::_Valid_Trans  MatrixH3f::_Valid_Trans\endlink
 *    oraz 
 *    \link MatrixH3f::_Trans_Order MatrixH3f::_Trans_Order \endlink
 *    warto�ci \p TO_After.
 */
void MatrixH3f::SetTransX_TAfterR(float Tx)
{
  UpdateParam_Trans_TAfterR();
  _Trans.x = Tx;
  MatrixRT3f::SetTrans_TAfterR(_Trans);
  ValidParam_Trans_TAfterR();
}


/*!
 * Nadaje now� warto�� \e y-owej wsp�rz�dnej wektora translacji.
 * \param Ty - nowa warto�� \e y-owej wsp�rz�dnej wektora translacji.
 * \post Do pola \link MatrixH3f::_Trans _Trans\endlink 
 *       w miejsce \e y-owej wsp�rz�dnej zostaje wpisany
 *       nowa warto�� przekazana przez parametr \e Ty.
 *       Zostaje ona wpisana r�wnie� do odpowiedniego elementu
 *       4 kolumny macierzy wsp�czynnik�w
 *       transformacji (patrz opis pola 
 *       \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink)
 *       zachowuj�c aktualno��
 *       wylicze� wp�czynnik�w tej macierzy.
 *       
 *       Dzia�anie metody powoduje przypisanie polom 
 *    \link MatrixH3f::_Valid_Trans  MatrixH3f::_Valid_Trans\endlink
 *    oraz 
 *    \link MatrixH3f::_Trans_Order MatrixH3f::_Trans_Order \endlink
 *    warto�ci \p TO_After.
 */
void MatrixH3f::SetTransY_TAfterR(float Ty)
{
  UpdateParam_Trans_TAfterR();
  _Trans.y = Ty;
  MatrixRT3f::SetTrans_TAfterR(_Trans);
  ValidParam_Trans_TAfterR();
}


/*!
 * Nadaje now� warto�� \e z-owej wsp�rz�dnej wektora translacji.
 * \param Tz - nowa warto�� \e z-owej wsp�rz�dnej wektora translacji.
 * \post Do pola \link MatrixH3f::_Trans _Trans\endlink 
 *       w miejsce \e z-owej wsp�rz�dnej zostaje wpisany
 *       nowa warto�� przekazana przez parametr \e Tz.
 *       Zostaje ona wpisana r�wnie� do odpowiedniego elementu
 *       4 kolumny macierzy wsp�czynnik�w
 *       transformacji (patrz opis pola 
 *       \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink)
 *       zachowuj�c aktualno��
 *       wylicze� wp�czynnik�w tej macierzy.
 *       
 *       Dzia�anie metody powoduje przypisanie polom 
 *    \link MatrixH3f::_Valid_Trans  MatrixH3f::_Valid_Trans\endlink
 *    oraz 
 *    \link MatrixH3f::_Trans_Order MatrixH3f::_Trans_Order \endlink
 *    warto�ci \p TO_After.
 */
void MatrixH3f::SetTransZ_TAfterR(float Tz)
{
  UpdateParam_Trans_TAfterR();
  _Trans.z = Tz;
  MatrixRT3f::SetTrans_TAfterR(_Trans);
  ValidParam_Trans_TAfterR();
}



/*!
 * Dodaje przekazany przez parametr wektor do wektora translacji,
 *  kt�ry traktowany jest
 * jako translacja przed skalowaniem i rotacj�, tzn.
 * \f[
      F = R \circ S \circ T
   \f]
 * \param dT - (\b in) dodawany wektor.
 * \post Suma wektora translacji pochodz�cego bezpo�renio z 4 kolumny 
 *       macierzy wsp�czynnik�w transformacji 
 *       (patrz opis pola 
 *       \link MatrixRT3f::_DH _DH\endlink) oraz parametru \e dT
 *       wpisana zostaje
 *       do 4 kolumny macierzy wsp�czynnik�w.
 */
void MatrixH3f::AddTrans_TBeforeR(const Vector3f &dT)
{ 
  UpdateParam_Trans_TBeforeR();
  MatrixRT3f::SetTrans_TBeforeR(_Trans += dT);
}



/*!
 * Dodaje przekazan� warto�� do \e x-owej sk�adowej wektora translacji,
 *  kt�ry traktowany jest
 * jako translacja przed skalowaniem i rotacj�, tzn.
 * \f[
      F = R \circ S \circ T
   \f]
 * \param d_Tx - (\b in) dodawany wektor.
 * \post Suma wektora translacji pochodz�cego bezpo�renio z 4 kolumny 
 *       macierzy wsp�czynnik�w transformacji 
 *       (patrz opis pola 
 *       \link MatrixRT3f::_DH _DH\endlink) oraz parametru \e dT
 *       wpisana zostaje
 *       do 4 kolumny macierzy wsp�czynnik�w.
 */
void MatrixH3f::AddTransX_TBeforeR(float d_Tx)
{ 
  UpdateParam_Trans_TBeforeR();
  MatrixRT3f::SetTrans_TBeforeR(_Trans.x += d_Tx, _Trans.y, _Trans.z);
}



/*!
 * Dodaje przekazan� warto�� do \e y-owej sk�adowej wektora translacji,
 *  kt�ry traktowany jest
 * jako translacja przed skalowaniem i rotacj�, tzn.
 * \f[
      F = R \circ S \circ T
   \f]
 * \param d_Ty - (\b in) dodawany wektor.
 * \post Suma wektora translacji pochodz�cego bezpo�renio z 4 kolumny 
 *       macierzy wsp�czynnik�w transformacji 
 *       (patrz opis pola 
 *       \link MatrixRT3f::_DH _DH\endlink) oraz parametru \e dT
 *       wpisana zostaje
 *       do 4 kolumny macierzy wsp�czynnik�w.
 */
void MatrixH3f::AddTransY_TBeforeR(float d_Ty)
{ 
  UpdateParam_Trans_TBeforeR();
  MatrixRT3f::SetTrans_TBeforeR(_Trans.x, _Trans.y += d_Ty, _Trans.z);
}


/*!
 * Dodaje przekazan� warto�� do \e z-owej sk�adowej wektora translacji,
 *  kt�ry traktowany jest
 * jako translacja przed skalowaniem i rotacj�, tzn.
 * \f[
      F = R \circ S \circ T
   \f]
 * \param d_Tz - (\b in) dodawany wektor.
 * \post Suma wektora translacji pochodz�cego bezpo�renio z 4 kolumny 
 *       macierzy wsp�czynnik�w transformacji 
 *       (patrz opis pola 
 *       \link MatrixRT3f::_DH _DH\endlink) oraz parametru \e dT
 *       wpisana zostaje
 *       do 4 kolumny macierzy wsp�czynnik�w.
 */
void MatrixH3f::AddTransZ_TBeforeR(float d_Tz)
{ 
  UpdateParam_Trans_TBeforeR();
  MatrixRT3f::SetTrans_TBeforeR(_Trans.x, _Trans.y, _Trans.z += d_Tz);
}





/*!
 * Dodaje przekazany przez parametr wektor do wektora translacji,
 *  kt�ry traktowany jest
 * jako translacja po rotacji, tzn.
 * \f[
      F = T \circ R \circ S
   \f]
 * \param dT - dodawany wektor.
 * \post Suma wektora translacji pochodz�cego bezpo�renio z 4 kolumny 
 *       macierzy wsp�czynnik�w transformacji 
 *       (patrz opis pola 
 *       \link MatrixRT3f::_DH _DH\endlink) oraz parametru \e dT
 *       wpisana zostaje
 *       do 4 kolumny macierzy wsp�czynnik�w.
 */
void MatrixH3f::AddTrans_TAfterR(const Vector3f &dT)
{ 
  MatrixRT3f::AddTrans_TAfterR(dT);
  InvalidParam_Trans();
}

/*!
 * Dodaje do \e x-owej wsp�rz�dnej wektora translacji traktowanego 
 * jako translacja po rotacji, podany warto��.
 * \param Tx - dodawana warto�� \e x-owej wsp�rz�dnej wektora translacji.
 * \post Do pola \link MatrixH3f::_Trans _Trans\endlink zostaje wpisana
 *       suma wektora translacji pochodz�cego bezpo�renio z 4 kolumny 
 *       macierzy wsp�czynnik�w transformacji 
 *       Nowa wyliczona warto�� zostaje wpisana
 *       do odpowiedniego elementu 
 *       4 kolumny macierzy wsp�czynnik�w transformacji.
 *       (patrz opis pola 
 *       \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink).
 *       
 *       Dzia�anie metody powoduje wypisanie warto�ci \p false
 *       do pola 
 *        \link MatrixH3f::_Valid_Trans _Valid_Trans\endlink.
 */
void MatrixH3f::AddTransX_TAfterR(float Tx)
{ 
  MatrixRT3f::AddTrans_TAfterR(Vector3f(Tx,0,0));
  InvalidParam_Trans();
}

/*!
 * Dodaje do \e y-owej wsp�rz�dnej wektora translacji traktowanego 
 * jako translacja po rotacji, podany warto��.
 * \param Ty - dodawana warto�� \e y-owej wsp�rz�dnej wektora translacji.
 * \post Do pola \link MatrixH3f::_Trans _Trans\endlink zostaje wpisana
 *       suma wektora translacji pochodz�cego bezpo�renio z 4 kolumny 
 *       macierzy wsp�czynnik�w transformacji 
 *       Nowa wyliczona warto�� zostaje wpisana
 *       do odpowiedniego elementu 
 *       4 kolumny macierzy wsp�czynnik�w transformacji.
 *       (patrz opis pola 
 *       \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink).
 *       
 *       Dzia�anie metody powoduje wypisanie warto�ci \p false
 *       do pola 
 *        \link MatrixH3f::_Valid_Trans _Valid_Trans\endlink.
 */
void MatrixH3f::AddTransY_TAfterR(float Ty)
{ 
  MatrixRT3f::AddTrans_TAfterR(Vector3f(0,Ty,0));
  InvalidParam_Trans();
}

/*!
 * Dodaje do \e z-owej wsp�rz�dnej wektora translacji traktowanego 
 * jako translacja po rotacji, podany warto��.
 * \param Tz - dodawana warto�� \e z-owej wsp�rz�dnej wektora translacji.
 * \post Do pola \link MatrixH3f::_Trans _Trans\endlink zostaje wpisana
 *       suma wektora translacji pochodz�cego bezpo�renio z 4 kolumny 
 *       macierzy wsp�czynnik�w transformacji 
 *       Nowa wyliczona warto�� zostaje wpisana
 *       do odpowiedniego elementu 
 *       4 kolumny macierzy wsp�czynnik�w transformacji.
 *       (patrz opis pola 
 *       \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink).
 *       
 *       Dzia�anie metody powoduje wypisanie warto�ci \p false
 *       do pola 
 *        \link MatrixH3f::_Valid_Trans _Valid_Trans\endlink.
 */
void MatrixH3f::AddTransZ_TAfterR(float Tz)
{ 
  MatrixRT3f::AddTrans_TAfterR(Vector3f(0,0,Tz));
  InvalidParam_Trans();
}



/*!
 * \brief Udost�pnia wektor skali dla osi \e OX, \e OY, \e OZ.
 *
 * Metoda udost�pnia wektor skali wzgl�dem poszczeg�lnych osi
 * (warto�� pola \link MatrixH3f::_Scale _Scale\endlink).
 * Je�eli jest to konieczne, to aktualizuje jego zawarto��,
 * tak aby dopowiada�a ona warto�ci wynikaj�cej ze wsp�czynnik�w
 * macierzy transformacji.
 * \return referencj� do pola  \link MatrixH3f::_Scale _Scale\endlink
 *         zawieraj�cego wektor wsp�czynnik�w skali.
 * \post Pole 
 *   \link MatrixH3f::_Valid_Scale  MatrixH3f::_Valid_Scale\endlink
 *   ma warto�� \p true.
 *
 * Uwaga: Pobieranie wsp�czynnik�w skali nie zale�y od
 *        kolejno�ci wykonanej translacji.
 */
const Vector3f &MatrixH3f::GetScale() const
{
  USE(MatrixH3f).UpdateParam_Scale();
  return _Scale;
}



/*!
 * \brief Ustawia now� skal� dla przypadku translacji po rotacji.
 *
 * Ustawia now� skal� przyjmuj�c, �e aktualne wsp�czynniki
 * macierzy przekszta�cenia jednorodnego odpowiadaj� przypadkowi,
 * gdy translacja jest realizowana przed rotacj�. W takim przypadku
 * operacja nie powoduje zmiany czwartej kolumny macierzy transformacji,
 * kt�ra w tej interpretacji odpowiada bezpo�rednio wektorowi translacji.
 * \param Scale - (\b in) wektor nowych wsp�czynnik�w skali wzgl�dem 
 *               poszczeg�lnych
 *               osi, tzn. \e OX, \e OY, \e OZ.
 * \pre �aden ze wsp�czynnik�w skali nie mo�e by� r�wny 0.
 *      Je�eli dla danej osi wcze�niej wsp�czynnik skali by� ustawiony
 *      na warto�� 0, to dla tej osi przeskalowanie nie jest realizowane.
 * \post Pole
 *  \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink
 *  ma warto�� \p true.
 */
void MatrixH3f::SetScale_TBeforeR(const Vector3f &Scale)
{
  Vector3f  S = MakeDT_0(Scale);
  UpdateParam_Scale_XYZ_Angles();
  UpdateParam_Trans_TBeforeR();
  S.Set(1,1,1);
  MatrixRT3f::SetMatrix_XYZ_TBeforeR_Rad(_RotAng,_Trans,_Scale = S);
}


/*!
 * \brief Ustawia wsp�czynnik skali osi \e OX dla przypadku translacji po rotacji.
 *
 * Ustawia nowy wsp�czynnik skali osi \e OX
 * przyjmuj�c, �e aktualne wsp�czynniki
 * macierzy przekszta�cenia jednorodnego odpowiadaj� przypadkowi,
 * gdy translacja jest realizowana przed rotacj�. W takim przypadku
 * operacja nie powoduje zmiany czwartej kolumny macierzy transformacji,
 * kt�ra w tej interpretacji odpowiada bezpo�rednio wektorowi translacji.
 * \param Sx - (\b in) wsp�czynnik skali osi \e OX.
 * \pre �aden ze wsp�czynnik�w skali nie mo�e by� r�wny 0.
 *      Je�eli dla danej osi wcze�niej wsp�czynnik skali by� ustawiony
 *      na warto�� 0, to dla tej osi przeskalowanie nie jest realizowane.
 * \post Pole
 *  \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink
 *  ma warto�� \p true.
 */
void MatrixH3f::SetScaleX_TBeforeR(float Sx)
{
  UpdateParam_Scale_Euler_Angles();
  _Scale.x = MakeDT_0(Sx);
  UpdateParam_Trans_TBeforeR();
  MatrixRT3f::SetMatrix_Euler_TBeforeR_Rad(_RotAng,_Trans,_Scale);
}


/*!
 * \brief Ustawia wsp�czynnik skali osi \e OY dla przypadku translacji po rotacji.
 *
 * Ustawia nowy wsp�czynnik skali osi \e OY
 * przyjmuj�c, �e aktualne wsp�czynniki
 * macierzy przekszta�cenia jednorodnego odpowiadaj� przypadkowi,
 * gdy translacja jest realizowana przed rotacj�. W takim przypadku
 * operacja nie powoduje zmiany czwartej kolumny macierzy transformacji,
 * kt�ra w tej interpretacji odpowiada bezpo�rednio wektorowi translacji.
 * \param Sy - (\b in) wsp�czynnik skali osi \e OY.
 * \pre �aden ze wsp�czynnik�w skali nie mo�e by� r�wny 0.
 *      Je�eli dla danej osi wcze�niej wsp�czynnik skali by� ustawiony
 *      na warto�� 0, to dla tej osi przeskalowanie nie jest realizowane.
 * \post Pole
 *  \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink
 *  ma warto�� \p true.
 */
void MatrixH3f::SetScaleY_TBeforeR(float Sy)
{
  UpdateParam_Scale_Euler_Angles();
  _Scale.y = MakeDT_0(Sy);
  UpdateParam_Trans_TBeforeR();
  MatrixRT3f::SetMatrix_Euler_TBeforeR_Rad(_RotAng,_Trans,_Scale);
}



/*!
 * \brief Ustawia wsp�czynnik skali osi \e OZ dla przypadku translacji 
 *        po rotacji.
 *
 * Ustawia nowy wsp�czynnik skali osi \e OZ
 * przyjmuj�c, �e aktualne wsp�czynniki
 * macierzy przekszta�cenia jednorodnego odpowiadaj� przypadkowi,
 * gdy translacja jest realizowana przed rotacj�. W takim przypadku
 * operacja nie powoduje zmiany czwartej kolumny macierzy transformacji,
 * kt�ra w tej interpretacji odpowiada bezpo�rednio wektorowi translacji.
 * \param Sz - (\b in) wsp�czynnik skali osi \e OZ.
 * \pre �aden ze wsp�czynnik�w skali nie mo�e by� r�wny 0.
 *      Je�eli dla danej osi wcze�niej wsp�czynnik skali by� ustawiony
 *      na warto�� 0, to dla tej osi przeskalowanie nie jest realizowane.
 * \post Pole
 *  \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink
 *  ma warto�� \p true.
 */
void MatrixH3f::SetScaleZ_TBeforeR(float Sz)
{
  UpdateParam_Scale_Euler_Angles();
  _Scale.z = MakeDT_0(Sz);
  UpdateParam_Trans_TBeforeR();
  MatrixRT3f::SetMatrix_Euler_TBeforeR_Rad(_RotAng,_Trans,_Scale);
}




/*!
 * \brief Ustawia now� skal� dla przypadku translacji po rotacji.
 *
 * Ustawia now� skal� przyjmuj�c, �e aktualne wsp�czynniki
 * macierzy przekszta�cenia jednorodnego odpowiadaj� przypadkowi,
 * gdy translacja jest realizowana po rotacji. W takim przypadku
 * operacja nie powoduje zmiany czwartej kolumny macierzy transformacji,
 * kt�ra w tej interpretacji odpowiada bezpo�rednio wektorowi translacji.
 * \param Scale - (\b in) wektor nowych wsp�czynnik�w skali wzgl�dem 
 *               poszczeg�lnych
 *               osi, tzn. \e OX, \e OY, \e OZ.
 * \pre �aden ze wsp�czynnik�w skali nie mo�e by� r�wny 0.
 *      Je�eli dla danej osi wcze�niej wsp�czynnik skali by� ustawiony
 *      na warto�� 0, to dla tej osi przeskalowanie nie jest realizowane.
 * \post Pole
 *  \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink
 *  ma warto�� \p true.
 */
void MatrixH3f::SetScale_TAfterR(const Vector3f &Scale)
{
  MatrixRT3f::SetScale_TAfterR(_Scale = MakeDT_0(Scale));
  ValidParam_Scale();
}


const Vector3f& MatrixH3f::GetAng_Euler_Rad() const
{
  USE(MatrixH3f).UpdateParam_Euler_Angles_condScale();
  return _RotAng;
}




void MatrixH3f::UpdateParam_Euler_Angles_condScale()
{
  if (_Valid_RotAng && _AngInterp == AT_Euler) return;
  MatrixH3f::GetEuler_Angles_Scale(_RotAng,_Scale);
  ValidParam_Scale_Euler_Angles();
}



/*!
 *  Realizuje aktualizacj� warto�ci k�t�w 
 *  przyjmuj�c jako podstaw� do interpretacji 
 *  warto�� pola \link MatrixH3f::_AngInterp _AngInterp\endlink.
 *  Operacja wykonywana jest tylko wtedy
 *  gdy stwierdzone zostanie, �e warto�ci k�t�w nie s� aktualne
 *  w stosunku do warto�ci macierzy.
 *  Zapisywane warto�ci wyliczane s� na podstawie aktualnych parameter�w
 *  macierzy transformacji.
 *  Je�eli aktualizowane s� warto�ci k�t�w, to aktualizowany
 *  jest r�wnie�  wektor skali 
 *   (pola \link MatrixH3f::_Scale _Scale\endlink).
 *  w kt�rym zapisany s�
 *  wsp�czynniki skali dla poszczeg�lnych osi. 
 * \post Wyliczone warto�ci k�t�w mieszcz� si� w przedzia�ach:
 *         \li \f$ \psi \in (-\pi,-\pi]\f$ - odpowiada wsp�rz�dnej $y$
 *            wektora k�t�w rotacji.
 *       Pole \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *       ma warto�� \p true, za� pole 
 *       \link MatrixH3f::_AngInterp _AngInterp\endlink warto��
 *       \p AT_Euler.
 *       Pondto je�eli nast�pi�a aktualizacja warto�ci k�t�w,
 *      to pole  \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink
 *      ma warto�� \p true, za� 
 *       \link MatrixH3f::_Scale _Scale\endlink zawiera aktualny
 *      wektor skali.
 */
void MatrixH3f::UpdateParam_Angles_condScale_Auto()
{
  if (_Valid_RotAng) return;
  switch (_AngInterp) {
    case AT_Euler:
      UpdateParam_Euler_Angles_condScale();
      break;
    case AT_xyz:
      UpdateParam_XYZ_Angles_condScale();
      break;
    default:
      cerr << "!!! Uwaga:  W metodzie " 
           << "\"void MatrixH3f::UpdateParam_Angles_condScale_Auto()\" " 
           << endl;
      cerr << "!!! Wystapil nieobslugiwany typ kata: " << _AngInterp << endl;
      break;
  }
}




/*!
 *  Nadaje nowe warto�ci k�tom rotacji danej transformacji
 *  w reprezentacji \e XYZ.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�t�w powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w radianach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Ax - (\b in) warto�� k�ta \f$\alpha\f$ 
 *                     (rotacja wok� osi \f$ OX\f$).
 *  \param Ay - (\b in) warto�� k�ta \f$\beta\f$ 
 *                    (rotacja wok� osi \f$ OY'\f$).
 *  \param Az - (\b in) warto�� k�ta \f$\gamma\f$ 
 *                    (rotacja wok� osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_XYZ_TAfterR_Rad(float Ax, float Ay, float Az)
{
  UpdateParam_Scale();
  MatrixRT3f:: SetRotMtx_XYZ_Rad(_RotAng.Set(Ax,Ay,Az),_Scale);
  ValidParam_XYZ_Angles();
}





/*!
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia zadan� indeksem wsp�rz�dn� wektora translacji
 * \endif
 *
 *  Ustawia zadan� indeksem wsp�rz�dn� wektora translacji
 *  dla transformacji, gdy translacja wykonywana jest po rotacji.
 *  Metoda pozostawia niezmienione warto�ci wektora rotacji i
 *  skali. Zadanie warto�ci translacji
 *  powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Idx - (\b in) indeks okre�laj�cy, kt�rej wsp�rz�dnej
 *               wektora translacji ma zosta� nadana nowa warto��.
 *               Indeks mo�e przyjmowa� warto�ci: 0, 1, 2.
 *             Odpowiadaj� one odpowiednio wsp�rz�dnej \e x, \e y, \e z.
 *  \param Val - (\b in) nowa warto�� translacji.
 * \post Do pola \link MatrixH3f::_Trans _Trans\endlink 
 *       w miejsce wybranej wsp�rz�dnej zostaje wpisana
 *       nowa warto�� przekazana przez parametr \e Val.
 *       Zostaje ona wpisana r�wnie� do odpowiedniego elementu
 *       4 kolumny macierzy wsp�czynnik�w
 *       transformacji (patrz opis pola 
 *       \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink)
 *       zachowuj�c aktualno��
 *       wylicze� wp�czynnik�w tej macierzy.
 *       
 *       Dzia�anie metody powoduje przypisanie polom 
 *    \link MatrixH3f::_Valid_Trans  MatrixH3f::_Valid_Trans\endlink
 *    oraz 
 *    \link MatrixH3f::_Trans_Order MatrixH3f::_Trans_Order \endlink
 *    warto�ci \p TO_After.
 */
void MatrixH3f::SetTrans_TAfterR(unsigned int Idx, float Val)
{
  switch (Idx) {
   case 0: SetTransX_TAfterR(Val);  break;
   case 1: SetTransY_TAfterR(Val);  break;
   case 2: SetTransZ_TAfterR(Val);  break;
  }
}




/*!
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia zadan� indeksem wsp�rz�dn� wektora translacji
 * \endif
 *
 *  Ustawia zadan� indeksem wsp�rz�dn� wektora translacji
 *  dla transformacji, gdy translacja wykonywana jest przed rotacj�.
 *  Metoda pozostawia niezmienione warto�ci wektora rotacji i
 *  skali. Zadanie warto�ci translacji
 *  powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F =  R \circ S \circ T
    \f]
 *  \param Idx - (\b in) indeks okre�laj�cy, kt�rej wsp�rz�dnej
 *               wektora translacji ma zosta� nadana nowa warto��.
 *               Indeks mo�e przyjmowa� warto�ci: 0, 1, 2.
 *             Odpowiadaj� one odpowiednio wsp�rz�dnej \e x, \e y, \e z.
 *  \param Val - (\b in) nowa warto�� translacji.
 * \post Do pola \link MatrixH3f::_Trans _Trans\endlink 
 *       w miejsce wybranej wsp�rz�dnej zostaje wpisana
 *       nowa warto�� przekazana przez parametr \e Val.
 *       Zostaje ona wpisana r�wnie� do odpowiedniego elementu
 *       4 kolumny macierzy wsp�czynnik�w
 *       transformacji (patrz opis pola 
 *       \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink)
 *       zachowuj�c aktualno��
 *       wylicze� wp�czynnik�w tej macierzy.
 *
 *       Dzia�anie metody powoduje przypisanie polom 
 *    \link MatrixH3f::_Valid_Trans  MatrixH3f::_Valid_Trans\endlink
 *    oraz 
 *    \link MatrixH3f::_Trans_Order MatrixH3f::_Trans_Order \endlink
 *    warto�ci \p TO_Before.
 */
void MatrixH3f::SetTrans_TBeforeR(unsigned int Idx, float Val)
{
  switch (Idx) {
   case 0: SetTransX_TBeforeR(Val);  break;
   case 1: SetTransY_TBeforeR(Val);  break;
   case 2: SetTransZ_TBeforeR(Val);  break;
  }
}




/*!
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia zadan� indeksem wsp�rz�dn� wektora skali
 * \endif
 *
 *  Ustawia zadan� indeksem wsp�rz�dn� wektora skali
 *  dla transformacji, gdy translacja wykonywana jest przed rotacj�.
 *  Metoda pozostawia niezmienione warto�ci wektora rotacji i translacji.
 *  Zadanie warto�ci skali
 *  powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = R \circ S \circ T
    \f]
 *  \param Idx - (\b in) indeks okre�laj�cy, kt�rej wsp�rz�dnej
 *               wektora skali ma zosta� nadana nowa warto��.
 *               Indeks mo�e przyjmowa� warto�ci: 0, 1, 2.
 *             Odpowiadaj� one odpowiednio wsp�rz�dnej \e x, \e y, \e z.
 *  \param Val - (\b in) nowa warto�� skali.
 * \post Nie powoduje zmiany warto�ci p�l okre�laj�cych wa�no�� poszczeg�lnych
 *       parametr�w (w tym r�wnie� skali).
 */
void MatrixH3f::SetScale_TBeforeR(unsigned int Idx, float Val)
{
  switch (Idx) {
   case 0: SetScaleX_TBeforeR(Val);  break;
   case 1: SetScaleY_TBeforeR(Val);  break;
   case 2: SetScaleZ_TBeforeR(Val);  break;
  }
}



/*!
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia zadan� indeksem wsp�rz�dn� wektora skali
 * \endif
 *
 *  Ustawia zadan� indeksem wsp�rz�dn� wektora skali
 *  dla transformacji, gdy translacja wykonywana jest po rotacji.
 *  Metoda pozostawia niezmienione warto�ci wektora rotacji i translacji.
 *  Zadanie warto�ci skali
 *  powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Idx - (\b in) indeks okre�laj�cy, kt�rej wsp�rz�dnej
 *               wektora skali ma zosta� nadana nowa warto��.
 *               Indeks mo�e przyjmowa� warto�ci: 0, 1, 2.
 *             Odpowiadaj� one odpowiednio wsp�rz�dnej \e x, \e y, \e z.
 *  \param Val - (\b in) nowa warto�� skali.
 * \post Nie powoduje zmiany warto�ci p�l okre�laj�cych wa�no�� poszczeg�lnych
 *       parametr�w (w tym r�wnie� skali).
 */
void MatrixH3f::SetScale_TAfterR(unsigned int Idx, float Val)
{
  switch (Idx) {
   case 0: SetScaleX_TAfterR(Val);  break;
   case 1: SetScaleY_TAfterR(Val);  break;
   case 2: SetScaleZ_TAfterR(Val);  break;
  }
}








/*!
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy zadany k�t rotacji w reprezentacji 
 *         \e XYZ dla translacji po rotacji.
 * \endif
 *
 *  Ustawia zadany indeksem k�t rotacji w reprezentacji 
 *  \e XYZ dla translacji po rotacji.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�ta powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�� k�ta wyra�ona jest
 *  w radianach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Idx - (\b in) indeks okre�laj�cy, kt�remu z k�t�w
 *                       ma zosta� nadana nowa warto��.
 *               Indeks mo�e przyjmowa� warto�ci: 0, 1, 2.
 *             Odpowiadaj� one odpowiednio pierwszemu (obr�t wok� osi
                \f$ OX\f$), drugiemu (obr�t wok� osi \f$ OY'\f$)
 *             oraz trzeciemu (obr�t wok� osi \f$ OZ''\f$) k�towi rotacji.
 *  \param Ang - (\b in) warto�� zadanego k�ta rotacji wyra�ona w radianach.
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_XYZ_TAfterR_Rad(unsigned int Idx, float Ang)
{
  switch (Idx) {
   case 0: SetAng_XYZoX_TAfterR_Rad(Ang);  break;
   case 1: SetAng_XYZoY_TAfterR_Rad(Ang);  break;
   case 2: SetAng_XYZoZ_TAfterR_Rad(Ang);  break;
  }
}






/*!
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy zadany k�t rotacji w reprezentacji 
 *         \e XYZ dla translacji po rotacji.
 * \endif
 *
 *  Ustawia zadany indeksem k�t rotacji w reprezentacji 
 *  \e XYZ dla translacji po rotacji.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�ta powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�� k�ta wyra�ona jest
 *  w stopniach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Idx - (\b in) indeks okre�laj�cy, kt�remu z k�t�w
 *                       ma zosta� nadana nowa warto��.
 *               Indeks mo�e przyjmowa� warto�ci: 0, 1, 2.
 *             Odpowiadaj� one odpowiednio pierwszemu (obr�t wok� osi
                \f$ OX\f$), drugiemu (obr�t wok� osi \f$ OY'\f$)
 *             oraz trzeciemu (obr�t wok� osi \f$ OZ''\f$) k�towi rotacji.
 *  \param Ang - (\b in) warto�� zadanego k�ta rotacji wyra�ona w stopniach.
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_XYZ_TAfterR_Deg(unsigned int Idx, float Ang)
{
  switch (Idx) {
   case 0: SetAng_XYZoX_TAfterR_Deg(Ang);  break;
   case 1: SetAng_XYZoY_TAfterR_Deg(Ang);  break;
   case 2: SetAng_XYZoZ_TAfterR_Deg(Ang);  break;
  }
}





/*!
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy zadany k�t rotacji w reprezentacji 
 *         \e XYZ dla translacji przed rotacj�.
 * \endif
 *
 *  Ustawia zadany indeksem k�t rotacji w reprezentacji 
 *  \e XYZ dla translacji przed rotacj�.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�ta powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�� k�ta wyra�ona jest
 *  w radianach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = R \circ S \circ T
    \f]
 *  \param Idx - (\b in) indeks okre�laj�cy, kt�remu z k�t�w
 *                       ma zosta� nadana nowa warto��.
 *               Indeks mo�e przyjmowa� warto�ci: 0, 1, 2.
 *             Odpowiadaj� one odpowiednio pierwszemu (obr�t wok� osi
                \f$ OX\f$), drugiemu (obr�t wok� osi \f$ OY'\f$)
 *             oraz trzeciemu (obr�t wok� osi \f$ OZ''\f$) k�towi rotacji.
 *  \param Ang - (\b in) warto�� zadanego k�ta rotacji wyra�ona w radianach.
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_XYZ_TBeforeR_Rad(unsigned int Idx, float Ang)
{
  switch (Idx) {
   case 0: SetAng_XYZoX_TBeforeR_Rad(Ang);  break;
   case 1: SetAng_XYZoY_TBeforeR_Rad(Ang);  break;
   case 2: SetAng_XYZoZ_TBeforeR_Rad(Ang);  break;
  }
}







/*!
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy zadany k�t rotacji w reprezentacji 
 *         \e XYZ dla translacji przed rotacj�.
 * \endif
 *
 *  Ustawia zadany indeksem k�t rotacji w reprezentacji 
 *  \e XYZ dla translacji przed rotacj�.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�ta powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�� k�ta wyra�ona jest
 *  w stopniach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = R \circ S \circ T
    \f]
 *  \param Idx - (\b in) indeks okre�laj�cy, kt�remu z k�t�w
 *                       ma zosta� nadana nowa warto��.
 *               Indeks mo�e przyjmowa� warto�ci: 0, 1, 2.
 *             Odpowiadaj� one odpowiednio pierwszemu (obr�t wok� osi
                \f$ OX\f$), drugiemu (obr�t wok� osi \f$ OY'\f$)
 *             oraz trzeciemu (obr�t wok� osi \f$ OZ''\f$) k�towi rotacji.
 *  \param Ang - (\b in) warto�� zadanego k�ta rotacji wyra�ona w stopniach.
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_XYZ_TBeforeR_Deg(unsigned int Idx, float Ang)
{
  switch (Idx) {
   case 0: SetAng_XYZoX_TBeforeR_Deg(Ang);  break;
   case 1: SetAng_XYZoY_TBeforeR_Deg(Ang);  break;
   case 2: SetAng_XYZoZ_TBeforeR_Deg(Ang);  break;
  }
}









/*!
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy zadany k�t rotacji w reprezentacji 
 *         k�t�w Eulera dla translacji po rotacji.
 * \endif
 *
 *  Ustawia zadany indeksem k�t rotacji w reprezentacji 
 *  k�t�w Eulera dla translacji po rotacji.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�ta powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�� k�ta wyra�ona jest
 *  w radianach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Idx - (\b in) indeks okre�laj�cy, kt�remu z k�t�w
 *                       ma zosta� nadana nowa warto��.
 *               Indeks mo�e przyjmowa� warto�ci: 0, 1, 2.
 *             Odpowiadaj� one odpowiednio pierwszemu (obr�t wok� osi
                \f$ OZ\f$, k�t \f$\varphi\f$), 
                drugiemu (obr�t wok� osi \f$ OY'\f$, k�t \f$\theta\f$)
 *             oraz trzeciemu (obr�t wok� osi \f$ OZ''\f$, k�t \f$\psi\f$) 
 *             k�towi rotacji.
 *  \param Ang - (\b in) warto�� zadanego k�ta rotacji wyra�ona w radianach.
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_Euler_TAfterR_Rad(unsigned int Idx, float Ang)
{
  switch (Idx) {
   case 0: SetAng_EulerVPhi_TAfterR_Rad(Ang);  break;
   case 1: SetAng_EulerTheta_TAfterR_Rad(Ang);  break;
   case 2: SetAng_EulerPsi_TAfterR_Rad(Ang);  break;
  }
}






/*!
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy zadany k�t rotacji w reprezentacji 
 *         k�t�w Eulera dla translacji po rotacji.
 * \endif
 *
 *  Ustawia zadany indeksem k�t rotacji w reprezentacji 
 *  k�t�w Eulera dla translacji po rotacji.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�ta powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�� k�ta wyra�ona jest
 *  w stopniach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Idx - (\b in) indeks okre�laj�cy, kt�remu z k�t�w
 *                       ma zosta� nadana nowa warto��.
 *               Indeks mo�e przyjmowa� warto�ci: 0, 1, 2.
 *             Odpowiadaj� one odpowiednio pierwszemu (obr�t wok� osi
                \f$ OZ\f$, k�t \f$\varphi\f$), 
                drugiemu (obr�t wok� osi \f$ OY'\f$, k�t \f$\theta\f$)
 *             oraz trzeciemu (obr�t wok� osi \f$ OZ''\f$, k�t \f$\psi\f$) 
 *             k�towi rotacji.
 *  \param Ang - (\b in) warto�� zadanego k�ta rotacji wyra�ona w stopniach.
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_Euler_TAfterR_Deg(unsigned int Idx, float Ang)
{
  switch (Idx) {
   case 0: SetAng_EulerVPhi_TAfterR_Deg(Ang);  break;
   case 1: SetAng_EulerTheta_TAfterR_Deg(Ang);  break;
   case 2: SetAng_EulerPsi_TAfterR_Deg(Ang);  break;
  }
}








/*!
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy zadany k�t rotacji w reprezentacji 
 *         k�t�w Eulera dla translacji przed rotacji.
 * \endif
 *
 *  Ustawia zadany indeksem k�t rotacji w reprezentacji 
 *  k�t�w Eulera dla translacji przed rotacji.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�ta powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�� k�ta wyra�ona jest
 *  w radianach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F =  R \circ S \circ T
    \f]
 *  \param Idx - (\b in) indeks okre�laj�cy, kt�remu z k�t�w
 *                       ma zosta� nadana nowa warto��.
 *               Indeks mo�e przyjmowa� warto�ci: 0, 1, 2.
 *             Odpowiadaj� one odpowiednio pierwszemu (obr�t wok� osi
                \f$ OZ\f$, k�t \f$\varphi\f$), 
                drugiemu (obr�t wok� osi \f$ OY'\f$, k�t \f$\theta\f$)
 *             oraz trzeciemu (obr�t wok� osi \f$ OZ''\f$, k�t \f$\psi\f$) 
 *             k�towi rotacji.
 *  \param Ang - (\b in) warto�� zadanego k�ta rotacji wyra�ona w radianach.
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_Euler_TBeforeR_Rad(unsigned int Idx, float Ang)
{
  switch (Idx) {
   case 0: SetAng_EulerVPhi_TBeforeR_Rad(Ang);  break;
   case 1: SetAng_EulerTheta_TBeforeR_Rad(Ang);  break;
   case 2: SetAng_EulerPsi_TBeforeR_Rad(Ang);  break;
  }
}







/*!
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy zadany k�t rotacji w reprezentacji 
 *         k�t�w Eulera dla translacji przed rotacji.
 * \endif
 *
 *  Ustawia zadany indeksem k�t rotacji w reprezentacji 
 *  k�t�w Eulera dla translacji przed rotacji.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�ta powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�� k�ta wyra�ona jest
 *  w stopniach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F =  R \circ S \circ T
    \f]
 *  \param Idx - (\b in) indeks okre�laj�cy, kt�remu z k�t�w
 *                       ma zosta� nadana nowa warto��.
 *               Indeks mo�e przyjmowa� warto�ci: 0, 1, 2.
 *             Odpowiadaj� one odpowiednio pierwszemu (obr�t wok� osi
                \f$ OZ\f$, k�t \f$\varphi\f$), 
                drugiemu (obr�t wok� osi \f$ OY'\f$, k�t \f$\theta\f$)
 *             oraz trzeciemu (obr�t wok� osi \f$ OZ''\f$, k�t \f$\psi\f$) 
 *             k�towi rotacji.
 *  \param Ang - (\b in) warto�� zadanego k�ta rotacji wyra�ona w stopniach.
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_Euler_TBeforeR_Deg(unsigned int Idx, float Ang)
{
  switch (Idx) {
   case 0: SetAng_EulerVPhi_TBeforeR_Deg(Ang);  break;
   case 1: SetAng_EulerTheta_TBeforeR_Deg(Ang);  break;
   case 2: SetAng_EulerPsi_TBeforeR_Deg(Ang);  break;
  }
}












/*!
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy pierwszy k�t rotacji w reprezentacji 
 *         \e XYZ dla translacji po rotacji.
 * \endif
 *
 *  Ustawia nowy pierwszy k�t rotacji w reprezentacji 
 *  \e XYZ dla translacji po rotacji.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�ta powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�� k�ta wyra�ona jest
 *  w radianach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Ax - (\b in) warto�� k�ta \f$\alpha\f$ 
 *                     (rotacja wok� osi \f$ OX\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_XYZoX_TAfterR_Rad(float Ax)
{
  UpdateParam_Scale_XYZ_Angles();
  _RotAng.x = Ax;
  MatrixRT3f:: SetRotMtx_XYZ_Rad(_RotAng,_Scale);
  ValidParam_XYZ_Angles();
}


/*!
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy drugi k�t rotacji w reprezentacji 
 *         \e XYZ dla translacji po rotacji.
 * \endif
 *
 *  Ustawia nowy drugi k�t rotacji w reprezentacji 
 *  \e XYZ dla translacji po rotacji.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�ta powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�� k�ta wyra�ona jest
 *  w radianach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Ay - (\b in) warto�� k�ta \f$\alpha\f$ 
 *                     (rotacja wok� osi \f$ OY'\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_XYZoY_TAfterR_Rad(float Ay)
{
  UpdateParam_Scale_XYZ_Angles();
  _RotAng.y = Ay;
  MatrixRT3f:: SetRotMtx_XYZ_Rad(_RotAng,_Scale);
  ValidParam_XYZ_Angles();
}



/*!
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy trzeci k�t rotacji w reprezentacji 
 *         \e XYZ dla translacji po rotacji.
 * \endif
 *
 *  Ustawia nowy trzeci k�t rotacji w reprezentacji 
 *  \e XYZ dla translacji po rotacji.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�ta powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�� k�ta wyra�ona jest
 *  w radianach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Az - (\b in) warto�� k�ta \f$\alpha\f$ 
 *                     (rotacja wok� osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_XYZoZ_TAfterR_Rad(float Az)
{
  UpdateParam_Scale_XYZ_Angles();
  _RotAng.z = Az;
  MatrixRT3f:: SetRotMtx_XYZ_Rad(_RotAng,_Scale);
  ValidParam_XYZ_Angles();
}





/*!
 *  Nadaje nowe warto�ci k�tom rotacji danej transformacji
 *  w reprezentacji \e XYZ.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�t�w powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w radianach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = R \circ S \circ T
    \f]
 *  \param Ax - (\b in) warto�� k�ta \f$\alpha\f$ 
 *                     (rotacja wok� osi \f$ OX\f$).
 *  \param Ay - (\b in) warto�� k�ta \f$\beta\f$ 
 *                    (rotacja wok� osi \f$ OY'\f$).
 *  \param Az - (\b in) warto�� k�ta \f$\gamma\f$ 
 *                    (rotacja wok� osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_XYZ_TBeforeR_Rad(float Ax, float Ay, float Az)
{
  UpdateParam_Scale();
  UpdateParam_Trans_TBeforeR();
  MatrixRT3f::SetRotMtx_XYZ_Rad(_RotAng.Set(Ax,Ay,Az),_Scale);
  ValidParam_XYZ_Angles();
  MatrixRT3f::SetTrans_TBeforeR(_Trans);
}



/*!
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy pierwszy k�t rotacji w reprezentacji 
 *         \e XYZ dla translacji przed rotacj�. 
 * \endif
 *
 *  Nadaje now� warto�� pierwszemu k�towi rotacji danej transformacji
 *  w reprezentacji \e XYZ.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�t�w powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w radianach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = R \circ S \circ T
    \f]
 *  \param Ax - (\b in) warto�� k�ta \f$\alpha\f$ 
 *                     (rotacja wok� osi \f$ OX\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_XYZoX_TBeforeR_Rad(float Ax)
{
  UpdateParam_Scale_XYZ_Angles();
  UpdateParam_Trans_TBeforeR();
  _RotAng.x = Ax;
  MatrixRT3f::SetRotMtx_XYZ_Rad(_RotAng,_Scale);
  MatrixRT3f::SetTrans_TBeforeR(_Trans);
}


/*!
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy drugi k�t rotacji w reprezentacji 
 *         \e XYZ dla translacji przed rotacj�. 
 * \endif
 *
 *  Nadaje now� warto�� drugiemu k�towi rotacji danej transformacji
 *  w reprezentacji \e XYZ.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�t�w powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w radianach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = R \circ S \circ T
    \f]
 *  \param Ay - (\b in) warto�� k�ta \f$\alpha\f$ 
 *                     (rotacja wok� osi \f$ OY'\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_XYZoY_TBeforeR_Rad(float Ay)
{
  UpdateParam_Scale_XYZ_Angles();
  UpdateParam_Trans_TBeforeR();
  _RotAng.y = Ay;
  MatrixRT3f::SetRotMtx_XYZ_Rad(_RotAng,_Scale);
  MatrixRT3f::SetTrans_TBeforeR(_Trans);
}


/*!
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy trzeci k�t rotacji w reprezentacji 
 *         \e XYZ dla translacji przed rotacj�. 
 * \endif
 *
 *  Nadaje now� warto�� trzeciemu k�towi rotacji danej transformacji
 *  w reprezentacji \e XYZ.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�t�w powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w radianach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = R \circ S \circ T
    \f]
 *  \param Az - (\b in) warto�� k�ta \f$\alpha\f$ 
 *                     (rotacja wok� osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_XYZoZ_TBeforeR_Rad(float Az)
{
  UpdateParam_Scale_XYZ_Angles();
  UpdateParam_Trans_TBeforeR();
  _RotAng.z = Az;
  MatrixRT3f::SetRotMtx_XYZ_Rad(_RotAng,_Scale);
  MatrixRT3f::SetTrans_TBeforeR(_Trans);
}






/*!
 * \if matrixh3f_brief_desc
 *  \brief Ustawia warto�ci k�t�w Eulera dla transformacji z translacj�
 *         przed rotacj�
 * \endif
 *
 *  Nadaje nowe warto�ci k�tom Eulera danej transformacji.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�t�w powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w radianach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F =  R \circ S \circ T
    \f]
 *  \param VPhi - (\b in) warto�� k�ta \f$\varphi\f$ 
 *                     (rotacja wok� osi \f$ OZ\f$).
 *  \param Theta - (\b in) warto�� k�ta \f$\theta\f$ 
 *                    (rotacja wok� osi \f$ OY'\f$).
 *  \param Psi - (\b in) warto�� k�ta \f$\psi\f$ 
 *                    (rotacja wok� osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_Euler_TBeforeR_Rad(float VPhi, float Theta, float Psi)
{
  UpdateParam_Scale();
  UpdateParam_Trans_TBeforeR();
  MatrixRT3f::SetMatrix_Euler_TBeforeR_Rad(_RotAng.Set(VPhi,Theta,Psi),
                                            _Trans,_Scale);
  ValidParam_Euler_Angles();
}



void MatrixH3f::SetAng_Auto_TAfterR_Rad( const Vector3f &Angles,
                                         const Vector3f &Scale
                                       )
{
  switch (_AngInterp) {
   case AT_Euler:
     MatrixRT3f::SetRotMtx_Euler_Rad(Angles,Scale);
     ValidParam_Scale_Euler_Angles();
     break;
   case AT_xyz:
     MatrixRT3f::SetRotMtx_XYZ_Rad(Angles,Scale);
     ValidParam_Scale_XYZ_Angles();
     break;
  }
}



/*!
 * \if matrixh3f_brief_desc
 *  \brief Ustawia warto�� k�ta Eulera \f$\varphi\f$ dla transformacji 
 *     z translacj� przed rotacj�
 * \endif
 *
 *  Nadaje nowe warto�� k�ta Eulera \f$\varphi\f$ danej transformacji.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie warto�ci k�ta powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w radianach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F =  R \circ S \circ T
    \f]
 *  \param VPhi - (\b in) warto�� k�ta \f$\varphi\f$ 
 *                     (rotacja wok� osi \f$ OZ\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_EulerVPhi_TBeforeR_Rad(float VPhi)
{
  UpdateParam_Scale_Euler_Angles();
  UpdateParam_Trans_TBeforeR();
  _RotAng.x = VPhi;
  MatrixRT3f::SetMatrix_Euler_TBeforeR_Rad(_RotAng,_Trans,_Scale);
}




/*!
 * \if matrixh3f_brief_desc
 *  \brief Ustawia warto�� k�ta Eulera \f$\theta\f$ dla transformacji z translacj�
 *         przed rotacj�
 * \endif
 *
 *  Nadaje nowe warto�� k�ta Eulera \f$\theta\f$ danej transformacji.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie warto�ci k�ta powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w radianach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F =  R \circ S \circ T
    \f]
 *  \param Theta - (\b in) warto�� k�ta \f$\theta\f$ 
 *                     (rotacja wok� osi \f$ OY'\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_EulerTheta_TBeforeR_Rad(float Theta)
{
  UpdateParam_Scale_Euler_Angles();
  UpdateParam_Trans_TBeforeR();
  _RotAng.y = Theta;
  MatrixRT3f::SetMatrix_Euler_TBeforeR_Rad(_RotAng,_Trans,_Scale);
}



/*!
 * \if matrixh3f_brief_desc
 *  \brief Ustawia warto�� k�ta Eulera \f$\psi\f$ dla transformacji z translacj�
 *         przed rotacj�
 * \endif
 *
 *  Nadaje nowe warto�� k�ta Eulera \f$\psi\f$ danej transformacji.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie warto�ci k�ta powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w radianach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F =  R \circ S \circ T
    \f]
 *  \param Psi - (\b in) warto�� k�ta \f$\psi\f$ 
 *                     (rotacja wok� osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_EulerPsi_TBeforeR_Rad(float Psi)
{
  UpdateParam_Scale_Euler_Angles();
  UpdateParam_Trans_TBeforeR();
  _RotAng.z = Psi;
  MatrixRT3f::SetMatrix_Euler_TBeforeR_Rad(_RotAng,_Trans,_Scale);
}








/*!
 *  Nadaje nowe warto�ci k�tom Eulera danej transformacji.
 *  Metoda pozostawia niezmienione warto�ci wektora translacji i
 *  skali. Zadanie k�t�w powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w radianach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param VPhi - (\b in) warto�� k�ta \f$\varphi\f$ 
 *                     (rotacja wok� osi \f$ OZ\f$).
 *  \param Theta - (\b in) warto�� k�ta \f$\theta\f$ 
 *                    (rotacja wok� osi \f$ OY'\f$).
 *  \param Psi - (\b in) warto�� k�ta \f$\psi\f$ 
 *                    (rotacja wok� osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_Euler_TAfterR_Rad(float VPhi, float Theta, float Psi)
{
  if (!_Valid_Scale) UpdateParam_Scale();
  MatrixRT3f::SetAng_Euler_TAfterR_Rad(_RotAng.Set(VPhi,Theta,Psi),_Scale);
  ValidParam_Euler_Angles();
}


/*!
 *  Nadaje now� warto�� k�ta Eulera \f$\varphi\f$ danej transformacji.
 *  Metoda pozostawia niezmienione warto�ci wszystkich pozosta�ych
 *  parametr�w transformacji.
 *  Zadanie k�ta powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w radianach.
 *  \param VPhi - (\b in) warto�� k�ta \f$\varphi\f$ 
 *                     (rotacja wok� osi \f$ OZ\f$) w radianach.
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_EulerVPhi_TAfterR_Rad(float VPhi)
{
 UpdateParam_Scale();
 UpdateParam_Euler_Angles_condScale(); 
 _RotAng.x = VPhi;
 MatrixRT3f::SetAng_Euler_TAfterR_Rad(_RotAng,_Scale);  
}

/*!
 *  Nadaje now� warto�� k�ta Eulera \f$\theta\f$ danej transformacji.
 *  Metoda pozostawia niezmienione warto�ci wszystkich pozosta�ych
 *  parametr�w transformacji.
 *  Zadanie k�ta powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w radianach.
 *  \param Theta - (\b in) warto�� k�ta \f$\theta\f$ 
 *                     (rotacja wok� osi \f$ OZ\f$) w radianach.
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_EulerTheta_TAfterR_Rad(float Theta)
{
 UpdateParam_Scale();
 UpdateParam_Euler_Angles_condScale(); 
 _RotAng.y = Theta;
 MatrixRT3f::SetAng_Euler_TAfterR_Rad(_RotAng,_Scale);  
}

/*!
 *  Nadaje now� warto�� k�ta Eulera \f$\psi\f$ danej transformacji.
 *  Metoda pozostawia niezmienione warto�ci wszystkich pozosta�ych
 *  parametr�w transformacji.
 *  Zadanie k�ta powoduje jednocze�nie odpowiednie przeliczenie
 *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
 *  w radianach.
 * Zak�ada si�, �e translacja ma by� wykonana po skalowanii i rotacji,
 *  tzn.
 *  \f[
            F = T \circ R \circ S
     \f]
 *  \param Psi - (\b in) warto�� k�ta \f$\psi\f$ 
 *                     (rotacja wok� osi \f$ OZ\f$) w radianach.
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj� warto�� \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj� aktualne
 *        warto�ci parametr�w odpowiednio k�t�w rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto�� \p AT_Euler.\n
 *        Zostaj� przeliczone wsp�czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada�y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_EulerPsi_TAfterR_Rad(float Psi)
{
 UpdateParam_Scale();
 UpdateParam_Euler_Angles_condScale(); 
 _RotAng.z = Psi;
 MatrixRT3f::SetAng_Euler_TAfterR_Rad(_RotAng,_Scale);  
}




/*!
 *  \if brief_public_methods
 *   \brief Bezpo�rednio zadaje wsp�czynniki macierzy transformacji.
 *  \endif
 *
 *  Umo�liwia bezpo�rednie zadawanie wsp�czynnik�w transformacji
 *  danej macierzy. Metod� t� nale�y stosowa� bardzo rozwa�nie,
 *  gdy� wsp�czynniki transformacji nie mog� by� dowolnymi warto�ciami,
 *  o ile nie maj� wprowadza� deformacji w transformowanych bry�ach.
 *  Je�eli wsp�czynniki nie b�d� spe�nia�y wi�z�w na�o�onych ma macierz
 *  rotacji, to wszystkie metody wyliczaj�ce k�ty rotacji, nie
 *  b�d� zwraca�y poprawnych warto�ci.\n
 *  Dla podmacierzy rotacji wspomniane wi�zy maj� posta�:
 *
 \f[
            \left[\begin{array}{cccc}
               a_{11} & a_{12} &  a_{13}  & a_{14} \\
               a_{21} & a_{22} &  a_{23}  & a_{24} \\
               a_{31} & a_{32} &  a_{33}  & a_{34}\\
                   0 & 0 & 0 & 1
              \end{array}\right]       
             =
            \left[\begin{array}{cccc}
               s_xr_{11} & s_yr_{12} &  s_zr_{13}  & t_x \\
               s_xr_{21} & s_yr_{22} &  s_zr_{23}  & t_y \\
               s_xr_{31} & s_yr_{32} &  s_zr_{33}  & t_z\\
                   0 & 0 & 0 & 1
              \end{array}\right]       
 \f]
\f[
         a_{11}^2 + a_{21}^2 + a_{31}^2 = s_x
\f]
\f[
         a_{12}^2 + a_{22}^2 + a_{32}^2 = s_y
\f]
\f[
         a_{13}^2 + a_{23}^2 + a_{33}^2 = s_z
\f]
\f[
        a_{1i}a_{1j} + a_{2i}a_{2j} + a_{3i}a_{3j} = 0
\f]
 *   gdzie  \f$ i,j = 1,2,3 \f$ oraz \f$ i \ne j\f$.
 *  \param Col1_Rot - warto�ci wsp�czynnik�w transformacji dla pierwszej
 *                    kolumny (pierwsza kolumna podmacierzy rotacji).
 *  \param Col2_Rot - warto�ci wsp�czynnik�w transformacji dla drugiej
 *                    kolumny (druga kolumna podmacierzy rotacji).
 *  \param Col3_Rot - warto�ci wsp�czynnik�w transformacji dla drugiej
 *                    kolumny (trzecia kolumna podmacierzy rotacji).
 *  \param Col4_Trans - warto�ci wsp�czynnik�w transformacji dla trzeciej
 *                    kolumny (wektor translacji).
 *  \post Uniewa�niane s� aktualne pami�tane warto�ci parametr�w transformacji.
 *        Oznacza to, �e u�ycie jakiejkolwiek metody typu \e Get wymusi ich
 *        wyliczenie.
 */
void MatrixH3f::SetMatrix( const Vector3f &Col1_Rot, 
                           const Vector3f &Col2_Rot,
                           const Vector3f &Col3_Rot,
                           const Vector3f &Col4_Trans
                         )
{
  MatrixRT3f::SetMatrix(Col1_Rot,Col2_Rot,Col3_Rot,Col4_Trans);
  SetParamInvalid();
}



void MatrixH3f::SetMatrix_Euler_TAfterR_Rad( const Vector3f  &Ang, 
                                              const Vector3f  &Trans,
                                              const Vector3f  &Scale
                                            )
{
  MatrixRT3f::SetMatrix_Euler_TAfterR_Rad(_RotAng = Ang,_Trans = Trans,
                                                         _Scale = Scale);
  ValidParam_Trans_TAfterR();
  ValidParam_Scale_Euler_Angles();
}


void MatrixH3f::SetMatrix_XYZ_TAfterR_Rad( const Vector3f  &Ang, 
					    const Vector3f  &Trans,
                                            const Vector3f  &Scale
                                          )
{
  MatrixRT3f::SetMatrix_XYZ_TAfterR_Rad(_RotAng = Ang,_Trans = Trans,
                                                         _Scale = Scale);
  ValidParam_Trans_TAfterR();
  ValidParam_Scale_XYZ_Angles();
}




/*!
 * Dodaje podane warto�ci do aktalnych warto�ci k�t�w rotacji 
 * w reprezentacji \e XYZ i aktualizuje
 * macierz transformacji. Warto�ci k�t�w wyra�one s� w radianach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F =  R \circ S  \circ T
   \f]
 * \param d_Ax - warto�� o kt�r� ma by� zwi�kszony k�t \f$\alpha\f$
 *               (obr�t wok� osi \f$ OX\f$).
 * \param d_Ay - warto�� o kt�r� ma by� zwi�kszony k�t \f$\beta\f$
 *               (obr�t wok� osi \f$ OY'\f$.
 * \param d_Az - warto�� o kt�r� ma by� zwi�kszony k�t \f$\gamma\f$
 *               (obr�t wok� osi \f$ OZ''\f$).
 * \post Do k�t�w transformacji dodane zostaj� podane warto�ci
 *       oraz zostaje zaaktualizowana macierz wsp�czynnik�w transformacji.
 */
void MatrixH3f::AddAng_XYZ_TBeforeR_Rad( float d_Ax, float d_Ay, float d_Az )
{
  UpdateParam_Scale_XYZ_Angles();
  UpdateParam_Trans_TBeforeR();
  MatrixRT3f::SetRotMtx_XYZ_Rad(_RotAng.Add(d_Ax,d_Ay,d_Az),_Scale);
  MatrixRT3f::SetTrans_TBeforeR(_Trans);
}



/*!
 * Dodaje podane warto�ci do aktalnych warto�ci k�t�w rotacji 
 * w reprezentacji \e XYZ i aktualizuje
 * macierz transformacji. Warto�ci k�t�w wyra�one s� w radianach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = T \circ R \circ S  
   \f]
 * \param d_Ax -  (\b in) warto�� o kt�r� ma by� zwi�kszony k�t \f$\alpha\f$
 *               (obr�t wok� osi \f$ OX\f$).
 * \param d_Ay -  (\b in) warto�� o kt�r� ma by� zwi�kszony k�t \f$\beta\f$
 *               (obr�t wok� osi \f$ OY'\f$.
 * \param d_Az -  (\b in) warto�� o kt�r� ma by� zwi�kszony k�t \f$\gamma\f$
 *               (obr�t wok� osi \f$ OZ''\f$).
 * \post Do k�t�w transformacji dodane zostaj� podane warto�ci
 *       oraz zostaje zaaktualizowana macierz wsp�czynnik�w transformacji.
 */
void MatrixH3f::AddAng_XYZ_TAfterR_Rad( float d_Ax, float d_Ay, float d_Az )
{
  UpdateParam_Scale_XYZ_Angles();
  MatrixRT3f::SetRotMtx_XYZ_Rad(_RotAng.Add(d_Ax,d_Ay,d_Az),_Scale);
}




/*!
 * Dodaje do aktalnych warto�ci k�t�w Eulera podane warto�ci i aktualizuje
 * macierz transformacji. Warto�ci k�t�w wyra�one s� w radianach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = R \circ S \circ T
   \f]
 * \param d_VPhi -  (\b in) warto�� o kt�r� ma by� zwi�kszony k�t \f$\varphi\f$.
 * \param d_Theta -  (\b in) warto�� o kt�r� ma by� zwi�kszony k�t \f$\theta\f$.
 * \param d_Psi -  (\b in) warto�� o kt�r� ma by� zwi�kszony k�t \f$\psi\f$.
 * \post Do k�t�w transformacji dodane zostaj� podane warto�ci
 *       oraz zostaje zaaktualizowana macierz wsp�czynnik�w transformacji.
 *       Zostaj� ustawione znaczniki wa�no�ci wszystkich pami�tanych
 *       parametr�w transformacji.
 */
void MatrixH3f::AddAng_Euler_TBeforeR_Rad( float d_VPhi, float d_Theta, float d_Psi)
{
  UpdateParam_Scale_Euler_Angles();
  UpdateParam_Trans_TBeforeR();
  MatrixRT3f::SetRotMtx_Euler_Rad(_RotAng.Add(d_VPhi,d_Theta,d_Psi),_Scale);
  MatrixRT3f::SetTrans_TBeforeR(_Trans);
}



/*!
 * Dodaje do aktalnych warto�ci k�t�w Eulera podane warto�ci i aktualizuje
 * macierz transformacji. Warto�ci k�t�w wyra�one s� w radianach.
 * Zak�ada si�, �e transformacja ma posta�:
 * \f[
      F = T \circ R \circ S  
   \f]
 * \param d_VPhi -  (\b in) warto�� o kt�r� ma by� zwi�kszony k�t \f$\varphi\f$.
 * \param d_Theta -  (\b in) warto�� o kt�r� ma by� zwi�kszony k�t \f$\theta\f$.
 * \param d_Psi -  (\b in) warto�� o kt�r� ma by� zwi�kszony k�t \f$\psi\f$.
 * \post Do k�t�w transformacji dodane zostaj� podane warto�ci
 *       oraz zostaje zaaktualizowana macierz wsp�czynnik�w transformacji.
 */
void MatrixH3f::AddAng_Euler_TAfterR_Rad( float d_VPhi, float d_Theta, float d_Psi )
{
  UpdateParam_Scale_Euler_Angles();
  MatrixRT3f::SetAng_Euler_TAfterR_Rad(_RotAng.Add(d_VPhi,d_Theta,d_Psi),_Scale);
}



/*!
 *  Aktualizuje warto�� pola \link MatrixH3f::_Scale _Scale\endlink, 
 *  w kt�rym zapisany jest
 *  wektor wsp�czynnik�w skali dla poszczeg�lnych osi. 
 *  Aktualizuje jednocze�nie wektor k�t�w rotacji nie zmieniaj�c
 *  dotychczasowej ich interpretacji.
 *  Zapisywane warto�ci wyliczane s� na podstawie aktualnych parameter�w
 *  macierzy transformacji.
 * \pre Wyliczenia b�d� poprawne wtedy i tylko wtedy gdy
 *      wsp�czynniki skali musz� s� od zera.
 * \post Zostaj� ustawione znaczniki wa�no�ci warto�ci parametr�w
 *       transformacji. Oznacza to, �e pobranie ich warto�ci 
 *       za pomoc� innych metoda nie b�dzie wymusza�o ponownego ich 
 *       obliczenia.
 */
void MatrixH3f::UpdateParam_Scale_Angles_Auto()
{
      switch (_AngInterp) {
       case AT_Euler: UpdateParam_Scale_Euler_Angles();
	 break;
       case AT_xyz: UpdateParam_Scale_XYZ_Angles();
	 break;
      }
}





/*!
 *  Aktualizuje warto�� pola \link MatrixH3f::_Scale _Scale\endlink, 
 *  w kt�rym zapisany jest
 *  wektor wsp�czynnik�w skali dla poszczeg�lnych osi. 
 *  Aktualizuje jednocze�nie wektor k�t�w rotacji, traktuj�c je
 *  jako k�ty Eulera.
 *  Zapisywane warto�ci wyliczane s� na podstawie aktualnych parameter�w
 *  macierzy transformacji.
 * \pre Wyliczenia b�d� poprawne wtedy i tylko wtedy gdy
 *      wsp�czynniki skali musz� s� od zera.
 * \post Zostaj� ustawione znaczniki wa�no�ci warto�ci parametr�w
 *       transformacji. Oznacza to, �e pobranie ich warto�ci 
 *       za pomoc� innych metoda nie b�dzie wymusza�o ponownego ich 
 *       obliczenia.
 */
void MatrixH3f::UpdateParam_Scale_Euler_Angles()
{
  if (_Valid_Scale && _Valid_RotAng && _AngInterp == AT_Euler) return;
  MatrixRT3f::GetEuler_Angles_Scale(_RotAng,_Scale);
  ValidParam_Scale_Euler_Angles();
}



/*!
 *  Dodaje do wsp�czynnik�w skali danej transformacji podane warto�ci.
 * Zak�ada si�, �e translacja ma by� wykonana przed skalowaniem i rotacj�,
 *  tzn.
 *  \f[
           F = R \circ S \circ T
     \f]
 *  \param d_Sx - (\b in) warto�� dodawana do \e x-owego wsp�czynnika skali.
 *  \param d_Sy - (\b in) warto�� dodawana do \e y-owego wsp�czynnika skali.
 *  \param d_Sz - (\b in) warto�� dodawana do \e z-owego wsp�czynnika skali.
 *  \post Zostaj� zaktualizowany parametr skali i obliczone nowe
 *        warto�ci wsp�czynnik�w macierzy transformacji przy za�o�eniu,
 *        �e transformacja jest realizowana przed skalowaniem i rotacj�.
 *        Nie jest zmieniana interpretacja k�t�w rotacji.
 */
void MatrixH3f::AddScale_TBeforeR(float d_Sx, float d_Sy, float d_Sz)
{
  // UpdateParam_Scale_Euler_Angles();
  UpdateParam_Scale_Angles_Auto();
  UpdateParam_Trans_TBeforeR();
  MatrixH3f::SetAng_Auto_TAfterR_Rad(_RotAng,_Scale.Add(d_Sx,d_Sy,d_Sz));
  //  MatrixRT3f::SetAng_Euler_TAfterR_Rad(_RotAng,_Scale.Add(d_Sx,d_Sy,d_Sz));
  MatrixRT3f::SetTrans_TBeforeR(_Trans);
}



/*!
 *  Dodaje do wsp�czynnik�w skali danej transformacji podane warto�ci.
 *  \param d_Sx - (\b in) warto�� dodawana do \e x-owego wsp�czynnika skali.
 *  \param d_Sy - (\b in) warto�� dodawana do \e y-owego wsp�czynnika skali.
 *  \param d_Sz - (\b in) warto�� dodawana do \e z-owego wsp�czynnika skali.
 *  \post Zostaj� zaktualizowany parametr skali i obliczone nowe
 *        warto�ci wsp�czynnik�w macierzy transformacji przy za�o�eniu,
 *        �e transformacja jest realizowana po rotacji.
 */
void MatrixH3f::AddScale_TAfterR(float d_Sx, float d_Sy, float d_Sz)
{
  UpdateParam_Scale_Angles_Auto();
  MatrixH3f::SetAng_Auto_TAfterR_Rad(_RotAng,_Scale.Add(d_Sx,d_Sy,d_Sz));
}




/*============================================================================
 * Metoda dokonuje normalizacji macierzy rotacji (bez kolumny translacji).
 * Sprowadza w ten spos�b wsp�czynniki skali wzd�u� osi OX, OY, OZ do 
 * warto�ci 1. 
 */
MatrixH3f &MatrixH3f::Normalize()
{
 MatrixRT3f::Normalize();
 _Scale.Set(1,1,1);
 ValidParam_Scale();
 return *this;
}



/*!
 * Operator umo�liwia podstawienie parametr�w macierzy
 * transformacji i wyliczenie wszystkich wsp�czynnik�w tej macierzy.
 */
MatrixH3f &MatrixH3f::operator <<= (MatrixH3f::Parameters const &PF)
{
  switch (_AngInterp) {
   case AT_Euler:
    if (_Trans_Order == TO_After) {
       SetMatrix_Euler_TAfterR_Rad(PF.GetAng_Rad(),PF.GetTrans(),
                                                    PF.GetScale());
    } else {
       SetMatrix_Euler_TBeforeR_Rad(PF.GetAng_Rad(),PF.GetTrans(),
                                                     PF.GetScale());
    }
   case AT_xyz:
    if (_Trans_Order == TO_After) {
       SetMatrix_XYZ_TAfterR_Rad(PF.GetAng_Rad(),PF.GetTrans(),
                                                  PF.GetScale());
    } else {
       SetMatrix_XYZ_TBeforeR_Rad(PF.GetAng_Rad(),PF.GetTrans(),
                                                   PF.GetScale());
    }
   default:
    cerr << "!!! Typ katow rotacji: " << _AngInterp;
    cerr << " nie jest obslugiwany przez" << endl;
    cerr << "!!! operator ";
    cerr << "MatrixH3f::operator <<= (MatrixH3f::Parameters const &)." << endl;
    cerr << "!!! Fakt ten nalezy zglosic autorowi tej biblioteki" << endl;
  }
 return *this;
}


void MatrixH3f::SetMatrix_Euler_TBeforeR_Rad( const Vector3f &Ang, 
                                               const Vector3f &Trans,
                                               const Vector3f &Scale
                                             )
{
  SetRotMtx_Euler_Rad(Ang,Scale);
  SetTrans_TBeforeR(Scale);
}


/*!
 * \if matrixh3f_brief_desc 
 * \brief Udost�pnia k�ty w reprezentacji \e XYZ w radianach.
 * \endif
 *
 * Udost�pnia k�ty obrotu wzgl�dem osi \f$ OX\f$, \f$ OY'\f$ oraz \f$ OZ''\f$
 * dla danej macierzy transformacji.
 * Kolejne wsp�rz�dne wektora odpowiadaj� k�tom
 *  \f$\alpha\f$ (pierwszy obr�t - wok� osi \f$ OX\f$),
 *  \f$\beta\f$ (drugi obr�t - wok� osi \f$ OY'\f$),
 *  \f$\gamma\f$ (trzeci obr�t - wok� osi \f$ OZ''\f$).
 * Udost�pniane warto�ci k�t�w wyra�one s� w radianach.
 */
const Vector3f& MatrixH3f::GetAng_XYZ_Rad() const
{
  USE(MatrixH3f).UpdateParam_XYZ_Angles_condScale();
  return _RotAng;
}


void MatrixH3f::SetMatrix_XYZ_TBeforeR_Rad( const Vector3f &Ang, 
                                             const Vector3f &Trans,
                                             const Vector3f &Scale
                                           )
{
  // To trzeba jeszcze napisac
}



/*!
 *  Wstawia do macierzy transformacji wsp�czynnik translacji
 *  wyliczany dla translacji wykonanej przed skalowaniem i rotacj�,
 *  tzn.
 *  \f[
        F = R \circ S \circ T
    \f]
 *  Operacja wykonywana jest tylko dla \e x-owej sk�adowej.
 *  \param Tx -  (\b in) wsp�rz�dna \e x-owa wektora translacji.
 * \post Do pola \link MatrixH3f::_Trans _Trans\endlink 
 *       w miejsce wsp�rz�dnej \e x-owej zostaje wpisana
 *       nowa warto�� przekazana przez parametr \e Val.
 *       Zostaje ona wpisana r�wnie� do odpowiedniego elementu
 *       4 kolumny macierzy wsp�czynnik�w
 *       transformacji (patrz opis pola 
 *       \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink)
 *       zachowuj�c aktualno��
 *       wylicze� wp�czynnik�w tej macierzy.
 *
 *       Dzia�anie metody powoduje przypisanie polom 
 *    \link MatrixH3f::_Valid_Trans  MatrixH3f::_Valid_Trans\endlink
 *    oraz 
 *    \link MatrixH3f::_Trans_Order MatrixH3f::_Trans_Order \endlink
 *    warto�ci \p TO_Before.
 */
void MatrixH3f::SetTransX_TBeforeR( float Tx )
{
  UpdateParam_Trans_TBeforeR();
  MatrixRT3f::SetTrans_TBeforeR(_Trans.x = Tx,_Trans.y,_Trans.z);
}



/*!
 *  Wstawia do macierzy transformacji wsp�czynnik translacji
 *  wyliczany dla translacji wykonanej przed skalowaniem i rotacj�,
 *  tzn.
 *  \f[
        F = R \circ S \circ T
    \f]
 *  Operacja wykonywana jest tylko dla \e y-owej sk�adowej.
 *  \param Ty -  (\b in) wsp�rz�dna \e y-owa wektora translacji.
 * \post Do pola \link MatrixH3f::_Trans _Trans\endlink 
 *       w miejsce wsp�rz�dnej \e y-owej zostaje wpisana
 *       nowa warto�� przekazana przez parametr \e Val.
 *       Zostaje ona wpisana r�wnie� do odpowiedniego elementu
 *       4 kolumny macierzy wsp�czynnik�w
 *       transformacji (patrz opis pola 
 *       \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink)
 *       zachowuj�c aktualno��
 *       wylicze� wp�czynnik�w tej macierzy.
 *
 *       Dzia�anie metody powoduje przypisanie polom 
 *    \link MatrixH3f::_Valid_Trans  MatrixH3f::_Valid_Trans\endlink
 *    oraz 
 *    \link MatrixH3f::_Trans_Order MatrixH3f::_Trans_Order \endlink
 *    warto�ci \p TO_Before.
 */
void MatrixH3f::SetTransY_TBeforeR( float Ty )
{
  UpdateParam_Trans_TBeforeR();
  MatrixRT3f::SetTrans_TBeforeR(_Trans.x,_Trans.y = Ty,_Trans.z);
}


/*!
 *  Wstawia do macierzy transformacji wsp�czynnik translacji
 *  wyliczany dla translacji wykonanej przed skalowaniem i rotacj�,
 *  tzn.
 *  \f[
        F = R \circ S \circ T
    \f]
 *  Operacja wykonywana jest tylko dla \e z-owej sk�adowej.
 *  \param Tz - (\b in) wsp�rz�dna \e z-owa wektora translacji.
 * \post Do pola \link MatrixH3f::_Trans _Trans\endlink 
 *       w miejsce wsp�rz�dnej \e z-owej zostaje wpisana
 *       nowa warto�� przekazana przez parametr \e Val.
 *       Zostaje ona wpisana r�wnie� do odpowiedniego elementu
 *       4 kolumny macierzy wsp�czynnik�w
 *       transformacji (patrz opis pola 
 *       \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink)
 *       zachowuj�c aktualno��
 *       wylicze� wp�czynnik�w tej macierzy.
 *
 *       Dzia�anie metody powoduje przypisanie polom 
 *    \link MatrixH3f::_Valid_Trans  MatrixH3f::_Valid_Trans\endlink
 *    oraz 
 *    \link MatrixH3f::_Trans_Order MatrixH3f::_Trans_Order \endlink
 *    warto�ci \p TO_Before.
 */
void MatrixH3f::SetTransZ_TBeforeR( float Tz )
{
  UpdateParam_Trans_TBeforeR();
  MatrixRT3f::SetTrans_TBeforeR(_Trans.x,_Trans.y,_Trans.z = Tz);
}


//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^





MatrixH3f::MatrixH3f()
{
 int x,y;

 _Valid_Trans = true;
 _Trans_Order = TO_After;
 _Valid_Scale = true;
 _Valid_RotAng = true;
 ValidParam_Euler_Angles();
 
 SetParamValid();
 _Scale.Set(1,1,1);
 MatrixRT3f::SetUnitMtx();
}

//....................... MatrixH3f ..........................................
//############################################################################



//############################################################################
//....................... MatrixH3f::Parameters ..............................

/*!
 *  Wydobywa z macierzy transformacji jej parametry. 
 *  Wyliczane s� one bezpo�rednio ze wsp�czynnik�w transformacji
 *  w z pola MatrixRT3f::_DH parametru \e Mtx.
 *  \param Mtx - (in) macierz, kt�rej parametry transformacji maj�
 *               zosta� przepisane.
 *  \return referencj� do samego siebie (\b *this).
 *  \post Parametry transformacji z macierzy \e Mtx zostaj� przepisne 
 *   do p�l
 *    \link MatrixH3f::Parameters::_Scale _Scale\endlink,
 *    \link MatrixH3f::Parameters::_Trans _Trans\endlink,
 *    \link MatrixH3f::Parameters::_RotAng _RotAng\endlink.
 */
MatrixH3f::Parameters &
                MatrixH3f::Parameters::operator <<= (MatrixH3f const &Mtx)
{
 SetAngInterp(Mtx.GetAngInterp());
 _Scale  = Mtx.GetScale();

 switch (_AngInterp) {
   case AT_Euler:
    _RotAng = Mtx.GetAng_Euler_Rad();       
    if (Mtx._Trans_Order == TO_After) {
        _Trans  = Mtx.GetTrans_TAfterR();
    } else {
        _Trans  = Mtx.GetTrans_TBeforeR();
    }
   case AT_xyz:
    _RotAng = Mtx.GetAng_XYZ_Rad();
    if (Mtx._Trans_Order == TO_After) {
        _Trans  = Mtx.GetTrans_TAfterR();
    } else {
        _Trans  = Mtx.GetTrans_TBeforeR();
    }
   default:
    cerr << "!!! Typ katow rotacji: " << _AngInterp;
    cerr << " nie jest obslugiwany przez" << endl;
    cerr << "!!! operator ";
    cerr << "MatrixH3f::Parameters operator <<= (MatrixH3f const &)." << endl;
    cerr << "!!! Fakt ten nalezy zglosic autorowi tej biblioteki" << endl;
  }
 return *this;
}



/*!
 *  Aktualizuje warto�� pola \link MatrixH3f::_Scale _Scale\endlink, 
 *  w kt�rym zapisany jest
 *  wektor wsp�czynnik�w skali dla poszczeg�lnych osi. 
 *  Aktualizuje jednocze�nie wektor k�t�w rotacji, traktuj�c je
 *  jako k�ty obrotu wok� osi
 *  \f$ OX\f$, \f$ OY'\f$, \f$ OZ''\f$.
 *  Zapisywane warto�ci wyliczane s� na podstawie aktualnych parameter�w
 *  macierzy transformacji.
 * \pre Wyliczenia b�d� poprawne wtedy i tylko wtedy gdy 
 *      wsp�czynniki skali s� r�ne od zera.
 * \post Zostaj� ustawione znaczniki wa�no�ci warto�ci parametr�w
 *       transformacji. Oznacza to, �e pobranie ich warto�ci 
 *       za pomoc� innych metoda nie b�dzie wymusza�o ponownego ich 
 *       obliczenia.
 */
void MatrixH3f::UpdateParam_Scale_XYZ_Angles()
{
  if (_Valid_Scale && _Valid_RotAng && _AngInterp == AT_xyz) return;
  MatrixRT3f::GetXYZ_Angles_Scale(_RotAng,_Scale);
  ValidParam_Scale_XYZ_Angles();
}



/*!
 * \if matrixh3f_brief_desc 
 *  \brief Aktualizacja k�t�w i warunkowa aktualizacja skali.
 * \endif
 *
 *  Aktualizuje wektor k�t�w rotacji, traktuj�c je
 *  jako k�ty obrotu wok� osi
 *  \f$ OX\f$, \f$ OY'\f$, \f$ OZ''\f$.
 *  W przypadku gdy aktualizowany s� warto�ci k�t�w, donywana jest aktualizacja
 *  wsp�czynnik�w skali. Jednak je�eli aktualizacja warto�ci k�t�w nie
 *  jest konieczna, to wsp�czynniki skali r�wnie� nie s� aktualizowane.
 *  Zapisywane warto�ci wyliczane s� na podstawie aktualnych parameter�w
 *  macierzy transformacji.
 * \pre Wyliczenia b�d� poprawne wtedy i tylko wtedy gdy 
 *      wsp�czynniki skali s� r�ne od zera.
 * \post Zostaj� ustawione znaczniki wa�no�ci warto�ci parametr�w
 *       transformacji. Oznacza to, �e pobranie ich warto�ci 
 *       za pomoc� innych metoda nie b�dzie wymusza�o ponownego ich 
 *       obliczenia.
 */
void MatrixH3f::UpdateParam_XYZ_Angles_condScale()
{
  if (_Valid_RotAng && _AngInterp == AT_xyz) return;
  MatrixRT3f::GetXYZ_Angles_Scale(_RotAng,_Scale);
  ValidParam_Scale_XYZ_Angles();
}





//........................... MatrixH3f ..................................
//#############################################################################





//#############################################################################
//........................... MatrixH3f::Parameters ...........................

/*!
 * Zapisuje do pliku tekstowego lini� z zestawem parametr�w
 * transformacji
 * macierzy. Parametry te brane s� z p�l:
 *    \link MatrixH3f::Parameters::_Scale _Scale\endlink,
 *    \link MatrixH3f::Parameters::_Trans _Trans\endlink,
 *    \link MatrixH3f::Parameters::_RotAng _RotAng\endlink.
 *
 * Przyk�adowa linia zapisu parametr�w ma postac:
 *
 *  Position (1, 1.5, 1) (15.2, 14.5, 60) (10, 100, 10)
 *
 * Kolejno�� parametr�w: wsp�czynniki skali, k�ty rotacji, wsp�rz�dne
 * wektora translacji.
 *
 * \param f - wska�nik na struktur� skojarzon� z otwartym do zapisu
 *            plikiem tekstowym.
 * \pre \e f != \p NULL. Parametr skojarzony jest z plikiem otwartym do
 *        zapisu.
 * \post Po dokonaniu operacji zapisu plik nie jest zamykany i operacje
 *       zapisu mog� by� kontynuowane.
 */
int MatrixH3f::Parameters::Save(FILE *f)
{
 fprintf(f," %s ",KW_POSITION);

 fprintf(f," (%f, %f, %f)",_Scale.x,_Scale.y,_Scale.z);
 fprintf(f," (%f, %f, %f)",_RotAng.x,_RotAng.y,_RotAng.z);
 fprintf(f," (%f, %f, %f);\n",_Trans.x,_Trans.y,_Trans.z);
 return 0;
}



/*!
 *  Zapisuje do bufora znakowe \e Descr parametry transformacji (tzn.
 *  k�ty Eulera, wektor translacji i skal�).
 *  Sk�adnia zapisu:
 *  \verbatim
 *    Angles { Euler | XYZ } { Deg | Rad }: ( k�t1, k�t2, k�t3 )
 *    Translation: ( sk�adowa_x, sk�adowa_y, sk�adowa_z )
 *    Scale: ( skala_x, skala_y, skala_z ); 
 *  \endverbatim
 *
 *  \param Descr - (\b out) wpisywany do niego s� parametry opisuj�ce
 *                dan� macierz transformacji.
 *  \param  AType - okre�la rodzaj k�t�w rotacji. W tej chwili
 *                obs�ugiwane s� k�ty Eulera oraz k�ty rotacji 
 *                wok� osi OX, OY, OZ.
 *  \param  AUnit - okre�la w jakich jednostkach maj� by� zapisane
 *                warto�ci k�t�w.
 *  \param  Margin - ilo�� spacji poprzedzaj�cych kolejne linie
 *                zapisu.
 *  \retval 0 - gdy w trakcie zapisu nie wyst�pi� �aden b��d.
 */
int  MatrixH3f::WriteParamTo( ExtString    &Descr, 
                              AnglesType    AType,
                              AngleUnit     AUnit,
                              unsigned int  Margin
                            ) const
{
  MatrixH3f  Mtx = *this;

  Descr.AddSpace(Margin);
  Descr << KW_ANGLES << " ";
  switch (AType) {
   case AT_Euler: 
       Descr << KW_ANG_EULER << " ";  
       switch (AUnit) {
         case AU_Rad: Descr << KW_ANG_RAD << " " << Mtx.GetAng_Euler_Rad();  
                break;
         case AU_Deg: Descr << KW_ANG_DEG << " "  << Mtx.GetAng_Euler_Deg();  
                break;
       }
       break;

   case AT_xyz:    
       Descr << KW_ANG_XYZ << " ";  
       switch (AUnit) {
         case AU_Rad: Descr << KW_ANG_RAD << " " << Mtx.GetAng_XYZ_Rad();  
                break;
         case AU_Deg: Descr << KW_ANG_DEG << " "  << Mtx.GetAng_XYZ_Deg();  
                break;
       }
       break;
  };


  (Descr << "\n").AddSpace(Margin);

  Descr << KW_TRANSLATION << ": " << Mtx.GetTrans_TAfterR() << '\n';
  Descr.AddSpace(Margin);
  Descr << KW_SCALE << ": " << GetScale() << '\n';
  return 0;
}




/*!
 *  Zapisuje do strumienia \e ostrm parametry transformacji (tzn.
 *  k�ty Eulera, wektor translacji i skal�).
 *  Sk�adnia zapisu:
 *  \verbatim
 *    Angles { Euler | XYZ } { Deg | Rad }: ( k�t1, k�t2, k�t3 )
 *    Translation: ( sk�adowa_x, sk�adowa_y, sk�adowa_z )
 *    Scale: ( skala_x, skala_y, skala_z ); 
 *  \endverbatim
 *
 *  \param ostrm - otwarty strumie� wyj�ciowy, ze wzgl�du na hierarchi�
 *                dziedziczenia klas w bibliotece standardowej mo�e to
 *                by� r�wnie� strumie� klasy \b ofstream. 
 *  \param  LeftMargin - ilo�� spacji poprzedzaj�cych kolejne linie
 *                zapisu.
 *  \param  AType - okre�la rodzaj k�t�w rotacji. W tej chwili
 *                obs�ugiwane s� k�ty Eulera oraz k�ty rotacji 
 *                wok� osi OX, OY, OZ.
 *  \param  AUnit - okre�la w jakich jednostkach maj� by� zapisane
 *                warto�ci k�t�w.
 *  \retval 0 - gdy w trakcie zapisu nie wyst�pi� �aden b��d.
 */
int  MatrixH3f::Save( ostream      &ostrm, 
                      unsigned int  LeftMargin, 
                      AnglesType    AType,
                      AngleUnit     AUnit
                    ) const
{
  AnglesType AType_Old = GetAngInterp();
  ((MatrixH3f*)this)->SetAngInterp(AType);
  Space(ostrm,LeftMargin) << KW_ANGLES << " ";
  switch (AType) {
   case AT_Euler:  ostrm << KW_ANG_EULER << " ";  break;
   case AT_xyz:    ostrm << KW_ANG_XYZ << " ";  break;
  };
  switch (AUnit) {
   case AU_Rad: ostrm << KW_ANG_RAD << ": " << GetAng_Euler_Rad();  break;
   case AU_Deg: ostrm << KW_ANG_DEG << " " 
                      << compute_rad2deg(GetAng_Euler_Rad());  
                break;
  }
  Space(ostrm << endl, LeftMargin) << KW_TRANSLATION << ": "
              << GetTrans_TAfterR() << endl;
  Space(ostrm,LeftMargin) << KW_SCALE << ": " << GetScale() << endl;
  ((MatrixH3f*)this)->SetAngInterp(AType_Old);
  return 0;
}

//.......................... MatrixH3f::Parameters ............................
//#############################################################################



std::ostream &operator << ( std::ostream &ostr, MatrixH3f const &F )
{
  ostr << std::endl;
  std::cout << " -----------------------------" << std::endl;
  for (unsigned int ix=0; ix < DH_MAXX; ix++) {
    std::cout << "    ";
    for (unsigned int iy=0; iy < DH_MAXY; iy++) {
      std::cout << "  " << F(ix,iy);
    }
    std::cout << std::endl;
  }
  std::cout << " -----------------------------" << std::endl;
  return ostr;
}


