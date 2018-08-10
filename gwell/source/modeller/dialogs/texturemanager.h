////////////////////////////////////////////////////////////////////////////////
///
///  class: TextureManager (.h)
///
///  klasa zarz±dza kolejk± tekstur, wszystkie metody statyczne
///
////////////////////////////////////////////////////////////////////////////////
#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <qptrlist.h>
#include <qimage.h>
#include <qobject.h>
#include <qcombobox.h>

#include <math.h>

#include <kernel.h>
#include <texture.h>
#include <textureparams.h>

class ViElemePolyhExt;
class CellFrame;


/*!
Klasa zarz±dza mechanizmem teksturowania w ca³ej aplikacji.
*/
class TextureManager
{
  static QPtrList<Texture> textureList;
  
  static CellFrame* hostFrame;
  static void makeCurrent();
  
  static QComboBox* loadedTexturesCombo;
  static void updateComboBox();
  
  static GLuint  createTexture( QString fileName, QImage::ScaleMode scaleMode, bool mipmapEnabled, const QImage* image );
  
  static void addTextureToObject( ViElemePolyhExt* elem, GLuint GLTextureID ); // zadawanie tekstury pojedynczemu obiektowi na podstawie ID
  static void addTextureToObjects( QPtrList<ViNTreeNode> *selectedList, GLuint GLTextureID ); // zadawanie tekstur grupie obiektów
  
  static bool _verbose;
  static bool _autoRemoveUnusedTextures; // czy za ka¿dym razem maj± byæ wyszukiwane nieu¿ywane tekstury i usuwane - to pole nie dotyczy metod deleteTextureFromObject() i deleteTexturesFromObjects(), domy¶lnie jest false - trzeba wtedy w³asnorêcznie wywo³aæ metodê removeUnusedTextures()
  
  static bool _safeMode; // safeMode nie pozwala na generowanie mipmap dla obrazów wiêkszych ni¿ 512x512
  static GLint _safeSize;
  
  static int     incHowManyUsers( GLuint GLTextureID );
  static int     decHowManyUsers( GLuint GLTextureID );
  static void    printInfo();
  static Texture* findTexture( GLuint GLTextureID );
  
  public:
    /*!
    Metoda ustawia widok bazowy (kontekst), do którego ³adowane bêd± wszystkie tekstury.
    */
    static void setHostFrame( CellFrame* frame ) { hostFrame = frame; }
    static void setComboBox( QComboBox* loadedTexCombo );
    
    static void loadTexturesFromObjects( ViMultiPolyh* mph ); // ³adowanie tekstur
    
    static void addTextureToObject( ViElemePolyhExt* elem, QString fileName, QImage::ScaleMode scaleMode, bool mipmapEnabled, const QImage* image );
    static void addTextureToObject( ViElemePolyhExt* elem, TextureParams* textureParams );
    static void addTextureToObjects( QPtrList<ViNTreeNode> *selectedList, QString fileName, QImage::ScaleMode scaleMode, bool mipmapEnabled, const QImage* inputImage );
    static GLint addTextureToObjectsFromCombo( QPtrList<ViNTreeNode> *selectedList );
    
    static void deleteTexturesFromObjects( QPtrList<ViNTreeNode> *selectedList ); // usuwanie tekstur
    static void deleteTextureFromObject( ViElemePolyhExt* elem ); // usuwanie tekstur
    
    static const Texture& getTexture( GLuint GLTextureID, bool* found=0L );
    static void     removeUnusedTextures();
    /*!
    Metoda zwraca ilo¶æ tekstur znajduj±cych siê w pamiêci.
    */
    static int      howManyTexturesLoaded()  { return textureList.count(); }
    
    /*!
    Metoda ustawia tryb wy¶wietlania komunikatów (do celów debuggowania).
    */
    static void     setVerboseMode( bool yes ) { _verbose = yes; }
    /*!
    Metoda zwraca tryb wy¶wietlania komunikatów.
    */
    static bool     verboseMode() { return _verbose; }
    /*!
    Metoda w³±cza/wy³±cza stosowanie bezpiecznego teksturowania.
    */
    static void     setSafeMode( bool yes ) { _safeMode = yes; }
    /*!
    Metoda zwraca flagê stosowania bezpiecznego teksturowania.
    */
    static bool     safeMode() { return _safeMode; }
    /*!
    Metoda ustawia bezpieczny dopuszczalny rozmiar tekstury.
    */
    static void     setSafeSize( GLint size ) { _safeSize = size; }
    /*!
    Metoda zwraca bezpieczny dopuszczalny rozmiar tekstury.
    */
    static GLint      safeSize() { return _safeSize; }
    
    /*!
    Metoda ustawia automatyczne usuwanie nieu¿ywanych tekstur.
    */
    static void     setAutoRemoveUnusedTextures( bool yes)  { _autoRemoveUnusedTextures = yes; }
    /*!
    Metoda zwraca flagê stosowania automatycznego usuwania nieu¿ywanych tekstur.
    */
    static bool     autoRemoveUnusedTextures() { return _autoRemoveUnusedTextures; }
};



#endif


