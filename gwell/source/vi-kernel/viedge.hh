#ifndef VIEDGE_HH
#define VIEDGE_HH

/*!
 *  Stanowi identyfikator pozwlaj�cy stwierdzi�, �e kraw�d� nie s�siaduje z
 *  �adn� �ciank� po danej stronie. Zdefiniowna warto�� mo�e pojawi� si�
 *  w polach \link ViEdge::_LeftFaceIdx _LeftFaceIdx\endlink lub 
 *   \link ViEdge::_LeftFaceIdx _LeftFaceIdx\endlink. Warto�� tego indyfikatora
 *  jest r�wnie� przejawem za�o�enia, �e bry�a elementarna nie mo�e mie� wi�cej
 *  �cianek ni� 4096.
 */
#define ET_NULLFACE  4096
#include <iostream>
#include "vector3f.hh"

/*!
 * \file viedge.hh
 *  Plik zawiera definicj� klasy ViEdge. Obiekty tej klasy
 *  reprezentuj� kraw�dzie bry�y
 *  elementarnej, kt�ra modelowana jest� przez klas� ViPattePolyh.
 *  Obiekty klasy ViEdge nie stanowi�  bezpo�redniej reprezentacji kraw�dzi
 *  �cianki bry�y, gdy� nie
 *  uwzgl�dnia orientacji danej �cianki. Tak� reprezentacj� zapewniaj�
 *  obiekty klasy  ViFaceEdge.
 * \author Bogdan Kreczmer
 * \date   2003.10
 */


class ViPattePolyh;
class ViFace;

/*!
 * Obiekt klasy ViEdge zawiera dane dotycz� pojedynczej kraw�dzi bry�y
 * wzorcowej (\link ViPattePolyh ViPattePolyh \endlink). 
 * Do danych tych nale�y numer 
 * pierwszego i drugiego wierzcho�ka
 * pomi�dzy kt�rymi przebiega kraw�d�. Numery s� indeksami w tablicy
 * dost�pnej w obiekcie klasy \link ViPattePolyh ViPattePolyh\endlink. 
 * Klasa ViEdge zawiera r�wnie� metody
 * pozwalaj�ce na bezpo�redni dost�p do tych wierzcho�k�w.
 *
 *   W obiekcie klasy ViEdge dost�pe s� r�wnie� numery �cianek bry�y,
 * kt�re maj� wsp�ln� dan� krew�dz. �cianki te okre�lane s� jako prawa i lewa.
 * Odpowiada to ich lokalizacji wzgl�dem danej kraw�dzi przy za�o�eniu, �e
 * idziemy od pierwszego wierzcho�ka do drugiego i poruszamy si� na zewn�trz
 * bry�y.
 *
 * \warning Bry�y nie musz� mie� wszystkich �cian. Dlatego te� niekt�re
 *         kraw�dzie mog� mie� tylko po jednej stronie �ciank� lub istnie�
 *         samodzielnie.
 *
 * Klasa ta zawiera r�wnie� metody pozwalaj�ce na bezpo�redni dost�p do
 * wspomnianych �cian.
 *
 * \warning Obiekty tej klasy nie stanowi�  bezpo�redniej reprezentacji kraw�d�
 *  i �cianki bry�y, gdy� nie
 *  uwzgl�dnia orientacji danej �cianki. Tak� reprezentacj� zapewniaj� obiekty
 *  klasy  ViFaceEdge.
 *
 */

class ViEdge {

   /*!
    * Referencja do obiektu klasy \link ViPattePolyh ViPattePolyh\endlink
    * b�d�cego w�a�cicielem danej kraw�dzi.
    */   
  ViPattePolyh  &_Owner;

   /*!
    * Indeksy pierwszego wierzcho�ka kraw�dzi. 
    */
  unsigned int  _FirstVtxIdx;

   /*!
    * Indeksy drugiego wierzcho�ka kraw�dzi. 
    */
  unsigned int  _SecondVtxIdx; 


   /*!
    * Indeksy lewej �ciany wzd�u� danej kraw�dzi. 
    */
  unsigned int  _LeftFaceIdx;

