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
Klasa reprezentuje bry�� elementarn� wraz z atrybutami materia�u i tekstury.
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
    Metoda zwraca domy�lny materia�.
    */
    static const Material& defaultMaterial()        { return _DefMaterial; }
    /*!
    Metoda ustawia podany materia� jako domy�lny.
    */
    static void setDefaultMaterial( Material &mat ) { _DefMaterial = mat; }
    /*!
    Metoda zwraca domy�lne parametry tekstury.
    */
    static const TextureParams& defaultTextureParams()              { return _DefTextureParams; }
    /*!
    Metoda ustawia domy�lne parametry tekstury.
    */
    static void setDefaultTextureParams( TextureParams &texParams ) { _DefTextureParams = texParams; }

    /*!
    Metoda zwraca licznik utworzonych obiekt�w tej klasy.
    */
    int count() { return _count; }
    
    // materia�
    /*!
    Metoda zwraca wska�nik na materia� wykorzystywany przez ten element.
    */
    Material* material() const  { return _material; }
    /*!
    Metoda zwraca typ powierzchni, kt�rym aplikowany jest materia�.
    */
    GLenum    applyTo()  const  { return _applyTo;  }
    /*!
    Czy stosowanie materia�u jest w��czone?
    */
    bool      materialEnabled() const { return _materialEnabled; }
        
    // tekstura
    /*!
    Czy stosowanie tekstury jest w��czone?
    */
    bool            textureEnabled() const { return _textureEnabled; }
    /*!
    Metoda zwraca wska�nik na aktualnie stosowane parametry tekstury.
    */
    TextureParams*  textureParams()  const { return _textureParams; }
  
  private:
    static Material _DefMaterial;
    static TextureParams  _DefTextureParams;
    static int _count;
    
    // materia�
    Material* _material;
    bool      _materialEnabled;
    GLenum    _applyTo;
        
    // tekstura
    bool           _textureEnabled;
    TextureParams* _textureParams;
    
  
  public slots:
    // materia�
    void setApplyTo         ( GLenum applyTo );
    /*!
    Metoda w��cza/wy��cza stosowanie materia�u.
    */
    void setMaterialEnabled ( bool yes ) { _materialEnabled = yes; }
    
    // tekstura
    /*!
    Metoda w��cza/wy��cza stosowanie tekstury.
    */
    void setTextureEnabled  ( bool yes )          { _textureEnabled = yes; }
    /*!
    Metoda ustawia nowe parametry tekstury.
    */
    void setTextureParams   ( TextureParams& texParams ) { *_textureParams = texParams; }
};




#endif
