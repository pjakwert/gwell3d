#ifndef VIERRORS_HH
#define VIERRORS_HH

/*!
 *  \file vierrors.hh
 *  \author Bogdan Kreczmer
 *  \date   2004.03.24
 *
 *  Plik zawiera numery i opis b³êdów jakie mog± byæ zg³oszone przez
 *  metody lub funkcje z bilioteki projektu VIONA.
 */

#include "strprintf.hh"



/*!
 * B³±d inicjalizacji iteratora \link DireTableIterator \endlink 
 * lub \link IndiTableIterator \endlink. Inicjalizacja indeksem 
 * spoza zakresu tablicy.
 */
#define ERRNUM_TABITER_BADINIT  1
/*!
 * Komunikat dla b³êdu inicjalizacji iteratora 
 * \link DireTableIterator \endlink 
 * lub \link IndiTableIterator \endlink. Inicjalizacja indeksem 
 * spoza zakresu tablicy.
 */
#define ERRMSG_TABITER_BADINIT  "Indeks iteratora zosta³ zanicjalizowany "\
                                "warto¶ci± spoza dozwolonego przedzia³u."


#define ERRNUM_FACE_VTXNO       2
#define ERRMSG_FACE_VTXNO "Numer wierzcho³ka ¶cianki dla bry³y wzorcowej "\
                   "\"%s\" jest wiêkszy ni¿ liczba jej wierzcho³ków (%i)."\
                   "Warto¶æ indeksu wynosila: %i."

/*!
 *  B³±d wyznaczenia wektora normalnego dla ¶cianki bry³y wzorcowej.
 */
#define ERRNUM_FACE_NORVCT      3
/*!
 *  Komunikat b³êdu wyznaczenia wektora normalnego dla ¶cianki bry³y
 *  wzorcowej.
 */
#define ERRMSG_FACE_NORVCT "Wektor normalny dla ¶cianki o indeksie %u "\
                   "bry³y wzorcowej %s nie mo¿e zostaæ wyliczony."\
                   " Przyczyn± mog± byæ zerowe wspó³rzêdne wierzcho³ków, "\
                   " lub ich po³o¿enienie na linii prostej."


/*!
 *  B³±d struktory danych. W bibliotece obiektów wzorcowych brak krawêdzi
 *  dla jednej ze ¶cianek.
 */
#define ERRNUM_FACE_NOEDGE      4
/*!
 *  Komunikat struktory danych. W bibliotece obiektów wzorcowych brak
 *  krawêdzi dla  dla jednej ze ¶cianek.
 */
#define ERRMSG_FACE_NOEDGE "Brak zdefiniowanej krawêdzi nr %u dla ¶cianki "\
                     " nr %u bry³y wzorcowej \"%s\"."\
          " Krawêd¼ powinna byæ poprowadzona miêdzy wierzcho³kami "\
          " %u oraz %u (%u, %u) (uwaga: numeracja wszêdzie od 1)."




/*!
 *  Indeks inicjalizacji iteratora dla ¶cianek trójk±tnych jest mniejszy ni¿
 *  2.
 */
#define ERRNUM_FACE_IDXBELOW2      5
/*!
 *  Komunikat b³ednej warto¶ci indeksu inicjalizacji iteratora dla ¶cianek 
 *  trójk±tnych> Jego warto¶æ jest mniejsza ni¿ 2.
 */
#define ERRMSG_FACE_IDXBELOW2 "Indeks inicjalizacji iteratora dla ¶cianki "\
          " trójk±tnej bry³y elementarnej jest mniejszy ni¿ 2 (wynosi %u)."




/*!
 *  Indeks inicjalizacji iteratora dla ¶cianek trójk±tnych jest mniejszy ni¿
 *  2.
 */
#define ERRNUM_ELEMEFACE_IDXBELOW2      6
/*!
 *  Komunikat b³ednej warto¶ci indeksu inicjalizacji iteratora dla ¶cianek 
 *  trójk±tnych> Jego warto¶æ jest mniejsza ni¿ 2.
 */
