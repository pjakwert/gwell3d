#ifndef VIFACE_HH
#define VIFACE_HH

/*!
 * \file  viface.hh
 * \author	Bogdan Kreczmer
 * \date	2003.09
 *
 * Plik zawiera definicj� klasy \link ViFace ViFace\endlink modeluj�cej
 * pojedyncz� �ciank� bry�y wzorcowej.
 */


#ifdef __GNUG__
#pragma interface
#endif


#include <iostream>
#include "viexception.hh"
#include "vifaceedge.hh"
#include "inditableiterator.hh"
#include "chaintableiterator.hh"
#include "vitriangle3f.hh"

class ViPattePolyh;
class ViEdge;



/*!
 * Klasa ViType opisuje pojedyncza �ciank� bry�y wzorcowej.
 * Klasa ta zawiera tablic� numer�w wierzcho�k�w, kt�re le�� na obwodzie
 * danej �cianki. Dost�pne (w spos�b po�redni) s� wsp�rz�dne wierzcho�k�w
 * (znajduj� si� one w tablicy obiektu klasy 
 * \link ViPattePolyh ViPattePolyh\endlink).
 * Numery wierzcho�k�w wymieniane s� po kolei zgodnie z ich u�o�eniem na
 * obwodzie �cianki w kierunku przeciwnym do ruchu wskaz�wek zegara.
 *
 * Tablica numerow wierzcho�k�w danej �cianki dost�pna jest poprzez pole
 * \link ViFace::_NodeSet _NodeSet\endlink. 
 * Tablica ta zorganizowana jest w nast�puj�cy spos�b:
 *    W pierwszym elemencie przechowywana jest ilo�� wszystkich wierzcho�k�w,
 *    Od nast�pnego elementu rozpoczyna si� w�a�ciwa tablica numer�w 
 *    wierzcho�kow. 
 *    W���ciwy dost�p do tej tablicy zapewnia metoda 
 * \link ViFace::GetFaceVtxTable GetFaceVtxTable\endlink 
 *    za� do pierwszego elementu metoda 
 * \link ViFace::GetVtxNo GetVtxNo\endlink.
 */
class ViFace  {
    /*!
     * Referencja do obiektu modeluj�cego bry��, do kt�rej to bry�y nale�y
     * �cianka reprezentowana przez ten obiekt.
     */
   ViPattePolyh &_Owner;
    /*!
     * W tej chwili to pole nie jest wykorzystywane. Przewidziane jest do
     * zapisu informacji o ilo�ci wierzcho�k�w danej �cianki.
     */
   unsigned int  _NodesNo;
    /*!
     * Tablica numer�w wierzcho�k�w �cianki. Numery odnosz� si� do tablicy
     * wszystkich wierzcho�k�w znajduj�cej si� dost�pnych poprzez pole
     * ViPattePolyh::_Vertex obiektu modeluj�ceg dan� bry��.
     * Sam obiekt klasy \b ViFace znajduje si� w tablicy dost�pnej poprzez
     * pole ViPattePolyh::_Faces.
     */
   unsigned int *_NodeSet;
    /*!
     * Zawiera tablic� wska�nik�w do obiekt�w zawieraj�cych informacje
     * o kraw�dziach danej �cianki. Porz�dek element�w tablicy, jak te�
     * porz�dek wierzcho�k�w dla ka�dek kraw�dzi dost�pnych poprzez
     * te obiekty, jest zgodny z orientacj� brzegu �cianki.
     */
   ViFaceEdge **_EdgesSet;
    /*!
     *  Wektor normalny do powierzchni �cianki. Wektor wskazuje kierunek
     *  na zewn�trz �cianki.
     */
   Vector3f _NormVct;


    /*!
     *  Pole ma charakter roboczy. Wykorzystywane jest przy wydrukach
     *  realizowany za pomoc� przeci��enia operatora << dla ostream.
     *  La�cuch znak�w dost�pny poprzez to pole pojawia si� zawsze przed
     *  wy�wietleniam danych dotycz�cych danej kraw�dzi. Je�eli adresem
     *  tego pola jest NULL, to przyjmuje si�, �e wy�wietla si�
     *  �a�cuch pusty.
     */  
   char const *_PrintPrefix;    

