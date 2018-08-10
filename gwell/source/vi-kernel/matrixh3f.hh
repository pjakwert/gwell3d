#ifndef MATRIXH3F_HH
#define MATRIXH3F_HH

/*!
 * \file        matrixh3f.hh
 * Plik zawiera definicjê klasy MatrixH3f. Jest ona podstaw± wszystkich
 * transforacji miêdzy poszczególnymi uk³adami wspó³rzêdnych.
 * \author	Bogdan Kreczmer
 * \date        2004.01
 */


#ifdef __GNUG__
#pragma interface
#endif


#include "vector3f.hh"
#include <cmath>
#include <cstdio>
#include <iostream>
#include "matrixrt3f.hh"
#include "vi-utils.hh"
#include "bexception.hh"

class ExtString;
class SxInterp;


/*
 * Numeracja bledow dla matrixh3f rozpoczyna sie od: 200.
 */

/*!
 * Numer b³êdu zg³aszanego w przypadku, gdy napis poddany konwersji
 * na typ \link matrixh3f::TransOrder
 *                    TransOrder\endlink nie odpowiada
 * ¿adnej z akceptowanych nazw.\n
 * Zg³aszanemu b³êdowi odpowiada mu komunikat zdefinowany przez sta³±
 *  \link vimatrixh3f.hh::ERRMSG_TRANSORDER__IMPROPER_NAME
 *                     ERRMSG_TRANSORDER__IMPROPER_NAME\endlink
 */
#define ERRNUM_TRANSORDER__IMPROPER_NAME  200
/*!
 * Komunikat b³êdu zg³aszanego w przypadku, gdy napis poddany konwersji
 * na typ \link matrixh3f.hh::TransformType 
 *                            TransformType\endlink nie odpowiada
 * ¿adnej z akceptowanych nazw.
 */
#define ERRMSG_TRANSORDER__IMPROPER_NAME  "Nazwa warto¶ci typu"\
    " TransOrder nie odpowiada ¿adnej z oczekiwanych nazw."\
    " Otrzymano nazwê \"%s\", oczekuje siê jednej z nazw: %s"




/*!
 *  Umo¿liwia kowersjê typu, np z const MatrixH3f na MatrixH3f.
 *  \param Type - nazwa typu.
 */
#define USE(Type)    (*(Type*)this)

 /*!
  *  Okre¶la jednostkê w jakiej wyra¿one s± k±ty. Jednostkami
  *  tymi dla poszczególnych warto¶ci mog± byc:
  *
  *    \li  AU_Deg   - stopnie,
  *    \li  AU_Rad   - radiany.
  */
typedef enum { AU_Deg, AU_Rad } AngleUnit;


 /*!
  *  Okre¶la koleno¶æ realizacji translacji, tzn. przed dokonaniem
  *  rotacji lub po.
  *
  *    \li  TO_Before   - po rotacji,
  *    \li  TO_After    - przed rotacj±.
  */
typedef enum { TO_Before, TO_After } TransOrder;

namespace Vi {
  const char *MakeString(TransOrder Val);
  TransOrder String2TransOrder(const char *Name) throw(Ba::Exception);
}


class MatrixH3f: protected MatrixRT3f { //==================================
  public:

    /*!
     * Okre¶la typ k±tów w reprezentacji przekszta³cenia. W tej chwili
     * dostêpne
     * s± dwie reprezentacje: poprzez k±ty Eulera i k±ty obrotu wzglêdem osi
     * OX,OY,OZ.
     *
     *    \li \p AT_xyz    - obrót wzgl. osi X,Y,Z
     *    \li \p AT_Euler  - k±ty Eulera
     *
     */
   typedef enum { AT_xyz, AT_Euler } AnglesType;

    /*!
     * Decyduje o typie rotacji, czy ma ona zostaæ dokonana wzglêdem
     * lokalnego uk³adu wspó³rzêdnych, czy te¿ wzglêdem uk³adu 
     * wspó³rzêdnych rodzica.
     */
   typedef enum { CS_Parent, CS_Local } CoordSysType;


  class Parameters { //_______________________________________________________

    AnglesType  _AngInterp;
    TransOrder  _TransOrder;
    Vector3f    _RotAng;
    Vector3f    _Trans; 
    Vector3f    _Scale;

   public:

    void SetAngInterp(AnglesType ATyp) { _AngInterp = ATyp; }
    AnglesType GetAngInterp() const { return _AngInterp; }

    Parameters &SetTransType(TransOrder TOrder)
                                 { _TransOrder = TOrder;  return *this; }
    void SetTrans(float x, float y, float z) { _Trans.Set(x,y,z);}

    void SetAng_Rad( float ax_rad, float ay_rad, float az_rad )
                                 { _RotAng.Set(ax_rad,ay_rad,az_rad); }
    void SetAng( float ax, float ay, float az, AngleUnit AngUnit )
              { 
                if (AngUnit == AU_Rad) _RotAng.Set(ax,ay,az);
                  else _RotAng.Set(DEG2RAD(ax),DEG2RAD(ay),DEG2RAD(az));
              }

    void SetAng( const Vector3f  &Ang, AngleUnit AngUnit ) 
                            { SetAng(Ang.x,Ang.y,Ang.z,AngUnit); }

    void SetAngX_Rad(float ang) { _RotAng.x = ang; }
     /*!
      *  Podstawia now± warto¶æ k±ta rotacji wzglêdem osi OY.
      *  K±t wyra¿ony musi byæ w radianach.  Warto¶ci pozosta³ych k±tów
      *  nie ulegaj± zmianie.
      *  \param ang - nowa warto¶æ rotacji wzglêdem osi OY. 
      */
     void SetAngY_Rad(float ang) { _RotAng.y = ang; }
     /*!
      *  Podstawia now± warto¶æ k±ta rotacji wzglêdem osi OZ.
      *  K±t wyra¿ony musi byæ w radianach.  Warto¶ci pozosta³ych k±tów
      *  nie ulegaj± zmianie.
      *  \param ang - nowa warto¶æ rotacji wzglêdem osi OZ. 
      */
     void SetAngZ_Rad(float ang) { _RotAng.z = ang; }
     /*!
      * Nadaje nowe warto¶ci wektorowi wspó³czynników skali
      * (patrz pole  \link MatrixH3f::Parameters::_Scale _Scale\endlink).
      * \param Sc - wektor nowych warto¶ci wspó³czynników skali.
      * \return referencjê do samego siebie (\b *this).
      * \post Do pola \link MatrixH3f::Parameters::_Scale _Scale\endlink
      *       zostaje podstawiony nowy wektor (\e Sc) warto¶ci wspó³czynników
      *       skali wzglêdem poszczególnych osi.
      */
     Parameters &SetScale(Vector3f const &Sc){ _Scale.Set(Sc); return *this; }
     /*!
      * Nadaje nowe warto¶ci wektorowi translacji
      * (patrz pole  \link MatrixH3f::Parameters::_Trans _Trans\endlink).
      * \param Tr - nowy wektor translacji.
      * \return referencjê do samego siebie (\b *this).
      * \post Do pola \link MatrixH3f::Parameters::_Trans _Trans\endlink
      *       zostaje podstawiony nowy wektor translacji (\e Tr).
      */
     Parameters &SetTrans(Vector3f const &Tr) { _Trans.Set(Tr); return *this; }
     /*!
      * Nadaje nowe warto¶ci wektorowi k±tów rotacji 
      * (patrz pole  \link MatrixH3f::Parameters::_RotAng _RotAng\endlink).
      * \param Ro - wektor nowych k±tów rotacji wyra¿onych w radianach.
      * \return referencjê do samego siebie (\b *this).
      * \post Do pola \link MatrixH3f::Parameters::_RotAng _RotAng\endlink
      *       zostaje podstawiony nowy wektor (\e Ro) warto¶ci k±tów
      *       rotacji wzglêdem poszczególnych osi.
      */
     Parameters &SetAng(Vector3f const &Ro) { _RotAng.Set(Ro);  return *this; }

      /*!
       *  Nadaje nowe warto¶ci wspó³czynnikom skali.
       *  \param sx - nowa warto¶æ wspó³czynnika skali wzglêdem osi OX,
       *  \param sy - nowa warto¶æ wspó³czynnika skali wzglêdem osi OY,
       *  \param sz - nowa warto¶æ wspó³czynnika skali wzglêdem osi OZ.
       *  \post Nowe warto¶ci wspó³czynników skali zostaj± wpisane do
       *        pola \link MatrixH3f::Parameters::_Scale _Scale\endlink.
       */
     void SetScale(float sx, float sy, float sz) { _Scale.Set(sx,sy,sz); }

