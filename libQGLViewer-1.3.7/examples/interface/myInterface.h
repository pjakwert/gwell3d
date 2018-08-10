/****************************************************************************
** Form interface generated from reading ui file 'myInterface.ui'
**
** Created: Tue Sep 23 11:32:03 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef FORM1_H
#define FORM1_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QCheckBox;
class QPushButton;
class Viewer;

class myInterface : public QWidget
{ 
    Q_OBJECT

public:
    myInterface( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~myInterface();

    Viewer* Viewer1;
    QCheckBox* CheckBox1;
    QCheckBox* CheckBox3;
    QPushButton* PushButton1;
    QCheckBox* CheckBox2;


protected:
    QGridLayout* Form1Layout;
};

#endif // FORM1_H
