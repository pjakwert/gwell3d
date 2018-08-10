#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include <qwidget.h>
#include <qgroupbox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtextedit.h>
#include <qapplication.h>
#include <qmessagebox.h>

#include <icons.h>
#include <helpstring.h>


class HelpWidget : public QWidget
{
  Q_OBJECT

  public:
    HelpWidget(QString title, QWidget *parent=0, const char *name=0);
    ~HelpWidget() {}

  private:
    QGridLayout *mainGrid;
    QGridLayout *grid;
    QGroupBox   *groupBox;
    QTextEdit   *infoText;
    QPushButton *aboutQTButton;
    QPushButton *aboutAppButton;
    
  private slots:
    void aboutApp();
};





#endif
