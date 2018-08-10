#ifndef VIPATTEPOLYH_HH
#define VIPATTEPOLYH_HH

/*!  
 *  \file vipattepolyh.hh
 *  \author  Bogdan Kreczmer
 *  \date    2004.02
 *  Plik zawiera definicj� klasy \link ViPattePolyh ViPattePolyh\endlink
 *  modeluj�cej bry�y wzorcowe.
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
 * Obiekty klasy ViPattePolyh (Pattern Polyhedron) tworz� bry�y wzorcowe.
 * Z ka�dej takiej 
 * bry�y poprzez transformacj� wsp�rz�dnych i skali mo�na tworzy� obiekt
 * elementarny (\link ViElemePolyh ViElemePolyh\endlink). 
 * Z obiekt�w elementarnych tworzone s� obiekty
 * z�o�one (\link ViMultiPolyh ViMultiPolyh\endlink).
 */

class ViPattePolyh: public ListItem<ViPattePolyh,0> {
     /*!
      * Nazwa bry�y wzorcowej. Musi by� unikalna w ramach zbioru wszystkich
      * bry� wzorcowych. Zbior tych bry� dost�pny jest poprzez obiekt klasy
      * ViPattePolyhLib.
      */
   ExtString     _Name; 

   unsigned int  _VertexNo; /*!< Ilo�� wierzcho�k�w bry�y                 */
   Vector3f      *_Vertex;  /*!< Tablica wsp�rz�dnych wierzho�k�w bry�y  */

   unsigned int  _EdgesNo; /*!< Ilo�� kraw�dzi bry�y                      */
   ViEdge       *_Edges;   /*!< Tablica kraw�dzi bry�y                    */

   unsigned int  _FacesNo; /*!< Ilo�� �cianek bry�y                       */
   ViFace       *_Faces;   /*!< Tablica �cianek bry�y                     */

  public:
   /*!
    *  Typ pomocniczy zdefiniowany dla umo�liwienia odwo�ywania
    *  si� do typu macierzystego poprzez skr�con� nazw�.
    *  Iterator tej klasy umo�liwia dost�p do kraw�dzi jako obiekt�w
    *  modyfikowalnych.
    */
   typedef DireTableIterator<ViEdge>         VarEdgeIter;

   /*!
    *  Typ pomocniczy zdefiniowany dla umo�liwienia odwo�ywania
    *  si� do typu macierzystego poprzez skr�con� nazw�.
    *  Iterator tej klasy umo�liwia dost�p do kraw�dzi jako obiekt�w
    *  sta�ych.
    */
   typedef DireTableIterator<const ViEdge>   ConEdgeIter;



   /*!
    *  Typ pomocniczy zdefiniowany dla umo�liwienia odwo�ywania
    *  si� do typu macierzystego poprzez skr�con� nazw�.
    *  Iterator tej klasy umo�liwia dost�p do kraw�dzi jako obiekt�w
    *  modyfikowalnych.
    */
   typedef DireTableIterator<ViFace>         VarFaceIter;

   /*!
    *  Typ pomocniczy zdefiniowany dla umo�liwienia odwo�ywania
    *  si� do typu macierzystego poprzez skr�con� nazw�.
    *  Iterator tej klasy umo�liwia dost�p do kraw�dzi jako obiekt�w
    *  sta�ych.
    */
   typedef DireTableIterator<const ViFace>   ConFaceIter;



    /*!
     * Konstruktor inicjalizuje wszystkie pola warto�ciami 0 (ilo��
     *  wierzcho�k�w, kraw�dzi, �cianek oraz analogicznie warto�ci NULL
     *  w polach wsk�nikowych dla tablic  wierzcho�k�w, kraw�dzi i �cianek)
     */
   ViPattePolyh(void);
   ~ViPattePolyh(void);

  /*!
   *  Udost�pnia wska�nik na list�, do kt�rej nale�y.
   *  \retval Name - nazwa, biblioteki do kt�rej nale�y,
   *  \retval \p NULL - w przypadku gdy nie jest zwi�zana z �adn� bibliotek�.
   */
   const ViPattePolyhList *GetPatteList() const;
  /*!
   *  Udost�pnia wska�nik na bibliotek�, do kt�rej nale�y.
   *  \retval Name - nazwa, biblioteki do kt�rej nale�y,
   *  \retval \p NULL - w przypadku gdy nie jest zwi�zana z �adn� bibliotek�.
   */
   const ViPattePolyhLib  *GetPatteLib() const;

    /*!
     * Udost�pnia nazw� danej bry�y wzrocowej.
     */
   char const *GetName() const  { return _Name; }

