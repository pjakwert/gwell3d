#ifndef VIELEMEPOLYHFACE_HH
#define VIELEMEPOLYHFACE_HH


/*!
 * \file vielemepolyhface.hh
 *  Plik zawiera definicjê  klasy ViElemePolyhFace. Wykorzystywana
 *  jest ona do modelowania ¶cianek bry³ elementarnych
 *  (klasa ViElemePolyh).
 *
 *  \author Bogdan Kreczmer
 *  \date   2004.02
 */


#ifdef __GNUG__
#pragma interface
#endif

#include "vector3.hh"
#include "vector3f.hh"
#include "plain3f.hh"
#include "vitriangle3f.hh"
#include "chaintableiterator.hh"
#include "vielemepolyhfaceedge.hh"

class ViElemePolyh;
class ViFace;


/*!
 * Obiekt klasy ViElemePolyhFace zawiera informacje o ¶ciance danej
 * bry³y elementarnej reprezentowanej przez obiekty klasy 
 * \link ViElemePolyh ViElemePolyh\endlink.
 */
class ViElemePolyhFace {

    /*!
     *  Jest referencj± do obiektu (\link ViElemePolyh ViElemePolyh\endlink)
     *  zawieraj±cego opis modelu bry³y,
     *  do której nale¿y ¶cianka reprezentowana przez ten obiekt
     *  (ViElemePolyhFace). Jest on po³±czony z obiektami modeluj±cymi
     *  poszczególne ¶cianki poprzez swoje pole 
     *  \link ViElemePolyh::_PolyhFaces ViElemePolyh::_PolyhFaces\endlink.
     */
    ViElemePolyh   &_Owner;

    /*! Pole zapewnia bezpo¶redni dostêp do opisu ¶cianki w obiekcie 
     *  bry³y wzorcowej reprezentowanej przez obiekt klasy 
     *  \link ViPattePolyh ViPattePolyh\endlink.
     */
    ViFace  const  &_PattFigFace;

    /*!
     *  Pole zawiera wspó³czynnik równiania p³aszczyzny, w której le¿y
     *  dana ¶cianka. W polu tym dostêpne s± równie¿ wspó³rzêdne wektora
     *  normalnego do ¶cianki. Wszystkie wielko¶ci podane s± w globalnym
     *  uk³adzie wspó³rzêdnych.
     */
    Plain3f               _FacePlain3f;

    /*!
     * Zawiera tablicê wska¼ników do obiektów zawieraj±cych informacje
     * o krawêdziach danej ¶cianki. Porz±dek elementów tablicy, jak te¿
     * porz±dek wierzcho³ków dla ka¿dek krawêdzi dostêpnych poprzez
     * te obiekty, jest zgodny z orientacj± brzegu ¶cianki.
     */
   ViElemePolyhFaceEdge  **_GlbEdgesSet;

    /*!
     *  Pole ma charakter roboczy. Wykorzystywane jest przy wydrukach
     *  realizowany za pomoc± przeci±¿enia operatora << dla ostream.
     *  Lañcuch znaków dostêpny poprzez to pole pojawia siê zawsze przed
     *  wy¶wietleniam danych dotycz±cych danej krawêdzi. Je¿eli adresem
     *  tego pola jest NULL, to przyjmuje siê, ¿e wy¶wietla siê 
     *  ³añcuch pusty.
     */  
   char const            *_PrintPrefix;    


  void InitGlbEdgesSet();
   /*!
    *  Zawalnia pamiêci dostêpne poprzez pole
    * \link ViElemePolyhFace::_GlbEdgesSet _GlbEdgesSet\endlink.
    */
  void DestroyGlbEdgesSet();

  public:

