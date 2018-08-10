/*------------------------------------------------------------------------
 * \file        matrixh3f.cpp
 * Plik zawiera implementacjê metod klasy MatrixH3f. Jest ona podstaw±
 * wszystkich transforacji miêdzy poszczególnymi uk³adami wspó³rzêdnych.
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
 *  \brief Udostêpnia informacjê o interpretacji k±tów rotacji.
 * \endif
 *
 * Udostêpnia warto¶æ pola \link MatrixH3f::_AngInterp _AngInterp\endlink
 * informuj±c± o sposobie interpretacji k±tów rotacji, które zapisane
 * s± w polu \link MatrixH3f::_RotAng _RotAng\endlink.
 */

/*! \fn MatrixH3f::GetTransOrder() const
 * \if matrixh3f_brief_desc 
 *  \brief Udostêpnia informacjê o interpretacji translacji.
 * \endif
 *
 * Udostêpnia informacjê dotycz±c± kolejno¶ci translacji wzglêdem
 * rotacji.
 */


/*! \class MatrixH3f
 * \if matrixh3f_brief_desc 
 *  \brief Klasa modeluje macierz transformacji dla wspó³rzêdnych
 *         jednorodnych.
 * \endif
 *
 * Klasa modeluje macierz transformacji dla wspó³rzêdnych jednorodnych.
 * Pozwala ona zadawaæ transformacjê zarówno poprzez podanie k±tów Eulera
 * jak te¿ poprzez obroty wokó³ osi \e OX, \e OY, \e OZ.
 * Wektor translacji mo¿e byæ zadawany przed rotacj± lub po niej.
 *
 * Podstawow± cech± tej klasy jest to, ¿e pozwala ona odzyskiwaæ
 * warto¶ci k±tów rotacji oraz wspó³rzêdne wektora translacji.
 * W takiej konwecji jaka w danym momencie jest potrzebna niezale¿nie
 * od sposobu zadania parametrów transformacji.
 *
 * Aby unikn±æ ci±g³ych wyliczeñ parametrów transformacji, ich warto¶ci
 * s± przechowywane w odpowiednich polach. S± one aktualizowane tylko
 * wtedy gdy zachodzi taka potrzeba. Pozwala to zredukowaæ ilo¶æ
 * koniecznych obliczeñ.
 */


/*! \fn const Vector3f& MatrixH3f::GetAng_Euler_Rad() const
 * \if matrixh3f_brief_desc 
 * \brief Udostêpnia k±ty Eulera w radianach.
 * \endif
 *
 * Udostêpnia k±ty Eulera dla danej macierzy transformacji.
 * Kolejne wspó³rzêdne wektora odpowiadaj± k±tom
 *  \f$\varphi\f$ (pierwszy obrót - wokó³ osi \f$ OZ\f$),
 *  \f$\theta\f$ (drugi obrót - wokó³ osi \f$ OY'\f$),
 *  \f$\psi\f$ (trzeci obrót - wokó³ osi \f$ OZ''\f$).
 */


/*! \fn Vector3f MatrixH3f::GetAng_Euler_Deg() const
 * \if matrixh3f_brief_desc 
 * \brief Udostêpnia k±ty Eulera w stopniach.
 * \endif
 *
 * Udostêpnia k±ty Eulera dla danej macierzy transformacji.
 * Kolejne wspó³rzêdne wektora odpowiadaj± k±tom
 *  \f$\varphi\f$ (pierwszy obrót - wokó³ osi \f$ OZ\f$),
 *  \f$\theta\f$ (drugi obrót - wokó³ osi \f$ OY'\f$),
 *  \f$\psi\f$ (trzeci obrót - wokó³ osi \f$ OZ''\f$).
 */

 /*!
  * \fn  Vector3f MatrixH3f::TakeAng_XYZ_Deg() const
  * \if matrixh3f_brief_desc 
  * \brief Metoda przeznaczona do debugowania.
  * \endif
  * 
  * Metoda wymusza wyliczenie k±tów rotacji w reprezentacji \e XYZ
  * bezpo¶rednio ze wspó³czynników macierzy.
  * \warning Metoda ta przeznaczona jest do debugowania i nie powinna
  *   byæ wykorzystywana we w³a¶ciwej aplikacji, chyba ¿e programista
  *   wie na pewno co robi :).
  */

 /*!
  * \fn  Vector3f MatrixH3f::TakeAng_Euler_Deg() const
  * \if matrixh3f_brief_desc 
  * \brief Metoda przeznaczona do debugowania.
  * \endif
  * 
  * Metoda wymusza wyliczenie k±tów rotacji w reprezentacji \e Euler
  * bezpo¶rednio ze wspó³czynników macierzy.
  * \warning Metoda ta przeznaczona jest do debugowania i nie powinna
  *   byæ wykorzystywana we w³a¶ciwej aplikacji, chyba ¿e programista
  *   wie na pewno co robi :).
  */



//----------------- MatrixH3f -----------------------------------------------
//-------- Metody publiczne: ................................................

/*! \fn  float MatrixH3f::GetScaleX() const 
 * \if matrixh3f_brief_desc 
 * \brief Udostêpnia skalê dla osi \e OX.
 * \endif
 *
 * Udostêpnia wspó³czynnik skali dla osi \e OX.
 * \return wpó³czynnik skali dla osi \e OX.
 * \post Pole 
 *   \link MatrixH3f::_Valid_Scale  MatrixH3f::_Valid_Scale\endlink
 *   ma warto¶æ \p true.
 *
 * Uwaga: Pobieranie wspó³czynników skali nie zale¿y od
 *        kolejno¶ci wykonanej translacji.
 */

/*!  \fn  float MatrixH3f::GetScaleY() const
 * \if matrixh3f_brief_desc 
 * \brief Udostêpnia skalê dla osi \e OY.
 * \endif
 *
 * Udostêpnia wspó³czynnik skali dla osi \e OY.
 * \return wpó³czynnik skali dla osi \e OY.
 * \post Pole 
 *   \link MatrixH3f::_Valid_Scale  MatrixH3f::_Valid_Scale\endlink
 *   ma warto¶æ \p true.
 *
 * Uwaga: Pobieranie wspó³czynników skali nie zale¿y od
 *        kolejno¶ci wykonanej translacji.
 */

/*! \fn  float MatrixH3f::GetScaleZ() const 
 * \if matrixh3f_brief_desc 
 * \brief Udostêpnia skalê dla osi \e OZ.
 * \endif
 *
 * Udostêpnia wspó³czynnik skali dla osi \e OZ.
 * \return wpó³czynnik skali dla osi \e OZ.
 * \post Pole 
 *   \link MatrixH3f::_Valid_Scale  MatrixH3f::_Valid_Scale\endlink
 *   ma warto¶æ \p true.
 *
 * Uwaga: Pobieranie wspó³czynników skali nie zale¿y od
 *        kolejno¶ci wykonanej translacji.
 */

/*! \fn void MatrixH3f::SetScale_TAfterR(float Sx, float Sy, float Sz)
 * \if matrixh3f_brief_desc 
 * \brief Ustawia now± skalê dla przypadku translacji po rotacji.
 * \endif
 *
 * Wstawia now± skalê przyjmuj±c, ¿e aktualne wspó³czynniki
 * macierzy przekszta³cenia jednorodnego odpowiadaj± przypadkowi,
 * gdy translacja jest realizowana po rotacji. W takim przypadku
 * operacja nie powoduje zmiany czwartej kolumny macierzy transformacji,
 * która w tej interpretacji odpowiada bezpo¶rednio wektorowi translacji.
 * \param Sx - (\b in) wspó³czynnik skali dla osi \e OX.
 * \param Sy - (\b in) wspó³czynnik skali dla osi \e OY.
 * \param Sz - (\b in) wspó³czynnik skali dla osi \e OZ.
 * \pre ¯aden ze wspó³czynników skali nie mo¿e byæ równy 0.
 *      Je¿eli dla danej osi wcze¶niej wspó³czynnik skali by³ ustawiony
 *      na warto¶æ 0, to dla tej osi przeskalowanie nie jest realizowane.
 * \post Pole
 *  \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink
 *  ma warto¶æ \p true.
 */

/*! \fn  void MatrixH3f::SetScaleX_TAfterR(float Sx)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia now± skalê osi \e OX dla przypadku translacji po rotacji. 
 * \endif
 *
 * Wstawia now± skalê dla osi \e OX przyjmuj±c, ¿e aktualne wspó³czynniki
 * macierzy przekszta³cenia jednorodnego odpowiadaj± przypadkowi,
 * gdy translacja jest realizowana po rotacji. W takim przypadku
 * operacja nie powoduje zmiany czwartej kolumny macierzy transformacji,
 * która w tej interpretacji odpowiada bezpo¶rednio wektorowi translacji.
 * \param Sx - (\b in) wspó³czynnik skali dla osi \e OX.
 * \pre Wspó³czynnik skali nie mo¿e byæ równy 0.
 *      Je¿eli dla danej osi wcze¶niej wspó³czynnik skali by³ ustawiony
 *      na warto¶æ 0, to przeskalowanie nie jest realizowane.
 */

/*! \fn void MatrixH3f::SetScaleY_TAfterR(float Sy)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia now± skalê osi \e OY dla przypadku translacji po rotacji. 
 * \endif
 *
 * Wstawia now± skalê dla osi \e OY przyjmuj±c, ¿e aktualne wspó³czynniki
 * macierzy przekszta³cenia jednorodnego odpowiadaj± przypadkowi,
 * gdy translacja jest realizowana po rotacji. W takim przypadku
 * operacja nie powoduje zmiany czwartej kolumny macierzy transformacji,
 * która w tej interpretacji odpowiada bezpo¶rednio wektorowi translacji.
 * \param Sy - (\b in) wspó³czynnik skali dla osi \e OY.
 * \pre Wspó³czynnik skali nie mo¿e byæ równy 0.
 *      Je¿eli dla danej osi wcze¶niej wspó³czynnik skali by³ ustawiony
 *      na warto¶æ 0, to przeskalowanie nie jest realizowane.
 */

/*! \fn void MatrixH3f::SetScaleZ_TAfterR(float Sz)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia now± skalê osi \e OZ dla przypadku translacji po rotacji. 
 * \endif
 *
 * Wstawia now± skalê dla osi \e OZ przyjmuj±c, ¿e aktualne wspó³czynniki
 * macierzy przekszta³cenia jednorodnego odpowiadaj± przypadkowi,
 * gdy translacja jest realizowana po rotacji. W takim przypadku
 * operacja nie powoduje zmiany czwartej kolumny macierzy transformacji,
 * która w tej interpretacji odpowiada bezpo¶rednio wektorowi translacji.
 * \param Sz - (\b in) wspó³czynnik skali dla osi \e OZ.
 * \pre Wspó³czynnik skali nie mo¿e byæ równy 0.
 *      Je¿eli dla danej osi wcze¶niej wspó³czynnik skali by³ ustawiony
 *      na warto¶æ 0, to przeskalowanie nie jest realizowane.
 */


/*! \fn const Vector3f &MatrixH3f::GetTrans_TBeforeR() const
 * \if matrixh3f_brief_desc 
 *  \brief Udostêpnia wektor translacji dla przypadku translacji przed rotacj±
 * \endif
 *
 * Metoda udostêpnia wektor translacji traktowanej jako translacja
 * przed rotacj±, tzn.
 * \f[
      F = R \circ S \circ T
   \f]
 * Przed udostêpnieniem tych warto¶ci metoda dokonuje aktualizacji
 * (o ile jest ona konieczna) warto¶ci parametrów na podstawie
 * warto¶ci wspó³czynników macierzy.
 */

/*! \fn void MatrixH3f::SetAng_XYZ_TBeforeR_Rad(const Vector3f &Angles)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia now± rotacjê w reprezentacji \e XYZ dla translacji
 *         przed rotacj±.
 * \endif
 *
 *  Nadaje nowe warto¶ci k±tom rotacji danej transformacji
 *  w reprezentacji \e XYZ.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±tów powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w radianach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = R \circ S \circ T
    \f]
 *  \param Angles - (\b in) wektor warto¶ci k±tów 
 *        odpowiednio \f$\alpha\f$ (rotacja wokó³ osi \f$ OX\f$).
 *        \f$\beta\f$ (rotacja wokó³ osi \f$ OY'\f$)
 *       oraz  \f$\gamma\f$ (rotacja wokó³ osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
 */


/*! \fn  void MatrixH3f::SetAng_XYZ_TBeforeR_Deg(float Ax, float Ay, float Az)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia now± rotacjê w reprezentacji \e XYZ dla translacji przed
 *         rotacj±.
 * \endif
 *
 *  Nadaje nowe warto¶ci k±tom rotacji danej transformacji
 *  w reprezentacji \e XYZ.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±tów powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w stopniach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = R \circ S \circ T
    \f]
 *  \param Ax - (\b in) warto¶æ k±ta \f$\alpha\f$ 
 *                     (rotacja wokó³ osi \f$ OX\f$).
 *  \param Ay - (\b in) warto¶æ k±ta \f$\beta\f$ 
 *                    (rotacja wokó³ osi \f$ OY'\f$).
 *  \param Az - (\b in) warto¶æ k±ta \f$\gamma\f$ 
 *                    (rotacja wokó³ osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
 */


/*! \fn void MatrixH3f::SetAng_XYZ_TAfterR_Rad( const Vector3f &Angles )
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia now± rotacjê w reprezentacji \e XYZ dla translacji
 *         po rotacji.
 * \endif
 *
 *  Nadaje nowe warto¶ci k±tom rotacji danej transformacji
 *  w reprezentacji \e XYZ.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±tów powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w radianach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Angles - (\b in) wektor warto¶ci k±tów 
 *        odpowiednio \f$\alpha\f$ (rotacja wokó³ osi \f$ OX\f$).
 *        \f$\beta\f$ (rotacja wokó³ osi \f$ OY'\f$)
 *       oraz  \f$\gamma\f$ (rotacja wokó³ osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
 */




/*! \fn void MatrixH3f::SetAng_XYZ_TAfterR_Deg( const Vector3f &Angles )
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia now± rotacjê w reprezentacji \e XYZ dla translacji
 *         po rotacji.
 * \endif
 *
 *  Nadaje nowe warto¶ci k±tom rotacji danej transformacji
 *  w reprezentacji \e XYZ.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±tów powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w stopniach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Angles - (\b in) wektor warto¶ci k±tów 
 *        odpowiednio \f$\alpha\f$ (rotacja wokó³ osi \f$ OX\f$).
 *        \f$\beta\f$ (rotacja wokó³ osi \f$ OY'\f$)
 *       oraz  \f$\gamma\f$ (rotacja wokó³ osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
 */







