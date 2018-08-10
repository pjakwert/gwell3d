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


/*!
Klasa reprezentuje bry³ê elementarn± wraz z atrybutami materia³u i tekstury.
*/
DEFPOLYHCLASS( ViElemePolyhExt, ViElemePolyh )
{
  public:
    ViElemePolyhExt();
    ViElemePolyhExt( ViPattePolyh const &PPolyh, const char *IndivName );
    ViElemePolyhExt( const ViElemePolyhExt &extEl );
    ~ViElemePolyhExt();
    bool WriteDescriptionTo( ExtString &Descr ) const;
    void InitWithDescr( ExtString &Descr );

    /*!
    Metoda zwraca domy¶lny materia³.
    */
    static const Material& defaultMaterial()        { return _DefMaterial; }
    /*!
    Metoda ustawia podany materia³ jako domy¶lny.
    */
    static void setDefaultMaterial( Material &mat ) { _DefMaterial = mat; }
    /*!
    Metoda zwraca domy¶lne parametry tekstury.
    */
    static const TextureParams& defaultTextureParams()              { return _DefTextureParams; }
    /*!
    Metoda ustawia domy¶lne parametry tekstury.
    */
    static void setDefaultTextureParams( TextureParams &texParams ) { _DefTextureParams = texParams; }

    /*!
    Metoda zwraca licznik utworzonych obiektów tej klasy.
    */
    int count() { return _count; }
    
    // materia³
    /*!
    Metoda zwraca wska¼nik na materia³ wykorzystywany przez ten element.
    */
    Material* material() const  { return _material; }
    /*!
    Metoda zwraca typ powierzchni, którym aplikowany jest materia³.
    */
    GLenum    applyTo()  const  { return _applyTo;  }
    /*!
    Czy stosowanie materia³u jest w³±czone?
    */
    bool      materialEnabled() const { return _materialEnabled; }
        
    // tekstura
    /*!
    Czy stosowanie tekstury jest w³±czone?
    */
    bool            textureEnabled() const { return _textureEnabled; }
    /*!
    Metoda zwraca wska¼nik na aktualnie stosowane parametry tekstury.
    */
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
    /*!
    Metoda w³±cza/wy³±cza stosowanie materia³u.
    */
    void setMaterialEnabled ( bool yes ) { _materialEnabled = yes; }
    
    // tekstura
    /*!
    Metoda w³±cza/wy³±cza stosowanie tekstury.
    */
    void setTextureEnabled  ( bool yes )          { _textureEnabled = yes; }
    /*!
    Metoda ustawia nowe parametry tekstury.
    */
    void setTextureParams   ( TextureParams& texParams ) { *_textureParams = texParams; }
};




#endif
