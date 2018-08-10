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

   connect(newFileButton, SIGNAL(clicked()), this, SLOT(newScene()));
   connect(openFileButton, SIGNAL(clicked()), this, SLOT(openScene()));
   connect(saveFileButton, SIGNAL(clicked()), this, SLOT(saveScene()));
   connect(exitButton, SIGNAL(clicked()), this, SLOT(exit()));
}




bool FileWidget::newScene()
{
  if ( !(CellFrame::sceneIsEmpty()) ) // czy scena posiada obiekty z³o¿one
  {
    int choice = QMessageBox::question(qApp->mainWidget(),
                                       tr("New"),
                                       tr("Are you sure you want to clear current scene?"),
                                       QMessageBox::Yes, QMessageBox::No);
    if (choice == QMessageBox::Yes)
    {
     CellFrame::scene()->DeleteAllMultiPolyh();
     CellFrame::scene()->SetSceneName( "" );
     CellFrame::selected()->clear();
     Workspace::resetAllFrames();
     CellFrame::refresh();
     emit setScene( CellFrame::scene() );
     QString s(APPNAME);
     emit setFileCaption( s );
     return true; // wyczyszczono
    }
    
    return false; // user nie zgodzi³ siê na czyszczenie
    
  } 
}




void FileWidget::saveScene()
{
  /*
  if ( CellFrame::sceneIsEmpty() ) // jezeli scena jest pusta
  {
    QMessageBox::information(qApp->mainWidget(), tr("Save to file"), tr("There's nothing to save."));
    return; 
  }
  */
  
  QString fileName = QFileDialog::getSaveFileName(
                                                   Options::scenesPath(),
                                                   tr("Scene files (*.scn *.SCN *.Scn )"),
                                                   qApp->mainWidget(),
                                                   tr("Choose filename to save Your scene")
                                                  ); 

  if ( fileName != QString::null ) // czy uzytkownik nie klepnal Cancel
  {
    // czy wredas wpisa³ rozszerzenie? je¶li nie - dodaj je
    if (fileName.right(4) != ".scn") fileName+=".scn";

    if (QFile::exists(fileName))
    {
      int choice = QMessageBox::question(qApp->mainWidget(),
                                         tr("Save to File"),
                                         tr("File '%1' already exists.\nDo you want to overwrite it?").arg(fileName),
                                         QMessageBox::Yes, QMessageBox::No);
      if (choice == QMessageBox::No) return;
    }
    
    int errNo = saveSceneToFile( fileName ); // zapisz do pliku
    
    QString info;
    
    switch (errNo)
    {
      case 0  : {
                  info = tr("Scene written successfully to file:\n'%1'").arg(fileName); 
                  QString s = QString("%1 - %2").arg(APPNAME).arg(fileName);
                  emit setFileCaption( s );
                } break;
      case -1 : info = tr("Unable to write to file:\n'%1'").arg(fileName); break;
      default : info = tr("Unknown write error."); break;
    }

    if (errNo == 0) QMessageBox::information(qApp->mainWidget(), tr("Save to file"), info);
    else QMessageBox::critical(qApp->mainWidget(), tr("Save to file"), info);

  }                                                 
}




