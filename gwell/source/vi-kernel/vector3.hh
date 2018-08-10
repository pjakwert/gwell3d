#ifndef VECTIR3_HH
#define VECTIR3_HH

/*!
 * \file	vector3.hh
 * \author      Bogdan Kreczmer
 * \date        2003.12
 *
 * Szablon przeznaczony jest do definiowania wektorów w przestrzeni 3D.
 */


#ifdef __GNUG__
#pragma interface
#endif
#include <iostream>
#include <cmath>
#include "sgn.hh"

using namespace std;


/*!
 * Szablon modeluje wektor w przestrzeni 3D. Zapewnia zamodelowanie wekora
 * nad cia³em liczb typu TYPE (zdefiniowana jest operacja dodawnia i 
 * odejmowania wektorów oraz mno¿enia i dzielenia przez liczbê).
 * Zdefiniowny jest iloczyn sklarny i wektorowy oraz wszystkie oraz dodatkowe
 * pomocnicze metody pozwalaj±ce stwierdziæ, czy dany punkty znajduje
 * siê wewn±trz zadanego prostopad³o¶cianu.
 */
template<typename TYPE>
class Vector3 {

    /*!
     *  W niniejszej tablicy przechowywane s± warto¶ci poszczególnych 
     *  sk³adowych wektora poczynaj±c od sk³adowej \e x i dalej \e y
     *  \e z.
     */
   TYPE  _tab[3];

    /*!
     *  Pole jest referencj± do elementu \e _tab[0]. Daje bezpo¶redni
     *  dostêp do \e x-owej sk³adowej wektora.
     */
   TYPE  &_x;

    /*!
     *  Pole jest referencj± do elementu \e _tab[1]. Daje bezpo¶redni
     *  dostêp do \e y-owej sk³adowej wektora.
     */
   TYPE  &_y;

    /*!
     *  Pole jest referencj± do elementu \e _tab[1]. Daje bezpo¶redni
     *  dostêp do \e y-owej sk³adowej wektora.
     */
   TYPE  &_z;

  public:

    /*!
     *  Pole jest referencj± do elementu \e _tab[0]. Daje bezpo¶redni
     *  dostêp do \e x-owej sk³adowej wektora.  Przeznaczone
     *  jest do wykorzystywania na poziomie innych metod (spoza klasy
     *  Vetor3).
     */
   TYPE  &x;

    /*!
     *  Pole jest referencj± do elementu \e _tab[1]. Daje bezpo¶redni
     *  dostêp do \e y-owej sk³adowej wektora.  Przeznaczone
     *  jest do wykorzystywania na poziomie innych metod (spoza klasy
     *  Vetor3).
     */
   TYPE  &y;

    /*!
     *  Pole jest referencj± do elementu \e _tab[2]. Daje bezpo¶redni
     *  dostêp do \e z-owej sk³adowej wektora.  Przeznaczone
     *  jest do wykorzystywania na poziomie innych metod (spoza klasy
     *  Vetor3).
     */
   TYPE  &z;


    /*!
     * Tworzy obiekt i inicjalizuje sk³adowe wektora odpowiadaj±cym
     * im warto¶ciom parametrów.
     * \param xx - warto¶æ dla sk³adowej \e x,
     * \param yy - warto¶æ dla sk³adowej \e y,
     * \param zz - warto¶æ dla sk³adowej \e z.
     */
   Vector3<TYPE>(TYPE xx, TYPE yy, TYPE zz);


    /*!
     * Tworzy obiekt i inicjalizuje sk³adowe wektora odpowiadaj±cym
     * im warto¶ciom wektora przekazywanego jako parametr.
     * \param V - warto¶æ inicjalizuj±ca tworzony obiekt.
     */
   Vector3<TYPE>(Vector3<TYPE> const &V);

    /*!
     * Tworzy obiekt i inicjalizuje sk³adowe wektora warto¶ci± 0.
     */
   Vector3<TYPE>(void);


    /*!
     *  Zwraca warto¶æ sk³adowej \e x.
     * \warning Ze wzglêdu na wprowadzenie bezpo¶rednich publicznych
     *    referencji do poszczególnych pól metoda przewidziana jest
     *    do usuniêcia i nie nale¿y jej wykorzystywaæ. Zalecane jest
     *    bezpo¶redne pos³ugiwanie siê polami 
     *     \link Vector3::x x\endlink, 
     *     \link Vector3::y y\endlink, 
     *     \link Vector3::z z\endlink.
     */
   TYPE X() const { return _x; }

