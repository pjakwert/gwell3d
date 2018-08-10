#include "tools.h"




/*!
Metoda realizuje rekursywne przeszukiwanie pliku wg³±b rozpoczynaj±c od podanego katalogu.
/return fileName - pe³na ¶cie¿ka do znalezionego pliku,
/return QString::null() - je¿eli pliku nie znaleziono lub podany katalog nie istnieje.
*/
QString Tools::search( const QString fileName, const QString startDir )
{
  QDir files( startDir );
  QDir dirs( startDir );
  
  if ( !dirs.exists() ) return QString::null;
  
  files.setFilter( QDir::Files | QDir::Hidden );
  files.setNameFilter( fileName );
  
  dirs.setFilter( QDir::Dirs | QDir::Hidden | QDir::NoSymLinks | QDir::Readable | QDir::Executable );
  dirs.setSorting( QDir::Name );
  QFileInfoListIterator it( *(dirs.entryInfoList()) );
  QFileInfo *dirInfo;
  
  if ( !dirs.entryInfoList()->isEmpty() )
  {
    while ( (dirInfo = it.current()) != 0 )
    {
      if ( (dirInfo->fileName() != ".") && (dirInfo->fileName() != "..") )
      {
        QString s = search( fileName, dirInfo->absFilePath() );
        if ( s != QString::null ) return s;
      }
      ++it;
    }
  }
  
  if ( files.entryInfoList()->isEmpty() ) return QString::null;
  else
  {
    QFileInfoListIterator fii( *(files.entryInfoList()) );
    QFileInfo *fi = fii.current();
    if (fi) return fi->absFilePath(); else return QString::null;
  }
    
}




QString Tools::search( const QString fileName, const QStringList* startDirsList )
{
  for ( QStringList::ConstIterator it = startDirsList->begin(); it != startDirsList->end() ; ++it )
  {
      QString s = search( fileName, *it );
      if ( s != QString::null ) return s;
  }
  
  return QString::null;
}



