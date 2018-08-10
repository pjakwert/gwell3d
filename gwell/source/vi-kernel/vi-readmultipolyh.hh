#ifndef VI_READMULTIPOLYH_HH
#define VI_READMULTIPOLYH_HH

/*! \file vi-readmultipolyh.hh
 *  Plik zawiera zapwied� definicji funkcji czytaj�cej i interpretuj�cej
 *  opis bry�y z�o�onej.
 *  \author  Bogdan Kreczmer
 *  \date   2004.06.07
 */


#include <istream>
#include "viexception.hh"
#include "viscene.hh"

class ViNTreeNode;


/*! \namespace  Vi
 * Przestrze� nazw \b Vi zawiera definicj� funkcji operuj�cych
 * na strukturach biblioteki \ref viona-biblioteka "VIONA".
 */
namespace Vi {
  /*!
   *  Funkcja czyta ze strumienia wej�ciowego opis bry�y z�o�onej,
   *  tworzy j� i umieszcza na scenie.
   *  \param istrm - strumie� wej�ciowy,
   *  \param Scn - scena w kt�rej ma by� umieszczona utworzona
   *               wg. odczytanego opisu bry�a z�o�ona.
   *  \param ListType - okre�la do jakiego rodzaju listy bry� (normalnych
   *               lub specjalnych) danej sceny zostanie wczytana dana bry�a.
   *  \param ObjectCreator - funkcja tworz�ca obiekt o nazwie, kt�ra przekazana
   *               zostanie do niej za pomoc� parametru \e ClassName.
   *  \retval 0 - je�li odczyt opisu i utworzenie bry�y zako�czy�y si�
   *              powdzeniem.
   *  \post Operacja wczytania nie powoduje usuni�cia jakiekolwiek istniej�cej
   *        ju� bry�y w danej scenie.
   *  \exception ViException_Syntax - mo�e by� zg�oszony z kodami b��d�w:
   *    \li \link vierrors.hh::ERRNUM_SYNTAX__UNEXPECTED_KEYWORD
   *                       ERRNUM_SYNTAX__UNEXPECTED_KEYWORD\endlink -
   *           gdy napotkane s�owo nie odpowiada oczekiwanemu s�owu kluczowemu.
   *
   *    \li \link vierrors.hh::ERRNUM_SYNTAX__UNEXPECTED_KEYWORD2
   *                       ERRNUM_SYNTAX__UNEXPECTED_KEYWORD2\endlink -
   *           gdy napotkane s�owo nie odpowiada �adnemu �adnemu s�owu
   *           z zadanego zbioru oczekiwanych s��w kluczowych.
   *    \li  \link vierrors.hh::ERRNUM_SYNTAX__UNEXPECTED_END
   *                           ERRNUM_SYNTAX__UNEXPECTED_END\endlink -
   *        w przypadku, gdy osi�gni�ty zosta� koniec strumienia,
   *        nie zosta�o napotkane natomiast oczekiwane s�owo kluczowe.
   *   \li \link sxinterp.hh::ERRNUM_SX__UNEXP_CHAR 
   *              ERRNUM_SX__UNEXP_CHAR\endlink - gdy napotkany zosta�
   *                inny znaku ni� oczekiwany.
   *   \li \link sxinterp.hh::ERRNUM_SX__FAIL_FLOAT
   *           ERRNUM_SX__FAIL_FLOAT\endlink - w przypadku niemo�no�ci
   *             wczytania liczby typu \e float.
   *   \li \link sxinterp.hh::ERRNUM_SX__FAIL_INT ERRNUM_SX__FAIL_INT\endlink -
   *             w przypadku niemo�no�ci wczytania liczby typu \e integer.
   *   \li \link sxinterp.hh::ERRNUM_SX__NO_KEYWORDS 
   *             ERRNUM_SX__NO_KEYWORDS\endlink - gdy brak listy ze s�owami
   *             kluczowymi.
   *   \li \link sxinterp.hh::ERRNUM_SX__START_NO_KEYWORD
   *             ERRNUM_SX__START_NO_KEYWORD\endlink - gdy napotkany znak
   *             nie mo�e by� pocz�tkiem �adnego s�owa kluczowego.
   *   \li \link sxinterp.hh::ERRNUM_SX__NO_KEYWORD 
   *                                          ERRNUM_SX__NO_KEYWORD\endlink
   *             - gdy znalezione s�owo nie jest �adnym z oczekiwanych
   *               s��w kluczowych.
   *   \li \link sxinterp.hh::ERRNUM_SX__NO_WORD ERRNUM_SX__NO_WORD\endlink -
   *             gdy nie znaleziono �adnego s�owa.
   *   \li \link vierrors.hh::ERRNUM_MULTI__MOVE2LIST_FAILED
   *               ERRNUM_MULTI__MOVE2LIST_FAILED\endlink - gdy nie powiod�a
   *               si� operacja przesuni�cia utworzonej bry�y z�o�onej z listy
   *               tymczasowej do listy finalnej danej sceny.
   *    \li \link vierrors.hh::ERRNUM_POLYH__CREATE_FAILED
   *               ERRNUM_POLYH__CREATE_FAILED\endlink - gdy nie powiod� si�
   *               odczyt klasy finalnej opisu danego w�z�a.
   *  \exception ViException - mo�e by� zg�oszony z kodami b��d�w:
   *    \li \link vierrors.hh::ERRMSG_POLYH__CREATE_FAILED
   *                       ERRMSG_POLYH__CREATE_FAILED\endlink - gdy nie
   *               powiod�o si� utworzenie obiektu na podstawie otrzymanego
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
   *  Funkcja czyta z pliku opis bry�y z�o�onej,
   *  tworzy j� i umieszcza na scenie.
   *  \param FileName - nazwa pilku,
   *  \param Scn - scena w kt�rej ma by� umieszczona utworzona
   *               wg. odczytanego opisu bry�a z�o�ona.
   *  \param ListType - okre�la do jakiego rodzaju listy bry� (normalnych
   *               lub specjalnych) danej sceny zostanie wczytana dana bry�a.
   *  \param ObjectCreator - funkcja tworz�ca obiekt o nazwie, kt�ra przekazana
   *               zostanie do niej za pomoc� parametru \e ClassName.
   *
   *  \post Operacja wczytania nie powoduje usuni�cia jakiekolwiek istniej�cej
   *        ju� bry�y w danej scenie.
   *
   *  \exception ViException_File - zg�aszany jest kodem b�edu 
   *    \link vierrors.hh::ERRNUM_FILE__OPEN2READ_FAILED 
   *                       ERRNUM_FILE__OPEN2READ_FAILED\endlink. Zg�aszany on
   *           jest w przypadku niepowodzenia operacji otwarcia do otczytu
   *           pliku.
   *  \exception ViException_Syntax - mo�e by� zg�oszony z kodami b��d�w:
   *    \li \link vierrors.hh::ERRNUM_SYNTAX__UNEXPECTED_KEYWORD
   *                       ERRNUM_SYNTAX__UNEXPECTED_KEYWORD\endlink -
   *           gdy napotkane s�owo nie odpowiada oczekiwanemu s�owu kluczowemu.
   *
   *    \li \link vierrors.hh::ERRNUM_SYNTAX__UNEXPECTED_KEYWORD2
   *                       ERRNUM_SYNTAX__UNEXPECTED_KEYWORD2\endlink -
   *           gdy napotkane s�owo nie odpowiada �adnemu �adnemu s�owu
   *           z zadanego zbioru oczekiwanych s��w kluczowych.
   *    \li  \link vierrors.hh::ERRNUM_SYNTAX__UNEXPECTED_END
   *                           ERRNUM_SYNTAX__UNEXPECTED_END\endlink -
   *        w przypadku, gdy osi�gni�ty zosta� koniec strumienia,
   *        nie zosta�o napotkane natomiast oczekiwane s�owo kluczowe.
   *   \li \link sxinterp.hh::ERRNUM_SX__UNEXP_CHAR 
   *              ERRNUM_SX__UNEXP_CHAR\endlink - gdy napotkany zosta�
   *                inny znaku ni� oczekiwany.
   *   \li \link sxinterp.hh::ERRNUM_SX__FAIL_FLOAT
   *           ERRNUM_SX__FAIL_FLOAT\endlink - w przypadku niemo�no�ci
   *             wczytania liczby typu \e float.
   *   \li \link sxinterp.hh::ERRNUM_SX__FAIL_INT ERRNUM_SX__FAIL_INT\endlink -
   *             w przypadku niemo�no�ci wczytania liczby typu \e integer.
   *   \li \link sxinterp.hh::ERRNUM_SX__NO_KEYWORDS 
   *             ERRNUM_SX__NO_KEYWORDS\endlink - gdy brak listy ze s�owami
   *             kluczowymi.
   *   \li \link sxinterp.hh::ERRNUM_SX__START_NO_KEYWORD
   *             ERRNUM_SX__START_NO_KEYWORD\endlink - gdy napotkany znak
   *             nie mo�e by� pocz�tkiem �adnego s�owa kluczowego.
   *   \li \link sxinterp.hh::ERRNUM_SX__NO_KEYWORD 
   *                                            ERRNUM_SX__NO_KEYWORD\endlink
   *             - gdy znalezione s�owo nie jest �adnym z oczekiwanych
   *               s��w kluczowych.
   *   \li \link sxinterp.hh::ERRNUM_SX__NO_WORD ERRNUM_SX__NO_WORD\endlink -
   *             gdy nie znaleziono �adnego s�owa.
   *   \li \link vierrors.hh::ERRNUM_MULTI__MOVE2LIST_FAILED
   *               ERRNUM_MULTI__MOVE2LIST_FAILED\endlink - gdy nie powiod�a
   *               si� operacja przesuni�cia utworzonej bry�y z�o�onej z listy
   *               tymczasowej do listy finalnej danej sceny.
   *    \li \link vierrors.hh::ERRNUM_POLYH__CREATE_FAILED
   *               ERRNUM_POLYH__CREATE_FAILED\endlink - gdy nie powiod� si�
   *               odczyt klasy finalnej opisu danego w�z�a.
   *  \exception ViException - mo�e by� zg�oszony z kodami b��d�w:
   *    \li \link vierrors.hh::ERRMSG_POLYH__CREATE_FAILED
   *                       ERRMSG_POLYH__CREATE_FAILED\endlink - gdy nie
   *               powiod�o si� utworzenie obiektu na podstawie otrzymanego
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
   *  Funkcja czyta z pliku opis bry�y z�o�onej,
   *  tworzy j� i umieszcza na scenie. Jest ona wersj� funkcji
   *  \ref ReadMultiPolyh-file-excep "ReadMultiPolyh", kt�ra mog�a
   *  zg�asza� wyj�tki.\n
   *  W niniejszej funkcji mechanizm obs�ugi b��d�w zosta� uproszczony.
   *  Funkcja sama przechwytuje wszystkie wyj�tki i na zewn�trz przekazuje
   *  tylko obiekt z kodem b��du i komunikatem o b��dzie.\n
   *  Dokonane uproszczenie wynika z tego, �e wszystkie zg�aszane b��dy
   *  s� b��dami typu fatalnego. Ich obs�uga praktycznie mo�na sprowadzi�
   *  jedynie do wy�wietlenia otrzymanego komunikatu.\n
   *  \param FileName - nazwa pilku,
   *  \param Scn - scena w kt�rej ma by� umieszczona utworzona
   *               wg. odczytanego opisu bry�a z�o�ona.
   *  \param ListType - okre�la do jakiego rodzaju listy bry� (normalnych
   *               lub specjalnych) danej sceny zostanie wczytana dana bry�a.
   *  \param Excep - w przypadku wyst�pinia b��du zawiera kod b��du i
   *                 odpowiedni komunikat.
   *                 Wszystkie kody b��d�w wymienione s� w opisie 
   *            funkcji  \ref ReadMultiPolyh-file-excep "ReadMultiPolyh",
   *            kt�ra mo�e zg�asza� wyj�tki.
   *  \param ObjectCreator - funkcja tworz�ca obiekt o nazwie, kt�ra przekazana
   *               zostanie do niej za pomoc� parametru \e ClassName.
   *
   *  \post Operacja wczytania nie powoduje usuni�cia jakiekolwiek istniej�cej
   *        ju� bry�y w danej scenie.
   *  \retval  0 - gdy operacja zako�czy�a si� powodzeniem,
   *  \retval -1 - gdy nie powiod�a si� operacja otwarcia danego pliku
   *               do odczytu. Komunikat b��du i jego kod 
   *               (w tym przypadku b�dzie to zawsze b��d o kodzie
   *                 \link vierrors.hh::ERRNUM_FILE__OPEN2READ_FAILED 
   *                       ERRNUM_FILE__OPEN2READ_FAILED\endlink)
   *               dost�pny jest poprzez obiekt Excep 
   *              (patrz metody 
   *            \link Ba::Exception::GetErrID GetErrID\endlink i 
   *            \link Ba::Exception::GetErrMsg GetErrMsg\endlink).
   *  \retval -2 - gdy wyst�pi� b��d odczytu opisu bry�y z�o�onej.
   *               Komunikat b��du i jego kod 
   *               dost�pny jest poprzez obiekt Excep 
   *              (patrz metody 
   *            \link Ba::Exception::GetErrID GetErrID\endlink i 
   *            \link Ba::Exception::GetErrMsg GetErrMsg\endlink).
   *         Wykaz zg�aszanych wyj�tk�w znajduje si� 
   *      w opisie wersji funkcji 
   *      \ref ReadMultiPolyh-file-excep "ReadMultiPolyh" ze zg�aszaniem 
   *      wyj�tk�w.
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
   *  Funkcja czyta z pliku opis bry�y z�o�onej,
   *  tworzy j� i przekazuje wska�nik do niej wska�nik. Jest ona wersj� funkcji
   *  \ref ReadMultiPolyh-file-excep "ReadMultiPolyh", kt�ra mog�a
   *  zg�asza� wyj�tki.\n
   *  W niniejszej funkcji mechanizm obs�ugi b��d�w zosta� uproszczony.
   *  Funkcja sama przechwytuje wszystkie wyj�tki i na zewn�trz przekazuje
   *  tylko obiekt z kodem b��du i komunikatem o b��dzie.\n
   *  Dokonane uproszczenie wynika z tego, �e wszystkie zg�aszane b��dy
   *  s� b��dami typu fatalnego. Ich obs�uga praktycznie mo�na sprowadzi�
   *  jedynie do wy�wietlenia otrzymanego komunikatu.\n
   *  \param FileName - nazwa pilku,
   *  \param Scn - (\b in) scena w kt�rej ma by� umieszczona utworzona
   *               wg. odczytanego opisu bry�a z�o�ona.
   *  \param ppMultiPolyh - wska�nik do zmiennej wska�nikowej, w kt�rej 
   *               wpisany zostaje adres do utworzonej bry�y z�o�onej,
   *              o ile operacja odczytu jej opisu przebieg�a pomy�lnie.
   *  \param Excep - (\b out) w przypadku wyst�pinia b��du zawiera kod b��du i
   *                 odpowiedni komunikat.
   *                 Wszystkie kody b��d�w wymienione s� w opisie 
   *            funkcji  \ref ReadMultiPolyh-file-excep "ReadMultiPolyh",
   *            kt�ra mo�e zg�asza� wyj�tki.
   *  \param ObjectCreator - funkcja tworz�ca obiekt o nazwie, kt�ra przekazana
   *               zostanie do niej za pomoc� parametru \e ClassName.
   *
   *  \post Operacja wczytania nie powoduje usuni�cia jakiekolwiek istniej�cej
   *        ju� bry�y w danej scenie.
   *  \retval  0 - gdy operacja zako�czy�a si� powodzeniem,
   *  \retval -1 - gdy nie powiod�a si� operacja otwarcia danego pliku
   *               do odczytu. Komunikat b��du i jego kod 
   *               (w tym przypadku b�dzie to zawsze b��d o kodzie
   *                 \link vierrors.hh::ERRNUM_FILE__OPEN2READ_FAILED 
   *                       ERRNUM_FILE__OPEN2READ_FAILED\endlink)
   *               dost�pny jest poprzez obiekt Excep 
   *              (patrz metody 
   *            \link Ba::Exception::GetErrID GetErrID\endlink i 
   *            \link Ba::Exception::GetErrMsg GetErrMsg\endlink).
   *  \retval -2 - gdy wyst�pi� b��d odczytu opisu bry�y z�o�onej.
   *               Komunikat b��du i jego kod 
   *               dost�pny jest poprzez obiekt Excep 
   *              (patrz metody 
   *            \link Ba::Exception::GetErrID GetErrID\endlink i 
   *            \link Ba::Exception::GetErrMsg GetErrMsg\endlink).
   *         Wykaz zg�aszanych wyj�tk�w znajduje si� 
   *      w opisie wersji funkcji 
   *      \ref ReadMultiPolyh-file-excep "ReadMultiPolyh" ze zg�aszaniem 
   *      wyj�tk�w.
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
   *  Funkcja czyta z pliku opis bry�y z�o�onej,
   *  tworzy j� i przekazuje wska�nik do niej wska�nik. Jest ona wersj� funkcji
   *  \ref ReadMultiPolyh-file-excep "ReadMultiPolyh", kt�ra mog�a
   *  zg�asza� wyj�tki.\n
   *  Niniejsza funkcja nie odwo�uje si� do ca��j sceny, a jedynie jako
   *  jeden ze swoich parametr�w wymaga referencji na list� bibliotek
   *  bry� wzorcowych.
   *
   *  Ponadto w niniejsza funkcja zawiera uproszczony mechanizm obs�ugi b��d�w.
   *  Funkcja sama przechwytuje wszystkie wyj�tki i na zewn�trz przekazuje
   *  tylko obiekt z kodem b��du i komunikatem o b��dzie.\n
   *  Dokonane uproszczenie wynika z tego, �e wszystkie zg�aszane b��dy
   *  s� b��dami typu fatalnego. Ich obs�uga praktycznie mo�na sprowadzi�
   *  jedynie do wy�wietlenia otrzymanego komunikatu.\n
   *  \param FileName - nazwa pilku,
   *  \param PatteLibList - (\b in) lista bibliotek bry� wzorcowych,
   *               kt�re maj� by� podstaw� tworzenia bry� elementarnych
   *               jako sk�adnik�w ca�ej bry�y z�o�onej
   *               wg. odczytanego jej opisu.
   *  \param ppMultiPolyh - wska�nik do zmiennej wska�nikowej, w kt�rej 
   *               wpisany zostaje adres do utworzonej bry�y z�o�onej,
   *              o ile operacja odczytu jej opisu przebieg�a pomy�lnie.
   *  \param Excep - (\b out) w przypadku wyst�pinia b��du zawiera kod b��du i
   *                 odpowiedni komunikat.
   *                 Wszystkie kody b��d�w wymienione s� w opisie 
   *            funkcji  \ref ReadMultiPolyh-file-excep "ReadMultiPolyh",
   *            kt�ra mo�e zg�asza� wyj�tki.
   *  \param ObjectCreator - funkcja tworz�ca obiekt o nazwie, kt�ra przekazana
   *               zostanie do niej za pomoc� parametru \e ClassName.
   *
   *  \post Operacja wczytania nie powoduje usuni�cia jakiekolwiek istniej�cej
   *        ju� bry�y w danej scenie.
   *  \retval  0 - gdy operacja zako�czy�a si� powodzeniem,
   *  \retval -1 - gdy nie powiod�a si� operacja otwarcia danego pliku
   *               do odczytu. Komunikat b��du i jego kod 
   *               (w tym przypadku b�dzie to zawsze b��d o kodzie
   *                 \link vierrors.hh::ERRNUM_FILE__OPEN2READ_FAILED 
   *                       ERRNUM_FILE__OPEN2READ_FAILED\endlink)
   *               dost�pny jest poprzez obiekt Excep 
   *              (patrz metody 
   *            \link Ba::Exception::GetErrID GetErrID\endlink i 
   *            \link Ba::Exception::GetErrMsg GetErrMsg\endlink).
   *  \retval -2 - gdy wyst�pi� b��d odczytu opisu bry�y z�o�onej.
   *               Komunikat b��du i jego kod 
   *               dost�pny jest poprzez obiekt Excep 
   *              (patrz metody 
   *            \link Ba::Exception::GetErrID GetErrID\endlink i 
   *            \link Ba::Exception::GetErrMsg GetErrMsg\endlink).
   *         Wykaz zg�aszanych wyj�tk�w znajduje si� 
   *      w opisie wersji funkcji 
   *      \ref ReadMultiPolyh-file-excep "ReadMultiPolyh" ze zg�aszaniem 
   *      wyj�tk�w.
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
