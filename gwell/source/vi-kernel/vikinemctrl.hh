#ifndef VIKINEMCTRL_HH
#define VIKINEMCTRL_HH

/*!
 * \file vikinemctrl.hh
 * Plik zawiera definicjê klasy ViKinemCtrlItem i ViKinemCtrlSet.
 * Obiekty tych klas wykorzystywane s± do definiowania interfejsu 
 * do zadawnia
 * wybranych wspó³rzêdnych wewnêtrznych elementów danej bry³y z³o¿onej.
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
   * Pozwala okre¶liæ tyb jednoskti metrycznej. Obecnie zdefiniowane
   * s± typy dla nastêpuj±cych jednostek:
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
   *  Okre¶la typ realizowanej transformacji.
   */
  typedef enum { TT_Rot_Euler, TT_Rot_XYZ, TT_Trans, TT_Scale } 
               TransformType;
  /*!
   *  Okre¶la numer wspó³rzêdnej w wektorze 3D.
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
 *  \brief  Klasa okre¶la rodzaj zmienianego parametru transformacji.
 *
 *  Klasa ta pozwala na okre¶lenie rodzaju zmienianego parametru
 *  transformacji wspó³rzêdnych lokalnych danej bry³y do uk³adu
 *  wspó³rzêdnych jej rodzica. Okre¶lenia "potomek" i "rodzic" s±
 *  rozumiane tutaj w sensie drzewiastej struktury
 *  modelu bry³y z³o¿onej.
 */
