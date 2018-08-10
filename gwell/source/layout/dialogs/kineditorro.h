#ifndef KINEMATICS_EDITOR_RO_H
#define KINEMATICS_EDITOR_RO_H

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


/*!
Klasa implementuje dialog do osb�ugi interfejsu sterowania. Od klasy KinematicsEditor r�ni si� tym,
�e w�a�ciwo�ci element�w interfejsu nie mog� by� modyfikowane.
*/
class KinematicsEditorRO : public QDialog
{
  Q_OBJECT
  
  public:
    KinematicsEditorRO(QPtrList<ViMultiPolyh> *selectedList, QWidget *parent=0, const char *name=0, bool modal=true, WFlags fl=WType_Dialog | WDestructiveClose);
    ~KinematicsEditorRO() {}
    
  private:
    ViMultiPolyh *_multiPolyh;
    QPtrList<ViMultiPolyh> *_selectedList;
    QGridLayout *mainGrid;
    QFrame      *mainFrame;
    QGridLayout *frameGrid;
    QLabel      *obLabel;
    QLineEdit   *obEdit;
    Table       *table;
    Knob        *knob;
    QPushButton *okButton;
    
  private slots:
    void updateView();
    void updateView(double);
    
  protected:
    void keyPressEvent( QKeyEvent* );

};



#endif
