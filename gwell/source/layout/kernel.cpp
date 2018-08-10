#include "kernel.h"


ViScene* Kernel::_scene = new ViScene;

void Kernel::computeScene()
{
  _scene->ComputeGlbVtx();
}


Kernel::Kernel(QWidget *parent) : QObject(parent)
{
  _count = 0;
}


Kernel::~Kernel()
{
  _scene->DeleteAllMultiPolyh(); // usuñ wszystko ze sceny
  delete _scene;
}




/*!
Metoda inicjuje caly kernel. Wczytuje wszystkie biblioteki z podanego katalogu (wykorzystuje
metode readAllLibraries()).
Powinna byc wywolywana od razu po utworzeniu obiektu Kernel.
*/
void Kernel::init(QString initLibPath)
{
  StatusBar::printStatusMsg(tr("Good day, i'd like to introduce You the Kernel."), "Kernel");
  int k = readAllLibraries(initLibPath);
  if (k < 1) StatusBar::printStatusMsg(tr("No libriaries found in directory: '%1'").arg(initLibPath), "Kernel"); 
        else
        {
          StatusBar::printStatusMsg(tr("Number of read libraries: %1.").arg(k), "Kernel");
          emit sendScene(_scene); // po wczytaniu wszystkich bibliotek, wysyla wskaznik na scene
        }
  
  // poka¿ i ustaw informacjê o maksymalnym rozmiarze tekstury
  GLint val[1];
  glGetIntegerv( GL_MAX_TEXTURE_SIZE, val);
  StatusBar::printStatusMsg( tr("Maximum texture size for Your OpenGL implementation = %1x%2").arg(val[0]).arg(val[0]), "Kernel" );
  TextureManager::setSafeSize( val[0] );
  TextureManager::setSafeMode( true );
  
  emit sendScene( _scene );
}


/*!
Metoda laduje wszystkie biblioteki znajdujace sie w podanym katalogu.
Biblioteki sa ladowane kolejno wedlug nazwy pliku.
\param path - katalog zawierajacy biblioteki bryl (pliki *.lib)
\return ilo¶æ znalezionych/wczytanych bibliotek lub: -1 gdy katalog nie istnieje, -2 katalog jest pusty
*/
int Kernel::readAllLibraries( QString path )
{
  QDir dir(path); // katalog do przeszukania

  if (!dir.exists()) return -1; // katalog nie istnieje

  dir.setFilter(QDir::Files | QDir::Hidden); // interesuja nas tylko pliki (takze ukryte)
  dir.setNameFilter("*.lib *.LIB *.Lib"); // obslugiwane rozszerzenia
  dir.setSorting(QDir::Name); // znalezione pliki sortowane wedlug nazwy

  const QFileInfoList *list = dir.entryInfoList(); // lista znalezionych plikow
  QFileInfoListIterator iter (*list);              // iterator ww. listy
  QFileInfo *fileInfo;                             // dane znalezionego pliku

  int i=0;
  int err;
  ExtString errMsg;
  ExtString libName;
  QString name;

  while ((fileInfo = iter.current()) != 0)
  {
    i++;
    name = dir.filePath(fileInfo->fileName()); // name = path+fileName
    err = _scene->ReadPatteLib(name.ascii(), errMsg, &libName);  // parsowanie biblioteki
    if (err)
     { StatusBar::printStatusMsg(tr("Error reading library from '%1': %2.").arg(name).arg(errMsg.c_str()), "Kernel"); i--; }
    else 
     StatusBar::printStatusMsg(tr("Library \"%1\" read successfully from '%2'.").arg(libName.c_str()).arg(name), "Kernel");
    ++iter;
  }

  if (i==0) return -2; // katalog pusty
  
  return i; // zwraca ilo¶æ poprawnie wczytanych bibliotek
}



// funkcja tworzenia nowych obiektów dziedziczonych klas
ViNTreeNode* kernelCreateFunction( const char *className )
{
  if ( strcmp( "ViElemePolyhExt", className ) == 0 ) return new ViElemePolyhExt;
  if ( strcmp( "ViMultiPolyh", className ) == 0 ) return new ViMultiPolyhExt();
  return 0;
}  



