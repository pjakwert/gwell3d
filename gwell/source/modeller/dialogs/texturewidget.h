////////////////////////////////////////////////////////////////////////////////
///
///  class: TextureWidget (.h)
///
///  widget do edycji w³a¶ciwo¶ci tekstury - jedna z zak³adek w MaterialEditor
///
////////////////////////////////////////////////////////////////////////////////
#ifndef TEXTUREWIDGET_H
#define TEXTUREWIDGET_H

#include <qframe.h>
#include <qcheckbox.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qgroupbox.h>
#include <qpixmap.h>
#include <qspinbox.h>
#include <qstringlist.h>
#include <qfont.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qfiledialog.h>
#include <qfile.h>
#include <qtooltip.h>

#include <const.h>
#include <icons.h>
#include <kernel.h>

#include <floatspinbox.h>
#include <texturemanager.h>
#include <imagepreview.h>


class CellFrame;


class TextureWidget : public QWidget
{
  Q_OBJECT
      
  public:
    TextureWidget( QPtrList<ViNTreeNode> *selectedList, QWidget *parent=0, const char* name=0, WFlags fl=0 );
    ~TextureWidget() { TextureManager::removeUnusedTextures(); TextureManager::setComboBox( 0L ); }
    
    void undoTexturing();
    
  private:
    QPtrList<ViNTreeNode> *_selectedList;       // lista obrabianych obiektów
    bool    _dynamicPreview;
    static QString _lastPath;  // u¿ywana przez FileDialog - ostatnio u¿ywany katalog
    static QImage  _lastImage;    // przechowuje ca³y aktualnie u¿ywany obraz
    static QString _lastFileName; // nazwa pliku skojarzona z powy¿szym obrazem
    
    QFrame*       mainFrame;
    QCheckBox*    textureEnabledCheck;
    QCheckBox*    dynamicPreviewCheck;
    QCheckBox*    mipmapCheck;
    QCheckBox*    reflectCheck;
    QFrame*       topLine;
    QFont         f9, f10;
    
    QGroupBox*    texParamsGroup;
     QLabel*      magFilterLabel; 
     QComboBox*   magFilterCombo; 
     QLabel*      minFilterLabel;
     QComboBox*   minFilterCombo; 
     QLabel*      wrapSLabel;
     QComboBox*   wrapSCombo; 
     QLabel*      wrapTLabel;
     QComboBox*   wrapTCombo;
     QLabel*      envModeLabel;
     QComboBox*   envModeCombo;
     
    QGroupBox*    blendGroup;
     QCheckBox*   enableBlendCheck;
     QLabel*      srcBlendLabel;
     QComboBox*   srcBlendCombo;
     QLabel*      destBlendLabel;
     QComboBox*   destBlendCombo;
    
    QGroupBox*    imageParamsGroup;
     QPushButton* loadImageButton;
     QPushButton* removeImageButton;
     QLabel*      scaleModeLabel;
     QComboBox*   scaleModeCombo;
     QLabel*      previewLabel;
     QLabel*      fileLabel;
     QLineEdit*   fileEdit;
     QLabel*      origSizeLabel;
     QLineEdit*   origSizeEdit;
     QLabel*      currSizeLabel;
     QLineEdit*   currSizeEdit;
     
    QGroupBox*    coordsGroup; 
     QLabel*      MINlabel;
     QLabel*      MAXlabel;
     QLabel*      widthLabel;
     QLabel*      heightLabel;
     FloatSpinBox* minWSpin;
     FloatSpinBox* minHSpin;
     FloatSpinBox* maxWSpin;
     FloatSpinBox* maxHSpin;
    
    QPushButton*  makeDefaultButton;
    QPushButton*  resetToDefaultButton; 
    
    QComboBox*    loadedTexturesCombo;
    
    void generatePreviewAndInfo( QString fileName=QString::null, QImage::ScaleMode=QImage::ScaleFree, const QImage* inputImage=0L );
    void setInfo( QString fileName=QString::null, QString oldSize=QString::null, QString newSize=QString::null );
    /*
    QFrame*       bottomLine;
    QTextEdit*    glTexSyntaxEdit;
    QToolButton*  generateButton;
    */
    
  private slots:
    void setTextureEnabledGUI    ( bool yes );  // metody *GUI ustawiaj± tylko widgety,
    void setBlendingEnabledGUI   ( bool yes );  // nie zmieniaj± w³a¶ciwo¶ci obiektu
    
    void setTextureEnabled ( bool yes );
    
    void setScaleMode      ( QImage::ScaleMode scaleMode, bool apply );
    void setMipmapingEnabled( bool yes );
    void setMagFilter      ( GLenum magFilter, bool apply );
    void setMinFilter      ( GLenum minFilter, bool apply );
    void setWrapS          ( GLenum wrapS, bool apply );
    void setWrapT          ( GLenum wrapT, bool apply );
    void setEnvMode        ( GLenum envMode, bool apply );
    void setBlendingEnabled( bool yes );
    void setBlendSrcFactor ( GLenum srcFactor, bool apply );
    void setBlendDestFactor( GLenum destFactor, bool apply );
    void setReflectingEnabled( bool yes );
    void setMinWH          ( GLfloat minW, GLfloat minH, bool apply );
    void setMaxWH          ( GLfloat maxW, GLfloat maxH, bool apply );
    
    void setDynamicPreview ( bool on );
    void refresh();
    
    // sloty dla widgetow
    void setMagFilterFromCombo( int );
    void setMinFilterFromCombo( int );
    void setWrapSFromCombo    ( int );
    void setWrapTFromCombo    ( int );
    void setEnvModeFromCombo  ( int );
    void setBlendSrcFactorFromCombo ( int );
    void setBlendDestFactorFromCombo( int );
    void setScaleModeFromCombo( int );
    void minWHChanged         ( float );
    void maxWHChanged         ( float );
    void openFileDialog();
    void removeImage();
    void makeCurrentTextureDefault();
    void resetToDefaultTexture();
    void loadTextureFromCombo( int );
};



#endif
