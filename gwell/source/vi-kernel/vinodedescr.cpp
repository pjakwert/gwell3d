#ifdef __GNUG__
#pragma implementation
#endif

#include "vinodedescr.hh"
#include "vi-keywords.hh"

using namespace std;


//================================================================================
//.........................  ViNodeDescr  ........................................

ViNodeDescr & ViNodeDescr::operator = (const char *str)
{
  return  *(ViNodeDescr*)&((*(ExtString*)this) = str);
}


int ViNodeDescr::ClassesNum() const
{
 int  CNo = 1;
 
 if (!FindFirstSecBeg()) return 0;
 while (FindNextSecBeg()) ++CNo;
 return CNo;
}


bool ViNodeDescr::FindFirstSecBeg() const
{
 return ((*(ViNodeDescr*)this)._SecIdx = find(KW_BEGIN_DERIVSEC)) != string::npos;
}


bool ViNodeDescr::FindNextSecBeg() const
{
 return ((*(ViNodeDescr*)this)._SecIdx = find(KW_BEGIN_DERIVSEC,_SecIdx+1)) != 
                                                                    string::npos;
}


bool ViNodeDescr::FindNextSecEnd() const
{
 return ((*(ViNodeDescr*)this)._SecIdx = find(KW_END_DERIVSEC,_SecIdx+1)) != 
                                                                     string::npos;
}



bool ViNodeDescr::GetClassDescr(const char *ClassName, ExtString &Desc) const
{
  // Szukanie jest bardziej rozbudowane, aby zabezpieczyc sie przed
  // przypadkiem roznej ilosci bialych znakow miedzy slowem kluczowym
  // i nazwa klasy.
  ExtString  CName;
  string::size_type  Idx_o;

  if (!FindFirstSecBeg()) return false;
  while (GoToSpaceChar(), (Idx_o = GetNotSpacedString(_SecIdx,CName)) != string::npos) {
    if (CName == ClassName) {
      Idx_o = GoToNotSpaceChar(Idx_o);
      if (!FindNextSecEnd()) return false;
      Desc = substr(Idx_o, GetSecIdx()-Idx_o);
      return true;
    }
    if (!FindNextSecBeg()) return false;
  }
  return false;
}


bool ViNodeDescr::GetClassDescr(unsigned int Idx, ExtString &Desc) const
{
  if (!FindFirstSecBeg()) return false;
  while (Idx > 0) { 
    if (!FindNextSecBeg()) return false;
    --Idx;
  }
  string::size_type  Idx_o = SkipLine(GetSecIdx());
  if (Idx_o == string::npos) return false;
  /* Warto¶æ tego indeksu wskazuje na pierwszy znak ró¿ny od znaku bia³ego */
  /* znajduj±cy siê za s³owem kluczowym opisu sekcji.                      */
  if (!FindNextSecEnd())  return false;
  Desc = substr(Idx_o, GetSecIdx()-Idx_o);
  return true;
}


bool ViNodeDescr::GoToSpaceChar() const
{
  string::size_type Idx = ExtString::GoToSpaceChar(_SecIdx+1);
  if (Idx == string::npos) return false;
  (*(ViNodeDescr*)this)._SecIdx = Idx;
  return true;
}


bool ViNodeDescr::GetClassName(unsigned int Idx, ExtString &ClassName) const
{
  string::size_type  Idx_Store = _SecIdx;

  if (!FindFirstSecBeg()) { 
      (*(ViNodeDescr*)this)._SecIdx = Idx_Store;  return false; 
  }
  while (Idx) { 
    if (!FindNextSecBeg()) {
      (*(ViNodeDescr*)this)._SecIdx = Idx_Store;  return false;
    }
    --Idx;
  }
  if (!GoToSpaceChar()) { 
     (*(ViNodeDescr*)this)._SecIdx = Idx_Store;  return false;
  }

  if (GetNotSpacedString(_SecIdx,ClassName) == string::npos) return false;
  (*(ViNodeDescr*)this)._SecIdx = Idx_Store;
  return true;
}



bool ViNodeDescr::GetTopClassName(ExtString &ClassName) const 
{
  int Idx = ClassesNum();
  if ( Idx < 1 ) return false;
  return GetClassName((unsigned int)(Idx)-1,ClassName);  
}

//..........................  ViNodeDescr  ......................................
//===============================================================================

