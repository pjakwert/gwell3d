#ifndef VIKINEMCTRL_HH
#define VIKINEMCTRL_HH

/*!
 * \file vikinemctrl.hh
 * Plik zawiera definicj� klasy ViKinemCtrlItem i ViKinemCtrlSet.
 * Obiekty tych klas wykorzystywane s� do definiowania interfejsu 
 * do zadawnia
 * wybranych wsp�rz�dnych wewn�trznych element�w danej bry�y z�o�onej.
 * \author Bogdan Kreczmer
 * \date   2004.08
 */

#ifndef __GNUG__
#pragma interface
#endif

#include <iostream>
#include "listque.hh"
#include "vimatrix3f.hh"
#include "extstring.hh"
#include "vi-listid.hh"
#include "viexception.hh"
#include "bindanonpair.hh"

class ViNTreeNode;
class ViElemePolyh;
class ViMultiPolyh;

namespace Vi {
  /*!
   * Pozwala okre�li� tyb jednoskti metrycznej. Obecnie zdefiniowane
   * s� typy dla nast�puj�cych jednostek:
   * \li MU_NONE - jednostka niemianowana,
   * \li MU_Deg  - stopnie,
   * \li MU_Rad  - radiany,
   * \li MU_Mil  - milimetry
   * \li MU_Cen  - centymetry,
   * \li MU_Met  - netry.
   */
  typedef enum { MU_NONE, MU_Deg, MU_Rad, MU_Cen, MU_Met, MU_Mil } 
               MetricUnit;

  /*!
   *  Okre�la typ realizowanej transformacji.
   */
  typedef enum { TT_Rot_Euler, TT_Rot_XYZ, TT_Trans, TT_Scale } 
               TransformType;
  /*!
   *  Okre�la numer wsp�rz�dnej w wektorze 3D.
   */
  typedef enum { CT_1=0, CT_2=1, CT_3=2 } Coord3DType;

  const char *MakeString(MetricUnit);
  TransformType String2TransformType(const char *Name)
           throw(ViException);
  MetricUnit String2MetricUnit(const char *Name) throw(ViException);
  Coord3DType String2Coord3DType(const char *Name) throw(ViException);
  const char *MakeString(TransformType);
  const char *MakeString(Coord3DType);
};


class ViKinemCtrlSet;

/*!
 *  \brief  Klasa okre�la rodzaj zmienianego parametru transformacji.
 *
 *  Klasa ta pozwala na okre�lenie rodzaju zmienianego parametru
 *  transformacji wsp�rz�dnych lokalnych danej bry�y do uk�adu
 *  wsp�rz�dnych jej rodzica. Okre�lenia "potomek" i "rodzic" s�
 *  rozumiane tutaj w sensie drzewiastej struktury
 *  modelu bry�y z�o�onej.
 */
