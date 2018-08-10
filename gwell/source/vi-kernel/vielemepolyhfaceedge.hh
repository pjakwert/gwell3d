#ifndef VIELMEPOLYHFACEEDGE_HH
#define VIELMEPOLYHFACEEDGE_HH

/*!
 * \file  vielemepolyhfaceedge.hh
 * \author	Bogdan Kreczmer
 * \date	2003.03.23
 *
 * Plik zawiera definicjê klasy ViElemePolyhFaceEdge
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
#include "vifaceedge.hh"

class ViElemePolyhFace;
class ViElemePolyh;


/*!
 * Klasa zwiera opis krawêdzi danej ¶cianki z uwzglêdnieniem
 * jej prawid³owej orientacji wzglêdem brzegu ¶cianki
 */
class ViElemePolyhFaceEdge {
   /*!
    * Pole zawiera referencjê do ¶cianki bry³y elementarnej, do której
    * to ¶cianki nale¿y dana krawêd¼.
    */
   const ViElemePolyhFace   &_Owner;  
     /*!
      *  Pole zawiera referencjê do krawêdzi ¶cianki bry³y wzorcowej
      *  odpowiadaj±c± krawêdzi modelowanej przez ten obiekty dla
      *  bry³y elementarnej.
      */
   const ViFaceEdge         &_PatteFaceEdge;
   const Vector3f &_FstVtx; /*!< Pierwszy wierzcho³ek krawêdzi. */
   const Vector3f &_SndVtx; /*!< Drugi wierzcho³ek krawêdzi.    */
     /*!
      *  \if brief_private_fields
      *  \brief Wska¼nik na drug± ¶ciankê
      *  \endif
      *
      *  Wska¼nik na drug± ¶ciankê, z która s±siaduje krawêd¼.
      *  ¦cianka ta nie musi istnieæ, wówczas w polu tym
      *  wpisana zostaje warto¶æ \p NULL.
      */
   const ViElemePolyhFace   *_pNeighborFace; 

   friend class ViElemePolyh;

   void PostInit();

  public:
    /*!
     * Inicjalizuje obiekt referencjami do poszczególnych pól.
     * \param Owner - referencja do ¶cianki, do której nale¿y ta krawêd¼,
     * \param Edge  - referencja do krawêdzi ¶cianki bry³y wzorcowej,
     *                która odpowiada krawêdzi modelowanej przez tworzony
     *                obiekt w bryle elementarnej, do której nale¿y.
     */
   ViElemePolyhFaceEdge( const ViElemePolyhFace    &Owner, 
                         const ViFaceEdge & Edge
			 );

   /*!
    * Udostêpnia referencjê do ¶cianki, której czê¶ci± jest ta krawêd¼.
    */
   const ViElemePolyhFace &GetFace() const { return _Owner; }
   /*!
    * Udostêpnia referencjê do ¶cianki, z któr± krawêd¼ ta s±siaduje.
    */
   const ViElemePolyhFace *GetNeighborFace() const { return _pNeighborFace; }
   /*!
    * Referencja do pierwszego wierzcho³ka krawêdzi.
    */
   const Vector3f &GetFstVtx() const { return _FstVtx; }
   /*!
    * Referencja do drugiego wierzcho³ka krawêdzi.
    */
   const Vector3f &GetSndVtx() const { return _SndVtx; }
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
std::ostream &operator  << (std::ostream &ostrm, 
                            ViElemePolyhFaceEdge const &EFace);

#endif
