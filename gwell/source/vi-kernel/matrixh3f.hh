#ifndef MATRIXH3F_HH
#define MATRIXH3F_HH

/*!
 * \file        matrixh3f.hh
 * Plik zawiera definicj� klasy MatrixH3f. Jest ona podstaw� wszystkich
 * transforacji mi�dzy poszczeg�lnymi uk�adami wsp�rz�dnych.
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
 * Numer b��du zg�aszanego w przypadku, gdy napis poddany konwersji
 * na typ \link matrixh3f::TransOrder
 *                    TransOrder\endlink nie odpowiada
 * �adnej z akceptowanych nazw.\n
 * Zg�aszanemu b��dowi odpowiada mu komunikat zdefinowany przez sta��
 *  \link vimatrixh3f.hh::ERRMSG_TRANSORDER__IMPROPER_NAME
 *                     ERRMSG_TRANSORDER__IMPROPER_NAME\endlink
 */
#define ERRNUM_TRANSORDER__IMPROPER_NAME  200
/*!
 * Komunikat b��du zg�aszanego w przypadku, gdy napis poddany konwersji
 * na typ \link matrixh3f.hh::TransformType 
 *                            TransformType\endlink nie odpowiada
 * �adnej z akceptowanych nazw.
 */
#define ERRMSG_TRANSORDER__IMPROPER_NAME  "Nazwa warto�ci typu"\
    " TransOrder nie odpowiada �adnej z oczekiwanych nazw."\
    " Otrzymano nazw� \"%s\", oczekuje si� jednej z nazw: %s"




/*!
 *  Umo�liwia kowersj� typu, np z const MatrixH3f na MatrixH3f.
 *  \param Type - nazwa typu.
 */
#define USE(Type)    (*(Type*)this)

 /*!
  *  Okre�la jednostk� w jakiej wyra�one s� k�ty. Jednostkami
  *  tymi dla poszczeg�lnych warto�ci mog� byc:
  *
  *    \li  AU_Deg   - stopnie,
  *    \li  AU_Rad   - radiany.
  */
typedef enum { AU_Deg, AU_Rad } AngleUnit;


 /*!
  *  Okre�la koleno�� realizacji translacji, tzn. przed dokonaniem
  *  rotacji lub po.
  *
  *    \li  TO_Before   - po rotacji,
  *    \li  TO_After    - przed rotacj�.
  */
typedef enum { TO_Before, TO_After } TransOrder;

namespace Vi {
  const char *MakeString(TransOrder Val);
  TransOrder String2TransOrder(const char *Name) throw(Ba::Exception);
}


class MatrixH3f: protected MatrixRT3f { //==================================
  public:

    /*!
     * Okre�la typ k�t�w w reprezentacji przekszta�cenia. W tej chwili
     * dost�pne
     * s� dwie reprezentacje: poprzez k�ty Eulera i k�ty obrotu wzgl�dem osi
     * OX,OY,OZ.
     *
     *    \li \p AT_xyz    - obr�t wzgl. osi X,Y,Z
     *    \li \p AT_Euler  - k�ty Eulera
     *
     */
   typedef enum { AT_xyz, AT_Euler } AnglesType;

    /*!
     * Decyduje o typie rotacji, czy ma ona zosta� dokonana wzgl�dem
     * lokalnego uk�adu wsp�rz�dnych, czy te� wzgl�dem uk�adu 
     * wsp�rz�dnych rodzica.
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
      *  Podstawia now� warto�� k�ta rotacji wzgl�dem osi OY.
      *  K�t wyra�ony musi by� w radianach.  Warto�ci pozosta�ych k�t�w
      *  nie ulegaj� zmianie.
      *  \param ang - nowa warto�� rotacji wzgl�dem osi OY. 
      */
     void SetAngY_Rad(float ang) { _RotAng.y = ang; }
     /*!
      *  Podstawia now� warto�� k�ta rotacji wzgl�dem osi OZ.
      *  K�t wyra�ony musi by� w radianach.  Warto�ci pozosta�ych k�t�w
      *  nie ulegaj� zmianie.
      *  \param ang - nowa warto�� rotacji wzgl�dem osi OZ. 
      */
     void SetAngZ_Rad(float ang) { _RotAng.z = ang; }
     /*!
      * Nadaje nowe warto�ci wektorowi wsp�czynnik�w skali
      * (patrz pole  \link MatrixH3f::Parameters::_Scale _Scale\endlink).
      * \param Sc - wektor nowych warto�ci wsp�czynnik�w skali.
      * \return referencj� do samego siebie (\b *this).
      * \post Do pola \link MatrixH3f::Parameters::_Scale _Scale\endlink
      *       zostaje podstawiony nowy wektor (\e Sc) warto�ci wsp�czynnik�w
      *       skali wzgl�dem poszczeg�lnych osi.
      */
     Parameters &SetScale(Vector3f const &Sc){ _Scale.Set(Sc); return *this; }
     /*!
      * Nadaje nowe warto�ci wektorowi translacji
      * (patrz pole  \link MatrixH3f::Parameters::_Trans _Trans\endlink).
      * \param Tr - nowy wektor translacji.
      * \return referencj� do samego siebie (\b *this).
      * \post Do pola \link MatrixH3f::Parameters::_Trans _Trans\endlink
      *       zostaje podstawiony nowy wektor translacji (\e Tr).
      */
     Parameters &SetTrans(Vector3f const &Tr) { _Trans.Set(Tr); return *this; }
     /*!
      * Nadaje nowe warto�ci wektorowi k�t�w rotacji 
      * (patrz pole  \link MatrixH3f::Parameters::_RotAng _RotAng\endlink).
      * \param Ro - wektor nowych k�t�w rotacji wyra�onych w radianach.
      * \return referencj� do samego siebie (\b *this).
      * \post Do pola \link MatrixH3f::Parameters::_RotAng _RotAng\endlink
      *       zostaje podstawiony nowy wektor (\e Ro) warto�ci k�t�w
      *       rotacji wzgl�dem poszczeg�lnych osi.
      */
     Parameters &SetAng(Vector3f const &Ro) { _RotAng.Set(Ro);  return *this; }

      /*!
       *  Nadaje nowe warto�ci wsp�czynnikom skali.
       *  \param sx - nowa warto�� wsp�czynnika skali wzgl�dem osi OX,
       *  \param sy - nowa warto�� wsp�czynnika skali wzgl�dem osi OY,
       *  \param sz - nowa warto�� wsp�czynnika skali wzgl�dem osi OZ.
       *  \post Nowe warto�ci wsp�czynnik�w skali zostaj� wpisane do
       *        pola \link MatrixH3f::Parameters::_Scale _Scale\endlink.
       */
     void SetScale(float sx, float sy, float sz) { _Scale.Set(sx,sy,sz); }

