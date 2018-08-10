#include "lightswidget.h"

#include <qimage.h>

// konstruktor
LightsWidget::LightsWidget( QString title, QWidget *parent, const char *name ) : QWidget( parent, name )
{
    _decimals = Options::decimals();
    
    posModifier = new TranslateLightPosModifier( QCursor(QPixmap(*(Icons::transLightIcon()))) );
    dirModifier = new TranslateLightDirModifier( QCursor(QPixmap(*(Icons::dirLightIcon()))) );
    connect( posModifier, SIGNAL( vectorChanged(MModifier::ModifierType, Vector3f) ), this, SLOT( updateData(MModifier::ModifierType, Vector3f) ) );
    connect( dirModifier, SIGNAL( vectorChanged(MModifier::ModifierType, Vector3f) ), this, SLOT( updateData(MModifier::ModifierType, Vector3f) ) );
    
    QGridLayout* globalGrid = new QGridLayout( this, 1,1, 2,5, "globalGrid" );
    
     mainGroupBox = new QGroupBox( this );
     mainGroupBox->setCheckable( true );
     mainGroupBox->setChecked( true );
     mainGroupBox->setTitle( title );
    globalGrid->addWidget( mainGroupBox, 0,0 );
    
    mainGrid = new QGridLayout( mainGroupBox, 6,1, 6,5, "mainGrid" ); // g³ówny grid - 5 wierszy + wype³niacz, 1 kolumna
    upperSpace = new QSpacerItem(5,15, QSizePolicy::Maximum,QSizePolicy::Fixed);
    mainGrid->addMultiCell( upperSpace, 0,0, 0,1 );

//----------------------------------------- GUI    
    
    addAndDeleteBox = new QHBox( mainGroupBox );
    addAndDeleteBox->setSpacing( 10 );
     addLightButton = new QToolButton( addAndDeleteBox );
     addLightButton->setTextLabel( tr("add Light") );
     addLightButton->setPixmap( *(Icons::addIcon()) );
     addLightButton->setUsesTextLabel( true );
      addLightPopup = new QPopupMenu( addLightButton );
      addLightPopup->insertItem( QPixmap( *(Icons::bulbIcon()) ), tr("Bulb light"), 0 );
      addLightPopup->insertItem( QPixmap( *(Icons::spotIcon()) ), tr("Spot light"), 1 );
     addLightButton->setPopup( addLightPopup );
     addLightButton->setPopupDelay( 0 );
     deleteLightButton = new QToolButton( addAndDeleteBox ); // --------------------------------------
     deleteLightButton->setTextLabel( tr("delete Light") );
     deleteLightButton->setPixmap( *(Icons::deleteIcon()) );
     deleteLightButton->setUsesTextLabel( true );
    mainGrid->addWidget( addAndDeleteBox, 1,0 );
    
    lightsTable = new LightsTableWidget( mainGroupBox );
    mainGrid->addWidget( lightsTable, 2,0 );
    
    moveButtonsBox = new QHBox( mainGroupBox );
    moveButtonsBox->setSpacing( 10 );
     transLightButton = new QToolButton( moveButtonsBox );
     transLightButton->setTextLabel( tr("move Light") );
     transLightButton->setPixmap( QPixmap( Icons::moveIcon() ) );
     transLightButton->setUsesTextLabel( true );
     transLightButton->setToggleButton( true );
     transLightButton->setAutoRaise( true );
     changeDirectionButton = new QToolButton( moveButtonsBox ); // ------------------------------------
     changeDirectionButton->setTextLabel( tr("change direction") );
     changeDirectionButton->setPixmap( QPixmap( Icons::moveIcon() ) );
     changeDirectionButton->setUsesTextLabel( true );
     changeDirectionButton->setToggleButton( true );
     changeDirectionButton->setAutoRaise( true );
    mainGrid->addWidget( moveButtonsBox, 3,0 );
    
  
    QDoubleValidator* doubleValidator = new QDoubleValidator( this );
    doubleValidator->setDecimals( _decimals );
      
    paramsBox = new QGroupBox( tr(" Parameters "), mainGroupBox );
     paramsGrid = new QGridLayout( paramsBox, 10,3, 10,5 );
     pSpacer = new QSpacerItem( 5,15, QSizePolicy::Maximum, QSizePolicy::Fixed );
     paramsGrid->addMultiCell( pSpacer, 0,0, 0,2 );
      lightTypeCombo = new QComboBox( false, paramsBox );
      lightTypeCombo->insertItem( tr("Directional"), 0 );
      lightTypeCombo->insertItem( tr("Positional"),  1 );
      lightIsLabel = new QLabel( lightTypeCombo, tr("Light is"), paramsBox );
     paramsGrid->addWidget( lightIsLabel,   1,0 );
     paramsGrid->addMultiCellWidget( lightTypeCombo, 1,1, 1,2 );
      
      positionLabel = new QLabel( tr("Position"), paramsBox );
     paramsGrid->addMultiCellWidget( positionLabel, 2,2, 0,1 );
     
     positionBox = new QHBox( paramsBox );
     positionBox->setSpacing( 3 );
       xPosLabel = new QLabel( tr("X"), positionBox );
       xPosEdit  = new QLineEdit( positionBox );
       xPosEdit->setValidator( doubleValidator );
       yPosLabel = new QLabel( tr("Y"), positionBox );
       yPosEdit  = new QLineEdit( positionBox );
       yPosEdit->setValidator( doubleValidator );
       zPosLabel = new QLabel( tr("Z"), positionBox );
       zPosEdit  = new QLineEdit( positionBox );
       zPosEdit->setValidator( doubleValidator );
     paramsGrid->addMultiCellWidget( positionBox, 3,3, 0,2 ); 
     
      directionLabel = new QLabel( tr("Direction"), paramsBox );
     paramsGrid->addMultiCellWidget( directionLabel, 4,4, 0,1 );
      
     directionBox = new QHBox( paramsBox );
     directionBox->setSpacing( 3 );
       xDirLabel = new QLabel( tr("X"), directionBox );
       xDirEdit  = new QLineEdit( directionBox );
       xDirEdit->setValidator( doubleValidator );
       yDirLabel = new QLabel( tr("Y"), directionBox );
       yDirEdit  = new QLineEdit( directionBox );
       yDirEdit->setValidator( doubleValidator );
       zDirLabel = new QLabel( tr("Z"), directionBox );
       zDirEdit  = new QLineEdit( directionBox );
       zDirEdit->setValidator( doubleValidator );
     paramsGrid->addMultiCellWidget( directionBox, 5,5, 0,2 );
     
      attLabel = new QLabel( tr("Attenuation"), paramsBox );
     paramsGrid->addMultiCellWidget( attLabel, 6,6, 0,1 );
     
     attGrid = new QGrid( 3, Qt::Horizontal, paramsBox );
     attGrid->setSpacing( 5 );
      constLabel  = new QLabel( tr("linear"),    attGrid );
      constLabel->setAlignment( Qt::AlignHCenter );
      linearLabel = new QLabel( tr("constant"),  attGrid );
      linearLabel->setAlignment( Qt::AlignHCenter );
      quadLabel   = new QLabel( tr("quadratic"), attGrid );
      quadLabel->setAlignment( Qt::AlignHCenter );
      constEdit   = new QLineEdit( attGrid );
      constEdit->setValidator( doubleValidator );
      linearEdit  = new QLineEdit( attGrid );
      linearEdit->setValidator( doubleValidator );
      quadEdit    = new QLineEdit( attGrid );
      quadEdit->setValidator( doubleValidator );
     paramsGrid->addMultiCellWidget( attGrid, 7,7, 0,2 ); 
      
     // dla cutOffAngle jest validator z wide³kami
     QDoubleValidator *doubleCutOffValidator = new QDoubleValidator( 0.0, 90.0, _decimals, this );
     // dla expEdit validator równie¿ z wide³kami
     QDoubleValidator *doubleExpValidator = new QDoubleValidator( 0.0, 128.0, _decimals, this );
     
     expAndCutOffBox = new QHBox( paramsBox );
     expAndCutOffBox->setSpacing( 3 );
      expLabel = new QLabel( tr("Exponent"), expAndCutOffBox );
      expEdit  = new QLineEdit( expAndCutOffBox );
      expEdit->setValidator( doubleExpValidator );
      cutOffLabel = new QLabel( tr("CutOff"), expAndCutOffBox );
      cutOffEdit  = new QLineEdit( expAndCutOffBox );
      cutOffEdit->setValidator( doubleCutOffValidator );
      
      expAndCutOffBox->setStretchFactor( expLabel, 1 );
      expAndCutOffBox->setStretchFactor( expEdit,  2 );
      expAndCutOffBox->setStretchFactor( cutOffLabel, 1 );
      expAndCutOffBox->setStretchFactor( cutOffEdit, 2 );
     
     paramsGrid->addMultiCellWidget( expAndCutOffBox, 8,8, 0,2 ); 
      
      movingWithCameraCheck = new QCheckBox( tr("Light moves with camera"), paramsBox );
     paramsGrid->addMultiCellWidget( movingWithCameraCheck, 9,9, 0,2 ); 
    
     mainGrid->addWidget( paramsBox, 4,0 );
    
     
     colorsTabWidget = new QTabWidget( mainGroupBox );
      ambientWidget  = new ColorWidget( colorsTabWidget, tr(" Ambient ") );
      diffuseWidget  = new ColorWidget( colorsTabWidget, tr(" Diffuse ") );
      specularWidget = new ColorWidget( colorsTabWidget, tr(" Specular ") );
      colorsTabWidget->insertTab( ambientWidget,  tr("Ambient"),  1 );
      colorsTabWidget->insertTab( diffuseWidget,  tr("Diffuse"),  2 );
      colorsTabWidget->insertTab( specularWidget, tr("Specular"), 3 );
     mainGrid->addWidget( colorsTabWidget, 5,0 );

///////////////////////////////////////////////////////////////////////////////////////  FONT    
     QFont f( this->font() );
     f.setPointSize( f.pointSize() - 2 );

     paramsBox->setFont( f );
     colorsTabWidget->setFont( f );
///////////////////////////////////////////////////////////////////////////////////////  FONT
     
     
     
     
//////////////////////////////////////////////////////////////////////////////////////   INIT    
    // tworzymy listê ¶wiate³
    _lightsList = new QPtrList<Light>;
    
    lightsTable->setLightsList( _lightsList );
    CellFrame::setLightsList( _lightsList );
/////////////////////////////////////////////////////////////////////////////////////   INIT
     
//////////////////////////////////////////////////////////////////////////////////////////// connections
    // wszystkie ¶wiat³a ON/OFF
    connect( mainGroupBox, SIGNAL( toggled(bool) ), this, SLOT( lightsToggled(bool) ) );
    // modyfikatory
    connect( transLightButton, SIGNAL( toggled(bool) ), this, SLOT( transLightToggled(bool) ) );
    connect( changeDirectionButton, SIGNAL( toggled(bool) ), this, SLOT( changeDirToggled(bool) ) );
    // lightsTable -> parametry ¶wiat³a
    connect( lightsTable, SIGNAL( lightSelected(Light*) ), this, SLOT( currentLightChanged(Light*) ) );
    connect( lightsTable, SIGNAL( lightParamsChanged(Light*) ), this, SLOT( lightParamsChanged(Light*) ) );
    connect( lightsTable, SIGNAL( lightRemoved() ), this, SLOT( updateWorkspace() ) );
    connect( lightsTable, SIGNAL( lightAdded() ), this, SLOT( updateWorkspace() ) );
    // add/delete light
    connect( addLightPopup, SIGNAL( activated(int) ), lightsTable, SLOT( addLight(int) ) );
    connect( deleteLightButton, SIGNAL( clicked() ), lightsTable, SLOT( deleteLight() ) );
//////////////////////////////////////////////////////////////////////////////////////////// connections

    connect( lightTypeCombo, SIGNAL( activated(int) ), this, SLOT( setLightTypeFromCombo(int) ) );   // lightType
    connect( xPosEdit, SIGNAL( returnPressed() ), this, SLOT( setAllParamsFromEdits() ) );   // position
    connect( yPosEdit, SIGNAL( returnPressed() ), this, SLOT( setAllParamsFromEdits() ) );
    connect( zPosEdit, SIGNAL( returnPressed() ), this, SLOT( setAllParamsFromEdits() ) );
    connect( xDirEdit, SIGNAL( returnPressed() ), this, SLOT( setAllParamsFromEdits() ) );  // direction
    connect( yDirEdit, SIGNAL( returnPressed() ), this, SLOT( setAllParamsFromEdits() ) );
    connect( zDirEdit, SIGNAL( returnPressed() ), this, SLOT( setAllParamsFromEdits() ) );
    connect( constEdit,  SIGNAL( returnPressed() ), this, SLOT( setAllParamsFromEdits() ) ); //att.const
    connect( linearEdit, SIGNAL( returnPressed() ), this, SLOT( setAllParamsFromEdits() ) ); //att.linear
    connect( quadEdit,   SIGNAL( returnPressed() ), this, SLOT( setAllParamsFromEdits() ) ); //att.quad
    connect( expEdit, SIGNAL( returnPressed() ), this, SLOT( setAllParamsFromEdits() ) );  // exponent
    connect( cutOffEdit, SIGNAL( returnPressed() ), this, SLOT( setAllParamsFromEdits() ) ); // cutOffAngle
    connect( movingWithCameraCheck, SIGNAL( toggled(bool) ), this, SLOT( setMovingWithCamera(bool) ) );
    
    connect( ambientWidget, SIGNAL( colorChanged(const QColor&, int) ), this, SLOT( updateLightForWorkspace( const QColor&, int ) ) );
    connect( diffuseWidget, SIGNAL( colorChanged(const QColor&, int) ), this, SLOT( updateLightForWorkspace( const QColor&, int ) ) );
    connect( specularWidget, SIGNAL( colorChanged(const QColor&, int) ), this, SLOT( updateLightForWorkspace( const QColor&, int ) ) );
    
    // tworzymy jedno domy¶lne ¶wiat³o (¿arówka) z domy¶lnymi warto¶ciami OpenGL,
    // pierwsze ¶wiat³o porusza siê z kamer±
    lightsTable->addLight( 0, true );    
}