  /*!
   * Udost�pnia nazw� listy.
   * \retval Name - nazwa listy,
   * \retval "?"  - w przypadku, gdy nie jest zwi�zana z �adn� list�.
   */
  const char *GetListName() const;
  /*!
   * Udost�pnia nazw� biblioteki, w sk�ad kt�rej wchodzi dana lista.
   * \retval Name - nazwa biblioteki,
   * \retval "?"  - w przypadku, gdy nie jest zwi�zana z �adn� bibliotek�.
   */
   const char *GetLibName() const;

    /*!
     * Udost�pnia nazw� danej bry�y bezpo�renio w postaci referencji
     */
   ExtString const &GetStrName() const { return _Name; }

 
    /*!
     * Nadaje now� nazw� \e Name bryle wzorcowej.
     * \param Name - nowa nazwa dla bry�y wzorcowej.
     * \post 
     *   Nazwa nowej bry�y zostaje zmieniona na �a�cuch dost�pny
     *   poprzez parametr \e Name. �a�cuch jest duplikowany
     *   w polu \e _Name.
     */
   void SetName(char const *Name);

    /*!
     * Inicjuje iterator do przegladania wszystkich kraw�dzi.
     *
     * \warning Ten typ iteratora uwa�any jest za przestarza�y i przeznaczony
     *          jest do usuni�cia. Do iteracji kraw�dzi nale�y korzysta� 
     *          z iterator�w udost�pnianych przez metody
     *          \link ViPattePolyh::ConBegin_Edge ConBegin_Edge\endlink
     *          oraz \link ViPattePolyh::VarBegin_Edge VarBegin_Edge\endlink.
     */
   ViEdgeIterator InitEdgeIterator() const;

    /*!
     * Udost�pnia wsp�rz�dne wierzcho�ka o indeksie \e Idx. Wsp�rz�dne
     * wyra�one s� w lokalnym uk�adzie wsp�rz�dnych bry�y.
     * \param Idx - indeks wiercho�ka.
     * \pre  0 <= Idx < \link ViPattePolyh::_VertexNo _VertexNo\endlink
     * \return 
     *    referencj� sta�� do wierzcho�ka o indeksie \e Idx.
     */
   Vector3f const &GetPattePolyhVtx(unsigned int Idx) const 
                                                     { return _Vertex[Idx]; }

    /*!
     * Udost�pnia w spos�b bezpieczny wsp�rz�dne wierzcho�ka o indeksie
     * \e Idx.
     * \param Idx - indeks wiercho�ka.
     * \pre  0 <= Idx < \link ViPattePolyh::_VertexNo _VertexNo\endlink
     * \return 
     *    referencj� sta�� do wierzcho�ka o indeksie \e Idx.
     *    Je�li indeks jest spoza dozwolonego przedzia�u, to
     *    zg�aszany jest wyj�tek ViExeption_out_of_range
     */
   Vector3f const &SGetPattePolyhVtx(unsigned int Idx) const
      {
        return Idx >= _VertexNo ? *_Vertex : _Vertex[Idx];
      }

    /*!
     * Przydziela pami�� dla tablicy wierzcho�k�w. 
     * \param Number - ilo�� wierzcho�k�w, dla kt�rych trzeba utworzy� tablic�.
     * \retval true - je�li operacja zosta�a wykonana poprawnie (pami��
     *                 zosta�a przydzielona.
     *              Wska�nik do tablicy zapisany zostaje w polu
     *              \link ViPattePolyh::_Vertex _Vertex\endlink.
     * \retval false - w przypadku przeciwnym.
     */
   bool CreateVertexTable(unsigned int Number);

    /*!
     * Przypisuje nowe warto�ci wsp�rz�dnych wierzcho�kowi o indeksie
     * \e Idx.
     * \param Idx - indeks wierzcho�ka,
     * \param Vtx - nowe warto�ci wsp�rz�dnych wierzcho�ka.
     * \pre   0 <= Idx < \link ViPattePolyh::_VertexNo _VertexNo\endlink
     * \retval true - je�li operacja si� powiod�a, tzn. nowe warto�ci 
     *              zosta�y podstawione do wierzcho�ka o indeksie $Idx$.
     * \retval false - w przpadku przeciwnym.
     */
   bool SetVtx(unsigned int Idx, Vector3f const &Vtx);


    /*!
     * Udost�pnia ilo�� wszystkich kraw�dzi bry�y.
     */
   unsigned int GetEdgesNo() const { return _EdgesNo; }

    /*!
     *  Udost�pnia tablic� kraw�dzi bry�y.
     */
   const ViEdge *GetEdgesTab() const { return _Edges; }

