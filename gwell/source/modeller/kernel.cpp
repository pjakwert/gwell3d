#include "kernel.h"


ViScene* Kernel::_scene = new ViScene;

QStringList* Kernel::_pattePolyhList = new QStringList;


/*!
Metoda wykonuje obliczenia globalnych wierzcho³ków sceny.
*/
void Kernel::computeScene()
{
  _scene->ComputeGlbVtx_NormPolyh();
}


Kernel::Kernel(QWidget *parent) : QObject(parent)
{
  _multiPolyh = new ViMultiPolyh( tr("MainObject") );
  _scene->AddNormMultiPolyh(_multiPolyh);
  _count = 0;
}


Kernel::~Kernel()
{
  delete _multiPolyh;
  delete _scene;
}

/*!
Metoda zwraca wka¼nik na edytowany obiekt z³o¿ony.
*/
ViMultiPolyh* Kernel::multiPolyh()
{
  return _multiPolyh;
}



/*!
Metoda inicjuje ca³y Kernel. Wczytuje wszystkie biblioteki z podanego katalogu (wykorzystuje
metodê readAllLibraries()).
Powinna byæ wywo³ywana od razu po utworzeniu obiektu Kernel.
*/
void Kernel::init(QString initLibPath)
{
  StatusBar::printStatusMsg(tr("Good day, i'd like to introduce You the Kernel."), "Kernel");
  int k = readAllLibraries(initLibPath);
  if (k < 1) StatusBar::printStatusMsg(tr("No libriaries found in directory: '%1'").arg(initLibPath), "Kernel"); // TUTAJ CHYBA POWINIEN WYJSC Z PROGRAMU
        else
        {
          StatusBar::printStatusMsg(tr("Number of read libraries: %1.").arg(k), "Kernel");
          emit sendScene( _scene ); // po wczytaniu wszystkich bibliotek, wysyla wskaznik na scene
        }
  
  // poka¿ i ustaw informacjê o maksymalnym rozmiarze tekstury
  GLint val[1];
  glGetIntegerv( GL_MAX_TEXTURE_SIZE, val);
  StatusBar::printStatusMsg( tr("Maximum texture size for Your OpenGL implementation = %1x%2").arg(val[0]).arg(val[0]), "Kernel" );
  TextureManager::setSafeSize( val[0] );
  TextureManager::setSafeMode( true );
  emit sendMultiPolyh( _multiPolyh );
}


/*!
Metoda ³aduje wszystkie biblioteki znajduj±ce sie w podanym katalogu.
Biblioteki s± ³adowane kolejno wed³ug nazwy pliku.
\param path - katalog zawieraj±cy biblioteki z bry³ami (pliki *.lib)
\return ilo¶æ znalezionych/wczytanych bibliotek lub: -1 gdy katalog nie istnieje, -2 katalog jest pusty.
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
  
  buildPattePolyhList(); // na koñcu tworzymy listê wszystkich nazw
  
  return i; // zwraca ilo¶æ poprawnie wczytanych bibliotek
}



/*!
Metoda tworzy listê QStringList nazw wszystkich wczytanych bry³ elementarnych.
*/
void Kernel::buildPattePolyhList()
{
  _pattePolyhList->clear(); // wyczyszczenie poprzedniej listy
  // iteracja wszystkich bry³ wzorcowych wczytanych do sceny
  for ( ViScene::ConNormPatteIter iter = _scene->ConBegin_NormPatte(); iter; ++iter )
  {
    _pattePolyhList->append( iter->GetName() ); // dodanie nazwy do listy
  }
  
  emit sendPrimitiveList( _pattePolyhList );
}



/*!
Metoda zwraca wska¼nik do bry³y wzorcowej na podstawie podanej nazwy.
*/
const ViPattePolyh* Kernel::findPattePolyh( const char* objectName )
{
  return _scene->FindNormPattePolyh( objectName );
}

/*!
Metoda zwraca wska¼nik do bry³y wzorcowej na podstawie indeksu jego nazwy na li¶cie.
*/
const ViPattePolyh* Kernel::findPattePolyh( int stringListIndex )
{
  // indeks poza list±
  if ( (stringListIndex < 0) || (stringListIndex >= _pattePolyhList->count()) ) return 0L;
  
  QString name( (*_pattePolyhList)[stringListIndex] );
  
  return _scene->FindNormPattePolyh( name.ascii() );
}



