#include "lightstablewidget.h"


// konstruktor
LightsTableWidget::LightsTableWidget( QWidget* parent ) : QTable( 0,3, parent )
{
  QFont font( this->font() );
  font.setPointSize( font.pointSize() - 2 );
  setFont( font );
  
  setLeftMargin( 0 );
  setShowGrid( false );
  horizontalHeader()->setLabel( 0, tr("Light") );
  horizontalHeader()->setLabel( 1, tr("ON") );
  horizontalHeader()->setLabel( 2, tr("type") );

  setSelectionMode( QTable::SingleRow );
    
  connect( this, SIGNAL( currentChanged(int,int) ), this, SLOT( currentLightChanged(int,int) ));
  connect( this, SIGNAL( valueChanged(int,int) ), this, SLOT( userChangedName(int,int) ) );
  
  _widgetsList = new QPtrList<WidgetsList>;
  _widgetsList->setAutoDelete( true );
}



// slot do zmiany nazwy ¶wiat³a
void LightsTableWidget::userChangedName( int row, int col )
{
  if ( col != 0 ) return;
  
  Light* light = _lightsList->at( row );
  light->setName( text(row,col) );
  emit lightParamsChanged( light );
}



// metoda dodaje nowe domy¶lne ¶wiat³o: 0=bulb, 1=spotlight
void LightsTableWidget::addLight( int bulbOrSpotlight, bool isMovingWithCamera )
{
  Light *light;
  // tworzymy ¿arówkê lub spotlight
  if ( bulbOrSpotlight == 0 ) light = new Light( false ); else light = new Light( true );
  
  if ( !light->createdSuccessfully() ) return; // utworzenie nowego ¶wiat³a nie powiod³o siê - wyjd¼
  
  _lightsList->append( light );
  light->setMovingWithCamera( isMovingWithCamera );
  
  //setLightsList( _lightsList );
  
  ///////////////////////////////////////////////////// dodanie pojedynczego ¶wiat³a
  int currRow = numRows();
  insertRows( numRows(), 1 );
  
  QStringList comboList;  comboList << tr("Bulb") << tr("Spotlight");
  setText( currRow, 0, light->name() ); // nazwa ¶wiat³a
    
  if ( light->isSpotlight() ) setPixmap( currRow, 0, QPixmap( *(Icons::spotIcon()) ) ); // ikona
   else setPixmap( currRow, 0, QPixmap( *(Icons::bulbIcon()) ) );
    
  WidgetsList *wl = new WidgetsList;
  _widgetsList->append( wl );
  wl->light = light;
  wl->tableCheck = new QCheckBox( this ); // checkBox ON/OFF
  
  if ( light->isEnabled() ) wl->tableCheck->setChecked( true ); 
   else wl->tableCheck->setChecked( false );
  connect( wl->tableCheck, SIGNAL( toggled(bool) ), this, SLOT( toggleLight(bool) ) );
  setCellWidget( currRow, 1, wl->tableCheck );
    
  wl->tableCombo = new QComboBox( false, this );   // comboBox bulb/spot
  wl->tableCombo->insertStringList( comboList );
    
  if ( light->isSpotlight() ) wl->tableCombo->setCurrentItem( 1 );
   else wl->tableCombo->setCurrentItem( 0 );
  connect( wl->tableCombo, SIGNAL( activated(int) ), this, SLOT( bulbOrSpotChanged(int) ) );
  setCellWidget( currRow, 2, wl->tableCombo );
  ///////////////////////////////////////////////////// dodanie pojedynczego ¶wiat³a
    
  emit lightSelected( light );
  emit lightAdded();
}