    /*!
     *  Zwraca referencjê do sk³adowej \e x.
     * \warning Ze wzglêdu na wprowadzenie bezpo¶rednich publicznych
     *    referencji do poszczególnych pól metoda przewidziana jest
     *    do usuniêcia i nie nale¿y jej wykorzystywaæ. Zalecane jest
     *    bezpo¶redne pos³ugiwanie siê polami 
     *     \link Vector3::x x\endlink, 
     *     \link Vector3::y y\endlink, 
     *     \link Vector3::z z\endlink.
     */
   TYPE &X() { return _x; }

    /*!
     *  Zwraca warto¶æ sk³adowej \e y.
     * \warning Ze wzglêdu na wprowadzenie bezpo¶rednich publicznych
     *    referencji do poszczególnych pól metoda przewidziana jest
     *    do usuniêcia i nie nale¿y jej wykorzystywaæ. Zalecane jest
     *    bezpo¶redne pos³ugiwanie siê polami 
     *     \link Vector3::x x\endlink, 
     *     \link Vector3::y y\endlink, 
     *     \link Vector3::z z\endlink.
     */
   TYPE Y() const { return _y; }

    /*!
     *  Zwraca referencjê do sk³adowej \e y.
     * \warning Ze wzglêdu na wprowadzenie bezpo¶rednich publicznych
     *    referencji do poszczególnych pól metoda przewidziana jest
     *    do usuniêcia i nie nale¿y jej wykorzystywaæ. Zalecane jest
     *    bezpo¶redne pos³ugiwanie siê polami 
     *     \link Vector3::x x\endlink, 
     *     \link Vector3::y y\endlink, 
     *     \link Vector3::z z\endlink.
     */
   TYPE &Y() { return _y; }

    /*!
     *  Zwraca warto¶æ sk³adowej \e z.
     * \warning Ze wzglêdu na wprowadzenie bezpo¶rednich publicznych
     *    referencji do poszczególnych pól metoda przewidziana jest
     *    do usuniêcia i nie nale¿y jej wykorzystywaæ. Zalecane jest
     *    bezpo¶redne pos³ugiwanie siê polami 
     *     \link Vector3::x x\endlink, 
     *     \link Vector3::y y\endlink, 
     *     \link Vector3::z z\endlink.
     */
   TYPE Z() const { return _z; }

    /*!
     *  Zwraca referencjê do sk³adowej \e z.
     * \warning Ze wzglêdu na wprowadzenie bezpo¶rednich publicznych
     *    referencji do poszczególnych pól metoda przewidziana jest
     *    do usuniêcia i nie nale¿y jej wykorzystywaæ. Zalecane jest
     *    bezpo¶redne pos³ugiwanie siê polami 
     *     \link Vector3::x x\endlink, 
     *     \link Vector3::y y\endlink, 
     *     \link Vector3::z z\endlink.
     */
   TYPE &Z() { return _z; }


    /*!
     *  Udostêpnia sk³adow± wektora o podanym indeksie.
     *  Udostêpniona sk³adowa nie  mo¿e byæ poddawana zmianom.
     *  \param  inx - indeks sk³adowej wektora.
     *  \pre \e inx musi zawieraæ jedn± z warto¶ci: 0, 1, 2.
     *   Odpowiadaj± one sk³adowym: \e x, \e y, \e z.
     *   Podanie innej warto¶ci jest niedopuszczalne (brak kontroli
     *   b³edu).
     *  \post Zwraca referencjê sta³± do wybranej sk³adowej wektora.
     */
   TYPE  &operator [](unsigned int inx) { return _tab[inx]; }

    /*!
     *  Udostêpnia sk³adow± wektora o podanym indeksie.
     *  Udostêpniona sk³adowa mo¿e byæ poddawana zmianom.
     *  \param  inx - indeks sk³adowej wektora.
     *  \pre \e inx musi zawieraæ jedn± z warto¶ci: 0, 1, 2.
     *   Odpowiadaj± one sk³adowym: \e x, \e y, \e z.
     *   Podanie innej warto¶ci jest niedopuszczalne (brak kontroli
     *   b³edu).
     *  \post Zwraca referencjê do wybranej sk³adowej wektora.
     */
   TYPE operator [](unsigned int inx) const { return _tab[inx]; }