/*! \fn void MatrixH3f::SetAng_XYZ_TAfterR_Deg(float Ax, float Ay, float Az)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia now± rotacjê w reprezentacji \e XYZ dla translacji
 *         po rotacji.
 * \endif
 *
 *  Nadaje nowe warto¶ci k±tom rotacji danej transformacji
 *  w reprezentacji \e XYZ.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±tów powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w stopniach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Ax - (\b in) warto¶æ k±ta \f$\alpha\f$ 
 *                     (rotacja wokó³ osi \f$ OX\f$).
 *  \param Ay - (\b in) warto¶æ k±ta \f$\beta\f$ 
 *                    (rotacja wokó³ osi \f$ OY'\f$).
 *  \param Az - (\b in) warto¶æ k±ta \f$\psi\f$ 
 *                    (rotacja wokó³ osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
 */




/*! \fn  void MatrixH3f::SetAng_XYZoX_TAfterR_Deg(float Ax)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy pierwszy k±t rotacji w reprezentacji 
 *         \e XYZ dla translacji po rotacji.
 * \endif
 *
 *  Ustawia nowy pierwszy k±t rotacji w reprezentacji 
 *  \e XYZ dla translacji po rotacji.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±ta powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶æ k±ta wyra¿ona jest
 *  w stopniach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Ax - (\b in) warto¶æ k±ta \f$\alpha\f$ 
 *                     (rotacja wokó³ osi \f$ OX\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
 */



/*! \fn void MatrixH3f::SetAng_Euler_TBeforeR_Rad(const Vector3f &Angles)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowe k±ty rotacji Eulera
 *         dla translacji przed rotacj±.
 * \endif
 *
 *  Nadaje nowe warto¶ci k±tom Eulera danej transformacji.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±tów powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w radianach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F =  R \circ S \circ T
    \f]
 *  \param Angles - (\b in) wektor warto¶ci k±tów Eulera.
 *      jego kolejne wspó³rzêdne odpowiadaj± k±tom \f$\varphi\f$ 
 *                     (rotacja wokó³ osi \f$ OZ\f$),
 *     \f$\theta\f$ (rotacja wokó³ osi \f$ OY'\f$),
 *     \f$\psi\f$   (rotacja wokó³ osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
 */


/*! \fn  void MatrixH3f::SetAng_Euler_TBeforeR_Deg(float VPhi, 
                                                    float Theta, float Psi)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowe k±ty rotacji Eulera
 *         dla translacji przed rotacj±.
 * \endif
 *
 *  Nadaje nowe warto¶ci k±tom Eulera danej transformacji.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±tów powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w stopniach. Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F =  R \circ S \circ T
    \f]
 *  \param VPhi - (\b in) warto¶æ k±ta \f$\varphi\f$ 
 *                     (rotacja wokó³ osi \f$ OZ\f$).
 *  \param Theta - (\b in) warto¶æ k±ta \f$\theta\f$ 
 *                    (rotacja wokó³ osi \f$ OY'\f$).
 *  \param Psi - (\b in) warto¶æ k±ta \f$\psi\f$ 
 *                    (rotacja wokó³ osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
 */



/*!
 * \fn void MatrixH3f::SetAng_XYZoY_TAfterR_Rad(float Ay)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy drugi k±t rotacji w reprezentacji 
 *         \e XYZ dla translacji po rotacji.
 * \endif
 *
 *  Ustawia nowy drugi k±t rotacji w reprezentacji 
 *  \e XYZ dla translacji po rotacji.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±ta powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶æ k±ta wyra¿ona jest
 *  w radianach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Ay - (\b in) warto¶æ k±ta \f$\alpha\f$ 
 *                     (rotacja wokó³ osi \f$ OY'\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
 */


/*!
 * \fn void MatrixH3f::SetAng_XYZoY_TAfterR_Deg(float Ay)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy drugi k±t rotacji w reprezentacji 
 *         \e XYZ dla translacji po rotacji.
 * \endif
 *
 *  Ustawia nowy drugi k±t rotacji w reprezentacji 
 *  \e XYZ dla translacji po rotacji.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±ta powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶æ k±ta wyra¿ona jest
 *  w stopniach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Ay - (\b in) warto¶æ k±ta \f$\alpha\f$ 
 *                     (rotacja wokó³ osi \f$ OY'\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
 */


/*! \fn void MatrixH3f::SetAng_XYZoZ_TAfterR_Deg(float Az)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy trzeci k±t rotacji w reprezentacji 
 *         \e XYZ dla translacji po rotacji.
 * \endif
 *
 *  Ustawia nowy trzeci k±t rotacji w reprezentacji 
 *  \e XYZ dla translacji po rotacji.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±ta powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶æ k±ta wyra¿ona jest
 *  w stopniach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Az - (\b in) warto¶æ k±ta \f$\alpha\f$ 
 *                     (rotacja wokó³ osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
 */


/*! \fn  void MatrixH3f::SetAng_XYZoY_TBeforeR_Deg(float Ay)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy drugi k±t rotacji w reprezentacji 
 *         \e XYZ dla translacji przed rotacj±. 
 * \endif
 *
 *  Nadaje now± warto¶æ drugiemu k±towi rotacji danej transformacji
 *  w reprezentacji \e XYZ.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±tów powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w stopniach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = R \circ S \circ T
    \f]
 *  \param Ay - (\b in) warto¶æ k±ta \f$\alpha\f$ 
 *                     (rotacja wokó³ osi \f$ OY'\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
 */



/*!\fn void MatrixH3f::SetAng_XYZoZ_TBeforeR_Deg(float Az)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy trzeci k±t rotacji w reprezentacji 
 *         \e XYZ dla translacji przed rotacj±. 
 * \endif
 *
 *  Nadaje now± warto¶æ trzeciemu k±towi rotacji danej transformacji
 *  w reprezentacji \e XYZ.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±tów powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w stopniach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = R \circ S \circ T
    \f]
 *  \param Az - (\b in) warto¶æ k±ta \f$\alpha\f$ 
 *                     (rotacja wokó³ osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
 */



/*! \fn void MatrixH3f::AddAng_XYZ_TBeforeR_Rad( const Vector3f &d_Angles )
 * \if matrixh3f_brief_desc 
 *  \brief Dodaje do k±tów rotacji w reprezentacji \e XYZ dla translacji
 *         przed rotacj±
 * \endif
 * 
 * Dodaje podane warto¶ci do aktalnych warto¶ci k±tów rotacji 
 * w reprezentacji \e XYZ i aktualizuje
 * macierz transformacji. Warto¶ci k±tów wyra¿one s± w radianach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = R \circ S \circ T
   \f]
 * \param d_Angles - (\b in) wektor warto¶ci k±tów rotacji w reprezentacji
 *               \e XYZ o które maj± byæ zwiêkszone aktualne k±ty rotacji
 *             dla danej transformacji. Kolejne wspó³rzêdne reprezentuj±
 *               odpowiednio \f$\Delta\alpha\f$ (obrót wokó³ osi \f$ OX\f$),
 *              \f$\Delta\beta\f$ (obrót wokó³ osi \f$ OY'\f$,
 *              \f$\Delta\gamma\f$ (obrót wokó³ osi \f$ OZ''\f$).
 * \post Do k±tów transformacji dodane zostaj± podane warto¶ci
 *       oraz zostaje zaaktualizowana macierz wspó³czynników transformacji.
 */


/*! \fn void MatrixH3f::AddAng_XYZ_TBeforeR_Deg( float d_Ax, float d_Ay, 
                                                  float d_Az )
 * \if matrixh3f_brief_desc 
 *  \brief Dodaje do k±tów rotacji w reprezentacji \e XYZ dla translacji
 *         przed rotacj±
 * \endif
 *
 * Dodaje podane warto¶ci do aktalnych warto¶ci k±tów rotacji 
 * w reprezentacji \e XYZ i aktualizuje
 * macierz transformacji. Warto¶ci k±tów wyra¿one s± w stopniach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F =  R \circ S  \circ T
   \f]
 * \param d_Ax - (\b in) warto¶æ o któr± ma byæ zwiêkszony k±t \f$\alpha\f$
 *               (obrót wokó³ osi \f$ OX\f$).
 * \param d_Ay -  (\b in) warto¶æ o któr± ma byæ zwiêkszony k±t \f$\beta\f$
 *               (obrót wokó³ osi \f$ OY'\f$.
 * \param d_Az -  (\b in) warto¶æ o któr± ma byæ zwiêkszony k±t \f$\gamma\f$
 *               (obrót wokó³ osi \f$ OZ''\f$).
 * \post Do k±tów transformacji dodane zostaj± podane warto¶ci
 *       oraz zostaje zaaktualizowana macierz wspó³czynników transformacji.
 */



/*! \fn MatrixH3f::SetAng_XYZoX_TBeforeR_Deg(float Ax)
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia nowy pierwszy k±t rotacji w reprezentacji 
 *         \e XYZ dla translacji przed rotacj±. 
 * \endif
 *
 *  Nadaje now± warto¶æ pierwszemu k±towi rotacji danej transformacji
 *  w reprezentacji \e XYZ.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±tów powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w stopniach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = R \circ S \circ T
    \f]
 *  \param Ax - (\b in) warto¶æ k±ta \f$\alpha\f$ 
 *                     (rotacja wokó³ osi \f$ OX\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
 */



/*! \fn void MatrixH3f::SetAng_Euler_TAfterR_Rad(const Vector3f &Angles)
 * \if matrixh3f_brief_desc
 *  \brief Nadaje nowe warto¶ci k±tom Eulera dla transformacji z translacj±
 *         po rotacji.
 * \endif
 *
 *  Nadaje nowe warto¶ci k±tom Eulera danej transformacji.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±tów powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w radianach. Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F =  T \circ R \circ S
    \f]
 *  \param Angles - (\b in) wektor warto¶ci k±tów Eulera.
 *      jego kolejne wspó³rzêdne odpowiadaj± k±tom \f$\varphi\f$ 
 *                     (rotacja wokó³ osi \f$ OZ\f$),
 *     \f$\theta\f$ (rotacja wokó³ osi \f$ OY'\f$),
 *     \f$\psi\f$   (rotacja wokó³ osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
 */



/*! \fn void MatrixH3f::SetAng_Auto_TAfterR_Rad( const Vector3f &Angles,
                                                 const Vector3f &Scale 
                                               )
 * \if matrixh3f_brief_desc
 *  \brief Nadaje nowe warto¶ci k±tom rotacji zachowuj±c dotychczasow±
 *         interpretacjê.
 * \endif
 *
 *  Nadaje nowe warto¶ci k±tom rotacji danej transformacji.
 *  Metoda interpretuje k±ty zgodnie z ich wcze¶niejsz± interpretacj±,
 *  o której decyduje warto¶æ pola 
 *  \link MatrixH3f::_AngInterp _AngInterp\endlink.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±tów powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w radianach. Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F =  T \circ R \circ S
    \f]
 *  \param Angles - (\b in) wektor warto¶ci k±tów rotacji.
 *              Ich interpretacja zale¿y od dotychczasowej warto¶ci
 *              pola \link MatrixH3f::_AngInterp _AngInterp\endlink.
 *  \param Scale - (\b in) wektor warto¶ci skali dla poszczególnych osi.
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
 */





/*! \fn void MatrixH3f::SetAng_EulerVPhi_TBeforeR_Deg(float VPhi)
 * \if matrixh3f_brief_desc
 *  \brief Ustawia warto¶æ k±ta Eulera \f$\varphi\f$ dla transformacji z translacj±
 *         przed rotacj±
 * \endif
 *
 *  Nadaje nowe warto¶æ k±ta Eulera \f$\varphi\f$ danej transformacji.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie warto¶ci k±ta powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w stopniach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F =  R \circ S \circ T
    \f]
 *  \param VPhi - (\b in) warto¶æ k±ta \f$\varphi\f$ 
 *                     (rotacja wokó³ osi \f$ OZ\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
 */


/*! \fn void MatrixH3f::SetAng_EulerTheta_TBeforeR_Rad(float Theta)
 * \if matrixh3f_brief_desc
 *  \brief Ustawia warto¶æ k±ta Eulera \f$\theta\f$ dla transformacji
 *   z translacj± przed rotacj±
 * \endif
 *
 *  Nadaje nowe warto¶æ k±ta Eulera \f$\theta\f$ danej transformacji.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie warto¶ci k±ta powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w radianach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F =  R \circ S \circ T
    \f]
 *  \param Theta - (\b in) warto¶æ k±ta \f$\theta\f$ 
 *                     (rotacja wokó³ osi \f$ OY'\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
 */

/*! \fn void MatrixH3f::SetAng_EulerTheta_TBeforeR_Deg(float Theta)
 * \if matrixh3f_brief_desc
 *  \brief Ustawia warto¶æ k±ta Eulera \f$\theta\f$ dla transformacji 
 *   z translacj± przed rotacj±
 * \endif
 *
 *  Nadaje nowe warto¶æ k±ta Eulera \f$\theta\f$ danej transformacji.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie warto¶ci k±ta powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w stopniach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F =  R \circ S \circ T
    \f]
 *  \param Theta - (\b in) warto¶æ k±ta \f$\theta\f$ 
 *                     (rotacja wokó³ osi \f$ OY'\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
 */




/*! \fn void MatrixH3f::SetAng_EulerPsi_TBeforeR_Deg(float Psi)
 * \if matrixh3f_brief_desc
 *  \brief Ustawia warto¶æ k±ta Eulera \f$\psi\f$ dla transformacji z translacj±
 *         przed rotacj±
 * \endif
 *
 *  Nadaje nowe warto¶æ k±ta Eulera \f$\psi\f$ danej transformacji.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie warto¶ci k±ta powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w stopniach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F =  R \circ S \circ T
    \f]
 *  \param Psi - (\b in) warto¶æ k±ta \f$\psi\f$ 
 *                     (rotacja wokó³ osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
 */


