#ifndef VIERRORS_HH
#define VIERRORS_HH

/*!
 *  \file vierrors.hh
 *  \author Bogdan Kreczmer
 *  \date   2004.03.24
 *
 *  Plik zawiera numery i opis b��d�w jakie mog� by� zg�oszone przez
 *  metody lub funkcje z bilioteki projektu VIONA.
 */

#include "strprintf.hh"



/*!
 * B��d inicjalizacji iteratora \link DireTableIterator \endlink 
 * lub \link IndiTableIterator \endlink. Inicjalizacja indeksem 
 * spoza zakresu tablicy.
 */
#define ERRNUM_TABITER_BADINIT  1
/*!
 * Komunikat dla b��du inicjalizacji iteratora 
 * \link DireTableIterator \endlink 
 * lub \link IndiTableIterator \endlink. Inicjalizacja indeksem 
 * spoza zakresu tablicy.
 */
#define ERRMSG_TABITER_BADINIT  "Indeks iteratora zosta� zanicjalizowany "\
                                "warto�ci� spoza dozwolonego przedzia�u."


#define ERRNUM_FACE_VTXNO       2
#define ERRMSG_FACE_VTXNO "Numer wierzcho�ka �cianki dla bry�y wzorcowej "\
                   "\"%s\" jest wi�kszy ni� liczba jej wierzcho�k�w (%i)."\
                   "Warto�� indeksu wynosila: %i."

/*!
 *  B��d wyznaczenia wektora normalnego dla �cianki bry�y wzorcowej.
 */
#define ERRNUM_FACE_NORVCT      3
/*!
 *  Komunikat b��du wyznaczenia wektora normalnego dla �cianki bry�y
 *  wzorcowej.
 */
#define ERRMSG_FACE_NORVCT "Wektor normalny dla �cianki o indeksie %u "\
                   "bry�y wzorcowej %s nie mo�e zosta� wyliczony."\
                   " Przyczyn� mog� by� zerowe wsp�rz�dne wierzcho�k�w, "\
                   " lub ich po�o�enienie na linii prostej."


/*!
 *  B��d struktory danych. W bibliotece obiekt�w wzorcowych brak kraw�dzi
 *  dla jednej ze �cianek.
 */
#define ERRNUM_FACE_NOEDGE      4
/*!
 *  Komunikat struktory danych. W bibliotece obiekt�w wzorcowych brak
 *  kraw�dzi dla  dla jednej ze �cianek.
 */
#define ERRMSG_FACE_NOEDGE "Brak zdefiniowanej kraw�dzi nr %u dla �cianki "\
                     " nr %u bry�y wzorcowej \"%s\"."\
          " Kraw�d� powinna by� poprowadzona mi�dzy wierzcho�kami "\
          " %u oraz %u (%u, %u) (uwaga: numeracja wsz�dzie od 1)."




/*!
 *  Indeks inicjalizacji iteratora dla �cianek tr�jk�tnych jest mniejszy ni�
 *  2.
 */
#define ERRNUM_FACE_IDXBELOW2      5
/*!
 *  Komunikat b�ednej warto�ci indeksu inicjalizacji iteratora dla �cianek 
 *  tr�jk�tnych> Jego warto�� jest mniejsza ni� 2.
 */
#define ERRMSG_FACE_IDXBELOW2 "Indeks inicjalizacji iteratora dla �cianki "\
          " tr�jk�tnej bry�y elementarnej jest mniejszy ni� 2 (wynosi %u)."




/*!
 *  Indeks inicjalizacji iteratora dla �cianek tr�jk�tnych jest mniejszy ni�
 *  2.
 */
#define ERRNUM_ELEMEFACE_IDXBELOW2      6
/*!
 *  Komunikat b�ednej warto�ci indeksu inicjalizacji iteratora dla �cianek 
 *  tr�jk�tnych> Jego warto�� jest mniejsza ni� 2.
 */