      /*!
       *  Nadaje nowe warto¶ci wspó³czynnikom skali.
       *  \param x_S - nowa warto¶æ wspó³czynnika skali wzglêdem osi OX,
       *  \post Nowa warto¶æ wspó³czynnika \e x-owej wspó³rzêdnej 
       *        wektora skali zostaje wpisane do
       *        pola \link MatrixH3f::Parameters::_Scale _Scale\endlink.
       */
     void SetScaleX(float x_S) { _Scale.x = x_S; }
      /*!
       *  Nadaje nowe warto¶ci wspó³czynnikom skali.
       *  \param y_S - nowa warto¶æ wspó³czynnika skali wzglêdem osi OY,
       *  \post Nowa warto¶æ wspó³czynnika \e y-owej wspó³rzêdnej 
       *        wektora skali zostaje wpisane do
       *        pola \link MatrixH3f::Parameters::_Scale _Scale\endlink.
       */
     void SetScaleY(float y_S) { _Scale.y = y_S; }
      /*!
       *  Nadaje nowe warto¶ci wspó³czynnikom skali.
       *  \param z_S - nowa warto¶æ wspó³czynnika skali wzglêdem osi OZ,
       *  \post Nowa warto¶æ wspó³czynnika \e z-owej wspó³rzêdnej 
       *        wektora skali zostaje wpisane do
       *        pola \link MatrixH3f::Parameters::_Scale _Scale\endlink.
       */
     void SetScaleZ(float z_S) { _Scale.z = z_S; }

      /*! 
       * Udostêpnia wektor wspó³czynników skali dla poszczególnuch osi.
       * Warto¶ci te s± udostêpnione z pola 
       * \link MatrixH3f::Parameters::_Scale _Scale\endlink.
       *
       * Uwaga: Pobieranie wspó³czynników skali nie zale¿y od
       *        kolejno¶ci wykonanej translacji.
       */
      Vector3f const &GetScale() const { return _Scale; }

      /*! 
       * Udostêpnia wektor translacji pocz±tku uk³adu wspó³rzêdnych.
       * Warto¶ci te s± udostêpnione z pola 
       * \link MatrixH3f::Parameters::_Trans _Trans\endlink.
       */
     Vector3f const &GetTrans() const { return _Trans; }
      /*! 
       * Udostêpnia wektor k±tów rotacji dla poszczególnch osi.
       * Warto¶ci te s± udostêpnione z pola 
       * \link MatrixH3f::Parameters::_RotAng _RotAng\endlink.
       */
     Vector3f const &GetAng_Rad() const { return _RotAng; }

      /*! 
       * Udostêpnia warto¶æ k±ta pierwszej rotacji. Warto¶æ k±ta
       * wyra¿ona jest w stopniach.
       * Udostêpniona jest z pola 
       * \link MatrixH3f::Parameters::_RotAng _RotAng.x\endlink.
       */
     float GetAng1_Deg() const { return RAD2DEG(_RotAng.x); }
      /*! 
       * Udostêpnia warto¶æ k±ta drugiej rotacji. Warto¶æ k±ta
       * wyra¿ona jest w stopniach.
       * Udostêpniona jest z pola 
       * \link MatrixH3f::Parameters::_RotAng _RotAng.y\endlink.
       */
     float GetAng2_Deg() const { return RAD2DEG(_RotAng.y); }
      /*! 
       * Udostêpnia warto¶æ k±ta trzeciej rotacji. Warto¶æ k±ta
       * wyra¿ona jest w stopniach.
       * Udostêpniona jest z pola 
       * \link MatrixH3f::Parameters::_RotAng _RotAng.y\endlink.
       */
     float GetAng3_Deg() const { return RAD2DEG(_RotAng.z); }


     Parameters &operator <<= (MatrixH3f const &Mtx);


     int Save(FILE *f);
  

      /*!
       * Inicjalizuje parametry transformacji jako parametry przekszta³cenia 
       * to¿samo¶ciowego, tzn. k±ty rotacji oraz wektor translacji maj± zerowe
       * warto¶ci, za¶ wspó³czynniki skali maj± warto¶ci 1.
       */
     Parameters(){ _RotAng.Set_0(); _Trans.Set_0(); _Scale.Set_1(); };
   }; //_______________________ Parameters ___________________________________

  private:

    /*!
     *  Okre¶la w jakich jednostkach wyra¿ony s± k±ty rotacji.
     *  Pole to ma charakter roboczy i jest wykorzystywane w trakcie
     *  operacji pobierania warto¶ci k±tów.
     */
    mutable AngleUnit   _AngUnit;


    /*!
     *  Okre¶la czy warto¶ci k±tów w polu  
     *  \link MatrixH3f::_RotAng _RotAng\endlink nale¿y interpretowaæ jako
     *  k±ty Eulera (warto¶æ \p AT_Euler) czy te¿ jako k±ty obrotu 
     *  wzglêdem osi OX, OY i OZ (warto¶æ \p AT_xyz).
     */
    mutable AnglesType  _AngInterp;


     /*!
      * Zawiera k±ty rotacji. Iterpretacja tych k±tów oke¶lona jest
      * poprzez warto¶æ pola \link MatrixH3f::_AngInterp _AngInterp\endlink.
      * Faktyczne wspó³czynniki macierzy transformacji znajduj± siê w 
      * \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink.  O tym czy warto¶ci
      * pola \link MatrixH3f::_Scale _Scale\endlink s±
      * adekwatne do wspó³czynników w 
      * \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink informuje warto¶æ w polu
      * \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink. 
      *  Parametry przestaj± byæ adekwatne je¿eli podstawiany 
      * zostaje wynik mno¿enia dwóch macierzy. Metody pobieraj±ce konkretne
      * warto¶ci wspó³czynników wykrywaj± to i odpowiednio aktualizuj± 
      * warto¶ci parametrów.
      */
    Vector3f  _RotAng;

     /*!
      * Zawiera wektor translacji. Faktyczne 
      * wspó³czynniki macierzy transformacji znajduj± siê w 
      * \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink.  O tym czy warto¶ci
      * pola \link MatrixH3f::_Scale _Scale\endlink s±
      * adekwatne do wspó³czynników w 
      * \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink informuje warto¶æ w polu
      * \link MatrixH3f::_Valid_Trans _Valid_Trans\endlink. 
      *  Parametry przestaj± byæ adekwatne je¿eli podstawiany 
      * zostaje wynik mno¿enia dwóch macierzy. Metody pobieraj±ce konkretne
      * warto¶ci wspó³czynników wykrywaj± to i odpowiednio aktualizuj± 
      * warto¶ci parametrów.
      */
    Vector3f  _Trans; 

     /*!
      * Zawiera wspó³czynniki skali wzd³u¿ osi OX, OY, OZ. Faktyczne 
      * wspó³czynniki macierzy transformacji znajduj± siê w 
      * \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink.  O tym czy warto¶ci
      * pola \link MatrixH3f::_Scale _Scale\endlink s±
      * adekwatne do wspó³czynników w 
      * \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink informuje warto¶æ
      * w polu \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink. 
      *  Parametry przestaj± byæ adekwatne je¿eli podstawiany 
      * zostaje wynik mno¿enia dwóch macierzy. Metody pobieraj±ce konkretne
      * warto¶ci wspó³czynników wykrywaj± to i odpowiednio aktualizuj± 
      * warto¶ci parametrów.
      */
    Vector3f  _Scale;


   /*! 
    * Warto¶æ pola okre¶la czy parametry transformacji 
    * \link MatrixH3f::_Trans _Trans\endlink
    * odpowiada
    * faktycznej warto¶ci wspó³czynnikom macierzy transformacji
    * w \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink.
    */
    mutable bool     _Valid_Trans;

   /*! 
    * Warto¶æ pola okre¶la czy parametry transformacji 
    * \link MatrixH3f::_Trans _Trans\endlink
    * odpowiada translacji po rotacji (\p TO_After),
    * czy te¿ przed (\p TO_Before).
    */
    mutable TransOrder   _Trans_Order;

   /*! 
    * Warto¶æ pola okre¶la czy parametry transformacji 
    * \link MatrixH3f::_Scale _Scale\endlink
    * odpowiada
    * faktycznej warto¶ci wspó³czynnikom macierzy transformacji
    * w \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink.
    */
    mutable bool     _Valid_Scale;

   /*!
    * Warto¶æ pola okre¶la czy parametry transformacji 
    * \link MatrixH3f::_RotAng _RotAng\endlink
    * odpowiada
    * faktycznej warto¶ci wspó³czynnikom macierzy transformacji
    * w \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink.
    */
    mutable bool     _Valid_RotAng;


    /*!
     * Ustawia sposób interpretacji k±tów rotacji.
     * \param ATyp - nowa wartosc dla pola 
     * \link MatrixH3f::_AngInterp _AngInterp\endlink informuj±ca o sposobie
     *  interpretacji k±tów rotacji.
     * \post Zostaje zmodyfikowna warto¶æ pola 
     * \link MatrixH3f::_AngInterp _AngInterp\endlink.
     */
    void SetAngInterp(AnglesType ATyp) { _AngInterp = ATyp; }



    /*!
     * Czyni niewa¿nymi aktualne warto¶ci pola 
     * \link MatrixH3f::_Trans _Trans\endlink. W ten sposób pozosta³e
     * metody s± informowane, ¿e przed skorzystaniem z tego pola
     * nale¿y zaktualizowaæ jego warto¶æ na podstawie warto¶ci
     * parametrów macierzy transformacji.
     * \post Pole
     *  \link MatrixH3f::_Valid_Trans MatrixH3f::_Valid_Trans\endlink
     *  ma warto¶æ \p false.
     */
    void InvalidParam_Trans() { _Valid_Trans = false; }


