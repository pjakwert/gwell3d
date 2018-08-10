#include "optionswidget.h"



// konstruktor
OptionsWidget::OptionsWidget( QString title, QWidget *parent, const char *name ) : QWidget( parent, name )
{
  ///////////////////////////////////////////////////////////////////////////    GUI
    globalGrid = new QGridLayout(this, 1,1, 0,0);

    QFont f( this->font() );
    f.setPointSize( f.pointSize() - 2 );
    
    mainGroupBox = new QGroupBox( this );
    mainGroupBox->setTitle(title);
     mainGrid = new QGridLayout( mainGroupBox, 7,1, 10,5 ); // spacer+4rows+spacer, 1col
    
     QSpacerItem *upperSpacer = new QSpacerItem( 5,15, QSizePolicy::Fixed, QSizePolicy::Fixed );
     mainGrid->addItem( upperSpacer, 0,0 );
     
     dirBox = new QGroupBox( 3, Qt::Horizontal, tr(" Directories "), mainGroupBox );
      libsLabel = new QLabel( tr("Libs"), dirBox ); 
      libsLabel->setFont( f );
      libsEdit  = new QLineEdit( dirBox );
      libsEdit->setReadOnly( true );
      libsEdit->setFont( f );
      libsButton = new QToolButton( dirBox );
      libsButton->setTextLabel( "..." );
      libsButton->setUsesTextLabel( true );
      QToolTip::add( libsButton, tr("change") );
      
      mphLabel = new QLabel( tr("Objects"), dirBox );
      mphLabel->setFont( f );
      mphEdit  = new QLineEdit( dirBox );
      mphEdit->setFont( f );
      mphEdit->setReadOnly( true );
      mphButton = new QToolButton( dirBox );
      mphButton->setTextLabel( "..." );
      mphButton->setUsesTextLabel( true );
      QToolTip::add( mphButton, tr("change") );
      
      scenesLabel = new QLabel( tr("Scenes"), dirBox );
      scenesLabel->setFont( f );
      scenesEdit  = new QLineEdit( dirBox );
      scenesEdit->setFont( f );
      scenesEdit->setReadOnly( true );
      scenesButton = new QToolButton( dirBox );
      scenesButton->setTextLabel( "..." );
      scenesButton->setUsesTextLabel( true );
      QToolTip::add( scenesButton, tr("change") );
      
      matLabel = new QLabel( tr("Materials"), dirBox );
      matLabel->setFont( f );
      matEdit  = new QLineEdit( dirBox );
      matEdit->setFont( f );
      matEdit->setReadOnly( true );
      matButton = new QToolButton( dirBox );
      matButton->setTextLabel( "..." );
      matButton->setUsesTextLabel( true );
      QToolTip::add( matButton, tr("change") );
      
      imgLabel = new QLabel( tr("Images"), dirBox );
      imgLabel->setFont( f );
      imgEdit  = new QLineEdit( dirBox );
      imgEdit->setFont( f );
      imgEdit->setReadOnly( true );
      imgButton = new QToolButton( dirBox );
      imgButton->setTextLabel( "..." );
      imgButton->setUsesTextLabel( true );
      QToolTip::add( imgButton, tr("change") );
      
      langLabel = new QLabel( tr("Languages"), dirBox );
      langLabel->setFont( f );
      langEdit  = new QLineEdit( dirBox );
      langEdit->setFont( f );
      langEdit->setReadOnly( true );
      langButton = new QToolButton( dirBox );
      langButton->setTextLabel( "..." );
      langButton->setUsesTextLabel( true );
      QToolTip::add( langButton, tr("change") );
     mainGrid->addWidget( dirBox, 1,0 );
     
     colorBox = new QGroupBox( 2, Qt::Horizontal, tr(" Colors ") ,mainGroupBox );
      bkgLabel = new QLabel( tr("Background"), colorBox );
      bkgLabel->setFont( f );
      bkgButton = new QToolButton( colorBox );
      bkgButton->setAutoRaise( true );
      
      wireLabel = new QLabel( tr("Wire"), colorBox );
      wireLabel->setFont( f );
      wireButton = new QToolButton( colorBox );
      wireButton->setAutoRaise( true );
      
      wireSelLabel = new QLabel( tr("Wire selected"), colorBox );
      wireSelLabel->setFont( f );
      wireSelButton = new QToolButton( colorBox );
      wireSelButton->setAutoRaise( true );
      
      solidLabel = new QLabel( tr("Solid"), colorBox );
      solidLabel->setFont( f );
      solidButton = new QToolButton( colorBox );
      solidButton->setAutoRaise( true );
      
      solidSelLabel = new QLabel( tr("Solid selected"), colorBox );
      solidSelLabel->setFont( f );
      solidSelButton = new QToolButton( colorBox );
      solidSelButton->setAutoRaise( true );
      
      gridLabel = new QLabel( tr("Grid"), colorBox );
      gridLabel->setFont( f );
      gridButton = new QToolButton( colorBox );
      gridButton->setAutoRaise( true );
      
      grid3DLabel = new QLabel( tr("Grid 3D"), colorBox );
      grid3DLabel->setFont( f );
      grid3DButton = new QToolButton( colorBox );
      grid3DButton->setAutoRaise( true );
      
      lightsLabel = new QLabel( tr("Lights"), colorBox );
      lightsLabel->setFont( f );
      lightsButton = new QToolButton( colorBox );
      lightsButton->setAutoRaise( true );
      
      frameLabel = new QLabel( tr("Frame"), colorBox );
      frameLabel->setFont( f );
      frameButton = new QToolButton( colorBox );
      frameButton->setAutoRaise( true );
      
      infoLabel = new QLabel( tr("Info text"), colorBox );
      infoLabel->setFont( f );
      infoButton = new QToolButton( colorBox );
      infoButton->setAutoRaise( true );
     mainGrid->addWidget( colorBox, 2,0 );
     
     renderBox = new QGroupBox( 1, Qt::Horizontal, tr(" Render Options "), mainGroupBox );
      shadeLabel = new QLabel( tr("GL_SHADE_MODEL"), renderBox );
      shadeLabel->setFont( f );
      shadeCombo = new QComboBox( false, renderBox );
      shadeCombo->setFont( f );
      shadeCombo->insertItem( tr("GL_FLAT"),  0 );
      shadeCombo->insertItem( tr("GL_SMOOTH"),1 );
      
      corrLabel = new QLabel( tr("GL_CORRECTION_HINT"), renderBox );
      corrLabel->setFont( f );
      corrCombo = new QComboBox( false, renderBox );
      corrCombo->setFont( f );
      corrCombo->insertItem( tr("GL_FASTEST"),  0 );
      corrCombo->insertItem( tr("GL_NICEST"),   1 );
      corrCombo->insertItem( tr("GL_DONT_CARE"),2 );
     mainGrid->addWidget( renderBox, 3,0 );
     
     othersBox = new QGroupBox( 2, Qt::Horizontal, tr(" Other "), mainGroupBox );
      decLabel = new QLabel( tr("Decimal digits"), othersBox );
      decLabel->setFont( f );
      decSpin  = new QSpinBox( 1, 10, 1, othersBox );
      decSpin->setFont( f );
     
      lngLabel = new QLabel( tr("Language"), othersBox );
      lngLabel->setFont( f );
      langCombo = new QComboBox( false, othersBox );
      langCombo->setFont( f );
     mainGrid->addWidget( othersBox, 4,0 );
     
     setBox = new QGroupBox( 1, Qt::Horizontal, tr(" Settings "), mainGroupBox );
      saveButton = new QPushButton( tr("Save settings"), setBox );
      restoreButton = new QPushButton( tr("Restore settings"), setBox );
      resetButton = new QPushButton( tr("Reset to defaults"), setBox );
     mainGrid->addWidget( setBox, 5,0 );
      
     QSpacerItem *lowerSpacer = new QSpacerItem( 5,15, QSizePolicy::Fixed, QSizePolicy::Expanding );
     mainGrid->addItem( lowerSpacer, 6,0 );
     
    globalGrid->addWidget( mainGroupBox, 0,0 );
  ///////////////////////////////////////////////////////////////////////////////////    GUI
  
  /// init
  this->refresh();
    
      
  
  ///////////////////////////////////////////////////////////////////////////////////  connections
  connect( libsButton, SIGNAL( clicked() ), this, SLOT( chooseDirectory() ) );
  connect( mphButton,  SIGNAL( clicked() ), this, SLOT( chooseDirectory() ) );
  connect(scenesButton,SIGNAL( clicked() ), this, SLOT( chooseDirectory() ) );
  connect( matButton,  SIGNAL( clicked() ), this, SLOT( chooseDirectory() ) );
  connect( imgButton,  SIGNAL( clicked() ), this, SLOT( chooseDirectory() ) );
  connect( langButton, SIGNAL( clicked() ), this, SLOT( chooseDirectory() ) );
    
  connect( bkgButton,       SIGNAL( clicked() ), this, SLOT( chooseColor() ) );
  connect( wireButton,      SIGNAL( clicked() ), this, SLOT( chooseColor() ) );
  connect( wireSelButton,   SIGNAL( clicked() ), this, SLOT( chooseColor() ) );
  connect( solidButton,     SIGNAL( clicked() ), this, SLOT( chooseColor() ) );
  connect( solidSelButton,  SIGNAL( clicked() ), this, SLOT( chooseColor() ) );
  connect( gridButton,      SIGNAL( clicked() ), this, SLOT( chooseColor() ) );
  connect( grid3DButton,    SIGNAL( clicked() ), this, SLOT( chooseColor() ) );
  connect( lightsButton,    SIGNAL( clicked() ), this, SLOT( chooseColor() ) );
  connect( frameButton,     SIGNAL( clicked() ), this, SLOT( chooseColor() ) );
  connect( infoButton,      SIGNAL( clicked() ), this, SLOT( chooseColor() ) );
  
  connect( shadeCombo, SIGNAL( activated(int) ), this, SLOT( shadeChanged(int) ) );
  connect( corrCombo,  SIGNAL( activated(int) ), this, SLOT( corrChanged(int) ) );
  
  connect( decSpin,   SIGNAL( valueChanged(int) ), this, SLOT( decChanged(int) ) );
  connect( langCombo, SIGNAL( activated(int) ),    this, SLOT( langChanged(int) ) );
  
  connect( saveButton,    SIGNAL( clicked() ), this, SLOT( saveSettings() ) );
  connect( restoreButton, SIGNAL( clicked() ), this, SLOT( restoreSettings() ) );
  connect( resetButton,   SIGNAL( clicked() ), this, SLOT( resetToDefaults() ) );
  ///////////////////////////////////////////////////////////////////////////////////  connections
}


