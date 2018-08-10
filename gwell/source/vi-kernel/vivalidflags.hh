#ifndef VIVALIDFLAGS_H
#define VIVALIDFLAGS_H

/*!
 * \file vivalidflags.hh
 *  Plik zawiera definicjê kalsy ViValidFlags.
 *  \author Bogdan Kreczmer
 *  \date   2003.12
 */


#ifdef __GNUG__
#pragma interface
#endif




//  U W A G A !!!  Warto¶ci definiuj±ce flagi musz± byæ byê poteg± 2.

/*!
 * Gdy jest  obiekt wyselekcjonowany
 */
#define VF__DRAW_SELECTED       1    
/*!
 * Sta³a definiuje flagê reprezentuj±c± wa¿no¶æ obliczeñ wspó³rzêdnych
 *  wierzcho³ków w uk³adzie globalnym.
 */
#define VF__GLB_VTX             2 
/*!
 * Flaga ta jest zasz³o¶ci± z poprzednich wersji aplikacji.
 * Jest przewidziana do usuniêcia i dlatego nie nale¿y siê do niej
 * odwo³ywaæ.
 *
 * Sta³a definiuje flagê reprezentuj±c±
 * wa¿no¶æ obliczeñ dla wierzho³ków w uk³adzie obserwatora policzone
 * (odnosi siê tylko do perspektywy technicznej bez OpenGl).
 */
#define VF__VIEW_VTX            4      
/*!
 * Flaga ta jest zasz³o¶ci± z poprzednich wersji aplikacji.
 * Jest przewidziana do usuniêcia i dlatego nie nale¿y siê do niej
 * odwo³ywaæ.
 *
 * Sta³a definiuje flagê reprezentuj±c±
 *  wa¿no¶æ obliczeñ prostok±ta obrysu (RectOut) obiektu elementarnego 
 * (RealFigure) dla widoku oraz widzialno¶ci powierzchni (Visible)
 */
#define VF__RECT_OUT            8  

 /*!
  * Flaga ta jest zasz³o¶ci± z poprzednich wersji aplikacji.
  * Jest przewidziana do usuniêcia i dlatego nie nale¿y siê do niej
  * odwo³ywaæ.
  *
  * Sta³a definiuje flagê reprezentuj±c±
  * wa¿no¶æ obliczeñ dla ¶cianek.
  */
#define VF__FACE_POLY          16

 /*!
  * Flaga ta jest zasz³o¶ci± z poprzednich wersji aplikacji.
  * Jest przewidziana do usuniêcia i dlatego nie nale¿y siê do niej
  * odwo³ywaæ.
  *
  * Sta³a definiuje flagê reprezentuj±c±
  * wa¿no¶æ obliczeñ dla obrysu prostok±tnego danej ¶cianki (wykorzystywane
  * przy selekcji za pomoc± myszy.
  */
#define VF__FACE_RGN           32

 /*!
  * Flaga ta jest zasz³o¶ci± z poprzednich wersji aplikacji.
  * Jest przewidziana do usuniêcia i dlatego nie nale¿y siê do niej
  * odwo³ywaæ.
  *
  * Sta³a definiuje flagê reprezentuj±c±
  * wa¿no¶æ obliczeñ dla obrysu prostok±tnego danej ¶cianki (wykorzystywane
  * przy selekcji za pomoc± myszy) dla uk³adu wspó³rzêdnych ekranu danego
  * widoku.
  */
#define VF__FACE_VIEW_RGN      64
 /*!
  * Definiuje flagê informuj±c± o tym, ¿e dane obliczeniowe jednego
  * z potomków nie s± aktualne.
  */
#define VF__TEST_DESCENDANTS   128   
 /*!
  * Definiuje flagê informuj±c± o tym, ¿e
  * dane obliczeniowe prostopad³o¶ciennego obrysu bry³y nie s± aktualne.
  */
#define VF__OUTLINE3D          256


 /*!
  *  Klasa specjalizowana jest do obs³ugi znaczników jednobitowych.
  *  Czê¶æ z flag zaimplementowanych w tej klasie jest ju¿ zasz³o¶ci±.
  *  Niemniej flagi zwi±zane z wa¿no¶ci± obliczeñ wspólrzednych globalnych
  *  wierzcho³ków jest i bêdzie wykorzystywane w ca³ym projekcie.
  */