    /*!
     * Czyni wa¿nymi aktualne warto¶ci pola 
     * \link MatrixH3f::_Trans _Trans\endlink. W ten sposób pozosta³e
     * metody s± informowane, ¿e przed skorzystaniem z tego pola
     * nie jest potrzebna aktualizacja jego warto¶ci.
     * Nieniejsza metoda operuje tylko na polach
     * \link MatrixH3f::_Valid_Trans _Valid_Trans\endlink
     * oraz
     *  \link MatrixH3f::_Trans_Order _Trans_Order\endlink.
     *
     * \post Pole
     *  \link MatrixH3f::_Valid_Trans _Valid_Trans\endlink
     *  ma warto¶æ \p true, za¶ 
     *  \link MatrixH3f::_Trans_Order _Trans_Order\endlink
     *  maj± warto¶æ \p TO_After.
     */
    void ValidParam_Trans_TAfterR() 
                      {_Trans_Order = TO_After; _Valid_Trans = true;}

    /*!
     * Czyni wa¿nymi aktualne warto¶ci pola 
     * \link MatrixH3f::_Trans _Trans\endlink. W ten sposób pozosta³e
     * metody s± informowane, ¿e przed skorzystaniem z tego pola
     * nie jest potrzebna aktualizacja jego warto¶ci.
     * Nieniejsza metoda operuje tylko na polach
     * \link MatrixH3f::_Valid_Trans _Valid_Trans\endlink
     * oraz
     *  \link MatrixH3f::_Trans_Order _Trans_Order\endlink.
     *
     * \post Pola
     *  \link MatrixH3f::_Valid_Trans _Valid_Trans\endlink
     *  ma warto¶æ \p true, za¶ 
     *  \link MatrixH3f::_Trans_Order _Trans_Order\endlink
     *  warto¶æ \p TO_Before.
     */
    void ValidParam_Trans_TBeforeR() 
                          {_Trans_Order = TO_Before; _Valid_Trans = true; }


    /*!
     * Czyni wa¿nymi aktualne warto¶ci pola 
     * \link MatrixH3f::_Scale _Scale\endlink. W ten sposób pozosta³e
     * metody s± informowane, ¿e przed skorzystaniem z tego pola
     * nie jest potrzebna aktualizacja jego warto¶ci.
     * Nieniejsza metoda operuje tylko na polu
     * \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink.
     * \post Pole
     *  \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink
     *  ma warto¶æ \p true.
     */
    void ValidParam_Scale() { _Valid_Scale = true; }

   /*!
    * Ustawia znaczniki wa¿no¶ci zawarto¶ci pola
    * \link MatrixH3f::_RotAng _RotAng\endlink przyjmuj±c, ¿e
    * warto¶ciomi k±tów s± k±ty Eulera.
    * \post Polu
    * \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
    * przypisana zostaje warto¶æ \p true. Natomiast polu
    * \link MatrixH3f::_AngInterp _AngInterp\endlink warto¶æ
    * \p AT_Euler.
    */
    void ValidParam_Euler_Angles() 
                        { _Valid_RotAng = true; SetAngInterp(AT_Euler); }

   /*!
    * Ustawia znaczniki wa¿no¶ci zawarto¶ci pola
    * \link MatrixH3f::_RotAng _RotAng\endlink przyjmuj±c, ¿e
    * warto¶ciomi k±tów s± k±ty \e XYZ.
    * \post Polu
    * \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
    * przypisana zostaje warto¶æ \p true. Natomiast polu
    * \link MatrixH3f::_AngInterp _AngInterp\endlink warto¶æ
    * \p AT_xyz.
    */
    void ValidParam_XYZ_Angles() 
                        { _Valid_RotAng = true; SetAngInterp(AT_xyz); }




   /*!
    * Ustawia znaczniki wa¿no¶ci zawarto¶ci pól
    * \link MatrixH3f::_Scale _Scale\endlink oraz
    * \link MatrixH3f::_RotAng _RotAng\endlink przyjmuj±c, ¿e
    * warto¶ciomi k±tów s± k±ty Eulera.
    * \post Polom \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink
    * oraz \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
    * przypisana zostaje warto¶æ \p true. Natomiast polu
    * \link MatrixH3f::_AngInterp _AngInterp\endlink warto¶æ
    * \p AT_Euler.
    */
    void ValidParam_Scale_Euler_Angles() 
                        { ValidParam_Scale();  ValidParam_Euler_Angles(); }


   /*!
    * Ustawia znaczniki wa¿no¶ci zawarto¶ci pól
    * \link MatrixH3f::_Scale _Scale\endlink oraz
    * \link MatrixH3f::_RotAng _RotAng\endlink przyjmuj±c, ¿e
    * warto¶ciomi k±tów s± k±ty \e XYZ.
    * \post Polom \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink
    * oraz \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
    * przypisana zostaje warto¶æ \p true. Natomiast polu
    * \link MatrixH3f::_AngInterp _AngInterp\endlink warto¶æ
    * \p AT_xyz.
    */
    void ValidParam_Scale_XYZ_Angles() 
                        { ValidParam_Scale();  ValidParam_XYZ_Angles(); }



    /*!
     *  Aktualizuje warto¶æ pola \link MatrixH3f::_Scale _Scale\endlink, 
     *  w którym zapisany jest
     *  wektor wspó³czynników skali dla poszczególnych osi. 
     *  Zapisywane warto¶ci wyliczane s± na podstawie aktualnych parameterów
     *  macierzy transformacji.
     * \post Pole 
     *   \link MatrixH3f::_Valid_Scale  _Valid_Scale\endlink
     *   ma warto¶æ \p true.
     */
    void UpdateParam_Scale()
      {
        if (_Valid_Scale) return;
        MatrixRT3f::GetScale(_Scale);
        ValidParam_Scale();
      }


   void UpdateParam_Trans_TAfterR();
   void UpdateParam_Trans_TBeforeR();


    /*!
     *  Aktualizuje wektor k±tów rotacji, traktuj±c je
     *  jako k±ty Eulera. Operacja wykonywana jest tylko wtedy
     *  gdy stwierdzone zostanie, ¿e warto¶ci k±tów nie s± aktualne
     *  w stosunku do warto¶ci macierzy lub nie reprezentuj± one
     *  k±tów Eulera.
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
    void UpdateParam_Euler_Angles_condScale();
    void UpdateParam_XYZ_Angles_condScale();
    void UpdateParam_Angles_condScale_Auto();



     /*!
      * Zmienia warto¶æ pól 
      * \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink,
      * \link MatrixH3f::_Valid_Trans _Valid_Trans\endlink, oraz
      * \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink,
      * na \p true
      * sygnalizuj±c w ten sposób, ¿e warto¶ci parametrów transformacji
      * zapisane w polach 
      * \link MatrixH3f::_RotAng _RotAng\endlink,
      * \link MatrixH3f::_Trans _Trans\endlink oraz
      * \link MatrixH3f::_Scale _Scale\endlink,
      * s± zgodne z
      * faktycznymi warto¶ciami w 
      * \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink.
      */
    void   SetParamValid() 
            { _Valid_Trans = _Valid_Scale = _Valid_RotAng = true; }
     /*!
      * Informuj±c±, czy warto¶ci parametrów transformacji
      * zapisane w polach 
      * \link MatrixH3f::_RotAng _RotAng\endlink,
      * \link MatrixH3f::_Trans _Trans\endlink oraz
      * \link MatrixH3f::_Scale _Scale\endlink,
      * s± zgodne z
      * faktycznymi warto¶ciami w 
      *         \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink.
      */
    bool  AreParamValid() const 
        { return _Valid_Trans && _Valid_Scale && _Valid_RotAng; }

     /*!
      * Zmienia warto¶æ pól 
      * \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink,
      * \link MatrixH3f::_Valid_Trans _Valid_Trans\endlink, oraz
      * \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink,
      * na \p false
      * sygnalizuj±c w ten sposób, ¿e warto¶ci parametrów transformacji
      * zapisane w polach 
      * \link MatrixH3f::_RotAng _RotAng\endlink,
      * \link MatrixH3f::_Trans _Trans\endlink oraz
      * \link MatrixH3f::_Scale _Scale\endlink,
      * nie odpowiadaj±
      * faktycznymi warto¶ciomi w 
      * \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink.
      */
    void   SetParamInvalid() 
            { _Valid_Scale = _Valid_Trans = _Valid_RotAng = false; }

    void UpdateParam_Scale_XYZ_Angles();
    void UpdateParam_Scale_Euler_Angles();
    void UpdateParam_Scale_Angles_Auto();

    void SetAng_Auto_TAfterR_Rad( const Vector3f &Rot, 
                                  const Vector3f &Scale
                                );

  //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  public:

   AnglesType GetAngInterp() const { return _AngInterp; }
   TransOrder GetTransOrder() const { return _Trans_Order; }

