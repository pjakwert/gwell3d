#ifndef VIPATTEPOLYH_HH
#define VIPATTEPOLYH_HH

/*!  
 *  \file vipattepolyh.hh
 *  \author  Bogdan Kreczmer
 *  \date    2004.02
 *  Plik zawiera definicjê klasy \link ViPattePolyh ViPattePolyh\endlink
 *  modeluj±cej bry³y wzorcowe.
 */


#ifdef __GNUG__
#pragma interface
#endif



#include "listque.hh"
#include "vector3f.hh"
#include "viedge.hh"
#include "viedgeiterator.hh"
#include "diretableiterator.hh"
#include "extstring.hh"

class ExtString;
class ViFace;
class ViEdgeIterator;
class ViPattePolyhList;
class ViPattePolyhLib;  

/*!
 * Obiekty klasy ViPattePolyh (Pattern Polyhedron) tworz± bry³y wzorcowe.
 * Z ka¿dej takiej 
 * bry³y poprzez transformacjê wspó³rzêdnych i skali mo¿na tworzyæ obiekt
 * elementarny (\link ViElemePolyh ViElemePolyh\endlink). 
 * Z obiektów elementarnych tworzone s± obiekty
 * z³o¿one (\link ViMultiPolyh ViMultiPolyh\endlink).
 */

class ViPattePolyh: public ListItem<ViPattePolyh,0> {
     /*!
      * Nazwa bry³y wzorcowej. Musi byæ unikalna w ramach zbioru wszystkich
      * bry³ wzorcowych. Zbior tych bry³ dostêpny jest poprzez obiekt klasy
      * ViPattePolyhLib.
      */
   ExtString     _Name; 

   unsigned int  _VertexNo; /*!< Ilo¶æ wierzcho³ków bry³y                 */
   Vector3f      *_Vertex;  /*!< Tablica wspó³rzêdnych wierzho³ków bry³y  */

   unsigned int  _EdgesNo; /*!< Ilo¶æ krawêdzi bry³y                      */
   ViEdge       *_Edges;   /*!< Tablica krawêdzi bry³y                    */

   unsigned int  _FacesNo; /*!< Ilo¶æ ¶cianek bry³y                       */
   ViFace       *_Faces;   /*!< Tablica ¶cianek bry³y                     */

  public:
   /*!
    *  Typ pomocniczy zdefiniowany dla umo¿liwienia odwo³ywania
    *  siê do typu macierzystego poprzez skrócon± nazwê.
    *  Iterator tej klasy umo¿liwia dostêp do krawêdzi jako obiektów
    *  modyfikowalnych.
    */
   typedef DireTableIterator<ViEdge>         VarEdgeIter;

   /*!
    *  Typ pomocniczy zdefiniowany dla umo¿liwienia odwo³ywania
    *  siê do typu macierzystego poprzez skrócon± nazwê.
    *  Iterator tej klasy umo¿liwia dostêp do krawêdzi jako obiektów
    *  sta³ych.
    */
   typedef DireTableIterator<const ViEdge>   ConEdgeIter;



   /*!
    *  Typ pomocniczy zdefiniowany dla umo¿liwienia odwo³ywania
    *  siê do typu macierzystego poprzez skrócon± nazwê.
    *  Iterator tej klasy umo¿liwia dostêp do krawêdzi jako obiektów
    *  modyfikowalnych.
    */
   typedef DireTableIterator<ViFace>         VarFaceIter;

   /*!
    *  Typ pomocniczy zdefiniowany dla umo¿liwienia odwo³ywania
    *  siê do typu macierzystego poprzez skrócon± nazwê.
    *  Iterator tej klasy umo¿liwia dostêp do krawêdzi jako obiektów
    *  sta³ych.
    */
   typedef DireTableIterator<const ViFace>   ConFaceIter;



    /*!
     * Konstruktor inicjalizuje wszystkie pola warto¶ciami 0 (ilo¶æ
     *  wierzcho³ków, krawêdzi, ¶cianek oraz analogicznie warto¶ci NULL
     *  w polach wsk¼nikowych dla tablic  wierzcho³ków, krawêdzi i ¶cianek)
     */
   ViPattePolyh(void);
   ~ViPattePolyh(void);

  /*!
   *  Udostêpnia wska¼nik na listê, do której nale¿y.
   *  \retval Name - nazwa, biblioteki do której nale¿y,
   *  \retval \p NULL - w przypadku gdy nie jest zwi±zana z ¿adn± bibliotek±.
   */
   const ViPattePolyhList *GetPatteList() const;
  /*!
   *  Udostêpnia wska¼nik na bibliotekê, do której nale¿y.
   *  \retval Name - nazwa, biblioteki do której nale¿y,
   *  \retval \p NULL - w przypadku gdy nie jest zwi±zana z ¿adn± bibliotek±.
   */
   const ViPattePolyhLib  *GetPatteLib() const;

