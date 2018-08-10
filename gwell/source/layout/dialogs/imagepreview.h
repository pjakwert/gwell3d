//////////////////////////////////////////////////////////////////
///
///  class: ImagePreview (.h)
///
///  Widget do podgl±du plików graficznych w QFileDialog
///
//////////////////////////////////////////////////////////////////
#ifndef IMAGEPREVIEW_H
#define IMAGEPREVIEW_H

#include <qfiledialog.h>
#include <qlabel.h>
#include <qurl.h>
#include <qstring.h>
#include <qpixmap.h>
#include <qimage.h>
#include <qlayout.h>
#include <qvbox.h>

#include <math.h>

class ImagePreview : public QFrame, public QFilePreview
{
  Q_OBJECT
  
  public:
    ImagePreview( QWidget *parent=0 );
    ~ImagePreview();
    virtual void previewUrl( const QUrl &u );
  
  protected:
    void resizeEvent( QResizeEvent *e );
    
  private:
    QImage* image;
    QLabel* imgLabel;
    QLabel* oldSizeLabel;
    QLabel* newSizeLabel;
    QLabel* bppLabel;
    
    void setInfo( QString oldSize=QString::null, QString newSize=QString::null, QString bpp=QString::null );
};

#endif
