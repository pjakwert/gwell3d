#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <qwidget.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qtoolbutton.h>
#include <qhbox.h>
#include <qspinbox.h>
#include <qgroupbox.h>
#include <qcolordialog.h>
#include <qfiledialog.h>
#include <qtooltip.h>
#include <qlayout.h>
#include <qapplication.h>

#include <options.h>
#include <cellframe.h>


class OptionsWidget : public QWidget
{
  Q_OBJECT

  public:
    OptionsWidget( QString title, QWidget *parent=0, const char *name=0 );
    ~OptionsWidget() {}

  private:
    QStringList _langList;
    //////////////////////////////////////// GUI
    QGridLayout *globalGrid;
     QGroupBox   *mainGroupBox;
     QGridLayout *mainGrid;
     
     QGroupBox*   dirBox;
      QLabel*      libsLabel;
      QLineEdit*   libsEdit;
      QToolButton* libsButton;
      QLabel*      mphLabel;
      QLineEdit*   mphEdit;
      QToolButton* mphButton;
      QLabel*      scenesLabel;
      QLineEdit*   scenesEdit;
      QToolButton* scenesButton;
      QLabel*      matLabel;
      QLineEdit*   matEdit;
      QToolButton* matButton;
      QLabel*      imgLabel;
      QLineEdit*   imgEdit;
      QToolButton* imgButton;
      QLabel*      langLabel;
      QLineEdit*   langEdit;
      QToolButton* langButton;
     QGroupBox*   colorBox;
      QLabel*      bkgLabel;
      QToolButton* bkgButton;
      QLabel*      wireLabel;
      QToolButton* wireButton;
      QLabel*      wireSelLabel;
      QToolButton* wireSelButton;
      QLabel*      solidLabel;
      QToolButton* solidButton;
      QLabel*      solidSelLabel;
      QToolButton* solidSelButton;
      QLabel*      gridLabel;
      QToolButton* gridButton;
      QLabel*      grid3DLabel;
      QToolButton* grid3DButton;
      QLabel*      lightsLabel;
      QToolButton* lightsButton;
      QLabel*      frameLabel;
      QToolButton* frameButton;
      QLabel*      infoLabel;
      QToolButton* infoButton;
     QGroupBox*   renderBox;
      QLabel*      shadeLabel;
      QComboBox*   shadeCombo;
      QLabel*      corrLabel;
      QComboBox*   corrCombo;
     QGroupBox*    othersBox;
      QLabel*      decLabel;
      QSpinBox*    decSpin;
      QLabel*      lngLabel;
      QComboBox*   langCombo;
     QGroupBox*    setBox;
      QPushButton* saveButton;
      QPushButton* restoreButton;
      QPushButton* resetButton;
    //////////////////////////////////////// GUI
    
    private slots:
      void refresh();
      void chooseDirectory();
      void chooseColor();
      void shadeChanged( int );
      void corrChanged( int );
      void decChanged( int );
      void langChanged( int );
      void fillLangCombo( const QString& path );
      void setTranslator( const QString& fileName );
      void saveSettings();
      void restoreSettings();
      void resetToDefaults();
};







#endif