#define ERRMSG_ELEMEFACE_IDXBELOW2\
       "Indeks inicjalizacji iteratora dla �cianki "\
       " tr�jk�tnej bry�y elementarnej jest mniejszy ni� 2 (wynosi %u)."


/*!
 *  Numer b��du zg�aszany w momencie, gdy wczytane s�owo kluczowe jest
 *  inne ni� oczekiwane.
 *  Odpowiada mu komunikat zdefinowany przez sta��
 *  \link vierrors.hh::ERRMSG_SYNTAX__UNEXPECTED_KEYWORD 
 *                     ERRMSG_SYNTAX__UNEXPECTED_KEYWORD\endlink.
 */
#define ERRNUM_SYNTAX__UNEXPECTED_KEYWORD      7
/*!
 *  Komunikat b�edu zg�aszanego w momencie przez funkcje czytania
 *  plik�w, gdy wczytane s�owo kluczowe jest
 *  inne ni� oczekiwane. 
 */ 
#define ERRMSG_SYNTAX__UNEXPECTED_KEYWORD\
          "Napotkane zosta�o s�owo kluczowe '%s', podczas gdy"\
          " oczekuje si� wyst�pienia s�owa '%s'."


/*!
 *  Numer b��du zg�aszany w momencie, gdy wczytane s�owo kluczowe jest
 *  inne ni� oczekiwane.
 *  Odpowiada mu komunikat zdefinowany przez sta��
 *  \link vierrors.hh::ERRMSG_SYNTAX__UNEXPECTED_KEYWORD2
 *                     ERRMSG_SYNTAX__UNEXPECTED_KEYWORD2\endlink.
 */
#define ERRNUM_SYNTAX__UNEXPECTED_KEYWORD2      8
/*!
 *  Komunikat b�edu zg�aszanego w momencie przez funkcje czytania
 *  plik�w, gdy wczytane s�owo kluczowe jest
 *  inne ni� oczekiwane.
 */ 
#define ERRMSG_SYNTAX__UNEXPECTED_KEYWORD2\
          "Napotkane zosta�o s�owo kluczowe '%s', podczas gdy"\
          " oczekuje si� wyst�pienia jednego ze s��w: '%s'."


/*!
 *  Numer b��du zg�aszany w momencie, gdy oczekiwane jest okre�lone
 *  s�owo kluczowe napotkany natomiast zosta� koniec pliku.
 *  Odpowiada mu komunikat zdefinowany przez sta��
 *  \link vierrors.hh::ERRMSG_SYNTAX__UNEXPECTED_END
 *                     ERRMSG_SYNTAX__UNEXPECTED_END\endlink.
 */
#define ERRNUM_SYNTAX__UNEXPECTED_END      9
/*!
 *  Komunikat b�edu zg�aszanego w momencie przez funkcje czytania
 *  plik�w, gdy wczytane s�owo kluczowe jest
 *  inne ni� oczekiwane.
 */ 
#define ERRMSG_SYNTAX__UNEXPECTED_END\
          "Napotkane zosta� koniec pliku, podczas gdy oczekiwanym "\
          "s�owem kluczowym jest '%s'."



/*!
 *  Numer b��du zg�aszany w momencie, gdy w opisie danego w�z�a
 *  (bry�y elementarnej lub pomocniczej) nie znaleziono opisu
 *  dla danej klasy.
 */
#define ERRNUM_SYNTAX__NO_CLASS_DESCR        10
/*!
 *  Komunikat b�edu zg�aszanego w momencie, gdy w opisie danego w�z�a
 *  (bry�y elementarnej lub pomocniczej) nie znaleziono opisu
 *  dla danej klasy.
 */ 
#define ERRMSG_SYNTAX__NO_CLASS_DESCR\
          "W opisie w�z�a nie zosta� znaleziony opis dla klasy '%s'."

/*!
 *  Numer b��du zg�aszany w momencie, gdy przed pr�b� wyszukiwana bry�y
 *  wzorcowej w bibliotekach danej sceny, podany adres bry�y jest okazuje
 *  si� by� �le zbudowany. Opis sk�adni adresu bry�y wzorcowej znajduje
 *  si� w opisie klasy ViPatteAddress.
 */
