//////////////////////////////////////////////////////////////////
///
///  class: Light (.h)
///
///  klasa opisuj±ca pojedyncze ¼ród³o ¶wiat³a
///
//////////////////////////////////////////////////////////////////
#ifndef LIGHT_H
#define LIGHT_H


#include <qstring.h>
#include <qcolor.h>
#include <qvaluelist.h>
#include <qobject.h>

#include <kernel.h>
#include <GL/gl.h>



class Light : public QObject
{
  Q_OBJECT
  
  // domy¶lne kolory dla nowo utworzonego ¶wiat³a
  static const GLfloat defaultAmbientColor[];
  static const GLfloat defaultDiffuseColor[];
  static const GLfloat defaultSpecularColor[];
  static const Vector3f defaultPosition;
  static const Vector3f defaultSpotDirection;
  
  // lista zawiera wolne warto¶ci GLenum odpowiadaj±ce nazwom ¶wiate³ w OpenGL
  static QValueList<GLenum> freeLightNamesList;
  
  public:
    typedef enum { Directional = 0, Positional } LightType;
    
    Light( 
            bool            isSpotlight, // jedyny wymagany parametr - ¿arówka czy spotlight
            QString         lightName             = QString::null,
            bool            isEnabled             = true,
            LightType       lightType             = Directional,
            bool            isMovingWithCamera    = false,
            const GLfloat*  ambientColor          = defaultAmbientColor,
            const GLfloat*  diffuseColor          = defaultDiffuseColor,
            const GLfloat*  specularColor         = defaultSpecularColor,
            Vector3f        position              = defaultPosition,
            Vector3f        spotDirection         = defaultSpotDirection,
            GLfloat         spotExponent          = 0.0,
            GLfloat         spotCutOffAngle       = 180.0,
            GLfloat         constantAttenuation   = 1.0,
            GLfloat         linearAttenuation     = 0.0,
            GLfloat         quadraticAttenuation  = 0.0
        );
    
    ~Light();
  
  private:
    QString   _name;
    GLenum    _GLname;
    bool      _isEnabled;
    bool      _isSpotlight;
    bool      _isMovingWithCamera;
    LightType _lightType;
    GLfloat   _ambientColor[4];
    GLfloat   _diffuseColor[4];
    GLfloat   _specularColor[4];
    GLfloat   _position[4];
    GLfloat   _spotDirection[3];
    GLfloat   _spotExponent;
    GLfloat   _spotCutOffAngle;
    GLfloat   _prevCutOff;            // wcze¶niejsza warto¶æ _spotCutOffAngle
    GLfloat   _constantAttenuation;
    GLfloat   _linearAttenuation;
    GLfloat   _quadraticAttenuation;
    bool      _createdSuccessfully;
    
    bool findSetAndDeleteGLName();
    
    static bool afterInit;
    void initFreeLightNamesList();
  
    
  public:
    const QString   name()                 const { return _name; }
    const GLenum    GLname()               const { return _GLname; }
    bool            isEnabled()            const { return _isEnabled; }
    bool            isSpotlight()          const { return _isSpotlight; }
    bool            isMovingWithCamera()   const { return _isMovingWithCamera; }
    LightType       lightType()            const { return _lightType; }
    const GLfloat*  ambientColor4fv()      const { return _ambientColor; }
    const GLfloat*  diffuseColor4fv()      const { return _diffuseColor; }
    const GLfloat*  specularColor4fv()     const { return _specularColor; }
    const GLfloat*  position4fv()          const { return _position; }
    const GLfloat*  spotDirection3fv()     const { return _spotDirection; }
    GLfloat         spotExponent()         const { return _spotExponent; }
    GLfloat         spotCutOffAngle()      const { return _spotCutOffAngle; }
    GLfloat         constantAttenuation()  const { return _constantAttenuation; }
    GLfloat         linearAttenuation()    const { return _linearAttenuation; }
    GLfloat         quadraticAttenuation() const { return _quadraticAttenuation; }
    bool            createdSuccessfully()  const { return _createdSuccessfully; }
      
  public slots:
    void setLightType( LightType lightType );
    void setSpotlight( bool yes );
    void setName( QString lightName = QString::null );
    void setEnabled( bool yes );
    void setPosition( Vector3f position );
    
    void setAmbientColor( const QColor& color, int alpha = -1 );
    void setAmbientColor( const GLfloat* ambientColor );
    void setDiffuseColor( const QColor& color, int alpha = -1 );
    void setDiffuseColor( const GLfloat* diffuseColor );
    void setSpecularColor( const QColor& color, int alpha = -1 );
    void setSpecularColor( const GLfloat* specularColor );
    
    void setMovingWithCamera( bool yes );
    void setSpotDirection( Vector3f spotDirection );
    void setSpotExponent( GLfloat spotExponent );
    void setSpotCutOffAngle( GLfloat spotCutOff );
    void setConstantAttenuation( GLfloat ca );
    void setLinearAttenuation( GLfloat la );
    void setQuadraticAttenuation( GLfloat qa );
    void reset();
    
};    



#endif
