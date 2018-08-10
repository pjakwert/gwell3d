///////////////////////////////////////////////////////////////////////////
///
///  class: Options (.cpp)
///
///  klasa statyczna zawieraj±ca wszystkie konfigurowalne opcje aplikacji
///
///////////////////////////////////////////////////////////////////////////

#include "options.h"



// kolory pocz±tkowe
QColor Options::_backgroundColor    = QColor( 0, 0, 0 );
QColor Options::_wireColor          = QColor( 178, 153, 128 );
QColor Options::_wireSelectedColor  = QColor( 255, 204, 0 );
QColor Options::_solidColor         = QColor( 230, 76, 51 );
QColor Options::_solidSelectedColor = QColor( 255, 204, 0 );
QColor Options::_gridColor          = QColor( 178, 178, 178 );
QColor Options::_grid3DColor        = QColor( 150, 150, 150 );
QColor Options::_lightsColor        = QColor( 255, 255, 0 );
QColor Options::_frameColor         = QColor( 255, 255, 255 );
QColor Options::_infoTextColor      = QColor( 0, 178, 76 );

int Options::_decimals = 3;

QStringList Options::_libPaths        = QStringList( "libs" );
QStringList Options::_mphPaths        = QStringList( "mph" );
QStringList Options::_materialPaths   = QStringList( "materials" );
QString Options::_imagesPath = QString( "images" );
QString Options::_scenesPath = QString( "scenes" );
QString Options::_langPath = QString( "languages" );
QString Options::_layoutLangFile = QString( "english" );
QString Options::_modelerLangFile = QString( "english" );

GLenum Options::_correctionHint = GL_NICEST;
GLenum Options::_shadeModel = GL_SMOOTH;


// ustawienie koloru dla odpowiedniego elementu
void Options::setColor( Colors whichColor, const QColor& color )
{
  if ( !color.isValid() ) return;
  
  switch ( whichColor )
  {
    case BackgroundColor     : _backgroundColor    = color; break;
    case WireColor           : _wireColor          = color; break;
    case WireSelectedColor   : _wireSelectedColor  = color; break;
    case SolidColor          : _solidColor         = color; break;
    case SolidSelectedColor  : _solidSelectedColor = color; break;
    case GridColor           : _gridColor          = color; break;
    case Grid3DColor         : _grid3DColor        = color; break;
    case LightsColor         : _lightsColor        = color; break;
    case FrameColor          : _frameColor         = color; break;
    case InfoTextColor       : _infoTextColor      = color; break;
    default : break;
  }
}


// ustawia GL_CORRECTION_HINT wg indeksu combo (0,1,2)
void Options::setIntCorrectionHint( int index )
{
  switch ( index )
  {
    case 0 : setCorrectionHint( GL_FASTEST ); break;
    case 1 : setCorrectionHint( GL_NICEST );  break;
    case 2 : setCorrectionHint( GL_DONT_CARE ); break;
    default : break;
  }
}


// ustawia GL_RENDER_MODE wg indeksu combo (0,1)
void Options::setIntShadeModel( int index )
{
  switch ( index )
  {
    case 0 : setShadeModel( GL_FLAT );  break;
    case 1 : setShadeModel( GL_SMOOTH); break;
    default : break;
  }
}


// zwraca indeks dla combo
// nigdy nie powinien zwróciæ -1 = B£¡D!
const int Options::intCorrectionHint()
{
  switch ( _correctionHint )
  {
    case GL_FASTEST   : return 0;
    case GL_NICEST    : return 1;
    case GL_DONT_CARE : return 2;
    default : return -1;
  }
}
    

// zwraca indeks dla combo
// nigdy nie powinien zwróciæ -1 = B£¡D!
const int Options::intShadeModel()
{
  switch ( _shadeModel )
  {
    case GL_FLAT   : return 0;
    case GL_SMOOTH : return 1;
    default : return -1;
  }
}