   const Vector3f &GetScale() const;
   float GetScaleX() const 
              { USE(MatrixH3f).UpdateParam_Scale();  return _Scale.x; }
   float GetScaleY() const 
              { USE(MatrixH3f).UpdateParam_Scale();  return _Scale.y; }
   float GetScaleZ() const 
             {USE(MatrixH3f).UpdateParam_Scale(); return _Scale.z;}

   void SetScale_TAfterR(unsigned int idx, float Val);
   void SetScale_TBeforeR(unsigned int idx, float Val);
   void SetScale_TAfterR(const Vector3f &Scale);
   void SetScale_TAfterR(float Sx, float Sy, float Sz)
                           { SetScale_TAfterR(Vector3f(Sx,Sy,Sz)); }
   void SetScaleX_TAfterR(float Sx) 
                           { MatrixRT3f::SetScaleX_TAfterR(Sx); }
   void SetScaleY_TAfterR(float Sy)
                           { MatrixRT3f::SetScaleY_TAfterR(Sy); }
   void SetScaleZ_TAfterR(float Sz)
                           { MatrixRT3f::SetScaleZ_TAfterR(Sz); }

   void SetScale_TBeforeR(const Vector3f &Scale);
   void SetScale_TBeforeR(float Sx, float Sy, float Sz)
                           { SetScale_TBeforeR(Vector3f(Sx,Sy,Sz)); }
   void SetScaleX_TBeforeR(float Sx);
   void SetScaleY_TBeforeR(float Sy);
   void SetScaleZ_TBeforeR(float Sz);




   const Vector3f &GetTrans_TAfterR() const;

   const Vector3f &GetTrans_TBeforeR() const
      {
        USE(MatrixH3f).UpdateParam_Trans_TBeforeR();
        return _Trans;
      }





   void SetTrans_TBeforeR(float, float, float );

   /*!
    * Nadaje now± warto¶æ wektorowi translacji.
    * Zak³ada siê, ¿e translacja ma byæ wykonana przed skalowaniem i rotacj±,
    *  tzn.
    *  \f[
           F = R \circ S \circ T
       \f]
    * \param T - wektory nowych warto¶ci wspó³rzêdnych wektora translacji.
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
   void SetTrans_TBeforeR(Vector3f const &T)
                            { MatrixH3f::SetTrans_TBeforeR(T.x,T.y,T.z); }
   void SetTrans_TBeforeR(unsigned int idx, float T);
   void SetTransX_TBeforeR(float Tx);
   void SetTransY_TBeforeR(float Ty);
   void SetTransZ_TBeforeR(float Tz);


   void SetTrans_TAfterR(Vector3f const &);

    /*!
     * Nadaje now± warto¶æ wektorowi translacji.
     * Zak³ada siê, ¿e translacja ma byæ wykonana po skalowanii i rotacji,
     *  tzn.
     *  \f[
            F = T \circ R \circ S
        \f]
     * \param Tx - nowa warto¶æ \e x-owej wspó³rzêdnej wektora translacji.
     * \param Ty - nowa warto¶æ \e y-owej wspó³rzêdnej wektora translacji.
     * \param Tz - nowa warto¶æ \e z-owej wspó³rzêdnej wektora translacji.
     * \post Do pola \link MatrixH3f::_Trans _Trans\endlink zostaje wpisany
     *       nowy wektor translacji przekazany przez parametry
     *       \e Tx, \e Ty, \e Tz.
     *       Wpisane zostaj± równie¿ do 4 kolumny macierzy wspó³czynników
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
    void SetTrans_TAfterR(float Tx, float Ty, float Tz)
                                { SetTrans_TAfterR(Vector3f(Tx,Ty,Tz)); }

    void SetTrans_TAfterR(unsigned int idx, float T);

    void SetTransX_TAfterR(float Tx);
    void SetTransY_TAfterR(float Ty);
    void SetTransZ_TAfterR(float Tz);

    void AddTrans_TBeforeR(const Vector3f &dT);
    void AddTransX_TBeforeR(float Tx);
    void AddTransY_TBeforeR(float Ty);
    void AddTransZ_TBeforeR(float Tz);

    void AddTrans_TAfterR(const Vector3f &dT);
    void AddTransX_TAfterR(float Tx);
    void AddTransY_TAfterR(float Ty);
    void AddTransZ_TAfterR(float Tz);


   Vector3f TakeAng_Euler_Deg() const 
     {  Vector3f Ang, Scale;
        MatrixRT3f::GetEuler_Angles_Scale(Ang,Scale);
       return convert_rad2deg(Ang);
     }


   Vector3f TakeAng_XYZ_Deg() const 
     {  Vector3f Ang, Scale;
        MatrixRT3f::GetXYZ_Angles_Scale(Ang,Scale);
       return convert_rad2deg(Ang);
     }


     /*!
      * Sprowadza warto¶æ skali transformacji do (1,1,1) aktualizuj±c
      * odpowiednio wspó³czynniki macierzy transformacji.
      * \post Pole 
      *  \link MatrixH3f::_Valid_Scale  _Valid_Scale\endlink
      *  ma warto¶æ \p true.
      */
    MatrixH3f &Normalize();

    /*!
     *  Inicjalizuje dan± macierz jako macierz jednostkow±.
     */
    void SetUnitMtx();

   /*!
    * Operator mno¿enia macierzy (sk³adanie transformacji) przez macierz
    * i podstawienia.
    * Dezaktualizuj± wa¿no¶æ parametrów wszystkich znaczników
    * akutalno¶ci przechowywanych parametrów. Oznacza to, ¿e przy
    * próbie pobrania jakiego¶ parametru, np. wektora translacji,
    * bêdzie on musia³ byæ wcze¶niej wyliczony przed³u¿aj±c tym
    * samym dzia³anie metody.
    */
   MatrixH3f  &operator *= (MatrixH3f const &M)
        { SetParamInvalid();  MatrixRT3f::MultiplyByMatrix(M);  return *this; }


   /*!
    * Operator mno¿enia macierzy (sk³adanie transformacji) przez macierz.
    * Operacja nie wp³ywa na warto¶æ znaczników wa¿no¶ci
    * przechowywanych prametrów transformacji.
    */
   MatrixH3f   operator *  (MatrixH3f const &M) const 
                  { MatrixH3f Res(*this);  return Res *= M; }


   /*!
    * Operator mno¿enia macierzy przez wektor.
    * Operacja nie wp³ywa na wa¿no¶æ parametrów transformacji.
    * \param V - (\b in) wektor, który ma byæ przemno¿ony przez dan± maicerz.
    * \return wynikowy wektor po przemno¿eniu przez macierz.
    */
   Vector3f  operator *  (Vector3f const &V) const
                       { return *(const MatrixRT3f*)this * V; }

   /*!
    * Operator udostêpnia zadany elemement macierzy transformacji.
    * \param w - numer wiersza.
    * \param k - numer kolumny. 
    * \pre \f$ 0 \le w \le 2\f$, \f$ 0 \le k \le 3\f$.
    */
   float operator ()(unsigned int w, unsigned int k) const
                                  { return (*(const MatrixRT3f*)this)(w,k); }

  /*!
   * Metoda wyznacza macierz transformacji odwrotnej (rozumianej jako macierzy
   * przekszta³cenia jednorodnego) do danej macierzy.
   * \param FOut - (\b out) po wykonaniu operacji parametr zawiera 
   *              wspó³czynniki macierzy odwrotnej, o ile obliczenie
   *              takiej macierzy okaza³o siê byæ mo¿liwe.
   * \retval false - je¶li wyznacznie macierzy odwrotnej nie jest mo¿liwe (gdy
   *             przekszta³cenie osobliwe).
   *        \e FOut - obiekt nie ulega zmianie.
   *
   * \retval true  - gdy macierz przekszta³cenia odwrotnego
   *                 zosta³a wyznaczona.
   *        \e FOut - zawiera wynik obliczeñ, tzn. macierz przekszta³cenia 
   *                odwrotnego do danej macierzy.
   * \post W macierzy \e FOut przyjmuje siê, ¿e aktualne warto¶ci
   *       parametrów nie odpowiadaj± warto¶ciom rzeczywistym wynikaj±cym
   *       ze wspó³czynników macierzy. Pierwsza próba pobrania tych warto¶ci
   *       spowoduje ich uaktualnienie.
   */
   bool  InvertFrame(MatrixH3f &FOut) const {
          if (!MatrixRT3f::InvertMtx(FOut)) return false;
          FOut.SetParamInvalid(); 
          return true;
   }

