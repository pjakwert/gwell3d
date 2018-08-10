#include "drawwidget.h"



// konstruktor
DrawWidget::DrawWidget(QString title, QWidget *parent, const char *name) : QWidget(parent, name)
{
    mainGrid = new QGridLayout(this, 1,1, 0,0);
    
    groupBox = new QGroupBox(1, Qt::Horizontal, this);
    groupBox->setTitle(title); // tytul widgeta
    toolBox = new QToolBox(groupBox);

    mainGrid->addWidget(groupBox, 0,0);
    
    _scene = 0L;
}



// usuwa wszystkie widgety z toolBoxa i czysci liste zawierajaca widoki bryl
void DrawWidget::clearToolBox()
{
  for (int i=0; i<(toolBox->count()); i++)
  {
   toolBox->removeItem(toolBox->item(i));
  }
}


// metoda ³aduje obiekty z³o¿one z podanego katalogu
void DrawWidget::loadFromDir( QString dirPath, int &count )
{
  QDir dir( dirPath );
  if ( !dir.exists() ) return;
  
  QString name;
  
  // teraz przegl±damy pliki, tworzymy kontener dla katalogu i ³adujemy je
  QDir files( dirPath );
  files.setFilter( QDir::Files | QDir::Hidden ); // tylko pliki
  files.setNameFilter("*.mph *.MPH *.Mph"); // obs³ugiwane rozszerzenia  
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
  // do toolboxa dodajemy tylko wtedy, je¿eli wczytane zosta³y jakie¶ obiekty
  if ( count != i )
  {
    connect( mphMenu, SIGNAL( mphSelected(const char*)), this, SLOT(multiPolyhSelected(const char*)) );
    toolBox->addItem( mphMenu , QIconSet(QPixmap(Icons::showAllSceneIcon())), dirPath.section('/',-2,-1) );
    // etykiet± s± dwa podkatalogi
  }
}



// metoda ³aduje bry³y z³o¿one z podanych ¶cie¿ek do menu
// musi byæ wywo³ywana po za³adowaniu bry³ elementarnych do sceny
//  zwraca ilo¶æ wczytanych obiektów z³o¿onych
int DrawWidget::loadMphs( QStringList* paths, ViScene *scene )
{
  if ( paths == 0L || scene == 0L ) return 0;
  
  int count = 0; // liczba wczytanych MPH
  
  // iterator dla wszystkich ¶cie¿ek
  for ( QStringList::Iterator it = paths->begin(); it != paths->end(); ++it )
  {
    loadFromDir( *it, count ); // ka¿d± ¶cie¿kê przeszukujemy wg³±b
  }
  
  return count;
}



// ustawia obslugiwana scene, w szczegolnosci chodzi o dostep do zaladowanych przez Kernel bryl elementarnych
// tworzy zakladki toolBoxa z elementami bibliotek
void DrawWidget::setScene( ViScene *scene )
{
  if ( _scene != scene ) // ³aduj wszystko tylko raz (potem zawsze wska¼nik na scenê jest taki sam)
  {
    clearToolBox();

    int i = loadMphs( Options::mphPaths(), scene );
    if ( i==0 ) StatusBar::printStatusMsg( tr("No MultiPolyhedrons readed.").arg(i), "Kernel" );
    else if ( i==1 ) StatusBar::printStatusMsg( tr("1 MultiPolyhedron readed successfully.").arg(i), "Kernel" );
    else StatusBar::printStatusMsg( tr("%1 MultiPolyhedrons readed successfully.").arg(i), "Kernel" );
  }
  
  _scene = scene;
}



// slot przekazuje dalej sygna³ o wybraniu z GLMphMenu obiektu z³o¿onego
void DrawWidget::multiPolyhSelected( const char* mphPath )
{
  emit addMultiPolyh( mphPath );
}

