#ifndef VIELEMEPOLYHEXT_H
#define VIELEMEPOLYHEXT_H

#include <qdom.h>

#include <const.h>
#include <kernel.h>

#include <material.h>
#include <texturemanager.h>
#include <textureparams.h>
#include <options.h>
#include <tools.h>



DEFPOLYHCLASS( ViElemePolyhExt, ViElemePolyh )
{
  public:
    ViElemePolyhExt();
    ViElemePolyhExt( ViPattePolyh const &PPolyh, const char *IndivName );
    ViElemePolyhExt( const ViElemePolyhExt &extEl );
    ~ViElemePolyhExt();
    bool WriteDescriptionTo( ExtString &Descr ) const;
    void InitWithDescr( ExtString &Descr );

    static const Material& defaultMaterial()        { return _DefMaterial; }
    static void setDefaultMaterial( Material &mat ) { _DefMaterial = mat; }
    static const TextureParams& defaultTextureParams()              { return _DefTextureParams; }
    static void setDefaultTextureParams( TextureParams &texParams ) { _DefTextureParams = texParams; }

    int count() { return _count; }
    
    // materia³
    Material* material() const  { return _material; }
    GLenum    applyTo()  const  { return _applyTo;  }
    bool      materialEnabled() const { return _materialEnabled; }
        
    // tekstura
    bool            textureEnabled() const { return _textureEnabled; }
    TextureParams*  textureParams()  const { return _textureParams; }
  
  private:
    static Material _DefMaterial;
    static TextureParams  _DefTextureParams;
    static int _count;
    
    // materia³
    Material* _material;
    bool      _materialEnabled;
    GLenum    _applyTo;
        
    // tekstura
    bool           _textureEnabled;
    TextureParams* _textureParams;
    
  
  public slots:
    // materia³
    void setApplyTo         ( GLenum applyTo );
    void setMaterialEnabled ( bool yes ) { _materialEnabled = yes; }
    
    // tekstura
    void setTextureEnabled  ( bool yes )          { _textureEnabled = yes; }
    void setTextureParams   ( TextureParams& texParams ) { *_textureParams = texParams; }
};




#endif
