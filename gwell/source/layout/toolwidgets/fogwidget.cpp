#include "fogwidget.h"

FogStruct* FogWidget::_fog = new FogStruct;

FogWidget::FogWidget( QString title, QWidget *parent, const char *name ) : QWidget( parent,name )
{
  //_fog = new FogStruct;
  ///////////////////////////////////////////////////////////////////////////    GUI
  globalGrid = new QGridLayout( this, 1,1, 0,0 );

  QFont f( this->font() );
  f.setPointSize( f.pointSize() - 2 );
    
  mainGroupBox = new QGroupBox( this );
  mainGroupBox->setTitle( title );
  mainGroupBox->setCheckable( true );
  mainGroupBox->setChecked( false );
  mainGrid = new QGridLayout( mainGroupBox, 7,1, 10,5 ); // spacer+5rows+spacer, 1col
    
  QSpacerItem *upperSpacer = new QSpacerItem( 5,15, QSizePolicy::Fixed, QSizePolicy::Fixed );
  mainGrid->addItem( upperSpacer, 0,0 );
  
  fogModeLabel = new QLabel( tr("Fog mode"), mainGroupBox );
  fogModeLabel->setFont( f );
  mainGrid->addWidget( fogModeLabel, 1,0 );
  fogModeCombo = new QComboBox( false, mainGroupBox );
  fogModeCombo->setFont( f );
  fogModeCombo->insertItem( tr("GL_EXP") );
  fogModeCombo->insertItem( tr("GL_EXP2") );
  fogModeCombo->insertItem( tr("GL_LINEAR") );
  mainGrid->addWidget( fogModeCombo, 1,1 );
  
  fogDensityLabel = new QLabel( tr("Fog density"), mainGroupBox );
  fogDensityLabel->setFont( f );
  mainGrid->addWidget( fogDensityLabel, 2,0 );
  fogDensitySpinBox = new FloatSpinBox( 0.0, 128.0, 0.1, Options::decimals(), mainGroupBox );
  fogDensitySpinBox->setFont( f );
  mainGrid->addWidget( fogDensitySpinBox, 2,1 );
  
  QGroupBox* startEndBox = new QGroupBox( 2, Qt::Horizontal, mainGroupBox );
  fogStartLabel = new QLabel( tr("Fog start"), startEndBox );
  fogStartLabel->setFont( f );
  fogStartLabel->setAlignment( Qt::AlignHCenter );
  fogEndLabel   = new QLabel( tr("Fog end"), startEndBox );
  fogEndLabel->setFont( f );
  fogEndLabel->setAlignment( Qt::AlignHCenter );
  fogStartSpinBox = new FloatSpinBox( -99999.0, 99999.0, 10.0, Options::decimals(), startEndBox );
  fogStartSpinBox->setFont( f );
  fogEndSpinBox   = new FloatSpinBox( -99999.0, 99999.0, 10.0, Options::decimals(), startEndBox );
  fogEndSpinBox->setFont( f );
  mainGrid->addMultiCellWidget( startEndBox, 3,3, 0,1 );
  
  fogColorBox = new ColorWidget( mainGroupBox, tr(" Fog color "), Options::backgroundColor(), 255 );
  // ustawiamy kolor mg³y na aktualny kolor t³a - najwiêkszy realizm
  mainGrid->addMultiCellWidget( fogColorBox, 4,4, 0,1 );
  
  getBkgColorButton = new QPushButton( tr("Get background color"), mainGroupBox );
  getBkgColorButton->setFont( f );
  mainGrid->addMultiCellWidget( getBkgColorButton, 5,5, 0,1 );
  
  QSpacerItem *lowerSpacer = new QSpacerItem( 5,15, QSizePolicy::Fixed, QSizePolicy::Expanding );
  mainGrid->addItem( lowerSpacer, 6,0 );
  
  globalGrid->addWidget( mainGroupBox, 0,0 );
  ///////////////////////////////////////////////////////////////////////////    GUI
  
  
  ///////////////////////////////////////////////////////////////////////////   CONNECT
  connect( mainGroupBox, SIGNAL( toggled(bool) ), this, SLOT( fogToggled(bool) ) );
  connect( fogModeCombo, SIGNAL( activated(int) ), this, SLOT( fogModeChanged(int) ) );
  connect( fogDensitySpinBox, SIGNAL( valueChanged(float) ), this, SLOT( fogDensityChanged(float) ) );
  connect( fogStartSpinBox, SIGNAL( valueChanged(float) ), this, SLOT( fogStartChanged(float) ) );
  connect( fogEndSpinBox, SIGNAL( valueChanged(float) ), this, SLOT( fogEndChanged(float) ) );
  connect( fogColorBox, SIGNAL( colorChanged(const QColor&, int) ), this, SLOT( fogColorChanged(const QColor&, int) ) );
  connect( getBkgColorButton, SIGNAL( clicked() ), this, SLOT( getBackgroundColor() ) );
  ///////////////////////////////////////////////////////////////////////////   CONNECT
  
  fogModeCombo->setCurrentItem( 2 ); // na pocz±tku ustawiamy typ mg³y = GL_LINEAR (naj³adniejszy)
  fogDensitySpinBox->setFloatValue( 0.35 ); // gêsto¶æ
  fogStartSpinBox->setFloatValue( 0.0 );
  fogEndSpinBox->setFloatValue( 1000.0 );
  
  fogToggled( false );
  fogDensityChanged( 0.35 );
  fogStartChanged( 0.0 );
  fogEndChanged( 1000.0 );
  fogColorChanged( Options::backgroundColor(), 255 );
  fogModeChanged( 2 );
}



