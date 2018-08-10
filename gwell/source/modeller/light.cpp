//////////////////////////////////////////////////////////////////
///
///  class: Light (.cpp)
///
///  klasa opsiuj�ca pojedyncze �r�d�o �wiat�a
///
//////////////////////////////////////////////////////////////////

#include "light.h"


/*! domy�lne kolory dla nowo utworzonego �wiat�a */
const GLfloat Light::defaultAmbientColor[]  = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat Light::defaultDiffuseColor[]  = { 1.0, 1.0, 1.0, 1.0 };
const GLfloat Light::defaultSpecularColor[] = { 1.0, 1.0, 1.0, 1.0 };
const Vector3f Light::defaultPosition       = Vector3f( 0.0, 0.0, 1.0 );
const Vector3f Light::defaultSpotDirection  = Vector3f( 0.0, 0.0, -1.0 );


QValueList<GLenum> Light::freeLightNamesList = QValueList<GLenum>();

/*! czy lista �wiate� zosta�a zainicjowana - operacja wykonywana tylko raz */
bool Light::afterInit = false;


Light::Light(
              bool            isSpotlight,
              QString         lightName,
              bool            isEnabled,
              LightType       lightType,
              bool            isMovingWithCamera,
              const GLfloat*  ambientColor,
              const GLfloat*  diffuseColor,
              const GLfloat*  specularColor,
              Vector3f        position,
              Vector3f        spotDirection,
              GLfloat         spotExponent,
              GLfloat         spotCutOffAngle,
              GLfloat         constantAttenuation,
              GLfloat         linearAttenuation,
              GLfloat         quadraticAttenuation
            ) : QObject()
{
  // wywo�ywane tylko raz - inicjalizacja listy nazw �wiate�
  if ( !afterInit ) initFreeLightNamesList();
  
  _createdSuccessfully = false;
   // czy mo�na doda� �r�d�o �wiat�a
   if ( !findSetAndDeleteGLName() ) return;
  _createdSuccessfully = true;
  
  _prevCutOff = 22.5;
  _isSpotlight = false;
  
  setSpotlight( isSpotlight );
  setName( lightName );
  setEnabled( isEnabled );
  setMovingWithCamera( isMovingWithCamera );
  setLightType( lightType );
  setAmbientColor( ambientColor );
  setDiffuseColor( diffuseColor );
  setSpecularColor( specularColor );
  setPosition( position );
  setSpotDirection( spotDirection );
  setSpotExponent( spotExponent );
  setSpotCutOffAngle( spotCutOffAngle );
  setConstantAttenuation( constantAttenuation );
  setLinearAttenuation( linearAttenuation );
  setQuadraticAttenuation( quadraticAttenuation );
  
}


/*!
Destruktor - usuni�cie �wiat�a powoduje od�o�enie jego nazwy na list� wolnych nazw OpenGL.
*/
Light::~Light()
{
  if ( this->_createdSuccessfully ) // o ile �wiat�o zosta�o wcze�niej utworzone pomy�lnie
  {
    freeLightNamesList.append( this->_GLname );
  }
}


/*!
Metoda znajduje woln� nazw� na li�cie, ustawia j� jako aktualn� i zdejmuje z listy wolnych nazw.
*/
bool Light::findSetAndDeleteGLName()
{
  if ( freeLightNamesList.isEmpty() ) return false;
  
  this->_GLname = freeLightNamesList.first(); // pierwsza wolna nazwa
  
  freeLightNamesList.pop_front();       // usuwamy j� z listy wolnych nazw
  
  return true;
}


/*!
Metoda inicjuje list� wolnych nazw OpenGL dla 8 �wiate�.
*/
void Light::initFreeLightNamesList()
{
  freeLightNamesList.clear();
  freeLightNamesList.append( GL_LIGHT0 );
  freeLightNamesList.append( GL_LIGHT1 );
  freeLightNamesList.append( GL_LIGHT2 );
  freeLightNamesList.append( GL_LIGHT3 );
  freeLightNamesList.append( GL_LIGHT4 );
  freeLightNamesList.append( GL_LIGHT5 );
  freeLightNamesList.append( GL_LIGHT6 );
  freeLightNamesList.append( GL_LIGHT7 );
  afterInit = true;
}



