#include "glmphmenu.h"


GLMphMenu::GLMphMenu( QWidget* parent, const QFileInfoList* fileList, int& count ) : QWidget( parent )
{
  setMouseTracking( true );
  setPaletteBackgroundColor( QColor(0, 0, 0) );

  
  grid = new QGridLayout( this, 2,1, 0,0 );
  gridzik = new QGrid( 2, this ); // w tym gridzie bêd± 2 kolumny GLMphMenuItem-s
  
  
  QFileInfoListIterator it( *fileList );
  QFileInfo *fileInfo;
  QString name;
  
  GLMphMenuItem* mphItem;
  
  while ( ( fileInfo = it.current() ) != 0 )
  {
    name = fileInfo->absFilePath();
    
    mphItem = new GLMphMenuItem( gridzik, name);
    connect( mphItem, SIGNAL( mphSelected(const char*) ), this, SLOT( multiPolyhSelected(const char*) ) );
    
    count++;
    ++it;
  }
  
  grid->addWidget( gridzik, 0,0 );

  QSpacerItem *spacer = new QSpacerItem(10,10, QSizePolicy::Expanding, QSizePolicy::Expanding);
  grid->addItem(spacer,1,0);
}



void GLMphMenu::multiPolyhSelected( const char* mphPath )
{
  emit mphSelected( mphPath );
}
