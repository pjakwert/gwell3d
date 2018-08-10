/*--------------------------------------------------------------------
 * \file  vipattepolyhlib.cpp
 * \author Bogdan Kreczmer
 * \date   2004.03
 *
 *  Plik zawiera implementacjê metod klasy ViPattePolyhLib stanowi±c± 
 *  bibliotekê obiektów wzorcowych.
 */


#ifdef __GNUG__
#pragma implementation
#endif


#include "extstring.hh"
#include "vipattepolyh.hh"
#include "vipattepolyhlib.hh"
#include "vipatteaddress.hh"
#include "viexception.hh"









ViPattePolyh *ViPattePolyhLib::AddNormPattePolyh(ViPattePolyh *pPPolyh)
{
  if (!pPPolyh) 
    if (!(pPPolyh = new ViPattePolyh())) return 0L;
 return _NormPattePolyh.AddToTail(pPPolyh);
}


ViPattePolyh *ViPattePolyhLib::AddSpecPattePolyh(ViPattePolyh *pPPolyh)
{
  if (!pPPolyh) 
    if (!(pPPolyh = new ViPattePolyh())) return 0L;
 return _SpecPattePolyh.AddToTail(pPPolyh);
}



const ViPattePolyh *ViPattePolyhLib::FindNormPattePolyh(char const *name) const
{
  for (const ViPattePolyh *pPPolyh = _NormPattePolyh.First(); pPPolyh;  
       pPPolyh = pPPolyh->Next())
     if (pPPolyh->GetStrName() == name) return pPPolyh;
  return 0L;
}


const ViPattePolyh *ViPattePolyhLib::FindSpecPattePolyh(char const *name) const
{ 
  for (const ViPattePolyh *pPPolyh = _SpecPattePolyh.First(); pPPolyh;  
       pPPolyh = pPPolyh->Next())
    if (pPPolyh->GetStrName() == name) return pPPolyh;
  return 0L;
}

ViPattePolyhLib::ViPattePolyhLib():
 _NormPattePolyh(*this,PA_TYPE_NORM), _SpecPattePolyh(*this,PA_TYPE_SPEC)
{}

ViPattePolyhLib::~ViPattePolyhLib(void)
{}