#define ERRNUM_SYNTAX__BAD_PATTE_ADDR        11
/*!
 *  Komunikat b��du zg�aszany w momencie, gdy przed pr�b� wyszukiwana bry�y
 *  wzorcowej w bibliotekach danej sceny, podany adres bry�y jest okazuje
 *  si� by� �le zbudowany. Opis sk�adni adresu bry�y wzorcowej znajduje
 *  si� w opisie klasy ViPatteAddress.
 */
#define ERRMSG_SYNTAX__BAD_PATTE_ADDR   "Adres bry�y wzorcowej ma"\
           " niepoprawn� konstrukcj�. Analizowana posta� adresu ma "\
           "posta�: \"%s\""

/*!
 *  Numer b��du zg�aszanego w momencie, gdy podj�ta jest pr�ba wyszukiwana 
 *  bry�y
 *  wzorcowej w bibliotece, kt�ra nie istnieje w danej scenie.
 */
#define ERRNUM_PATTE__NO_SUCH_LIBRARY        12
/*!
 *  Komunikat b��du zg�aszanego w momencie, gdy podj�ta jest pr�ba 
 *  wyszukiwana
 *  bry�y wzorcowej w bibliotece, kt�ra nie istnieje w danej scenie.
 */
#define ERRMSG_PATTE__NO_SUCH_LIBRARY  "Podj�ta zosta�a pr�ba szukania "\
          " bry�y wzorcowej '%s' w bibliotece '%s', kt�ra nie istnieje "\
          "w danej scenie."

/*!
 *  Numer b��du zg�aszanego w momencie, gdy w danej biliotece brak jest 
 *  bry�y o podanej nazwie. Komunikat b��du zdefiniowany jest sta��
 * \link vierrors.hh::ERRMSG_PATTE__NO_PATTE_POLYH 
 *                    ERRMSG_PATTE__NO_PATTE_POLYH\endlink
 */
#define ERRNUM_PATTE__NO_PATTE_POLYH        13
/*!
 *  Komunikat b��du zg�aszanego w momencie, gdy w danej biliotece brak jest 
 *  bry�y o podanej nazwie.
 */
#define ERRMSG_PATTE__NO_PATTE_POLYH  "W bibliotece '%s' brak jest bry�y "\
                              "'%s' typu '%s'"

/*!
 *  Numer b��du zg�aszanego w momencie, gdy dokonywana jest pr�ba
 *  umieszczenia
 *  w modelu sceny na pierwszym poziomie obiektu, kt�rego klasa nie jest
 *  klas� pochodn� wzgl�dem klasy ViMultiPolyh. Komunikat b��du zdefiniowany
 *  jest sta��
 * \link vierrors.hh::ERRMSG_HIER__TOP_NO_MULTI
 *                                ERRMSG_HIER__TOP_NO_MULTI\endlink
 */
#define ERRNUM_HIER__TOP_NO_MULTI      14
/*!
 *  Komunikat b��du zg�aszanego w momencie, gdy dokonywana jest pr�ba
 *   umieszczenia
 *  w modelu sceny na pierwszym poziomie obiektu, kt�rego klasa nie jest
 *  klas� pochodn� wzgl�dem klasy ViMultiPolyh.
 */
#define ERRMSG_HIER__TOP_NO_MULTI  "Pr�ba dodania na pierwszy poziom"\
     " modelu sceny obiektu '%s' klasy '%s', kt�ra nie jest klas�"\
     " pochodn� wzgl�dem klasy ViMultiPolyh."

/*!
 * Numer b��du zg�aszane w momencie, gdy podany adres w�z�a w drzewie, nie
 * jest poprawnym adresem. Komunikat b��du zdefiniowany jest sta��
 * \link vierrors.hh::ERRMSG_HIER__NO_VALID_ADDR
 *                                     ERRMSG_HIER__NO_VALID_ADDR\endlink
 */
