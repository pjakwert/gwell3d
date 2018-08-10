#include "filewidget.h"

#define HasDescendants() IsDescendant()

// konstruktor
FileWidget::FileWidget(QString title, QWidget *parent, const char *name) : QWidget(parent, name)
{
    grid = new QGridLayout(this, 1,1, 0,0);
    
    groupBox = new QGroupBox(1, Qt::Horizontal, this);
    groupBox->setTitle(title);
      newFileButton  = new QPushButton(QIconSet(QPixmap(Icons::newIcon())),tr("New..."),   groupBox);
      openFileButton = new QPushButton(QIconSet(QPixmap(Icons::openIcon())),tr("Open..."),  groupBox);
      saveFileButton = new QPushButton(QIconSet(QPixmap(Icons::saveIcon())),tr("Save..."),  groupBox);

      QFrame *frame = new QFrame(groupBox);
      frame->setFrameShape(QFrame::HLine);
      frame->setMinimumHeight(20);
      
      exitButton     = new QPushButton(QIconSet(QPixmap(Icons::exitIcon())),tr("Exit ..."), groupBox);

   grid->addWidget(groupBox, 0,0);

   connect(newFileButton, SIGNAL(clicked()), this, SLOT(newMultiPolyh()));
   connect(openFileButton, SIGNAL(clicked()), this, SLOT(openMultiPolyh()));
   connect(saveFileButton, SIGNAL(clicked()), this, SLOT(saveMultiPolyh()));
   connect(exitButton, SIGNAL(clicked()), this, SLOT(exit()));
}





bool FileWidget::newMultiPolyh()
{
  if (CellFrame::multiPolyh() == 0L) return true;

  if (CellFrame::multiPolyh()->HasDescendants())
  {
    int choice = QMessageBox::question(qApp->mainWidget(),
                                       tr("New"),
                                       tr("Are you sure you want to clear current object?"),
                                       QMessageBox::Yes, QMessageBox::No);
    if (choice == QMessageBox::Yes)
    {
     CellFrame::multiPolyh()->DeleteAllDesc();         // masakra
     CellFrame::multiPolyh()->SetName( "MainObject" );
     CellFrame::selected()->clear();
     //Workspace::resetAllFrames();
     CellFrame::refresh();
     emit setMultiPolyh( CellFrame::multiPolyh() );
     QString s(APPNAME);
     emit setFileCaption( s );
     return true; // wyczyszczono
    }
    
    return false; // user nie zgodzi³ siê na czyszczenie
    
  }
  return true;
}




void FileWidget::saveMultiPolyh()
{
  // jezeli scena jest pusta
  if (CellFrame::multiPolyh() == 0L)
  {
    QMessageBox::information(qApp->mainWidget(), tr("Save to file"), tr("There's nothing to save."));
    return; 
  }
  if (!CellFrame::multiPolyh()->HasDescendants())
  {
    QMessageBox::information(qApp->mainWidget(), tr("Save to file"), tr("There's nothing to save."));
    return;
  }
  
  QString fileName = QFileDialog::getSaveFileName(
                                                   Options::mphPaths()->first(),
                                                   tr("Complex Polyhedron files (*.mph *.MPH *.Mph )"),
                                                   qApp->mainWidget(),
                                                   tr("Choose filename to save Your object")
                                                  ); 

  if ( fileName != QString::null ) // czy uzytkownik nie klepnal Cancel
  {
    // czy wpisal rozszerzenie? jesli nie - dodaj je
    if (fileName.right(4) != ".mph") fileName+=".mph";

    if (QFile::exists(fileName))
    {
      int choice = QMessageBox::question(qApp->mainWidget(),
                                         tr("Save to File"),
                                         tr("File '%1' already exists.\nDo you want to overwrite it?").arg(fileName),
                                         QMessageBox::Yes, QMessageBox::No);
      if (choice == QMessageBox::No) return;
    }
    
    int errNo = CellFrame::multiPolyh()->WriteMultiPolyhToFile(fileName.ascii()); // zapisz do pliku
    QString info;
    
    switch (errNo)
    {
      case 0  : {
                  info = tr("Object written successfully to file:\n'%1'").arg(fileName); 
                  QString s = QString("%1 - %2").arg(APPNAME).arg(fileName);
                  emit setFileCaption( s );
                } break;
      case -1 : info = tr("Unable to write to file:\n'%1'").arg(fileName); break;
      case -2 : info = tr("Creating object's description failed."); break;
      default : info = tr("Unknown write error."); break;
    }

    if (errNo == 0) QMessageBox::information(qApp->mainWidget(), tr("Save to file"), info);
    else QMessageBox::critical(qApp->mainWidget(), tr("Save to file"), info);

  }                                                 
}




void FileWidget::openMultiPolyh()
{
  if ( !newMultiPolyh() ) return; // najpierw czy¶cimy wszystko o ile co¶ jest i user pozwoli
  
  MphPreview *prev = new MphPreview;
  
  QFileDialog *fileDialog = new QFileDialog(
                                             Options::mphPaths()->first(),
                                             tr("Complex Polyhedron files (*.mph *.MPH *.Mph)"),
                                             qApp->mainWidget()
                                           );
  
  fileDialog->setCaption( tr("Choose filename to save Your object") );
  fileDialog->setContentsPreviewEnabled( true );
  fileDialog->setContentsPreview( prev, prev );
  fileDialog->setPreviewMode( QFileDialog::Contents );
  
  QString fileName;
  
  if ( fileDialog->exec() == QDialog::Accepted ) fileName = fileDialog->selectedFile();
  else return; // CANCEL pressed
  
  if ( fileName != QString::null ) // je¿eli u¿ytkownik nie klepn±³ Cancel
  {
    QString s = QString("%1 - %2").arg(APPNAME).arg(fileName);
    emit setFileCaption( s );
    // wczytaj mp
    emit loadMultiPolyh( fileName.ascii() );
  }
}





void FileWidget::exit()
{
  int choice = QMessageBox::question(qApp->mainWidget(),
                                     tr("Quit"),
                                     tr("Are you sure you want to quit? (i will try harder ;)"),
                                     QMessageBox::Yes, QMessageBox::No);
  if (choice == QMessageBox::Yes) qApp->quit();
}

