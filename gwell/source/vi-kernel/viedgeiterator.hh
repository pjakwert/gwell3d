#ifndef EDGEITERATOR_H
#define EDGEITERATOR_H

/*!  
 *  \file viedgeiterator.hh
 *  \author  Bogdan Kreczmer
 *  \date    2004.02
 *  Plik zawiera definicjê klasy \link ViEdgeIterator ViEdgeIterator\endlink
 *  umo¿liwiaj±cej przechodzedzenie po kolejnych krawêdziach bry³y.
 */



#ifdef __GNUG__
#pragma interface
#endif


class ViEdge;

/*!
 *  Klasa ViEdgeIterotor jest iteratorem krawêdzi. 
 *  Jest to jednak konstrukcja przestarza³a i przeznaczona do usuniêcia.
 *  Z tych te¿ wzglêdów nie nale¿y jej wykorzystywaæ.
 *  Odpowiednie iteratory krawêdzi znale¼æ mo¿na np. w klasie 
 *  ViPattePolyh.
 * 
 *  Przyk³ad wykorzystania niniejszej klasy mo¿na znalezæ w 
 *  metodzie ViFace::GetEdge.
 */
class ViEdgeIterator {
   /*!
    *   Pole prechowuje ilo¶æ krawêdzi.
    */
   unsigned int _EdgesNo;
   /*!
    *  Zawiera wska¼nik na tablicê krawêdzi.
    */
   ViEdge  *_EdgeTab;
    /*!
     *  Wska¼nik roboczy, który zmienia siê w trakcie iteracji
     *  wskazuj±c na poszczególne elementy tablicy.
     */
   ViEdge  *_WrkEdge; 
    /*!
     * Status ostatniej operacji (in/de)krementacji.
     */
   bool       _OpStatus;  

  public:
   /*!
    *  Inicjalizuje iteratator kojarz±c go z ¿±dan± tablic±.
    *  \param No - ilo¶æ krawêdzi.
    *  \param Tab - wska¼nik na tablicê krawêdzi.
    */
   ViEdgeIterator(unsigned int No, ViEdge *Tab);
   /*!
    *  Udostêpnia status ostatniej operacji.
    */
   operator bool () const { return _OpStatus; }
   /*!
    *  Wykonuje operacjê dekrementacji, o ile nie doprowadzi ona
    *  do przekroczenia zakresu tablicy.
    *  \post Status operacji zapisany zostaje w polu
    *  \link ViEdgeIterator::_OpStatus _OpStatus\endlink.
    */
   ViEdgeIterator &operator -- ();
   /*!
    *  Wykonuje operacjê inkrementacji, o ile nie doprowadzi ona
    *  do przekroczenia zakresu tablicy.
    *  \post Status operacji zapisany zostaje w polu
    *  \link ViEdgeIterator::_OpStatus _OpStatus\endlink.
    */
   ViEdgeIterator &operator ++ ();
   /*!
    *  Udostêpnia wska¼nik do iterowanej krawêdzi.
    */
   operator ViEdge* () const { return _WrkEdge; }
   /*!
    *  Udostêpnia wska¼nik do iterowanej krawêdzi.
    */
   ViEdge *operator () () const { return _WrkEdge; }
   /*!
    *  Udostêpnia indeks iterowanej krawêdzi.
    */
   int Index() const;
   /*!
    *  Sprowadza interator do stanu pocz±tkowego.
    */
   void Reset() { _WrkEdge = _EdgeTab; }
};


inline
ViEdgeIterator::ViEdgeIterator(unsigned int No, ViEdge *Tab):
  _EdgesNo(No-1), _EdgeTab(Tab), _WrkEdge(Tab)
{ 
 _OpStatus = _EdgeTab != 0L; 
}

#endif
