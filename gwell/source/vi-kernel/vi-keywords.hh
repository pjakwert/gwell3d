#ifndef VI_KEYWORDS_HH
#define VI_KEYWORDS_HH

/*!
 * \file vi-keywords.hh
 * Plik zawiera definicjê sta³ych reprezentuj±cych poszczególne s³owa
 * kluczowe wykorzystywane przy zapisie i odczycie opisów bry³ wzorcowych,
 * elementarnych i z³o¿onych. 
 * \author Bogdan Kreczmer
 * \date   2004.06
 */

/*!
 *  S³owo kluczowe rozpoczynaj±ce sekcjê opisu bry³y z³o¿onej.
 */
# define  KW_MULTIPOLYH_BEGIN   "MultiPolyh__Begin"
/*!
 *  S³owo kluczowe koñcz±ce sekcjê opisu bry³y z³o¿onej.
 */
# define  KW_MULTIPOLYH_END     "MultiPolyh__End"
/*!
 *  S³owo kluczowe opisy bry³y, po którym podana jest indywidualna 
 *  nazwa danego wêz³a (bry³y sk³adowej)
 *  danej struktury wielodrzewa.\n
 *  Format zapisu:
 *  \verbatim
        NodeName:  nazwa_wêz³a
    \endverbatim
 *  Opis specyfikacji nazwy znajduje siê  w sekcji \ref  nazwy_bryl 
 *  "Nazwy i bry³".
 */
# define  KW_INDIVNAME        "NodeName"
/*!
 *  S³owo kluczowe poprzedzaj±ce adres danego wêz³a.
 *  Adres wêz³a wystêpuje po znaku ':', który wpisywany jest
 *  bezpo¶rednio po tym s³owie kluczowy.
 */
# define  KW_NODEADDRESS      "NodeAddress"
/*!
 *  S³owo kluczowe poprzedzaj±ce opis macierzy transformacji
 *  uk³adu wspó³rzêdnych lokalnych danego wêz³a 
 *  do uk³adu wspó³rzêdnych jego rodzica rodzica.
 */
# define  KW_TRANSF2PARENT    "Transf_Node2Parent"
/*!
 *  S³owo kluczowe poprzedzaj±ce opis warto¶ci k±tów
 *  dla danej tranformacji.
 */
# define  KW_ANGLES           "Angles"
/*!
 *  S³owo kluczowe, które w opisie k±tów rotacji okre¶la
 *  ich typ. W tym przypadku odnosi siê ono do k±tów Eulera
 *  (\e ZYZ).
 */
# define  KW_ANG_EULER        "Euler"
/*!
 *  S³owo kluczowe, które w opisie k±tów rotacji okre¶la
 *  ich typ. W tym przypadku odnosi siê ono do k±tów \e XYZ,
 *  tzn. pierwszy obrów wokó³ osi \f$ OX\f$, drugi wokó³ osi
 *  \f$ OY'\$, trzeci wokó³ osi \f$ OZ''\f$.
 */
# define  KW_ANG_XYZ          "XYZ"
/*!
 * Wykorzystywane jest przy zapisie warto¶ci k±tów.
 * Wskazuje ono, ¿e warto¶ci k±tów wyra¿one s± w radianach.
 */
# define  KW_ANG_RAD          "Rad"
/*!
 * Wykorzystywane jest przy zapisie warto¶ci k±tów.
 * Wskazuje ono, ¿e warto¶ci k±tów wyra¿one s± w stopniach.
 */
# define  KW_ANG_DEG          "Deg"
/*!
 * Definiuje s³owo kluczowe poprzedzaj±ce warto¶æ wektora translacji
 * w opisie macierzy transformacji uk³adu wspó³rzêdnych.
 */ 
# define  KW_TRANSLATION      "Translation"
/*!
 * Definiuje s³owo kluczowe poprzedzaj±ce warto¶æ wektora skali
 * w opisie macierzy transformacji uk³adu wspó³rzêdnych.
 */ 
# define  KW_SCALE            "Scale"
/*!
 * S³owo kluczowe otwieraj±ce sekcjê opisu wêz³a.
 */
# define  KW_NODE             "Node__Begin"
/*!
 * S³owo kluczowe zamykaj±ce sekcjê opisu wêz³a.
 */