// ! mechanizm zoptymalizowany pod k±tem szybko¶ci od¶wie¿ania !
// wysy³a do Workspace sygna³, który kolor którego ¶wiat³a ma zostaæ od¶wie¿ony
// a dzia³a to tak: sygna³y z colorWidgets s± pod³±czone do tego slotu (argumenty nie s±
// u¿ywane), na podstawie nadawcy okre¶lany jest edytowany kolor GL: GL_AMBIENT, GL_DIFFUSE lub
// GL_SPECULAR, CellFrames otrzymuj± sygna³ który kolor którego ¶wiat³a od¶wie¿yæ i robi± to :)
void LightsWidget::updateLightForWorkspace( const QColor&, int )
{
  if ( !_currentLight ) return;
  
  // na podstawie sender() okre¶l, który kolor siê zmieni³
  ColorWidget* cw = (ColorWidget*) ( sender() );
  if ( !cw )
  {
    StatusBar::printStatusMsg( tr("updateLightForWorkspace(): can't recognize sender"), "LightsWidget" );
    return;
  }
  
  GLenum whichColor;
  if ( cw == ambientWidget )  whichColor = GL_AMBIENT;
  else if ( cw == diffuseWidget )  whichColor = GL_DIFFUSE;
  else if ( cw == specularWidget ) whichColor = GL_SPECULAR;
    
  emit updateLightColor( whichColor, _currentLight );
}


