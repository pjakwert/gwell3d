#ifndef VIELEMEPOLYHFACE_HH
#define VIELEMEPOLYHFACE_HH


/*!
 * \file vielemepolyhface.hh
 *  Plik zawiera definicj�  klasy ViElemePolyhFace. Wykorzystywana
 *  jest ona do modelowania �cianek bry� elementarnych
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
 * Obiekt klasy ViElemePolyhFace zawiera informacje o �ciance danej
 * bry�y elementarnej reprezentowanej przez obiekty klasy 
 * \link ViElemePolyh ViElemePolyh\endlink.
 */
class ViElemePolyhFace {

    /*!
     *  Jest referencj� do obiektu (\link ViElemePolyh ViElemePolyh\endlink)
     *  zawieraj�cego opis modelu bry�y,
     *  do kt�rej nale�y �cianka reprezentowana przez ten obiekt
     *  (ViElemePolyhFace). Jest on po��czony z obiektami modeluj�cymi
     *  poszczeg�lne �cianki poprzez swoje pole 
     *  \link ViElemePolyh::_PolyhFaces ViElemePolyh::_PolyhFaces\endlink.
     */
    ViElemePolyh   &_Owner;

    /*! Pole zapewnia bezpo�redni dost�p do opisu �cianki w obiekcie 
     *  bry�y wzorcowej reprezentowanej przez obiekt klasy 
     *  \link ViPattePolyh ViPattePolyh\endlink.
     */
    ViFace  const  &_PattFigFace;

    /*!
     *  Pole zawiera wsp�czynnik r�wniania p�aszczyzny, w kt�rej le�y
     *  dana �cianka. W polu tym dost�pne s� r�wnie� wsp�rz�dne wektora
     *  normalnego do �cianki. Wszystkie wielko�ci podane s� w globalnym
     *  uk�adzie wsp�rz�dnych.
     */
    Plain3f               _FacePlain3f;

    /*!
     * Zawiera tablic� wska�nik�w do obiekt�w zawieraj�cych informacje
     * o kraw�dziach danej �cianki. Porz�dek element�w tablicy, jak te�
     * porz�dek wierzcho�k�w dla ka�dek kraw�dzi dost�pnych poprzez
     * te obiekty, jest zgodny z orientacj� brzegu �cianki.
     */
   ViElemePolyhFaceEdge  **_GlbEdgesSet;

    /*!
     *  Pole ma charakter roboczy. Wykorzystywane jest przy wydrukach
     *  realizowany za pomoc� przeci��enia operatora << dla ostream.
     *  La�cuch znak�w dost�pny poprzez to pole pojawia si� zawsze przed
     *  wy�wietleniam danych dotycz�cych danej kraw�dzi. Je�eli adresem
     *  tego pola jest NULL, to przyjmuje si�, �e wy�wietla si� 
     *  �a�cuch pusty.
     */  
   char const            *_PrintPrefix;    


  void InitGlbEdgesSet();
   /*!
    *  Zawalnia pami�ci dost�pne poprzez pole
    * \link ViElemePolyhFace::_GlbEdgesSet _GlbEdgesSet\endlink.
    */
  void DestroyGlbEdgesSet();

  public:

   /*!
    * Klasa definiuje iterator dla kraw�dzi
    * bry�y, kt�rych opis jest w uk�adzie wsp�rz�dnych globalnych sceny.
    * Obiekty tej klasy s� tworzone i wykorzystywane na poziomie
    * klasy ViElemePolyh przez metod� 
    * \link ViElemePolyh::ConBegin_GlbEdge(unsigned int Idx = 0)const
    *     ViElemePolyh::ConBegin_GlbEdge(unsigned int Idx = 0) const
    * \endlink
    *
    * Przyk�ad u�ycia iteratora ViElemePolyhFace::ConEdgeIter :
    * \code
    *  // Szuka najd�u�szej kraw�dzi.
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
    *  Iterator wykorzystywany jest do iteracji kolejnych kraw�dzi
    *  �cianki danej bry�y. Udost�pniane kraw�dzie reprezentowane
    *  s� przez obiekty klasy ViElemePolyhFaceEdge.
    */
   class ConEdgeIter: 
         public IndiTableIterator<const ViElemePolyhFaceEdge* const, 
                                  const ViElemePolyhFaceEdge> {
    public:
     /*!
      *  Inicjalizuje iterator kraw�dzi.
      *  \param No - rozmiar iterowanej tablicy,
      *  \param Tab - wska�nik na iterowan� tablic� kraw�dzi,
      *  \param Idx - pocz�tkowa warto�� indeksu pocz�tkowego elementu
      *               dla iteracji.
      */
     ConEdgeIter(unsigned int No, ViElemePolyhFaceEdge * const *Tab, 
                  unsigned int Idx = 0 ):
        IndiTableIterator<const ViElemePolyhFaceEdge* const, 
                          const ViElemePolyhFaceEdge>(No,Tab,Idx) {}

     /*!
      *  Inicjalizuje iterator kraw�dzi danej �cianki. Kraw�dzie przegl�dane
      *  s� w porz�dku zgodnym z orientacj� danej �cianki.
      */
     ConEdgeIter(ViElemePolyhFace const *Face, unsigned int Idx = 0 );


     /*!
      *  Konwerter udost�pnia wska�nik na bie��cy element tablicy.
      */
     operator const ViElemePolyhFaceEdge* () const 
                                        { return _BasePtr[_Idx]; }
     /*!
      *  Udost�pnia referencj� do bie��cego elementu tablicy.
      */
     const ViElemePolyhFaceEdge &operator *  () const 
                                       {return *_BasePtr[_Idx];}
     /*!
      *  Konwerter udost�pnia wska�nik na bie��cy element tablicy.
      */
     const ViElemePolyhFaceEdge *operator -> () const 
                                       { return _BasePtr[_Idx];}

   }; //-------------- ViElemePolyhFace::ConEdgeIter -----------------------

