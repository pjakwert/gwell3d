#include "viedgeiterator.hh"
#include "viedge.hh"

int ViEdgeIterator::Index() const 
{ 
  return _WrkEdge - _EdgeTab; 
}


ViEdgeIterator &ViEdgeIterator::operator -- () 
{ 
  if (!(_OpStatus = ((_WrkEdge - _EdgeTab) > 0))) return *this;
  _WrkEdge--;
  return *this;
}



ViEdgeIterator &ViEdgeIterator::operator ++ ()
{ 
  if (!(_OpStatus = ((_WrkEdge - _EdgeTab) < (int)_EdgesNo))) return *this; 
  _WrkEdge++;
  return *this;
}
