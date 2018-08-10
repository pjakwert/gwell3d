#ifndef VECTIR3_HH
#define VECTIR3_HH

/*!
 * \file	vector3.hh
 * \author      Bogdan Kreczmer
 * \date        2003.12
 *
 * Szablon przeznaczony jest do definiowania wektor�w w przestrzeni 3D.
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
 * nad cia�em liczb typu TYPE (zdefiniowana jest operacja dodawnia i 
 * odejmowania wektor�w oraz mno�enia i dzielenia przez liczb�).
 * Zdefiniowny jest iloczyn sklarny i wektorowy oraz wszystkie oraz dodatkowe
 * pomocnicze metody pozwalaj�ce stwierdzi�, czy dany punkty znajduje
 * si� wewn�trz zadanego prostopad�o�cianu.
 */
template<typename TYPE>
class Vector3 {

    /*!
     *  W niniejszej tablicy przechowywane s� warto�ci poszczeg�lnych 
     *  sk�adowych wektora poczynaj�c od sk�adowej \e x i dalej \e y
     *  \e z.
     */
   TYPE  _tab[3];

    /*!
     *  Pole jest referencj� do elementu \e _tab[0]. Daje bezpo�redni
     *  dost�p do \e x-owej sk�adowej wektora.
     */
   TYPE  &_x;

    /*!
     *  Pole jest referencj� do elementu \e _tab[1]. Daje bezpo�redni
     *  dost�p do \e y-owej sk�adowej wektora.
     */
   TYPE  &_y;

    /*!
     *  Pole jest referencj� do elementu \e _tab[1]. Daje bezpo�redni
     *  dost�p do \e y-owej sk�adowej wektora.
     */
   TYPE  &_z;

  public:

    /*!
     *  Pole jest referencj� do elementu \e _tab[0]. Daje bezpo�redni
     *  dost�p do \e x-owej sk�adowej wektora.  Przeznaczone
     *  jest do wykorzystywania na poziomie innych metod (spoza klasy
     *  Vetor3).
     */
   TYPE  &x;

    /*!
     *  Pole jest referencj� do elementu \e _tab[1]. Daje bezpo�redni
     *  dost�p do \e y-owej sk�adowej wektora.  Przeznaczone
     *  jest do wykorzystywania na poziomie innych metod (spoza klasy
     *  Vetor3).
     */
   TYPE  &y;

    /*!
     *  Pole jest referencj� do elementu \e _tab[2]. Daje bezpo�redni
     *  dost�p do \e z-owej sk�adowej wektora.  Przeznaczone
     *  jest do wykorzystywania na poziomie innych metod (spoza klasy
     *  Vetor3).
     */
   TYPE  &z;


    /*!
     * Tworzy obiekt i inicjalizuje sk�adowe wektora odpowiadaj�cym
     * im warto�ciom parametr�w.
     * \param xx - warto�� dla sk�adowej \e x,
     * \param yy - warto�� dla sk�adowej \e y,
     * \param zz - warto�� dla sk�adowej \e z.
     */
   Vector3<TYPE>(TYPE xx, TYPE yy, TYPE zz);


    /*!
     * Tworzy obiekt i inicjalizuje sk�adowe wektora odpowiadaj�cym
     * im warto�ciom wektora przekazywanego jako parametr.
     * \param V - warto�� inicjalizuj�ca tworzony obiekt.
     */
   Vector3<TYPE>(Vector3<TYPE> const &V);

    /*!
     * Tworzy obiekt i inicjalizuje sk�adowe wektora warto�ci� 0.
     */
   Vector3<TYPE>(void);


    /*!
     *  Zwraca warto�� sk�adowej \e x.
     * \warning Ze wzgl�du na wprowadzenie bezpo�rednich publicznych
     *    referencji do poszczeg�lnych p�l metoda przewidziana jest
     *    do usuni�cia i nie nale�y jej wykorzystywa�. Zalecane jest
     *    bezpo�redne pos�ugiwanie si� polami 
     *     \link Vector3::x x\endlink, 
     *     \link Vector3::y y\endlink, 
     *     \link Vector3::z z\endlink.
     */
   TYPE X() const { return _x; }

