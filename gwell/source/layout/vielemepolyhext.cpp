#include "vielemepolyhext.h"


int ViElemePolyhExt::_count = 0; // licznik obiektów tej klasy

// tworzymy domy¶lny materia³ (wg OpenGL)
Material ViElemePolyhExt::_DefMaterial = Material(
                                                  "OpenGL default",
                                                  QColor(51,51,51),    255, // ambient
                                                  QColor(204,204,204), 255, // diffuse
                                                  QColor(0,0,0),       255, // specular
                                                  QColor(0,0,0),       255, // emission
                                                  0                         // shininess
                                                 );

// tworzymy domy¶lne parametry tekstury
TextureParams ViElemePolyhExt::_DefTextureParams = TextureParams();

                                                 

// konstruktor domy¶lny
ViElemePolyhExt::ViElemePolyhExt( )
{
  // nazwa obiektu
  QString s = QString("_noPattePolyh_%2").arg( _count );
  SetName( s.ascii() );
  
  /////////////////////////////////////////// utworzenie materia³u dla elementu i ustawienie na domy¶lny
  _material = new Material;
  *_material = _DefMaterial;  
  // domy¶lnie materia³ jest w³±czony
  setMaterialEnabled( true );
  // domy¶lnie stosujemy materia³ do GL_FRONT
  setApplyTo( GL_FRONT );
  
  /////////////////////////////////////////// utworzenie tekstury dla elementu i ustawienie na domy¶ln±
  _textureParams = new TextureParams;
  *_textureParams = _DefTextureParams;
  // domy¶lnie tekstura jest wy³±czona
  setTextureEnabled( false );
  // zadaj teksturê obiektowi
  TextureManager::addTextureToObject( this, _textureParams );
  
  _count++;
}



// konstruktor parametryczny
ViElemePolyhExt::ViElemePolyhExt( ViPattePolyh const &PPolyh, const char *IndivName )
{
  SetPattePolyh( PPolyh );
  SetName( IndivName );

  /////////////////////////////////////////// utworzenie materia³u dla elementu i ustawienie na domy¶lny
  _material = new Material;
  *_material = _DefMaterial;  
  // domy¶lnie materia³ jest w³±czony
  setMaterialEnabled( true );
  // domy¶lnie stosujemy materia³ do GL_FRONT
  setApplyTo( GL_FRONT );
  
  /////////////////////////////////////////// utworzenie tekstury dla elementu i ustawienie na domy¶ln±
  _textureParams = new TextureParams;
  *_textureParams = _DefTextureParams;
  // domy¶lnie tekstura jest wy³±czona
  setTextureEnabled( false );
  // zadaj teksturê obiektowi
  TextureManager::addTextureToObject( this, _textureParams );
  
  _count++;
}



// konstruktor kopiuj±cy
ViElemePolyhExt::ViElemePolyhExt( const ViElemePolyhExt &extEl )
{
  SetPattePolyh( extEl.PattePolyh() ); // bry³a taka sama
  
  // nazwa obiektu
  QString s = QString("%1_%2").arg(extEl.PattePolyh().GetName()).arg(_count);
  SetName( s.ascii() );
  
  _material = new Material; // kopiujemy materia³
  *_material = *(extEl.material());
  setMaterialEnabled( extEl.materialEnabled() );
  setApplyTo( extEl.applyTo() );
  
  _textureParams = new TextureParams; // kopiujemy teksturê
  TextureManager::addTextureToObject( this, extEl.textureParams() );
  
  setTextureEnabled( extEl.textureEnabled() );
  *_textureParams = *(extEl.textureParams() ); // przepisanie parametrów na koñcu !!!
  
  // skopiuj równie¿ transformacje
  MatrixH3f m;
  m = extEl.Mtx2SolidFigCoord();
  this->SetMtx2SolidFigCoord( m );
  
  m = extEl.Mtx2IndivCoord();
  this->SetMtx2IndivCoord( m );
  
  m = extEl.Mtx2ParentCoord();
  this->SetMtx2ParentCoord( m );
  
  _count++;
}