// slot wysy³a sygna³ setLightsList do Workspace - wykonywane w przypadku dodania/usuniêcia ¶wiat³a
void LightsWidget::updateWorkspace()
{
  emit setLightsList( _lightsList );
}


// metoda w³±cza/wy³±cza parametry ¶wiat³a
void LightsWidget::setAllParamsEnabled( bool yes )
{
  paramsBox->setEnabled( yes );
  colorsTabWidget->setEnabled( yes );
}





// slot s³u¿y do wype³nienia zawarto¶ci paramsBox
void LightsWidget::currentLightChanged( Light* light )
{ 
  // od³±cz colorsWidgets od aktualnego ¶wiat³a
  if ( _currentLight )
  {
    ambientWidget->disconnect ( _currentLight );
    diffuseWidget->disconnect ( _currentLight );
    specularWidget->disconnect( _currentLight );
  }
  
  // ustaw nowe aktualne ¶wiat³o
  _currentLight = light;
  
  // ustaw nowe aktualne ¶wiat³o modyfikatorom
  posModifier->setCurrentLight( _currentLight );
  dirModifier->setCurrentLight( _currentLight );
  
  if ( !_currentLight ) // nowe aktualne ¶wiat³o jest puste
  {
    // tutaj wyczy¶æ wszystko - nie ma ¿adnego ¶wiat³a
    setAllParamsEnabled( false );   
    return;
  }

  // pod³±czamy colorsWidgets do nowego ¶wiat³a
  connect( ambientWidget, SIGNAL( colorChanged(const QColor&, int) ), _currentLight, SLOT( setAmbientColor(const QColor&, int) ) );
  connect( diffuseWidget, SIGNAL( colorChanged(const QColor&, int) ), _currentLight, SLOT( setDiffuseColor(const QColor&, int) ) );
  connect( specularWidget, SIGNAL( colorChanged(const QColor&, int) ), _currentLight, SLOT( setSpecularColor(const QColor&, int) ) );
  
  /////////////////////////////////////////////////////////////////////// ustaw colorWidgets
  ambientWidget->setColor ( _currentLight->ambientColor4fv() );
  diffuseWidget->setColor ( _currentLight->diffuseColor4fv() );
  specularWidget->setColor( _currentLight->specularColor4fv() );
  
  // w zale¿no¶ci od tego czy ¶wiat³o jest w³±czone, udostêpniamy edycjê parametrów
  setAllParamsEnabled( light->isEnabled() );
  
  // typ ¶wiat³a
  if ( light->lightType() == Light::Directional ) lightTypeCombo->setCurrentItem( 0 );
   else lightTypeCombo->setCurrentItem( 1 );
  
  // pozycja ¶wiat³a
  const GLfloat* pos = light->position4fv();
  xPosEdit->setText( QString::number( *pos,     'f', _decimals ) );
  yPosEdit->setText( QString::number( *(pos+1), 'f', _decimals ) );
  zPosEdit->setText( QString::number( *(pos+2), 'f', _decimals ) );
  
  // kierunek
  const GLfloat* dir = light->spotDirection3fv();
  xDirEdit->setText( QString::number( *dir,     'f', _decimals ) );
  yDirEdit->setText( QString::number( *(dir+1), 'f', _decimals ) );
  zDirEdit->setText( QString::number( *(dir+2), 'f', _decimals ) );
  
  // attenuation
  constEdit->setText( QString::number( light->constantAttenuation(), 'f', _decimals ) );
  linearEdit->setText( QString::number( light->linearAttenuation(), 'f', _decimals ) );
  quadEdit->setText( QString::number( light->quadraticAttenuation(), 'f', _decimals ) );
  
  expEdit->setText( QString::number( light->spotExponent(), 'f', _decimals ) );
  cutOffEdit->setText( QString::number( light->spotCutOffAngle(), 'f', _decimals ) );
  
  movingWithCameraCheck->setChecked( light->isMovingWithCamera() );
  
  // je¿eli jest to ¿arówka to wy³±cz pola dotycz±ca spotlight-a
  if ( !light->isSpotlight() )
  {
    directionLabel->setEnabled ( false );
    xDirLabel->setEnabled( false );
    yDirLabel->setEnabled( false );
    zDirLabel->setEnabled( false );
    xDirEdit->setEnabled( false );
    yDirEdit->setEnabled( false );
    zDirEdit->setEnabled( false );
    expLabel->setEnabled( false );
    expEdit->setEnabled( false );
    cutOffLabel->setEnabled( false );
    cutOffEdit->setEnabled( false );
    cutOffEdit->setText( "180.0" ); // ciekawe czy przejdzie przez validator
  }
  else
  {
    directionLabel->setEnabled ( true );
    xDirLabel->setEnabled( true );
    yDirLabel->setEnabled( true );
    zDirLabel->setEnabled( true );
    xDirEdit->setEnabled( true );
    yDirEdit->setEnabled( true );
    zDirEdit->setEnabled( true );
    expLabel->setEnabled( true );
    expEdit->setEnabled( true );
    cutOffLabel->setEnabled( true );
    cutOffEdit->setEnabled( true );
  }
  
}



