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
#include <statusbar.h>


/*!
Klasa Kernel zarz±dza ³adowaniem bry³ wzorcowych oraz obiektów z³o¿onych z pliku.
*/
class Kernel : public QObject
{
  Q_OBJECT
  
  public:
    Kernel(QWidget *parent=0);
    ~Kernel();
    void init( QString initLibPath );
    ViMultiPolyh* multiPolyh();
    static void computeScene();
    static ViScene* scene() { return _scene; }
    static const ViPattePolyh* findPattePolyh( const char* objectName );
    static const ViPattePolyh* findPattePolyh( int stringListIndex );
    static const QStringList* pattePolyhList() { return _pattePolyhList; }

  private:
    static ViScene *_scene;            // scena
    static QStringList *_pattePolyhList;
    ViMultiPolyh *_multiPolyh;  // glowny obiekt zlozony
    int _count; // licznik elementów na scenie
    
    int readAllLibraries(QString path);
    void buildPattePolyhList();

  public slots:
    void addPattePolyh( const char *objectName ); // dodaje nowy obiekt jako ViElemePolyhExt
    void addMultiPolyh( const char *pathToMph, ViNTreeNode* parent ); // dodaje nowy obiekt jako ViMultiPolyh
    void loadMultiPolyh( const char *fileName );

  signals:
    void sendScene(ViScene *scene); // do drawWidget, zeby stworzyc menu z zaladowanymi brylami wzorcowymi
    void sendMultiPolyh(ViMultiPolyh *multiPolyh); // wysyla obiekt zlozony
    void sendSelected(QPtrList<ViNTreeNode> *selectedList);
    void sendPrimitiveList( QStringList* );
};

#endif
