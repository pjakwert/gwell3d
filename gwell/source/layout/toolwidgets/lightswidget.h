#ifndef LIGHTSWIDGET_H
#define LIGHTSWIDGET_H

#include <qwidget.h>
#include <qgroupbox.h>
#include <qlayout.h>
#include <qhbox.h>
#include <qtoolbutton.h>
#include <qpopupmenu.h>
#include <qtable.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qtabwidget.h>
#include <qgrid.h>
#include <qvalidator.h>

#include <colorwidget.h>
#include <cellframe.h>
#include <lightstablewidget.h>
#include <options.h>
#include <m_translightpos.h>
#include <m_translightdir.h>


class LightsWidget : public QWidget
{
  Q_OBJECT

  public:
    LightsWidget( QString title, QWidget *parent=0, const char *name=0 );
    ~LightsWidget() {};
    static bool lightingEnabled() { return _lightingEnabled; }

  private:
    QPtrList<Light>* _lightsList;
    Light*           _currentLight;
    int              _decimals;
    static bool      _lightingEnabled;
    
    // modyfikatory
    TranslateLightPosModifier* posModifier;
    TranslateLightDirModifier* dirModifier;
    
//----------------------------------------- GUI    
    QGroupBox*    mainGroupBox;
    QGridLayout*  mainGrid;
    QSpacerItem*  upperSpace;
    
    QHBox*        addAndDeleteBox;
     QToolButton* addLightButton;
      QPopupMenu* addLightPopup;
     QToolButton* deleteLightButton;
    
    LightsTableWidget* lightsTable;
    
    QHBox*        moveButtonsBox;
     QToolButton* transLightButton;
     QToolButton* changeDirectionButton;
    
    QGroupBox*    paramsBox;
    QGridLayout*  paramsGrid;
    QSpacerItem*  pSpacer;
     QLabel*      lightIsLabel;
      QComboBox*  lightTypeCombo;
     QLabel*      positionLabel;
      QHBox*      positionBox;
       QLabel*    xPosLabel;
       QLineEdit* xPosEdit;
       QLabel*    yPosLabel;
       QLineEdit* yPosEdit;
       QLabel*    zPosLabel;
       QLineEdit* zPosEdit;
     QLabel*      directionLabel;
      QHBox*      directionBox;
       QLabel*    xDirLabel;
       QLineEdit* xDirEdit;
       QLabel*    yDirLabel;
       QLineEdit* yDirEdit;
       QLabel*    zDirLabel;
       QLineEdit* zDirEdit; 
     QLabel*      attLabel;
      QGrid*      attGrid;
       QLabel*    linearLabel;
       QLabel*    constLabel;
       QLabel*    quadLabel;
       QLineEdit* linearEdit;
       QLineEdit* constEdit;
       QLineEdit* quadEdit;
     QHBox*       expAndCutOffBox;
      QLabel*     expLabel;
      QLineEdit*  expEdit;
      QLabel*     cutOffLabel;
      QLineEdit*  cutOffEdit;
     QCheckBox*   movingWithCameraCheck;
       
    QTabWidget*   colorsTabWidget;
     ColorWidget* ambientWidget;
     ColorWidget* diffuseWidget;
     ColorWidget* specularWidget;
     
    QSpacerItem*  spacer;
//----------------------------------------- GUI   
  
  private slots:
    void lightsToggled( bool on );
    void currentLightChanged( Light* light );
    void lightParamsChanged( Light* light );
    void updateLightForWorkspace( const QColor&, int );
    void setAllParamsEnabled( bool yes );
    void updateWorkspace();
    void setLightTypeFromCombo(int);
    void setAllParamsFromEdits();
    void setMovingWithCamera( bool yes );
    void updateData( MModifier::ModifierType mType, Vector3f v );
    void transLightToggled( bool );
    void changeDirToggled( bool );
    
  public slots:
    void disableModifiers();
    void turnModifiersButtonsOff();
    void setModifier( MModifier::ModifierType mType );
    
    void enableLighting( bool yes ) { lightsToggled( yes ); }
    void clearAllLights() { lightsTable->deleteAllLights(); }
    void addLight( Light* light ) { lightsTable->addLight( light ); }
    
  protected:
    //virtual void showEvent( QShowEvent* );
    //virtual void hideEvent( QHideEvent* );
    
  signals:
    void setLightingEnabled( bool yes );
    void setLightEnabled( GLenum light, bool yes );
    void setLight( Light* );
    void setLightsList( QPtrList<Light>* );
    void updateLightColor( GLenum GLwhichColor, Light* _currentLight );
    //void showLightShapes( bool yes );
    
    void sendModifier( MModifier *modifier );
    void setDefaultModifier();
};







#endif
