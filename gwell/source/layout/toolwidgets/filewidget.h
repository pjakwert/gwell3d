#ifndef FILEWIDGET_H
#define FILEWIDGET_H

#include <qwidget.h>
#include <qgroupbox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qfile.h>
#include <qdom.h>

#include <const.h>
#include <icons.h>
#include <options.h>
#include <workspace.h>
#include <fogwidget.h>
#include <lightswidget.h>


class FileWidget : public QWidget
{
  Q_OBJECT

  public:
    FileWidget(QString title, QWidget *parent=0, const char *name=0);
    ~FileWidget() {}

  private:
    QGridLayout *grid;
    QGroupBox   *groupBox;
    QPushButton *newFileButton;
    QPushButton *openFileButton;
    QPushButton *saveFileButton;
    QPushButton *exitButton;

  private slots:
    bool newScene();
    void saveScene();
    void openScene();
    void exit();
    int saveSceneToFile( QString& fileName );
    int loadSceneFromFile( QString& fileName );
     int readLighting( QDomElement elem );
     int readFog( QDomElement elem );
     //int readShadows( QDomElement elem );
     int readElements( QDomElement elem );
    
  signals:
    void addMultiPolyh( const char* fileName, const char* name, const Vector3f& trans, const Vector3f& rotDeg, const Vector3f& scale );
    void setScene( ViScene* scene ); // wysy³a sygna³ o nowej scenie
    void setFileCaption( const QString& ); // sygna³ zawieraj±cy znak tytu³ g³ównego widgetu
    
    void setLightingEnabled( bool );
    void clearAllLights();
    void addLight( Light *light );
    void updateFog();
};







#endif
