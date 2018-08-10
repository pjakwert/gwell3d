#ifndef VIFACEEDGE_HH
#define VIFACEEDGE_HH

/*!
 * \file  vifaceedge.hh
 * \author	Bogdan Kreczmer
 * \date	2003.03.23
 *
 * Plik zawiera definicjê klasy \link ViFaceEdge ViFaceEdge\endlink
 * modeluj±cej krawêdzie zwi±zane z dan± ¶ciank± i maj±ce w³a¶ciw±
 * orientacjê wzglêdem tej ¶cianki. Czego nie gwarantuj± obiekty
 * klasy ViEdge.
 *
 */



#ifdef __GNUG__
#pragma interface
#endif


#include <iostream>
#include "vector3f.hh"

class ViFace;

/*!
 * Klasa zwiera opis krawêdzi danej ¶cianki z uwzglêdnieniem
 * jej prawid³owej orientacji wzglêdem brzegu ¶cianki
 * Przyjmuje siê, ¿e orientacja brzegu ¶cianki jest zgodna 
 * z ruchem wskazówek zegara.
 */
class ViFaceEdge {
   /*!
    * Pole zawiera referencjê do ¶cianki bry³y wzorcowej, do której
    * to ¶cianki nale¿y dana krawêd¼.
    */
   const ViFace   &_Owner;  
   const Vector3f &_FstVtx; /*!< Pierwszy wierzcho³ek krawêdzi. */
   const Vector3f &_SndVtx; /*!< Drugi wierzcho³ek krawêdzi.    */
    /*!
     * Indeks wspó³rzêdnych pierwszego wierzcho³ka w tablicy
     *  ViPattePolyh::_Vertex.
     */
   unsigned int _FstIdx;
    /*!
     * Numer drugiego wierzcho³ka w tablicy
     * \link ViPattePolyh::_Vertex  ViPattePolyh::_Vertex\endlink.
     */
   unsigned int _SndIdx;
    /*!
     *  Wska¼nik na drug± ¶ciankê, z która s±siaduje krawêd¼.
     *  Je¶li ¶cianka ta nie istnieje, to warto¶ci± pola jest adres
     *  \p NULL.
     */
   const ViFace   *_pNeighborFace; 
    /*!
     *  Pole zawiera indeks ¶cianki, z która s±siaduje krawêd¼.
     *  ¦cianka ta nie musi istnieæ.
     */
   unsigned int  _NeighborFaceIdx;
  public:
    /*!
     * Inicjalizuje obiekt referencjami do poszczególnych pól.
     * \param Owner - referencja do ¶cianki, do której nale¿y ta krawêd¼,
     * \param FstVtx - pierwszy wierzcho³ek krawêdzi,
     * \param FstIdx - indeks pierwszego wierzcho³ka krawêdzi w tablicy
     *          \link ViPattePolyh::_Vertex  ViPattePolyh::_Vertex\endlink.
     * \param SndVtx - drugi wierzcho³ek krawêdzi,
     * \param SndIdx - indeks drugiego wierzcho³ka krawêdzi w tablicy
     *          \link ViPattePolyh::_Vertex  ViPattePolyh::_Vertex\endlink.
     * \param pNeighbor - wska¼nik na ¶ciankê, z któr± s±siaduje ta krawêd¼
     *                    (¶cianka ta nie musi istnieæ),
     * \param NeighborIdx - indeks s±siaduj±cej ¶cianki. Warto¶æ indeksu
     *            odnosi siê do tablicy 
     *          \link ViPattePolyh::_Faces  ViPattePolyh::_Faces\endlink.
     */
   ViFaceEdge( const ViFace    &Owner, 
               const Vector3f  &FstVtx, 
               unsigned int     FstIdx,
               const Vector3f  &SndVtx,
               unsigned int     SndIdx,
               const ViFace    *pNeighbor = 0L,
               unsigned int     NeighborIdx = 0
            ):  _Owner(Owner), _FstVtx(FstVtx), 
               _SndVtx(SndVtx), _pNeighborFace(pNeighbor) 
      { _FstIdx = FstIdx;  _SndIdx = SndIdx; _NeighborFaceIdx = NeighborIdx; }

   /*!
    * Udostêpnia referencjê do ¶cianki, której czê¶ci± jest ta krawêd¼.
    */
   const ViFace &GetFace() const { return _Owner; }
   /*!
    * Udostêpnia referencjê do ¶cianki, z której krawêd¼ ta s±siaduje.
    */
   const ViFace *GetNeighborFace() const { return _pNeighborFace; }
   /*!
    * Udostêpnia indeks ¶cianki, z której krawêd¼ ta s±siaduje.
    * Warto¶æ indeksu odnosi siê do tablicy 
    *   \link ViPattePolyh::_Faces  ViPattePolyh::_Faces\endlink.
    */
   unsigned int GetNeighborIdx() const { return _NeighborFaceIdx; }
   /*!
    * Referencja do pierwszego wierzcho³ka krawêdzi.
    */
   const Vector3f &GetFstVtx() const { return _FstVtx; }
   /*!
    * Referencja do drugiego wierzcho³ka krawêdzi.
    */
   const Vector3f &GetSndVtx() const { return _SndVtx; }
   /*!
    * Udostêpnia indeks pierwszego wierzcho³ka krawêdzi
    * w tablicy
    * \link ViPattePolyh::_Vertex  ViPattePolyh::_Vertex\endlink.
    */
   unsigned int GetFstVtxIdx() const { return _FstIdx; }
   /*!
    * Udostêpnia indeks drugiego wierzcho³ka krawêdzi.
    * \link ViPattePolyh::_Vertex  ViPattePolyh::_Vertex\endlink.
    */
   unsigned int GetSndVtxIdx() const { return _SndIdx; }
   /*!
    * Udostêpnia wektor normalny ¶cianki, do której nale¿y.
    */
   const Vector3f &FaceNormVect() const;

   /*!
    * Udostêpnia wektor normalny ¶cianki s±siedniej. W przypadku,
    * gdy nie ma s±siedniej ¶cianki zwracany jest wektor zerowy.
    */
   Vector3f FaceNormVect_Neighbor() const;

   /*! 
    * Metoda umo¿liwia okre¶lenie czy krawêd¼ jest widoczna
    * z danego kierunku patrzenia. Metoda przeznaczona jest tylko
    * do rysowania miniaturek figur wzorcowych. Nie ma zastosowania
    * w przypadku rysowania w uk³adzie wspó³rzêdnych globalnych.
    * \param ViewVct - wektor kierunku patrzenia. Wektor skierowany
    *                  jest od oka w kierunku przedmiotu.
    * \retval true - je¶li krawêd¼ jest widoczna,
    * \retval false - w przypadku przeciwnym.
    */
   bool IsVisible(const Vector3f &ViewVct) const 
     { return sgn(FaceNormVect() & ViewVct) == -1 ||
              sgn(FaceNormVect_Neighbor() & ViewVct) == -1; }
};


/*!
 *  Wy¶wietla informacje dotycz±ce danej krawêdzi (wspó³rzêdne pierwszego
 *  i drugiego wierzcho³ka).
 */
std::ostream &operator  << (std::ostream &ostrm, ViFaceEdge const &EFace);

#endif
