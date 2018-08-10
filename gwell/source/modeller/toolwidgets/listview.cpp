#include "listview.h"


#define expandID    0
#define collapseID  1
#define kinematicID 2



ListView::ListView( QWidget * parent, QToolButton* treeViewButton, const char * name, WFlags f ) : QListView(parent,name,f)
{
  _treeViewButton = treeViewButton;
  
  popup = new QPopupMenu( this );
  popup->insertItem( tr("expand All"), expandID );
  popup->insertItem( tr("collapse"), collapseID );
  popup->insertSeparator();
  popup->insertItem( tr("Kinematics"), kinematicID );
  connect( popup, SIGNAL( aboutToShow() ), this,  SLOT ( popupAboutToShow() ) );
  connect( popup, SIGNAL( activated(int) ), this, SLOT ( choosedFromPopup(int) ) );
}
    


// rozwija pelne drzewo
void ListView::expandAll()
{
  QListViewItemIterator it(this);
  QListViewItem *item;
  while (it.current())
  {
    item = it.current();
    this->setOpen(item, true);
    ++it;
  }
}


// zwija drzewo
void ListView::collapseAll()
{
  QListViewItemIterator it(this);
  QListViewItem *item;
  while (it.current())
  {
    item = it.current();
    this->setOpen(item, false);
    ++it;
  }
}



    
/*!
Metoda obs³uguje zdarzenie wystêpuj±ce zanim otwarte zostanie popup menu.
Ukrywa opcje rozwijania i zwijania drzewa, gdy wy¶wietlana jest lista
*/
void ListView::popupAboutToShow()
{
  bool on;
  if ( _treeViewButton->isOn() ) on=true; // w³±czony widok drzewa
  else on=false;
  popup->setItemEnabled( expandID, on );
  popup->setItemEnabled( collapseID, on );
  
  if ( CellFrame::multiPolyh() == 0L )//  mp jest pusty
  on = false; else on = true;
  popup->setItemEnabled( kinematicID, on );
}

/*!
Metoda obs³uguje zdarzenie wyboru opcji z popup Menu - zwija lub rozwija drzewo.
*/
void ListView::choosedFromPopup( int id )
{
  switch ( id )
  {
    case expandID    : expandAll(); break;
    case collapseID  : collapseAll(); break;
    case kinematicID : {
                          KinematicsEditor *ke = new KinematicsEditor( CellFrame::selected(), this );
                       } break; // tutaj edytor kinematyki
  }
}


/*!
Obs³uga zdarzenia klikniêcia mysz±. Prawy przycisk pokazuje popup menu.
*/
void ListView::contentsMousePressEvent( QMouseEvent *e )
{
  if ( e->button() == Qt::RightButton )
  {
    popup->exec( QCursor::pos() );
  }
  else QListView::contentsMousePressEvent(e);
}
