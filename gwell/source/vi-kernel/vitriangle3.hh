#ifndef VITRIANGLE3_HH
#define VITRIANGLE3_HH

/*! \file vitriangle3.hh
 *  Plik zawiera definicj� szablonu ViTriangle3. Wykorzystyny jest on
 *  do rozbijania dowolnej �cianki reprezentowanej przez wielobok wypuk�y
 *  na zbi�r tr�jk�t�w.
 *  \author  Bogdan Kreczmer
 *  \date    2004.03.27
 */



#ifdef __GNUG__
#pragma interface
#endif

#include <iostream>
#include "vector3.hh"


/*!
 *  Szablon wykorzystyny jest do modelowania pojedynczego tr�jk�ta.
 *  Wykorzystywane s� one do rozbijania dowolnej �cianki reprezentowanej
 *  przez wielobok wypuk�y na zbi�r tr�jk�t�w. 
 */
template<typename TYPE>
class ViTriangle3 {
  /*!
   *  Pole reprezentuje poszczeg�lne wierzcho�ki tr�jk�ta. 
   *  Kolejno�� wyst�powania wsp�rz�dnych wierzcho�k�w w tej tablicy
   *  okre�lona jest przez orientacj� brzegu, kt�ra wyznacza
   *  wierzchni� i spodni� cz�� tr�jk�tnej �cianki.
   */
  Vector3<TYPE>   _Vtx[3];
  /*!
   *  Referencje do pierwszego wierzcho�ka tr�jk�ta.
   */
  Vector3<TYPE>  &_Vtx0;
  /*!
   *  Referencje do drugiego wierzcho�ka tr�jk�ta.
   */
  Vector3<TYPE>  &_Vtx1;
  /*!
   *  Referencje do trzeciego wierzcho�ka tr�jk�ta.
   */
  Vector3<TYPE>  &_Vtx2;
 public:

  /*!
   *  Inicjalizuje pola referencyjne. Do wsp�rz�dnych wszystkich 
   *  wierzcho�k�w s� podstawiane warto�ci zerowe.
   */
  ViTriangle3(): _Vtx0(_Vtx[0]),  _Vtx1(_Vtx[1]),  _Vtx2(_Vtx[2]) {}
  /*!
   *  Inicjalizuje pola referencyjne. Do wsp�rz�dnych wszystkich 
   *  wierzcho�k�w s� podstawiane warto�ci dost�pne poprzez parametry.
   *  \param V0 - wsp�rz�dne pierwszego wierzcho�ka,
   *  \param V1 - wsp�rz�dne drugiego wierzcho�ka,
   *  \param V2 - wsp�rz�dne trzeciego wierzcho�ka.
   */
  ViTriangle3( Vector3<TYPE> const &V0,
              Vector3<TYPE> const &V1,
              Vector3<TYPE> const &V2): 
              _Vtx0(_Vtx[0]),  _Vtx1(_Vtx[1]),  _Vtx2(_Vtx[2]) 
      {  _Vtx0 = V0;  _Vtx1 = V1;  _Vtx2 = V2; }

  /*!
   *  Podstawia wsp�rz�dne dla wszystkich wierzcho�kow tr�jk�ta.
   *  \param V0 - wsp�rz�dne pierwszego wierzcho�ka,
   *  \param V1 - wsp�rz�dne drugiego wierzcho�ka,
   *  \param V2 - wsp�rz�dne trzeciego wierzcho�ka.
   */
  void Set( Vector3<TYPE> const &V0,
            Vector3<TYPE> const &V1,
            Vector3<TYPE> const &V2)
    {  _Vtx0 = V0;  _Vtx1 = V1;  _Vtx2 = V2; }
  /*!
   * Udost�pnia wybrany wierzcho�ek z zastosowaniem jego indeksu.
   * \param Idx - indeks wierzcho�ka.
   * \pre 0 <= \e Idx <= 2.
   * \return referencj� do wsp�rz�dnych wybranego wierzcho�ka jako
   *         do obiektu sta�ego.
   */
  Vector3<TYPE> const &operator [] (unsigned int Idx) const 
                                      { return _Vtx[Idx]; }
  /*!
   * Udost�pnia wybrany wierzcho�ek z zastosowaniem jego indeksu.
   * \param Idx - indeks wierzcho�ka.
   * \pre 0 <= \e Idx <= 2.
   * \return referencj� do wsp�rz�dnych wybranego wierzcho�ka jako
   *         do obiektu modyfikowalnego.
   */
  Vector3<TYPE> &operator [] (unsigned int Idx) { return _Vtx[Idx]; }
  /*!
   *  Udost�pnia wsp�rz�dne pierwszego wierzcho�ka.
   *  Wsp�rz�dne dost�pne s� poprzez referencj� do obiektu sta�ego.
   */
  Vector3<TYPE> const &Vtx0() const { return _Vtx0; }
  /*!
   *  Udost�pnia wsp�rz�dne drugiego wierzcho�ka.
   *  Wsp�rz�dne dost�pne s� poprzez referencj� do obiektu sta�ego.
   */
  Vector3<TYPE> const &Vtx1() const { return _Vtx1; }
  /*!
   *  Udost�pnia wsp�rz�dne trzeciego wierzcho�ka.
   *  Wsp�rz�dne dost�pne s� poprzez referencj� do obiektu sta�ego.
   */
  Vector3<TYPE> const &Vtx2() const { return _Vtx2; }

  /*!
   *  Udost�pnia wsp�rz�dne pierwszego wierzcho�ka.
   *  Wsp�rz�dne dost�pne s� poprzez referencj� do obiektu modyfikowalnego.
   */
  Vector3<TYPE>  &Vtx0()  { return _Vtx0; }
  /*!
   *  Udost�pnia wsp�rz�dne drugiego wierzcho�ka.
   *  Wsp�rz�dne dost�pne s� poprzez referencj� do obiektu modyfikowalnego.
   */
  Vector3<TYPE>  &Vtx1()  { return _Vtx1; }
  /*!
   *  Udost�pnia wsp�rz�dne trzeciego wierzcho�ka.
   *  Wsp�rz�dne dost�pne s� poprzez referencj� do obiektu modyfikowalnego.
   */
  Vector3<TYPE>  &Vtx2()  { return _Vtx2; }

};


/*!
 *  Umo�liwia wy�wietlenie wierzcho�k�w �cianki tr�jk�tnej.
 *  \param ostrm - strumien standaradowy,
 *  \param Tr - �cianka tr�jk�tna, kt�rej wierzcho�ki maj� zosta� 
 *              wy�wietlone.
 */
template <typename TYPE>
inline
std::ostream &operator << (std::ostream &ostrm, ViTriangle3<TYPE> const &Tr)
{
  return ostrm << "[" << Tr.Vtx0() << ", " << Tr.Vtx1() << ", " 
               << Tr.Vtx2() << "]";
}

#endif