class ViKinemCtrlItem:
          public ListItem<ViKinemCtrlItem>,
	  public ListItem<ViKinemCtrlItem,ID_KINEMCTRL_NTREENODE>,
          public BindAnonPair<0> {
  friend class ViKinemCtrlSet;
  /*!
   *  Okre�la jaka jest kolejno�� translacji wzgl�dem rotacji,
   *  tzn. czy translacja ma by� realizowana po rotacji, czy te� przed.
   */
   TransOrder   _Trans_Order;

  /*!
   *  Okre�la jednostki, w kt�rych podawana jest dana wielko��.
   *  Obecnie ma to jedynie zastosowanie do k�t�w.
   */
   Vi::MetricUnit   _Unit;

  /*!
   *  \brief Typ transformacji
   *
   *  Okre�la typ realizowanej transformacji.
   */
  Vi::TransformType  _Transf_Type;

  /*!
   *  Okre�la numer wsp�rz�dnej, kt�ra poddawana jest modyfkiacji.
   */
  Vi::Coord3DType    _Coord_Type;

  /*!
   * \if brief_private_field
   *  \brief Referencja do macierzy transformacji
   * \endif
   *
   *  Jest referencj� do macierzy transformacji, kt�rej wybrany 
   *  parametr (okre�lony jest on przez pole
   *  \link ViKinemCtrlItem::_Transf_Type _Transf_Type\endlink) ma 
   *  podlega� zmianom.
   */
   ViMatrix3f    &_Mtx;

  /*!
   * \if brief_private_field
   *  \brief Nazwa parametru w dialogu
   * \endif
   *
   *  Nazwa przyporz�dkowana danemu parametrowi. Nazwa ta
   *  przewidziana jest do wyswietlenia w okienku dialogowym
   *  umo�liwiaj�cym zmian� wybranego zbioru parametr�w
   *  transformacji. Parametry te mog�, np. bezpo�rednio
   *  odpowiada� wsp�rz�dnym wewn�trznym robota.
   *
   *  Pole to umo�liwia identyfikacj� obiektu w zbiorze
   *  obiekt�w, kt�re tworz� list� wskaza� na parametry,
   *  dla kt�rych przewidziana jest mo�liwo�� zmian
   *  za pomoc�, np. wsp�lnego interfejsu graficznego.
   */
   ExtString     _CommentName;

  /*!
   *  Nazwa po kt�rej mo�e by� szukany dany pozycja interfejsu.
   *  Pe�ni analogiczn� rel� jak pole
   *  \link ViKinemCtrlItem::_KeyID _KeyID\endlink
   */
   ExtString     _KeyName;
  /*!
   * \brief Pole ma znaczenie pomocnicze i s�u�y do indentyfikacji.
   *
   *  Pole to umo�liwia identyfikacj� obiektu w zbiorze
   *  obiekt�w, kt�re tworz� list� wskaza� na parametry,
   *  dla kt�rych przewidziana jest mo�liwo�� zmian
   *  za pomoc�, np. wsp�lnego interfejsu graficznego.\n
   *  Wykorzystanie tego pola nie jest obligatoryjne, gdy�
   *  operacja wyszukiwania mo�na r�wnie� realizowa�
   *  na podstawie zawarto�ci pola
   *  \link ViKinemCtrlItem::_CommentName _CommentName\endlink.
   */
   int _KeyID;
  /*!
   *  Bie��ca warto�� zmienianego parametru.
   */
   float         _Val;
  /*!
   *  Zawiera dopuszczaln� warto�� maksymaln� danego parametru, kt�ry
   *  ma podlega� zmianom.
   *  Je�eli warto�� jest niegoraniczona to pole zawiera
   *  liczb� \e -numeric_limits<float>::max()
   */
   float         _Min;
  /*!
   *  Zawiera dopuszczaln� warto�� minimaln� danego parametru, kt�ry
   *  ma podlega� zmianom.
   *  Je�eli warto�� jest niegoraniczona to pole zawiera
   *  liczb� \e numeric_limits<float>::max()
   */
   float         _Max;

  /*!
   *  Aktualizuje wsp�czynniki macierzy dla zmian k�t�w Eulera.
   */
    void UpdateMtx_Rot_Euler();
    void UpdateMtx_Rot_XYZ();
    void UpdateMtx_Trans();
    void UpdateMtx_Scale();
   /*!
    *  Metoda ma charakter pomocniczy. Udost�pnia ona nast�pny element
    *  listy interfejsu sterownia.
    *  Wska�nik zwracany jest w trybie modyfikacji.
    */
    ViKinemCtrlItem *NextCtrlItem() 
             { return ListItem<ViKinemCtrlItem>::Next(); }
   /*!
    *  Metoda ma charakter pomocniczy. Udost�pnia ona nast�pny element
    *  listy interfejsu sterownia.
    *  Wska�nik zwracany jest w trybie sta�ym.
    */
    const ViKinemCtrlItem *NextCtrlItem() const 
             { return ListItem<ViKinemCtrlItem>::Next(); }
  public:

   const ViNTreeNode *GetPolyh() const;
   ViNTreeNode *UsePolyh();    

   const ViElemePolyh *GetElemePolyh() const;
   ViElemePolyh *UseElemePolyh();    

   const ViMultiPolyh *GetRootMultiPolyh() const;
   ViMultiPolyh *UseRootMultiPolyh();    

   bool ComputeAllPolyhGlbVtx();

  /*!
   *  Udost�pnia referencj� do macierzy, z kt�r� skojarzony jest dana
   *  pozycja interfejsu sterowania.
   */
   const ViMatrix3f &GetMtx() const { return _Mtx; }

   void MoveCtrlItemBehind();
   void MoveCtrlItemAhead();


   void UpdateMtx();
  /*!
   * \if brief_public_methods
   * \brief Umo�liwia ustawienie warto�ci maksymalnej zmienianego parametru.
   * \endif
   *
   * Umo�liwia ustawienie warto�ci maksymalnej zmienianego parametru.
   * \post Do pola \link ViKinemCtrlItem::_Max _Max\endlink
   * wpisana zostaje warto�� parametru \e Val.
   */
   void SetMax(float Val) { _Max = Val; }

   int SetVal(float Val);
  /*!
   *  Inicjalizuje warto�� pola 
   * \link ViKinemCtrlItem::_Val _Val\endlink bez aktualizowania
   *  parametr�w macierzy.
   */
   void InitVal(float Val) { _Val = Val; }
  /*!
   *  Udost�pnia aktualn� warto�� parametru wpisan� wcze�iej przez 
   *  metod� \link ViKinemCtrlItem::SetVal SetVal\endlink.
   */
   float GetVal() const { return _Val; }

  /*!
   *  Usuwa g�rne ograniczenie.
   */
   void SetMax_Unlimited() { _Max = numeric_limits<float>::max(); }

  /*!
   *  Sprawdza czy istnieje g�rne ograniczenia na zmienian� warto��.
   */
   bool IsMaxUnlimited() const 
                   { return _Max == numeric_limits<float>::max(); }



  /*!
   * \if brief_public_methods
   * \brief Umo�liwia ustawienie warto�ci minimalnej zmienianego parametru.
   * \endif
   *
   * Umo�liwia ustawienie warto�ci minimalnej zmienianego parametru.
   * \post Do pola \link ViKinemCtrlItem::_Min _Min\endlink
   * wpisana zostaje warto�� parametru \e Val.
   */
   void SetMin(float Val) { _Min = Val; }

  /*!
   *  Usuwa dolne ograniczenie.
   */
   void SetMin_Unlimited() { _Min = -numeric_limits<float>::max(); }

  /*!
   *  Sprawdza czy istnieje dolne ograniczenia na zmienian� warto��.
   */
   bool IsMinUnlimited() const 
                   { return _Min == -numeric_limits<float>::max(); }

  /*!
   *  Sprawdza czy s� oba ograniczenia na zadawan� warto��.
   *  \retval true - je�li ustawione s� oba ograniczenia na zadawan� warto��.
   *  \retval false - gdy przynajmniej brakuje jednego z ogranicze�
   */
   bool IsUnlimited() const { return IsMinUnlimited() || IsMaxUnlimited(); }

  /*!
   * \if brief_public_methods
   * \brief  Udost�pnia warto�� maksymaln� zmienianego parametru.
   * \endif
   *
   * Udost�pnia warto�� maksymaln� zmienianego parametru
   *  (zawarto�� pola \link ViKinemCtrlItem::_Max _Max\endlink).
   */
   float GetMax() const { return _Max; }


  /*!
   * \if brief_public_methods
   * \brief  Udost�pnia warto�� maksymaln� zmienianego parametru.
   * \endif
   *
   * Udost�pnia warto�� maksymaln� zmienianego parametru
   *  (zawarto�� pola \link ViKinemCtrlItem::_Max _Max\endlink).
   */
   float GetMin() const { return _Min; }


  ViKinemCtrlItem( ViMatrix3f   &Mtx, 
                   int           KeyID, 
                   const char   *KeyName = "nokeyname"
                 );

  ViKinemCtrlItem( ViMatrix3f   &Mtx, 
                   const char  *KeyName,
                   int          KeyID = -1
                 );

  ViKinemCtrlItem( ViNTreeNode    *pPolyh,
                   ViMatrix3f          &Mtx,
                   Vi::TransformType   TransfType,
                   Vi::Coord3DType     Coord,
                   TransOrder          TOrder = TO_Before,
                   Vi::MetricUnit      Unit = Vi::MU_NONE
                 );
  ~ViKinemCtrlItem();

  /*!
   * \if brief_public_methods
   * \brief Udost�pnia identyfikator obiektu.
   * \endif
   *
   * Udost�pnia zawarto�� pola 
   * \link ViKinemCtrlItem::_KeyID _KeyID\endlink.
   * traktowanego jako klucz identyfikuj�cy dan� pozycj�
   * w li�cie (patrz ViKinemCtrlSet)
   * tworz�cej interfejs do zmianianych parametr�w
   * obiektu.
   */
   int GetKeyID() const { return _KeyID; }

  /*!
   * Wi��e tekst z dan� wsp�rz�dn�, kt�ry ma by� 
   * wykorzystany w tworzonym dialogu.
   * \param Name - nadawana nazwa dla danej wsp�rz�dnej.
   */
   void SetCommentName(const char *Name) { _CommentName = Name; }

  /*!
   * Udost�pnia tekst zwi�zany z dan� wsp�rz�dn�, kt�ry ma by� 
   * wykorzystany w tworzonym dialogu.
   */
   const ExtString& GetCommentName() const { return _CommentName; }


  /*!
   * Nadaje nazw� dla danej wsp�rz�dnej, wed�ug kt�rej mo�e by�
   * wyszukiwany dany element w kolejce interfejsu.
   * \param Name - nadawana nazwa dla danej wsp�rz�dnej.
   * \warning Znaki bia�e z przodu i z ty�u napisu s� zawsze usuwane.
   */
   void SetKeyName(const char *Name) 
            { _KeyName = Name;  _KeyName.RemoveSpace(); }

  /*!
   * Udost�pnia nazw� dla danej wsp�rz�dnej, wed�ug kt�rej mo�e by�
   * wyszukiwany dany element w kolejce interfejsu.
   */
   const ExtString& GetKeyName() const { return _KeyName; }


  /*!
   * Udost�pnia informacj�, kt�ra ze wsp�rz�dnych
   * danego wektora parametr�w ma podlega� zmianie.
   * Wektory parametr�w, kt�rych wsp�rz�dne mog� podlega� zmianie,
   * to rotacja, translacja i skala.
   */
  Vi::Coord3DType  GetCoordType() const { return  _Coord_Type; }

  /*!
   * Ustala wsp�rz�dna
   * danego wektora parametr�w ma podlega� zmianie.
   * Wektory parametr�w, kt�rych wsp�rz�dne mog� podlega� zmianie,
   * to rotacja, translacja i skala.
   * \param Coord - okre�la, kt�ra ze wsp�rz�dnych wektora ma
   *                podlega� zmianie.
   */
  void SetCoordType(Vi::Coord3DType Coord) { _Coord_Type = Coord; }


  /*!
   * Udst�pnia informacj� o porz�dku translacji wzgl�dem rotacji.
   */
  TransOrder  GetTransOrder() const { return _Trans_Order; }


  /*!
   * Zadaje porz�dek translacji wzgl�dem rotacji.
   * \param Order - okre�la zadawany porz�dek translacji wzgl�dem rotacji.
   */
  void SetTransOrder(TransOrder  Order) { _Trans_Order = Order; }


  /*!
   *  \if brief_public_methods
   *  \brief Udost�pnia typ transformacji
   *  \endif
   *
   *   Udost�pnia typ transformacji.
   */
  Vi::TransformType  GetTransfType() const { return _Transf_Type;}


  /*!
   *  \if brief_public_methods
   *  \brief Zmienia typ transformacji
   *  \endif
   *
   *   Zadaje nowy typ transformacji.
   *   \param TransfType - warto�� parametru okre�la typ 
   *                       tranformacji, kt�rej parametr b�dzie podlega�
   *                       zmianom.
   */
  void SetTransfType(Vi::TransformType TransfType)
                              {_Transf_Type = TransfType;}

  /*!
   * Udost�pnia typ jednostki miary zmienianej wielko�ci.
   */
  Vi::MetricUnit  GetUnit() const { return  _Unit; }


  /*!
   * Zadaje nowy typ jednostki miary zmienianej wielko�ci.
   */
  void SetUnit(Vi::MetricUnit Unit) { _Unit = Unit; }


  /*!
   * Nadaje now� warto�� polu 
   * \link ViKinemCtrlItem::_KeyID _KeyID\endlink.
   */
   void SetKeyID(int Key) { _KeyID = Key; }    

   bool WriteTo(  ostream      &ostrm,
                  unsigned int  Margin
               ) const;
};



