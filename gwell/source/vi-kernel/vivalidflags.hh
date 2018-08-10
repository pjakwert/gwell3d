#ifndef VIVALIDFLAGS_H
#define VIVALIDFLAGS_H

/*!
 * \file vivalidflags.hh
 *  Plik zawiera definicj� kalsy ViValidFlags.
 *  \author Bogdan Kreczmer
 *  \date   2003.12
 */


#ifdef __GNUG__
#pragma interface
#endif




//  U W A G A !!!  Warto�ci definiuj�ce flagi musz� by� by� poteg� 2.

/*!
 * Gdy jest  obiekt wyselekcjonowany
 */
#define VF__DRAW_SELECTED       1    
/*!
 * Sta�a definiuje flag� reprezentuj�c� wa�no�� oblicze� wsp�rz�dnych
 *  wierzcho�k�w w uk�adzie globalnym.
 */
#define VF__GLB_VTX             2 
/*!
 * Flaga ta jest zasz�o�ci� z poprzednich wersji aplikacji.
 * Jest przewidziana do usuni�cia i dlatego nie nale�y si� do niej
 * odwo�ywa�.
 *
 * Sta�a definiuje flag� reprezentuj�c�
 * wa�no�� oblicze� dla wierzho�k�w w uk�adzie obserwatora policzone
 * (odnosi si� tylko do perspektywy technicznej bez OpenGl).
 */
#define VF__VIEW_VTX            4      
/*!
 * Flaga ta jest zasz�o�ci� z poprzednich wersji aplikacji.
 * Jest przewidziana do usuni�cia i dlatego nie nale�y si� do niej
 * odwo�ywa�.
 *
 * Sta�a definiuje flag� reprezentuj�c�
 *  wa�no�� oblicze� prostok�ta obrysu (RectOut) obiektu elementarnego 
 * (RealFigure) dla widoku oraz widzialno�ci powierzchni (Visible)
 */
#define VF__RECT_OUT            8  

 /*!
  * Flaga ta jest zasz�o�ci� z poprzednich wersji aplikacji.
  * Jest przewidziana do usuni�cia i dlatego nie nale�y si� do niej
  * odwo�ywa�.
  *
  * Sta�a definiuje flag� reprezentuj�c�
  * wa�no�� oblicze� dla �cianek.
  */
#define VF__FACE_POLY          16

 /*!
  * Flaga ta jest zasz�o�ci� z poprzednich wersji aplikacji.
  * Jest przewidziana do usuni�cia i dlatego nie nale�y si� do niej
  * odwo�ywa�.
  *
  * Sta�a definiuje flag� reprezentuj�c�
  * wa�no�� oblicze� dla obrysu prostok�tnego danej �cianki (wykorzystywane
  * przy selekcji za pomoc� myszy.
  */
#define VF__FACE_RGN           32

 /*!
  * Flaga ta jest zasz�o�ci� z poprzednich wersji aplikacji.
  * Jest przewidziana do usuni�cia i dlatego nie nale�y si� do niej
  * odwo�ywa�.
  *
  * Sta�a definiuje flag� reprezentuj�c�
  * wa�no�� oblicze� dla obrysu prostok�tnego danej �cianki (wykorzystywane
  * przy selekcji za pomoc� myszy) dla uk�adu wsp�rz�dnych ekranu danego
  * widoku.
  */
#define VF__FACE_VIEW_RGN      64
 /*!
  * Definiuje flag� informuj�c� o tym, �e dane obliczeniowe jednego
  * z potomk�w nie s� aktualne.
  */
#define VF__TEST_DESCENDANTS   128   
 /*!
  * Definiuje flag� informuj�c� o tym, �e
  * dane obliczeniowe prostopad�o�ciennego obrysu bry�y nie s� aktualne.
  */
#define VF__OUTLINE3D          256


 /*!
  *  Klasa specjalizowana jest do obs�ugi znacznik�w jednobitowych.
  *  Cz�� z flag zaimplementowanych w tej klasie jest ju� zasz�o�ci�.
  *  Niemniej flagi zwi�zane z wa�no�ci� oblicze� wsp�lrzednych globalnych
  *  wierzcho�k�w jest i b�dzie wykorzystywane w ca�ym projekcie.
  */