#define ERRNUM_HIER__NO_VALID_ADDR    15
/*!
 * Komunikat b��du zg�aszane w momencie, gdy podany adres w�z�a w drzewie,
 * nie jest poprawnym adresem. 
 */
#define ERRMSG_HIER__NO_VALID_ADDR  "Adres w�z�a rodzica '%s' dla"\
                        " obiektu '%s' nie jest poprawnym adresm."

/*!
 * Numer b��du zg�aszane w momencie, gdy w pierwszej warstwie 
 * hierarchicznego modelu sceny znajduje si� w�ze�, kt�ry jest obiektem
 * klasy nie wyprowadzonej
 * z klasy ViMultiPolyh. Pierwsza warstwa musi by� zawsze list� obiekt�w
 * z�o�onych.
 */
#define ERRNUM_HIER__NO_MULTI_AT_TOP    16
/*!
 * Komunikat b��du zg�aszane w momencie, gdy w pierwszej warstwie 
 * hierarchicznego modelu sceny znajduje si� w�ze�, kt�ry jest obiektem
 * klasy nie wyprowadzonej z klasy ViMultiPolyh. Pierwsza warstwa musi 
 * by� zawsze list� obiekt�w
 * z�o�onych.
 */
#define ERRMSG_HIER__NO_MULTI_AT_TOP "W li�cie bry� z�o�onych sceny jest "\
             "obiekt '%s' jest klasy '%s', kt�ra nie jest klas� pochodn� "\
             "klasy ViMultiPolyh."

/*!
 * Numer b��du zg�aszanego w przypadku, gdy nie powiod�a si� operacja 
 * przesuni�cia utworzonej bry�y z�o�onej z listy tymczasowej do listy
 * sceny.\n
 * Zg�aszanemu b�edowi odpowiada mu komunikat zdefinowany przez sta��
 *  \link vierrors.hh::ERRMSG_MULTI__MOVE2LIST_FAILED 
 *             ERRMSG_MULTI__MOVE2LIST_FAILED\endlink.
 */
#define ERRNUM_MULTI__MOVE2LIST_FAILED  17
/*!
 * Komunikat b��du zg�aszanego w przypadku, gdy nie powiod�a si� operacja 
 * przesuni�cia utworzonej bry�y z�o�onej z listy tymczasowej do listy
 * sceny.
 */
#define ERRMSG_MULTI__MOVE2LIST_FAILED  "Nie powiod�o si� przesuni�cie "\
            "bry�y z�o�onej z listy tymczasowej do listy bry� sceny."

/*!
 * Numer b��du zg�aszany w przypadku niepowodzenia operacji otwarcia
 * do odczytu danego pliku.\n
 * Zg�aszanemu b�edowi odpowiada mu komunikat zdefinowany przez sta��
 *  \link vierrors.hh::ERRMSG_FILE__OPEN2READ_FAILED
 *             ERRMSG_FILE__OPEN2READ_FAILED\endlink.
 */
#define ERRNUM_FILE__OPEN2READ_FAILED   18
/*!
 * Komunikat b��du zg�aszany w przypadku niepowodzenia operacji otwarcia
 * do odczytu danego pliku.
 */
#define ERRMSG_FILE__OPEN2READ_FAILED "Niepowiod�a si� operacja otwarcia "\
                      "do odczytu pliku '%s'."
/*!
 * Numer b��du zg�aszany w przypadku, gdy nie powiod�a si� operacja 
 * utworzenia obiektu danej klasy na podstawie jej opisu.
 * Prawdopodobn� przyczyn� jest brak implementacji procedury tworzenia
 * danego obiektu lub mniej prawdopodobne brak dost�pnej pami�ci.\n
 * Zg�aszanemu b�edowi odpowiada mu komunikat zdefinowany przez sta��
 *  \link vierrors.hh::ERRMSG_POLYH__CREATE_FAILED
 *                     ERRMSG_POLYH__CREATE_FAILED\endlink
 */
