#ifndef __GNUG__
#define pragma implementation
#endif

#include <limits>
#include "vikinemctrl.hh"
#include "vintreenode.hh"
#include "vielemepolyh.hh"
#include "vimultipolyh.hh"
#include "streamutils.hh"
#include "vi-keywords.hh"
#include "vinodeaddress.hh"



/*!
 *  Znajduje najmniejsz± warto¶æ indetyfikatora liczbowego
 *  spo¶ród wszystkich identyfikatorów elementów interfejsu sterownia.
 *  Je¶li lista jest pusta, to zwracana jest warto¶æ
 *  \e numeric_limits<int>::max().
 */
int ViKinemCtrlSet::GetMinKeyID() const
{
  int MinID = numeric_limits<int>::max();

  for (const ViKinemCtrlItem *pItem = First(); 
                              pItem; 
                              pItem = pItem->NextCtrlItem())
    if (pItem->GetKeyID() < MinID) MinID = pItem->GetKeyID();
  return MinID;
}



/*!
 *  Znajduje najwiêksz± warto¶æ indetyfikatora liczbowego
 *  spo¶ród wszystkich identyfikatorów elementów interfejsu sterownia.
 *  Je¶li lista jest pusta, to zwracana jest warto¶æ
 *  \e -numeric_limits<int>::max().
 */
int ViKinemCtrlSet::GetMaxKeyID() const
{
  int MaxID = -numeric_limits<int>::max();

  for (const ViKinemCtrlItem *pItem = First(); 
                              pItem; 
                              pItem = pItem->NextCtrlItem())
    if (pItem->GetKeyID() > MaxID) MaxID = pItem->GetKeyID();
  return MaxID;
}



/*!
 * Umo¿liwia wy¶wietlenie na wyj¶ciu standardowym ustawieñ danej pozycji
 * interfejsu sterownia.
 * \note Je¿eli nie jest zdefiniowana warto¶æ minimalna (lub maksymalna)
 *       danego parametru, to pozycja dotyczaca minimu (lub maksimum)
 *       nie jest wy¶wietlana.
 * \param strm - (\b in/\b out) strumieñ wyj¶ciowy,
 * \param CItem - element, którego zawarto¶æ zostanie ma byæ wy¶wietlona
 *                na wyj¶ciu standardowym.
 */
std::ostream &operator << (std::ostream &strm, const ViKinemCtrlItem &CItem)
{
  CItem.WriteTo(strm,1);  return strm;
}


namespace Vi {
  /*!
   *  Zwraca napis odpowiadaj±cy danej warto¶ci
   *  typu \link Vi::MetricUnit Vi::MetricUnit\endlink.
   */
  const char *MakeString(Vi::MetricUnit Val)
  { 
    switch (Val) {
      case MU_NONE: return KW__MU_NONE;
      case MU_Deg:  return KW__MU_DEG;
      case MU_Rad:  return KW__MU_RAD;
      case MU_Cen:  return KW__MU_CEN;
      case MU_Met:  return KW__MU_MET;
      case MU_Mil:  return KW__MU_MIL;
    }
  }

  /*!
   *  Zwraca napis odpowiadaj±cy danej warto¶ci
   *  typu \link Vi::TransformType Vi::TransformType\endlink.
   */
  const char *MakeString(Vi::TransformType Val)
  { 
    switch (Val) {
      case TT_Rot_Euler: return KW__TT_ROT_EULER;
      case TT_Rot_XYZ:   return KW__TT_ROT_XYZ;
      case TT_Trans:     return KW__TT_TRANS;
      case TT_Scale:     return KW__TT_SCALE;
    }
  }
  /*!
   *  Funkcja dokonuje konwersji nazwy warto¶ci typu 
   * \link Vi::TransformType TransformType\endlink na warto¶æ 
   * tego typu.\n
   * Zestaw dopuszczalnych nazw zdefiniowany jest poprzez sta³e:
   *  \li \link vi-kewords.hh::KW__TT_ROT_EULER KW__TT_ROT_EULER\endlink
   *  \li \link vi-kewords.hh::KW__TT_ROT_XYZ KW__TT_ROT_XYZ\endlink
   *  \li \link vi-kewords.hh::KW__TT_TRANS KW__TT_TRANS\endlink
   *  \li \link vi-kewords.hh::KW__TT_SCALE KW__TT_SCALE\endlink
   * \param Name - nazwa warto¶ci typu  
   *               \link Vi::TransformType TransformType\endlink
   * \exception ViException z kodem b³êdu \link
   *                 vierrors.hh::ERRNUM_TRANSFTYPE__IMPROPER_NAME
   *                 ERRNUM_TRANSFTYPE__IMPROPER_NAME\endlink
   *            w przypadku, gdy nazwa nie odpowiada ¿adnej z oczekiwanych
   *            nazw.
   */
  TransformType String2TransformType(const char *Name) throw(ViException)
  {
    if (!strcmp(Name,KW__TT_ROT_EULER)) return TT_Rot_Euler;
    else if (!strcmp(Name,KW__TT_ROT_XYZ)) return TT_Rot_XYZ;
    else if (!strcmp(Name,KW__TT_TRANS)) return TT_Trans;
    else if (!strcmp(Name,KW__TT_SCALE)) return TT_Scale;
    else throw ViException(ERRNUM_TRANSFTYPE__IMPROPER_NAME,
         (MSG(ERRMSG_TRANSFTYPE__IMPROPER_NAME),
	  Name,
         KW__TT_ROT_EULER", "KW__TT_ROT_XYZ", "KW__TT_TRANS", "KW__TT_SCALE"."));
  }