    /*! 
     *  Operacja implementuje sume wektorów.
     *  \param  V - drugi sk³adnik.
     *  \retval  Vector3<TYPE> - obiekt zawieraj±cy warto¶æ sumy
     *                           dwóch wektorów \b *this i \e V.
     */
   Vector3<TYPE>  operator  + (Vector3<TYPE> const &V) const;

    /*! 
     *  Operacja implementuje sumê wektorów.
     *  \param  V - drugi sk³adnik.
     *  \retval *this - referencja do samego siebie.
     *                  Obiekt przyjmuje now± warto¶æ bêd±c±
     *                 sum± dwóch wektorów \b *this i \e V.
     */
   Vector3<TYPE> &operator += (Vector3<TYPE> const &V);

    /*! 
     *  Operacja implementuje ró¿nicê wektorów.
     *  \param  V - odjemnik.
     *  \retval  Vector3<TYPE> - obiekt bêd±cy ró¿nic± dwóch wektorów
     *                                  \b *this i \e V.
     */
   Vector3<TYPE>  operator  - (Vector3<TYPE> const &V) const;

    /*! 
     *  Operacja implementuje ró¿nicê wektorów.
     *  \param  V - odjemnik.
     *  \retval *this - referencja do samego siebie.
     *                  Obiekt przyjmuje now± warto¶æ bêd±c± 
     *                 ró¿nic± dwóch wektorów \b *this i \e V.
     */
   Vector3<TYPE> &operator -= (Vector3<TYPE> const &V);

     /*!
      * Operator implementuje iloczyn wektorowy. 
      * \param     V - drugi czynnik iloczynu.
      * \retval  Vector3<TYPE>  - obiekt bêd±cy produktem iloczynu
      *                           wektorowego \b *this i \e V.
      */
   Vector3<TYPE>  operator  * (Vector3<TYPE> const &V) const;

     /*!
      * Operator implementuje iloczyn wektorowy. 
      * \param     V - drugi czynnik iloczynu.
      * \retval *this  - referencjê do samego siebie.
      *              Obiekt przyjmuje now± warto¶æ bêd±c±
      *              produktem iloczynu wektorowego \b *this i \e V.
      */
   Vector3<TYPE> &operator *= (Vector3<TYPE> const &V); 

     /*!
      * Operator implementuje mno¿enie wektora przez liczbê.
      * \param     L - drugi czynnik iloczynu (liczba).
      * \retval  Vector3<TYPE>  - obiekt bêd±cy  iloczynu wekora
      *                            \b *this i liczby \e L.
      */
   Vector3<TYPE>  operator  * (TYPE L) const;

     /*!
      * Operator implementuje iloczyn wektora przez liczbê.
      * \param     L - drugi czynnik iloczynu (liczba).
      * \retval *this  - referencjê do samego siebie.
      *              Obiekt przyjmuje now± warto¶æ bêd±c±
      *              produktem iloczynem \b *this i liczby \e L.
      */
   Vector3<TYPE> &operator *= (TYPE L);

     /*!
      * Operator implementuje iloraz wektora przez liczbê.
      * \param     L - dzielnik wekora (liczba).
      * \retval  Vector3<TYPE>  - obiekt bêd±cy ilorazem
      *                            \b *this (wektor) / \e L (liczba).
      */
   Vector3<TYPE>  operator  / (TYPE L) const;

     /*!
      * Operator implementuje iloraz wektora przez liczbê.
      * \param     L - dzielnik wektora (liczba).
      * \retval *this  - referencjê do samego siebie.
      *              Obiekt przyjmuje now± warto¶æ bêd±c±
      *              ilorazem \b *this i liczby \e L.
      */
   Vector3<TYPE> &operator /= (TYPE L);

     /*!
      * Operator implementuje iloczyn sklarany dwóch wektorów.
      * \param V - drugi czynnik iloczynu skalarnego.
      * \return Warto¶æ bêd±c± iloczynem skalarnym wektorów \b *this
      *         i \e V.
      */
   TYPE  operator & (Vector3<TYPE> const &V) const;      // skalar product


    /*!
     *  Wykonuje operacjê podstawienia.
     *  \return
     *     referencjê na samego siebie (tzn. referencjê na obiekt, dla którego
     *     wywo³any zosta³ ten operator).
     */
  Vector3<TYPE> &operator = (Vector3<TYPE> const & Pnt);