#define ERRNUM_POLYH__CREATE_FAILED     19
/*!
 * Komunikat b��du zg�aszany w przypadku, gdy nie powiod�a si� operacja 
 * utworzenia obiektu danej klasy na podstawie jej opisu.
 * Prawdopodobn� przyczyn� jest brak dost�pnej pami�ci.
 */
#define ERRMSG_POLYH__CREATE_FAILED  "Utworzenie obiektu klasy '%s' nie "\
      "powiod�o si�. Prawdopodobn� przyczyn� jest brak procedury "\
      "tworzenia obiektu tej klasy lub mniej prawdopodobny brak"\
      " wystarczaj�cej ilo�ci pami�ci."


/*!
 *  Numer b��du zg�aszany w przypadku, gdy nie powiod�o si� odczytanie
 *  z opisu w�z�a nazwy finalnej klasy.\n
 *  Zg�aszanemu b�edowi odpowiada mu komunikat zdefinowany przez sta��
 *  \link vierrors.hh::ERRMSG_SYNTAX__NO_TOP_CLASS_NAME
 *                     ERRMSG_SYNTAX__NO_TOP_CLASS_NAME\endlink
 */
#define ERRNUM_SYNTAX__NO_TOP_CLASS_NAME    20
/*!
 *  Komunikat b��du zg�aszany w przypadku, gdy nie powiod�o si� odczytanie
 *  z opisu w�z�a nazwy finalnej klasy.
 */
#define ERRMSG_SYNTAX__NO_TOP_CLASS_NAME  "Nie powiod� si� odczyt nazwy "\
              "klasy finalnej z opisu w�z�a:\n %s"


/*!
 * Numer b��du zg�aszany w przypadku, gdy w danej warstwie struktury
 * hierarchicznego modelu obiektu istnieje juz obiekt o podanej nazwie.\n
 * Zg�aszanemu b�edowi odpowiada mu komunikat zdefinowany przez sta��
 *  \link vierrors.hh::ERRMSG_POLYH__IS_NODE_ALREADY
 *                     ERRMSG_POLYH__IS_NODE_ALREADY\endlink
 */
#define ERRNUM_POLYH__IS_NODE_ALREADY     21
/*!
 * Numer b��du zg�aszany w przypadku, gdy w danej warstwie struktury
 * hierarchicznego modelu obiektu istnieje juz obiekt o podanej nazwie.
 */
#define ERRMSG_POLYH__IS_NODE_ALREADY  "Niedozwolona proba dodania "\
     "obiektu o tej samej nazwie '%s' w tej samej lokalizacji '%s' (tzn. "\
     " istnieje juz bry�a elementarna o adresie '%s.%s')."

/*!
 * Numer b��du zg�aszany w przypadku, gdy w danej liscie bryl zlozonych
 * istnieje juz bryla o danej nazwie.
 *  Zg�aszanemu b��dowi odpowiada mu komunikat zdefinowany przez sta��
 *  \link vierrors.hh::ERRMSG_POLYH__IS_NODE_ALREADY
 *                     ERRMSG_POLYH__IS_NODE_ALREADY\endlink
 */
#define ERRNUM_POLYH__IS_MULTI_ALREADY     22
/*!
 * Komunikat b��du zg�aszany w przypadku, gdy w danej liscie bryl zlozonych
 * istnieje juz bryla o danej nazwie.
 */
#define ERRMSG_POLYH__IS_MULTI_ALREADY   "Niedozwolona operacja. "\
             " W li�cie bry� z�o�onych istnieje "\
             "ju� bry�a o nazwie '%s'."

