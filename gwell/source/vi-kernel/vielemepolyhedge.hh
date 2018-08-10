#ifndef VIELEMEPOLYHEDGE_HH
#define VIELEMEPOLYHEDGE_HH

/*! \file vielemepolyhedge.hh
 *  Plik zawiera definicj� klasy ViElemePolyhEdge. Jest ona wykorzystywana
 *  jako klasa pomocnicza do iteracji kraw�dzi bry�y elementarnej.
 *  Daje ona bezpo�redni dost�p do opisu �cianek s�siaduj�cych z t� 
 *  kraw�dzi� oraz wsp�rz�dnych wierzcho�k�w w globalnym uk�adzie
 *  wsp�rz�dnych sceny.
 *
 *  \author Bogdan Kreczmer
 *  \date   2004.12
 *  \version  1.00.00
 */


#ifdef __GNUG__
#pragma interface
#endif
#include <iostream>
#include "viedge.hh"

class ViElemePolyh;
class ViElemePolyhFace;


/*! 
 *  Jest ona wykorzystywana
 *  jako klasa pomocnicza do iteracji kraw�dzi bry�y elementarnej.
 *  Daje ona bezpo�redni dost�p do opisu �cianek s�siaduj�cych z t� 
 *  kraw�dzi� oraz wsp�rz�dnych wierzcho�k�w w globalnym uk�adzie
 *  wsp�rz�dnych sceny.
 *
 * Przyk�ad u�ycia iteratora ViElemePolyh::ConEdgeIter :
 * \code
 *  // Szuka najd�u�szej kraw�dzi.
 *  //
 * float SzukajNajdluzszej(const ViElemePolyh &PPolyh)
 * {
 *   int       d, d_max = 0;
 *   Vector3f  EVct;
 *
 *   for (ViElemePolyh::ConEdgeIter Iter = PPolyh.ConBegin_GlbEdge();
 *        Iter;  Iter++) {
 *     EVct = Iter->GetFstVtx()-Iter->GetFstVtx();
 *     if ( (d = EVct.Length()) > d_max ) d_max = d;
 *   }
 *   return d_max;
 * }
 * \endcode
 */
class ViElemePolyhEdge {
   /*!
    *  Zawiera referencj� do obiektu reprezntuj�cego bry�� elementarn�,
    *  do kt�rej nale�y kraw�d� reprezentowana przez niniejszy obiekt
    *  klasy ViElemePolyhEdge.
    */
   const ViElemePolyh  &_Owner;
   /*!
    *  Zawiera wska�nik na kraw�d� w opisie bry�y wzorcowej, kt�rej
    *  opis w uk�adzie wsp�rz�dnych globalnych ma by� reprezentowany przez
    *  niniejszy obiekt klasy ViElemePolyhEdge.
    */
   const ViEdge  *_pEdge;
  public:
   /*!
    * Inicjalizuje obiekt referencj� do obiektu reprezentuj�cego
    * bry�� elementarn� oraz wska�nikiem do obiektu, kt�ry reprezentuje
    * jedn� z jego kraw�dzi.
    * \param EPolyh - referencja do obiektu reprezntuj�cego wybran� 
    *                 bry�� elementarn�,
    * \param pEdge - wska�nik do obiektu reprezentuj�cego zadan� kraw�d�
    *                bry�y elementarnej, kt�rej opis udost�pnia
    *                \e EPolyh.
    * \pre  \f$ pEdge \ne NULL \f$.
    */
  ViElemePolyhEdge(const ViElemePolyh &EPolyh, const ViEdge *pEdge);

   /*!
    * Inicjalizuje obiekt referencj� do obiektu reprezentuj�cego
    * bry�� elementarn� oraz wska�nikiem do obiektu, kt�ry reprezentuje
    * jedn� z jego kraw�dzi.
    * \param EPolyh - referencja do obiektu reprezntuj�cego wybran� 
    *                 bry�� elementarn�,
    * \param Idx    - indeks zadanej kraw�dzi
    *                bry�y elementarnej, kt�rej opis udost�pnia
    *                \e EPolyh.
    * \pre  \f$ pEdge \ne NULL \f$,  \f$ 0 \le Idx \le N_{edges}\f$
    */
  ViElemePolyhEdge(const ViElemePolyh &EPolyh, unsigned int Idx = 0);


