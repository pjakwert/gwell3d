////////////////////////////////////////////////////////////////////////////////////////////////
///
///  class: Texture (.h)
///
///  klasa opisuje tekstur�
///  przeci��one s� operatory przypisania i por�wnania
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


/*!
Klasa opisuje pojedyncz� tekstur� (bez parametr�w).
*/
class Texture
{
  public:
    Texture(
              QString           fileName = QString::null,   // nazwa (�cie�ka do) pliku graficznego
              QImage::ScaleMode scaleMode = QImage::ScaleFree, // typ skalowania w przypadku wymiar�w != 2^n
              bool              mipmapingEnabled = true,
              GLuint            GLTextureID = 0,
              int               howManyUsers = 0,    // licznik obiekt�w, kt�re u�ywaj� tej tekstury
              QPixmap*          preview = 0L         // mini podgl�d obrazu
           );

    ~Texture() { /* QT */ };
    
    int  setFileName( const QString& fileName );
    /*!
    Metoda ustawia typ skalowania.
    */
    void setScaleMode( const QImage::ScaleMode mode ) { _scaleMode = mode; }
    /*!
    Metoda w��cza/wy��cza stosowanie mipmap.
    */
    void setMipmapEnabled( bool yes )                 { _mipmapEnabled = yes; }
    /*!
    Metoda ustawia obrazek podgl�du dla tekstury.
    */
    void setPreview( QPixmap* pixmap )                { _preview = pixmap; }
    /*!
    Metoda zwi�ksza o 1 liczb� obiekt�w u�ywaj�cych tej tekstury.
    */
    int  incHowManyUsers() { _howManyUsers++; return _howManyUsers; }
    /*!
    Metoda zmniejsza o 1 liczb� obiekt�w u�ywaj�cych tej tekstury.
    */
    int  decHowManyUsers() { _howManyUsers--; return _howManyUsers; }
    
    /*!
    Metoda zwraca �cie�k� do pliku z tekstur�.
    */
    const   QString& fileName()   const { return _fileName;  }
    /*!
    Metoda zwraca typ skalowania.
    */
    QImage::ScaleMode scaleMode() const { return _scaleMode; }
    /*!
    Czy mipmapy s� stosowane?
    */
    bool    mipmapingEnabled()    const { return _mipmapEnabled; }
    /*!
    Metoda zwraca ID tekstury (adres fizyczny).
    */
    GLuint  GLTextureID()         const { return _GLTextureID; }
    /*!
    Metoda zwraca podgl�d tekstury.
    */
    QPixmap* preview()            const { return _preview; }
    /*!
    Metoda zwi�ksza liczb� element�w u�ywaj�cych tekstury.
    */
    int     howManyUsers()        const { return _howManyUsers; }
    
    /*!
    Czy tekstura jest prawid�owa? (sprawdza czy plik jest poprawny).
    */
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
    
    /*!
    Metoda ustawia adres fizyczny tekstury.
    */
    void setGLTextureID( GLuint GLTextureID ) { _GLTextureID = GLTextureID; }
    /*!
    Metoda ustawia liczb� obiekt�w u�ywaj�cych tej tekstury.
    */
    void setHowManyUsers( int howMany ) { _howManyUsers = howMany; }
};


#endif