  /*!
   *  Funkcja dokonuje konwersji nazwy warto¶ci typu 
   * \link Vi::MetricUnit MetricUnit\endlink na warto¶æ 
   * tego typu.\n
   * Zestaw dopuszczalnych nazw zdefiniowany jest poprzez sta³e:
   *  \li \link vi-kewords.hh::KW__MU_NONE KW__MU_NONE\endlink
   *  \li \link vi-kewords.hh::KW__MU_DEG KW__MU_DEG\endlink
   *  \li \link vi-kewords.hh::KW__MU_RAD KW__MU_RAD\endlink
   *  \li \link vi-kewords.hh::KW__MU_MET KW__MU_MET\endlink
   *  \li \link vi-kewords.hh::KW__MU_CEN KW__MU_CEN\endlink
   *  \li \link vi-kewords.hh::KW__MU_MIL KW__MU_MIL\endlink
   * \param Name - nazwa warto¶ci typu  
   *               \link Vi::MetricUnit MetricUnit\endlink
   * \exception ViException z kodem b³êdu \link
   *                 vierrors.hh::ERRNUM_METRICUNIT__IMPROPER_NAME
   *                 ERRNUM_METRICUNIT__IMPROPER_NAME\endlink
   *            w przypadku, gdy nazwa nie odpowiada ¿adnej z oczekiwanych
   *            nazw.
   */
  Vi::MetricUnit String2MetricUnit(const char *Name) throw(ViException)
  {
    if (!strcmp(Name,KW__MU_DEG)) return MU_Deg;
    else if (!strcmp(Name,KW__MU_NONE)) return MU_NONE;
    else if (!strcmp(Name,KW__MU_RAD)) return MU_Rad;
    else if (!strcmp(Name,KW__MU_CEN)) return MU_Cen;
    else if (!strcmp(Name,KW__MU_MET)) return MU_Met;
    else if (!strcmp(Name,KW__MU_MIL)) return MU_Mil;
    else throw ViException(ERRNUM_METRICUNIT__IMPROPER_NAME,
         (MSG(ERRMSG_METRICUNIT__IMPROPER_NAME),
	  Name,
         KW__MU_NONE", "KW__MU_DEG", "KW__MU_RAD", "KW__MU_CEN", "
         KW__MU_MET", "KW__MU_MIL"."));
  }




  /*!
   *  Zwraca napis odpowiadaj±cy danej warto¶ci
   *  typu \link Vi::Coord3DType Vi::Coord3DType\endlink.
   */
  const char *MakeString(Vi::Coord3DType Val)
  { 
    switch (Val) {
      case Vi::CT_1: return "1";
      case Vi::CT_2: return "2";
      case Vi::CT_3: return "3";
    }
  }



  /*!
   *  Funkcja dokonuje konwersji nazwy warto¶ci typu 
   * \link Vi::Coord3DType Coord3DType\endlink na warto¶æ 
   * tego typu.\n
   * Zestaw dopuszczalnych nazw zdefiniowany jest poprzez nazwy:
   *  \li "1"
   *  \li "2"
   *  \li "3"
   * \param Name - nazwa warto¶ci typu  
   *               \link Vi::Coord3DType Coord3DType\endlink
   * \exception ViException z kodem b³êdu \link
   *                 vierrors.hh::ERRNUM_METRICUNIT__IMPROPER_NAME
   *                 ERRNUM_METRICUNIT__IMPROPER_NAME\endlink
   *            w przypadku, gdy nazwa nie odpowiada ¿adnej z oczekiwanych
   *            nazw.
   */
  Vi::Coord3DType String2Coord3DType(const char *Name) throw(ViException)
  {
    if (!strcmp(Name,"1")) return Vi::CT_1;
    else if (!strcmp(Name,"2")) return Vi::CT_2;
    else if (!strcmp(Name,"3")) return Vi::CT_3;
    else throw ViException(ERRNUM_COORD3DTYPE__IMPROPER_NAME,
                            (MSG(ERRMSG_COORD3DTYPE__IMPROPER_NAME),
	                         Name,"1, 2, 3."));
  }

}





/*!
 *  Udostêpnia wska¼nik na klasê bazow± ViNTreeNode obiektu, który
 *  zosta³ skojarzony z dan± pozycj± interfejsu.\n
 *  Wska¼nik na obiekt udostêpniany jest w trybie sta³ym.
 */
