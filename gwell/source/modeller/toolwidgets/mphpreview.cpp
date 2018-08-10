//////////////////////////////////////////////////////////////////
///
///  class: MphPreview (.cpp)
///
///  Widget do podgl±du plików z bry³ami z³o¿onymi
///
//////////////////////////////////////////////////////////////////
#include "mphpreview.h"


// konstruktor
MphPreview::MphPreview( QWidget *parent ) : QFrame( parent )
{
  grid = new QGridLayout( this, 1,1, 5,5 );
  
  _mphItem = new GLMphMenuItem( this, "__________" );
  
  _mphItem->blockSignals( true );
  _mphItem->setMinimumSize( 150,150 );
  
  grid->addWidget( _mphItem, 0,0 );
}


MphPreview::~MphPreview() {}


void MphPreview::previewUrl( const QUrl &u )
{
  QString path = u.path();
  _mphItem->setMultiPolyh( path );
  QToolTip::remove( _mphItem );
}

