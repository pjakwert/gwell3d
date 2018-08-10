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
    
    QGridLayout *mainGrid = new QGridLayout( mainBox, 4,1, 10,5 ); // 3rows+wype³niacz, 1col
    
    QSpacerItem* upperSpacer = new QSpacerItem( 5, 15, QSizePolicy::Expanding, QSizePolicy::Fixed );
    mainGrid->addItem( upperSpacer, 0,0 );
    
    // grupa dwóch guzików - treeViewButton i pathsViewButton
    buttonGroup = new QButtonGroup( 1, Qt::Vertical, mainBox );
    buttonGroup->setExclusive(true);
    buttonGroup->setFlat(true);
    buttonGroup->setFrameStyle( QFrame::NoFrame );
    buttonGroup->setLineWidth(0);
    buttonGroup->setInsideMargin(3);
      // przycisk treeViewButton
      treeViewButton = new QToolButton( buttonGroup );
      treeViewButton->setIconSet(QIconSet(QPixmap(Icons::asTreeIcon())));
      treeViewButton->setTextLabel(tr("View as tree"), true);
      treeViewButton->setFixedSize(30, 30);
      treeViewButton->setAutoRaise(true);
      treeViewButton->setToggleButton(true);
      // przycisk pathsViewButton
      pathsViewButton = new QToolButton( buttonGroup );
      pathsViewButton->setIconSet(QIconSet(QPixmap(Icons::asPathsIcon())));
      pathsViewButton->setTextLabel(tr("View as paths"), true);
      pathsViewButton->setFixedSize(30, 30);
      pathsViewButton->setAutoRaise(true);
      pathsViewButton->setToggleButton(true);
    mainGrid->addWidget( buttonGroup, 1,0 );
    
    ////////////////////// drzewo
      listView = new ListView( mainBox, treeViewButton );
      listView->setAllColumnsShowFocus( true );           // zaznacza wszystkie kolumny
      listView->setShowSortIndicator( false );            // nie pokazuj wska¼nika sortowania
      listView->setSelectionMode( QListView::Extended );  // tryb zaznaczania
      listView->setRootIsDecorated( true );               // poka¿ plusiki rozwijania
      //   listView->setSorting(-1);                         // nie sortuj
      listView->addColumn(QIconSet(QPixmap(Icons::showAllSceneIcon())), tr("Object"));
      listView->addColumn(QIconSet(QPixmap(Icons::pyramidIcon())), tr("Pattern Polyhedron"));
      //listView->addColumn(QIconSet(QPixmap(Icons::colorsIcon())), tr("Color"));
      //listView->addColumn(QIconSet(QPixmap(Icons::textureIcon())), tr("Material"));
      listView->setColumnWidthMode( 0, QListView::Maximum );
      listView->setColumnWidthMode( 1, QListView::Maximum );
      //listView->setColumnWidthMode(2, QListView::Maximum);
      //listView->setColumnWidthMode(3, QListView::Maximum);               
      listView->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Expanding );
    
      QFont f( this->font() );
      f.setPointSize( f.pointSize() - 2 );
      listView->setFont( f );
    mainGrid->addWidget( listView, 2,0 );
    
    ////////////////////// dolny LineEdit
      addrEdit = new QLineEdit( mainBox );
      addrEdit->setReadOnly( true );
      addrEdit->setFont( f );
    mainGrid->addWidget( addrEdit, 3,0 );
    
    globalGrid->addWidget( mainBox, 0,0 );
    

   treeViewButton->setOn(true);       // na poczatek ustaw wlaczony przycisk drzewa
/////////////////////////////////////////////////////////////////////////////////////// connections   
   connect( buttonGroup, SIGNAL(clicked(int)), this, SLOT(viewToggled(int)));      
   connect( listView, SIGNAL(selectionChanged()), this, SLOT(buildSelectedList()));
   connect( listView, SIGNAL(clicked(QListViewItem*)), this, SLOT(setAddrEditPath(QListViewItem*)));
/////////////////////////////////////////////////////////////////////////////////////// connections  
   
   _selectedList = CellFrame::selected();
}




// ustawienie listy zaznaczonych obiektów
void ObjectsWidget::setSelectedList( QPtrList<ViNTreeNode> *selectedList )
{
  //update();
  showSelectedList();
}



// ustawienie korzenia ca³ej sceny - powinno byæ wywo³ywane tylko raz, zaraz po tym
// jak Kernel utworzy g³ówny obiekt z³o¿ony
void ObjectsWidget::setRoot( ViMultiPolyh* root )
{
  _root = root;
  update();
}



// slot odrysowuje ca³± hierarchiê i pokazuje zaznaczenie
// powinno byæ wywo³ywane po dodaniu/usuniêciu obiektu
void ObjectsWidget::update()
{
  if ( treeViewButton->isOn() ) 
    viewToggled( buttonGroup->id( treeViewButton ) );
  else
    viewToggled( buttonGroup->id( pathsViewButton ) );
}



// slot obslugujacy sygnal klikniecia buttona z przekazywanym jego numerem ID
void ObjectsWidget::viewToggled(int buttonID)
{
  if (buttonID == buttonGroup->id(treeViewButton))
  {
    listView->setRootIsDecorated(true);
    buildTree();  // buduj drzewo
    //expandAll();  // calosc rozwin
    showSelectedList();    
    return;
  }

  if (buttonID == buttonGroup->id(pathsViewButton))
  {
    listView->setRootIsDecorated(false);
    buildPaths();
    showSelectedList();    
    return;
  }
}




