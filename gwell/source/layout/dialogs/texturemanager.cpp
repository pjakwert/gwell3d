// ////////////////////////////////////////////////////////////////////////////////
///
///  class: TextureManager (.cpp)
///
///  klasa zarz�dza kolejk� tekstur, wszystkie metody statyczne
///
////////////////////////////////////////////////////////////////////////////////

#include "texturemanager.h"


#include "cellframe.h"


QPtrList<Texture> TextureManager::textureList = QPtrList<Texture>();

bool TextureManager::_verbose = false;

bool TextureManager::_safeMode = false;
int  TextureManager::_safeSize = 512;

bool TextureManager::_autoRemoveUnusedTextures = false;


//////////////////////////////////////// ustawienie kontekstu OpenGL, do kt�rego �adowane b�d� tekstury
CellFrame* TextureManager::hostFrame = 0L;



void TextureManager::makeCurrent()
{
  if ( hostFrame ) hostFrame->makeCurrent();
  else
  {
     printf("TextureManager: no host frame with OpenGL context set, textures will go to heaven.\n");
     printf("TextureManager: use TextureManager::setHostFrame( CellFrame* hostFrame ).\n");
     printf("a po polsku znaczy to tyle, �eby� przed �adowaniem tekstur ustawi� widok-kontener :)\n");
  }
}

////////////////////////////////// ustawienie comboBox-a, do kt�rego zapisywane b�d� za�adowane tekstury
QComboBox* TextureManager::loadedTexturesCombo = 0L;

/// metoda ustawia combo w kt�rym b�d� wy�wietlane u�ywane tekstury
void TextureManager::setComboBox( QComboBox* loadedTexCombo )
{ 
  loadedTexturesCombo = loadedTexCombo;
  if ( loadedTexturesCombo ) updateComboBox();
}

void TextureManager::updateComboBox()
{
  if ( !loadedTexturesCombo ) return;
  
  loadedTexturesCombo->clear();
  
  QString s;
  QString mipmap;
  QString scaleMode;
  for ( Texture* tex = textureList.first(); tex; tex = textureList.next() )
  {
    if ( tex->mipmapingEnabled() ) mipmap = "mipmaping"; else mipmap = "no mipmaping";
    
    switch ( tex->scaleMode() )
    {
      case QImage::ScaleFree : scaleMode = "ScaleFree"; break;
      case QImage::ScaleMin  : scaleMode = "ScaleMin"; break;
      case QImage::ScaleMax  : scaleMode = "ScaleMax"; break;
      default : scaleMode = "BAD SCALE"; break;
    }
    
    s = QString("%1, %2, %3").arg( tex->fileName() ).arg( scaleMode ).arg( mipmap );
    
    if ( tex->preview() ) 
      loadedTexturesCombo->insertItem( *(tex->preview()), s );
    else
      loadedTexturesCombo->insertItem( s );
  }
}



// 1. metoda sprawdza czy do TextureManager-a pod��czone jest comboBox,
// 2. odpowiednio ustala o kt�r� tekstur� chodzi ( comboBox->currentItem() )
// 3. zadaje tekstur� obiektom
// 4. zwraca ID zadanej tekstury
GLint TextureManager::addTextureToObjectsFromCombo( QPtrList<ViNTreeNode> *selectedList )
{
  if ( !loadedTexturesCombo ) return 0;
  
  QString s = loadedTexturesCombo->currentText();
  
  if ( s.isEmpty() ) return 0;
  
  QImage::ScaleMode scaleMode = QImage::ScaleMax;
  bool mipmap = false;
  
  QString fileName   = s.section( ", ", 0,0 );
  QString scaleModeS = s.section( ", ", 1,1 );
  QString mipmapS    = s.section( ", ", 2,2 );
  
       if ( scaleModeS == "ScaleFree" ) scaleMode = QImage::ScaleFree;
  else if ( scaleModeS == "ScaleMin"  ) scaleMode = QImage::ScaleMin;
  
  if ( mipmapS == "mipmaping" ) mipmap = true;
  
///////////////////////////////////////////////////////////// szukamy tekstury o podanych parametrach
  for ( Texture* tex = textureList.first(); tex; tex = textureList.next() )
  {
    Texture pattTex( fileName, scaleMode, mipmap, 0, 0 );
    
    if ( (*tex) == pattTex ) // znaleziono tak� tekstur�
    {
      addTextureToObjects( selectedList, tex->GLTextureID() );
      return tex->GLTextureID();
    }
  }
/////////////////////////////////////////////////////////////////////////////////////////////////////
  StatusBar::printStatusMsg( "ComboBox error: YOU SHOULDN'T SEE THIS MESSAGE", "TextureManager" );
  return 0;
}




