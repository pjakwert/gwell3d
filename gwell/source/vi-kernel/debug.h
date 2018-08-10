/*
 * File:	debug.h
 * Purpose:	 Umozliwia pisanie komunikatow do zbioru LOGFILE (Windows)
 *            lub do standardowego wyjscia (Unix).
 * Author:	Pawel Rogalinski
 * Created:	Marzec 1995
 * Updated:
 * Copyright:	(c) 1995, Pawel Rogalinski
 */


#ifdef __GNUG__
#pragma interface
#endif


#ifndef DEBUG_H
#define DEBUG_H



#include <fstream>


#define  LogFile  std::cout


class LogFileFlush {};
class LogFileCopy {};

extern LogFileCopy  CP;
extern LogFileFlush LF;
std::ostream &operator << (std::ostream &out, LogFileFlush &Flush);
std::ostream &operator << (std::ostream &out, LogFileCopy &Copy);

#endif
