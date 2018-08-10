////////////////////////////////////////////////////////////////////////////////////////////////
///
///  class: Material (.h)
///
///  klasa opisuj�ca materia�, warto�ci kolor�w przechowywane s� w obiektach klasy QColor i
///  wektorach przeznaczonych do u�ycia w OpenGL
///  przeci��one s� operatory przypisania i por�wnania,
///
///  !! nazwa materia�u nie jest por�wnywana !!
///  !! przypisanie tworzy dok�adn� kopi� - ��cznie z nazw� !!
///
////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef MATERIAL_H
#define MATERIAL_H


#include <qcolor.h>
#include <qstring.h>
#include <QGLViewer/qglviewer.h>

/*!
Klasa Material opisuje wszystkie w�a�ciwo�ci materia�u obiektu.
*/
class Material
{
  public:
    // konstruktor domy�lny - inicjuje materia� warto�ciami zerowymi
    Material();
    
    // konstruktor parametryczny QT
    Material(
              QString   materialName,                 
              QColor    ambientColor,
              int       ambientAlpha,
              QColor    diffuseColor,
              int       diffuseAlpha,
              QColor    specularColor,
              int       specularAlpha,
              QColor    emissionColor,
              int       emissionAlpha,
              GLint     shininess
            );
    
    // konstruktor parametryczny OpenGL   
    Material(
              const char*     materialName,
              const GLfloat*  ambientColor4fv,
              const GLfloat*  diffuseColor4fv,
              const GLfloat*  specularColor4fv,
              const GLfloat*  emissionColor4fv,
                    GLint     shininess
            );
                
    // destruktor
    ~Material();
    
    
    // metody zwracaj�ce nazw� i warto�ci kolor�w
    QString materialName() const { return _materialName; }
    
    const GLfloat* ambientColor4fv()  const { return &_ambientColor[0];  }
    const GLfloat* diffuseColor4fv()  const { return &_diffuseColor[0];  }
    const GLfloat* specularColor4fv() const { return &_specularColor[0]; }
    const GLfloat* emissionColor4fv() const { return _emissionColor; }
  
    const QColor& ambientColorQT()  const { return _qAmbientColor;  }
    const QColor& diffuseColorQT()  const { return _qDiffuseColor;  }
    const QColor& specularColorQT() const { return _qSpecularColor; }
    const QColor& emissionColorQT() const { return _qEmissionColor; }
    
    int   ambientAlpha()  const { return _iAmbientAlpha;  }
    int   diffuseAlpha()  const { return _iDiffuseAlpha;  }
    int   specularAlpha() const { return _iSpecularAlpha; }
    int   emissionAlpha() const { return _iEmissionAlpha; }
    
    GLint shininess() const { return _shininess; }
    // metoda zwraca odpowiedni wektor do wykorzystania w OpenGL
    const GLfloat* shininess1fv() const { return &_shininessf; }
    
    // metody ustawiaj�ce nazw� materia�u i kolory                                        
                                        
    // QT
    void setMaterialName    ( const QString materialName );
    void setAmbientColor    ( const QColor& color, int alpha=-1 );
    void setDiffuseColor    ( const QColor& color, int alpha=-1 );
    void setSpecularColor   ( const QColor& color, int alpha=-1 );
    void setEmissionColor   ( const QColor& color, int alpha=-1 );
      
    // OpenGL
    void setMaterialName    ( const char* materialName );
    void setAmbientColor    ( const GLfloat* color );
    void setDiffuseColor    ( const GLfloat* color );
    void setSpecularColor   ( const GLfloat* color );
    void setEmissionColor   ( const GLfloat* color );
    
    // wsp�lne
    void setShininess       ( GLint shininess );                                    
                                        
                                              
    // operatory por�wnania i przypisania
    bool operator==(const Material& material);
    Material& operator=(const Material& material);
    
  private:
    // licznik materia��w utworzonych konstruktorem domy�lnym
    static int emptyMaterialsCount; 
    // metody pomocnicze do ustawiania koloru
    void setColor( const QColor& INcolor, int INalpha, QColor* OUTcolor, int* OUTalpha, GLfloat* OUTcolor4fv);
    void setColor( const GLfloat* INcolor4fv, GLfloat* OUTcolor4fv, QColor* OUTcolor, int* OUTalpha );
    
    QString _materialName;
    GLint   _shininess;
    GLfloat _shininessf;  // przechowywane ze wzgl�du na przyspieszenie operacji dla OpenGL
    // QT
    QColor  _qAmbientColor;
     int    _iAmbientAlpha;
    QColor  _qDiffuseColor;
     int    _iDiffuseAlpha;
    QColor  _qSpecularColor;
     int    _iSpecularAlpha;
    QColor  _qEmissionColor;
     int    _iEmissionAlpha;
    // OpenGL
    GLfloat _ambientColor[4];
    GLfloat _diffuseColor[4];
    GLfloat _specularColor[4];
    GLfloat _emissionColor[4];
};


#endif