    /*!
     *  Zwraca referencj� do sk�adowej \e x.
     * \warning Ze wzgl�du na wprowadzenie bezpo�rednich publicznych
     *    referencji do poszczeg�lnych p�l metoda przewidziana jest
     *    do usuni�cia i nie nale�y jej wykorzystywa�. Zalecane jest
     *    bezpo�redne pos�ugiwanie si� polami 
     *     \link Vector3::x x\endlink, 
     *     \link Vector3::y y\endlink, 
     *     \link Vector3::z z\endlink.
     */
   TYPE &X() { return _x; }

    /*!
     *  Zwraca warto�� sk�adowej \e y.
     * \warning Ze wzgl�du na wprowadzenie bezpo�rednich publicznych
     *    referencji do poszczeg�lnych p�l metoda przewidziana jest
     *    do usuni�cia i nie nale�y jej wykorzystywa�. Zalecane jest
     *    bezpo�redne pos�ugiwanie si� polami 
     *     \link Vector3::x x\endlink, 
     *     \link Vector3::y y\endlink, 
     *     \link Vector3::z z\endlink.
     */
   TYPE Y() const { return _y; }

    /*!
     *  Zwraca referencj� do sk�adowej \e y.
     * \warning Ze wzgl�du na wprowadzenie bezpo�rednich publicznych
     *    referencji do poszczeg�lnych p�l metoda przewidziana jest
     *    do usuni�cia i nie nale�y jej wykorzystywa�. Zalecane jest
     *    bezpo�redne pos�ugiwanie si� polami 
     *     \link Vector3::x x\endlink, 
     *     \link Vector3::y y\endlink, 
     *     \link Vector3::z z\endlink.
     */
   TYPE &Y() { return _y; }

    /*!
     *  Zwraca warto�� sk�adowej \e z.
     * \warning Ze wzgl�du na wprowadzenie bezpo�rednich publicznych
     *    referencji do poszczeg�lnych p�l metoda przewidziana jest
     *    do usuni�cia i nie nale�y jej wykorzystywa�. Zalecane jest
     *    bezpo�redne pos�ugiwanie si� polami 
     *     \link Vector3::x x\endlink, 
     *     \link Vector3::y y\endlink, 
     *     \link Vector3::z z\endlink.
     */
   TYPE Z() const { return _z; }

    /*!
     *  Zwraca referencj� do sk�adowej \e z.
     * \warning Ze wzgl�du na wprowadzenie bezpo�rednich publicznych
     *    referencji do poszczeg�lnych p�l metoda przewidziana jest
     *    do usuni�cia i nie nale�y jej wykorzystywa�. Zalecane jest
     *    bezpo�redne pos�ugiwanie si� polami 
     *     \link Vector3::x x\endlink, 
     *     \link Vector3::y y\endlink, 
     *     \link Vector3::z z\endlink.
     */
   TYPE &Z() { return _z; }


    /*!
     *  Udost�pnia sk�adow� wektora o podanym indeksie.
     *  Udost�pniona sk�adowa nie  mo�e by� poddawana zmianom.
     *  \param  inx - indeks sk�adowej wektora.
     *  \pre \e inx musi zawiera� jedn� z warto�ci: 0, 1, 2.
     *   Odpowiadaj� one sk�adowym: \e x, \e y, \e z.
     *   Podanie innej warto�ci jest niedopuszczalne (brak kontroli
     *   b�edu).
     *  \post Zwraca referencj� sta�� do wybranej sk�adowej wektora.
     */
   TYPE  &operator [](unsigned int inx) { return _tab[inx]; }

    /*!
     *  Udost�pnia sk�adow� wektora o podanym indeksie.
     *  Udost�pniona sk�adowa mo�e by� poddawana zmianom.
     *  \param  inx - indeks sk�adowej wektora.
     *  \pre \e inx musi zawiera� jedn� z warto�ci: 0, 1, 2.
     *   Odpowiadaj� one sk�adowym: \e x, \e y, \e z.
     *   Podanie innej warto�ci jest niedopuszczalne (brak kontroli
     *   b�edu).
     *  \post Zwraca referencj� do wybranej sk�adowej wektora.
     */
   TYPE operator [](unsigned int inx) const { return _tab[inx]; }