 public:
   //-------------------- ViFace::ConEdgeIter -----------------------------
   /*!
    *  Iterator wykorzystywany jest do iteracji kolejnych kraw�dzi
    *  �cianki danej bry�y. Udost�pniane kraw�dzie reprezentowane
    *  s� przez obiekty klasy ViFaceEdge.
    */
   class ConEdgeIter: 
         public IndiTableIterator<const ViFaceEdge* const, const ViFaceEdge> {
     public:
     /*!
      *  Inicjalizuje iterator kraw�dzi.
      *  \param No - rozmiar iterowanej tablicy,
      *  \param Tab - wska�nik na iterowan� tablic� kraw�dzi,
      *  \param Idx - pocz�tkowa warto�� indeksu pocz�tkowego elementu
      *               dla iteracji.
      */
      ConEdgeIter(unsigned int No, ViFaceEdge * const *Tab, int Idx = 0 ):
        IndiTableIterator<const ViFaceEdge* const, 
                          const ViFaceEdge>(No,Tab,Idx) {}
     /*!
      *  Konwerter udost�pnia wska�nik na bie��cy element tablicy.
      */
     operator const ViFaceEdge* () const { return _BasePtr[_Idx]; }
     /*!
      *  Udost�pnia referencj� do bie��cego elementu tablicy.
      */
     const ViFaceEdge &operator *  () const { return *_BasePtr[_Idx]; }
     /*!
      *  Konwerter udost�pnia wska�nik na bie��cy element tablicy.
      */
     const ViFaceEdge *operator -> () const { return _BasePtr[_Idx]; } 

   };
   //-------------------- ViFace::ConEdgeIterator -----------------------------

   //-------------------- ViFace::ConTriaIterator -----------------------------
  /*!
   *  Klasa ta pe�ni rol� iteratora dla danej �cianki. Umo�liwia ona
   *  iteracj� �cianki w postaci pokrywaj�cych j� tr�jk�t�w.
   */  
  class ConTriaIter: 
     public ChainTableIterator<const ViFace, const ViTriangle3f> {

     /*!
      * Metoda jest wywo�ywana po ka�dorazowej iteracji i aktualizuje
      * pole \link ChainTableIterator::_Field _Field\endlink dziedziczone
      * z szablonu ChainTableIterator. W pole to wpisywane s� wierzcho�ki
      * nast�pnego tr�jk�ta danej �cianki.
      */ 
    void UpdateField();

     /*!
      * Metoda jest wywo�ywana po zainicjalizwaniu iteratora oraz
      * przy wykonywaniu operacja 
      * \link ChainTableIterator::Reset\endlink.
      * Metoda inicjalizuje pole 
      * ChainTableIterator::_Field dziedziczone z szablonu ChainTableIterator.
      * Do zainicjalizowanego pola wpisane zostaj� wierzcho�ki pierwszego
      * tr�jk�ta danej �cianki.
      */ 
    void InitField();

   public:
     /*!
      *  Inicjalizuje iterator kojarz�c go z dan� tablic�.
      *  \param  Face - referencja do �cianki, dla kt�rej ma by� wywo�any ten
      *                 iterator.
      *  \param  No - ilo�� element�w tablicy,
      *  \param  Idx - warto�� pocz�tkowa indeksu.
      *  \pre  2 <= \e Idx < \e No;
      *  \post Je�eli warto�� \e Idx nie spe�nia warunku pocz�tkowego,
      *      to zg�aszany jest wyj�tek 
      *      \link ViException_OutOfRange ViException_OutOfRange\endlink
      *     przez konstruktor szablon IndiTableIterator.
      *      Jako numer b��du ma warto�� 
      *  \link vierrors.hh::ERRNUM_TABITER_BADINIT
      *                                     ERRNUM_TABITER_BADINIT\endlink,
      *   za� jako numer pomocniczy: 2.
      *      W przypadku przeciwnym pole
      *      \link IndiTableIterator::_OpStatus _OpStatus\endlink
      *     dziedziczone z IndiTableIterator
      *        inicjalizowane jest warto�ci� \p true.
      *  Je�eli \e Idx < 2, to zg�aszany jest wyj�tek ViException_OutOfRange
      *  z numerem b��du
      *  \link vierrors.hh::ERRNUM_FACE_IDXBELOW2
      *                                     ERRNUM_FACE_IDXBELOW2\endlink,
      *   za� jako numer pomocniczy: 0.
      *
      *  Je�eli wszystko jest poprawnie to wywo�ywana jest metoda 
      *  \link ConTriaIter::InitField InitField\endlink do 
      *  inicjalizacji pola  
      *  \link ConTriaIter::_Field _Field\endlink.
      */
     ConTriaIter( const ViFace   *Face, 
                  unsigned int    No, 
                  unsigned int   Idx = 2 
                );
  };
   //-------------------- ViFace::ConTriaIterator -----------------------------