# define  KW_ENDNODE          "Node__End"
/*!
 * S³owo kluczowe otwieraj±ce sekcjê opisu klasy.
 * Sekcja ta znajduje siê wewn±trz sekcji opisu wêz³a.
 */
# define  KW_BEGIN_DERIVSEC   "ClassSection__Begin"
/*!
 * S³owo kluczowe zamykaj±ce sekcjê opisu klasy.
 * Sekcja ta znajduje siê wewn±trz sekcji opisu wêz³a.
 */
# define  KW_END_DERIVSEC     "ClassSection__End"
/*!
 * S³owo kluczowe poprzedzaj±ce nazwê bry³y wzorcowej.
 * Nazwa wystêpuje po znaku ':'.
 * Niniejsze s³owo kluczowe wykorzystywane jest w opisie 
 * bry³y elementarnej.
 */
# define  KW_PATTNAME         "PatternPolyhedronName"
/*!
 *  S³owo kluczowe poprzedza opis macierzy transformacji
 *  z uk³adu wspó³rzêdnych bry³y wzorcowej do uk³adu wspó³rzêdnych
 *  bry³y elementarnej.
 */
# define  KW_PATTE2ELEME      "Transf_Patte2Eleme"
/*!
 *  S³owo kluczowe poprzedza opis macierzy transformacji
 *  z uk³adu wspó³rzêdnych bry³y elementarnej do jej 
 *  indywidualnego uk³adu wspó³rzêdnych.
 */
# define  KW_ELEME2INDIV      "Transf_Eleme2Indiv"


/*!
 *  S³owo kluczowe otwieraj±ce sekcjê interfejsu sterowania w 
 *  opisie bry³y z³o¿onej.
 */
# define  KW_CTRLINTERFACE_BEGIN "CtrlInterface__Begin"
/*!
 *  S³owo kluczowe zamykaj±ce sekcjê interfejsu sterowania w 
 *  opisie bry³y z³o¿onej.
 */
# define  KW_CTRLINTERFACE_END   "CtrlInterface__End"
/*!
 *  S³owo kluczowe otwieraj±ce sekcjê danej pozycji interfejsu 
 *  sterowania w opisie bry³y z³o¿onej.
 */
# define  KW_CTRLINTERFACEITEM_BEGIN "InterfaceItem__Begin"
/*!
 *  S³owo kluczowe zamykaj±ce sekcjê danej pozycji interfejsu 
 *  sterowania w opisie bry³y z³o¿onej.
 */
# define  KW_CTRLINTERFACEITEM_END "InterfaceItem__End"

/*!
 * S³owo kluczowe poprzedza numer identyfikatora dla obiektu
 * danej sturktury (zwykle chodzi o identyfikator umo¿liwiaj±cy
 * odnalezienie ¿±danego elementu w li¶cie).
 * Identyfikator umieszczany jest po znaku ':'.
 */
# define  KW_KEYID   "KeyID"
/*!
 * S³owo kluczowe poprzedza nazwê identyfikuj±c± obiekt
 * danej sturktury (zwykle chodzi o identyfikator umo¿liwiaj±cy
 * odnalezienie ¿±danego elementu w li¶cie).  Identyfikator umieszczany 
 * jest po znaku ':'.
 */
# define  KW_KEYNAME "KeyName"
/*!
 * S³owo poprzedza komentarz, który przewidziany jest w tworzonym
 * dialogu, np. dialogu sterowania danym prametrem transformacji.
 */
# define  KW_COMMENT "Comment"
/*!
 * S³owo kluczowe poprzedzaj±ce warto¶æ parametru w 
 * opisie interfejsu sterowania bry³± z³o¿on±.
 */
# define  KW_VALUE   "Value"
/*!
 * S³owo kluczowe poprzedza warto¶æ dolnego ograniczenia parametru
 * zadawanego poprzez interfejs sterowania.
 * Wspomniana warto¶c wystêpuje po znaku ':'.
 */
# define  KW_MIN     "Min"
/*!
 * S³owo kluczowe poprzedza warto¶æ górnego ograniczenia parametru
 * zadawanego poprzez interfejs sterowania.
 * Wspomniana warto¶c wystêpuje po znaku ':'.
 */
