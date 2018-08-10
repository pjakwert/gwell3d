#ifndef VI_KEYWORDS_HH
#define VI_KEYWORDS_HH

/*!
 * \file vi-keywords.hh
 * Plik zawiera definicj� sta�ych reprezentuj�cych poszczeg�lne s�owa
 * kluczowe wykorzystywane przy zapisie i odczycie opis�w bry� wzorcowych,
 * elementarnych i z�o�onych. 
 * \author Bogdan Kreczmer
 * \date   2004.06
 */

/*!
 *  S�owo kluczowe rozpoczynaj�ce sekcj� opisu bry�y z�o�onej.
 */
# define  KW_MULTIPOLYH_BEGIN   "MultiPolyh__Begin"
/*!
 *  S�owo kluczowe ko�cz�ce sekcj� opisu bry�y z�o�onej.
 */
# define  KW_MULTIPOLYH_END     "MultiPolyh__End"
/*!
 *  S�owo kluczowe opisy bry�y, po kt�rym podana jest indywidualna 
 *  nazwa danego w�z�a (bry�y sk�adowej)
 *  danej struktury wielodrzewa.\n
 *  Format zapisu:
 *  \verbatim
        NodeName:  nazwa_w�z�a
    \endverbatim
 *  Opis specyfikacji nazwy znajduje si�  w sekcji \ref  nazwy_bryl 
 *  "Nazwy i bry�".
 */
# define  KW_INDIVNAME        "NodeName"
/*!
 *  S�owo kluczowe poprzedzaj�ce adres danego w�z�a.
 *  Adres w�z�a wyst�puje po znaku ':', kt�ry wpisywany jest
 *  bezpo�rednio po tym s�owie kluczowy.
 */
# define  KW_NODEADDRESS      "NodeAddress"
/*!
 *  S�owo kluczowe poprzedzaj�ce opis macierzy transformacji
 *  uk�adu wsp�rz�dnych lokalnych danego w�z�a 
 *  do uk�adu wsp�rz�dnych jego rodzica rodzica.
 */
# define  KW_TRANSF2PARENT    "Transf_Node2Parent"
/*!
 *  S�owo kluczowe poprzedzaj�ce opis warto�ci k�t�w
 *  dla danej tranformacji.
 */
# define  KW_ANGLES           "Angles"
/*!
 *  S�owo kluczowe, kt�re w opisie k�t�w rotacji okre�la
 *  ich typ. W tym przypadku odnosi si� ono do k�t�w Eulera
 *  (\e ZYZ).
 */
# define  KW_ANG_EULER        "Euler"
/*!
 *  S�owo kluczowe, kt�re w opisie k�t�w rotacji okre�la
 *  ich typ. W tym przypadku odnosi si� ono do k�t�w \e XYZ,
 *  tzn. pierwszy obr�w wok� osi \f$ OX\f$, drugi wok� osi
 *  \f$ OY'\$, trzeci wok� osi \f$ OZ''\f$.
 */
# define  KW_ANG_XYZ          "XYZ"
/*!
 * Wykorzystywane jest przy zapisie warto�ci k�t�w.
 * Wskazuje ono, �e warto�ci k�t�w wyra�one s� w radianach.
 */
# define  KW_ANG_RAD          "Rad"
/*!
 * Wykorzystywane jest przy zapisie warto�ci k�t�w.
 * Wskazuje ono, �e warto�ci k�t�w wyra�one s� w stopniach.
 */
# define  KW_ANG_DEG          "Deg"
/*!
 * Definiuje s�owo kluczowe poprzedzaj�ce warto�� wektora translacji
 * w opisie macierzy transformacji uk�adu wsp�rz�dnych.
 */ 
# define  KW_TRANSLATION      "Translation"
/*!
 * Definiuje s�owo kluczowe poprzedzaj�ce warto�� wektora skali
 * w opisie macierzy transformacji uk�adu wsp�rz�dnych.
 */ 
# define  KW_SCALE            "Scale"
/*!
 * S�owo kluczowe otwieraj�ce sekcj� opisu w�z�a.
 */
# define  KW_NODE             "Node__Begin"
/*!
 * S�owo kluczowe zamykaj�ce sekcj� opisu w�z�a.
 */
