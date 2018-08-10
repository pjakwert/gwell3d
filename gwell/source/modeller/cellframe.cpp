//////////////////////////////////////////////////////////////////
///
///  class: CellFrame (.cpp)
///
///  okno edycyjne aplikacji
///
//////////////////////////////////////////////////////////////////

#define DEF_INFO_POS_X 10
#define DEF_INFO_POS_Y this->height()-12

#define HasDescendants() IsDescendant()

#define SelectID       0
#define TransID        1
#define RotID          2
#define ScaleID        3
#define LinkID         4
#define TransCoordsID  5
#define RotCoordsID    6
#define MatEditID      7
#define TexEditID      8
#define TransLightID   9
#define DirLightID    10
#define CameraID      11
#define DeleteID      12
#define CopyID        13
#define CutID         14
#define PasteID       15
#define SelectAllID   16
#define KinematicID   17


#include "cellframe.h"



using namespace qglviewer;


// zmienne statyczne
QPtrList<ViNTreeNode> CellFrame::nameList; // przechowuje odpowiednie warto¶ci liczbowe obiektów

ViMultiPolyh* CellFrame::_multiPolyh = 0L;  // wska¼nik do wy¶wietlanego obiektu z³o¿onego

QPtrList<ViNTreeNode>* CellFrame::_selectedList = new QPtrList<ViNTreeNode>; // lista zaznaczonych
QPtrList<ViNTreeNode>* CellFrame::_clipboard = new QPtrList<ViNTreeNode>; // schowek

QPtrList<Light>* CellFrame::_lightsList = 0L;

MModifier* CellFrame::_modifier = 0L; // obowi±zuj±cy modyfikator


const GLfloat CellFrame::no_material[] = { 0.0, 0.0, 0.0, 1.0 };  // pusty materia³
const GLfloat CellFrame::no_shininess[] = { 0.0 };                // zerowa po³yskliwo¶æ
const GLfloat CellFrame::white_material[] = { 1.0, 1.0, 1.0, 1.0 };  // bia³y materia³


/*! 
Metoda sortuje listê obiektów przezroczystych wzglêdem wspó³rzêdnej Z (we wspó³rzêdnych kamery).
*/
bool CellFrame::sortBlendedList()
{
  if ( blendedList.isEmpty() ) return false;
  
  QPtrList<ViElemePolyhExt> sortedList;
  
  ViElemePolyhExt* minExtEl = blendedList.first();
   Vector3f minVec( minExtEl->GlbOlnBox().Min() );
   Vector3f maxVec( minExtEl->GlbOlnBox().Max() );
   float minMinZ = camera()->cameraCoordinatesOf( Vec::Vec( minVec.x, minVec.y, minVec.z ) ).z;
   float minMaxZ = camera()->cameraCoordinatesOf( Vec::Vec( maxVec.x, maxVec.y, maxVec.z ) ).z;
  float minZ = QMIN( minMinZ, minMaxZ );
  int minIndex = 0;
   
  while ( true )
  { 
    // szukamy mniejszego elementu
   int i = 0;
   for ( ViElemePolyhExt* extEl = blendedList.first(); extEl; extEl = blendedList.next() )
   {
    minVec.Set( extEl->GlbOlnBox().Min() );
    maxVec.Set( extEl->GlbOlnBox().Max() );
    minMinZ = camera()->cameraCoordinatesOf( Vec::Vec( minVec.x, minVec.y, minVec.z ) ).z;
    minMaxZ = camera()->cameraCoordinatesOf( Vec::Vec( maxVec.x, maxVec.y, maxVec.z ) ).z;
    float v = QMIN( minMinZ, minMaxZ );
    if ( v < minZ ) { minZ = v; minExtEl = extEl; minIndex = i; }
    i++;
   }
   // wstawiamy go do listy sortedList
   sortedList.append( minExtEl );
   // usuwamy z listy blendedList 
   blendedList.remove( minIndex );
   
   if ( blendedList.isEmpty() ) break; // je¿eli lista po usuniêciu jest pusta - wyjd¼
   else // je¿eli nie - ustaw min na pierwszy jej element
   { 
    minExtEl = blendedList.first(); 
    minZ = QMIN( minExtEl->GlbOlnBox().Min().z, minExtEl->GlbOlnBox().Max().z );
    minIndex = 0;
   }
  }
  
  blendedList = sortedList;
  
  if ( !blendedList.isEmpty() ) return true; else return false; // na wszelki wypadek (ewentualny b³±d)
}



// konstruktor
CellFrame::CellFrame (QWidget *parent, const char *name, QGLWidget *shareWidget, WFlags f) : QGLViewer( parent,name,shareWidget,f ), blendedList()
{
  nameList.clear(); // wyczy¶æ listê asocjacyjn± nazw obiektów dla openGL
  blendedList.clear();
  _info = "";
  _gridIsDrawn = false; // na poczatku wy³±cz siatkê
  _grid3DIsDrawn = false; // siatka 3D
  _axisIsDrawn = false; // wy³±cz osie
  _lightsAreDrawn = false; // wy³±cz kszta³ty ¶wiate³
  _cameraIsMoving = false; // na pocz±tku nie ma poruszania kamer±
  _drawMethod = Wire; // domy¶lnie rysujemy druciak
  
  startWidget = new StartWidget(this); // ikonka w lewym górnym naro¿niku
   startWidget->setPaletteBackgroundColor( Options::backgroundColor() );
   startWidget->setCursor(QCursor(Qt::ArrowCursor));
   QToolTip::add(startWidget, tr("Menu (`)"));
  cellWidget = new CellWidget(this); // podrêczne znikaj±ce menu
   cellWidget->setCursor(QCursor(Qt::ArrowCursor));

  hbox = new QHBoxLayout(this);
  hbox->addWidget(startWidget, 0, Qt::AlignLeft | Qt::AlignTop); // w lewym gornym rogu
  hbox->addWidget(cellWidget, 0, Qt::AlignTop);

  /////////////////////////////////////////////////////////////////////////////////////////// PopupMenu
  popupMenu = new QPopupMenu( this );
  popupMenu->insertItem( QIconSet(QPixmap(Icons::selectIcon())), tr("Select"),    SelectID );
  popupMenu->insertItem( QIconSet(QPixmap(Icons::cameraIcon())), tr("Camera"),    CameraID );
  popupMenu->insertSeparator();
  popupMenu->insertItem( tr("Select All"), SelectAllID );
  popupMenu->insertItem( QIconSet(QPixmap(*Icons::copyIcon())),  tr("Copy"),     CopyID );
  popupMenu->insertItem( QIconSet(QPixmap(*Icons::pasteIcon())), tr("Paste"),    PasteID );
  popupMenu->insertItem( QIconSet(QPixmap(*Icons::cutIcon())),   tr("Cut"),      CutID );
  popupMenu->insertItem( QIconSet( QPixmap(*Icons::deleteIcon())), tr("Delete"), DeleteID );
  popupMenu->insertSeparator();
  popupMenu->insertItem( QIconSet(QPixmap(Icons::moveIcon())),   tr("Translate"), TransID );
  popupMenu->insertItem( QIconSet(QPixmap(Icons::rotateIcon())), tr("Rotate"),    RotID );
  popupMenu->insertItem( QIconSet(QPixmap(Icons::scaleIcon())),  tr("Scale"),     ScaleID );
  popupMenu->insertItem( QIconSet(QPixmap(Icons::linkIcon())),   tr("Link"),      LinkID );
  popupMenu->insertItem( QIconSet(QPixmap(Icons::moveIcon())),   tr("Translate coords"), TransCoordsID );
  popupMenu->insertItem( QIconSet(QPixmap(Icons::rotateIcon())), tr("Rotate coords"),    RotCoordsID );
  popupMenu->insertSeparator();
  popupMenu->insertItem( QIconSet(QPixmap(Icons::colorsIcon())),  tr("Material editor"), MatEditID );
  popupMenu->insertItem( QIconSet(QPixmap(Icons::textureIcon())), tr("Texture  editor"), TexEditID );
  popupMenu->insertItem( QIconSet(QPixmap(Icons::axisIcon())),    tr("Kinematics editor"), KinematicID );
  popupMenu->insertSeparator();
  popupMenu->insertItem( QIconSet(QPixmap(*Icons::bulbIcon())), tr("Translate light"),  TransLightID );
  popupMenu->insertItem(QIconSet(QPixmap(*Icons::spotIcon())), tr("Change light direction"),DirLightID);
  
      
  connect( popupMenu, SIGNAL( aboutToShow() ), this,  SLOT ( popupAboutToShow() ) );
  connect( popupMenu, SIGNAL( activated(int) ), this, SLOT ( choosedFromPopup(int) ) );
  /////////////////////////////////////////////////////////////////////////////////////////// PopupMenu
  
  
  // startWidget wlacza i wylacza cellWidget
  connect(startWidget, SIGNAL(clicked()), cellWidget, SLOT(toggleVisibility()));

// polaczenia dla CELLWIDGETa
  connect( cellWidget, SIGNAL(moveCamera(bool)), this, SLOT(setCameraMoving(bool)));
  connect( cellWidget, SIGNAL(showEntireScene()), this, SLOT(showAllScene()));
  connect( cellWidget, SIGNAL(showGrid(bool)), this, SLOT(setDrawGridXZ(bool)));
  connect( cellWidget, SIGNAL(showAxis(bool)), this, SLOT(setDrawAxisXYZ(bool)));
  connect( cellWidget, SIGNAL(showLights(bool)), this, SLOT( setDrawLights(bool) ) );
  connect( cellWidget, SIGNAL(viewDirectionChanged(int)), this, SLOT(setViewDirection(int)));
  connect( cellWidget, SIGNAL(setViewType(DrawMethod)), this, SLOT(setDrawMethod(DrawMethod)));
  connect( cellWidget, SIGNAL(setProjType(qglviewer::Camera::Type)), this, SLOT(setCameraType(qglviewer::Camera::Type)));
  connect( cellWidget, SIGNAL(makeScreenshot()), this, SLOT(saveSnapshot())); // saveSnapshot jest slotem QGLViewer
  connect( cellWidget, SIGNAL(maximize()), this, SLOT(maximize()));

  // domyslnie cellWidget jest na poczatku ukrywany
  cellWidget->hide();
  
  setSceneRadius(2.0); // domyslny promien sceny 2.0

  setWheelBinding( Qt::NoButton, CAMERA, ZOOM );
  setCameraMoving( false );
}