   //----------------- ViElemePolyhFace::ConTriaIter -----------------------
    /*!
     * Klasa ConTriaIter przeznaczona jest do iterowania �cianki
     * w postaci pojednyczych tr�jk�t�w.
     */
   class ConTriaIter: 
       public ChainTableIterator<const ViElemePolyhFace, const ViTriangle3f>
    {
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
      * ChainTableIterator::_Field dziedziczone z szablonu
      * ChainTableIterator.
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
      ConTriaIter( const ViElemePolyhFace  *Face, 
                   unsigned int             No, 
                   unsigned int             Idx = 2 
                 );
   };   //--------------- ViElemePolyhFace::ConTriaIterator ------------------

     /*!
      * Inicjalizuje pole \link ViElemePolyhFace::_Owner _Owner\endlink
      * oraz pole \link ViElemePolyhFace::_PattFigFace _PattFigFace\endlink.
      * Wywo�uje tak�e metod� \link ViElemePolyh::IncFacesCount
      *  ViElemePolyh::IncFacesCount\endlink.
      */
    ViElemePolyhFace(ViElemePolyh &Polyh);
     /*!
      * Zwalnia pami�� zaj�t� dla kraw�dzi tworz�cych obw�d �cianki.
      */
    ~ViElemePolyhFace() { DestroyGlbEdgesSet(); }

    /*!
     * Udost�pnia referencj� do bry�y, kt�rej �cianke modeluje 
     * ten obiekt (\b *this).
     */
    ViElemePolyh const &Owner_ElemePolyh() const { return _Owner; }

    /*!
     * Udost�pnia sw�j indeks, jaki ma w tablicy
     * ViElemePolyh:: _PolyhFaces.
     */
    unsigned int GetMyIdx() const;

     /*!
      *  Udost�pnia ilo�� kraw�dzi danej �cianki.
      *  Zak�ada si�, �e ka�dy obw�d wzd�u� wierzcho�k�w jest zamkni�ty.
      */
    unsigned int GetEdgesNo() const;
 
     /*!
      *  Udostepnia wska�nik do tablicy kraw�dzi danej �cianki.
      *  Jest to metoda niskiego poziomu wykorzystywana do inicjacji
      *  iterator�w. Nie powinna by� ona wykorzystywana bezpo�rednio
      *  w aplikacji.
      */
    const ViElemePolyhFaceEdge * const *GetGlbEdgesTab() const 
                                                    { return _GlbEdgesSet; }


     /*!
      *  Udost�pnia kraw�d� danej �cianki. Jej orientacja jest zgodna z
      *  orientacj� przyj�t� dla brzegu �cianki (zgodna z ruchem
      *  wskaz�wek zegara).
      *  \param Idx - indeks �cianki.
      *  \pre 0 <= \e Idx < \link ViElemePolyhFace::GetEdgesNo
      *                                               GetEdgesNo\endlink;
      *       Tablica \link ViElemePolyhFace::GetEdgesNo
      *                                       GetEdgesNo\endlink musi by�
      *       zainicjalizowana (patrze metoda  
      *       \link ViElemePolyhFace::InitGlbEdgesSet
      *                                             InitGlbEdgesSet\endlink.
      *  \return Zwraca referencj� do wskazanego wierzcho�ka.
      *          Referencja udost�pniana jest w trybie sta�ym.
      *  \post Je�li warunki wst�pne nie s� spe�nione, to dzia�anie
      *        metody nie jest okre�lone.
      */
    ViElemePolyhFaceEdge const &GetGlbEdge(unsigned int Idx) const
                                           { return *_GlbEdgesSet[Idx]; }