void FileWidget::openScene()
{
  if ( !newScene() ) return; // najpierw czy¶cimy wszystko o ile co¶ jest i user pozwoli
  
 QFileDialog *fileDialog = new QFileDialog(
                                             Options::scenesPath(),
                                             tr("Scene files (*.scn *.SCN *.Scn)"),
                                             qApp->mainWidget()
                                           );
  
  fileDialog->setCaption( tr("Choose scene to open") );
  
  QString fileName;
  
  if ( fileDialog->exec() == QDialog::Accepted ) fileName = fileDialog->selectedFile();
  else return; // CANCEL pressed
  
  if ( fileName != QString::null ) // je¿eli u¿ytkownik nie klepn±³ Cancel
  {
    QString s = QString("%1 - %2").arg(APPNAME).arg(fileName);
    emit setFileCaption( s );
    int errNo = loadSceneFromFile( fileName );
    switch ( errNo )
    {
      case 0 : StatusBar::printStatusMsg( tr("Scene '%1' loaded successfully.").arg(fileName), "File"); break;
      case -1 : StatusBar::printStatusMsg( tr("Error opening scene file '%1'.").arg(fileName), "File"); break;
      case -2 : StatusBar::printStatusMsg( tr("Error parsing scene file '%1'.").arg(fileName), "File"); break;
      default : StatusBar::printStatusMsg( tr("Error reading scene file '%1'.").arg(fileName), "File"); break;
    }
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





// metoda zapisuje scenê do pliku, je¿eli plik istnieje - zostaje wcze¶niej wyczyszczony
// zwraca: 0 = OK, -1 = b³±d, 2 = no znowu b³±d
int FileWidget::saveSceneToFile( QString& fileName )
{
  QDomDocument doc;
  QDomElement main = doc.createElement( SCENE_MAIN ); // root
  doc.appendChild( main );
  main.setAttribute( ATTR_SCENE_NAME, (CellFrame::scene())->GetSceneName().c_str() ); // nazwa sceny
  
  QDomElement lighting = doc.createElement( ELEM_LIGHTING ); // grupa ¶wiate³
  main.appendChild( lighting );
  
  QString s;
  
  if ( LightsWidget::lightingEnabled() ) s = "true"; else s = "false";
  lighting.setAttribute( ATTR_LIGHTING_ENABLED, s );
    
  // zapisujemy wszystkie ¶wiat³a
  for ( Light* light = (CellFrame::lightsList())->first(); light; light = (CellFrame::lightsList())->next())
  {
    QDomElement lightElem = doc.createElement( ELEM_LIGHT ); // grupa pojedynczego ¶wiat³a
    lighting.appendChild( lightElem );
    
    lightElem.setAttribute( ATTR_LIGHT_NAME, light->name() );           // jego parametry
    if ( light->isEnabled() ) s="true"; else s="false";
     lightElem.setAttribute( ATTR_LIGHT_ENABLED, s );
    if ( light->isSpotlight() ) s="spotlight"; else s="bulb";
     lightElem.setAttribute( ATTR_LIGHT_TYPE, s );
    if ( light->lightType() == Light::Directional ) s="directional"; else s="positional";
     lightElem.setAttribute( ATTR_LIGHT_IS, s );
    lightElem.setAttribute( ATTR_LIGHT_EXPONENT, light->spotExponent() );
    lightElem.setAttribute( ATTR_LIGHT_CUTOFF, light->spotCutOffAngle() );
    if ( light->isMovingWithCamera() ) s="true"; else s="false";
     lightElem.setAttribute( ATTR_LIGHT_MOVES_WITH_CAMERA, s );
    
    QDomElement positionElem = doc.createElement( ELEM_LIGHT_POSITION ); // grupa pozycji ¶wiat³a
    lightElem.appendChild( positionElem );
    const GLfloat* pos = light->position4fv();
    positionElem.setAttribute( ATTR_X, pos[0] );   // pozycja x,y,z
    positionElem.setAttribute( ATTR_Y, pos[1] );
    positionElem.setAttribute( ATTR_Z, pos[2] );
    
    QDomElement dirElem = doc.createElement( ELEM_LIGHT_DIRECTION ); // grupa kierunku ¶wiat³a
    lightElem.appendChild( dirElem );
    const GLfloat* dir = light->spotDirection3fv();
    dirElem.setAttribute( ATTR_X, dir[0] );   // kierunek x,y,z
    dirElem.setAttribute( ATTR_Y, dir[1] );
    dirElem.setAttribute( ATTR_Z, dir[2] );
    
    QDomElement attElem = doc.createElement( ELEM_LIGHT_ATTENUATION ); // rozproszenie
    lightElem.appendChild( attElem );
    attElem.setAttribute( ATTR_LIGHT_CONSTANT,  light->constantAttenuation() );
    attElem.setAttribute( ATTR_LIGHT_LINEAR,    light->linearAttenuation() );
    attElem.setAttribute( ATTR_LIGHT_QUADRATIC, light->quadraticAttenuation() );
    
    QDomElement ambientElem = doc.createElement( ELEM_LIGHT_AMBIENT ); // kolor ambient
    lightElem.appendChild( ambientElem );
    const GLfloat* ac = light->ambientColor4fv();
    ambientElem.setAttribute( ATTR_RED,   ac[0] ); // sk³adowe
    ambientElem.setAttribute( ATTR_GREEN, ac[1] );
    ambientElem.setAttribute( ATTR_BLUE,  ac[2] );
    ambientElem.setAttribute( ATTR_ALPHA, ac[3] );
    
    QDomElement diffuseElem = doc.createElement( ELEM_LIGHT_DIFFUSE ); // kolor diffuse
    lightElem.appendChild( diffuseElem );
    const GLfloat* dc = light->diffuseColor4fv();
    diffuseElem.setAttribute( ATTR_RED,   dc[0] ); // sk³adowe
    diffuseElem.setAttribute( ATTR_GREEN, dc[1] );
    diffuseElem.setAttribute( ATTR_BLUE,  dc[2] );
    diffuseElem.setAttribute( ATTR_ALPHA, dc[3] );
    
    QDomElement specularElem = doc.createElement( ELEM_LIGHT_SPECULAR ); // kolor specular
    lightElem.appendChild( specularElem );
    const GLfloat* sc = light->specularColor4fv();
    specularElem.setAttribute( ATTR_RED,   sc[0] ); // sk³adowe
    specularElem.setAttribute( ATTR_GREEN, sc[1] );
    specularElem.setAttribute( ATTR_BLUE,  sc[2] );
    specularElem.setAttribute( ATTR_ALPHA, sc[3] );
    
    // i to tyle dla pojedynczego ¶wiat³a
  }
  
  FogStruct *f = FogWidget::fog(); // mg³a
  
  QDomElement fog = doc.createElement( ELEM_FOG ); // grupa mg³y
  main.appendChild( fog );
  if ( f->fogEnabled ) s="true"; else s="false";
   fog.setAttribute( ATTR_FOG_ENABLED, s ); // atrybuty mg³y
  switch ( f->fogMode )
  {
    case GL_LINEAR : s="GL_LINEAR"; break;
    case GL_EXP    : s="GL_EXP"; break;
    case GL_EXP2   : s="GL_EXP2"; break;
    default : s="GL_LINEAR"; break;
  }
   fog.setAttribute( ATTR_FOG_MODE, s );
  fog.setAttribute( ATTR_FOG_DENSITY, f->fogDensity );
  
  QDomElement distance = doc.createElement( ELEM_FOG_DISTANCE ); // podgrupa distance
  fog.appendChild( distance );
  distance.setAttribute( ATTR_FOG_START, f->fogStart );
  distance.setAttribute( ATTR_FOG_END, f->fogEnd );
  
  QDomElement fogColor = doc.createElement( ELEM_FOG_COLOR ); // podgrupa koloru mg³y
  fog.appendChild( fogColor );
  fogColor.setAttribute( ATTR_RED,   (f->fogColor)[0] );    // sk³adowe koloru
  fogColor.setAttribute( ATTR_GREEN, (f->fogColor)[1] );
  fogColor.setAttribute( ATTR_BLUE,  (f->fogColor)[2] );
  fogColor.setAttribute( ATTR_ALPHA, (f->fogColor)[3] );
  
  /*
  QDomElement shadows = doc.createElement( ELEM_SHADOWS ); // grupa cieni
  main.appendChild( shadows );
  */
  
  ViScene *scene = CellFrame::scene();  // obiekty
  
  QDomElement elements = doc.createElement( ELEM_ELEMENTS );
  main.appendChild( elements );
  
  for ( ViScene::ConMultiPolyhIter mph = scene->ConBegin_NormMultiPolyh(); mph; ++mph )
  {
    QDomElement mphElem = doc.createElement( ELEM_OBJECT ); // grupa pojedynczego obiektu
    elements.appendChild( mphElem );
    ViMultiPolyhExt *me = (ViMultiPolyhExt*) & (*mph);
    mphElem.setAttribute( ATTR_ELEM_FILENAME, me->fileName() );   // jego atrybuty
    mphElem.setAttribute( ATTR_ELEM_NAME, mph->NodeName() );
    
    const MatrixH3f m = mph->Mtx2ParentCoord();
    Vector3f v;
    
    QDomElement trans = doc.createElement( ELEM_TRANS ); // podgrupa translacji
    mphElem.appendChild( trans );
    v = m.GetTrans_TAfterR();
    trans.setAttribute( ATTR_X, v.x );   // przesuniêcie
    trans.setAttribute( ATTR_Y, v.y );
    trans.setAttribute( ATTR_Z, v.z );
    
    QDomElement rot = doc.createElement( ELEM_ROT ); // podgrupa rotacji
    mphElem.appendChild( rot );
    v = m.GetAng_XYZ_Deg();
    rot.setAttribute( ATTR_X, v.x );   // rotacja w k±tach
    rot.setAttribute( ATTR_Y, v.y );
    rot.setAttribute( ATTR_Z, v.z );
    
    QDomElement scale = doc.createElement( ELEM_SCALE ); // podgrupa skali
    mphElem.appendChild( scale );
    v = m.GetScale();
    scale.setAttribute( ATTR_X, v.x );   // skala
    scale.setAttribute( ATTR_Y, v.y );
    scale.setAttribute( ATTR_Z, v.z );
  }
  
  QFile file( fileName ); // plik
  if ( !file.open( IO_WriteOnly ) )  // otwarcie pliku do zapisu
  {
    QMessageBox::critical(
                          this,
                          tr("Save scene"),
                          tr("Unable to save file \"%1\".").arg(file.name())
                         );
    return -1;
  }

  QTextStream stream( &file ); // tworzymy strumieñ
  stream << doc.toString();    // wysy³amy XML-a do pliku
  file.close();                // zamykamy plik
  
  return 0;
}






// metoda ³aduje scenê z pliku
// zwraca: 0 = OK, -1 = brak pliku, -2 = b³±d parsowania
int FileWidget::loadSceneFromFile( QString& fileName )
{
  if ( !QFile::exists( fileName ) ) return -1;
  
  QFile file( fileName );
  
  QDomDocument doc;
  if (!doc.setContent( &file, false )) return -2;
  
  QDomElement root = doc.documentElement();
  if ( root.tagName() != SCENE_MAIN ) return -2;
  if ( !root.hasChildNodes() ) return -2;
  if ( !root.hasAttributes() ) return -2;
  
  QString s = root.attribute( ATTR_SCENE_NAME, "Scene" );     // nazwa sceny
  (CellFrame::scene())->SetSceneName( s.ascii() );
  
  QDomNode node = root.firstChild();  // zczytujemy pierwszego potomka
  if ( node.nodeType() != QDomNode::ElementNode ) return -2;
  
  while ( !node.isNull() )
  {
    QDomElement elem = node.toElement();
    // w zale¿no¶ci od tego jaki to element - wywo³ujemy odpowiedni± metodê czytania
    if ( elem.tagName() == ELEM_LIGHTING )
    { 
      readLighting( elem ); 
      node = node.nextSibling(); 
      continue;
    }
    if ( elem.tagName() == ELEM_FOG )
    {
      readFog( elem ); 
      node = node.nextSibling(); 
      continue;
    }
    /*
    if ( elem.tagName() == ELEM_SHADOWS )
    {
      readShadows( elem ); 
      node = node.nextSibling(); 
      continue;
    }
    */
    if ( elem.tagName() == ELEM_ELEMENTS )
    {
      readElements( elem ); 
      node = node.nextSibling(); 
      continue;
    }
  }
  return 0;
}



// metoda zczytuje ¶wiat³a
// 0 = OK, -2 = b³±d parsowania
int FileWidget::readLighting( QDomElement elem )
{
  emit clearAllLights();
  
  Light *light;
  QString s;
  bool b, ok;
  float f,r,g,bl,a,x,y,z;
  
  if ( !elem.hasAttributes() ) return -2;
  s = elem.attribute( ATTR_LIGHTING_ENABLED, "true" );
   ( s=="true" ) ? b=true : b=false;
   emit setLightingEnabled( b );
  
  if ( !elem.hasChildNodes() ) return 0; // nie ma ¿adnego ¶wiat³a
  
  // teraz ³adujemy kolejne ¶wiat³a
  QDomNode node = elem.firstChild();
  while ( !node.isNull() )
  {
    QDomElement el = node.toElement();
    light = new Light( false ); //zarowka
    
    s = el.attribute( ATTR_LIGHT_NAME, light->name() ); // nazwa ¶wiat³a
     light->setName( s );
    s = el.attribute( ATTR_LIGHT_ENABLED, "true" ); // czy ¶wiat³o ON
     ( s=="true" ) ? b=true : b=false;
     light->setEnabled( b );
    s = el.attribute( ATTR_LIGHT_TYPE, "bulb" ); // ¿arówka/latarka
     ( s=="bulb" ) ? light->setSpotlight( false ) : light->setSpotlight( true );
    s = el.attribute( ATTR_LIGHT_IS, "positional" ); // pozycyjne czy kierunkowe
     ( s=="positional" ) ? light->setLightType( Light::Positional ) : light->setLightType( Light::Directional );
    s = el.attribute( ATTR_LIGHT_EXPONENT, "0" ); // exponent
     f = s.toFloat( &ok );
     if (!ok) f = 0.0;
     light->setSpotExponent( f );
    s = el.attribute( ATTR_LIGHT_CUTOFF, "180.0" ); // cutOff
     f = s.toFloat( &ok );
     if (!ok) f = 180.0;
     light->setSpotCutOffAngle( f );
    s = el.attribute( ATTR_LIGHT_MOVES_WITH_CAMERA, "true" ); // moves with camera
     ( s=="true" ) ? b=true : b=false;
     light->setMovingWithCamera( b );
     
    /////// teraz elementy, czyli: pozycja, kierunek, rozproszenie i kolory
    QDomNode subNode = el.firstChild();
    QString tag;
    while ( !subNode.isNull() )
    {
      QDomElement subEl = subNode.toElement();
      tag = subEl.tagName();
      
      // pozycja lub kierunek ¶wiat³a
      if ( (tag == ELEM_LIGHT_POSITION) || (tag == ELEM_LIGHT_DIRECTION) )
      {
        x = subEl.attribute( ATTR_X, "0" ).toFloat( &ok );
        if ( !ok ) x=0.0;
        y = subEl.attribute( ATTR_Y, "0" ).toFloat( &ok );
        if ( !ok ) y=0.0;
        z = subEl.attribute( ATTR_Z, "-1.0" ).toFloat( &ok );
        if ( !ok ) z=-1.0;
        Vector3f v( x,y,z );
        
        if ( tag == ELEM_LIGHT_POSITION ) light->setPosition( v ); else light->setSpotDirection( v );
        subNode = subNode.nextSibling();
        continue;
      }
      
      // rozproszenie ¶wiat³a (x=linear, y=constant, z=quadratic)
      if ( tag == ELEM_LIGHT_ATTENUATION )
      {
        f = subEl.attribute( ATTR_LIGHT_LINEAR, "0").toFloat( &ok );
         if ( !ok ) f=0.0;
         light->setLinearAttenuation( f );
        f = subEl.attribute( ATTR_LIGHT_CONSTANT, "1.0").toFloat( &ok );
         if ( !ok ) f=1.0;
         light->setConstantAttenuation( f );
        f = subEl.attribute( ATTR_LIGHT_QUADRATIC, "0").toFloat( &ok );
         if ( !ok ) f=0.0;
         light->setQuadraticAttenuation( f );
    
        subNode = subNode.nextSibling();
        continue;
      }
     
      // kolory
      if ( (tag==ELEM_LIGHT_AMBIENT) || (tag==ELEM_LIGHT_DIFFUSE) || (tag==ELEM_LIGHT_SPECULAR) )
      {
        r = subEl.attribute( ATTR_RED, "1" ).toFloat( &ok );
         if ( !ok ) r=1.0;
        g = subEl.attribute( ATTR_GREEN, "1" ).toFloat( &ok );
         if ( !ok ) g=1.0;
        bl = subEl.attribute( ATTR_BLUE, "1" ).toFloat( &ok );
         if ( !ok ) bl=1.0;
        a = subEl.attribute( ATTR_ALPHA, "1" ).toFloat( &ok );
         if ( !ok ) a=1.0;
        
        const GLfloat color[] = { r, g, bl, a };
        
        if ( tag==ELEM_LIGHT_AMBIENT ) light->setAmbientColor( color ); else
        if ( tag==ELEM_LIGHT_DIFFUSE ) light->setDiffuseColor( color ); else
        light->setSpecularColor( color );
        
        subNode = subNode.nextSibling();
        continue;
      }
      
    }
     
    emit addLight( light );
    node = node.nextSibling();
  }
  
  return 0;
}



// metoda zczytuje parametry mg³y
// zwraca: 0=OK, -2=b³±d XML
int FileWidget::readFog( QDomElement elem )
{
  if ( !elem.hasAttributes() ) return -2;
  
  QString s;
  float f;
  bool b, ok;
  GLenum gl;
  
  FogStruct *fog = FogWidget::fog();
  
  s = elem.attribute( ATTR_FOG_ENABLED, "false" ); // mg³a ON/OFF
   ( s=="true" ) ? b=true : b=false;
   fog->fogEnabled = b;
  s = elem.attribute( ATTR_FOG_MODE, "GL_LINEAR" ); // typ mg³y
   if ( s=="GL_LINEAR" ) gl=GL_LINEAR; else
   if ( s=="GL_EXP" )    gl=GL_EXP;    else gl=GL_EXP2;
   fog->fogMode = gl;
  f = elem.attribute( ATTR_FOG_DENSITY, "0.35" ).toFloat( &ok ); // gêsto¶æ
   if ( !ok ) f=0.35;
   fog->fogDensity = f;
  
  ///////////////////////// elementy: distance i kolor
  QDomNode node = elem.firstChild();
  while ( !node.isNull() )
  {
    QDomElement el = node.toElement();
    
    if ( el.tagName() == ELEM_FOG_DISTANCE ) // distance
    {
      f = el.attribute( ATTR_FOG_START, "0").toFloat( &ok );
       if ( !ok ) f=0.0;
       fog->fogStart = f;
      f = el.attribute( ATTR_FOG_END, "1000" ).toFloat( &ok );
       if ( !ok ) f=1000.0;
       fog->fogEnd = f;
      
      node = node.nextSibling();
      continue;
    }

    if ( el.tagName() == ELEM_FOG_COLOR ) // color
    {
      f = el.attribute( ATTR_RED, "0" ).toFloat( &ok );
       if ( !ok ) f=0.0;
       fog->fogColor[0] = f;
      f = el.attribute( ATTR_GREEN, "0" ).toFloat( &ok );
       if ( !ok ) f=0.0;
       fog->fogColor[1] = f;
      f = el.attribute( ATTR_BLUE, "0" ).toFloat( &ok );
       if ( !ok ) f=0.0;
       fog->fogColor[2] = f;
      f = el.attribute( ATTR_ALPHA, "0" ).toFloat( &ok );
       if ( !ok ) f=0.0;
       fog->fogColor[3] = f;
      
      node = node.nextSibling();
      continue;
    }
    
  }
  
  emit updateFog();
  return 0;
}


/*
int FileWidget::readShadows( QDomElement elem )
{
}
*/


// wczytuje obiekty z³o¿one
// zwraca: 0=OK, -2=b³±d XML
int FileWidget::readElements( QDomElement elem )
{
  if ( !elem.hasChildNodes() ) return 0; // nie ma obiektów na scenie
  QString name, path;
  float x,y,z;
  bool ok;
  Vector3f trans,rot,scale;
  
  QDomNode node = elem.firstChild();
  while ( !node.isNull() ) // czytaj kolejne obiekty
  {
    QDomElement el = node.toElement();
    if ( !el.hasAttributes() ) { node = node.nextSibling(); continue; }
    
    name = el.attribute( ATTR_ELEM_NAME, "newObject" ); // nazwa obiektu
    path = el.attribute( ATTR_ELEM_FILENAME, "" ); // ¶cie¿ka do obiektu
     if ( path.isEmpty() ) { node = node.nextSibling(); continue; }
    
    //////////////// teraz: trans, rot, scale
    QDomNode subNode = el.firstChild();
    while ( !subNode.isNull() )
    {
      QDomElement v = subNode.toElement();
      
      x = v.attribute( ATTR_X, "0" ).toFloat( &ok );
       if (!ok) x=0.0;
      y = v.attribute( ATTR_Y, "0" ).toFloat( &ok );
       if (!ok) y=0.0;
      z = v.attribute( ATTR_Z, "0" ).toFloat( &ok );
       if (!ok) z=0.0;
      
      if ( v.tagName() == ELEM_TRANS )
      {
        trans.Set( x,y,z );
      } else
      if ( v.tagName() == ELEM_ROT )
      {
        rot.Set( x,y,z );
      } else
      if ( v.tagName() == ELEM_SCALE )
      {
        scale.Set( x,y,z );
      }
      
      subNode = subNode.nextSibling();
    }
    
    /// wysy³amy ¿±danie utworzenia nowego obiektu
    emit addMultiPolyh( path.ascii(), name.ascii(), trans, rot, scale );
    
    node = node.nextSibling();
  }
  emit setScene( Kernel::scene() );
  return 0;
}