      /*!
       *  Nadaje nowe warto�ci wsp�czynnikom skali.
       *  \param x_S - nowa warto�� wsp�czynnika skali wzgl�dem osi OX,
       *  \post Nowa warto�� wsp�czynnika \e x-owej wsp�rz�dnej 
       *        wektora skali zostaje wpisane do
       *        pola \link MatrixH3f::Parameters::_Scale _Scale\endlink.
       */
     void SetScaleX(float x_S) { _Scale.x = x_S; }
      /*!
       *  Nadaje nowe warto�ci wsp�czynnikom skali.
       *  \param y_S - nowa warto�� wsp�czynnika skali wzgl�dem osi OY,
       *  \post Nowa warto�� wsp�czynnika \e y-owej wsp�rz�dnej 
       *        wektora skali zostaje wpisane do
       *        pola \link MatrixH3f::Parameters::_Scale _Scale\endlink.
       */
     void SetScaleY(float y_S) { _Scale.y = y_S; }
      /*!
       *  Nadaje nowe warto�ci wsp�czynnikom skali.
       *  \param z_S - nowa warto�� wsp�czynnika skali wzgl�dem osi OZ,
       *  \post Nowa warto�� wsp�czynnika \e z-owej wsp�rz�dnej 
       *        wektora skali zostaje wpisane do
       *        pola \link MatrixH3f::Parameters::_Scale _Scale\endlink.
       */
     void SetScaleZ(float z_S) { _Scale.z = z_S; }

      /*! 
       * Udost�pnia wektor wsp�czynnik�w skali dla poszczeg�lnuch osi.
       * Warto�ci te s� udost�pnione z pola 
       * \link MatrixH3f::Parameters::_Scale _Scale\endlink.
       *
       * Uwaga: Pobieranie wsp�czynnik�w skali nie zale�y od
       *        kolejno�ci wykonanej translacji.
       */
      Vector3f const &GetScale() const { return _Scale; }

      /*! 
       * Udost�pnia wektor translacji pocz�tku uk�adu wsp�rz�dnych.
       * Warto�ci te s� udost�pnione z pola 
       * \link MatrixH3f::Parameters::_Trans _Trans\endlink.
       */
     Vector3f const &GetTrans() const { return _Trans; }
      /*! 
       * Udost�pnia wektor k�t�w rotacji dla poszczeg�lnch osi.
       * Warto�ci te s� udost�pnione z pola 
       * \link MatrixH3f::Parameters::_RotAng _RotAng\endlink.
       */
     Vector3f const &GetAng_Rad() const { return _RotAng; }

      /*! 
       * Udost�pnia warto�� k�ta pierwszej rotacji. Warto�� k�ta
       * wyra�ona jest w stopniach.
       * Udost�pniona jest z pola 
       * \link MatrixH3f::Parameters::_RotAng _RotAng.x\endlink.
       */
     float GetAng1_Deg() const { return RAD2DEG(_RotAng.x); }
      /*! 
       * Udost�pnia warto�� k�ta drugiej rotacji. Warto�� k�ta
       * wyra�ona jest w stopniach.
       * Udost�pniona jest z pola 
       * \link MatrixH3f::Parameters::_RotAng _RotAng.y\endlink.
       */
     float GetAng2_Deg() const { return RAD2DEG(_RotAng.y); }
      /*! 
       * Udost�pnia warto�� k�ta trzeciej rotacji. Warto�� k�ta
       * wyra�ona jest w stopniach.
       * Udost�pniona jest z pola 
       * \link MatrixH3f::Parameters::_RotAng _RotAng.y\endlink.
       */
     float GetAng3_Deg() const { return RAD2DEG(_RotAng.z); }


     Parameters &operator <<= (MatrixH3f const &Mtx);


     int Save(FILE *f);
  