// dodaje utworzone wcze¶niej ¶wiat³o do listy
void LightsTableWidget::addLight( Light *light )
{
  _lightsList->append( light );
    
  // dodanie wiersza do tabeli
  int currRow = numRows();
  insertRows( numRows(), 1 );
  setText( currRow, 0, light->name() ); // nazwa ¶wiat³a
  
  if ( light->isSpotlight() ) setPixmap( currRow, 0, QPixmap( *(Icons::spotIcon()) ) ); // ikona
   else setPixmap( currRow, 0, QPixmap( *(Icons::bulbIcon()) ) );
   
  QStringList comboList;  
  comboList << tr("Bulb") << tr("Spotlight");
   
  WidgetsList *wl = new WidgetsList;
  _widgetsList->append( wl );
  wl->light = light;
  wl->tableCheck = new QCheckBox( this ); // checkBox ON/OFF
  
  if ( light->isEnabled() ) wl->tableCheck->setChecked( true ); else wl->tableCheck->setChecked( false );
  connect( wl->tableCheck, SIGNAL( toggled(bool) ), this, SLOT( toggleLight(bool) ) );
  setCellWidget( currRow, 1, wl->tableCheck );
    
  wl->tableCombo = new QComboBox( false, this );   // comboBox bulb/spot
  wl->tableCombo->insertStringList( comboList );
    
  if ( light->isSpotlight() ) wl->tableCombo->setCurrentItem( 1 );
   else wl->tableCombo->setCurrentItem( 0 );
  connect( wl->tableCombo, SIGNAL( activated(int) ), this, SLOT( bulbOrSpotChanged(int) ) );
  setCellWidget( currRow, 2, wl->tableCombo );

      
  emit lightSelected( light );
  emit lightAdded();
}




// metoda usuwa aktualnie zaznaczone ¶wiat³o
void LightsTableWidget::deleteLight()
{
  if ( !_lightsList ) return;
  if ( _lightsList->isEmpty() ) return;
  
  int currRow = currentRow(); // aktualny wiersz
  
  // usuwamy ¶wiat³o
  _lightsList->setAutoDelete( true );
   _lightsList->remove( currRow );
  _lightsList->setAutoDelete( false );
  
  // usuwamy wiersz
  this->removeRow( currRow );
  
  _widgetsList->setAutoDelete( false ); // removeRow() ju¿ usun±³ widgety
    _widgetsList->remove( currRow );
  _widgetsList->setAutoDelete( true );
  
  // po usuniêciu ustawiamy aktualne ¶wiat³o: lista pusta=puste ¶wiat³o lub pierwsze z listy
  if ( _lightsList->isEmpty() ) emit lightSelected( 0L );
   else { selectRow( 0 ); emit lightSelected( _lightsList->first() ); }
  
  emit lightRemoved();
}


// usuwa wszystkie ¶wiat³a
void LightsTableWidget::deleteAllLights()
{
  if ( !_lightsList ) return;
  if ( _lightsList->isEmpty() ) return;
  
  _lightsList->setAutoDelete( true );
  _widgetsList->setAutoDelete( true );

  _lightsList->clear();
  _widgetsList->clear();
  for ( int i=numRows()-1; i>=0; i-- ) this->removeRow( i );
  
  _lightsList->setAutoDelete( false );
  _widgetsList->setAutoDelete( false );
  
  emit lightSelected( 0L );
  emit lightRemoved();
}