   const Vector3f& GetAng_XYZ_Rad() const;
   Vector3f  GetAng_XYZ_Deg() const
               { return Vector3f(RAD2DEG(GetAng_XYZ_Rad().x),
                                 RAD2DEG(GetAng_XYZ_Rad().y),
                                 RAD2DEG(GetAng_XYZ_Rad().z)); }
  /*!
   *  Udostêpnia k±t rotacji \f$ \alpha\f$ (pierwszy obrót - 
   *  wokó³ osi \f$ OX\f$) wyra¿ony w stopniach.
   *  Warto¶æ k±ta jest udostêpniana dla reprezentacji
   *  k±tów rotacji \e XYZ.
   *
   *  Metoda aktualizuje jednocze¶nie warto¶ci pól
   *  \link MatrixH3f::_RotAng _RotAng\endlink oraz
   *  \link MatrixH3f::_Scale _Scale\endlink.
   */
   float GetAng_XYZoX_Deg() const
             { return RAD2DEG(MatrixH3f::GetAng_XYZ_Rad().x); }


  /*!
   *  Udostêpnia k±t rotacji \f$ \beta\f$ (drugi obrót - 
   *  wokó³ osi \f$ OY'\f$) wyra¿ony w stopniach.
   *  Warto¶æ k±ta jest udostêpniana dla reprezentacji
   *  k±tów rotacji \e XYZ.
   *
   *  Metoda aktualizuje jednocze¶nie warto¶ci pól
   *  \link MatrixH3f::_RotAng _RotAng\endlink oraz
   *  \link MatrixH3f::_Scale _Scale\endlink.
   */
   float GetAng_XYZoY_Deg() const
             { return RAD2DEG(MatrixH3f::GetAng_XYZ_Rad().y); }


  /*!
   *  Udostêpnia k±t rotacji \f$ \gamma\f$ (trzeci obrót - 
   *  wokó³ osi \f$ OZ''\f$) wyra¿ony w stopniach.
   *  Warto¶æ k±ta jest udostêpniana dla reprezentacji
   *  k±tów rotacji \e XYZ.
   *
   *  Metoda aktualizuje jednocze¶nie warto¶ci pól
   *  \link MatrixH3f::_RotAng _RotAng\endlink oraz
   *  \link MatrixH3f::_Scale _Scale\endlink.
   */
   float GetAng_XYZoZ_Deg() const
             { return RAD2DEG(MatrixH3f::GetAng_XYZ_Rad().z); }


    const Vector3f& GetAng_Euler_Rad() const;
    Vector3f GetAng_Euler_Deg() const
               { return Vector3f(RAD2DEG(GetAng_Euler_Rad().x),
                                 RAD2DEG(GetAng_Euler_Rad().y),
                                 RAD2DEG(GetAng_Euler_Rad().z)); }
   /*!
    * Udostêpnia k±t Eulera \f$\varphi\f$ 
    * (pierwszy obrót - wokó³ osi \f$ OZ\f$) dla danej macierzy
    * transformacji. Warto¶æ k±ta wyra¿ona jest w stopniach.
    */
    float GetAng_EulerVPhi_Deg() const 
              { return RAD2DEG(GetAng_Euler_Rad().x); }

   /*!
    * Udostêpnia k±t Eulera \f$\theta\f$ 
    * (drugi obrót - wokó³ osi \f$ OY'\f$) dla danej macierzy
    * transformacji. Warto¶æ k±ta wyra¿ona jest w stopniach.
    */
    float GetAng_EulerTheta_Deg() const 
              { return RAD2DEG(GetAng_Euler_Rad().y); }

   /*!
    * Udostêpnia k±t Eulera \f$\psi\f$ 
    * (trzeci obrót - wokó³ osi \f$ OZ''\f$) dla danej macierzy
    * transformacji. Warto¶æ k±ta wyra¿ona jest w stopniach.
    */
    float GetAng_EulerPsi_Deg() const 
              { return RAD2DEG(GetAng_Euler_Rad().z); }


  void SetAng_XYZ_TBeforeR_Rad(unsigned int AngID, float Value);
  void SetAng_XYZ_TBeforeR_Deg(unsigned int AngID, float Value);
  void SetAng_XYZ_TAfterR_Rad(unsigned int AngID, float Value);
  void SetAng_XYZ_TAfterR_Deg(unsigned int AngID, float Value);


  void SetAng_Euler_TBeforeR_Rad(unsigned int AngID, float Value);
  void SetAng_Euler_TBeforeR_Deg(unsigned int AngID, float Value);
  void SetAng_Euler_TAfterR_Rad(unsigned int AngID, float Value);
  void SetAng_Euler_TAfterR_Deg(unsigned int AngID, float Value);


  void SetAng_XYZ_TBeforeR_Rad(float Ax, float Ay, float Az);
  void SetAng_XYZ_TBeforeR_Rad(const Vector3f &Angles)
                  { SetAng_XYZ_TBeforeR_Rad(Angles.x, Angles.y, Angles.z); }
  void SetAng_XYZ_TBeforeR_Deg(float Ax, float Ay, float Az)
              { SetAng_XYZ_TBeforeR_Rad(DEG2RAD(Ax),DEG2RAD(Ay),DEG2RAD(Az));}

  void SetAng_XYZ_TAfterR_Rad(float Ax, float Ay, float Az);
  void SetAng_XYZ_TAfterR_Rad( const Vector3f &Angles )
                    { SetAng_XYZ_TAfterR_Rad(Angles.x,Angles.y,Angles.z); }
  void SetAng_XYZ_TAfterR_Deg(float Ax, float Ay, float Az)
     { SetAng_XYZ_TAfterR_Rad(DEG2RAD(Ax),DEG2RAD(Ay),DEG2RAD(Az)); }
  void SetAng_XYZ_TAfterR_Deg( const Vector3f &Angles )
                    { SetAng_XYZ_TAfterR_Deg(Angles.x,Angles.y,Angles.z); }

  void SetAng_XYZoX_TAfterR_Rad(float Ax);
  void SetAng_XYZoX_TAfterR_Deg(float Ax)
                            { SetAng_XYZoX_TAfterR_Rad(DEG2RAD(Ax)); }
  void SetAng_XYZoY_TAfterR_Rad(float Ay);
  void SetAng_XYZoY_TAfterR_Deg(float Ay)
                            { SetAng_XYZoY_TAfterR_Rad(DEG2RAD(Ay)); }
  void SetAng_XYZoZ_TAfterR_Rad(float Az);
  void SetAng_XYZoZ_TAfterR_Deg(float Az)
                            { SetAng_XYZoZ_TAfterR_Rad(DEG2RAD(Az)); }

  void SetAng_XYZoX_TBeforeR_Rad(float Ax);
  void SetAng_XYZoX_TBeforeR_Deg(float Ax)
                            { SetAng_XYZoX_TBeforeR_Rad(DEG2RAD(Ax)); }
  void SetAng_XYZoY_TBeforeR_Rad(float Ay);
  void SetAng_XYZoY_TBeforeR_Deg(float Ay)
                            { SetAng_XYZoY_TBeforeR_Rad(DEG2RAD(Ay)); }
  void SetAng_XYZoZ_TBeforeR_Rad(float Az);
  void SetAng_XYZoZ_TBeforeR_Deg(float Az)
                            { SetAng_XYZoZ_TBeforeR_Rad(DEG2RAD(Az)); }


  void SetAng_Euler_TBeforeR_Rad(float Ax, float Ay, float Az);
  void SetAng_Euler_TBeforeR_Rad(const Vector3f &Angles)
       { SetAng_Euler_TBeforeR_Rad(Angles.x,Angles.y,Angles.z); }
  void SetAng_Euler_TBeforeR_Deg(float VPhi, float Theta, float Psi)
       {SetAng_Euler_TBeforeR_Rad(DEG2RAD(VPhi),DEG2RAD(Theta),DEG2RAD(Psi));}


  void SetAng_EulerVPhi_TBeforeR_Rad(float VPhi);
  void SetAng_EulerVPhi_TBeforeR_Deg(float VPhi)
                         { SetAng_EulerVPhi_TBeforeR_Rad(DEG2RAD(VPhi)); }
  void SetAng_EulerTheta_TBeforeR_Rad(float Theta);
  void SetAng_EulerTheta_TBeforeR_Deg(float Theta)
                        { SetAng_EulerTheta_TBeforeR_Rad(DEG2RAD(Theta)); }
  void SetAng_EulerPsi_TBeforeR_Rad(float Psi);
  void SetAng_EulerPsi_TBeforeR_Deg(float Psi)
                        { SetAng_EulerPsi_TBeforeR_Rad(DEG2RAD(Psi)); }

  void SetAng_Euler_TAfterR_Rad(float VPhi, float Theta, float Psi);
  void SetAng_Euler_TAfterR_Rad(const Vector3f &Angles)
       { SetAng_Euler_TAfterR_Rad(Angles.x,Angles.y,Angles.z); }