// przywraca domy¶lne kolory
void Options::resetColorsToDefaults()
{
  _backgroundColor.setRgb   ( 0, 0, 0 );
  _wireColor.setRgb         ( 178, 153, 128 );
  _wireSelectedColor.setRgb ( 255, 204, 0 );
  _solidColor.setRgb        ( 230, 76, 51 );
  _solidSelectedColor.setRgb( 255, 204, 0 );
  _gridColor.setRgb         ( 178, 178, 178 );
  _grid3DColor.setRgb       ( 150, 150, 150 );
  _lightsColor.setRgb       ( 255, 255, 0 );
  _frameColor.setRgb        ( 255, 255, 255 );
  _infoTextColor.setRgb     ( 0, 178, 76 );
}



// czy¶ci wszystkie ¶cie¿ki
void Options::clearAllPaths()
{
  clearLibPaths();
  clearMphPaths();
  clearMaterialPaths();
}


// przywraca domy¶lne ¶cie¿ki
void Options::resetPathsToDefaults()
{
  clearAllPaths();
  
  _libPaths.append("libs");
  _mphPaths.append("mph");
  _materialPaths.append("materials");
  setImagesPath( QString("images") );
  setScenesPath( QString("scenes") );
  setLangPath( QString("languages") );
  setModelerLangFile( QString("english") );
  setLayoutLangFile( QString("english") );
}


// wszystko ustawia na warto¶ci domy¶lne
void Options::resetToDefaults()
{
  resetColorsToDefaults();
  resetPathsToDefaults();
  _decimals = 3;
  _correctionHint = GL_NICEST;
  _shadeModel = GL_SMOOTH;
}




