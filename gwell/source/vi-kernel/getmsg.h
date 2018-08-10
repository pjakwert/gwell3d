/*
 * File:	getmsg.h
 * Purpose: Komunikaty w  wxICARS
 * Author:	Bogdan Kreczmer
 * Created:	Kwiecien 1995
 * Updated:
 * Copyright:	(c) 1995, Bogdan Kreczmer
 */

#ifndef GETMSG_H
#define GETMSG_H

#ifdef __GNUG__
#pragma interface
#endif

#ifndef STDARG_H
#include <stdarg.h>
#define STDARG_H
#endif
#include <string>




#define  ALLOC_OBJ_STR(s)  new char[s]
#define  RELEASE(ptr)  delete [] (ptr)

extern int  errGetMsg;


void ReleaseStr( char **pStr);
char* KernelTransformMsg( char const * const FMsg, 
                          char const *format, 
                          va_list      APtr
                        );
char* TransformMsg( char* Msg, char const * format, ... );
int   ReadMsg( char const *nameFile, int no, char **ptrMsg );
char* KernelFGetMsg( int          NoErr, 
                     char const  *fileName, 
                     char const  *format, 
                     va_list      AList 
                   );
char* FGetMsg( int NoErr, char const * fileName, char const * format, ... );
std::string  SGetMsg( int NoErr, char const * format, ... );
#endif
