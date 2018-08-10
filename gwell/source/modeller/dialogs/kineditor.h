#ifndef KINEMATICS_EDITOR_H
#define KINEMATICS_EDITOR_H

#include <qlabel.h>
#include <qlineedit.h>
#include <qtoolbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qframe.h>
#include <qpushbutton.h>


#include <kernel.h>
#include <cellframe.h>
#include <table.h>
#include <icons.h>
#include <knob.h>


class KinematicsEditor : public QDialog
{
  Q_OBJECT
  
  public:
    KinematicsEditor(QPtrList<ViNTreeNode> *selectedList, QWidget *parent=0, const char *name=0, bool modal=true, WFlags fl=WType_Dialog | WDestructiveClose);
    ~KinematicsEditor() {}
    
  private:
    ViMultiPolyh *_multiPolyh;
    QPtrList<ViNTreeNode> *_selectedList;
    QGridLayout *mainGrid;
    QFrame      *mainFrame;
    QGridLayout *frameGrid;
    QLabel      *obLabel;
    QLineEdit   *obEdit;
    Table       *table;
    QToolButton *addButton;
    QToolButton *removeButton;
    Knob        *knob;
    QPushButton *okButton;
    
  private slots:
    void addCtrlItem();
    void updateView();
    void updateView(double);
    
  protected:
    void keyPressEvent( QKeyEvent* );

};



#endif
