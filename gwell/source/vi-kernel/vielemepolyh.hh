#ifndef VIELEMEPOLYH_HH
#define VIELEMEPOLYH_HH

/*! \file vielemepolyh.hh
 *  Plik zawiera definicjê klasy ViElemePolyh oraz iteratorów 
 *  ¶cianek bry³y
 *   \link ViElemePolyh::ConFaceIter 
 *          ViElemePolyh::ConFaceIter\endlink i 
 *   \link ViElemePolyh::VarFaceIter  ViElemePolyh::VarFaceIter\endlink
 *  \author Bogdan Kreczmer
 *  \date   2003.12
 *  \version  1.00.00
 */


#ifdef __GNUG__
#pragma interface
#endif



#include "vimatrix3f.hh"
#include "vipattepolyh.hh"
#include "vintreenode.hh"
#include "figqueues-id.h"
#include "outlinebox3f.hh"
#include "vielemepolyhface.hh"
#include "vielemepolyhedge.hh"
#include "chaintableiterator.hh"
#include "vihierarchyline.hh"



/*! \class ViElemePolyh
 * Obiekty klasy \e ViElemePolyedron (Elementary Polyhedron)
 * reprezentuj± wielo¶ciany modeluj±ce elementarne obiekty
 * na scenie. Ka¿dy z nich reprezentuje pewien obiekt wzorcowy
 * (\link ViPattePolyh ViPattePolyh\endlink), z którego 
 * jest otrzymywany
 * poprzez zastosowanie przeskalowania i przetransformowania do swojego
 * w³asnego uk³adu wspó³rzêdnych. Obiekty tej klasy wchodz± w sk³ad
 * obiektów z³o¿onych (\link ViMultiPolyh ViMultiPolyh\endlink),
 * które s± ich konglomeratami.
 *
 * Ka¿dy obiekt klasy ViElemePolyh dysponuje zestawem wspó³rzêdnych
 * globalnych swoich wierzcho³ków. Przegl±danie ich nale¿y dokonywaæ
 * w oparciu o iterator ViElemePolyh::ConVtxIter.
 *
 * Przyk³ad u¿ycia iteratora ViElemePolyh::ConVtxIter:
 * \code
 *  // Szuka warto¶ci maksymalnej wspó³rzêdnej x sposród
 *  // wspó³rzêdnych wszystkich wierzcho³ków.
 *  //
 * float SzukajMaksimum(const ViElemePolyh &EPolyh)
 * {
 *   int  x_max = numeric_limits<float>::min();
 * 
 *   for (ViElemePolyh::ConVtxIter Iter = EPolyh.ConBegin_GlbVtx();
 *        Iter;  Iter++) {
 *     if ( Iter->x > x_max ) x_max = Iter->x;
 *   }
 *   return x_max;
 * }
 * \endcode
 *
 * Przegl±danie poszczególnych krawêdzi nale¿y dokonywaæ
 * w oparciu o iterator ViElemePolyh::ConEdgeIter.
 *
 * Przyk³ad u¿ycia iteratora ViElemePolyh::ConEdgeIter:
 * \code
 *  // Szuka najd³u¿szej krawêdzi.
 *  //
 * float SzukajNajdluzszej(const ViElemePolyh &EPolyh)
 * {
 *   int       d, d_max = 0;
 *   Vector3f  EVct;
 *
 *   for (ViElemePolyh::ConEdgeIter Iter = EPolyh.ConBegin_GlbEdge();
 *        Iter;  Iter++) {
 *     EVct = Iter->GetFstVtx()-Iter->GetFstVtx();
 *     if ( (d = EVct.Length()) > d_max ) d_max = d;
 *   }
 *   return d_max;
 * }
 * \endcode
 */

