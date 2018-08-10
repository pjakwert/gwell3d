#ifndef VIELEMEPOLYH_HH
#define VIELEMEPOLYH_HH

/*! \file vielemepolyh.hh
 *  Plik zawiera definicj� klasy ViElemePolyh oraz iterator�w 
 *  �cianek bry�y
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
 * reprezentuj� wielo�ciany modeluj�ce elementarne obiekty
 * na scenie. Ka�dy z nich reprezentuje pewien obiekt wzorcowy
 * (\link ViPattePolyh ViPattePolyh\endlink), z kt�rego 
 * jest otrzymywany
 * poprzez zastosowanie przeskalowania i przetransformowania do swojego
 * w�asnego uk�adu wsp�rz�dnych. Obiekty tej klasy wchodz� w sk�ad
 * obiekt�w z�o�onych (\link ViMultiPolyh ViMultiPolyh\endlink),
 * kt�re s� ich konglomeratami.
 *
 * Ka�dy obiekt klasy ViElemePolyh dysponuje zestawem wsp�rz�dnych
 * globalnych swoich wierzcho�k�w. Przegl�danie ich nale�y dokonywa�
 * w oparciu o iterator ViElemePolyh::ConVtxIter.
 *
 * Przyk�ad u�ycia iteratora ViElemePolyh::ConVtxIter:
 * \code
 *  // Szuka warto�ci maksymalnej wsp�rz�dnej x sposr�d
 *  // wsp�rz�dnych wszystkich wierzcho�k�w.
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
 * Przegl�danie poszczeg�lnych kraw�dzi nale�y dokonywa�
 * w oparciu o iterator ViElemePolyh::ConEdgeIter.
 *
 * Przyk�ad u�ycia iteratora ViElemePolyh::ConEdgeIter:
 * \code
 *  // Szuka najd�u�szej kraw�dzi.
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
   * Pole i zwiazane z nim metody maj� charakter roboczy i wykorzystywane
   * s� tylko w konstrukorze
   * \link ViElemePolyh::ViElemePolyh ViElemePolyh\endlink
   *  oraz w konstrukorze klasy 
   * \link ViElemePolyhFace::ViElemePolyhFace ViElemePolyhFace\endlink.
   */
   static unsigned int _FacesCount;  

 public:

    /*!
     * Metoda MUSI by� u�ywana bezpo�rednio przed tworzeniem tablicy �cianek
     * (patrz \link ViElemePolyh::_PolyhFaces _PolyhFaces\endlink).
     * Wywo�anie metody powoduje wyzerowanie licznika �cianek
     * \link  ViElemePolyh::_FacesCount _FacesCount\endlink, kt�ry jest
     * polem statycznym.
     */
   static void ResetFacesCount() { _FacesCount = 0; }

    /*!
     *  Inkrementuje (o 1) licznik �cianek 
     *  (\link  ViElemePolyh::_FacesCount _FacesCount\endlink).
     */
   static unsigned int IncFacesCount() { return _FacesCount++; }
 
 private:

    /*!
     * Referencja do obiektu wzorcowego, z kt�rego otrzymywany jest 
     * model reprezentowanej bry�y przez obiekt klasy ViPattePolyh.
     * Jest on otrzymywany poprzez przeskalowanie i przetransformowanie
     * (patrz macierze transformacji: 
     *  \link ViElemePolyh::_Mtx_Patte2Eleme _Mtx_Patte2Eleme\endlink
     * oraz \link ViElemePolyh::_Mtx_Eleme2Indiv _Mtx_Eleme2Indiv\endlink)
     * do lokalnego uk�adu wsp�rz�dnych
     * modelowanej bry�y.
     */
   ViPattePolyh const * _pPattePolyh;

    /*!
     *  Macierz transformacji przej�cia z uk�adu 
     *  wsp�rz�dnych wzorcowej bry�y (reprezentowanej przez obiekt
     *  klasy \link ViPattePolyh ViPattePolyh\endlink) do uk�adu
     *  wsp�rz�dnych tego obiektu.
     */
   ViMatrix3f        _Mtx_Patte2Eleme;

    /*!
     * Transformacja z uk�adu wielo�cianu do uk�adu okre�lonego przez 
     * u�ytkownika. Pozwala to przesun�� uk�ad wsp�rz�dnych. Jest to 
     * konieczne, aby mie� swobod� w lokalizowaniu i orientowaniu osi 
     * obrotu (np. przegubu) wzgl�dem wcze�niejszego
     * elementu w �a�cuchu kinematycznym.
     */
   ViMatrix3f        _Mtx_Eleme2Indiv;

    /*!
     *  Wska�nik na tablic� (tablica tworzona jest dynamicznie w
     *  konstruktorze) wsp�rz�dnych
     *  wierzcho�k�w w uk�adzie wsp�rz�dnych globalnych (tzn. 
     *  uk�adzie wsp�rz�dnych sceny). 
     */
   Vector3f         *_GlbVtx;      
           
    /*!
     *  Wska�nik na tablic� (tablica tworzona jest dynamicznie w
     *  konstruktorze)
     *  zawieraj�c� informacje dotycz�ce poszczeg�lnych �cianek wyra�one w 
     *  uk�adzie wsp�rz�dnych globalnych (np. wsp�rz�dne wektora 
     *  normalnego danej �cianki).
     */                  
   ViElemePolyhFace *_PolyhFaces; 

    /*!
     *  Zawiera wsp�rz�dne prostopad�o�cianu b�d�cego obrysem danej bry�y
     *  (w uk�adzie wsp�rz�dnych globalnych). Prostopad�o�cian tworzony
     *  jest w ten spos�b, �e jego poszczeg�lne �cianki s� r�wnoleg�e 
     *  do p�aszczyzn \e OXY, \e OXZ, \e OYZ.
     */
   OutlineBox3f      _GlbOutlineBox;

    /*!
     *  Informuje o tym czy obiekt jest wyselekcjonowany 
     *  (\p true - tak, \p false - nie).
     */
   bool              _Selected;  

  protected:

    /*!
     *  Wierzcho�ki w�a�ciwego lokalnego uk�adu wsp�rz�dnych wielo�cianu 
     *  Jest to struktura pomocnicza stworzona z my�l� o wizualizacji.
     *  
     *  Kolejne elementy tablicy odpowiadaj� punktom: 
     *                0 - \e O, 1 - \e X, 2 - \e Y, 3 - \e Z.
     */
   Vector3f         _IndividualCoord[4];



  public:

   /*!
    * Iteratory dla �cianek, dla kt�rych wsp�rz�dne wierzcho�k�w wyra�one s�
    * w globalnym uk�adzie wsp�rz�dnych. Za pomoc� tego iteratora otrzymywane
    * s� obiekty sta�e (tzn. \b const \link ViElemePolyhFace 
    * ViElemePolyhFace\endlink).
    */
   class ConFaceIter: public DireTableIterator<const ViElemePolyhFace> {
     public:
       /*!
	*  Konstruktor inicjalizuje iterator ustawiaj�c w nim wska�nik 
	*  pocz�tku tablicy i jej ilo�ci element�w, kt�re mag� by�
	*  przegl�dane z wykorzystaniem tego iteratora.
	*  \param No - ilo�� element�w tablicy, kt�re mog� by� przegl�dane
	*              z wykorzystaniem tego iteratora.
	*  \param Tab - wska�nik na pocz�tek tablicy, kt�ra ma by� iterowana.
	*  \post
	*    Iterowane elementy udost�pniane przez iterator nie mog� by�
	*    zmieniane.
	*/
      ConFaceIter(unsigned int No, ViElemePolyhFace const *Tab):
          DireTableIterator<const ViElemePolyhFace>(No,Tab) {}
   }; //---------------------------------------------------------------------

   /*!
    * Iteratory dla �cianek, dla kt�rych wsp�rz�dne wierzcho�k�w wyra�one s�
    * w globalnym uk�adzie wsp�rz�dnych. Za pomoc� tego iteratora otrzymywane
    * s� obiekty klasy \link ViElemePolyhFace ViElemePolyhFace\endlink.
    */
 class VarFaceIter: public DireTableIterator<ViElemePolyhFace> { //----------
     public:
       /*!
	*  Konstruktor inicjalizuje iterator ustawiaj�c w nim wska�nik 
	*  pocz�tku tablicy i jej ilo�ci element�w, kt�re mag� by�
	*  przegl�dane z wykorzystaniem tego iteratora.
	*  \param No - ilo�� element�w tablicy, kt�re mog� by� przegl�dane
	*              z wykorzystaniem tego iteratora.
	*  \param Tab - wska�nik na pocz�tek tablicy, kt�ra ma by� iterowana.
	*  \post
	*    Iterowane elementy udost�pniane przez iterator mog� by�
	*    poddane zmianom.
	*/
      VarFaceIter(unsigned int No, ViElemePolyhFace *Tab):
         DireTableIterator<ViElemePolyhFace>(No,Tab) {}
   }; //---------------------------------------------------------------------


   /*!
    * Klasa definiuje iterator dla wsp�rz�dnych 
    * wierzcho�k�w bry�y w uk�adzie globalnych wsp�rz�dnych sceny.
    * Obiekty tej klasy s� tworzone i wykorzystywane na poziomie
    * klasy ViElemePolyh przez metod� 
    * \link ViElemePolyh::ConBegin_GlbVtx(unsigned int Idx = 0)const
    *     ViElemePolyh::ConBegin_GlbVtx(unsigned int Idx = 0) const
    * \endlink
    *
    * Przyk�ad u�ycia iteratora ViElemePolyh::ConVtxIter :
    * \code
    *  // Szuka warto�ci maksymalnej wsp�rz�dnej x sposr�d
    *  // wsp�rz�dnych wszystkich wierzcho�k�w.
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
       * Inicjalizuje iterator dla danej bry�y elementarnej.
       * \param EPolyh - bry�a elementarna, dla kt�rej ma zosta� 
       *                 zainicjalizowany ten iterator.
       * \param Idx    - indeks pocz�tkowego wierzcho�ka, na kt�ry
       *               iterator b�dzie wskazywa� po jego zainicjalizowaniu.
       */
      ConVtxIter(ViElemePolyh const &EPolyh, unsigned int Idx = 0):
       DireTableIterator<const Vector3f>(EPolyh.GetVtxNo(),EPolyh._GlbVtx,Idx)
        {}
   }; //---------------------------------------------------------------------


   /*!
    * Klasa definiuje iterator dla kraw�dzi
    * bry�y, kt�rych opis jest w uk�adzie wsp�rz�dnych globalnych sceny.
    * Obiekty tej klasy s� tworzone i wykorzystywane na poziomie
    * klasy ViElemePolyh przez metod� 
    * \link ViElemePolyh::ConBegin_GlbEdge(unsigned int Idx = 0)const
    *     ViElemePolyh::ConBegin_GlbEdge(unsigned int Idx = 0) const
    * \endlink
    *
    * Przyk�ad u�ycia iteratora ViElemePolyh::ConEdgeIter :
    * \code
    *  // Szuka najd�u�szej kraw�dzi.
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
       *  Metoda inicjalizuje warto�� pola 
       *  \link ChainTableIterator::_Field _Field\endlink dziedziczonego
       *  z klasy ChainTableIterator. Pole 
       *   \link ChainTableIterator::_Field _Field\endlink w tym iteratorze
       *  jest klasy ViElemePolyhEdge.
       * 
       *  Inicjalizacja jest realizowana poprzez
       *  wywo�anie metody
       *  \link ViElemePolyhEdge::SetEdge SetEdge\endlink. Przypisuje
       *  ona wska�nik na now� kraw�d�. Jest ona okre�lona przez
       *  zawarto�� pola  \link IndiTableIterator::_Idx _Idx\endlink
       *  dziedziczonego po�rednio z szablonu klasy IndiTableIterator.
       *
       *  Metoda InitField wywo�ywana jest w momencie tworzenia obiektu
       *  oraz przy wowo�aniu metody 
       *  \link ChainTableIterator::Reset Reset\endlink dziedziczonej
       *  z klasy ChainTableIterator.
       */
      void InitField();
      /*!
       *  Metoda aktualizuje warto�� pola 
       *  \link ChainTableIterator::_Field _Field\endlink dziedziczonego
       *  z klasy ChainTableIterator. Pole 
       *   \link ChainTableIterator::_Field _Field\endlink w tym iteratorze
       *  jest klasy ViElemePolyhEdge.
       * 
       *  Aktualizacja jest realizowana inidentycznie jak w metodzie
       *  \link ConEdgeIter::InitField InitField\endlink, tzn
       *  poprzez
       *  wywo�anie metody
       *  \link ViElemePolyhEdge::SetEdge SetEdge\endlink. Przypisuje
       *  ona wska�nik na now� kraw�d�. Jest ona okre�lona przez
       *  zawarto�� pola  \link IndiTableIterator::_Idx _Idx\endlink
       *  dziedziczonego po�rednio z szablonu klasy IndiTableIterator.
       *
       *  Metoda UpdateField wywo�ywana jest w momencie wywo�ania
       *  operator iteracji.
       */
      void UpdateField();
     public:
      /*!
       *  Inicjalizuje iterator dla danej bry�y elementarnej.
       *  \param EPolyh - referencja do obiektu reprezentuj�cego dan� bry��
       *                  elementarn�.
       *  \param Idx    - indeks pocz�tkowej kraw�dzi, na kt�r�
       *               iterator b�dzie wskazywa� po jego zainicjalizowaniu.
       */
      ConEdgeIter(const ViElemePolyh &EPolyh, unsigned int Idx = 0);
   };


    /*!
     * Konstruktor tworz�c obiekt obowi�zkowo musi inicjowa� go referencj�
     * do bry�y wzorcowej, z kt�r� mo�e by� zwi�zany przez ca�y okres
     * swojego istnienia.
     * \param PPolyh    - referencja do bry�y wzorcowej,
     * \param IndivName - nazwa bry�y, kt�ra b�dzie s�u�yla do jej 
     *             identyfikacji. Powinna ona by� unikalna
     *             w ramach danej �cie�ki drzewiastej struktury obiektu
     *             z�o�onego. Stanowi ona nazw� w�z�a w tej strukturze
     *     (nazwa przechowywana jest w polu dziedziczonej klasy
     *       \link ViNTreeNode ViNTreeNode\endlink).
     *
     *    Nie zak�ada si�, �e wym�g ten musi by�
     *       bezwzgl�dnie spe�niony. Jednak jego niespe�nienie mo�e
     *    prowadzi� do niejednoznaczno�ci przy zewn�trznych poleceniach
     *    manipulowania bry��. 
     */
   ViElemePolyh(ViPattePolyh const &PPolyh, const char *IndivName);

    /*!
     * Konstruktor tworz�c obiekt i wi��e go z obiektem opisuj�cym
     * bry�� wzorcow� (obiekt klasy ViPattePolyh), o ile wska�nik nie
     * jest r�wny \p NULL.
     *
     * Konstruktor ten mo�e by� u�yty jako konstruktor bezparametryczny.
     * Powoduje to zainicjalizowanie pola 
     * \link ViElemePolyh::_pPattePolyh _pPattePolyh\endlink wska�nikiem
     * o warto�ci \p NULL. Nale�y wi�c po utworzeniu tego obiektu powi�za�
     * go z obiektem opisuj�cym bry�� wzorcow� za pomoc� metody 
     * \link ViElemePolyh::SetPattePolyh SetPattePolyh\endlink.
     * \param pPolyh    - wska�nik na obiekt opisuj�cy bry�� wzorcow�.
     * \param IndivName - nazwa bry�y, kt�ra b�dzie s�u�yla do jej 
     *             identyfikacji. Powinna ona by� unikalna
     *             w ramach danej �cie�ki drzewiastej struktury obiektu
     *             z�o�onego. Stanowi ona nazw� w�z�a w tej strukturze
     *     (nazwa przechowywana jest w polu dziedziczonej klasy
     *       \link ViNTreeNode ViNTreeNode\endlink).
     *
     *    Nie zak�ada si�, �e wym�g ten musi by�
     *       bezwzgl�dnie spe�niony. Jednak jego niespe�nienie mo�e
     *    prowadzi� do niejednoznaczno�ci przy zewn�trznych poleceniach
     *    manipulowania bry��. 
     */
   ViElemePolyh(ViPattePolyh const *pPolyh = 0L, const char *IndivName = "");
   virtual ~ViElemePolyh();

    /*!
     * Zwraca warto�� identyfikuj�c� klas� ViElemePolyh.
     * Metoda ta nie mo�e by�
     * reimplementowana w nast�pnych klasach pochodnych.
     * \retval IT_ELEMEPOLYH - warto�� identyfikatora dla klasy
     *      ViElemePolyh (patrz definicja symbolu
     *  \link vintreenode.hh::IT_ELEMEPOLYH
     *      IT_ELEMEPOLYH\endlink.
     */
   int GetInheritorType() const { return IT_ELEMEPOLYH; }


    /*!
     *  Udost�pnia wsp�rz�dne (w uk�adzie wsp�rz�dnych globalnych) 
     *  punktu zaczepienia w�a�ciwego lokalnego uk�adu wsp�rz�dnych bry�y.
     */
   Vector3f const &IndivCoord_O() const { return _IndividualCoord[0]; }

    /*!
     *  Udost�pnia referencj� (mo�liwa jest modyfikacja) wsp�rz�dnej
     *  (w uk�adzie wsp�rz�dnych globalnych)
     *  punktu zaczepienia w�a�ciwego lokalnego uk�adu wsp�rz�dnych bry�y.
     */
   Vector3f       &IndivCoord_O() { return _IndividualCoord[0]; }

    /*!
     *  Udost�pnia wsp�rz�dne (w uk�adzie wsp�rz�dnych globalnych) 
     *  punktu ko�ca wektora
     *  osi \e OX w�a�ciwego lokalnego uk�adu wsp�rz�dnych bry�y.
     */
   Vector3f const &IndivCoord_X() const { return _IndividualCoord[1]; }

    /*!
     *  Udost�pnia referencj� (mo�liwa jest modyfikacja) wsp�rz�dnej
     *  (w uk�adzie wsp�rz�dnych globalnych)
     *  punktu ko�ca wektora
     *  osi \e OX w�a�ciwego lokalnego uk�adu wsp�rz�dnych bry�y.
     */
   Vector3f       &IndivCoord_X() { return _IndividualCoord[1]; }


    /*!
     *  Udost�pnia wsp�rz�dne (w uk�adzie wsp�rz�dnych globalnych) 
     *  punktu ko�ca wektora
     *  osi \e OY w�a�ciwego lokalnego uk�adu wsp�rz�dnych bry�y.
     */
   Vector3f const &IndivCoord_Y() const { return _IndividualCoord[2]; }

    /*!
     *  Udost�pnia referencj� (mo�liwa jest modyfikacja) wsp�rz�dnej
     *  (w uk�adzie wsp�rz�dnych globalnych)
     *  punktu ko�ca wektora
     *  osi \e OY w�a�ciwego lokalnego uk�adu wsp�rz�dnych bry�y.
     */
   Vector3f       &IndivCoord_Y() { return _IndividualCoord[2]; }


    /*!
     *  Udost�pnia wsp�rz�dne (w uk�adzie wsp�rz�dnych globalnych) 
     *  punktu ko�ca wektora
     *  osi \e OZ w�a�ciwego lokalnego uk�adu wsp�rz�dnych bry�y.
     */
   Vector3f const &IndivCoord_Z() const { return _IndividualCoord[3]; }

    /*!
     *  Udost�pnia referencj� (mo�liwa jest modyfikacja) wsp�rz�dnej
     *  (w uk�adzie wsp�rz�dnych globalnych)
     *  punktu ko�ca wektora
     *  osi \e OZ w�a�ciwego lokalnego uk�adu wsp�rz�dnych bry�y.
     */
   Vector3f       &IndivCoord_Z() { return _IndividualCoord[3]; }



    /*!
     *  Inicjalizuje wierzcho�ki w�a�ciwego lokalne uk�adu wsp�rz�dnych.
     *  Punkt zaczepienia ukladu ustawiany jest na wsp�rz�dne (0,0,0), za�
     *  ko�ce wektor�w osi otrzymuj� wsp�rz�dne (Axis_Lenght,0,0), 
     *  (0,Axis_Lenght,0), (0,0,Axis_Lenght).
     */
   void  InitIndivCoord(float Axis_Length=10);

    /*!
     *  Oblicza globalne 
     *  wsp�rz�dne globalne wierzcho�k�w w�a�ciwego lokalnego uk�adu
     *  wsp�rz�dnych
     *  (pole \link ViElemePolyh::_IndividualCoord 
     *                                       _IndividualCoord\endlink).
     *  \param M - macierz transformacji z w�a�ciwego lokalnego uk�adu 
     *         wsp�rz�dnych bry�y do uk�adu globalnego.
     *  \post Obliczone zostaj� warto�ci wsp�rz�dnych globalnych
     *         wierzcho�k�w
     *  w�a�ciwego lokalnego uk�adu wsp�rz�dnych
     *  (pole \link ViElemePolyh::_IndividualCoord 
     *                                     _IndividualCoord\endlink).
     */
   void  ComputeCoordGlbVtx(MatrixH3f const &M);

    /*!
     *  Oblicza globalne wsp�rz�dne wierzcho�k�w bry�y 
     *  (pole \link ViElemePolyh::_GlbVtx _GlbVtx\endlink) oraz
     *  wsp�rz�dne globalne wierzcho�k�w w�a�ciwego lokalnego uk�adu
     *  wsp�rz�dnych
     *  (pole \link ViElemePolyh::_IndividualCoord
     *                              _IndividualCoord\endlink).
     *  \param ObjPos - macierz transformacji z w�a�ciwego lokalnego uk�adu 
     *         wsp�rz�dnych bry�y do uk�adu globalnego.
     *  \post Obliczone zostaj� warto�ci wsp�rz�dnych globalnych
     *         wierzcho�k�w
     *     bry�y (pole \link ViElemePolyh::_GlbVtx _GlbVtx\endlink) oraz
     *  wsp�rz�dne globalne wierzcho�k�w w�a�ciwego lokalnego uk�adu
     *  wsp�rz�dnych
     *  (pole \link ViElemePolyh::_IndividualCoord
     *                                         _IndividualCoord\endlink).
     *  Zostaj� zaktulizowane dane dotycz�ce obrysu bry�y we wsp�rz�dnych
     *  globalnych (pole \link ViElemePolyh::_GlbOutlineBox 
     *   _GlbOutlineBox\endlink).
     *  Flaga wa�no�ci oblicze� ustawiona zostaje w pozycji:
     *      \e WYNIKI_SA_AKTUALNE.
     *
     */
   void ComputeGlbVtx(MatrixH3f const &ObjPos);

   //@{
    /*! 
     * Udost�pnia referencj� do obiektu sta�ego reprezentuj�cego wielo�cian
     * wzorcowego
     * (warto�� pola \link ViElemePolyh::_pPattePolyh *_pPattePolyh\endlink),
     * kt�ry jest baz�
     * dla modelowenej bry�y przez dany obiekt. Ka�dy obiekt klasy
     * ViPattePolyh jest skojarzony z jednym i tylko jednym obiektem
     * klasy \link ViPattePolyh ViPattePolyh\endlink
     * reprezentuj�c� elementarn� bry�� wzorcow�.
     */
   const ViPattePolyh &PattPolyh() const { return *_pPattePolyh; }


    /*! 
     * Udost�pnia referencj� do obiektu sta�ego reprezentuj�cego wielo�cian
     * wzorcowego
     * (warto�� pola \link ViElemePolyh::_pPattePolyh *_pPattePolyh\endlink),
     * kt�ry jest baz�
     * dla modelowenej bry�y przez dany obiekt. Ka�dy obiekt klasy
     * ViPattePolyh jest skojarzony z jednym i tylko jednym obiektem
     * klasy \link ViPattePolyh ViPattePolyh\endlink
     * reprezentuj�c� elementarn� bry�� wzorcow�.
     *
     * Metoda \b PattePolyh jest identyczna z metod� 
     * \link ViElemePolyh::PattPolyh PattPolyh\endlink.
     * Zosta�a wprowadzona jedynie ze wzgl�du na ch�� ujednolicenia
     * nazywnictwa. W przysz�ych wersjach planowane jest wycofanie
     * metody \link ViElemePolyh::PattPolyh PattPolyh\endlink.
     * Nie nast�pi to jednak przed 31.10.2004.
     */
   const ViPattePolyh &PattePolyh() const { return *_pPattePolyh; }


   /*!
    *  Metoda wi��e obiekt klasy ViElemePolyh z obiektem klasy ViPattePolyh
    *  opisuj�cym bry�� wzorcow�. Je�eli przy tworzeniu obiektu klasy
    *  ViElemePolyh wykorzystany jest konstruktor bezparametryczny,
    *  to metoda zaraz po utwowrzeniu obiektu powinna zosta� wykorzystana
    *  do powi�zania tych z bry�� wzorcow�. Pos�ugiwanie si� obiektem,
    *  kt�ry nie jest powi�zany z �adn� bry�� wzorcow� mo�e doprowadzi�
    *  do b��du wykonania programu.
    *   \param pPatt - wska�nik na obiekt opisuj�cy bry�� wzorcow�,
    *
    *  \post Zostaje zainicjalizowane pole 
    *   \link ViElemePolyh::_pPattePolyh _pPattePolyh\endlink wska�nikiem
    *   na obiekt opisuj�cy bry�� wzorcow�. Ponadto zostaje zainicjalizowana
    *   tablica wierzcho�k�w globalnych (pole
    *   \link ViElemePolyh::_GlbVtx _GlbVtx\endlink) oraz tablica
    *    �cianek (pole \link ViElemePolyh::_PolyhFaces _PolyhFaces\endlink).
    */
   void SetPattePolyh(const ViPattePolyh *pPatt);
   /*!
    *  Metoda wi��e obiekt klasy ViElemePolyh z obiektem klasy ViPattePolyh
    *  opisuj�cym bry�� wzorcow�. Je�eli przy tworzeniu obiektu klasy
    *  ViElemePolyh wykorzystany jest konstruktor bezparametryczny,
    *  to metoda zaraz po utwowrzeniu obiektu powinna zosta� wykorzystana
    *  do powi�zania tych z bry�� wzorcow�. Pos�ugiwanie si� obiektem,
    *  kt�ry nie jest powi�zany z �adn� bry�� wzorcow� mo�e doprowadzi�
    *  do b��du wykonania programu.
    *   \param Patt - referencja do obiektu opisuj�cego bry�� wzorcow�,
    *
    *  \post Zostaje zainicjalizowane pole 
    *   \link ViElemePolyh::_pPattePolyh _pPattePolyh\endlink wska�nikiem
    *   na obiekt opisuj�cy bry�� wzorcow�. Ponadto zostaje zainicjalizowana
    *   tablica wierzcho�k�w globalnych (pole
    *   \link ViElemePolyh::_GlbVtx _GlbVtx\endlink) oraz tablica
    *    �cianek (pole \link ViElemePolyh::_PolyhFaces _PolyhFaces\endlink).
    */
   void SetPattePolyh(const ViPattePolyh &Patt)  { SetPattePolyh(&Patt); }
   //@}

    /*!
     *  Udost�pnia warto�� flagi selekcji 
     *  (pole \link ViElemePolyh::_Selected _Selected\endlink).
     *  \return \e true - je�li obiekt jest wyselekcjonowany, 
     *          \e false - w przypadku przeciwnym.
     */
   bool IsSelected() const { return _Selected; }

    /*!
     *  Dokonuje selekcji bry�y w zale�no�ci do modu parametru.
     *  \param SelMod - mod seleckji.
     *  \post
     *    W zale�no�ci do modu selekcji wykonywana zostaja operajca
     *    na polu \link ViElemePolyh::_Selected _Selected\endlink:
     *    \arg \c NOSELECT - nie zostanie wykonana �adna operacja,
     *    \arg \c SELECT - do pola  
     *              \link ViElemePolyh::_Selected _Selected\endlink
     *              wpisana zostanie warto�� \c true.
     *    \arg \c UNSELECT - do pola  
     *              \link ViElemePolyh::_Selected _Selected\endlink
     *              wpisana zostanie warto�� \c false.
     *    \arg \c XORSELECT - warto�� pola
     *             \link ViElemePolyh::_Selected _Selected\endlink
     *              zostaje zanegowana.
     *  \retval true - je�li nowa warto�� pola 
     *            \link ViElemePolyh::_Selected _Selected\endlink
     *             r�ni si� od poprzedniej,
     *  \retval false - w przypadku przeciwnym.
     */
   bool SetSelection(unsigned int SelMod);

    /*!
     *  Usuwa selekcj� danego obiektu.
     */
   void SetUnselected() { _Selected = false; }

    /*!
     * Udost�pnia referencj� sta�� do macierzy transformacji z pierwotnego
     * lokalnego uk�adu wsp�rz�dnych obiektu elementarnego do jego
     * w�a�ciwego
     * lokalnego uk�adu wsp�rz�dnych
     * (pole \link ViElemePolyh::_Mtx_Eleme2Indiv 
     *                            _Mtx_Eleme2Indiv\endlink). 
     */
   const ViMatrix3f &Mtx2IndivCoord() const { return _Mtx_Eleme2Indiv; }

    /*!
     * Udost�pnia referencj� do macierzy transformacji z pierwotnego
     * lokalnego uk�adu wsp�rz�dnych obiektu elementarnego do jego
     * w�a�ciwego
     * lokalnego uk�adu wsp�rz�dnych
     * (pole \link ViElemePolyh::_Mtx_Eleme2Indiv 
     *                                   _Mtx_Eleme2Indiv\endlink). 
     * Dost�pny w ten spos�b obiekty
     * mo�e by� modyfikowany.
     */
   ViMatrix3f &Mtx2IndivCoord() { return _Mtx_Eleme2Indiv; }

    /*!
     * Modyfikuje macierz transformacji wsp�rz�dnych wierzcho�k�w z 
     * pierwotnego lokalnego uk�adu wsp�rz�dnych bry�y elementarnej
     * do jej w�a�ciwego lokalnego uk�adu wsp�rz�dnych.
     * \param M - macierz nowych wsp�czynnik�w transformacji.
     * \return zmianie ulegaj� wsp�czynniki macierzy
     *    \link ViElemePolyh::_Mtx_Eleme2Indiv _Mtx_Eleme2Indiv\endlink. 
     */
   void SetMtx2IndivCoord(MatrixH3f::Parameters const &M);

    /*!
     * Modyfikuje macierz transformacji wsp�rz�dnych wierzcho�k�w z 
     * pierwotnego lokalnego uk�adu wsp�rz�dnych bry�y elementarnej
     * do jej w�a�ciwego lokalnego uk�adu wsp�rz�dnych.
     * \param M - nowe macierz wsp�czynnik�w transformacji.
     * \return zmianie ulegaj� wsp�czynniki macierzy
     *    \link ViElemePolyh::_Mtx_Eleme2Indiv _Mtx_Eleme2Indiv\endlink. 
     */
   void SetMtx2IndivCoord(MatrixH3f const &M);

    /*!
     * Modyfikuje macierz transformacji wsp�rz�dnych wierzcho�k�w z 
     * lokalnego uk�adu wsp�rz�dnych bry�y wzorcowej
     * (klasa \link ViPattePolyh ViPattePolyh\endlink) do 
     * pierwotnego lokalnego uk�adu wsp�rz�dnych 
     * bry�y elementarnej (ViElemePolyh).
     * \param Param - nowe warto�ci parametr�w transformacji (rotacja,
     *                skala, translacja).
     * \return zmianie ulegaj� wsp�czynniki macierzy
     *    \link ViElemePolyh::_Mtx_Patte2Eleme _Mtx_Patte2Eleme\endlink. 
     * \warning Metoda ta jest identyczna jak metoda jake metoda
     *   \link ViElemePolyh::SetMtx2ElemeCoord SetMtx2ElemeCoord\endlink
     *   i stosowanie tej metody jest zalecane zamiast Mtx2SolidFigCoord.
     *   W przysz�o�ci metoda Mtx2SolidFigCoord zostanie usuni�ta,
     *   jednak nie nast�pi to przed 2004.10.31.
     */
   void SetMtx2SolidFigCoord(MatrixH3f::Parameters const &Param);

    /*!
     * Modyfikuje macierz transformacji wsp�rz�dnych wierzcho�k�w z 
     * lokalnego uk�adu wsp�rz�dnych bry�y wzorcowej
     * (klasa \link ViPattePolyh ViPattePolyh\endlink) do uk�adu
     * pierwotnego uk�adu lokalnych wsp�rz�dnych bry�y elementarnej
     * (ViElemePolyh).
     * \param M - nowa macierz wsp�czynnik�w transformacji.
     * \return zmianie ulegaj� wsp�czynniki macierzy
     *    \link ViElemePolyh::_Mtx_Patte2Eleme _Mtx_Patte2Eleme\endlink. 
     * \warning Metoda ta jest identyczna jak metoda jake metoda
     *   \link ViElemePolyh::SetMtx2ElemeCoord SetMtx2ElemeCoord\endlink
     *   i stosowanie tej metody jest zalecane zamiast Mtx2SolidFigCoord.
     *   W przysz�o�ci metoda Mtx2SolidFigCoord zostanie usuni�ta,
     *   jednak nie nast�pi to przed 2004.10.31.
     */
   void SetMtx2SolidFigCoord(MatrixH3f const &M);

     /*!
      *  Udost�pnia referencj� sta�� do macierzy transformacji z uk�adu
      *  wsp�rz�dnych bry�y wzorcowej (obiekt klasy 
      *  \link ViPattePolyh ViPattePolyh\endlink)
      *  do pierwotnego uk�adu wsp�rz�dnych modelowanej bry�y.
      * \warning Metoda ta jest identyczna jak metoda jake metoda
      *   \link ViElemePolyh::Mtx2ElemeCoord Mtx2ElemeCoord\endlink
      *   i stosowanie tej metody jest zalecane zamiast Mtx2SolidFigCoord.
      *   W przysz�o�ci metoda Mtx2SolidFigCoord zostanie usuni�ta,
      *   jednak nie nast�pi to przed 2004.10.31.
      */
   ViMatrix3f const &Mtx2SolidFigCoord() const { return _Mtx_Patte2Eleme; }

     /*!
      *  Udost�pnia referencj� (obiekt mo�e ulega� zmianie) 
      *  do macierzy transformacji z uk�adu wsp�rz�dnych
      *  bry�y wzorcowej (obiekt klasy 
      *  \link ViPattePolyh ViPattePolyh\endlink)
      *  do pierwotnego uk�adu wsp�rz�dnych modelowanej bry�y.
      * \warning Metoda ta jest identyczna jak metoda jake metoda
      *   \link ViElemePolyh::Mtx2ElemeCoord Mtx2ElemeCoord\endlink
      *   i stosowanie tej metody jest zalecane zamiast Mtx2SolidFigCoord.
      *   W przysz�o�ci metoda Mtx2SolidFigCoord zostanie usuni�ta,
      *   jednak nie nast�pi to przed 2004.10.31.
      */
   ViMatrix3f &Mtx2SolidFigCoord() { return _Mtx_Patte2Eleme; }

   //=== Synownimy dla metod ...SolidFigCoord



    /*!
     * Modyfikuje macierz transformacji wsp�rz�dnych wierzcho�k�w z 
     * lokalnego uk�adu wsp�rz�dnych bry�y wzorcowej
     * (klasa \link ViPattePolyh ViPattePolyh\endlink) do 
     * pierwotnego lokalnego uk�adu wsp�rz�dnych 
     * bry�y elementarnej (ViElemePolyh).
     * \param Param - nowe warto�ci parametr�w transformacji (rotacja,
     *                skala, translacja).
     * \return zmianie ulegaj� wsp�czynniki macierzy
     *    \link ViElemePolyh::_Mtx_Patte2Eleme _Mtx_Patte2Eleme\endlink. 
     */
   void SetMtx2ElemeCoord(MatrixH3f::Parameters const &Param)
                                            { SetMtx2SolidFigCoord(Param); }

    /*!
     * Modyfikuje macierz transformacji wsp�rz�dnych wierzcho�k�w z 
     * lokalnego uk�adu wsp�rz�dnych bry�y wzorcowej
     * (klasa \link ViPattePolyh ViPattePolyh\endlink) do uk�adu
     * pierwotnego uk�adu lokalnych wsp�rz�dnych bry�y elementarnej
     * (ViElemePolyh).
     * \param M - nowa macierz wsp�czynnik�w transformacji.
     * \return zmianie ulegaj� wsp�czynniki macierzy
     *    \link ViElemePolyh::_Mtx_Patte2Eleme _Mtx_Patte2Eleme\endlink. 
     */
   void SetMtx2ElemeCoord(MatrixH3f const &M) { SetMtx2SolidFigCoord(M); }

     /*!
      *  Udost�pnia referencj� sta�� do macierzy transformacji z uk�adu
      *  wsp�rz�dnych bry�y wzorcowej (obiekt klasy 
      *  \link ViPattePolyh ViPattePolyh\endlink)
      *  do pierwotnego uk�adu wsp�rz�dnych modelowanej bry�y.
      */
   const ViMatrix3f &Mtx2ElemeCoord() const { return _Mtx_Patte2Eleme; }

     /*!
      *  Udost�pnia referencj� (obiekt mo�e ulega� zmianie) 
      *  do macierzy transformacji z uk�adu wsp�rz�dnych
      *  bry�y wzorcowej (obiekt klasy 
      *  \link ViPattePolyh ViPattePolyh\endlink)
      *  do pierwotnego uk�adu wsp�rz�dnych modelowanej bry�y.
      */
   ViMatrix3f &Mtx2ElemeCoord() { return _Mtx_Patte2Eleme; }



     /*! 
      *  Udost�pnia referencj� sta�� do pola 
      *  \link ViElemePolyh::_GlbOutlineBox _GlbOutlineBox\endlink
      *  zawieraj�cego prostopad�o�cienny obrys bry�y.
      */
   OutlineBox3f const &GlbOlnBox() const { return _GlbOutlineBox; }

     /*! 
      *  Udost�pnia referencj� do pola 
      *  \link ViElemePolyh::_GlbOutlineBox _GlbOutlineBox\endlink
      *  zawieraj�cego prostopad�o�cienny obrys bry�y.
      */     
   OutlineBox3f &GlbOlnBox() { return _GlbOutlineBox; }

     /*!
      * Sprawdza poprawno�� przydzia�u pami�ci dla tablicy wierzcho�k�w. 
      * \return \e true - gdy pami�� zosta�a przydzielona,
      *         \e false - w przypadku przeciwnym.
      */
   bool IsCreatedOK() const { return _GlbVtx != 0L; }

     /*!
      * Udost�pnia referencj� sta�� do struktury danych zawieraj�cych
      * wsp�rz�dne wierzcho�ka wyra�one w globalnym
      * uk�adzie wsp�rz�dnych sceny.
      * \param Idx - indeks wierzcho�ka 
      * \pre \e Idx nie mo�e zawiera� numeru wi�kszego ni� rozmiar
      *  tablicy, na kt�r� wskazuje 
      * \link ViElemePolyh::_GlbVtx _GlbVtx\endlink.
      *  Tak wi�c   0 <= \e Idx < \e N, gdzie \e N jest ilo�ci� 
      *  wszystkich wierzcho�k�w danej bry�y.
      * \return referencj� sta�� (obiekt nie mo�e ulega� zmianie) do obiektu
      *          reprezentuj�cego wierzcho�ek o indeksie \e Idx.
      */
   Vector3f const &GlbVtx(unsigned int Idx) const { return _GlbVtx[Idx];}

     /*!
      * Udost�pnia referencj� do struktury danych zawieraj�cych
      * wsp�rz�dne wierzcho�ka wyra�one w globalnym
      * uk�adzie wsp�rz�dnych sceny.
      * \param Idx - indeks wierzcho�ka 
      * \pre \e Idx nie mo�e zawiera� numeru wi�kszego ni� rozmiar
      *  tablicy, na kt�r� wskazuje 
      * \link ViElemePolyh::_GlbVtx _GlbVtx\endlink.
      *  Tak wi�c   0 <= \e Idx < \e N, gdzie \e N jest ilo�ci� 
      * wszystkich wierzcho�k�w danej bry�y.
      * \return Zwracana jest referencja do wierzcho�ka o indeksie \e Idx.
      */
   Vector3f &GlbVtx(unsigned int Idx) { return _GlbVtx[Idx]; }


    /*!
     * Udost�pnia referencj� sta�� do opisu p�aszczyzny (we wsp�rz�dnych
     * globalnych) danej �cianki.
     * \param  FNo - numer �cianki.
     * \pre \e FNo - warto�� parameteru musi nale�e� do przedzia�u [0,N),
     *       gdzie \e N jest ilo�ci� �cianek.
     *       Warto�� ta dost�pna jest poprzez metod� 
     *       \link ViElemePolyh::GetFacesNo GetFacesNo\endlink.
     * \return referencj� sta�� do opisu p�aszczyzny (we wsp�rz�dnych
     *         globalnych sceny) �cianki o numerze \e FNo.
     */
  Plain3f const &GetRealPlain3f(int FNo) const;


    /*!
     * Udost�pnia iterator sta�y (obiekty odpowiadaj�ce reprezentuj�ce
     * poszczeg�lne �cianki, nie mog� ulega� zmianom) dla �cianek bry�y.
     * Metoda jest przewidziana do usuni�cia. Zalecane jest korzystanie
     * z metody 
     *     \link ViElemePolyh::ConBegin_GlbFace ConBegin_GlbFace\endlink
     */
   ConFaceIter GetFacesIter_Const() const;

    /*!
     * Udost�pnia iterator dla �cianek bry�y.
     * Metoda jest przewidziana do usuni�cia. Zalecane jest korzystanie
     * z metody 
     *     \link ViElemePolyh::VarBegin_GlbFace VarBegin_GlbFace\endlink
     */
   VarFaceIter  GetFacesIter();

    /*!
     * Udost�pnia tablic� opisu �cianek bry�y wyra�onych we wsp�rz�dnych
     * globalnych. Zawarto�� tablicy mo�e by� poddawana zmianom.
     */
   ViElemePolyhFace *GetGlbFacesTab() { return _PolyhFaces; }

    /*!
     * Udost�pnia tablic� opisu �cianek bry�y wyra�onych we wsp�rz�dnych
     * globalnych. Zawarto�� tablicy mo�e by� poddawana zmianom.
     */
   ViElemePolyhFace *UseGlbFacesTab() { return _PolyhFaces; }


    /*!
     * Udost�pnia tablic� opisu �cianek bry�y wyra�onych we wsp�rz�dnych
     * globalnych. 
     */
   ViElemePolyhFace const *GetGlbFacesTab() const { return _PolyhFaces; }


    /*!
     * Udost�pnia opis �cianki (wska�nik na sta�y obiekt klasy 
     * \link ViElemePolyhFace ViElemePolyhFace\endlink) danej bry�y
     * we wsp�rz�dnych globalnych (wsp�rz�dne wierzcho�k�w, r�wnanie
     * p�aszczyzny, wektor normalny).
     * \param  FNo - numer �cianki bry�y.
     * \pre \e FNo - warto�� parameteru musi nale�e� do przedzia�u [0,N),
     *       gdzie \e N jest ilo�ci� �cianek.
     *       Warto�� ta dost�pna jest poprzez metod� 
     *       \link ViElemePolyh::GetFacesNo GetFacesNo\endlink.
     * \return wska�nik na sta�y obiekt klasy 
     *             \link ViElemePolyhFace ViElemePolyhFace\endlink
     *         opisuj�cy dan� �ciank�.
     */
   ViElemePolyhFace const *GetElemeFace(int FNo) const;


    /*!
     * Udost�pnia opis �cianki (wska�nik na sta�y obiekt klasy 
     * \link ViFace ViFace\endlink) danej bry�y.
     * \param  FNo - numer �cianki bry�y.
     * \pre \e FNo - warto�� parameteru musi nale�e� do przedzia�u [0,N),
     *       gdzie \e N jest ilo�ci� �cianek.
     *       Warto�� ta dost�pna jest poprzez metod� 
     *       \link ViElemePolyh::GetFacesNo GetFacesNo\endlink.
     * \return wska�nik na sta�y obiekt klasy \link ViFace ViFace\endlink
     *         opisuj�cy dan� �ciank�.
     */
   ViFace const *GetPattFace(int FNo) const;

    /*!
     * Zwraca ilo�� �cianek danej bry�y.
     */
   unsigned int  GetFacesNo()  const;

    /*!
     *  Zwraca ilo�� wszystkich wierzcho�k�w danej bry�y.
     */
   unsigned int  GetVtxNo() const { return PattPolyh().GetFacesNo(); }

    /*!
     *  Zwraca ilo�� wszystkich kraw�dzi danej bry�y.
     */
   unsigned int  GetEdgesNo() const { return PattPolyh().GetEdgesNo(); }

    /*!
     * Dokonuje zmiany rozmiaru obiektu. Jednocze�nie resetuje flagi wa�no�ci
     * danych obliczeniowych dla tego obiektu elementarnego.
     * \param ScaX - skala wzd�u� osi OX,
     * \param ScaY - skala wzd�u� osi OY,
     * \param ScaZ - skala wzd�u� osi OZ,
     * \param ValidFlagsForAllParents - warto�� parameteru decyduje o tym,
     *               czy zostan� uniewa�nione flagi sygnalizuj�ce aktualno��
     *               wyznaczonych parametr�w (wsp�rz�dnych wierzcho�k�w,
     *               normalnych do �cianek itd.). Domy�lnie maj� by�
     *               uniewa�nione (\e true).
     * \return
     *     Je�li  ValidFlagsForAllParents == true, to dla wszystkich przodk�w
     *  w strukturze drzewiastej danego obiektu ustawiana jest flaga
     *  VFLAG_TEST_DESCENDANTS  sygnalizuj�ca niewa�no�� danych obliczeniowych
     *  jednego z potomk�w. Skala jest zmieniana w macierzy
     *  \link ViElemePolyh::_Mtx_Eleme2Indiv _Mtx_Eleme2Indiv\endlink.
     *
     *  W przypadku przeciwnym flagi dla przodk�w nie s� ustawiane.
     */
   void  Resize(float ScaX, float ScaY, float ScaZ, 
                bool ValidFlagsForAllParents=true
               );
    /*!
     * Dokonuje zmiany rozmiaru obiektu. Jednocze�nie resetuje flagi wa�no�ci
     * danych obliczeniowych dla tego obiektu elementarnego.
     * \param Sca - wektor zawieraj�cy wsp�czynnik skali dla poszczeg�lnych
     *              osi, tzn wsp�rz�dna x dla osi OX itd.
     * \param ValidFlagsForAllParents - warto�� parameteru decyduje o tym,
     *               czy zostan� uniewa�nione flagi sygnalizuj�ce aktualno��
     *               wyznaczonych parametr�w (wsp�rz�dnych wierzcho�k�w,
     *               normalnych do �cianek itd.). Domy�lnie maj� by�
     *               uniewa�nione (\e true).
     * \return
     *     Je�li  ValidFlagsForAllParents == true, to dla wszystkich przodk�w
     *  w strukturze drzewiastej danego obiektu ustawiana jest flaga
     *  VFLAG_TEST_DESCENDANTS  sygnalizuj�ca niewa�no�� danych obliczeniowych
     *  jednego z potomk�w. Skala jest zmieniana w macierzy
     *  \link ViElemePolyh::_Mtx_Eleme2Indiv _Mtx_Eleme2Indiv\endlink.
     *
     *  W przypadku przeciwnym flagi dla przodk�w nie s� ustawiane.
     */
   void  Resize(Vector3f const &Sca, bool ValidFlagsForAllParents=true);

    /*!
     *  Dokonuje translacji w�a�ciwego uk�adu wsp�rz�dnych bry�y elementarnej
     *  (macierz transformacji
     *  \link ViElemePolyh::_Mtx_Eleme2Indiv _Mtx_Eleme2Indiv\endlink).
     *  wzgl�dem jej uk�adu pierwotnego (macierz transformacji
     *  \link ViElemePolyh::_Mtx_Patte2Eleme _Mtx_Patte2Eleme\endlink).
     *  \param Step - wektor translacji.
     *  \return zmodyfikowany zostaje wektor translacji w macierzy
     *    \link ViElemePolyh::_Mtx_Eleme2Indiv _Mtx_Eleme2Indiv\endlink.
     */
   void TranslateIndivCoord(Vector3f const &Step);

   /*!
    * Metoda zapisuje parametry opisu bry�y zwi�zane tylko z klas�
    * ViElemePolyh (bez klasy bazowej).
    * \param Descr - (\b out) wpisywany jest do tego parametru opis
    *                bry�y.
    * \pre Nie jest gwarantowane, �e parametr \e Descr jest pusty.
    *      Dlatego te� nale�y przed wszelkimi wpisami "wyczy�ci�" go,
    *      tzn. nale�y wywo�a� metod� clear().
    */
   void WriteDescriptionTo(ExtString &Descr) const;


   /*!
    *  Metoda na podstawie opisu parametr�w charakterystycznych dla danej
    *  klasy (bez uwzgl�dnienia parametr�w dziedziczonych) inicjalizuje
    *  odpowiednie pola (przyk�ad sk�adni opisu mo�na znale�� na stronie
    *  \ref odczyt-param "Odczyt parametr�w opisu bry�y").
    *  Metoda \e InitWithDesc wykorzystywana jest przez funkcje odczytu
    *  z pliku opisu bry�y i tworzenia oraz inicjalizacji obiekt�w 
    *  sk�adowych.
    *  \param Descr - (\b in) opis prarametr�w charakterystycznych dla danej
    *          klasy (z wy��czeniem parametr�w dziedziczonych).
    *  \exception ViException_Patte - gdy nie mo�e zosta� znaleziona w bibliotece
    *                  danej sceny bry�a wzorcowa o podanej nazwie.
    *                  W takim przypadku wyj�tek zg�aszany jest z kodem
    *                  b��du 
    * \link vierrors.hh::ERRNUM_PATTE__NO_PATTE_POLYH 
    *                    ERRNUM_PATTE__NO_PATTE_POLYH\endlink.
    */
   void InitWithDescr( const ExtString &Descr );


   //=================== Iteratory ========================================
   //----------------- Iterator dla wierzcho�k�w --------------------------
    /*!
     * Tworzy iterator do przegl�dania wsp�rz�dnych wierzcho�k�w danej
     * bry�y elementarnej w uk�adzie wsp�rz�dnych globalnych.
     * \param Idx - indeks pierwszego elementu tablicy od kt�rgo 
     *              ma zacz�� si� iteracja.
     * \return iterator dla wierzcho�k�w bry�y elementarnej, kt�rych
     *         wsp�rz�dne wyra�one s� w globalnym uk�adzie wsp�rz�dnych
     *         sceny.
     * 
     * Przyk�ad u�ycia:
     * \code
     *  // Szuka warto�ci maksymalnej wsp�rz�dnej x sposr�d
     *  // wsp�rz�dnych wszystkich wierzcho�k�w.
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
   //----------------- Iterator dla kraw�dzi ------------------------------
    /*!
     * Tworzy iterator do przegl�dania kraw�dzi danej
     * bry�y elementarnej w uk�adzie wsp�rz�dnych globalnych.
     * \param Idx - indeks pierwszego elementu tablicy od kt�rgo 
     *              ma zacz�� si� iteracja.
     * \return iterator dla kraw�dzi bry�y elementarnej, kt�rych
     *         wsp�rz�dne wierzcho�k�w wyra�one s� w globalnym uk�adzie
     *         wsp�rz�dnych sceny.
     * 
     * Przyk�ad u�ycia iteratora ViElemePolyh::ConEdgeIter :
     * \code
     *  // Szuka najd�u�szej kraw�dzi.
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
     * Udost�pnia iterator sta�y (obiekty odpowiadaj�ce reprezentuj�ce
     * poszczeg�lne �cianki, nie mog� ulega� zmianom) dla �cianek bry�y.
     */
   ConFaceIter ConBegin_GlbFace() const;

    /*!
     * Udost�pnia iterator dla �cianek bry�y.
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
