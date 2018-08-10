#ifndef VI_SXUTILS_HH
#define VI_SXUTILS_HH

/*!
 * \file        vi-sxutils.hh
 * Plik zawiera nag³ówki funkcji wspomagaj±cych wczytywanie, interpretacjê
 * nazw parametrów oraz inicjalizajcê struktur danych biblioteki VIONA.
 * \author	Bogdan Kreczmer
 * \date        2004.08
 */

namespace Vi {

/*!
 *  Metoda pozwala na wczytanie ze strumienia wej¶ciowego skojarzonego
 *  z danym intereterem syntaktycznym opisu parametrów macierzy
 *  transformacji. Dokonuje ich interpretaci i inicjalizacji
 *  ca³ej macierzy.
 *  \param Interp - interpreter, z którym skojarzony jest strumieñ
 *                  wej¶ciowy.
 *  \param Mtx - macierz transformacji, której parametry maj± zostaæ wczytane 
 *         ze strumienia i wej¶ciowego. Wczytane warto¶ci parametrów
 *         s± wykorzystane do zainicjalizowania macierzy.
 *               
 *  \pre Strumieñ wej¶ciowy skojarzony z parametrem \e Interp
 *       powinien byæ ustawiony w takim miejscu, aby na jego wej¶ciu
 *       by³ opis parametrów w postaci o nastêpuj±cej sk³adni:
 *  \code
 *      Angles [ Euler | XYZ ] [ Deg | Rad ]  (a_x, a_y, a_z)
 *      Translation: (t_x, t_y, t_z)
 *      Scale: (s_x, s_y, s_z)
 *  \endcode
 *  gdzie a_., t_., s_. s± warto¶ciami typu \b float.
 */
 void InitMtxFrom( SxInterp &Interp, MatrixH3f &Mtx ) throw (Sx::Exception);
}

#endif
