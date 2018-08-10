#ifndef VIFACE_HH
#define VIFACE_HH

/*!
 * \file  viface.hh
 * \author	Bogdan Kreczmer
 * \date	2003.09
 *
 * Plik zawiera definicjê klasy \link ViFace ViFace\endlink modeluj±cej
 * pojedyncz± ¶ciankê bry³y wzorcowej.
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
 * Klasa ViType opisuje pojedyncza ¶ciankê bry³y wzorcowej.
 * Klasa ta zawiera tablicê numerów wierzcho³ków, które le¿± na obwodzie
 * danej ¶cianki. Dostêpne (w sposób po¶redni) s± wspó³rzêdne wierzcho³ków
 * (znajduj± siê one w tablicy obiektu klasy 
 * \link ViPattePolyh ViPattePolyh\endlink).
 * Numery wierzcho³ków wymieniane s± po kolei zgodnie z ich u³o¿eniem na
 * obwodzie ¶cianki w kierunku przeciwnym do ruchu wskazówek zegara.
 *
 * Tablica numerow wierzcho³ków danej ¶cianki dostêpna jest poprzez pole
 * \link ViFace::_NodeSet _NodeSet\endlink. 
 * Tablica ta zorganizowana jest w nastêpuj±cy sposób:
 *    W pierwszym elemencie przechowywana jest ilo¶æ wszystkich wierzcho³ków,
 *    Od nastêpnego elementu rozpoczyna siê w³a¶ciwa tablica numerów 
 *    wierzcho³kow. 
 *    W³±¶ciwy dostêp do tej tablicy zapewnia metoda 
 * \link ViFace::GetFaceVtxTable GetFaceVtxTable\endlink 
 *    za¶ do pierwszego elementu metoda 
 * \link ViFace::GetVtxNo GetVtxNo\endlink.
 */
class ViFace  {
    /*!
     * Referencja do obiektu modeluj±cego bry³ê, do której to bry³y nale¿y
     * ¶cianka reprezentowana przez ten obiekt.
     */
   ViPattePolyh &_Owner;
    /*!
     * W tej chwili to pole nie jest wykorzystywane. Przewidziane jest do
     * zapisu informacji o ilo¶ci wierzcho³ków danej ¶cianki.
     */
   unsigned int  _NodesNo;
    /*!
     * Tablica numerów wierzcho³ków ¶cianki. Numery odnosz± siê do tablicy
     * wszystkich wierzcho³ków znajduj±cej siê dostêpnych poprzez pole
     * ViPattePolyh::_Vertex obiektu modeluj±ceg dan± bry³ê.
     * Sam obiekt klasy \b ViFace znajduje siê w tablicy dostêpnej poprzez
     * pole ViPattePolyh::_Faces.
     */
   unsigned int *_NodeSet;
    /*!
     * Zawiera tablicê wska¼ników do obiektów zawieraj±cych informacje
     * o krawêdziach danej ¶cianki. Porz±dek elementów tablicy, jak te¿
     * porz±dek wierzcho³ków dla ka¿dek krawêdzi dostêpnych poprzez
     * te obiekty, jest zgodny z orientacj± brzegu ¶cianki.
     */
   ViFaceEdge **_EdgesSet;
    /*!
     *  Wektor normalny do powierzchni ¶cianki. Wektor wskazuje kierunek
     *  na zewn±trz ¶cianki.
     */
   Vector3f _NormVct;


    /*!
     *  Pole ma charakter roboczy. Wykorzystywane jest przy wydrukach
     *  realizowany za pomoc± przeci±¿enia operatora << dla ostream.
     *  Lañcuch znaków dostêpny poprzez to pole pojawia siê zawsze przed
     *  wy¶wietleniam danych dotycz±cych danej krawêdzi. Je¿eli adresem
     *  tego pola jest NULL, to przyjmuje siê, ¿e wy¶wietla siê
     *  ³añcuch pusty.
     */  
   char const *_PrintPrefix;    

