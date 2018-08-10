//////////////////////////////////////////////////////////////////
///
///  class: MphPreview (.h)
///
///  Widget do podgl±du plików z bry³ami z³o¿onymi
///
//////////////////////////////////////////////////////////////////
#ifndef MPHPREVIEW_H
#define MPHPREVIEW_H

#include <qfiledialog.h>
#include <qlabel.h>
#include <qurl.h>
#include <qstring.h>
#include <qlayout.h>

#include <math.h>

#include <glmphmenuitem.h>


class MphPreview : public QFrame, public QFilePreview
{
  Q_OBJECT
  
  public:
    MphPreview( QWidget *parent=0 );
    ~MphPreview();
    virtual void previewUrl( const QUrl &u );
    
  private:
    GLMphMenuItem* _mphItem;
    QGridLayout* grid;
};

#endif