/*!
Metoda statyczna od¶wie¿aj±ca wszystkie widoki. Najpierw oblicza wspó³rzêdne globalne bry³.
*/
void CellFrame::refresh()
{
 if (_multiPolyh != 0L)
 {
   _multiPolyh->ComputeHierAllGlbVtx(); // przeliczenie wierzcholkow
 }
 updateGLForAllViewers();             // odrysowanie wszystkich widokow
}


/*!
Metoda zwraca wska¼nik na listê zaznaczonych obiektów.
*/
QPtrList<ViNTreeNode>* CellFrame::selected()
{
  return _selectedList;
}

/*!
Metoda zwraca wska¼nik na g³ówny (edytowany) obiekt z³o¿ony.
*/
ViMultiPolyh* CellFrame::multiPolyh()
{
  return _multiPolyh;
}




/*!
Metoda w³±cza/wy³±cza rysowanie poziomej siatki.
*/
void CellFrame::setDrawGridXZ(bool on)
{
  _gridIsDrawn = on;
  cellWidget->showGridButton->setOn(on);
  updateGL();
}

/*!
Metoda w³±cza/wy³±cza rysowanie siatki 3D.
*/
void CellFrame::setDrawGrid3D(bool on)
{
  _grid3DIsDrawn = on;
  updateGL();
}

/*!
Metoda w³±cza/wy³±cza rysowanie osi wspó³rzêdnych.
*/
void CellFrame::setDrawAxisXYZ( bool on )
{
  _axisIsDrawn = on;
  cellWidget->showAxisButton->setOn(on);
  updateGL();
}

/*!
Metoda w³±cza/wy³±cza rysowanie kszta³tów ¶wiate³.
*/
void CellFrame::setDrawLights( bool on )
{
  _lightsAreDrawn = on;
  cellWidget->showLightsButton->setOn(on);
  updateGL();
}


/*!
Metoda ustawia tekst wy¶wietlany jako informacja w oknie edycyjnym.
*/
void CellFrame::setInfo(QString s, int x, int y)
{
  _info = s;

  if (x==-1 || y==-1)
  {
    _infoPosX = DEF_INFO_POS_X;
    _infoPosY = DEF_INFO_POS_Y;
  }
  else
  {
    _infoPosX = x;
    _infoPosY = y;
  }
}


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////  R Y S O W A N I E ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

/*!
Metoda inicjuje OpenGL.
*/
void CellFrame::init()
{
  glEnable( GL_DEPTH_TEST );
  glDisable( GL_BLEND );
  
  // czy potrzebne?
  //glColor4f( 1.0f, 1.0f, 1.0f, 0.5f );
  //glBlendFunc( GL_SRC_ALPHA, GL_ONE );
}


/*!
G³ówna metoda, wewn±trz której odbywa siê ca³e rysowanie.
*/
void CellFrame::draw()
{
  qglClearColor( Options::backgroundColor() ); // wywo³uje glClearColor()
  glShadeModel( Options::shadeModel() );
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, Options::correctionHint() );
  
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // czyszczenie bufora OpenGL
  drawScene();
  drawInfo();
}


/*!
Metoda wy¶wietla informacjê tekstow± zawart± w polu _info.
U¿ywa czcionki zdefiniowanej globalnie dla ca³ej aplikacji.
*/
void CellFrame::drawInfo()
{
   glDisable( GL_LIGHTING );
   glDisable( GL_TEXTURE_2D );
   qglColor( Options::infoTextColor() );
    drawText(_infoPosX, _infoPosY, _info);
}


/*!
Metoda rysuje lub zrzuca nazwy obiektów na stos OpenGL (do celów po¼niejszej selekcji):
\param pushID - w³±czone indeksowanie obiektów.
*/
void CellFrame::drawScene( bool pushID )
{
  if ( _gridIsDrawn && !pushID ) // rysowanie siatki
  {
    glDisable( GL_LIGHTING );
    glDisable( GL_TEXTURE_2D );
    glDisable( GL_BLEND );
    qglColor( Options::gridColor() ); // domyslny kolor rysowania siatki
    drawGridXZ();
  }
  
  if ( _grid3DIsDrawn && !pushID ) // rysowanie siatki 3D
  {
    glDisable( GL_LIGHTING );
    glDisable( GL_TEXTURE_2D );
    glDisable( GL_BLEND );
    qglColor( Options::grid3DColor() ); // domy¶lny kolor rysowania siatki 3D
    drawGrid3D();
  }
  
  // g³ówny uk³ad wspó³rzêdnych
    if ( _axisIsDrawn && (!pushID) )
    {
      glPushMatrix();
       glTranslatef( 0.0, 0.0, 0.0 );

        // wyzerowane materia³y, aby nie dotyka³y osi
        glDisable( GL_TEXTURE_2D );
        glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT,   no_material );
        glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE,   no_material );
        glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR,  no_material );
        glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION,  no_material );
        glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, no_shininess );

        float maxScale = sceneRadius() * 0.9;
        // trzeba w³±czyæ ¶wiat³o ¿eby by³o widaæ osie
         GLboolean on;
         glGetBooleanv ( GL_LIGHT0, &on );
         if (!on) glEnable( GL_LIGHT0 );
        drawAxis( maxScale );
         if ( !on ) glDisable( GL_LIGHT0 ); // je¿eli by³o wy³±czone to wy³±czamy z powrotem
        
      glPopMatrix();
     }
  
  if ( this->hasFocus() && !pushID )   // ramka dla aktywnej CellFrame
  {
    glDisable( GL_LIGHTING );
    glDisable( GL_TEXTURE_2D );
    glDisable( GL_BLEND );
   startScreenCoordinatesSystem();
    glDisable(GL_LIGHTING);
    glDisable( GL_TEXTURE_2D );
    glLineWidth(1.0);
    qglColor( Options::frameColor() );
    glBegin(GL_LINE_LOOP);
     glVertex2d(2,2);
     glVertex2d(this->width()-3, 2);
     glVertex2d(this->width()-3, this->height()-3);
     glVertex2d(2, this->height()-3);
    glEnd();
   stopScreenCoordinatesSystem();
  }
  
  if ( _multiPolyh ) // je¿eli jest co rysowaæ
  {
    //if ( !_multiPolyh->HasDescendants() ) return; // obiekt musi mieæ potomków

    ViElemePolyhExt *extEl = 0L;
    
    if ( pushID ) nameList.clear();  // wyczy¶æ liste asocjacyjn± nazw obiektów

    blendedList.clear(); // wyczy¶æ listê obiektów przezroczystych
    
    for (ViNTreeNode::ConPolyhIter hierIter = _multiPolyh->ConBegin_PolyhHierList(); hierIter; ++hierIter)
    { // iteracja polyhHier


     switch ( hierIter->GetInheritorType() )
     {
       case IT_MULTIPOLYH     : extEl = 0L; break; // powinien iterowac wszystkie BRYLY multipolyha - jedno NAME!
       case IT_ELEMEPOLYH     : extEl = (ViElemePolyhExt*) & *hierIter; break;
       case IT_SCENEPOLYHLIST : extEl = 0L; break; // zboczeniec
       default                : break; // zboczeniec!
     }

     if ( !extEl ) continue;  // OGRANICZENIE CHWILOWE - brak rysowanie MULTIPOLYHow


    if ( pushID )
    {
      nameList.append( extEl );              // dodaj obiekt do listy
      glPushName( (GLuint) nameList.at() );  // po³ó¿ na stos GL
    }

    // w³±czenie ¶wiate³
    for ( Light* light = _lightsList->first(); light; light = _lightsList->next() )
    {
      if ( !light->isEnabled() ) continue;
      
      if ( !light->isMovingWithCamera() )
      {
        glLightfv( light->GLname(), GL_POSITION, light->position4fv() );
        glLightfv( light->GLname(), GL_SPOT_DIRECTION, light->spotDirection3fv() );
      }
      else
      {
        glPushMatrix();
        glLoadIdentity();
          glLightfv( light->GLname(), GL_POSITION, light->position4fv() );
          glLightfv( light->GLname(), GL_SPOT_DIRECTION, light->spotDirection3fv() );
        glPopMatrix();
      }
    }    
    
    if ( _lightsAreDrawn && !pushID ) // rysuj kszta³ty ¶wiate³
    {
      if ( _lightsList )
      {
        for ( Light* light = _lightsList->first(); light; light = _lightsList->next() ) 
        drawLightShape( light );
      }
    }


     // **************** WIRE *********************************
     if ( _drawMethod == Wire )
     {
        // je¿eli obiekt jest zaznaczony, rysuj go innym kolorem
        bool isSelected = false;
        if ( _selectedList->findRef( hierIter ) != -1 ) isSelected = true;
        drawWired( extEl, isSelected );
     }

     // **************** SOLID *********************************
     if ( _drawMethod == Solid )
     {
       bool isSelected = false;
       if ( _selectedList->findRef( hierIter ) != -1 ) isSelected = true;
       drawSolid( extEl, isSelected );
     }


     // **************** TEXTURED *********************************
     if ( _drawMethod==Textured )
     {
       bool isSelected = false;
       if ( _selectedList->findRef( hierIter ) != -1 ) isSelected = true;
       
       if ( extEl->textureParams()->blendingEnabled() ) blendedList.append( extEl ); // dodaj do listy obiektów przezroczystych i przeskocz (narysujemy je pó¼niej)
       else drawTextured( extEl, isSelected );
     }

     
     
    if ( pushID ) glPopName(); // zdejmij aktualn± nazwê ze stosu GL


     if ( _axisIsDrawn && (!pushID) ) /* wyswietlanie indywidualnych ukl wsp */
     {
       drawElemAxis( extEl );
     }

    } // bryly (for iterator)

    
    // teraz dopiero rysujemy bry³y z bledningiem (o ile w³±czony jest tryb textured)
    if ( _drawMethod == Textured )
    {
      // najpierw sortujemy listê obiektów wzglêdem wspó³rzêdnej Z rosn±co
      if ( sortBlendedList() )
      // teraz je rysujemy od najdalszego do najbli¿szego
      {
        for ( ViElemePolyhExt* extEl = blendedList.first(); extEl; extEl = blendedList.next() )
        {
          bool isSelected = false;
          if ( _selectedList->findRef( ((ViNTreeNode*) extEl) ) != -1 ) isSelected = true;
          
          if ( pushID )
          {
            nameList.append( extEl );              // dodaj obiekt do listy
            glPushName( (GLuint) nameList.at() );  // po³ó¿ na stos GL
          }
          
          drawTextured( extEl, isSelected );
          
          if ( pushID ) glPopName();
        }
      }
    }
    
  } // if (!0L)

}