 public:
   //-------------------- ViFace::ConEdgeIter -----------------------------
   /*!
    *  Iterator wykorzystywany jest do iteracji kolejnych krawêdzi
    *  ¶cianki danej bry³y. Udostêpniane krawêdzie reprezentowane
    *  s± przez obiekty klasy ViFaceEdge.
    */
   class ConEdgeIter: 
         public IndiTableIterator<const ViFaceEdge* const, const ViFaceEdge> {
     public:
     /*!
      *  Inicjalizuje iterator krawêdzi.
      *  \param No - rozmiar iterowanej tablicy,
      *  \param Tab - wska¼nik na iterowan± tablicê krawêdzi,
      *  \param Idx - pocz±tkowa warto¶æ indeksu pocz±tkowego elementu
      *               dla iteracji.
      */
      ConEdgeIter(unsigned int No, ViFaceEdge * const *Tab, int Idx = 0 ):
        IndiTableIterator<const ViFaceEdge* const, 
                          const ViFaceEdge>(No,Tab,Idx) {}
     /*!
      *  Konwerter udostêpnia wska¼nik na bie¿±cy element tablicy.
      */
     operator const ViFaceEdge* () const { return _BasePtr[_Idx]; }
     /*!
      *  Udostêpnia referencjê do bie¿±cego elementu tablicy.
      */
     const ViFaceEdge &operator *  () const { return *_BasePtr[_Idx]; }
     /*!
      *  Konwerter udostêpnia wska¼nik na bie¿±cy element tablicy.
      */
     const ViFaceEdge *operator -> () const { return _BasePtr[_Idx]; } 

   };
   //-------------------- ViFace::ConEdgeIterator -----------------------------

