#ifndef VI_READMULTIPOLYH_HH
#define VI_READMULTIPOLYH_HH

/*! \file vi-readmultipolyh.hh
 *  Plik zawiera zapwied¼ definicji funkcji czytaj±cej i interpretuj±cej
 *  opis bry³y z³o¿onej.
 *  \author  Bogdan Kreczmer
 *  \date   2004.06.07
 */


#include <istream>
#include "viexception.hh"
#include "viscene.hh"

class ViNTreeNode;


/*! \namespace  Vi
 * Przestrzeñ nazw \b Vi zawiera definicjê funkcji operuj±cych
 * na strukturach biblioteki \ref viona-biblioteka "VIONA".
 */
namespace Vi {
  /*!
   *  Funkcja czyta ze strumienia wej¶ciowego opis bry³y z³o¿onej,
   *  tworzy j± i umieszcza na scenie.
   *  \param istrm - strumieñ wej¶ciowy,
   *  \param Scn - scena w której ma byæ umieszczona utworzona
   *               wg. odczytanego opisu bry³a z³o¿ona.
   *  \param ListType - okre¶la do jakiego rodzaju listy bry³ (normalnych
   *               lub specjalnych) danej sceny zostanie wczytana dana bry³a.
   *  \param ObjectCreator - funkcja tworz±ca obiekt o nazwie, która przekazana
   *               zostanie do niej za pomoc± parametru \e ClassName.
   *  \retval 0 - je¶li odczyt opisu i utworzenie bry³y zakoñczy³y siê
   *              powdzeniem.
   *  \post Operacja wczytania nie powoduje usuniêcia jakiekolwiek istniej±cej
   *        ju¿ bry³y w danej scenie.
   *  \exception ViException_Syntax - mo¿e byæ zg³oszony z kodami b³êdów:
   *    \li \link vierrors.hh::ERRNUM_SYNTAX__UNEXPECTED_KEYWORD
   *                       ERRNUM_SYNTAX__UNEXPECTED_KEYWORD\endlink -
   *           gdy napotkane s³owo nie odpowiada oczekiwanemu s³owu kluczowemu.
   *
   *    \li \link vierrors.hh::ERRNUM_SYNTAX__UNEXPECTED_KEYWORD2
   *                       ERRNUM_SYNTAX__UNEXPECTED_KEYWORD2\endlink -
   *           gdy napotkane s³owo nie odpowiada ¿adnemu ¿adnemu s³owu
   *           z zadanego zbioru oczekiwanych s³ów kluczowych.
   *    \li  \link vierrors.hh::ERRNUM_SYNTAX__UNEXPECTED_END
   *                           ERRNUM_SYNTAX__UNEXPECTED_END\endlink -
   *        w przypadku, gdy osi±gniêty zosta³ koniec strumienia,
   *        nie zosta³o napotkane natomiast oczekiwane s³owo kluczowe.
   *   \li \link sxinterp.hh::ERRNUM_SX__UNEXP_CHAR 
   *              ERRNUM_SX__UNEXP_CHAR\endlink - gdy napotkany zosta³
   *                inny znaku ni¿ oczekiwany.
   *   \li \link sxinterp.hh::ERRNUM_SX__FAIL_FLOAT
   *           ERRNUM_SX__FAIL_FLOAT\endlink - w przypadku niemo¿no¶ci
   *             wczytania liczby typu \e float.
   *   \li \link sxinterp.hh::ERRNUM_SX__FAIL_INT ERRNUM_SX__FAIL_INT\endlink -
   *             w przypadku niemo¿no¶ci wczytania liczby typu \e integer.
   *   \li \link sxinterp.hh::ERRNUM_SX__NO_KEYWORDS 
   *             ERRNUM_SX__NO_KEYWORDS\endlink - gdy brak listy ze s³owami
   *             kluczowymi.
   *   \li \link sxinterp.hh::ERRNUM_SX__START_NO_KEYWORD
   *             ERRNUM_SX__START_NO_KEYWORD\endlink - gdy napotkany znak
   *             nie mo¿e byæ pocz±tkiem ¿adnego s³owa kluczowego.
   *   \li \link sxinterp.hh::ERRNUM_SX__NO_KEYWORD 
   *                                          ERRNUM_SX__NO_KEYWORD\endlink
   *             - gdy znalezione s³owo nie jest ¿adnym z oczekiwanych
   *               s³ów kluczowych.
   *   \li \link sxinterp.hh::ERRNUM_SX__NO_WORD ERRNUM_SX__NO_WORD\endlink -
   *             gdy nie znaleziono ¿adnego s³owa.
   *   \li \link vierrors.hh::ERRNUM_MULTI__MOVE2LIST_FAILED
   *               ERRNUM_MULTI__MOVE2LIST_FAILED\endlink - gdy nie powiod³a
   *               siê operacja przesuniêcia utworzonej bry³y z³o¿onej z listy
   *               tymczasowej do listy finalnej danej sceny.
   *    \li \link vierrors.hh::ERRNUM_POLYH__CREATE_FAILED
   *               ERRNUM_POLYH__CREATE_FAILED\endlink - gdy nie powiod³ siê
   *               odczyt klasy finalnej opisu danego wêz³a.
   *  \exception ViException - mo¿e byæ zg³oszony z kodami b³êdów:
   *    \li \link vierrors.hh::ERRMSG_POLYH__CREATE_FAILED
   *                       ERRMSG_POLYH__CREATE_FAILED\endlink - gdy nie
   *               powiod³o siê utworzenie obiektu na podstawie otrzymanego
   *               opisu.
   */
  void ReadMultiPolyh(
                 std::istream &          istrm, 
                 ViScene      &          Scn, 
                 Vi::MultiPolyhListType  ListType,
                 ViNTreeNode * (*ObjectCreator)(const char *ClassName) = 0L
		); //throw (ViException_Syntax);