const ViNTreeNode * ViKinemCtrlItem::GetPolyh() const
{
  return (const ViNTreeNode*)
           ListItem<ViKinemCtrlItem,ID_KINEMCTRL_NTREENODE>::Root();
}


/*!
 *  Udostêpnia wska¼nik na klasê bazow± ViNTreeNode obiektu, który
 *  zosta³ skojarzony z dan± pozycj± interfejsu.\n
 *  Wska¼nik na obiekt udostêpniany jest w trybie modyfikacji.
 */
ViNTreeNode * ViKinemCtrlItem::UsePolyh()
{
  return (ViNTreeNode*)
           ListItem<ViKinemCtrlItem,ID_KINEMCTRL_NTREENODE>::Root();
}

/*!
 *  Udostêpnia wska¼nik na obiekt klasy ViElemePolyh, o ile zosta³
 *  on skojarzony z dan± pozycj± interfejsu. W przypadku przeciwnym 
 *  zwracany jest wska¼nik \p NULL.\n
 *  Wska¼nik na obiekt udostêpniany jest w trybie sta³ym.
 */
const ViElemePolyh *ViKinemCtrlItem::GetElemePolyh() const
{
  return GetPolyh() ? 
            (GetPolyh()->GetInheritorType() == IT_ELEMEPOLYH ?
	     (const ViElemePolyh*) GetPolyh() : 0L) : 0L;
}


/*!
 *  Udostêpnia wska¼nik na obiekt klasy ViElemePolyh, o ile zosta³
 *  on skojarzony z dan± pozycj± interfejsu. W przypadku przeciwnym 
 *  zwracany jest wska¼nik \p NULL.\n
 *  Wska¼nik na obiekt udostêpniany jest w trybie modyfikacji.
 */
ViElemePolyh *ViKinemCtrlItem::UseElemePolyh()
{
  return UsePolyh() ? 
            (UsePolyh()->GetInheritorType() == IT_ELEMEPOLYH ?
	     (ViElemePolyh*) UsePolyh() : 0L) : 0L;
}

/*!
 *  Udostêpnia wska¼nik na korzeñ ca³ej struktury modelu bry³y z³o¿onej.
 *  Je¿eli korzeniem nie jest obiekt klasy ViMultiPolyh lub klasy pochodnej,
 *  to zwracany jest wska¼nik \p NULL.\n
 *  Wska¼nik na obiekt udostêpniany jest w trybie sta³ym.
 */
const ViMultiPolyh *ViKinemCtrlItem::GetRootMultiPolyh() const
{
  if (const ViNTreeNode *pPolyh = GetPolyh()) {
    return 
       (pPolyh = pPolyh->GetTreeRoot())->GetInheritorType() == IT_MULTIPOLYH ?
	     (const ViMultiPolyh*) pPolyh : 0L; 
  } 
  return 0L;
}


/*!
 *  Udostêpnia wska¼nik na korzeñ ca³ej struktury modelu bry³y z³o¿onej.
 *  Je¿eli korzeniem nie jest obiekt klasy ViMultiPolyh lub klasy pochodnej,
 *  to zwracany jest wska¼nik \p NULL.\n
 *  Wska¼nik na obiekt udostêpniany jest w trybie modyfikacji.
 */
ViMultiPolyh *ViKinemCtrlItem::UseRootMultiPolyh()
{
  if (ViNTreeNode *pPolyh = UsePolyh()) {
    return 
       (pPolyh = pPolyh->GetTreeRoot())->GetInheritorType() == IT_MULTIPOLYH ?
	     (ViMultiPolyh*) pPolyh : 0L; 
  } 
  return 0L;
}


/*!
 *  Wylicza wszystkie wierzcho³ki dla danej bry³y z³o¿onej, której
 *  dowolny element zosta³ kojarzony z dan± pozycj± interfejsu.
 *  \retval true - je¶li obliczenia zosta³y poprawnie przeprowadzone.
 *  \retval false - gdy oblicznia nie mog³y byæ przeprowadzone,
 *                np. korzen ca³ej struktury modelu bry³y nie jest
 *                obiektem klasy ViMultiPolyh lub klasy pochodnej.
 */
bool ViKinemCtrlItem::ComputeAllPolyhGlbVtx()
{
  if (ViMultiPolyh *pMuPolyh = UseRootMultiPolyh()) {
    return !pMuPolyh->ComputeHierAllGlbVtx();
  }
  return false;
}





