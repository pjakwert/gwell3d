#ifdef __GNUG__
#pragma implementation
#endif

#include <string>
#include <cstring>
#include "vipatteaddress.hh"
#include <iostream>

using namespace std;




bool IsStringWord( const char *Str )
{
  if (!Str) return false;
  for (const char *s = Str; *s; ++s) 
    if (!isalnum(*s) && *s != '_') return false;
  return true;
}




bool ViPatteAddress::IsAddrOK() const
{
  if (Find_ith(PA_PATTEADDRSEP,2) == string::npos) return false;

  ExtString  TestName;
  if (!GetLibraryName(TestName)) return false;
  if (!(TestName == "*") && !IsStringWord(TestName)) return false;
  if (!GetPatteType(TestName)) return false;
  if (TestName != PA_TYPE_NORM && TestName != PA_TYPE_SPEC) return false;
  if (!IsStringWord(TestName)) return false;
  if (!GetPatteName(TestName)) return false;
  if (!IsStringWord(TestName)) return false;
  return true;
}




std::string ViPatteAddress::GetLibraryNameStr() const
{
  std::string  Str;
  GetLibraryName(Str);
  return Str;
}


std::string ViPatteAddress::GetPatteTypeStr() const
{
  std::string  Str;
  GetPatteType(Str);
  return Str;
}


std::string ViPatteAddress::GetPatteNameStr() const
{
  std::string  Str;
  GetPatteName(Str);
  return Str;
}



bool  ViPatteAddress::GetLibraryName( std::string &LName ) const
{
  string::size_type Idx = find(PA_PATTEADDRSEP);

  if (Idx == string::npos) return false;
  LName = substr(0,Idx);
  return true;
}



bool  ViPatteAddress::GetPatteType( std::string &TName ) const
{
  string::size_type  Idx_1 = find(PA_PATTEADDRSEP);

  if (Idx_1 == string::npos) return false;
  Idx_1 += strlen(PA_PATTEADDRSEP);

  string::size_type  Idx_2 = find(PA_PATTEADDRSEP,Idx_1);
  if (Idx_2 == string::npos) return false;
  TName = substr(Idx_1,Idx_2-Idx_1);
  return true;
}



bool  ViPatteAddress::GetPatteName( std::string &PName ) const
{
  string::size_type  Idx_1 = Find_ith(PA_PATTEADDRSEP,2);

  if (Idx_1 == string::npos) return false;
  Idx_1 += strlen(PA_PATTEADDRSEP);

  PName = substr(Idx_1);
  return true;
}