/*!
Metoda rysuje element jako druciak:
\param elem - obiekt klasy ViElemePolyhExt do narysowania,
\param isSelected - czy obiekt jest zaznaczony.
*/
void CellFrame::drawWired( ViElemePolyhExt* elem, bool isSelected )
{
  glDisable( GL_LIGHTING );
  glDisable( GL_TEXTURE_2D );
  glDisable( GL_BLEND );

  if ( isSelected ) qglColor( Options::wireSelectedColor() ); // kolor zaznaczenia
  else qglColor( Options::wireColor() ); // kolor domyslny dla WIRE

  glBegin(GL_LINES);
  for (ViElemePolyhExt::ConFaceIter faceIter = elem->ConBegin_GlbFace(); faceIter; ++faceIter)
  { // iteracja scianek
    for (ViElemePolyhFace::ConEdgeIter edgeIter = faceIter->ConBegin_GlbEdge(); edgeIter; ++edgeIter)
    {
        glVertex3f(edgeIter->GetFstVtx().x, edgeIter->GetFstVtx().y, edgeIter->GetFstVtx().z);
        glVertex3f(edgeIter->GetSndVtx().x, edgeIter->GetSndVtx().y, edgeIter->GetSndVtx().z);
    } // krawedzie
  } // scianki
  glEnd();
}



/*!
Metoda rysuje element w trybie prostego renderingu:
\param elem - obiekt klasy ViElemePolyhExt do narysowania,
\param isSelected - czy obiekt jest zaznaczony.
*/
void CellFrame::drawSolid( ViElemePolyhExt* elem, bool isSelected )
{
  glEnable ( GL_LIGHTING );
  glEnable ( GL_COLOR_MATERIAL );
  glDisable( GL_TEXTURE_2D );
  glDisable( GL_BLEND );
  
  /// wy³±czamy materia³
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   &no_material[0]);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   &no_material[0]);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  &no_material[0]);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,  &no_material[0]);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &no_shininess[0]);
  
  if ( isSelected ) qglColor( Options::solidSelectedColor() ); // kolor zaznaczenia
  else qglColor( Options::solidColor() ); // kolor domyslny dla SOLID
  
  glBegin(GL_TRIANGLES);
  for (ViElemePolyhExt::ConFaceIter faceIter = elem->ConBegin_GlbFace(); faceIter; ++faceIter)
  { // iteracja scianek
    for (ViElemePolyhFace::ConTriaIter triIter = faceIter->ConBegin_GlbTria(); triIter; ++triIter)
    { // iteracja trojkatow
        glNormal3f(faceIter->GetNormVect().x, faceIter->GetNormVect().y, faceIter->GetNormVect().z);
        glVertex3f((*triIter).Vtx0().x, (*triIter).Vtx0().y, (*triIter).Vtx0().z);
        glVertex3f((*triIter).Vtx1().x, (*triIter).Vtx1().y, (*triIter).Vtx1().z);
        glVertex3f((*triIter).Vtx2().x, (*triIter).Vtx2().y, (*triIter).Vtx2().z);
    } // trojkaty
  } // scianki
  glEnd();
}



/*!
Metoda rysuje element w trybie teksturowanym:
\param elem - obiekt klasy ViElemePolyhExt do narysowania,
\param isSelected - czy obiekt jest zaznaczony (tutaj nie wykorzystywane).
*/
void CellFrame::drawTextured( ViElemePolyhExt* elem, bool isSelected )
{
  glEnable ( GL_LIGHTING );
  glDisable( GL_COLOR_MATERIAL );
  glEnable ( GL_TEXTURE_2D );
  
  // element nie ma ani materia³u ani tekstury
  if ( !elem->materialEnabled()  &&  !elem->textureEnabled() )
  {
    drawSolid( elem, isSelected );
    return;
  }
  
  if ( elem->materialEnabled() ) // jezeli element ma w³±czony materia³
  {
     Material *mat = elem->material();
     glMaterialfv( elem->applyTo(), GL_AMBIENT,   mat->ambientColor4fv());
     glMaterialfv( elem->applyTo(), GL_DIFFUSE,   mat->diffuseColor4fv());
     glMaterialfv( elem->applyTo(), GL_SPECULAR,  mat->specularColor4fv());
     glMaterialfv( elem->applyTo(), GL_EMISSION,  mat->emissionColor4fv());
     glMaterialfv( elem->applyTo(), GL_SHININESS, mat->shininess1fv());
  }
  else // materia³ jest wy³±czony - ale w³±czona jest tekstura, wiêc materia³ ustawiamy na bia³y
  {
    glMaterialfv( elem->applyTo(), GL_AMBIENT,   white_material);
    glMaterialfv( elem->applyTo(), GL_DIFFUSE,   white_material);
    glMaterialfv( elem->applyTo(), GL_SPECULAR,  white_material);
    glMaterialfv( elem->applyTo(), GL_EMISSION,  white_material);
    glMaterialfv( elem->applyTo(), GL_SHININESS, no_shininess);
  }
  
  
  if ( elem->textureEnabled() && elem->textureParams()->GLTexID() ) // element ma w³±czon± teksturê i obraz
  {
    TextureParams* p = elem->textureParams();
    
    glBindTexture( GL_TEXTURE_2D, p->GLTexID() );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, p->magFilter() );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, p->minFilter() );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     p->wrapS() );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     p->wrapT() );
    glTexEnvf( GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE,         p->envMode() );
    
    if ( p->blendingEnabled() )
    {
      glEnable( GL_BLEND );
      glColor4f( 1.0f, 1.0f, 1.0f, 0.5f );
      glBlendFunc( p->blendSrcFactor(), p->blendDestFactor() );
    }
    else
    {
      glDisable( GL_BLEND );
    }
    
    // jeszcze reflecting
    
    GLfloat minW = p->minW();
    GLfloat minH = p->minH();
    GLfloat maxW = p->maxW();
    GLfloat maxH = p->maxH();
    
    bool first;
    
    glBegin(GL_TRIANGLES);
    for (ViElemePolyhExt::ConFaceIter faceIter = elem->ConBegin_GlbFace(); faceIter; ++faceIter)
    { // iteracja scianek
      first = true;
      for (ViElemePolyhFace::ConTriaIter triIter = faceIter->ConBegin_GlbTria(); triIter; ++triIter)
      { // iteracja trojkatow
          glNormal3f( faceIter->GetNormVect().x, faceIter->GetNormVect().y, faceIter->GetNormVect().z );
          if ( first ) glTexCoord2f( minW,maxH ); else glTexCoord2f( minW,maxH );
           glVertex3f( (*triIter).Vtx0().x, (*triIter).Vtx0().y, (*triIter).Vtx0().z );
          if ( first ) glTexCoord2f( minW,minH ); else glTexCoord2f( maxW,minH );
           glVertex3f( (*triIter).Vtx1().x, (*triIter).Vtx1().y, (*triIter).Vtx1().z );
          if ( first ) glTexCoord2f( maxW,minH ); else glTexCoord2f( maxW,maxH );
           glVertex3f( (*triIter).Vtx2().x, (*triIter).Vtx2().y, (*triIter).Vtx2().z );
        first = !first;
      } // trojkaty
    } // scianki
    glEnd();
  } /////////////////////////////// if textureEnabled() && TexID!=0
  
  
  
  else // rysuj bez tekstury
  {
    glDisable( GL_TEXTURE_2D );
    glBegin(GL_TRIANGLES);
    for (ViElemePolyhExt::ConFaceIter faceIter = elem->ConBegin_GlbFace(); faceIter; ++faceIter)
    { // iteracja scianek
      for (ViElemePolyhFace::ConTriaIter triIter = faceIter->ConBegin_GlbTria(); triIter; ++triIter)
      { // iteracja trojkatow
          glNormal3f( faceIter->GetNormVect().x, faceIter->GetNormVect().y, faceIter->GetNormVect().z );
          glVertex3f( (*triIter).Vtx0().x, (*triIter).Vtx0().y, (*triIter).Vtx0().z );
          glVertex3f( (*triIter).Vtx1().x, (*triIter).Vtx1().y, (*triIter).Vtx1().z );
          glVertex3f( (*triIter).Vtx2().x, (*triIter).Vtx2().y, (*triIter).Vtx2().z );
      } // trojkaty
    } // scianki
    glEnd();
  }
}