   /*!
    * Kojarzy obiekt z now� kraw�dzi� bry�y elementarnej.
    * \param pEdge - warto�� wska�nika na now� kraw�d�.
    * \pre Kraw�d� reprezentowana przez obiekt \e *pEdge musi
    *      nale�e� do bry�y wzorcowej, kt�rej odpowiada bry�a elementarna
    *      o opisie dost�pnym poprzez pole 
    *      \link ViElemePolyhEdge::_pEdge _pEdge\endlink.
    * \post Do pola 
    *      \link ViElemePolyhEdge::_pEdge _pEdge\endlink wpisana zostaje
    *      wska�nik na now� kraw�d� bry�y wzorcowej.
    */
   void SetEdge(const ViEdge *pEdge) { _pEdge = pEdge; }
   /*!
    * Udost�pnia wsp�rz�dne (w uk�adzie globalnym sceny) pierwszego 
    * wierzcho�ka kraw�dzi.
    */
  const Vector3f &GetFstVtx() const;

   /*!
    * Udost�pnia wsp�rz�dne (w uk�adzie globalnym sceny) pierwszego 
    * wierzcho�ka kraw�dzi.
    */
  const Vector3f &GetSndVtx() const;

   /*!
    * Udost�pnia wska�nik do prawej �cianki. Strony lewo, prawo
    * rozr�niane s� przy za�o�eniu,
    * �e idziemy wzd�u� kraw�dzi po zewn�trznej
    * stronie powierzchni bry�y od pierwszego wierzcho�ka do drugiego.
    * \warning Nie ka�da kraw�d� musi mie� dw�ch s�siad�w.
    * \return wska�nik do prawej �cianki opisanej w uk�adzie wsp�rz�dnych
    *         globalnych sceny je�eli kraw�d� ma praw� �ciank�.
    *         W przypadku przeciwnym zwraca wska�nik \p NULL.
    */
  ViElemePolyhFace const *GetRightFace() const;


   /*!
    * Udost�pnia wska�nik do lewej �cianki. Strony lewo, prawo
    * rozr�niane s� przy za�o�eniu,
    * �e idziemy wzd�u� kraw�dzi po zewn�trznej
    * stronie powierzchni bry�y od pierwszego wierzcho�ka do drugiego.
    * \warning Nie ka�da kraw�d� musi mie� dw�ch s�siad�w.
    * \return wska�nik do lewej �cianki opisanej w uk�adzie wsp�rz�dnych
    *         globalnych sceny je�eli kraw�d� ma lew� �ciank�.
    *         W przypadku przeciwnym zwraca wska�nik \p NULL.
    */
  ViElemePolyhFace const *GetLeftFace() const;

   /*!
    * Udost�pnia indeks lewej �cianki w tablicy
    * \link ViElemePolyh::_PolyhFaces _PolyhFaces\endlink
    *  w obiekcie klasy ViElemePolyh.
    */
  unsigned int GetLeftFaceIdx() const;

   /*!
    * Udost�pnia indeks prawej �cianki w tablicy
    * \link ViElemePolyh::_PolyhFaces _PolyhFaces\endlink
    *  w obiekcie klasy ViElemePolyh.
    */
  unsigned int GetRightFaceIdx() const;
};


/*!
 *  Umo�liwia wy�wietlenie wierzcho�k�w kraw�dzi oraz numer�w lewej
 *  i prawej �cianki.
 *  \param ostrm - strumien standaradowy,
 *  \param Edge - krawed� bry�y elementarnej.
 * 
 *  Format wy�wietlania:
 *
 *  [ (x1,y1,z1), (x2,y2,z2) ] [Idx1, Idx2]
 */
std::ostream &operator << (std::ostream &ostrm, ViElemePolyhEdge const &Edge);


#endif