/*!
 *  Przesuwa dany element listy za element poprzedzaj�cy go,
 *  tzn. w kierunku pocz�tku listy.
 *
 *  Schemat realizacji operacji:
 * \image html list-movebehind1.gif "Sytuacja przed wykonaniem metody \b MoveCtrlItemBehind" width=5cm
 * \image html list-movebehind2.gif "Sytuacja po wykonaniu metody \b MoveCtrlItemBehind" width=5cm
 * \image latex list-movebehind1.eps "Sytuacja przed wykonaniem metody \b MoveCtrlItemBehind" width=5cm
 * \image latex list-movebehind2.eps "Sytuacja po wykonaniu metody \b MoveCtrlItemBehind" width=5cm
 */
inline
void ViKinemCtrlItem::MoveCtrlItemBehind() 
{ 
  ListItem<ViKinemCtrlItem>::MoveBehind(); 
}



/*!
 *  Przesuwa dany element listy przed element nast�pny,
 *  tzn. w kierunku ko�ca listy.
 *
 *  Schemat realizacji operacji:
 * \image html list-moveahead1.gif "Sytuacja przed wykonaniem metody \b MoveCtrlItemAhead" width=5cm
 * \image html list-moveahead2.gif "Sytuacja po wykonaniu metody \b MoveCtrlItemAhead" width=5cm
 * \image latex list-moveahead1.eps "Sytuacja przed wykonaniem metody \b MoveCtrlItemAhead" width=5cm
 * \image latex list-moveahead2.eps "Sytuacja po wykonaniu metody \b MoveCtrlItemAhead" width=5cm
 */