void ViKinemCtrlItem::UpdateMtx_Rot_Euler()
{

  switch (_Unit) {
   case Vi::MU_Deg:
     switch (_Trans_Order) {
      case TO_Before:
        _Mtx.SetAng_Euler_TBeforeR_Deg(_Coord_Type,_Val);
	break;
      case TO_After:
        _Mtx.SetAng_Euler_TAfterR_Deg(_Coord_Type,_Val);
	break;
     }
     break;
   case Vi::MU_Rad:
     switch (_Trans_Order) {
      case TO_Before:
        _Mtx.SetAng_Euler_TBeforeR_Rad(_Coord_Type,_Val);
	break;
      case TO_After:
        _Mtx.SetAng_Euler_TAfterR_Rad(_Coord_Type,_Val);
	break;
     }
     break;
   default:
     cerr << "!!! W metodzie ViKinemCtrlItem::UpdateMtx_Rot_Euler" 
          << " wystepuje nie obslugiwany typ jednostki.";
     cerr << endl;
     break;
  }
}


/*!
 *  Aktualizuje wspó³czynniki macierzy dla zmian k±tów \e XYZ.
 */
void ViKinemCtrlItem::UpdateMtx_Rot_XYZ()
{
  switch (_Unit) {
   case Vi::MU_Deg:
     switch (_Trans_Order) {
      case TO_Before:
        _Mtx.SetAng_XYZ_TBeforeR_Deg(_Coord_Type,_Val);
	break;
      case TO_After:
        _Mtx.SetAng_XYZ_TAfterR_Deg(_Coord_Type,_Val);
	break;
     }
     break;
   case Vi::MU_Rad:
     switch (_Trans_Order) {
      case TO_Before:
        _Mtx.SetAng_XYZ_TBeforeR_Rad(_Coord_Type,_Val);
	break;
      case TO_After:
        _Mtx.SetAng_XYZ_TAfterR_Rad(_Coord_Type,_Val);
	break;
     }
     break;
   default:
     cerr << "!!! W metodzie ViKinemCtrlItem::UpdateMtx_Rot_XYZ" 
          << " wystepuje nie obslugiwany typ jednostki.";
     cerr << endl;
     break;
  }
}



/*!
 *  Aktualizuje wspó³czynniki macierzy dla zmian wspó³rzêdnej wektora
 *  translacji.
 */
void ViKinemCtrlItem::UpdateMtx_Trans()
{
  switch (_Trans_Order) {
      case TO_Before:
        _Mtx.SetTrans_TBeforeR(_Coord_Type,_Val);
	break;
      case TO_After:
        _Mtx.SetTrans_TAfterR(_Coord_Type,_Val);
	break;
  }
}




/*!
 *  Aktualizuje wspó³czynniki macierzy dla zmian wspó³rzêdnej wektora
 *  skali.
 */
void ViKinemCtrlItem::UpdateMtx_Scale()
{
  switch (_Trans_Order) {
      case TO_Before:
        _Mtx.SetScale_TBeforeR(_Coord_Type,_Val);
	break;
      case TO_After:
        _Mtx.SetScale_TAfterR(_Coord_Type,_Val);
	break;
  }
}





/*!
 * \if brief_public_methods
 * \brief Aktualizuje warto¶æ parametru macierzy transformacji
 * \endif
 *
 * Aktualizuje warto¶æ parametru macierzy transformacji pobieraj±c
 * jego warto¶æ z pola \link ViKinemCtrlItem::_Val _Val\endlink.
 * Umieszczana jest ona jako odpowiedni parametr zgodnie z zadan±
 * interpretacj± (patrz metody
 * \link ViKinemCtrlItem::SetCoordType SetCoordType\endlink,
 * \link ViKinemCtrlItem::SetTransOrder SetTransOrder\endlink,
 * \link ViKinemCtrlItem::SetTransfType SetTransfType\endlink,
 * \link ViKinemCtrlItem::SetUnit SetUnit\endlink).
 *
 * Niniejsza metoda jest aktualnie w opracowaniu.
 */
void ViKinemCtrlItem::UpdateMtx()
{
  switch (GetTransfType()) {
   case Vi::TT_Rot_Euler:  UpdateMtx_Rot_Euler(); break;
   case Vi::TT_Rot_XYZ: UpdateMtx_Rot_XYZ(); break;
   case Vi::TT_Trans: UpdateMtx_Trans(); break;
   case Vi::TT_Scale: UpdateMtx_Scale(); break;
  }
}



/*!
 * Inicjalizuje obiekt i ³±czy go jednocze¶nie z dan± macierz± 
 * transformacji. Realizowane to jest poprzez inicjalizacjê 
 * referencji do tej macierzy. Sprawia to, ¿e takie skojarzenie
 * tego obiektu ze wspomnian± macierz± nie mo¿e byæ ju¿ pó¼niej 
 * modyfikowalne.
 * \param Mtx - macierz transformacji, z któr± skojarzony
 *              zostaje dany obiekt.
 * \param KeyID - identyfikator liczbowy pozwalaj±cy odnale¼æ dany
 *                 dany element w kolejce.
 * \param KeyName - napis indentyfikuj±cy dany element po¶ród 
 *                 innych elementów. Mo¿e byæ wykorzystywany
 *                 tylko jeden z identyfikatorów tzn. liczbowy
 *                 lub napisowy. 
 */
