#ifndef FILEWIDGET_H
#define FILEWIDGET_H

#include <qwidget.h>
#include <qgroupbox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qfile.h>

#include <icons.h>
#include <options.h>
#include <workspace.h>
#include <mphpreview.h>


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
    bool newMultiPolyh();
    void saveMultiPolyh();
    void openMultiPolyh();
    void exit();
    
  signals:
    void loadMultiPolyh( const char* fileName );
    void setMultiPolyh( ViMultiPolyh* mp );
    void setFileCaption( const QString& ); // sygna³ zawieraj±cy znak tytu³ g³ównego widgetu
};







#endif