// LightsTableWidget zmieni³ parametry ¶wiat³a (name, on/off lub bulb/spotlight ) - podaj dalej
void LightsWidget::lightParamsChanged( Light* light )
{
  currentLightChanged( light );
  emit setLight( light );
}




// slot wysy³a sygna³ w³/wy³ ca³ego o¶wietlenia
void LightsWidget::lightsToggled( bool on )
{
  emit setLightingEnabled( on );
}




void LightsWidget::setLightTypeFromCombo( int type )
{
  if ( !_currentLight ) return;
  
  if ( type == 0 ) _currentLight->setLightType( Light::Directional );
  else _currentLight->setLightType( Light::Positional );
  
  emit setLight( _currentLight );
}




void LightsWidget::setAllParamsFromEdits()
{
  if ( !_currentLight ) return;
  
  // POSITION
  // je¿eli które¶ z pól jest puste, ustaw warto¶æ na 0.0
  if ( xPosEdit->text().isEmpty() ) xPosEdit->setText("0.0");
  if ( yPosEdit->text().isEmpty() ) yPosEdit->setText("0.0");
  if ( zPosEdit->text().isEmpty() ) zPosEdit->setText("0.0");
  Vector3f pos( xPosEdit->text().toFloat(), yPosEdit->text().toFloat(), zPosEdit->text().toFloat() );
  _currentLight->setPosition( pos );
  
  // je¿eli które¶ z pól jest puste, ustaw warto¶æ na 0.0
  // DIRECTION
  if ( xDirEdit->text().isEmpty() ) xDirEdit->setText("0.0");
  if ( yDirEdit->text().isEmpty() ) yDirEdit->setText("0.0");
  if ( zDirEdit->text().isEmpty() ) zDirEdit->setText("0.0");
  Vector3f dir( xDirEdit->text().toFloat(), yDirEdit->text().toFloat(), zDirEdit->text().toFloat() );
  _currentLight->setSpotDirection( dir );
  
  // ATTENUATION
  if ( !constEdit->text().isEmpty() ) // const
    _currentLight->setConstantAttenuation( constEdit->text().toFloat() );
  if ( !linearEdit->text().isEmpty() )// linear
    _currentLight->setLinearAttenuation( linearEdit->text().toFloat() );
  if ( !quadEdit->text().isEmpty() )  // quadratic
    _currentLight->setQuadraticAttenuation( quadEdit->text().toFloat() );

  // EXPONENT
  if ( !expEdit->text().isEmpty() )
    _currentLight->setSpotExponent( expEdit->text().toFloat() );
      
  // CUTOFF
  if ( !cutOffEdit->text().isEmpty() )
    _currentLight->setSpotCutOffAngle( cutOffEdit->text().toFloat() );
  
  emit setLight( _currentLight );
}