    /*!
     * Udostêpnia nazwê danej bry³y wzrocowej.
     */
   char const *GetName() const  { return _Name; }

  /*!
   * Udostêpnia nazwê listy.
   * \retval Name - nazwa listy,
   * \retval "?"  - w przypadku, gdy nie jest zwi±zana z ¿adn± list±.
   */
  const char *GetListName() const;
  /*!
   * Udostêpnia nazwê biblioteki, w sk³ad której wchodzi dana lista.
   * \retval Name - nazwa biblioteki,
   * \retval "?"  - w przypadku, gdy nie jest zwi±zana z ¿adn± bibliotek±.
   */
   const char *GetLibName() const;

    /*!
     * Udostêpnia nazwê danej bry³y bezpo¶renio w postaci referencji
     */
   ExtString const &GetStrName() const { return _Name; }

 
    /*!
     * Nadaje now± nazwê \e Name bryle wzorcowej.
     * \param Name - nowa nazwa dla bry³y wzorcowej.
     * \post 
     *   Nazwa nowej bry³y zostaje zmieniona na ³añcuch dostêpny
     *   poprzez parametr \e Name. £añcuch jest duplikowany
     *   w polu \e _Name.
     */
   void SetName(char const *Name);

    /*!
     * Inicjuje iterator do przegladania wszystkich krawêdzi.
     *
     * \warning Ten typ iteratora uwa¿any jest za przestarza³y i przeznaczony
     *          jest do usuniêcia. Do iteracji krawêdzi nale¿y korzystaæ 
     *          z iteratorów udostêpnianych przez metody
     *          \link ViPattePolyh::ConBegin_Edge ConBegin_Edge\endlink
     *          oraz \link ViPattePolyh::VarBegin_Edge VarBegin_Edge\endlink.
     */
   ViEdgeIterator InitEdgeIterator() const;

    /*!
     * Udostêpnia wspó³rzêdne wierzcho³ka o indeksie \e Idx. Wspó³rzêdne
     * wyra¿one s± w lokalnym uk³adzie wspó³rzêdnych bry³y.
     * \param Idx - indeks wiercho³ka.
     * \pre  0 <= Idx < \link ViPattePolyh::_VertexNo _VertexNo\endlink
     * \return 
     *    referencjê sta³± do wierzcho³ka o indeksie \e Idx.
     */
   Vector3f const &GetPattePolyhVtx(unsigned int Idx) const 
                                                     { return _Vertex[Idx]; }

    /*!
     * Udostêpnia w sposób bezpieczny wspó³rzêdne wierzcho³ka o indeksie
     * \e Idx.
     * \param Idx - indeks wiercho³ka.
     * \pre  0 <= Idx < \link ViPattePolyh::_VertexNo _VertexNo\endlink
     * \return 
     *    referencjê sta³± do wierzcho³ka o indeksie \e Idx.
     *    Je¶li indeks jest spoza dozwolonego przedzia³u, to
     *    zg³aszany jest wyj±tek ViExeption_out_of_range
     */
   Vector3f const &SGetPattePolyhVtx(unsigned int Idx) const
      {
        return Idx >= _VertexNo ? *_Vertex : _Vertex[Idx];
      }

    /*!
     * Przydziela pamiêæ dla tablicy wierzcho³ków. 
     * \param Number - ilo¶æ wierzcho³ków, dla których trzeba utworzyæ tablicê.
     * \retval true - je¶li operacja zosta³a wykonana poprawnie (pamiêæ
     *                 zosta³a przydzielona.
     *              Wska¼nik do tablicy zapisany zostaje w polu
     *              \link ViPattePolyh::_Vertex _Vertex\endlink.
     * \retval false - w przypadku przeciwnym.
     */
   bool CreateVertexTable(unsigned int Number);

    /*!
     * Przypisuje nowe warto¶ci wspó³rzêdnych wierzcho³kowi o indeksie
     * \e Idx.
     * \param Idx - indeks wierzcho³ka,
     * \param Vtx - nowe warto¶ci wspó³rzêdnych wierzcho³ka.
     * \pre   0 <= Idx < \link ViPattePolyh::_VertexNo _VertexNo\endlink
     * \retval true - je¶li operacja siê powiod³a, tzn. nowe warto¶ci 
     *              zosta³y podstawione do wierzcho³ka o indeksie $Idx$.
     * \retval false - w przpadku przeciwnym.
     */
   bool SetVtx(unsigned int Idx, Vector3f const &Vtx);


    /*!
     * Udostêpnia ilo¶æ wszystkich krawêdzi bry³y.
     */
   unsigned int GetEdgesNo() const { return _EdgesNo; }

    /*!
     *  Udostêpnia tablicê krawêdzi bry³y.
     */
   const ViEdge *GetEdgesTab() const { return _Edges; }