# define  KW_ENDNODE          "Node__End"
/*!
 * S�owo kluczowe otwieraj�ce sekcj� opisu klasy.
 * Sekcja ta znajduje si� wewn�trz sekcji opisu w�z�a.
 */
# define  KW_BEGIN_DERIVSEC   "ClassSection__Begin"
/*!
 * S�owo kluczowe zamykaj�ce sekcj� opisu klasy.
 * Sekcja ta znajduje si� wewn�trz sekcji opisu w�z�a.
 */
# define  KW_END_DERIVSEC     "ClassSection__End"
/*!
 * S�owo kluczowe poprzedzaj�ce nazw� bry�y wzorcowej.
 * Nazwa wyst�puje po znaku ':'.
 * Niniejsze s�owo kluczowe wykorzystywane jest w opisie 
 * bry�y elementarnej.
 */
# define  KW_PATTNAME         "PatternPolyhedronName"
/*!
 *  S�owo kluczowe poprzedza opis macierzy transformacji
 *  z uk�adu wsp�rz�dnych bry�y wzorcowej do uk�adu wsp�rz�dnych
 *  bry�y elementarnej.
 */
# define  KW_PATTE2ELEME      "Transf_Patte2Eleme"
/*!
 *  S�owo kluczowe poprzedza opis macierzy transformacji
 *  z uk�adu wsp�rz�dnych bry�y elementarnej do jej 
 *  indywidualnego uk�adu wsp�rz�dnych.
 */
# define  KW_ELEME2INDIV      "Transf_Eleme2Indiv"


/*!
 *  S�owo kluczowe otwieraj�ce sekcj� interfejsu sterowania w 
 *  opisie bry�y z�o�onej.
 */
# define  KW_CTRLINTERFACE_BEGIN "CtrlInterface__Begin"
/*!
 *  S�owo kluczowe zamykaj�ce sekcj� interfejsu sterowania w 
 *  opisie bry�y z�o�onej.
 */
# define  KW_CTRLINTERFACE_END   "CtrlInterface__End"
/*!
 *  S�owo kluczowe otwieraj�ce sekcj� danej pozycji interfejsu 
 *  sterowania w opisie bry�y z�o�onej.
 */
# define  KW_CTRLINTERFACEITEM_BEGIN "InterfaceItem__Begin"
/*!
 *  S�owo kluczowe zamykaj�ce sekcj� danej pozycji interfejsu 
 *  sterowania w opisie bry�y z�o�onej.
 */
# define  KW_CTRLINTERFACEITEM_END "InterfaceItem__End"

/*!
 * S�owo kluczowe poprzedza numer identyfikatora dla obiektu
 * danej sturktury (zwykle chodzi o identyfikator umo�liwiaj�cy
 * odnalezienie ��danego elementu w li�cie).
 * Identyfikator umieszczany jest po znaku ':'.
 */
# define  KW_KEYID   "KeyID"
/*!
 * S�owo kluczowe poprzedza nazw� identyfikuj�c� obiekt
 * danej sturktury (zwykle chodzi o identyfikator umo�liwiaj�cy
 * odnalezienie ��danego elementu w li�cie).  Identyfikator umieszczany 
 * jest po znaku ':'.
 */
# define  KW_KEYNAME "KeyName"
/*!
 * S�owo poprzedza komentarz, kt�ry przewidziany jest w tworzonym
 * dialogu, np. dialogu sterowania danym prametrem transformacji.
 */
# define  KW_COMMENT "Comment"
/*!
 * S�owo kluczowe poprzedzaj�ce warto�� parametru w 
 * opisie interfejsu sterowania bry�� z�o�on�.
 */
# define  KW_VALUE   "Value"
/*!
 * S�owo kluczowe poprzedza warto�� dolnego ograniczenia parametru
 * zadawanego poprzez interfejs sterowania.
 * Wspomniana warto�c wyst�puje po znaku ':'.
 */
# define  KW_MIN     "Min"
/*!
 * S�owo kluczowe poprzedza warto�� g�rnego ograniczenia parametru
 * zadawanego poprzez interfejs sterowania.
 * Wspomniana warto�c wyst�puje po znaku ':'.
 */