/*!
Metoda rysuje lokalny uk³ad wspó³rzêdnych dla elementu:
\param extEl - element, dla którego narysowany bêdzie lokalny uk³ad wspó³rzêdnych.
*/
void CellFrame::drawElemAxis( ViElemePolyhExt* extEl )
{
  if (!extEl) return;
  
  glPushMatrix();
    //Vector3f vo = extEl->IndivCoord_O();
    
    MatrixH3f mp = extEl->Mtx2ParentCoord();
    MatrixH3f mi = extEl->Mtx2IndivCoord();
    MatrixH3f m = extEl->Mtx2ElemeCoord();
    
    mi *= mp;
    m *= mi;
    
    Vector3f vo = mi.GetTrans_TAfterR(); // translacja
    Vector3f vr = mi.GetAng_XYZ_Deg();
    
    glTranslatef( vo.x, vo.y, vo.z );
    /*
    glRotatef( vr.x, 1.0, 0.0, 0.0 );
    glRotatef( vr.y, 0.0, 1.0, 0.0 );
    glRotatef( vr.z, 0.0, 0.0, 1.0 ); */
    // zorientowaæ osie

    // wyzerowane materia³y, aby nie dotyka³y osi
    glDisable( GL_TEXTURE_2D );
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT,   no_material );
    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE,   no_material );
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR,  no_material );
    glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION,  no_material );
    glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, no_shininess );

    // skalowanie osi - skala zale¿y tylko od finalnych rozmiarów bry³y
    Vector3f minVec( extEl->GlbOlnBox().Min() );
    Vector3f maxVec( extEl->GlbOlnBox().Max() );
    Vector3f diff(maxVec-minVec);
    float maxScale = QMAX( QMAX(abs( diff.x ), abs( diff.y )), abs( diff.z ) );
    
    // trzeba w³±czyæ ¶wiat³o ¿eby by³o widaæ osie
    
    GLboolean on;
    GLboolean texOn;
    glGetBooleanv ( GL_LIGHT0, &on );
    glGetBooleanv ( GL_TEXTURE_2D, &texOn );
    if (!on) glEnable( GL_LIGHT0 );
    if (texOn) glDisable( GL_TEXTURE_2D ); // wy³±czamy teksturê
     drawAxis( maxScale );
    if ( !on ) glDisable( GL_LIGHT0 ); // je¿eli by³o wy³±czone to wy³±czamy z powrotem
    if (texOn) glEnable( GL_TEXTURE_2D ); // w³±czamy teksturê, je¿eli by³a w³±czona
  glPopMatrix();
}
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////  R Y S O W A N I E ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////  S E L E K C J A //////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/*!
Metoda realizuj±ca selekcjê obiektu w przestrzeni OpenGL:
\param e - zdarzenie myszy, zawieraj±ce pozycjê kursora i naci¶niêty przycisk
*/
void CellFrame::select(const QMouseEvent *e)
{
  makeCurrent();

  const int SENSITIVITY = 4;       // obszar lapania pixeli przez kursor
  const int MAX_HITS = 64;         // max ilosc "zlapanych" obiektow

  static GLuint hits[MAX_HITS];

  glSelectBuffer( MAX_HITS, hits );
  glRenderMode ( GL_SELECT );        // przej¶cie w tryb selekcji obiektów
  glInitNames();

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  GLint viewport[4];
  camera()->getViewport(viewport);
  gluPickMatrix(static_cast <GLdouble> (e->x()), static_cast <GLdouble> (e->y()), SENSITIVITY, SENSITIVITY, viewport);

  camera()->loadProjectionMatrix(false); // nie resetuj aktualnej GL_PROJECTION
  camera()->loadModelViewMatrix();

  drawScene(true);
  glFlush();

  GLint hits_num = glRenderMode(GL_RENDER); // zwraca ilosc zaznaczonych obiektow (kazdy rekord po 4 pola)
  
  if (hits_num <= 0)       // nic nie zaznaczono
  {
   _selectedList->clear();
   //_selectedList->append( _multiPolyh ); // jako zaznaczenie dodajemy g³ówny mp
   emit userSelected(_selectedList); // wys³anie sygna³u
   setSelected(_selectedList);
   return;
  }

  // szukanie obiektu najblizszego userowi, czyli min Z
  unsigned int zMin = hits[1]; // zMin to pierwsze pole rekordu
  int selected = hits[3]; // nazwa pierwszego zaznaczonego obiektu
  for (int i=1; i<hits_num; ++i)
   if (hits[i*4+1] < zMin)    // obiekt jest blizej
   {
     zMin = hits[i*4+1];      
     selected = hits[i*4+3];
   }

  // selected zawiera teraz indeks najblizszego obiektu

  if (e->state() & Qt::ShiftButton)  // wcisniety SHIFT - dodaj obiekt do kolejki
  {
    _selectedList->append(nameList.at(selected));
  }
  else                              // jezeli nie - wyczysc kolejke i wstaw tylko ten
  {
   _selectedList->clear();
   _selectedList->append(nameList.at(selected));
  }

  setSelected(_selectedList);

  emit userSelected(_selectedList); // wys³anie listy zaznaczonych elementów
}
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////  S E L E K C J A //////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


/*!
Metoda (slot) w³±cza/wy³±cza wszystkie ¶wiat³a.
UWAGA! w³±czane s± tylko te ¶wiat³a, które maj± ustawione isEnabled() (s± w³±czone).
Metoda nie wp³ywa na o¶wietlenie globalne GL_LIGHTING - tym nie manipulujemy ze wzglêdu na rysowanie WIRE.
*/
void CellFrame::turnAllLights( bool on )
{
  makeCurrent();
  if ( !on )
  {
    glDisable( GL_LIGHT0 );
    glDisable( GL_LIGHT1 );
    glDisable( GL_LIGHT2 );
    glDisable( GL_LIGHT3 );
    glDisable( GL_LIGHT4 );
    glDisable( GL_LIGHT5 );
    glDisable( GL_LIGHT6 );
    glDisable( GL_LIGHT7 );
  }
  else
  {
    if ( !_lightsList ) return;
    
    for ( Light* light = _lightsList->first(); light; light = _lightsList->next() )
    {
      if ( light->isEnabled() ) glEnable( light->GLname() );
      else glDisable( light->GLname() );
    }
  }
  updateGL();
}


/*!
Metoda ustawia statyczny wska¼nik do listy wszystkich ¶wiate³.
Wywo³ywana jeden raz na pocz±tku.
\param lightsList - wska¼nik na listê ¶wiate³.
*/
void CellFrame::setLightsList( QPtrList<Light> *lightsList )
{
  _lightsList = lightsList;
}

/*!
Metoda ustawia parametry wszystkich ¶wiate³ z listy w przestrzeni OpenGL.
*/
void CellFrame::setAllLights()
{
  if ( !_lightsList ) return;
  
  turnAllLights( false );
  
  for ( Light* light = _lightsList->first(); light; light = _lightsList->next() )
  {
    setLight( light );
  }
  
  updateGL();
}


/*!
Metoda ustawia parametry aktualnie edytowanego ¶wiat³a dla widoku.
*/
void CellFrame::setLight( Light* light )
{   
  if ( !light ) return;
  if ( !light->createdSuccessfully() ) return;
  
  makeCurrent();
  
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  
  GLenum l = light->GLname();
    
  // ustawiamy wszystkie parametry ¶wiat³a
  glLightfv( l, GL_AMBIENT,  light->ambientColor4fv() );  // kolor AMBIENT
  glLightfv( l, GL_DIFFUSE,  light->diffuseColor4fv() );  // kolor DIFFUSE
  glLightfv( l, GL_SPECULAR, light->specularColor4fv() ); // kolor SPECULAR
  glLightf ( l, GL_SPOT_EXPONENT,  light->spotExponent() ); // exponenta
  glLightf ( l, GL_SPOT_CUTOFF  ,  light->spotCutOffAngle() ); // cutOff
  glLightf ( l, GL_CONSTANT_ATTENUATION,  light->constantAttenuation() ); //ca
  glLightf ( l, GL_LINEAR_ATTENUATION,    light->linearAttenuation() ); //ca
  glLightf ( l, GL_QUADRATIC_ATTENUATION, light->quadraticAttenuation() ); //ca
    
  if ( light->isMovingWithCamera() )
  {
    glLightfv( l, GL_POSITION, light->position4fv() );      // pozycja
    glLightfv( l, GL_SPOT_DIRECTION, light->spotDirection3fv() ); // kierunek
  }
  
  // i w³±czamy/wy³±czamy ¶wiat³o
  if ( light->isEnabled() ) glEnable( l ); else glDisable( l );
  updateGL();
}