    /*!
     *  Dokonuje porównania dwóch wektorów.
     *  \retval  true - je¶li odpowiadaj±ce sk³adowej s± sobie równe
     *              w sensie funkcji sgn (patrz \link sgn.hh sgn.hh \endlink).
     *              pozwala to uwzglêdniæ (przynajmniej czê¶ciowo) b³edy 
     *              obliczeñ,
     *  \retval  false - w przypadku przeciwnym.
     */
   bool          operator == (Vector3<TYPE> const &);



    /*!
     *  Wylicza d³ugo¶æ wektora w sensie metryki euklidesowej.
     */
   TYPE Length() const;

    /*!
     *  Zmienia znak wszystkich sk³adowych wektora na przeciwny.
     *  \return\b *this - zwraca referencjê do samego siebie.
     */
   Vector3<TYPE> &Inverse() { _x = -_x; _y = -_y; _z = -_z; return *this; }

    /*!
     *  Dokonuje podstawieñ do poszczególnych sk³adowych warto¶ci 
     *  przekazywanych przez parametry wywo³ania.
     *  \param xx - warto¶æ dla sk³adowej {\e _x},
     *  \param yy - warto¶æ dla sk³adowej {\e _y},
     *  \param zz - warto¶æ dla sk³adowej {\e _z},
     *  \return zwraca referencjê do samego siebie (tzn. do obiektu,
     *          dla którego zosta³a wywo³ana).
     */
   Vector3<TYPE> &Set(TYPE xx, TYPE yy, TYPE zz) 
                         { _x=xx; _y=yy; _z=zz; return *this; }

    /*! 
     *  Dodaje do danego wspó³rzêdnych danego wektora podane
     *  warto¶ci.
     *  \param  xx - warto¶æ dodawana do \e x-owej wspó³rzêdnej.
     *  \param  yy - warto¶æ dodawana do \e y-owej wspó³rzêdnej.
     *  \param  zz - warto¶æ dodawana do \e z-owej wspó³rzêdnej.
     *  \retval *this - referencja do samego siebie.
     *                  Obiekt przyjmuje now± warto¶æ bêd±c±
     *       do którego wspó³rzêdnych dodane zosta³y podane warto¶ci.
     */
   Vector3<TYPE> &Add(TYPE xx, TYPE yy, TYPE zz) 
                         { _x+=xx; _y+=yy; _z+=zz; return *this; }

    /*!
     *  Podstawia zadan± warto¶æ do wszystkich sk³adowych wektora.
     *  \param val - podstawiana warto¶æ.
     *  \post
     *    Do wszystkich pól wektora zostaje wpisana warto¶æ przekazana
     *    przez parametr \e val.
     */
   void Set(TYPE val) { _x=_y=_z=val;  }


    /*!
     *  Podstawia warto¶æ 0 do wszystkich sk³adowych wektora.
     *  \post
     *    Do wszystkich pól wektora zostaje wpisana warto¶æ 0.
     */
   void SetZero() { _x=_y=_z=0;  }

    /*!
     *  Dokonuje podstawienia nowych warto¶ci wektora z przekazanego 
     *  parametru wywo³ania metody.
     *  \param V - nowe podstawiane warto¶ci.
     *  \post
     *    Do pól wektora zostaj± wpisane warto¶ci z odpowiadaj±cych
     *    im pól parametru \e V.
     */
   void Set(Vector3<TYPE> const &V) { _x=V._x; _y=V._y; _z=V._z; }

    /*!
     * Podstawia warto¶æ 0 do wszystkich sk³adowych wektora.
     */
   void Set_0() { _x=_y=_z=0; }

    /*!
     * Podstawia warto¶æ 1 do wszystkich sk³adowych wektora.
     */
   void Set_1() { _x=_y=_z=1; }


    /*!
     * Sprawdza czy dany wektor jest wektorem zerowym. Przyjmuje
     * siê ¿e pole marto¶æ 0 je¶li funkcja sgn zwróci warto¶æ 0.
     * Wspomniana funkcja uwzglêdnia b³êdy obliczeñ zdefiniowane
     * poprzez sta³± ERROR_LEVEL.
     * \return true - je¶li sgn zwróci dla wszystkich pól zero,
     * \return false - w przypadku przeciwnym.
     */
   bool IsZero() const; 


