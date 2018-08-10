#ifndef CELLWIDGET_H
#define CELLWIDGET_H

#include <qpixmap.h>
#include <qwidget.h>
#include <qframe.h>
#include <qtoolbutton.h>
#include <qcombobox.h>
#include <qlayout.h> 
#include <qtooltip.h>

#include <QGLViewer/qglviewer.h>
#include <const.h>
#include <icons.h>



class CellWidget : public QFrame
{
  Q_OBJECT

  public:
    CellWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CellWidget() {}

    QToolButton *showAllButton;
    QToolButton *cameraButton;
    QToolButton *showGridButton;
    QToolButton *showBoxesButton;
    QToolButton *showAxisButton;
    QToolButton *showLightsButton;
    QComboBox   *viewDirCombo;
    QComboBox   *viewTypeCombo;
    QComboBox   *viewProjCombo;
    QToolButton *screenshotButton;
    QToolButton *maximizeButton;

  public slots:
    void toggleVisibility();
    void hidePrivateButtons();

  private slots:
    void cameraToggled(bool on);
    void showAll();
    void gridToggled(bool on);
    void axisToggled(bool on);
    void boxesToggled( bool on );
    void lightsToggled( bool on );
    void viewDirChanged(int direction);
    void viewTypeChanged(int viewType);
    void viewProjChanged(int viewProj);
    void screenshotClicked();
    void maximizeClicked();

  signals:
    void moveCamera(bool on);
    void showEntireScene();
    void showGrid(bool on);
    void showAxis(bool on);
    void showBoxes( bool on );
    void showLights( bool on );
    void viewDirectionChanged(int direction);
    void setViewType( DrawMethod type);
    void setProjType( qglviewer::Camera::Type type );
    void makeScreenshot();
    void maximize();
};


#endif
