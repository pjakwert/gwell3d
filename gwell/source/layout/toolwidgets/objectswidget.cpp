//////////////////////////////////////////////////////////////////
///
///  class: ObjectsWidget (.cpp)
///
///  widget zawieraj±cy ObjectExplorer-a
///
//////////////////////////////////////////////////////////////////

#include "objectswidget.h"



// konstruktor
ObjectsWidget::ObjectsWidget( QString title, QWidget *parent, const char *name ) : QWidget( parent, name )
{
    globalGrid = new QGridLayout(this, 1,1, 0,0);

    mainBox = new QGroupBox( this );
    mainBox->setTitle( title );
    
    QGridLayout *mainGrid = new QGridLayout( mainBox, 3,1, 10,5 ); // 3rows+wype³niacz, 1col
    
    QSpacerItem* upperSpacer = new QSpacerItem( 5, 15, QSizePolicy::Expanding, QSizePolicy::Fixed );
    mainGrid->addItem( upperSpacer, 0,0 );
    
    ////////////////////// drzewo
      listView = new QListView( mainBox );
      listView->setRootIsDecorated(true);
      listView->setAllColumnsShowFocus( true );           // zaznacza wszystkie kolumny
      listView->setShowSortIndicator( false );            // nie pokazuj wska¼nika sortowania
      listView->setSelectionMode( QListView::Extended );  // tryb zaznaczania
      listView->setRootIsDecorated( true );               // poka¿ plusiki rozwijania
      //   listView->setSorting(-1);                         // nie sortuj
      listView->addColumn(QIconSet(QPixmap(Icons::showAllSceneIcon())), tr("Object"));
      
      listView->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Expanding );
      
      QFont f( this->font() );
      f.setPointSize( f.pointSize() - 2 );
      listView->setFont( f );
    mainGrid->addWidget( listView, 1,0 );
    
    ////////////////////// dolny LineEdit
      addrEdit = new QLineEdit( mainBox );
      addrEdit->setReadOnly( true );
      addrEdit->setFont( f );
    mainGrid->addWidget( addrEdit, 2,0 );
    
    globalGrid->addWidget( mainBox, 0,0 );
    

/////////////////////////////////////////////////////////////////////////////////////// connections   
   connect( listView, SIGNAL(selectionChanged()), this, SLOT(buildSelectedList()));
   connect( listView, SIGNAL(clicked(QListViewItem*)), this, SLOT(setAddrEditPath(QListViewItem*)));
/////////////////////////////////////////////////////////////////////////////////////// connections  
   
   _selectedList = CellFrame::selected();
   
   listView->setColumnWidthMode( 0, QListView::Maximum );
}




// ustawienie listy zaznaczonych obiektów
void ObjectsWidget::setSelectedList( QPtrList<ViMultiPolyh> *selectedList )
{
  update();
}



// ustawienie korzenia ca³ej sceny - powinno byæ wywo³ywane tylko raz, zaraz po tym
// jak Kernel utworzy g³ówny obiekt z³o¿ony
void ObjectsWidget::setRoot( ViScene* scene )
{
  _scene = scene;
  update();
}



// slot odrysowuje ca³± hierarchiê i pokazuje zaznaczenie
// powinno byæ wywo³ywane po dodaniu/usuniêciu obiektu
void ObjectsWidget::update()
{
  buildList();  // buduj listê
  expandAll();  // calosc rozwin
  showSelectedList();    
}



// metoda buduje liste hierarchiczna obiektow sceny
//
void ObjectsWidget::buildList()
{
  if ( _scene == 0L ) return;
  
  listView->clear();   // wyczysc cala liste

  HierListViewItem *item;
  QString name;
  ViMultiPolyh *mph;
  
  // zwyczajnie dodajemy obiekty do listy
  for ( ViScene::ConMultiPolyhIter iter = _scene->ConBegin_NormMultiPolyh(); iter; ++iter )
  {
    name = iter->NodeName();
  
    mph = (ViMultiPolyh*) & (*iter);
    item = new HierListViewItem( listView, name, mph);
    
    item->setPixmap(0, QPixmap(Icons::showAllSceneIcon()));
  }
}



// rozwija pe³ne drzewo
void ObjectsWidget::expandAll()
{
  QListViewItemIterator it(listView);
  QListViewItem *item;
  while (it.current())
  {
    item = it.current();
    listView->setOpen(item, true);
    ++it;
  }
}


// zwija drzewo
void ObjectsWidget::collapseAll()
{
  QListViewItemIterator it(listView);
  QListViewItem *item;
  while (it.current())
  {
    item = it.current();
    listView->setOpen(item, false);
    ++it;
  }
}




// slot tworzy listê _selectedList po otrzymaniu sygna³u o zmianie zaznaczenia
void ObjectsWidget::buildSelectedList()
{
  QListViewItemIterator it(listView);
  QListViewItem *item;

  _selectedList->clear(); // wyczy¶æ poprzedni± listê zaznaczonych obiektów
  
  while (it.current())
  {
    item = it.current();
    if (listView->isSelected(item))
    {
     _selectedList->append(((HierListViewItem*) item)->mp()); // konwersja na (ViMultiPolyh*) i dodanie wskaznika
    }
    ++it;
  }

  emit selectionChanged( _selectedList );
}




// slot zaznacza na listView obiekty zawarte w liscie selectedList
void ObjectsWidget::showSelectedList()
{
  QListViewItemIterator it(listView);
  HierListViewItem *item;
  addrEdit->clear();
  
  if ( _selectedList->isEmpty() ) // nic nie jest zaznaczone - odznacz wszystko
  {
   while ( it.current() )
   {
     item = (HierListViewItem*) it.current();
     item->setSelected( false );
     ++it;
   }
  }

  else
  // aplikuj zaznaczenia
  while (it.current())
  {
   item = (HierListViewItem*) it.current();

   if (_selectedList->findRef(item->mp()) != -1)  // zaznaczamy obiekt na listView 
   {
    item->setSelected(true);
    setAddrEditPath(item);
   }
   else item->setSelected(false);
            
   ++it;
  }
}



// metoda wpisuje pelna sciezke do obiektu w wolnym pasku (odpowiada na sygnal clicked())
void ObjectsWidget::setAddrEditPath( QListViewItem *item )
{
  if (item == 0) { addrEdit->clear(); return; }
  
  addrEdit->setText(QString(((HierListViewItem*) item)->address().c_str()));
}