// slot wywo³ywany przez przyciski zmiany katalogu
// rozpoznawany jest nadawca i ustawiana odpowiednia ¶cie¿ka z dialogu
void OptionsWidget::chooseDirectory()
{
  QToolButton* snd = (QToolButton*) sender();
  if ( !snd ) return; // b³±d
  
  QString path;
  int id = -1; // numerek buttona
      
  // ustawiamy id buttona i star± ¶cie¿kê - od niej zaczniemy wybieranie
  if ( snd == libsButton ) { path = Options::libPaths()->first(); id = 0; }
  if ( snd == mphButton  ) { path = Options::mphPaths()->first(); id = 1; }
  if ( snd == matButton  ) { path = Options::materialPaths()->first(); id = 2; }
  if ( snd == imgButton  ) { path = Options::imagesPath(); id = 3; }
  if ( snd == scenesButton){ path = Options::scenesPath(); id = 4; }
  if ( snd == langButton ) { path = Options::langPath(); id = 5; }
  
  if ( id == -1 ) return; // b³±d - to nie powinno nigdy zaj¶æ
  
  QFileDialog f;
  f.setMode( QFileDialog::DirectoryOnly ); // pokazuj tylko katalogi
  f.setDir( path ); // rozpocznij wybieranie w starym katalogu
  if ( f.exec() == QDialog::Accepted ) path = f.selectedFile(); else return;
  
  if ( path.isEmpty() ) return; // to nie powinno siê zda¿yæ, ale na wszelki wypadek
    
  // w zale¿no¶ci od przycisku odpowiednia akcja
  switch ( id )
  {
    case 0 : Options::clearLibPaths(); Options::addLibPath( path ); libsEdit->setText( path ); break;
    case 1 : Options::clearMphPaths(); Options::addMphPath( path ); mphEdit->setText( path ); break;
    case 2 : Options::clearMaterialPaths(); Options::addMaterialPath( path ); matEdit->setText( path ); break;
    case 3 : Options::setImagesPath( path ); imgEdit->setText( path ); break;
    case 4 : Options::setScenesPath( path ); scenesEdit->setText( path ); break;
    case 5 : Options::setLangPath( path ); langEdit->setText( path ); fillLangCombo( path ); break;
    default : break;
  }
  
}