  /*!
   *  \anchor  ReadMultiPolyh-file-excep
   *  Funkcja czyta z pliku opis bry³y z³o¿onej,
   *  tworzy j± i umieszcza na scenie.
   *  \param FileName - nazwa pilku,
   *  \param Scn - scena w której ma byæ umieszczona utworzona
   *               wg. odczytanego opisu bry³a z³o¿ona.
   *  \param ListType - okre¶la do jakiego rodzaju listy bry³ (normalnych
   *               lub specjalnych) danej sceny zostanie wczytana dana bry³a.
   *  \param ObjectCreator - funkcja tworz±ca obiekt o nazwie, która przekazana
   *               zostanie do niej za pomoc± parametru \e ClassName.
   *
   *  \post Operacja wczytania nie powoduje usuniêcia jakiekolwiek istniej±cej
   *        ju¿ bry³y w danej scenie.
   *
   *  \exception ViException_File - zg³aszany jest kodem b³edu 
   *    \link vierrors.hh::ERRNUM_FILE__OPEN2READ_FAILED 
   *                       ERRNUM_FILE__OPEN2READ_FAILED\endlink. Zg³aszany on
   *           jest w przypadku niepowodzenia operacji otwarcia do otczytu
   *           pliku.
   *  \exception ViException_Syntax - mo¿e byæ zg³oszony z kodami b³êdów:
   *    \li \link vierrors.hh::ERRNUM_SYNTAX__UNEXPECTED_KEYWORD
   *                       ERRNUM_SYNTAX__UNEXPECTED_KEYWORD\endlink -
   *           gdy napotkane s³owo nie odpowiada oczekiwanemu s³owu kluczowemu.
   *
   *    \li \link vierrors.hh::ERRNUM_SYNTAX__UNEXPECTED_KEYWORD2
   *                       ERRNUM_SYNTAX__UNEXPECTED_KEYWORD2\endlink -
   *           gdy napotkane s³owo nie odpowiada ¿adnemu ¿adnemu s³owu
   *           z zadanego zbioru oczekiwanych s³ów kluczowych.
   *    \li  \link vierrors.hh::ERRNUM_SYNTAX__UNEXPECTED_END
   *                           ERRNUM_SYNTAX__UNEXPECTED_END\endlink -
   *        w przypadku, gdy osi±gniêty zosta³ koniec strumienia,
   *        nie zosta³o napotkane natomiast oczekiwane s³owo kluczowe.
   *   \li \link sxinterp.hh::ERRNUM_SX__UNEXP_CHAR 
   *              ERRNUM_SX__UNEXP_CHAR\endlink - gdy napotkany zosta³
   *                inny znaku ni¿ oczekiwany.
   *   \li \link sxinterp.hh::ERRNUM_SX__FAIL_FLOAT
   *           ERRNUM_SX__FAIL_FLOAT\endlink - w przypadku niemo¿no¶ci
   *             wczytania liczby typu \e float.
   *   \li \link sxinterp.hh::ERRNUM_SX__FAIL_INT ERRNUM_SX__FAIL_INT\endlink -
   *             w przypadku niemo¿no¶ci wczytania liczby typu \e integer.
   *   \li \link sxinterp.hh::ERRNUM_SX__NO_KEYWORDS 
   *             ERRNUM_SX__NO_KEYWORDS\endlink - gdy brak listy ze s³owami
   *             kluczowymi.
   *   \li \link sxinterp.hh::ERRNUM_SX__START_NO_KEYWORD
   *             ERRNUM_SX__START_NO_KEYWORD\endlink - gdy napotkany znak
   *             nie mo¿e byæ pocz±tkiem ¿adnego s³owa kluczowego.
   *   \li \link sxinterp.hh::ERRNUM_SX__NO_KEYWORD 
   *                                            ERRNUM_SX__NO_KEYWORD\endlink
   *             - gdy znalezione s³owo nie jest ¿adnym z oczekiwanych
   *               s³ów kluczowych.
   *   \li \link sxinterp.hh::ERRNUM_SX__NO_WORD ERRNUM_SX__NO_WORD\endlink -
   *             gdy nie znaleziono ¿adnego s³owa.
   *   \li \link vierrors.hh::ERRNUM_MULTI__MOVE2LIST_FAILED
   *               ERRNUM_MULTI__MOVE2LIST_FAILED\endlink - gdy nie powiod³a
   *               siê operacja przesuniêcia utworzonej bry³y z³o¿onej z listy
   *               tymczasowej do listy finalnej danej sceny.
   *    \li \link vierrors.hh::ERRNUM_POLYH__CREATE_FAILED
   *               ERRNUM_POLYH__CREATE_FAILED\endlink - gdy nie powiod³ siê
   *               odczyt klasy finalnej opisu danego wêz³a.
   *  \exception ViException - mo¿e byæ zg³oszony z kodami b³êdów:
   *    \li \link vierrors.hh::ERRMSG_POLYH__CREATE_FAILED
   *                       ERRMSG_POLYH__CREATE_FAILED\endlink - gdy nie
   *               powiod³o siê utworzenie obiektu na podstawie otrzymanego
   *               opisu.
   */
  void ReadMultiPolyh( 
                 const char *       FileName, 
                 ViScene    &       Scn, 
                 Vi::MultiPolyhListType  ListType,
                 ViNTreeNode * (*ObjectCreator)(const char *ClassName) = 0L
	       ); // throw (ViException, ViException_File, ViException_Syntax);

