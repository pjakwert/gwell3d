////////////////////////////////////////////////////////////////////////////////////////////////
///
///  class: Material (.h)
///
///  klasa opisuj�ca materia�, warto�ci kolor�w przechowywane s� w obiektach klasy QColor i
///	 wektorach przeznaczonych do u�ycia w OpenGL
///  przeci��one s� operatory przypisania i por�wnania,
///
///  !! nazwa materia�u nie jest por�wnywana !!
///  !! przypisanie nie kopiuje nazwy materia�u !!
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "material.h"


// licznik obiekt�w klasy MaterialQT utworzonych przez konstruktor domy�lny
// u�ywany do nadawania kolejnych domy�lnych nazw pustym materia�om
int Material::emptyMaterialsCount = 0;



// konstruktor domy�lny
Material::Material()																// warto�ci domy�lne
{
	// zwi�kszamy licznik pustych materia��w i stosujemy go w nazwie domy�lnego materia�u
	_materialName			= QString("Default material (%1)").arg(++emptyMaterialsCount);
	
	const GLfloat emptyMat[4] = { 0.0, 0.0, 0.0, 1.0 };
	
	setAmbientColor  ( emptyMat );
	setDiffuseColor  ( emptyMat );
	setSpecularColor ( emptyMat );
	setEmissionColor ( emptyMat );
	setShininess	( 0 );
}	



// konstruktor parametryczny QT
Material::Material( 
										QString		materialName, 									
										QColor		ambientColor,
										int				ambientAlpha,
										QColor		diffuseColor,
										int				diffuseAlpha,
										QColor		specularColor,
										int				specularAlpha,
										QColor		emissionColor,
										int				emissionAlpha,
										GLint			shininess
									)
{
	_materialName = materialName;

	setAmbientColor	 ( ambientColor,  ambientAlpha  );
	setDiffuseColor  ( diffuseColor,  diffuseAlpha  );
	setSpecularColor ( specularColor, specularAlpha );
	setEmissionColor ( emissionColor, emissionAlpha );
	setShininess ( shininess );
}



// konstruktor parametryczny OpenGL
Material::Material(
										const char*			materialName,
										const GLfloat*	ambientColor4fv,
										const GLfloat*	diffuseColor4fv,
										const GLfloat*	specularColor4fv,
										const GLfloat*	emissionColor4fv,
													GLint			shininess
									)
{
	_materialName 		= materialName;
	
	setAmbientColor ( ambientColor4fv  );
	setDiffuseColor ( diffuseColor4fv  );
	setSpecularColor( specularColor4fv );
	setEmissionColor( emissionColor4fv );
	setShininess ( shininess );
}
	
	

// destruktor
Material::~Material() {}



// operator przypisania
// - NAZWA MATERIA�U NIE JEST KOPIOWANA
Material& Material::operator=(const Material& material)
{
	setAmbientColor	( material.ambientColor4fv()  );
	setDiffuseColor	( material.diffuseColor4fv()  );
	setSpecularColor( material.specularColor4fv() );
	setEmissionColor( material.emissionColor4fv() );
	setShininess		( material.shininess() );
	
	return *this;
}	


// operator por�wnania:
//  - NAZWA MATERIA�U NIE JEST POR�WNYWANA
bool Material::operator==(const Material& material)
{
	if (_qAmbientColor 	!= 	material.ambientColorQT()) 	return false;
	if (_iAmbientAlpha 	!= 	material.ambientAlpha()) 		return false;
	if (_qDiffuseColor 	!= 	material.diffuseColorQT()) 	return false;
	if (_iDiffuseAlpha 	!= 	material.diffuseAlpha()) 		return false;
	if (_qSpecularColor	!= 	material.specularColorQT())	return false;
	if (_iSpecularAlpha	!= 	material.specularAlpha()) 	return false;
	if (_qEmissionColor	!= 	material.emissionColorQT()) return false;
	if (_iEmissionAlpha	!= 	material.emissionAlpha()) 	return false;
	if (_shininess 			!= 	material.shininess()) 			return false;

	return true;
}


///////////////////////////////////////////////////////////////////  ustaw nazw� dla materia�u
void Material::setMaterialName( const QString materialName )
{
	_materialName = materialName;
}