// dodaje nowy mph, zadaje transformacje, nie wysy³a sceny
void Kernel::addMultiPolyh( const char *pathToMph, const char* mphName, const Vector3f& trans, const Vector3f& rotDeg, const Vector3f& scale )
{
  ViMultiPolyhExt* mp = readMultiPolyh( pathToMph );
  if ( mp == 0L ) return;
  
  MatrixH3f m = mp->Mtx2ParentCoord();
  m.SetTrans_TAfterR( trans );
  m.SetAng_XYZ_TAfterR_Deg( rotDeg );
  m.SetScale_TAfterR( scale );
  mp->SetMtx2ParentCoord( m );
  
  // je¿eli obiekt ma inn± indywidualn± nazwê
  if ( strcmp( mphName, mp->NodeName() ) != 0 )
  {
    // nadajmy mu nazwê w³asn±, ale jezeli istnieje ju¿ obiekt o takiej nazwie - zmieniaj nazwê do bólu
    bool found;
    QString name( mphName );
    do
    {
      found = false;
      for ( ViScene::ConMultiPolyhIter iter = _scene->ConBegin_NormMultiPolyh(); iter; ++iter )
      {
        if ( strcmp( name.ascii(), iter->NodeName() ) == 0 )
        {
          // zmieñ nazwê (dodaj podkre¶lenie)
          name += "_";
          found = true;
          break;
        }
      }
    } while ( found );
    mp->SetNodeName( name.ascii() );
  }
}



void Kernel::addMultiPolyh( const char *pathToMph )
{
  ViMultiPolyhExt *mp = readMultiPolyh( pathToMph );
  if ( mp == 0L ) return;
  emit sendScene( _scene ); // po wszystkich operacjach wysy³amy scenê
}


/*!
Metoda dodaje nowy obiekt z³o¿ony do sceny, zwraca wska¼nik do niego lub OL w razie niepowodzenia
*/
ViMultiPolyhExt* Kernel::readMultiPolyh( const char *pathToMph )
{
  QString mphPath( pathToMph );
    
  ViMultiPolyh *newMultiPolyh;
  
  if ( !(QFile::exists( mphPath )) ) // plik nie istnieje, doklejmy ¶cie¿ke z mph
  {
    QFileInfo fi( mphPath );
    QString name = fi.fileName();
    
    /*
    QString p( (Options::mphPaths())->first() );
    QString sl = p.right( 1 ); 
    if ( sl != "/" ) p+="/"; // czy ostatni jest slash
    
    mphPath = p + name; // nowa ¶cie¿ka
    */
    
    mphPath = Tools::search( name, Options::mphPaths() );
  }
  
    
  if ( (QFile::exists( mphPath )) && ( mphPath != QString::null ) )
  {
    // dodaj nowy obiekt do aktualnego
    ViException exception;
    switch ( Vi::ReadMultiPolyh( mphPath.ascii(), *_scene, &newMultiPolyh, exception, kernelCreateFunction ) )
    //switch ( Vi::ReadMultiPolyh( pathToMph, *_scene, Vi::LT_Norm, exception, kernelCreateFunction ) )
    {
      case 0 : {
                  StatusBar::printStatusMsg( tr("MultiPolyhedron added succesfully from file '%1'.").arg(mphPath), "Kernel" ); 
              } break;
      case -1 : {
                  StatusBar::printStatusMsg( tr("Error reading file '%1'.").arg(mphPath), "Kernel" );
                  StatusBar::printStatusMsg( tr("ErrorMsg: %1").arg(exception.GetErrMsg()), "Kernel" );
                } return 0L;
      case -2 : {
                  StatusBar::printStatusMsg( tr("Error reading file '%1'.").arg(mphPath), "Kernel" );
                  StatusBar::printStatusMsg( tr("ErrorMsg: %1").arg(exception.GetErrMsg()), "Kernel" );
                } return 0L;
      default : {
                  StatusBar::printStatusMsg( tr("Error adding mph: '%1'.").arg(mphPath), "Kernel" );
                } return 0L;
    } // switch
    
    ViMultiPolyhExt *nm = (ViMultiPolyhExt*) newMultiPolyh;
    nm->setFileName( mphPath );
    
    nm->ComputeHierAllGlbVtx();
    
    // jezeli istnieje ju¿ obiekt o takiej nazwie - zmieniaj nazwê do bólu
    bool found;
    QString name( nm->NodeName() );
    do
    {
      found = false;
      for ( ViScene::ConMultiPolyhIter iter = _scene->ConBegin_NormMultiPolyh(); iter; ++iter )
      {
        if ( strcmp( name.ascii(), iter->NodeName() ) == 0 )
        {
          // zmieñ nazwê (dodaj podkre¶lenie)
          name += "_";
          found = true;
          break;
        }
      }
    } while ( found );
    nm->SetNodeName( name.ascii() );
    
    _scene->AddNormMultiPolyh( nm );
    _scene->ComputeGlbVtx();
    
    return nm;
  }
  else { StatusBar::printStatusMsg( tr("File '%1' not found.").arg(pathToMph), "Kernel" ); return 0L; }
}
  