ViKinemCtrlItem::ViKinemCtrlItem(  ViMatrix3f   &Mtx, 
			           const char  *KeyName,
                                   int          KeyID
                                ): 
  _Mtx(Mtx) 
{
  _Min = -numeric_limits<float>::max();
  _Max = numeric_limits<float>::max();
  SetKeyName(KeyName);  SetKeyID(KeyID);
}



/*!
 * Inicjalizuje obiekt i ³±czy go jednocze¶nie z dan± macierz± 
 * transformacji. Realizowane to jest poprzez inicjalizacjê 
 * referencji do tej macierzy. Sprawia to, ¿e takie skojarzenie
 * tego obiektu ze wspomnian± macierz± nie mo¿e byæ ju¿ pó¼niej 
 * modyfikowalne.
 * \param Mtx - macierz transformacji, z któr± skojarzony
 *              zostaje dany obiekt.
 * \param KeyID - identyfikator liczbowy pozwalaj±cy odnale¼æ dany
 *                 dany element w kolejce.
 * \param KeyName - napis indentyfikuj±cy dany element po¶ród 
 *                 innych elementów. Mo¿e byæ wykorzystywany
 *                 tylko jeden z identyfikatorów tzn. liczbowy
 *                 lub napisowy. 
 */
ViKinemCtrlItem::ViKinemCtrlItem( ViMatrix3f   &Mtx, 
                                  int          KeyID, 
                                  const char  *KeyName 
                               ): 
  _Mtx(Mtx) 
{
  _Min = -numeric_limits<float>::max();
  _Max = numeric_limits<float>::max();
  SetKeyName(KeyName);  SetKeyID(KeyID);
}


/*!
 *  Wpisuje now± warto¶æ i jednocze¶nie aktualizuje wspó³czynnik macierzy,
 *  które zwi±zane s± ze zmienianym parametrem transformacji.
 *  Nowa warto¶æ jest wpisywana, o ile spe³nia ograniczenia,
 *  tzn. \f$ \_Min \leq Val \leq \_Max \f$.
 *  \param   Val - (\b in) nowa warto¶æ parametru transformacji.
 *  \retval  0   - je¿eli spe³nione s± ograniczenia i nowa warto¶æ
 *                 zosta³a podstawiona.
 *  \retval -1   - gdy nie jest spe³nione dolne ograniczenie,
 *                 tzn. \f$ Val < \_Min\f$.
 *  \retval  1   - gdy nie jest spe³nione górne ograniczenie,
 *                 tzn. \f$ \_Max < Val \f$.
 */
int ViKinemCtrlItem::SetVal(float Val) 
 { 
     if (Val < _Min) return -1;
     if (_Max < Val) return 1;
      _Val = Val;  UpdateMtx(); 
     return 0;
 }



/*!
 * Inicjalizuje obiekt i ³±czy go jednocze¶nie z dan± macierz± 
 * transformacji. Realizowane to jest poprzez inicjalizacjê 
 * referencji do tej macierzy. Sprawia to, ¿e takie skojarzenie
 * tego obiektu ze wspomnian± macierz± nie mo¿e byæ ju¿ pó¼niej 
 * modyfikowalne.
 * \param pPolyh - wska¼nik na macierz, do której nale¿y dana macierz.
 * \param Mtx - macierz transformacji, z któr± skojarzony
 *              zostaje dany obiekt.
 * \param TransfType - typ transformacji, której parametr bêdzie podlega³
 *                     zmianie,
 * \param Coord - okre¶la, która ze wspó³rzêdnych danego wektora parametrów
 *                ma podlegaæ zmianom.
 * \param TOrder - okre¶la porz±dek translacji wzglêdem rotacji,
 * \param Unit - okre¶la jednostkê, w których podawana jest warto¶æ
 *               danego parametru.
 */
ViKinemCtrlItem::ViKinemCtrlItem( ViNTreeNode     *pPolyh,
                                  ViMatrix3f          &Mtx,
                                  Vi::TransformType   TransfType,
                                  Vi::Coord3DType     Coord,
                                  TransOrder          TOrder,
                                  Vi::MetricUnit      Unit
                                ): _Mtx(Mtx)
{
  _Min = -numeric_limits<float>::max();
  _Max = numeric_limits<float>::max();  
  SetTransfType(TransfType);
  SetCoordType(Coord);
  SetTransOrder(TOrder);
  SetUnit(Unit);
  if (pPolyh) pPolyh->BindWithCtrlInterfaceItem(this);
}

ViKinemCtrlItem::~ViKinemCtrlItem() {}



/*!
 *  \if brief_public_methods
 *   \brief  Metoda zapisuje sekcjê interfejsu.
 *  \endif
 *
 *  Metoda zapisuje sekcjê interfejsu.
 *  Sekcja interfejsu jest tworzona bez wzglêdu na to, czy jest pusta,
 *  czy te¿ nie.
 *  \param ostrm - (\b in/\b out) strumieñ wyj¶ciowy.
 *  \param Margin - (\b in) okre¶la ilo¶æ spacji jakie poprzedzaj± 
 *                   s³owo kluczowe otwieraj±ce sekcjê interfejsu sterownia.
 *  \retval true - je¶li operacja zapisu powiod³a siê.
 *  \retval false - w przypadku przeciwnym.
 */
