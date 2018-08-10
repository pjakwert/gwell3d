//////////////////////////////////////////////////////////////////
///
///  class: ObjectsWidget (.h)
///
///  widget zawieraj±cy ObjectExplorer-a
///
//////////////////////////////////////////////////////////////////
#ifndef OBJECTSWIDGET_H
#define OBJECTSWIDGET_H

#include <qwidget.h>
#include <qgroupbox.h>
#include <qbuttongroup.h>
#include <qtoolbutton.h>
#include <qlayout.h>
#include <qlistview.h>
#include <qlineedit.h>

#include <kernel.h>
#include <icons.h>
#include <hierlistviewitem.h>
#include <cellframe.h>


class ObjectsWidget : public QWidget
{
  Q_OBJECT

  public:
    ObjectsWidget(QString title, QWidget *parent=0, const char *name=0);
    ~ObjectsWidget() {}

  private:
    ViScene                   *_scene;         // scena
    QPtrList<ViMultiPolyh> *_selectedList; // lista zaznaczonych obiektów
    
    QGridLayout *globalGrid;
    QGroupBox   *mainBox;
     QListView *listView;
     QLineEdit *addrEdit;
     
  private slots:
    void buildList();
    void expandAll();
    void collapseAll();
    void showSelectedList();
    void buildSelectedList();
    void setAddrEditPath( QListViewItem *item );
    
  public slots:
    void setSelectedList( QPtrList<ViMultiPolyh> *selectedList );
    void setRoot( ViScene* scene );
    void update();
    
  signals:
    void selectionChanged( QPtrList<ViMultiPolyh> *selectedList );
};







#endif
