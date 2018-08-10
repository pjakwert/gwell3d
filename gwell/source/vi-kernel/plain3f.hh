#ifndef PLAIN3f_HH
#define PLAIN3f_HH

/*!
 * \file plain3f.hh
 * Plik zawiera definicjê klasy Plain3f.
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
 * Obiekty klasy Plain3f przechwuj± informacjê p³aszczyznie w 3D.
 * Do informacji tych nale¿± warto¶ci wspó³czynników równania p³aszczyzny
 * (w kartezjañskimi uk³adzie wspó³rzêdnych) o postaci:
 *
 * \f[       A*x + B*y + C*z + D = 0   \f]
 *
 * przy czym wspó³czynniki te maj± nastêpuj±ce interpretacjê:
 * 
 *  \li  (\e A,\e B,\e C) - reprezentuj± wspó³rzêdne wektora normalnego
 *                         do p³aszczyzny,
 * 
 *  \li  e D       - modu³ tej warto¶ci jest odleg³o¶ci± p³aszczyzny do pocz±tku
 *              uk³adu wspó³rzêdnych
 */
class Plain3f {
 private:
  Vector3f  _NVct; /*!< Wektor normalny do p³aszczyzny                       */
   /*!
    *  Wspó³czynnik \e D w równaniu p³aszczyzny. Jego modu³ odpowiada
    *  odleg³o¶ci p³aszczyzny od ¶rodka uk³adu wspó³rzêdnych.
    */
  float     _D; 

 public:
   /*! 
    * Udostêpnia wektor normalny do p³aszczyzny.  
    */
  Vector3f const &GetNVct() const  { return _NVct;}
   /*!
    * Udostêpnia wspó³czynnik D równania p³aszczyzny.  
    */
  float           GetD()    const  { return _D;}


   /*!
    * Wyznacza wspó³rzêdn± \e x-ow± punktu le¿±cego na p³aszczy¼nie na
    * podstawie dwóch pozosta³ych wspó³rzêdnych.
    * \param y - wspó³rzêdna \e y-owa punktu,
    * \param z - wspó³rzêdna \e z-owa punktu,
    * \return wspó³rzêdna \e x-ow± punktu.
    */
  float X(float y, float z) const;
   /*!
    * Wyznacza wspó³rzêdn± \e y-ow± punktu le¿±cego na p³aszczy¼nie na
    * podstawie dwóch pozosta³ych wspó³rzêdnych.
    * \param x - wspó³rzêdna \e x-owa punktu,
    * \param z - wspó³rzêdna \e z-owa punktu,
    * \return wspó³rzêdna \e y-ow± punktu.
    */
  float Y(float x, float z) const;
   /*!
    * Wyznacza wspó³rzêdn± \e z-ow± punktu le¿±cego na p³aszczy¼nie na
    * podstawie dwóch pozosta³ych wspó³rzêdnych.
    * \param x - wspó³rzêdna \e x-owa punktu,
    * \param y - wspó³rzêdna \e y-owa punktu,
    * \return wspó³rzêdna \e z-ow± punktu.
    */
  float Z(float x, float y) const;

   /*!
    * Nadaje nowe warto¶ci wspó³rzêdnym wektorowa normalnego do p³aszczyzny.
    * \param x - nowa wspó³rzêdna \e x-owa,
    * \param y - nowa wspó³rzêdna \e y-owa,
    * \param z - nowa wspó³rzêdna \e z-owa.
    * \post Zostaj± przypisane  nowe warto¶ci polu 
    *         \link Plain3f::_NVct _NVct\endlink.
    */
  void   SetNVct(float x, float y, float z) { _NVct.Set(x,y,z);}

   /*!
    * Nadaje nowe warto¶ci wspó³rzêdnym wektorowa normalnego do p³aszczyzny.
    * \param Vct - wektor nowych wspó³rzêdnych dla wektora normalnego
    *              do p³aszczyzny.
    * \post Zostaj± przypisane  nowe warto¶ci polu 
    *         \link Plain3f::_NVct _NVct\endlink.
    */
  void   SetNVct(Vector3f const &Vct) { _NVct = Vct;}