void Material::setMaterialName( const char* materialName )
{
	_materialName = materialName;
}
///////////////////////////////////////////////////////////////////  ustaw nazw� dla materia�u



/////////////////////////////////////////////////////////////////// ustawienie kolor�w QT
// metoda uniwersalna do ustawienia koloru
//  INcolor			= kolor QT, na kt�ry chcemy ustawi�
//  INalpha			= przezroczysto��, na kt�r� chcemy ustawi�
//  OUTcolor		= wyj�ciowy kolor QT
//  OUTalpha		= wyj�ciowa alpha
//  OUTcolor4fv	=	wyj�ciowy kolor OpenGL : GLfloat[4]
void Material::setColor( const QColor& INcolor, int INalpha, QColor* OUTcolor, int* OUTalpha, GLfloat* OUTcolor4fv)
{
  if (!INcolor.isValid()) return;

  if (INalpha >= 0 && INalpha <= 255) // je�eli podano prawid�owo przezroczysto��
	{
		*(OUTcolor4fv + 3)	= (GLfloat) INalpha/255;  
		*OUTalpha						= (int) INalpha;
	}
	
	*OUTcolor = INcolor; // zachowujemy kolor w postaci QT
		
	// zachowujemy kolor w postaci OpenGL
	*(OUTcolor4fv + 0) = (GLfloat) INcolor.red()/255;
  *(OUTcolor4fv + 1) = (GLfloat) INcolor.green()/255;
  *(OUTcolor4fv + 2) = (GLfloat) INcolor.blue()/255;
}

void Material::setAmbientColor( const QColor& color, int alpha )
{
	setColor( color, alpha, &_qAmbientColor, &_iAmbientAlpha, _ambientColor);
}

void Material::setDiffuseColor( const QColor& color, int alpha )
{
	setColor( color, alpha, &_qDiffuseColor, &_iDiffuseAlpha, _diffuseColor);
}

void Material::setSpecularColor( const QColor& color, int alpha )
{
  setColor( color, alpha, &_qSpecularColor, &_iSpecularAlpha, _specularColor);
}

void Material::setEmissionColor( const QColor& color, int alpha )
{
  setColor( color, alpha, &_qEmissionColor, &_iEmissionAlpha, _emissionColor);
}

void Material::setShininess( GLint shininess )
{
	_shininess  = shininess;
	_shininessf = (GLfloat) shininess;
}
/////////////////////////////////////////////////////////////////// ustawienie kolor�w QT




/////////////////////////////////////////////////////////////////// ustawienie kolor�w OpenGL
// metoda uniwersalna
//  INcolor4fv  = kolor OpenGL, na kt�ry chcemy ustawi�
//  OUTcolor4fv = kolor wyj�ciowy OpenGL
//  OUTcolor	  = kolor wyj�ciowy QT
//  OUTalpha	  = alpha wyj�ciowa QT
void Material::setColor( const GLfloat* INcolor4fv, GLfloat* OUTcolor4fv, QColor* OUTcolor, int* OUTalpha )
{
	for (int i=0; i<4; i++)
		*(OUTcolor4fv + i) = *(INcolor4fv + i);  // przepisanie warto�ci koloru
	
	
	OUTcolor->setRgb((int) ((*(INcolor4fv+0))*255.0),
							 		 (int) ((*(INcolor4fv+1))*255.0),
									 (int) ((*(INcolor4fv+2))*255.0));
	
	*OUTalpha = (int) ((*(INcolor4fv+3))*255.0);
}

void Material::setAmbientColor(	const GLfloat* color )
{
	setColor( color, _ambientColor, &_qAmbientColor, &_iAmbientAlpha );
}

void Material::setDiffuseColor(	const GLfloat* color )
{
	setColor( color, _diffuseColor, &_qDiffuseColor, &_iDiffuseAlpha );
}

void Material::setSpecularColor( const GLfloat* color )
{
	setColor( color, _specularColor, &_qSpecularColor, &_iSpecularAlpha );
}

void Material::setEmissionColor( const GLfloat* color )
{
	setColor( color, _emissionColor, &_qEmissionColor, &_iEmissionAlpha );
}
/////////////////////////////////////////////////////////////////// ustawienie kolor�w OpenGL