    /*!
     * Udost�pnia dane dotycz�ce wybranej kraw�dzi.
     * \param  Idx - indeks kraw�dzi.
     * \pre 
     *       0 <= \e Idx < \link ViPattePolyh::_EdgesNo _EdgesNo\endlink
     * \return
     *       indeks do obiektu reprezentuj�cego kraw�d� o indeksie \e Idx.
     */
   const ViEdge *GetPolyhEdge(unsigned int Idx) const { return _Edges+Idx; }


    /*!
     * Udost�pnia obiekt reprezentuj�cy wybran� kraw�d�.
     * Obiekt udost�pniany jest do modyfikacji. Metoda ta nie powinna
     * by� wywo�ywana nigdzie indziej poza funkcjami realizuj�cymi
     * wczytywanie obiekt�w wzorcowych z dysku.
     * \param Idx - indeks kraw�dzi.
     * \pre 
     *       0 <= \e Idx < \link ViPattePolyh::_EdgesNo _EdgesNo\endlink
     * \return
     *       indeks do obiektu reprezentuj�cego kraw�d� o indeksie \e Idx.
     */
   ViEdge *ModifyEdge(unsigned int Idx) { return _Edges+Idx; }


    /*!
     * Przydziela pami�� dla tablicy kraw�dzi. Je�li tablica zosta�
     * wcze�niej ju� zaalokowana, to najpierw j� usuwa, a p�niej przydziela
     * pami�� dla nowej tablicy.
     * \param  Number - ilo�� kraw�dzi bry�y, dla kt�rych zosta� ma
     *                  zaalokowana tablica.
     * \retval  true - gdy tablica na ilo�� element�w \e Number zosta�a
     *                 poprawnie zaalokowana.
     *              Wska�nik do tablicy zapisany zostaje w polu
     *              \link ViPattePolyh::_Edges _Edges\endlink.
     *          false - w przypadku przeciwnym.
     */
   bool CreateEdgesTable(unsigned int Number);

    /*!
     * Ustawia indeksy wierzcho�k�w kraw�dzi.
     * \param EdgeIdx - indeks kraw�dzi,
     * \param FrtVtxIdx - indeks pierwszego wierzcho�ka dla danej kraw�dzi,
     * \param SndVtxIdx - indeks drugiego wierzcho�ka dla danej kraw�dzi.
     * \pre 0 <= EdgeIdx < \link ViPattePolyh::_EdgesNo _EdgesNo\endlink,
     *  0 <= FrtVtxIdx < \link ViPattePolyh::_VertexNo _VertexNo\endlink,  
     *  0 <= SndVtxIdx < \link ViPattePolyh::_VertexNo _VertexNo\endlink,  
     *
     * \retval true - je�li operacja powiedzie si� (tzn. gdy s� spe�nione 
     *               warunki wst�pne). W takiej sytuacji do odpowiednich
     *        p�l obiektu klasy \link ViEdge ViEdge\endlink zostaj� wpisane
     *        indeksy pierwszego i drugiego wierzcho�ka. Numery s�siaduj�cych
     *        �cianek zainicjalizowane zostaj� warto�ciami NULLFACE.
     * \retval false - w przypadku przeciwnym.
     */
   bool SetEdgeVtx( unsigned int EdgeIdx, 
                    unsigned int FrtVtxIdx,
                    unsigned int SndVtxIdx
                  );


    /*!
     * Ustawia ID koloru kraw�dzi. Metoda jest zasz�o�ci�.
     * \param  EdgeIdx - indeks kraw�dzi,
     * \param  Color   - indeks koloru.
     * \pre   0 <= EdgeIdx < \link ViPattePolyh::_EdgesNo _EdgesNo\endlink
     * \retval  true - je�li istnieje kraw�d� o danym indeksie, oznacza to
     *                 jednocze�nie ustawienie koloru dla danej kraw�dzi.
     * \retval  false - w przypadku przeciwnym.
     */
   bool SetEdgeColorID( unsigned int EdgeIdx, unsigned int Color);


    /*!
     * Metoda tworzy tablic� �cianek. Je�eli wcze�niej by�a ju� utworzona
     * taka tablica, to j� usuwa.
     * \param Size - ilo�� �cianek, dla kt�rych ma zosta� zaalokowana
     *                tablica.
     * \retval 0  - je�li wszystko powiodlo si�.
     *              Wska�nik do tablicy zapisany zostaje w polu
     *              \link ViPattePolyh::_Faces _Faces\endlink.
     * \retval -1 - w przypadku przeciwnym.
     */
   bool CreateFacesTab( unsigned int Size );


    /*!
     * Wyznacza wektory normalne dla wszystkich �cianek bry�y wzorcowej
     * oraz inicjalizuje opis kraw�dzi wzgl�dem dla kolejnych �cianek.
     */
   void InitFacesData();