/*!
Metoda tworzy i dodaje obiekt elementarny do aktualnego obiektu z³o¿onego.
*/
void Kernel::addPattePolyh(const char *objectName)
{
  ViPattePolyh const *pPaPolyh = _scene->FindNormPattePolyh(objectName); // szukaj obiektu w bibliotece
  if (pPaPolyh) // je¿eli znaleziono obiekt
  {
      // dodaj element do mp, nazwa domy¶lna = typ bry³y + kolejno generowany numer
      ViElemePolyhExt *el = new ViElemePolyhExt(*pPaPolyh, QString("%1_nr_%2").arg(objectName).arg(_count++).ascii());

     _multiPolyh->AddNode(el);            // dodaj utworzony obiekt do struktury
     _multiPolyh->ComputeHierAllGlbVtx(); // przelicz wierzcho³ki
     _scene->ComputeGlbVtx_NormPolyh();   // przelicz wierzcho³ki - dziwne :O
  }
  else StatusBar::printStatusMsg( tr("Primitve not found. REALLY FATAL ERROR!"), "Kernel" ); // nie znaleziono bry³y - to nie mo¿e wyst±piæ !!!

  emit sendMultiPolyh(_multiPolyh); // po wszystkich operacjach dodawania wysylamy MultiPolyh
}


/*
Funkcja tworzenia nowych obiektów dziedziczonych klas.
*/
ViNTreeNode* kernelCreateFunction( const char *className )
{
  if ( strcmp( "ViElemePolyhExt", className ) == 0 ) return new ViElemePolyhExt;
  return 0;
}  



/*!
Metoda dodaje nowy obiekt z³o¿ony do aktualnego obiektu z³o¿onego lub elementu parent (o ile takowy istnieje).
*/
void Kernel::addMultiPolyh( const char *pathToMph, ViNTreeNode *parent )
{
  ViMultiPolyh *newMultiPolyh;
  QString mphPath( pathToMph );
  if ( QFile::exists( mphPath ) )
  {
    // dodaj nowy obiekt do aktualnego
    ViException exception;
    switch ( Vi::ReadMultiPolyh( pathToMph, *_scene, &newMultiPolyh, exception, kernelCreateFunction ) )
    {
      case 0 : {
                  StatusBar::printStatusMsg( tr("MultiPolyhedron added succesfully from file '%1'.").arg(pathToMph), "Kernel" ); 
              } break;
      case -1 : {
                  StatusBar::printStatusMsg( tr("Error reading file '%1'.").arg(pathToMph), "Kernel" );
                  StatusBar::printStatusMsg( tr("ErrorMsg: %1").arg(exception.GetErrMsg()), "Kernel" );
                } return;
      case -2 : {
                  StatusBar::printStatusMsg( tr("Error reading file '%1'.").arg(pathToMph), "Kernel" );
                  StatusBar::printStatusMsg( tr("ErrorMsg: %1").arg(exception.GetErrMsg()), "Kernel" );
                } return;
    } // switch
    
    newMultiPolyh->ComputeHierAllGlbVtx();
    
    // dodajemy nowy mph albo do rodzica albo do g³ównego MPH (parent=0);    
    if ( !parent ) _multiPolyh->AddNode( newMultiPolyh );
    else parent->AddNode( newMultiPolyh );
    
    _multiPolyh->ComputeHierAllGlbVtx();
    _scene->ComputeGlbVtx();
    
    // zmienimy teraz nazwê ¿eby by³a unikatowa
    // jezeli istnieje ju¿ obiekt o takiej nazwie - zmieniaj nazwê do bólu
    bool found;
    QString name( newMultiPolyh->NodeName() );
    do
    {
      found = false;
      for (ViNTreeNode::ConPolyhIter iter = _multiPolyh->ConBegin_PolyhHierList(); iter; ++iter) 
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
    newMultiPolyh->SetNodeName( name.ascii() );
    
    emit sendMultiPolyh( _multiPolyh ); // po wszystkich operacjach wysy³amy MultiPolyh
  }
}
  
  

/*!
Metoda ³aduje nowy obiekt z³o¿ony z pliku.
*/
void Kernel::loadMultiPolyh( const char *fileName )
{
  _scene->DeleteAllMultiPolyh(); // usuñ wszystko ze sceny
  
  ViException exception;
  
  switch ( Vi::ReadMultiPolyh( fileName, *_scene, &_multiPolyh, exception, kernelCreateFunction ) )
  {
    case 0 : {
                StatusBar::printStatusMsg( tr("MultiPolyhedron readed succesfully from file '%1'.").arg(fileName), "Kernel" ); 
             } break;
    case -1 : {
                StatusBar::printStatusMsg( tr("Error reading file '%1'.").arg(fileName), "Kernel" );
                StatusBar::printStatusMsg( tr("ErrorMsg: %1").arg(exception.GetErrMsg()), "Kernel" );
              } return;
    case -2 : {
                StatusBar::printStatusMsg( tr("Error reading file '%1'.").arg(fileName), "Kernel" );
                StatusBar::printStatusMsg( tr("ErrorMsg: %1").arg(exception.GetErrMsg()), "Kernel" );
              } return;
  } // switch
    
  _scene->AddNormMultiPolyh( _multiPolyh ); // dodaj nowy obiekt do sceny
  _multiPolyh->ComputeHierAllGlbVtx(); // przelicz wierzcho³ki
  _scene->ComputeGlbVtx_NormPolyh();   // przelicz wierzcho³ki - dziwne :O
  
  emit sendMultiPolyh( _multiPolyh ); // po wszystkich operacjach wysy³amy MultiPolyh
}