// destruktor usuwa swoj± teksturê (przynajmniej powinien, ale jest b³±d - wogle nie jest wywo³ywany!)
ViElemePolyhExt::~ViElemePolyhExt()
{
  //printf(" jestem destruktorem ViElemePolyhExt\n ");
  //TextureManager::deleteTextureFromObject( this ); to jest wykonywane w CellFrame::deleteSelectedObjects(), poniewa¿ ten destruktor nie jest wywo³ywany
}


// opis materia³u i tekstury zapisujemy sobie ³adnie w XML-u
// !!! NAZWA MATERIA£U NIE JEST ZAPISYWANA DO PLIKU - JEDYNIE JEGO PARAMETRY !!!
bool ViElemePolyhExt::WriteDescriptionTo(ExtString &Descr) const
{
  QString txt;
  const GLfloat *mat;
  
  QDomDocument doc; // g³ówny dokument XML
  
/////////////////////////////////////////////////////////////////////////////// MATERIAL
  QDomElement root = doc.createElement( ELEMENT_PROPERTIES );
  doc.appendChild( root );
  
  QDomElement main = doc.createElement( MATERIAL_MAIN );
  root.appendChild( main );

  if (_materialEnabled) txt="true"; else txt="false";
  main.setAttribute(ATTR_MATERIAL_ENABLED, txt);

  switch (_applyTo)
  {
    case GL_FRONT : txt="GL_FRONT"; break;
    case GL_BACK  : txt="GL_BACK"; break;
    case GL_FRONT_AND_BACK : txt="GL_FRONT_AND_BACK"; break;
    default : txt="unknown (You shouldn't see this)"; break;
  }
  main.setAttribute(ATTR_APPLY_MATERIAL_TO, txt);

  QDomElement ambient = doc.createElement(ELEM_AMBIENT_COLOR);
  main.appendChild(ambient);
    mat = _material->ambientColor4fv();
  ambient.setAttribute(ATTR_RED,   *(mat + 0));
  ambient.setAttribute(ATTR_GREEN, *(mat + 1));
  ambient.setAttribute(ATTR_BLUE,  *(mat + 2));
  ambient.setAttribute(ATTR_ALPHA, *(mat + 3));

  QDomElement diffuse = doc.createElement(ELEM_DIFFUSE_COLOR);
  main.appendChild(diffuse);
    mat = _material->diffuseColor4fv();
  diffuse.setAttribute(ATTR_RED,   *(mat + 0));
  diffuse.setAttribute(ATTR_GREEN, *(mat + 1));
  diffuse.setAttribute(ATTR_BLUE,  *(mat + 2));
  diffuse.setAttribute(ATTR_ALPHA, *(mat + 3));

  QDomElement specular = doc.createElement(ELEM_SPECULAR_COLOR);
  main.appendChild(specular);
    mat = _material->specularColor4fv();
  specular.setAttribute(ATTR_RED,   *(mat + 0));
  specular.setAttribute(ATTR_GREEN, *(mat + 1));
  specular.setAttribute(ATTR_BLUE,  *(mat + 2));
  specular.setAttribute(ATTR_ALPHA, *(mat + 3));

  QDomElement emission = doc.createElement(ELEM_EMISSION_COLOR);
  main.appendChild(emission);
    mat = _material->emissionColor4fv();
  emission.setAttribute(ATTR_RED,   *(mat + 0));
  emission.setAttribute(ATTR_GREEN, *(mat + 1));
  emission.setAttribute(ATTR_BLUE,  *(mat + 2));
  emission.setAttribute(ATTR_ALPHA, *(mat + 3));

  QDomElement shine = doc.createElement(ELEM_SHININESS);
  main.appendChild(shine);
  shine.setAttribute(ATTR_SHININESS, (int) _material->shininess());

/////////////////////////////////////////////////////////////////////////////// TEKSTURA  
  QDomElement mainTex = doc.createElement( TEXTURE_MAIN );
  root.appendChild( mainTex );
  
  if ( _textureEnabled ) txt="true"; else txt="false";
  mainTex.setAttribute( ATTR_TEXTURE_ENABLED, txt );           // tekstura ON/OFF
  
  TextureParams *tp = _textureParams;
  
  if ( tp->reflectingEnabled() ) txt="true"; else txt="false";  // reflecting
  mainTex.setAttribute( ATTR_TEXTURE_REFLECT, txt );
  
  QDomElement imageParams = doc.createElement( ELEM_IMAGE_PARAMS ); // grupa ImageParameters
  mainTex.appendChild( imageParams );
  
  bool found;
  const Texture t = TextureManager::getTexture( tp->GLTexID(), &found ); // szukamy takiej tekstury
  
  // ¶cie¿ka do obrazka
  if ( !found ) txt = "NO IMAGE"; else txt = t.fileName();
  imageParams.setAttribute( ATTR_IMAGE_FILENAME, txt );
  
  // typ skalowania
  switch( t.scaleMode() )
  {
    case QImage::ScaleFree : txt = "ScaleFree"; break;
    case QImage::ScaleMin  : txt = "ScaleMin" ; break;
    case QImage::ScaleMax  : txt = "ScaleMax" ; break;
    default : txt = "Scale ERROR!"; break;
  }
  imageParams.setAttribute( ATTR_IMAGE_SCALEMODE, txt );
  
  // mipmaping
  if ( t.mipmapingEnabled() ) txt = "true"; else txt = "false";
  imageParams.setAttribute( ATTR_IMAGE_MIPMAPING, txt );
  
  
  QDomElement filterParams = doc.createElement( ELEM_FILTERING ); // grupa parametrów filtrowania
  mainTex.appendChild( filterParams );
  
  switch ( tp->magFilter() )
  {
    case GL_NEAREST : txt = "GL_NEAREST"; break;
    case GL_LINEAR  : txt = "GL_LINEAR";  break;
    default : txt = "magFilter ERROR!"; break;
  }
  filterParams.setAttribute( ATTR_FILTER_MAG, txt );
  
  switch ( tp->minFilter() )
  {
    case GL_NEAREST : txt = "GL_NEAREST"; break;
    case GL_LINEAR  : txt = "GL_LINEAR"; break;
    case GL_NEAREST_MIPMAP_NEAREST : txt = "GL_NEAREST_MIPMAP_NEAREST"; break;
    case GL_NEAREST_MIPMAP_LINEAR  : txt = "GL_NEAREST_MIPMAP_LINEAR"; break;
    case GL_LINEAR_MIPMAP_NEAREST  : txt = "GL_LINEAR_MIPMAP_NEAREST"; break;
    case GL_LINEAR_MIPMAP_LINEAR   : txt = "GL_LINEAR_MIPMAP_LINEAR"; break;
    default : txt = "minFilter ERROR!"; break;
  }
  filterParams.setAttribute( ATTR_FILTER_MIN, txt );
  
  switch ( tp->wrapS() )
  {
    case GL_CLAMP  : txt = "GL_CLAMP";  break;
    case GL_REPEAT : txt = "GL_REPEAT"; break;
    default : txt = "wrapS ERROR!"; break;
  }
  filterParams.setAttribute( ATTR_FILTER_WRAPS, txt );
  
  switch ( tp->wrapT() )
  {
    case GL_CLAMP  : txt = "GL_CLAMP";  break;
    case GL_REPEAT : txt = "GL_REPEAT"; break;
    default : txt = "wrapT ERROR!"; break;
  }
  filterParams.setAttribute( ATTR_FILTER_WRAPT, txt );
  
  switch ( tp->envMode() )
  {
    case GL_DECAL    : txt = "GL_DECAL"; break;
    case GL_MODULATE : txt = "GL_MODULATE"; break;
    case GL_BLEND    : txt = "GL_BLEND"; break;
    default : txt = "envMode ERROR!"; break;
  }
  filterParams.setAttribute( ATTR_FILTER_ENVMODE, txt );
  
  
  QDomElement blending = doc.createElement( ELEM_BLENDING ); // grupa parametrów blendingu
  mainTex.appendChild( blending );
    
  if ( tp->blendingEnabled() ) txt="true"; else txt="false"; // blending ON/OFF
  blending.setAttribute( ATTR_BLENDING_ENABLED, txt );
  
  switch ( tp->blendSrcFactor() )
  {
    case GL_ZERO      : txt = "GL_ZERO"; break;
    case GL_ONE       : txt = "GL_ONE"; break;
    case GL_DST_COLOR : txt = "GL_DST_COLOR"; break;
    case GL_SRC_COLOR : txt = "GL_SRC_COLOR"; break;
    case GL_ONE_MINUS_DST_COLOR : txt = "GL_ONE_MINUS_DST_COLOR"; break;
    case GL_ONE_MINUS_SRC_COLOR : txt = "GL_ONE_MINUS_SRC_COLOR"; break;
    case GL_SRC_ALPHA           : txt = "GL_SRC_ALPHA"; break;
    case GL_ONE_MINUS_SRC_ALPHA : txt = "GL_ONE_MINUS_SRC_ALPHA"; break;
    case GL_DST_ALPHA           : txt = "GL_DST_ALPHA"; break;
    case GL_ONE_MINUS_DST_ALPHA : txt = "GL_ONE_MINUS_DST_ALPHA"; break;
    case GL_SRC_ALPHA_SATURATE  : txt = "GL_SRC_ALPHA_SATURATE"; break;
    default : txt = "blendSRC ERROR!"; break;
  }
  blending.setAttribute( ATTR_BLENDING_SRC, txt );
    
  switch ( tp->blendDestFactor() )
  {
    case GL_ZERO      : txt = "GL_ZERO"; break;
    case GL_ONE       : txt = "GL_ONE"; break;
    case GL_DST_COLOR : txt = "GL_DST_COLOR"; break;
    case GL_SRC_COLOR : txt = "GL_SRC_COLOR"; break;
    case GL_ONE_MINUS_DST_COLOR : txt = "GL_ONE_MINUS_DST_COLOR"; break;
    case GL_ONE_MINUS_SRC_COLOR : txt = "GL_ONE_MINUS_SRC_COLOR"; break;
    case GL_SRC_ALPHA           : txt = "GL_SRC_ALPHA"; break;
    case GL_ONE_MINUS_SRC_ALPHA : txt = "GL_ONE_MINUS_SRC_ALPHA"; break;
    case GL_DST_ALPHA           : txt = "GL_DST_ALPHA"; break;
    case GL_ONE_MINUS_DST_ALPHA : txt = "GL_ONE_MINUS_DST_ALPHA"; break;
    case GL_SRC_ALPHA_SATURATE  : txt = "GL_SRC_ALPHA_SATURATE"; break;
    default : txt = "blendDEST ERROR!"; break;
  }
  blending.setAttribute( ATTR_BLENDING_DEST, txt );
  
  // tutaj jeszcze trzeba dodaæ blendingColor //
  //#define ELEM_BLENDING_COLOR    "blendingColor"
  // po tym id± atrybuty ATTR_RED, ATTR_GREEN, ...

  QDomElement texCoords = doc.createElement( ELEM_TEXTURE_COORDS ); // grupa wspó³rzêdnych tekstury
  mainTex.appendChild( texCoords );
  
  texCoords.setAttribute( ATTR_MINW, tp->minW() );
  texCoords.setAttribute( ATTR_MINH, tp->minH() );
  texCoords.setAttribute( ATTR_MAXW, tp->maxW() );
  texCoords.setAttribute( ATTR_MAXH, tp->maxH() );
  
  
////////////////////////////////////////////////////// zapis ca³ego dokumentu do stringa  
  txt = doc.toString(4);
  Descr.clear();
  Descr << txt.ascii();

  return true;
}