   /*!
    * Indeksy prawej �ciany wzd�u� danej kraw�dzi. 
    */
  unsigned int  _RightFaceIdx;

   /*!
    * Identyfikator koloru danej kraw�dzi.
    */
  unsigned int  _ColorID;

 public:



     /*!
      * Jest to jedyny dopuszczalny konstruktor obiekt�w tej klasy.
      * \param  Owner - referencja do obiektu wzorcowego, do kt�rego
      *         nale�y kraw�d� modelowna przez tworzony obiekt.
      * \return Pole \link ViEdge::_Owner _Owner\endlink jest inicjalizowane
      *      warto�ci� parametru \e Owner. Natomiast pola 
      *      \link  ViEdge::_LeftFaceIdx _LeftFaceIdx\endlink oraz
      *      \link  ViEdge::_RightFaceIdx _RightFaceIdx\endlink inicjalizowane
      *      s� wartosci� ET_NULLFACE. Pole 
      *      \link ViEdge::_ColorID  _ColorID\endlink inicjalizowane jest
      *      warto�ci� 0.
      */
  ViEdge(ViPattePolyh &Owner): _Owner(Owner) 
                  { SetFacesIdx(ET_NULLFACE,ET_NULLFACE);  SetColorID(0);}
  ~ViEdge() {}

     /*!
      * Nadaje now� warto�� identyfikatorowi koloru kraw�dzi.
      */
  void SetColorID(unsigned int Color) { _ColorID = Color; }

     /*!
      * Udost�pnia indentyfikator koloru kraw�dzi.
      */
  unsigned int GetColorID() const { return _ColorID; }

     /*!
      * Nadaje now� warto�� numerowi pierwszego indeksu wierzcho�ka.
      * \param  VtxIdx - numer indeksu wierzcho�ka.
      * \return Warto�� parametru \e VtxIdx zostaje podstawiona
      *         do pola \link ViEdge::_FirstVtxIdx _FirstVtxIdx\endlink.
      */
  void SetFirstVtxIdx(unsigned int VtxIdx) {  _FirstVtxIdx = VtxIdx; }

     /*!
      * Nadaje now� warto�� numerowi drugiego indeksu wierzcho�ka.
      * \param  VtxIdx - numer indeksu wierzcho�ka.
      * \return Warto�� parametru \e VtxIdx zostaje podstawiona
      *         do pola \link ViEdge::_SecondVtxIdx _SecondVtxIdx\endlink.
      */
  void SetSecondVtxIdx(unsigned int VtxIdx)  {  _SecondVtxIdx = VtxIdx; }

     /*!
      * Nadaje nowe warto�ci numer�w indeks�w wierzcho�k�w.
      * \param  FstVtxIdx - numer indeksu pierwszego wierzcho�ka.
      * \param  SndVtxIdx - numer indeksu drugiego wierzcho�ka.
      * \return Warto�� parametru \e FstVtxIdx zostaje podstawiona do 
      *         do pola \link ViEdge::_FirstVtxIdx _FirstVtxIdx\endlink, 
      *         za� parametru \e SndVtxIdx do
      *         pola  \link ViEdge::_SecondVtxIdx _SecondVtxIdx\endlink.
      */
  void SetVtxIdx(unsigned int FstVtxIdx, unsigned int SndVtxIdx)
            {  SetFirstVtxIdx(FstVtxIdx);  SetSecondVtxIdx(SndVtxIdx); }


     /*!
      * Nadaje now� warto�� numerowi indeksu lewej �cianki.
      * \param FaceIdx - numer indeksu �cianki.
      * \return Warto�� parametru \e FaceIdx zostaje podstawiona do pola
      *         \link  ViEdge::_LeftFaceIdx _LeftFaceIdx\endlink.
      */
  void SetLeftFaceIdx(unsigned int FaceIdx)   {  _LeftFaceIdx = FaceIdx; }

