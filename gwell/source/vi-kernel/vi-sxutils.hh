#ifndef VI_SXUTILS_HH
#define VI_SXUTILS_HH

/*!
 * \file        vi-sxutils.hh
 * Plik zawiera nag��wki funkcji wspomagaj�cych wczytywanie, interpretacj�
 * nazw parametr�w oraz inicjalizajc� struktur danych biblioteki VIONA.
 * \author	Bogdan Kreczmer
 * \date        2004.08
 */

namespace Vi {

/*!
 *  Metoda pozwala na wczytanie ze strumienia wej�ciowego skojarzonego
 *  z danym intereterem syntaktycznym opisu parametr�w macierzy
 *  transformacji. Dokonuje ich interpretaci i inicjalizacji
 *  ca�ej macierzy.
 *  \param Interp - interpreter, z kt�rym skojarzony jest strumie�
 *                  wej�ciowy.
 *  \param Mtx - macierz transformacji, kt�rej parametry maj� zosta� wczytane 
 *         ze strumienia i wej�ciowego. Wczytane warto�ci parametr�w
 *         s� wykorzystane do zainicjalizowania macierzy.
 *               
 *  \pre Strumie� wej�ciowy skojarzony z parametrem \e Interp
 *       powinien by� ustawiony w takim miejscu, aby na jego wej�ciu
 *       by� opis parametr�w w postaci o nast�puj�cej sk�adni:
 *  \code
 *      Angles [ Euler | XYZ ] [ Deg | Rad ]  (a_x, a_y, a_z)
 *      Translation: (t_x, t_y, t_z)
 *      Scale: (s_x, s_y, s_z)
 *  \endcode
 *  gdzie a_., t_., s_. s� warto�ciami typu \b float.
 */
 void InitMtxFrom( SxInterp &Interp, MatrixH3f &Mtx ) throw (Sx::Exception);
}

#endif