    /*! 
     *  Operacja implementuje sume wektor�w.
     *  \param  V - drugi sk�adnik.
     *  \retval  Vector3<TYPE> - obiekt zawieraj�cy warto�� sumy
     *                           dw�ch wektor�w \b *this i \e V.
     */
   Vector3<TYPE>  operator  + (Vector3<TYPE> const &V) const;

    /*! 
     *  Operacja implementuje sum� wektor�w.
     *  \param  V - drugi sk�adnik.
     *  \retval *this - referencja do samego siebie.
     *                  Obiekt przyjmuje now� warto�� b�d�c�
     *                 sum� dw�ch wektor�w \b *this i \e V.
     */
   Vector3<TYPE> &operator += (Vector3<TYPE> const &V);

    /*! 
     *  Operacja implementuje r�nic� wektor�w.
     *  \param  V - odjemnik.
     *  \retval  Vector3<TYPE> - obiekt b�d�cy r�nic� dw�ch wektor�w
     *                                  \b *this i \e V.
     */
   Vector3<TYPE>  operator  - (Vector3<TYPE> const &V) const;

    /*! 
     *  Operacja implementuje r�nic� wektor�w.
     *  \param  V - odjemnik.
     *  \retval *this - referencja do samego siebie.
     *                  Obiekt przyjmuje now� warto�� b�d�c� 
     *                 r�nic� dw�ch wektor�w \b *this i \e V.
     */
   Vector3<TYPE> &operator -= (Vector3<TYPE> const &V);

     /*!
      * Operator implementuje iloczyn wektorowy. 
      * \param     V - drugi czynnik iloczynu.
      * \retval  Vector3<TYPE>  - obiekt b�d�cy produktem iloczynu
      *                           wektorowego \b *this i \e V.
      */
   Vector3<TYPE>  operator  * (Vector3<TYPE> const &V) const;

     /*!
      * Operator implementuje iloczyn wektorowy. 
      * \param     V - drugi czynnik iloczynu.
      * \retval *this  - referencj� do samego siebie.
      *              Obiekt przyjmuje now� warto�� b�d�c�
      *              produktem iloczynu wektorowego \b *this i \e V.
      */
   Vector3<TYPE> &operator *= (Vector3<TYPE> const &V); 

     /*!
      * Operator implementuje mno�enie wektora przez liczb�.
      * \param     L - drugi czynnik iloczynu (liczba).
      * \retval  Vector3<TYPE>  - obiekt b�d�cy  iloczynu wekora
      *                            \b *this i liczby \e L.
      */
   Vector3<TYPE>  operator  * (TYPE L) const;

     /*!
      * Operator implementuje iloczyn wektora przez liczb�.
      * \param     L - drugi czynnik iloczynu (liczba).
      * \retval *this  - referencj� do samego siebie.
      *              Obiekt przyjmuje now� warto�� b�d�c�
      *              produktem iloczynem \b *this i liczby \e L.
      */
   Vector3<TYPE> &operator *= (TYPE L);

     /*!
      * Operator implementuje iloraz wektora przez liczb�.
      * \param     L - dzielnik wekora (liczba).
      * \retval  Vector3<TYPE>  - obiekt b�d�cy ilorazem
      *                            \b *this (wektor) / \e L (liczba).
      */
   Vector3<TYPE>  operator  / (TYPE L) const;

     /*!
      * Operator implementuje iloraz wektora przez liczb�.
      * \param     L - dzielnik wektora (liczba).
      * \retval *this  - referencj� do samego siebie.
      *              Obiekt przyjmuje now� warto�� b�d�c�
      *              ilorazem \b *this i liczby \e L.
      */
   Vector3<TYPE> &operator /= (TYPE L);