   /*!
    * Klasa definiuje iterator dla krawêdzi
    * bry³y, których opis jest w uk³adzie wspó³rzêdnych globalnych sceny.
    * Obiekty tej klasy s± tworzone i wykorzystywane na poziomie
    * klasy ViElemePolyh przez metodê 
    * \link ViElemePolyh::ConBegin_GlbEdge(unsigned int Idx = 0)const
    *     ViElemePolyh::ConBegin_GlbEdge(unsigned int Idx = 0) const
    * \endlink
    *
    * Przyk³ad u¿ycia iteratora ViElemePolyhFace::ConEdgeIter :
    * \code
    *  // Szuka najd³u¿szej krawêdzi.
    *  //
    * float SzukajNajdluzszej(const ViElemePolyhFace &EPolyh)
    * {
    *   int       d, d_max = 0;
    *   Vector3f  EVct;
    *
    *   for (ViElemePolyhFace::ConEdgeIter Iter = EPolyh.ConBegin_GlbEdge();
    *        Iter;  Iter++) {
    *     EVct = Iter->GetFstVtx()-Iter->GetFstVtx();
    *     if ( (d = EVct.Length()) > d_max ) d_max = d;
    *   }
    *   return d_max;
    * }
    * \endcode
    */
   //-------------------- ViElemePolyhFace::ConEdgeIter -----------------------
   /*!
    *  Iterator wykorzystywany jest do iteracji kolejnych krawêdzi
    *  ¶cianki danej bry³y. Udostêpniane krawêdzie reprezentowane
    *  s± przez obiekty klasy ViElemePolyhFaceEdge.
    */
   class ConEdgeIter: 
         public IndiTableIterator<const ViElemePolyhFaceEdge* const, 
                                  const ViElemePolyhFaceEdge> {
    public:
     /*!
      *  Inicjalizuje iterator krawêdzi.
      *  \param No - rozmiar iterowanej tablicy,
      *  \param Tab - wska¼nik na iterowan± tablicê krawêdzi,
      *  \param Idx - pocz±tkowa warto¶æ indeksu pocz±tkowego elementu
      *               dla iteracji.
      */
     ConEdgeIter(unsigned int No, ViElemePolyhFaceEdge * const *Tab, 
                  unsigned int Idx = 0 ):
        IndiTableIterator<const ViElemePolyhFaceEdge* const, 
                          const ViElemePolyhFaceEdge>(No,Tab,Idx) {}

     /*!
      *  Inicjalizuje iterator krawêdzi danej ¶cianki. Krawêdzie przegl±dane
      *  s± w porz±dku zgodnym z orientacj± danej ¶cianki.
      */
     ConEdgeIter(ViElemePolyhFace const *Face, unsigned int Idx = 0 );


     /*!
      *  Konwerter udostêpnia wska¼nik na bie¿±cy element tablicy.
      */
     operator const ViElemePolyhFaceEdge* () const 
                                        { return _BasePtr[_Idx]; }
     /*!
      *  Udostêpnia referencjê do bie¿±cego elementu tablicy.
      */
     const ViElemePolyhFaceEdge &operator *  () const 
                                       {return *_BasePtr[_Idx];}
     /*!
      *  Konwerter udostêpnia wska¼nik na bie¿±cy element tablicy.
      */
     const ViElemePolyhFaceEdge *operator -> () const 
                                       { return _BasePtr[_Idx];}

   }; //-------------- ViElemePolyhFace::ConEdgeIter -----------------------

   //----------------- ViElemePolyhFace::ConTriaIter -----------------------
    /*!
     * Klasa ConTriaIter przeznaczona jest do iterowania ¶cianki
     * w postaci pojednyczych trójk±tów.
     */
   class ConTriaIter: 
       public ChainTableIterator<const ViElemePolyhFace, const ViTriangle3f>
    {
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
      * ChainTableIterator::_Field dziedziczone z szablonu
      * ChainTableIterator.
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
      ConTriaIter( const ViElemePolyhFace  *Face, 
                   unsigned int             No, 
                   unsigned int             Idx = 2 
                 );
   };   //--------------- ViElemePolyhFace::ConTriaIterator ------------------