     /*!
      *  Udost�pnia kraw�d� danej �cianki. Jej orientacja jest zgodna z
      *  orientacj� przyj�t� dla brzegu �cianki (zgodna z ruchem
      *  wskaz�wek zegara).
      *  \param Idx - indeks �cianki.
      *  \pre 0 <= \e Idx < \link ViElemePolyhFace::GetEdgesNo
      *                                               GetEdgesNo\endlink;
      *       Tablica \link ViElemePolyhFace::GetEdgesNo
      *                                       GetEdgesNo\endlink musi by�
      *       zainicjalizowana (patrze metoda  
      *       \link ViElemePolyhFace::InitGlbEdgesSet
      *                                             InitGlbEdgesSet\endlink.
      *  \return Zwraca referencj� do wskazanego wierzcho�ka.
      *          Referencja udost�pniana jest w trybie modyfikacji.
      *  \post Je�li warunki wst�pne nie s� spe�nione, to dzia�anie
      *        metody nie jest okre�lone.
      */
    ViElemePolyhFaceEdge &UseGlbEdge(unsigned int Idx) 
                                              { return *_GlbEdgesSet[Idx]; }




     /*!
      * Udost�pnia ilo�� wierzcho�k�w danej �cianki.
      */
    unsigned int GetVtxNo() const;


     /*!
      * Udost�pnia wsp�rz�dne wierzcho�ka danej �cianki w uk�adzie globalnym.
      * Porz�dek wierzcho�k�w na obowdzie �cianki jest zgodny z ruchem
      * wskaz�wek zegara.
      * \param  Idx - numer wierzcho�ka �cianki. Kolejne wierzcho�ki
      *         numerowane s� od 0. Numer wierzcho�ka musi by� prawid�owy,
      *          tzn. 
      *       \f$ 0 \le  VtxNo < N_{max} \f$,
      *        gdzie \f$ N_{max}\f$, to warto�� dost�pna poprzez metod�
      *       \link ViElemePolyhFace::GetVtxNo GetVtxNo\endlink.
      *
      * \pre  Pole \link ViFace::_NodeSet _NodeSet\endlink - musi by�
      *       prawd�owo  zainicjalizowane.
      *
      * \return
      *   referencja do obiektu zawieraj�cego wsp�rz�dne wierzcho�ka
      *   w uk�adzie wsp�rz�dnych globalnych.
      *   Je�eli numer wierzcho�ka b�dzie poza dopuszczalnym przedzia�em,
      *   to dzia�anie programu b�dzie nieokre�lone.
      */
    Vector3f const &GlbVtx(unsigned int Idx) const;

     /*!
      * Na podstawie wsp�rz�dnych globalnych wierzcho�k�w wyznacza r�wnanie
      * p�aszczyzny dla �cianki (r�wnie� wektor normalny).
      * Do wyzanaczenia r�wniania brane s� trzy pierwsze wierzcho�ki danej
      * �cianki.
      * \retval true - je�li obliczenia zako�czy�y si� poprawnie,
      * \retval false - je�li r�wnianie p�aszczyzny nie mog�o by� wyznaczone
      *             (np. wierzcho�ki by�y wsp�liniowe). 
      */
    bool ComputePlain3f();

     /*!
      * Udost�pnia referencj� sta�� do pola zwieraj�ce wsp�czynniki r�wnania
      * p�aszczyzny danej �cianki.
      */
    Plain3f const &GetPlain() const { return _FacePlain3f; }

     /*!
      * Udost�pnia wektor normalny do p�aszczyzny �cianki.
      */
    Vector3f const &GetNormVect() const { return GetPlain().GetNVct(); }

    //===================== Iteratory =====================================

     /*!
      *  Tworzy iterator od przegl�dania pokrycia tr�jk�tnego danej �cianki,
      *  tzn. udost�pnia kolejne tr�k�ty na kt�re rozbita zostaje dana
      *  �cianki.
      */
    ConTriaIter ConBegin_GlbTria(unsigned int Idx = 2) const 
         { return  ConTriaIter(this,GetVtxNo(),Idx); }

     /*!
      *  Tworzy iterator od przegl�dania kraw�dzi danej �cianki.
      *  Porz�dek przegl�danych kraw�dzi jest zgodny z orientacj� brzegu.
      */
    ConEdgeIter ConBegin_GlbEdge(unsigned int Idx = 0) const 
         { return  ConEdgeIter(this,Idx); }


   /*!
    *  Nadaje now� warto�� dla prefiksu wydruku. Zmiany te nie s� istotne
    *  z punktu widzenia ca�ej struktury obiektu dlatego metoda ta 
    *  traktowana jest jako \b const.
    */
   void SetPrintPrefix(char const *Pref) const 
            { ((ViElemePolyhFace*)this)->_PrintPrefix = Pref; }
   /*!
    *  Wpisuje do pola ViElemePolyhFace::_PrintPrefix wska�nik 0L.
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
 *  \post Wpisuje do pola ViElemePolyhFace::_PrintPrefix wska�nik 0L.
 *
 */
std::ostream &operator  << (std::ostream &ostrm, ViElemePolyhFace const &Face);

#endif