// metoda �aduje tekstury obiekt�w sk�adowych g��wnego obiektu z�o�onego,
// zastosowaniem metody jest �adowanie MPH z dysku
//  je�eli jaka� tekstura ju� jest w pami�ci - nie robi nic,
//  je�eli nie ma takiej tekstury - tworzy j�
void TextureManager::loadTexturesFromObjects( ViMultiPolyh *mph )
{
  makeCurrent();
  updateComboBox();
  if (mph == 0L) return;
}



// !!!!!!!! METODA NIE ZMIENIA howManyUsers
// metoda przeszukuje list� czy tekstury o takich parametrach nie ma ju� w pami�ci,
//  je�eli nie ma - tworzy now�, dodaje do listy i zwraca jej GLTextureID
//  je�eli jest - zwraca jej GLTextureID
GLuint TextureManager::createTexture( QString fileName, QImage::ScaleMode scaleMode, bool mipmapEnabled, const QImage* inputImage )
{
  makeCurrent();
  
  //if (_verbose) StatusBar::printStatusMsg( tr("##############  createTexture  ##############"), "TextureManager" );
  
  Texture inTex( fileName, scaleMode, mipmapEnabled, 0, 0 );
  if ( !inTex.isValid() ) return 0; // nazwa pliku jest nieprawid�owa
  if ( inputImage->isNull() ) return 0; // z�y obraz
  
  
  
////////////////////////////////////////////////////////// szukamy tekstury o podanych parametrach
  for ( Texture* tex = textureList.first(); tex; tex = textureList.next() )
  {
    Texture pattTex( fileName, scaleMode, mipmapEnabled, 0, 0 );
    
    if ( (*tex) == pattTex ) // znaleziono tak� tekstur�
    {
      //if (_verbose) StatusBar::printStatusMsg( tr("createTexture: texture found (ID=%1)").arg(tex->GLTextureID()), "TextureManager" );
      return ( tex->GLTextureID() ); // zwraca jej ID
    }
  }
///////////////////////////////////////////////////////////////////////////////////////////////////
  
  
    //if (_verbose) StatusBar::printStatusMsg( tr("createTexture: texture not found, create new"), "TextureManager" );
    
    // zmiana rozmiar�w obrazu, �eby by�y 2^n
    int newWidth  = 1 << (int) (1 + log(inputImage->width() -1+1E-3) / log(2.0));
    int newHeight = 1 << (int) (1 + log(inputImage->height()-1+1E-3) / log(2.0));
    
    //if (_verbose)
      //StatusBar::printStatusMsg( tr("createTexture: (newWidth,newHeight) = %1x%2").arg(newWidth).arg(newHeight), "TextureManager");
    
    QImage img;
    
     // je�eli wymiary nie s� 2^n -  obraz musi by� przeskalowany
    if ( (newWidth != inputImage->width()) || (newHeight != inputImage->height()) )
    {
      img = inputImage->scale( newWidth, newHeight, scaleMode ).copy(0,0,newWidth,newHeight);
    }
    else 
    {
      img = inputImage->copy(0,0,newWidth,newHeight); // je�eli obraz jest w porz�dku
    }
    
    //if (_verbose)
      //StatusBar::printStatusMsg( tr("createTexture: inputImg=%1x%2, scaledImage=%3x%4").arg(inputImage->width()).arg(inputImage->height()).arg(img.width()).arg(img.height()), "TextureManager");
    
    // konwersja obrazu na format OpenGL
    QImage glImage = QGLWidget::convertToGLFormat( img );
    
    // wygeneruj nowe GLTextureID
    GLuint texID[1];
    do
    {
      glGenTextures( 1, texID );
    } while ( (findTexture( texID[0] ) != 0L) );
    
    //if (_verbose) StatusBar::printStatusMsg( tr("createTexture: new ID=%1").arg(texID[0]), "TextureManager" );
    
    // podpinamy nowe ID do tekstury
    glBindTexture( GL_TEXTURE_2D, texID[0] );
    
    
    
//////////////////////////////////////////////////////////////////// tworzymy mipmapy czy jedn� tekstur�?
    
    // je�eli (safeMode==OFF) lub (ON i wymiary s� bezpieczne), tw�rz mipmapy 
    if ( ( mipmapEnabled && (!_safeMode) ) ||
       ( mipmapEnabled && _safeMode && (img.width()<=_safeSize) && (img.height()<=_safeSize)) )
    { // mipmapy
      gluBuild2DMipmaps( GL_TEXTURE_2D, 
                         GL_RGBA, 
                         glImage.width(), glImage.height(), 
                         GL_RGBA, 
                         GL_UNSIGNED_BYTE, 
                         glImage.bits() );
      
      //if (_verbose) StatusBar::printStatusMsg( tr("createTexture: mipmapping, size is safe"), "TextureManager" );
    }
    
    else 
    
    // wymiary nie s� bezpieczne - ponownie przeskaluj obraz i utw�rz mipmapy
    if ( mipmapEnabled && _safeMode && ((img.width()>_safeSize) || (img.height()>_safeSize)))
    {
      int newW = img.width();
      int newH = img.height();
       int oldW = newW; // for verbose mode
       int oldH = newH; // for verbose mode
      
      do {              // skaluj tak d�ugo, a� wymiary nie b�d� bezpieczne
          newW /= 2;
          newH /= 2;
         } while ( (newW>_safeSize) || (newH>_safeSize) );
      
      QImage safeImg = img.scale( newW, newH, QImage::ScaleFree ).copy(0,0,newW,newH);
      glImage.reset();
      glImage = QGLWidget::convertToGLFormat( safeImg );
      safeImg.reset(); // usu� niepotrzebne dane z pami�ci
      img.reset();
      
      gluBuild2DMipmaps( GL_TEXTURE_2D, 
                         GL_RGBA, 
                         glImage.width(), glImage.height(), 
                         GL_RGBA, 
                         GL_UNSIGNED_BYTE, 
                         glImage.bits() );
      
      //if (_verbose) StatusBar::printStatusMsg( tr("createTexture: mipmapping, need resizing from %1x%2 to %3x%4").arg(oldW).arg(oldH).arg(newW).arg(newH), "TextureManager" );
    }
    
    else
      
    { // pojedyncza tekstura
      glTexImage2D( GL_TEXTURE_2D, 
                    0, 
                    GL_RGBA, 
                    glImage.width(), glImage.height(), 
                    0, 
                    GL_RGBA, 
                    GL_UNSIGNED_BYTE, 
                    glImage.bits() );
      
      //if (_verbose) StatusBar::printStatusMsg( tr("createTexture: single texture"), "TextureManager" );
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////    
    
    // utw�rz podgl�d
    int w = 32;
    int h = 32;
    QPixmap *preview = new QPixmap( inputImage->scale( w,h, scaleMode).copy( 0,0,w,h ) );
    
    // dodaj tekstur� do listy textureList : nowe ID, na razie bez u�ytkownika
    Texture *newTex = new Texture( fileName, scaleMode, mipmapEnabled, texID[0], 0, preview );
    textureList.append( newTex );
    
    updateComboBox();
    //if (_verbose) StatusBar::printStatusMsg(tr("createTexture: newTex->GLTextureID()=%1, newTex->howMany()=%2").arg(newTex->GLTextureID()).arg(newTex->howManyUsers()), "TextureManager");
    
      
  return texID[0]; // zwraca nowe ID
}





// zadawanie tekstury pojedynczemu obiektowi na podstawie ID - PRIVATE
void TextureManager::addTextureToObject( ViElemePolyhExt* elem, GLuint GLTextureID )
{
  if ( elem == 0L ) return;
  
  if ( GLTextureID == 0 ) return;
  
  if ( elem->textureParams()->GLTexID() == GLTextureID ) return; // obiekt ma w�a�nie t� tekstur�
  
  decHowManyUsers( elem->textureParams()->GLTexID() ); // zmniejszamy u�ytkownik�w starej teksturze
  
  elem->textureParams()->setGLTexID( GLTextureID );    // zadajemy now�
  
  incHowManyUsers( GLTextureID );                      // zwi�kszamy u�ytkownik�w nowej
  
   //if (_verbose) StatusBar::printStatusMsg( tr("addTextureToObject: elem->setGLTexID(%1)").arg(GLTextureID), "TextureManager" );
  
  if ( _autoRemoveUnusedTextures ) removeUnusedTextures();
}




// zadawanie tekstury pojedynczemu obiektowi - PUBLIC
void TextureManager::addTextureToObject( ViElemePolyhExt* elem, QString fileName, QImage::ScaleMode scaleMode, bool mipmapEnabled, const QImage* image )
{
  GLuint newID = createTexture( fileName, scaleMode, mipmapEnabled, image );
  addTextureToObject( elem, newID );  
}


// zadawanie tekstury pojedynczemu obiektowi na podstawie TextureParams - PUBLIC
void TextureManager::addTextureToObject( ViElemePolyhExt* elem, TextureParams* textureParams )
{
  if ( elem == 0L ) return;
  if ( textureParams == 0L ) return;
  
  if ( textureParams->GLTexID() == 0 ) { elem->textureParams()->setGLTexID( 0 ); return; }
  
  if ( findTexture( textureParams->GLTexID() ) )
  {
    addTextureToObject( elem, textureParams->GLTexID() );
    return;
  }
  
  // nie znaleziono takiej tekstury, wi�c ustaw 0
  elem->textureParams()->setGLTexID( 0 );
}



// metoda zadaje tekstur� o podanym ID wszystkim obiektom z listy
void TextureManager::addTextureToObjects( QPtrList<ViNTreeNode> *selectedList, GLuint GLTextureID )
{
  if ( selectedList->isEmpty() ) return; // pusta lista
  
  // je�eli zadajemy tekstur� o ID=0 to znaczy, �e usuwamy obiektom tekstury
  if ( GLTextureID == 0 ) { deleteTexturesFromObjects( selectedList ); return; }
        
  ViElemePolyhExt* extEl;
  
  // zadajemy tekstur� wszystkim elementom
  for ( ViNTreeNode* sel = selectedList->first(); sel; sel = selectedList->next() )
  {
    if ( sel->GetInheritorType() != IT_ELEMEPOLYH ) continue; // tylko elementy ViElemePolyhExt
    
    extEl = dynamic_cast<ViElemePolyhExt*> (sel);
    if (extEl == 0L)
    { 
      //StatusBar::printStatusMsg( tr("addTexturesToObjects error: extEl == 0L"), "TextureManager" );
      continue; // to nie powinno si� zda�y�
    }
    
  
    // obiekt ju� posiada w�a�nie tak� tekstur� - nic nie trzeba robi�
    if ( extEl->textureParams()->GLTexID() == GLTextureID )
    {
     //if (_verbose) StatusBar::printStatusMsg( tr("add: elem->GLTexID = GLTextureID, continue"), "TextureManager" );
     continue;
    }
    
    
    // teksturze u�ywanej wcze�niej przez obiekt zmniejszamy howManyUsers
    decHowManyUsers( extEl->textureParams()->GLTexID() );
    
    // zadajemy temu obiektowi nowe GLTextureID
    extEl->textureParams()->setGLTexID( GLTextureID );
    
    incHowManyUsers( GLTextureID );
    
     //if (_verbose) StatusBar::printStatusMsg( tr("addTexturesToObjects: elem->setGLTexID(%1)").arg(GLTextureID), "TextureManager" );
    // zwi�kszamy teksturze liczb� u�ytkownik�w
  }
  
  printInfo();
  
  if ( _autoRemoveUnusedTextures ) removeUnusedTextures(); // na ko�cu usuwamy wszystkie nieu�ywane tekstury ( howManyUsers==0 )
}




// metoda najpierw szuka/tworzy tekstur� o zadanych parametrach a nast�pnie zadaje j�
// obiektom
void TextureManager::addTextureToObjects( QPtrList<ViNTreeNode> *selectedList, QString fileName, QImage::ScaleMode scaleMode, bool mipmapEnabled, const QImage* image)
{
  GLuint newID = createTexture( fileName, scaleMode, mipmapEnabled, image );
  addTextureToObjects( selectedList, newID );
}




// metoda powinna by� wywo�ana przed usuni�ciem obiekt�w z pami�ci (delete)
// przegl�da ca�� list� i zmniejsza howManyUsers teksturom u�ywanym przez te obiekty
// dzi�ki temu, je�eli usuni�to obiekt, wykorzystuj�cy jako jedyny dan� tekstur� -
// b�dzie ona usuni�ta z pami�ci
void TextureManager::deleteTexturesFromObjects( QPtrList<ViNTreeNode> *selectedList )
{
  if ( selectedList->isEmpty() ) return; // pusta lista
        
  ViElemePolyhExt *extEl;
  
  for ( ViNTreeNode* sel = selectedList->first(); sel; sel = selectedList->next() )
  {
    if ( sel->GetInheritorType() != IT_ELEMEPOLYH ) continue; // tylko elementy ViElemePolyhExt
    
    extEl = dynamic_cast<ViElemePolyhExt*> (sel);
    if (extEl == 0L)
    { 
      //StatusBar::printStatusMsg( tr("deleteTexturesFromObjects error: extEl == 0L"), "TextureManager" );
      continue; // to nie powinno si� zda�y�
    }
    
    // ID=0 : ten element nie posiada tekstury - skip
    if ( extEl->textureParams()->GLTexID() == 0) continue;
    
     // szukamy tekstury o takim ID
    Texture* tex = findTexture( extEl->textureParams()->GLTexID() );
    if (tex == 0L)
    { 
      //StatusBar::printStatusMsg( tr("deleteTexturesFromObjects error: tex == 0L"), "TextureManager" );
      continue; // to nie powinno si� zda�y�
    }
    
    // znalezionej teksturze zmniejszamy liczb� jej u�ytkownik�w
    tex->decHowManyUsers();
    // obiektowi ustawiamy GLTextureID=0
    extEl->textureParams()->setGLTexID( 0 );
  }
  
  removeUnusedTextures(); // na ko�cu usuwamy wszystkie nieu�ywane tekstury ( howManyUsers==0 )
}




// metoda usuwa tekstur� pojedynczemu obiektowi
void TextureManager::deleteTextureFromObject( ViElemePolyhExt* elem ) // usuwanie tekstur
{
  if ( elem->textureParams()->GLTexID() == 0 ) return; // obiekt nie posiada tekstury
  
  Texture* tex = findTexture( elem->textureParams()->GLTexID() );
  if ( tex == 0L )
  {
    //StatusBar::printStatusMsg( tr("deleteTextureFromObject error: tex == 0L"), "TextureManager" );
    return;
  }
  
  tex->decHowManyUsers();
  elem->textureParams()->setGLTexID( 0 );
  
  removeUnusedTextures();
}




// metoda zwi�ksza liczb� u�ytkownik�w tekstury o podanym ID
// zwraca liczb� u�ytkownik�w tekstury po zwi�kszeniu,
// 0 dla TextID=0, -1, je�eli nie znalaz� takiej tekstury
int TextureManager::incHowManyUsers( GLuint GLTextureID )
{
  if ( GLTextureID == 0 ) return 0; // pusta tekstura

  GLuint h;
  
  Texture *tex = findTexture( GLTextureID );
  if ( tex ) // znaleziono
  {
    h = tex->incHowManyUsers();
      //if (_verbose) StatusBar::printStatusMsg(tr("incHowManyUsers for ID=%1 to %2").arg(GLTextureID).arg(h), "TextureManager");
    return h;
  }
  
  // tutaj nie powinni�my doj�� - nie znaleziono takiego ID
  //StatusBar::printStatusMsg(tr("incHowManyUsers error : incorrect texture ID=%1").arg(GLTextureID), "TextureManager");
  return -1;
}




// metoda zmniejsza liczb� u�ytkownik�w tekstury o podanym ID
// zwraca liczb� u�ytkownik�w tekstury po zmniejszeniu,
// 0 dla TextID=0, -1, je�eli nie znalaz� takiej tekstury
int TextureManager::decHowManyUsers( GLuint GLTextureID )
{
  if ( GLTextureID == 0 ) return 0; // pusta tekstura

  GLuint h;
    
  Texture* tex = findTexture( GLTextureID );
  if ( tex )
  {
    h = tex->decHowManyUsers();
    //  if (_verbose) StatusBar::printStatusMsg(tr("decHowManyUsers for ID=%1 to %2").arg(GLTextureID).arg(h), "TextureManager");
    return h;
  }
  
  // tutaj nie powinni�my doj�� - nie znaleziono takiego ID
  //StatusBar::printStatusMsg(tr("decHowManyUsers error : incorrect texture ID=%1").arg(GLTextureID), "TextureManager");
  return -1;
}




// metoda zwraca wska�nik do tekstury o podanym ID
Texture* TextureManager::findTexture( GLuint GLTextureID )
{
  if ( GLTextureID == 0 ) return 0L;
  
  for ( Texture* tex = textureList.first(); tex; tex = textureList.next() )
  {
    if ( (tex->GLTextureID()) == GLTextureID ) return tex;
  }
  // nie znaleziono tekstury o takim ID
  return 0L;
}
    
   
// zwraca referencj� szukanej tekstury lub pust� tekstur� w razie niepowodzenia,
// flaga found jest ustawiana w zale�no�ci od rezultatu poszukiwa�
const Texture& TextureManager::getTexture( GLuint GLTextureID, bool* found )
{
  // pusta tekstura jest zwracana, je�eli nie znajdzie tekstury
  static const Texture emptyTexture = Texture( QString::null, QImage::ScaleFree, true, 0, 0 );
  
  if ( GLTextureID == 0 ) { *found = false; return emptyTexture; }
  
  Texture* tex = findTexture( GLTextureID );
  
  if ( tex )
  {
     *found = true;
     return (*tex);
  }
  else 
  {
      *found = false;
      return emptyTexture;
  }
}


// metoda przegl�da list� i usuwa wszystkie tekstury, kt�re maj� howManyUsers==0
// tekstury usuwane s� z listy textureList i z OpenGL
void TextureManager::removeUnusedTextures()
{
  makeCurrent();
  
  GLuint texID[1];
  
  //if (_verbose) StatusBar::printStatusMsg( tr("removeUnusedTextures: all textures count = %1").arg(textureList.count()), "TextureManager" );
  
  // szukamy i usuwamy tekstury, kt�re maj� howManyUsers==0
  Texture* tex = textureList.first();
  while ( tex )
  {
    if ( tex->howManyUsers() == 0 )
    {
      texID[0] = tex->GLTextureID();
    //    if (_verbose) StatusBar::printStatusMsg( tr("removeUnusedTextures: no users for ID=%1, remove").arg(texID[0]), "TextureManager" );
      glDeleteTextures( 1, texID );
      
      delete tex;
      
      textureList.remove();
      tex = textureList.first();
    }
    else tex = textureList.next();
  }
    
  updateComboBox();
  
  //if (_verbose) StatusBar::printStatusMsg( tr("removeUnusedTextures: textures count after removal = %1").arg(textureList.count()), "TextureManager" );
}




void TextureManager::printInfo()
{
  if (!_verbose) return;
  
  /*
  QString s;
  QString out;
  int i=0;
  
  out = QString("--------------------- textureList ----------------------");
  StatusBar::printStatusMsg( out, "textureList" );
  
  for ( Texture* tex = textureList.first(); tex; tex = textureList.next() )
  {
    out = QString("%1: filename=%2, ID=%3, howMany=%4").arg(i++).arg(tex->fileName()).arg(tex->GLTextureID()).arg(tex->howManyUsers());
    StatusBar::printStatusMsg( out, "textureList" );
  }
  
  out = QString("-------------------------------------------------------");
  StatusBar::printStatusMsg( out, "textureList" );
  */
}

