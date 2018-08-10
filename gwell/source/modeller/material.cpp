////////////////////////////////////////////////////////////////////////////////////////////////
///
///  class: Material (.h)
///
///  klasa opisuj±ca materia³, warto¶ci kolorów przechowywane s± w obiektach klasy QColor i
///  wektorach przeznaczonych do u¿ycia w OpenGL
///  przeci±¿one s± operatory przypisania i porównania,
///
///  !! nazwa materia³u nie jest porównywana !!
///  !! przypisanie nie kopiuje nazwy materia³u !!
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "material.h"


/*!
Licznik obiektów klasy MaterialQT utworzonych przez konstruktor domy¶lny,
u¿ywany do nadawania kolejnych domy¶lnych nazw pustym materia³om.
*/
int Material::emptyMaterialsCount = 0;



/*!
Konstruktor domy¶lny.
*/
Material::Material()                                // warto¶ci domy¶lne
{
  // zwiêkszamy licznik pustych materia³ów i stosujemy go w nazwie domy¶lnego materia³u
  _materialName     = QString("Default material (%1)").arg(++emptyMaterialsCount);
  
  const GLfloat emptyMat[4] = { 0.0, 0.0, 0.0, 1.0 };
  
  setAmbientColor  ( emptyMat );
  setDiffuseColor  ( emptyMat );
  setSpecularColor ( emptyMat );
  setEmissionColor ( emptyMat );
  setShininess  ( 0 );
} 



/*!
Konstruktor parametryczny QT.
*/
Material::Material( 
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
                  )
{
  _materialName = materialName;

  setAmbientColor  ( ambientColor,  ambientAlpha  );
  setDiffuseColor  ( diffuseColor,  diffuseAlpha  );
  setSpecularColor ( specularColor, specularAlpha );
  setEmissionColor ( emissionColor, emissionAlpha );
  setShininess ( shininess );
}



/*!
Konstruktor parametryczny OpenGL.
*/
Material::Material(
                    const char*     materialName,
                    const GLfloat*  ambientColor4fv,
                    const GLfloat*  diffuseColor4fv,
                    const GLfloat*  specularColor4fv,
                    const GLfloat*  emissionColor4fv,
                          GLint     shininess
                  )
{
  _materialName     = materialName;
  
  setAmbientColor ( ambientColor4fv  );
  setDiffuseColor ( diffuseColor4fv  );
  setSpecularColor( specularColor4fv );
  setEmissionColor( emissionColor4fv );
  setShininess ( shininess );
}
  
  

// destruktor
Material::~Material() {}


/*!
Operator przypisania.
NAZWA MATERIA£U NIE JEST KOPIOWANA.
*/
Material& Material::operator=(const Material& material)
{
  setAmbientColor ( material.ambientColor4fv()  );
  setDiffuseColor ( material.diffuseColor4fv()  );
  setSpecularColor( material.specularColor4fv() );
  setEmissionColor( material.emissionColor4fv() );
  setShininess    ( material.shininess() );
  
  return *this;
} 

/*!
Operator porównania.
NAZWA MATERIA£U NIE JEST PORÓWNYWANA.
*/
bool Material::operator==(const Material& material)
{
  if (_qAmbientColor  !=  material.ambientColorQT())  return false;
  if (_iAmbientAlpha  !=  material.ambientAlpha())    return false;
  if (_qDiffuseColor  !=  material.diffuseColorQT())  return false;
  if (_iDiffuseAlpha  !=  material.diffuseAlpha())    return false;
  if (_qSpecularColor !=  material.specularColorQT()) return false;
  if (_iSpecularAlpha !=  material.specularAlpha())   return false;
  if (_qEmissionColor !=  material.emissionColorQT()) return false;
  if (_iEmissionAlpha !=  material.emissionAlpha())   return false;
  if (_shininess      !=  material.shininess())       return false;

  return true;
}


/*!
Metoda ustawia nazwê dla materia³u.
*/
///////////////////////////////////////////////////////////////////  ustaw nazwê dla materia³u
void Material::setMaterialName( const QString materialName )
{
  _materialName = materialName;
}

/*!
Metoda ustawia nazwê dla materia³u.
*/
void Material::setMaterialName( const char* materialName )
{
  _materialName = materialName;
}
///////////////////////////////////////////////////////////////////  ustaw nazwê dla materia³u