// slot wywo³ywany przez przyciski kolorów
// rozpoznawany jest nadawca i ustawiany odpowiedni kolor z dialogu
void OptionsWidget::chooseColor()
{
  QToolButton* snd = (QToolButton*) sender();
  if ( !snd ) return; // b³±d
  
  Options::Colors whichColor;
  QColor col; // aktualny kolor
  
  if ( snd == bkgButton  )     { whichColor = Options::BackgroundColor; 
                                 col = Options::backgroundColor(); }
  if ( snd == wireButton )     { whichColor = Options::WireColor;
                                 col = Options::wireColor(); }
  if ( snd == wireSelButton )  { whichColor = Options::WireSelectedColor;
                                 col = Options::wireSelectedColor(); }
  if ( snd == solidButton )    { whichColor = Options::SolidColor;
                                 col = Options::solidColor(); }
  if ( snd == solidSelButton ) { whichColor = Options::SolidSelectedColor;
                                 col = Options::solidSelectedColor(); }
  if ( snd == gridButton )     { whichColor = Options::GridColor;
                                 col = Options::gridColor(); }
  if ( snd == grid3DButton )   { whichColor = Options::Grid3DColor;
                                 col = Options::grid3DColor(); }
  if ( snd == lightsButton )   { whichColor = Options::LightsColor;
                                 col = Options::lightsColor(); }
  if ( snd == frameButton )    { whichColor = Options::FrameColor;
                                 col = Options::frameColor(); }
  if ( snd == infoButton )     { whichColor = Options::InfoTextColor;
                                 col = Options::infoTextColor(); }
  
  const QColor newColor = QColorDialog::getColor( col, this );
  
  if ( newColor.isValid() ) // user zaakceptowa³ nowy kolor
  {
    Options::setColor( whichColor, newColor );
    CellFrame::refresh();
    snd->setPaletteBackgroundColor( newColor ); // nadaj przyciskowi nowy kolor
  }
}



