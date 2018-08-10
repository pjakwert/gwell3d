#ifndef TOOLS_H
#define TOOLS_H


#include <qstring.h>
#include <qstringlist.h>
#include <qdir.h>
#include <qfileinfo.h>


/*!
Klasa zawiera ró¿ne przydatne metody.
*/
class Tools
{
  public:
    static QString search( const QString fileName, const QString startDir );
    static QString search( const QString fileName, const QStringList* startDirsList );
};




#endif