/*!
Metoda uaktualnia warto¶æ koloru dla danego ¼ród³a ¶wiat³a:
\param GLcolorChanged - który parametr ¶wiat³a uleg³ zmianie (ambient, diffuse, itp.),
\param light - ¶wiat³o, któremu zmieniono warto¶æ.
*/
void CellFrame::updateColorForLight( GLenum GLcolorChanged, Light* light )
{
  makeCurrent();
  switch( GLcolorChanged )
  {
    case GL_AMBIENT  : glLightfv( light->GLname(), GLcolorChanged, light->ambientColor4fv() );  break;
    case GL_DIFFUSE  : glLightfv( light->GLname(), GLcolorChanged, light->diffuseColor4fv() );  break;
    case GL_SPECULAR : glLightfv( light->GLname(), GLcolorChanged, light->specularColor4fv() ); break;
    default : StatusBar::printStatusMsg( tr("updateColorForLight(): bad color type"), "CellFrame" ); return;
  }
  updateGL();
}



/*!
Metoda rysuje kszta³ty ¼róde³ ¶wiat³a w zale¿no¶ci od ich parametrów:
\param light - opisuje ¼ród³o ¶wiat³a,
\param scale - skala w jakie rysujemy ¶wiat³o ( parametr aktualnie nieu¿ywany).
*/
void CellFrame::drawLightShape( Light* light, float scale )
{
  if ( !light ) return;
  if ( light->isMovingWithCamera() ) return;
   
  const float r = camera()->sceneRadius()*scale / 30.0;
  static GLUquadric* quadric = gluNewQuadric();
  const GLfloat* pos = light->position4fv();
  
  GLfloat p[4];
  GLfloat d[3];
  
  glGetLightfv( light->GLname(), GL_POSITION, p); // pozycja ¶wiat³a przekszta³cona przez GL_MODELVIEW
  glGetLightfv( light->GLname(), GL_SPOT_DIRECTION, d ); // kierunek po przekszta³ceniu
  
  const GLfloat src[] = { p[0]/p[3], p[1]/p[3], p[2]/p[3] }; // pozycja ¼ród³a ¶wiat³a
  
  // ¶wiat³o jest w³±czone
  if ( light->isEnabled() )
  {
    if ( light->lightType() == Light::Positional ) ///////////////////// ¶wiat³o pozycycje = posiada ¼ród³o
    {
      // ¶wiat³o jest typu spotlight
      if ( light->isSpotlight() )
      {
        glPushMatrix();
        glLoadIdentity();
        glDisable( GL_LIGHTING );
        glDisable( GL_TEXTURE_2D );
          
        Vec dn( d[0], d[1], d[2] ); // wektor kierunku
        dn.normalize();             // normalizujemy wektor kierunku
         
        // rysuj kierunek ¶wiat³a - kropki
        glLineStipple( 2, 0x00FF );
        glEnable( GL_LINE_STIPPLE );
        qglColor( Options::lightsColor() ); // rysujemy kolorem grid-a
        glBegin( GL_LINES );
          glVertex3fv( src );
          glVertex3f( p[0]/p[3]+(dn.x*sceneRadius()*2), p[1]/p[3]+(dn.y*sceneRadius()*2), p[2]/p[3]+(dn.z*sceneRadius()*2) );
        glEnd();
          
        // rysuj sto¿ek ¶wiat³a
        GLfloat height = sceneRadius();           // wysoko¶æ sto¿ka
        GLfloat radius = r/2;                                                          // mniejsza podstawa
        GLfloat Radius = tan( (float) (light->spotCutOffAngle()*PI/180.0) ) * height;  // wiêksza podstawa
          
        // oblicz k±t obrotu
        Quaternion q( Vec(0.0,0.0,1.0), dn );   // kwaternion opisuje obrót wektora kierunku wokó³ osi
        Vec axis;
        GLfloat angle;
        q.getAxisAngle( axis, angle ); // kat zwracany w radianach
        angle *= 180.0/PI;
        
        glTranslatef( src[0], src[1], src[2] );               // przesuwamy sto¿ek na pozycjê ¼ród³a
        glRotatef( angle, axis.x, axis.y, axis.z );           // odpowiednio obracamy
        
        // rysuj sto¿ek
        glLineStipple( 1, 0x0F0F );
        gluQuadricDrawStyle( quadric, GLU_LINE );
        gluCylinder( quadric, radius, Radius, height, 10, 1 );
        
        glDisable( GL_LINE_STIPPLE );
        
        // rysuj latarkê
        gluQuadricDrawStyle( quadric, GLU_FILL );
        glTranslatef( 0.0, 0.0, -2*r );
        gluCylinder( quadric, r, 2*r, 2*r, 10, 10 ); // przód
        glTranslatef( 0.0, 0.0, -2*r );
        gluCylinder( quadric, r, r, 4*r, 10, 10 );     // korpus
        
        glEnable( GL_LIGHTING );
        glPopMatrix();
      }
      else // ¶wiat³o jest typu bulb (¿arówka)
      {
        glPushMatrix();
        glLoadIdentity();
          glTranslatef( src[0], src[1], src[2] );
          glDisable( GL_LIGHTING );
          glDisable( GL_TEXTURE_2D );
          qglColor( Options::lightsColor() );
          glScalef( 1.5, 1.5, 1.5 );
          gluSphere( quadric, r, 10, 10 ); // rysuje kulkê ¿arówki
          glTranslatef( 0.0, -0.8*r, 0.0 );
          glRotatef( 90.0, 1.0, 0.0, 0.0 );
          gluCylinder( quadric, r/2, r/2, r, 10, 10 ); // rysuje gwint
          glEnable( GL_LIGHTING );
        glPopMatrix();
      }
      
      // teraz rysujemy nazwê ¶wiat³a
      glPushMatrix();
      glLoadIdentity();
        glDisable( GL_LIGHTING );
        glDisable( GL_TEXTURE_2D );
        qglColor( Options::lightsColor() );
        Vec screenPos = camera()->projectedCoordinatesOf( Vec(pos[0], pos[1], pos[2]) );
        drawText(((int) screenPos[0])-20, ((int) screenPos[1])+30, light->name());
        glEnable( GL_LIGHTING );
      glPopMatrix();
      
    }
    else ///////////////////////////////////////////////////////////////// ¶wiat³o kierunkowe = brak ¼ród³a
    {     
      glDisable( GL_LIGHTING );
      glDisable( GL_TEXTURE_2D );
      glLineStipple( 2, 0x00FF );
      glEnable( GL_LINE_STIPPLE );
      qglColor( Options::lightsColor() );
      glBegin( GL_LINES );
        glVertex3fv( camera()->sceneCenter().address() );
        const float l = 5.0 * camera()->sceneRadius();
        glVertex3f( l*p[0], l*p[1], l*p[2] );
      glEnd();
      glDisable( GL_LINE_STIPPLE );
      glEnable( GL_LIGHTING );
    }
    
  } // if light->isEnabled();
}



/*!
Metoda ustawia czy poruszamy kamer±.
*/
void CellFrame::setCameraMoving(bool on)
{
  if (on)  // bindowanie myszy dla ruchow kamery
  {
     setMouseBinding(Qt::LeftButton, CAMERA, ROTATE);
     setMouseBinding(Qt::RightButton, CAMERA, TRANSLATE);
     setCursor(QCursor(QPixmap(Icons::cameraIcon())));
  }
  else    // przejscie w tryb modyfikatora
  {
     if (_modifier == 0L) setCursor(QCursor(Qt::ForbiddenCursor));
      else setCursor(_modifier->cursor()); // kursor aktualnego modyfikatora
  }

  _cameraIsMoving = on;
  cellWidget->cameraButton->setOn(on);
}

/*!
Metoda ustawia typu rzutowania.
*/
void CellFrame::setCameraType(Camera::Type type)
{
  camera()->setType(type);

  int i=-1;                                      // ustawienie Combo gdyby zmiane wywolano nie z CellWidget
  if (type==Camera::ORTHO) i=0; else i=1;
  cellWidget->viewProjCombo->setCurrentItem(i);
  updateGL();
}



/*!
Metoda ustawia tryb rysowania dla widoku:
\param drawMethod - okre¶la jaki to tryb: Wire, Solid, Textured
*/
void CellFrame::setDrawMethod(DrawMethod drawMethod)
{
  _drawMethod = drawMethod;

  makeCurrent();
  
  int i=-1;                                      // ustawienie Combo gdyby zmiane wywolano nie z CellWidget
  switch(drawMethod)
  {
    case Wire : i=0; break;
    case Solid: i=1; break;
    case Textured: i=2; break;
  }
  cellWidget->viewTypeCombo->setCurrentItem(i);
  updateGL();
}



/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////  S T A T I C //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

/*!
Metoda ustawia g³ówn± bry³ê do wy¶wietlania.
*/
void CellFrame::setMultiPolyh( ViMultiPolyh *multiPolyh )
{
  _multiPolyh = multiPolyh;
  updateGLForAllViewers();
}