# define  KW_MAX     "Max"
/*!
 *  S�owo kluczowe poprzedzaj�ce nazw� okre�laj�c� kolejno��
 *  rotacji wzgl�dem translacji.\n
 *  Wspomniany �a�cuch wyst�puje po znaku ':'.
 */
# define  KW_TRANSORDER   "TransOrder"




/*!
 *  S�owo kluczowe, kt�re odpowiada warto�ci \p TO_After
 *  dla typu \link matrixh3f.hh::TransOrder TransOrder\endlink.
 */
# define  KW__TO_AFTER    "TAfterR"
/*!
 *  S�owo kluczowe, kt�re odpowiada warto�ci \p TO_Before
 *  dla typu \link matrixh3f.hh::TransOrder TransOrder\endlink.
 */
# define  KW__TO_BEFORE   "TBeforeR"
/*!
 * S�owo kluczowe poprzedzaj�ce nazw� jednostki miary danej
 * wielko�ci.\n
 * Wspomniana nazwa wyst�puje po znaku ':'.
 */
# define  KW_UNIT  "Unit"





/*!
 * S�owo kluczowe, kt�re odpowiada warto�ci \p TU_NONE
 *  dla typu \link Vi::MetricUnit Vi::MetricUnit\endlink.
 */
# define  KW__MU_NONE  "None"
/*!
 * S�owo kluczowe, kt�re odpowiada warto�ci \p TU_DEG
 *  dla typu \link Vi::MetricUnit Vi::MetricUnit\endlink.
 */
# define  KW__MU_DEG  "Deg"
/*!
 * S�owo kluczowe, kt�re odpowiada warto�ci \p TU_RAD
 *  dla typu \link Vi::MetricUnit Vi::MetricUnit\endlink.
 */
# define  KW__MU_RAD  "Rad"
/*!
 * S�owo kluczowe, kt�re odpowiada warto�ci \p TU_CEN
 *  dla typu \link Vi::MetricUnit Vi::MetricUnit\endlink.
 */
# define  KW__MU_CEN  "Centimeter"
/*!
 * S�owo kluczowe, kt�re odpowiada warto�ci \p TU_MET
 *  dla typu \link Vi::MetricUnit Vi::MetricUnit\endlink.
 */
# define  KW__MU_MET  "Meter"
/*!
 * S�owo kluczowe, kt�re odpowiada warto�ci \p TU_MIL
 *  dla typu \link Vi::MetricUnit Vi::MetricUnit\endlink.
 */
# define  KW__MU_MIL  "Millimeter"


/*!
 *  S�owo kluczowe poprzedza okre�lenie typu transformacji,
 *  jaka jest zwi�zana z dan� pozycj� interfejsu sterownia.
 */
# define  KW_TRANSFTYPE   "TransfType"


/*!
 * S�owo kluczowe, kt�re odpowiada warto�ci \p TT_Rot_Euler
 *  dla typu \link Vi::TransformType Vi::TransformType\endlink.
 */
# define  KW__TT_ROT_EULER  "Rot__Euler_Ang"
/*!
 * S�owo kluczowe, kt�re odpowiada warto�ci \p TT_Rot_XYZ
 *  dla typu \link Vi::TransformType Vi::TransformType\endlink.
 */
# define  KW__TT_ROT_XYZ    "Rot__XYZ_Ang"
/*!
 * S�owo kluczowe, kt�re odpowiada warto�ci \p TT_Trans
 *  dla typu \link Vi::TransformType Vi::TransformType\endlink.
 */
# define  KW__TT_TRANS    "Translation"
/*!
 * S�owo kluczowe, kt�re odpowiada warto�ci \p TT_Scale
 *  dla typu \link Vi::TransformType Vi::TransformType\endlink.
 */
# define  KW__TT_SCALE    "Scale"

/*!
 * S�owo kluczowe, kt�re poprzedza numer wsp�rz�dnej wektora
 * parametr�w, kt�ry ma podlega� zmianom w ramach danej pozycji
 * interfejsu sterowania.
 */
# define  KW_COORDTYPE    "CoordNo"
/*!
 * S�owo kluczowe poprzedzaj�ce identyfikator macierzy reprezentowanej
 * przez klas� ViMatrix3f.\n
 * Identyfikator jest umieszczony po znaku ':'.
 */
# define  KW_MTXID      "MatrixID"
#endif