/*!
 *  Numer b��du zg�aszanego w przypadku, gdy w opisie pozycji interfejsu
 *  sterowania zostanie napotkany identyfikator rodzaju macierzy, kt�ry nie
 *  odpowiada �adnemu ze znanych typ�w. Wspomniany identyfikator okre�la
 *  lokalizacj� macierzy w danej klasie.\n
 *  Zg�aszanemu b��dowi odpowiada mu komunikat zdefinowany przez sta��
 *  \link vierrors.hh::ERRMSG_POLYH__WRONG_MTXID
 *                     ERRMSG_POLYH__WRONG_MTXID\endlink
 */
#define ERRNUM_POLYH__WRONG_MTXID         23
/*!
 *  Komunikat b��du zg�aszanego w przypadku, gdy w opisie pozycji interfejsu
 *  sterowania zostanie napotkany identyfikator rodzaju macierzy, kt�ry nie
 *  odpowiada �adnemu ze znanych typ�w. Wspomniany identyfikator okre�la
 *  lokalizacj� macierzy w danej klasie.
 */
#define ERRMSG_POLYH__WRONG_MTXID "Odczytany identyfikator '%i' rodzaju"\
         " macierzy transformacji nie odpowiada �adnemu ze znanych"\
         " identyfikator�w. Oczekiwane identyfikatory to: "\
         " %i (ViNTreeNode::_Transf2ParentCoord),"\
         " %i (ViElemePolyh::_Mtx_Patte2Eleme),"\
         " %i (ViElemePolyh::_Mtx_Eleme2Indiv)."


/*! 
 *  Numer b��du zg�aszanego w przypadku, gdy podany adres nie odpowiada
 *  �adnemu w�z�owi drzewa modeluj�cego scen�.\n
 *  Zg�aszanemu b��dowi odpowiada mu komunikat zdefinowany przez sta��
 *  \link vierrors.hh::ERRMSG_HIER__WRONG_ADDR
 *                     ERRMSG_HIER__WRONG_ADDR\endlink
 */
#define ERRNUM_HIER__WRONG_ADDR           24
/*! 
 *  Komunikat b��du zg�aszanego w przypadku, gdy podany adres nie 
 *  odpowiada �adnemu w�z�owi drzewa modeluj�cego scen�.
 */
#define ERRMSG_HIER__WRONG_ADDR "Adres '%s' nie odpowiada �adnemu"\
                       " w�z�owi w danym modelu sceny."

/*!
 *  Numer b��du zg�aszanego w przypadku, gdy przed wykonaniem danej
 *  operacji oczekiwane jest wcze�niejsze znalezienie lub utworzenie
 *  obiektu klasy ViNTreeNode.\n
 * Odpowiada mu komunikat zdefinowany przez sta��
 *  \link vierrors.hh::ERRMSG_INTERF__NO_POLYH_FOUND
 *                     ERRMSG_INTERF__NO_POLYH_FOUND\endlink
 */
#define ERRNUM_INTERF__NO_POLYH_FOUND    25
/*!
 *  Komunikat b��du zg�aszanego w przypadku, gdy przed wykonaniem danej
 *  operacji oczekiwane jest wcze�niejsze znalezienie lub utworzenie
 *  obiektu klasy ViNTreeNode.
 */
#define ERRMSG_INTERF__NO_POLYH_FOUND "Brak obiektu obiektu klasy"\
              " ViNTreeNode przed wykonaniem operacji, kt�ra"\
              " wymaga jego istnienia."

/*! 
 * Numer b��du zg�aszanego w przypadku, gdy przy odczytywaniu
 * opisu interfejsu sterowania identyfikator macierzy nie jest
 * zgodny z identyfikatorem klasy obiektu, z kt�rym ma by�
 * skojarzona dana pozycja interfejsu.\n
 * Zg�aszanemu b��dowi odpowiada mu komunikat zdefinowany przez sta��
 *  \link vierrors.hh::ERRMSG_INTERF__IMPROPER_MTX
 *                     ERRMSG_INTERF__IMPROPER_MTX\endlink
 */
