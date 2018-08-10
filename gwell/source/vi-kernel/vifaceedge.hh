#ifndef VIFACEEDGE_HH
#define VIFACEEDGE_HH

/*!
 * \file  vifaceedge.hh
 * \author	Bogdan Kreczmer
 * \date	2003.03.23
 *
 * Plik zawiera definicj� klasy \link ViFaceEdge ViFaceEdge\endlink
 * modeluj�cej kraw�dzie zwi�zane z dan� �ciank� i maj�ce w�a�ciw�
 * orientacj� wzgl�dem tej �cianki. Czego nie gwarantuj� obiekty
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
 * Klasa zwiera opis kraw�dzi danej �cianki z uwzgl�dnieniem
 * jej prawid�owej orientacji wzgl�dem brzegu �cianki
 * Przyjmuje si�, �e orientacja brzegu �cianki jest zgodna 
 * z ruchem wskaz�wek zegara.
 */
class ViFaceEdge {
   /*!
    * Pole zawiera referencj� do �cianki bry�y wzorcowej, do kt�rej
    * to �cianki nale�y dana kraw�d�.
    */
   const ViFace   &_Owner;  
   const Vector3f &_FstVtx; /*!< Pierwszy wierzcho�ek kraw�dzi. */
   const Vector3f &_SndVtx; /*!< Drugi wierzcho�ek kraw�dzi.    */
    /*!
     * Indeks wsp�rz�dnych pierwszego wierzcho�ka w tablicy
     *  ViPattePolyh::_Vertex.
     */
   unsigned int _FstIdx;
    /*!
     * Numer drugiego wierzcho�ka w tablicy
     * \link ViPattePolyh::_Vertex  ViPattePolyh::_Vertex\endlink.
     */
   unsigned int _SndIdx;
    /*!
     *  Wska�nik na drug� �ciank�, z kt�ra s�siaduje kraw�d�.
     *  Je�li �cianka ta nie istnieje, to warto�ci� pola jest adres
     *  \p NULL.
     */
   const ViFace   *_pNeighborFace; 
    /*!
     *  Pole zawiera indeks �cianki, z kt�ra s�siaduje kraw�d�.
     *  �cianka ta nie musi istnie�.
     */
   unsigned int  _NeighborFaceIdx;
  public:
    /*!
     * Inicjalizuje obiekt referencjami do poszczeg�lnych p�l.
     * \param Owner - referencja do �cianki, do kt�rej nale�y ta kraw�d�,
     * \param FstVtx - pierwszy wierzcho�ek kraw�dzi,
     * \param FstIdx - indeks pierwszego wierzcho�ka kraw�dzi w tablicy
     *          \link ViPattePolyh::_Vertex  ViPattePolyh::_Vertex\endlink.
     * \param SndVtx - drugi wierzcho�ek kraw�dzi,
     * \param SndIdx - indeks drugiego wierzcho�ka kraw�dzi w tablicy
     *          \link ViPattePolyh::_Vertex  ViPattePolyh::_Vertex\endlink.
     * \param pNeighbor - wska�nik na �ciank�, z kt�r� s�siaduje ta kraw�d�
     *                    (�cianka ta nie musi istnie�),
     * \param NeighborIdx - indeks s�siaduj�cej �cianki. Warto�� indeksu
     *            odnosi si� do tablicy 
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
    * Udost�pnia referencj� do �cianki, kt�rej cz�ci� jest ta kraw�d�.
    */
   const ViFace &GetFace() const { return _Owner; }
   /*!
    * Udost�pnia referencj� do �cianki, z kt�rej kraw�d� ta s�siaduje.
    */
   const ViFace *GetNeighborFace() const { return _pNeighborFace; }
   /*!
    * Udost�pnia indeks �cianki, z kt�rej kraw�d� ta s�siaduje.
    * Warto�� indeksu odnosi si� do tablicy 
    *   \link ViPattePolyh::_Faces  ViPattePolyh::_Faces\endlink.
    */
   unsigned int GetNeighborIdx() const { return _NeighborFaceIdx; }
   /*!
    * Referencja do pierwszego wierzcho�ka kraw�dzi.
    */
   const Vector3f &GetFstVtx() const { return _FstVtx; }
   /*!
    * Referencja do drugiego wierzcho�ka kraw�dzi.
    */
   const Vector3f &GetSndVtx() const { return _SndVtx; }
   /*!
    * Udost�pnia indeks pierwszego wierzcho�ka kraw�dzi
    * w tablicy
    * \link ViPattePolyh::_Vertex  ViPattePolyh::_Vertex\endlink.
    */
   unsigned int GetFstVtxIdx() const { return _FstIdx; }
   /*!
    * Udost�pnia indeks drugiego wierzcho�ka kraw�dzi.
    * \link ViPattePolyh::_Vertex  ViPattePolyh::_Vertex\endlink.
    */
   unsigned int GetSndVtxIdx() const { return _SndIdx; }
   /*!
    * Udost�pnia wektor normalny �cianki, do kt�rej nale�y.
    */
   const Vector3f &FaceNormVect() const;

   /*!
    * Udost�pnia wektor normalny �cianki s�siedniej. W przypadku,
    * gdy nie ma s�siedniej �cianki zwracany jest wektor zerowy.
    */
   Vector3f FaceNormVect_Neighbor() const;

   /*! 
    * Metoda umo�liwia okre�lenie czy kraw�d� jest widoczna
    * z danego kierunku patrzenia. Metoda przeznaczona jest tylko
    * do rysowania miniaturek figur wzorcowych. Nie ma zastosowania
    * w przypadku rysowania w uk�adzie wsp�rz�dnych globalnych.
    * \param ViewVct - wektor kierunku patrzenia. Wektor skierowany
    *                  jest od oka w kierunku przedmiotu.
    * \retval true - je�li kraw�d� jest widoczna,
    * \retval false - w przypadku przeciwnym.
    */
   bool IsVisible(const Vector3f &ViewVct) const 
     { return sgn(FaceNormVect() & ViewVct) == -1 ||
              sgn(FaceNormVect_Neighbor() & ViewVct) == -1; }
};


/*!
 *  Wy�wietla informacje dotycz�ce danej kraw�dzi (wsp�rz�dne pierwszego
 *  i drugiego wierzcho�ka).
 */
std::ostream &operator  << (std::ostream &ostrm, ViFaceEdge const &EFace);

#endif
