#ifdef __GNUG__
#pragma implementation
#endif


#include "vielemepolyhedge.hh"
#include "vielemepolyh.hh"


std::ostream &operator << (std::ostream &ostrm, ViElemePolyhEdge const &Edge)
{
  return ostrm << "[" << Edge.GetFstVtx() << ", " << Edge.GetSndVtx() 
               << "] ["  << Edge.GetLeftFaceIdx() << ", "
               << Edge.GetRightFaceIdx() << "]";
}



ViElemePolyhEdge::ViElemePolyhEdge( const ViElemePolyh &EPolyh, 
                                    const ViEdge *pEdge
                                  ):
      _Owner(EPolyh), _pEdge(pEdge) {}


ViElemePolyhEdge::ViElemePolyhEdge( const ViElemePolyh &EPolyh, 
                                    unsigned int Idx
                                  ):
      _Owner(EPolyh), _pEdge(EPolyh.PattPolyh().GetPolyhEdge(Idx)) {}



unsigned int ViElemePolyhEdge::GetLeftFaceIdx() const
{
  return _pEdge->GetLeftFaceIdx();
}


unsigned int ViElemePolyhEdge::GetRightFaceIdx() const
{
  return _pEdge->GetRightFaceIdx();
}


const Vector3f &ViElemePolyhEdge::GetFstVtx() const 
        { return _Owner.GlbVtx(_pEdge->GetFirstVtxIdx()); }


const Vector3f &ViElemePolyhEdge::GetSndVtx() const 
        { return _Owner.GlbVtx(_pEdge->GetSecondVtxIdx()); }

ViElemePolyhFace const *ViElemePolyhEdge::GetRightFace() const
{ 
  return _pEdge->IsRightFace() ?
                      _Owner.GetElemeFace(_pEdge->GetRightFaceIdx()) : 0L; 
}


ViElemePolyhFace const *ViElemePolyhEdge::GetLeftFace() const
{ 
  return _pEdge->IsLeftFace() ?
                      _Owner.GetElemeFace(_pEdge->GetLeftFaceIdx()) : 0L; 
}