/*!
Metoda ustawia listê bry³ zaznaczonych.
*/
void CellFrame::setSelected( QPtrList<ViNTreeNode> *selectedList )
{
  _selectedList = selectedList;
  updateGLForAllViewers();
}


/*!
Metoda ustawia modyfikator obowi±zuj±cy dla wszystkich widoków.
*/
void CellFrame::setModifier(MModifier *modifier)
{
  _modifier = modifier;
}

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////  S T A T I C //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////



/*!
Metoda nadmiarowa - jest tylko dlatego, ¿e nie mo¿na ³±czyæ slotów statycznych.
Wywo³uje metodê statyczn± setSelected().
*/
void CellFrame::setSelectedSlot( QPtrList<ViNTreeNode> *selectedList )
{
  CellFrame::setSelected( selectedList );
}

/*!
Metoda dopasowuje widok do rozmiarów sceny, tak ¿eby wszystko by³o widoczne.
*/
void CellFrame::showAllScene()
{
  if ((_multiPolyh == 0L) || (!_multiPolyh->HasDescendants())) // je¿eli mp jest pusty - przywróæ ustawienia domy¶lne
  { 
   glDisable( GL_BLEND );
   setSceneCenter( 0.0, 0.0, 0.0 );
   setSceneRadius( 2.0 );
   showEntireScene();
   return;
  }

  // obrys prostopadloscienny calej bryly zlozonej
  Vector3f min(_multiPolyh->GlbOlnBox().Min());
  Vector3f max(_multiPolyh->GlbOlnBox().Max());

  // wyliczenie srodka i promienia sceny
  Vec vMax(max.x,max.y,max.z);
  Vec mid((min.x+max.x)/2, (min.y+max.y)/2, (min.z+max.z)/2); // srodek przekatnej prostopadloscianu ograniczajacego
  float r = Vec::Vec(vMax-mid).norm(); // promien od srodka do rogu prostopadloscianu

  
  setSceneCenter(mid); // srodek sceny w srodku prostopadloscianu
  camera()->setRevolveAroundPoint(0.0, 0.0, 0.0);
//  camera()->setRevolveAroundPoint(mid);
//  setSceneCenter(0.0, 0.0, 0.0);

  setSceneRadius(r * 1.3);   // promieñ trochê powiêkszony  

  showEntireScene();   // poka¿ ca³± scenê
}



/*!
Metoda ustawia kamerê w okre¶lony (predefiniowany) sposób - spojrzenie z boku, z przodu lub z góry sceny.
Podwojne klikniêcie na scenie powoduje powrót do tego ustawienia (obs³uga mouseDoubleClickEvent()).
\param direction - jest predefiniowanym kierunkiem.
*/
void CellFrame::setViewDirection(int direction)
{
  Vec vec;

  switch (direction)
  {
     case 0 : return; // Custom - nic nie zmienia, ustawia sie samoczynnie, jezeli user rusza kamera
     case 1 : { // Top
                vec.x = 0.0;
                vec.y = sceneRadius();
                vec.z = 0.0;
                camera()->setUpVector(0.0, 0.0, -1.0);
                break;
              }
     case 2 : { // Side
                vec.x = sceneRadius();
                vec.y = 0.0;
                vec.z = 0.0;
                camera()->setUpVector(0.0, 1.0, 0.0);
                break;
              }
     case 3 : { // Front
                vec.x = 0.0;
                vec.y = 0.0;
                vec.z = sceneRadius();
                camera()->setUpVector(0.0, 1.0, 0.0);                
                break;
              }
     default : return; // taka sytuacja nie zachodzi
  }

  camera()->setPosition(vec);
  camera()->lookAt(0.0, 0.0, 0.0);
  showAllScene();
  cellWidget->viewDirCombo->setCurrentItem(direction);
}


/*!
Metoda rysuje siatkê w p³aszczy¼nie XZ (poziom±).
*/
void CellFrame::drawGridXZ(/*float length, float width, float nbSub*/)
{
  /*
  glDisable(GL_LIGHTING);
  glLineWidth(1.0);

  float length = sceneRadius();
  float width = length;
  float nbSub = 10.0;

  glBegin(GL_LINES);
  for (int i=0; i<=nbSub; ++i)
    {
      glVertex3f(length*(2*i/nbSub-1.0), 0, -width);
      glVertex3f(length*(2*i/nbSub-1.0), 0, +width);
      glVertex3f(-length, 0, width*(2*i/nbSub-1.0));
      glVertex3f( length, 0, width*(2*i/nbSub-1.0));
    }
  glEnd();
  */

  glPushMatrix();
   glRotatef(90.0, 1.0, 0.0, 0.0);
   GLfloat r = sceneRadius()/1.1; //sceneRadius(); bylo /1.4
   glScalef(r, r, r);          // skaluj siatke wg promienia sceny
   drawGrid();
  glPopMatrix();
}




// rysuje siatkê 3D
/*
void CellFrame::drawGrid3D()
{
  //glLineStipple( 1, 0xF0F0 );
  //glEnable( GL_LINE_STIPPLE );
  
  float r = sceneRadius();
  
  glPushMatrix();
  for ( int i=0; i<5; i++ )
  {
    drawGridXZ();
    glTranslatef( 0.0, 0.2*r, 0.0 );
  }
  glPopMatrix();
  
  //glDisable( GL_LINE_STIPPLE );
}
*/

/*!
Metoda rysuje siatkê 3D.
*/
void CellFrame::drawGrid3D()
{
//  drawGridXZ();
  GLfloat r = sceneRadius()/1.1;
  
  glPushMatrix();
    glTranslatef( -r, 0.0, 0.0 );
    glTranslatef( 0.0, r, 0.0 );
    glRotatef( 90.0, 0.0, 0.0, 1.0 );
    drawGridXZ();
  glPopMatrix();
    
  glPushMatrix();
    glTranslatef( 0.0, 0.0, -r );
    glTranslatef( 0.0, r, 0.0 );
    glRotatef( 90.0, 1.0, 0.0, 0.0 );
    drawGridXZ();
  glPopMatrix();
}



/*!
Metoda maksymalizuje okno widoku, minimalizuj±c pozosta³e.
WARUNEK - CellFrame jest dzieckiem obiektu klasy QSplitter, który ma równie¿ rodzica QSplitter.
Sposób dzia³ania tej metody jest ¶ci¶le uzale¿niony od struktury splitterów, w których obiekt
CellFrame egzystuje - struktura ta budowana jest w obiekcie klasy Workspace.
*/
void CellFrame::maximize()
{
  // zwijanie okien nale¿±cych do innych splitterów, oprócz aktualnego
  // zwijamy wszystkie widgety nale¿±ce do tego samego splittera
  QSplitter *parentSplit = dynamic_cast<QSplitter*> (parentWidget());
  QObjectList objectList = *(parentSplit->children());
  QValueList<int> sizes;
  for (QObject *obj = objectList.first(); obj; obj = objectList.next()) // iterujemy jego dzieci
  {
    if (obj->isA(this->className())) // teraz zwijane s± tylko obiekty klasy CellFrame - mo¿na inne
    {
      (obj == (dynamic_cast<QObject*>(this))) ? sizes.push_back(100) : sizes.push_back(0); // zostaje tylko aktualny
    }
  }
  parentSplit->setSizes(sizes);


  // teraz zwijamy wszystkie potomne splittery, oprócz aktualnego
  QSplitter *mainSplit = dynamic_cast<QSplitter*> (parentWidget()->parentWidget()); // g³ówny splitter
  QObjectList mainSplitObjList = *(mainSplit->children()); // dzieci g³ównego splittera
  sizes.clear();
  for (QObject *split = mainSplitObjList.first(); split; split = mainSplitObjList.next())
  {
    QSplitter *splitter = dynamic_cast<QSplitter*> (split);
    if (splitter) // znaleziono splitter
    {
      (splitter == parentSplit) ? sizes.push_back(100) : sizes.push_back(0); // nasz splitter zostaje
    }
  }
  mainSplit->setSizes(sizes);
}


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////  Z D A R Z E N I A   M Y S Z Y ////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

/*!
Gdy mysz wjedzie na CellFrame, automatycznie ustawiany jest dla niej focus klawiatury.
*/
void CellFrame::enterEvent(QEvent*)
{
  this->setFocus();
}

