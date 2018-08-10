#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <qgroupbox.h>
#include <qtoolbox.h>
#include <qlayout.h>

#include <kernel.h>
#include <glmenuitem.h>
#include <glmenu.h>
#include <glmphmenuitem.h>
#include <glmphmenu.h>
#include <icons.h>
#include <options.h>
#include <cellframe.h>



class DrawWidget : public QWidget
{
  Q_OBJECT

  public:
    DrawWidget(QString title, QWidget *parent=0, const char *name=0);
    ~DrawWidget() {}

  private:
    QGroupBox   *groupBox;
    QGridLayout *mainGrid;
    QToolBox    *toolBox;

    void clearToolBox();
    ViScene     *_scene;

  private:
    int  loadMphs( QStringList* paths, ViScene* scene );
    void loadFromDir( QString dirPath, int &count );

  private slots:
    void objectItemSelected( const char *objectName );
    void multiPolyhSelected( const char* mphPath );
      
  public slots:
    void setScene( ViScene *scene );

  signals:
    void objectSelected( const char *objectName );
    void addMultiPolyh( const char* mphPath, ViNTreeNode* parent );
};





#endif