#define ERRMSG_ELEMEFACE_IDXBELOW2\
       "Indeks inicjalizacji iteratora dla ¶cianki "\
       " trójk±tnej bry³y elementarnej jest mniejszy ni¿ 2 (wynosi %u)."


/*!
 *  Numer b³êdu zg³aszany w momencie, gdy wczytane s³owo kluczowe jest
 *  inne ni¿ oczekiwane.
 *  Odpowiada mu komunikat zdefinowany przez sta³±
 *  \link vierrors.hh::ERRMSG_SYNTAX__UNEXPECTED_KEYWORD 
 *                     ERRMSG_SYNTAX__UNEXPECTED_KEYWORD\endlink.
 */
#define ERRNUM_SYNTAX__UNEXPECTED_KEYWORD      7
/*!
 *  Komunikat b³edu zg³aszanego w momencie przez funkcje czytania
 *  plików, gdy wczytane s³owo kluczowe jest
 *  inne ni¿ oczekiwane. 
 */ 
#define ERRMSG_SYNTAX__UNEXPECTED_KEYWORD\
          "Napotkane zosta³o s³owo kluczowe '%s', podczas gdy"\
          " oczekuje siê wyst±pienia s³owa '%s'."


/*!
 *  Numer b³êdu zg³aszany w momencie, gdy wczytane s³owo kluczowe jest
 *  inne ni¿ oczekiwane.
 *  Odpowiada mu komunikat zdefinowany przez sta³±
 *  \link vierrors.hh::ERRMSG_SYNTAX__UNEXPECTED_KEYWORD2
 *                     ERRMSG_SYNTAX__UNEXPECTED_KEYWORD2\endlink.
 */
#define ERRNUM_SYNTAX__UNEXPECTED_KEYWORD2      8
/*!
 *  Komunikat b³edu zg³aszanego w momencie przez funkcje czytania
 *  plików, gdy wczytane s³owo kluczowe jest
 *  inne ni¿ oczekiwane.
 */ 
#define ERRMSG_SYNTAX__UNEXPECTED_KEYWORD2\
          "Napotkane zosta³o s³owo kluczowe '%s', podczas gdy"\
          " oczekuje siê wyst±pienia jednego ze s³ów: '%s'."


/*!
 *  Numer b³êdu zg³aszany w momencie, gdy oczekiwane jest okre¶lone
 *  s³owo kluczowe napotkany natomiast zosta³ koniec pliku.
 *  Odpowiada mu komunikat zdefinowany przez sta³±
 *  \link vierrors.hh::ERRMSG_SYNTAX__UNEXPECTED_END
 *                     ERRMSG_SYNTAX__UNEXPECTED_END\endlink.
 */
#define ERRNUM_SYNTAX__UNEXPECTED_END      9
/*!
 *  Komunikat b³edu zg³aszanego w momencie przez funkcje czytania
 *  plików, gdy wczytane s³owo kluczowe jest
 *  inne ni¿ oczekiwane.
 */ 
#define ERRMSG_SYNTAX__UNEXPECTED_END\
          "Napotkane zosta³ koniec pliku, podczas gdy oczekiwanym "\
          "s³owem kluczowym jest '%s'."



/*!
 *  Numer b³êdu zg³aszany w momencie, gdy w opisie danego wêz³a
 *  (bry³y elementarnej lub pomocniczej) nie znaleziono opisu
 *  dla danej klasy.
 */
#define ERRNUM_SYNTAX__NO_CLASS_DESCR        10
/*!
 *  Komunikat b³edu zg³aszanego w momencie, gdy w opisie danego wêz³a
 *  (bry³y elementarnej lub pomocniczej) nie znaleziono opisu
 *  dla danej klasy.
 */ 
#define ERRMSG_SYNTAX__NO_CLASS_DESCR\
          "W opisie wêz³a nie zosta³ znaleziony opis dla klasy '%s'."

