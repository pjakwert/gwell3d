//////////////////////////////////////////////////////////////////
///
///  class: ImagePreview (.cpp)
///
///  Widget do podgl±du plików graficznych w QFileDialog
///
//////////////////////////////////////////////////////////////////

#include "imagepreview.h"


// konstruktor
ImagePreview::ImagePreview( QWidget *parent ) : QFrame( parent )
{
	image = new QImage;
	imgLabel = new QLabel( this );
	imgLabel->setAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
	imgLabel->setFrameStyle( QFrame::Sunken | QFrame::Box );
	imgLabel->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
	
	QVBox* infoBox = new QVBox( this );
	infoBox->setFrameStyle( QFrame::Sunken | QFrame::Box );
	oldSizeLabel = new QLabel( tr("image size:"), infoBox );
	newSizeLabel = new QLabel( tr("image resized:"), infoBox );
	bppLabel = new QLabel( tr("bits per pixel:"), infoBox );
	
	//QSpacerItem spacer = new QSpacerItem(10,10, QSizePolicy::Expanding, QSizePolicy::Expanding );
	
	QGridLayout *grid = new QGridLayout( this, 2,1, 0,5 );
	grid->addWidget( imgLabel, 0,0);
	grid->addWidget( infoBox, 1,0);
	//grid->addItem( spacer, 1,0 );
}


ImagePreview::~ImagePreview() {}


void ImagePreview::previewUrl( const QUrl &u )
{
	QString path = u.path();
	if (!image->isNull()) delete image;
	image = new QImage( path );
	
  if ( image->isNull() ) { imgLabel->clear(); setInfo(); }
	else
	{
		int w = imgLabel->width()-5;
		int h = imgLabel->height()-5;
		
		if ( (image->width() > w) || (image->height() > h) )
		{
			QImage img( image->scale( w, h, QImage::ScaleMin ) );
			QPixmap pix( img );
			imgLabel->setPixmap( pix );
		}
		else 
		{
			QPixmap pix( *image );
			imgLabel->setPixmap( pix );
		}

		QString os = QString("%1x%2").arg(image->width()).arg(image->height());
		
  	int newWidth  = 1 << (int) (1 + log(image->width() -1+1E-3) / log(2.0));
  	int newHeight = 1 << (int) (1 + log(image->height()-1+1E-3) / log(2.0));

		QString ns = QString("%1x%2").arg(newWidth).arg(newHeight);
		
		setInfo( os, ns, QString::number( image->depth() ) );
	}
}


void ImagePreview::resizeEvent( QResizeEvent *e )
{
	if ( image->isNull() ) return;
	
	int w = imgLabel->size().width()-5;
	int h = imgLabel->size().height()-5;
	
	if ( (image->width() > w) || (image->height() > h) )
	{
		QImage img( image->scale( w, h, QImage::ScaleMin ) );
		QPixmap pix( img );
		imgLabel->setPixmap( pix );
	}
	else 
	{
		QPixmap pix( *image );
		imgLabel->setPixmap( pix );
	}
}


void ImagePreview::setInfo( QString oldSize, QString newSize, QString bpp )
{
	oldSizeLabel->setText(tr("image size: %1").arg(oldSize));
	newSizeLabel->setText(tr("image resized: %1").arg(newSize));
	bppLabel->setText(tr("bits per pixel: %1").arg(bpp));
}
