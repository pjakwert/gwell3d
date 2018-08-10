#ifndef VIELEMEPOLYHEDGE_HH
#define VIELEMEPOLYHEDGE_HH

/*! \file vielemepolyhedge.hh
 *  Plik zawiera definicjê klasy ViElemePolyhEdge. Jest ona wykorzystywana
 *  jako klasa pomocnicza do iteracji krawêdzi bry³y elementarnej.
 *  Daje ona bezpo¶redni dostêp do opisu ¶cianek s±siaduj±cych z t± 
 *  krawêdzi± oraz wspó³rzêdnych wierzcho³ków w globalnym uk³adzie
 *  wspó³rzêdnych sceny.
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
 *  jako klasa pomocnicza do iteracji krawêdzi bry³y elementarnej.
 *  Daje ona bezpo¶redni dostêp do opisu ¶cianek s±siaduj±cych z t± 
 *  krawêdzi± oraz wspó³rzêdnych wierzcho³ków w globalnym uk³adzie
 *  wspó³rzêdnych sceny.
 *
 * Przyk³ad u¿ycia iteratora ViElemePolyh::ConEdgeIter :
 * \code
 *  // Szuka najd³u¿szej krawêdzi.
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
    *  Zawiera referencjê do obiektu reprezntuj±cego bry³ê elementarn±,
    *  do której nale¿y krawêd¼ reprezentowana przez niniejszy obiekt
    *  klasy ViElemePolyhEdge.
    */
   const ViElemePolyh  &_Owner;
   /*!
    *  Zawiera wska¼nik na krawêd¼ w opisie bry³y wzorcowej, której
    *  opis w uk³adzie wspó³rzêdnych globalnych ma byæ reprezentowany przez
    *  niniejszy obiekt klasy ViElemePolyhEdge.
    */
   const ViEdge  *_pEdge;
  public:
   /*!
    * Inicjalizuje obiekt referencj± do obiektu reprezentuj±cego
    * bry³ê elementarn± oraz wska¼nikiem do obiektu, który reprezentuje
    * jedn± z jego krawêdzi.
    * \param EPolyh - referencja do obiektu reprezntuj±cego wybran± 
    *                 bry³ê elementarn±,
    * \param pEdge - wska¼nik do obiektu reprezentuj±cego zadan± krawêd¼
    *                bry³y elementarnej, której opis udostêpnia
    *                \e EPolyh.
    * \pre  \f$ pEdge \ne NULL \f$.
    */
  ViElemePolyhEdge(const ViElemePolyh &EPolyh, const ViEdge *pEdge);

   /*!
    * Inicjalizuje obiekt referencj± do obiektu reprezentuj±cego
    * bry³ê elementarn± oraz wska¼nikiem do obiektu, który reprezentuje
    * jedn± z jego krawêdzi.
    * \param EPolyh - referencja do obiektu reprezntuj±cego wybran± 
    *                 bry³ê elementarn±,
    * \param Idx    - indeks zadanej krawêdzi
    *                bry³y elementarnej, której opis udostêpnia
    *                \e EPolyh.
    * \pre  \f$ pEdge \ne NULL \f$,  \f$ 0 \le Idx \le N_{edges}\f$
    */
  ViElemePolyhEdge(const ViElemePolyh &EPolyh, unsigned int Idx = 0);


   /*!
    * Kojarzy obiekt z now± krawêdzi± bry³y elementarnej.
    * \param pEdge - warto¶æ wska¼nika na now± krawêd¼.
    * \pre Krawêd¼ reprezentowana przez obiekt \e *pEdge musi
    *      nale¿eæ do bry³y wzorcowej, której odpowiada bry³a elementarna
    *      o opisie dostêpnym poprzez pole 
    *      \link ViElemePolyhEdge::_pEdge _pEdge\endlink.
    * \post Do pola 
    *      \link ViElemePolyhEdge::_pEdge _pEdge\endlink wpisana zostaje
    *      wska¼nik na now± krawêd¼ bry³y wzorcowej.
    */
   void SetEdge(const ViEdge *pEdge) { _pEdge = pEdge; }
   /*!
    * Udostêpnia wspó³rzêdne (w uk³adzie globalnym sceny) pierwszego 
    * wierzcho³ka krawêdzi.
    */
  const Vector3f &GetFstVtx() const;

   /*!
    * Udostêpnia wspó³rzêdne (w uk³adzie globalnym sceny) pierwszego 
    * wierzcho³ka krawêdzi.
    */
  const Vector3f &GetSndVtx() const;

   /*!
    * Udostêpnia wska¼nik do prawej ¶cianki. Strony lewo, prawo
    * rozró¿niane s± przy za³o¿eniu,
    * ¿e idziemy wzd³u¿ krawêdzi po zewnêtrznej
    * stronie powierzchni bry³y od pierwszego wierzcho³ka do drugiego.
    * \warning Nie ka¿da krawêd¼ musi mieæ dwóch s±siadów.
    * \return wska¼nik do prawej ¶cianki opisanej w uk³adzie wspó³rzêdnych
    *         globalnych sceny je¿eli krawêd¼ ma praw± ¶ciankê.
    *         W przypadku przeciwnym zwraca wska¼nik \p NULL.
    */
  ViElemePolyhFace const *GetRightFace() const;


   /*!
    * Udostêpnia wska¼nik do lewej ¶cianki. Strony lewo, prawo
    * rozró¿niane s± przy za³o¿eniu,
    * ¿e idziemy wzd³u¿ krawêdzi po zewnêtrznej
    * stronie powierzchni bry³y od pierwszego wierzcho³ka do drugiego.
    * \warning Nie ka¿da krawêd¼ musi mieæ dwóch s±siadów.
    * \return wska¼nik do lewej ¶cianki opisanej w uk³adzie wspó³rzêdnych
    *         globalnych sceny je¿eli krawêd¼ ma lew± ¶ciankê.
    *         W przypadku przeciwnym zwraca wska¼nik \p NULL.
    */
  ViElemePolyhFace const *GetLeftFace() const;

   /*!
    * Udostêpnia indeks lewej ¶cianki w tablicy
    * \link ViElemePolyh::_PolyhFaces _PolyhFaces\endlink
    *  w obiekcie klasy ViElemePolyh.
    */
  unsigned int GetLeftFaceIdx() const;

   /*!
    * Udostêpnia indeks prawej ¶cianki w tablicy
    * \link ViElemePolyh::_PolyhFaces _PolyhFaces\endlink
    *  w obiekcie klasy ViElemePolyh.
    */
  unsigned int GetRightFaceIdx() const;
};


/*!
 *  Umo¿liwia wy¶wietlenie wierzcho³ków krawêdzi oraz numerów lewej
 *  i prawej ¶cianki.
 *  \param ostrm - strumien standaradowy,
 *  \param Edge - krawed¼ bry³y elementarnej.
 * 
 *  Format wy¶wietlania:
 *
 *  [ (x1,y1,z1), (x2,y2,z2) ] [Idx1, Idx2]
 */
std::ostream &operator << (std::ostream &ostrm, ViElemePolyhEdge const &Edge);


#endif