class ViValidFlags {
 private:
    /*!
     * Zestawienie flag w polu _Flags decyduje o tym czy dane
     *  obliczenia uwa�a sie za wykonane lub nie np. obliczenia wierzcho�k�w
     *  globalnych. Je�eli dana flaga jest ustawiona, to pomimo wywo�ania
     *  metody
     *  przeprowadzaj�cej ��dane obliczenia, nie zostan� one wykonane
     *  dla tego obiektu elementarnego.
     *
     * Rodzaje flag:
     *  \li VF__DRAW_SELECTED  - obiekt jest wyselekcjonowany.
     *  \li VF__GLB_VTX  - obliczenia wierzcho�k�w globalnych.
     *  \li VF__VIEW_VTX - obliczenia wierzcho�k�w dla wszystkich widok�w.
     *  \li VF__RECT_OUT -  obliczenia prostok�ta, w kt�ry wpisany
     *              jest rysunek obiektu elementarnego dla wszystkich widok�w
     *              (znacznik jest zasz�o�ci� i jest niesp�jny
     *               z koncepcj� tej biblioteki, dlatego te� nie nale�y
     *               go stosowa�).
     *  \li VF__FACE_POLY - obliczenia danych dotycz�cych poszczeg�lnych
     *                      �cianek.
     *  \li VF__FACE_RGN  - obliczenia prostok�t�w, w kt�rych wpisane s�
     *                       rysunki
     *               poszczeg�lnych �cianek
     *              (znacznik jest zasz�o�ci� i jest niesp�jny
     *               z koncepcj� tej biblioteki, dlatego te� nie nale�y
     *               go stosowa�)..
     *  \li VF__FACE_VIEW_RGN - obliczenia prostok�t�w, w kt�rych wpisane s� 
     *               rysunki poszczeg�lnych �cianek dla otwartych widok�w
     *              (znacznik jest zasz�o�ci� i jest niesp�jny
     *               z koncepcj� tej biblioteki, dlatego te� nie nale�y
     *               go stosowa�)..
     *  \li VF__FLAG_TEST_DESCENDANTS - informuje o tym, �e dla jednego z
     *               potomk�w
     *               dane obliczeniowe musz� zosta� zaktualizowane.
     */               
   unsigned short int _Flags;

    /*!
     *  Zeruje wybrany zestaw flag.
     *  \param FlagsSet - zbi�r znacznik�w (suma binarna wybranych pot�g
     *                    liczby 2 odpowiadaj�cych wybranym flagom), 
     *                    kt�re maj�
     *                    zosta� wyzerowane.
     *  \post W polu \link ViValidFlags::_Flags _Flags\endlink
     *        zerowane s� flagi przekazane przez parametr \e FlagsSet.
     */
   void  VF_Reset(unsigned int FlagsSet) { _Flags &= ~FlagsSet; }

    /*!
     *  Ustawia wybrany zestaw flag.
     *  \param FlagsSet - zbi�r znacznik�w (suma binarna wybranych pot�g
     *                    liczby 2 odpowiadaj�cych wybranym flagom), 
     *                    kt�re maj�
     *                    zosta� wyzerowane.
     *  \post W polu \link ViValidFlags::_Flags _Flags\endlink
     *        zerowane s� flagi przekazane przez parametr \e FlagsSet.
     */
   void  VF_Set(unsigned int FlagsSet)   { _Flags |= FlagsSet;  }

 public:

   /*!
    * Inicjalizuje znaczniki wszystkich flag jako uniewa�nione.
    */
   ViValidFlags() { _Flags = 0; }


    /*!
     * Uniewa�nia flag� dla struktur zale�nych od danych obliczeniowych
     * dla danej �cianki.
     * Uniewa�niane flagi to: VF__FACE_RGN, VF__FACE_VIEW_RGN.
     */
   void VF_ResetDependedOnFacePoly()
     {
       VF_Reset(VF__FACE_RGN | VF__FACE_VIEW_RGN);
     }