void LightsWidget::setMovingWithCamera( bool yes )
{
  if ( !_currentLight ) return;
  _currentLight->setMovingWithCamera( yes );
  emit setLight( _currentLight );
}

/*
// zdarzenia wysy³aj±ce sygna³ o pokazaniu,ukryciu widgeta
// dziêki temu bêdziemy w³±czaæ wszystkie kszta³ty ¶wiate³ w przypadku wyboru zak³adki Lights
void LightsWidget::showEvent( QShowEvent* )
{
  emit showLightShapes( true );
}

void LightsWidget::hideEvent( QHideEvent* )
{
  emit showLightShapes( false );  
}
*/

////////////////////////////////////////////////////////////////////////// obs³uga modyfikatorów
// wy³±czenie aktualnego modyfikatora
void LightsWidget::disableModifiers()
{
  if ( transLightButton->isOn() ) transLightButton->setOn( false );
  if ( changeDirectionButton->isOn() ) changeDirectionButton->setOn( false );
  emit setDefaultModifier();
}


// ten slot TYLKO-I-WY£¡CZNIE wy³±cza przyciski, blokuje im sygna³y
void LightsWidget::turnModifiersButtonsOff()
{
  transLightButton->blockSignals( true );
  changeDirectionButton->blockSignals( true );
    transLightButton->setOn( false );
    changeDirectionButton->setOn( false );
  transLightButton->blockSignals( false );
  changeDirectionButton->blockSignals( false );
}


