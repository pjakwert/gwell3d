#ifdef __GNUG__
#pragma implementation
#endif

/*------------------------------------------------------------------
 *  \file strprintf.cpp
 *  \author Bogdan Kreczmer
 *  \date   2004.03.24
 *
 *   Zawiera implementacjê metod klasy StrPrintf.
 */
#include <cstring>
#include <sstream>
#include "strprintf.hh"

#define SP_INT     "%i"
#define SP_UNSINT  "%u"
#define SP_STR     "%s"
#define SP_CHAR    "%c"
#define SP_FLOAT   "%f"
#define SP_DOUBLE  "%g"

using namespace std;

template <class Type>
StrPrintf &InsertIntoStr(StrPrintf &SPrn, Type Arg, const char *Format) 
{
  std::string::size_type Pos = SPrn.find(Format);
  if (Pos == std::string::npos) return SPrn;
  std::ostringstream  IStr;
  IStr << Arg;
  SPrn.replace(Pos,strlen(Format),IStr.str().c_str());
  return SPrn;
}


StrPrintf &StrPrintf::operator << (int Arg) 
{
  return  InsertIntoStr(*this,Arg,SP_INT);
}




StrPrintf &StrPrintf::operator << (unsigned int Arg) 
{
  return  InsertIntoStr(*this,Arg,SP_UNSINT);
}



StrPrintf &StrPrintf::operator << (const char* Arg) 
{
  return  InsertIntoStr(*this,Arg,SP_STR);
}


StrPrintf &StrPrintf::operator << (char Arg) 
{
  return  InsertIntoStr(*this,Arg,SP_CHAR);
}



StrPrintf &StrPrintf::operator << (float Arg) 
{
  return  InsertIntoStr(*this,Arg,SP_FLOAT);
}


StrPrintf &StrPrintf::operator << (double Arg) 
{
  return  InsertIntoStr(*this,Arg,SP_DOUBLE);
}
