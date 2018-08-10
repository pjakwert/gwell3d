#ifndef VIEXCEPTION_HH
#define VIEXCEPTION_HH
/*!
 * \file viexception.hh
 * \author Bogdan Kreczmer
 * \date 2004.03
 *
 * Plik zawiera definicj� klas wyj�tk�w, kt�re mog� by� zg�aszane przez
 * funkcje i metody z aplikacji projektu VIONA.
 */

#include <string>
#include "bexception.hh"

/*!
 *  Jest to klasa bazowa dla wszystkich wyjatk�w zg�aszanych w aplikacji
 *  projektu VIONA.
 */
class ViException: public Ba::Exception {
  public:
   /*!
    *  Inicjalizuje informacje o b��dzie.
    *  \param Err - numer b��du,
    *  \param Msg - komunikat b��du,
    *  \param AuxID - pomocniczy identyfikator dla okre�lenia miejsca
    *                 wyst�pienia b��du (inicjalizuje pole
    *                 \link ViException::_ErrAuxID _ErrAuxID\endlink).
    * \warning Przyjmuje si�, �e warto�� doy�lna kodu b��du 0 sygnalizuje brak b��du.
    */
  ViException(int Err = 0, const char *Msg = 0L, int AuxID = 0): 
        Ba::Exception(Err,Msg,AuxID) {}
};


/*!
 *  Obiekty tej klasy wykorzystywane s� do zg�aszania b��du przekroczenia
 *  zakresu.
 */
class ViException_OutOfRange: public ViException 
{
  public:
   /*!
    *  Inicjalizuje informacje o b��dzie.
    *  \param Err - numer b��du,
    *  \param Msg - komunikat b��du,
    *  \param AuxID - pomocniczy identyfikator dla okre�lenia miejsca
    *                 wyst�pienia b��du (inicjalizuje pole
    *                 \link ViException::_ErrAuxID _ErrAuxID\endlink).
    * \warning Przyjmuje si�, �e warto�� doy�lna kodu b��du 0 sygnalizuje brak b��du.
    */
  ViException_OutOfRange(int Err = 0, const char *Msg = 0L, int AuxID = 0):
      ViException(Err,Msg,AuxID) {}
};



/*!
 *  Obiekty tej klasy wykorzystywane s� do zg�aszania b��du wyst�puj�cego
 *  przy niezgodno�ci oblicze� z oczekiwanymi wynikami.
 */
class ViException_WrongComputation: public ViException 
{
  public:
   /*!
    *  Inicjalizuje informacje o b��dzie.
    *  \param Err - numer b��du,
    *  \param Msg - komunikat b��du,
    *  \param AuxID - pomocniczy identyfikator dla okre�lenia miejsca
    *                 wyst�pienia b��du (inicjalizuje pole
    *                 \link ViException::_ErrAuxID _ErrAuxID\endlink).
    * \warning Przyjmuje si�, �e warto�� doy�lna kodu b��du 0 sygnalizuje brak b��du.
    */
  ViException_WrongComputation( int         Err = 0,
                                const char *Msg = 0L,
                                int         AuxID = 0
                              ):  ViException(Err,Msg,AuxID) {}
};




/*!
 *  Obiekty tej klasy wykorzystywane s� do zg�aszania b��du wyst�puj�cego
 *  przy niezgodno�ci struktury danych.
 */
class ViException_DataInconsistence: public ViException 
{
  public:
   /*!
    *  Inicjalizuje informacje o b��dzie.
    *  \param Err - numer b��du,
    *  \param Msg - komunikat b��du,
    *  \param AuxID - pomocniczy identyfikator dla okre�lenia miejsca
    *                 wyst�pienia b��du (inicjalizuje pole
    *                 \link ViException::_ErrAuxID _ErrAuxID\endlink).
    * \warning Przyjmuje si�, �e warto�� doy�lna kodu b��du 0 sygnalizuje brak b��du.
    */
  ViException_DataInconsistence( int         Err = 0,
                                 const char *Msg = 0L,
                                 int         AuxID = 0
                               ):  ViException(Err,Msg,AuxID) {}
};



/*!
 *  Obiekty tej klasy wykorzystywane s� do zg�aszania b��d�w sk�adni
 *  wczytywanych plik�w.
 */
class ViException_Syntax: public ViException 
{
  public:
   /*!
    *  Inicjalizuje informacje o b��dzie.
    *  \param Err - numer b��du,
    *  \param Msg - komunikat b��du,
    *  \param AuxID - pomocniczy identyfikator dla okre�lenia miejsca
    *                 wyst�pienia b��du (inicjalizuje pole
    *                 \link ViException::_ErrAuxID _ErrAuxID\endlink).
    * \warning Przyjmuje si�, �e warto�� doy�lna kodu b��du 0 sygnalizuje brak b��du.
    */
  ViException_Syntax(int Err = 0, const char *Msg = 0L, int AuxID = 0):
      ViException(Err,Msg,AuxID) {}
};



/*!
 *  Obiekty tej klasy wykorzystywane s� do zg�aszania b��d�w
 *  zwi�zanych z obs�ug� bry� wzorcowych.
 */
class ViException_Patte: public ViException 
{
  public:
   /*!
    *  Inicjalizuje informacje o b��dzie.
    *  \param Err - numer b��du,
    *  \param Msg - komunikat b��du,
    *  \param AuxID - pomocniczy identyfikator dla okre�lenia miejsca
    *                 wyst�pienia b��du (inicjalizuje pole
    *                 \link ViException::_ErrAuxID _ErrAuxID\endlink).
    * \warning Przyjmuje si�, �e warto�� doy�lna kodu b��du 0 sygnalizuje brak b��du.
    */
  ViException_Patte(int Err = 0, const char *Msg = 0L, int AuxID = 0):
      ViException(Err,Msg,AuxID) {}
};



/*!
 *  Obiekty tej klasy wykorzystywane s� do zg�aszania b��d�w
 *  zwi�zanych z obs�ug� plik, np. b��dami otwarcia plik�w do odczytu.
 */
class ViException_File: public ViException 
{
  public:
   /*!
    *  Inicjalizuje informacje o b��dzie.
    *  \param Err - numer b��du,
    *  \param Msg - komunikat b��du,
    *  \param AuxID - pomocniczy identyfikator dla okre�lenia miejsca
    *                 wyst�pienia b��du (inicjalizuje pole
    *                 \link ViException::_ErrAuxID _ErrAuxID\endlink).
    * \warning Przyjmuje si�, �e warto�� doy�lna kodu b��du 0 sygnalizuje brak b��du.
    */
  ViException_File(int Err = 0, const char *Msg = 0L, int AuxID = 0):
      ViException(Err,Msg,AuxID) {}
};


#endif