    /*!
     * Sprawdza czy wspó³rzêdna \e x znajduje siê wewn±trz przedzia³u.
     * \param x_min - dolny kraniec przedzia³u.
     * \param x_max - górny kraniec przedzia³u.
     * \return true - je¶li warto¶æ pola \e _x jest wewn±trz przedzialu 
     *               (\e x_min, \e x_max).
     * \return false - w przypadku przeciwnym.
     */
   bool InX(TYPE x_min, TYPE x_max) const {return (x_min<_x) && (_x<x_max);}

    /*!
     * Sprawdza czy wspó³rzêdna \e y znajduje siê wewn±trz przedzia³u.
     * \param y_min - dolny kraniec przedzia³u.
     * \param y_max - górny kraniec przedzia³u.
     * \return true - je¶li warto¶æ pola \e _y jest wewn±trz przedzialu 
     *               (\e y_min, \e y_max).
     * \return false - w przypadku przeciwnym.
     */
   bool InY(TYPE y_min, TYPE y_max) const {return (y_min<_y) && (_y<y_max);}

    /*!
     * Sprawdza czy wspó³rzêdna \e z znajduje siê wewn±trz przedzia³u.
     * \param z_min - dolny kraniec przedzia³u.
     * \param z_max - górny kraniec przedzia³u.
     * \return true - je¶li warto¶æ pola \e _z jest wewn±trz przedzialu 
     *               (\e z_min, \e z_max).
     * \return false - w przypadku przeciwnym.
     */
   bool InZ(TYPE z_min, TYPE z_max) const {return (z_min<_z) && (_z<z_max);}

    /*!
     * Sprawdza czy dany punkty jest wewn±trz prostopad³o¶cianu.
     * Zak³ada siê, ¿e ¶cianki prostopad³o¶cu s± równoleg³e do jednej
     * z p³aszczyzn kartezjañskiegu uk³adu wspó³rzêdnych OXY.
     * \param Min - zawiera wspó³rzêdne wierzcho³ka, którego sk³adowe
     *              maj± minimalne warto¶ci spo¶ród sk³adowych tego 
     *              samego typu wszyskich wierzcho³ków
     *              tego prostopad³o¶cianu.
     * \param Max - zawiera wspó³rzêdne wierzcho³ka, którego sk³adowe
     *              maj± maksymalne warto¶ci spo¶ród sk³adowych tego 
     *              samego typu wszyskich wierzcho³ków
     *              tego prostopad³o¶cianu.
     *              prostopad³o¶cianu.
     * \return  true  - je¶li punkt jest wewn±trz prostopad³o¶cianu.
     * \return  false - w przypadku przeciwnym.
     */
   bool IsInside(Vector3<TYPE> const &Min, Vector3<TYPE> Max) const;

    /*!
     * Normalizuje wektor.
     */
  void Normalize() 
      { TYPE d = (TYPE)sqrt(_x*_x+_y*_y+_z*_z); _x/=d; _y/=d; _z/=d; }
};



template<typename TYPE>
inline
Vector3<TYPE> &Vector3<TYPE>::operator = (Vector3<TYPE> const & Pnt)
  { _x = Pnt._x;  _y = Pnt._y;  _z = Pnt._z;  return *this; }


template<typename TYPE>
inline
Vector3<TYPE>::Vector3(): _x(_tab[0]), _y(_tab[1]), _z(_tab[2]),
                      x(_tab[0]), y(_tab[1]), z(_tab[2]) { _x=_y=_z=0; };


template<typename TYPE>
inline
Vector3<TYPE>::Vector3(TYPE xx, TYPE yy, TYPE zz):
     _x(_tab[0]), _y(_tab[1]), _z(_tab[2]),
     x(_tab[0]), y(_tab[1]), z(_tab[2]) { _x=xx; _y=yy; _z=zz; };


template<typename TYPE>
inline
Vector3<TYPE>::Vector3(Vector3 const &V): 
           _x(_tab[0]), _y(_tab[1]), _z(_tab[2]),
           x(_tab[0]), y(_tab[1]), z(_tab[2]) { _x=V._x; _y=V._y; _z=V._z; };



template<typename TYPE>
inline
bool Vector3<TYPE>::IsInside(Vector3<TYPE> const &Min, Vector3<TYPE> Max) const
{
  return InX(Min._x,Max._x) && InY(Min._y,Max._y) && InZ(Min._z,Max._z);
}