      /*!
       * Inicjalizuje parametry transformacji jako parametry przekszta�cenia 
       * to�samo�ciowego, tzn. k�ty rotacji oraz wektor translacji maj� zerowe
       * warto�ci, za� wsp�czynniki skali maj� warto�ci 1.
       */
     Parameters(){ _RotAng.Set_0(); _Trans.Set_0(); _Scale.Set_1(); };
   }; //_______________________ Parameters ___________________________________

  private:

    /*!
     *  Okre�la w jakich jednostkach wyra�ony s� k�ty rotacji.
     *  Pole to ma charakter roboczy i jest wykorzystywane w trakcie
     *  operacji pobierania warto�ci k�t�w.
     */
    mutable AngleUnit   _AngUnit;


    /*!
     *  Okre�la czy warto�ci k�t�w w polu  
     *  \link MatrixH3f::_RotAng _RotAng\endlink nale�y interpretowa� jako
     *  k�ty Eulera (warto�� \p AT_Euler) czy te� jako k�ty obrotu 
     *  wzgl�dem osi OX, OY i OZ (warto�� \p AT_xyz).
     */
    mutable AnglesType  _AngInterp;


     /*!
      * Zawiera k�ty rotacji. Iterpretacja tych k�t�w oke�lona jest
      * poprzez warto�� pola \link MatrixH3f::_AngInterp _AngInterp\endlink.
      * Faktyczne wsp�czynniki macierzy transformacji znajduj� si� w 
      * \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink.  O tym czy warto�ci
      * pola \link MatrixH3f::_Scale _Scale\endlink s�
      * adekwatne do wsp�czynnik�w w 
      * \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink informuje warto�� w polu
      * \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink. 
      *  Parametry przestaj� by� adekwatne je�eli podstawiany 
      * zostaje wynik mno�enia dw�ch macierzy. Metody pobieraj�ce konkretne
      * warto�ci wsp�czynnik�w wykrywaj� to i odpowiednio aktualizuj� 
      * warto�ci parametr�w.
      */
    Vector3f  _RotAng;

     /*!
      * Zawiera wektor translacji. Faktyczne 
      * wsp�czynniki macierzy transformacji znajduj� si� w 
      * \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink.  O tym czy warto�ci
      * pola \link MatrixH3f::_Scale _Scale\endlink s�
      * adekwatne do wsp�czynnik�w w 
      * \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink informuje warto�� w polu
      * \link MatrixH3f::_Valid_Trans _Valid_Trans\endlink. 
      *  Parametry przestaj� by� adekwatne je�eli podstawiany 
      * zostaje wynik mno�enia dw�ch macierzy. Metody pobieraj�ce konkretne
      * warto�ci wsp�czynnik�w wykrywaj� to i odpowiednio aktualizuj� 
      * warto�ci parametr�w.
      */
    Vector3f  _Trans; 

     /*!
      * Zawiera wsp�czynniki skali wzd�u� osi OX, OY, OZ. Faktyczne 
      * wsp�czynniki macierzy transformacji znajduj� si� w 
      * \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink.  O tym czy warto�ci
      * pola \link MatrixH3f::_Scale _Scale\endlink s�
      * adekwatne do wsp�czynnik�w w 
      * \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink informuje warto��
      * w polu \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink. 
      *  Parametry przestaj� by� adekwatne je�eli podstawiany 
      * zostaje wynik mno�enia dw�ch macierzy. Metody pobieraj�ce konkretne
      * warto�ci wsp�czynnik�w wykrywaj� to i odpowiednio aktualizuj� 
      * warto�ci parametr�w.
      */
    Vector3f  _Scale;


   /*! 
    * Warto�� pola okre�la czy parametry transformacji 
    * \link MatrixH3f::_Trans _Trans\endlink
    * odpowiada
    * faktycznej warto�ci wsp�czynnikom macierzy transformacji
    * w \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink.
    */
    mutable bool     _Valid_Trans;

   /*! 
    * Warto�� pola okre�la czy parametry transformacji 
    * \link MatrixH3f::_Trans _Trans\endlink
    * odpowiada translacji po rotacji (\p TO_After),
    * czy te� przed (\p TO_Before).
    */
    mutable TransOrder   _Trans_Order;

   /*! 
    * Warto�� pola okre�la czy parametry transformacji 
    * \link MatrixH3f::_Scale _Scale\endlink
    * odpowiada
    * faktycznej warto�ci wsp�czynnikom macierzy transformacji
    * w \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink.
    */
    mutable bool     _Valid_Scale;

   /*!
    * Warto�� pola okre�la czy parametry transformacji 
    * \link MatrixH3f::_RotAng _RotAng\endlink
    * odpowiada
    * faktycznej warto�ci wsp�czynnikom macierzy transformacji
    * w \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink.
    */
    mutable bool     _Valid_RotAng;


    /*!
     * Ustawia spos�b interpretacji k�t�w rotacji.
     * \param ATyp - nowa wartosc dla pola 
     * \link MatrixH3f::_AngInterp _AngInterp\endlink informuj�ca o sposobie
     *  interpretacji k�t�w rotacji.
     * \post Zostaje zmodyfikowna warto�� pola 
     * \link MatrixH3f::_AngInterp _AngInterp\endlink.
     */
    void SetAngInterp(AnglesType ATyp) { _AngInterp = ATyp; }



    /*!
     * Czyni niewa�nymi aktualne warto�ci pola 
     * \link MatrixH3f::_Trans _Trans\endlink. W ten spos�b pozosta�e
     * metody s� informowane, �e przed skorzystaniem z tego pola
     * nale�y zaktualizowa� jego warto�� na podstawie warto�ci
     * parametr�w macierzy transformacji.
     * \post Pole
     *  \link MatrixH3f::_Valid_Trans MatrixH3f::_Valid_Trans\endlink
     *  ma warto�� \p false.
     */
    void InvalidParam_Trans() { _Valid_Trans = false; }


    /*!
     * Czyni wa�nymi aktualne warto�ci pola 
     * \link MatrixH3f::_Trans _Trans\endlink. W ten spos�b pozosta�e
     * metody s� informowane, �e przed skorzystaniem z tego pola
     * nie jest potrzebna aktualizacja jego warto�ci.
     * Nieniejsza metoda operuje tylko na polach
     * \link MatrixH3f::_Valid_Trans _Valid_Trans\endlink
     * oraz
     *  \link MatrixH3f::_Trans_Order _Trans_Order\endlink.
     *
     * \post Pole
     *  \link MatrixH3f::_Valid_Trans _Valid_Trans\endlink
     *  ma warto�� \p true, za� 
     *  \link MatrixH3f::_Trans_Order _Trans_Order\endlink
     *  maj� warto�� \p TO_After.
     */
    void ValidParam_Trans_TAfterR() 
                      {_Trans_Order = TO_After; _Valid_Trans = true;}

    /*!
     * Czyni wa�nymi aktualne warto�ci pola 
     * \link MatrixH3f::_Trans _Trans\endlink. W ten spos�b pozosta�e
     * metody s� informowane, �e przed skorzystaniem z tego pola
     * nie jest potrzebna aktualizacja jego warto�ci.
     * Nieniejsza metoda operuje tylko na polach
     * \link MatrixH3f::_Valid_Trans _Valid_Trans\endlink
     * oraz
     *  \link MatrixH3f::_Trans_Order _Trans_Order\endlink.
     *
     * \post Pola
     *  \link MatrixH3f::_Valid_Trans _Valid_Trans\endlink
     *  ma warto�� \p true, za� 
     *  \link MatrixH3f::_Trans_Order _Trans_Order\endlink
     *  warto�� \p TO_Before.
     */
    void ValidParam_Trans_TBeforeR() 
                          {_Trans_Order = TO_Before; _Valid_Trans = true; }


    /*!
     * Czyni wa�nymi aktualne warto�ci pola 
     * \link MatrixH3f::_Scale _Scale\endlink. W ten spos�b pozosta�e
     * metody s� informowane, �e przed skorzystaniem z tego pola
     * nie jest potrzebna aktualizacja jego warto�ci.
     * Nieniejsza metoda operuje tylko na polu
     * \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink.
     * \post Pole
     *  \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink
     *  ma warto�� \p true.
     */
    void ValidParam_Scale() { _Valid_Scale = true; }

   /*!
    * Ustawia znaczniki wa�no�ci zawarto�ci pola
    * \link MatrixH3f::_RotAng _RotAng\endlink przyjmuj�c, �e
    * warto�ciomi k�t�w s� k�ty Eulera.
    * \post Polu
    * \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
    * przypisana zostaje warto�� \p true. Natomiast polu
    * \link MatrixH3f::_AngInterp _AngInterp\endlink warto��
    * \p AT_Euler.
    */
    void ValidParam_Euler_Angles() 
                        { _Valid_RotAng = true; SetAngInterp(AT_Euler); }

   /*!
    * Ustawia znaczniki wa�no�ci zawarto�ci pola
    * \link MatrixH3f::_RotAng _RotAng\endlink przyjmuj�c, �e
    * warto�ciomi k�t�w s� k�ty \e XYZ.
    * \post Polu
    * \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
    * przypisana zostaje warto�� \p true. Natomiast polu
    * \link MatrixH3f::_AngInterp _AngInterp\endlink warto��
    * \p AT_xyz.
    */
    void ValidParam_XYZ_Angles() 
                        { _Valid_RotAng = true; SetAngInterp(AT_xyz); }




   /*!
    * Ustawia znaczniki wa�no�ci zawarto�ci p�l
    * \link MatrixH3f::_Scale _Scale\endlink oraz
    * \link MatrixH3f::_RotAng _RotAng\endlink przyjmuj�c, �e
    * warto�ciomi k�t�w s� k�ty Eulera.
    * \post Polom \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink
    * oraz \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
    * przypisana zostaje warto�� \p true. Natomiast polu
    * \link MatrixH3f::_AngInterp _AngInterp\endlink warto��
    * \p AT_Euler.
    */
    void ValidParam_Scale_Euler_Angles() 
                        { ValidParam_Scale();  ValidParam_Euler_Angles(); }


   /*!
    * Ustawia znaczniki wa�no�ci zawarto�ci p�l
    * \link MatrixH3f::_Scale _Scale\endlink oraz
    * \link MatrixH3f::_RotAng _RotAng\endlink przyjmuj�c, �e
    * warto�ciomi k�t�w s� k�ty \e XYZ.
    * \post Polom \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink
    * oraz \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink
    * przypisana zostaje warto�� \p true. Natomiast polu
    * \link MatrixH3f::_AngInterp _AngInterp\endlink warto��
    * \p AT_xyz.
    */
    void ValidParam_Scale_XYZ_Angles() 
                        { ValidParam_Scale();  ValidParam_XYZ_Angles(); }



    /*!
     *  Aktualizuje warto�� pola \link MatrixH3f::_Scale _Scale\endlink, 
     *  w kt�rym zapisany jest
     *  wektor wsp�czynnik�w skali dla poszczeg�lnych osi. 
     *  Zapisywane warto�ci wyliczane s� na podstawie aktualnych parameter�w
     *  macierzy transformacji.
     * \post Pole 
     *   \link MatrixH3f::_Valid_Scale  _Valid_Scale\endlink
     *   ma warto�� \p true.
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
     *  Aktualizuje wektor k�t�w rotacji, traktuj�c je
     *  jako k�ty Eulera. Operacja wykonywana jest tylko wtedy
     *  gdy stwierdzone zostanie, �e warto�ci k�t�w nie s� aktualne
     *  w stosunku do warto�ci macierzy lub nie reprezentuj� one
     *  k�t�w Eulera.
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
    void UpdateParam_Euler_Angles_condScale();
    void UpdateParam_XYZ_Angles_condScale();
    void UpdateParam_Angles_condScale_Auto();



     /*!
      * Zmienia warto�� p�l 
      * \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink,
      * \link MatrixH3f::_Valid_Trans _Valid_Trans\endlink, oraz
      * \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink,
      * na \p true
      * sygnalizuj�c w ten spos�b, �e warto�ci parametr�w transformacji
      * zapisane w polach 
      * \link MatrixH3f::_RotAng _RotAng\endlink,
      * \link MatrixH3f::_Trans _Trans\endlink oraz
      * \link MatrixH3f::_Scale _Scale\endlink,
      * s� zgodne z
      * faktycznymi warto�ciami w 
      * \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink.
      */
    void   SetParamValid() 
            { _Valid_Trans = _Valid_Scale = _Valid_RotAng = true; }
     /*!
      * Informuj�c�, czy warto�ci parametr�w transformacji
      * zapisane w polach 
      * \link MatrixH3f::_RotAng _RotAng\endlink,
      * \link MatrixH3f::_Trans _Trans\endlink oraz
      * \link MatrixH3f::_Scale _Scale\endlink,
      * s� zgodne z
      * faktycznymi warto�ciami w 
      *         \link MatrixRT3f::_DH MatrixRT3f::_DH\endlink.
      */
    bool  AreParamValid() const 
        { return _Valid_Trans && _Valid_Scale && _Valid_RotAng; }

     /*!
      * Zmienia warto�� p�l 
      * \link MatrixH3f::_Valid_RotAng _Valid_RotAng\endlink,
      * \link MatrixH3f::_Valid_Trans _Valid_Trans\endlink, oraz
      * \link MatrixH3f::_Valid_Scale _Valid_Scale\endlink,
      * na \p false
      * sygnalizuj�c w ten spos�b, �e warto�ci parametr�w transformacji
      * zapisane w polach 
      * \link MatrixH3f::_RotAng _RotAng\endlink,
      * \link MatrixH3f::_Trans _Trans\endlink oraz
      * \link MatrixH3f::_Scale _Scale\endlink,
      * nie odpowiadaj�
      * faktycznymi warto�ciomi w 
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
    * Nadaje now� warto�� wektorowi translacji.
    * Zak�ada si�, �e translacja ma by� wykonana przed skalowaniem i rotacj�,
    *  tzn.
    *  \f[
           F = R \circ S \circ T
       \f]
    * \param T - wektory nowych warto�ci wsp�rz�dnych wektora translacji.
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
   void SetTrans_TBeforeR(Vector3f const &T)
                            { MatrixH3f::SetTrans_TBeforeR(T.x,T.y,T.z); }
   void SetTrans_TBeforeR(unsigned int idx, float T);
   void SetTransX_TBeforeR(float Tx);
   void SetTransY_TBeforeR(float Ty);
   void SetTransZ_TBeforeR(float Tz);


   void SetTrans_TAfterR(Vector3f const &);

    /*!
     * Nadaje now� warto�� wektorowi translacji.
     * Zak�ada si�, �e translacja ma by� wykonana po skalowanii i rotacji,
     *  tzn.
     *  \f[
            F = T \circ R \circ S
        \f]
     * \param Tx - nowa warto�� \e x-owej wsp�rz�dnej wektora translacji.
     * \param Ty - nowa warto�� \e y-owej wsp�rz�dnej wektora translacji.
     * \param Tz - nowa warto�� \e z-owej wsp�rz�dnej wektora translacji.
     * \post Do pola \link MatrixH3f::_Trans _Trans\endlink zostaje wpisany
     *       nowy wektor translacji przekazany przez parametry
     *       \e Tx, \e Ty, \e Tz.
     *       Wpisane zostaj� r�wnie� do 4 kolumny macierzy wsp�czynnik�w
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
      * Sprowadza warto�� skali transformacji do (1,1,1) aktualizuj�c
      * odpowiednio wsp�czynniki macierzy transformacji.
      * \post Pole 
      *  \link MatrixH3f::_Valid_Scale  _Valid_Scale\endlink
      *  ma warto�� \p true.
      */
    MatrixH3f &Normalize();

    /*!
     *  Inicjalizuje dan� macierz jako macierz jednostkow�.
     */
    void SetUnitMtx();

   /*!
    * Operator mno�enia macierzy (sk�adanie transformacji) przez macierz
    * i podstawienia.
    * Dezaktualizuj� wa�no�� parametr�w wszystkich znacznik�w
    * akutalno�ci przechowywanych parametr�w. Oznacza to, �e przy
    * pr�bie pobrania jakiego� parametru, np. wektora translacji,
    * b�dzie on musia� by� wcze�niej wyliczony przed�u�aj�c tym
    * samym dzia�anie metody.
    */
   MatrixH3f  &operator *= (MatrixH3f const &M)
        { SetParamInvalid();  MatrixRT3f::MultiplyByMatrix(M);  return *this; }


   /*!
    * Operator mno�enia macierzy (sk�adanie transformacji) przez macierz.
    * Operacja nie wp�ywa na warto�� znacznik�w wa�no�ci
    * przechowywanych prametr�w transformacji.
    */
   MatrixH3f   operator *  (MatrixH3f const &M) const 
                  { MatrixH3f Res(*this);  return Res *= M; }


   /*!
    * Operator mno�enia macierzy przez wektor.
    * Operacja nie wp�ywa na wa�no�� parametr�w transformacji.
    * \param V - (\b in) wektor, kt�ry ma by� przemno�ony przez dan� maicerz.
    * \return wynikowy wektor po przemno�eniu przez macierz.
    */
   Vector3f  operator *  (Vector3f const &V) const
                       { return *(const MatrixRT3f*)this * V; }

   /*!
    * Operator udost�pnia zadany elemement macierzy transformacji.
    * \param w - numer wiersza.
    * \param k - numer kolumny. 
    * \pre \f$ 0 \le w \le 2\f$, \f$ 0 \le k \le 3\f$.
    */
   float operator ()(unsigned int w, unsigned int k) const
                                  { return (*(const MatrixRT3f*)this)(w,k); }

  /*!
   * Metoda wyznacza macierz transformacji odwrotnej (rozumianej jako macierzy
   * przekszta�cenia jednorodnego) do danej macierzy.
   * \param FOut - (\b out) po wykonaniu operacji parametr zawiera 
   *              wsp�czynniki macierzy odwrotnej, o ile obliczenie
   *              takiej macierzy okaza�o si� by� mo�liwe.
   * \retval false - je�li wyznacznie macierzy odwrotnej nie jest mo�liwe (gdy
   *             przekszta�cenie osobliwe).
   *        \e FOut - obiekt nie ulega zmianie.
   *
   * \retval true  - gdy macierz przekszta�cenia odwrotnego
   *                 zosta�a wyznaczona.
   *        \e FOut - zawiera wynik oblicze�, tzn. macierz przekszta�cenia 
   *                odwrotnego do danej macierzy.
   * \post W macierzy \e FOut przyjmuje si�, �e aktualne warto�ci
   *       parametr�w nie odpowiadaj� warto�ciom rzeczywistym wynikaj�cym
   *       ze wsp�czynnik�w macierzy. Pierwsza pr�ba pobrania tych warto�ci
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
   *  Udost�pnia k�t rotacji \f$ \alpha\f$ (pierwszy obr�t - 
   *  wok� osi \f$ OX\f$) wyra�ony w stopniach.
   *  Warto�� k�ta jest udost�pniana dla reprezentacji
   *  k�t�w rotacji \e XYZ.
   *
   *  Metoda aktualizuje jednocze�nie warto�ci p�l
   *  \link MatrixH3f::_RotAng _RotAng\endlink oraz
   *  \link MatrixH3f::_Scale _Scale\endlink.
   */
   float GetAng_XYZoX_Deg() const
             { return RAD2DEG(MatrixH3f::GetAng_XYZ_Rad().x); }


  /*!
   *  Udost�pnia k�t rotacji \f$ \beta\f$ (drugi obr�t - 
   *  wok� osi \f$ OY'\f$) wyra�ony w stopniach.
   *  Warto�� k�ta jest udost�pniana dla reprezentacji
   *  k�t�w rotacji \e XYZ.
   *
   *  Metoda aktualizuje jednocze�nie warto�ci p�l
   *  \link MatrixH3f::_RotAng _RotAng\endlink oraz
   *  \link MatrixH3f::_Scale _Scale\endlink.
   */
   float GetAng_XYZoY_Deg() const
             { return RAD2DEG(MatrixH3f::GetAng_XYZ_Rad().y); }


  /*!
   *  Udost�pnia k�t rotacji \f$ \gamma\f$ (trzeci obr�t - 
   *  wok� osi \f$ OZ''\f$) wyra�ony w stopniach.
   *  Warto�� k�ta jest udost�pniana dla reprezentacji
   *  k�t�w rotacji \e XYZ.
   *
   *  Metoda aktualizuje jednocze�nie warto�ci p�l
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
    * Udost�pnia k�t Eulera \f$\varphi\f$ 
    * (pierwszy obr�t - wok� osi \f$ OZ\f$) dla danej macierzy
    * transformacji. Warto�� k�ta wyra�ona jest w stopniach.
    */
    float GetAng_EulerVPhi_Deg() const 
              { return RAD2DEG(GetAng_Euler_Rad().x); }

   /*!
    * Udost�pnia k�t Eulera \f$\theta\f$ 
    * (drugi obr�t - wok� osi \f$ OY'\f$) dla danej macierzy
    * transformacji. Warto�� k�ta wyra�ona jest w stopniach.
    */
    float GetAng_EulerTheta_Deg() const 
              { return RAD2DEG(GetAng_Euler_Rad().y); }

   /*!
    * Udost�pnia k�t Eulera \f$\psi\f$ 
    * (trzeci obr�t - wok� osi \f$ OZ''\f$) dla danej macierzy
    * transformacji. Warto�� k�ta wyra�ona jest w stopniach.
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
   *  Nadaje nowe warto�ci k�tom Eulera danej transformacji.
   *  Metoda pozostawia niezmienione warto�ci wektora translacji i
   *  skali. Zadanie k�t�w powoduje jednocze�nie odpowiednie przeliczenie
   *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
   *  w stopniach. Zak�ada si�, �e transformacja ma posta�:
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
   void SetAng_Euler_TAfterR_Deg(float VPhi, float Theta, float Psi)
    {SetAng_Euler_TAfterR_Rad(DEG2RAD(VPhi),DEG2RAD(Theta),DEG2RAD(Psi));}


   void SetAng_EulerVPhi_TAfterR_Rad(float VPhi);


  /*!
   *  Nadaje now� warto�� k�ta Eulera \f$\varphi\f$ danej transformacji.
   *  Metoda pozostawia niezmienione warto�ci wszystkich pozosta�ych
   *  parametr�w transformacji.
   *  Zadanie k�ta powoduje jednocze�nie odpowiednie przeliczenie
   *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
   *  w stopniach. Zak�ada si�, �e transformacja ma posta�:
   * \f[
      F = T \circ R \circ S  
     \f]
   *  \param VPhi - (\b in) warto�� k�ta \f$\varphi\f$ 
   *                     (rotacja wok� osi \f$ OZ\f$) w stopniach.
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
   void SetAng_EulerVPhi_TAfterR_Deg(float VPhi)
                       { SetAng_EulerVPhi_TAfterR_Rad(DEG2RAD(VPhi)); }


   void SetAng_EulerTheta_TAfterR_Rad(float Theta);


  /*!
   *  Nadaje now� warto�� k�ta Eulera \f$\theta\f$ danej transformacji.
   *  Metoda pozostawia niezmienione warto�ci wszystkich pozosta�ych
   *  parametr�w transformacji.
   *  Zadanie k�ta powoduje jednocze�nie odpowiednie przeliczenie
   *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
   *  w stopniach. Zak�ada si�, �e transformacja ma posta�: 
   * \f[
      F = T \circ R \circ S  
     \f]
   *  \param Theta - (\b in) warto�� k�ta \f$\theta\f$ 
   *                     (rotacja wok� osi \f$ OZ\f$) w stopniach.
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
   void SetAng_EulerTheta_TAfterR_Deg(float Theta)
                       { SetAng_EulerTheta_TAfterR_Rad(DEG2RAD(Theta)); }


   void SetAng_EulerPsi_TAfterR_Rad(float Psi);


  /*!
   *  Nadaje now� warto�� k�ta Eulera \f$\psi\f$ danej transformacji.
   *  Metoda pozostawia niezmienione warto�ci wszystkich pozosta�ych
   *  parametr�w transformacji.
   *  Zadanie k�ta powoduje jednocze�nie odpowiednie przeliczenie
   *  wsp�czynnik�w macierzy transformacji. Warto�ci k�t�w wyra�one s�
   *  w stopniach. Zak�ada si�, �e transformacja ma posta�:
   * \f[
      F = T \circ R \circ S  
     \f]
   *  \param Psi - (\b in) warto�� k�ta \f$\psi\f$ 
   *                     (rotacja wok� osi \f$ OZ\f$) w stopniach.
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
   void SetAng_EulerPsi_TAfterR_Deg(float Psi)
                       { SetAng_EulerPsi_TAfterR_Rad(DEG2RAD(Psi)); }



  /*!
   *  Wyznacza podmacierz rotacji przy przyjmuj�c, �e rotacja jest
   *  okre�lona za pomoc� k�t�w Eulera
   *  (tzn. pierwszy
   *  obr�t wzgl�dem osi \f$ OZ\f$, drugi wzgl�dem osi \f$ OY'\f$,
   *  trzeci wzgl�dem osi \f$ OZ''\f$). Wsp�czynniki macierzy wyznaczane
   *  s� przy za�o�eniu, �e skalowanie realizowane jest najpierw.
   *  Wsp�czynniki translacji nie s� modyfikowane.
   *
   *  \param Ang - (\b in) zawiera warto�ci k�t�w odpowiednio obrotu
   *             wzgl�dem osi \f$ OZ\f$, \f$ OY'\f$, \f$ OZ''\f$.
   *             Warto�ci k�t�w wyra�one s� w radianach.
   *  \param Scale - (\b in) wektor wsp�czynnik�w skali wzgl�dem
   *                  poszczeg�lnych
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
   *  Wyznacza macierz transformacji wykorzystuj�c reprezentacj� rotacji
   *  za pomoc� k�t�w Eulera
   *  (tzn. pierwszy
   *  obr�t wzgl�dem osi \f$ OZ\f$, drugi wzgl�dem osi \f$ OY'\f$,
   *  trzeci wzgl�dem osi \f$ OZ''\f$). Macierz wyznaczana jest dla
   *  translacji wykonanej po skalowaniu i rotacji, tzn
   *  \f[
              F = T\circ R \circ S.
      \f]
   *  \param Ang - (\b in) zawiera warto�ci k�t�w odpowiednio obrotu
   *             wzgl�dem osi \f$ OZ\f$, \f$ OY'\f$, \f$ OZ''\f$.
   *             Warto�ci k�t�w wyra�one s� w radianach.
   *  \param Trans - (\b in) wektor translacji,
   *  \param Scale - (\b in) wektor wsp�czynnik�w skali wzgl�dem
   *                  poszczeg�lnych
   *                  osi odpowiednio  osi \f$ OX\f$, \f$ OY\f$, \f$ OZ\f$.
   *  \post Zostaje wyznaczona macierz transformacji za� zostaj� zapami�tane
   *        w odpowiednich polach.
   */
   void SetMatrix_Euler_TAfterR_Rad( const Vector3f &Ang, 
                                      const Vector3f &Trans=Vector3f(),
                                      const Vector3f &Scale=Vector3f(1,1,1)
                                    );



  /*!
   *  Wyznacza macierz transformacji wykorzystuj�c reprezentacj� rotacji
   *  za pomoc� k�t�w Eulera
   *  (tzn. pierwszy
   *  obr�t wzgl�dem osi \f$ OZ\f$, drugi wzgl�dem osi \f$ OY'\f$,
   *  trzeci wzgl�dem osi \f$ OZ''\f$). Macierz wyznaczana jest dla
   *  translacji wykonanej przed skalowaniem i przed rotacj�, tzn
   *  \f[
              F = R \circ S \circ T.
      \f]
   *  \param Ang - (\b in) zawiera warto�ci k�t�w odpowiednio obrotu
   *             wzgl�dem osi \f$ OZ\f$, \f$ OY'\f$, \f$ OZ''\f$.
   *             Warto�ci k�t�w wyra�one s� w radianach.
   *  \param Trans - (\b in) wektor translacji,
   *  \param Scale - (\b in) wektor wsp�czynnik�w skali wzgl�dem
   *                  poszczeg�lnych
   *                  osi odpowiednio  osi \f$ OX\f$, \f$ OY\f$, \f$ OZ\f$.
   *  \post Zostaje wyznaczona macierz transformacji za� zostaj� zapami�tane
   *        w odpowiednich polach.
   */
   void SetMatrix_Euler_TBeforeR_Rad( const Vector3f &Ang, 
                                       const Vector3f &Trans=Vector3f(),
                                       const Vector3f &Scale=Vector3f(1,1,1)
                                     );


  /*!
   *  Wyznacza macierz transformacji w reprezentacji \e XYZ (tzn. pierwszy
   *  obr�t wzgl�dem osi \f$ OX\f$, drugi wzgl�dem osi \f$ OY'\f$,
   *  trzeci wzgl�dem osi \f$ OZ''\f$). Macierz wyznaczana jest dla
   *  translacji wykonanej po skalowaniu i rotacji, tzn
   *  \f[
              F = T\circ R \circ S.
      \f]
   *  \param Ang - (\b in) zawiera warto�ci k�t�w odpowiednio obrotu
   *             wzgl�dem osi \f$ OX\f$, \f$ OY'\f$, \f$ OZ''\f$.
   *             Warto�ci k�t�w wyra�one s� w radianach.
   *  \param Trans - (\b in) wektor translacji,
   *  \param Scale - (\b in) wektor wsp�czynnik�w skali wzgl�dem
   *                  poszczeg�lnych
   *                  osi odpowiednio  osi \f$ OX\f$, \f$ OY\f$, \f$ OZ\f$.
   *  \post Zostaje wyznaczona macierz transformacji za� zostaj� zapami�tane
   *        w odpowiednich polach.
   */
  void SetMatrix_XYZ_TAfterR_Rad( const Vector3f &Ang, 
                                   const Vector3f &Trans=Vector3f(),
                                   const Vector3f &Scale=Vector3f(1,1,1)
		                 );


  /*!
   *  Wyznacza macierz transformacji w reprezentacji \e XYZ (tzn. pierwszy
   *  obr�t wzgl�dem osi \f$ OX\f$, drugi wzgl�dem osi \f$ OY'\f$,
   *  trzeci wzgl�dem osi \f$ OZ''\f$). Macierz wyznaczana jest dla
   *  translacji wykonanej przed skalowaniem i rotacj�, tzn
   *  \f[
              F = R \circ S \circ T.
      \f]
   *  \param Ang - (\b in) zawiera warto�ci k�t�w odpowiednio obrotu
   *             wzgl�dem osi \f$ OX\f$, \f$ OY'\f$, \f$ OZ''\f$.
   *             Warto�ci k�t�w wyra�one s� w radianach.
   *  \param Trans - (\b in) wektor translacji,
   *  \param Scale - (\b in) wektor wsp�czynnik�w skali wzgl�dem
   *                  poszczeg�lnych
   *                  osi odpowiednio  osi \f$ OX\f$, \f$ OY\f$, \f$ OZ\f$.
   *  \post Zostaje wyznaczona macierz transformacji za� zostaj� zapami�tane
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
   * Dodaje podane warto�ci do aktalnych warto�ci k�t�w rotacji 
   * w reprezentacji \e XYZ i aktualizuje
   * macierz transformacji. Warto�ci k�t�w wyra�one s� w stopniach.
   * Zak�ada si�, �e transformacja ma posta�:
   * \f[
      F = T \circ R \circ S  
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
  void AddAng_XYZ_TAfterR_Rad( const Vector3f &d_Angles )
    {AddAng_XYZ_TAfterR_Rad(d_Angles.x,d_Angles.y,d_Angles.z);}

  /*!
   * Dodaje podane warto�ci do aktalnych warto�ci k�t�w rotacji 
   * w reprezentacji \e XYZ i aktualizuje
   * macierz transformacji. Warto�ci k�t�w wyra�one s� w stopniach.
   * Zak�ada si�, �e transformacja ma posta�:
   * \f[
      F = T \circ R \circ S  
   \f]
   * \param d_Ax -(\b in)  warto�� o kt�r� ma by� zwi�kszony k�t 
   *               \f$\alpha\f$ (obr�t wok� osi \f$ OX\f$).
   * \param d_Ay - (\b in) warto�� o kt�r� ma by� zwi�kszony k�t 
   *             \f$\beta\f$ (obr�t wok� osi \f$ OY'\f$.
   * \param d_Az -(\b in)  warto�� o kt�r� ma by� zwi�kszony k�t 
   *              \f$\gamma\f$ (obr�t wok� osi \f$ OZ''\f$).
   * \post Do k�t�w transformacji dodane zostaj� podane warto�ci
   *       oraz zostaje zaaktualizowana macierz wsp�czynnik�w transformacji.
   */
  void AddAng_XYZ_TAfterR_Deg( float d_Ax, float d_Ay, float d_Az )
    {AddAng_XYZ_TAfterR_Rad(DEG2RAD(d_Ax),DEG2RAD(d_Ay),DEG2RAD(d_Az));}


  void AddAng_Euler_TBeforeR_Rad( float d_VPhi, float d_Theta, float d_Psi );
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
  void AddAng_Euler_TBeforeR_Deg( float d_VPhi, float d_Theta, float d_Psi )
   {AddAng_Euler_TBeforeR_Rad(DEG2RAD(d_VPhi),DEG2RAD(d_Theta),DEG2RAD(d_Psi));}
  /*!
   * Dodaje do aktalnych warto�ci k�t�w Eulera podane warto�ci i aktualizuje
   * macierz transformacji. Warto�ci k�t�w wyra�one s� w radianach.
   * Zak�ada si�, �e transformacja ma posta�:
   * \f[
      F = R \circ S \circ T
   \f]
   * \param d_Angles - (\b in)  wektor warto�ci k�t�w, kt�re maj� by� dodane
   *          odpowiednio do k�t�w  \f$\varphi\f$ (obr�t wok� osi \f$ OZ\f$),
   *          \f$\theta\f$ (obr�t wok� osi \f$ OY'\f$),
   *          \f$\psi\f$ (obr�t wok� osi \f$ OZ''\f$).
   * \post Do k�t�w transformacji dodane zostaj� podane warto�ci
   *       oraz zostaje zaaktualizowana macierz wsp�czynnik�w transformacji.
   *       Zostaj� ustawione znaczniki wa�no�ci wszystkich pami�tanych
   *       parametr�w transformacji.
   */
  void AddAng_Euler_TBeforeR_Rad( const Vector3f &d_Angles )
             {AddAng_Euler_TBeforeR_Rad(d_Angles.x,d_Angles.y,d_Angles.z);}

  void AddAng_Euler_TAfterR_Rad( float d_VPhi, float d_Theta, float d_Psi );

  /*!
   * Dodaje do aktalnych warto�ci k�t�w Eulera podane warto�ci i aktualizuje
   * macierz transformacji. Warto�ci k�t�w wyra�one s� w stopniach.
   * Zak�ada si�, �e transformacja ma posta�:
   * \f[
      F = T \circ R \circ S
     \f]
   * \param d_VPhi - (\b in) warto�� o kt�r� ma by� zwi�kszony k�t \f$\varphi\f$.
   * \param d_Theta - (\b in) warto�� o kt�r� ma by� zwi�kszony k�t \f$\theta\f$.
   * \param d_Psi -(\b in)  warto�� o kt�r� ma by� zwi�kszony k�t \f$\psi\f$.
   * \post Do k�t�w transformacji dodane zostaj� podane warto�ci
   *       oraz zostaje zaaktualizowana macierz wsp�czynnik�w transformacji.
   */
  void AddAng_Euler_TAfterR_Deg( float d_VPhi, float d_Theta, float d_Psi )
    { AddAng_Euler_TAfterR_Rad(DEG2RAD(d_VPhi),DEG2RAD(d_Theta),DEG2RAD(d_Psi));}


  /*!
   * Dodaje do aktalnych warto�ci k�t�w Eulera podane warto�ci i aktualizuje
   * macierz transformacji. Warto�ci k�t�w wyra�one s� w radianach.
   * \param Angles - (\b in)  wektor warto�ci k�t�w, kt�re maj� by� dodane
   *          odpowiednio do k�t�w  \f$\varphi\f$ (obr�t wok� osi \f$ OZ\f$),
   *          \f$\theta\f$ (obr�t wok� osi \f$ OY'\f$),
   *          \f$\psi\f$ (obr�t wok� osi \f$ OZ''\f$).
   * \post Do k�t�w transformacji dodane zostaj� podane warto�ci
   *       oraz zostaje zaaktualizowana macierz wsp�czynnik�w transformacji.
   */
  void AddAng_Euler_TAfterR_Rad( const Vector3f &Angles )
       { AddAng_Euler_TAfterR_Rad(Angles.x,Angles.y,Angles.z); }

  /*!
   * Dodaje do aktalnych warto�ci k�t�w Eulera podane warto�ci i aktualizuje
   * macierz transformacji. Warto�ci k�t�w wyra�one s� w stopniach.
   * \param Angles - (\b in) wektor warto�ci k�t�w, kt�re maj� by� dodane
   *          odpowiednio do k�t�w  \f$\varphi\f$ (obr�t wok� osi \f$ OZ\f$),
   *          \f$\theta\f$ (obr�t wok� osi \f$ OY'\f$),
   *          \f$\psi\f$ (obr�t wok� osi \f$ OZ''\f$).
   * \post Do k�t�w transformacji dodane zostaj� podane warto�ci
   *       oraz zostaje zaaktualizowana macierz wsp�czynnik�w transformacji.
   */
  void AddAng_Euler_TAfterR_Deg( const Vector3f &Angles )
       { AddAng_Euler_TAfterR_Deg(Angles.x,Angles.y,Angles.z); }


  /*!
   * Dodaje do aktalnych warto�ci k�ta Eulera \f$varphi\f$ podane warto��
   * i aktualizuje
   * macierz transformacji. Warto�� k�ta wyra�ona jest w radianach.
   * \param d_VPhi - (\b in) warto�� o kt�r� ma by� zwi�kszony k�t \f$\varphi\f$
   *                (obr�t wok� osi \f$ OZ\f$).
   * \post Do k�t�w transformacji dodane zostaj� podane warto�ci
   *       oraz zostaje zaaktualizowana macierz wsp�czynnik�w transformacji.
   */
  void AddAng_EulerVPhi_TAfterR_Rad( float d_VPhi )
                                { AddAng_Euler_TAfterR_Rad(d_VPhi,0,0); }


  /*!
   * Dodaje do aktalnych warto�ci k�ta Eulera \f$theta\f$ podane warto��
   * i aktualizuje
   * macierz transformacji. Warto�� k�ta wyra�ona jest w radianach.
   * \param d_Theta - (\b in) warto�� o kt�r� ma by� zwi�kszony k�t \f$\theta\f$
   *                (obr�t wok� osi \f$ OZ\f$).
   * \post Do k�t�w transformacji dodane zostaj� podane warto�ci
   *       oraz zostaje zaaktualizowana macierz wsp�czynnik�w transformacji.
   */
  void AddAng_EulerTheta_TAfterR_Rad( float d_Theta )
                                { AddAng_Euler_TAfterR_Rad(0,d_Theta,0); }


  /*!
   * Dodaje do aktalnych warto�ci k�ta Eulera \f$psi\f$ podane warto��
   * i aktualizuje
   * macierz transformacji. Warto�� k�ta wyra�ona jest w radianach.
   * \param d_Psi - (\b in) warto�� o kt�r� ma by� zwi�kszony k�t \f$\theta\f$
   *                (obr�t wok� osi \f$ OZ''\f$).
   * \post Do k�t�w transformacji dodane zostaj� podane warto�ci
   *       oraz zostaje zaaktualizowana macierz wsp�czynnik�w transformacji.
   */
  void AddAng_EulerPsi_TAfterR_Rad( float d_Psi )
                                { AddAng_Euler_TAfterR_Rad(0,0,d_Psi); }


  void AddScale_TBeforeR(float Sx, float Sy, float Sz);
  /*!
   *  Dodaje do wsp�czynnik�w skali danej transformacji podane warto�ci.
   * Zak�ada si�, �e translacja ma by� wykonana przed skalowaniem i rotacj�,
   *  tzn.
   *  \f[
           F = R \circ S \circ T
     \f]
   *  \param Scale - (\b in) wektor wsp�czynnik�w skali wzgl�dem
   *                  poszczeg�lnych
   *                  osi odpowiednio  osi \f$ OX\f$, \f$ OY\f$, \f$ OZ\f$.
   *  \post Zostaj� zaktualizowany parametr skali i obliczone nowe
   *        warto�ci wsp�czynnik�w macierzy transformacji przy za�o�eniu,
   *        �e transformacja jest realizowana przed skalowaniem i rotacj�.
   */
  void AddScale_TBeforeR(const Vector3f &Scale )
            { AddScale_TBeforeR(Scale.x,Scale.y,Scale.z); }  

  void AddScale_TAfterR(float d_Sx, float d_Sy, float d_Sz);


  /*!
   *  Dodaje do wsp�czynnik�w skali danej transformacji podane warto�ci.
   *  \param d_Scale - (\b in) wektor warto�ci wsp�czynnik�w skali 
   *                 dla poszczeg�lnych
   *                 osi, tzn. odpowiednio dla osi \e OX, \e OY, \e OZ.
   *  \post Zostaj� zaktualizowany parametr skali i obliczone nowe
   *        warto�ci wsp�czynnik�w macierzy transformacji przy za�o�eniu,
   *        �e transformacja jest realizowana po rotacji.
   */
  void AddScale_TAfterR( const Vector3f &d_Scale )
                        { AddScale_TAfterR(d_Scale.x,d_Scale.y,d_Scale.z); }

  /*!
   *  Dodaje do wsp�czynnika skali \e OX danej transformacji podan� warto��.
   *  \param d_Sx - (\b in) warto�� dodawana do \e x-owego wsp�czynnika skali.
   *  \post Zostaj� zaktualizowany parametr skali i obliczone nowe
   *        warto�ci wsp�czynnik�w macierzy transformacji przy za�o�eniu,
   *        �e transformacja jest realizowana po rotacji.
   */
  void AddScaleX_TAfterR( float  d_Sx )
                        { AddScale_TAfterR(d_Sx,0,0); }

  /*!
   *  Dodaje do wsp�czynnika skali \e OY danej transformacji podan� warto��.
   *  \param d_Sy - (\b in) warto�� dodawana do \e y-owego wsp�czynnika skali.
   *  \post Zostaj� zaktualizowany parametr skali i obliczone nowe
   *        warto�ci wsp�czynnik�w macierzy transformacji przy za�o�eniu,
   *        �e transformacja jest realizowana po rotacji.
   */
  void AddScaleY_TAfterR( float  d_Sy )
                        { AddScale_TAfterR(0,d_Sy,0); }


  /*!
   *  Dodaje do wsp�czynnika skali \e OZ danej transformacji podan� warto��.
   *  \param d_Sz - (\b in) warto�� dodawana do \e z-owego wsp�czynnika skali.
   *  \post Zostaj� zaktualizowany parametr skali i obliczone nowe
   *        warto�ci wsp�czynnik�w macierzy transformacji przy za�o�eniu,
   *        �e transformacja jest realizowana po rotacji.
   */
  void AddScaleZ_TAfterR( float  d_Sz )
                        { AddScale_TAfterR(0,0,d_Sz); }



  //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    /*!
     * Inicjalizuje macierz transformacji jako przekszta�cenie to�samo�ciowe.
     * \post Zainicjalizowaniu macierzy towarzyszy zgodno�� parametr�w
     *    zainicjalizowanych w polach 
     *    \link MatrixH3f::_RotAng _RotAng\endlink,
     *    \link MatrixH3f::_Trans _Trans\endlink oraz 
     *    \link MatrixH3f::_Scale _Scale\endlink. 
     *    Ponadto zostaj� ustawione znaczniki wa�no�ci warto�ci poszczeg�lnych
     *    parametr�w.
     */ 
    MatrixH3f();

    /*=!
     * Inicjalizuje macierz transformacji na podstawie podanych paramter�w 
     * transformacji.
     * \param Param - (\b in) zawiera parametry transformacji 
     *                (k�ty rotacji traktowane
     *                jako obroty wok� osi OX, OY, OZ, wektor translacji,
     *                wsp�czynniki skali).
     * \param ATyp - (\b in) okre�la spos�b interpretacji warto�ci k�t�w rotacji,
     *               kt�re dost�pne s� w polu
     *               \link MatrixH3f::_RotAng _RotAng\endlink.
     * \post Zainicjalizowaniu macierzy towarzyszy zgodno�� parametr�w
     *     zainicjalizowanych warto�ciami udost�pnianymi przez parametr
     *     \e Param.
     *     Warto�ci parametr�w transformacji wpisywane s� w polach 
     *     \link MatrixH3f::_RotAng _RotAng\endlink,
     *     \link MatrixH3f::_Trans _Trans\endlink oraz 
     *     \link MatrixH3f::_Scale _Scale\endlink. Dlatego te� pole
     *     \link MatrixH3f::_Valid _Valid\endlink inicjalizowane jest 
     *     warto�ci� \p true.
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
 * Umo�liwia wy�wietlenie na wyj�ciu standardowym ca�ej warto�ci
 * parametr�w transformacji.
 */
std::ostream &operator << ( std::ostream &, MatrixH3f::Parameters const & );

/*!
 * Umo�liwia wy�wietlenie na wyj�ciu standardowym napisu okre�laj�cego
 * typ k�t�w rotacji. Wy�wietlany napis zgodny z nazw� warto�ci
 * typu \link MatrixH3f::AnglesType MatrixH3f::AnglesType\endlink.
 */
std::ostream &operator << ( std::ostream &, MatrixH3f::AnglesType const & );


/*!
 * Umo�liwia wy�wietlenie na wyj�ciu standardowym ca�ej macierzy
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