DEFPOLYHCLASS(ViElemePolyh,ViNTreeNode),
          public ListItem<ViElemePolyh,IDFIGURE> { //___________

  /*!
   * Pole i zwiazane z nim metody maj± charakter roboczy i wykorzystywane
   * s± tylko w konstrukorze
   * \link ViElemePolyh::ViElemePolyh ViElemePolyh\endlink
   *  oraz w konstrukorze klasy 
   * \link ViElemePolyhFace::ViElemePolyhFace ViElemePolyhFace\endlink.
   */
   static unsigned int _FacesCount;  

 public:

    /*!
     * Metoda MUSI byæ u¿ywana bezpo¶rednio przed tworzeniem tablicy ¶cianek
     * (patrz \link ViElemePolyh::_PolyhFaces _PolyhFaces\endlink).
     * Wywo³anie metody powoduje wyzerowanie licznika ¶cianek
     * \link  ViElemePolyh::_FacesCount _FacesCount\endlink, który jest
     * polem statycznym.
     */
   static void ResetFacesCount() { _FacesCount = 0; }

    /*!
     *  Inkrementuje (o 1) licznik ¶cianek 
     *  (\link  ViElemePolyh::_FacesCount _FacesCount\endlink).
     */
   static unsigned int IncFacesCount() { return _FacesCount++; }
 
 private:

    /*!
     * Referencja do obiektu wzorcowego, z którego otrzymywany jest 
     * model reprezentowanej bry³y przez obiekt klasy ViPattePolyh.
     * Jest on otrzymywany poprzez przeskalowanie i przetransformowanie
     * (patrz macierze transformacji: 
     *  \link ViElemePolyh::_Mtx_Patte2Eleme _Mtx_Patte2Eleme\endlink
     * oraz \link ViElemePolyh::_Mtx_Eleme2Indiv _Mtx_Eleme2Indiv\endlink)
     * do lokalnego uk³adu wspó³rzêdnych
     * modelowanej bry³y.
     */
   ViPattePolyh const * _pPattePolyh;

    /*!
     *  Macierz transformacji przej¶cia z uk³adu 
     *  wspó³rzêdnych wzorcowej bry³y (reprezentowanej przez obiekt
     *  klasy \link ViPattePolyh ViPattePolyh\endlink) do uk³adu
     *  wspó³rzêdnych tego obiektu.
     */
   ViMatrix3f        _Mtx_Patte2Eleme;

    /*!
     * Transformacja z uk³adu wielo¶cianu do uk³adu okre¶lonego przez 
     * u¿ytkownika. Pozwala to przesun±æ uk³ad wspó³rzêdnych. Jest to 
     * konieczne, aby mieæ swobodê w lokalizowaniu i orientowaniu osi 
     * obrotu (np. przegubu) wzglêdem wcze¶niejszego
     * elementu w ³añcuchu kinematycznym.
     */
   ViMatrix3f        _Mtx_Eleme2Indiv;

    /*!
     *  Wska¼nik na tablicê (tablica tworzona jest dynamicznie w
     *  konstruktorze) wspó³rzêdnych
     *  wierzcho³ków w uk³adzie wspó³rzêdnych globalnych (tzn. 
     *  uk³adzie wspó³rzêdnych sceny). 
     */
   Vector3f         *_GlbVtx;      
           
    /*!
     *  Wska¼nik na tablicê (tablica tworzona jest dynamicznie w
     *  konstruktorze)
     *  zawieraj±c± informacje dotycz±ce poszczególnych ¶cianek wyra¿one w 
     *  uk³adzie wspó³rzêdnych globalnych (np. wspó³rzêdne wektora 
     *  normalnego danej ¶cianki).
     */                  
   ViElemePolyhFace *_PolyhFaces; 

    /*!
     *  Zawiera wspó³rzêdne prostopad³o¶cianu bêd±cego obrysem danej bry³y
     *  (w uk³adzie wspó³rzêdnych globalnych). Prostopad³o¶cian tworzony
     *  jest w ten sposób, ¿e jego poszczególne ¶cianki s± równoleg³e 
     *  do p³aszczyzn \e OXY, \e OXZ, \e OYZ.
     */
   OutlineBox3f      _GlbOutlineBox;

    /*!
     *  Informuje o tym czy obiekt jest wyselekcjonowany 
     *  (\p true - tak, \p false - nie).
     */
   bool              _Selected;  

  protected:

    /*!
     *  Wierzcho³ki w³a¶ciwego lokalnego uk³adu wspó³rzêdnych wielo¶cianu 
     *  Jest to struktura pomocnicza stworzona z my¶l± o wizualizacji.
     *  
     *  Kolejne elementy tablicy odpowiadaj± punktom: 
     *                0 - \e O, 1 - \e X, 2 - \e Y, 3 - \e Z.
     */
   Vector3f         _IndividualCoord[4];



  public:

   /*!
    * Iteratory dla ¶cianek, dla których wspó³rzêdne wierzcho³ków wyra¿one s±
    * w globalnym uk³adzie wspó³rzêdnych. Za pomoc± tego iteratora otrzymywane
    * s± obiekty sta³e (tzn. \b const \link ViElemePolyhFace 
    * ViElemePolyhFace\endlink).
    */
   class ConFaceIter: public DireTableIterator<const ViElemePolyhFace> {
     public:
       /*!
	*  Konstruktor inicjalizuje iterator ustawiaj±c w nim wska¼nik 
	*  pocz±tku tablicy i jej ilo¶ci elementów, które mag± byæ
	*  przegl±dane z wykorzystaniem tego iteratora.
	*  \param No - ilo¶æ elementów tablicy, które mog± byæ przegl±dane
	*              z wykorzystaniem tego iteratora.
	*  \param Tab - wska¼nik na pocz±tek tablicy, która ma byæ iterowana.
	*  \post
	*    Iterowane elementy udostêpniane przez iterator nie mog± byæ
	*    zmieniane.
	*/
      ConFaceIter(unsigned int No, ViElemePolyhFace const *Tab):
          DireTableIterator<const ViElemePolyhFace>(No,Tab) {}
   }; //---------------------------------------------------------------------

   /*!
    * Iteratory dla ¶cianek, dla których wspó³rzêdne wierzcho³ków wyra¿one s±
    * w globalnym uk³adzie wspó³rzêdnych. Za pomoc± tego iteratora otrzymywane
    * s± obiekty klasy \link ViElemePolyhFace ViElemePolyhFace\endlink.
    */
 class VarFaceIter: public DireTableIterator<ViElemePolyhFace> { //----------
     public:
       /*!
	*  Konstruktor inicjalizuje iterator ustawiaj±c w nim wska¼nik 
	*  pocz±tku tablicy i jej ilo¶ci elementów, które mag± byæ
	*  przegl±dane z wykorzystaniem tego iteratora.
	*  \param No - ilo¶æ elementów tablicy, które mog± byæ przegl±dane
	*              z wykorzystaniem tego iteratora.
	*  \param Tab - wska¼nik na pocz±tek tablicy, która ma byæ iterowana.
	*  \post
	*    Iterowane elementy udostêpniane przez iterator mog± byæ
	*    poddane zmianom.
	*/
      VarFaceIter(unsigned int No, ViElemePolyhFace *Tab):
         DireTableIterator<ViElemePolyhFace>(No,Tab) {}
   }; //---------------------------------------------------------------------


   /*!
    * Klasa definiuje iterator dla wspó³rzêdnych 
    * wierzcho³ków bry³y w uk³adzie globalnych wspó³rzêdnych sceny.
    * Obiekty tej klasy s± tworzone i wykorzystywane na poziomie
    * klasy ViElemePolyh przez metodê 
    * \link ViElemePolyh::ConBegin_GlbVtx(unsigned int Idx = 0)const
    *     ViElemePolyh::ConBegin_GlbVtx(unsigned int Idx = 0) const
    * \endlink
    *
    * Przyk³ad u¿ycia iteratora ViElemePolyh::ConVtxIter :
    * \code
    *  // Szuka warto¶ci maksymalnej wspó³rzêdnej x sposród
    *  // wspó³rzêdnych wszystkich wierzcho³ków.
    *  //
    * float SzukajMaksimum(const ViElemePolyh &EPolyh)
    * {
    *   int  x_max = numeric_limits<float>::min();
    * 
    *   for (ViElemePolyh::ConVtxIter Iter = EPolyh.ConBegin_GlbVtx();
    *        Iter;  Iter++) {
    *     if ( Iter->x > x_max ) x_max = Iter->x;
    *   }
    *   return x_max;
    * }
    * \endcode
    */
  class ConVtxIter: public DireTableIterator<const Vector3f> { //------------
     public:
      /*!
       * Inicjalizuje iterator dla danej bry³y elementarnej.
       * \param EPolyh - bry³a elementarna, dla której ma zostaæ 
       *                 zainicjalizowany ten iterator.
       * \param Idx    - indeks pocz±tkowego wierzcho³ka, na który
       *               iterator bêdzie wskazywa³ po jego zainicjalizowaniu.
       */
      ConVtxIter(ViElemePolyh const &EPolyh, unsigned int Idx = 0):
       DireTableIterator<const Vector3f>(EPolyh.GetVtxNo(),EPolyh._GlbVtx,Idx)
        {}
   }; //---------------------------------------------------------------------


   /*!
    * Klasa definiuje iterator dla krawêdzi
    * bry³y, których opis jest w uk³adzie wspó³rzêdnych globalnych sceny.
    * Obiekty tej klasy s± tworzone i wykorzystywane na poziomie
    * klasy ViElemePolyh przez metodê 
    * \link ViElemePolyh::ConBegin_GlbEdge(unsigned int Idx = 0)const
    *     ViElemePolyh::ConBegin_GlbEdge(unsigned int Idx = 0) const
    * \endlink
    *
    * Przyk³ad u¿ycia iteratora ViElemePolyh::ConEdgeIter :
    * \code
    *  // Szuka najd³u¿szej krawêdzi.
    *  //
    * float SzukajNajdluzszej(const ViElemePolyh &EPolyh)
    * {
    *   int       d, d_max = 0;
    *   Vector3f  EVct;
    *
    *   for (ViElemePolyh::ConEdgeIter Iter = EPolyh.ConBegin_GlbEdge();
    *        Iter;  Iter++) {
    *     EVct = Iter->GetFstVtx()-Iter->GetFstVtx();
    *     if ( (d = EVct.Length()) > d_max ) d_max = d;
    *   }
    *   return d_max;
    * }
    * \endcode
    */
   class ConEdgeIter: 
      public ChainTableIterator<const ViElemePolyh,const ViElemePolyhEdge>{
      /*!
       *  Metoda inicjalizuje warto¶æ pola 
       *  \link ChainTableIterator::_Field _Field\endlink dziedziczonego
       *  z klasy ChainTableIterator. Pole 
       *   \link ChainTableIterator::_Field _Field\endlink w tym iteratorze
       *  jest klasy ViElemePolyhEdge.
       * 
       *  Inicjalizacja jest realizowana poprzez
       *  wywo³anie metody
       *  \link ViElemePolyhEdge::SetEdge SetEdge\endlink. Przypisuje
       *  ona wska¼nik na now± krawêd¼. Jest ona okre¶lona przez
       *  zawarto¶æ pola  \link IndiTableIterator::_Idx _Idx\endlink
       *  dziedziczonego po¶rednio z szablonu klasy IndiTableIterator.
       *
       *  Metoda InitField wywo³ywana jest w momencie tworzenia obiektu
       *  oraz przy wowo³aniu metody 
       *  \link ChainTableIterator::Reset Reset\endlink dziedziczonej
       *  z klasy ChainTableIterator.
       */
      void InitField();
      /*!
       *  Metoda aktualizuje warto¶æ pola 
       *  \link ChainTableIterator::_Field _Field\endlink dziedziczonego
       *  z klasy ChainTableIterator. Pole 
       *   \link ChainTableIterator::_Field _Field\endlink w tym iteratorze
       *  jest klasy ViElemePolyhEdge.
       * 
       *  Aktualizacja jest realizowana inidentycznie jak w metodzie
       *  \link ConEdgeIter::InitField InitField\endlink, tzn
       *  poprzez
       *  wywo³anie metody
       *  \link ViElemePolyhEdge::SetEdge SetEdge\endlink. Przypisuje
       *  ona wska¼nik na now± krawêd¼. Jest ona okre¶lona przez
       *  zawarto¶æ pola  \link IndiTableIterator::_Idx _Idx\endlink
       *  dziedziczonego po¶rednio z szablonu klasy IndiTableIterator.
       *
       *  Metoda UpdateField wywo³ywana jest w momencie wywo³ania
       *  operator iteracji.
       */
      void UpdateField();
     public:
      /*!
       *  Inicjalizuje iterator dla danej bry³y elementarnej.
       *  \param EPolyh - referencja do obiektu reprezentuj±cego dan± bry³ê
       *                  elementarn±.
       *  \param Idx    - indeks pocz±tkowej krawêdzi, na któr±
       *               iterator bêdzie wskazywa³ po jego zainicjalizowaniu.
       */
      ConEdgeIter(const ViElemePolyh &EPolyh, unsigned int Idx = 0);
   };


    /*!
     * Konstruktor tworz±c obiekt obowi±zkowo musi inicjowaæ go referencj±
     * do bry³y wzorcowej, z któr± mo¿e byæ zwi±zany przez ca³y okres
     * swojego istnienia.
     * \param PPolyh    - referencja do bry³y wzorcowej,
     * \param IndivName - nazwa bry³y, która bêdzie s³u¿yla do jej 
     *             identyfikacji. Powinna ona byæ unikalna
     *             w ramach danej ¶cie¿ki drzewiastej struktury obiektu
     *             z³o¿onego. Stanowi ona nazwê wêz³a w tej strukturze
     *     (nazwa przechowywana jest w polu dziedziczonej klasy
     *       \link ViNTreeNode ViNTreeNode\endlink).
     *
     *    Nie zak³ada siê, ¿e wymóg ten musi byæ
     *       bezwzglêdnie spe³niony. Jednak jego niespe³nienie mo¿e
     *    prowadziæ do niejednoznaczno¶ci przy zewnêtrznych poleceniach
     *    manipulowania bry³±. 
     */
   ViElemePolyh(ViPattePolyh const &PPolyh, const char *IndivName);

    /*!
     * Konstruktor tworz±c obiekt i wi±¿e go z obiektem opisuj±cym
     * bry³ê wzorcow± (obiekt klasy ViPattePolyh), o ile wska¼nik nie
     * jest równy \p NULL.
     *
     * Konstruktor ten mo¿e byæ u¿yty jako konstruktor bezparametryczny.
     * Powoduje to zainicjalizowanie pola 
     * \link ViElemePolyh::_pPattePolyh _pPattePolyh\endlink wska¼nikiem
     * o warto¶ci \p NULL. Nale¿y wiêc po utworzeniu tego obiektu powi±zaæ
     * go z obiektem opisuj±cym bry³ê wzorcow± za pomoc± metody 
     * \link ViElemePolyh::SetPattePolyh SetPattePolyh\endlink.
     * \param pPolyh    - wska¼nik na obiekt opisuj±cy bry³ê wzorcow±.
     * \param IndivName - nazwa bry³y, która bêdzie s³u¿yla do jej 
     *             identyfikacji. Powinna ona byæ unikalna
     *             w ramach danej ¶cie¿ki drzewiastej struktury obiektu
     *             z³o¿onego. Stanowi ona nazwê wêz³a w tej strukturze
     *     (nazwa przechowywana jest w polu dziedziczonej klasy
     *       \link ViNTreeNode ViNTreeNode\endlink).
     *
     *    Nie zak³ada siê, ¿e wymóg ten musi byæ
     *       bezwzglêdnie spe³niony. Jednak jego niespe³nienie mo¿e
     *    prowadziæ do niejednoznaczno¶ci przy zewnêtrznych poleceniach
     *    manipulowania bry³±. 
     */
   ViElemePolyh(ViPattePolyh const *pPolyh = 0L, const char *IndivName = "");
   virtual ~ViElemePolyh();

    /*!
     * Zwraca warto¶æ identyfikuj±c± klasê ViElemePolyh.
     * Metoda ta nie mo¿e byæ
     * reimplementowana w nastêpnych klasach pochodnych.
     * \retval IT_ELEMEPOLYH - warto¶æ identyfikatora dla klasy
     *      ViElemePolyh (patrz definicja symbolu
     *  \link vintreenode.hh::IT_ELEMEPOLYH
     *      IT_ELEMEPOLYH\endlink.
     */
   int GetInheritorType() const { return IT_ELEMEPOLYH; }


    /*!
     *  Udostêpnia wspó³rzêdne (w uk³adzie wspó³rzêdnych globalnych) 
     *  punktu zaczepienia w³a¶ciwego lokalnego uk³adu wspó³rzêdnych bry³y.
     */
   Vector3f const &IndivCoord_O() const { return _IndividualCoord[0]; }

    /*!
     *  Udostêpnia referencjê (mo¿liwa jest modyfikacja) wspó³rzêdnej
     *  (w uk³adzie wspó³rzêdnych globalnych)
     *  punktu zaczepienia w³a¶ciwego lokalnego uk³adu wspó³rzêdnych bry³y.
     */
   Vector3f       &IndivCoord_O() { return _IndividualCoord[0]; }

    /*!
     *  Udostêpnia wspó³rzêdne (w uk³adzie wspó³rzêdnych globalnych) 
     *  punktu koñca wektora
     *  osi \e OX w³a¶ciwego lokalnego uk³adu wspó³rzêdnych bry³y.
     */
   Vector3f const &IndivCoord_X() const { return _IndividualCoord[1]; }

    /*!
     *  Udostêpnia referencjê (mo¿liwa jest modyfikacja) wspó³rzêdnej
     *  (w uk³adzie wspó³rzêdnych globalnych)
     *  punktu koñca wektora
     *  osi \e OX w³a¶ciwego lokalnego uk³adu wspó³rzêdnych bry³y.
     */
   Vector3f       &IndivCoord_X() { return _IndividualCoord[1]; }


    /*!
     *  Udostêpnia wspó³rzêdne (w uk³adzie wspó³rzêdnych globalnych) 
     *  punktu koñca wektora
     *  osi \e OY w³a¶ciwego lokalnego uk³adu wspó³rzêdnych bry³y.
     */
   Vector3f const &IndivCoord_Y() const { return _IndividualCoord[2]; }

    /*!
     *  Udostêpnia referencjê (mo¿liwa jest modyfikacja) wspó³rzêdnej
     *  (w uk³adzie wspó³rzêdnych globalnych)
     *  punktu koñca wektora
     *  osi \e OY w³a¶ciwego lokalnego uk³adu wspó³rzêdnych bry³y.
     */
   Vector3f       &IndivCoord_Y() { return _IndividualCoord[2]; }


    /*!
     *  Udostêpnia wspó³rzêdne (w uk³adzie wspó³rzêdnych globalnych) 
     *  punktu koñca wektora
     *  osi \e OZ w³a¶ciwego lokalnego uk³adu wspó³rzêdnych bry³y.
     */
   Vector3f const &IndivCoord_Z() const { return _IndividualCoord[3]; }

    /*!
     *  Udostêpnia referencjê (mo¿liwa jest modyfikacja) wspó³rzêdnej
     *  (w uk³adzie wspó³rzêdnych globalnych)
     *  punktu koñca wektora
     *  osi \e OZ w³a¶ciwego lokalnego uk³adu wspó³rzêdnych bry³y.
     */
   Vector3f       &IndivCoord_Z() { return _IndividualCoord[3]; }



    /*!
     *  Inicjalizuje wierzcho³ki w³a¶ciwego lokalne uk³adu wspó³rzêdnych.
     *  Punkt zaczepienia ukladu ustawiany jest na wspó³rzêdne (0,0,0), za¶
     *  koñce wektorów osi otrzymuj± wspó³rzêdne (Axis_Lenght,0,0), 
     *  (0,Axis_Lenght,0), (0,0,Axis_Lenght).
     */
   void  InitIndivCoord(float Axis_Length=10);

    /*!
     *  Oblicza globalne 
     *  wspó³rzêdne globalne wierzcho³ków w³a¶ciwego lokalnego uk³adu
     *  wspó³rzêdnych
     *  (pole \link ViElemePolyh::_IndividualCoord 
     *                                       _IndividualCoord\endlink).
     *  \param M - macierz transformacji z w³a¶ciwego lokalnego uk³adu 
     *         wspó³rzêdnych bry³y do uk³adu globalnego.
     *  \post Obliczone zostaj± warto¶ci wspó³rzêdnych globalnych
     *         wierzcho³ków
     *  w³a¶ciwego lokalnego uk³adu wspó³rzêdnych
     *  (pole \link ViElemePolyh::_IndividualCoord 
     *                                     _IndividualCoord\endlink).
     */
   void  ComputeCoordGlbVtx(MatrixH3f const &M);

    /*!
     *  Oblicza globalne wspó³rzêdne wierzcho³ków bry³y 
     *  (pole \link ViElemePolyh::_GlbVtx _GlbVtx\endlink) oraz
     *  wspó³rzêdne globalne wierzcho³ków w³a¶ciwego lokalnego uk³adu
     *  wspó³rzêdnych
     *  (pole \link ViElemePolyh::_IndividualCoord
     *                              _IndividualCoord\endlink).
     *  \param ObjPos - macierz transformacji z w³a¶ciwego lokalnego uk³adu 
     *         wspó³rzêdnych bry³y do uk³adu globalnego.
     *  \post Obliczone zostaj± warto¶ci wspó³rzêdnych globalnych
     *         wierzcho³ków
     *     bry³y (pole \link ViElemePolyh::_GlbVtx _GlbVtx\endlink) oraz
     *  wspó³rzêdne globalne wierzcho³ków w³a¶ciwego lokalnego uk³adu
     *  wspó³rzêdnych
     *  (pole \link ViElemePolyh::_IndividualCoord
     *                                         _IndividualCoord\endlink).
     *  Zostaj± zaktulizowane dane dotycz±ce obrysu bry³y we wspó³rzêdnych
     *  globalnych (pole \link ViElemePolyh::_GlbOutlineBox 
     *   _GlbOutlineBox\endlink).
     *  Flaga wa¿no¶ci obliczeñ ustawiona zostaje w pozycji:
     *      \e WYNIKI_SA_AKTUALNE.
     *
     */
   void ComputeGlbVtx(MatrixH3f const &ObjPos);

   //@{
    /*! 
     * Udostêpnia referencjê do obiektu sta³ego reprezentuj±cego wielo¶cian
     * wzorcowego
     * (warto¶æ pola \link ViElemePolyh::_pPattePolyh *_pPattePolyh\endlink),
     * który jest baz±
     * dla modelowenej bry³y przez dany obiekt. Ka¿dy obiekt klasy
     * ViPattePolyh jest skojarzony z jednym i tylko jednym obiektem
     * klasy \link ViPattePolyh ViPattePolyh\endlink
     * reprezentuj±c± elementarn± bry³ê wzorcow±.
     */
   const ViPattePolyh &PattPolyh() const { return *_pPattePolyh; }


    /*! 
     * Udostêpnia referencjê do obiektu sta³ego reprezentuj±cego wielo¶cian
     * wzorcowego
     * (warto¶æ pola \link ViElemePolyh::_pPattePolyh *_pPattePolyh\endlink),
     * który jest baz±
     * dla modelowenej bry³y przez dany obiekt. Ka¿dy obiekt klasy
     * ViPattePolyh jest skojarzony z jednym i tylko jednym obiektem
     * klasy \link ViPattePolyh ViPattePolyh\endlink
     * reprezentuj±c± elementarn± bry³ê wzorcow±.
     *
     * Metoda \b PattePolyh jest identyczna z metod± 
     * \link ViElemePolyh::PattPolyh PattPolyh\endlink.
     * Zosta³a wprowadzona jedynie ze wzglêdu na chêæ ujednolicenia
     * nazywnictwa. W przysz³ych wersjach planowane jest wycofanie
     * metody \link ViElemePolyh::PattPolyh PattPolyh\endlink.
     * Nie nast±pi to jednak przed 31.10.2004.
     */
   const ViPattePolyh &PattePolyh() const { return *_pPattePolyh; }


   /*!
    *  Metoda wi±¿e obiekt klasy ViElemePolyh z obiektem klasy ViPattePolyh
    *  opisuj±cym bry³ê wzorcow±. Je¿eli przy tworzeniu obiektu klasy
    *  ViElemePolyh wykorzystany jest konstruktor bezparametryczny,
    *  to metoda zaraz po utwowrzeniu obiektu powinna zostaæ wykorzystana
    *  do powi±zania tych z bry³± wzorcow±. Pos³ugiwanie siê obiektem,
    *  który nie jest powi±zany z ¿adn± bry³± wzorcow± mo¿e doprowadziæ
    *  do b³êdu wykonania programu.
    *   \param pPatt - wska¼nik na obiekt opisuj±cy bry³ê wzorcow±,
    *
    *  \post Zostaje zainicjalizowane pole 
    *   \link ViElemePolyh::_pPattePolyh _pPattePolyh\endlink wska¼nikiem
    *   na obiekt opisuj±cy bry³ê wzorcow±. Ponadto zostaje zainicjalizowana
    *   tablica wierzcho³ków globalnych (pole
    *   \link ViElemePolyh::_GlbVtx _GlbVtx\endlink) oraz tablica
    *    ¶cianek (pole \link ViElemePolyh::_PolyhFaces _PolyhFaces\endlink).
    */
   void SetPattePolyh(const ViPattePolyh *pPatt);
   /*!
    *  Metoda wi±¿e obiekt klasy ViElemePolyh z obiektem klasy ViPattePolyh
    *  opisuj±cym bry³ê wzorcow±. Je¿eli przy tworzeniu obiektu klasy
    *  ViElemePolyh wykorzystany jest konstruktor bezparametryczny,
    *  to metoda zaraz po utwowrzeniu obiektu powinna zostaæ wykorzystana
    *  do powi±zania tych z bry³± wzorcow±. Pos³ugiwanie siê obiektem,
    *  który nie jest powi±zany z ¿adn± bry³± wzorcow± mo¿e doprowadziæ
    *  do b³êdu wykonania programu.
    *   \param Patt - referencja do obiektu opisuj±cego bry³ê wzorcow±,
    *
    *  \post Zostaje zainicjalizowane pole 
    *   \link ViElemePolyh::_pPattePolyh _pPattePolyh\endlink wska¼nikiem
    *   na obiekt opisuj±cy bry³ê wzorcow±. Ponadto zostaje zainicjalizowana
    *   tablica wierzcho³ków globalnych (pole
    *   \link ViElemePolyh::_GlbVtx _GlbVtx\endlink) oraz tablica
    *    ¶cianek (pole \link ViElemePolyh::_PolyhFaces _PolyhFaces\endlink).
    */
   void SetPattePolyh(const ViPattePolyh &Patt)  { SetPattePolyh(&Patt); }
   //@}

    /*!
     *  Udostêpnia warto¶æ flagi selekcji 
     *  (pole \link ViElemePolyh::_Selected _Selected\endlink).
     *  \return \e true - je¶li obiekt jest wyselekcjonowany, 
     *          \e false - w przypadku przeciwnym.
     */
   bool IsSelected() const { return _Selected; }

    /*!
     *  Dokonuje selekcji bry³y w zale¿no¶ci do modu parametru.
     *  \param SelMod - mod seleckji.
     *  \post
     *    W zale¿no¶ci do modu selekcji wykonywana zostaja operajca
     *    na polu \link ViElemePolyh::_Selected _Selected\endlink:
     *    \arg \c NOSELECT - nie zostanie wykonana ¿adna operacja,
     *    \arg \c SELECT - do pola  
     *              \link ViElemePolyh::_Selected _Selected\endlink
     *              wpisana zostanie warto¶æ \c true.
     *    \arg \c UNSELECT - do pola  
     *              \link ViElemePolyh::_Selected _Selected\endlink
     *              wpisana zostanie warto¶æ \c false.
     *    \arg \c XORSELECT - warto¶æ pola
     *             \link ViElemePolyh::_Selected _Selected\endlink
     *              zostaje zanegowana.
     *  \retval true - je¶li nowa warto¶æ pola 
     *            \link ViElemePolyh::_Selected _Selected\endlink
     *             ró¿ni siê od poprzedniej,
     *  \retval false - w przypadku przeciwnym.
     */
   bool SetSelection(unsigned int SelMod);

    /*!
     *  Usuwa selekcjê danego obiektu.
     */
   void SetUnselected() { _Selected = false; }

    /*!
     * Udostêpnia referencjê sta³± do macierzy transformacji z pierwotnego
     * lokalnego uk³adu wspó³rzêdnych obiektu elementarnego do jego
     * w³a¶ciwego
     * lokalnego uk³adu wspó³rzêdnych
     * (pole \link ViElemePolyh::_Mtx_Eleme2Indiv 
     *                            _Mtx_Eleme2Indiv\endlink). 
     */
   const ViMatrix3f &Mtx2IndivCoord() const { return _Mtx_Eleme2Indiv; }

    /*!
     * Udostêpnia referencjê do macierzy transformacji z pierwotnego
     * lokalnego uk³adu wspó³rzêdnych obiektu elementarnego do jego
     * w³a¶ciwego
     * lokalnego uk³adu wspó³rzêdnych
     * (pole \link ViElemePolyh::_Mtx_Eleme2Indiv 
     *                                   _Mtx_Eleme2Indiv\endlink). 
     * Dostêpny w ten sposób obiekty
     * mo¿e byæ modyfikowany.
     */
   ViMatrix3f &Mtx2IndivCoord() { return _Mtx_Eleme2Indiv; }

    /*!
     * Modyfikuje macierz transformacji wspó³rzêdnych wierzcho³ków z 
     * pierwotnego lokalnego uk³adu wspó³rzêdnych bry³y elementarnej
     * do jej w³a¶ciwego lokalnego uk³adu wspó³rzêdnych.
     * \param M - macierz nowych wspó³czynników transformacji.
     * \return zmianie ulegaj± wspó³czynniki macierzy
     *    \link ViElemePolyh::_Mtx_Eleme2Indiv _Mtx_Eleme2Indiv\endlink. 
     */
   void SetMtx2IndivCoord(MatrixH3f::Parameters const &M);

    /*!
     * Modyfikuje macierz transformacji wspó³rzêdnych wierzcho³ków z 
     * pierwotnego lokalnego uk³adu wspó³rzêdnych bry³y elementarnej
     * do jej w³a¶ciwego lokalnego uk³adu wspó³rzêdnych.
     * \param M - nowe macierz wspó³czynników transformacji.
     * \return zmianie ulegaj± wspó³czynniki macierzy
     *    \link ViElemePolyh::_Mtx_Eleme2Indiv _Mtx_Eleme2Indiv\endlink. 
     */
   void SetMtx2IndivCoord(MatrixH3f const &M);

    /*!
     * Modyfikuje macierz transformacji wspó³rzêdnych wierzcho³ków z 
     * lokalnego uk³adu wspó³rzêdnych bry³y wzorcowej
     * (klasa \link ViPattePolyh ViPattePolyh\endlink) do 
     * pierwotnego lokalnego uk³adu wspó³rzêdnych 
     * bry³y elementarnej (ViElemePolyh).
     * \param Param - nowe warto¶ci parametrów transformacji (rotacja,
     *                skala, translacja).
     * \return zmianie ulegaj± wspó³czynniki macierzy
     *    \link ViElemePolyh::_Mtx_Patte2Eleme _Mtx_Patte2Eleme\endlink. 
     * \warning Metoda ta jest identyczna jak metoda jake metoda
     *   \link ViElemePolyh::SetMtx2ElemeCoord SetMtx2ElemeCoord\endlink
     *   i stosowanie tej metody jest zalecane zamiast Mtx2SolidFigCoord.
     *   W przysz³o¶ci metoda Mtx2SolidFigCoord zostanie usuniêta,
     *   jednak nie nast±pi to przed 2004.10.31.
     */
   void SetMtx2SolidFigCoord(MatrixH3f::Parameters const &Param);

    /*!
     * Modyfikuje macierz transformacji wspó³rzêdnych wierzcho³ków z 
     * lokalnego uk³adu wspó³rzêdnych bry³y wzorcowej
     * (klasa \link ViPattePolyh ViPattePolyh\endlink) do uk³adu
     * pierwotnego uk³adu lokalnych wspó³rzêdnych bry³y elementarnej
     * (ViElemePolyh).
     * \param M - nowa macierz wspó³czynników transformacji.
     * \return zmianie ulegaj± wspó³czynniki macierzy
     *    \link ViElemePolyh::_Mtx_Patte2Eleme _Mtx_Patte2Eleme\endlink. 
     * \warning Metoda ta jest identyczna jak metoda jake metoda
     *   \link ViElemePolyh::SetMtx2ElemeCoord SetMtx2ElemeCoord\endlink
     *   i stosowanie tej metody jest zalecane zamiast Mtx2SolidFigCoord.
     *   W przysz³o¶ci metoda Mtx2SolidFigCoord zostanie usuniêta,
     *   jednak nie nast±pi to przed 2004.10.31.
     */
   void SetMtx2SolidFigCoord(MatrixH3f const &M);

     /*!
      *  Udostêpnia referencjê sta³± do macierzy transformacji z uk³adu
      *  wspó³rzêdnych bry³y wzorcowej (obiekt klasy 
      *  \link ViPattePolyh ViPattePolyh\endlink)
      *  do pierwotnego uk³adu wspó³rzêdnych modelowanej bry³y.
      * \warning Metoda ta jest identyczna jak metoda jake metoda
      *   \link ViElemePolyh::Mtx2ElemeCoord Mtx2ElemeCoord\endlink
      *   i stosowanie tej metody jest zalecane zamiast Mtx2SolidFigCoord.
      *   W przysz³o¶ci metoda Mtx2SolidFigCoord zostanie usuniêta,
      *   jednak nie nast±pi to przed 2004.10.31.
      */
   ViMatrix3f const &Mtx2SolidFigCoord() const { return _Mtx_Patte2Eleme; }

     /*!
      *  Udostêpnia referencjê (obiekt mo¿e ulegaæ zmianie) 
      *  do macierzy transformacji z uk³adu wspó³rzêdnych
      *  bry³y wzorcowej (obiekt klasy 
      *  \link ViPattePolyh ViPattePolyh\endlink)
      *  do pierwotnego uk³adu wspó³rzêdnych modelowanej bry³y.
      * \warning Metoda ta jest identyczna jak metoda jake metoda
      *   \link ViElemePolyh::Mtx2ElemeCoord Mtx2ElemeCoord\endlink
      *   i stosowanie tej metody jest zalecane zamiast Mtx2SolidFigCoord.
      *   W przysz³o¶ci metoda Mtx2SolidFigCoord zostanie usuniêta,
      *   jednak nie nast±pi to przed 2004.10.31.
      */
   ViMatrix3f &Mtx2SolidFigCoord() { return _Mtx_Patte2Eleme; }

   //=== Synownimy dla metod ...SolidFigCoord



    /*!
     * Modyfikuje macierz transformacji wspó³rzêdnych wierzcho³ków z 
     * lokalnego uk³adu wspó³rzêdnych bry³y wzorcowej
     * (klasa \link ViPattePolyh ViPattePolyh\endlink) do 
     * pierwotnego lokalnego uk³adu wspó³rzêdnych 
     * bry³y elementarnej (ViElemePolyh).
     * \param Param - nowe warto¶ci parametrów transformacji (rotacja,
     *                skala, translacja).
     * \return zmianie ulegaj± wspó³czynniki macierzy
     *    \link ViElemePolyh::_Mtx_Patte2Eleme _Mtx_Patte2Eleme\endlink. 
     */
   void SetMtx2ElemeCoord(MatrixH3f::Parameters const &Param)
                                            { SetMtx2SolidFigCoord(Param); }

    /*!
     * Modyfikuje macierz transformacji wspó³rzêdnych wierzcho³ków z 
     * lokalnego uk³adu wspó³rzêdnych bry³y wzorcowej
     * (klasa \link ViPattePolyh ViPattePolyh\endlink) do uk³adu
     * pierwotnego uk³adu lokalnych wspó³rzêdnych bry³y elementarnej
     * (ViElemePolyh).
     * \param M - nowa macierz wspó³czynników transformacji.
     * \return zmianie ulegaj± wspó³czynniki macierzy
     *    \link ViElemePolyh::_Mtx_Patte2Eleme _Mtx_Patte2Eleme\endlink. 
     */
   void SetMtx2ElemeCoord(MatrixH3f const &M) { SetMtx2SolidFigCoord(M); }

     /*!
      *  Udostêpnia referencjê sta³± do macierzy transformacji z uk³adu
      *  wspó³rzêdnych bry³y wzorcowej (obiekt klasy 
      *  \link ViPattePolyh ViPattePolyh\endlink)
      *  do pierwotnego uk³adu wspó³rzêdnych modelowanej bry³y.
      */
   const ViMatrix3f &Mtx2ElemeCoord() const { return _Mtx_Patte2Eleme; }

     /*!
      *  Udostêpnia referencjê (obiekt mo¿e ulegaæ zmianie) 
      *  do macierzy transformacji z uk³adu wspó³rzêdnych
      *  bry³y wzorcowej (obiekt klasy 
      *  \link ViPattePolyh ViPattePolyh\endlink)
      *  do pierwotnego uk³adu wspó³rzêdnych modelowanej bry³y.
      */
   ViMatrix3f &Mtx2ElemeCoord() { return _Mtx_Patte2Eleme; }



     /*! 
      *  Udostêpnia referencjê sta³± do pola 
      *  \link ViElemePolyh::_GlbOutlineBox _GlbOutlineBox\endlink
      *  zawieraj±cego prostopad³o¶cienny obrys bry³y.
      */
   OutlineBox3f const &GlbOlnBox() const { return _GlbOutlineBox; }

     /*! 
      *  Udostêpnia referencjê do pola 
      *  \link ViElemePolyh::_GlbOutlineBox _GlbOutlineBox\endlink
      *  zawieraj±cego prostopad³o¶cienny obrys bry³y.
      */     
   OutlineBox3f &GlbOlnBox() { return _GlbOutlineBox; }

     /*!
      * Sprawdza poprawno¶æ przydzia³u pamiêci dla tablicy wierzcho³ków. 
      * \return \e true - gdy pamiêæ zosta³a przydzielona,
      *         \e false - w przypadku przeciwnym.
      */
   bool IsCreatedOK() const { return _GlbVtx != 0L; }

     /*!
      * Udostêpnia referencjê sta³± do struktury danych zawieraj±cych
      * wspó³rzêdne wierzcho³ka wyra¿one w globalnym
      * uk³adzie wspó³rzêdnych sceny.
      * \param Idx - indeks wierzcho³ka 
      * \pre \e Idx nie mo¿e zawieraæ numeru wiêkszego ni¿ rozmiar
      *  tablicy, na któr± wskazuje 
      * \link ViElemePolyh::_GlbVtx _GlbVtx\endlink.
      *  Tak wiêc   0 <= \e Idx < \e N, gdzie \e N jest ilo¶ci± 
      *  wszystkich wierzcho³ków danej bry³y.
      * \return referencjê sta³± (obiekt nie mo¿e ulegaæ zmianie) do obiektu
      *          reprezentuj±cego wierzcho³ek o indeksie \e Idx.
      */
   Vector3f const &GlbVtx(unsigned int Idx) const { return _GlbVtx[Idx];}

     /*!
      * Udostêpnia referencjê do struktury danych zawieraj±cych
      * wspó³rzêdne wierzcho³ka wyra¿one w globalnym
      * uk³adzie wspó³rzêdnych sceny.
      * \param Idx - indeks wierzcho³ka 
      * \pre \e Idx nie mo¿e zawieraæ numeru wiêkszego ni¿ rozmiar
      *  tablicy, na któr± wskazuje 
      * \link ViElemePolyh::_GlbVtx _GlbVtx\endlink.
      *  Tak wiêc   0 <= \e Idx < \e N, gdzie \e N jest ilo¶ci± 
      * wszystkich wierzcho³ków danej bry³y.
      * \return Zwracana jest referencja do wierzcho³ka o indeksie \e Idx.
      */
   Vector3f &GlbVtx(unsigned int Idx) { return _GlbVtx[Idx]; }


    /*!
     * Udostêpnia referencjê sta³± do opisu p³aszczyzny (we wspó³rzêdnych
     * globalnych) danej ¶cianki.
     * \param  FNo - numer ¶cianki.
     * \pre \e FNo - warto¶æ parameteru musi nale¿eæ do przedzia³u [0,N),
     *       gdzie \e N jest ilo¶ci± ¶cianek.
     *       Warto¶æ ta dostêpna jest poprzez metodê 
     *       \link ViElemePolyh::GetFacesNo GetFacesNo\endlink.
     * \return referencjê sta³± do opisu p³aszczyzny (we wspó³rzêdnych
     *         globalnych sceny) ¶cianki o numerze \e FNo.
     */
  Plain3f const &GetRealPlain3f(int FNo) const;


    /*!
     * Udostêpnia iterator sta³y (obiekty odpowiadaj±ce reprezentuj±ce
     * poszczególne ¶cianki, nie mog± ulegaæ zmianom) dla ¶cianek bry³y.
     * Metoda jest przewidziana do usuniêcia. Zalecane jest korzystanie
     * z metody 
     *     \link ViElemePolyh::ConBegin_GlbFace ConBegin_GlbFace\endlink
     */
   ConFaceIter GetFacesIter_Const() const;

    /*!
     * Udostêpnia iterator dla ¶cianek bry³y.
     * Metoda jest przewidziana do usuniêcia. Zalecane jest korzystanie
     * z metody 
     *     \link ViElemePolyh::VarBegin_GlbFace VarBegin_GlbFace\endlink
     */
   VarFaceIter  GetFacesIter();

    /*!
     * Udostêpnia tablicê opisu ¶cianek bry³y wyra¿onych we wspó³rzêdnych
     * globalnych. Zawarto¶æ tablicy mo¿e byæ poddawana zmianom.
     */
   ViElemePolyhFace *GetGlbFacesTab() { return _PolyhFaces; }

    /*!
     * Udostêpnia tablicê opisu ¶cianek bry³y wyra¿onych we wspó³rzêdnych
     * globalnych. Zawarto¶æ tablicy mo¿e byæ poddawana zmianom.
     */
   ViElemePolyhFace *UseGlbFacesTab() { return _PolyhFaces; }


    /*!
     * Udostêpnia tablicê opisu ¶cianek bry³y wyra¿onych we wspó³rzêdnych
     * globalnych. 
     */
   ViElemePolyhFace const *GetGlbFacesTab() const { return _PolyhFaces; }


    /*!
     * Udostêpnia opis ¶cianki (wska¼nik na sta³y obiekt klasy 
     * \link ViElemePolyhFace ViElemePolyhFace\endlink) danej bry³y
     * we wspó³rzêdnych globalnych (wspó³rzêdne wierzcho³ków, równanie
     * p³aszczyzny, wektor normalny).
     * \param  FNo - numer ¶cianki bry³y.
     * \pre \e FNo - warto¶æ parameteru musi nale¿eæ do przedzia³u [0,N),
     *       gdzie \e N jest ilo¶ci± ¶cianek.
     *       Warto¶æ ta dostêpna jest poprzez metodê 
     *       \link ViElemePolyh::GetFacesNo GetFacesNo\endlink.
     * \return wska¼nik na sta³y obiekt klasy 
     *             \link ViElemePolyhFace ViElemePolyhFace\endlink
     *         opisuj±cy dan± ¶ciankê.
     */
   ViElemePolyhFace const *GetElemeFace(int FNo) const;


    /*!
     * Udostêpnia opis ¶cianki (wska¼nik na sta³y obiekt klasy 
     * \link ViFace ViFace\endlink) danej bry³y.
     * \param  FNo - numer ¶cianki bry³y.
     * \pre \e FNo - warto¶æ parameteru musi nale¿eæ do przedzia³u [0,N),
     *       gdzie \e N jest ilo¶ci± ¶cianek.
     *       Warto¶æ ta dostêpna jest poprzez metodê 
     *       \link ViElemePolyh::GetFacesNo GetFacesNo\endlink.
     * \return wska¼nik na sta³y obiekt klasy \link ViFace ViFace\endlink
     *         opisuj±cy dan± ¶ciankê.
     */
   ViFace const *GetPattFace(int FNo) const;

    /*!
     * Zwraca ilo¶æ ¶cianek danej bry³y.
     */
   unsigned int  GetFacesNo()  const;

    /*!
     *  Zwraca ilo¶æ wszystkich wierzcho³ków danej bry³y.
     */
   unsigned int  GetVtxNo() const { return PattPolyh().GetFacesNo(); }

    /*!
     *  Zwraca ilo¶æ wszystkich krawêdzi danej bry³y.
     */
   unsigned int  GetEdgesNo() const { return PattPolyh().GetEdgesNo(); }

    /*!
     * Dokonuje zmiany rozmiaru obiektu. Jednocze¶nie resetuje flagi wa¿no¶ci
     * danych obliczeniowych dla tego obiektu elementarnego.
     * \param ScaX - skala wzd³u¿ osi OX,
     * \param ScaY - skala wzd³u¿ osi OY,
     * \param ScaZ - skala wzd³u¿ osi OZ,
     * \param ValidFlagsForAllParents - warto¶æ parameteru decyduje o tym,
     *               czy zostan± uniewa¿nione flagi sygnalizuj±ce aktualno¶æ
     *               wyznaczonych parametrów (wspó³rzêdnych wierzcho³ków,
     *               normalnych do ¶cianek itd.). Domy¶lnie maj± byæ
     *               uniewa¿nione (\e true).
     * \return
     *     Je¶li  ValidFlagsForAllParents == true, to dla wszystkich przodków
     *  w strukturze drzewiastej danego obiektu ustawiana jest flaga
     *  VFLAG_TEST_DESCENDANTS  sygnalizuj±ca niewa¿no¶æ danych obliczeniowych
     *  jednego z potomków. Skala jest zmieniana w macierzy
     *  \link ViElemePolyh::_Mtx_Eleme2Indiv _Mtx_Eleme2Indiv\endlink.
     *
     *  W przypadku przeciwnym flagi dla przodków nie s± ustawiane.
     */
   void  Resize(float ScaX, float ScaY, float ScaZ, 
                bool ValidFlagsForAllParents=true
               );
    /*!
     * Dokonuje zmiany rozmiaru obiektu. Jednocze¶nie resetuje flagi wa¿no¶ci
     * danych obliczeniowych dla tego obiektu elementarnego.
     * \param Sca - wektor zawieraj±cy wspó³czynnik skali dla poszczególnych
     *              osi, tzn wspó³rzêdna x dla osi OX itd.
     * \param ValidFlagsForAllParents - warto¶æ parameteru decyduje o tym,
     *               czy zostan± uniewa¿nione flagi sygnalizuj±ce aktualno¶æ
     *               wyznaczonych parametrów (wspó³rzêdnych wierzcho³ków,
     *               normalnych do ¶cianek itd.). Domy¶lnie maj± byæ
     *               uniewa¿nione (\e true).
     * \return
     *     Je¶li  ValidFlagsForAllParents == true, to dla wszystkich przodków
     *  w strukturze drzewiastej danego obiektu ustawiana jest flaga
     *  VFLAG_TEST_DESCENDANTS  sygnalizuj±ca niewa¿no¶æ danych obliczeniowych
     *  jednego z potomków. Skala jest zmieniana w macierzy
     *  \link ViElemePolyh::_Mtx_Eleme2Indiv _Mtx_Eleme2Indiv\endlink.
     *
     *  W przypadku przeciwnym flagi dla przodków nie s± ustawiane.
     */
   void  Resize(Vector3f const &Sca, bool ValidFlagsForAllParents=true);

    /*!
     *  Dokonuje translacji w³a¶ciwego uk³adu wspó³rzêdnych bry³y elementarnej
     *  (macierz transformacji
     *  \link ViElemePolyh::_Mtx_Eleme2Indiv _Mtx_Eleme2Indiv\endlink).
     *  wzglêdem jej uk³adu pierwotnego (macierz transformacji
     *  \link ViElemePolyh::_Mtx_Patte2Eleme _Mtx_Patte2Eleme\endlink).
     *  \param Step - wektor translacji.
     *  \return zmodyfikowany zostaje wektor translacji w macierzy
     *    \link ViElemePolyh::_Mtx_Eleme2Indiv _Mtx_Eleme2Indiv\endlink.
     */
   void TranslateIndivCoord(Vector3f const &Step);

   /*!
    * Metoda zapisuje parametry opisu bry³y zwi±zane tylko z klas±
    * ViElemePolyh (bez klasy bazowej).
    * \param Descr - (\b out) wpisywany jest do tego parametru opis
    *                bry³y.
    * \pre Nie jest gwarantowane, ¿e parametr \e Descr jest pusty.
    *      Dlatego te¿ nale¿y przed wszelkimi wpisami "wyczy¶ciæ" go,
    *      tzn. nale¿y wywo³aæ metodê clear().
    */
   void WriteDescriptionTo(ExtString &Descr) const;


   /*!
    *  Metoda na podstawie opisu parametrów charakterystycznych dla danej
    *  klasy (bez uwzglêdnienia parametrów dziedziczonych) inicjalizuje
    *  odpowiednie pola (przyk³ad sk³adni opisu mo¿na znale¼æ na stronie
    *  \ref odczyt-param "Odczyt parametrów opisu bry³y").
    *  Metoda \e InitWithDesc wykorzystywana jest przez funkcje odczytu
    *  z pliku opisu bry³y i tworzenia oraz inicjalizacji obiektów 
    *  sk³adowych.
    *  \param Descr - (\b in) opis prarametrów charakterystycznych dla danej
    *          klasy (z wy³±czeniem parametrów dziedziczonych).
    *  \exception ViException_Patte - gdy nie mo¿e zostaæ znaleziona w bibliotece
    *                  danej sceny bry³a wzorcowa o podanej nazwie.
    *                  W takim przypadku wyj±tek zg³aszany jest z kodem
    *                  b³êdu 
    * \link vierrors.hh::ERRNUM_PATTE__NO_PATTE_POLYH 
    *                    ERRNUM_PATTE__NO_PATTE_POLYH\endlink.
    */
   void InitWithDescr( const ExtString &Descr );


   //=================== Iteratory ========================================
   //----------------- Iterator dla wierzcho³ków --------------------------
    /*!
     * Tworzy iterator do przegl±dania wspó³rzêdnych wierzcho³ków danej
     * bry³y elementarnej w uk³adzie wspó³rzêdnych globalnych.
     * \param Idx - indeks pierwszego elementu tablicy od którgo 
     *              ma zacz±æ siê iteracja.
     * \return iterator dla wierzcho³ków bry³y elementarnej, których
     *         wspó³rzêdne wyra¿one s± w globalnym uk³adzie wspó³rzêdnych
     *         sceny.
     * 
     * Przyk³ad u¿ycia:
     * \code
     *  // Szuka warto¶ci maksymalnej wspó³rzêdnej x sposród
     *  // wspó³rzêdnych wszystkich wierzcho³ków.
     *  //
     * float SzukajMaksimum(const ViElemePolyh &EPolyh)
     * {
     *   int  x_max = numeric_limits<float>::min();
     * 
     *   for (ViElemePolyh::ConVtxIter Iter = EPolyh.ConBegin_GlbVtx();
     *        Iter;  Iter++) {
     *     if ( Iter->x > x_max ) x_max = Iter->x;
     *   }
     *   return x_max;
     * }
     * \endcode
     */
   ConVtxIter ConBegin_GlbVtx(unsigned int Idx = 0) const 
                                        { return ConVtxIter(*this,Idx); }

   //=================== Iteratory ========================================
   //----------------- Iterator dla krawêdzi ------------------------------
    /*!
     * Tworzy iterator do przegl±dania krawêdzi danej
     * bry³y elementarnej w uk³adzie wspó³rzêdnych globalnych.
     * \param Idx - indeks pierwszego elementu tablicy od którgo 
     *              ma zacz±æ siê iteracja.
     * \return iterator dla krawêdzi bry³y elementarnej, których
     *         wspó³rzêdne wierzcho³ków wyra¿one s± w globalnym uk³adzie
     *         wspó³rzêdnych sceny.
     * 
     * Przyk³ad u¿ycia iteratora ViElemePolyh::ConEdgeIter :
     * \code
     *  // Szuka najd³u¿szej krawêdzi.
     *  //
     * float SzukajNajdluzszej(const ViElemePolyh &EPolyh)
     * {
     *   int       d, d_max = 0;
     *   Vector3f  EVct;
     *
     *   for (ViElemePolyh::ConEdgeIter Iter = EPolyh.ConBegin_GlbEdge();
     *        Iter;  Iter++) {
     *     EVct = Iter->GetFstVtx()-Iter->GetFstVtx();
     *     if ( (d = EVct.Length()) > d_max ) d_max = d;
     *   }
     *   return d_max;
     * }
     * \endcode
     */
   ConEdgeIter ConBegin_GlbEdge(unsigned int Idx = 0) const 
                                        { return ConEdgeIter(*this,Idx); }



    /*!
     * Udostêpnia iterator sta³y (obiekty odpowiadaj±ce reprezentuj±ce
     * poszczególne ¶cianki, nie mog± ulegaæ zmianom) dla ¶cianek bry³y.
     */
   ConFaceIter ConBegin_GlbFace() const;

    /*!
     * Udostêpnia iterator dla ¶cianek bry³y.
     */
   VarFaceIter VarBegin_GlbFace();


}; //_________________________________________________________________________



inline
void ViElemePolyh::ConEdgeIter::InitField()
{
  (*(ViElemePolyhEdge*)&_Field).SetEdge(_pOwner->
                                           PattPolyh().GetPolyhEdge(_Idx));
}


inline
void ViElemePolyh::ConEdgeIter::UpdateField()
{
  (*(ViElemePolyhEdge*)&_Field).SetEdge(_pOwner->
                                           PattPolyh().GetPolyhEdge(_Idx));
}


inline
ViElemePolyh::ConEdgeIter::ConEdgeIter( const ViElemePolyh &EPolyh, 
                                        unsigned int        Idx
                                      ):
  ChainTableIterator<const ViElemePolyh,const ViElemePolyhEdge>
      (EPolyh.GetEdgesNo(),&EPolyh) { InitField(); }




inline
ViElemePolyhFace const *ViElemePolyh::GetElemeFace(int FNo) const
{
  return _PolyhFaces+ FNo; 
}


inline
Plain3f const &ViElemePolyh::GetRealPlain3f(int FNo) const 
{ 
  return _PolyhFaces[FNo].GetPlain();
}


#endif
