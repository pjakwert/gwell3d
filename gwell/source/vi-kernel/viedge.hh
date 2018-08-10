#ifndef VIEDGE_HH
#define VIEDGE_HH

/*!
 *  Stanowi identyfikator pozwlaj±cy stwierdziæ, ¿e krawêd¼ nie s±siaduje z
 *  ¿adn± ¶ciank± po danej stronie. Zdefiniowna warto¶æ mo¿e pojawiæ siê
 *  w polach \link ViEdge::_LeftFaceIdx _LeftFaceIdx\endlink lub 
 *   \link ViEdge::_LeftFaceIdx _LeftFaceIdx\endlink. Warto¶æ tego indyfikatora
 *  jest równie¿ przejawem za³o¿enia, ¿e bry³a elementarna nie mo¿e mieæ wiêcej
 *  ¶cianek ni¿ 4096.
 */
#define ET_NULLFACE  4096
#include <iostream>
#include "vector3f.hh"

/*!
 * \file viedge.hh
 *  Plik zawiera definicjê klasy ViEdge. Obiekty tej klasy
 *  reprezentuj± krawêdzie bry³y
 *  elementarnej, która modelowana jest± przez klasê ViPattePolyh.
 *  Obiekty klasy ViEdge nie stanowi±  bezpo¶redniej reprezentacji krawêdzi
 *  ¶cianki bry³y, gdy¿ nie
 *  uwzglêdnia orientacji danej ¶cianki. Tak± reprezentacjê zapewniaj±
 *  obiekty klasy  ViFaceEdge.
 * \author Bogdan Kreczmer
 * \date   2003.10
 */


class ViPattePolyh;
class ViFace;

/*!
 * Obiekt klasy ViEdge zawiera dane dotycz± pojedynczej krawêdzi bry³y
 * wzorcowej (\link ViPattePolyh ViPattePolyh \endlink). 
 * Do danych tych nale¿y numer 
 * pierwszego i drugiego wierzcho³ka
 * pomiêdzy którymi przebiega krawêd¼. Numery s± indeksami w tablicy
 * dostêpnej w obiekcie klasy \link ViPattePolyh ViPattePolyh\endlink. 
 * Klasa ViEdge zawiera równie¿ metody
 * pozwalaj±ce na bezpo¶redni dostêp do tych wierzcho³ków.
 *
 *   W obiekcie klasy ViEdge dostêpe s± równie¿ numery ¶cianek bry³y,
 * które maj± wspóln± dan± krewêdz. ¦cianki te okre¶lane s± jako prawa i lewa.
 * Odpowiada to ich lokalizacji wzglêdem danej krawêdzi przy za³o¿eniu, ¿e
 * idziemy od pierwszego wierzcho³ka do drugiego i poruszamy siê na zewn±trz
 * bry³y.
 *
 * \warning Bry³y nie musz± mieæ wszystkich ¶cian. Dlatego te¿ niektóre
 *         krawêdzie mog± mieæ tylko po jednej stronie ¶ciankê lub istnieæ
 *         samodzielnie.
 *
 * Klasa ta zawiera równie¿ metody pozwalaj±ce na bezpo¶redni dostêp do
 * wspomnianych ¶cian.
 *
 * \warning Obiekty tej klasy nie stanowi±  bezpo¶redniej reprezentacji krawêd¼
 *  i ¶cianki bry³y, gdy¿ nie
 *  uwzglêdnia orientacji danej ¶cianki. Tak± reprezentacjê zapewniaj± obiekty
 *  klasy  ViFaceEdge.
 *
 */

class ViEdge {

   /*!
    * Referencja do obiektu klasy \link ViPattePolyh ViPattePolyh\endlink
    * bêd±cego w³a¶cicielem danej krawêdzi.
    */   
  ViPattePolyh  &_Owner;

   /*!
    * Indeksy pierwszego wierzcho³ka krawêdzi. 
    */
  unsigned int  _FirstVtxIdx;

   /*!
    * Indeksy drugiego wierzcho³ka krawêdzi. 
    */
  unsigned int  _SecondVtxIdx; 


   /*!
    * Indeksy lewej ¶ciany wzd³u¿ danej krawêdzi. 
    */
  unsigned int  _LeftFaceIdx;