    /*!
     * Uniewa�nia flagi wa�no�ci danych obliczeniowych dla �cianek liczonych
     * dla danego widoku (flaga: VF__FACE_POLY) oraz struktur od nich 
     * zale�nych.
     */
   void VF_ResetFacePoly()
     { 
       VF_Reset(VF__FACE_POLY);
       VF_ResetDependedOnFacePoly();
     }

    /*!
     * Ustawia flag� wa�no�ci danych obliczeniowych dla �cianki 
     * (flaga VF__FACE_POLY) oraz
     * uniewa�nia flag� dla struktur zale�nych od danych obliczeniowych
     * dla danej �cianki.
     */
   void VF_SetFacePoly()
     {
       VF_Set(VF__FACE_POLY);
       VF_ResetDependedOnFacePoly();
     }


    /*!
     * Ustawia flag� wa�no�ci oblicze� obrazu �cianki 
     * (flagi VF__FACE_RGN, VF__FACE_VIEW_RGN).
     * Flagi te s� zasz�o�ci� i przewidziane s� do usuni�cia.
     * Tego typu flagi maj� prawo znale�� si� jedynie w klasach pochodnych.
     */
   void VF_SetFacePolygonOutlineBox3fs()
     {
       VF_Set(VF__FACE_RGN | VF__FACE_VIEW_RGN);
     }


    /*!
     * Metoda jest zasz�o�ci� jeszcze z wcze�niejszych wersji aplikacji
     * i nie nale�y jej wykorzystywa�.
     * Przeznaczona jest ona do usuni�cia, gdy� wi��e si� z interfejsem 
     * graficznym.
     * 
     * 
     * Ustawia flag� wa�no�ci danych obliczeniowych dla wsp�rz�dnych
     * wierzcho�k�w i obrysu prostok�ta danej figury dla danego widoku.
     */
   void VF_Set_ViewVtx_RectOutlineBox3f() { 
        VF_Set(VF__VIEW_VTX | VF__RECT_OUT); 
        VF_ResetDependedOnViewVtx();
      }


    /*!
     * Metoda jest zasz�o�ci� jeszcze z wcze�niejszych wersji aplikacji
     * i nie nale�y jej wykorzystywa�.
     * Przeznaczona jest ona do usuni�cia, gdy� wi��e si� z interfejsem 
     * graficznym.
     * 
     * 
     * Ustawia flag� wa�no�ci danych obliczeniowych dla
     * obrysu prostok�ta danej figury dla danego widoku.
     */
   void VF_SetRectOutlineBox3f() { VF_Set(VF__RECT_OUT); }


    /*!
     * Metoda jest zasz�o�ci� jeszcze z wcze�niejszych wersji aplikacji
     * i nie nale�y jej wykorzystywa�.
     * Przeznaczona jest ona do usuni�cia, gdy� wi��e si� z interfejsem 
     * graficznym.
     * 
     * 
     * Uniewa�nia flag� dla struktur zale�nych od wsp�rz�dnych globalnych.
     */
   void VF_ResetDependedOnViewVtx()
     {
       VF_Reset(VF__FACE_POLY |
                VF__FACE_RGN | VF__FACE_VIEW_RGN);
     }

    /*!
     * Metoda jest zasz�o�ci� jeszcze z wcze�niejszych wersji aplikacji
     * i nie nale�y jej wykorzystywa�.
     * Przeznaczona jest ona do usuni�cia, gdy� wi��e si� z interfejsem 
     * graficznym.
     * 
     * 
     * Uniewa�nia flag� wa�no�ci oblicze� dla wsp�rzednych wierzcho�k�w 
     * w uk�adzie obserwatora i uniewa�nia flagi dla struktur zale�nych od
     * tych wsp�rz�dnych.
     */
   void VF_ResetViewVtx()
     {
       VF_ResetDependedOnViewVtx();
       VF_Reset(VF__VIEW_VTX);
     }