     /*!
      * Operator implementuje iloczyn sklarany dw�ch wektor�w.
      * \param V - drugi czynnik iloczynu skalarnego.
      * \return Warto�� b�d�c� iloczynem skalarnym wektor�w \b *this
      *         i \e V.
      */
   TYPE  operator & (Vector3<TYPE> const &V) const;      // skalar product


    /*!
     *  Wykonuje operacj� podstawienia.
     *  \return
     *     referencj� na samego siebie (tzn. referencj� na obiekt, dla kt�rego
     *     wywo�any zosta� ten operator).
     */
  Vector3<TYPE> &operator = (Vector3<TYPE> const & Pnt);

    /*!
     *  Dokonuje por�wnania dw�ch wektor�w.
     *  \retval  true - je�li odpowiadaj�ce sk�adowej s� sobie r�wne
     *              w sensie funkcji sgn (patrz \link sgn.hh sgn.hh \endlink).
     *              pozwala to uwzgl�dni� (przynajmniej cz�ciowo) b�edy 
     *              oblicze�,
     *  \retval  false - w przypadku przeciwnym.
     */
   bool          operator == (Vector3<TYPE> const &);



    /*!
     *  Wylicza d�ugo�� wektora w sensie metryki euklidesowej.
     */
   TYPE Length() const;

    /*!
     *  Zmienia znak wszystkich sk�adowych wektora na przeciwny.
     *  \return\b *this - zwraca referencj� do samego siebie.
     */
   Vector3<TYPE> &Inverse() { _x = -_x; _y = -_y; _z = -_z; return *this; }

    /*!
     *  Dokonuje podstawie� do poszczeg�lnych sk�adowych warto�ci 
     *  przekazywanych przez parametry wywo�ania.
     *  \param xx - warto�� dla sk�adowej {\e _x},
     *  \param yy - warto�� dla sk�adowej {\e _y},
     *  \param zz - warto�� dla sk�adowej {\e _z},
     *  \return zwraca referencj� do samego siebie (tzn. do obiektu,
     *          dla kt�rego zosta�a wywo�ana).
     */
   Vector3<TYPE> &Set(TYPE xx, TYPE yy, TYPE zz) 
                         { _x=xx; _y=yy; _z=zz; return *this; }

    /*! 
     *  Dodaje do danego wsp�rz�dnych danego wektora podane
     *  warto�ci.
     *  \param  xx - warto�� dodawana do \e x-owej wsp�rz�dnej.
     *  \param  yy - warto�� dodawana do \e y-owej wsp�rz�dnej.
     *  \param  zz - warto�� dodawana do \e z-owej wsp�rz�dnej.
     *  \retval *this - referencja do samego siebie.
     *                  Obiekt przyjmuje now� warto�� b�d�c�
     *       do kt�rego wsp�rz�dnych dodane zosta�y podane warto�ci.
     */
   Vector3<TYPE> &Add(TYPE xx, TYPE yy, TYPE zz) 
                         { _x+=xx; _y+=yy; _z+=zz; return *this; }

    /*!
     *  Podstawia zadan� warto�� do wszystkich sk�adowych wektora.
     *  \param val - podstawiana warto��.
     *  \post
     *    Do wszystkich p�l wektora zostaje wpisana warto�� przekazana
     *    przez parametr \e val.
     */
   void Set(TYPE val) { _x=_y=_z=val;  }


    /*!
     *  Podstawia warto�� 0 do wszystkich sk�adowych wektora.
     *  \post
     *    Do wszystkich p�l wektora zostaje wpisana warto�� 0.
     */
   void SetZero() { _x=_y=_z=0;  }

    /*!
     *  Dokonuje podstawienia nowych warto�ci wektora z przekazanego 
     *  parametru wywo�ania metody.
     *  \param V - nowe podstawiane warto�ci.
     *  \post
     *    Do p�l wektora zostaj� wpisane warto�ci z odpowiadaj�cych
     *    im p�l parametru \e V.
     */
   void Set(Vector3<TYPE> const &V) { _x=V._x; _y=V._y; _z=V._z; }

    /*!
     * Podstawia warto�� 0 do wszystkich sk�adowych wektora.
     */
   void Set_0() { _x=_y=_z=0; }

