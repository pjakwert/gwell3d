#ifndef BEXCEPTION_HH
#define BEXCEPTION_HH
/*!
 * \file bexception.hh
 * \author Bogdan Kreczmer
 * \date 2004.08
 *
 * Plik zawiera definicj� klas wyj�tku BException. Jest ona podstaw� 
 * hierarchii wyj�tk�w tworzonych w innych aplikacjach korzystaj�cych z tego 
 * modu�u.
 */

#ifdef __GNUG__
# pragma interface
#endif

#include <string>
#include "strprintf.hh"


/*!
 * Niniejsza przestrze� nazw zawiera bazowe struktury og�lnego przeznaczenia.
 */
namespace Ba {

/*!
 *  Jest to klasa bazowa dla wszystkich wyjatk�w zg�aszanych w aplikacji
 *  projektu VIONA.
 */
 class Exception {
  public:
 /*!
  *  Pe�ni rol� zmiennej globalnej i ma znaczenie pomocnicze.
  *  Pole to jest wykorzystywane do budowania
  *  komunik�w o b��dach z zastosowaniem makra MSG.
  */
  static StrPrintf _TmpMsg;

  protected:
    /*!
     *  Zawiera napis opisuj�cy zg�oszony b��d.
     */
   std::string _ErrorMsg;

    /*!
     *  Zawiera numer b��du.
     * \warning Przyjmuje si�, �e warto�� doy�lna kodu b��du 0 sygnalizuje brak b��du.
     */
   int         _ErrorID;  
    /*!
     *  Pomocniczy numer identyfikuj�cy miejsce wyst�pienia b��du.
     *  Mo�e by� pomocny w przypadku, gdy zachodzi konieczno�� okre�lenia
     *  miejsca wyst�pienia b��du, kt�ry mo�e zosta� zg�oszony w kilku 
     *  miejscach.
     */
   int         _ErrAuxID;
  public:

   /*!
    *  Inicjalizuje informacje o b��dzie.
    *  \param Err - numer b��du,
    *  \param Msg - komunikat b��du,
    *  \param AuxID - pomocniczy identyfikator dla okre�lenia miejsca
    *                 wyst�pienia b��du (inicjalizuje pole
    *                 \link ViException::_ErrAuxID _ErrAuxID\endlink).
    * \warning Przyjmuje si�, �e warto�� doy�lna kodu b��du 0 
    *          sygnalizuje brak b��du.
    */
   Exception(int Err = 0, const char *Msg = 0L, int AuxID = 0);

   virtual ~Exception() {}

   /*!
    *  Udost�pnia numer b��du.
    */
   int GetErrID() const { return _ErrorID; }
   /*!
    *  Udost�pnia pomocniczy numer b��du.
    */
   int GetErrAuxID() const { return _ErrAuxID; }
   /*!
    *  Udost�pnia komunikat o b��dzie.
    */
   const char *GetErrMsg() const { return _ErrorMsg.c_str(); }
 };



 /*!
  *  Wspomaga wykorzystywanie parametryzowanych komunikat�w o b��dach.
  *  \param  xErrMsg  - pametryzowany komunikat b��du,
  *
  *  Przyk��d u�ycia:
  *  \code
  *    MSG(ERRMSG_FACE_VTXNO),"SZESCIAN",8,10
  *  \endcode
  */
# define MSG(xErrMsg)  (Ba::Exception::_TmpMsg = xErrMsg)


}
#endif