bool ViKinemCtrlItem::WriteTo( ostream      &ostrm,
                               unsigned int  Margin
                             ) const
{
  Space(ostrm,Margin) << KW_CTRLINTERFACEITEM_BEGIN << endl;
  Margin += 2;
  Space(ostrm,Margin) << KW_NODEADDRESS << ": "
                        << GetPolyh()->GetNodeAddress() << endl;
  Space(ostrm,Margin) << KW_MTXID << ": " << GetMtx().GetMtxID() << endl;
  Space(ostrm,Margin) << KW_KEYID << ": " << GetKeyID() << endl;

  if (!GetKeyName().IsEmptyText()) {
    Space(ostrm,Margin) << KW_KEYNAME << ": " << GetKeyName() << endl;
  }
  if (!GetCommentName().IsEmptyText()) {
    Space(ostrm,Margin) << KW_COMMENT << ": " << GetCommentName() << endl;
  }
  Space(ostrm,Margin) << KW_TRANSFTYPE << ": " 
                      << Vi::MakeString(GetTransfType()) << endl;
  Space(ostrm,Margin) << KW_TRANSORDER << ": "
                      << Vi::MakeString(GetTransOrder()) << endl;
  Space(ostrm,Margin) << KW_UNIT << ": " << Vi::MakeString(GetUnit()) << endl;
  Space(ostrm,Margin) << KW_COORDTYPE << ": "
                      << Vi::MakeString(GetCoordType()) << endl;
  if (!IsMaxUnlimited()) {
    Space(ostrm,Margin+1) << KW_MAX << ": " << GetMax() << endl;
  }
  if (!IsMinUnlimited()) {
    Space(ostrm,Margin+1) << KW_MIN << ": " << GetMin() << endl;
  }
  Space(ostrm,Margin) << KW_VALUE << ": " << GetVal() << endl;
  Margin -= 2;
  return (Space(ostrm,Margin) << KW_CTRLINTERFACEITEM_END << endl).good();
}




//======================================================================
//__________________ ViKinemCtrlSet _______________________________





/*!
 *  \if brief_public_methods
 *   \brief  Metoda zapisuje sekcjê interfejsu.
 *  \endif
 *
 *  Metoda zapisuje sekcjê interfejsu.
 *  Sekcja interfejsu jest tworzona bez wzglêdu na to, czy jest pusta,
 *  czy te¿ nie.
 *  \param ostrm - (\b in/\b out) strumieñ wyj¶ciowy.
 *  \param Margin - (\b in) okre¶la ilo¶æ spacji jakie poprzedzaj± 
 *                   s³owo kluczowe otwieraj±ce sekcjê interfejsu sterownia.
 *  \retval true - je¶li operacja zapisu powiod³a siê.
 *  \retval false - w przypadku przeciwnym.
 */
bool ViKinemCtrlSet::WriteTo( ostream      &ostrm,
                              unsigned int  Margin
                            ) const
{
  Space(ostrm,Margin) << KW_CTRLINTERFACE_BEGIN << endl;
  for (ViKinemCtrlSet::ConCtrlIter Iter = ConBegin_Ctrl(); Iter; ++Iter) {
    if (!Iter->WriteTo(ostrm,Margin+2)) return false;
  }
  return (Space(ostrm,Margin) << KW_CTRLINTERFACE_END << endl).good();
}







/*!
 *  Dodaje now± pozycjê, daj±c± dostêp do zadanej macierzy 
 *  transformacji i definiuj±c± interfejs do danej wspó³rzêdnej.
 * \param Mtx - macierz transformacji, z któr± skojarzony
 *              zostaje dany obiekt.
 * \param KeyID - identyfikator liczbowy pozwalaj±cy odnale¼æ dany
 *                 dany element w kolejce.
 * \param KeyName - napis indentyfikuj±cy dany element po¶ród 
 *                 innych elementów. Mo¿e byæ wykorzystywany
 *                 tylko jeden z identyfikatorów tzn. liczbowy
 *                 lub napisowy. 
 */
ViKinemCtrlItem *ViKinemCtrlSet::Add( ViMatrix3f   &Mtx, 
                                      int          KeyID, 
                                      const char  *KeyName
                                    )
{
  return AddToTail(new ViKinemCtrlItem(Mtx,KeyID,KeyName));
}



/*!
 *  Dodaje now± pozycjê, daj±c± dostêp do zadanej macierzy 
 *  transformacji i definiuj±c± interfejs do danej wspó³rzêdnej.
 * \param Mtx - macierz transformacji, z któr± skojarzony
 *              zostaje dany obiekt.
 * \param KeyID - identyfikator liczbowy pozwalaj±cy odnale¼æ dany
 *                 dany element w kolejce.
 * \param KeyName - napis indentyfikuj±cy dany element po¶ród 
 *                 innych elementów. Mo¿e byæ wykorzystywany
 *                 tylko jeden z identyfikatorów tzn. liczbowy
 *                 lub napisowy. 
 */
