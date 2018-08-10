#ifndef OUTLINEBOX3_HH
#define OUTLINEBOX3_HH

/*!
 * \file outlinebox3.hh
 *  Plik zawiera definicj� szablonu klasy OutlineBox3. Wykorzystywana
 *  jest ona do wyznaczania prostopad�o�ciennego obrysu bry�y lub zbioru
 *  bry�.
 *  \author Bogdan Kreczmer
 *  \date   2004.02
 */

#include <limits>
#include "vector3.hh"

/*!
 *  Wzorzec ten jest wykorzystywany do tworzenia prostopa�o�ciennego
 *  obrysu bry�y lub zbior�w bry�. Prostopad�o�cian jest tworzony
 *  w ten spos�b, �e jego poszczeg�lne �ciany r�wnoleg�e s� 
 *  do jednej z p�aszczyzn OXY, OXZ lub OYX.
 */
template <class TYPE>
class  OutlineBox3 { 
  protected:
   /*!
    * Zawiera wsp�rz�dne wierzcho�ka prostopad�o�ciennego obrysu,
    * kt�rego warto�ci wsp�rz�dnych
    * wzd�u� poszczeg�lnych osi s� najmniejsze spo�r�d
    * wszystkich jego wierzcho�k�w. Wierzcho�ek ten okre�lany jest
    * w tym opisie jako skrajny dolny.
    */
   Vector3<TYPE> _OutMin;
   /*!
    * Zawiera wsp�rz�dne wierzcho�ka prostopad�o�ciennego obrysu,
    * kt�rego warto�ci wsp�rz�dnych
    * wzd�u� poszczeg�lnych osi s� najwi�kszymi spo�r�d
    * wszystkich jego wierzcho�k�w. Wierzcho�ek ten okre�lany jest
    * w tym opisie jako skrajny dolny.
    */
   Vector3<TYPE> _OutMax;

  public:

   /*!
    *  Inicjalizuje pola \link OutlineBox3::_OutMin _OutMin\endlink i
    *  \link OutlineBox3::_OutMax _OutMax\endlink warto�ciami 
    *  odpowiednio najmniejszymi i najmniejszymi w�a�ciwymi dla danego
    *  typu. W ten spos�b utworzony prostopad�o�cian interpretowany jest
    *  jako pusty.
    */
   void Init() {
      _OutMin.Set(numeric_limits<TYPE>::max());
      _OutMax.Set(-numeric_limits<TYPE>::max());
   }

    /*!
     *  Inicjalizuje prostopad�o�cienny obrys jako pusty.
     */
   OutlineBox3(){ Init(); }

    /*!
     *  Inicjalizuje prostopad�o�cienny obrys danymi z innego obrysu
     *  udost�pnionego poprzez parametr.
     *  \param  pOln - wska�nik na prostopad�o�cienny obrys, kt�rego
     *                 danymi inicjalizowany jest powstaj�cy obiekt.
     */
   OutlineBox3(OutlineBox3 const *pOln): 
                   _OutMin(pOln->_OutMin), _OutMax(pOln->_OutMax) {}
   /*!
    *  Udost�pnia wsp�rz�dne skrajnego g�rnego wierzcho�ka 
    *  prostopad�o�ciennego obrysu (pole 
    *   \link OutlineBox3::_OutMax _OutMax\endlink).
    */
   Vector3<TYPE> const &Max() const { return _OutMax; }
   /*!
    *  Udost�pnia wsp�rz�dne skrajnego g�rnego wierzcho�ka 
    *  prostopad�o�ciennego obrysu (pole 
    *   \link OutlineBox3::_OutMax _OutMax\endlink). Wsp�rz�dne
    *  te udost�pniane s� jako modyfikowalne.
    */
   Vector3<TYPE>  &Max() { return _OutMax; }
   /*!
    *  Udost�pnia wsp�rz�dne skrajnego dolnego wierzcho�ka 
    *  prostopad�o�ciennego obrysu (pole 
    *   \link OutlineBox3::_OutMin _OutMin\endlink).
    */
   Vector3<TYPE> const &Min() const { return _OutMin; }
   /*!
    *  Udost�pnia wsp�rz�dne skrajnego g�rnego wierzcho�ka 
    *  prostopad�o�ciennego obrysu (pole 
    *   \link OutlineBox3::_OutMin _OutMin\endlink). Wsp�rz�dne
    *  te udost�pniane s� jako modyfikowalne.
    */
   Vector3<TYPE>  &Min() { return _OutMin; }

    /*!
     *  Inicjalizuje prostopad�o�cienny obrys danymi z innego obrysu
     *  udost�pnionego poprzez parametr.
     *  \param  Oln - zawiera prostopad�o�cienny obrys, kt�rego
     *                 dane przepisywane s� do tego obiektu.
     */
   void Init(OutlineBox3<TYPE> const &Oln) {
      _OutMin =  Oln._OutMin;  _OutMin = Oln._OutMax;
   }
    /*!
     *  Przepisuje do wsp�rz�dnych skrajnego dolnego 
     *  (pole \link OutlineBox3::_OutMin _OutMin\endlink) i skrajnego
     *  g�rnego wierzcho�ka obrysu 
     *  (pole \link OutlineBox3::_OutMax _OutMax\endlink) wsp�rz�dne
     *  podanego punktu.
     *  \param Pnt  - wsp�rz�dne punktu, kt�re maj� by� podstawione
     *             do wsp�rz�dnych skrajengo dolnego i g�rnego wierzcho�ka
     *             obrysu.
     */
   void Init(Vector3<TYPE> const &Pnt) {
       _OutMin = _OutMax = Pnt;
   }