class ViKinemCtrlItem:
          public ListItem<ViKinemCtrlItem>,
	  public ListItem<ViKinemCtrlItem,ID_KINEMCTRL_NTREENODE>,
          public BindAnonPair<0> {
  friend class ViKinemCtrlSet;
  /*!
   *  Okre¶la jaka jest kolejno¶æ translacji wzglêdem rotacji,
   *  tzn. czy translacja ma byæ realizowana po rotacji, czy te¿ przed.
   */
   TransOrder   _Trans_Order;

  /*!
   *  Okre¶la jednostki, w których podawana jest dana wielko¶æ.
   *  Obecnie ma to jedynie zastosowanie do k±tów.
   */
   Vi::MetricUnit   _Unit;

  /*!
   *  \brief Typ transformacji
   *
   *  Okre¶la typ realizowanej transformacji.
   */
  Vi::TransformType  _Transf_Type;

  /*!
   *  Okre¶la numer wspó³rzêdnej, która poddawana jest modyfkiacji.
   */
  Vi::Coord3DType    _Coord_Type;

  /*!
   * \if brief_private_field
   *  \brief Referencja do macierzy transformacji
   * \endif
   *
   *  Jest referencj± do macierzy transformacji, której wybrany 
   *  parametr (okre¶lony jest on przez pole
   *  \link ViKinemCtrlItem::_Transf_Type _Transf_Type\endlink) ma 
   *  podlegaæ zmianom.
   */
   ViMatrix3f    &_Mtx;

  /*!
   * \if brief_private_field
   *  \brief Nazwa parametru w dialogu
   * \endif
   *
   *  Nazwa przyporz±dkowana danemu parametrowi. Nazwa ta
   *  przewidziana jest do wyswietlenia w okienku dialogowym
   *  umo¿liwiaj±cym zmianê wybranego zbioru parametrów
   *  transformacji. Parametry te mog±, np. bezpo¶rednio
   *  odpowiadaæ wspó³rzêdnym wewnêtrznym robota.
   *
   *  Pole to umo¿liwia identyfikacjê obiektu w zbiorze
   *  obiektów, które tworz± listê wskazañ na parametry,
   *  dla których przewidziana jest mo¿liwo¶æ zmian
   *  za pomoc±, np. wspólnego interfejsu graficznego.
   */
   ExtString     _CommentName;

  /*!
   *  Nazwa po której mo¿e byæ szukany dany pozycja interfejsu.
   *  Pe³ni analogiczn± relê jak pole
   *  \link ViKinemCtrlItem::_KeyID _KeyID\endlink
   */
   ExtString     _KeyName;
  /*!
   * \brief Pole ma znaczenie pomocnicze i s³u¿y do indentyfikacji.
   *
   *  Pole to umo¿liwia identyfikacjê obiektu w zbiorze
   *  obiektów, które tworz± listê wskazañ na parametry,
   *  dla których przewidziana jest mo¿liwo¶æ zmian
   *  za pomoc±, np. wspólnego interfejsu graficznego.\n
   *  Wykorzystanie tego pola nie jest obligatoryjne, gdy¿
   *  operacja wyszukiwania mo¿na równie¿ realizowaæ
   *  na podstawie zawarto¶ci pola
   *  \link ViKinemCtrlItem::_CommentName _CommentName\endlink.
   */
   int _KeyID;
  /*!
   *  Bie¿±ca warto¶æ zmienianego parametru.
   */
   float         _Val;
  /*!
   *  Zawiera dopuszczaln± warto¶æ maksymaln± danego parametru, który
   *  ma podlegaæ zmianom.
   *  Je¿eli warto¶æ jest niegoraniczona to pole zawiera
   *  liczbê \e -numeric_limits<float>::max()
   */
   float         _Min;
  /*!
   *  Zawiera dopuszczaln± warto¶æ minimaln± danego parametru, który
   *  ma podlegaæ zmianom.
   *  Je¿eli warto¶æ jest niegoraniczona to pole zawiera
   *  liczbê \e numeric_limits<float>::max()
   */
   float         _Max;

  /*!
   *  Aktualizuje wspó³czynniki macierzy dla zmian k±tów Eulera.
   */
    void UpdateMtx_Rot_Euler();
    void UpdateMtx_Rot_XYZ();
    void UpdateMtx_Trans();
    void UpdateMtx_Scale();
   /*!
    *  Metoda ma charakter pomocniczy. Udostêpnia ona nastêpny element
    *  listy interfejsu sterownia.
    *  Wska¼nik zwracany jest w trybie modyfikacji.
    */
    ViKinemCtrlItem *NextCtrlItem() 
             { return ListItem<ViKinemCtrlItem>::Next(); }
   /*!
    *  Metoda ma charakter pomocniczy. Udostêpnia ona nastêpny element
    *  listy interfejsu sterownia.
    *  Wska¼nik zwracany jest w trybie sta³ym.
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
   *  Udostêpnia referencjê do macierzy, z któr± skojarzony jest dana
   *  pozycja interfejsu sterowania.
   */
   const ViMatrix3f &GetMtx() const { return _Mtx; }

   void MoveCtrlItemBehind();
   void MoveCtrlItemAhead();


   void UpdateMtx();
  /*!
   * \if brief_public_methods
   * \brief Umo¿liwia ustawienie warto¶ci maksymalnej zmienianego parametru.
   * \endif
   *
   * Umo¿liwia ustawienie warto¶ci maksymalnej zmienianego parametru.
   * \post Do pola \link ViKinemCtrlItem::_Max _Max\endlink
   * wpisana zostaje warto¶æ parametru \e Val.
   */
   void SetMax(float Val) { _Max = Val; }

   int SetVal(float Val);
  /*!
   *  Inicjalizuje warto¶æ pola 
   * \link ViKinemCtrlItem::_Val _Val\endlink bez aktualizowania
   *  parametrów macierzy.
   */
   void InitVal(float Val) { _Val = Val; }
  /*!
   *  Udostêpnia aktualn± warto¶æ parametru wpisan± wcze¶iej przez 
   *  metodê \link ViKinemCtrlItem::SetVal SetVal\endlink.
   */
   float GetVal() const { return _Val; }

  /*!
   *  Usuwa górne ograniczenie.
   */
   void SetMax_Unlimited() { _Max = numeric_limits<float>::max(); }

  /*!
   *  Sprawdza czy istnieje górne ograniczenia na zmienian± warto¶æ.
   */
   bool IsMaxUnlimited() const 
                   { return _Max == numeric_limits<float>::max(); }



  /*!
   * \if brief_public_methods
   * \brief Umo¿liwia ustawienie warto¶ci minimalnej zmienianego parametru.
   * \endif
   *
   * Umo¿liwia ustawienie warto¶ci minimalnej zmienianego parametru.
   * \post Do pola \link ViKinemCtrlItem::_Min _Min\endlink
   * wpisana zostaje warto¶æ parametru \e Val.
   */
   void SetMin(float Val) { _Min = Val; }

  /*!
   *  Usuwa dolne ograniczenie.
   */
   void SetMin_Unlimited() { _Min = -numeric_limits<float>::max(); }

  /*!
   *  Sprawdza czy istnieje dolne ograniczenia na zmienian± warto¶æ.
   */
   bool IsMinUnlimited() const 
                   { return _Min == -numeric_limits<float>::max(); }

  /*!
   *  Sprawdza czy s± oba ograniczenia na zadawan± warto¶æ.
   *  \retval true - je¶li ustawione s± oba ograniczenia na zadawan± warto¶æ.
   *  \retval false - gdy przynajmniej brakuje jednego z ograniczeñ
   */
   bool IsUnlimited() const { return IsMinUnlimited() || IsMaxUnlimited(); }

  /*!
   * \if brief_public_methods
   * \brief  Udostêpnia warto¶æ maksymaln± zmienianego parametru.
   * \endif
   *
   * Udostêpnia warto¶æ maksymaln± zmienianego parametru
   *  (zawarto¶æ pola \link ViKinemCtrlItem::_Max _Max\endlink).
   */
   float GetMax() const { return _Max; }


  /*!
   * \if brief_public_methods
   * \brief  Udostêpnia warto¶æ maksymaln± zmienianego parametru.
   * \endif
   *
   * Udostêpnia warto¶æ maksymaln± zmienianego parametru
   *  (zawarto¶æ pola \link ViKinemCtrlItem::_Max _Max\endlink).
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
   * \brief Udostêpnia identyfikator obiektu.
   * \endif
   *
   * Udostêpnia zawarto¶æ pola 
   * \link ViKinemCtrlItem::_KeyID _KeyID\endlink.
   * traktowanego jako klucz identyfikuj±cy dan± pozycjê
   * w li¶cie (patrz ViKinemCtrlSet)
   * tworz±cej interfejs do zmianianych parametrów
   * obiektu.
   */
   int GetKeyID() const { return _KeyID; }

  /*!
   * Wi±¿e tekst z dan± wspó³rzêdn±, który ma byæ 
   * wykorzystany w tworzonym dialogu.
   * \param Name - nadawana nazwa dla danej wspó³rzêdnej.
   */
   void SetCommentName(const char *Name) { _CommentName = Name; }

  /*!
   * Udostêpnia tekst zwi±zany z dan± wspó³rzêdn±, który ma byæ 
   * wykorzystany w tworzonym dialogu.
   */
   const ExtString& GetCommentName() const { return _CommentName; }


  /*!
   * Nadaje nazwê dla danej wspó³rzêdnej, wed³ug której mo¿e byæ
   * wyszukiwany dany element w kolejce interfejsu.
   * \param Name - nadawana nazwa dla danej wspó³rzêdnej.
   * \warning Znaki bia³e z przodu i z ty³u napisu s± zawsze usuwane.
   */
   void SetKeyName(const char *Name) 
            { _KeyName = Name;  _KeyName.RemoveSpace(); }

  /*!
   * Udostêpnia nazwê dla danej wspó³rzêdnej, wed³ug której mo¿e byæ
   * wyszukiwany dany element w kolejce interfejsu.
   */
   const ExtString& GetKeyName() const { return _KeyName; }


  /*!
   * Udostêpnia informacjê, która ze wspó³rzêdnych
   * danego wektora parametrów ma podlegaæ zmianie.
   * Wektory parametrów, których wspó³rzêdne mog± podlegaæ zmianie,
   * to rotacja, translacja i skala.
   */
  Vi::Coord3DType  GetCoordType() const { return  _Coord_Type; }

  /*!
   * Ustala wspó³rzêdna
   * danego wektora parametrów ma podlegaæ zmianie.
   * Wektory parametrów, których wspó³rzêdne mog± podlegaæ zmianie,
   * to rotacja, translacja i skala.
   * \param Coord - okre¶la, która ze wspó³rzêdnych wektora ma
   *                podlegaæ zmianie.
   */
  void SetCoordType(Vi::Coord3DType Coord) { _Coord_Type = Coord; }


  /*!
   * Udstêpnia informacjê o porz±dku translacji wzglêdem rotacji.
   */
  TransOrder  GetTransOrder() const { return _Trans_Order; }


  /*!
   * Zadaje porz±dek translacji wzglêdem rotacji.
   * \param Order - okre¶la zadawany porz±dek translacji wzglêdem rotacji.
   */
  void SetTransOrder(TransOrder  Order) { _Trans_Order = Order; }


  /*!
   *  \if brief_public_methods
   *  \brief Udostêpnia typ transformacji
   *  \endif
   *
   *   Udostêpnia typ transformacji.
   */
  Vi::TransformType  GetTransfType() const { return _Transf_Type;}


  /*!
   *  \if brief_public_methods
   *  \brief Zmienia typ transformacji
   *  \endif
   *
   *   Zadaje nowy typ transformacji.
   *   \param TransfType - warto¶æ parametru okre¶la typ 
   *                       tranformacji, której parametr bêdzie podlega³
   *                       zmianom.
   */
  void SetTransfType(Vi::TransformType TransfType)
                              {_Transf_Type = TransfType;}

  /*!
   * Udostêpnia typ jednostki miary zmienianej wielko¶ci.
   */
  Vi::MetricUnit  GetUnit() const { return  _Unit; }


  /*!
   * Zadaje nowy typ jednostki miary zmienianej wielko¶ci.
   */
  void SetUnit(Vi::MetricUnit Unit) { _Unit = Unit; }


  /*!
   * Nadaje now± warto¶æ polu 
   * \link ViKinemCtrlItem::_KeyID _KeyID\endlink.
   */
   void SetKeyID(int Key) { _KeyID = Key; }    

   bool WriteTo(  ostream      &ostrm,
                  unsigned int  Margin
               ) const;
};