ViKinemCtrlItem *ViKinemCtrlSet::Add( ViMatrix3f   &Mtx, 
                                      const char  *KeyName,
                                      int          KeyID
                                    )
{
  return AddToTail(new ViKinemCtrlItem(Mtx,KeyID,KeyName));
}




/*!
 *  Dodaje now± pozycjê, daj±c± dostêp do zadanej macierzy 
 *  transformacji i definiuj±c± interfejs do danej wspó³rzêdnej.
 * \param pPolyh - wska¼nik na obiekt modeluj±cy bry³ê, dla której 
 *                 bêdzie modyfikowany dany parametr transformacji.
 * \param Mtx - macierz transformacji, z któr± skojarzony
 *              zostaje dany obiekt.
 * \param TransfType - typ transformacji, której parametr bêdzie podlega³
 *                     zmianie,
 * \param Coord - okre¶la, która ze wspó³rzêdnych danego wektora parametrów
 *                ma podlegaæ zmianom.
 * \param TOrder - okre¶la porz±dek translacji wzglêdem rotacji,
 * \param Unit - okre¶la jednostkê, w których podawana jest warto¶æ
 *               danego parametru.
 */
ViKinemCtrlItem *ViKinemCtrlSet::Add( ViNTreeNode    *pPolyh,
                                      ViMatrix3f          &Mtx,
                                      Vi::TransformType   TransfType,
                                      Vi::Coord3DType     Coord,
                                      TransOrder          TOrder,
                                      Vi::MetricUnit      Unit
                                    )
{
  return 
    AddToTail(new ViKinemCtrlItem(pPolyh,Mtx,TransfType,Coord,TOrder,Unit));
}


inline
bool CompareKeyID_Const(int Key,  const ListItem<ViKinemCtrlItem> *Item )
{
  return Key ==  ((const ViKinemCtrlItem *)Item)->GetKeyID();
}

inline
bool CompareKeyID_Modyf(int Key, const ListItem<ViKinemCtrlItem> *Item )
{
  return Key == ((const ViKinemCtrlItem *)Item)->GetKeyID();
}



/*!
 * \if brief_public_methods
 *  \brief Wyszukuje zadany element
 * \endif
 *
 * Wyszukuje danej pozycji interfejsu sterowania parametrem transformacji
 * wg. identyfikatora liczbowego.
 * \param Key - (\b in) identyfikator liczbowy danej pozycji interfejsu.
 * \return wska¼nik na znaleziony element (udostêpniany on jest w trybie sta³ym)
 *         lub adres \p NULL w przypadku,
 *         gdy taki element nie zosta³ znaleziony. 
 */
const ViKinemCtrlItem *ViKinemCtrlSet::FindByKeyID(int Key) const
{
  return (const ViKinemCtrlItem *) 
                 FindInList(*this,Key,CompareKeyID_Const);
}


/*!
 * Wyszukuje i usuwa element interfejsu sterowania o zadanym 
 * identyfikatorze.
 * \param Key - identyfikator liczbowym danej pozycji interfejsu
 *              sterowania.
 * \retval true - je¿eli element o zadanym indentyfikatorze zosta³
 *                odnaleziony i usuniêty.
 * \retval false - gdy element o podanym identyfikatorze nie zosta³
 *                odnaleziony.
 */
bool ViKinemCtrlSet::DeleteByKeyID(int Key)
{
  if (ViKinemCtrlItem *pCItem = FindByKeyID(Key)) {
    delete pCItem;
    return true;
  }
  return false;
}


/*!
 * Wyszukuje i usuwa element interfejsu sterowania o zadanym 
 * identyfikatorze znakowym.
 * \param KeyName - identyfikator znakowym danej pozycji interfejsu
 *              sterowania.
 * \retval true - je¿eli element o zadanym indentyfikatorze zosta³
 *                odnaleziony i usuniêty.
 * \retval false - gdy element o podanym identyfikatorze nie zosta³
 *                odnaleziony.
 */
bool ViKinemCtrlSet::DeleteByKeyName(const char *KeyName)
{
  if (ViKinemCtrlItem *pCItem = FindByKeyName(KeyName)) {
    delete pCItem;
    return true;
  }
  return false;
}


/*!
 * Wyszukuje i usuwa element interfejsu sterowania o zadanym 
 * nazwie komentarza skojarzonego z szukan± pozycj±.
 * \param CommentName - komentarz skojarzony z szukan± pozycj± 
 *              interfejsu sterowania.
 * \retval true - je¿eli szukany element zosta³
 *                odnaleziony i usuniêty.
 * \retval false - gdy element o nie zosta³
 *                odnaleziony.
 */