/*!
 *  Numer b³êdu zg³aszany w momencie, gdy przed prób± wyszukiwana bry³y
 *  wzorcowej w bibliotekach danej sceny, podany adres bry³y jest okazuje
 *  siê byæ ¼le zbudowany. Opis sk³adni adresu bry³y wzorcowej znajduje
 *  siê w opisie klasy ViPatteAddress.
 */
#define ERRNUM_SYNTAX__BAD_PATTE_ADDR        11
/*!
 *  Komunikat b³êdu zg³aszany w momencie, gdy przed prób± wyszukiwana bry³y
 *  wzorcowej w bibliotekach danej sceny, podany adres bry³y jest okazuje
 *  siê byæ ¼le zbudowany. Opis sk³adni adresu bry³y wzorcowej znajduje
 *  siê w opisie klasy ViPatteAddress.
 */
#define ERRMSG_SYNTAX__BAD_PATTE_ADDR   "Adres bry³y wzorcowej ma"\
           " niepoprawn± konstrukcjê. Analizowana postaæ adresu ma "\
           "postaæ: \"%s\""

/*!
 *  Numer b³êdu zg³aszanego w momencie, gdy podjêta jest próba wyszukiwana 
 *  bry³y
 *  wzorcowej w bibliotece, która nie istnieje w danej scenie.
 */
#define ERRNUM_PATTE__NO_SUCH_LIBRARY        12
/*!
 *  Komunikat b³êdu zg³aszanego w momencie, gdy podjêta jest próba 
 *  wyszukiwana
 *  bry³y wzorcowej w bibliotece, która nie istnieje w danej scenie.
 */
#define ERRMSG_PATTE__NO_SUCH_LIBRARY  "Podjêta zosta³a próba szukania "\
          " bry³y wzorcowej '%s' w bibliotece '%s', która nie istnieje "\
          "w danej scenie."

/*!
 *  Numer b³êdu zg³aszanego w momencie, gdy w danej biliotece brak jest 
 *  bry³y o podanej nazwie. Komunikat b³êdu zdefiniowany jest sta³±
 * \link vierrors.hh::ERRMSG_PATTE__NO_PATTE_POLYH 
 *                    ERRMSG_PATTE__NO_PATTE_POLYH\endlink
 */
#define ERRNUM_PATTE__NO_PATTE_POLYH        13
/*!
 *  Komunikat b³êdu zg³aszanego w momencie, gdy w danej biliotece brak jest 
 *  bry³y o podanej nazwie.
 */
#define ERRMSG_PATTE__NO_PATTE_POLYH  "W bibliotece '%s' brak jest bry³y "\
                              "'%s' typu '%s'"

/*!
 *  Numer b³êdu zg³aszanego w momencie, gdy dokonywana jest próba
 *  umieszczenia
 *  w modelu sceny na pierwszym poziomie obiektu, którego klasa nie jest
 *  klas± pochodn± wzglêdem klasy ViMultiPolyh. Komunikat b³êdu zdefiniowany
 *  jest sta³±
 * \link vierrors.hh::ERRMSG_HIER__TOP_NO_MULTI
 *                                ERRMSG_HIER__TOP_NO_MULTI\endlink
 */
#define ERRNUM_HIER__TOP_NO_MULTI      14
/*!
 *  Komunikat b³êdu zg³aszanego w momencie, gdy dokonywana jest próba
 *   umieszczenia
 *  w modelu sceny na pierwszym poziomie obiektu, którego klasa nie jest
 *  klas± pochodn± wzglêdem klasy ViMultiPolyh.
 */
#define ERRMSG_HIER__TOP_NO_MULTI  "Próba dodania na pierwszy poziom"\
     " modelu sceny obiektu '%s' klasy '%s', która nie jest klas±"\
     " pochodn± wzglêdem klasy ViMultiPolyh."

/*!
 * Numer b³êdu zg³aszane w momencie, gdy podany adres wêz³a w drzewie, nie
 * jest poprawnym adresem. Komunikat b³êdu zdefiniowany jest sta³±
 * \link vierrors.hh::ERRMSG_HIER__NO_VALID_ADDR
 *                                     ERRMSG_HIER__NO_VALID_ADDR\endlink
 */