// zmiana GL_SHADE_MODEL
void OptionsWidget::shadeChanged( int index )
{
  Options::setIntShadeModel( index );
  CellFrame::refresh();
}


// zmiana GL_HINT_CORRECTION
void OptionsWidget::corrChanged( int index )
{
  Options::setIntCorrectionHint( index );
  CellFrame::refresh();
}


// zmiana decimals
void OptionsWidget::decChanged( int value )
{
  Options::setDecimals( value );
  // no i co? przeliczyæ wszystko jeszcze raz? bez sensu, chyba lepiej nic tutaj nie robiæ
}


// wyszukiwane s± pliki .qm w podanej ¶cie¿ce i wstawiane do combo
// na pocz±tku zawsze jest angielski
void OptionsWidget::fillLangCombo( const QString& path )
{
  langCombo->clear();
  _langList.clear();
  _langList.append( "english" );
  
  QDir p(path);
  
  if ( p.exists() )
  {
    p.setFilter( QDir::Files | QDir::Hidden );
    p.setNameFilter( "*.qm *.QM *.Qm" );
    p.setSorting( QDir::Name );
  
    const QFileInfoList *list = p.entryInfoList();
    QFileInfoListIterator it( *list );
    QFileInfo *fi;
  
    while ( (fi = it.current()) != 0 )
    {
      QString s = fi->fileName();
      if ( s.contains( "model" , false ) ) // wyszukuj tylko jêzyki dla modu³u Modeler
      {
        _langList.append( s );
      }
      ++it;
    }
  }
  
  langCombo->insertStringList( _langList, 0 );
}


