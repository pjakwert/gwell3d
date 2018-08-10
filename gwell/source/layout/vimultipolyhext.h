#ifndef VIMULTIPOLYHEXT_H
#define VIMULTIPOLYHEXT_H

#include <qstring.h>

#include <const.h>
#include <kernel.h>
#include <options.h>



DEFPOLYHCLASS( ViMultiPolyhExt, ViMultiPolyh )
{
  public:
    ViMultiPolyhExt();
    ViMultiPolyhExt( const char *name, QString& fileName );
    ~ViMultiPolyhExt() {}
    bool ShouldCallForClassDescr( const char* className ) const;
    
    void setFileName( QString& fileName ) { _fileName = fileName; }
    QString& fileName() { return _fileName; }
  
  private:
    QString _fileName;
};




#endif
