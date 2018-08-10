#include "vimultipolyhext.h"

ViMultiPolyhExt::ViMultiPolyhExt()
{
  SetName( "noname" );
  QString s = "_";
  setFileName( s );
}


ViMultiPolyhExt::ViMultiPolyhExt( const char *name, QString& fileName )
{
  SetName( name );
  setFileName( fileName );
}


bool ViMultiPolyhExt::ShouldCallForClassDescr( const char* className ) const
{
  return ( strcmp( className, "ViMultiPolyhExt" ) );
}
