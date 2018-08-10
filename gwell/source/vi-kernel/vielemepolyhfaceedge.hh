#ifndef VIELMEPOLYHFACEEDGE_HH
#define VIELMEPOLYHFACEEDGE_HH

/*!
 * \file  vielemepolyhfaceedge.hh
 * \author	Bogdan Kreczmer
 * \date	2003.03.23
 *
 * Plik zawiera definicj� klasy ViElemePolyhFaceEdge
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
#include "vifaceedge.hh"

class ViElemePolyhFace;
class ViElemePolyh;


/*!
 * Klasa zwiera opis kraw�dzi danej �cianki z uwzgl�dnieniem
 * jej prawid�owej orientacji wzgl�dem brzegu �cianki
 */
class ViElemePolyhFaceEdge {
   /*!
    * Pole zawiera referencj� do �cianki bry�y elementarnej, do kt�rej
    * to �cianki nale�y dana kraw�d�.
    */
   const ViElemePolyhFace   &_Owner;  
     /*!
      *  Pole zawiera referencj� do kraw�dzi �cianki bry�y wzorcowej
      *  odpowiadaj�c� kraw�dzi modelowanej przez ten obiekty dla
      *  bry�y elementarnej.
      */
   const ViFaceEdge         &_PatteFaceEdge;
   const Vector3f &_FstVtx; /*!< Pierwszy wierzcho�ek kraw�dzi. */
   const Vector3f &_SndVtx; /*!< Drugi wierzcho�ek kraw�dzi.    */
     /*!
      *  \if brief_private_fields
      *  \brief Wska�nik na drug� �ciank�
      *  \endif
      *
      *  Wska�nik na drug� �ciank�, z kt�ra s�siaduje kraw�d�.
      *  �cianka ta nie musi istnie�, w�wczas w polu tym
      *  wpisana zostaje warto�� \p NULL.
      */
   const ViElemePolyhFace   *_pNeighborFace; 

   friend class ViElemePolyh;

   void PostInit();

  public:
    /*!
     * Inicjalizuje obiekt referencjami do poszczeg�lnych p�l.
     * \param Owner - referencja do �cianki, do kt�rej nale�y ta kraw�d�,
     * \param Edge  - referencja do kraw�dzi �cianki bry�y wzorcowej,
     *                kt�ra odpowiada kraw�dzi modelowanej przez tworzony
     *                obiekt w bryle elementarnej, do kt�rej nale�y.
     */
   ViElemePolyhFaceEdge( const ViElemePolyhFace    &Owner, 
                         const ViFaceEdge & Edge
			 );

   /*!
    * Udost�pnia referencj� do �cianki, kt�rej cz�ci� jest ta kraw�d�.
    */
   const ViElemePolyhFace &GetFace() const { return _Owner; }
   /*!
    * Udost�pnia referencj� do �cianki, z kt�r� kraw�d� ta s�siaduje.
    */
   const ViElemePolyhFace *GetNeighborFace() const { return _pNeighborFace; }
   /*!
    * Referencja do pierwszego wierzcho�ka kraw�dzi.
    */
   const Vector3f &GetFstVtx() const { return _FstVtx; }
   /*!
    * Referencja do drugiego wierzcho�ka kraw�dzi.
    */
   const Vector3f &GetSndVtx() const { return _SndVtx; }
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
std::ostream &operator  << (std::ostream &ostrm, 
                            ViElemePolyhFaceEdge const &EFace);

#endif