#define ERRNUM_HIER__NO_VALID_ADDR    15
/*!
 * Komunikat b³êdu zg³aszane w momencie, gdy podany adres wêz³a w drzewie,
 * nie jest poprawnym adresem. 
 */
#define ERRMSG_HIER__NO_VALID_ADDR  "Adres wêz³a rodzica '%s' dla"\
                        " obiektu '%s' nie jest poprawnym adresm."

/*!
 * Numer b³êdu zg³aszane w momencie, gdy w pierwszej warstwie 
 * hierarchicznego modelu sceny znajduje siê wêze³, który jest obiektem
 * klasy nie wyprowadzonej
 * z klasy ViMultiPolyh. Pierwsza warstwa musi byæ zawsze list± obiektów
 * z³o¿onych.
 */
#define ERRNUM_HIER__NO_MULTI_AT_TOP    16
/*!
 * Komunikat b³êdu zg³aszane w momencie, gdy w pierwszej warstwie 
 * hierarchicznego modelu sceny znajduje siê wêze³, który jest obiektem
 * klasy nie wyprowadzonej z klasy ViMultiPolyh. Pierwsza warstwa musi 
 * byæ zawsze list± obiektów
 * z³o¿onych.
 */
#define ERRMSG_HIER__NO_MULTI_AT_TOP "W li¶cie bry³ z³o¿onych sceny jest "\
             "obiekt '%s' jest klasy '%s', która nie jest klas± pochodn± "\
             "klasy ViMultiPolyh."

/*!
 * Numer b³êdu zg³aszanego w przypadku, gdy nie powiod³a siê operacja 
 * przesuniêcia utworzonej bry³y z³o¿onej z listy tymczasowej do listy
 * sceny.\n
 * Zg³aszanemu b³edowi odpowiada mu komunikat zdefinowany przez sta³±
 *  \link vierrors.hh::ERRMSG_MULTI__MOVE2LIST_FAILED 
 *             ERRMSG_MULTI__MOVE2LIST_FAILED\endlink.
 */
#define ERRNUM_MULTI__MOVE2LIST_FAILED  17
/*!
 * Komunikat b³êdu zg³aszanego w przypadku, gdy nie powiod³a siê operacja 
 * przesuniêcia utworzonej bry³y z³o¿onej z listy tymczasowej do listy
 * sceny.
 */
#define ERRMSG_MULTI__MOVE2LIST_FAILED  "Nie powiod³o siê przesuniêcie "\
            "bry³y z³o¿onej z listy tymczasowej do listy bry³ sceny."

/*!
 * Numer b³êdu zg³aszany w przypadku niepowodzenia operacji otwarcia
 * do odczytu danego pliku.\n
 * Zg³aszanemu b³edowi odpowiada mu komunikat zdefinowany przez sta³±
 *  \link vierrors.hh::ERRMSG_FILE__OPEN2READ_FAILED
 *             ERRMSG_FILE__OPEN2READ_FAILED\endlink.
 */
#define ERRNUM_FILE__OPEN2READ_FAILED   18
/*!
 * Komunikat b³êdu zg³aszany w przypadku niepowodzenia operacji otwarcia
 * do odczytu danego pliku.
 */
#define ERRMSG_FILE__OPEN2READ_FAILED "Niepowiod³a siê operacja otwarcia "\
                      "do odczytu pliku '%s'."
/*!
 * Numer b³êdu zg³aszany w przypadku, gdy nie powiod³a siê operacja 
 * utworzenia obiektu danej klasy na podstawie jej opisu.
 * Prawdopodobn± przyczyn± jest brak implementacji procedury tworzenia
 * danego obiektu lub mniej prawdopodobne brak dostêpnej pamiêci.\n
 * Zg³aszanemu b³edowi odpowiada mu komunikat zdefinowany przez sta³±
 *  \link vierrors.hh::ERRMSG_POLYH__CREATE_FAILED
 *                     ERRMSG_POLYH__CREATE_FAILED\endlink
 */
