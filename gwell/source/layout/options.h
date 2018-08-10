///////////////////////////////////////////////////////////////////////////
///
///  class: Options (.h)
///
///  klasa statyczna zawieraj±ca wszystkie konfigurowalne opcje aplikacji
///
///////////////////////////////////////////////////////////////////////////
#ifndef OPTIONS_H
#define OPTIONS_H


#include <qstring.h>
#include <qstringlist.h>
#include <qcolor.h>
#include <qsettings.h>

#include <GL/gl.h>


class Options
{ 
  static QStringList _libPaths;
  static QStringList _mphPaths;
  static QStringList _materialPaths;
  static QString _imagesPath;
  static QString _scenesPath;
  static QString _langPath;
  static QString _layoutLangFile;
  static QString _modelerLangFile;
  
  static int         _decimals;
  
  static QColor      _backgroundColor;
  static QColor      _wireColor;
  static QColor      _wireSelectedColor;
  static QColor      _solidColor;
  static QColor      _solidSelectedColor;
  static QColor      _gridColor;
  static QColor      _grid3DColor;
  static QColor      _lightsColor;
  static QColor      _frameColor;
  static QColor      _infoTextColor;
  
  static GLenum      _correctionHint;
  static GLenum      _shadeModel;
  
  public:
    ///////////////////////////////////////////////////////////    SET
    static bool loadSettings();
    static bool saveSettings();
    
    static void resetColorsToDefaults();
    static void resetPathsToDefaults();
    static void resetToDefaults();
    
    static void clearAllPaths();
    
    static void addLibPath( QString& libPath )      { _libPaths.append( libPath ); }
    static void removeLibPath( QString& libPath );  
    static void clearLibPaths()                     { _libPaths.clear(); }
    
    static void addMphPath( QString& mphPath )      { _mphPaths.append( mphPath ); }
    static void removeMphPath( QString& mphPath );
    static void clearMphPaths()                     { _mphPaths.clear(); }

    static void addMaterialPath( QString& matPath ) { _materialPaths.append( matPath ); }
    static void removeMaterialPath( QString& matPath );
    static void clearMaterialPaths()                { _materialPaths.clear(); }
    
    static void setImagesPath( QString imgPath ) { _imagesPath = imgPath; }
    static void setScenesPath( QString scenesPath ) { _scenesPath = scenesPath; }
    static void setLangPath( QString langPath ) { _langPath = langPath; }
    static void setLayoutLangFile( QString fileName ) { _layoutLangFile = fileName; }
    static void setModelerLangFile( QString fileName ) { _modelerLangFile = fileName; }
    
    typedef enum { BackgroundColor=0, WireColor=1, WireSelectedColor, SolidColor, SolidSelectedColor,
                 GridColor, Grid3DColor, LightsColor, FrameColor,  InfoTextColor } Colors;
    static void setColor( Colors whichColor, const QColor& color );
    
    static void setBackgroundColor( const QColor& color )    { setColor( BackgroundColor, color ); }
    static void setWireColor( const QColor& color )          { setColor( WireColor, color ); }
    static void setWireSelectedColor( const QColor& color )  { setColor( WireSelectedColor, color ); }
    static void setSolidColor( const QColor& color )         { setColor( SolidColor, color ); }
    static void setSolidSelectedColor( const QColor& color ) { setColor( SolidSelectedColor, color ); }
    static void setGridColor( const QColor& color )          { setColor( GridColor, color ); }
    static void setGrid3DColor( const QColor& color )        { setColor( Grid3DColor, color ); }
    static void setLightsColor( const QColor& color )        { setColor( LightsColor, color ); }
    static void setFrameColor( const QColor& color )         { setColor( FrameColor, color ); }
    static void setInfoTextColor( const QColor& color )      { setColor( InfoTextColor, color ); }
    
    static void setDecimals( int decimals ) { if (decimals>0) _decimals = decimals; }
    
    static void setCorrectionHint( GLenum corrHint )         { _correctionHint = corrHint; }
    static void setIntCorrectionHint( int index );
    static void setShadeModel( GLenum shadeModel )           { _shadeModel = shadeModel; }
    static void setIntShadeModel( int index );
    
    ///////////////////////////////////////////////////////////    GET
    static const QStringList* libPaths()      { return &_libPaths; }
    static QStringList* mphPaths()      { return &_mphPaths; }
    static const QStringList* materialPaths() { return &_materialPaths; }
    static const QString& imagesPath()        { return _imagesPath; }
    static const QString& scenesPath()        { return _scenesPath; }
    static const QString& langPath()          { return _langPath; }
    static const QString& layoutLangFile()    { return _layoutLangFile; }
    static const QString& modelerLangFile()   { return _modelerLangFile; }
    
    static const int decimals()               { return _decimals; }
    
    static const GLenum correctionHint()      { return _correctionHint; }
    static const int intCorrectionHint();
    static const GLenum shadeModel()          { return _shadeModel; }
    static const int intShadeModel();
    
    static const QColor& backgroundColor()     { return _backgroundColor; }
    static const QColor& gridColor()           { return _gridColor; }
    static const QColor& grid3DColor()         { return _grid3DColor; }
    static const QColor& wireColor()           { return _wireColor; }
    static const QColor& wireSelectedColor()   { return _wireSelectedColor; }
    static const QColor& solidColor()          { return _solidColor; }
    static const QColor& solidSelectedColor()  { return _solidSelectedColor; }
    static const QColor& lightsColor()         { return _lightsColor; }
    static const QColor& frameColor()          { return _frameColor; }
    static const QColor& infoTextColor()       { return _infoTextColor; }
};




#endif