#define ERRNUM_INTERF__IMPROPER_MTX     26
/*! 
 * Komunika b��du zg�aszanego w przypadku, gdy przy odczytywaniu
 * opisu interfejsu sterowania identyfikator macierzy nie jest
 * zgodny z identyfikatorem klasy obiektu, z kt�rym ma by�
 * skojarzona dana pozycja interfejsu.
 */
#define ERRMSG_INTERF__IMPROPER_MTX  "Identyfikator rodzaju macierzy "\
   " ('%i') nie odpowiada klasie obiektu (identyfikator klasy: %i),"\
   " z kt�rym ma by� skojarzony dana pozycja interfejsu."

/*!
 * Numer b��du zg�aszanego w przypadku, gdy napis poddany konwersji
 * na typ \link Vi::TransformType Vi::TransformType\endlink nie odpowiada
 * �adnej z akceptowanych nazw.\n
 * Zg�aszanemu b��dowi odpowiada mu komunikat zdefinowany przez sta��
 *  \link vierrors.hh::ERRMSG_TRANSFTYPE__IMPROPER_NAME
 *                     ERRMSG_TRANSFTYPE__IMPROPER_NAME\endlink
 */
#define ERRNUM_TRANSFTYPE__IMPROPER_NAME  27
/*!
 * Komunikat b��du zg�aszanego w przypadku, gdy napis poddany konwersji
 * na typ \link Vi::TransformType Vi::TransformType\endlink nie odpowiada
 * �adnej z akceptowanych nazw.
 */
#define ERRMSG_TRANSFTYPE__IMPROPER_NAME  "Nazwa warto�ci typu"\
    " TransformType nie odpowiada �adnej z oczekiwanych nazw."\
    " Otrzymano nazw� \"%s\", oczekuje si� jednej z nazw: %s"


/*!
 * Numer b��du zg�aszanego w przypadku, gdy napis poddany konwersji
 * na typ \link Vi::MetricUnit Vi::MetricUnit\endlink nie odpowiada
 * �adnej z akceptowanych nazw.\n
 * Zg�aszanemu b��dowi odpowiada mu komunikat zdefinowany przez sta��
 *  \link vierrors.hh::ERRMSG_METRICUNIT__IMPROPER_NAME
 *                     ERRMSG_METRICUNIT__IMPROPER_NAME\endlink
 */
#define ERRNUM_METRICUNIT__IMPROPER_NAME  28
/*!
 * Komunikat b��du zg�aszanego w przypadku, gdy napis poddany konwersji
 * na typ \link Vi::MetricUnit Vi::MetricUnit\endlink nie odpowiada
 * �adnej z akceptowanych nazw.
 */
#define ERRMSG_METRICUNIT__IMPROPER_NAME  "Nazwa warto�ci typu"\
    " MetricUnit nie odpowiada �adnej z oczekiwanych nazw."\
    " Otrzymano nazw� \"%s\", oczekuje si� jednej z nazw: %s"



/*!
 * Numer b��du zg�aszanego w przypadku, gdy napis poddany konwersji
 * na typ \link Vi::Coord3DType Vi::Coord3DType\endlink nie odpowiada
 * �adnej z akceptowanych nazw.\n
 * Zg�aszanemu b��dowi odpowiada mu komunikat zdefinowany przez sta��
 *  \link vierrors.hh::ERRMSG_COORD3DTYPE__IMPROPER_NAME
 *                     ERRMSG_COORD3DTYPE__IMPROPER_NAME\endlink
 */
#define ERRNUM_COORD3DTYPE__IMPROPER_NAME  29
/*!
 * Komunikat b��du zg�aszanego w przypadku, gdy napis poddany konwersji
 * na typ \link Vi::Coord3DType Vi::Coord3DType\endlink nie odpowiada
 * �adnej z akceptowanych nazw.
 */
#define ERRMSG_COORD3DTYPE__IMPROPER_NAME  "Nazwa warto�ci typu"\
    " Coord3DType nie odpowiada �adnej z oczekiwanych nazw."\
    " Otrzymano nazw� \"%s\", oczekuje si� jednej z nazw: %s"



#endif