    /*!
     * Udostêpnia dane dotycz±ce wybranej krawêdzi.
     * \param  Idx - indeks krawêdzi.
     * \pre 
     *       0 <= \e Idx < \link ViPattePolyh::_EdgesNo _EdgesNo\endlink
     * \return
     *       indeks do obiektu reprezentuj±cego krawêd¼ o indeksie \e Idx.
     */
   const ViEdge *GetPolyhEdge(unsigned int Idx) const { return _Edges+Idx; }


    /*!
     * Udostêpnia obiekt reprezentuj±cy wybran± krawêd¼.
     * Obiekt udostêpniany jest do modyfikacji. Metoda ta nie powinna
     * byæ wywo³ywana nigdzie indziej poza funkcjami realizuj±cymi
     * wczytywanie obiektów wzorcowych z dysku.
     * \param Idx - indeks krawêdzi.
     * \pre 
     *       0 <= \e Idx < \link ViPattePolyh::_EdgesNo _EdgesNo\endlink
     * \return
     *       indeks do obiektu reprezentuj±cego krawêd¼ o indeksie \e Idx.
     */
   ViEdge *ModifyEdge(unsigned int Idx) { return _Edges+Idx; }


    /*!
     * Przydziela pamiêæ dla tablicy krawêdzi. Je¶li tablica zosta³
     * wcze¶niej ju¿ zaalokowana, to najpierw j± usuwa, a pó¼niej przydziela
     * pamiêæ dla nowej tablicy.
     * \param  Number - ilo¶æ krawêdzi bry³y, dla których zostaæ ma
     *                  zaalokowana tablica.
     * \retval  true - gdy tablica na ilo¶æ elementów \e Number zosta³a
     *                 poprawnie zaalokowana.
     *              Wska¼nik do tablicy zapisany zostaje w polu
     *              \link ViPattePolyh::_Edges _Edges\endlink.
     *          false - w przypadku przeciwnym.
     */
   bool CreateEdgesTable(unsigned int Number);

    /*!
     * Ustawia indeksy wierzcho³ków krawêdzi.
     * \param EdgeIdx - indeks krawêdzi,
     * \param FrtVtxIdx - indeks pierwszego wierzcho³ka dla danej krawêdzi,
     * \param SndVtxIdx - indeks drugiego wierzcho³ka dla danej krawêdzi.
     * \pre 0 <= EdgeIdx < \link ViPattePolyh::_EdgesNo _EdgesNo\endlink,
     *  0 <= FrtVtxIdx < \link ViPattePolyh::_VertexNo _VertexNo\endlink,  
     *  0 <= SndVtxIdx < \link ViPattePolyh::_VertexNo _VertexNo\endlink,  
     *
     * \retval true - je¶li operacja powiedzie siê (tzn. gdy s± spe³nione 
     *               warunki wstêpne). W takiej sytuacji do odpowiednich
     *        pól obiektu klasy \link ViEdge ViEdge\endlink zostaj± wpisane
     *        indeksy pierwszego i drugiego wierzcho³ka. Numery s±siaduj±cych
     *        ¶cianek zainicjalizowane zostaj± warto¶ciami NULLFACE.
     * \retval false - w przypadku przeciwnym.
     */
   bool SetEdgeVtx( unsigned int EdgeIdx, 
                    unsigned int FrtVtxIdx,
                    unsigned int SndVtxIdx
                  );


    /*!
     * Ustawia ID koloru krawêdzi. Metoda jest zasz³o¶ci±.
     * \param  EdgeIdx - indeks krawêdzi,
     * \param  Color   - indeks koloru.
     * \pre   0 <= EdgeIdx < \link ViPattePolyh::_EdgesNo _EdgesNo\endlink
     * \retval  true - je¶li istnieje krawêd¼ o danym indeksie, oznacza to
     *                 jednocze¶nie ustawienie koloru dla danej krawêdzi.
     * \retval  false - w przypadku przeciwnym.
     */
   bool SetEdgeColorID( unsigned int EdgeIdx, unsigned int Color);


    /*!
     * Metoda tworzy tablicê ¶cianek. Je¿eli wcze¶niej by³a ju¿ utworzona
     * taka tablica, to j± usuwa.
     * \param Size - ilo¶æ ¶cianek, dla których ma zostaæ zaalokowana
     *                tablica.
     * \retval 0  - je¶li wszystko powiodlo siê.
     *              Wska¼nik do tablicy zapisany zostaje w polu
     *              \link ViPattePolyh::_Faces _Faces\endlink.
     * \retval -1 - w przypadku przeciwnym.
     */
   bool CreateFacesTab( unsigned int Size );


    /*!
     * Wyznacza wektory normalne dla wszystkich ¶cianek bry³y wzorcowej
     * oraz inicjalizuje opis krawêdzi wzglêdem dla kolejnych ¶cianek.
     */
   void InitFacesData();