  /*!
   *  \anchor  ReadMultiPolyh-file-noexcep
   *  Funkcja czyta z pliku opis bry³y z³o¿onej,
   *  tworzy j± i umieszcza na scenie. Jest ona wersj± funkcji
   *  \ref ReadMultiPolyh-file-excep "ReadMultiPolyh", która mog³a
   *  zg³aszaæ wyj±tki.\n
   *  W niniejszej funkcji mechanizm obs³ugi b³êdów zosta³ uproszczony.
   *  Funkcja sama przechwytuje wszystkie wyj±tki i na zewn±trz przekazuje
   *  tylko obiekt z kodem b³êdu i komunikatem o b³êdzie.\n
   *  Dokonane uproszczenie wynika z tego, ¿e wszystkie zg³aszane b³êdy
   *  s± b³êdami typu fatalnego. Ich obs³uga praktycznie mo¿na sprowadziæ
   *  jedynie do wy¶wietlenia otrzymanego komunikatu.\n
   *  \param FileName - nazwa pilku,
   *  \param Scn - scena w której ma byæ umieszczona utworzona
   *               wg. odczytanego opisu bry³a z³o¿ona.
   *  \param ListType - okre¶la do jakiego rodzaju listy bry³ (normalnych
   *               lub specjalnych) danej sceny zostanie wczytana dana bry³a.
   *  \param Excep - w przypadku wyst±pinia b³êdu zawiera kod b³êdu i
   *                 odpowiedni komunikat.
   *                 Wszystkie kody b³êdów wymienione s± w opisie 
   *            funkcji  \ref ReadMultiPolyh-file-excep "ReadMultiPolyh",
   *            która mo¿e zg³aszaæ wyj±tki.
   *  \param ObjectCreator - funkcja tworz±ca obiekt o nazwie, która przekazana
   *               zostanie do niej za pomoc± parametru \e ClassName.
   *
   *  \post Operacja wczytania nie powoduje usuniêcia jakiekolwiek istniej±cej
   *        ju¿ bry³y w danej scenie.
   *  \retval  0 - gdy operacja zakoñczy³a siê powodzeniem,
   *  \retval -1 - gdy nie powiod³a siê operacja otwarcia danego pliku
   *               do odczytu. Komunikat b³êdu i jego kod 
   *               (w tym przypadku bêdzie to zawsze b³±d o kodzie
   *                 \link vierrors.hh::ERRNUM_FILE__OPEN2READ_FAILED 
   *                       ERRNUM_FILE__OPEN2READ_FAILED\endlink)
   *               dostêpny jest poprzez obiekt Excep 
   *              (patrz metody 
   *            \link Ba::Exception::GetErrID GetErrID\endlink i 
   *            \link Ba::Exception::GetErrMsg GetErrMsg\endlink).
   *  \retval -2 - gdy wyst±pi³ b³±d odczytu opisu bry³y z³o¿onej.
   *               Komunikat b³êdu i jego kod 
   *               dostêpny jest poprzez obiekt Excep 
   *              (patrz metody 
   *            \link Ba::Exception::GetErrID GetErrID\endlink i 
   *            \link Ba::Exception::GetErrMsg GetErrMsg\endlink).
   *         Wykaz zg³aszanych wyj±tków znajduje siê 
   *      w opisie wersji funkcji 
   *      \ref ReadMultiPolyh-file-excep "ReadMultiPolyh" ze zg³aszaniem 
   *      wyj±tków.
   */
  int ReadMultiPolyh(
                 const char  *      FileName, 
                 ViScene     &      Scn, 
                 Vi::MultiPolyhListType  ListType,
                 ViException &      Excep,
                 ViNTreeNode * (*ObjectCreator)(const char *ClassName) = 0L
                );