/*!
 *  Umo¿liwia wy¶wietlenie wspó³rzêdnych wektora.
 *  \param ostrm - strumien standaradowy,
 *  \param V - wektor, której wspó³rzêdne maj± zostaæ wy¶wietlone.
 */
template<typename TYPE>
inline
std::ostream & operator << ( std::ostream &ostrm, const Vector3<TYPE> &V)
{
  return ostrm << "(" << V.X() << ", " << V.Y() << ", " << V.Z() << ")";
}



#ifdef EXTSTRING_HH
/*!
 *  Umo¿liwia wpisanie wspó³rzêdnych wektora bufora znakowego klasy ExtString.
 *  \param Buff - bufor znakowy,
 *  \param V - wektor, której wspó³rzêdne maj± zostaæ wy¶wietlone.
 */
template<typename TYPE>
inline
ExtString & operator << ( ExtString &Buff, const Vector3<TYPE> &V)
{
  return Buff << "(" << V.X() << ", " << V.Y() << ", " << V.Z() << ")";
}
#endif



template<typename TYPE>
inline
TYPE Vector3<TYPE>::Length() const
{
  return sqrt(*this & *this);
}


template<typename TYPE>
inline
Vector3<TYPE> Vector3<TYPE>::operator + (Vector3 const & sndComp) const
{
 return Vector3<TYPE>(_x+sndComp._x,y+sndComp._y,z+sndComp._z);
}


template<typename TYPE>
inline
Vector3<TYPE> &Vector3<TYPE>::operator += (Vector3<TYPE> const & Comp)
{
 _x+=Comp._x;  _y+=Comp._y;  _z+=Comp._z;  return *this;
}


template<typename TYPE>
inline
Vector3<TYPE> Vector3<TYPE>::operator - (Vector3<TYPE>  const &  sndComp) const
{
 return Vector3<TYPE>(_x-sndComp._x,_y-sndComp._y,_z-sndComp._z);
}


template<typename TYPE>
inline
Vector3<TYPE> &Vector3<TYPE>::operator -= (Vector3<TYPE> const & Comp)
{
  _x-=Comp._x;  _y-=Comp._y;  _z-=Comp._z;  return *this;
}


template<typename TYPE>
inline
Vector3<TYPE> Vector3<TYPE>::operator * (TYPE Digit) const
{
 return Vector3<TYPE>(_x*Digit,_y*Digit,_z*Digit);
}


template<typename TYPE>
inline
Vector3<TYPE> &Vector3<TYPE>::operator *= (TYPE Digit)
{ _x*=Digit;  _y*=Digit;  _z*=Digit;  return *this; }





template<typename TYPE>
inline
Vector3<TYPE> Vector3<TYPE>::operator *(Vector3<TYPE> const & sndComp) const
{
  return Vector3<TYPE>(_y*sndComp._z - _z*sndComp._y,
                    _z*sndComp._x - _x*sndComp._z,
                    _x*sndComp._y - _y*sndComp._x);
}



template<typename TYPE>
inline
Vector3<TYPE> &Vector3<TYPE>::operator *= (Vector3<TYPE> const & sndComp)
{ 
 return Set(_y*sndComp._z - _z*sndComp._y,
            _z*sndComp._x - _x*sndComp._z,
            _x*sndComp._y - _y*sndComp._x);
}


template<typename TYPE>
inline
Vector3<TYPE> Vector3<TYPE>::operator / (TYPE Digit) const
{
 return Vector3<TYPE>(_x/Digit,_y/Digit,_z/Digit);
}


template<typename TYPE>
inline
Vector3<TYPE> &Vector3<TYPE>::operator /= (TYPE Digit)
{ _x/=Digit;  _y/=Digit;  _z/=Digit;  return *this; }


template<typename TYPE>
inline
bool Vector3<TYPE>::IsZero() const
 { return  !(sgn(_x) || sgn(_y) || sgn(_z)); }


template<typename TYPE>
inline
bool Vector3<TYPE>::operator == (Vector3<TYPE> const & sndComp)
{ return !(sgn(sndComp._x-_x) || sgn(sndComp._y-_y) || sgn(sndComp._z-_z)); }


template<typename TYPE>
inline
TYPE Vector3<TYPE>::operator & (Vector3<TYPE> const &V) const
{
  return _x*V._x+_y*V._y+_z*V._z;
}

#endif
