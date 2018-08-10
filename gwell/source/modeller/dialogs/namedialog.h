/////////////////////////////////////////////////////////////////////////
///
///  class: NameDialog (.h)
///
///  dialog do wpisania nazwy materia?u (lub czegokolwiek innego)
///
/////////////////////////////////////////////////////////////////////////
/// stosowanie jako MODAL:
///
///   NameDialog *dlg = new NameDialog(...)
///    QString name;
///   if (dlg->exec() == QDialog::Accepted) name=dlg->name();
///   delete dlg;
/////////////////////////////////////////////////////////////////////////


#ifndef NAMEDIALOG_H
#define NAMEDIALOG_H

#include <qdialog.h>
#include <qlabel.h>
#include <qfont.h>
#include <qstring.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>

/*!
Prosta klasa implementuj±ca dialog do wpisania ci±gu znakowego.
*/
class NameDialog : public QDialog
{
  Q_OBJECT
  public:
    NameDialog(QString title, QString info, QWidget *parent=0, const char *name=0, bool modal=TRUE, WFlags fl=0);
    ~NameDialog();
    QString name();
  private:
    QLabel *infoLabel;
    QLineEdit *nameEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QGridLayout *grid;
};

#endif