/*!
 *  Przesuwa dany element listy za element poprzedzaj±cy go,
 *  tzn. w kierunku pocz±tku listy.
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
 *  Przesuwa dany element listy przed element nastêpny,
 *  tzn. w kierunku koñca listy.
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
 *  \brief Klasa pozwala zdefiniowaæ zbiór zmienianych parametrów
 *         definiuj±cych wzajemne po³o¿enie bry³ elementarnych
 *         danej bry³y z³o¿onej.
 *
 *  Klasa ta pozwala na zdefiniowanie zbioru bry³ danej bry³y z³o¿onej
 *  oraz skojarzonych z nimi zmienianych wspó³rzêdnych.
 *  Wspó³rzêdne te odnosz± siê lokalizacji danych bry³
 *  wzglêdem ich rodziców w drzewiastej strukturze
 *  modelu bry³y z³o¿onej.
 */
class ViKinemCtrlSet: public List<ViKinemCtrlItem> {
 public:

   /*!
    *  Definiuje skrócon± nazwê do typu iteratora listy elementów 
    *  interfejsu sterowania.
    *  Iterator ten udostêpnia iterowane obiekty w trybie \b sta³ym.
    */
   typedef List<ViKinemCtrlItem>::ConstIterator ConCtrlIter;
   /*!
    *  Definiuje skrócon± nazwê do typu iteratora listy elementów 
    *  interfejsu sterowania.
    *  Iterator ten udostêpnia iterowane obiekty w trybie \b modyfikacji.
    */
   typedef List<ViKinemCtrlItem>::VariaIterator VarCtrlIter;

   /*!
    * Tworzy iterator do przegl±dania elementów interfejsu sterowania.
    * Iterowane obiekty udostêpniane s± w trybie \e sta³ym.
    */
   ConCtrlIter ConBegin_Ctrl() const 
                           { return  List<ViKinemCtrlItem>::Begin(); }

   /*!
    * Tworzy iterator do przegl±dania elementów interfejsu sterowania.
    * Iterowane obiekty udostêpniane s± w trybie \e modyfikacji.
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