  /*!
   *  \anchor  ReadMultiPolyh-file-noexcep
   *  Funkcja czyta z pliku opis bry³y z³o¿onej,
   *  tworzy j± i przekazuje wska¼nik do niej wska¼nik. Jest ona wersj± funkcji
   *  \ref ReadMultiPolyh-file-excep "ReadMultiPolyh", która mog³a
   *  zg³aszaæ wyj±tki.\n
   *  W niniejszej funkcji mechanizm obs³ugi b³êdów zosta³ uproszczony.
   *  Funkcja sama przechwytuje wszystkie wyj±tki i na zewn±trz przekazuje
   *  tylko obiekt z kodem b³êdu i komunikatem o b³êdzie.\n
   *  Dokonane uproszczenie wynika z tego, ¿e wszystkie zg³aszane b³êdy
   *  s± b³êdami typu fatalnego. Ich obs³uga praktycznie mo¿na sprowadziæ
   *  jedynie do wy¶wietlenia otrzymanego komunikatu.\n
   *  \param FileName - nazwa pilku,
   *  \param Scn - (\b in) scena w której ma byæ umieszczona utworzona
   *               wg. odczytanego opisu bry³a z³o¿ona.
   *  \param ppMultiPolyh - wska¼nik do zmiennej wska¼nikowej, w której 
   *               wpisany zostaje adres do utworzonej bry³y z³o¿onej,
   *              o ile operacja odczytu jej opisu przebieg³a pomy¶lnie.
   *  \param Excep - (\b out) w przypadku wyst±pinia b³êdu zawiera kod b³êdu i
   *                 odpowiedni komunikat.
   *                 Wszystkie kody b³êdów wymienione s± w opisie 
   *            funkcji  \ref ReadMultiPolyh-file-excep "ReadMultiPolyh",
   *            która mo¿e zg³aszaæ wyj±tki.
   *  \param ObjectCreator - funkcja tworz±ca obiekt o nazwie, która przekazana
   *               zostanie do niej za pomoc± parametru \e ClassName.
   *
   *  \post Operacja wczytania nie powoduje usuniêcia jakiekolwiek istniej±cej
   *        ju¿ bry³y w danej scenie.
   *  \retval  0 - gdy operacja zakoñczy³a siê powodzeniem,
   *  \retval -1 - gdy nie powiod³a siê operacja otwarcia danego pliku
   *               do odczytu. Komunikat b³êdu i jego kod 
   *               (w tym przypadku bêdzie to zawsze b³±d o kodzie
   *                 \link vierrors.hh::ERRNUM_FILE__OPEN2READ_FAILED 
   *                       ERRNUM_FILE__OPEN2READ_FAILED\endlink)
   *               dostêpny jest poprzez obiekt Excep 
   *              (patrz metody 
   *            \link Ba::Exception::GetErrID GetErrID\endlink i 
   *            \link Ba::Exception::GetErrMsg GetErrMsg\endlink).
   *  \retval -2 - gdy wyst±pi³ b³±d odczytu opisu bry³y z³o¿onej.
   *               Komunikat b³êdu i jego kod 
   *               dostêpny jest poprzez obiekt Excep 
   *              (patrz metody 
   *            \link Ba::Exception::GetErrID GetErrID\endlink i 
   *            \link Ba::Exception::GetErrMsg GetErrMsg\endlink).
   *         Wykaz zg³aszanych wyj±tków znajduje siê 
   *      w opisie wersji funkcji 
   *      \ref ReadMultiPolyh-file-excep "ReadMultiPolyh" ze zg³aszaniem 
   *      wyj±tków.
   */
  int ReadMultiPolyh(
                 const char   *     FileName, 
                 const ViScene&     Scn,
                 ViMultiPolyh **    ppMultiPolyh, 
                 ViException &      Excep,
                 ViNTreeNode * (*ObjectCreator)(const char *ClassName) = 0L
                );


