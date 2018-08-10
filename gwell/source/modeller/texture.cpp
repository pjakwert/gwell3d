////////////////////////////////////////////////////////////////////////////////////////////////
///
///  class: Texture (.cpp)
///
///  klasa opisuje teksturê
///  przeci±¿one s± operatory przypisania i porównania:
//    - nie porównuje GLTextureID
//    - nie porównuje flagi _isValid, poniewa¿ przy przypisaniu i ustawianiu nazwy pliku jest ona ustawiana automatycznie
///   - nie porównuje pól howManyUsers (ale przepisuje je)
///
////////////////////////////////////////////////////////////////////////////////////////////////

#include "texture.h"


// konstruktor
Texture::Texture(
                  QString           fileName,
                  QImage::ScaleMode scaleMode,
                  bool              mipmapingEnabled,
                  GLuint            GLTextureID,
                  int               howManyUsers,
                  QPixmap*          preview
                )
{
  setFileName       ( fileName );
  setScaleMode      ( scaleMode );
  setMipmapEnabled  ( mipmapingEnabled );
  setGLTextureID    ( GLTextureID );
  setHowManyUsers   ( howManyUsers );
  setPreview        ( preview );
}



/*!
Metoda ustawia nazwê pliku tekstury. Sprawdza czy plik graficzny istnieje, nawet je¿eli nie istnieje - ustawia jego nazwê dla tekstury, ale flagê _isValid ustawia na FALSE.
\return 0 - OK,
\return -1 - plik nie istnieje,
\return -2 - nieprawid³owy format obrazu (aktualnie nieu¿ywane).
*/
int Texture::setFileName( const QString& fileName )
{ 
  _fileName = fileName;
  
  // sprawdzenie czy plik istnieje
  QFile file( fileName );
  if ( !file.exists() ) { _isValid = false; return -1; }
  
  // czy plik ma prawid³owy format
  //QImage image( fileName );
  //if ( image.isNull() ) { _isValid = false; return -2; }
  
  _isValid = true;
  return 0;
}





/*!
Operator przypisania. Nie przepisuje flagi isValid().
*/
Texture& Texture::operator=(Texture &t)
{
  setFileName       ( t.fileName() );
  setScaleMode      ( t.scaleMode() );
  setMipmapEnabled  ( t.mipmapingEnabled() );
  setGLTextureID    ( t.GLTextureID() );
  setHowManyUsers   ( t.howManyUsers() );
  
  // tworzona jest kopia pixmapy z podgl±dem
  if ( t.preview() )
  {
    QPixmap* preview = new QPixmap( *(t.preview()) );
    setPreview( preview );
  }
  else setPreview( 0L );

  return (*this);
}


/*!
Operator porównania. Nie porównuje: ID tekstury, howManyUsers, isValid.
*/
bool Texture::operator==(Texture &t)
{
  //if ( _GLTextureID != t.GLTextureID() ) return false;
  if ( _fileName != t.fileName() ) return false;
  if ( _scaleMode != t.scaleMode() ) return false;
  if ( _mipmapEnabled != t.mipmapingEnabled() ) return false;
  
  return true;
}