  /*!
   *  Nadaje nowe warto¶ci k±tom Eulera danej transformacji.
   *  Metoda pozostawia niezmienione warto¶ci wektora translacji i
   *  skali. Zadanie k±tów powoduje jednocze¶nie odpowiednie przeliczenie
   *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
   *  w stopniach. Zak³ada siê, ¿e transformacja ma postaæ:
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
   void SetAng_Euler_TAfterR_Deg(float VPhi, float Theta, float Psi)
    {SetAng_Euler_TAfterR_Rad(DEG2RAD(VPhi),DEG2RAD(Theta),DEG2RAD(Psi));}


   void SetAng_EulerVPhi_TAfterR_Rad(float VPhi);


  /*!
   *  Nadaje now± warto¶æ k±ta Eulera \f$\varphi\f$ danej transformacji.
   *  Metoda pozostawia niezmienione warto¶ci wszystkich pozosta³ych
   *  parametrów transformacji.
   *  Zadanie k±ta powoduje jednocze¶nie odpowiednie przeliczenie
   *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
   *  w stopniach. Zak³ada siê, ¿e transformacja ma postaæ:
   * \f[
      F = T \circ R \circ S  
     \f]
   *  \param VPhi - (\b in) warto¶æ k±ta \f$\varphi\f$ 
   *                     (rotacja wokó³ osi \f$ OZ\f$) w stopniach.
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
   void SetAng_EulerVPhi_TAfterR_Deg(float VPhi)
                       { SetAng_EulerVPhi_TAfterR_Rad(DEG2RAD(VPhi)); }


   void SetAng_EulerTheta_TAfterR_Rad(float Theta);


  /*!
   *  Nadaje now± warto¶æ k±ta Eulera \f$\theta\f$ danej transformacji.
   *  Metoda pozostawia niezmienione warto¶ci wszystkich pozosta³ych
   *  parametrów transformacji.
   *  Zadanie k±ta powoduje jednocze¶nie odpowiednie przeliczenie
   *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
   *  w stopniach. Zak³ada siê, ¿e transformacja ma postaæ: 
   * \f[
      F = T \circ R \circ S  
     \f]
   *  \param Theta - (\b in) warto¶æ k±ta \f$\theta\f$ 
   *                     (rotacja wokó³ osi \f$ OZ\f$) w stopniach.
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
   void SetAng_EulerTheta_TAfterR_Deg(float Theta)
                       { SetAng_EulerTheta_TAfterR_Rad(DEG2RAD(Theta)); }


   void SetAng_EulerPsi_TAfterR_Rad(float Psi);


  /*!
   *  Nadaje now± warto¶æ k±ta Eulera \f$\psi\f$ danej transformacji.
   *  Metoda pozostawia niezmienione warto¶ci wszystkich pozosta³ych
   *  parametrów transformacji.
   *  Zadanie k±ta powoduje jednocze¶nie odpowiednie przeliczenie
   *  wspó³czynników macierzy transformacji. Warto¶ci k±tów wyra¿one s±
   *  w stopniach. Zak³ada siê, ¿e transformacja ma postaæ:
   * \f[
      F = T \circ R \circ S  
     \f]
   *  \param Psi - (\b in) warto¶æ k±ta \f$\psi\f$ 
   *                     (rotacja wokó³ osi \f$ OZ\f$) w stopniach.
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
   void SetAng_EulerPsi_TAfterR_Deg(float Psi)
                       { SetAng_EulerPsi_TAfterR_Rad(DEG2RAD(Psi)); }



  /*!
   *  Wyznacza podmacierz rotacji przy przyjmuj±c, ¿e rotacja jest
   *  okre¶lona za pomoc± k±tów Eulera
   *  (tzn. pierwszy
   *  obrót wzglêdem osi \f$ OZ\f$, drugi wzglêdem osi \f$ OY'\f$,
   *  trzeci wzglêdem osi \f$ OZ''\f$). Wspó³czynniki macierzy wyznaczane
   *  s± przy za³o¿eniu, ¿e skalowanie realizowane jest najpierw.
   *  Wspó³czynniki translacji nie s± modyfikowane.
   *
   *  \param Ang - (\b in) zawiera warto¶ci k±tów odpowiednio obrotu
   *             wzglêdem osi \f$ OZ\f$, \f$ OY'\f$, \f$ OZ''\f$.
   *             Warto¶ci k±tów wyra¿one s± w radianach.
   *  \param Scale - (\b in) wektor wspó³czynników skali wzglêdem
   *                  poszczególnych
   *                  osi odpowiednio  osi \f$ OX\f$, \f$ OY\f$, \f$ OZ\f$.
   */
  void SetRotMtx_Euler_Rad( const Vector3f &Ang, const Vector3f &Scale )
   {
     MatrixRT3f::SetRotMtx_Euler_Rad(_RotAng = Ang, _Scale = Scale);
     ValidParam_Scale_Euler_Angles();
   }


   void SetMatrix( const Vector3f &Col1_Rot, 
                   const Vector3f &Col2_Rot,
                   const Vector3f &Col3_Rot,
                   const Vector3f &Col4_Trans
                 );



  /*!
   *  Wyznacza macierz transformacji wykorzystuj±c reprezentacjê rotacji
   *  za pomoc± k±tów Eulera
   *  (tzn. pierwszy
   *  obrót wzglêdem osi \f$ OZ\f$, drugi wzglêdem osi \f$ OY'\f$,
   *  trzeci wzglêdem osi \f$ OZ''\f$). Macierz wyznaczana jest dla
   *  translacji wykonanej po skalowaniu i rotacji, tzn
   *  \f[
              F = T\circ R \circ S.
      \f]
   *  \param Ang - (\b in) zawiera warto¶ci k±tów odpowiednio obrotu
   *             wzglêdem osi \f$ OZ\f$, \f$ OY'\f$, \f$ OZ''\f$.
   *             Warto¶ci k±tów wyra¿one s± w radianach.
   *  \param Trans - (\b in) wektor translacji,
   *  \param Scale - (\b in) wektor wspó³czynników skali wzglêdem
   *                  poszczególnych
   *                  osi odpowiednio  osi \f$ OX\f$, \f$ OY\f$, \f$ OZ\f$.
   *  \post Zostaje wyznaczona macierz transformacji za¶ zostaj± zapamiêtane
   *        w odpowiednich polach.
   */
   void SetMatrix_Euler_TAfterR_Rad( const Vector3f &Ang, 
                                      const Vector3f &Trans=Vector3f(),
                                      const Vector3f &Scale=Vector3f(1,1,1)
                                    );



  /*!
   *  Wyznacza macierz transformacji wykorzystuj±c reprezentacjê rotacji
   *  za pomoc± k±tów Eulera
   *  (tzn. pierwszy
   *  obrót wzglêdem osi \f$ OZ\f$, drugi wzglêdem osi \f$ OY'\f$,
   *  trzeci wzglêdem osi \f$ OZ''\f$). Macierz wyznaczana jest dla
   *  translacji wykonanej przed skalowaniem i przed rotacj±, tzn
   *  \f[
              F = R \circ S \circ T.
      \f]
   *  \param Ang - (\b in) zawiera warto¶ci k±tów odpowiednio obrotu
   *             wzglêdem osi \f$ OZ\f$, \f$ OY'\f$, \f$ OZ''\f$.
   *             Warto¶ci k±tów wyra¿one s± w radianach.
   *  \param Trans - (\b in) wektor translacji,
   *  \param Scale - (\b in) wektor wspó³czynników skali wzglêdem
   *                  poszczególnych
   *                  osi odpowiednio  osi \f$ OX\f$, \f$ OY\f$, \f$ OZ\f$.
   *  \post Zostaje wyznaczona macierz transformacji za¶ zostaj± zapamiêtane
   *        w odpowiednich polach.
   */
   void SetMatrix_Euler_TBeforeR_Rad( const Vector3f &Ang, 
                                       const Vector3f &Trans=Vector3f(),
                                       const Vector3f &Scale=Vector3f(1,1,1)
                                     );


  /*!
   *  Wyznacza macierz transformacji w reprezentacji \e XYZ (tzn. pierwszy
   *  obrót wzglêdem osi \f$ OX\f$, drugi wzglêdem osi \f$ OY'\f$,
   *  trzeci wzglêdem osi \f$ OZ''\f$). Macierz wyznaczana jest dla
   *  translacji wykonanej po skalowaniu i rotacji, tzn
   *  \f[
              F = T\circ R \circ S.
      \f]
   *  \param Ang - (\b in) zawiera warto¶ci k±tów odpowiednio obrotu
   *             wzglêdem osi \f$ OX\f$, \f$ OY'\f$, \f$ OZ''\f$.
   *             Warto¶ci k±tów wyra¿one s± w radianach.
   *  \param Trans - (\b in) wektor translacji,
   *  \param Scale - (\b in) wektor wspó³czynników skali wzglêdem
   *                  poszczególnych
   *                  osi odpowiednio  osi \f$ OX\f$, \f$ OY\f$, \f$ OZ\f$.
   *  \post Zostaje wyznaczona macierz transformacji za¶ zostaj± zapamiêtane
   *        w odpowiednich polach.
   */
  void SetMatrix_XYZ_TAfterR_Rad( const Vector3f &Ang, 
                                   const Vector3f &Trans=Vector3f(),
                                   const Vector3f &Scale=Vector3f(1,1,1)
		                 );


