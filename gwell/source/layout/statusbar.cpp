#include "statusbar.h"



StatusBar::StatusBar(QWidget *parent) : QTextEdit(parent)
{
  this->setReadOnly(true);
  statusBar = this;
}


StatusBar::~StatusBar()
{
}


// STATIC
// zmienna statyczna przechowuje wska¼nik do obiektu, do którego pisane bêd± wiadomo¶ci
StatusBar* StatusBar::statusBar;


// STATIC
// wyswietla informacje w oknie statusu
void StatusBar::printStatusMsg( const QString& msg, const QString& sender )
{
  QString s;
  
  if (sender != QString::null) s += "<B>" + sender + "</B>" + " : ";
   
  s += msg;
  
  statusBar->append(s);
}


// zapisuje cala zawartosc statusu do pliku
// zwraca 1, gdy operacja sie udala, -1 w przeciwnym przypadku
int StatusBar::writeAllToFile(QString fileName)
{
  QFile file(fileName);
  if (file.open(IO_WriteOnly))
  {
    QTextStream stream( &file );
    stream << this->text();
    return 1;
  }
  return -1;
}


// metoda otwiera okno dialogowe do wyboru pliku i uruchamia metode writeAllToFile(QString fileName)
int StatusBar::writeAllToFile()
{
   QString fileName = QFileDialog::getSaveFileName("",
                                                   tr("Text files (*.txt *.log)"),
                                                   this,
                                                   "Save file",
                                                   tr("Save file with application info"));
   if (fileName) return (writeAllToFile(fileName)); else return -1;
}


// kopiuje cala zawartosc statusu do schowka
void StatusBar::copyToClipboard()
{
  selectAll(true);
  copy();
  selectAll(false);
}



// metoda wirtualna definiujaca nowe menu podreczne (popupMenu)
QPopupMenu* StatusBar::createPopupMenu(const QPoint &pos)
{
  QPopupMenu *popup = new QPopupMenu(this);

  popup->insertItem(tr("Write all info to file ..."), this, SLOT(writeAllToFile()));
  popup->insertItem(tr("Copy all to clipboard"), this, SLOT(copyToClipboard()), CTRL+Key_C);

  return popup;
}


