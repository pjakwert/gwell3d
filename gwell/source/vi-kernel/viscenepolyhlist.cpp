
#ifdef __GNUG__
#pragma implementation
#endif


#include "viscenepolyhlist.hh"
#include "vimultipolyh.hh"
#include "vinodeaddress.hh"
#include "viexception.hh"
#include <iostream>

using namespace std;



const ViMultiPolyh *ViScenePolyhList::GetFirstMultiPolyh() const 
                                                throw(ViException)
{
  const ViNTreeNode *pHrPolyh = FirstDesc();

  if (!pHrPolyh) return 0L;
  if (pHrPolyh->GetViClassID() != IT_MULTIPOLYH)
    throw ViException(ERRNUM_HIER__NO_MULTI_AT_TOP,
            (MSG(ERRMSG_HIER__NO_MULTI_AT_TOP),pHrPolyh->IndivName().c_str(),
                                              pHrPolyh->GetFinalClassName()));
  return (const ViMultiPolyh*) pHrPolyh;
}



ViMultiPolyh *ViScenePolyhList::
              MoveFirstMultiPolyh(ViScenePolyhList & MList) //throw(ViException)
{
  ViMultiPolyh *pPolyh = GetFirstMultiPolyh();
  if (!pPolyh) return 0L;
  MList.AddMultiPolyh(pPolyh);
  return pPolyh;
}





void ViScenePolyhList::ComputeGlbVtx()
{
  _GlbOutlineBox.Reset();
  for (ViNTreeNode *pPolyh = FirstDesc(); 
                          pPolyh; pPolyh = pPolyh->NextNode()) {
    ((ViMultiPolyh*)pPolyh)->ComputeHierAllGlbVtx();
    _GlbOutlineBox.Join(((ViMultiPolyh*)pPolyh)->GetOutlineBox());
  }
}




const ViNTreeNode *ViScenePolyhList::
                        GetNodeUsingAddress( const ViNodeAddress & Addr ) const
{
  if (Addr == ".") return this;

  ExtString  NodeLabel;
  int        Idx = 1;
  const ViNTreeNode *pPolyh = this;
  int err; 

  for (int AddrLen = Addr.AddressLength(); Idx < AddrLen; ++Idx) {
        err = Addr.GetLabel_ith(Idx,NodeLabel); 
        if (!(pPolyh = pPolyh->SeekNodeInLayer(NodeLabel))) return 0L;
  }
  return pPolyh;
}




ViMultiPolyh *ViScenePolyhList::AddMultiPolyh(ViMultiPolyh *pMPolyh)
  throw (ViException)
{
  ViNodeAddress Addr = ".";
  Addr += pMPolyh->IndivName();
  if (GetNodeUsingAddress(Addr)) 
    throw ViException(ERRNUM_POLYH__IS_MULTI_ALREADY,
                      (MSG(ERRMSG_POLYH__IS_MULTI_ALREADY),pMPolyh->IndivName()));
  return (ViMultiPolyh *) AddNode(pMPolyh);
}





void ViScenePolyhList::AddUsingAddress( ViNTreeNode *      pPolyh, 
                                        const ViNodeAddress &  Addr 
					) throw (ViException)
{
  ViNodeAddress  TreePath;

  Addr.ExtractWithoutLast(TreePath);

  
  if (TreePath == ".") {
    if (pPolyh->GetViClassID() != IT_MULTIPOLYH) {
      throw ViException(ERRNUM_HIER__TOP_NO_MULTI,
                       (MSG(ERRMSG_HIER__TOP_NO_MULTI),pPolyh->IndivName(),
                                                      pPolyh->GetClassName()));
    }
  }
  ViNTreeNode *pParentPolyh = GetNodeUsingAddress(TreePath);
  if (pParentPolyh->SeekNodeInLayer(pPolyh->IndivName())) 
    throw ViException(1,(MSG(ERRMSG_POLYH__IS_NODE_ALREADY),
             pPolyh->IndivName().c_str(),TreePath.c_str(),
             TreePath.c_str(),pPolyh->IndivName().c_str()));

  if (!pParentPolyh) {
    throw ViException(ERRNUM_HIER__NO_VALID_ADDR,(MSG(ERRMSG_HIER__NO_VALID_ADDR),
                          Addr.c_str(),pPolyh->IndivName().c_str()));
  }
  pParentPolyh->AddNode(pPolyh);
}