      /*!
       * Inicjalizuje obiekt przydzielaj�c mu w���ciela, kt�rym jest obiekt
       * klasy ViPattePolyh. Musi on modelowa� bry��, kt�rej �ciank� ma
       * reprezentowa� ten tworzony obiekt.
       *
       * \param Owner - obiekt modeluj�cy bry�� posiadaj�c� dan� �ciank�.
       */
   ViFace( ViPattePolyh &Owner ): _Owner(Owner), _NodesNo(0), _NodeSet(0L),
       _EdgesSet(0)  { _PrintPrefix = 0L; }
   ~ViFace();

    /*!
     * Udost�pnia nazw� bry�y wzorcowej, w kt�rej sk�ad wchodzi
     * �cianka reprezentowana przez ten obiekt.
     */
   const char *GetName() const;

    /*!
     * Udost�pnia sw�j indeks, jaki ma w tablicy
     * ViPattePolyh::_Faces.
     */
   unsigned int GetMyIdx() const;

    /*!
     * Alokuje pami�� dla tablicy numer�w wierzcho�k�w.
     */
   int CreateNodeTable( unsigned int NodeNo );

      //----------------------------------------------------------------------
      // Inicjuje tablic� numer�w wierzcho�k�w. -----------------------------
   int InitNodeIndexTable( unsigned int *Tab );

      //----------------------------------------------------------------------
      // Alokuje pami�� dla tablicy numer�w wierzcho�k�w i j� inicjuje. ------
      //
   int CreateAndInitNodeIndexTable( unsigned int *Tab );

    /*!
     * Inicjalizuje tablic� kraw�dzi.
     */
   void InitEdgesSet();
    /*!
     * Zwalnia pami�� zaj�t� przez tablic� kraw�dzi.
     */
   void DestroyEdgesSet();
   
    /*!
     *  Inicjalizuje wektor normalny dla danej �cianki.
     *  Wektor wyliczany jest na podstawie dw�ch pierwszych bok�w,
     *  kt�re nie s� wsp�lniowe.
     *  \pre Zak�ada si�, �e �cianka jest wypuk�a.
     *  \post Je�li obliczenia nie mog� zako�czy� si� powodzeniem
     *     (wierzcho�ki le�� na jednej prostej), to zg�aszany jest
     *     wyj�tek ViException_WrongComputation.
     */
   void InitNormVect();

   /*!
    * Udost�pnia wektor normalny �cianki.
    */
  const Vector3f &GetNormVect() const { return _NormVct; }

      /*!
       * Udost�pnia indeks wierzcho�ka. Jest on indeksem pozycji w tablicy
       * ViPattePolyh::_Vertex. Przechowywane s� tam wsp�rz�dne tego
       * wierzcho�ka.
       * \param VtxNo - numer wierzcho�ka dla danej �cianki.
       * \return zwraca indeks wierzcho�ka.
       *
       * Przyk�ad u�ycia (na poziomie tej klasy):
       * \code
       *   _Owner.GetPattePolyhVtx(GetVtxIdx(VtxNo));
       * \endcode
       * Powy�sza operacja r�wnowa�na jest wywo�aniu metody:
       * \code
       *  GetFaceVtx(VtxNo);
       * \endcode
       */
   unsigned int GetVtxIdx(int VtxNo) const { return _NodeSet[VtxNo+1]; }

      /*!
       * Udost�pnia tablic� numer�w wierzcho�k�w. 
       */
   unsigned int *GetFaceVtxTable() const
         { return _NodeSet+1; }

      /*!
       * Udost�pnia ilo�� wierzcho�k�w danej �cianki.
       */
   unsigned int  GetVtxNo()  const { return *_NodeSet; }

      //----------------------------------------------------------------------
      // Udost�pnia ws�rz�dne danego wierzcho�ka o numerze VtxNo. -----------
      //
   Vector3f const &GetFaceVtx(unsigned int VtxNo) const;