#define ERRNUM_POLYH__CREATE_FAILED     19
/*!
 * Komunikat b³êdu zg³aszany w przypadku, gdy nie powiod³a siê operacja 
 * utworzenia obiektu danej klasy na podstawie jej opisu.
 * Prawdopodobn± przyczyn± jest brak dostêpnej pamiêci.
 */
#define ERRMSG_POLYH__CREATE_FAILED  "Utworzenie obiektu klasy '%s' nie "\
      "powiod³o siê. Prawdopodobn± przyczyn± jest brak procedury "\
      "tworzenia obiektu tej klasy lub mniej prawdopodobny brak"\
      " wystarczaj±cej ilo¶ci pamiêci."


/*!
 *  Numer b³êdu zg³aszany w przypadku, gdy nie powiod³o siê odczytanie
 *  z opisu wêz³a nazwy finalnej klasy.\n
 *  Zg³aszanemu b³edowi odpowiada mu komunikat zdefinowany przez sta³±
 *  \link vierrors.hh::ERRMSG_SYNTAX__NO_TOP_CLASS_NAME
 *                     ERRMSG_SYNTAX__NO_TOP_CLASS_NAME\endlink
 */
#define ERRNUM_SYNTAX__NO_TOP_CLASS_NAME    20
/*!
 *  Komunikat b³êdu zg³aszany w przypadku, gdy nie powiod³o siê odczytanie
 *  z opisu wêz³a nazwy finalnej klasy.
 */
#define ERRMSG_SYNTAX__NO_TOP_CLASS_NAME  "Nie powiod³ siê odczyt nazwy "\
              "klasy finalnej z opisu wêz³a:\n %s"


/*!
 * Numer b³êdu zg³aszany w przypadku, gdy w danej warstwie struktury
 * hierarchicznego modelu obiektu istnieje juz obiekt o podanej nazwie.\n
 * Zg³aszanemu b³edowi odpowiada mu komunikat zdefinowany przez sta³±
 *  \link vierrors.hh::ERRMSG_POLYH__IS_NODE_ALREADY
 *                     ERRMSG_POLYH__IS_NODE_ALREADY\endlink
 */
#define ERRNUM_POLYH__IS_NODE_ALREADY     21
/*!
 * Numer b³êdu zg³aszany w przypadku, gdy w danej warstwie struktury
 * hierarchicznego modelu obiektu istnieje juz obiekt o podanej nazwie.
 */
#define ERRMSG_POLYH__IS_NODE_ALREADY  "Niedozwolona proba dodania "\
     "obiektu o tej samej nazwie '%s' w tej samej lokalizacji '%s' (tzn. "\
     " istnieje juz bry³a elementarna o adresie '%s.%s')."

/*!
 * Numer b³êdu zg³aszany w przypadku, gdy w danej liscie bryl zlozonych
 * istnieje juz bryla o danej nazwie.
 *  Zg³aszanemu b³êdowi odpowiada mu komunikat zdefinowany przez sta³±
 *  \link vierrors.hh::ERRMSG_POLYH__IS_NODE_ALREADY
 *                     ERRMSG_POLYH__IS_NODE_ALREADY\endlink
 */
#define ERRNUM_POLYH__IS_MULTI_ALREADY     22
/*!
 * Komunikat b³êdu zg³aszany w przypadku, gdy w danej liscie bryl zlozonych
 * istnieje juz bryla o danej nazwie.
 */
#define ERRMSG_POLYH__IS_MULTI_ALREADY   "Niedozwolona operacja. "\
             " W li¶cie bry³ z³o¿onych istnieje "\
             "ju¿ bry³a o nazwie '%s'."