   /*!
    * Nadaje now± warto¶æ wspó³czynnikowi D w równaniu p³aszczyzny.
    * \param  D_new - nowa warto¶æ dla wspó³czynika \e D.
    * \post  Polu \link Plain3f::_D _D\endlink zostaje przypisana
    *        nowa warto¶æ.
    */
  void   SetD(float  D_new) {  _D = D_new;}

   /*!
    * Dokonuje normalizacji wspó³rzêdnych wektora normalnego do p³aszczyzny.
    * \post  Pole \link Plain3f::_NVct _NVct\endlink zostaje zmodyfikowane
    *        i po modyfikacji zawiera znormalizowane wspó³rzêdne wektora.
    */
  bool  NormalizeVct();

   /*!
    * Wyznacza równanie p³aszczyzny przechodz±cej przez punkty P0, P1, P2.
    * \param P0 - wspó³rzêdne pierwszego punktu p³aszczyzny,
    * \param P1 - wspó³rzêdne drugiego punktu p³aszczyzny,
    * \param P2 - wspó³rzêdne trzeciego punktu p³aszczyzny.
    * \retval true - je¶li wyznaczenie równania p³aszczyzny powiod³o siê.
    * \retval false - je¶li wyznaczenie równania p³aszczyzny okaza³o siê
    *                 niemo¿liwe.
    * \post W przypadku wyznaczenia równiania p³aszczyzny, wspó³czynniki
    *       tego równania zostaj± zapisane w polach
    *       \link Plain3f::_NVct _NVct\endlink i \link Plain3f::_D _D\endlink.
    */
  bool   ComputePlain3f( Vector3f const &P0, 
                         Vector3f const &P1, 
                         Vector3f const &P2
                       );

   /*!
    * Metoda wyznacza punkt przeciêcia linii prostej z dan± p³aszczyzn±.
    * \param Ln - (b in) zawiera parametry linii prostej,
    * \param Pnt - (\b out) po zakoñczeniu obliczeñ, o ile okaza³o siê
    *              mo¿liwe wyliczenie wspó³rzêdnych punktu, po przez ten
    *              parametr przekazywane s± jego wspó³rzêdne.
    * \param t - (\b out) zawiera parametr \e t, okre¶laj±cy po³o¿enie
    *             na prostej znalezionego punkty przeciêcia. Po³o¿enie
    *             to jest dane w sensie parametrycznego równania tej 
    *             prostej.
    * \retval true - gdy wyliczenie punktu przeciêcia by³o mo¿liwe.
    * \retval false - gdy prosta z dan± p³aszczyzn± nie przecina siê.
    */
  bool  CrossPoint4Line(Line3f const &Ln, Vector3f &Pnt, float &t) const;

   /*!
    * Metoda wyznacza punkt przeciêcia linii pó³prostej z dan± p³aszczyzn±.
    * \param HLn - (b in) zawiera parametry linii pó³prostej,
    * \param Pnt - (\b out) po zakoñczeniu obliczeñ, o ile okaza³o siê
    *              mo¿liwe wyliczenie wspó³rzêdnych punktu, po przez ten
    *              parametr przekazywane s± jego wspó³rzêdne.
    * \param t - (\b out) zawiera parametr \e t, okre¶laj±cy po³o¿enie
    *             na pó³prostej znalezionego punkty przeciêcia. Po³o¿enie
    *             to jest dane w sensie parametrycznego równania tej 
    *             pó³prostej.
    * \retval true - gdy wyliczenie punktu przeciêcia by³o mo¿liwe.
    * \retval false - gdy pó³prosta z dan± p³aszczyzn± nie przecina siê.
    */
  bool  CrossPoint4HalfLine(HalfLine3f const &HLn, Vector3f &Pnt, float &t) const;
};



/*
inline
float Plain3f::ComputeZ(float x, float y) const 
 { return (-GetNVct().x*x-GetNVct().y*y-GetD())/GetNVct().z;}
*/

#endif
