#ifndef MODIFYWIDGET_H
#define MODIFYWIDGET_H

#include <qwidget.h>
#include <qgroupbox.h>
#include <qpushbutton.h>
#include <qtoolbutton.h>
#include <qradiobutton.h>
#include <qlayout.h>
#include <qfont.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qtoolbox.h>
#include <qhbox.h>

#include <modifiers.h>
#include <icons.h>
#include <nodotvalidator.h>
#include <cellframe.h>
#include <statusbar.h>
#include <options.h>


class ModifyWidget : public QWidget
{
  Q_OBJECT

  public:
    ModifyWidget( QString title, QWidget *parent=0, const char *name=0 );
    ~ModifyWidget() {}

  private:
    QPtrList<ViMultiPolyh> *_selectedList;
    QGridLayout *grid;
    bool        _rad;
    void block(bool yes);  // blokuje lub odblokowuje sygnaly textChanged
    
   QGroupBox   *toolsBox;
    QToolButton *selectButton;
    QToolButton *transButton;
    QToolButton *rotateButton;
    QToolButton *scaleButton;
//    QWidget     *emptyWidget;
    QToolButton *currentButton;

  QDoubleValidator *doubleValidator;
  NoDotValidator   *noDotValidator;
  
  
   QGroupBox   *editBox;
    QGridLayout *editGrid;
    QLineEdit   *txe;
    QLineEdit   *tye;
    QLineEdit   *tze;
    QLineEdit   *rxe;
    QLineEdit   *rye;
    QLineEdit   *rze;
    QRadioButton *degRadio;
    QRadioButton *radRadio;
    QLineEdit   *sxe;
    QLineEdit   *sye;
    QLineEdit   *sze;
    
  QGroupBox* fitScaleBox;
    QLineEdit* widthEdit;
    QLineEdit* heightEdit;
    QLineEdit* depthEdit;    

  QGroupBox *nameBox;       
    QLineEdit* obNameEdit;
    
  QGroupBox     *coordsBox;
    QLabel      *ctLabel;
     QLineEdit  *ctxe;
     QLineEdit  *ctye;
     QLineEdit  *ctze;
    QLabel      *crLabel;
     QLineEdit  *crxe;
     QLineEdit  *crye;
     QLineEdit  *crze;
  
  QGroupBox     *primitiveTypeBox;
    QComboBox   *primitiveTypeCombo;
    
    SelectModifier    *mSelect;
    TranslateModifier *mTrans;
    RotateModifier    *mRot;
    ScaleModifier     *mScale;

    void setActiveButton( QToolButton *activeButton );

  private slots:
    void buttonClicked();
    void setName(const QString &name);
    void setTrans();
    void setRot();
    void setScale();
    void fitScale();
    void setDeg(bool on);
    void setRad(bool on);
    void updateData( MModifier::ModifierType mType, Vector3f v );
    void enableInput( bool yes );

  public slots:
    void setDefaultModifier();
    void setModifier( MModifier::ModifierType mType );
    void setSelected(QPtrList<ViMultiPolyh> *selectedList);

  signals:
    void sendModifier(MModifier *modifier);
    void modifierChoosed();
    void nameChanged();
};







#endif
