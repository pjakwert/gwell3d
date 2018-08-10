#ifndef VITRIANGLE3_HH
#define VITRIANGLE3_HH

/*! \file vitriangle3.hh
 *  Plik zawiera definicjê szablonu ViTriangle3. Wykorzystyny jest on
 *  do rozbijania dowolnej ¶cianki reprezentowanej przez wielobok wypuk³y
 *  na zbiór trójk±tów.
 *  \author  Bogdan Kreczmer
 *  \date    2004.03.27
 */



#ifdef __GNUG__
#pragma interface
#endif

#include <iostream>
#include "vector3.hh"


/*!
 *  Szablon wykorzystyny jest do modelowania pojedynczego trójk±ta.
 *  Wykorzystywane s± one do rozbijania dowolnej ¶cianki reprezentowanej
 *  przez wielobok wypuk³y na zbiór trójk±tów. 
 */
template<typename TYPE>
class ViTriangle3 {
  /*!
   *  Pole reprezentuje poszczególne wierzcho³ki trójk±ta. 
   *  Kolejno¶æ wystêpowania wspó³rzêdnych wierzcho³ków w tej tablicy
   *  okre¶lona jest przez orientacjê brzegu, która wyznacza
   *  wierzchni± i spodni± czê¶æ trójk±tnej ¶cianki.
   */
  Vector3<TYPE>   _Vtx[3];
  /*!
   *  Referencje do pierwszego wierzcho³ka trójk±ta.
   */
  Vector3<TYPE>  &_Vtx0;
  /*!
   *  Referencje do drugiego wierzcho³ka trójk±ta.
   */
  Vector3<TYPE>  &_Vtx1;
  /*!
   *  Referencje do trzeciego wierzcho³ka trójk±ta.
   */
  Vector3<TYPE>  &_Vtx2;
 public:

  /*!
   *  Inicjalizuje pola referencyjne. Do wspó³rzêdnych wszystkich 
   *  wierzcho³ków s± podstawiane warto¶ci zerowe.
   */
  ViTriangle3(): _Vtx0(_Vtx[0]),  _Vtx1(_Vtx[1]),  _Vtx2(_Vtx[2]) {}
  /*!
   *  Inicjalizuje pola referencyjne. Do wspó³rzêdnych wszystkich 
   *  wierzcho³ków s± podstawiane warto¶ci dostêpne poprzez parametry.
   *  \param V0 - wspó³rzêdne pierwszego wierzcho³ka,
   *  \param V1 - wspó³rzêdne drugiego wierzcho³ka,
   *  \param V2 - wspó³rzêdne trzeciego wierzcho³ka.
   */
  ViTriangle3( Vector3<TYPE> const &V0,
              Vector3<TYPE> const &V1,
              Vector3<TYPE> const &V2): 
              _Vtx0(_Vtx[0]),  _Vtx1(_Vtx[1]),  _Vtx2(_Vtx[2]) 
      {  _Vtx0 = V0;  _Vtx1 = V1;  _Vtx2 = V2; }

  /*!
   *  Podstawia wspó³rzêdne dla wszystkich wierzcho³kow trójk±ta.
   *  \param V0 - wspó³rzêdne pierwszego wierzcho³ka,
   *  \param V1 - wspó³rzêdne drugiego wierzcho³ka,
   *  \param V2 - wspó³rzêdne trzeciego wierzcho³ka.
   */
  void Set( Vector3<TYPE> const &V0,
            Vector3<TYPE> const &V1,
            Vector3<TYPE> const &V2)
    {  _Vtx0 = V0;  _Vtx1 = V1;  _Vtx2 = V2; }
  /*!
   * Udostêpnia wybrany wierzcho³ek z zastosowaniem jego indeksu.
   * \param Idx - indeks wierzcho³ka.
   * \pre 0 <= \e Idx <= 2.
   * \return referencjê do wspó³rzêdnych wybranego wierzcho³ka jako
   *         do obiektu sta³ego.
   */
  Vector3<TYPE> const &operator [] (unsigned int Idx) const 
                                      { return _Vtx[Idx]; }
  /*!
   * Udostêpnia wybrany wierzcho³ek z zastosowaniem jego indeksu.
   * \param Idx - indeks wierzcho³ka.
   * \pre 0 <= \e Idx <= 2.
   * \return referencjê do wspó³rzêdnych wybranego wierzcho³ka jako
   *         do obiektu modyfikowalnego.
   */
  Vector3<TYPE> &operator [] (unsigned int Idx) { return _Vtx[Idx]; }
  /*!
   *  Udostêpnia wspó³rzêdne pierwszego wierzcho³ka.
   *  Wspó³rzêdne dostêpne s± poprzez referencjê do obiektu sta³ego.
   */
  Vector3<TYPE> const &Vtx0() const { return _Vtx0; }
  /*!
   *  Udostêpnia wspó³rzêdne drugiego wierzcho³ka.
   *  Wspó³rzêdne dostêpne s± poprzez referencjê do obiektu sta³ego.
   */
  Vector3<TYPE> const &Vtx1() const { return _Vtx1; }
  /*!
   *  Udostêpnia wspó³rzêdne trzeciego wierzcho³ka.
   *  Wspó³rzêdne dostêpne s± poprzez referencjê do obiektu sta³ego.
   */
  Vector3<TYPE> const &Vtx2() const { return _Vtx2; }

  /*!
   *  Udostêpnia wspó³rzêdne pierwszego wierzcho³ka.
   *  Wspó³rzêdne dostêpne s± poprzez referencjê do obiektu modyfikowalnego.
   */
  Vector3<TYPE>  &Vtx0()  { return _Vtx0; }
  /*!
   *  Udostêpnia wspó³rzêdne drugiego wierzcho³ka.
   *  Wspó³rzêdne dostêpne s± poprzez referencjê do obiektu modyfikowalnego.
   */
  Vector3<TYPE>  &Vtx1()  { return _Vtx1; }
  /*!
   *  Udostêpnia wspó³rzêdne trzeciego wierzcho³ka.
   *  Wspó³rzêdne dostêpne s± poprzez referencjê do obiektu modyfikowalnego.
   */
  Vector3<TYPE>  &Vtx2()  { return _Vtx2; }

};


/*!
 *  Umo¿liwia wy¶wietlenie wierzcho³ków ¶cianki trójk±tnej.
 *  \param ostrm - strumien standaradowy,
 *  \param Tr - ¶cianka trójk±tna, której wierzcho³ki maj± zostaæ 
 *              wy¶wietlone.
 */
template <typename TYPE>
inline
std::ostream &operator << (std::ostream &ostrm, ViTriangle3<TYPE> const &Tr)
{
  return ostrm << "[" << Tr.Vtx0() << ", " << Tr.Vtx1() << ", " 
               << Tr.Vtx2() << "]";
}

#endif
