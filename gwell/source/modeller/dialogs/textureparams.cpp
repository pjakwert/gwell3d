////////////////////////////////////////////////////////////////////////////////
///
///  class: TextureParams (.cpp)
///
///  klasa opisuje w³a¶ciwo¶ci tekstury
///
////////////////////////////////////////////////////////////////////////////////
#include "textureparams.h"

TextureParams::TextureParams(
                              GLuint  GLTexID,
                              GLenum  magFilter,
                              GLenum  minFilter,
                              GLenum  wrapS,
                              GLenum  wrapT,
                              GLenum  envMode,
                              bool    blendingEnabled,
                              GLenum  blendSrcFactor,
                              GLenum  blendDestFactor,
                              bool    reflectingEnabled,
                              GLfloat minW,
                              GLfloat minH,
                              GLfloat maxW,
                              GLfloat maxH
                            )
{
  setGLTexID( GLTexID );
  setMagFilter( magFilter );
  setMinFilter( minFilter );
  setWrapS( wrapS );
  setWrapT( wrapT );
  setEnvMode( envMode );
  setBlendingEnabled( blendingEnabled );
  setBlendSrcFactor( blendSrcFactor );
  setBlendDestFactor( blendDestFactor );
  setReflectingEnabled( reflectingEnabled );
  setMinWH( minW, minH );
  setMaxWH( maxW, maxH );
}



/////////////////////////////////////////////////////////////////////////// wspó³rzêdne mapowania tekstury
void TextureParams::setMinWH( GLfloat minW, GLfloat minH )
{
  _minW = minW;
  _minH = minH;
}

void TextureParams::setMaxWH( GLfloat maxW, GLfloat maxH )
{
  _maxW = maxW;
  _maxH = maxH;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////




// operator przypisania
TextureParams& TextureParams::operator=(TextureParams& tp)
{
  setGLTexID( tp.GLTexID() );
  setMagFilter( tp.magFilter() );
  setMinFilter( tp.minFilter() );
  setWrapS( tp.wrapS() );
  setWrapT( tp.wrapT() );
  setEnvMode( tp.envMode() );
  setBlendingEnabled( tp.blendingEnabled() );
  setBlendSrcFactor( tp.blendSrcFactor() );
  setBlendDestFactor( tp.blendDestFactor() );
  setReflectingEnabled( tp.reflectingEnabled() );
  setMinWH( tp.minW(), tp.minH() );
  setMaxWH( tp.maxW(), tp.maxH() );

  return (*this);
}



// operator porównania
bool TextureParams::operator==(TextureParams& tp)
{
  if ( _glTexID != tp.GLTexID() ) return false;
  if ( _magFilter != tp.magFilter() ) return false;
  if ( _minFilter != tp.minFilter() ) return false;
  if ( _wrapS != tp.wrapS() ) return false;
  if ( _wrapT != tp.wrapT() ) return false;
  if ( _envMode != tp.envMode() ) return false;
  if ( _blendingEnabled != tp.blendingEnabled() ) return false;
  if ( _srcFactor != tp.blendSrcFactor() ) return false;
  if ( _destFactor != tp.blendDestFactor() ) return false;
  if ( _reflectingEnabled != tp.reflectingEnabled() ) return false;
  if ( _minW != tp.minW() ) return false;
  if ( _minH != tp.minH() ) return false;
  if ( _maxW != tp.maxW() ) return false;
  if ( _maxH != tp.maxH() ) return false;
  
  return true;
}