// zwraca wska¼nik do elementu o nazwie text znalezionego na g³ównym poziomie listy,
// je¿eli nie znajdzie - zwraca 0L
QListViewItem* ObjectsWidget::findChild( const QListView* list, const QString& txt )
{
  QListViewItem *item = list->firstChild();
  
  while ( item )
  {
    if ( item->text(0) == txt ) return item;
    item = item->nextSibling();
  }
  
  return 0L;
}


// zwraca wska¼nik do dziecka o podanym tek¶cie, je¿eli nie ma takiego dziecka - 0L
QListViewItem* ObjectsWidget::findChild( const QListViewItem* parent, const QString& txt )
{
  if ( parent->childCount() == 0 ) return 0L; // bezdzietny
  
  QListViewItem *item = parent->firstChild();
  while ( item )
  {
    if ( item->text(0) == txt ) return item;
    item = item->nextSibling();
  }
  return 0L;
}


// metoda buduje liste hierarchiczna dla obiektu zlozonego
// !!!! WAZNE !!!! nazwy obiektow nie moga sie powtarzac - wtedy efekt bedzie niepoprawny
//
void ObjectsWidget::buildTree()
{
  if ( _root == 0L ) return;
  
  listView->clear();   // wyczysc cala liste

  ViNodeAddress addr;
  int length;
  QString adres;
  QString s;
  QListViewItem *current;
  QListViewItem *it;
  HierListViewItem *item;
  
  const ViNTreeNode* _hierRoot = dynamic_cast<ViNTreeNode*>(_root);
  
  
  for (ViNTreeNode::ConPolyhIter iter = _hierRoot->ConBegin_PolyhHierList(); iter; ++iter)
  {
     addr = iter->GetNodeAddress();
     adres = QString(addr.c_str());  // printf("adres: %s\n", adres.ascii());
     length = addr.AddressLength();
    
     for ( int i=0; i<length-1; i++ )
     {
       s = adres.section('.', i,i, QString::SectionSkipEmpty);  // rozdzielaj stringa
       
       if ( i==0 ) it = findChild( listView, s ); // zerowy poziom - szukaj na g³ównym listView
       else it = findChild( current, s );
       
       if ( it == 0L ) // utwórz nowy
       {
         if ( i==0 ) item = new HierListViewItem( listView, s, iter);
          else item = new HierListViewItem( (HierListViewItem*) current, s, iter );
         current = item;  
          
          // odpowiednia ikonka w zaleznosci od typu figury
          switch (iter->GetInheritorType())
          {
            case IT_MULTIPOLYH : item->setPixmap(0, QPixmap(Icons::showAllSceneIcon()));   break; 
            case IT_ELEMEPOLYH : item->setPixmap(0, QPixmap(Icons::coneIcon())); break; 
            case IT_SCENEPOLYHLIST : break; // zboczeniec
            default : break; // zboczeniec!
          }

          // typ bryly wzorcowej - tylko dla ElemePolyh
          if (iter->GetInheritorType() == IT_ELEMEPOLYH)
          {
            ViElemePolyhExt *el = (ViElemePolyhExt*) & *iter;
            item->setText(1, QString(el->PattPolyh().GetName()));
          }  
       }
       else current = it;
     }

  }
  showSelectedList();
}



// metoda tworzy liste sciezek
void ObjectsWidget::buildPaths()
{
  if ( _root == 0L ) return;

  listView->clear();   // wyczysc cala liste

  ViNodeAddress addr;
  QString adres;
  HierListViewItem *item;

  const ViNTreeNode* _hierRoot = dynamic_cast<ViNTreeNode*>(_root);
  
  for (ViNTreeNode::ConPolyhIter iter = _hierRoot->ConBegin_PolyhHierList(); iter; ++iter)
//  for (ViMultiPolyh::ConElemePolyhIter iter = _multiPolyh->ConBegin_ElemePolyh(); iter; ++iter)
  {
     addr = iter->GetNodeAddress();
     adres = QString(addr.c_str());  // printf("adres: %s\n", adres.ascii());

     item = new HierListViewItem(listView, adres, iter);

     // odpowiednia ikonka w zaleznosci od typu figury
     switch (iter->GetInheritorType())
     {
       case IT_MULTIPOLYH : item->setPixmap(0, QPixmap(Icons::showAllSceneIcon()));   break;
       case IT_ELEMEPOLYH : item->setPixmap(0, QPixmap(Icons::coneIcon())); break;
       case IT_SCENEPOLYHLIST : break; // zboczeniec
       default : break; // zboczeniec!
     }

     // typ bryly wzorcowej - tylko dla ElemePolyh
     if (iter->GetInheritorType() == IT_ELEMEPOLYH)
     {
       ViElemePolyhExt *el = (ViElemePolyhExt*) & *iter;
       item->setText(1, QString(el->PattPolyh().GetName()));
     }
  }

  showSelectedList();
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
     _selectedList->append(((HierListViewItem*) item)->hier()); // konwersja na (HierListViewItem*) i dodanie wskaznika
    }
    ++it;
  }

  _selectedList->removeRef( _root ); // usuñ z zaznaczonej listy g³ówny _mp
  
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
     listView->repaintItem( item );
     ++it;
   }
  }

  else
  // aplikuj zaznaczenia
  while (it.current())
  {
   item = (HierListViewItem*) it.current();

   if (_selectedList->findRef(item->hier()) != -1)  // zaznaczamy obiekt na listView 
   {
    item->setSelected(true);
    setAddrEditPath(item);
   }
   else item->setSelected(false);
   listView->repaintItem( item );
   ++it;
  }
}



// metoda wpisuje pelna sciezke do obiektu w wolnym pasku (odpowiada na sygnal clicked())
void ObjectsWidget::setAddrEditPath( QListViewItem *item )
{
  if (item == 0) { addrEdit->clear(); return; }
  
  addrEdit->setText(QString(((HierListViewItem*) item)->address().c_str()));
}