   /*!
    * Indeksy prawej ¶ciany wzd³u¿ danej krawêdzi. 
    */
  unsigned int  _RightFaceIdx;

   /*!
    * Identyfikator koloru danej krawêdzi.
    */
  unsigned int  _ColorID;

 public:



     /*!
      * Jest to jedyny dopuszczalny konstruktor obiektów tej klasy.
      * \param  Owner - referencja do obiektu wzorcowego, do którego
      *         nale¿y krawêd¼ modelowna przez tworzony obiekt.
      * \return Pole \link ViEdge::_Owner _Owner\endlink jest inicjalizowane
      *      warto¶ci± parametru \e Owner. Natomiast pola 
      *      \link  ViEdge::_LeftFaceIdx _LeftFaceIdx\endlink oraz
      *      \link  ViEdge::_RightFaceIdx _RightFaceIdx\endlink inicjalizowane
      *      s± wartosci± ET_NULLFACE. Pole 
      *      \link ViEdge::_ColorID  _ColorID\endlink inicjalizowane jest
      *      warto¶ci± 0.
      */
  ViEdge(ViPattePolyh &Owner): _Owner(Owner) 
                  { SetFacesIdx(ET_NULLFACE,ET_NULLFACE);  SetColorID(0);}
  ~ViEdge() {}

     /*!
      * Nadaje now± warto¶æ identyfikatorowi koloru krawêdzi.
      */
  void SetColorID(unsigned int Color) { _ColorID = Color; }

     /*!
      * Udostêpnia indentyfikator koloru krawêdzi.
      */
  unsigned int GetColorID() const { return _ColorID; }

     /*!
      * Nadaje now± warto¶æ numerowi pierwszego indeksu wierzcho³ka.
      * \param  VtxIdx - numer indeksu wierzcho³ka.
      * \return Warto¶æ parametru \e VtxIdx zostaje podstawiona
      *         do pola \link ViEdge::_FirstVtxIdx _FirstVtxIdx\endlink.
      */
  void SetFirstVtxIdx(unsigned int VtxIdx) {  _FirstVtxIdx = VtxIdx; }

     /*!
      * Nadaje now± warto¶æ numerowi drugiego indeksu wierzcho³ka.
      * \param  VtxIdx - numer indeksu wierzcho³ka.
      * \return Warto¶æ parametru \e VtxIdx zostaje podstawiona
      *         do pola \link ViEdge::_SecondVtxIdx _SecondVtxIdx\endlink.
      */
  void SetSecondVtxIdx(unsigned int VtxIdx)  {  _SecondVtxIdx = VtxIdx; }

     /*!
      * Nadaje nowe warto¶ci numerów indeksów wierzcho³ków.
      * \param  FstVtxIdx - numer indeksu pierwszego wierzcho³ka.
      * \param  SndVtxIdx - numer indeksu drugiego wierzcho³ka.
      * \return Warto¶æ parametru \e FstVtxIdx zostaje podstawiona do 
      *         do pola \link ViEdge::_FirstVtxIdx _FirstVtxIdx\endlink, 
      *         za¶ parametru \e SndVtxIdx do
      *         pola  \link ViEdge::_SecondVtxIdx _SecondVtxIdx\endlink.
      */
  void SetVtxIdx(unsigned int FstVtxIdx, unsigned int SndVtxIdx)
            {  SetFirstVtxIdx(FstVtxIdx);  SetSecondVtxIdx(SndVtxIdx); }


     /*!
      * Nadaje now± warto¶æ numerowi indeksu lewej ¶cianki.
      * \param FaceIdx - numer indeksu ¶cianki.
      * \return Warto¶æ parametru \e FaceIdx zostaje podstawiona do pola
      *         \link  ViEdge::_LeftFaceIdx _LeftFaceIdx\endlink.
      */
  void SetLeftFaceIdx(unsigned int FaceIdx)   {  _LeftFaceIdx = FaceIdx; }

