#ifndef PLAIN3f_HH
#define PLAIN3f_HH

/*!
 * \file plain3f.hh
 * Plik zawiera definicj� klasy Plain3f.
 * \author Bogdan Kreczmer
 * \date   2003.11
 */


#ifdef __GNUG__
#pragma interface
#endif


#include "vector3f.hh"

class Line3f;
class HalfLine3f;

/*!
 * Obiekty klasy Plain3f przechwuj� informacj� p�aszczyznie w 3D.
 * Do informacji tych nale�� warto�ci wsp�czynnik�w r�wnania p�aszczyzny
 * (w kartezja�skimi uk�adzie wsp�rz�dnych) o postaci:
 *
 * \f[       A*x + B*y + C*z + D = 0   \f]
 *
 * przy czym wsp�czynniki te maj� nast�puj�ce interpretacj�:
 * 
 *  \li  (\e A,\e B,\e C) - reprezentuj� wsp�rz�dne wektora normalnego
 *                         do p�aszczyzny,
 * 
 *  \li  e D       - modu� tej warto�ci jest odleg�o�ci� p�aszczyzny do pocz�tku
 *              uk�adu wsp�rz�dnych
 */
class Plain3f {
 private:
  Vector3f  _NVct; /*!< Wektor normalny do p�aszczyzny                       */
   /*!
    *  Wsp�czynnik \e D w r�wnaniu p�aszczyzny. Jego modu� odpowiada
    *  odleg�o�ci p�aszczyzny od �rodka uk�adu wsp�rz�dnych.
    */
  float     _D; 

 public:
   /*! 
    * Udost�pnia wektor normalny do p�aszczyzny.  
    */
  Vector3f const &GetNVct() const  { return _NVct;}
   /*!
    * Udost�pnia wsp�czynnik D r�wnania p�aszczyzny.  
    */
  float           GetD()    const  { return _D;}


   /*!
    * Wyznacza wsp�rz�dn� \e x-ow� punktu le��cego na p�aszczy�nie na
    * podstawie dw�ch pozosta�ych wsp�rz�dnych.
    * \param y - wsp�rz�dna \e y-owa punktu,
    * \param z - wsp�rz�dna \e z-owa punktu,
    * \return wsp�rz�dna \e x-ow� punktu.
    */
  float X(float y, float z) const;
   /*!
    * Wyznacza wsp�rz�dn� \e y-ow� punktu le��cego na p�aszczy�nie na
    * podstawie dw�ch pozosta�ych wsp�rz�dnych.
    * \param x - wsp�rz�dna \e x-owa punktu,
    * \param z - wsp�rz�dna \e z-owa punktu,
    * \return wsp�rz�dna \e y-ow� punktu.
    */
  float Y(float x, float z) const;
   /*!
    * Wyznacza wsp�rz�dn� \e z-ow� punktu le��cego na p�aszczy�nie na
    * podstawie dw�ch pozosta�ych wsp�rz�dnych.
    * \param x - wsp�rz�dna \e x-owa punktu,
    * \param y - wsp�rz�dna \e y-owa punktu,
    * \return wsp�rz�dna \e z-ow� punktu.
    */
  float Z(float x, float y) const;

   /*!
    * Nadaje nowe warto�ci wsp�rz�dnym wektorowa normalnego do p�aszczyzny.
    * \param x - nowa wsp�rz�dna \e x-owa,
    * \param y - nowa wsp�rz�dna \e y-owa,
    * \param z - nowa wsp�rz�dna \e z-owa.
    * \post Zostaj� przypisane  nowe warto�ci polu 
    *         \link Plain3f::_NVct _NVct\endlink.
    */
  void   SetNVct(float x, float y, float z) { _NVct.Set(x,y,z);}

   /*!
    * Nadaje nowe warto�ci wsp�rz�dnym wektorowa normalnego do p�aszczyzny.
    * \param Vct - wektor nowych wsp�rz�dnych dla wektora normalnego
    *              do p�aszczyzny.
    * \post Zostaj� przypisane  nowe warto�ci polu 
    *         \link Plain3f::_NVct _NVct\endlink.
    */
  void   SetNVct(Vector3f const &Vct) { _NVct = Vct;}