class ViValidFlags {
 private:
    /*!
     * Zestawienie flag w polu _Flags decyduje o tym czy dane
     *  obliczenia uwa¿a sie za wykonane lub nie np. obliczenia wierzcho³ków
     *  globalnych. Je¿eli dana flaga jest ustawiona, to pomimo wywo³ania
     *  metody
     *  przeprowadzaj±cej ¿±dane obliczenia, nie zostan± one wykonane
     *  dla tego obiektu elementarnego.
     *
     * Rodzaje flag:
     *  \li VF__DRAW_SELECTED  - obiekt jest wyselekcjonowany.
     *  \li VF__GLB_VTX  - obliczenia wierzcho³ków globalnych.
     *  \li VF__VIEW_VTX - obliczenia wierzcho³ków dla wszystkich widoków.
     *  \li VF__RECT_OUT -  obliczenia prostok±ta, w który wpisany
     *              jest rysunek obiektu elementarnego dla wszystkich widoków
     *              (znacznik jest zasz³o¶ci± i jest niespójny
     *               z koncepcj± tej biblioteki, dlatego te¿ nie nale¿y
     *               go stosowaæ).
     *  \li VF__FACE_POLY - obliczenia danych dotycz±cych poszczególnych
     *                      ¶cianek.
     *  \li VF__FACE_RGN  - obliczenia prostok±tów, w których wpisane s±
     *                       rysunki
     *               poszczególnych ¶cianek
     *              (znacznik jest zasz³o¶ci± i jest niespójny
     *               z koncepcj± tej biblioteki, dlatego te¿ nie nale¿y
     *               go stosowaæ)..
     *  \li VF__FACE_VIEW_RGN - obliczenia prostok±tów, w których wpisane s± 
     *               rysunki poszczególnych ¶cianek dla otwartych widoków
     *              (znacznik jest zasz³o¶ci± i jest niespójny
     *               z koncepcj± tej biblioteki, dlatego te¿ nie nale¿y
     *               go stosowaæ)..
     *  \li VF__FLAG_TEST_DESCENDANTS - informuje o tym, ¿e dla jednego z
     *               potomków
     *               dane obliczeniowe musz± zostaæ zaktualizowane.
     */               
   unsigned short int _Flags;

    /*!
     *  Zeruje wybrany zestaw flag.
     *  \param FlagsSet - zbiór znaczników (suma binarna wybranych potêg
     *                    liczby 2 odpowiadaj±cych wybranym flagom), 
     *                    które maj±
     *                    zostaæ wyzerowane.
     *  \post W polu \link ViValidFlags::_Flags _Flags\endlink
     *        zerowane s± flagi przekazane przez parametr \e FlagsSet.
     */
   void  VF_Reset(unsigned int FlagsSet) { _Flags &= ~FlagsSet; }

    /*!
     *  Ustawia wybrany zestaw flag.
     *  \param FlagsSet - zbiór znaczników (suma binarna wybranych potêg
     *                    liczby 2 odpowiadaj±cych wybranym flagom), 
     *                    które maj±
     *                    zostaæ wyzerowane.
     *  \post W polu \link ViValidFlags::_Flags _Flags\endlink
     *        zerowane s± flagi przekazane przez parametr \e FlagsSet.
     */
   void  VF_Set(unsigned int FlagsSet)   { _Flags |= FlagsSet;  }

 public:

   /*!
    * Inicjalizuje znaczniki wszystkich flag jako uniewa¿nione.
    */
   ViValidFlags() { _Flags = 0; }


    /*!
     * Uniewa¿nia flagê dla struktur zale¿nych od danych obliczeniowych
     * dla danej ¶cianki.
     * Uniewa¿niane flagi to: VF__FACE_RGN, VF__FACE_VIEW_RGN.
     */
   void VF_ResetDependedOnFacePoly()
     {
       VF_Reset(VF__FACE_RGN | VF__FACE_VIEW_RGN);
     }