/*! \fn Vectore3f MatrixH3f::GetAng_XYZ_Deg() const 
 * \if matrixh3f_brief_desc 
 * \brief Udostêpnia k±ty w reprezentacji \e XYZ w stopniach.
 * \endif
 *
 * Udostêpnia k±ty obrotu wzglêdem osi \f$ OX\f$, \f$ OY'\f$ oraz \f$ OZ''\f$
 * dla danej macierzy transformacji.
 * Kolejne wspó³rzêdne wektora odpowiadaj± k±tom
 *  \f$\alpha\f$ (pierwszy obrót - wokó³ osi \f$ OX\f$),
 *  \f$\beta\f$ (drugi obrót - wokó³ osi \f$ OY'\f$),
 *  \f$\gamma\f$ (trzeci obrót - wokó³ osi \f$ OZ''\f$).
 * Udostêpniane warto¶ci k±tów wyra¿one s± w stopniach.
 */



//===========================================================================
//..................  MatrixH3f::Parameters  ................................
//...........................................................................

/*! \class MatrixH3f::Parameters
 *  \brief Klasa zawiera parametry transformacji
 *
 * Klasa zawiera parametry transformacji dla macierzy przekszta³cenia
 * we wspó³rzêdnych jednorodnych (k±ty rotacji, wektor translacji i
 * skale wzd³u¿ osi OX, OY, OZ.
 */


/*! \fn  void MatrixH3f::Parameters::SetAngX_Rad(float ang)
 * \if matrixh3f_brief_desc 
 *  \brief Nadaje now± warto¶æ pierwszemu k±towi rotacji.
 * \endif
 *
 *  Podstawia now± warto¶æ k±ta rotacji wzglêdem osi OX.
 *  K±t wyra¿ony musi byæ w radianach.  Warto¶ci pozosta³ych k±tów
 *  nie ulegaj± zmianie.
 *  \param ang - nowa warto¶æ rotacji wzglêdem osi OX. 
 */



/*! \fn void MatrixH3f::Parameters::SetAng( const Vector3f  &Ang, 
                                            AngleUnit        AngUnit ) 
 * \if matrixh3f_brief_desc 
 *  \brief Nadaje nowe warto¶ci k±tom rotacji.
 * \endif
 *
 *  Nadaje nowe warto¶ci k±tom rotacji. Warto¶ci k±tów domy¶lnie 
 *  wyra¿one s± w radianach. Mo¿na jednak wyraziæ je w stopniach.
 *  O tym w jakich jednostkach s± wyra¿one k±ty decyduje
 *  parametr \e AngUnit.
 *  \param Ang - wektor nowych warto¶ci k±tów rotacji.
 *  \param AngUnit - zawiera informacjê o tym w jakich jednostkach s±
 *                   wyra¿one k±ty.
 *  \post Nowe warto¶ci k±tów rotacji zostaj± wpisane do
 *        pola \link MatrixH3f::Parameters::_RotAng _RotAng\endlink.
 */


/*! \var MatrixH3f::Parameters::_AngInterp
 *  \brief Reprezentacja k±tów rotacji
 *
 *  Okre¶la czy warto¶ci k±tów rotacji w polu  
 *  \link Parameters::_RotAng  _RotAng\endlink nale¿y interpretowaæ jako
 *  k±ty Eulera (warto¶æ \p AT_Euler) czy te¿ jako k±ty obrotu 
 *  wzglêdem osi OX, OY i OZ (warto¶æ \p AT_xyz).
 */

/*! \var MatrixH3f::Parameters::_TransOrder
 *
 *  \brief Porz±dek translacji wzglêdem rotacji
 *
 * Warto¶æ pola okre¶la czy parametry transformacji 
 * \link MatrixH3f::_Trans _Trans\endlink
 * odpowiada translacji po rotacji (\p true),
 * czy te¿ przed (\p false).
 */

/*! \var MatrixH3f::Parameters::_RotAng
 *  \brief K±ty rotacji
 *
 *  Kolejne wspó³rzêdne wektora zawieraj± warto¶ci k±tów rotacji 
 *  wzglêdem osi OX, OY i OZ lub te¿ k±ty Eulera.
 *  Warto¶ci k±tów wyra¿one s± w radianach.
 *
 *  Je¿eli przyjêta jest reprezentacja za pomoc± k±tów Eulera,
 *  to kolejne wspó³rzêdne wektora zawieraj± k±ty:
 *  \f$ \varphi \f$ (obrót wokó³ osi \f$ OZ\f$), \f$ \theta\f$
 *  (obrót wokó³ chwilowej osi \f$ OY'\f$) oraz \f$\psi\f$
 *  (obrót wokó³ chwilowej osi \f$ OZ''\f$).
 */

/*! \var MatrixH3f::Parameters::_Trans
 *  \brief  Wektor translacji.
 *
 *  Pole zawiera wektor translacji pocz±tku uk³adu wspó³rzêdnych.
 */

/*! \var MatrixH3f::Parameters::_Scale
 *  \brief Skala dla poszczególnych osi \e OX, \e OY oraz \e OZ
 *
 *  Kolejne wspó³rzêdne wektora zawieraj± warto¶ci wspó³czynników
 *  skali dla poszczególnych osi.
 */


/*! \fn void MatrixH3f::SetScale_TBeforeR(float Sx, float Sy, float Sz)
 * \brief Ustawia now± skalê dla przypadku translacji po rotacji.
 *
 * Ustawia now± skalê przyjmuj±c, ¿e aktualne wspó³czynniki
 * macierzy przekszta³cenia jednorodnego odpowiadaj± przypadkowi,
 * gdy translacja jest realizowana przed rotacj±. W takim przypadku
 * operacja nie powoduje zmiany czwartej kolumny macierzy transformacji,
 * która w tej interpretacji odpowiada bezpo¶rednio wektorowi translacji.
 * \param Sx - (\b in) wspó³czynnik skali osi \e OX.
 * \param Sy - (\b in) wspó³czynnik skali osi \e OY.
 * \param Sz - (\b in) wspó³czynnik skali osi \e OZ.
 * \pre ¯aden ze wspó³czynników skali nie mo¿e byæ równy 0.
 *      Je¿eli dla danej osi wcze¶niej wspó³czynnik skali by³ ustawiony
 *      na warto¶æ 0, to dla tej osi przeskalowanie nie jest realizowane.
 * \post Pole
 *  \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink
 *  ma warto¶æ \p true.
 */



//--------------- MatrixH3f::Parameters ---------------------------------
//------ Metody publiczne: ..............................................

/*! \fn void MatrixH3f::Parameters::SetTrans(float x, float y, float z)
 *  Nadaje nowe wspó³rzêdnym wektora translacji.
 *  \param x - nowa warto¶æ wspó³rzêdnej \e x wektora translacji,
 *  \param y - nowa warto¶æ wspó³rzêdnej \e y wektora translacji,
 *  \param z - nowa warto¶æ wspó³rzêdnej \e z wektora translacji.
 *  \post Nowe warto¶ci wspó³czynników skali zostaj± wpisane do
 *        pola \link MatrixH3f::Parameters::_Trans _Trans\endlink.
 */

/*! \fn void MatrixH3f::Parameters::SetAngInterp(AnglesType ATyp)
 *  \brief Ustawia sposób interpretacji k±tów rotacji.
 *
 * Ustawia sposób interpretacji k±tów rotacji.
 * \param ATyp - nowa wartosc dla pola 
 * \link Parameters::_AngInterp _AngInterp\endlink informuj±ca o sposobie
 *  interpretacji k±tów rotacji.
 * \post Zostaje zmodyfikowna warto¶æ pola 
 *  \link Parameters::_AngInterp _AngInterp\endlink.
 */

/*! \fn AnglesType MatrixH3f::Parameters::GetAngInterp() const
 *  \brief Udostêpnia typ reprezentacji k±tów rotacji. 
 *
 * Udostêpnia warto¶æ pola \link Parameters::_AngInterp _AngInterp\endlink
 * informuj±c± o sposobie interpretacji k±tów rotacji, które zapisane
 * s± w polu \link Parameters::_RotAng _RotAng\endlink.
 */

/*! \fn Parameters &MatrixH3f::Parameters::SetTransType(TransOrder TOrder)
 * \brief Ustawia interpretacjê kolejno¶ci translacji wzglêdem rotacji.
 *
 * Wprowadza i zapamiêtuje informacjê o kolejno¶ci wykonania translacji, tzn.
 * czy wykonana zosta³a przed rotacj±, czy te¿ po.
 * \param TOrder - informacja o kolejno¶ci wykonania translacji wzglêdem rotacji.
 */


/*! \fn void MatrixH3f::Parameters::SetAng_Rad( float ax_rad, float ay_rad,
                                                                   float az_rad )
 *  \brief Nadaje nowe warto¶ci k±tom rotacji
 *
 *  Nadaje nowe warto¶ci k±tom rotacji. Warto¶ci k±tów 
 *  wyra¿one s± w radianach.
 *  \param ax_rad - nowa warto¶æ pierwszego k±ta rotacji,
 *  \param ay_rad - nowa warto¶æ drugiego k±ta rotacji,
 *  \param az_rad - nowa warto¶æ trzeciego k±ta rotacji.
 *  \post Nowe warto¶ci k±tów rotacji zostaj± wpisane do
 *        pola \link MatrixH3f::Parameters::_RotAng _RotAng\endlink.
 */

/*! \fn void MatrixH3f::Parameters::SetAng( float ax, float ay, float az, 
                                                           AngleUnit AngUnit )
 *  \brief Nadaje nowe warto¶ci k±tów rotacji.
 *
 *  Nadaje nowe warto¶ci k±tów rotacji. Warto¶ci k±tów domy¶lnie 
 *  wyra¿one s± w radianach. Mo¿na jednak wyraziæ je w stopniach.
 *  O tym w jakich jednostkach s± wyra¿one k±ty decyduje
 *  parametr \e AngUnit.
 *  \param ax - nowa warto¶æ pierwszego k±ta rotacji,
 *  \param ay - nowa warto¶æ drugiego k±ta rotacji,
 *  \param az - nowa warto¶æ trzeciego k±ta rotacji.
 *  \param AngUnit - zawiera informacjê o tym w jakich jednostkach s±
 *                   wyra¿one k±ty.
 *  \post Nowe warto¶ci k±tów rotacji zostaj± wpisane do
 *        pola \link MatrixH3f::Parameters::_RotAng _RotAng\endlink.
 */