     /*!
      * Inicjalizuje pole \link ViElemePolyhFace::_Owner _Owner\endlink
      * oraz pole \link ViElemePolyhFace::_PattFigFace _PattFigFace\endlink.
      * Wywo³uje tak¿e metodê \link ViElemePolyh::IncFacesCount
      *  ViElemePolyh::IncFacesCount\endlink.
      */
    ViElemePolyhFace(ViElemePolyh &Polyh);
     /*!
      * Zwalnia pamiêæ zajêt± dla krawêdzi tworz±cych obwód ¶cianki.
      */
    ~ViElemePolyhFace() { DestroyGlbEdgesSet(); }

    /*!
     * Udostêpnia referencjê do bry³y, której ¶cianke modeluje 
     * ten obiekt (\b *this).
     */
    ViElemePolyh const &Owner_ElemePolyh() const { return _Owner; }

    /*!
     * Udostêpnia swój indeks, jaki ma w tablicy
     * ViElemePolyh:: _PolyhFaces.
     */
    unsigned int GetMyIdx() const;

     /*!
      *  Udostêpnia ilo¶æ krawêdzi danej ¶cianki.
      *  Zak³ada siê, ¿e ka¿dy obwód wzd³u¿ wierzcho³ków jest zamkniêty.
      */
    unsigned int GetEdgesNo() const;
 
     /*!
      *  Udostepnia wska¼nik do tablicy krawêdzi danej ¶cianki.
      *  Jest to metoda niskiego poziomu wykorzystywana do inicjacji
      *  iteratorów. Nie powinna byæ ona wykorzystywana bezpo¶rednio
      *  w aplikacji.
      */
    const ViElemePolyhFaceEdge * const *GetGlbEdgesTab() const 
                                                    { return _GlbEdgesSet; }


     /*!
      *  Udostêpnia krawêd¼ danej ¶cianki. Jej orientacja jest zgodna z
      *  orientacj± przyjêt± dla brzegu ¶cianki (zgodna z ruchem
      *  wskazówek zegara).
      *  \param Idx - indeks ¶cianki.
      *  \pre 0 <= \e Idx < \link ViElemePolyhFace::GetEdgesNo
      *                                               GetEdgesNo\endlink;
      *       Tablica \link ViElemePolyhFace::GetEdgesNo
      *                                       GetEdgesNo\endlink musi byæ
      *       zainicjalizowana (patrze metoda  
      *       \link ViElemePolyhFace::InitGlbEdgesSet
      *                                             InitGlbEdgesSet\endlink.
      *  \return Zwraca referencjê do wskazanego wierzcho³ka.
      *          Referencja udostêpniana jest w trybie sta³ym.
      *  \post Je¶li warunki wstêpne nie s± spe³nione, to dzia³anie
      *        metody nie jest okre¶lone.
      */
    ViElemePolyhFaceEdge const &GetGlbEdge(unsigned int Idx) const
                                           { return *_GlbEdgesSet[Idx]; }



     /*!
      *  Udostêpnia krawêd¼ danej ¶cianki. Jej orientacja jest zgodna z
      *  orientacj± przyjêt± dla brzegu ¶cianki (zgodna z ruchem
      *  wskazówek zegara).
      *  \param Idx - indeks ¶cianki.
      *  \pre 0 <= \e Idx < \link ViElemePolyhFace::GetEdgesNo
      *                                               GetEdgesNo\endlink;
      *       Tablica \link ViElemePolyhFace::GetEdgesNo
      *                                       GetEdgesNo\endlink musi byæ
      *       zainicjalizowana (patrze metoda  
      *       \link ViElemePolyhFace::InitGlbEdgesSet
      *                                             InitGlbEdgesSet\endlink.
      *  \return Zwraca referencjê do wskazanego wierzcho³ka.
      *          Referencja udostêpniana jest w trybie modyfikacji.
      *  \post Je¶li warunki wstêpne nie s± spe³nione, to dzia³anie
      *        metody nie jest okre¶lone.
      */
    ViElemePolyhFaceEdge &UseGlbEdge(unsigned int Idx) 
                                              { return *_GlbEdgesSet[Idx]; }