  /*!
   *  Wyznacza macierz transformacji w reprezentacji \e XYZ (tzn. pierwszy
   *  obrót wzglêdem osi \f$ OX\f$, drugi wzglêdem osi \f$ OY'\f$,
   *  trzeci wzglêdem osi \f$ OZ''\f$). Macierz wyznaczana jest dla
   *  translacji wykonanej przed skalowaniem i rotacj±, tzn
   *  \f[
              F = R \circ S \circ T.
      \f]
   *  \param Ang - (\b in) zawiera warto¶ci k±tów odpowiednio obrotu
   *             wzglêdem osi \f$ OX\f$, \f$ OY'\f$, \f$ OZ''\f$.
   *             Warto¶ci k±tów wyra¿one s± w radianach.
   *  \param Trans - (\b in) wektor translacji,
   *  \param Scale - (\b in) wektor wspó³czynników skali wzglêdem
   *                  poszczególnych
   *                  osi odpowiednio  osi \f$ OX\f$, \f$ OY\f$, \f$ OZ\f$.
   *  \post Zostaje wyznaczona macierz transformacji za¶ zostaj± zapamiêtane
   *        w odpowiednich polach.
   */
  void SetMatrix_XYZ_TBeforeR_Rad( const Vector3f &Ang, 
                                    const Vector3f &Trans=Vector3f(),
                                    const Vector3f &Scale=Vector3f(1,1,1)
		                  );


  /*!
   * Metoda oblicza wyznacznik danej macierzy (traktowanej jako macierz) --
   * transformacji jednorodnej.
   */
  float     Det() const { return MatrixRT3f::Det(); }


  void AddAng_XYZ_TBeforeR_Rad( float d_Ax, float d_Ay, float d_Az );

  void AddAng_XYZ_TBeforeR_Deg( float d_Ax, float d_Ay, float d_Az )
       { AddAng_XYZ_TBeforeR_Rad(DEG2RAD(d_Ax),DEG2RAD(d_Ay),DEG2RAD(d_Az));}
  void AddAng_XYZ_TBeforeR_Rad( const Vector3f &d_Angles )
       { AddAng_XYZ_TBeforeR_Rad(d_Angles.x,d_Angles.y,d_Angles.z); }

  void AddAng_XYZ_TAfterR_Rad( float d_Ax, float d_Ay, float d_Az );

  /*!
   * Dodaje podane warto¶ci do aktalnych warto¶ci k±tów rotacji 
   * w reprezentacji \e XYZ i aktualizuje
   * macierz transformacji. Warto¶ci k±tów wyra¿one s± w stopniach.
   * Zak³ada siê, ¿e transformacja ma postaæ:
   * \f[
      F = T \circ R \circ S  
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
  void AddAng_XYZ_TAfterR_Rad( const Vector3f &d_Angles )
    {AddAng_XYZ_TAfterR_Rad(d_Angles.x,d_Angles.y,d_Angles.z);}

  /*!
   * Dodaje podane warto¶ci do aktalnych warto¶ci k±tów rotacji 
   * w reprezentacji \e XYZ i aktualizuje
   * macierz transformacji. Warto¶ci k±tów wyra¿one s± w stopniach.
   * Zak³ada siê, ¿e transformacja ma postaæ:
   * \f[
      F = T \circ R \circ S  
   \f]
   * \param d_Ax -(\b in)  warto¶æ o któr± ma byæ zwiêkszony k±t 
   *               \f$\alpha\f$ (obrót wokó³ osi \f$ OX\f$).
   * \param d_Ay - (\b in) warto¶æ o któr± ma byæ zwiêkszony k±t 
   *             \f$\beta\f$ (obrót wokó³ osi \f$ OY'\f$.
   * \param d_Az -(\b in)  warto¶æ o któr± ma byæ zwiêkszony k±t 
   *              \f$\gamma\f$ (obrót wokó³ osi \f$ OZ''\f$).
   * \post Do k±tów transformacji dodane zostaj± podane warto¶ci
   *       oraz zostaje zaaktualizowana macierz wspó³czynników transformacji.
   */
  void AddAng_XYZ_TAfterR_Deg( float d_Ax, float d_Ay, float d_Az )
    {AddAng_XYZ_TAfterR_Rad(DEG2RAD(d_Ax),DEG2RAD(d_Ay),DEG2RAD(d_Az));}


  void AddAng_Euler_TBeforeR_Rad( float d_VPhi, float d_Theta, float d_Psi );
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
  void AddAng_Euler_TBeforeR_Deg( float d_VPhi, float d_Theta, float d_Psi )
   {AddAng_Euler_TBeforeR_Rad(DEG2RAD(d_VPhi),DEG2RAD(d_Theta),DEG2RAD(d_Psi));}
  /*!
   * Dodaje do aktalnych warto¶ci k±tów Eulera podane warto¶ci i aktualizuje
   * macierz transformacji. Warto¶ci k±tów wyra¿one s± w radianach.
   * Zak³ada siê, ¿e transformacja ma postaæ:
   * \f[
      F = R \circ S \circ T
   \f]
   * \param d_Angles - (\b in)  wektor warto¶ci k±tów, które maj± byæ dodane
   *          odpowiednio do k±tów  \f$\varphi\f$ (obrót wokó³ osi \f$ OZ\f$),
   *          \f$\theta\f$ (obrót wokó³ osi \f$ OY'\f$),
   *          \f$\psi\f$ (obrót wokó³ osi \f$ OZ''\f$).
   * \post Do k±tów transformacji dodane zostaj± podane warto¶ci
   *       oraz zostaje zaaktualizowana macierz wspó³czynników transformacji.
   *       Zostaj± ustawione znaczniki wa¿no¶ci wszystkich pamiêtanych
   *       parametrów transformacji.
   */
  void AddAng_Euler_TBeforeR_Rad( const Vector3f &d_Angles )
             {AddAng_Euler_TBeforeR_Rad(d_Angles.x,d_Angles.y,d_Angles.z);}

  void AddAng_Euler_TAfterR_Rad( float d_VPhi, float d_Theta, float d_Psi );

  /*!
   * Dodaje do aktalnych warto¶ci k±tów Eulera podane warto¶ci i aktualizuje
   * macierz transformacji. Warto¶ci k±tów wyra¿one s± w stopniach.
   * Zak³ada siê, ¿e transformacja ma postaæ:
   * \f[
      F = T \circ R \circ S
     \f]
   * \param d_VPhi - (\b in) warto¶æ o któr± ma byæ zwiêkszony k±t \f$\varphi\f$.
   * \param d_Theta - (\b in) warto¶æ o któr± ma byæ zwiêkszony k±t \f$\theta\f$.
   * \param d_Psi -(\b in)  warto¶æ o któr± ma byæ zwiêkszony k±t \f$\psi\f$.
   * \post Do k±tów transformacji dodane zostaj± podane warto¶ci
   *       oraz zostaje zaaktualizowana macierz wspó³czynników transformacji.
   */
  void AddAng_Euler_TAfterR_Deg( float d_VPhi, float d_Theta, float d_Psi )
    { AddAng_Euler_TAfterR_Rad(DEG2RAD(d_VPhi),DEG2RAD(d_Theta),DEG2RAD(d_Psi));}


  /*!
   * Dodaje do aktalnych warto¶ci k±tów Eulera podane warto¶ci i aktualizuje
   * macierz transformacji. Warto¶ci k±tów wyra¿one s± w radianach.
   * \param Angles - (\b in)  wektor warto¶ci k±tów, które maj± byæ dodane
   *          odpowiednio do k±tów  \f$\varphi\f$ (obrót wokó³ osi \f$ OZ\f$),
   *          \f$\theta\f$ (obrót wokó³ osi \f$ OY'\f$),
   *          \f$\psi\f$ (obrót wokó³ osi \f$ OZ''\f$).
   * \post Do k±tów transformacji dodane zostaj± podane warto¶ci
   *       oraz zostaje zaaktualizowana macierz wspó³czynników transformacji.
   */
  void AddAng_Euler_TAfterR_Rad( const Vector3f &Angles )
       { AddAng_Euler_TAfterR_Rad(Angles.x,Angles.y,Angles.z); }

  /*!
   * Dodaje do aktalnych warto¶ci k±tów Eulera podane warto¶ci i aktualizuje
   * macierz transformacji. Warto¶ci k±tów wyra¿one s± w stopniach.
   * \param Angles - (\b in) wektor warto¶ci k±tów, które maj± byæ dodane
   *          odpowiednio do k±tów  \f$\varphi\f$ (obrót wokó³ osi \f$ OZ\f$),
   *          \f$\theta\f$ (obrót wokó³ osi \f$ OY'\f$),
   *          \f$\psi\f$ (obrót wokó³ osi \f$ OZ''\f$).
   * \post Do k±tów transformacji dodane zostaj± podane warto¶ci
   *       oraz zostaje zaaktualizowana macierz wspó³czynników transformacji.
   */
  void AddAng_Euler_TAfterR_Deg( const Vector3f &Angles )
       { AddAng_Euler_TAfterR_Deg(Angles.x,Angles.y,Angles.z); }