namespace Vi {
  /*!
   *  Funkcja zwraca nazwê odpowiadaj±c± danej warto¶ci typu
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
   *  Funkcja dokonuje konwersji nazwy warto¶ci typu 
   * \link matrixh3f.hh::TransOrder TransOrder\endlink na warto¶æ 
   * tego typu.\n
   * Zestaw dopuszczalnych nazw zdefiniowany jest poprzez sta³e:
   *  \li \link vi-kewords.hh::KW__TO_BEFORE KW__TO_BEFORE\endlink
   *  \li \link vi-kewords.hh::KW__TO_AFTER KW__TO_AFTER\endlink
   * \param Name - nazwa warto¶ci typu  
   *               \link matrixh3f.hh::TransOrder TransOrder\endlink
   * \exception ViException z kodem b³êdu \link
   *                 vierrors.hh::ERRNUM_TRANSORDER__IMPROPER_NAME
   *                 ERRNUM_TRANSORDER__IMPROPER_NAME\endlink
   *            w przypadku, gdy nazwa nie odpowiada ¿adnej z oczekiwanych
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
 *  Sprawdza czy dana warto¶æ jest wiêksza lub mniejsza od warto¶ci 
 *  \link matrixh3f.cpp::D_VERYSMALLPLUS D_VERYSMALLPLUS\endlink.
 *  Je¿eli nie, to podstawia warto¶æ
 *  \link matrixh3f.cpp::D_VERYSMALLPLUS D_VERYSMALLPLUS\endlink.
 */
float MakeDT_0(float Val)
{
  return Val > D_VERYSMALLPLUS ? Val : 
         Val < -D_VERYSMALLPLUS ? Val : D_VERYSMALLPLUS;
}


/*!
 *  Powoduje, ¿e ka¿da wspó³rzêdna wektora bêdzie wiêksza 
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
 *  Aktualizuje zawarto¶æ pola 
 *  \link MatrixH3f::_Trans  _Trans\endlink traktuj±c wektor translacji
 *  jako translacjê po rotacji.
 *  \post Pole  \link MatrixH3f::_Trans  _Trans\endlink
 *    zwiera aktualn± warto¶æ wektora translacji wyliczonego
 *    na podstawie wspó³czynników macierzy transformacji.
 *    Wektor translacji traktowany jest jako translacja po
 *    rotacji, tzn.
 * \f[
     F = R \circ S \circ T
   \f]
 *    Ponadto pola
 *    \link MatrixH3f::_Valid_Trans _Valid_Trans\endlink
 *     oraz 
 *    \link MatrixH3f::_Trans_Order _Trans_Order\endlink
 *    maj± warto¶æ \p TO_After.
 */
void MatrixH3f::UpdateParam_Trans_TAfterR()
{
  if ((_Trans_Order == TO_After) && _Valid_Trans)  return;
  MatrixRT3f::GetTrans_TAfterR(_Trans);
  ValidParam_Trans_TAfterR();
}


/*!
 *  Aktualizuje zawarto¶æ pola 
 *  \link MatrixH3f::_Trans  _Trans\endlink traktuj±c wektor translacji
 *  jako translacjê po rotacji.
 *  \post Pole  \link MatrixH3f::_Trans  _Trans\endlink
 *    zwiera aktualn± warto¶æ wektora translacji wyliczonego
 *    na podstawie wspó³czynników macierzy transformacji.
 *    Wektor translacji traktowany jest jako translacja przed
 *    skalowaniem i rotacj±, tzn.
 * \f[
       F = T \circ R \circ S
   \f]
 * Ponadto pola
 *    \link MatrixH3f::_Valid_Trans _Valid_Trans\endlink
 *     oraz 
 *    \link MatrixH3f::_Trans_Order _Trans_Order\endlink
 *    maj± warto¶æ \p TO_Before.
 */
void MatrixH3f::UpdateParam_Trans_TBeforeR()
{
  if ((_Trans_Order == TO_Before) && _Valid_Trans)  return;
  MatrixRT3f::GetTrans_TBeforeR(_Trans);
  ValidParam_Trans_TBeforeR();
}



/*!
 *  \brief Udostêpnia wektor translacji dla przypadku translacji po rotacji
 *
 * Metoda udostêpnia wektor translacji traktowanej jako translacja
 * po rotacji, tzn.
 * \f[
       F = T \circ R \circ S
   \f]
 * Przed udostêpnieniem tych warto¶ci metoda dokonuje aktualizacji
 * (o ile jest ona konieczna) warto¶ci parametrów na podstawie
 * warto¶ci wspó³czynników macierzy.
 */
const Vector3f &MatrixH3f::GetTrans_TAfterR() const
{
  USE(MatrixH3f).UpdateParam_Trans_TAfterR();
  return _Trans;
}




/*!
 * Nadaje now± warto¶æ wektorowi translacji.
 * Zak³ada siê, ¿e translacja ma byæ wykonana przed skalowaniem i rotacj±,
 *  tzn.
 *  \f[
        F = R \circ S \circ T
    \f]
 * \param Tx - nowa warto¶æ wspó³rzêdnej \e x-owej wektora translacji.
 * \param Ty - nowa warto¶æ wspó³rzêdnej \e y-owej wektora translacji.
 * \param Tz - nowa warto¶æ wspó³rzêdnej \e z-owej wektora translacji.
 * \post Do pola \link MatrixH3f::_Trans _Trans\endlink zostaje wpisany
 *       nowy wektor translacji przekazany przez parametr \e T.
 *       Wpisany zostaje on równie¿ do 4 kolumny macierzy wspó³czynników
 *       transformacji (patrz opis pola 
 *       \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink)
 *       zachowuj±c aktualno¶æ
 *       wyliczeñ wpó³czynników tej macierzy.
 *       
 *       Dzia³anie metody powoduje przypisanie polom 
 *    \link MatrixH3f::_Valid_Trans  MatrixH3f::_Valid_Trans\endlink
 *    oraz 
 *    \link MatrixH3f::_Trans_Order MatrixH3f::_Trans_Order \endlink
 *    warto¶ci \p TO_Before.
 */
void  MatrixH3f::SetTrans_TBeforeR(float Tx, float Ty, float Tz)
{ 
  _Trans.Set(Tx,Ty,Tz); 
  MatrixRT3f::SetTrans_TBeforeR(Tx,Ty,Tz);
  ValidParam_Trans_TBeforeR();
}



/*!
 * Nadaje now± warto¶æ wektorowi translacji
 * Zak³ada siê, ¿e translacja ma byæ wykonana po skalowanii i rotacji,
 *  tzn.
 *  \f[
          F = T \circ R \circ S
    \f]
 * \param T - nowa warto¶æ wektora translacji.
 * \post Do pola \link MatrixH3f::_Trans _Trans\endlink zostaje wpisany
 *       nowy wektor translacji przekazany przez parametr \e T.
 *       Wpisany zostaje on równie¿ do 4 kolumny macierzy wspó³czynników
 *       transformacji (patrz opis pola 
 *       \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink)
 *       zachowuj±c aktualno¶æ
 *       wyliczeñ wpó³czynników tej macierzy.
 *       
 *       Dzia³anie metody powoduje przypisanie polom 
 *    \link MatrixH3f::_Valid_Trans  MatrixH3f::_Valid_Trans\endlink
 *    oraz 
 *    \link MatrixH3f::_Trans_Order MatrixH3f::_Trans_Order \endlink
 *    warto¶ci \p TO_After.
 */
void MatrixH3f::SetTrans_TAfterR(Vector3f const &T)
{
  MatrixRT3f::SetTrans_TAfterR(_Trans = T);
  ValidParam_Trans_TAfterR();
}


/*!
 * Nadaje now± warto¶æ \e x-owej wspó³rzêdnej wektora translacji.
 * \param Tx - nowa warto¶æ \e x-owej wspó³rzêdnej wektora translacji.
 * \post Do pola \link MatrixH3f::_Trans _Trans\endlink 
 *       w miejsce \e x-owej wspó³rzêdnej zostaje wpisany
 *       nowa warto¶æ przekazana przez parametr \e Tx.
 *       Zostaje ona wpisana równie¿ do odpowiedniego elementu
 *       4 kolumny macierzy wspó³czynników
 *       transformacji (patrz opis pola 
 *       \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink)
 *       zachowuj±c aktualno¶æ
 *       wyliczeñ wpó³czynników tej macierzy.
 *       
 *       Dzia³anie metody powoduje przypisanie polom 
 *    \link MatrixH3f::_Valid_Trans  MatrixH3f::_Valid_Trans\endlink
 *    oraz 
 *    \link MatrixH3f::_Trans_Order MatrixH3f::_Trans_Order \endlink
 *    warto¶ci \p TO_After.
 */
void MatrixH3f::SetTransX_TAfterR(float Tx)
{
  UpdateParam_Trans_TAfterR();
  _Trans.x = Tx;
  MatrixRT3f::SetTrans_TAfterR(_Trans);
  ValidParam_Trans_TAfterR();
}


/*!
 * Nadaje now± warto¶æ \e y-owej wspó³rzêdnej wektora translacji.
 * \param Ty - nowa warto¶æ \e y-owej wspó³rzêdnej wektora translacji.
 * \post Do pola \link MatrixH3f::_Trans _Trans\endlink 
 *       w miejsce \e y-owej wspó³rzêdnej zostaje wpisany
 *       nowa warto¶æ przekazana przez parametr \e Ty.
 *       Zostaje ona wpisana równie¿ do odpowiedniego elementu
 *       4 kolumny macierzy wspó³czynników
 *       transformacji (patrz opis pola 
 *       \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink)
 *       zachowuj±c aktualno¶æ
 *       wyliczeñ wpó³czynników tej macierzy.
 *       
 *       Dzia³anie metody powoduje przypisanie polom 
 *    \link MatrixH3f::_Valid_Trans  MatrixH3f::_Valid_Trans\endlink
 *    oraz 
 *    \link MatrixH3f::_Trans_Order MatrixH3f::_Trans_Order \endlink
 *    warto¶ci \p TO_After.
 */
void MatrixH3f::SetTransY_TAfterR(float Ty)
{
  UpdateParam_Trans_TAfterR();
  _Trans.y = Ty;
  MatrixRT3f::SetTrans_TAfterR(_Trans);
  ValidParam_Trans_TAfterR();
}


/*!
 * Nadaje now± warto¶æ \e z-owej wspó³rzêdnej wektora translacji.
 * \param Tz - nowa warto¶æ \e z-owej wspó³rzêdnej wektora translacji.
 * \post Do pola \link MatrixH3f::_Trans _Trans\endlink 
 *       w miejsce \e z-owej wspó³rzêdnej zostaje wpisany
 *       nowa warto¶æ przekazana przez parametr \e Tz.
 *       Zostaje ona wpisana równie¿ do odpowiedniego elementu
 *       4 kolumny macierzy wspó³czynników
 *       transformacji (patrz opis pola 
 *       \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink)
 *       zachowuj±c aktualno¶æ
 *       wyliczeñ wpó³czynników tej macierzy.
 *       
 *       Dzia³anie metody powoduje przypisanie polom 
 *    \link MatrixH3f::_Valid_Trans  MatrixH3f::_Valid_Trans\endlink
 *    oraz 
 *    \link MatrixH3f::_Trans_Order MatrixH3f::_Trans_Order \endlink
 *    warto¶ci \p TO_After.
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
 *  który traktowany jest
 * jako translacja przed skalowaniem i rotacj±, tzn.
 * \f[
      F = R \circ S \circ T
   \f]
 * \param dT - (\b in) dodawany wektor.
 * \post Suma wektora translacji pochodz±cego bezpo¶renio z 4 kolumny 
 *       macierzy wspó³czynników transformacji 
 *       (patrz opis pola 
 *       \link MatrixRT3f::_DH _DH\endlink) oraz parametru \e dT
 *       wpisana zostaje
 *       do 4 kolumny macierzy wspó³czynników.
 */
void MatrixH3f::AddTrans_TBeforeR(const Vector3f &dT)
{ 
  UpdateParam_Trans_TBeforeR();
  MatrixRT3f::SetTrans_TBeforeR(_Trans += dT);
}



/*!
 * Dodaje przekazan± warto¶æ do \e x-owej sk³adowej wektora translacji,
 *  który traktowany jest
 * jako translacja przed skalowaniem i rotacj±, tzn.
 * \f[
      F = R \circ S \circ T
   \f]
 * \param d_Tx - (\b in) dodawany wektor.
 * \post Suma wektora translacji pochodz±cego bezpo¶renio z 4 kolumny 
 *       macierzy wspó³czynników transformacji 
 *       (patrz opis pola 
 *       \link MatrixRT3f::_DH _DH\endlink) oraz parametru \e dT
 *       wpisana zostaje
 *       do 4 kolumny macierzy wspó³czynników.
 */
void MatrixH3f::AddTransX_TBeforeR(float d_Tx)
{ 
  UpdateParam_Trans_TBeforeR();
  MatrixRT3f::SetTrans_TBeforeR(_Trans.x += d_Tx, _Trans.y, _Trans.z);
}



/*!
 * Dodaje przekazan± warto¶æ do \e y-owej sk³adowej wektora translacji,
 *  który traktowany jest
 * jako translacja przed skalowaniem i rotacj±, tzn.
 * \f[
      F = R \circ S \circ T
   \f]
 * \param d_Ty - (\b in) dodawany wektor.
 * \post Suma wektora translacji pochodz±cego bezpo¶renio z 4 kolumny 
 *       macierzy wspó³czynników transformacji 
 *       (patrz opis pola 
 *       \link MatrixRT3f::_DH _DH\endlink) oraz parametru \e dT
 *       wpisana zostaje
 *       do 4 kolumny macierzy wspó³czynników.
 */
void MatrixH3f::AddTransY_TBeforeR(float d_Ty)
{ 
  UpdateParam_Trans_TBeforeR();
  MatrixRT3f::SetTrans_TBeforeR(_Trans.x, _Trans.y += d_Ty, _Trans.z);
}


/*!
 * Dodaje przekazan± warto¶æ do \e z-owej sk³adowej wektora translacji,
 *  który traktowany jest
 * jako translacja przed skalowaniem i rotacj±, tzn.
 * \f[
      F = R \circ S \circ T
   \f]
 * \param d_Tz - (\b in) dodawany wektor.
 * \post Suma wektora translacji pochodz±cego bezpo¶renio z 4 kolumny 
 *       macierzy wspó³czynników transformacji 
 *       (patrz opis pola 
 *       \link MatrixRT3f::_DH _DH\endlink) oraz parametru \e dT
 *       wpisana zostaje
 *       do 4 kolumny macierzy wspó³czynników.
 */
void MatrixH3f::AddTransZ_TBeforeR(float d_Tz)
{ 
  UpdateParam_Trans_TBeforeR();
  MatrixRT3f::SetTrans_TBeforeR(_Trans.x, _Trans.y, _Trans.z += d_Tz);
}





/*!
 * Dodaje przekazany przez parametr wektor do wektora translacji,
 *  który traktowany jest
 * jako translacja po rotacji, tzn.
 * \f[
      F = T \circ R \circ S
   \f]
 * \param dT - dodawany wektor.
 * \post Suma wektora translacji pochodz±cego bezpo¶renio z 4 kolumny 
 *       macierzy wspó³czynników transformacji 
 *       (patrz opis pola 
 *       \link MatrixRT3f::_DH _DH\endlink) oraz parametru \e dT
 *       wpisana zostaje
 *       do 4 kolumny macierzy wspó³czynników.
 */
void MatrixH3f::AddTrans_TAfterR(const Vector3f &dT)
{ 
  MatrixRT3f::AddTrans_TAfterR(dT);
  InvalidParam_Trans();
}

/*!
 * Dodaje do \e x-owej wspó³rzêdnej wektora translacji traktowanego 
 * jako translacja po rotacji, podany warto¶æ.
 * \param Tx - dodawana warto¶æ \e x-owej wspó³rzêdnej wektora translacji.
 * \post Do pola \link MatrixH3f::_Trans _Trans\endlink zostaje wpisana
 *       suma wektora translacji pochodz±cego bezpo¶renio z 4 kolumny 
 *       macierzy wspó³czynników transformacji 
 *       Nowa wyliczona warto¶æ zostaje wpisana
 *       do odpowiedniego elementu 
 *       4 kolumny macierzy wspó³czynników transformacji.
 *       (patrz opis pola 
 *       \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink).
 *       
 *       Dzia³anie metody powoduje wypisanie warto¶ci \p false
 *       do pola 
 *        \link MatrixH3f::_Valid_Trans _Valid_Trans\endlink.
 */
void MatrixH3f::AddTransX_TAfterR(float Tx)
{ 
  MatrixRT3f::AddTrans_TAfterR(Vector3f(Tx,0,0));
  InvalidParam_Trans();
}

/*!
 * Dodaje do \e y-owej wspó³rzêdnej wektora translacji traktowanego 
 * jako translacja po rotacji, podany warto¶æ.
 * \param Ty - dodawana warto¶æ \e y-owej wspó³rzêdnej wektora translacji.
 * \post Do pola \link MatrixH3f::_Trans _Trans\endlink zostaje wpisana
 *       suma wektora translacji pochodz±cego bezpo¶renio z 4 kolumny 
 *       macierzy wspó³czynników transformacji 
 *       Nowa wyliczona warto¶æ zostaje wpisana
 *       do odpowiedniego elementu 
 *       4 kolumny macierzy wspó³czynników transformacji.
 *       (patrz opis pola 
 *       \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink).
 *       
 *       Dzia³anie metody powoduje wypisanie warto¶ci \p false
 *       do pola 
 *        \link MatrixH3f::_Valid_Trans _Valid_Trans\endlink.
 */
void MatrixH3f::AddTransY_TAfterR(float Ty)
{ 
  MatrixRT3f::AddTrans_TAfterR(Vector3f(0,Ty,0));
  InvalidParam_Trans();
}

/*!
 * Dodaje do \e z-owej wspó³rzêdnej wektora translacji traktowanego 
 * jako translacja po rotacji, podany warto¶æ.
 * \param Tz - dodawana warto¶æ \e z-owej wspó³rzêdnej wektora translacji.
 * \post Do pola \link MatrixH3f::_Trans _Trans\endlink zostaje wpisana
 *       suma wektora translacji pochodz±cego bezpo¶renio z 4 kolumny 
 *       macierzy wspó³czynników transformacji 
 *       Nowa wyliczona warto¶æ zostaje wpisana
 *       do odpowiedniego elementu 
 *       4 kolumny macierzy wspó³czynników transformacji.
 *       (patrz opis pola 
 *       \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink).
 *       
 *       Dzia³anie metody powoduje wypisanie warto¶ci \p false
 *       do pola 
 *        \link MatrixH3f::_Valid_Trans _Valid_Trans\endlink.
 */
void MatrixH3f::AddTransZ_TAfterR(float Tz)
{ 
  MatrixRT3f::AddTrans_TAfterR(Vector3f(0,0,Tz));
  InvalidParam_Trans();
}



/*!
 * \brief Udostêpnia wektor skali dla osi \e OX, \e OY, \e OZ.
 *
 * Metoda udostêpnia wektor skali wzglêdem poszczególnych osi
 * (warto¶æ pola \link MatrixH3f::_Scale _Scale\endlink).
 * Je¿eli jest to konieczne, to aktualizuje jego zawarto¶æ,
 * tak aby dopowiada³a ona warto¶ci wynikaj±cej ze wspó³czynników
 * macierzy transformacji.
 * \return referencjê do pola  \link MatrixH3f::_Scale _Scale\endlink
 *         zawieraj±cego wektor wspó³czynników skali.
 * \post Pole 
 *   \link MatrixH3f::_Valid_Scale  MatrixH3f::_Valid_Scale\endlink
 *   ma warto¶æ \p true.
 *
 * Uwaga: Pobieranie wspó³czynników skali nie zale¿y od
 *        kolejno¶ci wykonanej translacji.
 */
const Vector3f &MatrixH3f::GetScale() const
{
  USE(MatrixH3f).UpdateParam_Scale();
  return _Scale;
}



/*!
 * \brief Ustawia now± skalê dla przypadku translacji po rotacji.
 *
 * Ustawia now± skalê przyjmuj±c, ¿e aktualne wspó³czynniki
 * macierzy przekszta³cenia jednorodnego odpowiadaj± przypadkowi,
 * gdy translacja jest realizowana przed rotacj±. W takim przypadku
 * operacja nie powoduje zmiany czwartej kolumny macierzy transformacji,
 * która w tej interpretacji odpowiada bezpo¶rednio wektorowi translacji.
 * \param Scale - (\b in) wektor nowych wspó³czynników skali wzglêdem 
 *               poszczególnych
 *               osi, tzn. \e OX, \e OY, \e OZ.
 * \pre ¯aden ze wspó³czynników skali nie mo¿e byæ równy 0.
 *      Je¿eli dla danej osi wcze¶niej wspó³czynnik skali by³ ustawiony
 *      na warto¶æ 0, to dla tej osi przeskalowanie nie jest realizowane.
 * \post Pole
 *  \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink
 *  ma warto¶æ \p true.
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
 * \brief Ustawia wspó³czynnik skali osi \e OX dla przypadku translacji po rotacji.
 *
 * Ustawia nowy wspó³czynnik skali osi \e OX
 * przyjmuj±c, ¿e aktualne wspó³czynniki
 * macierzy przekszta³cenia jednorodnego odpowiadaj± przypadkowi,
 * gdy translacja jest realizowana przed rotacj±. W takim przypadku
 * operacja nie powoduje zmiany czwartej kolumny macierzy transformacji,
 * która w tej interpretacji odpowiada bezpo¶rednio wektorowi translacji.
 * \param Sx - (\b in) wspó³czynnik skali osi \e OX.
 * \pre ¯aden ze wspó³czynników skali nie mo¿e byæ równy 0.
 *      Je¿eli dla danej osi wcze¶niej wspó³czynnik skali by³ ustawiony
 *      na warto¶æ 0, to dla tej osi przeskalowanie nie jest realizowane.
 * \post Pole
 *  \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink
 *  ma warto¶æ \p true.
 */
void MatrixH3f::SetScaleX_TBeforeR(float Sx)
{
  UpdateParam_Scale_Euler_Angles();
  _Scale.x = MakeDT_0(Sx);
  UpdateParam_Trans_TBeforeR();
  MatrixRT3f::SetMatrix_Euler_TBeforeR_Rad(_RotAng,_Trans,_Scale);
}


/*!
 * \brief Ustawia wspó³czynnik skali osi \e OY dla przypadku translacji po rotacji.
 *
 * Ustawia nowy wspó³czynnik skali osi \e OY
 * przyjmuj±c, ¿e aktualne wspó³czynniki
 * macierzy przekszta³cenia jednorodnego odpowiadaj± przypadkowi,
 * gdy translacja jest realizowana przed rotacj±. W takim przypadku
 * operacja nie powoduje zmiany czwartej kolumny macierzy transformacji,
 * która w tej interpretacji odpowiada bezpo¶rednio wektorowi translacji.
 * \param Sy - (\b in) wspó³czynnik skali osi \e OY.
 * \pre ¯aden ze wspó³czynników skali nie mo¿e byæ równy 0.
 *      Je¿eli dla danej osi wcze¶niej wspó³czynnik skali by³ ustawiony
 *      na warto¶æ 0, to dla tej osi przeskalowanie nie jest realizowane.
 * \post Pole
 *  \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink
 *  ma warto¶æ \p true.
 */
void MatrixH3f::SetScaleY_TBeforeR(float Sy)
{
  UpdateParam_Scale_Euler_Angles();
  _Scale.y = MakeDT_0(Sy);
  UpdateParam_Trans_TBeforeR();
  MatrixRT3f::SetMatrix_Euler_TBeforeR_Rad(_RotAng,_Trans,_Scale);
}



/*!
 * \brief Ustawia wspó³czynnik skali osi \e OZ dla przypadku translacji 
 *        po rotacji.
 *
 * Ustawia nowy wspó³czynnik skali osi \e OZ
 * przyjmuj±c, ¿e aktualne wspó³czynniki
 * macierzy przekszta³cenia jednorodnego odpowiadaj± przypadkowi,
 * gdy translacja jest realizowana przed rotacj±. W takim przypadku
 * operacja nie powoduje zmiany czwartej kolumny macierzy transformacji,
 * która w tej interpretacji odpowiada bezpo¶rednio wektorowi translacji.
 * \param Sz - (\b in) wspó³czynnik skali osi \e OZ.
 * \pre ¯aden ze wspó³czynników skali nie mo¿e byæ równy 0.
 *      Je¿eli dla danej osi wcze¶niej wspó³czynnik skali by³ ustawiony
 *      na warto¶æ 0, to dla tej osi przeskalowanie nie jest realizowane.
 * \post Pole
 *  \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink
 *  ma warto¶æ \p true.
 */
void MatrixH3f::SetScaleZ_TBeforeR(float Sz)
{
  UpdateParam_Scale_Euler_Angles();
  _Scale.z = MakeDT_0(Sz);
  UpdateParam_Trans_TBeforeR();
  MatrixRT3f::SetMatrix_Euler_TBeforeR_Rad(_RotAng,_Trans,_Scale);
}




/*!
 * \brief Ustawia now± skalê dla przypadku translacji po rotacji.
 *
 * Ustawia now± skalê przyjmuj±c, ¿e aktualne wspó³czynniki
 * macierzy przekszta³cenia jednorodnego odpowiadaj± przypadkowi,
 * gdy translacja jest realizowana po rotacji. W takim przypadku
 * operacja nie powoduje zmiany czwartej kolumny macierzy transformacji,
 * która w tej interpretacji odpowiada bezpo¶rednio wektorowi translacji.
 * \param Scale - (\b in) wektor nowych wspó³czynników skali wzglêdem 
 *               poszczególnych
 *               osi, tzn. \e OX, \e OY, \e OZ.
 * \pre ¯aden ze wspó³czynników skali nie mo¿e byæ równy 0.
 *      Je¿eli dla danej osi wcze¶niej wspó³czynnik skali by³ ustawiony
 *      na warto¶æ 0, to dla tej osi przeskalowanie nie jest realizowane.
 * \post Pole
 *  \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink
 *  ma warto¶æ \p true.
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
 *  Realizuje aktualizacjê warto¶ci k±tów 
 *  przyjmuj±c jako podstawê do interpretacji 
 *  warto¶æ pola \link MatrixH3f::_AngInterp _AngInterp\endlink.
 *  Operacja wykonywana jest tylko wtedy
 *  gdy stwierdzone zostanie, ¿e warto¶ci k±tów nie s± aktualne
 *  w stosunku do warto¶ci macierzy.
 *  Zapisywane warto¶ci wyliczane s± na podstawie aktualnych parameterów
 *  macierzy transformacji.
 *  Je¿eli aktualizowane s± warto¶ci k±tów, to aktualizowany
 *  jest równie¿  wektor skali 
 *   (pola \link MatrixH3f::_Scale _Scale\endlink).
 *  w którym zapisany s±
 *  wspó³czynniki skali dla poszczególnych osi. 
 * \post Wyliczone warto¶ci k±tów mieszcz± siê w przedzia³ach:
 *         \li \f$ \psi \in (-\pi,-\pi]\f$ - odpowiada wspó³rzêdnej $y$
 *            wektora k±tów rotacji.
 *       Pole \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *       ma warto¶æ \p true, za¶ pole 
 *       \link MatrixH3f::_AngInterp _AngInterp\endlink warto¶æ
 *       \p AT_Euler.
 *       Pondto je¿eli nast±pi³a aktualizacja warto¶ci k±tów,
 *      to pole  \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink
 *      ma warto¶æ \p true, za¶ 
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
 *  Nadaje nowe warto¶ci k±tom rotacji danej transformacji
 *  w reprezentacji \e XYZ.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±tów powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w radianach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Ax - (\b in) warto¶æ k±ta \f$\alpha\f$ 
 *                     (rotacja wokó³ osi \f$ OX\f$).
 *  \param Ay - (\b in) warto¶æ k±ta \f$\beta\f$ 
 *                    (rotacja wokó³ osi \f$ OY'\f$).
 *  \param Az - (\b in) warto¶æ k±ta \f$\gamma\f$ 
 *                    (rotacja wokó³ osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_XYZ_TAfterR_Rad(float Ax, float Ay, float Az)
{
  UpdateParam_Scale();
  MatrixRT3f:: SetRotMtx_XYZ_Rad(_RotAng.Set(Ax,Ay,Az),_Scale);
  ValidParam_XYZ_Angles();
}





/*!
 * \if matrixh3f_brief_desc 
 *  \brief Ustawia zadan± indeksem wspó³rzêdn± wektora translacji
 * \endif
 *
 *  Ustawia zadan± indeksem wspó³rzêdn± wektora translacji
 *  dla transformacji, gdy translacja wykonywana jest po rotacji.
 *  Metoda pozostawia niezmienione warto¶ci wektora rotacji i
 *  skali. Zadanie warto¶ci translacji
 *  powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Idx - (\b in) indeks okre¶laj±cy, której wspó³rzêdnej
 *               wektora translacji ma zostaæ nadana nowa warto¶æ.
 *               Indeks mo¿e przyjmowaæ warto¶ci: 0, 1, 2.
 *             Odpowiadaj± one odpowiednio wspó³rzêdnej \e x, \e y, \e z.
 *  \param Val - (\b in) nowa warto¶æ translacji.
 * \post Do pola \link MatrixH3f::_Trans _Trans\endlink 
 *       w miejsce wybranej wspó³rzêdnej zostaje wpisana
 *       nowa warto¶æ przekazana przez parametr \e Val.
 *       Zostaje ona wpisana równie¿ do odpowiedniego elementu
 *       4 kolumny macierzy wspó³czynników
 *       transformacji (patrz opis pola 
 *       \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink)
 *       zachowuj±c aktualno¶æ
 *       wyliczeñ wpó³czynników tej macierzy.
 *       
 *       Dzia³anie metody powoduje przypisanie polom 
 *    \link MatrixH3f::_Valid_Trans  MatrixH3f::_Valid_Trans\endlink
 *    oraz 
 *    \link MatrixH3f::_Trans_Order MatrixH3f::_Trans_Order \endlink
 *    warto¶ci \p TO_After.
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
 *  \brief Ustawia zadan± indeksem wspó³rzêdn± wektora translacji
 * \endif
 *
 *  Ustawia zadan± indeksem wspó³rzêdn± wektora translacji
 *  dla transformacji, gdy translacja wykonywana jest przed rotacj±.
 *  Metoda pozostawia niezmienione warto¶ci wektora rotacji i
 *  skali. Zadanie warto¶ci translacji
 *  powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F =  R \circ S \circ T
    \f]
 *  \param Idx - (\b in) indeks okre¶laj±cy, której wspó³rzêdnej
 *               wektora translacji ma zostaæ nadana nowa warto¶æ.
 *               Indeks mo¿e przyjmowaæ warto¶ci: 0, 1, 2.
 *             Odpowiadaj± one odpowiednio wspó³rzêdnej \e x, \e y, \e z.
 *  \param Val - (\b in) nowa warto¶æ translacji.
 * \post Do pola \link MatrixH3f::_Trans _Trans\endlink 
 *       w miejsce wybranej wspó³rzêdnej zostaje wpisana
 *       nowa warto¶æ przekazana przez parametr \e Val.
 *       Zostaje ona wpisana równie¿ do odpowiedniego elementu
 *       4 kolumny macierzy wspó³czynników
 *       transformacji (patrz opis pola 
 *       \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink)
 *       zachowuj±c aktualno¶æ
 *       wyliczeñ wpó³czynników tej macierzy.
 *
 *       Dzia³anie metody powoduje przypisanie polom 
 *    \link MatrixH3f::_Valid_Trans  MatrixH3f::_Valid_Trans\endlink
 *    oraz 
 *    \link MatrixH3f::_Trans_Order MatrixH3f::_Trans_Order \endlink
 *    warto¶ci \p TO_Before.
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
 *  \brief Ustawia zadan± indeksem wspó³rzêdn± wektora skali
 * \endif
 *
 *  Ustawia zadan± indeksem wspó³rzêdn± wektora skali
 *  dla transformacji, gdy translacja wykonywana jest przed rotacj±.
 *  Metoda pozostawia niezmienione warto¶ci wektora rotacji i translacji.
 *  Zadanie warto¶ci skali
 *  powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = R \circ S \circ T
    \f]
 *  \param Idx - (\b in) indeks okre¶laj±cy, której wspó³rzêdnej
 *               wektora skali ma zostaæ nadana nowa warto¶æ.
 *               Indeks mo¿e przyjmowaæ warto¶ci: 0, 1, 2.
 *             Odpowiadaj± one odpowiednio wspó³rzêdnej \e x, \e y, \e z.
 *  \param Val - (\b in) nowa warto¶æ skali.
 * \post Nie powoduje zmiany warto¶ci pól okre¶laj±cych wa¿no¶æ poszczególnych
 *       parametrów (w tym równie¿ skali).
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
 *  \brief Ustawia zadan± indeksem wspó³rzêdn± wektora skali
 * \endif
 *
 *  Ustawia zadan± indeksem wspó³rzêdn± wektora skali
 *  dla transformacji, gdy translacja wykonywana jest po rotacji.
 *  Metoda pozostawia niezmienione warto¶ci wektora rotacji i translacji.
 *  Zadanie warto¶ci skali
 *  powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Idx - (\b in) indeks okre¶laj±cy, której wspó³rzêdnej
 *               wektora skali ma zostaæ nadana nowa warto¶æ.
 *               Indeks mo¿e przyjmowaæ warto¶ci: 0, 1, 2.
 *             Odpowiadaj± one odpowiednio wspó³rzêdnej \e x, \e y, \e z.
 *  \param Val - (\b in) nowa warto¶æ skali.
 * \post Nie powoduje zmiany warto¶ci pól okre¶laj±cych wa¿no¶æ poszczególnych
 *       parametrów (w tym równie¿ skali).
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
 *  \brief Ustawia nowy zadany k±t rotacji w reprezentacji 
 *         \e XYZ dla translacji po rotacji.
 * \endif
 *
 *  Ustawia zadany indeksem k±t rotacji w reprezentacji 
 *  \e XYZ dla translacji po rotacji.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±ta powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶æ k±ta wyra¿ona jest
 *  w radianach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Idx - (\b in) indeks okre¶laj±cy, któremu z k±tów
 *                       ma zostaæ nadana nowa warto¶æ.
 *               Indeks mo¿e przyjmowaæ warto¶ci: 0, 1, 2.
 *             Odpowiadaj± one odpowiednio pierwszemu (obrót wokó³ osi
                \f$ OX\f$), drugiemu (obrót wokó³ osi \f$ OY'\f$)
 *             oraz trzeciemu (obrót wokó³ osi \f$ OZ''\f$) k±towi rotacji.
 *  \param Ang - (\b in) warto¶æ zadanego k±ta rotacji wyra¿ona w radianach.
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
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
 *  \brief Ustawia nowy zadany k±t rotacji w reprezentacji 
 *         \e XYZ dla translacji po rotacji.
 * \endif
 *
 *  Ustawia zadany indeksem k±t rotacji w reprezentacji 
 *  \e XYZ dla translacji po rotacji.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±ta powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶æ k±ta wyra¿ona jest
 *  w stopniach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Idx - (\b in) indeks okre¶laj±cy, któremu z k±tów
 *                       ma zostaæ nadana nowa warto¶æ.
 *               Indeks mo¿e przyjmowaæ warto¶ci: 0, 1, 2.
 *             Odpowiadaj± one odpowiednio pierwszemu (obrót wokó³ osi
                \f$ OX\f$), drugiemu (obrót wokó³ osi \f$ OY'\f$)
 *             oraz trzeciemu (obrót wokó³ osi \f$ OZ''\f$) k±towi rotacji.
 *  \param Ang - (\b in) warto¶æ zadanego k±ta rotacji wyra¿ona w stopniach.
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
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
 *  \brief Ustawia nowy zadany k±t rotacji w reprezentacji 
 *         \e XYZ dla translacji przed rotacj±.
 * \endif
 *
 *  Ustawia zadany indeksem k±t rotacji w reprezentacji 
 *  \e XYZ dla translacji przed rotacj±.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±ta powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶æ k±ta wyra¿ona jest
 *  w radianach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = R \circ S \circ T
    \f]
 *  \param Idx - (\b in) indeks okre¶laj±cy, któremu z k±tów
 *                       ma zostaæ nadana nowa warto¶æ.
 *               Indeks mo¿e przyjmowaæ warto¶ci: 0, 1, 2.
 *             Odpowiadaj± one odpowiednio pierwszemu (obrót wokó³ osi
                \f$ OX\f$), drugiemu (obrót wokó³ osi \f$ OY'\f$)
 *             oraz trzeciemu (obrót wokó³ osi \f$ OZ''\f$) k±towi rotacji.
 *  \param Ang - (\b in) warto¶æ zadanego k±ta rotacji wyra¿ona w radianach.
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
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
 *  \brief Ustawia nowy zadany k±t rotacji w reprezentacji 
 *         \e XYZ dla translacji przed rotacj±.
 * \endif
 *
 *  Ustawia zadany indeksem k±t rotacji w reprezentacji 
 *  \e XYZ dla translacji przed rotacj±.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±ta powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶æ k±ta wyra¿ona jest
 *  w stopniach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = R \circ S \circ T
    \f]
 *  \param Idx - (\b in) indeks okre¶laj±cy, któremu z k±tów
 *                       ma zostaæ nadana nowa warto¶æ.
 *               Indeks mo¿e przyjmowaæ warto¶ci: 0, 1, 2.
 *             Odpowiadaj± one odpowiednio pierwszemu (obrót wokó³ osi
                \f$ OX\f$), drugiemu (obrót wokó³ osi \f$ OY'\f$)
 *             oraz trzeciemu (obrót wokó³ osi \f$ OZ''\f$) k±towi rotacji.
 *  \param Ang - (\b in) warto¶æ zadanego k±ta rotacji wyra¿ona w stopniach.
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
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
 *  \brief Ustawia nowy zadany k±t rotacji w reprezentacji 
 *         k±tów Eulera dla translacji po rotacji.
 * \endif
 *
 *  Ustawia zadany indeksem k±t rotacji w reprezentacji 
 *  k±tów Eulera dla translacji po rotacji.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±ta powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶æ k±ta wyra¿ona jest
 *  w radianach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Idx - (\b in) indeks okre¶laj±cy, któremu z k±tów
 *                       ma zostaæ nadana nowa warto¶æ.
 *               Indeks mo¿e przyjmowaæ warto¶ci: 0, 1, 2.
 *             Odpowiadaj± one odpowiednio pierwszemu (obrót wokó³ osi
                \f$ OZ\f$, k±t \f$\varphi\f$), 
                drugiemu (obrót wokó³ osi \f$ OY'\f$, k±t \f$\theta\f$)
 *             oraz trzeciemu (obrót wokó³ osi \f$ OZ''\f$, k±t \f$\psi\f$) 
 *             k±towi rotacji.
 *  \param Ang - (\b in) warto¶æ zadanego k±ta rotacji wyra¿ona w radianach.
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
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
 *  \brief Ustawia nowy zadany k±t rotacji w reprezentacji 
 *         k±tów Eulera dla translacji po rotacji.
 * \endif
 *
 *  Ustawia zadany indeksem k±t rotacji w reprezentacji 
 *  k±tów Eulera dla translacji po rotacji.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±ta powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶æ k±ta wyra¿ona jest
 *  w stopniach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Idx - (\b in) indeks okre¶laj±cy, któremu z k±tów
 *                       ma zostaæ nadana nowa warto¶æ.
 *               Indeks mo¿e przyjmowaæ warto¶ci: 0, 1, 2.
 *             Odpowiadaj± one odpowiednio pierwszemu (obrót wokó³ osi
                \f$ OZ\f$, k±t \f$\varphi\f$), 
                drugiemu (obrót wokó³ osi \f$ OY'\f$, k±t \f$\theta\f$)
 *             oraz trzeciemu (obrót wokó³ osi \f$ OZ''\f$, k±t \f$\psi\f$) 
 *             k±towi rotacji.
 *  \param Ang - (\b in) warto¶æ zadanego k±ta rotacji wyra¿ona w stopniach.
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
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
 *  \brief Ustawia nowy zadany k±t rotacji w reprezentacji 
 *         k±tów Eulera dla translacji przed rotacji.
 * \endif
 *
 *  Ustawia zadany indeksem k±t rotacji w reprezentacji 
 *  k±tów Eulera dla translacji przed rotacji.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±ta powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶æ k±ta wyra¿ona jest
 *  w radianach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F =  R \circ S \circ T
    \f]
 *  \param Idx - (\b in) indeks okre¶laj±cy, któremu z k±tów
 *                       ma zostaæ nadana nowa warto¶æ.
 *               Indeks mo¿e przyjmowaæ warto¶ci: 0, 1, 2.
 *             Odpowiadaj± one odpowiednio pierwszemu (obrót wokó³ osi
                \f$ OZ\f$, k±t \f$\varphi\f$), 
                drugiemu (obrót wokó³ osi \f$ OY'\f$, k±t \f$\theta\f$)
 *             oraz trzeciemu (obrót wokó³ osi \f$ OZ''\f$, k±t \f$\psi\f$) 
 *             k±towi rotacji.
 *  \param Ang - (\b in) warto¶æ zadanego k±ta rotacji wyra¿ona w radianach.
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
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
 *  \brief Ustawia nowy zadany k±t rotacji w reprezentacji 
 *         k±tów Eulera dla translacji przed rotacji.
 * \endif
 *
 *  Ustawia zadany indeksem k±t rotacji w reprezentacji 
 *  k±tów Eulera dla translacji przed rotacji.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±ta powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶æ k±ta wyra¿ona jest
 *  w stopniach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F =  R \circ S \circ T
    \f]
 *  \param Idx - (\b in) indeks okre¶laj±cy, któremu z k±tów
 *                       ma zostaæ nadana nowa warto¶æ.
 *               Indeks mo¿e przyjmowaæ warto¶ci: 0, 1, 2.
 *             Odpowiadaj± one odpowiednio pierwszemu (obrót wokó³ osi
                \f$ OZ\f$, k±t \f$\varphi\f$), 
                drugiemu (obrót wokó³ osi \f$ OY'\f$, k±t \f$\theta\f$)
 *             oraz trzeciemu (obrót wokó³ osi \f$ OZ''\f$, k±t \f$\psi\f$) 
 *             k±towi rotacji.
 *  \param Ang - (\b in) warto¶æ zadanego k±ta rotacji wyra¿ona w stopniach.
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
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
 *  \brief Ustawia nowy pierwszy k±t rotacji w reprezentacji 
 *         \e XYZ dla translacji po rotacji.
 * \endif
 *
 *  Ustawia nowy pierwszy k±t rotacji w reprezentacji 
 *  \e XYZ dla translacji po rotacji.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±ta powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶æ k±ta wyra¿ona jest
 *  w radianach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Ax - (\b in) warto¶æ k±ta \f$\alpha\f$ 
 *                     (rotacja wokó³ osi \f$ OX\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
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
 *  \brief Ustawia nowy drugi k±t rotacji w reprezentacji 
 *         \e XYZ dla translacji po rotacji.
 * \endif
 *
 *  Ustawia nowy drugi k±t rotacji w reprezentacji 
 *  \e XYZ dla translacji po rotacji.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±ta powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶æ k±ta wyra¿ona jest
 *  w radianach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Ay - (\b in) warto¶æ k±ta \f$\alpha\f$ 
 *                     (rotacja wokó³ osi \f$ OY'\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
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
 *  \brief Ustawia nowy trzeci k±t rotacji w reprezentacji 
 *         \e XYZ dla translacji po rotacji.
 * \endif
 *
 *  Ustawia nowy trzeci k±t rotacji w reprezentacji 
 *  \e XYZ dla translacji po rotacji.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±ta powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶æ k±ta wyra¿ona jest
 *  w radianach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param Az - (\b in) warto¶æ k±ta \f$\alpha\f$ 
 *                     (rotacja wokó³ osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_XYZoZ_TAfterR_Rad(float Az)
{
  UpdateParam_Scale_XYZ_Angles();
  _RotAng.z = Az;
  MatrixRT3f:: SetRotMtx_XYZ_Rad(_RotAng,_Scale);
  ValidParam_XYZ_Angles();
}





/*!
 *  Nadaje nowe warto¶ci k±tom rotacji danej transformacji
 *  w reprezentacji \e XYZ.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±tów powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w radianach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = R \circ S \circ T
    \f]
 *  \param Ax - (\b in) warto¶æ k±ta \f$\alpha\f$ 
 *                     (rotacja wokó³ osi \f$ OX\f$).
 *  \param Ay - (\b in) warto¶æ k±ta \f$\beta\f$ 
 *                    (rotacja wokó³ osi \f$ OY'\f$).
 *  \param Az - (\b in) warto¶æ k±ta \f$\gamma\f$ 
 *                    (rotacja wokó³ osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
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
 *  \brief Ustawia nowy pierwszy k±t rotacji w reprezentacji 
 *         \e XYZ dla translacji przed rotacj±. 
 * \endif
 *
 *  Nadaje now± warto¶æ pierwszemu k±towi rotacji danej transformacji
 *  w reprezentacji \e XYZ.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±tów powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w radianach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = R \circ S \circ T
    \f]
 *  \param Ax - (\b in) warto¶æ k±ta \f$\alpha\f$ 
 *                     (rotacja wokó³ osi \f$ OX\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
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
 *  \brief Ustawia nowy drugi k±t rotacji w reprezentacji 
 *         \e XYZ dla translacji przed rotacj±. 
 * \endif
 *
 *  Nadaje now± warto¶æ drugiemu k±towi rotacji danej transformacji
 *  w reprezentacji \e XYZ.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±tów powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w radianach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = R \circ S \circ T
    \f]
 *  \param Ay - (\b in) warto¶æ k±ta \f$\alpha\f$ 
 *                     (rotacja wokó³ osi \f$ OY'\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
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
 *  \brief Ustawia nowy trzeci k±t rotacji w reprezentacji 
 *         \e XYZ dla translacji przed rotacj±. 
 * \endif
 *
 *  Nadaje now± warto¶æ trzeciemu k±towi rotacji danej transformacji
 *  w reprezentacji \e XYZ.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±tów powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w radianach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = R \circ S \circ T
    \f]
 *  \param Az - (\b in) warto¶æ k±ta \f$\alpha\f$ 
 *                     (rotacja wokó³ osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
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
 *  \brief Ustawia warto¶ci k±tów Eulera dla transformacji z translacj±
 *         przed rotacj±
 * \endif
 *
 *  Nadaje nowe warto¶ci k±tom Eulera danej transformacji.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±tów powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w radianach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F =  R \circ S \circ T
    \f]
 *  \param VPhi - (\b in) warto¶æ k±ta \f$\varphi\f$ 
 *                     (rotacja wokó³ osi \f$ OZ\f$).
 *  \param Theta - (\b in) warto¶æ k±ta \f$\theta\f$ 
 *                    (rotacja wokó³ osi \f$ OY'\f$).
 *  \param Psi - (\b in) warto¶æ k±ta \f$\psi\f$ 
 *                    (rotacja wokó³ osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
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
 *  \brief Ustawia warto¶æ k±ta Eulera \f$\varphi\f$ dla transformacji 
 *     z translacj± przed rotacj±
 * \endif
 *
 *  Nadaje nowe warto¶æ k±ta Eulera \f$\varphi\f$ danej transformacji.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie warto¶ci k±ta powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w radianach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F =  R \circ S \circ T
    \f]
 *  \param VPhi - (\b in) warto¶æ k±ta \f$\varphi\f$ 
 *                     (rotacja wokó³ osi \f$ OZ\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
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
 *  \brief Ustawia warto¶æ k±ta Eulera \f$\theta\f$ dla transformacji z translacj±
 *         przed rotacj±
 * \endif
 *
 *  Nadaje nowe warto¶æ k±ta Eulera \f$\theta\f$ danej transformacji.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie warto¶ci k±ta powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w radianach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F =  R \circ S \circ T
    \f]
 *  \param Theta - (\b in) warto¶æ k±ta \f$\theta\f$ 
 *                     (rotacja wokó³ osi \f$ OY'\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
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
 *  \brief Ustawia warto¶æ k±ta Eulera \f$\psi\f$ dla transformacji z translacj±
 *         przed rotacj±
 * \endif
 *
 *  Nadaje nowe warto¶æ k±ta Eulera \f$\psi\f$ danej transformacji.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie warto¶ci k±ta powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w radianach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F =  R \circ S \circ T
    \f]
 *  \param Psi - (\b in) warto¶æ k±ta \f$\psi\f$ 
 *                     (rotacja wokó³ osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_EulerPsi_TBeforeR_Rad(float Psi)
{
  UpdateParam_Scale_Euler_Angles();
  UpdateParam_Trans_TBeforeR();
  _RotAng.z = Psi;
  MatrixRT3f::SetMatrix_Euler_TBeforeR_Rad(_RotAng,_Trans,_Scale);
}








/*!
 *  Nadaje nowe warto¶ci k±tom Eulera danej transformacji.
 *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
 *  skali. Zadanie k±tów powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w radianach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = T \circ R \circ S
    \f]
 *  \param VPhi - (\b in) warto¶æ k±ta \f$\varphi\f$ 
 *                     (rotacja wokó³ osi \f$ OZ\f$).
 *  \param Theta - (\b in) warto¶æ k±ta \f$\theta\f$ 
 *                    (rotacja wokó³ osi \f$ OY'\f$).
 *  \param Psi - (\b in) warto¶æ k±ta \f$\psi\f$ 
 *                    (rotacja wokó³ osi \f$ OZ''\f$).
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_Euler_TAfterR_Rad(float VPhi, float Theta, float Psi)
{
  if (!_Valid_Scale) UpdateParam_Scale();
  MatrixRT3f::SetAng_Euler_TAfterR_Rad(_RotAng.Set(VPhi,Theta,Psi),_Scale);
  ValidParam_Euler_Angles();
}


/*!
 *  Nadaje now± warto¶æ k±ta Eulera \f$\varphi\f$ danej transformacji.
 *  Metoda pozostawia niezmienione warto¶ci wszystkich pozosta³ych
 *  parametrów transformacji.
 *  Zadanie k±ta powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w radianach.
 *  \param VPhi - (\b in) warto¶æ k±ta \f$\varphi\f$ 
 *                     (rotacja wokó³ osi \f$ OZ\f$) w radianach.
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_EulerVPhi_TAfterR_Rad(float VPhi)
{
 UpdateParam_Scale();
 UpdateParam_Euler_Angles_condScale(); 
 _RotAng.x = VPhi;
 MatrixRT3f::SetAng_Euler_TAfterR_Rad(_RotAng,_Scale);  
}

/*!
 *  Nadaje now± warto¶æ k±ta Eulera \f$\theta\f$ danej transformacji.
 *  Metoda pozostawia niezmienione warto¶ci wszystkich pozosta³ych
 *  parametrów transformacji.
 *  Zadanie k±ta powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w radianach.
 *  \param Theta - (\b in) warto¶æ k±ta \f$\theta\f$ 
 *                     (rotacja wokó³ osi \f$ OZ\f$) w radianach.
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
 */
void MatrixH3f::SetAng_EulerTheta_TAfterR_Rad(float Theta)
{
 UpdateParam_Scale();
 UpdateParam_Euler_Angles_condScale(); 
 _RotAng.y = Theta;
 MatrixRT3f::SetAng_Euler_TAfterR_Rad(_RotAng,_Scale);  
}

/*!
 *  Nadaje now± warto¶æ k±ta Eulera \f$\psi\f$ danej transformacji.
 *  Metoda pozostawia niezmienione warto¶ci wszystkich pozosta³ych
 *  parametrów transformacji.
 *  Zadanie k±ta powoduje jednocze¶nie odpowiednie przeliczenie
 *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
 *  w radianach.
 * Zak³ada siê, ¿e translacja ma byæ wykonana po skalowanii i rotacji,
 *  tzn.
 *  \f[
            F = T \circ R \circ S
     \f]
 *  \param Psi - (\b in) warto¶æ k±ta \f$\psi\f$ 
 *                     (rotacja wokó³ osi \f$ OZ\f$) w radianach.
 *  \post Pola \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
 *        i \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink 
 *        waj± warto¶æ \p true. Tym samym pola 
 *        \link MatrixH3f::_RotAng _RotAng\endlink i 
 *        \link MatrixH3f::_Scale _Scale\endlink zawieraj± aktualne
 *        warto¶ci parametrów odpowiednio k±tów rotacji i skali.
 *        Pole \link MatrixH3f::_AngInterp _AngInterp\endlink ma 
 *        natomiast warto¶æ \p AT_Euler.\n
 *        Zostaj± przeliczone wspó³czynniki macierzy transformacji
 *        (patrz pole \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink,
 *        tak aby odpowiada³y zadanym parametrom transformacji.
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
 *   \brief Bezpo¶rednio zadaje wspó³czynniki macierzy transformacji.
 *  \endif
 *
 *  Umo¿liwia bezpo¶rednie zadawanie wspó³czynników transformacji
 *  danej macierzy. Metodê tê nale¿y stosowaæ bardzo rozwa¿nie,
 *  gdy¿ wspó³czynniki transformacji nie mog± byæ dowolnymi warto¶ciami,
 *  o ile nie maj± wprowadzaæ deformacji w transformowanych bry³ach.
 *  Je¿eli wspó³czynniki nie bêd± spe³nia³y wiêzów na³o¿onych ma macierz
 *  rotacji, to wszystkie metody wyliczaj±ce k±ty rotacji, nie
 *  bêd± zwraca³y poprawnych warto¶ci.\n
 *  Dla podmacierzy rotacji wspomniane wiêzy maj± postaæ:
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
 *  \param Col1_Rot - warto¶ci wspó³czynników transformacji dla pierwszej
 *                    kolumny (pierwsza kolumna podmacierzy rotacji).
 *  \param Col2_Rot - warto¶ci wspó³czynników transformacji dla drugiej
 *                    kolumny (druga kolumna podmacierzy rotacji).
 *  \param Col3_Rot - warto¶ci wspó³czynników transformacji dla drugiej
 *                    kolumny (trzecia kolumna podmacierzy rotacji).
 *  \param Col4_Trans - warto¶ci wspó³czynników transformacji dla trzeciej
 *                    kolumny (wektor translacji).
 *  \post Uniewa¿niane s± aktualne pamiêtane warto¶ci parametrów transformacji.
 *        Oznacza to, ¿e u¿ycie jakiejkolwiek metody typu \e Get wymusi ich
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
 * Dodaje podane warto¶ci do aktalnych warto¶ci k±tów rotacji 
 * w reprezentacji \e XYZ i aktualizuje
 * macierz transformacji. Warto¶ci k±tów wyra¿one s± w radianach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F =  R \circ S  \circ T
   \f]
 * \param d_Ax - warto¶æ o któr± ma byæ zwiêkszony k±t \f$\alpha\f$
 *               (obrót wokó³ osi \f$ OX\f$).
 * \param d_Ay - warto¶æ o któr± ma byæ zwiêkszony k±t \f$\beta\f$
 *               (obrót wokó³ osi \f$ OY'\f$.
 * \param d_Az - warto¶æ o któr± ma byæ zwiêkszony k±t \f$\gamma\f$
 *               (obrót wokó³ osi \f$ OZ''\f$).
 * \post Do k±tów transformacji dodane zostaj± podane warto¶ci
 *       oraz zostaje zaaktualizowana macierz wspó³czynników transformacji.
 */
void MatrixH3f::AddAng_XYZ_TBeforeR_Rad( float d_Ax, float d_Ay, float d_Az )
{
  UpdateParam_Scale_XYZ_Angles();
  UpdateParam_Trans_TBeforeR();
  MatrixRT3f::SetRotMtx_XYZ_Rad(_RotAng.Add(d_Ax,d_Ay,d_Az),_Scale);
  MatrixRT3f::SetTrans_TBeforeR(_Trans);
}



/*!
 * Dodaje podane warto¶ci do aktalnych warto¶ci k±tów rotacji 
 * w reprezentacji \e XYZ i aktualizuje
 * macierz transformacji. Warto¶ci k±tów wyra¿one s± w radianach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = T \circ R \circ S  
   \f]
 * \param d_Ax -  (\b in) warto¶æ o któr± ma byæ zwiêkszony k±t \f$\alpha\f$
 *               (obrót wokó³ osi \f$ OX\f$).
 * \param d_Ay -  (\b in) warto¶æ o któr± ma byæ zwiêkszony k±t \f$\beta\f$
 *               (obrót wokó³ osi \f$ OY'\f$.
 * \param d_Az -  (\b in) warto¶æ o któr± ma byæ zwiêkszony k±t \f$\gamma\f$
 *               (obrót wokó³ osi \f$ OZ''\f$).
 * \post Do k±tów transformacji dodane zostaj± podane warto¶ci
 *       oraz zostaje zaaktualizowana macierz wspó³czynników transformacji.
 */
void MatrixH3f::AddAng_XYZ_TAfterR_Rad( float d_Ax, float d_Ay, float d_Az )
{
  UpdateParam_Scale_XYZ_Angles();
  MatrixRT3f::SetRotMtx_XYZ_Rad(_RotAng.Add(d_Ax,d_Ay,d_Az),_Scale);
}




/*!
 * Dodaje do aktalnych warto¶ci k±tów Eulera podane warto¶ci i aktualizuje
 * macierz transformacji. Warto¶ci k±tów wyra¿one s± w radianach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = R \circ S \circ T
   \f]
 * \param d_VPhi -  (\b in) warto¶æ o któr± ma byæ zwiêkszony k±t \f$\varphi\f$.
 * \param d_Theta -  (\b in) warto¶æ o któr± ma byæ zwiêkszony k±t \f$\theta\f$.
 * \param d_Psi -  (\b in) warto¶æ o któr± ma byæ zwiêkszony k±t \f$\psi\f$.
 * \post Do k±tów transformacji dodane zostaj± podane warto¶ci
 *       oraz zostaje zaaktualizowana macierz wspó³czynników transformacji.
 *       Zostaj± ustawione znaczniki wa¿no¶ci wszystkich pamiêtanych
 *       parametrów transformacji.
 */
void MatrixH3f::AddAng_Euler_TBeforeR_Rad( float d_VPhi, float d_Theta, float d_Psi)
{
  UpdateParam_Scale_Euler_Angles();
  UpdateParam_Trans_TBeforeR();
  MatrixRT3f::SetRotMtx_Euler_Rad(_RotAng.Add(d_VPhi,d_Theta,d_Psi),_Scale);
  MatrixRT3f::SetTrans_TBeforeR(_Trans);
}



/*!
 * Dodaje do aktalnych warto¶ci k±tów Eulera podane warto¶ci i aktualizuje
 * macierz transformacji. Warto¶ci k±tów wyra¿one s± w radianach.
 * Zak³ada siê, ¿e transformacja ma postaæ:
 * \f[
      F = T \circ R \circ S  
   \f]
 * \param d_VPhi -  (\b in) warto¶æ o któr± ma byæ zwiêkszony k±t \f$\varphi\f$.
 * \param d_Theta -  (\b in) warto¶æ o któr± ma byæ zwiêkszony k±t \f$\theta\f$.
 * \param d_Psi -  (\b in) warto¶æ o któr± ma byæ zwiêkszony k±t \f$\psi\f$.
 * \post Do k±tów transformacji dodane zostaj± podane warto¶ci
 *       oraz zostaje zaaktualizowana macierz wspó³czynników transformacji.
 */
void MatrixH3f::AddAng_Euler_TAfterR_Rad( float d_VPhi, float d_Theta, float d_Psi )
{
  UpdateParam_Scale_Euler_Angles();
  MatrixRT3f::SetAng_Euler_TAfterR_Rad(_RotAng.Add(d_VPhi,d_Theta,d_Psi),_Scale);
}



/*!
 *  Aktualizuje warto¶æ pola \link MatrixH3f::_Scale _Scale\endlink, 
 *  w którym zapisany jest
 *  wektor wspó³czynników skali dla poszczególnych osi. 
 *  Aktualizuje jednocze¶nie wektor k±tów rotacji nie zmieniaj±c
 *  dotychczasowej ich interpretacji.
 *  Zapisywane warto¶ci wyliczane s± na podstawie aktualnych parameterów
 *  macierzy transformacji.
 * \pre Wyliczenia bêd± poprawne wtedy i tylko wtedy gdy
 *      wspó³czynniki skali musz± s± od zera.
 * \post Zostaj± ustawione znaczniki wa¿no¶ci warto¶ci parametrów
 *       transformacji. Oznacza to, ¿e pobranie ich warto¶ci 
 *       za pomoc± innych metoda nie bêdzie wymusza³o ponownego ich 
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
 *  Aktualizuje warto¶æ pola \link MatrixH3f::_Scale _Scale\endlink, 
 *  w którym zapisany jest
 *  wektor wspó³czynników skali dla poszczególnych osi. 
 *  Aktualizuje jednocze¶nie wektor k±tów rotacji, traktuj±c je
 *  jako k±ty Eulera.
 *  Zapisywane warto¶ci wyliczane s± na podstawie aktualnych parameterów
 *  macierzy transformacji.
 * \pre Wyliczenia bêd± poprawne wtedy i tylko wtedy gdy
 *      wspó³czynniki skali musz± s± od zera.
 * \post Zostaj± ustawione znaczniki wa¿no¶ci warto¶ci parametrów
 *       transformacji. Oznacza to, ¿e pobranie ich warto¶ci 
 *       za pomoc± innych metoda nie bêdzie wymusza³o ponownego ich 
 *       obliczenia.
 */
void MatrixH3f::UpdateParam_Scale_Euler_Angles()
{
  if (_Valid_Scale && _Valid_RotAng && _AngInterp == AT_Euler) return;
  MatrixRT3f::GetEuler_Angles_Scale(_RotAng,_Scale);
  ValidParam_Scale_Euler_Angles();
}



/*!
 *  Dodaje do wspó³czynników skali danej transformacji podane warto¶ci.
 * Zak³ada siê, ¿e translacja ma byæ wykonana przed skalowaniem i rotacj±,
 *  tzn.
 *  \f[
           F = R \circ S \circ T
     \f]
 *  \param d_Sx - (\b in) warto¶æ dodawana do \e x-owego wspó³czynnika skali.
 *  \param d_Sy - (\b in) warto¶æ dodawana do \e y-owego wspó³czynnika skali.
 *  \param d_Sz - (\b in) warto¶æ dodawana do \e z-owego wspó³czynnika skali.
 *  \post Zostaj± zaktualizowany parametr skali i obliczone nowe
 *        warto¶ci wspó³czynników macierzy transformacji przy za³o¿eniu,
 *        ¿e transformacja jest realizowana przed skalowaniem i rotacj±.
 *        Nie jest zmieniana interpretacja k±tów rotacji.
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
 *  Dodaje do wspó³czynników skali danej transformacji podane warto¶ci.
 *  \param d_Sx - (\b in) warto¶æ dodawana do \e x-owego wspó³czynnika skali.
 *  \param d_Sy - (\b in) warto¶æ dodawana do \e y-owego wspó³czynnika skali.
 *  \param d_Sz - (\b in) warto¶æ dodawana do \e z-owego wspó³czynnika skali.
 *  \post Zostaj± zaktualizowany parametr skali i obliczone nowe
 *        warto¶ci wspó³czynników macierzy transformacji przy za³o¿eniu,
 *        ¿e transformacja jest realizowana po rotacji.
 */
void MatrixH3f::AddScale_TAfterR(float d_Sx, float d_Sy, float d_Sz)
{
  UpdateParam_Scale_Angles_Auto();
  MatrixH3f::SetAng_Auto_TAfterR_Rad(_RotAng,_Scale.Add(d_Sx,d_Sy,d_Sz));
}




/*============================================================================
 * Metoda dokonuje normalizacji macierzy rotacji (bez kolumny translacji).
 * Sprowadza w ten sposób wspó³czynniki skali wzd³u¿ osi OX, OY, OZ do 
 * warto¶ci 1. 
 */
MatrixH3f &MatrixH3f::Normalize()
{
 MatrixRT3f::Normalize();
 _Scale.Set(1,1,1);
 ValidParam_Scale();
 return *this;
}



/*!
 * Operator umo¿liwia podstawienie parametrów macierzy
 * transformacji i wyliczenie wszystkich wspó³czynników tej macierzy.
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
 * \brief Udostêpnia k±ty w reprezentacji \e XYZ w radianach.
 * \endif
 *
 * Udostêpnia k±ty obrotu wzglêdem osi \f$ OX\f$, \f$ OY'\f$ oraz \f$ OZ''\f$
 * dla danej macierzy transformacji.
 * Kolejne wspó³rzêdne wektora odpowiadaj± k±tom
 *  \f$\alpha\f$ (pierwszy obrót - wokó³ osi \f$ OX\f$),
 *  \f$\beta\f$ (drugi obrót - wokó³ osi \f$ OY'\f$),
 *  \f$\gamma\f$ (trzeci obrót - wokó³ osi \f$ OZ''\f$).
 * Udostêpniane warto¶ci k±tów wyra¿one s± w radianach.
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
 *  Wstawia do macierzy transformacji wspó³czynnik translacji
 *  wyliczany dla translacji wykonanej przed skalowaniem i rotacj±,
 *  tzn.
 *  \f[
        F = R \circ S \circ T
    \f]
 *  Operacja wykonywana jest tylko dla \e x-owej sk³adowej.
 *  \param Tx -  (\b in) wspó³rzêdna \e x-owa wektora translacji.
 * \post Do pola \link MatrixH3f::_Trans _Trans\endlink 
 *       w miejsce wspó³rzêdnej \e x-owej zostaje wpisana
 *       nowa warto¶æ przekazana przez parametr \e Val.
 *       Zostaje ona wpisana równie¿ do odpowiedniego elementu
 *       4 kolumny macierzy wspó³czynników
 *       transformacji (patrz opis pola 
 *       \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink)
 *       zachowuj±c aktualno¶æ
 *       wyliczeñ wpó³czynników tej macierzy.
 *
 *       Dzia³anie metody powoduje przypisanie polom 
 *    \link MatrixH3f::_Valid_Trans  MatrixH3f::_Valid_Trans\endlink
 *    oraz 
 *    \link MatrixH3f::_Trans_Order MatrixH3f::_Trans_Order \endlink
 *    warto¶ci \p TO_Before.
 */
void MatrixH3f::SetTransX_TBeforeR( float Tx )
{
  UpdateParam_Trans_TBeforeR();
  MatrixRT3f::SetTrans_TBeforeR(_Trans.x = Tx,_Trans.y,_Trans.z);
}



/*!
 *  Wstawia do macierzy transformacji wspó³czynnik translacji
 *  wyliczany dla translacji wykonanej przed skalowaniem i rotacj±,
 *  tzn.
 *  \f[
        F = R \circ S \circ T
    \f]
 *  Operacja wykonywana jest tylko dla \e y-owej sk³adowej.
 *  \param Ty -  (\b in) wspó³rzêdna \e y-owa wektora translacji.
 * \post Do pola \link MatrixH3f::_Trans _Trans\endlink 
 *       w miejsce wspó³rzêdnej \e y-owej zostaje wpisana
 *       nowa warto¶æ przekazana przez parametr \e Val.
 *       Zostaje ona wpisana równie¿ do odpowiedniego elementu
 *       4 kolumny macierzy wspó³czynników
 *       transformacji (patrz opis pola 
 *       \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink)
 *       zachowuj±c aktualno¶æ
 *       wyliczeñ wpó³czynników tej macierzy.
 *
 *       Dzia³anie metody powoduje przypisanie polom 
 *    \link MatrixH3f::_Valid_Trans  MatrixH3f::_Valid_Trans\endlink
 *    oraz 
 *    \link MatrixH3f::_Trans_Order MatrixH3f::_Trans_Order \endlink
 *    warto¶ci \p TO_Before.
 */
void MatrixH3f::SetTransY_TBeforeR( float Ty )
{
  UpdateParam_Trans_TBeforeR();
  MatrixRT3f::SetTrans_TBeforeR(_Trans.x,_Trans.y = Ty,_Trans.z);
}


/*!
 *  Wstawia do macierzy transformacji wspó³czynnik translacji
 *  wyliczany dla translacji wykonanej przed skalowaniem i rotacj±,
 *  tzn.
 *  \f[
        F = R \circ S \circ T
    \f]
 *  Operacja wykonywana jest tylko dla \e z-owej sk³adowej.
 *  \param Tz - (\b in) wspó³rzêdna \e z-owa wektora translacji.
 * \post Do pola \link MatrixH3f::_Trans _Trans\endlink 
 *       w miejsce wspó³rzêdnej \e z-owej zostaje wpisana
 *       nowa warto¶æ przekazana przez parametr \e Val.
 *       Zostaje ona wpisana równie¿ do odpowiedniego elementu
 *       4 kolumny macierzy wspó³czynników
 *       transformacji (patrz opis pola 
 *       \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink)
 *       zachowuj±c aktualno¶æ
 *       wyliczeñ wpó³czynników tej macierzy.
 *
 *       Dzia³anie metody powoduje przypisanie polom 
 *    \link MatrixH3f::_Valid_Trans  MatrixH3f::_Valid_Trans\endlink
 *    oraz 
 *    \link MatrixH3f::_Trans_Order MatrixH3f::_Trans_Order \endlink
 *    warto¶ci \p TO_Before.
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
 *  Wyliczane s± one bezpo¶rednio ze wspó³czynników transformacji
 *  w z pola MatrixRT3f::_DH parametru \e Mtx.
 *  \param Mtx - (in) macierz, której parametry transformacji maj±
 *               zostaæ przepisane.
 *  \return referencjê do samego siebie (\b *this).
 *  \post Parametry transformacji z macierzy \e Mtx zostaj± przepisne 
 *   do pól
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
 *  Aktualizuje warto¶æ pola \link MatrixH3f::_Scale _Scale\endlink, 
 *  w którym zapisany jest
 *  wektor wspó³czynników skali dla poszczególnych osi. 
 *  Aktualizuje jednocze¶nie wektor k±tów rotacji, traktuj±c je
 *  jako k±ty obrotu wokó³ osi
 *  \f$ OX\f$, \f$ OY'\f$, \f$ OZ''\f$.
 *  Zapisywane warto¶ci wyliczane s± na podstawie aktualnych parameterów
 *  macierzy transformacji.
 * \pre Wyliczenia bêd± poprawne wtedy i tylko wtedy gdy 
 *      wspó³czynniki skali s± ró¿ne od zera.
 * \post Zostaj± ustawione znaczniki wa¿no¶ci warto¶ci parametrów
 *       transformacji. Oznacza to, ¿e pobranie ich warto¶ci 
 *       za pomoc± innych metoda nie bêdzie wymusza³o ponownego ich 
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
 *  \brief Aktualizacja k±tów i warunkowa aktualizacja skali.
 * \endif
 *
 *  Aktualizuje wektor k±tów rotacji, traktuj±c je
 *  jako k±ty obrotu wokó³ osi
 *  \f$ OX\f$, \f$ OY'\f$, \f$ OZ''\f$.
 *  W przypadku gdy aktualizowany s± warto¶ci k±tów, donywana jest aktualizacja
 *  wspó³czynników skali. Jednak je¿eli aktualizacja warto¶ci k±tów nie
 *  jest konieczna, to wspó³czynniki skali równie¿ nie s± aktualizowane.
 *  Zapisywane warto¶ci wyliczane s± na podstawie aktualnych parameterów
 *  macierzy transformacji.
 * \pre Wyliczenia bêd± poprawne wtedy i tylko wtedy gdy 
 *      wspó³czynniki skali s± ró¿ne od zera.
 * \post Zostaj± ustawione znaczniki wa¿no¶ci warto¶ci parametrów
 *       transformacji. Oznacza to, ¿e pobranie ich warto¶ci 
 *       za pomoc± innych metoda nie bêdzie wymusza³o ponownego ich 
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
 * Zapisuje do pliku tekstowego liniê z zestawem parametrów
 * transformacji
 * macierzy. Parametry te brane s± z pól:
 *    \link MatrixH3f::Parameters::_Scale _Scale\endlink,
 *    \link MatrixH3f::Parameters::_Trans _Trans\endlink,
 *    \link MatrixH3f::Parameters::_RotAng _RotAng\endlink.
 *
 * Przyk³adowa linia zapisu parametrów ma postac:
 *
 *  Position (1, 1.5, 1) (15.2, 14.5, 60) (10, 100, 10)
 *
 * Kolejno¶æ parametrów: wsp³czynniki skali, k±ty rotacji, wspó³rzêdne
 * wektora translacji.
 *
 * \param f - wska¼nik na strukturê skojarzon± z otwartym do zapisu
 *            plikiem tekstowym.
 * \pre \e f != \p NULL. Parametr skojarzony jest z plikiem otwartym do
 *        zapisu.
 * \post Po dokonaniu operacji zapisu plik nie jest zamykany i operacje
 *       zapisu mog± byæ kontynuowane.
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
 *  k±ty Eulera, wektor translacji i skalê).
 *  Sk³adnia zapisu:
 *  \verbatim
 *    Angles { Euler | XYZ } { Deg | Rad }: ( k±t1, k±t2, k±t3 )
 *    Translation: ( sk³adowa_x, sk³adowa_y, sk³adowa_z )
 *    Scale: ( skala_x, skala_y, skala_z ); 
 *  \endverbatim
 *
 *  \param Descr - (\b out) wpisywany do niego s± parametry opisuj±ce
 *                dan± macierz transformacji.
 *  \param  AType - okre¶la rodzaj k±tów rotacji. W tej chwili
 *                obs³ugiwane s± k±ty Eulera oraz k±ty rotacji 
 *                wokó³ osi OX, OY, OZ.
 *  \param  AUnit - okre¶la w jakich jednostkach maj± byæ zapisane
 *                warto¶ci k±tów.
 *  \param  Margin - ilo¶æ spacji poprzedzaj±cych kolejne linie
 *                zapisu.
 *  \retval 0 - gdy w trakcie zapisu nie wyst±pi³ ¿aden b³±d.
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
 *  k±ty Eulera, wektor translacji i skalê).
 *  Sk³adnia zapisu:
 *  \verbatim
 *    Angles { Euler | XYZ } { Deg | Rad }: ( k±t1, k±t2, k±t3 )
 *    Translation: ( sk³adowa_x, sk³adowa_y, sk³adowa_z )
 *    Scale: ( skala_x, skala_y, skala_z ); 
 *  \endverbatim
 *
 *  \param ostrm - otwarty strumieñ wyj¶ciowy, ze wzglêdu na hierarchiê
 *                dziedziczenia klas w bibliotece standardowej mo¿e to
 *                byæ równie¿ strumieñ klasy \b ofstream. 
 *  \param  LeftMargin - ilo¶æ spacji poprzedzaj±cych kolejne linie
 *                zapisu.
 *  \param  AType - okre¶la rodzaj k±tów rotacji. W tej chwili
 *                obs³ugiwane s± k±ty Eulera oraz k±ty rotacji 
 *                wokó³ osi OX, OY, OZ.
 *  \param  AUnit - okre¶la w jakich jednostkach maj± byæ zapisane
 *                warto¶ci k±tów.
 *  \retval 0 - gdy w trakcie zapisu nie wyst±pi³ ¿aden b³±d.
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


