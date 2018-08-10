#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <qstring.h>
#include <qtextedit.h>
#include <qpopupmenu.h>
#include <qfile.h>
#include <qfiledialog.h>



class StatusBar : public QTextEdit
{
  Q_OBJECT

  public:
    StatusBar(QWidget *parent);
    ~StatusBar();
		static void printStatusMsg( const QString& msg, const QString& sender = 0); // metoda dodaje tekst do statusBar-a wskazywanego przez wska¿nik statyczny statusBar
		
	private:
		static StatusBar* statusBar; // zmienna statyczna przechowuje wska¼nik do this

  public slots:
    //void printStatusMsg(QString msg);
    int writeAllToFile();
    int writeAllToFile(QString fileName);
    void copyToClipboard();

  protected:
    virtual QPopupMenu* createPopupMenu( const QPoint &pos ); 
};





#endif