  /*!
   * Dodaje do aktalnych warto¶ci k±ta Eulera \f$varphi\f$ podane warto¶æ
   * i aktualizuje
   * macierz transformacji. Warto¶æ k±ta wyra¿ona jest w radianach.
   * \param d_VPhi - (\b in) warto¶æ o któr± ma byæ zwiêkszony k±t \f$\varphi\f$
   *                (obrót wokó³ osi \f$ OZ\f$).
   * \post Do k±tów transformacji dodane zostaj± podane warto¶ci
   *       oraz zostaje zaaktualizowana macierz wspó³czynników transformacji.
   */
  void AddAng_EulerVPhi_TAfterR_Rad( float d_VPhi )
                                { AddAng_Euler_TAfterR_Rad(d_VPhi,0,0); }


  /*!
   * Dodaje do aktalnych warto¶ci k±ta Eulera \f$theta\f$ podane warto¶æ
   * i aktualizuje
   * macierz transformacji. Warto¶æ k±ta wyra¿ona jest w radianach.
   * \param d_Theta - (\b in) warto¶æ o któr± ma byæ zwiêkszony k±t \f$\theta\f$
   *                (obrót wokó³ osi \f$ OZ\f$).
   * \post Do k±tów transformacji dodane zostaj± podane warto¶ci
   *       oraz zostaje zaaktualizowana macierz wspó³czynników transformacji.
   */
  void AddAng_EulerTheta_TAfterR_Rad( float d_Theta )
                                { AddAng_Euler_TAfterR_Rad(0,d_Theta,0); }


  /*!
   * Dodaje do aktalnych warto¶ci k±ta Eulera \f$psi\f$ podane warto¶æ
   * i aktualizuje
   * macierz transformacji. Warto¶æ k±ta wyra¿ona jest w radianach.
   * \param d_Psi - (\b in) warto¶æ o któr± ma byæ zwiêkszony k±t \f$\theta\f$
   *                (obrót wokó³ osi \f$ OZ''\f$).
   * \post Do k±tów transformacji dodane zostaj± podane warto¶ci
   *       oraz zostaje zaaktualizowana macierz wspó³czynników transformacji.
   */
  void AddAng_EulerPsi_TAfterR_Rad( float d_Psi )
                                { AddAng_Euler_TAfterR_Rad(0,0,d_Psi); }


  void AddScale_TBeforeR(float Sx, float Sy, float Sz);
  /*!
   *  Dodaje do wspó³czynników skali danej transformacji podane warto¶ci.
   * Zak³ada siê, ¿e translacja ma byæ wykonana przed skalowaniem i rotacj±,
   *  tzn.
   *  \f[
           F = R \circ S \circ T
     \f]
   *  \param Scale - (\b in) wektor wspó³czynników skali wzglêdem
   *                  poszczególnych
   *                  osi odpowiednio  osi \f$ OX\f$, \f$ OY\f$, \f$ OZ\f$.
   *  \post Zostaj± zaktualizowany parametr skali i obliczone nowe
   *        warto¶ci wspó³czynników macierzy transformacji przy za³o¿eniu,
   *        ¿e transformacja jest realizowana przed skalowaniem i rotacj±.
   */
  void AddScale_TBeforeR(const Vector3f &Scale )
            { AddScale_TBeforeR(Scale.x,Scale.y,Scale.z); }  

  void AddScale_TAfterR(float d_Sx, float d_Sy, float d_Sz);


  /*!
   *  Dodaje do wspó³czynników skali danej transformacji podane warto¶ci.
   *  \param d_Scale - (\b in) wektor warto¶ci wspó³czynników skali 
   *                 dla poszczególnych
   *                 osi, tzn. odpowiednio dla osi \e OX, \e OY, \e OZ.
   *  \post Zostaj± zaktualizowany parametr skali i obliczone nowe
   *        warto¶ci wspó³czynników macierzy transformacji przy za³o¿eniu,
   *        ¿e transformacja jest realizowana po rotacji.
   */
  void AddScale_TAfterR( const Vector3f &d_Scale )
                        { AddScale_TAfterR(d_Scale.x,d_Scale.y,d_Scale.z); }

  /*!
   *  Dodaje do wspó³czynnika skali \e OX danej transformacji podan± warto¶æ.
   *  \param d_Sx - (\b in) warto¶æ dodawana do \e x-owego wspó³czynnika skali.
   *  \post Zostaj± zaktualizowany parametr skali i obliczone nowe
   *        warto¶ci wspó³czynników macierzy transformacji przy za³o¿eniu,
   *        ¿e transformacja jest realizowana po rotacji.
   */
  void AddScaleX_TAfterR( float  d_Sx )
                        { AddScale_TAfterR(d_Sx,0,0); }

  /*!
   *  Dodaje do wspó³czynnika skali \e OY danej transformacji podan± warto¶æ.
   *  \param d_Sy - (\b in) warto¶æ dodawana do \e y-owego wspó³czynnika skali.
   *  \post Zostaj± zaktualizowany parametr skali i obliczone nowe
   *        warto¶ci wspó³czynników macierzy transformacji przy za³o¿eniu,
   *        ¿e transformacja jest realizowana po rotacji.
   */
  void AddScaleY_TAfterR( float  d_Sy )
                        { AddScale_TAfterR(0,d_Sy,0); }


  /*!
   *  Dodaje do wspó³czynnika skali \e OZ danej transformacji podan± warto¶æ.
   *  \param d_Sz - (\b in) warto¶æ dodawana do \e z-owego wspó³czynnika skali.
   *  \post Zostaj± zaktualizowany parametr skali i obliczone nowe
   *        warto¶ci wspó³czynników macierzy transformacji przy za³o¿eniu,
   *        ¿e transformacja jest realizowana po rotacji.
   */
  void AddScaleZ_TAfterR( float  d_Sz )
                        { AddScale_TAfterR(0,0,d_Sz); }



  //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    /*!
     * Inicjalizuje macierz transformacji jako przekszta³cenie to¿samo¶ciowe.
     * \post Zainicjalizowaniu macierzy towarzyszy zgodno¶æ parametrów
     *    zainicjalizowanych w polach 
     *    \link MatrixH3f::_RotAng _RotAng\endlink,
     *    \link MatrixH3f::_Trans _Trans\endlink oraz 
     *    \link MatrixH3f::_Scale _Scale\endlink. 
     *    Ponadto zostaj± ustawione znaczniki wa¿no¶ci warto¶ci poszczególnych
     *    parametrów.
     */ 
    MatrixH3f();

    /*=!
     * Inicjalizuje macierz transformacji na podstawie podanych paramterów 
     * transformacji.
     * \param Param - (\b in) zawiera parametry transformacji 
     *                (k±ty rotacji traktowane
     *                jako obroty wokó³ osi OX, OY, OZ, wektor translacji,
     *                wspó³czynniki skali).
     * \param ATyp - (\b in) okre¶la sposób interpretacji warto¶ci k±tów rotacji,
     *               które dostêpne s± w polu
     *               \link MatrixH3f::_RotAng _RotAng\endlink.
     * \post Zainicjalizowaniu macierzy towarzyszy zgodno¶æ parametrów
     *     zainicjalizowanych warto¶ciami udostêpnianymi przez parametr
     *     \e Param.
     *     Warto¶ci parametrów transformacji wpisywane s± w polach 
     *     \link MatrixH3f::_RotAng _RotAng\endlink,
     *     \link MatrixH3f::_Trans _Trans\endlink oraz 
     *     \link MatrixH3f::_Scale _Scale\endlink. Dlatego te¿ pole
     *     \link MatrixH3f::_Valid _Valid\endlink inicjalizowane jest 
     *     warto¶ci± \p true.
     */ 
  //   MatrixH3f(Parameters const &Param, AnglesType ATyp = AT_xyz);

   MatrixH3f      &operator <<= (Parameters const &PF);
       
   int WriteParamTo( ExtString    &Descr, 
                     AnglesType    AType      = AT_Euler,
                     AngleUnit     AUnit      = AU_Deg,
                     unsigned int  Margin     = 0
                   ) const;


   int Save( ostream      &ostrm, 
             unsigned int  LeftMargin = 0, 
             AnglesType    AType      = AT_Euler,
             AngleUnit     AUnit      = AU_Deg
           ) const;

};  //=============== MatrixH3f ==============================================




/*!
 * Umo¿liwia wy¶wietlenie na wyj¶ciu standardowym ca³ej warto¶ci
 * parametrów transformacji.
 */
std::ostream &operator << ( std::ostream &, MatrixH3f::Parameters const & );

/*!
 * Umo¿liwia wy¶wietlenie na wyj¶ciu standardowym napisu okre¶laj±cego
 * typ k±tów rotacji. Wy¶wietlany napis zgodny z nazw± warto¶ci
 * typu \link MatrixH3f::AnglesType MatrixH3f::AnglesType\endlink.
 */
std::ostream &operator << ( std::ostream &, MatrixH3f::AnglesType const & );


/*!
 * Umo¿liwia wy¶wietlenie na wyj¶ciu standardowym ca³ej macierzy
 * transformacji.
 */
std::ostream &operator << ( std::ostream &, MatrixH3f const & );


inline
void MatrixH3f::SetUnitMtx()
{
 _RotAng.SetZero();
 _Scale.Set(1,1,1);
 MatrixRT3f::SetUnitMtx();
 SetParamValid();
}

#endif
