#ifndef OUTLINEBOX3_HH
#define OUTLINEBOX3_HH

/*!
 * \file outlinebox3.hh
 *  Plik zawiera definicjê szablonu klasy OutlineBox3. Wykorzystywana
 *  jest ona do wyznaczania prostopad³o¶ciennego obrysu bry³y lub zbioru
 *  bry³.
 *  \author Bogdan Kreczmer
 *  \date   2004.02
 */

#include <limits>
#include "vector3.hh"

/*!
 *  Wzorzec ten jest wykorzystywany do tworzenia prostopa³o¶ciennego
 *  obrysu bry³y lub zbiorów bry³. Prostopad³o¶cian jest tworzony
 *  w ten sposób, ¿e jego poszczególne ¶ciany równoleg³e s± 
 *  do jednej z p³aszczyzn OXY, OXZ lub OYX.
 */
template <class TYPE>
class  OutlineBox3 { 
  protected:
   /*!
    * Zawiera wspó³rzêdne wierzcho³ka prostopad³o¶ciennego obrysu,
    * którego warto¶ci wspó³rzêdnych
    * wzd³u¿ poszczególnych osi s± najmniejsze spo¶ród
    * wszystkich jego wierzcho³ków. Wierzcho³ek ten okre¶lany jest
    * w tym opisie jako skrajny dolny.
    */
   Vector3<TYPE> _OutMin;
   /*!
    * Zawiera wspó³rzêdne wierzcho³ka prostopad³o¶ciennego obrysu,
    * którego warto¶ci wspó³rzêdnych
    * wzd³u¿ poszczególnych osi s± najwiêkszymi spo¶ród
    * wszystkich jego wierzcho³ków. Wierzcho³ek ten okre¶lany jest
    * w tym opisie jako skrajny dolny.
    */
   Vector3<TYPE> _OutMax;

  public:

   /*!
    *  Inicjalizuje pola \link OutlineBox3::_OutMin _OutMin\endlink i
    *  \link OutlineBox3::_OutMax _OutMax\endlink warto¶ciami 
    *  odpowiednio najmniejszymi i najmniejszymi w³a¶ciwymi dla danego
    *  typu. W ten sposób utworzony prostopad³o¶cian interpretowany jest
    *  jako pusty.
    */
   void Init() {
      _OutMin.Set(numeric_limits<TYPE>::max());
      _OutMax.Set(-numeric_limits<TYPE>::max());
   }

    /*!
     *  Inicjalizuje prostopad³o¶cienny obrys jako pusty.
     */
   OutlineBox3(){ Init(); }

    /*!
     *  Inicjalizuje prostopad³o¶cienny obrys danymi z innego obrysu
     *  udostêpnionego poprzez parametr.
     *  \param  pOln - wska¼nik na prostopad³o¶cienny obrys, którego
     *                 danymi inicjalizowany jest powstaj±cy obiekt.
     */
   OutlineBox3(OutlineBox3 const *pOln): 
                   _OutMin(pOln->_OutMin), _OutMax(pOln->_OutMax) {}
   /*!
    *  Udostêpnia wspó³rzêdne skrajnego górnego wierzcho³ka 
    *  prostopad³o¶ciennego obrysu (pole 
    *   \link OutlineBox3::_OutMax _OutMax\endlink).
    */
   Vector3<TYPE> const &Max() const { return _OutMax; }
   /*!
    *  Udostêpnia wspó³rzêdne skrajnego górnego wierzcho³ka 
    *  prostopad³o¶ciennego obrysu (pole 
    *   \link OutlineBox3::_OutMax _OutMax\endlink). Wspó³rzêdne
    *  te udostêpniane s± jako modyfikowalne.
    */
   Vector3<TYPE>  &Max() { return _OutMax; }
   /*!
    *  Udostêpnia wspó³rzêdne skrajnego dolnego wierzcho³ka 
    *  prostopad³o¶ciennego obrysu (pole 
    *   \link OutlineBox3::_OutMin _OutMin\endlink).
    */
   Vector3<TYPE> const &Min() const { return _OutMin; }
   /*!
    *  Udostêpnia wspó³rzêdne skrajnego górnego wierzcho³ka 
    *  prostopad³o¶ciennego obrysu (pole 
    *   \link OutlineBox3::_OutMin _OutMin\endlink). Wspó³rzêdne
    *  te udostêpniane s± jako modyfikowalne.
    */
   Vector3<TYPE>  &Min() { return _OutMin; }