    /*!
     * Podstawia warto�� 1 do wszystkich sk�adowych wektora.
     */
   void Set_1() { _x=_y=_z=1; }


    /*!
     * Sprawdza czy dany wektor jest wektorem zerowym. Przyjmuje
     * si� �e pole marto�� 0 je�li funkcja sgn zwr�ci warto�� 0.
     * Wspomniana funkcja uwzgl�dnia b��dy oblicze� zdefiniowane
     * poprzez sta�� ERROR_LEVEL.
     * \return true - je�li sgn zwr�ci dla wszystkich p�l zero,
     * \return false - w przypadku przeciwnym.
     */
   bool IsZero() const; 


    /*!
     * Sprawdza czy wsp�rz�dna \e x znajduje si� wewn�trz przedzia�u.
     * \param x_min - dolny kraniec przedzia�u.
     * \param x_max - g�rny kraniec przedzia�u.
     * \return true - je�li warto�� pola \e _x jest wewn�trz przedzialu 
     *               (\e x_min, \e x_max).
     * \return false - w przypadku przeciwnym.
     */
   bool InX(TYPE x_min, TYPE x_max) const {return (x_min<_x) && (_x<x_max);}

    /*!
     * Sprawdza czy wsp�rz�dna \e y znajduje si� wewn�trz przedzia�u.
     * \param y_min - dolny kraniec przedzia�u.
     * \param y_max - g�rny kraniec przedzia�u.
     * \return true - je�li warto�� pola \e _y jest wewn�trz przedzialu 
     *               (\e y_min, \e y_max).
     * \return false - w przypadku przeciwnym.
     */
   bool InY(TYPE y_min, TYPE y_max) const {return (y_min<_y) && (_y<y_max);}

    /*!
     * Sprawdza czy wsp�rz�dna \e z znajduje si� wewn�trz przedzia�u.
     * \param z_min - dolny kraniec przedzia�u.
     * \param z_max - g�rny kraniec przedzia�u.
     * \return true - je�li warto�� pola \e _z jest wewn�trz przedzialu 
     *               (\e z_min, \e z_max).
     * \return false - w przypadku przeciwnym.
     */
   bool InZ(TYPE z_min, TYPE z_max) const {return (z_min<_z) && (_z<z_max);}

    /*!
     * Sprawdza czy dany punkty jest wewn�trz prostopad�o�cianu.
     * Zak�ada si�, �e �cianki prostopad�o�cu s� r�wnoleg�e do jednej
     * z p�aszczyzn kartezja�skiegu uk�adu wsp�rz�dnych OXY.
     * \param Min - zawiera wsp�rz�dne wierzcho�ka, kt�rego sk�adowe
     *              maj� minimalne warto�ci spo�r�d sk�adowych tego 
     *              samego typu wszyskich wierzcho�k�w
     *              tego prostopad�o�cianu.
     * \param Max - zawiera wsp�rz�dne wierzcho�ka, kt�rego sk�adowe
     *              maj� maksymalne warto�ci spo�r�d sk�adowych tego 
     *              samego typu wszyskich wierzcho�k�w
     *              tego prostopad�o�cianu.
     *              prostopad�o�cianu.
     * \return  true  - je�li punkt jest wewn�trz prostopad�o�cianu.
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
 *  Umo�liwia wy�wietlenie wsp�rz�dnych wektora.
 *  \param ostrm - strumien standaradowy,
 *  \param V - wektor, kt�rej wsp�rz�dne maj� zosta� wy�wietlone.
 */
template<typename TYPE>
inline
std::ostream & operator << ( std::ostream &ostrm, const Vector3<TYPE> &V)
{
  return ostrm << "(" << V.X() << ", " << V.Y() << ", " << V.Z() << ")";
}



#ifdef EXTSTRING_HH
/*!
 *  Umo�liwia wpisanie wsp�rz�dnych wektora bufora znakowego klasy ExtString.
 *  \param Buff - bufor znakowy,
 *  \param V - wektor, kt�rej wsp�rz�dne maj� zosta� wy�wietlone.
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