     /*!
      * Nadaje now± warto¶æ numerowi indeksu prawej ¶cianki.
      * \param FaceIdx - numer indeksu ¶cianki.
      * \return Warto¶æ parametru \e FaceIdx zostaje podstawiona do pola
      *         \link  ViEdge::_RightFaceIdx _RightFaceIdx\endlink.
      */
  void SetRightFaceIdx(unsigned int FaceIdx)  {  _RightFaceIdx = FaceIdx; }

     /*!
      * Nadaje nowe warto¶ci numerom indeksów lewej i prawej ¶cianki.
      * \param LeftFaceIdx - numer indeksu lewej ¶cianki.
      * \param RightFaceIdx - numer indeksu prawej ¶cianki.
      * \return Warto¶æ parametru \e LeftFaceIdx zostaje podstawiona do pola
      *     \link  ViEdge::_LeftFaceIdx _LeftFaceIdx\endlink,
      *     za¶ warto¶æ parametru \e RightFaceIdx zostaje podstawiona do pola
      *     \link  ViEdge::_RightFaceIdx _RightFaceIdx\endlink.
      */
  void SetFacesIdx(unsigned int LeftFaceIdx, unsigned int RightFaceIdx)
            {  SetLeftFaceIdx(LeftFaceIdx);  SetRightFaceIdx(RightFaceIdx); }


     /*!
      * Udostêpnia indeks prawej ¶cianki.
      */
  unsigned int GetRightFaceIdx() const { return _RightFaceIdx; }

     /*!
      * Udostêpnia indeks lewej ¶cianki.
      */
  unsigned int GetLeftFaceIdx() const  { return _LeftFaceIdx; }

     /*!
      * Udostêpnia indeks pierwszego wierzcho³ka.
      */
  unsigned int GetFirstVtxIdx() const { return _FirstVtxIdx; }

     /*!
      * Udostêpnia indeks drugiego wierzcho³ka.
      */
  unsigned int GetSecondVtxIdx() const { return _SecondVtxIdx; }

     /*!
      * Udostêpnia wska¼nik do prawej ¶cianki.
      */
  ViFace const *GetRightFace() const;

     /*!
      * Udostêpnia wska¼nik do lewej ¶cianki.
      */
  ViFace const *GetLeftFace() const;

     /*!
      * Udostêpnia referencjê do pierwszego wierzcho³ka.
      */
  Vector3f const &GetFirstVtx() const;

     /*!
      * Udostêpnia referencjê do drugiego wierzcho³ka.
      */
  Vector3f const &GetSecondVtx() const;


     /*!
      * Pozwala stwierdziæ czy po lewej stronie krawêdzi jest ¶cianka.
      * \retval true - gdy po lewej stronie krawêdzi jest ¶cianka.
      * \retval false - w przypadku przeciwnym.
      */
  bool IsLeftFace() const { return GetLeftFaceIdx() != ET_NULLFACE; }


     /*!
      * Pozwala stwierdziæ czy po prawej stronie krawêdzi jest ¶cianka.
      * \retval true - gdy po prawej stronie krawêdzi jest ¶cianka.
      * \retval false - w przypadku przeciwnym.
      */
  bool IsRightFace() const { return GetRightFaceIdx() != ET_NULLFACE; }


   /*! 
    * Metoda umo¿liwia okre¶lenie czy krawêd¼ jest widoczna
    * z danego kierunku patrzenia. Metoda przeznaczona jest tylko
    * do rysowania miniaturek figur wzorcowych. Nie ma zastosowania
    * w przypadku rysowania w uk³adzie wspó³rzêdnych globalnych.
    * \param ViewVct - wektor kierunku patrzenia. Wektor skierowany
    *                  jest od oka w kierunku przedmiotu.
    * \retval true - je¶li krawêd¼ jest widoczna,
    * \retval false - w przypadku przeciwnym.
    */
  bool IsVisible(const Vector3f &ViewVct) const;
};

/*!
 *  Wy¶wietla informacje dotycz±ce danej krawêdzi (wspó³rzêdne pierwszego
 *  i drugiego wierzcho³ka, ich kolejno¶æ nie ma zwi±zku z orientacj±
 *  ¿adnej ze ¶cianek, do których nale¿y ta krawêd¼).
 */
std::ostream &operator  << (std::ostream &ostrm, ViEdge const &Edge);


#endif
