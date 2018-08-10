#ifndef VIEXCEPTION_HH
#define VIEXCEPTION_HH
/*!
 * \file viexception.hh
 * \author Bogdan Kreczmer
 * \date 2004.03
 *
 * Plik zawiera definicjê klas wyj±tków, które mog± byæ zg³aszane przez
 * funkcje i metody z aplikacji projektu VIONA.
 */

#include <string>
#include "bexception.hh"

/*!
 *  Jest to klasa bazowa dla wszystkich wyjatków zg³aszanych w aplikacji
 *  projektu VIONA.
 */
class ViException: public Ba::Exception {
  public:
   /*!
    *  Inicjalizuje informacje o b³êdzie.
    *  \param Err - numer b³êdu,
    *  \param Msg - komunikat b³êdu,
    *  \param AuxID - pomocniczy identyfikator dla okre¶lenia miejsca
    *                 wyst±pienia b³êdu (inicjalizuje pole
    *                 \link ViException::_ErrAuxID _ErrAuxID\endlink).
    * \warning Przyjmuje siê, ¿e warto¶æ doy¶lna kodu b³êdu 0 sygnalizuje brak b³êdu.
    */
  ViException(int Err = 0, const char *Msg = 0L, int AuxID = 0): 
        Ba::Exception(Err,Msg,AuxID) {}
};


/*!
 *  Obiekty tej klasy wykorzystywane s± do zg³aszania b³êdu przekroczenia
 *  zakresu.
 */
class ViException_OutOfRange: public ViException 
{
  public:
   /*!
    *  Inicjalizuje informacje o b³êdzie.
    *  \param Err - numer b³êdu,
    *  \param Msg - komunikat b³êdu,
    *  \param AuxID - pomocniczy identyfikator dla okre¶lenia miejsca
    *                 wyst±pienia b³êdu (inicjalizuje pole
    *                 \link ViException::_ErrAuxID _ErrAuxID\endlink).
    * \warning Przyjmuje siê, ¿e warto¶æ doy¶lna kodu b³êdu 0 sygnalizuje brak b³êdu.
    */
  ViException_OutOfRange(int Err = 0, const char *Msg = 0L, int AuxID = 0):
      ViException(Err,Msg,AuxID) {}
};



/*!
 *  Obiekty tej klasy wykorzystywane s± do zg³aszania b³êdu wystêpuj±cego
 *  przy niezgodno¶ci obliczeñ z oczekiwanymi wynikami.
 */
class ViException_WrongComputation: public ViException 
{
  public:
   /*!
    *  Inicjalizuje informacje o b³êdzie.
    *  \param Err - numer b³êdu,
    *  \param Msg - komunikat b³êdu,
    *  \param AuxID - pomocniczy identyfikator dla okre¶lenia miejsca
    *                 wyst±pienia b³êdu (inicjalizuje pole
    *                 \link ViException::_ErrAuxID _ErrAuxID\endlink).
    * \warning Przyjmuje siê, ¿e warto¶æ doy¶lna kodu b³êdu 0 sygnalizuje brak b³êdu.
    */
  ViException_WrongComputation( int         Err = 0,
                                const char *Msg = 0L,
                                int         AuxID = 0
                              ):  ViException(Err,Msg,AuxID) {}
};




/*!
 *  Obiekty tej klasy wykorzystywane s± do zg³aszania b³êdu wystêpuj±cego
 *  przy niezgodno¶ci struktury danych.
 */
class ViException_DataInconsistence: public ViException 
{
  public:
   /*!
    *  Inicjalizuje informacje o b³êdzie.
    *  \param Err - numer b³êdu,
    *  \param Msg - komunikat b³êdu,
    *  \param AuxID - pomocniczy identyfikator dla okre¶lenia miejsca
    *                 wyst±pienia b³êdu (inicjalizuje pole
    *                 \link ViException::_ErrAuxID _ErrAuxID\endlink).
    * \warning Przyjmuje siê, ¿e warto¶æ doy¶lna kodu b³êdu 0 sygnalizuje brak b³êdu.
    */
  ViException_DataInconsistence( int         Err = 0,
                                 const char *Msg = 0L,
                                 int         AuxID = 0
                               ):  ViException(Err,Msg,AuxID) {}
};



/*!
 *  Obiekty tej klasy wykorzystywane s± do zg³aszania b³êdów sk³adni
 *  wczytywanych plików.
 */
class ViException_Syntax: public ViException 
{
  public:
   /*!
    *  Inicjalizuje informacje o b³êdzie.
    *  \param Err - numer b³êdu,
    *  \param Msg - komunikat b³êdu,
    *  \param AuxID - pomocniczy identyfikator dla okre¶lenia miejsca
    *                 wyst±pienia b³êdu (inicjalizuje pole
    *                 \link ViException::_ErrAuxID _ErrAuxID\endlink).
    * \warning Przyjmuje siê, ¿e warto¶æ doy¶lna kodu b³êdu 0 sygnalizuje brak b³êdu.
    */
  ViException_Syntax(int Err = 0, const char *Msg = 0L, int AuxID = 0):
      ViException(Err,Msg,AuxID) {}
};



/*!
 *  Obiekty tej klasy wykorzystywane s± do zg³aszania b³êdów
 *  zwi±zanych z obs³ug± bry³ wzorcowych.
 */
class ViException_Patte: public ViException 
{
  public:
   /*!
    *  Inicjalizuje informacje o b³êdzie.
    *  \param Err - numer b³êdu,
    *  \param Msg - komunikat b³êdu,
    *  \param AuxID - pomocniczy identyfikator dla okre¶lenia miejsca
    *                 wyst±pienia b³êdu (inicjalizuje pole
    *                 \link ViException::_ErrAuxID _ErrAuxID\endlink).
    * \warning Przyjmuje siê, ¿e warto¶æ doy¶lna kodu b³êdu 0 sygnalizuje brak b³êdu.
    */
  ViException_Patte(int Err = 0, const char *Msg = 0L, int AuxID = 0):
      ViException(Err,Msg,AuxID) {}
};



/*!
 *  Obiekty tej klasy wykorzystywane s± do zg³aszania b³êdów
 *  zwi±zanych z obs³ug± plik, np. b³êdami otwarcia plików do odczytu.
 */
class ViException_File: public ViException 
{
  public:
   /*!
    *  Inicjalizuje informacje o b³êdzie.
    *  \param Err - numer b³êdu,
    *  \param Msg - komunikat b³êdu,
    *  \param AuxID - pomocniczy identyfikator dla okre¶lenia miejsca
    *                 wyst±pienia b³êdu (inicjalizuje pole
    *                 \link ViException::_ErrAuxID _ErrAuxID\endlink).
    * \warning Przyjmuje siê, ¿e warto¶æ doy¶lna kodu b³êdu 0 sygnalizuje brak b³êdu.
    */
  ViException_File(int Err = 0, const char *Msg = 0L, int AuxID = 0):
      ViException(Err,Msg,AuxID) {}
};


#endif