   /*!
    *  Jest to wywo�anie metody \link OutlineBox3::Init Init\endlink
    *  bez zadnych parameter�w.
    *
    *  Inicjalizuje pola \link OutlineBox3::_OutMin _OutMin\endlink i
    *  \link OutlineBox3::_OutMax _OutMax\endlink warto�ciami 
    *  odpowiednio najmniejszymi i najmniejszymi w�a�ciwymi dla danego
    *  typu. W ten spos�b utworzony prostopad�o�cian interpretowany jest
    *  jako pusty.
    */
   void Reset() { Init(); }
   /*!
    *  Dla obrysu prostopad�o�ciennego i punktu tworzy nowy 
    *  najmniejszy obrys zwieraj�cy oba te elementy.
    *  \param Pnt - wsp�rz�dne punktu, kt�ry ma by� w��czony do
    *               nowego obrysu.
    *  \post Zostaj� zaktualizowane wsp�rz�dne w polach 
    *  \link OutlineBox3::_OutMin _OutMin\endlink i 
    *  \link OutlineBox3::_OutMax _OutMax\endlink, tak aby tworzy�y
    *  nowy obrys zawieraj�cy obrys wcze�niejszy i punkt \e Pnt.
    */
   void Join(Vector3<TYPE> const &Pnt)
    { // Koniecznie trzeba sprawdzac podwojnie dla Min i Max
       if (Pnt.x<_OutMin.x) _OutMin.x=Pnt.x;
       if (Pnt.x>_OutMax.x) _OutMax.x=Pnt.x;
       if (Pnt.y<_OutMin.y) _OutMin.y=Pnt.y;
       if (Pnt.y>_OutMax.y) _OutMax.y=Pnt.y;
       if (Pnt.z<_OutMin.z) _OutMin.z=Pnt.z;
       if (Pnt.z>_OutMax.z) _OutMax.z=Pnt.z;
     }
   /*!
    *  Dla obrysu prostopad�o�ciennego i obrysu, kt�rego dane przekazane
    *  s� poprzez parametr wywo�ania tej metody tworzy nowy 
    *  najmniejszy obrys zwieraj�cy oba te elementy.
    *  \param Oln - obrys prostopad�o�cienny, dla kt�ry w po��czeniu z 
    *          obrysem z obiektu \b *this ma by� utworzony jeden wsp�lny
    *          obrys.
    *  \post Zostaj� zaktualizowane wsp�rz�dne w polach 
    *  \link OutlineBox3::_OutMin _OutMin\endlink i 
    *  \link OutlineBox3::_OutMax _OutMax\endlink, tak aby tworzy�y
    *  nowy obrys zawieraj�cy obrys wcze�niejszy i obrys  \e Oln.
    */
   void Join( OutlineBox3<TYPE> const &Oln )
            { if (_OutMin.x > Oln._OutMin.x)  _OutMin.x = Oln._OutMin.x;
              if (_OutMin.y > Oln._OutMin.y)  _OutMin.y = Oln._OutMin.y;
              if (_OutMin.z > Oln._OutMin.z)  _OutMin.z = Oln._OutMin.z;
              if (_OutMax.x < Oln._OutMax.x)  _OutMax.x = Oln._OutMax.x;
              if (_OutMax.y < Oln._OutMax.y)  _OutMax.y = Oln._OutMax.y;
              if (_OutMax.z < Oln._OutMax.z)  _OutMax.z = Oln._OutMax.z;
            }
    /*!
     *  Sprawdza czy dane dwa obrysy maj� wsp�ln� cz�� wn�trza.
     *  \param Oln - obrys, dla kt�rego b�dzie sprawdzane czy ma on
     *               wsp�ln� cz�� z obrysem przechowywanym w obiekcie
     *               \b *this.
     *  \retval true - je�li obrysy maj� wsp�ln� cz�� wn�trza,
     *  \retval false - w przypadku przeciwnym.
     */
   bool IsCommonPart( OutlineBox3<TYPE> const &Oln ) const
           { return !((_OutMax.x <= Oln._OutMin.x) ||
                      (_OutMin.x >= Oln._OutMax.x) ||
                      (_OutMax.y <= Oln._OutMin.y) ||
                      (_OutMin.y >= Oln._OutMax.y) ||
                      (_OutMax.z <= Oln._OutMin.z) ||
                      (_OutMin.z >= Oln._OutMax.z));
           }

};



template <class TYPE>
inline
ostream &operator << (ostream &ostrm, OutlineBox3<TYPE> const &Box)
{
  return ostrm << Box.Min() << " " << Box.Max();
}

#endif