/*!
Zdarzenie naci¶niêcia przycisku myszy - rozpoczynamy dzia³anie modyfikatora.
*/
void CellFrame::mousePressEvent(QMouseEvent *e)
{
     // kamera ma najwy¿szy priorytet - lewy przycisk=rotate, prawy=translate
  if ( _cameraIsMoving ) { QGLViewer::mousePressEvent(e); return; }
  
  if (_multiPolyh == 0L) return; // pustych obiektow nie obslugujemy
  
////////////////////////////////////////////////////////////////////////////////// MODYFIKATOR
  if (e->button() == Qt::LeftButton)   // lewy klik - dziala modyfikator
  {
   if (_modifier->type() == MModifier::M_SELECT) {select(e); return;} // dla modyfikatora selekcji nie ma zadnych akcji - tylko selekcja

   //select(e);  // obojetnie jaki modyfikator - zaznacza sobie najpierw obiekt

//////////////////////////////////////////////////////////////////// przygotuj odpowiedni modyfikator   
   // modyfikator LINKOWANIA
   if (_modifier->type() == MModifier::M_LINK) 
   {
     if (_selectedList->isEmpty()) return; // musza byc wczesniej zaznaczone jakies obiekty zrodlowe
   
     QPtrList<ViNTreeNode> *oldList = new QPtrList<ViNTreeNode>(*_selectedList); // kopiuj wszystkie zaznaczenia
     select(e); // zaznacz obiekt docelowy
     if (_selectedList->isEmpty()) // jezeli nie wybrano obiektu docelowego - bedzie nim glowny MULTIPOLYH
     {
       *_selectedList = *oldList;  // skopiuj poprzednia zawartosc
       _selectedList->append(_multiPolyh);  // dodaj na koniec glowny obiekt zlozony
     }
     else  // zaznaczono obiekt docelowy
     {
       ViNTreeNode *_selected = _selectedList->last(); // to jest cel
       // teraz trzeba sprawdziæ czy cel nie nale¿y przypadkiem do oldlist (krn±brny user)
       if ( oldList->findRef( _selected ) != -1 )
       {
          // niestety user chce nas zrobiæ
         *_selectedList = *oldList; // przywracamy star± listê i odchodzimy zniesmaczeni
         return;
       }
       
       *_selectedList = *oldList;  // skopiuj poprzednia zawartosc
       _selectedList->append(_selected); // dodaj cel na koniec listy
     }

     delete oldList; // czy bezpieczne? NIE WOLNO skasowac obiektow wskazywanych !
   }
   // koniec modyfikatora LINKOWANIA

   
   // je¿eli mamy do czynienia z modyfikatorami ¶wiate³ - w³±czamy rysowania kszta³tów ¶wiate³
   if ( (_modifier->type() == MModifier::M_TRANSLIGHTPOS) || (_modifier->type() == MModifier::M_TRANSLIGHTDIR) ) setDrawLights( true );
   
   // podobnie jak wy¿ej, je¿eli mamy do czynienia z modyfikatorami uk³adów wspó³rzêdnych -
   // automatycznie w³±czamy wy¶wietlanie osi
   if ( ( _modifier->type() == MModifier::M_TRANSLATECOORDS ) || ( _modifier->type() == MModifier::M_ROTATECOORDS ) ) setDrawAxisXYZ( true );
              
   
////////////////////////////////////////////////////////////// koniec przygotowañ - uruchom modyfikator  
   makeCurrent();

   _modifier->mousePressEvent(e, camera(), _selectedList); // metoda modyfikatora modyfikujaca wybrany obiekt
   
   /////////////////////////// je¿eli zadzia³a³ modyfikator linkowania trzeba wys³aæ sygna³
   /////////////////////////// o zmianie struktury obiektu
   if ( _modifier->type() == MModifier::M_LINK ) emit mphStructureChanged();
   
   
   // g³ównego multiPolyha nie ruszamy! nie wolno go modyfikowaæ - to eter, woda w której p³ywaj± 
   // wszystkie rybki ( i jakkolwiek teoria istnienia eteru zosta³a z hukiem obalona to woda jest niezbicie // namacalnym ¶wiadectwem wszelkiej egzystencji )
   if ( _selectedList->last() == _multiPolyh ) _selectedList->removeLast();
   
   refresh();
   return;
  }
////////////////////////////////////////////////////////////////////////////////// MODYFIKATOR

  if (e->button() == Qt::RightButton)    // prawy klik - popupMenu z wlasciwosciami obiektu
  {
    // dla lewego klawisza mamy popupMenu (i ewentualnie wczesniej select)
    //select(e);
    popupMenu->exec( QCursor::pos() );
  }
}


/*!
Zdarzenie ruchu mysz± (przy wci¶niêtym przycisku).
Dzia³a modyfikator.
*/
void CellFrame::mouseMoveEvent(QMouseEvent *e)
{
  if (_cameraIsMoving) QGLViewer::mouseMoveEvent(e);
  else
  {
   if (_multiPolyh == 0L) return; // pustych obiektow nie obslugujemy
   if (_modifier->type() == MModifier::M_SELECT) return; // dla modyfikatora selecji nie ma zadnych akcji

////////////////////////////////////////////////////////////////////////////////// MODYFIKATOR
    makeCurrent();

    QString info;
    _modifier->mouseMoveEvent(e, camera(), info); // metoda modyfikatora modyfikujaca wybrany obiekt

    setInfo(info);
   
    refresh();
////////////////////////////////////////////////////////////////////////////////// MODYFIKATOR   
  }
}


/*!
Zdarzenie zwolnienia przycisku myszy.
*/
void CellFrame::mouseReleaseEvent(QMouseEvent *e)
{
  if (_cameraIsMoving) QGLViewer::mouseReleaseEvent(e);
  else
  {
   if (_multiPolyh == 0L) return; // pustych obiektow nie obslugujemy
   if (_modifier->type() == MModifier::M_SELECT) return; // dla modyfikatora selecji nie ma zadnych akcji
   
////////////////////////////////////////////////////////////////////////////////// MODYFIKATOR
    makeCurrent();

    _modifier->mouseReleaseEvent(e); // metoda modyfikatora modyfikujaca wybrany obiekt
    emit userSelected( _selectedList );

    setInfo("");
        
    refresh();
////////////////////////////////////////////////////////////////////////////////// MODYFIKATOR
  }
}


/*!
Podwójne klikniêcie mysza - przywracany jest odpowiedni widok dla okna.
*/
void CellFrame::mouseDoubleClickEvent(QMouseEvent *)
{
 int viewDir = cellWidget->viewDirCombo->currentItem();
 setViewDirection(viewDir); // direction jest jednym z predefiniowanych kierunkow
}

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////  Z D A R Z E N I A   M Y S Z Y ////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////////////////////////////////////////////////// PopupMenu
/*!
Metoda wywo³ywana w momencie wywo³ania popupMenu - wy³±cza opcje zale¿ne od selekcji.
*/
void CellFrame::popupAboutToShow()
{
  bool ok = true;
  if ( _selectedList->isEmpty() ) ok = false; // nie ma ¿adnego zaznaczonego obiektu
  
  popupMenu->setItemEnabled( TransID, ok );
  popupMenu->setItemEnabled( RotID, ok );
  popupMenu->setItemEnabled( ScaleID, ok );
  popupMenu->setItemEnabled( LinkID, ok );
  popupMenu->setItemEnabled( TransCoordsID, ok );
  popupMenu->setItemEnabled( RotCoordsID, ok );
  popupMenu->setItemEnabled( MatEditID, ok );
  popupMenu->setItemEnabled( TexEditID, ok );
  //popupMenu->setItemEnabled( KinematicID, ok );
  popupMenu->setItemEnabled( DeleteID, ok );
  popupMenu->setItemEnabled( CopyID, ok );
  popupMenu->setItemEnabled( CutID, ok );
  
  ( _clipboard->isEmpty() ) ? ok=false : ok=true;
  popupMenu->setItemEnabled( PasteID, ok );
}

/*!
Metoda wywo³uje odpowiedni± akcjê w zale¿no¶ci od pozycji wybranej z popupMenu.
*/
void CellFrame::choosedFromPopup( int n )
{
  switch ( n )
  {
    case SelectID      : emit setModifierFromCellFrame( MModifier::M_SELECT ); break;
    case CameraID      : setCameraMoving( true ); break;
    case TransID       : emit setModifierFromCellFrame( MModifier::M_TRANSLATE ); break;
    case RotID         : emit setModifierFromCellFrame( MModifier::M_ROTATE ); break;
    case ScaleID       : emit setModifierFromCellFrame( MModifier::M_SCALE ); break;
    case LinkID        : emit setModifierFromCellFrame( MModifier::M_LINK ); break;
    case TransCoordsID : emit setModifierFromCellFrame( MModifier::M_TRANSLATECOORDS ); break;
    case RotCoordsID   : emit setModifierFromCellFrame( MModifier::M_ROTATECOORDS ); break;
    case MatEditID     : { MaterialEditor *mt = new MaterialEditor( 0, _selectedList ); } break;
    case TexEditID     : { MaterialEditor *mt = new MaterialEditor( 1, _selectedList ); } break;
    case KinematicID   : { KinematicsEditor *ke = new KinematicsEditor( _selectedList ); } break;
    case TransLightID  : emit setModifierFromCellFrame( MModifier::M_TRANSLIGHTPOS ); break;
    case DirLightID    : emit setModifierFromCellFrame( MModifier::M_TRANSLIGHTDIR ); break;
    case DeleteID      : deleteSelectedObjects(); emit userSelected( _selectedList ); break;
    case CopyID        : clipboardCopy(); break;
    case PasteID       : {
                          clipboardPaste(); 
                          emit userSelected( _selectedList ); 
                          emit mphStructureChanged();
                         } break;
    case CutID         : {
                          clipboardCut(); 
                          emit userSelected( _selectedList ); 
                          emit mphStructureChanged();
                        } break;
    case SelectAllID   : selectAll(); break;
    default : break;
  }
}

/////////////////////////////////////////////////////////////////////////////////// PopupMenu



