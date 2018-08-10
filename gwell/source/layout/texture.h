////////////////////////////////////////////////////////////////////////////////////////////////
///
///  class: Texture (.h)
///
///  klasa opisuje teksturê
///  przeci±¿one s± operatory przypisania i porównania
///
////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef TEXTURE_H
#define TEXTURE_H

#include <qstring.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qfile.h>
#include <QGLViewer/qglviewer.h>
#include <qptrlist.h>

class Texture
{
  public:
    Texture(
              QString           fileName = QString::null,   // nazwa (¶cie¿ka do) pliku graficznego
              QImage::ScaleMode scaleMode = QImage::ScaleFree, // typ skalowania w przypadku wymiarów != 2^n
              bool              mipmapingEnabled = true,
              GLuint            GLTextureID = 0,
              int               howManyUsers = 0,    // licznik obiektów, które u¿ywaj± tej tekstury
              QPixmap*          preview = 0L         // mini podgl±d obrazu
           );

    ~Texture() { /* QT */ };
    
    int  setFileName( const QString& fileName );
    void setScaleMode( const QImage::ScaleMode mode ) { _scaleMode = mode; }
    void setMipmapEnabled( bool yes )                 { _mipmapEnabled = yes; }
    void setPreview( QPixmap* pixmap )                { _preview = pixmap; }
    int  incHowManyUsers() { _howManyUsers++; return _howManyUsers; }
    int  decHowManyUsers() { _howManyUsers--; return _howManyUsers; }
    
    const   QString& fileName()   const { return _fileName;  }
    QImage::ScaleMode scaleMode() const { return _scaleMode; }
    bool    mipmapingEnabled()    const { return _mipmapEnabled; }
    GLuint  GLTextureID()         const { return _GLTextureID; }
    QPixmap* preview()            const { return _preview; }
    int     howManyUsers()        const { return _howManyUsers; }
    
    bool    isValid()             const { return _isValid; } // flaga ustawiana tylko przez setFileName()
    
    Texture& operator=(Texture&);
    bool operator==(Texture&);
    
  private:
    QString   _fileName;
    QImage::ScaleMode _scaleMode;
    bool      _mipmapEnabled;
    int       _howManyUsers;
    QPixmap*  _preview;
    
    GLuint    _GLTextureID;
    
    bool      _isValid;
    
    void setGLTextureID( GLuint GLTextureID ) { _GLTextureID = GLTextureID; }
    void setHowManyUsers( int howMany ) { _howManyUsers = howMany; }
};


#endif