/*!
 *  Numer b³êdu zg³aszanego w przypadku, gdy w opisie pozycji interfejsu
 *  sterowania zostanie napotkany identyfikator rodzaju macierzy, który nie
 *  odpowiada ¿adnemu ze znanych typów. Wspomniany identyfikator okre¶la
 *  lokalizacjê macierzy w danej klasie.\n
 *  Zg³aszanemu b³êdowi odpowiada mu komunikat zdefinowany przez sta³±
 *  \link vierrors.hh::ERRMSG_POLYH__WRONG_MTXID
 *                     ERRMSG_POLYH__WRONG_MTXID\endlink
 */
#define ERRNUM_POLYH__WRONG_MTXID         23
/*!
 *  Komunikat b³êdu zg³aszanego w przypadku, gdy w opisie pozycji interfejsu
 *  sterowania zostanie napotkany identyfikator rodzaju macierzy, który nie
 *  odpowiada ¿adnemu ze znanych typów. Wspomniany identyfikator okre¶la
 *  lokalizacjê macierzy w danej klasie.
 */
#define ERRMSG_POLYH__WRONG_MTXID "Odczytany identyfikator '%i' rodzaju"\
         " macierzy transformacji nie odpowiada ¿adnemu ze znanych"\
         " identyfikatorów. Oczekiwane identyfikatory to: "\
         " %i (ViNTreeNode::_Transf2ParentCoord),"\
         " %i (ViElemePolyh::_Mtx_Patte2Eleme),"\
         " %i (ViElemePolyh::_Mtx_Eleme2Indiv)."


/*! 
 *  Numer b³êdu zg³aszanego w przypadku, gdy podany adres nie odpowiada
 *  ¿adnemu wêz³owi drzewa modeluj±cego scenê.\n
 *  Zg³aszanemu b³êdowi odpowiada mu komunikat zdefinowany przez sta³±
 *  \link vierrors.hh::ERRMSG_HIER__WRONG_ADDR
 *                     ERRMSG_HIER__WRONG_ADDR\endlink
 */
#define ERRNUM_HIER__WRONG_ADDR           24
/*! 
 *  Komunikat b³êdu zg³aszanego w przypadku, gdy podany adres nie 
 *  odpowiada ¿adnemu wêz³owi drzewa modeluj±cego scenê.
 */
#define ERRMSG_HIER__WRONG_ADDR "Adres '%s' nie odpowiada ¿adnemu"\
                       " wêz³owi w danym modelu sceny."

/*!
 *  Numer b³êdu zg³aszanego w przypadku, gdy przed wykonaniem danej
 *  operacji oczekiwane jest wcze¶niejsze znalezienie lub utworzenie
 *  obiektu klasy ViNTreeNode.\n
 * Odpowiada mu komunikat zdefinowany przez sta³±
 *  \link vierrors.hh::ERRMSG_INTERF__NO_POLYH_FOUND
 *                     ERRMSG_INTERF__NO_POLYH_FOUND\endlink
 */
#define ERRNUM_INTERF__NO_POLYH_FOUND    25
/*!
 *  Komunikat b³êdu zg³aszanego w przypadku, gdy przed wykonaniem danej
 *  operacji oczekiwane jest wcze¶niejsze znalezienie lub utworzenie
 *  obiektu klasy ViNTreeNode.
 */
#define ERRMSG_INTERF__NO_POLYH_FOUND "Brak obiektu obiektu klasy"\
              " ViNTreeNode przed wykonaniem operacji, która"\
              " wymaga jego istnienia."

/*! 
 * Numer b³êdu zg³aszanego w przypadku, gdy przy odczytywaniu
 * opisu interfejsu sterowania identyfikator macierzy nie jest
 * zgodny z identyfikatorem klasy obiektu, z którym ma byæ
 * skojarzona dana pozycja interfejsu.\n
 * Zg³aszanemu b³êdowi odpowiada mu komunikat zdefinowany przez sta³±
 *  \link vierrors.hh::ERRMSG_INTERF__IMPROPER_MTX
 *                     ERRMSG_INTERF__IMPROPER_MTX\endlink
 */
#define ERRNUM_INTERF__IMPROPER_MTX     26
/*! 
 * Komunika b³êdu zg³aszanego w przypadku, gdy przy odczytywaniu
 * opisu interfejsu sterowania identyfikator macierzy nie jest
 * zgodny z identyfikatorem klasy obiektu, z którym ma byæ
 * skojarzona dana pozycja interfejsu.
 */