    /*!
     * Uniewa¿nia flagi wa¿no¶ci danych obliczeniowych dla ¶cianek liczonych
     * dla danego widoku (flaga: VF__FACE_POLY) oraz struktur od nich 
     * zale¿nych.
     */
   void VF_ResetFacePoly()
     { 
       VF_Reset(VF__FACE_POLY);
       VF_ResetDependedOnFacePoly();
     }

    /*!
     * Ustawia flagê wa¿no¶ci danych obliczeniowych dla ¶cianki 
     * (flaga VF__FACE_POLY) oraz
     * uniewa¿nia flagê dla struktur zale¿nych od danych obliczeniowych
     * dla danej ¶cianki.
     */
   void VF_SetFacePoly()
     {
       VF_Set(VF__FACE_POLY);
       VF_ResetDependedOnFacePoly();
     }


    /*!
     * Ustawia flagê wa¿no¶ci obliczeñ obrazu ¶cianki 
     * (flagi VF__FACE_RGN, VF__FACE_VIEW_RGN).
     * Flagi te s± zasz³o¶ci± i przewidziane s± do usuniêcia.
     * Tego typu flagi maj± prawo znale¼æ siê jedynie w klasach pochodnych.
     */
   void VF_SetFacePolygonOutlineBox3fs()
     {
       VF_Set(VF__FACE_RGN | VF__FACE_VIEW_RGN);
     }


    /*!
     * Metoda jest zasz³o¶ci± jeszcze z wcze¶niejszych wersji aplikacji
     * i nie nale¿y jej wykorzystywaæ.
     * Przeznaczona jest ona do usuniêcia, gdy¿ wi±¿e siê z interfejsem 
     * graficznym.
     * 
     * 
     * Ustawia flagê wa¿no¶ci danych obliczeniowych dla wspó³rzêdnych
     * wierzcho³ków i obrysu prostok±ta danej figury dla danego widoku.
     */
   void VF_Set_ViewVtx_RectOutlineBox3f() { 
        VF_Set(VF__VIEW_VTX | VF__RECT_OUT); 
        VF_ResetDependedOnViewVtx();
      }


    /*!
     * Metoda jest zasz³o¶ci± jeszcze z wcze¶niejszych wersji aplikacji
     * i nie nale¿y jej wykorzystywaæ.
     * Przeznaczona jest ona do usuniêcia, gdy¿ wi±¿e siê z interfejsem 
     * graficznym.
     * 
     * 
     * Ustawia flagê wa¿no¶ci danych obliczeniowych dla
     * obrysu prostok±ta danej figury dla danego widoku.
     */
   void VF_SetRectOutlineBox3f() { VF_Set(VF__RECT_OUT); }


    /*!
     * Metoda jest zasz³o¶ci± jeszcze z wcze¶niejszych wersji aplikacji
     * i nie nale¿y jej wykorzystywaæ.
     * Przeznaczona jest ona do usuniêcia, gdy¿ wi±¿e siê z interfejsem 
     * graficznym.
     * 
     * 
     * Uniewa¿nia flagê dla struktur zale¿nych od wspó³rzêdnych globalnych.
     */
   void VF_ResetDependedOnViewVtx()
     {
       VF_Reset(VF__FACE_POLY |
                VF__FACE_RGN | VF__FACE_VIEW_RGN);
     }

    /*!
     * Metoda jest zasz³o¶ci± jeszcze z wcze¶niejszych wersji aplikacji
     * i nie nale¿y jej wykorzystywaæ.
     * Przeznaczona jest ona do usuniêcia, gdy¿ wi±¿e siê z interfejsem 
     * graficznym.
     * 
     * 
     * Uniewa¿nia flagê wa¿no¶ci obliczeñ dla wspó³rzednych wierzcho³ków 
     * w uk³adzie obserwatora i uniewa¿nia flagi dla struktur zale¿nych od
     * tych wspó³rzêdnych.
     */
   void VF_ResetViewVtx()
     {
       VF_ResetDependedOnViewVtx();
       VF_Reset(VF__VIEW_VTX);
     }