     /*!
      * Udostêpnia ilo¶æ wierzcho³ków danej ¶cianki.
      */
    unsigned int GetVtxNo() const;


     /*!
      * Udostêpnia wspó³rzêdne wierzcho³ka danej ¶cianki w uk³adzie globalnym.
      * Porz±dek wierzcho³ków na obowdzie ¶cianki jest zgodny z ruchem
      * wskazówek zegara.
      * \param  Idx - numer wierzcho³ka ¶cianki. Kolejne wierzcho³ki
      *         numerowane s± od 0. Numer wierzcho³ka musi byæ prawid³owy,
      *          tzn. 
      *       \f$ 0 \le  VtxNo < N_{max} \f$,
      *        gdzie \f$ N_{max}\f$, to warto¶æ dostêpna poprzez metodê
      *       \link ViElemePolyhFace::GetVtxNo GetVtxNo\endlink.
      *
      * \pre  Pole \link ViFace::_NodeSet _NodeSet\endlink - musi byæ
      *       prawd³owo  zainicjalizowane.
      *
      * \return
      *   referencja do obiektu zawieraj±cego wspó³rzêdne wierzcho³ka
      *   w uk³adzie wspó³rzêdnych globalnych.
      *   Je¿eli numer wierzcho³ka bêdzie poza dopuszczalnym przedzia³em,
      *   to dzia³anie programu bêdzie nieokre¶lone.
      */
    Vector3f const &GlbVtx(unsigned int Idx) const;

     /*!
      * Na podstawie wspó³rzêdnych globalnych wierzcho³ków wyznacza równanie
      * p³aszczyzny dla ¶cianki (równie¿ wektor normalny).
      * Do wyzanaczenia równiania brane s± trzy pierwsze wierzcho³ki danej
      * ¶cianki.
      * \retval true - je¶li obliczenia zakoñczy³y siê poprawnie,
      * \retval false - je¶li równianie p³aszczyzny nie mog³o byæ wyznaczone
      *             (np. wierzcho³ki by³y wspó³liniowe). 
      */
    bool ComputePlain3f();

     /*!
      * Udostêpnia referencjê sta³± do pola zwieraj±ce wspó³czynniki równania
      * p³aszczyzny danej ¶cianki.
      */
    Plain3f const &GetPlain() const { return _FacePlain3f; }

     /*!
      * Udostêpnia wektor normalny do p³aszczyzny ¶cianki.
      */
    Vector3f const &GetNormVect() const { return GetPlain().GetNVct(); }

    //===================== Iteratory =====================================

     /*!
      *  Tworzy iterator od przegl±dania pokrycia trójk±tnego danej ¶cianki,
      *  tzn. udostêpnia kolejne trók±ty na które rozbita zostaje dana
      *  ¶cianki.
      */
    ConTriaIter ConBegin_GlbTria(unsigned int Idx = 2) const 
         { return  ConTriaIter(this,GetVtxNo(),Idx); }

     /*!
      *  Tworzy iterator od przegl±dania krawêdzi danej ¶cianki.
      *  Porz±dek przegl±danych krawêdzi jest zgodny z orientacj± brzegu.
      */
    ConEdgeIter ConBegin_GlbEdge(unsigned int Idx = 0) const 
         { return  ConEdgeIter(this,Idx); }


   /*!
    *  Nadaje now± warto¶æ dla prefiksu wydruku. Zmiany te nie s± istotne
    *  z punktu widzenia ca³ej struktury obiektu dlatego metoda ta 
    *  traktowana jest jako \b const.
    */
   void SetPrintPrefix(char const *Pref) const 
            { ((ViElemePolyhFace*)this)->_PrintPrefix = Pref; }
   /*!
    *  Wpisuje do pola ViElemePolyhFace::_PrintPrefix wska¼nik 0L.
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
 *  \post Wpisuje do pola ViElemePolyhFace::_PrintPrefix wska¼nik 0L.
 *
 */
std::ostream &operator  << (std::ostream &ostrm, ViElemePolyhFace const &Face);

#endif