// ustawia listê ¶wiate³ i wszystkie umieszcza w tabeli
void LightsTableWidget::setLightsList( QPtrList<Light>* lightsList )
{
  _lightsList = lightsList;
  
  // wype³nienie tabeli
  setNumRows( 0 );
  if ( _lightsList->isEmpty() ) return;
  
  // najpierw wyczyszczenie ca³ej tabeli
  for ( int i=numRows()-1; i>=0; i-- ) removeRow( i );
  
  
  // wstawienie tylu wierszy ile jest ¶wiate³
  insertRows( 0, _lightsList->count() );
  
  _widgetsList->setAutoDelete( true );
  _widgetsList->clear();
  _widgetsList->setAutoDelete( false );
  QStringList comboList;
  comboList << tr("Bulb") << tr("Spotlight");
  
  int currRow = 0;
  for ( Light* light = _lightsList->first(); light; light = _lightsList->next() )
  {
    setText( currRow, 0, light->name() ); // nazwa ¶wiat³a
    
    if ( light->isSpotlight() ) setPixmap( currRow, 0, QPixmap( *(Icons::spotIcon()) ) ); // ikona
     else setPixmap( currRow, 0, QPixmap( *(Icons::bulbIcon()) ) );
  
    
    WidgetsList *wl = new WidgetsList;
    _widgetsList->append( wl );
    
    wl->light = light;
    
    wl->tableCheck = new QCheckBox( this ); // checkBox ON/OFF
  
    if ( light->isEnabled() ) wl->tableCheck->setChecked( true ); 
     else wl->tableCheck->setChecked( false );
    connect( wl->tableCheck, SIGNAL( toggled(bool) ), this, SLOT( toggleLight(bool) ) );
    setCellWidget( currRow, 1, wl->tableCheck );
    
    wl->tableCombo = new QComboBox( false, this );   // comboBox bulb/spot
    wl->tableCombo->insertStringList( comboList );
    
    if ( light->isSpotlight() ) wl->tableCombo->setCurrentItem( 1 );
     else wl->tableCombo->setCurrentItem( 0 );
    connect( wl->tableCombo, SIGNAL( activated(int) ), this, SLOT( bulbOrSpotChanged(int) ) );
    setCellWidget( currRow, 2, wl->tableCombo );
    
    currRow++;
  }
}



// slot, na podstawie aktualnego wiersza okre¶la, które ¶wiat³o zosta³o w³±czone/wy³±czone
// i wysy³a odpowiedni sygna³
void LightsTableWidget::toggleLight( bool on )
{
  QCheckBox* senderCheckBox = (QCheckBox*) sender();
  
  for ( WidgetsList *wl = _widgetsList->first(); wl; wl = _widgetsList->next() )
  {
    if ( wl->tableCheck == senderCheckBox )
    {
      wl->light->setEnabled( on );
      
      selectRow( _widgetsList->at() );
      emit lightParamsChanged( wl->light );
      return;
    }
  }
}


// slot, na podstawie aktualnego wiersza okre¶la, które ¶wiat³o zosta³o zmienione na bulb/spotlight
// i wysy³a odpowiedni sygna³
// index: 0=bulb, 1-spotlight
void LightsTableWidget::bulbOrSpotChanged( int index )
{
  QComboBox* senderComboBox = (QComboBox*) sender();
  
  for ( WidgetsList *wl = _widgetsList->first(); wl; wl = _widgetsList->next() )
  {
    if ( wl->tableCombo == senderComboBox )
    {
        if ( index == 0 ) 
        {
          wl->light->setSpotlight( false );  // bulb
          setPixmap( _widgetsList->at(), 0, QPixmap( *(Icons::bulbIcon()) ) );
        } 
        else
        {
          wl->light->setSpotlight( true );
          setPixmap( _widgetsList->at(), 0, QPixmap( *(Icons::spotIcon()) ) );
        }
        
        selectRow( _widgetsList->at() );
        emit lightParamsChanged( wl->light );
        return;
    }
  }
}




// slot pod³±czony do sygna³u currentChanged()
// wysy³a sygna³ z aktualnie edytowanym ¶wiat³em
void LightsTableWidget::currentLightChanged( int row, int col )
{
  if ( !_lightsList ) { emit lightSelected( 0L ); return; }
  
  Light* light = _lightsList->at( row );
  emit lightSelected( light );
}





// ¿eby kolumny by³y zawsze poprawnie skalowane
void LightsTableWidget::resizeEvent( QResizeEvent* e )
{
  int w = e->size().width() - 5;
  
  int nw = (int) (0.6 * (float) w); // name
  int ow = (int) (0.15 * (float) w); // on/off
  int tw = (int) (0.25 * (float) w); // bulb/spotlight
  
  setColumnWidth( 0, nw );
  setColumnWidth( 1, ow );
  setColumnWidth( 2, tw );
}