      //----------------------------------------------------------------------
      // Bezpieczne Udost�pnienie ws�rz�dnych wierzcho�ka o numerze VtxNo. --
      //
   Vector3f const &SGetFaceVtx(unsigned int VtxNo) const 
                                               throw (ViException_OutOfRange);

      //----------------------------------------------------------------------
      // Udost�pnienia wskaznik do s�siaduj�cej �cianki o numerze No. --------
      //
   ViFace const *GetNeighbor(unsigned int No) const;

      //----------------------------------------------------------------------
      // Udost�pnienia indeks obiektu w tablicy. -----------------------------
      //
   unsigned int GetFaceIdx() const;

      //----------------------------------------------------------------------
      // Udost�pnienia wybran� krew�dz danej �cianki. ------------------------
      //
   ViEdge const *GetPolyhEdge(unsigned int Idx) const;

     /*!
      *  Udost�pnia kraw�d� danej �cianki. Jej orientacja jest zgodna z
      *  orientacj� przyj�t� dla brzegu �cianki (zgodna z ruchem
      *  wskaz�wek zegara).
      *  \param Idx - indeks �cianki.
      *  \pre 0 <= \e Idx < \link ViFace::GetEdgesNo GetEdgesNo\endlink;
      *       Tablica \link ViFace::GetEdgesNo GetEdgesNo\endlink musi by�
      *       zainicjalizowana (patrze metoda  
      *       \link ViFace::InitEdgesSet() InitEdgesSet()\endlink.
      *  \return Zwraca referencj� do wskazanego wierzcho�ka.
      *  \post Je�li warunki wst�pne nie s� spe�nione, to dzia�anie
      *        metody nie jest okre�lone.
      */
  ViFaceEdge const &GetFaceEdge(unsigned int Idx) const 
                                               { return *_EdgesSet[Idx]; }
     /*!
      *  Udost�pnia ilo�� kraw�dzi danej �cianki.
      *  Zak�ada si�, �e ka�dy obw�d wzd�u� wierzcho�k�w jest zamkni�ty.
      */
   unsigned int GetEdgesNo() const { return _NodesNo; }

      //----------------------------------------------------------------------
      // Metoda realizuje dealokacje i alokacje pamieci dla kopiowanych
      // struktur.
   ViFace & operator = (ViFace const &);


  //---------------- Iteratory dla kraw�dzi ---------------------------------
    /*!
     * Tworzy iterator dla kraw�dzi danej bry�y. Iterator udost�pnia
     * obiekty klasy ViFaceEdge. S� one udost�pniane
     * jako obiekty sta�e. 
     */
   ConEdgeIter ConBegin_Edge() const
        { return ConEdgeIter(GetEdgesNo(),_EdgesSet); }

  //---------------- Iteratory dla tr�jk�tnych �cianek ----------------------
    /*!
     * Tworzy iterator dla kraw�dzi danej bry�y. Iterator udost�pnia
     * obiekty klasy ViFaceEdge. S� one udost�pniane
     * jako obiekty sta�e. 
     */
   ConTriaIter ConBegin_Tria() const
        { return ConTriaIter(this,GetVtxNo()); }



   /*!
    *  Nadaje now� warto�� dla prefiksu wydruku. Zmiany te nie s� istotne
    *  z punktu widzenia ca�ej struktury obiektu dlatego metoda ta 
    *  traktowana jest jako \b const.
    */
   void SetPrintPrefix(char const *Pref) const 
            { ((ViFace*)this)->_PrintPrefix = Pref; }
   /*!
    *  Wpisuje do pola ViFace::_PrintPrefix wska�nik 0L.
    */
   void ResetPrintPrefix() { _PrintPrefix = 0L; }
   /*!
    *  Udost�pnia prefiks dla wydruku.
    */
   const char* GetPrintPrefix() const {return _PrintPrefix ? _PrintPrefix :"";}

};


/*!
 *  Wy�wietla informacje dotycz�ce danej �cianki. Wy�wietlane s�
 *  poszczeg�lne kraw�dzie w porz�dku zgodnym z orientacj� brzegu.
 *  \post Wpisuje do pola ViFace::_PrintPrefix wska�nik 0L.
 *
 */
std::ostream &operator  << (std::ostream &ostrm, ViFace const &Face);


#endif