    /*!
     *  Udostêpnia tablicê ¶cianek bry³y. Tablica udostêpniana jest jako
     *  niemodyfikowalna.
     */
   ViFace const *GetFacesTab() const { return _Faces; }


    /*!
     *  Udostêpnia wska¼nik do ¶cianki o podanym indeksie. ¦cianka mo¿e
     *  byæ modyfikowana.
     *  \param  Idx - indeks ¶cianki.
     *  \pre 0 <= \e Idx  < \link ViPattePolyh::_VertexNo _VertexNo\endlink
     *  \return wska¼nik do obiektu (klasy \link ViFace ViFace\endlink)
     *          zawieraj±cego opis danej ¶cianki.
     */
   ViFace *UseFace(unsigned int Idx);

    /*!
     *  Udostêpnia wska¼nik do ¶cianki o podanym indeksie. ¦cianka 
     *  udostêpniana jest jako obiekt sta³y.
     *  \param  Idx - indeks ¶cianki.
     *  \pre 0 <= \e Idx  < \link ViPattePolyh::_VertexNo _VertexNo\endlink
     *  \return wska¼nik do obiektu (klasy \link ViFace ViFace\endlink)
     *          zawieraj±cego opis danej ¶cianki.
     */
   ViFace const *GetFace(unsigned int Idx) const;

    /*!
     *  Udostêpnia wska¼nik sta³y do ¶cianki o podanym indeksie. ¦cianka nie
     *  mo¿e byæ modyfikowana.
     *  \param  Idx - indeks ¶cianki.
     *  \pre 0 <= \e Idx  < \link ViPattePolyh::_VertexNo
     *                                           _VertexNo\endlink
     *  \return wska¼nik sta³y do obiektu (klasy \link ViFace ViFace\endlink)
     *          zawieraj±cego opis danej ¶cianki.
     */
   ViFace const *GetFigFace(unsigned int Idx) const;

    /*!
     *  Udostêpnia ilo¶æ ¶cianek bry³y (warto¶æ pola
     *   \link ViPattePolyh::_FacesNo  _FacesNo\endlink).
     */
   unsigned int GetFacesNo() const { return _FacesNo; }


    /*!
     *  Udostêpnia wspó³rzêdne wierzcho³ka.
     *  \param Idx - indeks wierzho³ka.
     *  \pre 
     *     0 <= \e Idx < \link ViPattePolyh::_VertexNo _VertexNo\endlink.
     *  \return 
     *       wspó³rzêdne wierzho³ka o indeksie \e Idx. Wspó³rzêdne
     *       wyra¿one s± w uk³adzie wspó³rzêdnych lokalnych bry³y
     *       wzorcowej.
     */
   Vector3f const &Vertex(unsigned int Idx) const { return _Vertex[Idx]; }

    /*!
     *  Udostêpnia ilo¶æ wierzcho³ków bry³y (warto¶æ pol
     *   \link ViPattePolyh::_VertexNo  _VertexNo\endlink).
     */
   unsigned int GetVtxNo() const { return _VertexNo; }


  //---------------- Iteratory dla krawêdzi -------------------------------
    /*!
     * Tworzy iterator dla krawêdzi danej bry³y. Iterator udostêpnia
     * obiekty klasy \link ViEdge ViEdge\endlink. S± one udostêpniane
     * jako obiekty sta³e. 
     */
   ConEdgeIter ConBegin_Edge() const
        { return ConEdgeIter(GetEdgesNo(),(ViEdge*)GetEdgesTab()); }

    /*!
     * Tworzy iterator dla krawêdzi danej bry³y. Iterator udostêpnia
     * obiekty klasy \link ViEdge ViEdge\endlink. S± one udostêpniane
     * w trybie modyfikacji. 
     */
   VarEdgeIter VarBegin_Edge()
        { return VarEdgeIter(GetEdgesNo(),(ViEdge*)GetEdgesTab()); }


  //---------------- Iteratory dla ¶cianek --------------------------------
    /*!
     * Tworzy iterator dla ¶cianek danej bry³y. Iterator udostêpnia
     * obiekty klasy \link ViFace ViFace\endlink. S± one udostêpniane
     * jako obiekty sta³e. 
     */
   ConFaceIter ConBegin_Face() const
        { return ConFaceIter(GetFacesNo(),(ViFace*)GetFacesTab()); }

    /*!
     * Tworzy iterator dla ¶cianek danej bry³y. Iterator udostêpnia
     * obiekty klasy \link ViFace ViFace\endlink. S± one udostêpniane
     * w trybie modyfikacji. 
     */
   VarFaceIter VarBegin_Face()
        { return VarFaceIter(GetFacesNo(),(ViFace*)GetFacesTab()); }

};

#endif