    /*!
     * Metoda jest zasz�o�ci� jeszcze z wcze�niejszych wersji aplikacji
     * i nie nale�y jej wykorzystywa�.
     * Przeznaczona jest ona do usuni�cia, gdy� wi��e si� z interfejsem 
     * graficznym.
     * 
     * 
     * Ustawia flag� wa�no�ci oblicze� dla wsp�rzednych wierzcho�k�w 
     * w uk�adzie obserwatora i uniewa�nia flagi dla struktur zale�nych od
     * tych wsp�rz�dnych.
     */
   void VF_SetViewVtx()
     {
       VF_ResetDependedOnViewVtx();
       VF_Reset(VF__RECT_OUT);
       VF_Set(VF__VIEW_VTX);
     }



    /*!
     * Uniewa�nia flag� dla struktur zale�nych do wsp�rz�dnych globalnych.
     */
   void VF_ResetDependedOnGlbVtx()
     {
       VF_Reset(VF__GLB_VTX | VF__OUTLINE3D | VF__VIEW_VTX |  VF__RECT_OUT
	              | VF__FACE_POLY | VF__FACE_RGN | VF__FACE_VIEW_RGN);
     }

    /*!
     * Uniewa�nia flag� dla wsp�rz�dnych globalnych i struktur od nich
     * zale�nych.
     */
   void VF_ResetGlbVtx()
     {
       VF_Reset(VF__GLB_VTX);
       VF_ResetDependedOnGlbVtx();
     }

    /*!
     * Ustawia wa�no�� flagi dla wsp�rz�dnych globalnych i uniewa�nia
     * flagi dla struktur od nich zale�nych.
     */
   void VF_SetGlbVtx()
     {
       VF_Set(VF__GLB_VTX);
       VF_ResetDependedOnGlbVtx();
     }


    /*!
     * Ustawia flag� (VF__TEST_DESCENDANTS), kt�ra informuje �e dane
     * obliczeniowe jednego z
     * potomk�w musz� by� zaaktualizowane.
     */
   void VF_SetTestDescants() { VF_Set(VF__TEST_DESCENDANTS); }

    /*!
     * Zeruje wszystkie flagi.
     */
   void VF_ResetAll() { _Flags = 0; }

    /*!
     * Zwraca \p true gdy flaga jest ustawiona, co oznacza, �e  
     * obliczone wcze�niej wsp�rz�dne globalne s� aktualne.
     */
   bool IsVF_GlbVtx()      const { return _Flags & VF__GLB_VTX; }
    /*!
     * Metoda jest zasz�o�ci� jeszcze z wcze�niejszych wersji aplikacji
     * i nie nale�y jej wykorzystywa�.
     * Przeznaczona jest ona do usuni�cia, gdy� wi��e si� z interfejsem 
     * graficznym.
     * 
     * 
     * Metoda zwraca \p true gdy flaga jest ustawiona, co oznacza, �e  
     * obliczone wcze�niej prostok�tny obrys rysunku danej bry�y na
     * ekranie jest wci�� aktualny.
     */
   bool IsVF_RectOutlineBox3f() const { return _Flags & VF__RECT_OUT; }
    /*!
     * Metoda jest zasz�o�ci� jeszcze z wcze�niejszych wersji aplikacji
     * i nie nale�y jej wykorzystywa�.
     * Przeznaczona jest ona do usuni�cia, gdy� wi��e si� z interfejsem 
     * graficznym.
     * 
     * 
     * Metoda zwraca \p true gdy flaga jest ustawiona, co oznacza, �e  
     * obliczone wcze�niej wsp�rz�dne wierzcho�k�w dla otwartych
     * widok�w s� wci�� aktualny.
     */
   bool IsVF_ViewVtx()     const { return _Flags & VF__VIEW_VTX; }

    /*!
     * Metoda jest zasz�o�ci� jeszcze z wcze�niejszych wersji aplikacji
     * i nie nale�y jej wykorzystywa�.
     * Przeznaczona jest ona do usuni�cia, gdy� wi��e si� z interfejsem 
     * graficznym.
     * 
     * 
     * Metoda zwraca \p true gdy flaga jest ustawiona, co oznacza, �e  
     * obliczone wcze�niej dane dla �cianki bry�y s� wci�� aktualny.
     */
   bool IsVF_FacePoly()    const { return _Flags & VF__FACE_POLY; }
};

#endif