    /*!
     * Metoda jest zasz³o¶ci± jeszcze z wcze¶niejszych wersji aplikacji
     * i nie nale¿y jej wykorzystywaæ.
     * Przeznaczona jest ona do usuniêcia, gdy¿ wi±¿e siê z interfejsem 
     * graficznym.
     * 
     * 
     * Ustawia flagê wa¿no¶ci obliczeñ dla wspó³rzednych wierzcho³ków 
     * w uk³adzie obserwatora i uniewa¿nia flagi dla struktur zale¿nych od
     * tych wspó³rzêdnych.
     */
   void VF_SetViewVtx()
     {
       VF_ResetDependedOnViewVtx();
       VF_Reset(VF__RECT_OUT);
       VF_Set(VF__VIEW_VTX);
     }



    /*!
     * Uniewa¿nia flagê dla struktur zale¿nych do wspó³rzêdnych globalnych.
     */
   void VF_ResetDependedOnGlbVtx()
     {
       VF_Reset(VF__GLB_VTX | VF__OUTLINE3D | VF__VIEW_VTX |  VF__RECT_OUT
	              | VF__FACE_POLY | VF__FACE_RGN | VF__FACE_VIEW_RGN);
     }

    /*!
     * Uniewa¿nia flagê dla wspó³rzêdnych globalnych i struktur od nich
     * zale¿nych.
     */
   void VF_ResetGlbVtx()
     {
       VF_Reset(VF__GLB_VTX);
       VF_ResetDependedOnGlbVtx();
     }

    /*!
     * Ustawia wa¿no¶æ flagi dla wspó³rzêdnych globalnych i uniewa¿nia
     * flagi dla struktur od nich zale¿nych.
     */
   void VF_SetGlbVtx()
     {
       VF_Set(VF__GLB_VTX);
       VF_ResetDependedOnGlbVtx();
     }


    /*!
     * Ustawia flagê (VF__TEST_DESCENDANTS), która informuje ¿e dane
     * obliczeniowe jednego z
     * potomków musz± byæ zaaktualizowane.
     */
   void VF_SetTestDescants() { VF_Set(VF__TEST_DESCENDANTS); }

    /*!
     * Zeruje wszystkie flagi.
     */
   void VF_ResetAll() { _Flags = 0; }

    /*!
     * Zwraca \p true gdy flaga jest ustawiona, co oznacza, ¿e  
     * obliczone wcze¶niej wspó³rzêdne globalne s± aktualne.
     */
   bool IsVF_GlbVtx()      const { return _Flags & VF__GLB_VTX; }
    /*!
     * Metoda jest zasz³o¶ci± jeszcze z wcze¶niejszych wersji aplikacji
     * i nie nale¿y jej wykorzystywaæ.
     * Przeznaczona jest ona do usuniêcia, gdy¿ wi±¿e siê z interfejsem 
     * graficznym.
     * 
     * 
     * Metoda zwraca \p true gdy flaga jest ustawiona, co oznacza, ¿e  
     * obliczone wcze¶niej prostok±tny obrys rysunku danej bry³y na
     * ekranie jest wci±¿ aktualny.
     */
   bool IsVF_RectOutlineBox3f() const { return _Flags & VF__RECT_OUT; }
    /*!
     * Metoda jest zasz³o¶ci± jeszcze z wcze¶niejszych wersji aplikacji
     * i nie nale¿y jej wykorzystywaæ.
     * Przeznaczona jest ona do usuniêcia, gdy¿ wi±¿e siê z interfejsem 
     * graficznym.
     * 
     * 
     * Metoda zwraca \p true gdy flaga jest ustawiona, co oznacza, ¿e  
     * obliczone wcze¶niej wspó³rzêdne wierzcho³ków dla otwartych
     * widoków s± wci±¿ aktualny.
     */
   bool IsVF_ViewVtx()     const { return _Flags & VF__VIEW_VTX; }

    /*!
     * Metoda jest zasz³o¶ci± jeszcze z wcze¶niejszych wersji aplikacji
     * i nie nale¿y jej wykorzystywaæ.
     * Przeznaczona jest ona do usuniêcia, gdy¿ wi±¿e siê z interfejsem 
     * graficznym.
     * 
     * 
     * Metoda zwraca \p true gdy flaga jest ustawiona, co oznacza, ¿e  
     * obliczone wcze¶niej dane dla ¶cianki bry³y s± wci±¿ aktualny.
     */
   bool IsVF_FacePoly()    const { return _Flags & VF__FACE_POLY; }
};

#endif
