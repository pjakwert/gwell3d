#ifndef EDGEITERATOR_H
#define EDGEITERATOR_H

/*!  
 *  \file viedgeiterator.hh
 *  \author  Bogdan Kreczmer
 *  \date    2004.02
 *  Plik zawiera definicj� klasy \link ViEdgeIterator ViEdgeIterator\endlink
 *  umo�liwiaj�cej przechodzedzenie po kolejnych kraw�dziach bry�y.
 */



#ifdef __GNUG__
#pragma interface
#endif


class ViEdge;

/*!
 *  Klasa ViEdgeIterotor jest iteratorem kraw�dzi. 
 *  Jest to jednak konstrukcja przestarza�a i przeznaczona do usuni�cia.
 *  Z tych te� wzgl�d�w nie nale�y jej wykorzystywa�.
 *  Odpowiednie iteratory kraw�dzi znale�� mo�na np. w klasie 
 *  ViPattePolyh.
 * 
 *  Przyk�ad wykorzystania niniejszej klasy mo�na znalez� w 
 *  metodzie ViFace::GetEdge.
 */
class ViEdgeIterator {
   /*!
    *   Pole prechowuje ilo�� kraw�dzi.
    */
   unsigned int _EdgesNo;
   /*!
    *  Zawiera wska�nik na tablic� kraw�dzi.
    */
   ViEdge  *_EdgeTab;
    /*!
     *  Wska�nik roboczy, kt�ry zmienia si� w trakcie iteracji
     *  wskazuj�c na poszczeg�lne elementy tablicy.
     */
   ViEdge  *_WrkEdge; 
    /*!
     * Status ostatniej operacji (in/de)krementacji.
     */
   bool       _OpStatus;  

  public:
   /*!
    *  Inicjalizuje iteratator kojarz�c go z ��dan� tablic�.
    *  \param No - ilo�� kraw�dzi.
    *  \param Tab - wska�nik na tablic� kraw�dzi.
    */
   ViEdgeIterator(unsigned int No, ViEdge *Tab);
   /*!
    *  Udost�pnia status ostatniej operacji.
    */
   operator bool () const { return _OpStatus; }
   /*!
    *  Wykonuje operacj� dekrementacji, o ile nie doprowadzi ona
    *  do przekroczenia zakresu tablicy.
    *  \post Status operacji zapisany zostaje w polu
    *  \link ViEdgeIterator::_OpStatus _OpStatus\endlink.
    */
   ViEdgeIterator &operator -- ();
   /*!
    *  Wykonuje operacj� inkrementacji, o ile nie doprowadzi ona
    *  do przekroczenia zakresu tablicy.
    *  \post Status operacji zapisany zostaje w polu
    *  \link ViEdgeIterator::_OpStatus _OpStatus\endlink.
    */
   ViEdgeIterator &operator ++ ();
   /*!
    *  Udost�pnia wska�nik do iterowanej kraw�dzi.
    */
   operator ViEdge* () const { return _WrkEdge; }
   /*!
    *  Udost�pnia wska�nik do iterowanej kraw�dzi.
    */
   ViEdge *operator () () const { return _WrkEdge; }
   /*!
    *  Udost�pnia indeks iterowanej kraw�dzi.
    */
   int Index() const;
   /*!
    *  Sprowadza interator do stanu pocz�tkowego.
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