inline
void ViKinemCtrlItem::MoveCtrlItemAhead() 
{ 
  ListItem<ViKinemCtrlItem>::MoveAhead(); 
}






/*!
 *  \brief Klasa pozwala zdefiniowa� zbi�r zmienianych parametr�w
 *         definiuj�cych wzajemne po�o�enie bry� elementarnych
 *         danej bry�y z�o�onej.
 *
 *  Klasa ta pozwala na zdefiniowanie zbioru bry� danej bry�y z�o�onej
 *  oraz skojarzonych z nimi zmienianych wsp�rz�dnych.
 *  Wsp�rz�dne te odnosz� si� lokalizacji danych bry�
 *  wzgl�dem ich rodzic�w w drzewiastej strukturze
 *  modelu bry�y z�o�onej.
 */
class ViKinemCtrlSet: public List<ViKinemCtrlItem> {
 public:

   /*!
    *  Definiuje skr�con� nazw� do typu iteratora listy element�w 
    *  interfejsu sterowania.
    *  Iterator ten udost�pnia iterowane obiekty w trybie \b sta�ym.
    */
   typedef List<ViKinemCtrlItem>::ConstIterator ConCtrlIter;
   /*!
    *  Definiuje skr�con� nazw� do typu iteratora listy element�w 
    *  interfejsu sterowania.
    *  Iterator ten udost�pnia iterowane obiekty w trybie \b modyfikacji.
    */
   typedef List<ViKinemCtrlItem>::VariaIterator VarCtrlIter;