    /*!
     *  Udost�pnia tablic� �cianek bry�y. Tablica udost�pniana jest jako
     *  niemodyfikowalna.
     */
   ViFace const *GetFacesTab() const { return _Faces; }


    /*!
     *  Udost�pnia wska�nik do �cianki o podanym indeksie. �cianka mo�e
     *  by� modyfikowana.
     *  \param  Idx - indeks �cianki.
     *  \pre 0 <= \e Idx  < \link ViPattePolyh::_VertexNo _VertexNo\endlink
     *  \return wska�nik do obiektu (klasy \link ViFace ViFace\endlink)
     *          zawieraj�cego opis danej �cianki.
     */
   ViFace *UseFace(unsigned int Idx);

    /*!
     *  Udost�pnia wska�nik do �cianki o podanym indeksie. �cianka 
     *  udost�pniana jest jako obiekt sta�y.
     *  \param  Idx - indeks �cianki.
     *  \pre 0 <= \e Idx  < \link ViPattePolyh::_VertexNo _VertexNo\endlink
     *  \return wska�nik do obiektu (klasy \link ViFace ViFace\endlink)
     *          zawieraj�cego opis danej �cianki.
     */
   ViFace const *GetFace(unsigned int Idx) const;

    /*!
     *  Udost�pnia wska�nik sta�y do �cianki o podanym indeksie. �cianka nie
     *  mo�e by� modyfikowana.
     *  \param  Idx - indeks �cianki.
     *  \pre 0 <= \e Idx  < \link ViPattePolyh::_VertexNo
     *                                           _VertexNo\endlink
     *  \return wska�nik sta�y do obiektu (klasy \link ViFace ViFace\endlink)
     *          zawieraj�cego opis danej �cianki.
     */
   ViFace const *GetFigFace(unsigned int Idx) const;

    /*!
     *  Udost�pnia ilo�� �cianek bry�y (warto�� pola
     *   \link ViPattePolyh::_FacesNo  _FacesNo\endlink).
     */
   unsigned int GetFacesNo() const { return _FacesNo; }


    /*!
     *  Udost�pnia wsp�rz�dne wierzcho�ka.
     *  \param Idx - indeks wierzho�ka.
     *  \pre 
     *     0 <= \e Idx < \link ViPattePolyh::_VertexNo _VertexNo\endlink.
     *  \return 
     *       wsp�rz�dne wierzho�ka o indeksie \e Idx. Wsp�rz�dne
     *       wyra�one s� w uk�adzie wsp�rz�dnych lokalnych bry�y
     *       wzorcowej.
     */
   Vector3f const &Vertex(unsigned int Idx) const { return _Vertex[Idx]; }

    /*!
     *  Udost�pnia ilo�� wierzcho�k�w bry�y (warto�� pol
     *   \link ViPattePolyh::_VertexNo  _VertexNo\endlink).
     */
   unsigned int GetVtxNo() const { return _VertexNo; }


  //---------------- Iteratory dla kraw�dzi -------------------------------
    /*!
     * Tworzy iterator dla kraw�dzi danej bry�y. Iterator udost�pnia
     * obiekty klasy \link ViEdge ViEdge\endlink. S� one udost�pniane
     * jako obiekty sta�e. 
     */
   ConEdgeIter ConBegin_Edge() const
        { return ConEdgeIter(GetEdgesNo(),(ViEdge*)GetEdgesTab()); }

    /*!
     * Tworzy iterator dla kraw�dzi danej bry�y. Iterator udost�pnia
     * obiekty klasy \link ViEdge ViEdge\endlink. S� one udost�pniane
     * w trybie modyfikacji. 
     */
   VarEdgeIter VarBegin_Edge()
        { return VarEdgeIter(GetEdgesNo(),(ViEdge*)GetEdgesTab()); }


  //---------------- Iteratory dla �cianek --------------------------------
    /*!
     * Tworzy iterator dla �cianek danej bry�y. Iterator udost�pnia
     * obiekty klasy \link ViFace ViFace\endlink. S� one udost�pniane
     * jako obiekty sta�e. 
     */
   ConFaceIter ConBegin_Face() const
        { return ConFaceIter(GetFacesNo(),(ViFace*)GetFacesTab()); }

    /*!
     * Tworzy iterator dla �cianek danej bry�y. Iterator udost�pnia
     * obiekty klasy \link ViFace ViFace\endlink. S� one udost�pniane
     * w trybie modyfikacji. 
     */
   VarFaceIter VarBegin_Face()
        { return VarFaceIter(GetFacesNo(),(ViFace*)GetFacesTab()); }

};

#endif
