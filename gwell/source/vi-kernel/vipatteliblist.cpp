/*-------------------------------------------------------------------------
 * \file  vipatteliblist.cpp
 * \author Bogdan Kreczmer
 * \date   2004.03.22
 *
 *  Plik zawiera implementacjê metod klasy ViPatteLibList bêd±c± list±
 *  bibliotek obiektów wzorcowych.
 */



#ifdef __GNUG__
#pragma implementation
#endif


#include "vipatteliblist.hh"
#include "viexception.hh"
#include "vinodeaddress.hh"
#include "vipatteaddress.hh"


using namespace std;


const ViPattePolyhLib *
           ViPatteLibList::FindPattePolyhLib(const char *LibName) const
{
  for (ConLibIterator Iter = Begin();
       Iter; ++Iter) {
    if (Iter->GetLibName() == LibName) return Iter;
  }
  return 0L;
}



ViPattePolyh const *ViPatteLibList::FindNormPattePolyh( const char *Name, 
                                                 const char *LibName
                                               ) const
  throw(ViException_Patte)
{
  if (LibName) {
     if  (ViPattePolyhLib const *pLib = FindPattePolyhLib(LibName)) 
          return pLib->FindNormPattePolyh(Name); 
     else throw ViException_Patte(ERRNUM_PATTE__NO_SUCH_LIBRARY,
                 (MSG(ERRMSG_PATTE__NO_SUCH_LIBRARY),Name,LibName));
  }

  const ViPattePolyh *PPolyh;

  for (ConLibIterator Iter = Begin(); Iter; ++Iter)
              if ((PPolyh = Iter->FindNormPattePolyh(Name))) return PPolyh;
  return 0L;
}





    //======================================================================
    //  Szuka specjalnej bry³y wzorcowej w podanej biliotece lub we 
    // wszystkich.
const ViPattePolyh *ViPatteLibList::FindSpecPattePolyh( const char *Name,
                                                 const char *LibName
                                               ) const
  throw(ViException_Patte)
{
  if (LibName) {
     if  (ViPattePolyhLib const *pLib = FindPattePolyhLib(LibName)) 
          return pLib->FindSpecPattePolyh(Name); 
     else throw ViException_Patte(ERRNUM_PATTE__NO_SUCH_LIBRARY,
                 (MSG(ERRMSG_PATTE__NO_SUCH_LIBRARY),Name,LibName));
  }

  const ViPattePolyh *PPolyh;

  for (ConLibIterator Iter = Begin(); Iter; ++Iter)
              if ((PPolyh = Iter->FindSpecPattePolyh(Name))) return PPolyh;
  return 0L;
}










const ViPattePolyh * ViPatteLibList::FindPattePolyh( const char *FullName ) const
                 throw (ViException_Patte)
{
  ViPatteAddress  PattAddr = FullName;

  if (!PattAddr.IsAddrOK()) 
      throw ViException_Patte(ERRNUM_SYNTAX__BAD_PATTE_ADDR,
			      (MSG(ERRMSG_SYNTAX__BAD_PATTE_ADDR),FullName));

  ExtString   LibName, PatteType, PatteName;

  PattAddr.GetLibraryName(LibName);
  PattAddr.GetPatteType(PatteType);
  PattAddr.GetPatteName(PatteName);
  
  if (PatteType == PA_TYPE_NORM) {
     return FindNormPattePolyh(PatteName, LibName == "*" ? 0L : LibName.c_str());
  }
  return FindSpecPattePolyh(PatteName, LibName == "*" ? 0L : LibName.c_str());
}