bool  ViKinemCtrlSet::DeleteByCommentName(const char *CommentName)
{
  if (ViKinemCtrlItem *pCItem = FindByCommentName(CommentName)) {
    delete pCItem;
    return true;
  }
  return false;
}



/*!
 * \if brief_public_methods
 *  \brief Wyszukuje zadany element
 * \endif
 *
 * Wyszukuje danej pozycji interfejsu sterowania parametrem transformacji
 * wg. identyfikatora liczbowego.
 * \param Key - (\b in) identyfikator liczbowy danej pozycji interfejsu.
 * \return wska¼nik na znaleziony element (udostêpniany on jest w trybie
 *         modyfikacji)
 *         lub adres \p NULL w przypadku,
 *         gdy taki element nie zosta³ znaleziony. 
 */
ViKinemCtrlItem *ViKinemCtrlSet::FindByKeyID(int Key)
{
  return (ViKinemCtrlItem *) FindInList(*this,Key,CompareKeyID_Modyf);
}







inline
bool CompareKeyName_Const( const char                           *Key,  
                           const ListItem<ViKinemCtrlItem> *Item 
                         )
{
  return ((const ViKinemCtrlItem *)Item)->GetKeyName() == Key;
}

inline
bool CompareKeyName_Modyf( const char                     *Key, 
                           ListItem<ViKinemCtrlItem> *Item 
                         )
{
  return ((ViKinemCtrlItem *)Item)->GetKeyName() == Key;
}



/*!
 * \if brief_public_methods
 *  \brief Wyszukuje zadany element
 * \endif
 *
 * Wyszukuje danej pozycji interfejsu sterowania parametrem transformacji
 * wg. identyfikatora liczbowego.
 * \param Key - (\b in) identyfikator tekstowy danej pozycji interfejsu.
 * \return wska¼nik na znaleziony element (udostêpniany on jest w trybie sta³ym)
 *         lub adres \p NULL w przypadku,
 *         gdy taki element nie zosta³ znaleziony. 
 */
const ViKinemCtrlItem *
              ViKinemCtrlSet::FindByKeyName(const char *Key) const
{
  return (const ViKinemCtrlItem *)
                    FindInList(*this,Key,CompareKeyName_Const);
}




/*!
 * \if brief_public_methods
 *  \brief Wyszukuje zadany element
 * \endif
 *
 * Wyszukuje danej pozycji interfejsu sterowania parametrem transformacji
 * wg. identyfikatora liczbowego.
 * \param Key - (\b in) identyfikator tekstowy danej pozycji interfejsu.
 * \return wska¼nik na znaleziony element (udostêpniany on jest w trybie
 *         modyfikacji)
 *         lub adres \p NULL w przypadku,
 *         gdy taki element nie zosta³ znaleziony. 
 */
ViKinemCtrlItem *ViKinemCtrlSet::FindByKeyName(const char *Key)
{
  return (ViKinemCtrlItem *) FindInList(*this,Key,CompareKeyName_Modyf);
}

















inline
bool CompareCommentName_Const( const char                           *Key,  
                               const ListItem<ViKinemCtrlItem> *Item 
                             )
{
  return ((const ViKinemCtrlItem *)Item)->GetCommentName() == Key;
}

inline
bool CompareCommentName_Modyf( const char                      *Key, 
                               ListItem<ViKinemCtrlItem>  *Item 
                             )
{
  return ((ViKinemCtrlItem *)Item)->GetCommentName() == Key;
}



/*!
 * \if brief_public_methods
 *  \brief Wyszukuje zadany element
 * \endif
 *
 * Wyszukuje danej pozycji interfejsu sterowania parametrem transformacji
 * wg. identyfikatora liczbowego.
 * \param Key - (\b in) nazwa danej pozycji interfejsu wykorzystywana 
 *              w dialogu.
 * \return wska¼nik na znaleziony element (udostêpniany on jest w trybie sta³ym)
 *         lub adres \p NULL w przypadku,
 *         gdy taki element nie zosta³ znaleziony. 
 */
const ViKinemCtrlItem *
              ViKinemCtrlSet::FindByCommentName(const char *Key) const
{
  return (const ViKinemCtrlItem *) 
                      FindInList(*this,Key,CompareCommentName_Const);
}




/*!
 * \if brief_public_methods
 *  \brief Wyszukuje zadany element
 * \endif
 *
 * Wyszukuje danej pozycji interfejsu sterowania parametrem transformacji
 * wg. identyfikatora liczbowego.
 * \param Key - (\b in) nazwa danej pozycji interfejsu wykorzystywana w
 *              diablogu.
 * \return wska¼nik na znaleziony element (udostêpniany on jest w trybie
 *         modyfikacji)
 *         lub adres \p NULL w przypadku,
 *         gdy taki element nie zosta³ znaleziony. 
 */
ViKinemCtrlItem *ViKinemCtrlSet::FindByCommentName(const char *Key)
{
  return (ViKinemCtrlItem *) 
                      FindInList(*this,Key,CompareCommentName_Modyf);
}
