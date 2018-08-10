#ifndef VIMATRIX3F_HH
#define VIMATRIX3F_HH

/*!
 * \file        vimatrix3f.hh
 * Plik zawiera definicjê klasy ViMatrixH3f. Jest ona wykorzystywana
 * w poszczególnych obiektach do reprezentacji transformacji 
 * uk³adów wspó³rzêdnych.
 * \author	Bogdan Kreczmer
 * \date        2004.10
 */


#ifdef __GNUG__
#pragma interface
#endif


#include "matrixh3f.hh"

/*!
 * Klasa ma znaczenie pomocnicze. Jest rozszerzeniem klasy MatrixH3f o 
 * pole przechowuj±cy indetyfikator macierzy. Pozwala to w przypadku
 * macierzy definiowanych jako pola w ViElemePolyh zidentyfikowaæ
 * wzajemn± odpowiednio¶æ macierzy i konkretnego pola w klasie
 * ViElemePolyh.
 */
class ViMatrix3f: public MatrixH3f {
   /*!
    *  Pole identyfikuje typ macierzy transformacji. Dziêki temu
    *  mo¿liwe jest okre¶lenie pola w danym obiekcie, które 
    *  dan± macierz. Warto¶æ indeksu jest inicjalizowana tylko i wy³±cznie
    *  przez konstruktor i nie podlega kopiowaniu.
    */
    const int _MtxID;

 public:
  /*!
   *  Konstruktor pozwala utworzyæ macierz i jednocze¶nie nadaæ
   *  warto¶æ jej identyfikatorawi. Zmiana identyfikatora w trakcie
   *  istninia macierzy jest niedopuszczalna. Nadanie warto¶ci identyfikatorowi
   *  jest mo¿liwe tylko i wy³±cznie poprzez niniejszy konstruktor.
   */
   ViMatrix3f(int ID = -1): _MtxID(ID) {}

   /*!
    *  Metoda zwraca indetyfikator macierzy 
    *  (warto¶æ pola \link ViMatrix3f::_MtxID _MtxID\endlink).
    */
   int GetMtxID() const { return _MtxID; }


  /*!
   * Przeci±¿enie operatora przypisania pozwala na to, ¿e w trakcie jej
   * wykonania nie zostaje zmieniona warto¶æ identyfikatora macierzy.
   * \param M - macierz, której wspó³czynniki zostan± przepisane do
   *            macierzy \b this.
   */
   ViMatrix3f &operator = (const MatrixH3f& M) 
                          { *(MatrixH3f*)this = M;  return *this; }
};



#endif
