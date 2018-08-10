////////////////////////////////////////////////////////////////////////////////
///
///  class: TextureWidget (.cpp)
///
///  widget do edycji w³a¶ciwo¶ci tekstury - jedna z zak³adek w MaterialEditor
///
////////////////////////////////////////////////////////////////////////////////

#include "texturewidget.h"
#include <cellframe.h>


// makro FOR_EACH_OBJECT DO [wywo³anie metody dla ViElemePolyhExt]; END
// wywo³uje metodê dla wszystkich obiektów klasy ViElemePolyhExt znajduj±cych siê na li¶cie
// _selectedList, czyli wszystkich zaznaczonych obiektów, dla których definiujemy materia³
// UWAGA !!! METODA OD¦WIE¯A WIDOKI CellFrame !!! w zale¿no¶ci od zmiennej _dynamicPreview
// przyk³ad: FOR_EACH_OBJECT DO setTextureEnabled(true); END
#define FOR_EACH_OBJECT \
for (ViNTreeNode* _selected = _selectedList->first(); _selected; _selected = _selectedList->next()) \
{ \
  if (_selected->GetInheritorType() != IT_ELEMEPOLYH) continue; \
  ViElemePolyhExt* extEl = dynamic_cast<ViElemePolyhExt*> (_selected);

#define DO extEl->
#define END } refresh();



QString TextureWidget::_lastPath = "./"; // ostatnio odwiedzona ¶cie¿ka przy wyborze obrazka

QImage  TextureWidget::_lastImage = QImage(); // ostatnio generowany podgl±d
QString TextureWidget::_lastFileName = QString();


TextureWidget::TextureWidget( QPtrList<ViNTreeNode> *selectedList, QWidget *parent, const char* name, WFlags fl ) : QWidget( parent, name, fl )
{
  _selectedList = selectedList;

  
  ///////////////////////////////////////////////////////////////////////////     GUI
  mainFrame = new QFrame( this, "mainFrame" );
  mainFrame->setFrameStyle( QFrame::Box | QFrame::Sunken );
    
  textureEnabledCheck = new QCheckBox( tr("Texture enabled"), mainFrame );
  dynamicPreviewCheck = new QCheckBox( tr("Dynamic preview"), mainFrame );
  mipmapCheck         = new QCheckBox( tr("Mipmaping"), mainFrame );
  mipmapCheck->setChecked( true ); // bo to jest dobre
  reflectCheck        = new QCheckBox( tr("Reflecting"), mainFrame );
  reflectCheck->hide();
  
  topLine = new QFrame( mainFrame );
  topLine->setFrameStyle( QFrame::HLine | QFrame::Sunken );
   
  texParamsGroup  = new QGroupBox( tr(" Texture parameters "), mainFrame );
  texParamsGroup->setAlignment( QGroupBox::AlignHCenter );
    magFilterCombo = new QComboBox( false, texParamsGroup );
    magFilterLabel = new QLabel( magFilterCombo, tr("GL_TEXTURE_MAG_FILTER"), texParamsGroup );
    minFilterCombo = new QComboBox( false, texParamsGroup );
    minFilterLabel = new QLabel( minFilterCombo, tr("GL_TEXTURE_MIN_FILTER"), texParamsGroup );
    wrapSCombo     = new QComboBox( false, texParamsGroup );
    wrapSLabel     = new QLabel( wrapSCombo, tr("GL_TEXTURE_WRAP_S"), texParamsGroup );
    wrapTCombo     = new QComboBox( false, texParamsGroup );
    wrapTLabel     = new QLabel( wrapTCombo, tr("GL_TEXTURE_WRAP_T"), texParamsGroup );
    envModeCombo   = new QComboBox( false, texParamsGroup );
    envModeLabel   = new QLabel( envModeCombo, tr("GL_TEXTURE_ENV_MODE"), texParamsGroup );
   
  blendGroup = new QGroupBox( tr(" Blending "), mainFrame );
  blendGroup->setAlignment( QGroupBox::AlignHCenter );
   enableBlendCheck = new QCheckBox( tr("Blending enabled"), blendGroup );
   srcBlendCombo    = new QComboBox( false, blendGroup );
   srcBlendLabel    = new QLabel( srcBlendCombo, tr("source factor"), blendGroup );
   destBlendCombo   = new QComboBox( false, blendGroup );
   destBlendLabel   = new QLabel( destBlendCombo, tr("destination factor"), blendGroup );
   
  imageParamsGroup = new QGroupBox( tr(" Image parameters "), mainFrame );
  imageParamsGroup->setAlignment( QGroupBox::AlignHCenter );
   loadImageButton = new QPushButton( tr("load Image ..."), imageParamsGroup );
   removeImageButton = new QPushButton( tr("remove image"), imageParamsGroup );
   scaleModeCombo  = new QComboBox( false, imageParamsGroup );
   scaleModeLabel  = new QLabel( scaleModeCombo, tr("Image scale mode"), imageParamsGroup );
   previewLabel    = new QLabel( imageParamsGroup );
   previewLabel->setFrameStyle( QFrame::Box | QFrame::Sunken );
   previewLabel->setAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
   fileEdit        = new QLineEdit( imageParamsGroup );
   fileEdit->setReadOnly( true );
   fileLabel       = new QLabel( fileEdit, tr("file"), imageParamsGroup );
   origSizeEdit    = new QLineEdit( imageParamsGroup );
   origSizeEdit->setReadOnly( true );
   origSizeLabel   = new QLabel( origSizeEdit, tr("original size"), imageParamsGroup );
   currSizeEdit    = new QLineEdit( imageParamsGroup );
   currSizeEdit->setReadOnly( true );
   currSizeLabel   = new QLabel( currSizeEdit, tr("current size"), imageParamsGroup );
   
  coordsGroup = new QGroupBox( tr(" Texture Coords "), mainFrame );
  coordsGroup->setAlignment( QGroupBox::AlignHCenter );
   MINlabel   = new QLabel( tr("MIN"), coordsGroup );
   MINlabel->setAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
   MAXlabel   = new QLabel( tr("MAX"), coordsGroup );
   MAXlabel->setAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
   widthLabel  = new QLabel( tr("width"), coordsGroup );
   widthLabel->setAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
   heightLabel = new QLabel( tr("height"), coordsGroup );
   heightLabel->setAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
    minWSpin      = new FloatSpinBox( -100.0, 100.0, 0.1, 2, coordsGroup );
    minHSpin      = new FloatSpinBox( -100.0, 100.0, 0.1, 2, coordsGroup );
    maxWSpin      = new FloatSpinBox( -100.0, 100.0, 0.1, 2, coordsGroup );
    maxHSpin      = new FloatSpinBox( -100.0, 100.0, 0.1, 2, coordsGroup );
  
  makeDefaultButton = new QPushButton( tr("make default"), mainFrame );
  makeDefaultButton->hide();
  resetToDefaultButton = new QPushButton( tr("reset to default"), mainFrame );
  resetToDefaultButton->hide();
  
  loadedTexturesCombo = new QComboBox( false, mainFrame );
  QToolTip::add( loadedTexturesCombo, tr("textures already loaded") );
  TextureManager::setComboBox( loadedTexturesCombo );
  ///////////////////////////////////////////////////////////////////////////     GUI


  ////////////////////////////////////////////////////////////////// zmieniamy fonty
  f10.setFamily(this->font().family());
  f10.setPointSize(this->font().pointSize()-2);
  f9 = f10;
  f9.setPointSize(this->font().pointSize()-3);
  
  magFilterLabel->setFont( f10 );
  minFilterLabel->setFont( f10 );
  wrapSLabel->setFont( f10 );
  wrapTLabel->setFont( f10 );
  envModeLabel->setFont( f10 );
  fileLabel->setFont( f10 );
  currSizeLabel->setFont( f10 );
  origSizeLabel->setFont( f10 );
  
  fileEdit->setFont( f10 );
  origSizeEdit->setFont( f10 );
  currSizeEdit->setFont( f10 );
  
  magFilterCombo->setFont( f10 );
  minFilterCombo->setFont( f10 );
  wrapSCombo->setFont( f10 );
  wrapTCombo->setFont( f10 );
  envModeCombo->setFont( f10 );
  scaleModeCombo->setFont( f10 );
  srcBlendCombo->setFont( f10 );
  destBlendCombo->setFont( f10 );
  MINlabel->setFont( f10 );
  MAXlabel->setFont( f10 );
  widthLabel->setFont( f10 );
  heightLabel->setFont( f10 );
  
  loadedTexturesCombo->setFont( f10 );
  
  makeDefaultButton->setFont( f10 );
  resetToDefaultButton->setFont( f10 );
  ////////////////////////////////////////////////////////////////// zmieniamy fonty
  
    
  
  //////////////////////////////////////////////////////////////////////////// GEOMETRIA    
  mainFrame->setGeometry( 10, 10, 770, 480 );
  textureEnabledCheck->setGeometry( 10, 10, 130, 22 );
  dynamicPreviewCheck->setGeometry( 180, 10, 130, 22 );
  mipmapCheck->setGeometry( 350, 10, 90, 22 );
  reflectCheck->setGeometry( 450, 10, 90, 22 );
  
  topLine->setGeometry( 10, 30, 750, 20 );
  
  texParamsGroup->setGeometry( 10, 50, 410, 180 );
   magFilterLabel->setGeometry( 10, 20, 170, 20 );
   magFilterCombo->setGeometry( 185, 20, 215, 20 );
   minFilterLabel->setGeometry( 10, 50, 170, 20 );
   minFilterCombo->setGeometry( 185, 50, 215, 20 );
   wrapSLabel->setGeometry( 10, 80, 160, 20 );
   wrapSCombo->setGeometry( 185, 80, 215, 20 );
   wrapTLabel->setGeometry( 10, 110, 160, 20 );
   wrapTCombo->setGeometry( 185, 110, 215, 20 );
   envModeLabel->setGeometry( 10, 140, 170, 20 );
   envModeCombo->setGeometry( 185, 144, 215, 20 );
  
  blendGroup->setGeometry( 10, 230, 410, 110 );
   enableBlendCheck->setGeometry( 11, 21, 191, 22 );
   srcBlendLabel->setGeometry( 11, 49, 170, 24 );
   srcBlendCombo->setGeometry( 185, 49, 215, 24 );
   destBlendLabel->setGeometry( 11, 79, 170, 24 );
   destBlendCombo->setGeometry( 185, 79, 215, 24 );  
   
  imageParamsGroup->setGeometry( 430, 50, 330, 390 );
   loadImageButton->setGeometry( 10, 20, 150, 25 );
   removeImageButton->setGeometry( 180, 20, 140, 25 );
   scaleModeLabel->setGeometry( 10, 54, 150, 17 );
   scaleModeCombo->setGeometry( 170, 54, 150, 20 ); 
   previewLabel->setGeometry( 10,80, 310,210 );
   fileLabel->setGeometry( 10,300, 20,20 );
   fileEdit->setGeometry( 40,300, 280,20 );
   origSizeLabel->setGeometry( 10,330, 76,20 );
   origSizeEdit->setGeometry( 90,330, 230,20 );
   currSizeLabel->setGeometry( 10,360, 75,20 );
   currSizeEdit->setGeometry( 90,360, 230,20 );
   
   coordsGroup->setGeometry( 10, 340, 200, 130 );
    MINlabel->setGeometry( 55, 30, 65, 17 );
    MAXlabel->setGeometry( 125, 30, 65, 17 );
    widthLabel->setGeometry( 5, 50, 40, 24 );
    heightLabel->setGeometry( 5, 90, 40, 24 );
     minWSpin->setGeometry( 55, 50, 65, 24 );
     minHSpin->setGeometry( 55, 90, 65, 24 );
     maxWSpin->setGeometry( 125, 50, 65, 24 );
     maxHSpin->setGeometry( 125, 90, 65, 24 );
     
   makeDefaultButton->setGeometry( 260, 370, 110, 20 );
   resetToDefaultButton->setGeometry( 260, 410, 110, 20 );
   
   loadedTexturesCombo->setGeometry( 220, 445, 540, 30 );
  //////////////////////////////////////////////////////////////////////////// GEOMETRIA
  
  
  ////////////////////////////////////////////////////////////////////////  WYPE£NIENIE COMBO 
  QStringList list;
  
  // MAG_FILTER
  list << "GL_NEAREST" << "GL_LINEAR";
  magFilterCombo->insertStringList( list ); // tu nie ma czyszczenia listy !!!!
         
  // MIN_FILTER
  list << "GL_NEAREST_MIPMAP_NEAREST" << "GL_NEAREST_MIPMAP_LINEAR" << "GL_LINEAR_MIPMAP_NEAREST" <<
          "GL_LINEAR_MIPMAP_LINEAR";
  minFilterCombo->insertStringList( list ); 
  list.clear();
  
  // WRAP_S i WRAP_T
  list << "GL_CLAMP" << "GL_REPEAT";
  wrapSCombo->insertStringList( list );
  wrapTCombo->insertStringList( list ); // oba zawieraj± to samo
  list.clear();
  
  // ENV_MODE
  list << "GL_DECAL" << "GL_MODULATE" << "GL_BLEND";
  envModeCombo->insertStringList( list ); 
  list.clear();
       
  // SCALEMODE
  list << tr("scale Free") << tr("scale Min") << tr("scale Max");
  scaleModeCombo->insertStringList( list );
  list.clear();
  
  // SRCBLEND i DSTBLEND
  list << "GL_ZERO" << "GL_ONE" << "GL_DST_COLOR" << "GL_SRC_COLOR" << "GL_ONE_MINUS_DST_COLOR" <<
          "GL_ONE_MINUS_SRC_COLOR" << "GL_SRC_ALPHA" << "GL_ONE_MINUS_SRC_ALPHA" << "GL_DST_ALPHA" << "GL_ONE_MINUS_DST_ALPHA" << "GL_SRC_ALPHA_SATURATE";
  srcBlendCombo->insertStringList( list );
  destBlendCombo->insertStringList( list ); // oba zawieraj± to samo
  
  srcBlendCombo->setSizeLimit( list.count() );
  destBlendCombo->setSizeLimit( list.count() );
  
  list.clear(); // na wszelki wypadek w razie pó¼niejszej próby u¿ycia
  
  ////////////////////////////////////////////////////////////////////////  WYPE£NIENIE COMBO 
  
  
  
  ////////////////////////////////////////////////////////////////////////////////////////  connections
  connect( textureEnabledCheck, SIGNAL( toggled(bool) ), this, SLOT( setTextureEnabled(bool) ) );
  connect( dynamicPreviewCheck, SIGNAL( toggled(bool) ), this, SLOT( setDynamicPreview(bool) ) );
  connect( mipmapCheck, SIGNAL( toggled(bool) ), this, SLOT( setMipmapingEnabled(bool) ) );
  connect( reflectCheck, SIGNAL( toggled(bool) ), this, SLOT( setReflectingEnabled(bool) ) );
  
  connect( magFilterCombo, SIGNAL( activated(int) ), this, SLOT( setMagFilterFromCombo(int) ) );
  connect( minFilterCombo, SIGNAL( activated(int) ), this, SLOT( setMinFilterFromCombo(int) ) );
  connect( wrapSCombo, SIGNAL( activated(int) ), this, SLOT( setWrapSFromCombo(int) ) );
  connect( wrapTCombo, SIGNAL( activated(int) ), this, SLOT( setWrapTFromCombo(int) ) );
  connect( envModeCombo, SIGNAL( activated(int) ), this, SLOT( setEnvModeFromCombo(int) ) );
  
  connect( enableBlendCheck, SIGNAL( toggled(bool) ), this, SLOT( setBlendingEnabled(bool) ) );
  connect( srcBlendCombo, SIGNAL( activated(int) ), this, SLOT( setBlendSrcFactorFromCombo(int) ) );
  connect( destBlendCombo, SIGNAL( activated(int) ), this, SLOT( setBlendDestFactorFromCombo(int) ) );
  
  connect( minWSpin, SIGNAL( valueChanged(float) ), this, SLOT( minWHChanged(float) ) );
  connect( minHSpin, SIGNAL( valueChanged(float) ), this, SLOT( minWHChanged(float) ) );
  connect( maxWSpin, SIGNAL( valueChanged(float) ), this, SLOT( maxWHChanged(float) ) );
  connect( maxHSpin, SIGNAL( valueChanged(float) ), this, SLOT( maxWHChanged(float) ) );
  
  connect( loadImageButton, SIGNAL( clicked() ), this, SLOT( openFileDialog() ) );
  connect( removeImageButton, SIGNAL( clicked() ), this, SLOT( removeImage() ) );
  connect( scaleModeCombo, SIGNAL( activated(int) ), this, SLOT( setScaleModeFromCombo( int ) ) );
  connect( loadedTexturesCombo, SIGNAL( activated(int) ), this, SLOT( loadTextureFromCombo(int) ) );
  
  connect( makeDefaultButton, SIGNAL( clicked() ), this, SLOT( makeCurrentTextureDefault() ) );
  connect( resetToDefaultButton, SIGNAL( clicked() ), this, SLOT( resetToDefaultTexture() ) );
  
  ////////////////////////////////////////////////////////////////////////////////////////  connections
  
  
  
  //////////////////////////////////////////////////////////////////////// BACKUP
  //
  //////////////////////////////////////////////////////////////////////// BACKUP
  
  
  
  //////////////////////////////////////////////////////////////// INICJALIZACJA DANYMI OBIEKTU
  if (!_selectedList->isEmpty())
  {
    ViNTreeNode* _selected;
    bool found=false;
    for (_selected = _selectedList->first(); _selected; _selected = _selectedList->next())
    {
      if (_selected->GetInheritorType() == IT_ELEMEPOLYH) {found=true; break;} // pierwszy lepszy viElemePolyhExt
    }

    if (found) // inicjujemy dialog warto¶ciami tego obiektu
    {
      ViElemePolyhExt *extEl = dynamic_cast<ViElemePolyhExt*> (_selected);
      
      TextureParams *tp = extEl->textureParams(); // wska¼nik na parametry tekstury elementu
      
      // czy element posiada teksturê?
      if ( tp->GLTexID() == 0 ) { generatePreviewAndInfo(); } // nie posiada
      else
      { // je¿eli tak, szukamy jej
        bool found;
        const Texture tex = TextureManager::getTexture( tp->GLTexID(), &found );
        if ( !found )
        {
          StatusBar::printStatusMsg(tr("Texture not found (ID error)"), "TextureWidget");
        }
        else
        {
          _lastFileName = tex.fileName();
          _lastImage.load( _lastFileName );
          // generuj podgl±d
          generatePreviewAndInfo( tex.fileName(), tex.scaleMode(), &_lastImage );
          // ustawiamy odpowiednio ScaleModeCombo, nic nie robimy obiektom
          setScaleMode( tex.scaleMode(), false );
          // ustawiamy Mipmaping
          mipmapCheck->blockSignals( true );
           mipmapCheck->setChecked( tex.mipmapingEnabled() );
          mipmapCheck->blockSignals( false );
        }
      }
      
      // teraz ustawiamy parametry tekstury (w³a¶ciwe obiektowi)
      // inicjalizacja widgetów
      setTextureEnabledGUI ( extEl->textureEnabled() );
      setMagFilter      ( tp->magFilter(), false );
      setMinFilter      ( tp->minFilter(), false );
      setWrapS          ( tp->wrapS(), false );
      setWrapT          ( tp->wrapT(), false );
      setEnvMode        ( tp->envMode(), false );
      setBlendingEnabledGUI( tp->blendingEnabled() );
      setBlendSrcFactor ( tp->blendSrcFactor(), false );
      setBlendDestFactor( tp->blendDestFactor(), false );
      reflectCheck->setChecked( tp->reflectingEnabled() );
      /*
      setMinWH          ( tp->minW(), tp->minH(), false );
      setMaxWH          ( tp->maxW(), tp->maxH(), false );
      */
      minWSpin->blockSignals( true );
      minHSpin->blockSignals( true );
      maxWSpin->blockSignals( true );
      maxHSpin->blockSignals( true );
        minWSpin->setFloatValue( tp->minW() );
        minHSpin->setFloatValue( tp->minH() );
        maxHSpin->setFloatValue( tp->maxH() );
        maxWSpin->setFloatValue( tp->maxW() );
      minWSpin->blockSignals( false );
      minHSpin->blockSignals( false );
      maxWSpin->blockSignals( false );
      maxHSpin->blockSignals( false );  
      
    } // if (found)
  } // if (!empty)
  //////////////////////////////////////////////////////////////// INICJALIZACJA DANYMI OBIEKTU
  
  setDynamicPreview( true );
  
  _lastPath = Options::imagesPath();
}





// generuje podgl±d obrazka i wy¶wietla info poni¿ej
void TextureWidget::generatePreviewAndInfo( QString fileName, QImage::ScaleMode scaleMode, const QImage* inputImage )
{
  if ( fileName.isEmpty() ) // brak obrazka do pokazania
  {
    previewLabel->setText( tr("No Image") );
    setInfo();
    return;
  }
  
  if ( inputImage->isNull() )
  {
    previewLabel->setText( tr("Bad Image Data") );
    setInfo();
    return;
  }
    
  // rozmiar podgl±du
  int w = previewLabel->width()-10;
  int h = previewLabel->height()-10;
  
  // rozmiary obrazu dobrane tak, aby by³y 2^n
  int newWidth  = 1 << (int) (1 + log(inputImage->width() -1+1E-3) / log(2.0));
  int newHeight = 1 << (int) (1 + log(inputImage->height()-1+1E-3) / log(2.0));
  
  QPixmap pix;
  
  // obraz spe³nia 2^n
  if ( (newWidth == inputImage->width()) && (newHeight == inputImage->height()) )
  {
    if ( (inputImage->width()<=w) && (inputImage->height()<=h) ) // ale mo¿e jest na tyle ma³y, ¿e wejdzie
      pix = QPixmap( *inputImage );
    else pix = QPixmap( inputImage->scale( w,h, QImage::ScaleMin) );
  }
  else  
  // obraz jest tak ma³y, ¿e nie trzeba go skalowaæ
  if ( (inputImage->width()<=w) && (inputImage->height()<=h) )
  {
    pix = QPixmap( *inputImage );
  }
  else
  // normalne skalowanie
  {
    pix = QPixmap( (inputImage->scale( w,h, scaleMode )).copy(0,0,w,h) );
  }
  
  previewLabel->setPixmap( pix );
  
  // ustawiamy INFO
    QString os = QString("%1 x %2").arg(inputImage->width()).arg(inputImage->height()); // stary rozmiar
    QString ns = QString("%1 x %2").arg(newWidth).arg(newHeight); // nowy rozmiar
    setInfo( fileName, os, ns ); // ustaw info
  //
}





// metoda ustawia info poni¿ej previewLabel
void TextureWidget::setInfo( QString fileName, QString oldSize, QString newSize )
{
  fileEdit->setText( fileName );
  origSizeEdit->setText( oldSize );
  currSizeEdit->setText( newSize );
}






// metoda otwiera dialog do wyboru obrazu i zadaje obiektom now± teksturê
void TextureWidget::openFileDialog()
{
  // fileDialog z podgl±dem
  ImagePreview *prev = new ImagePreview;
  QFileDialog *fileDialog = new QFileDialog( _lastPath, 
                                             tr("Images (*.png *.jpg *.xpm *.bmp)"),
                                             this );
  fileDialog->setCaption( tr("Select an image") );
  
  fileDialog->setContentsPreviewEnabled( true );
  fileDialog->setContentsPreview( prev, prev );
  fileDialog->setPreviewMode( QFileDialog::Contents );
  
  QString fileName;
  
  if ( fileDialog->exec() == QDialog::Accepted ) fileName = fileDialog->selectedFile();
  else return; // CANCEL pressed
  
  if ( fileName.isEmpty() ) return;  // pusta nazwa pliu
  
  QFileInfo fileInfo( fileName );
  _lastPath = fileInfo.dirPath( true ); // zapamiêtaj ostatnio u¿ywan± ¶cie¿kê

  QImage::ScaleMode scaleMode;
  switch( scaleModeCombo->currentItem() )
  {
    case 0 : scaleMode = QImage::ScaleFree; break;
    case 1 : scaleMode = QImage::ScaleMin;  break;
    case 2 : scaleMode = QImage::ScaleMax;  break;
    default: {
              StatusBar::printStatusMsg(tr("scaleModeCombo error: bad ScaleMode"), "TextureWidget");
              scaleMode = QImage::ScaleFree;
              break;
             }
  }
  
  if ( fileName != _lastFileName ) // user wybra³ inny plik ni¿ by³ poprzednio - za³aduj go
  {
    _lastImage.reset();
    _lastImage.load( fileName );
    _lastFileName = fileName;
  }
  
  // wszystkim obiektom zadajemy now± teksturê
  TextureManager::addTextureToObjects( _selectedList, _lastFileName, scaleMode, mipmapCheck->isChecked(), &_lastImage );
  
  // generujemy podgl±d i info
  generatePreviewAndInfo( _lastFileName, scaleMode, &_lastImage );
  
  refresh();
}



// usuwa obraz obiektom
void TextureWidget::removeImage()
{
  TextureManager::deleteTexturesFromObjects( _selectedList );
  generatePreviewAndInfo();
  refresh();
}






void TextureWidget::setTextureEnabled ( bool yes )
{
  textureEnabledCheck->blockSignals( true );
   textureEnabledCheck->setChecked( yes );
  textureEnabledCheck->blockSignals( false ); 
  
  FOR_EACH_OBJECT DO setTextureEnabled( yes ); END
  
  dynamicPreviewCheck->setEnabled( yes );
  mipmapCheck->setEnabled( yes );
  reflectCheck->setEnabled( yes );
  texParamsGroup->setEnabled( yes );
  imageParamsGroup->setEnabled( yes );
  blendGroup->setEnabled( yes );
  coordsGroup->setEnabled( yes );
  loadedTexturesCombo->setEnabled( yes );
  resetToDefaultButton->setEnabled( yes );
  makeDefaultButton->setEnabled( yes );
}




// mechanizm - setMagFilterFromCombo jest slotem dekoduj±cym pozycjê w combo (int) na GLenum,
//             z którym wywo³uje metodê setMagFilter(), która siê zajmuje ca³ym ustawianiem
//             wszystko inne dzia³a podobnie
// je¿eli apply=true, zmiana stosowana jest do obiektów
void TextureWidget::setMagFilter( GLenum magFilter, bool apply )
{
  int n=-1;
  switch ( magFilter )
  {
    case GL_NEAREST : n = 0; break;
    case GL_LINEAR  : n = 1; break;
    default : StatusBar::printStatusMsg( tr("magFilter error"), "TextureWidget" ); return;
  }
  magFilterCombo->setCurrentItem( n );
  if (apply) { FOR_EACH_OBJECT DO textureParams()->setMagFilter( magFilter ); END }
}

void TextureWidget::setMagFilterFromCombo( int n )
{
  GLenum mf;
  
  switch ( n )
  {
    case 0 : mf = GL_NEAREST; break;
    case 1 : mf = GL_LINEAR;  break;
    default : StatusBar::printStatusMsg( tr("magFilter combo error"), "TextureWidget" ); return;
  }
  setMagFilter( mf, true );
}
////////////////////////////////////////////////////////////////////////////////////////////////////



void TextureWidget::setMinFilter( GLenum minFilter, bool apply )
{
  int n=-1;
  switch ( minFilter )
  {
    case GL_NEAREST : n=0; break;
    case GL_LINEAR  : n=1; break;
    case GL_NEAREST_MIPMAP_NEAREST : n=2; break;
    case GL_NEAREST_MIPMAP_LINEAR  : n=3; break;
    case GL_LINEAR_MIPMAP_NEAREST  : n=4; break;
    case GL_LINEAR_MIPMAP_LINEAR   : n=5; break;
    default : StatusBar::printStatusMsg( tr("minFilter error"), "TextureWidget" ); return;
  }
  minFilterCombo->setCurrentItem( n );
  if (apply) { FOR_EACH_OBJECT DO textureParams()->setMinFilter( minFilter ); END }
}

void TextureWidget::setMinFilterFromCombo( int n )
{
  GLenum mf;
  
  switch ( n )
  {
    case 0 : mf = GL_NEAREST; break;
    case 1 : mf = GL_LINEAR;  break;
    case 2 : mf = GL_NEAREST_MIPMAP_NEAREST; break;
    case 3 : mf = GL_NEAREST_MIPMAP_LINEAR; break;
    case 4 : mf = GL_LINEAR_MIPMAP_NEAREST; break;
    case 5 : mf = GL_LINEAR_MIPMAP_LINEAR; break;
    default : StatusBar::printStatusMsg( tr("minFilter combo error"), "TextureWidget" ); return;
  }
  setMinFilter( mf, true );
}
////////////////////////////////////////////////////////////////////////////////////////////////////





void TextureWidget::setWrapS( GLenum wrapS, bool apply )
{  
  int n=-1;
  switch ( wrapS )
  {
    case GL_CLAMP  : n = 0; break;
    case GL_REPEAT : n = 1; break;
    default : StatusBar::printStatusMsg( tr("wrapS error"), "TextureWidget" ); return;
  }
  wrapSCombo->setCurrentItem( n );
  if (apply) { FOR_EACH_OBJECT DO textureParams()->setWrapS( wrapS ); END }
}

void TextureWidget::setWrapSFromCombo( int n )
{
  GLenum ws;
  
  switch ( n )
  {
    case 0 : ws = GL_CLAMP; break;
    case 1 : ws = GL_REPEAT;  break;
    default : StatusBar::printStatusMsg( tr("wrapS combo error"), "TextureWidget" ); return;
  }
  setWrapS( ws, true );
}
////////////////////////////////////////////////////////////////////////////////////////////////////




void TextureWidget::setWrapT( GLenum wrapT, bool apply )
{  
  int n=-1;
  switch ( wrapT )
  {
    case GL_CLAMP  : n = 0; break;
    case GL_REPEAT : n = 1; break;
    default : StatusBar::printStatusMsg( tr("wrapT error"), "TextureWidget" ); return;
  }
  wrapTCombo->setCurrentItem( n );
  if (apply) { FOR_EACH_OBJECT DO textureParams()->setWrapT( wrapT ); END }
}

void TextureWidget::setWrapTFromCombo( int n )
{
  GLenum wt;
  
  switch ( n )
  {
    case 0 : wt = GL_CLAMP; break;
    case 1 : wt = GL_REPEAT;  break;
    default : StatusBar::printStatusMsg( tr("wrapT combo error"), "TextureWidget" ); return;
  }
  setWrapT( wt, true );
}
////////////////////////////////////////////////////////////////////////////////////////////////////




void TextureWidget::setEnvMode( GLenum envMode, bool apply )
{  
  int n=-1;
  switch ( envMode )
  {
    case GL_DECAL    : n = 0; break;
    case GL_MODULATE : n = 1; break;
    case GL_BLEND    : n = 2; break;
    default : StatusBar::printStatusMsg( tr("envMode error"), "TextureWidget" ); return;
  }
  envModeCombo->setCurrentItem( n );
  if (apply) { FOR_EACH_OBJECT DO textureParams()->setEnvMode( envMode ); END }
}

void TextureWidget::setEnvModeFromCombo( int n )
{
  GLenum em;
  
  switch ( n )
  {
    case 0 : em = GL_DECAL;    break;
    case 1 : em = GL_MODULATE; break;
    case 2 : em = GL_BLEND;    break;
    default : StatusBar::printStatusMsg( tr("envMode combo error"), "TextureWidget" ); return;
  }
  setEnvMode( em, true );
}
////////////////////////////////////////////////////////////////////////////////////////////////////




// ta metoda s³u¿y równie¿ jako slot
void TextureWidget::setBlendingEnabled( bool yes )
{
  enableBlendCheck->blockSignals( true );
   enableBlendCheck->setChecked( yes );
  enableBlendCheck->blockSignals( false );
  
  srcBlendLabel->setEnabled( yes );
  srcBlendCombo->setEnabled( yes );
  destBlendLabel->setEnabled( yes );
  destBlendCombo->setEnabled( yes );
  
  FOR_EACH_OBJECT DO textureParams()->setBlendingEnabled( yes ); END
}



void TextureWidget::setBlendSrcFactor ( GLenum srcFactor, bool apply )
{ 
  int n=-1;
  switch ( srcFactor )
  {
    case GL_ZERO      : n = 0; break;
    case GL_ONE       : n = 1; break;
    case GL_DST_COLOR : n = 2; break;
    case GL_SRC_COLOR : n = 3; break;
    case GL_ONE_MINUS_DST_COLOR : n = 4; break;
    case GL_ONE_MINUS_SRC_COLOR : n = 5; break;
    case GL_SRC_ALPHA           : n = 6; break;
    case GL_ONE_MINUS_SRC_ALPHA : n = 7; break;
    case GL_DST_ALPHA           : n = 8; break;
    case GL_ONE_MINUS_DST_ALPHA : n = 9; break;
    case GL_SRC_ALPHA_SATURATE  : n = 10; break;
    default : StatusBar::printStatusMsg( tr("srcFactor error"), "TextureWidget" ); return;
  }
  srcBlendCombo->setCurrentItem( n );
  if (apply) { FOR_EACH_OBJECT DO textureParams()->setBlendSrcFactor( srcFactor ); END }
}

void TextureWidget::setBlendSrcFactorFromCombo ( int n )
{
  GLenum bsf;
  
  switch ( n )
  {
    case 0 : bsf = GL_ZERO; break;
    case 1 : bsf = GL_ONE; break;
    case 2 : bsf = GL_DST_COLOR; break;
    case 3 : bsf = GL_SRC_COLOR; break;
    case 4 : bsf = GL_ONE_MINUS_DST_COLOR; break;
    case 5 : bsf = GL_ONE_MINUS_SRC_COLOR; break;
    case 6 : bsf = GL_SRC_ALPHA; break;
    case 7 : bsf = GL_ONE_MINUS_SRC_ALPHA; break;
    case 8 : bsf = GL_DST_ALPHA; break;
    case 9 : bsf = GL_ONE_MINUS_DST_ALPHA; break;
    case 10 : bsf = GL_SRC_ALPHA_SATURATE; break;
    default : StatusBar::printStatusMsg( tr("srcFactor combo error"), "TextureWidget" ); return;
  }
  setBlendSrcFactor( bsf, true );
}
////////////////////////////////////////////////////////////////////////////////////////////////////





void TextureWidget::setBlendDestFactor ( GLenum destFactor, bool apply )
{ 
  int n=-1;
  switch ( destFactor )
  {
    case GL_ZERO      : n = 0; break;
    case GL_ONE       : n = 1; break;
    case GL_DST_COLOR : n = 2; break;
    case GL_SRC_COLOR : n = 3; break;
    case GL_ONE_MINUS_DST_COLOR : n = 4; break;
    case GL_ONE_MINUS_SRC_COLOR : n = 5; break;
    case GL_SRC_ALPHA           : n = 6; break;
    case GL_ONE_MINUS_SRC_ALPHA : n = 7; break;
    case GL_DST_ALPHA           : n = 8; break;
    case GL_ONE_MINUS_DST_ALPHA : n = 9; break;
    case GL_SRC_ALPHA_SATURATE  : n = 10; break;
    default : StatusBar::printStatusMsg( tr("destFactor error"), "TextureWidget" ); return;
  }
  destBlendCombo->setCurrentItem( n );
  if (apply) { FOR_EACH_OBJECT DO textureParams()->setBlendDestFactor( destFactor ); END }
}

void TextureWidget::setBlendDestFactorFromCombo ( int n )
{
  GLenum bsf;
  
  switch ( n )
  {
    case 0 : bsf = GL_ZERO; break;
    case 1 : bsf = GL_ONE; break;
    case 2 : bsf = GL_DST_COLOR; break;
    case 3 : bsf = GL_SRC_COLOR; break;
    case 4 : bsf = GL_ONE_MINUS_DST_COLOR; break;
    case 5 : bsf = GL_ONE_MINUS_SRC_COLOR; break;
    case 6 : bsf = GL_SRC_ALPHA; break;
    case 7 : bsf = GL_ONE_MINUS_SRC_ALPHA; break;
    case 8 : bsf = GL_DST_ALPHA; break;
    case 9 : bsf = GL_ONE_MINUS_DST_ALPHA; break;
    case 10 : bsf = GL_SRC_ALPHA_SATURATE; break;
    default : StatusBar::printStatusMsg( tr("destFactor combo error"), "TextureWidget" ); return;
  }
  setBlendDestFactor( bsf, true );
}
////////////////////////////////////////////////////////////////////////////////////////////////////



// metoda s³u¿y równie¿ jako slot
void TextureWidget::setReflectingEnabled( bool yes )
{
  reflectCheck->blockSignals( true );
    reflectCheck->setChecked( yes );
  reflectCheck->blockSignals( false );
  
  FOR_EACH_OBJECT DO textureParams()->setReflectingEnabled( yes ); END
}
//////////////////////////////////////////////////////////////////////////////////////////



void TextureWidget::setMinWH( GLfloat minW, GLfloat minH, bool apply )
{
  /*
  minWSpin->blockSignals( true );
  minHSpin->blockSignals( true );
    minWSpin->setFloatValue( (float) minW );
    minHSpin->setFloatValue( (float) minH );
  minWSpin->blockSignals( false );
  minHSpin->blockSignals( false );  
  */
  
  if (apply) { FOR_EACH_OBJECT DO textureParams()->setMinWH( minW, minH ); END }
}

void TextureWidget::minWHChanged( float )
{
  GLfloat minW = (GLfloat) (minWSpin->floatValue());
  GLfloat minH = (GLfloat) (minHSpin->floatValue());
  setMinWH( minW, minH, true );
}
////////////////////////////////////////////////////////////////////////////////////////



void TextureWidget::setMaxWH( GLfloat maxW, GLfloat maxH, bool apply )
{
  /*
  maxWSpin->blockSignals( true );
  maxHSpin->blockSignals( true );
    maxWSpin->setFloatValue( (float) maxW );
    maxHSpin->setFloatValue( (float) maxH );
  maxWSpin->blockSignals( false );
  maxHSpin->blockSignals( false );  
  */
  if (apply) { FOR_EACH_OBJECT DO textureParams()->setMaxWH( maxW, maxH ); END }
}

void TextureWidget::maxWHChanged( float )
{
  GLfloat maxW = (GLfloat) (maxWSpin->floatValue());
  GLfloat maxH = (GLfloat) (maxHSpin->floatValue());
  setMaxWH( maxW, maxH, true );
}
////////////////////////////////////////////////////////////////////////////////////////


    
void TextureWidget::setDynamicPreview ( bool on )
{
  dynamicPreviewCheck->blockSignals( true );
    dynamicPreviewCheck->setChecked( on );
  dynamicPreviewCheck->blockSignals( false );
  
  _dynamicPreview = on;
  refresh();
}


void TextureWidget::refresh()
{
  if (_dynamicPreview) CellFrame::refresh();
}



// ustawia scaleModeCombo na odpowiedni± warto¶æ
void TextureWidget::setScaleMode( QImage::ScaleMode scaleMode, bool apply )
{
  int n=-1;
  switch ( scaleMode )
  {
    case QImage::ScaleFree : n = 0; break;
    case QImage::ScaleMin  : n = 1; break;
    case QImage::ScaleMax  : n = 2; break;
    default : StatusBar::printStatusMsg(tr("ScaleMode error"), "TextureWidget"); return;
  }
    
  scaleModeCombo->setCurrentItem( n );
    
  if (apply)
  {
    // wszystkim obiektom zadajemy now± teksturê
    TextureManager::addTextureToObjects( _selectedList, _lastFileName, scaleMode, mipmapCheck->isChecked(), &_lastImage );
  
    // generujemy podgl±d i info
    generatePreviewAndInfo( _lastFileName, scaleMode, &_lastImage );
    
    refresh();
  }
}


void TextureWidget::setScaleModeFromCombo( int n )
{
  QImage::ScaleMode sm;
  
  switch ( n )
  {
    case 0 : sm = QImage::ScaleFree; break;
    case 1 : sm = QImage::ScaleMin;  break;
    case 2 : sm = QImage::ScaleMax;  break;
    default : StatusBar::printStatusMsg(tr("ScaleMode combo error"), "TextureWidget"); return;
  }
  setScaleMode( sm, true );
}
///////////////////////////////////////////////////////////////////////////////////////



// ustawia mipmapCheck na odpowiedni± warto¶æ i generuje teksturê
void TextureWidget::setMipmapingEnabled( bool yes )
{
  mipmapCheck->setChecked( yes );
  
  QImage::ScaleMode sm;
  switch ( scaleModeCombo->currentItem() )
  {
    case 0 : sm = QImage::ScaleFree; break;
    case 1 : sm = QImage::ScaleMin; break;
    case 2 : sm = QImage::ScaleMax; break;
    default : StatusBar::printStatusMsg(tr("ScaleMode combo error"), "TextureWidget"); return;
  }
  
  // tworzymy now± teksturê
  TextureManager::addTextureToObjects( _selectedList, _lastFileName, sm, yes, &_lastImage );
  
  refresh();
}   






void TextureWidget::resetToDefaultTexture()
{
  
}


void TextureWidget::makeCurrentTextureDefault()
{
  
  
}


// slot wywo³uje metodê statyczn± TextureManager-a, zadaj±c± obiektowi teksturê ju¿ za³adowan±
void TextureWidget::loadTextureFromCombo( int )
{
  GLint TextureID = TextureManager::addTextureToObjectsFromCombo( _selectedList );
  
  bool found;
  const Texture tex = TextureManager::getTexture( TextureID, &found );
  
  _lastFileName = tex.fileName();
  _lastImage.load( _lastFileName );
  // generuj podgl±d
  generatePreviewAndInfo( tex.fileName(), tex.scaleMode(), &_lastImage );
  // ustawiamy odpowiednio ScaleModeCombo, nic nie robimy obiektom
  setScaleMode( tex.scaleMode(), false );
  // ustawiamy Mipmaping
  mipmapCheck->blockSignals( true );
   mipmapCheck->setChecked( tex.mipmapingEnabled() );
  mipmapCheck->blockSignals( false );
}



//////////////////////////////////////////////////////////////////////////////////// GUI only METHODS
void TextureWidget::setTextureEnabledGUI ( bool yes )
{
  textureEnabledCheck->blockSignals( true );
   textureEnabledCheck->setChecked( yes );
  textureEnabledCheck->blockSignals( false ); 
  
  dynamicPreviewCheck->setEnabled( yes );
  mipmapCheck->setEnabled( yes );
  reflectCheck->setEnabled( yes );
  texParamsGroup->setEnabled( yes );
  imageParamsGroup->setEnabled( yes );
  blendGroup->setEnabled( yes );
  coordsGroup->setEnabled( yes );
  loadedTexturesCombo->setEnabled( yes );
  resetToDefaultButton->setEnabled( yes );
  makeDefaultButton->setEnabled( yes );
}

void TextureWidget::setBlendingEnabledGUI ( bool yes )
{
  enableBlendCheck->blockSignals( true );
   enableBlendCheck->setChecked( yes );
  enableBlendCheck->blockSignals( false );
  
  srcBlendLabel->setEnabled( yes );
  srcBlendCombo->setEnabled( yes );
  destBlendLabel->setEnabled( yes );
  destBlendCombo->setEnabled( yes );
}

//////////////////////////////////////////////////////////////////////////////////// GUI only METHODS


void TextureWidget::undoTexturing()
{
  
}
