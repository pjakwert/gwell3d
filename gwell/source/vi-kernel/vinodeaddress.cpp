/*-------------------------------------------------------------------------
 * \file vinodeaddress.cpp
 * Plik zawiera implementacjê metod klasy ViNodeAddress. Obiekty tej klasy
 * wykorzystywane s± do tworzenia adresów wêz³ów w strukturze drzewiastej
 * tworzonej w oparciu obiekty klasy ViElemePolyh i ViMultiPolyh.
 * \author Bogdan Kreczmer
 * \date   2003.10
 */



#ifdef __GNUG__
#pragma implementation
#endif

#include <cstdio>
#include <cstring>
#include "vinodeaddress.hh"


/*
  Skladnia adresu
 
    .Etykieta1.Etykieta2.Etykieta3. ... .EtykietaN
    0    1        2         3              N
    ^
    Root
 */

int  ViNodeAddress::GetNextLabel(ExtString &NodeLabel)
{
  int  err = GetLabel_ith(_No+1,NodeLabel);
  return err ? err : (_No++, 0) ;
}


int  ViNodeAddress::GetFirstLabel(ExtString &NodeLabel)
{
  _No = 1;
  return GetLabel_ith(1,NodeLabel);
}


int ViNodeAddress::ExtractHead(unsigned Len, ViNodeAddress &Addr) const
{
  if (IsEmpty()) { Addr = "";  return -1; }

  char const *pBeg = (*this)(), *pEnd;
  if (!Len)  {  Addr = "";  return -2; }
  for (pEnd = pBeg+1; Len && (pEnd = strchr(pEnd,NA_SEPARATOR)); Len--);
  if (!pEnd) { Addr = *this;  return -3; }
  Addr.Copy(pBeg,pEnd-1);
  return 0;
}


bool ViNodeAddress::IsHeadOf(ViNodeAddress const& Addr) const
{
  int HdLen = Addr.AddressLength();
  int Len   = AddressLength();
  if (Len > HdLen) return 0;
  if (Len == HdLen) {
    return Addr == *this;
  }

  ViNodeAddress  Addr_i;
  int err;
  if ((err = Addr.ExtractHead(Len,Addr_i))) return err;
  if (*this == Addr_i) return 1;
  return 0;
}


int ViNodeAddress::GetLabel_ith(unsigned int Idx, ExtString &NodeLabel) const
{
  if (!Idx) { NodeLabel = "";  return 0; }

  char const *pEnd;
  char const *pBeg;

  if  (IsEmpty()) return -1;
  if  (*c_str() != NA_SEPARATOR) return -2;
  pBeg = c_str();

  for (; Idx && (pBeg = strchr(pBeg,NA_SEPARATOR)); Idx--, pBeg++);
  if (!pBeg) return -3; 

  if (!*(pBeg+1)) return -4;
  if  ((pEnd = strchr(pBeg,NA_SEPARATOR))) {
     NodeLabel.Copy(pBeg,pEnd-1);    
     return 0;
  } 
  NodeLabel = pBeg;
  return 0;
}



//int ViNodeAddress::ExtractWithoutLast(ExtString &Path) const
int ViNodeAddress::ExtractPath(ExtString &Path) const
{
  if (IsEmpty()) return -1;
  if  (*c_str() != NA_SEPARATOR) return -2;

  char const *pBeg, *pEnd = c_str()+1;
  int  Idx = 1;

  for (pBeg = pEnd; 
        (pEnd = strchr(pEnd,NA_SEPARATOR)); 
        Idx++, pBeg = pEnd, pEnd++);

  Path.Copy(c_str(),pBeg);
  return 0;
}


int ViNodeAddress::ExtractWithoutLast(ExtString &Path) const
{
  if (IsEmpty()) return -1;
  if  (*c_str() != NA_SEPARATOR) return -2;

  char const *pBeg, *pEnd = c_str()+1;
  int  Idx = 1;

  for (pBeg = pEnd; 
        (pEnd = strchr(pEnd,NA_SEPARATOR)); 
        Idx++, pBeg = pEnd, pEnd++);

  Path.Copy(c_str(),pBeg-1);
  return 0;
}


int ViNodeAddress::ExtractLastLabel(ExtString &Label) const
{
  int No = AddressLength();

  if (No <= 0) return -4;
  return GetLabel_ith(No-1,Label);
}


int ViNodeAddress::AddLabel(char const *Label)
{
  if (!IsSeparatorAtEnd()) *this << NA_SEPARATOR;
  *this << Label;
  return 0;
}

//-----------------------------------------------------
// Ostatni separator nie jest liczony jesli nie ma za
// nim nazwy wezla
unsigned int ViNodeAddress::AddressLength() const
{
  unsigned int No = 0;

  if (IsEmpty()) return 0;
  for ( char const *pWrk = c_str(); (
        (pWrk = strchr(pWrk,NA_SEPARATOR))) && *(pWrk+1); 
        pWrk++, No++);
  return No+1;
}

ViNodeAddress &ViNodeAddress::operator = (char const * const Str)
{
  return *((ViNodeAddress*) &(*(ExtString*)this = Str));
}


ViNodeAddress &ViNodeAddress::operator = (char const c)
{
  return *((ViNodeAddress*) &(*(ExtString*)this = c));
}