# define  KW_MAX     "Max"
/*!
 *  S³owo kluczowe poprzedzaj±ce nazwê okre¶laj±c± kolejno¶æ
 *  rotacji wzglêdem translacji.\n
 *  Wspomniany ³añcuch wystêpuje po znaku ':'.
 */
# define  KW_TRANSORDER   "TransOrder"




/*!
 *  S³owo kluczowe, które odpowiada warto¶ci \p TO_After
 *  dla typu \link matrixh3f.hh::TransOrder TransOrder\endlink.
 */
# define  KW__TO_AFTER    "TAfterR"
/*!
 *  S³owo kluczowe, które odpowiada warto¶ci \p TO_Before
 *  dla typu \link matrixh3f.hh::TransOrder TransOrder\endlink.
 */
# define  KW__TO_BEFORE   "TBeforeR"
/*!
 * S³owo kluczowe poprzedzaj±ce nazwê jednostki miary danej
 * wielko¶ci.\n
 * Wspomniana nazwa wystêpuje po znaku ':'.
 */
# define  KW_UNIT  "Unit"





/*!
 * S³owo kluczowe, które odpowiada warto¶ci \p TU_NONE
 *  dla typu \link Vi::MetricUnit Vi::MetricUnit\endlink.
 */
# define  KW__MU_NONE  "None"
/*!
 * S³owo kluczowe, które odpowiada warto¶ci \p TU_DEG
 *  dla typu \link Vi::MetricUnit Vi::MetricUnit\endlink.
 */
# define  KW__MU_DEG  "Deg"
/*!
 * S³owo kluczowe, które odpowiada warto¶ci \p TU_RAD
 *  dla typu \link Vi::MetricUnit Vi::MetricUnit\endlink.
 */
# define  KW__MU_RAD  "Rad"
/*!
 * S³owo kluczowe, które odpowiada warto¶ci \p TU_CEN
 *  dla typu \link Vi::MetricUnit Vi::MetricUnit\endlink.
 */
# define  KW__MU_CEN  "Centimeter"
/*!
 * S³owo kluczowe, które odpowiada warto¶ci \p TU_MET
 *  dla typu \link Vi::MetricUnit Vi::MetricUnit\endlink.
 */
# define  KW__MU_MET  "Meter"
/*!
 * S³owo kluczowe, które odpowiada warto¶ci \p TU_MIL
 *  dla typu \link Vi::MetricUnit Vi::MetricUnit\endlink.
 */
# define  KW__MU_MIL  "Millimeter"


/*!
 *  S³owo kluczowe poprzedza okre¶lenie typu transformacji,
 *  jaka jest zwi±zana z dan± pozycj± interfejsu sterownia.
 */
# define  KW_TRANSFTYPE   "TransfType"


/*!
 * S³owo kluczowe, które odpowiada warto¶ci \p TT_Rot_Euler
 *  dla typu \link Vi::TransformType Vi::TransformType\endlink.
 */
# define  KW__TT_ROT_EULER  "Rot__Euler_Ang"
/*!
 * S³owo kluczowe, które odpowiada warto¶ci \p TT_Rot_XYZ
 *  dla typu \link Vi::TransformType Vi::TransformType\endlink.
 */
# define  KW__TT_ROT_XYZ    "Rot__XYZ_Ang"
/*!
 * S³owo kluczowe, które odpowiada warto¶ci \p TT_Trans
 *  dla typu \link Vi::TransformType Vi::TransformType\endlink.
 */
# define  KW__TT_TRANS    "Translation"
/*!
 * S³owo kluczowe, które odpowiada warto¶ci \p TT_Scale
 *  dla typu \link Vi::TransformType Vi::TransformType\endlink.
 */
# define  KW__TT_SCALE    "Scale"

/*!
 * S³owo kluczowe, które poprzedza numer wspó³rzêdnej wektora
 * parametrów, który ma podlegaæ zmianom w ramach danej pozycji
 * interfejsu sterowania.
 */
# define  KW_COORDTYPE    "CoordNo"
/*!
 * S³owo kluczowe poprzedzaj±ce identyfikator macierzy reprezentowanej
 * przez klasê ViMatrix3f.\n
 * Identyfikator jest umieszczony po znaku ':'.
 */
# define  KW_MTXID      "MatrixID"
#endif