/*!
Metoda przywraca domy�lne warto�ci OpenGL dla �wiat�a (opr�cz nazwy).
*/
void Light::reset()
{
  setEnabled( true );
  setMovingWithCamera( false );
  setLightType( Directional );
  setAmbientColor( defaultAmbientColor );
  setDiffuseColor( defaultDiffuseColor );
  setSpecularColor( defaultSpecularColor );
  setPosition( defaultPosition );
  setSpotDirection( defaultSpotDirection );
  setSpotExponent( 0.0 );
  setSpotCutOffAngle( 180.0 );
  setConstantAttenuation( 1.0 );
  setLinearAttenuation( 0.0 );
  setQuadraticAttenuation( 0.0 );
}




/*!
Metoda ustawia nazw� dla �wiat�a.
Je�eli nazwa nie zostanie podana, ustawi nazw� odpowiadaj�c� OpenGL: Gl_LIGHT0, GL_LIGHT1, ...
*/
void Light::setName( QString name )
{
  if ( name.isEmpty() )
  {
    switch ( _GLname )
    {
      case GL_LIGHT0 : _name = "GL_LIGHT0"; break;
      case GL_LIGHT1 : _name = "GL_LIGHT1"; break;
      case GL_LIGHT2 : _name = "GL_LIGHT2"; break;
      case GL_LIGHT3 : _name = "GL_LIGHT3"; break;
      case GL_LIGHT4 : _name = "GL_LIGHT4"; break;
      case GL_LIGHT5 : _name = "GL_LIGHT5"; break;
      case GL_LIGHT6 : _name = "GL_LIGHT6"; break;
      case GL_LIGHT7 : _name = "GL_LIGHT7"; break;
      default : _name = "GL_LIGHT NAME ERROR !"; break;
    }
  }
  else _name = name;
}


/*!
Metoda ustawia typ �wiat�a: Directional lub Positional.
W zale�no�ci od tego ustawia odpowiednio warto�� _position[3].
*/
void Light::setLightType( LightType lightType )
{
  _lightType = lightType;
  
  if ( _lightType == Positional ) _position[3] = 1.0f;
  else _position[3] = 0.0f;
}

/*!
Czy �wiat�o jest w��czone?
*/
void Light::setEnabled( bool yes )
{
  _isEnabled = yes;
}


/*!
Metoda ustawia pozycj� dla �wiat�a.
*/
void Light::setPosition( Vector3f position )
{
  _position[0] = (GLfloat) position.x;
  _position[1] = (GLfloat) position.y;
  _position[2] = (GLfloat) position.z;
}
    
/*!
Ustawienie koloru Ambient (parametry dla QT).
*/
void Light::setAmbientColor( const QColor& color, int alpha )
{
  _ambientColor[0] = (GLfloat) color.red()   / 255.0f;
  _ambientColor[1] = (GLfloat) color.green() / 255.0f;
  _ambientColor[2] = (GLfloat) color.blue()  / 255.0f;
  
  if ( alpha > -1 ) _ambientColor[3] = (GLfloat) alpha / 255.0f;
}

/*!
Ustawienie koloru Ambient (parametry dla OpenGL).
*/
void Light::setAmbientColor( const GLfloat* ambientColor )
{
  for (int i=0; i<4; i++) _ambientColor[i] = *(ambientColor+i);
}


/*!
Ustawienie koloru Diffuse (parametry dla QT).
*/
void Light::setDiffuseColor( const QColor& color, int alpha )
{
  _diffuseColor[0] = (GLfloat) color.red()   / 255.0f;
  _diffuseColor[1] = (GLfloat) color.green() / 255.0f;
  _diffuseColor[2] = (GLfloat) color.blue()  / 255.0f;
  
  if ( alpha > -1 ) _diffuseColor[3] = (GLfloat) alpha / 255.0f;
}


