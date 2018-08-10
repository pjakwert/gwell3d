////////////////////////////////////////////////////////////////////////////////
///
///  class: TextureParams (.h)
///
///  klasa opisuje w³a¶ciwo¶ci tekstury
///
////////////////////////////////////////////////////////////////////////////////
#ifndef TEXTURE_PARAMS_H
#define TEXTURE_PARAMS_H

#include <GL/gl.h>



class TextureParams
{
  public:
    TextureParams(                                              // konstruktor
                  GLuint  GLTexID   = 0,
                  GLenum  magFilter = GL_NEAREST,
                  GLenum  minFilter = GL_NEAREST,
                  GLenum  wrapS     = GL_REPEAT,
                  GLenum  wrapT     = GL_REPEAT,
                  GLenum  envMode   = GL_DECAL,
                  bool    blendingEnabled = false,
                  GLenum  blendSrcFactor  = GL_SRC_ALPHA,
                  GLenum  blendDestFactor = GL_ONE,
                  bool    reflectingEnabled = false,
                  GLfloat minW = 0.0,
                  GLfloat minH = 0.0,
                  GLfloat maxW = 1.0,
                  GLfloat maxH = 1.0
                 );
    
    ~TextureParams() {};  // destruktor
        
    GLuint    GLTexID()        { return _glTexID; }
    GLenum    magFilter()      { return _magFilter; } // parametry filtrów
    GLenum    minFilter()      { return _minFilter; }
    GLenum    wrapS()          { return _wrapS; }
    GLenum    wrapT()          { return _wrapT; }
    GLenum    envMode()        { return _envMode; }    
    bool      blendingEnabled()   { return _blendingEnabled; } // blending
    GLenum    blendSrcFactor()    { return _srcFactor; }
    GLenum    blendDestFactor()   { return _destFactor; }
    bool      reflectingEnabled() { return _reflectingEnabled; } // reflecting
    GLfloat   minW()  { return _minW; }   // wspó³rzêdne mapowania tekstury
    GLfloat   minH()  { return _minH; }
    GLfloat   maxW()  { return _maxW; }
    GLfloat   maxH()  { return _maxH; }

    void setGLTexID( GLuint glTexID )             { _glTexID = glTexID; }
    void setMagFilter( GLenum magFilter )         { _magFilter = magFilter; }
    void setMinFilter( GLenum minFilter )         { _minFilter = minFilter; }
    void setWrapS( GLenum wrapS )                 { _wrapS = wrapS; }
    void setWrapT( GLenum wrapT )                 { _wrapT = wrapT; }
    void setEnvMode( GLenum envMode )             { _envMode = envMode; }
    void setBlendingEnabled ( bool yes )          { _blendingEnabled = yes; }
    void setBlendSrcFactor  ( GLenum srcFactor )  { _srcFactor = srcFactor; }
    void setBlendDestFactor ( GLenum destFactor ) { _destFactor = destFactor; }
    void setReflectingEnabled( bool yes )         { _reflectingEnabled = yes; }   
    void setMinWH( GLfloat minW, GLfloat minH );
    void setMaxWH( GLfloat maxW, GLfloat maxH );
    
    void setTextureParams( TextureParams& tp )    { (*this) = tp; }
    
    TextureParams& operator=(TextureParams& tp);
    bool operator==(TextureParams& tp);
    
  private:
    GLuint    _glTexID;
    
    GLenum    _magFilter;
    GLenum    _minFilter;
    GLenum    _wrapS;
    GLenum    _wrapT;
    GLenum    _envMode;
    bool      _blendingEnabled;
    GLenum    _srcFactor;
    GLenum    _destFactor;
    bool      _reflectingEnabled;
    
    GLfloat   _minW, _minH;
    GLfloat   _maxW, _maxH;
};



#endif