/*!
Metoda usuwa wszystkie zaznaczone obiekty (znajduj±ce siê na li¶cie _selectedList),
po czym od¶wie¿a wszystkie widoki i wysy³a sygna³ nowej listy _selectedList.
Metoda nigdy nie usunie g³ównego obiektu z³o¿onego.
*/
void CellFrame::deleteSelectedObjects()
{
  if ( _selectedList->isEmpty() ) return;
  
  ViElemePolyhExt* extEl = 0L;
  
  for (ViNTreeNode *_selected = _selectedList->first(); _selected; _selected = _selectedList->next())
  {
    // je¿eli jest to element - usuñ teksturê zaalokowan± przez niego
    if ( _selected->GetInheritorType() == IT_ELEMEPOLYH )
    {
      extEl = dynamic_cast<ViElemePolyhExt*> (_selected);
      TextureManager::deleteTextureFromObject( extEl );
      _selected->DetachNode();
    }
    else
    // je¿eli MPH - usuñ tekstury elementom
    if ( _selected->GetInheritorType() == IT_MULTIPOLYH )
    {
      if ( ((ViMultiPolyh*) _selected) != _multiPolyh ) // je¿eli jest MPH != od g³ównej bry³y
      { // iteruj jego potomków i usuñ zaalokowane przez nich tekstury
        ViMultiPolyh *mph = (ViMultiPolyh*) _selected;
        for ( ViMultiPolyh::ConElemePolyhIter iter = mph->ConBegin_ElemePolyh(); iter; ++iter )
        {
          extEl = (ViElemePolyhExt*) & (*iter);
          TextureManager::deleteTextureFromObject( extEl );
        }
        _selected->DetachNode();
      }
    }
    // delete _selected
  }
  
  _selectedList->clear();  // wyczy¶æ listê zaznaczonych obiektów
  
  Kernel::computeScene();
  CellFrame::refresh();
}





/////////////////////////////////////////////////////////////////////////////////////  SCHOWEK

/*!
Metoda Copy.
Metoda czy¶ci schowek i tworzy nowe obiekty na podstawie wska¼ników z _selectedList.
*/
bool CellFrame::clipboardCopy()
{
  if ( _selectedList->isEmpty() ) return false;
  
  _clipboard->setAutoDelete( true );
  _clipboard->clear();
  
  for ( ViNTreeNode *s = _selectedList->first(); s; s = _selectedList->next() )
  {
    switch ( s->GetInheritorType() )
    {
      case IT_MULTIPOLYH : break;
      case IT_ELEMEPOLYH : {
                             ViElemePolyhExt *extEl = dynamic_cast<ViElemePolyhExt*> (s);
                             ViElemePolyhExt *newEl = new ViElemePolyhExt( *extEl );
                             _clipboard->append( newEl );       
                           } break;
      default : break;
    }
  }
  return true;
}

/*!
Metoda Paste.
Metoda wkleja zawarto¶æ schowka i do³±cza obiekty do pierwszego zaznaczonego obiektu
lub do g³ównego obiektu z³o¿onego, je¿eli nie ma zaznaczenia.
Nowo utworzone obiekty zostaj± zaznaczone (poprzednie odznaczone).
*/
bool CellFrame::clipboardPaste()
{
  if ( _clipboard->isEmpty() ) return false;
  
  ViNTreeNode *parent;
  if ( _selectedList->isEmpty() ) parent = _multiPolyh; else parent = _selectedList->last();
  
  _selectedList->clear();
  
  for ( ViNTreeNode *c = _clipboard->first(); c; c = _clipboard->next() )
  {
    switch ( c->GetInheritorType() )
    {
      case IT_MULTIPOLYH : break;
      case IT_ELEMEPOLYH : {
                             ViElemePolyhExt *extEl = dynamic_cast<ViElemePolyhExt*> (c);
                             ViElemePolyhExt *newEl = new ViElemePolyhExt( *extEl );
                             parent->AddNode( newEl );
                             _selectedList->append( newEl );
                           } break;
      default : break;
    }
  }
  
  Kernel::computeScene();
  CellFrame::refresh();
  
  return true;
}


/*!
Metoda Cut.
Metoda czy¶ci schowek, kopiuje zawarto¶æ _selectedList do schowka i usuwa kopiowane obiekty.
*/
void CellFrame::clipboardCut()
{
  if ( clipboardCopy() ) deleteSelectedObjects();
}
////////////////////////////////////////////////////////////////////////////////////  SCHOWEK


/*!
// Metoda zaznacza wszystkie obiekty na scenie.
*/
void CellFrame::selectAll()
{
  _selectedList->clear();
  for (ViNTreeNode::ConPolyhIter hierIter = _multiPolyh->ConBegin_PolyhHierList(); hierIter; ++hierIter)
  {
    _selectedList->append( hierIter );
  }
  emit userSelected( _selectedList );
  updateGLForAllViewers();
}



/*!
Przechwycenie i obs³uga zdarzenia klawiatury.
*/
void CellFrame::keyPressEvent(QKeyEvent *e)
{
  float sense;
  switch (e->key())
  {
    case Key_QuoteLeft : {                          // '`' - pokaz cellWidget
                            (cellWidget->isVisible()) ? cellWidget->hide() : cellWidget->show();
                         } break;
    case Key_A : {
                    if (e->state() == Qt::AltButton)        // 'ALT+A' - pokaz osie
                    {
                      setDrawAxisXYZ( !_axisIsDrawn );
                    } else
                    if ( e->state() == Qt::ControlButton ) // 'CTRL+A' - zaznacz wszystko
                    {
                      selectAll();
                    } 
                    else e->ignore();
                 } break;
    case Key_C : {
                    if ( e->state() == Qt::ControlButton ) 
                    {
                      CellFrame::clipboardCopy(); // 'CTRL+C' - kopiuj
                    }
                    else setCameraMoving( !_cameraIsMoving );               // 'C' - kamera
                 } break;
    case Key_Delete : {                                   // 'Delete' - usuniecie zaznaczonych obiektow
                        CellFrame::deleteSelectedObjects();
                        emit userSelected(_selectedList); // wy¶lij listê (pust±)
                        emit mphStructureChanged();
                      } break;
    case Key_F : showAllScene(); break;                     // 'F' - dopasuj scene do okna widoku
    case Key_G : setDrawGridXZ( !_gridIsDrawn ); break;     // 'G' - pokaz siatke
    case Key_H : setDrawGrid3D( !_grid3DIsDrawn ); break;     // 'H' - pokaz siatke 3D
    case Key_L : {                                          // 'ALT+L' - poka¿ kszta³ty ¶wiate³
                    if ( e->state() == Qt::AltButton )
                    {
                      setDrawLights( !_lightsAreDrawn );
                    } else  e->ignore();
                 }; break;
    case Key_M : {                                                    // 'CTRL+M' - maksymalizuje widok
                    if (e->state() == Qt::ControlButton) maximize();
                  } break;
    case Key_O : setCameraType(Camera::ORTHO); break;                 // 'O' - rzutowania prostopadle
    case Key_P : setCameraType(Camera::PERSPECTIVE); break;           // 'P' - rzutowania perspektywiczne
    case Key_S : {
                    if (e->state() == Qt::ControlButton) saveSnapshot(); // 'CTRL+S' - zapisz zrzut ekranu
                    else
                    if (e->state() == Qt::AltButton) setDrawMethod(Solid); // 'ALT+S' - rysuj metoda SOLID
                    else e->ignore();
                 } break;
    case Key_W : {
                    if (e->state() == Qt::AltButton) setDrawMethod(Wire);  // 'ALT+W' - rysuj metoda WIRE
                    else e->ignore();
                  } break;
    case Key_T : {
                    if (e->state() == Qt::AltButton) setDrawMethod(Textured); // 'ALT+T' - TEXTURED
                    else e->ignore();
                    break;
                 }
    case Key_V : {
                    if ( e->state() == Qt::ControlButton )  // 'CTRL+V' - wklej
                    {
                      CellFrame::clipboardPaste();
                      emit userSelected( _selectedList );
                      emit mphStructureChanged();
                    }
                    else e->ignore();
                 } break;
    case Key_X : {
                    if ( e->state() == Qt::ControlButton ) CellFrame::clipboardCut();   // 'CTRL+X' - wytnij
                    else e->ignore();
                 } break;
    case Key_Down: {                                   // 'stralka w dol' - ZOOM OUT
                  if (e->state() == Qt::ShiftButton) sense=0.001; else sense=0.1;
                  Vec trans(0.0, 0.0, camera()->sceneRadius()*sense);
                  camera()->frame()->translate(camera()->frame()->inverseTransformOf(trans));
                  updateGL();
                 }
                 break;
    case Key_Up: {                                 // 'stralka w gore' - ZOOM IN
                    if (e->state() == Qt::ShiftButton) sense=0.001; else sense=0.1;
                    Vec trans(0.0, 0.0, -camera()->sceneRadius()*sense);
                    camera()->frame()->translate(camera()->frame()->inverseTransformOf(trans));
                    updateGL();
                   }
                   break;
    case Key_Left: {                                   // 'stralka w lewo' - przesun widok w lewo
                    if (e->state() == Qt::ShiftButton) sense=0.001; else sense=0.1;
                    Vec trans(-camera()->sceneRadius()*sense, 0.0, 0.0);
                    camera()->frame()->translate(camera()->frame()->inverseTransformOf(trans));
                    updateGL();
                   }
                   break;
    case Key_Right: {                                 // 'stralka w prawo' - przesun widok w prawo
                     if (e->state() == Qt::ShiftButton) sense=0.001; else sense=0.1;
                     Vec trans(camera()->sceneRadius()*sense, 0.0, 0.0);
                     camera()->frame()->translate(camera()->frame()->inverseTransformOf(trans));
                     updateGL();
                    }
                    break;

    default : e->ignore(); break; // jezeli inny klawisz to przekaz go dalej
  }
}