// ustawia wszystkie widgety zgodnie z zawarto¶ci± struktury po czym wysy³a sygna³ z FogAll
void FogWidget::updateWidgets()
{
  fogModeCombo->blockSignals( true );
  fogDensitySpinBox->blockSignals( true );
  fogStartSpinBox->blockSignals( true );
  fogEndSpinBox->blockSignals( true );
  fogColorBox->blockSignals( true );
  
  mainGroupBox->setChecked( _fog->fogEnabled );
  
  if ( _fog->fogMode == GL_EXP ) fogModeCombo->setCurrentItem( 0 ); else
  if ( _fog->fogMode == GL_EXP2 ) fogModeCombo->setCurrentItem( 1 ); else
  fogModeCombo->setCurrentItem( 2 );
  
  fogDensitySpinBox->setFloatValue( _fog->fogDensity );
  fogStartSpinBox->setFloatValue( _fog->fogStart );
  fogEndSpinBox->setFloatValue( _fog->fogEnd );
  
  fogColorBox->setColor( _fog->fogColor );
  
  fogModeCombo->blockSignals( false );
  fogDensitySpinBox->blockSignals( false );
  fogStartSpinBox->blockSignals( false );
  fogEndSpinBox->blockSignals( false );
  fogColorBox->blockSignals( false );
  
  emit fogChanged( _fog, FogAll );
}



// sloty emituj± wska¼nik na strukturê parametrów FogStruct oraz parametr, który uleg³ zmianie
// (dziêki temu CellFrame nie bêdzie od¶wie¿a³ wszystkiego)
void FogWidget::fogToggled( bool on )
{
  _fog->fogEnabled = on;
  
  /*
  if ( on )
  {
    // je¿eli w³±czamy - trzeba wys³aæ wszystko
    fogDensityChanged( _fog->fogDensity );
    fogStartChanged( _fog->fogStart );
    fogEndChanged( _fog->fogEnd );
    fogColorChanged( fogColorBox->color(), fogColorBox->alpha() );
    fogModeChanged( fogModeCombo->currentItem() );
  }*/
  
  emit fogChanged( _fog, FogAll );
}


// parametr mode jest indeksem fogCombo
void FogWidget::fogModeChanged( int mode )
{
  switch ( mode )
  {
    case 0 : _fog->fogMode = GL_EXP;    break;
    case 1 : _fog->fogMode = GL_EXP2;   break;
    case 2 : _fog->fogMode = GL_LINEAR; break;
    default : return;
  }   
  emit fogChanged( _fog, FogMode );
}



void FogWidget::fogDensityChanged( float density )
{
  _fog->fogDensity = (GLfloat) density;
  emit fogChanged( _fog, FogDensity );
}



void FogWidget::fogStartChanged( float start )
{
  _fog->fogStart = (GLfloat) start;
  emit fogChanged( _fog, FogStart );
}



void FogWidget::fogEndChanged( float end )
{
  _fog->fogEnd = (GLfloat) end;
  emit fogChanged( _fog, FogEnd );
}



void FogWidget::fogColorChanged( const QColor& color, int alpha )
{
  GLfloat r,g,b,a;
  
  r = (GLfloat) color.red()   / 255.0;
  g = (GLfloat) color.green() / 255.0;
  b = (GLfloat) color.blue()  / 255.0;
  a = (GLfloat) alpha / 255.0;
  
  _fog->fogColor[0] = r;
  _fog->fogColor[1] = g;
  _fog->fogColor[2] = b;
  _fog->fogColor[3] = a;
  
  emit fogChanged( _fog, FogColor );
}


// metoda ustawia jako kolor mg³y aktualny kolor t³a sceny - najlepszy efekt
void FogWidget::getBackgroundColor()
{
  fogColorBox->setColor( Options::backgroundColor(), 255 );
}