     /*!
      * Nadaje now� warto�� numerowi indeksu prawej �cianki.
      * \param FaceIdx - numer indeksu �cianki.
      * \return Warto�� parametru \e FaceIdx zostaje podstawiona do pola
      *         \link  ViEdge::_RightFaceIdx _RightFaceIdx\endlink.
      */
  void SetRightFaceIdx(unsigned int FaceIdx)  {  _RightFaceIdx = FaceIdx; }

     /*!
      * Nadaje nowe warto�ci numerom indeks�w lewej i prawej �cianki.
      * \param LeftFaceIdx - numer indeksu lewej �cianki.
      * \param RightFaceIdx - numer indeksu prawej �cianki.
      * \return Warto�� parametru \e LeftFaceIdx zostaje podstawiona do pola
      *     \link  ViEdge::_LeftFaceIdx _LeftFaceIdx\endlink,
      *     za� warto�� parametru \e RightFaceIdx zostaje podstawiona do pola
      *     \link  ViEdge::_RightFaceIdx _RightFaceIdx\endlink.
      */
  void SetFacesIdx(unsigned int LeftFaceIdx, unsigned int RightFaceIdx)
            {  SetLeftFaceIdx(LeftFaceIdx);  SetRightFaceIdx(RightFaceIdx); }


     /*!
      * Udost�pnia indeks prawej �cianki.
      */
  unsigned int GetRightFaceIdx() const { return _RightFaceIdx; }

     /*!
      * Udost�pnia indeks lewej �cianki.
      */
  unsigned int GetLeftFaceIdx() const  { return _LeftFaceIdx; }

     /*!
      * Udost�pnia indeks pierwszego wierzcho�ka.
      */
  unsigned int GetFirstVtxIdx() const { return _FirstVtxIdx; }

     /*!
      * Udost�pnia indeks drugiego wierzcho�ka.
      */
  unsigned int GetSecondVtxIdx() const { return _SecondVtxIdx; }

     /*!
      * Udost�pnia wska�nik do prawej �cianki.
      */
  ViFace const *GetRightFace() const;

     /*!
      * Udost�pnia wska�nik do lewej �cianki.
      */
  ViFace const *GetLeftFace() const;

     /*!
      * Udost�pnia referencj� do pierwszego wierzcho�ka.
      */
  Vector3f const &GetFirstVtx() const;

     /*!
      * Udost�pnia referencj� do drugiego wierzcho�ka.
      */
  Vector3f const &GetSecondVtx() const;


     /*!
      * Pozwala stwierdzi� czy po lewej stronie kraw�dzi jest �cianka.
      * \retval true - gdy po lewej stronie kraw�dzi jest �cianka.
      * \retval false - w przypadku przeciwnym.
      */
  bool IsLeftFace() const { return GetLeftFaceIdx() != ET_NULLFACE; }


     /*!
      * Pozwala stwierdzi� czy po prawej stronie kraw�dzi jest �cianka.
      * \retval true - gdy po prawej stronie kraw�dzi jest �cianka.
      * \retval false - w przypadku przeciwnym.
      */
  bool IsRightFace() const { return GetRightFaceIdx() != ET_NULLFACE; }


   /*! 
    * Metoda umo�liwia okre�lenie czy kraw�d� jest widoczna
    * z danego kierunku patrzenia. Metoda przeznaczona jest tylko
    * do rysowania miniaturek figur wzorcowych. Nie ma zastosowania
    * w przypadku rysowania w uk�adzie wsp�rz�dnych globalnych.
    * \param ViewVct - wektor kierunku patrzenia. Wektor skierowany
    *                  jest od oka w kierunku przedmiotu.
    * \retval true - je�li kraw�d� jest widoczna,
    * \retval false - w przypadku przeciwnym.
    */
  bool IsVisible(const Vector3f &ViewVct) const;
};

/*!
 *  Wy�wietla informacje dotycz�ce danej kraw�dzi (wsp�rz�dne pierwszego
 *  i drugiego wierzcho�ka, ich kolejno�� nie ma zwi�zku z orientacj�
 *  �adnej ze �cianek, do kt�rych nale�y ta kraw�d�).
 */
std::ostream &operator  << (std::ostream &ostrm, ViEdge const &Edge);


#endif
