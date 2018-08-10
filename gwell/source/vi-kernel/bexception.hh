#ifndef BEXCEPTION_HH
#define BEXCEPTION_HH
/*!
 * \file bexception.hh
 * \author Bogdan Kreczmer
 * \date 2004.08
 *
 * Plik zawiera definicjê klas wyj±tku BException. Jest ona podstaw± 
 * hierarchii wyj±tków tworzonych w innych aplikacjach korzystaj±cych z tego 
 * modu³u.
 */

#ifdef __GNUG__
# pragma interface
#endif

#include <string>
#include "strprintf.hh"


/*!
 * Niniejsza przestrzeñ nazw zawiera bazowe struktury ogólnego przeznaczenia.
 */
namespace Ba {

/*!
 *  Jest to klasa bazowa dla wszystkich wyjatków zg³aszanych w aplikacji
 *  projektu VIONA.
 */
 class Exception {
  public:
 /*!
  *  Pe³ni rolê zmiennej globalnej i ma znaczenie pomocnicze.
  *  Pole to jest wykorzystywane do budowania
  *  komuników o b³êdach z zastosowaniem makra MSG.
  */
  static StrPrintf _TmpMsg;

  protected:
    /*!
     *  Zawiera napis opisuj±cy zg³oszony b³±d.
     */
   std::string _ErrorMsg;

    /*!
     *  Zawiera numer b³êdu.
     * \warning Przyjmuje siê, ¿e warto¶æ doy¶lna kodu b³êdu 0 sygnalizuje brak b³êdu.
     */
   int         _ErrorID;  
    /*!
     *  Pomocniczy numer identyfikuj±cy miejsce wyst±pienia b³êdu.
     *  Mo¿e byæ pomocny w przypadku, gdy zachodzi konieczno¶æ okre¶lenia
     *  miejsca wyst±pienia b³êdu, który mo¿e zostaæ zg³oszony w kilku 
     *  miejscach.
     */
   int         _ErrAuxID;
  public:

   /*!
    *  Inicjalizuje informacje o b³êdzie.
    *  \param Err - numer b³êdu,
    *  \param Msg - komunikat b³êdu,
    *  \param AuxID - pomocniczy identyfikator dla okre¶lenia miejsca
    *                 wyst±pienia b³êdu (inicjalizuje pole
    *                 \link ViException::_ErrAuxID _ErrAuxID\endlink).
    * \warning Przyjmuje siê, ¿e warto¶æ doy¶lna kodu b³êdu 0 
    *          sygnalizuje brak b³êdu.
    */
   Exception(int Err = 0, const char *Msg = 0L, int AuxID = 0);

   virtual ~Exception() {}

   /*!
    *  Udostêpnia numer b³êdu.
    */
   int GetErrID() const { return _ErrorID; }
   /*!
    *  Udostêpnia pomocniczy numer b³êdu.
    */
   int GetErrAuxID() const { return _ErrAuxID; }
   /*!
    *  Udostêpnia komunikat o b³êdzie.
    */
   const char *GetErrMsg() const { return _ErrorMsg.c_str(); }
 };



 /*!
  *  Wspomaga wykorzystywanie parametryzowanych komunikatów o b³êdach.
  *  \param  xErrMsg  - pametryzowany komunikat b³êdu,
  *
  *  Przyk³±d u¿ycia:
  *  \code
  *    MSG(ERRMSG_FACE_VTXNO),"SZESCIAN",8,10
  *  \endcode
  */
# define MSG(xErrMsg)  (Ba::Exception::_TmpMsg = xErrMsg)


}
#endif
