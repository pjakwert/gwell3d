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
#include <listview.h>


class ObjectsWidget : public QWidget
{
  Q_OBJECT

  public:
    ObjectsWidget(QString title, QWidget *parent=0, const char *name=0);
    ~ObjectsWidget() {}

  private:
    ViMultiPolyh              *_root;         // g³ówny obiekt z³o¿ony sceny - korzeñ
    QPtrList<ViNTreeNode> *_selectedList; // lista zaznaczonych obiektów
    
    QGridLayout *globalGrid;
    QGroupBox   *mainBox;
     QButtonGroup  *buttonGroup;
      QToolButton  *treeViewButton;
      QToolButton  *pathsViewButton;
     ListView *listView;
     QLineEdit *addrEdit;
    QPopupMenu *popup;
     
     QListViewItem* findChild( const QListView* list, const QString& text );
     QListViewItem* findChild( const QListViewItem* parent, const QString& text );     
  
  private slots:
    void buildTree();
    void buildPaths();
    void viewToggled( int buttonID );
    void showSelectedList();
    void buildSelectedList();
    void setAddrEditPath( QListViewItem *item );
    
  public slots:
    void setSelectedList( QPtrList<ViNTreeNode> *selectedList );
    void setRoot( ViMultiPolyh* root );
    void update();
    
  signals:
    void selectionChanged( QPtrList<ViNTreeNode> *selectedList );
};







#endif