// ustawia zadany translator aplikacji (tylko nazwa pliku)
void OptionsWidget::setTranslator( const QString& fileName )
{
  if ( fileName == "english" )
  {
    QTranslator translator( 0 );
    translator.clear();
    qApp->installTranslator( &translator );
    langCombo->setCurrentItem( 0 );
  }
  else
  {
    QTranslator translator( 0 );
    translator.load( fileName, Options::langPath() );
    qApp->installTranslator( &translator );
    langCombo->setCurrentItem( _langList.findIndex( fileName ) );
  }
  
  Options::setModelerLangFile( fileName );
}


// zmiana jêzyka - tutaj trzeba post±piæ roztropnie (co wcale nie znaczy, ¿e reszta nie jest roztropna :)
void OptionsWidget::langChanged( int index )
{
  if ( index == 0 ) // english - usuñ translator
  {
    setTranslator( "english" );
    return;
  }
  
  QString fileName = _langList[ index ];
  setTranslator( fileName );
}



void OptionsWidget::refresh()
{
  // katalogi
    libsEdit->setText( Options::libPaths()->first() );
    mphEdit->setText( Options::mphPaths()->first() );
    matEdit->setText( Options::materialPaths()->first() );
    imgEdit->setText( Options::imagesPath() );
    scenesEdit->setText( Options::scenesPath() );
    langEdit->setText( Options::langPath() );
    fillLangCombo( Options::langPath() );
    setTranslator( Options::modelerLangFile() );
    
  // kolory
    bkgButton->setPaletteBackgroundColor( Options::backgroundColor() );
    wireButton->setPaletteBackgroundColor( Options::wireColor() );
    wireSelButton->setPaletteBackgroundColor( Options::wireSelectedColor() );
    solidButton->setPaletteBackgroundColor( Options::solidColor() );
    solidSelButton->setPaletteBackgroundColor( Options::solidSelectedColor() );
    gridButton->setPaletteBackgroundColor( Options::gridColor() );
    grid3DButton->setPaletteBackgroundColor( Options::grid3DColor() );
    lightsButton->setPaletteBackgroundColor( Options::lightsColor() );
    frameButton->setPaletteBackgroundColor( Options::frameColor() );
    infoButton->setPaletteBackgroundColor( Options::infoTextColor() );
    
  // render options
    shadeCombo->setCurrentItem( Options::intShadeModel() );
    corrCombo->setCurrentItem( Options::intCorrectionHint() );
  // decimals
    decSpin->setValue( Options::decimals() );
  // language
  //langCombo->setCurrentItem( );
}


// zapisz aktualne ustawienia
void OptionsWidget::saveSettings()
{
  Options::saveSettings();
}


// przywróæ zapisane ustawienia
void OptionsWidget::restoreSettings()
{
  if ( Options::loadSettings() ) 
  {
    this->refresh(); // za³adowanie ustawieñ i od¶wie¿enie
    CellFrame::refresh();
  }
}


// przywraca ustawienia fabryczne
void OptionsWidget::resetToDefaults()
{
  Options::resetToDefaults();
  CellFrame::refresh();
  this->refresh();
}
    