  /*!
   *  \anchor  ReadMultiPolyh-file-noexcep
   *  Funkcja czyta z pliku opis bry³y z³o¿onej,
   *  tworzy j± i przekazuje wska¼nik do niej wska¼nik. Jest ona wersj± funkcji
   *  \ref ReadMultiPolyh-file-excep "ReadMultiPolyh", która mog³a
   *  zg³aszaæ wyj±tki.\n
   *  Niniejsza funkcja nie odwo³uje siê do ca³êj sceny, a jedynie jako
   *  jeden ze swoich parametrów wymaga referencji na listê bibliotek
   *  bry³ wzorcowych.
   *
   *  Ponadto w niniejsza funkcja zawiera uproszczony mechanizm obs³ugi b³êdów.
   *  Funkcja sama przechwytuje wszystkie wyj±tki i na zewn±trz przekazuje
   *  tylko obiekt z kodem b³êdu i komunikatem o b³êdzie.\n
   *  Dokonane uproszczenie wynika z tego, ¿e wszystkie zg³aszane b³êdy
   *  s± b³êdami typu fatalnego. Ich obs³uga praktycznie mo¿na sprowadziæ
   *  jedynie do wy¶wietlenia otrzymanego komunikatu.\n
   *  \param FileName - nazwa pilku,
   *  \param PatteLibList - (\b in) lista bibliotek bry³ wzorcowych,
   *               które maj± byæ podstaw± tworzenia bry³ elementarnych
   *               jako sk³adników ca³ej bry³y z³o¿onej
   *               wg. odczytanego jej opisu.
   *  \param ppMultiPolyh - wska¼nik do zmiennej wska¼nikowej, w której 
   *               wpisany zostaje adres do utworzonej bry³y z³o¿onej,
   *              o ile operacja odczytu jej opisu przebieg³a pomy¶lnie.
   *  \param Excep - (\b out) w przypadku wyst±pinia b³êdu zawiera kod b³êdu i
   *                 odpowiedni komunikat.
   *                 Wszystkie kody b³êdów wymienione s± w opisie 
   *            funkcji  \ref ReadMultiPolyh-file-excep "ReadMultiPolyh",
   *            która mo¿e zg³aszaæ wyj±tki.
   *  \param ObjectCreator - funkcja tworz±ca obiekt o nazwie, która przekazana
   *               zostanie do niej za pomoc± parametru \e ClassName.
   *
   *  \post Operacja wczytania nie powoduje usuniêcia jakiekolwiek istniej±cej
   *        ju¿ bry³y w danej scenie.
   *  \retval  0 - gdy operacja zakoñczy³a siê powodzeniem,
   *  \retval -1 - gdy nie powiod³a siê operacja otwarcia danego pliku
   *               do odczytu. Komunikat b³êdu i jego kod 
   *               (w tym przypadku bêdzie to zawsze b³±d o kodzie
   *                 \link vierrors.hh::ERRNUM_FILE__OPEN2READ_FAILED 
   *                       ERRNUM_FILE__OPEN2READ_FAILED\endlink)
   *               dostêpny jest poprzez obiekt Excep 
   *              (patrz metody 
   *            \link Ba::Exception::GetErrID GetErrID\endlink i 
   *            \link Ba::Exception::GetErrMsg GetErrMsg\endlink).
   *  \retval -2 - gdy wyst±pi³ b³±d odczytu opisu bry³y z³o¿onej.
   *               Komunikat b³êdu i jego kod 
   *               dostêpny jest poprzez obiekt Excep 
   *              (patrz metody 
   *            \link Ba::Exception::GetErrID GetErrID\endlink i 
   *            \link Ba::Exception::GetErrMsg GetErrMsg\endlink).
   *         Wykaz zg³aszanych wyj±tków znajduje siê 
   *      w opisie wersji funkcji 
   *      \ref ReadMultiPolyh-file-excep "ReadMultiPolyh" ze zg³aszaniem 
   *      wyj±tków.
   */
  int ReadMultiPolyh(
                 const char   *            FileName, 
                 const ViPatteLibList&     PatteLibList,
                 ViMultiPolyh **           ppMultiPolyh, 
                 ViException &             Excep,
                 ViNTreeNode * (*ObjectCreator)(const char *ClassName)
               );


};


#endif