    /*!
     *  Inicjalizuje prostopad³o¶cienny obrys danymi z innego obrysu
     *  udostêpnionego poprzez parametr.
     *  \param  Oln - zawiera prostopad³o¶cienny obrys, którego
     *                 dane przepisywane s± do tego obiektu.
     */
   void Init(OutlineBox3<TYPE> const &Oln) {
      _OutMin =  Oln._OutMin;  _OutMin = Oln._OutMax;
   }
    /*!
     *  Przepisuje do wspó³rzêdnych skrajnego dolnego 
     *  (pole \link OutlineBox3::_OutMin _OutMin\endlink) i skrajnego
     *  górnego wierzcho³ka obrysu 
     *  (pole \link OutlineBox3::_OutMax _OutMax\endlink) wspó³rzêdne
     *  podanego punktu.
     *  \param Pnt  - wspó³rzêdne punktu, które maj± byæ podstawione
     *             do wspó³rzêdnych skrajengo dolnego i górnego wierzcho³ka
     *             obrysu.
     */
   void Init(Vector3<TYPE> const &Pnt) {
       _OutMin = _OutMax = Pnt;
   }

   /*!
    *  Jest to wywo³anie metody \link OutlineBox3::Init Init\endlink
    *  bez zadnych parameterów.
    *
    *  Inicjalizuje pola \link OutlineBox3::_OutMin _OutMin\endlink i
    *  \link OutlineBox3::_OutMax _OutMax\endlink warto¶ciami 
    *  odpowiednio najmniejszymi i najmniejszymi w³a¶ciwymi dla danego
    *  typu. W ten sposób utworzony prostopad³o¶cian interpretowany jest
    *  jako pusty.
    */
   void Reset() { Init(); }
   /*!
    *  Dla obrysu prostopad³o¶ciennego i punktu tworzy nowy 
    *  najmniejszy obrys zwieraj±cy oba te elementy.
    *  \param Pnt - wspó³rzêdne punktu, który ma byæ w³±czony do
    *               nowego obrysu.
    *  \post Zostaj± zaktualizowane wspó³rzêdne w polach 
    *  \link OutlineBox3::_OutMin _OutMin\endlink i 
    *  \link OutlineBox3::_OutMax _OutMax\endlink, tak aby tworzy³y
    *  nowy obrys zawieraj±cy obrys wcze¶niejszy i punkt \e Pnt.
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
    *  Dla obrysu prostopad³o¶ciennego i obrysu, którego dane przekazane
    *  s± poprzez parametr wywo³ania tej metody tworzy nowy 
    *  najmniejszy obrys zwieraj±cy oba te elementy.
    *  \param Oln - obrys prostopad³o¶cienny, dla który w po³±czeniu z 
    *          obrysem z obiektu \b *this ma byæ utworzony jeden wspólny
    *          obrys.
    *  \post Zostaj± zaktualizowane wspó³rzêdne w polach 
    *  \link OutlineBox3::_OutMin _OutMin\endlink i 
    *  \link OutlineBox3::_OutMax _OutMax\endlink, tak aby tworzy³y
    *  nowy obrys zawieraj±cy obrys wcze¶niejszy i obrys  \e Oln.
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
     *  Sprawdza czy dane dwa obrysy maj± wspóln± czê¶æ wnêtrza.
     *  \param Oln - obrys, dla którego bêdzie sprawdzane czy ma on
     *               wspóln± czê¶æ z obrysem przechowywanym w obiekcie
     *               \b *this.
     *  \retval true - je¶li obrysy maj± wspóln± czê¶æ wnêtrza,
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