// metoda odczytuje parametry danej bry³y elementarnej
// i ustawia je
void ViElemePolyhExt::InitWithDescr( ExtString &Descr )
{
  QString descr( Descr.c_str() );
  QString s;
  bool bv, ok;
  GLenum v;
  float r,g,b,a;
  QDomElement elem;
  
  ////////////////////////////////////// te informacje zostan± u¿yte do utworzenia tekstury
  bool mipmaping;
  QString fileName;
  QImage::ScaleMode scaleMode;
  ////////////////////////////////////// te informacje zostan± u¿yte do utworzenia tekstury
  
  QDomDocument doc;
  doc.setContent( descr, false ); // zawarto¶æ XML-a
  
  QDomElement root = doc.documentElement();
  if ( root.tagName() != ELEMENT_PROPERTIES ) return;
  if ( !root.hasChildNodes() ) return;                 // brak potomków
  
  
  QDomNode mainNode = root.firstChild();
  if ( mainNode.nodeType() != QDomNode::ElementNode ) return;
  QDomElement main = mainNode.toElement();
  
  if ( !main.hasAttributes() ) return;                 // brak atrybutów - z³y XML
  if ( !main.hasChildNodes() ) return;                 // brak potomków
  if ( main.tagName() != MATERIAL_MAIN ) return;       // z³a nazwa wêz³a
  
  // applyTo
  s = main.attribute( ATTR_APPLY_MATERIAL_TO, "GL_FRONT_AND_BACK" );
  if ( s == "GL_FRONT" ) v = GL_FRONT;
  else if ( s == "GL_BACK" ) v = GL_BACK;
  else v = GL_FRONT_AND_BACK;
  setApplyTo( v );
  
  // materialEnabled
  s = main.attribute( ATTR_MATERIAL_ENABLED, "true" );
  ( s == "true" ) ? bv=true : bv=false;
  setMaterialEnabled( bv );
  
  
  // kolory materia³u
  QDomNode node = main.firstChild(); // wêz³y elementu Material
  while ( !node.isNull() )
  {
   if (node.nodeType() != QDomNode::ElementNode) return; // tylko elementy
   elem = node.toElement();

   if ((elem.nodeName() != ELEM_AMBIENT_COLOR)  &&
       (elem.nodeName() != ELEM_DIFFUSE_COLOR)  &&
       (elem.nodeName() != ELEM_SPECULAR_COLOR) &&
       (elem.nodeName() != ELEM_EMISSION_COLOR) &&
       (elem.nodeName() != ELEM_SHININESS)) return;

   if (elem.nodeName() != ELEM_SHININESS) // dla kolorów sprawa wygl±da tak samo, ale shininess..
   {
    QDomAttr red = elem.attributeNode(ATTR_RED);
     if (red.isNull()) return;
     r = red.value().toFloat(&ok);   
     if (!ok) return;
    QDomAttr green = elem.attributeNode(ATTR_GREEN);
     if (green.isNull()) return;
     g = green.value().toFloat(&ok); 
     if (!ok) return;
    QDomAttr blue = elem.attributeNode(ATTR_BLUE);
     if (blue.isNull()) return;
     b = blue.value().toFloat(&ok);
     if (!ok) return;
    QDomAttr alpha = elem.attributeNode(ATTR_ALPHA);
     if (alpha.isNull()) return;
     a = alpha.value().toFloat(&ok); 
     if (!ok) return;

    const GLfloat color[4] = { r, g, b, a };  // tworzymy wektor z odczytanych warto¶ci

    if (elem.tagName() == ELEM_AMBIENT_COLOR)  _material->setAmbientColor ( color );
    if (elem.tagName() == ELEM_DIFFUSE_COLOR)  _material->setDiffuseColor ( color );
    if (elem.tagName() == ELEM_SPECULAR_COLOR) _material->setSpecularColor( color );
    if (elem.tagName() == ELEM_EMISSION_COLOR) _material->setEmissionColor( color );
    
   }
   else // dla shininess jest tylko jeden atrybut
   {
    QDomAttr shine = elem.attributeNode(ATTR_SHININESS);
     if (shine.isNull()) return;
    int sh = shine.value().toInt(&ok); 
    if (!ok) return;

    _material->setShininess( sh );
   }

   node = node.nextSibling();
  } // while
  ////////////////////////////// koniec kolorów materia³u
  
  QDomNode mainTexNode = main.nextSibling(); // teraz tekstura
  if ( mainTexNode.nodeType() != QDomNode::ElementNode ) return;
  QDomElement mainTex = mainTexNode.toElement();
  
  if ( !mainTex.hasAttributes() ) return;                 // brak atrybutów - z³y XML
  if ( !mainTex.hasChildNodes() ) return;                 // brak potomków
  if ( mainTex.tagName() != TEXTURE_MAIN ) return;        // z³a nazwa wêz³a
  
  s = mainTex.attribute( ATTR_TEXTURE_REFLECT, "false" );
  ( s == "true" ) ? bv=true : bv=false;
  _textureParams->setReflectingEnabled( bv );
  
  s = mainTex.attribute( ATTR_TEXTURE_ENABLED, "false" );
  ( s == "true" ) ? bv=true : bv=false;
  setTextureEnabled( bv );
  
  // image Parameters
  node = mainTex.firstChild();
  if ( node.nodeType() != QDomNode::ElementNode ) return; // tylko elementy
  elem = node.toElement();
  
  if ( elem.tagName() != ELEM_IMAGE_PARAMS ) return; // z³a nazwa wêz³a
  // mipmaping  
  s = elem.attribute( ATTR_IMAGE_MIPMAPING, "true" );
  ( s == "true" ) ? mipmaping=true : mipmaping=false;
  // scaleMode
  s = elem.attribute( ATTR_IMAGE_SCALEMODE, "ScaleFree" );
  if ( s == "ScaleMin" ) scaleMode = QImage::ScaleMin;
  else if ( s == "ScaleMax") scaleMode = QImage::ScaleMax;
  else scaleMode = QImage::ScaleFree;
  // fileName
  fileName = elem.attribute( ATTR_IMAGE_FILENAME, "NO IMAGE" ); // UWAGA: fileName mo¿e zawieraæ "NO IMAGE"
  
  // texture filtering
  node = node.nextSibling();
  if ( node.nodeType() != QDomNode::ElementNode ) return; // tylko elementy
  elem = node.toElement();
  
  if ( elem.tagName() != ELEM_FILTERING ) return; // z³a nazwa
  // magFilter
  s = elem.attribute( ATTR_FILTER_MAG, "GL_LINEAR" );
  if ( s == "GL_NEAREST" ) v = GL_NEAREST; else v = GL_LINEAR;
  _textureParams->setMagFilter( v );
  // minFilter
  s = elem.attribute( ATTR_FILTER_MIN, "GL_LINEAR" );
  if ( s == "GL_LINEAR" ) v = GL_LINEAR;
  else if ( s == "GL_NEAREST_MIPMAP_NEAREST" ) v = GL_NEAREST_MIPMAP_NEAREST;
  else if ( s == "GL_NEAREST_MIPMAP_LINEAR" ) v = GL_NEAREST_MIPMAP_LINEAR;
  else if ( s == "GL_LINEAR_MIPMAP_NEAREST" ) v = GL_LINEAR_MIPMAP_NEAREST;
  else if ( s == "GL_LINEAR_MIPMAP_LINEAR" )  v = GL_LINEAR_MIPMAP_LINEAR;
  else v = GL_NEAREST;
  _textureParams->setMinFilter( v );
  // wrap S
  s = elem.attribute( ATTR_FILTER_WRAPS, "GL_REPEAT" );
  if ( s == "GL_REPEAT" ) v = GL_REPEAT; else v = GL_CLAMP;
  _textureParams->setWrapS( v );
  // wrap T
  s = elem.attribute( ATTR_FILTER_WRAPT, "GL_REPEAT" );
  if ( s == "GL_REPEAT" ) v = GL_REPEAT; else v = GL_CLAMP;
  _textureParams->setWrapT( v );
  // envMode
  s = elem.attribute( ATTR_FILTER_ENVMODE, "GL_MODULATE" );
  if ( s == "GL_DECAL" ) v = GL_DECAL;
  else if ( s == "GL_BLEND" ) v = GL_BLEND;
  else v = GL_MODULATE;
  _textureParams->setEnvMode( v );
  
  // blending
  node = node.nextSibling();
  if ( node.nodeType() != QDomNode::ElementNode ) return; // tylko elementy
  elem = node.toElement();
  if ( elem.tagName() != ELEM_BLENDING ) return; // z³a nazwa
  // blending enabled
  s = elem.attribute( ATTR_BLENDING_ENABLED, "false" );
  ( s == "true" ) ? bv=true : bv=false;
  _textureParams->setBlendingEnabled( bv );
  // blending src
  s = elem.attribute( ATTR_BLENDING_SRC, "GL_ONE_MINUS_SRC_ALPHA" );
  if ( s == "GL_ZERO" ) v = GL_ZERO;
  else if ( s == "GL_ONE" ) v = GL_ONE;
  else if ( s == "GL_DST_COLOR" ) v = GL_DST_COLOR;
  else if ( s == "GL_SRC_COLOR" ) v = GL_SRC_COLOR;
  else if ( s == "GL_ONE_MINUS_DST_COLOR" ) v = GL_ONE_MINUS_DST_COLOR;
  else if ( s == "GL_ONE_MINUS_SRC_COLOR" ) v = GL_ONE_MINUS_SRC_COLOR;
  else if ( s == "GL_SRC_ALPHA" ) v = GL_SRC_ALPHA;
  else if ( s == "GL_ONE_MINUS_SRC_ALPHA" ) v = GL_ONE_MINUS_SRC_ALPHA;
  else if ( s == "GL_DST_ALPHA" ) v = GL_DST_ALPHA;
  else if ( s == "GL_ONE_MINUS_DST_ALPHA" ) v = GL_ONE_MINUS_DST_ALPHA;
  else v = GL_SRC_ALPHA_SATURATE;
  _textureParams->setBlendSrcFactor( v );
  // blending dest
  s = elem.attribute( ATTR_BLENDING_DEST, "GL_ONE" );
  if ( s == "GL_ZERO" ) v = GL_ZERO;
  else if ( s == "GL_ONE" ) v = GL_ONE;
  else if ( s == "GL_DST_COLOR" ) v = GL_DST_COLOR;
  else if ( s == "GL_SRC_COLOR" ) v = GL_SRC_COLOR;
  else if ( s == "GL_ONE_MINUS_DST_COLOR" ) v = GL_ONE_MINUS_DST_COLOR;
  else if ( s == "GL_ONE_MINUS_SRC_COLOR" ) v = GL_ONE_MINUS_SRC_COLOR;
  else if ( s == "GL_SRC_ALPHA" ) v = GL_SRC_ALPHA;
  else if ( s == "GL_ONE_MINUS_SRC_ALPHA" ) v = GL_ONE_MINUS_SRC_ALPHA;
  else if ( s == "GL_DST_ALPHA" ) v = GL_DST_ALPHA;
  else if ( s == "GL_ONE_MINUS_DST_ALPHA" ) v = GL_ONE_MINUS_DST_ALPHA;
  else v = GL_SRC_ALPHA_SATURATE;
  _textureParams->setBlendDestFactor( v );
  
  // texture coordinates
  node = node.nextSibling();
  if ( node.nodeType() != QDomNode::ElementNode ) return; // tylko elementy
  elem = node.toElement();
  if ( elem.tagName() != ELEM_TEXTURE_COORDS ) return; // z³a nazwa
  
  GLfloat w,h;
  // minWH
  w = elem.attribute( ATTR_MINW ).toFloat();
  h = elem.attribute( ATTR_MINH ).toFloat();
  _textureParams->setMinWH( w, h );
  // maxWH
  w = elem.attribute( ATTR_MAXW ).toFloat();
  h = elem.attribute( ATTR_MAXH ).toFloat();
  _textureParams->setMaxWH( w, h );
  
  // teraz w koñcu dodajemy teksturê
  if ( fileName == "NO IMAGE" ) _textureParams->setGLTexID( 0 );
  else
  {
    if ( !QFile::exists( fileName ) )
    { // najpierw spróbuj znale¼æ plik w katalogu Options::imagesPath()
      QFileInfo fi( fileName );
      const QString name = fi.fileName();
      
      /*
      QString p( Options::imagesPath() );
      QString sl = p.right( 1 ); 
      if ( sl != "/" ) p+="/"; // czy ostatni jest slash
      
      QString newFileName = p + name; // nowa ¶cie¿ka
      if ( QFile::exists( newFileName ) ) // o, jest taki plik
      {
        QImage img( newFileName );
        TextureManager::addTextureToObject( this, newFileName, scaleMode, mipmaping, &img );
      }
      else _textureParams->setGLTexID( 0 ); // nie ma pliku ani tu ani tu
      */
      
      QString newFileName = Tools::search( name, Options::imagesPath() );
      if ( newFileName != QString::null )
      {
        QImage img( newFileName );
        TextureManager::addTextureToObject( this, newFileName, scaleMode, mipmaping, &img );
      }
      else _textureParams->setGLTexID( 0 );
    }
    else // plik z obrazem istnieje
    {
      QImage img( fileName );
      TextureManager::addTextureToObject( this, fileName, scaleMode, mipmaping, &img );
    }
  }
}




////////////////////////////// metody ustawiania/odczytu rodzaju powierzchni, dla których stosowaæ materia³
void ViElemePolyhExt::setApplyTo(GLenum applyTo)
{
  if ((applyTo != GL_FRONT)  &&  (applyTo != GL_BACK)  &&  (applyTo != GL_FRONT_AND_BACK)) return;

  _applyTo = applyTo;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////






