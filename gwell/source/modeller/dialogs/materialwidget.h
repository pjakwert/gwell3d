////////////////////////////////////////////////////////////////////////////////
///
///  class: MaterialWidget (.h)
///
///  widget do edycji w�a�ciwo�ci materia�u - jedna z zak�adek w MaterialEditor
///
////////////////////////////////////////////////////////////////////////////////
#ifndef MATERIALWIDGET_H
#define MATERIALWIDGET_H

#include <qptrlist.h>
#include <qcolor.h>
#include <qpushbutton.h>
#include <qbuttongroup.h>
#include <qlabel.h>
#include <qradiobutton.h>
#include <qgroupbox.h>
#include <qslider.h>
#include <qlineedit.h>
#include <qtextedit.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qdom.h>
#include <qdir.h>
#include <qmessagebox.h>

#include <const.h>
#include <kernel.h>
#include <icons.h>
#include <material.h>
#include <statusbar.h>

#include <namedialog.h>
#include <colorwidget.h>
#include <shinewidget.h>

class CellFrame;



/*!
Struktura u�ywana do przechowywania poprzednich w�a�ciwo�ci materia�owych obiekt�w
w celu ewentualnego ich odtworzenia (undo).
*/
typedef struct bk
{
  Material* _backupMaterial;        // zapami�tujemy oczywi�cie materia�
  bool      _backupMaterialEnabled; // czy materia� dla elementu by� w��czony
  GLenum    _backupApplyTo;         // do jakich �cian by� stosowany
} BackupStruct;


/*!
Klasa implementuje okno do edycji w�a�ciwo�ci materia�u.
*/
class MaterialWidget : public QWidget
{
  Q_OBJECT
      
  public:
    MaterialWidget( QPtrList<ViNTreeNode> *selectedList, QWidget *parent=0, const char* name=0, WFlags fl=0 );
    ~MaterialWidget();
    
  private:
    QPtrList<ViNTreeNode> *_selectedList;       // lista obrabianych obiekt�w
    QPtrList<Material>        *_materialList;       // lista materia��w za�adowana z dysku
    QPtrList<BackupStruct>    *_backupMaterialList; // zapasowa lista materia��w obrabianych obiekt�w
    bool _dynamicPreview;

    QFont f10;  // fonty rozmiar 9 i 10
    QFont f9;

    QFrame*         frameMat;
    QCheckBox*      enableMatCheck;
    QCheckBox*      dynamicPreviewCheck;
    QButtonGroup*   applyButtonGroup;
     QLabel*        applyLabel;
      QRadioButton* frontRadio;
      QRadioButton* backRadio;
      QRadioButton* fbRadio;
    ColorWidget*    ambientBox;
    ColorWidget*    diffuseBox;
    ColorWidget*    specularBox;
    ColorWidget*    emissionBox;
     QPushButton*   makeDefMatButton;
     QPushButton*   resetToDefMatButton;
    QComboBox*      materialCombo;
    QToolButton*    generateButton;
    QPushButton*    saveMatButton;
    ShineWidget*    shineBox;
    QTextEdit*      glMatSyntaxText;
    QFrame*         matLine2;
    QFrame*         matLine1;

  private slots:
    int  deduceMaterial         ( const Material* mat ) const;
    void setMaterialEnabled     ( bool on );
    void setDynamicPreview      ( bool on );
    void makeMaterialDefault    ();
    void resetToDefaultMaterial ();
    void setApplyTo             ( GLenum applyTo );
    void setApplyToFromButton   ( int num );
    void setAmbientColor        ( const QColor& color, int alpha );
    void setDiffuseColor        ( const QColor& color, int alpha );
    void setSpecularColor       ( const QColor& color, int alpha );
    void setEmissionColor       ( const QColor& color, int alpha );
    void setShininess           ( int shininess );
    void updateGLMatSyntaxText  ();
    void saveMaterial           ();
    int loadMaterials           ( QString path );
     int readFromFile           ( QString name );
     void selectMaterialFromCombo( int index );
    
  public slots:
    void undoMaterials();
};


#endif
