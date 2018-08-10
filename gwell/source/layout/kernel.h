#ifndef KERNEL_H
#define KERNEL_H


#include <qobject.h>
#include <qwidget.h>
#include <qdir.h>

#include <iostream>
#include <iomanip>

// vi-kernel
#include <matrixh3f.hh>
#include <vipattepolyhlib.hh>
#include <vimultipolyh.hh>
#include <vielemepolyh.hh>
#include <vi-readpattepolyhlib.hh>
#include <viscene.hh>
#include <extstring.hh>
#include <strprintf.hh>
#include <viface.hh>
#include <vierrors.hh>
#include <vinodeaddress.hh>
#include <vihierarchyline.hh>
#include <vi-readmultipolyh.hh>

#include <qstringlist.h>

#include <vielemepolyhext.h>
#include <vimultipolyhext.h>
#include <statusbar.h>
#include <options.h>
#include <tools.h>


class ViMultiPolyhExt;

class Kernel : public QObject
{
  Q_OBJECT
  
  public:
    Kernel(QWidget *parent=0);
    ~Kernel();
    void init( QString initLibPath );
    static void computeScene();
    static ViScene* scene() { return _scene; }

  private:
    static ViScene *_scene;            // scena
    int _count; // licznik elementów na scenie
    
    int readAllLibraries(QString path);

  public slots:
    ViMultiPolyhExt* readMultiPolyh( const char *pathToMph );
    void addMultiPolyh( const char *pathToMph ); // dodaje nowy obiekt ViMultiPolyh
    void addMultiPolyh( const char *pathToMph, const char* name, const Vector3f& trans, const Vector3f& rotDeg, const Vector3f& scale ); // dodaje nowy obiekt, zadaje transformacje, ale nie wysy³a sceny
    

  signals:
    void sendScene(ViScene *scene); // wysy³a scenê
};

#endif