   /*!
    * Tworzy iterator do przegl�dania element�w interfejsu sterowania.
    * Iterowane obiekty udost�pniane s� w trybie \e sta�ym.
    */
   ConCtrlIter ConBegin_Ctrl() const 
                           { return  List<ViKinemCtrlItem>::Begin(); }

   /*!
    * Tworzy iterator do przegl�dania element�w interfejsu sterowania.
    * Iterowane obiekty udost�pniane s� w trybie \e modyfikacji.
    */
   VarCtrlIter VarBegin_Ctrl() 
                           { return  List<ViKinemCtrlItem>::Begin(); }



  ViKinemCtrlItem *Add( ViMatrix3f   &Mtx, 
                        int          KeyID, 
                        const char  *KeyName = "nokeyname"
                      );
  ViKinemCtrlItem *Add( ViMatrix3f   &Mtx, 
                        const char  *KeyName,
                        int          KeyID = -1
                      );
  ViKinemCtrlItem *Add(  ViNTreeNode   *pPolyh,
                         ViMatrix3f          &Mtx,
                         Vi::TransformType   TransfType = Vi::TT_Rot_XYZ,
                         Vi::Coord3DType     Coord = Vi::CT_1,
                         TransOrder          TOrder = TO_After,
                         Vi::MetricUnit      Unit = Vi::MU_Deg
                      );
  bool DeleteByKeyID(int Key);
  bool DeleteByKeyName(const char *KeyName);
  bool DeleteByCommentName(const char *CommentName);

  const ViKinemCtrlItem *FindByKeyID(int Key) const;
  ViKinemCtrlItem *FindByKeyID(int Key);
  const ViKinemCtrlItem *FindByKeyName(const char *KeyName) const;
  ViKinemCtrlItem *FindByKeyName(const char *KeyName);
  const ViKinemCtrlItem *FindByCommentName(const char *CommentName) const;
  ViKinemCtrlItem *FindByCommentName(const char *CommentName);

  int GetMaxKeyID() const;
  int GetMinKeyID() const;

  bool WriteTo(  ostream      &ostrm,
                 unsigned int  Margin
              ) const;
};


std::ostream &operator << (std::ostream &, const ViKinemCtrlItem &);


#endif