/////////////////////////////////////////////////////////////////// ustawienie kolorów QT
/*!
Metoda uniwersalna do ustawienia koloru QT:
\param INcolor     - kolor QT, na który chcemy ustawiæ,
\param INalpha     - przezroczysto¶æ, na któr± chcemy ustawiæ,
\param OUTcolor    - wyj¶ciowy kolor QT,
\param OUTalpha    - wyj¶ciowa alpha,
\param OUTcolor4fv - wyj¶ciowy kolor OpenGL : GLfloat[4].
*/
void Material::setColor( const QColor& INcolor, int INalpha, QColor* OUTcolor, int* OUTalpha, GLfloat* OUTcolor4fv)
{
  if (!INcolor.isValid()) return;

  if (INalpha >= 0 && INalpha <= 255) // je¿eli podano prawid³owo przezroczysto¶æ
  {
    *(OUTcolor4fv + 3)  = (GLfloat) INalpha/255;  
    *OUTalpha           = (int) INalpha;
  }
  
  *OUTcolor = INcolor; // zachowujemy kolor w postaci QT
    
  // zachowujemy kolor w postaci OpenGL
  *(OUTcolor4fv + 0) = (GLfloat) INcolor.red()/255;
  *(OUTcolor4fv + 1) = (GLfloat) INcolor.green()/255;
  *(OUTcolor4fv + 2) = (GLfloat) INcolor.blue()/255;
}

/*!
Ustawienie koloru ambient (QT).
*/
void Material::setAmbientColor( const QColor& color, int alpha )
{
  setColor( color, alpha, &_qAmbientColor, &_iAmbientAlpha, _ambientColor);
}

/*!
Ustawienie koloru diffuse (QT).
*/
void Material::setDiffuseColor( const QColor& color, int alpha )
{
  setColor( color, alpha, &_qDiffuseColor, &_iDiffuseAlpha, _diffuseColor);
}

/*!
Ustawienie koloru specular (QT).
*/
void Material::setSpecularColor( const QColor& color, int alpha )
{
  setColor( color, alpha, &_qSpecularColor, &_iSpecularAlpha, _specularColor);
}

/*!
Ustawienie koloru emission (QT).
*/
void Material::setEmissionColor( const QColor& color, int alpha )
{
  setColor( color, alpha, &_qEmissionColor, &_iEmissionAlpha, _emissionColor);
}

/*!
Ustawienie po³yskliwo¶ci (QT i OpenGL).
*/
void Material::setShininess( GLint shininess )
{
  _shininess  = shininess;
  _shininessf = (GLfloat) shininess;
}
/////////////////////////////////////////////////////////////////// ustawienie kolorów QT




/////////////////////////////////////////////////////////////////// ustawienie kolorów OpenGL
/*!
Metoda uniwersalna do ustawiania koloru OpenGL:
\param INcolor4fv  - kolor OpenGL, na który chcemy ustawiæ,
\param OUTcolor4fv - kolor wyj¶ciowy OpenGL,
\param OUTcolor    - kolor wyj¶ciowy QT,
\param OUTalpha    - alpha wyj¶ciowa QT.
*/
void Material::setColor( const GLfloat* INcolor4fv, GLfloat* OUTcolor4fv, QColor* OUTcolor, int* OUTalpha )
{
  for (int i=0; i<4; i++)
    *(OUTcolor4fv + i) = *(INcolor4fv + i);  // przepisanie warto¶ci koloru
  
  
  OUTcolor->setRgb((int) ((*(INcolor4fv+0))*255.0),
                   (int) ((*(INcolor4fv+1))*255.0),
                   (int) ((*(INcolor4fv+2))*255.0));
  
  *OUTalpha = (int) ((*(INcolor4fv+3))*255.0);
}

/*!
Ustawienie koloru ambient (OpenGL).
*/
void Material::setAmbientColor( const GLfloat* color )
{
  setColor( color, _ambientColor, &_qAmbientColor, &_iAmbientAlpha );
}

/*!
Ustawienie koloru diffuse (OpenGL).
*/
void Material::setDiffuseColor( const GLfloat* color )
{
  setColor( color, _diffuseColor, &_qDiffuseColor, &_iDiffuseAlpha );
}

/*!
Ustawienie koloru specular (OpenGL).
*/
void Material::setSpecularColor( const GLfloat* color )
{
  setColor( color, _specularColor, &_qSpecularColor, &_iSpecularAlpha );
}

/*!
Ustawienie koloru emission (OpenGL).
*/
void Material::setEmissionColor( const GLfloat* color )
{
  setColor( color, _emissionColor, &_qEmissionColor, &_iEmissionAlpha );
}
/////////////////////////////////////////////////////////////////// ustawienie kolorów OpenGL

