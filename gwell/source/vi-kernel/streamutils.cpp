#include "streamutils.hh"

std::ostream &Space(std::ostream &ostrm, unsigned int SpaceNo)
{
  for (unsigned int i = 0; i < SpaceNo; i++)  ostrm << " ";
  return ostrm;
}