   /*!
    * Nadaje now� warto�� wsp�czynnikowi D w r�wnaniu p�aszczyzny.
    * \param  D_new - nowa warto�� dla wsp�czynika \e D.
    * \post  Polu \link Plain3f::_D _D\endlink zostaje przypisana
    *        nowa warto��.
    */
  void   SetD(float  D_new) {  _D = D_new;}

   /*!
    * Dokonuje normalizacji wsp�rz�dnych wektora normalnego do p�aszczyzny.
    * \post  Pole \link Plain3f::_NVct _NVct\endlink zostaje zmodyfikowane
    *        i po modyfikacji zawiera znormalizowane wsp�rz�dne wektora.
    */
  bool  NormalizeVct();

   /*!
    * Wyznacza r�wnanie p�aszczyzny przechodz�cej przez punkty P0, P1, P2.
    * \param P0 - wsp�rz�dne pierwszego punktu p�aszczyzny,
    * \param P1 - wsp�rz�dne drugiego punktu p�aszczyzny,
    * \param P2 - wsp�rz�dne trzeciego punktu p�aszczyzny.
    * \retval true - je�li wyznaczenie r�wnania p�aszczyzny powiod�o si�.
    * \retval false - je�li wyznaczenie r�wnania p�aszczyzny okaza�o si�
    *                 niemo�liwe.
    * \post W przypadku wyznaczenia r�wniania p�aszczyzny, wsp�czynniki
    *       tego r�wnania zostaj� zapisane w polach
    *       \link Plain3f::_NVct _NVct\endlink i \link Plain3f::_D _D\endlink.
    */
  bool   ComputePlain3f( Vector3f const &P0, 
                         Vector3f const &P1, 
                         Vector3f const &P2
                       );

   /*!
    * Metoda wyznacza punkt przeci�cia linii prostej z dan� p�aszczyzn�.
    * \param Ln - (b in) zawiera parametry linii prostej,
    * \param Pnt - (\b out) po zako�czeniu oblicze�, o ile okaza�o si�
    *              mo�liwe wyliczenie wsp�rz�dnych punktu, po przez ten
    *              parametr przekazywane s� jego wsp�rz�dne.
    * \param t - (\b out) zawiera parametr \e t, okre�laj�cy po�o�enie
    *             na prostej znalezionego punkty przeci�cia. Po�o�enie
    *             to jest dane w sensie parametrycznego r�wnania tej 
    *             prostej.
    * \retval true - gdy wyliczenie punktu przeci�cia by�o mo�liwe.
    * \retval false - gdy prosta z dan� p�aszczyzn� nie przecina si�.
    */
  bool  CrossPoint4Line(Line3f const &Ln, Vector3f &Pnt, float &t) const;

   /*!
    * Metoda wyznacza punkt przeci�cia linii p�prostej z dan� p�aszczyzn�.
    * \param HLn - (b in) zawiera parametry linii p�prostej,
    * \param Pnt - (\b out) po zako�czeniu oblicze�, o ile okaza�o si�
    *              mo�liwe wyliczenie wsp�rz�dnych punktu, po przez ten
    *              parametr przekazywane s� jego wsp�rz�dne.
    * \param t - (\b out) zawiera parametr \e t, okre�laj�cy po�o�enie
    *             na p�prostej znalezionego punkty przeci�cia. Po�o�enie
    *             to jest dane w sensie parametrycznego r�wnania tej 
    *             p�prostej.
    * \retval true - gdy wyliczenie punktu przeci�cia by�o mo�liwe.
    * \retval false - gdy p�prosta z dan� p�aszczyzn� nie przecina si�.
    */
  bool  CrossPoint4HalfLine(HalfLine3f const &HLn, Vector3f &Pnt, float &t) const;
};



/*
inline
float Plain3f::ComputeZ(float x, float y) const 
 { return (-GetNVct().x*x-GetNVct().y*y-GetD())/GetNVct().z;}
*/

#endif