#define ERRMSG_INTERF__IMPROPER_MTX  "Identyfikator rodzaju macierzy "\
   " ('%i') nie odpowiada klasie obiektu (identyfikator klasy: %i),"\
   " z którym ma byæ skojarzony dana pozycja interfejsu."

/*!
 * Numer b³êdu zg³aszanego w przypadku, gdy napis poddany konwersji
 * na typ \link Vi::TransformType Vi::TransformType\endlink nie odpowiada
 * ¿adnej z akceptowanych nazw.\n
 * Zg³aszanemu b³êdowi odpowiada mu komunikat zdefinowany przez sta³±
 *  \link vierrors.hh::ERRMSG_TRANSFTYPE__IMPROPER_NAME
 *                     ERRMSG_TRANSFTYPE__IMPROPER_NAME\endlink
 */
#define ERRNUM_TRANSFTYPE__IMPROPER_NAME  27
/*!
 * Komunikat b³êdu zg³aszanego w przypadku, gdy napis poddany konwersji
 * na typ \link Vi::TransformType Vi::TransformType\endlink nie odpowiada
 * ¿adnej z akceptowanych nazw.
 */
#define ERRMSG_TRANSFTYPE__IMPROPER_NAME  "Nazwa warto¶ci typu"\
    " TransformType nie odpowiada ¿adnej z oczekiwanych nazw."\
    " Otrzymano nazwê \"%s\", oczekuje siê jednej z nazw: %s"


/*!
 * Numer b³êdu zg³aszanego w przypadku, gdy napis poddany konwersji
 * na typ \link Vi::MetricUnit Vi::MetricUnit\endlink nie odpowiada
 * ¿adnej z akceptowanych nazw.\n
 * Zg³aszanemu b³êdowi odpowiada mu komunikat zdefinowany przez sta³±
 *  \link vierrors.hh::ERRMSG_METRICUNIT__IMPROPER_NAME
 *                     ERRMSG_METRICUNIT__IMPROPER_NAME\endlink
 */
#define ERRNUM_METRICUNIT__IMPROPER_NAME  28
/*!
 * Komunikat b³êdu zg³aszanego w przypadku, gdy napis poddany konwersji
 * na typ \link Vi::MetricUnit Vi::MetricUnit\endlink nie odpowiada
 * ¿adnej z akceptowanych nazw.
 */
#define ERRMSG_METRICUNIT__IMPROPER_NAME  "Nazwa warto¶ci typu"\
    " MetricUnit nie odpowiada ¿adnej z oczekiwanych nazw."\
    " Otrzymano nazwê \"%s\", oczekuje siê jednej z nazw: %s"



/*!
 * Numer b³êdu zg³aszanego w przypadku, gdy napis poddany konwersji
 * na typ \link Vi::Coord3DType Vi::Coord3DType\endlink nie odpowiada
 * ¿adnej z akceptowanych nazw.\n
 * Zg³aszanemu b³êdowi odpowiada mu komunikat zdefinowany przez sta³±
 *  \link vierrors.hh::ERRMSG_COORD3DTYPE__IMPROPER_NAME
 *                     ERRMSG_COORD3DTYPE__IMPROPER_NAME\endlink
 */
#define ERRNUM_COORD3DTYPE__IMPROPER_NAME  29
/*!
 * Komunikat b³êdu zg³aszanego w przypadku, gdy napis poddany konwersji
 * na typ \link Vi::Coord3DType Vi::Coord3DType\endlink nie odpowiada
 * ¿adnej z akceptowanych nazw.
 */
#define ERRMSG_COORD3DTYPE__IMPROPER_NAME  "Nazwa warto¶ci typu"\
    " Coord3DType nie odpowiada ¿adnej z oczekiwanych nazw."\
    " Otrzymano nazwê \"%s\", oczekuje siê jednej z nazw: %s"



#endif