// ustawienie aktualnego modyfikatora z zewn±trz
void LightsWidget::setModifier( MModifier::ModifierType mType )
{
  switch ( mType )
  {
    case MModifier::M_TRANSLIGHTPOS : {
                              transLightButton->setOn( true );
                              transLightToggled( true );
                           } break;
    case MModifier::M_TRANSLIGHTDIR : {
                              changeDirectionButton->setOn( true );
                              changeDirToggled( true );
                           } break;
    default              : break;
  }
}

// uaktualnienie LineEdits w zale¿no¶ci od dzia³ania modyfikatora
void LightsWidget::updateData( MModifier::ModifierType mType, Vector3f v )
{
  switch ( mType )
  {
    case MModifier::M_TRANSLIGHTPOS : {
                              xPosEdit->setText( QString::number( v.x, 'f', _decimals ) );
                              yPosEdit->setText( QString::number( v.y, 'f', _decimals ) );
                              zPosEdit->setText( QString::number( v.z, 'f', _decimals ) );
                           } break;
    case MModifier::M_TRANSLIGHTDIR : {
                              xDirEdit->setText( QString::number( v.x, 'f', _decimals ) );
                              yDirEdit->setText( QString::number( v.y, 'f', _decimals ) );
                              zDirEdit->setText( QString::number( v.z, 'f', _decimals ) );
                           } break;
    default              : break;
  }
}


// slot aktywowany naci¶niêciem przycisku transLightButton
void LightsWidget::transLightToggled( bool on )
{
  if ( on ) // je¿eli przycisk wci¶niêty
  {
    changeDirectionButton->setOn( false );
    emit sendModifier( dynamic_cast<MModifier*>( posModifier ) );
  }
  
  // oba s± wy³±czone - wy¶lij pusty modyfikator
  if ( !on && !changeDirectionButton->isOn() ) emit setDefaultModifier();
}



// slot aktywowany naci¶niêciem przycisku changeDirectionButton
void LightsWidget::changeDirToggled( bool on )
{
  if ( on )
  {
    transLightButton->setOn( false );
    emit sendModifier( dynamic_cast<MModifier*>( dirModifier ) );
  }
  
  // oba s± wy³±czone - wy¶lij pusty modyfikator
  if ( !on && !transLightButton->isOn() ) emit setDefaultModifier();
}

