#include "drawwidget.h"



// konstruktor
DrawWidget::DrawWidget(QString title, QWidget *parent, const char *name) : QWidget(parent, name)
{
    mainGrid = new QGridLayout(this, 1,1, 0,0);
    
    groupBox = new QGroupBox(1, Qt::Horizontal, this);
    groupBox->setTitle(title); // tytul widgeta
    toolBox = new QToolBox(groupBox);

    mainGrid->addWidget(groupBox, 0,0);
}



// usuwa wszystkie widgety z toolBoxa i czysci liste zawierajaca widoki bryl
void DrawWidget::clearToolBox()
{
  for (int i=0; i<(toolBox->count()); i++)
  {
   toolBox->removeItem(toolBox->item(i));
  }
}


// metoda �aduje obiekty z�o�one z podanego katalogu
void DrawWidget::loadFromDir( QString dirPath, int &count )
{
  QDir dir( dirPath );
  if ( !dir.exists() ) return;
  
  //if ( dirPath.right( 1 ) == QString("/") ) dirPath.remove( dirPath.length()-1, 1 );
  
  QString name;
  
  // teraz przegl�damy pliki, tworzymy kontener dla katalogu i �adujemy je
  QDir files( dirPath );
  files.setFilter( QDir::Files | QDir::Hidden ); // tylko pliki
  files.setNameFilter("*.mph *.MPH *.Mph"); // obs�ugiwane rozszerzenia  
  files.setSorting( QDir::Name );
  
  QDir dirs( dirPath );
  dirs.setFilter( QDir::Dirs ); // tylko katalogi
  dirs.setSorting( QDir::Name );
  QFileInfoListIterator it( *(dirs.entryInfoList()) );
  QFileInfo *dirInfo;
  
  if ( !dirs.entryInfoList()->isEmpty() )
  {
    while ( (dirInfo = it.current()) != 0 )
    {
      if ( (dirInfo->fileName() != ".") && (dirInfo->fileName() != "..") )  // rekursywne przeszukiwanie
        loadFromDir( dirInfo->absFilePath(), count );
      
      ++it;
    }
  }
  
  
  if ( (files.entryInfoList())->isEmpty() ) return;
  
  // tworzymy widget-kontener
  int i = count;
  GLMphMenu *mphMenu = new GLMphMenu( toolBox, files.entryInfoList(), count );
  // do toolboxa dodajemy tylko wtedy, je�eli wczytane zosta�y jakie� obiekty
  if ( count != i )
  {
    connect( mphMenu, SIGNAL( mphSelected(const char*)), this, SLOT(multiPolyhSelected(const char*)) );
    toolBox->addItem( mphMenu , QIconSet(QPixmap(Icons::showAllSceneIcon())), dirPath.section('/',-2,-1) );
    // etykiet� s� dwa podkatalogi
  }
}



// metoda �aduje bry�y z�o�one z podanych �cie�ek do menu
// musi by� wywo�ywana po za�adowaniu bry� elementarnych do sceny
//  zwraca ilo�� wczytanych obiekt�w z�o�onych
int DrawWidget::loadMphs( QStringList* paths, ViScene *scene )
{
  if ( paths == 0L || scene == 0L ) return 0;
  
  int count = 0; // liczba wczytanych MPH
  
  // iterator dla wszystkich �cie�ek
  for ( QStringList::Iterator it = paths->begin(); it != paths->end(); ++it )
  {
    loadFromDir( *it, count ); // ka�d� �cie�k� przeszukujemy wg��b
  }
  
  return count;
}




// ustawia obslugiwana scene, w szczegolnosci chodzi o dostep do zaladowanych przez Kernel bryl elementarnych
// tworzy zakladki toolBoxa z elementami bibliotek
void DrawWidget::setScene( ViScene *scene )
{
  _scene = scene;

  clearToolBox();

  GLMenu *menu;
  
  for (ViScene::ConLibIterator libIter = _scene->ConBegin_Lib(); libIter; libIter++)
  {
       //printf("biblioteka %s\n", libIter->GetLibName());
       menu = new GLMenu(toolBox, libIter);
       connect(menu, SIGNAL(objectSelected(const char*)), this, SLOT(objectItemSelected(const char*)));
       toolBox->addItem(menu , QIconSet(QPixmap(Icons::pyramidIcon())), QString(libIter->GetLibName()));
  }
  
  int i = loadMphs( Options::mphPaths(), scene );
  if ( i==0 ) StatusBar::printStatusMsg( tr("No MultiPolyhedrons readed.").arg(i), "Kernel" );
  else if ( i==1 ) StatusBar::printStatusMsg( tr("1 MultiPolyhedron readed successfully.").arg(i), "Kernel" );
  else StatusBar::printStatusMsg( tr("%1 MultiPolyhedrons readed successfully.").arg(i), "Kernel" );
}




// slot przekazujacy dalej sygnal z GLMenu o wybranym obiekcie
void DrawWidget::objectItemSelected(const char *objectName)
{
  emit objectSelected( objectName );
}


// slot przekazuje dalej sygna� o wybraniu z GLMphMenu obiektu z�o�onego
void DrawWidget::multiPolyhSelected( const char* mphPath )
{
  ViNTreeNode* parent = 0L;
  if ( !((CellFrame::selected())->isEmpty()) ) parent = (CellFrame::selected())->last();
      
  emit addMultiPolyh( mphPath, parent );
}