// ³aduje ustawienia z pliku
// zwraca TRUE po pomy¶lnym odczytaniu ustawieñ
bool Options::loadSettings()
{
  clearAllPaths(); // wyczy¶æ wszystkie ¶cie¿ki
    
  QSettings settings;
  settings.setPath( "PrzemekJakwert.pl", "Gwell" ); // domena korporacji i produkt :)
  
  settings.beginGroup( "/Gwell" );
  
  settings.beginGroup( "/Paths" ); // grupa ¶cie¿ek
    QString libs = settings.readEntry( "/libraries", "libs" ); // drugi argument to warto¶æ domy¶lna
    QString mph  = settings.readEntry( "/multipolyhedrons", "mph" );
    QString mat  = settings.readEntry( "/materials", "materials" );
    QString img  = settings.readEntry( "/images", "images" );
    QString scn  = settings.readEntry( "/scenes", "scenes" );
    QString lang = settings.readEntry( "/languages", "languages" );
  settings.endGroup(); // Paths
  
  _libPaths.append( libs );
  _mphPaths.append( mph );
  _materialPaths.append( mat );
  setImagesPath( img );
  setScenesPath( scn );
  setLangPath( lang );
  
  int r,g,b;
  settings.beginGroup( "/Colors" ); // grupa kolorów
    settings.beginGroup( "/background" );
      r = settings.readNumEntry( "/r", 0 );
      g = settings.readNumEntry( "/g", 0 );
      b = settings.readNumEntry( "/b", 0 );
      _backgroundColor.setRgb( r,g,b );
    settings.endGroup();
    settings.beginGroup( "/wire" );
      r = settings.readNumEntry( "/r", 178 );
      g = settings.readNumEntry( "/g", 153 );
      b = settings.readNumEntry( "/b", 128 );
      _wireColor.setRgb( r,g,b );
    settings.endGroup();
    settings.beginGroup( "/wireSelected" );
      r = settings.readNumEntry( "/r", 255 );
      g = settings.readNumEntry( "/g", 204 );
      b = settings.readNumEntry( "/b", 0 );
      _wireSelectedColor.setRgb( r,g,b );
    settings.endGroup();
    settings.beginGroup( "/solid" );
      r = settings.readNumEntry( "/r", 230 );
      g = settings.readNumEntry( "/g", 76 );
      b = settings.readNumEntry( "/b", 51 );
      _solidColor.setRgb( r,g,b );
    settings.endGroup();
    settings.beginGroup( "/solidSelected" );
      r = settings.readNumEntry( "/r", 255 );
      g = settings.readNumEntry( "/g", 204 );
      b = settings.readNumEntry( "/b", 0 );
      _solidSelectedColor.setRgb( r,g,b );
    settings.endGroup();
    settings.beginGroup( "/grid" );
      r = settings.readNumEntry( "/r", 178 );
      g = settings.readNumEntry( "/g", 178 );
      b = settings.readNumEntry( "/b", 178 );
      _gridColor.setRgb( r,g,b );
    settings.endGroup();
    settings.beginGroup( "/grid3D" );
      r = settings.readNumEntry( "/r", 150 );
      g = settings.readNumEntry( "/g", 150 );
      b = settings.readNumEntry( "/b", 150 );
      _grid3DColor.setRgb( r,g,b );
    settings.endGroup();
    settings.beginGroup( "/frame" );
      r = settings.readNumEntry( "/r", 255 );
      g = settings.readNumEntry( "/g", 255 );
      b = settings.readNumEntry( "/b", 255 );
      _frameColor.setRgb( r,g,b );
    settings.endGroup();
    settings.beginGroup( "/lights" );
      r = settings.readNumEntry( "/r", 255 );
      g = settings.readNumEntry( "/g", 255 );
      b = settings.readNumEntry( "/b", 0 );
      _lightsColor.setRgb( r,g,b );
    settings.endGroup();
    settings.beginGroup( "/infoText" );
      r = settings.readNumEntry( "/r", 0 );
      g = settings.readNumEntry( "/g", 178 );
      b = settings.readNumEntry( "/b", 76 );
      _infoTextColor.setRgb( r,g,b );
    settings.endGroup();
  settings.endGroup(); // Colors
  
  _decimals = settings.readNumEntry( "/Decimals", 3 ); // czê¶ci dziesiêtne
  _modelerLangFile = settings.readEntry( "/Modeler language", "english" ); // plik z jêzykiem dla Modeler-a
  _layoutLangFile = settings.readEntry( "/Layout language", "english" ); // plik z jêzykiem dla Layout-a
  
  settings.beginGroup( "/Render Options" ); // opcje renderingu OpenGL
    QString shadeModel = settings.readEntry( "/shadeModel", "GL_SMOOTH" );
    QString corrHint   = settings.readEntry( "/correctionHint", "GL_NICEST" );
  
    if ( shadeModel == "GL_FLAT" ) _shadeModel = GL_FLAT; else _shadeModel = GL_SMOOTH;
    if ( corrHint == "GL_FASTEST" ) _correctionHint = GL_FASTEST;
    else if ( corrHint == "GL_DONT_CARE" ) _correctionHint = GL_DONT_CARE;
    else corrHint = "GL_NICEST";
  settings.endGroup();
  
  settings.endGroup();
  
  return true;
}
    
  
// zapisuje ustawienia do pliku
// zwraca TRUE po pomy¶lnym zapisaniu ustawieñ
bool Options::saveSettings()
{
  QSettings settings;
  settings.setPath( "PrzemekJakwert.pl", "Gwell" ); // domena korporacji i produkt :)
  
  settings.writeEntry( "/Gwell/Paths/libraries", _libPaths.first() );
  settings.writeEntry( "/Gwell/Paths/multipolyhedrons", _mphPaths.first() );
  settings.writeEntry( "/Gwell/Paths/materials", _materialPaths.first() );
  settings.writeEntry( "/Gwell/Paths/images", _imagesPath );
  settings.writeEntry( "/Gwell/Paths/scenes", _scenesPath );
  settings.writeEntry( "/Gwell/Paths/languages", _langPath );
  
  settings.writeEntry( "/Gwell/Colors/background/r", _backgroundColor.red() );
  settings.writeEntry( "/Gwell/Colors/background/g", _backgroundColor.green() );
  settings.writeEntry( "/Gwell/Colors/background/b", _backgroundColor.blue() );
   settings.writeEntry( "/Gwell/Colors/wire/r", _wireColor.red() );
   settings.writeEntry( "/Gwell/Colors/wire/g", _wireColor.green() );
   settings.writeEntry( "/Gwell/Colors/wire/b", _wireColor.blue() );
  settings.writeEntry( "/Gwell/Colors/wireSelected/r", _wireSelectedColor.red() );
  settings.writeEntry( "/Gwell/Colors/wireSelected/g", _wireSelectedColor.green() );
  settings.writeEntry( "/Gwell/Colors/wireSelected/b", _wireSelectedColor.blue() );
   settings.writeEntry( "/Gwell/Colors/solid/r", _solidColor.red() );
   settings.writeEntry( "/Gwell/Colors/solid/g", _solidColor.green() );
   settings.writeEntry( "/Gwell/Colors/solid/b", _solidColor.blue() );
  settings.writeEntry( "/Gwell/Colors/solidSelected/r", _solidSelectedColor.red() );
  settings.writeEntry( "/Gwell/Colors/solidSelected/g", _solidSelectedColor.green() );
  settings.writeEntry( "/Gwell/Colors/solidSelected/b", _solidSelectedColor.blue() );
   settings.writeEntry( "/Gwell/Colors/grid/r", _gridColor.red() );
   settings.writeEntry( "/Gwell/Colors/grid/g", _gridColor.green() );
   settings.writeEntry( "/Gwell/Colors/grid/b", _gridColor.blue() );
  settings.writeEntry( "/Gwell/Colors/grid3D/r", _grid3DColor.red() );
  settings.writeEntry( "/Gwell/Colors/grid3D/g", _grid3DColor.green() );
  settings.writeEntry( "/Gwell/Colors/grid3D/b", _grid3DColor.blue() );
   settings.writeEntry( "/Gwell/Colors/frame/r", _frameColor.red() );
   settings.writeEntry( "/Gwell/Colors/frame/g", _frameColor.green() );
   settings.writeEntry( "/Gwell/Colors/frame/b", _frameColor.blue() );
  settings.writeEntry( "/Gwell/Colors/lights/r", _lightsColor.red() );
  settings.writeEntry( "/Gwell/Colors/lights/g", _lightsColor.green() );
  settings.writeEntry( "/Gwell/Colors/lights/b", _lightsColor.blue() );
   settings.writeEntry( "/Gwell/Colors/infoText/r", _infoTextColor.red() );
   settings.writeEntry( "/Gwell/Colors/infoText/g", _infoTextColor.green() );
   settings.writeEntry( "/Gwell/Colors/infoText/b", _infoTextColor.blue() );

  settings.writeEntry( "/Gwell/Decimals", _decimals ); // czê¶ci dziesiêtne
  settings.writeEntry( "/Gwell/Modeler language", _modelerLangFile ); // plik z jêzykiem dla Modeler-a
  settings.writeEntry( "/Gwell/Layout language", _layoutLangFile ); // plik z jêzykiem dla Layout-a
  
  QString s = "GL_SMOOTH";                         // shadeModel
  if ( _shadeModel == GL_FLAT ) s = "GL_FLAT";
  settings.writeEntry( "/Gwell/Render Options/shadeModel", s );
  
  s = "GL_NICEST";                                   // GL_CORRECTION_HINT
  if ( _correctionHint == GL_FASTEST ) s = "GL_FASTEST";
  else if ( _correctionHint == GL_DONT_CARE ) s = "GL_DONT_CARE";
  settings.writeEntry( "/Gwell/Render Options/correctionHint", s );
  
  return true;
}