   //-------------------- ViFace::ConTriaIterator -----------------------------
  /*!
   *  Klasa ta pe³ni rolê iteratora dla danej ¶cianki. Umo¿liwia ona
   *  iteracjê ¶cianki w postaci pokrywaj±cych j± trójk±tów.
   */  
  class ConTriaIter: 
     public ChainTableIterator<const ViFace, const ViTriangle3f> {

     /*!
      * Metoda jest wywo³ywana po ka¿dorazowej iteracji i aktualizuje
      * pole \link ChainTableIterator::_Field _Field\endlink dziedziczone
      * z szablonu ChainTableIterator. W pole to wpisywane s± wierzcho³ki
      * nastêpnego trójk±ta danej ¶cianki.
      */ 
    void UpdateField();

     /*!
      * Metoda jest wywo³ywana po zainicjalizwaniu iteratora oraz
      * przy wykonywaniu operacja 
      * \link ChainTableIterator::Reset\endlink.
      * Metoda inicjalizuje pole 
      * ChainTableIterator::_Field dziedziczone z szablonu ChainTableIterator.
      * Do zainicjalizowanego pola wpisane zostaj± wierzcho³ki pierwszego
      * trójk±ta danej ¶cianki.
      */ 
    void InitField();

   public:
     /*!
      *  Inicjalizuje iterator kojarz±c go z dan± tablic±.
      *  \param  Face - referencja do ¶cianki, dla której ma byæ wywo³any ten
      *                 iterator.
      *  \param  No - ilo¶æ elementów tablicy,
      *  \param  Idx - warto¶æ pocz±tkowa indeksu.
      *  \pre  2 <= \e Idx < \e No;
      *  \post Je¿eli warto¶æ \e Idx nie spe³nia warunku pocz±tkowego,
      *      to zg³aszany jest wyj±tek 
      *      \link ViException_OutOfRange ViException_OutOfRange\endlink
      *     przez konstruktor szablon IndiTableIterator.
      *      Jako numer b³êdu ma warto¶æ 
      *  \link vierrors.hh::ERRNUM_TABITER_BADINIT
      *                                     ERRNUM_TABITER_BADINIT\endlink,
      *   za¶ jako numer pomocniczy: 2.
      *      W przypadku przeciwnym pole
      *      \link IndiTableIterator::_OpStatus _OpStatus\endlink
      *     dziedziczone z IndiTableIterator
      *        inicjalizowane jest warto¶ci± \p true.
      *  Je¿eli \e Idx < 2, to zg³aszany jest wyj±tek ViException_OutOfRange
      *  z numerem b³êdu
      *  \link vierrors.hh::ERRNUM_FACE_IDXBELOW2
      *                                     ERRNUM_FACE_IDXBELOW2\endlink,
      *   za¶ jako numer pomocniczy: 0.
      *
      *  Je¿eli wszystko jest poprawnie to wywo³ywana jest metoda 
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
       * Inicjalizuje obiekt przydzielaj±c mu w³±¶ciela, którym jest obiekt
       * klasy ViPattePolyh. Musi on modelowaæ bry³ê, której ¶ciankê ma
       * reprezentowaæ ten tworzony obiekt.
       *
       * \param Owner - obiekt modeluj±cy bry³ê posiadaj±c± dan± ¶ciankê.
       */
   ViFace( ViPattePolyh &Owner ): _Owner(Owner), _NodesNo(0), _NodeSet(0L),
       _EdgesSet(0)  { _PrintPrefix = 0L; }
   ~ViFace();

    /*!
     * Udostêpnia nazwê bry³y wzorcowej, w której sk³ad wchodzi
     * ¶cianka reprezentowana przez ten obiekt.
     */
   const char *GetName() const;

    /*!
     * Udostêpnia swój indeks, jaki ma w tablicy
     * ViPattePolyh::_Faces.
     */
   unsigned int GetMyIdx() const;

    /*!
     * Alokuje pamiêæ dla tablicy numerów wierzcho³ków.
     */
   int CreateNodeTable( unsigned int NodeNo );

      //----------------------------------------------------------------------
      // Inicjuje tablicê numerów wierzcho³ków. -----------------------------
   int InitNodeIndexTable( unsigned int *Tab );

      //----------------------------------------------------------------------
      // Alokuje pamiêæ dla tablicy numerów wierzcho³ków i j± inicjuje. ------
      //
   int CreateAndInitNodeIndexTable( unsigned int *Tab );

    /*!
     * Inicjalizuje tablicê krawêdzi.
     */
   void InitEdgesSet();
    /*!
     * Zwalnia pamiêæ zajêt± przez tablicê krawêdzi.
     */
   void DestroyEdgesSet();
   
    /*!
     *  Inicjalizuje wektor normalny dla danej ¶cianki.
     *  Wektor wyliczany jest na podstawie dwóch pierwszych boków,
     *  które nie s± wspólniowe.
     *  \pre Zak³ada siê, ¿e ¶cianka jest wypuk³a.
     *  \post Je¶li obliczenia nie mog± zakoñczyæ siê powodzeniem
     *     (wierzcho³ki le¿± na jednej prostej), to zg³aszany jest
     *     wyj±tek ViException_WrongComputation.
     */
   void InitNormVect();

   /*!
    * Udostêpnia wektor normalny ¶cianki.
    */
  const Vector3f &GetNormVect() const { return _NormVct; }

      /*!
       * Udostêpnia indeks wierzcho³ka. Jest on indeksem pozycji w tablicy
       * ViPattePolyh::_Vertex. Przechowywane s± tam wspó³rzêdne tego
       * wierzcho³ka.
       * \param VtxNo - numer wierzcho³ka dla danej ¶cianki.
       * \return zwraca indeks wierzcho³ka.
       *
       * Przyk³ad u¿ycia (na poziomie tej klasy):
       * \code
       *   _Owner.GetPattePolyhVtx(GetVtxIdx(VtxNo));
       * \endcode
       * Powy¿sza operacja równowa¿na jest wywo³aniu metody:
       * \code
       *  GetFaceVtx(VtxNo);
       * \endcode
       */
   unsigned int GetVtxIdx(int VtxNo) const { return _NodeSet[VtxNo+1]; }

      /*!
       * Udostêpnia tablicê numerów wierzcho³ków. 
       */
   unsigned int *GetFaceVtxTable() const
         { return _NodeSet+1; }

      /*!
       * Udostêpnia ilo¶æ wierzcho³ków danej ¶cianki.
       */
   unsigned int  GetVtxNo()  const { return *_NodeSet; }

      //----------------------------------------------------------------------
      // Udostêpnia wsó³rzêdne danego wierzcho³ka o numerze VtxNo. -----------
      //
   Vector3f const &GetFaceVtx(unsigned int VtxNo) const;

      //----------------------------------------------------------------------
      // Bezpieczne Udostêpnienie wsó³rzêdnych wierzcho³ka o numerze VtxNo. --
      //
   Vector3f const &SGetFaceVtx(unsigned int VtxNo) const 
                                               throw (ViException_OutOfRange);

      //----------------------------------------------------------------------
      // Udostêpnienia wskaznik do s±siaduj±cej ¶cianki o numerze No. --------
      //
   ViFace const *GetNeighbor(unsigned int No) const;

      //----------------------------------------------------------------------
      // Udostêpnienia indeks obiektu w tablicy. -----------------------------
      //
   unsigned int GetFaceIdx() const;

      //----------------------------------------------------------------------
      // Udostêpnienia wybran± krewêdz danej ¶cianki. ------------------------
      //
   ViEdge const *GetPolyhEdge(unsigned int Idx) const;

     /*!
      *  Udostêpnia krawêd¼ danej ¶cianki. Jej orientacja jest zgodna z
      *  orientacj± przyjêt± dla brzegu ¶cianki (zgodna z ruchem
      *  wskazówek zegara).
      *  \param Idx - indeks ¶cianki.
      *  \pre 0 <= \e Idx < \link ViFace::GetEdgesNo GetEdgesNo\endlink;
      *       Tablica \link ViFace::GetEdgesNo GetEdgesNo\endlink musi byæ
      *       zainicjalizowana (patrze metoda  
      *       \link ViFace::InitEdgesSet() InitEdgesSet()\endlink.
      *  \return Zwraca referencjê do wskazanego wierzcho³ka.
      *  \post Je¶li warunki wstêpne nie s± spe³nione, to dzia³anie
      *        metody nie jest okre¶lone.
      */
  ViFaceEdge const &GetFaceEdge(unsigned int Idx) const 
                                               { return *_EdgesSet[Idx]; }
     /*!
      *  Udostêpnia ilo¶æ krawêdzi danej ¶cianki.
      *  Zak³ada siê, ¿e ka¿dy obwód wzd³u¿ wierzcho³ków jest zamkniêty.
      */
   unsigned int GetEdgesNo() const { return _NodesNo; }

      //----------------------------------------------------------------------
      // Metoda realizuje dealokacje i alokacje pamieci dla kopiowanych
      // struktur.
   ViFace & operator = (ViFace const &);


  //---------------- Iteratory dla krawêdzi ---------------------------------
    /*!
     * Tworzy iterator dla krawêdzi danej bry³y. Iterator udostêpnia
     * obiekty klasy ViFaceEdge. S± one udostêpniane
     * jako obiekty sta³e. 
     */
   ConEdgeIter ConBegin_Edge() const
        { return ConEdgeIter(GetEdgesNo(),_EdgesSet); }

  //---------------- Iteratory dla trójk±tnych ¶cianek ----------------------
    /*!
     * Tworzy iterator dla krawêdzi danej bry³y. Iterator udostêpnia
     * obiekty klasy ViFaceEdge. S± one udostêpniane
     * jako obiekty sta³e. 
     */
   ConTriaIter ConBegin_Tria() const
        { return ConTriaIter(this,GetVtxNo()); }



   /*!
    *  Nadaje now± warto¶æ dla prefiksu wydruku. Zmiany te nie s± istotne
    *  z punktu widzenia ca³ej struktury obiektu dlatego metoda ta 
    *  traktowana jest jako \b const.
    */
   void SetPrintPrefix(char const *Pref) const 
            { ((ViFace*)this)->_PrintPrefix = Pref; }
   /*!
    *  Wpisuje do pola ViFace::_PrintPrefix wska¼nik 0L.
    */
   void ResetPrintPrefix() { _PrintPrefix = 0L; }
   /*!
    *  Udostêpnia prefiks dla wydruku.
    */
   const char* GetPrintPrefix() const {return _PrintPrefix ? _PrintPrefix :"";}

};


/*!
 *  Wy¶wietla informacje dotycz±ce danej ¶cianki. Wy¶wietlane s±
 *  poszczególne krawêdzie w porz±dku zgodnym z orientacj± brzegu.
 *  \post Wpisuje do pola ViFace::_PrintPrefix wska¼nik 0L.
 *
 */
std::ostream &operator  << (std::ostream &ostrm, ViFace const &Face);


#endif