/*!
Ustawienie koloru Ambient (parametry dla OpenGL).
*/
void Light::setDiffuseColor( const GLfloat* diffuseColor )
{
  for (int i=0; i<4; i++) _diffuseColor[i] = *(diffuseColor+i);
}

/*!
Ustawienie koloru Specular (parametry dla QT).
*/
void Light::setSpecularColor( const QColor& color, int alpha )
{
  _specularColor[0] = (GLfloat) color.red()   / 255.0f;
  _specularColor[1] = (GLfloat) color.green() / 255.0f;
  _specularColor[2] = (GLfloat) color.blue()  / 255.0f;
  
  if ( alpha > -1 ) _specularColor[3] = (GLfloat) alpha / 255.0f;
}


/*!
Ustawienie koloru Specular (parametry dla OpenGL).
*/
void Light::setSpecularColor( const GLfloat* specularColor )
{
  for ( int i=0; i<4; i++ ) _specularColor[i] = *(specularColor+i);
}
    
/*!
Czy �wiat�o porusza si� razem z kamer�?
*/
void Light::setMovingWithCamera( bool yes )
{
  _isMovingWithCamera = yes;
}

/*!
Metoda ustawia kierunek �wiat�a kierunkowego :)
*/
void Light::setSpotDirection( Vector3f spotDirection )
{
  _spotDirection[0] = (GLfloat) spotDirection.x;
  _spotDirection[1] = (GLfloat) spotDirection.y;
  _spotDirection[2] = (GLfloat) spotDirection.z;
}


/*!
Metoda ustawia skupienie �wiat�a.
*/
void Light::setSpotExponent( GLfloat spotExponent )
{
  _spotExponent = spotExponent;
}


/*!
Metoda ustawia k�t rozwarcia sto�ka �wietlnego.
*/
void Light::setSpotCutOffAngle( GLfloat spotCutOff )
{
  if ( _spotCutOffAngle != 180.0 ) _prevCutOff = _spotCutOffAngle;
  _spotCutOffAngle = spotCutOff;
  
  setSpotlight( _isSpotlight ); // ta metoda ewentualnie skoryguje warto�� _spotCutOffAngle
}

/*!
Metoda ustawia �wiat�o na kierunkowe, dodatkowo koryguje warto�� rozwarcia sto�ka �wietlnego.
*/
void Light::setSpotlight( bool yes )
{
  if ( !_isSpotlight && yes ) // prze��czono z bulba na spotlight
  {
   // przywracamy starsz� warto��, zawieraj�c� poprawny k�t dla spotlight
   _spotCutOffAngle = _prevCutOff;    
  }
  
  if ( _isSpotlight && !yes ) // prze��czono ze spotlight na bulb
  {
    // zapami�taj k�t
    _prevCutOff = _spotCutOffAngle;   
  }
  
  _isSpotlight = yes;
  
  // spotlight nie mo�e mie� warto�ci cutOff poza przedzia�em [0.0, 90.0] - korekcja
  if ( yes && ( (_spotCutOffAngle < 0.0) || (_spotCutOffAngle > 90.0) ) )
  { 
    if ( _spotCutOffAngle > 90.0 ) _spotCutOffAngle = 89.0f;
    else _spotCutOffAngle = 1.0f;
  }
  
  if ( !yes ) // zwyk�e �wiat�o musi mie� cutOff = 180.0
  {
    _spotCutOffAngle = 180.0f;
  }
}


/*!
Ustawienie rozproszenia �wiat�a - wsp�czynnika sta�ego.
*/
void Light::setConstantAttenuation( GLfloat ca )
{
  _constantAttenuation = ca;
}

/*!
Ustawienie rozproszenia �wiat�a - wsp�czynnika liniowego.
*/
void Light::setLinearAttenuation( GLfloat la )
{
  _linearAttenuation = la;
}

/*!
Ustawienie rozproszenia �wiat�a - wsp�czynnika kwadratowego.
*/
void Light::setQuadraticAttenuation( GLfloat qa )
{
  _quadraticAttenuation = qa;
}

