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
#define TransLightID   5
#define DirLightID     6
#define CameraID       7
#define DeleteID       8
#define KinematicsID   9
#define SimulationID  10
#define SelectAllID   11


#include "cellframe.h"



using namespace qglviewer;


// zmienne statyczne
QPtrList<ViMultiPolyh> CellFrame::nameList; // przechowuje odpowiednie warto¶ci liczbowe obiektów

ViScene* CellFrame::_scene = 0L;  // wska¼nik do wy¶wietlanek sceny

QPtrList<ViMultiPolyh>* CellFrame::_selectedList = new QPtrList<ViMultiPolyh>; // lista zaznaczonych

QPtrList<Light>* CellFrame::_lightsList = 0L;

MModifier* CellFrame::_modifier = 0L; // obowi±zuj±cy modyfikator


const GLfloat CellFrame::no_material[] = { 0.0, 0.0, 0.0, 1.0 };  // pusty materia³
const GLfloat CellFrame::no_shininess[] = { 0.0 };                // zerowa po³yskliwo¶æ
const GLfloat CellFrame::white_material[] = { 1.0, 1.0, 1.0, 1.0 };  // bia³y materia³


GLuint CellFrame::_cubeDL = 0;
GLuint CellFrame::_squareDL = 0;
GLuint CellFrame::_hLineDL = 0;
GLuint CellFrame::_vLineDL = 0;

void CellFrame::createDL()
{
  if ( _cubeDL != 0 ) return;
  
  _cubeDL = glGenLists( 1 ); // generuj id
  _squareDL = glGenLists( 1 );
  _vLineDL = glGenLists( 1 );
  _hLineDL = glGenLists( 1 );
  
  glNewList( _vLineDL, GL_COMPILE );
    glBegin( GL_LINES );
      glVertex3f( 0.0, -0.5, 0.0 );
      glVertex3f( 0.0, 0.5, 0.0 );
    glEnd();
  glEndList();

  glNewList( _hLineDL, GL_COMPILE );
    glPushMatrix();
      glRotatef( 90.0, 0.0, 0.0, 1.0 );
      glCallList( _vLineDL );
    glPopMatrix();  
  glEndList();
      
  glNewList( _squareDL, GL_COMPILE );
    glPushMatrix();
      glTranslatef( -0.5, 0.0, 0.0 ); // lewy ¶rodek
      glCallList( _vLineDL );
    glPopMatrix();
    glPushMatrix();
      glTranslatef( 0.0, 0.5, 0.0 ); // gorny ¶rodek
      glCallList( _hLineDL );
    glPopMatrix();
    glPushMatrix();
      glTranslatef( 0.5, 0.0, 0.0 ); // prawy ¶rodek
      glCallList( _vLineDL );
    glPopMatrix();
    glPushMatrix();
      glTranslatef( 0.0, -0.5, 0.0 ); //dolny ¶rodek
      glCallList( _hLineDL );
    glPopMatrix();
  glEndList();
  
  glNewList( _cubeDL, GL_COMPILE );
    glPushMatrix();
      glTranslatef( -0.5, 0.0, 0.0 ); //lewa ¶ciana
      glRotatef( 90.0, 0.0, 1.0, 0.0 );
      glCallList( _squareDL );
    glPopMatrix();
    glPushMatrix();
      glTranslatef(  0.0, 0.0, -0.5 ); // tylna ¶ciana
      glCallList( _squareDL );
    glPopMatrix();
    glPushMatrix();
      glTranslatef( 0.5, 0.0, 0.0 ); // prawa ¶ciana
      glRotatef( 90.0, 0.0, 1.0, 0.0 );
      glCallList( _squareDL );
    glPopMatrix();
    glPushMatrix();
      glTranslatef( 0.0, 0.0, 0.5 ); // przednia ¶ciana
      glCallList( _squareDL );
    glPopMatrix();
    glPushMatrix();
      glTranslatef( 0.0, -0.5, 0.0 ); // dolna
      glRotatef( 90.0, 1.0, 0.0, 0.0 );
      glCallList( _squareDL );
    glPopMatrix();
    glPushMatrix();
      glTranslatef( 0.0, 0.5, 0.0 ); // górna
      glRotatef( 90.0, 1.0, 0.0, 0.0 );
      glCallList( _squareDL );
    glPopMatrix();
  glEndList();
}




// metoda sortuje listê obiektów przezroczystych wzglêdem wspó³rzêdnej Z (wzgl kamery)
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
  _grid3DIsDrawn = false; // na poczatku wy³±cz siatkê 3D
  _boxesAreDrawn = false; // nie rysujemy obrysów
  _axisIsDrawn = false; // wy³±cz osie
  _lightsAreDrawn = false; // wy³±cz kszta³ty ¶wiate³
  _fpsDisplayed = false; // wy³±cz wy¶wietlanie ilo¶ci klatek na sekundê
  _cameraIsMoving = false; // na pocz±tku nie ma poruszania kamer±
  _drawMethod = Wire; // domy¶lnie rysujemy druciak
  _fogEnabled = false; // mg³a wy³±czona
  
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
  popupMenu->insertSeparator();
  popupMenu->insertItem( QIconSet(QPixmap(Icons::moveIcon())),   tr("Translate"), TransID );
  popupMenu->insertItem( QIconSet(QPixmap(Icons::rotateIcon())), tr("Rotate"),    RotID );
  popupMenu->insertItem( QIconSet(QPixmap(Icons::scaleIcon())),  tr("Scale"),     ScaleID );
  popupMenu->insertSeparator();
  popupMenu->insertItem( QIconSet(QPixmap(*Icons::bulbIcon())), tr("Translate light"),  TransLightID );
  popupMenu->insertItem(QIconSet(QPixmap(*Icons::spotIcon())), tr("Change light direction"),DirLightID);
  popupMenu->insertSeparator();
  popupMenu->insertItem( QIconSet(QPixmap(Icons::axisIcon())), tr("Kinematics"), KinematicsID );
  popupMenu->insertItem( QIconSet(QPixmap(Icons::ballIcon())), tr("Simulation"), SimulationID ); 
  popupMenu->insertSeparator();
  popupMenu->insertItem( QIconSet( QPixmap(*Icons::deleteIcon())), tr("Delete"), DeleteID );
      
  connect( popupMenu, SIGNAL( aboutToShow() ), this,  SLOT ( popupAboutToShow() ) );
  connect( popupMenu, SIGNAL( activated(int) ), this, SLOT ( choosedFromPopup(int) ) );
  /////////////////////////////////////////////////////////////////////////////////////////// PopupMenu
  
  
  // startWidget wlacza i wylacza cellWidget
  connect(startWidget, SIGNAL(clicked()), cellWidget, SLOT(toggleVisibility()));

// polaczenia dla CELLWIDGETa
  connect( cellWidget, SIGNAL(moveCamera(bool)), this, SLOT(setCameraMoving(bool)));
  connect( cellWidget, SIGNAL(showEntireScene()), this, SLOT(showAllScene()));
  connect( cellWidget, SIGNAL(showGrid(bool)), this, SLOT(setDrawGridXZ(bool)));
  connect( cellWidget, SIGNAL(showBoxes(bool )), this, SLOT( setDrawBoxes(bool) ) );
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



// metoda statyczna odswiezajaca wszystkie widoki GL, najpierw oblicza wsp globalne bryl
void CellFrame::refresh()
{
  if ( _scene != 0L ) _scene->ComputeGlbVtx(); // przeliczenie wierzcholkow
  updateGLForAllViewers();             // odrysowanie wszystkich widokow
}



QPtrList<ViMultiPolyh>* CellFrame::selected()
{
  return _selectedList;
}

ViScene* CellFrame::scene()
{
  return _scene;
}

// zwraca TRUE, je¿eli scena nie zawiera ¿adnych obiektów lub
// wskazuje na NULL
bool CellFrame::sceneIsEmpty()
{
  if ( _scene == 0L ) return true;
  
  ViScene::ConMultiPolyhIter iter = _scene->ConBegin_NormMultiPolyh(); // pierwszy element
  if ( iter ) return false;
  
  return true;
}


// ustawia rysowanie siatki
void CellFrame::setDrawGridXZ(bool on)
{
  _gridIsDrawn = on;
  cellWidget->showGridButton->setOn(on);
  updateGL();
}

// ustawia rysowanie siatki 3D
void CellFrame::setDrawGrid3D(bool on)
{
  _grid3DIsDrawn = on;
  updateGL();
}

void CellFrame::setDrawAxisXYZ( bool on )
{
  _axisIsDrawn = on;
  cellWidget->showAxisButton->setOn(on);
  updateGL();
}


void CellFrame::setDrawBoxes( bool on )
{
  _boxesAreDrawn = on;
  cellWidget->showBoxesButton->setOn(on);
  updateGL();
}


void CellFrame::setDrawLights( bool on )
{
  _lightsAreDrawn = on;
  cellWidget->showLightsButton->setOn(on);
  updateGL();
}


void CellFrame::setShowFPS( bool on )
{
  _fpsDisplayed = on;
  setDisplayFPS( on );
  updateGL();
}

// ustawia aktualnie wyswietlane info;
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

///////////////////////////////////////////////////////////////////////////   CIENIE

// metoda rysuje cieñ dla pojedynczego elementu i pojedynczego ¼ród³a ¶wiat³a
void CellFrame::castShadow( ViElemePolyhExt* elem, const GLfloat* lp )
{
  /*
  // które ¶ciany odbijaj± ¶wiat³o
  for ( ViElemePolyhExt::ConFaceIter iter = elem->ConBegin_GlbFace(); iter; ++iter )
  {
    ViElemePolyhFace *face = (ViElemePolyhFace*) & (*iter);
    if ( face->ComputePlain3f() ) // wyznacz p³aszczyznê, na której le¿y ¶cianka
    {
      const Plain3f pl = face->GetPlain();
      
      // teraz sprawdzamy po której stronie jest ¶wiat³o
      const Vector3f nv = pl.GetNVct(); //(wsp. A,B,C)
      GLfloat d = pl.GetD();
      GLfloat side = nv.x * lp[0] +
                     nv.y * lp[1] +
                     nv.z * lp[2] +
                        d * lp[3];
      if ( side > 0 ) face->setIsVisible(true); else face->setIsVisible(false);
    }
  }
  // teraz przygotowujemy OpenGL
  glPushAttrib( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ENABLE_BIT | GL_POLYGON_BIT | GL_STENCIL_BUFFER_BIT );
  glDisable( GL_LIGHTING ); // wy³±czamy ¶wiat³o - renderujemy do stencil buffer-a
  glDepthMask( GL_FALSE );  // nie zapisujemy do depth buffer-a
  glDepthFunc( GL_LEQUAL );
  glEnable( GL_STENCIL_TEST ); // w³±czamy stencil buffer
  glColorMask( GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE ); // nie pisz do bufora koloru
  glStencilFunc( GL_ALWAYS, 1, 0xFFFFFFFFL );
  
  // pierwszy etap - zwiêkszaj warto¶æ stencil buffora dla cienia
  glFrontFace( GL_CCW ); // ¶ciany przeciwnie do wskazówek zegara - front
  glStencilOp( GL_KEEP, GL_KEEP, GL_INCR );
  doShadowPass( elem, lp );
  // drugi etap - zmniejsz warto¶æ stencil buffera dla ty³u ¶cian
  glFrontFace( GL_CW ); // zgodnie z zegarem - ty³
  glStencilOp( GL_KEEP, GL_KEEP, GL_DECR );
  doShadowPass( elem, lp );
  
  glFrontFace( GL_CCW );
  glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE ); // teraz dopiero zezwalamy na rysowanie
  
  // rysuj prostok±t cieniuj±cy ca³± scenê
  glColor4f( 0.0f, 0.0f, 0.0f, 0.4f ); // kolor i przezroczysto¶æ cienia mo¿na tutaj ustawiæ
  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
  glStencilFunc( GL_NOTEQUAL, 0, 0xFFFFFFFFL );
  glStencilOp( GL_KEEP, GL_KEEP, GL_KEEP );
  glPushMatrix();
    glLoadIdentity();
    GLfloat r = 2*sceneRadius();
    glBegin( GL_TRIANGLE_STRIP );
      glVertex3f( -0.1*r,  0.1*r, -0.1*r );
      glVertex3f( -0.1*r, -0.1*r, -0.1*r );
      glVertex3f(  0.1*r,  0.1*r, -0.1*r );
      glVertex3f(  0.1*r, -0.1*r, -0.1*r );
    glEnd();
  glPopMatrix();
  glPopAttrib();  // przywracamy ustawienia
  */
}



void CellFrame::doShadowPass( ViElemePolyhExt* elem, const GLfloat* lp )
{
  // iterujemy ¶cianki:
  // - je¿eli ¶cianka jest widoczna to przegl±damy wszystkie jej krawêdzie,
  // - je¿eli krawêd¼ s±siaduje z niewidoczn± ¶ciank± - krawêd¼ rzuca cieñ
  /*
  // ¶ciany
  for ( ViElemePolyhExt::ConFaceIter face = elem->ConBegin_GlbFace(); face; ++face )
  {
    //ViElemePolyhFace *face = (ViElemePolyhFace*) & (*iter);
    if ( face->isVisible() )
    {
      // krawêdzie
      for ( ViElemePolyhFace::ConEdgeIter edge = face->ConBegin_GlbEdge(); edge; ++edge )
      {
        ViElemePolyhFace *f = (ViElemePolyhFace*) & *(edge->GetNeighborFace()); // ¶ciana s±siaduj±ca
                
        const Vector3f a = edge->GetFstVtx();
        const Vector3f b = edge->GetSndVtx();
        float r = sceneRadius()*2;
        
        bool v = f->isVisible();
        v = false;
        if ( v == false ) // krawêd¼ jest niewidoczna - rzuca cieñ
        {
          // wektory bêd±ce efektem rzutowania zgodnie z kierunkiem ¶wiat³a
          Vector3f c( (a.x - lp[0])*r, (a.y - lp[1])*r, (a.z - lp[2])*r );
          Vector3f d( (b.x - lp[0])*r, (b.y - lp[1])*r, (b.z - lp[2])*r );
          
          // rysuj cieñ
          glBegin( GL_TRIANGLE_STRIP );
            glVertex3f( a.x, a.y, a.z );
            glVertex3f( a.x + c.x, a.y + c.y, a.z + c.z );
            glVertex3f( b.x, b.y, b.z );
            glVertex3f( b.x + d.x, b.y + d.y, b.z + d.z );
          glEnd();
        }
        
      }
    } // if face visible
  } // for
  */
}


// metoda rysuje cienie w oparciu o liste _lightsList (wywo³uje castShadow())
void CellFrame::castShadows()
{
  for ( ViScene::ConMultiPolyhIter mph = _scene->ConBegin_NormMultiPolyh(); mph; ++mph )
  {
    ViMultiPolyh *mp = (ViMultiPolyh*) & (*mph);
    for ( ViMultiPolyh::ConElemePolyhIter elem = mp->ConBegin_ElemePolyh(); elem; ++elem )
    {
      ViElemePolyhExt *extEl = (ViElemePolyhExt*) & (*elem);
      for ( Light* light = _lightsList->first(); light; light = _lightsList->next() )
      castShadow( extEl, light->position4fv() );
    }
  }
}
///////////////////////////////////////////////////////////////////////////   CIENIE


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////  R Y S O W A N I E ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

void CellFrame::init()
{
  createDL(); // utwórz displayList dla box-a
  glEnable( GL_DEPTH_TEST );
  glDisable( GL_BLEND );
  glDisable( GL_FOG );
  
  // czy potrzebne?
  //glColor4f( 1.0f, 1.0f, 1.0f, 0.5f );
  //glBlendFunc( GL_SRC_ALPHA, GL_ONE );
}



void CellFrame::draw()
{
  qglClearColor( Options::backgroundColor() ); // wywo³uje glClearColor()
  glShadeModel( Options::shadeModel() );
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, Options::correctionHint() );
  
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT ); // czyszczenie bufora OpenGL
  drawScene();
  drawInfo();
}


// wyswietla informacje tekstowa zawarta w polu _info
// u¿ywa czcionki zdefiniowanej dla ca³ej aplikacji
void CellFrame::drawInfo()
{
   glDisable( GL_LIGHTING );
   glDisable( GL_TEXTURE_2D );
   qglColor( Options::infoTextColor() );
    drawText(_infoPosX, _infoPosY, _info);
}


// metoda rysuj±ca, ewentualnie zrzuca nazwy obiektów na stos GL               
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
    qglColor( Options::grid3DColor() ); // domyslny kolor rysowania siatki 3D
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
  
  if ( _scene ) // je¿eli jest co rysowaæ
  {
    
    ViElemePolyhExt *extEl = 0L;
    ViMultiPolyh *mph = 0L;
    bool mphIsSelected;
    
    if ( pushID ) nameList.clear();  // wyczy¶æ liste asocjacyjn± nazw obiektów

    blendedList.clear(); // wyczy¶æ listê obiektów przezroczystych

    int i=-1;
    //iterujemy wszystkie obiekty z³o¿one sceny
    for ( ViScene::ConMultiPolyhIter mphIter = _scene->ConBegin_NormMultiPolyh(); mphIter; ++mphIter )
    {
      i++;
      
      mph = (ViMultiPolyh*) & (*mphIter);
      if ( mph == 0L ) continue;
      
      // selekcja tylko ca³ych mph
      if ( pushID )
      {
        nameList.append( mph );              // dodaj obiekt do listy
        glPushName( (GLuint) nameList.at() );  // po³ó¿ na stos GL
      }
      
      // sprawdzamy, czy ten mph jest w¶ród zaznaczonych
      mphIsSelected = false;
      if ( _selectedList->findRef( mph ) != -1 ) mphIsSelected = true;
      
      // po czym iterujemy elementy ka¿dego obiektu z³o¿onego
      
      for (ViMultiPolyh::ConElemePolyhIter iter = mph->ConBegin_ElemePolyh(); iter; ++iter)
      { // iteracja elemePolyh

        extEl = (ViElemePolyhExt*) & (*iter);
        if ( !extEl ) continue;  // nie powinno siê wyda¿yæ, ale wrw
        
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
        }  // ¶wiat³a ON/OFF  
    
        if ( _lightsAreDrawn && !pushID ) // rysuj kszta³ty ¶wiate³
        {
          if ( _lightsList )
          {   
            for ( Light* light = _lightsList->first(); light; light = _lightsList->next() ) 
            drawLightShape( light );
          }
        } // kszta³ty ¶wiate³

        // **************** WIRE *********************************
        if ( _drawMethod == Wire )
        {
          // mph jest zaznaczony, rysuj go innym kolorem
          drawWired( extEl, mphIsSelected );
        }

        // **************** SOLID *********************************
        if ( _drawMethod == Solid )
        {
          // mph jest zaznaczony, rysuj go innym kolorem
          drawSolid( extEl, mphIsSelected );
        }

        // **************** TEXTURED *********************************
        if ( _drawMethod == Textured )
        {
          // je¿eli element ma w³±czony blending
          if ( extEl->textureParams()->blendingEnabled() ) blendedList.append( extEl ); // dodaj do listy obiektów przezroczystych i przeskocz (narysujemy je pó¼niej)
          else drawTextured( extEl, mphIsSelected );
        }
        
        if ( _axisIsDrawn && (!pushID) ) // wyswietlanie indywidualnych ukl wsp
    
        {
          drawElemAxis( extEl );
        }
        

      } // bryly (for iterator) obiektu z³o¿onego
      
      if ( pushID ) glPopName(); // zdejmij aktualn± nazwê ze stosu GL
    
    } // obiekty z³o¿one sceny

    
    // teraz dopiero rysujemy bry³y z bledningiem (o ile w³±czony jest tryb textured)
    if ( _drawMethod == Textured )
    {
      // najpierw sortujemy listê obiektów wzglêdem wspó³rzêdnej Z rosn±co
      if ( sortBlendedList() )
      // teraz je rysujemy od najdalszego do najbli¿szego
      {
        for ( ViElemePolyhExt* extElem = blendedList.first(); extElem; extElem = blendedList.next() )
        {
          if ( pushID )
          {
//            nameList.append( extEl );              // dodaj obiekt do listy
            glPushName( (GLuint) nameList.at() );  // po³ó¿ na stos GL
          }
          
          drawTextured( extElem, mphIsSelected );
          
          if ( pushID ) glPopName();
        }
      }
    }
    
  
    if ( _boxesAreDrawn && !pushID ) // rysowanie obrysów bry³
    {
      glDisable( GL_LIGHTING );
      glDisable( GL_TEXTURE_2D );
      glDisable( GL_BLEND );
      qglColor( Options::grid3DColor() ); // domyslny kolor rysowania siatki
      drawBoxes();
    }
    
    //castShadows();
    
  } // if (scene != 0L)

}



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


void CellFrame::drawElemAxis( ViElemePolyhExt* extEl )
{
  if (!extEl) return;
  
  glPushMatrix();
    //Vector3f vo = extEl->IndivCoord_O();
    
    MatrixH3f mp = extEl->Mtx2ParentCoord();
    MatrixH3f mi = extEl->Mtx2IndivCoord();
    MatrixH3f m = extEl->Mtx2SolidFigCoord();
    
    mi *= mp;
    m *= mi;
    
    Vector3f vo = m.GetTrans_TAfterR(); // translacja
    Vector3f vr = m.GetAng_XYZ_Deg();
    
    glTranslatef( vo.x, vo.y, vo.z);
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


// metoda (SLOT) wy³±cza wszystkie ¶wiat³a,
// UWAGA! w³±czane s± tylko te ¶wiat³a, które maj± w³±czone isEnabled()
// nie rusza o¶wietlenia globalnego GL_LIGHTING - tym nie manipulujemy ze wzglêdu na rysowanie WIRE
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


// STATIC ustawia statyczny wska¼nik do listy wszystkich ¶wiate³
// wywo³ywane raczej jeden raz na pocz±tku
void CellFrame::setLightsList( QPtrList<Light> *lightsList )
{
  _lightsList = lightsList;
}


// metoda ustawia wszystkie ¶wiat³a z listy
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



// ustawia parametry aktualnie edytowanego ¶wiat³a
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


// uaktualnia kolor dla danego ¶wiat³a
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



// metoda rysuje kszta³ty ¼róde³ ¶wiat³a w zale¿no¶ci od ich parametrów
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




// ustawia czy poruszamy wlasnie kamera
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
     if (_modifier == 0L) setCursor(QCursor(Qt::ForbiddenCursor)); // to nie powinno nigdy zaj¶æ
      else setCursor(_modifier->cursor()); // kursor aktualnego modyfikatora
  }

  _cameraIsMoving = on;
  cellWidget->cameraButton->setOn(on);
}


// ustawienie typu rzutowania
void CellFrame::setCameraType(Camera::Type type)
{
  camera()->setType(type);

  int i=-1;                                      // ustawienie Combo gdyby zmiane wywolano nie z CellWidget
  if (type==Camera::ORTHO) i=0; else i=1;
  cellWidget->viewProjCombo->setCurrentItem(i);
  updateGL();
}



// ustawienie sposobu rysowania
void CellFrame::setDrawMethod(DrawMethod drawMethod)
{
  _drawMethod = drawMethod;

  makeCurrent();
  
  glDisable( GL_FOG );
  
  int i=-1;                                      // ustawienie Combo gdyby zmiane wywolano nie z CellWidget
  switch(drawMethod)
  {
    case Wire : i=0; break;
    case Solid: i=1; break;
    case Textured: { i=2; if ( _fogEnabled ) glEnable( GL_FOG ); } break;
  }
  cellWidget->viewTypeCombo->setCurrentItem(i);
  updateGL();
}



/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////  S T A T I C //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

// STATIC ustawienie sceny do wyswietlania
void CellFrame::setScene( ViScene *scene )
{
  _scene = scene;
  updateGLForAllViewers();
}


// STATIC ustawia bryle do zaznaczenia
void CellFrame::setSelected( QPtrList<ViMultiPolyh> *selectedList )
{
  _selectedList = selectedList;
  updateGLForAllViewers();
}


void CellFrame::setModifier(MModifier *modifier)
{
  _modifier = modifier;
}

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////  S T A T I C //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////



// METODA NADMIAROWA, poniewa¿ nie mo¿na ³±czyæ slotów statycznych - TYLKO PO TO JEST
// wywo³uje metodê statyczn± setSelected
void CellFrame::setSelectedSlot( QPtrList<ViMultiPolyh> *selectedList )
{
  CellFrame::setSelected( selectedList );
}


// dopasowuje widok do rozmiarów sceny, zeby wszystko by³o widoczne
void CellFrame::showAllScene()
{
  if ( CellFrame::sceneIsEmpty() ) // je¿eli scena jest pusta - przywróæ ustawienia domy¶lne
  { 
   glDisable( GL_BLEND );
   setSceneCenter( 0.0, 0.0, 0.0 );
   setSceneRadius( 2.0 );
   showEntireScene();
   return;
  }

  _scene->ComputeGlbVtx();
  // obrys prostopadloscienny ca³ej sceny
  Vector3f min( _scene->GetOutlineBox().Min() );
  Vector3f max( _scene->GetOutlineBox().Max() );

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



// ustawia kamere w okreslony (predefiniowany) sposob - spojrzenie na bok, przod lub gore sceny
// podwojne klikniecie na scenie powoduje powrot do tego ustawienia (obsluga mouseDoubleClickEvent())
// direction jest jednym z predefiniowanych kierunkow
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



// metoda rysuje obrysy prostopad³o¶cienne bry³
void CellFrame::drawBoxes()
{
  if ( sceneIsEmpty() ) return;
  Vector3f min, max, mid;
  float width, height, depth;
  ViMultiPolyh *mph;
  
  for ( ViScene::ConMultiPolyhIter iter = _scene->ConBegin_NormMultiPolyh(); iter; ++iter )
  {
    mph = (ViMultiPolyh*) & (*iter);
    
    min = mph->GlbOlnBox().Min();
    max = mph->GlbOlnBox().Max();
    mid.Set( (min.x+max.x)/2, (min.y+max.y)/2, (min.z+max.z)/2 ); // ¶rodek bry³y
    
    width  = max.x - min.x;
    height = max.y - min.y;
    depth  = max.z - min.z;
    
    glPushMatrix();
      glTranslatef( mid.x, mid.y, mid.z );
      glScalef( width, height, depth );
      drawCube();
    glPopMatrix();
    
  }
}



// rysuje siatke w plaszczyznie XZ
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


/*
// rysuje siatkê 3D
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



// metoda maksymalizuje okno widoku, minimalizuj±c pozosta³e
// WARUNEK - CellFrame jest dzieckiem obiektu klasy QSplitter, który ma równie¿ rodzica QSplitter
// sposób dzia³ania tej metody jest ¶ci¶le uzale¿niony od struktury splitterów, w których obiekt
// CellFrame egzystuje - struktura ta budowana jest w obiekcie klasy Workspace
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

// gdy mysz wjedzie na CellFrame, automatycznie ustawiany jest dla niej Focus klawiatury
void CellFrame::enterEvent(QEvent*)
{
  this->setFocus();
}


void CellFrame::mousePressEvent(QMouseEvent *e)
{
     // kamera ma najwy¿szy priorytet - lewy przycisk=rotate, prawy=translate
  if ( _cameraIsMoving ) { QGLViewer::mousePressEvent(e); return; }
  
 
////////////////////////////////////////////////////////////////////////////////// MODYFIKATOR
  if (e->button() == Qt::LeftButton)   // lewy klik - dziala modyfikator
  {
   if (_modifier->type() == MModifier::M_SELECT) {select(e); return;} // dla modyfikatora selekcji nie ma zadnych akcji - tylko selekcja

   //select(e);  // obojetnie jaki modyfikator - zaznacza sobie najpierw obiekt

//////////////////////////////////////////////////////////////////// przygotuj odpowiedni modyfikator   
   
   // je¿eli mamy do czynienia z modyfikatorami ¶wiate³ - w³±czamy rysowania kszta³tów ¶wiate³
   if ( (_modifier->type() == MModifier::M_TRANSLIGHTPOS) || (_modifier->type() == MModifier::M_TRANSLIGHTDIR) ) setDrawLights( true );
   

////////////////////////////////////////////////////////////// koniec przygotowañ - uruchom modyfikator  
   makeCurrent();

   _modifier->mousePressEvent(e, camera(), _selectedList); // metoda modyfikatora modyfikujaca wybrany obiekt
   
   // sceny nie ruszamy! nie wolno jej modyfikowaæ - to eter, woda w której p³ywaj± 
   // wszystkie rybki ( i jakkolwiek teoria istnienia eteru zosta³a z hukiem obalona to woda jest niezbicie // namacalnym ¶wiadectwem wszelkiej egzystencji )
   
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



void CellFrame::mouseMoveEvent(QMouseEvent *e)
{
  if (_cameraIsMoving) QGLViewer::mouseMoveEvent(e);
  else
  {
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



void CellFrame::mouseReleaseEvent(QMouseEvent *e)
{
  if (_cameraIsMoving) QGLViewer::mouseReleaseEvent(e);
  else
  {
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



// dla dwumlasku mysza przywracany jest widok z combo
void CellFrame::mouseDoubleClickEvent(QMouseEvent *)
{
 int viewDir = cellWidget->viewDirCombo->currentItem();
 setViewDirection(viewDir); // direction jest jednym z predefiniowanych kierunkow
}

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////  Z D A R Z E N I A   M Y S Z Y ////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////////////////////////////////////////////////// PopupMenu
// slot wywo³ywany w momencie wywo³ania popupMenu - wy³±cza opcje zale¿ne od selekcji
void CellFrame::popupAboutToShow()
{
  bool ok = true;
  if ( _selectedList->isEmpty() ) ok = false; // nie ma ¿adnego zaznaczonego obiektu
  
  popupMenu->setItemEnabled( TransID, ok );
  popupMenu->setItemEnabled( RotID, ok );
  popupMenu->setItemEnabled( ScaleID, ok );
  popupMenu->setItemEnabled( LinkID, ok );
  popupMenu->setItemEnabled( DeleteID, ok );
  popupMenu->setItemEnabled( KinematicsID, ok );
}


void CellFrame::choosedFromPopup( int n )
{
  switch ( n )
  {
    case SelectID      : emit setModifierFromCellFrame( MModifier::M_SELECT ); break;
    case CameraID      : setCameraMoving( true ); break;
    case TransID       : emit setModifierFromCellFrame( MModifier::M_TRANSLATE ); break;
    case RotID         : emit setModifierFromCellFrame( MModifier::M_ROTATE ); break;
    case ScaleID       : emit setModifierFromCellFrame( MModifier::M_SCALE ); break;
    case TransLightID  : emit setModifierFromCellFrame( MModifier::M_TRANSLIGHTPOS ); break;
    case DirLightID    : emit setModifierFromCellFrame( MModifier::M_TRANSLIGHTDIR ); break;
    case DeleteID      : deleteSelectedObjects(); emit userSelected( _selectedList ); break;
    case SelectAllID   : selectAll(); break;
    case KinematicsID  : { 
                           KinematicsEditorRO *ke = new KinematicsEditorRO( _selectedList );
                         } break;
    default : break;
  }
}

/////////////////////////////////////////////////////////////////////////////////// PopupMenu



// metoda ustawia pojedynczy parametr mg³y dla danego widoku
// UWAGA: mg³a wy¶wietlana jest tylko w trybie rysowania Textured
void CellFrame::setFog( FogStruct* fog, FogParamsEnum whichParamChanged )
{
  makeCurrent();
  
  switch ( whichParamChanged )
  {
    case FogEnabled : {
                        _fogEnabled = fog->fogEnabled; 
                        if ( _drawMethod == Textured )
                        {
                          if ( _fogEnabled ) glEnable( GL_FOG ); else glDisable( GL_FOG );
                        }
                      } break;
    case FogMode    : glFogi( GL_FOG_MODE, fog->fogMode ); break;
    case FogDensity : glFogf( GL_FOG_DENSITY, fog->fogDensity ); break;
    case FogStart   : glFogf( GL_FOG_START, fog->fogStart ); break;
    case FogEnd     : glFogf( GL_FOG_END, fog->fogEnd ); break;
    case FogColor   : glFogfv( GL_FOG_COLOR, fog->fogColor ); break;
    case FogAll     : {
                        _fogEnabled = fog->fogEnabled; 
                        if ( _drawMethod == Textured )
                        {
                          _fogEnabled ? glEnable( GL_FOG ) : glDisable( GL_FOG );
                        }
                        glFogi( GL_FOG_MODE, fog->fogMode );
                        glFogf( GL_FOG_DENSITY, fog->fogDensity );
                        glFogf( GL_FOG_START, fog->fogStart );
                        glFogf( GL_FOG_END, fog->fogEnd );
                        glFogfv( GL_FOG_COLOR, fog->fogColor );
                      } break;
  }
  
  updateGL(); 
}






// metoda usuwa wszystkie obiekty znajduj±ce siê na li¶cie _selectedList,
// po czym od¶wie¿a wszystkie widoki i wysy³a sygna³ nowej listy _selectedList
// UWAGA: nie usuwa g³ównego MultiPolyh-a
void CellFrame::deleteSelectedObjects()
{
  if ( _selectedList->isEmpty() ) return;
  
  ViElemePolyhExt *extEl;
  
  for (ViMultiPolyh *_selected = _selectedList->first(); _selected; _selected = _selectedList->next())
  {
    // iteruj elementy ViElemePolyhExt obiektu i usuñ im tekstury
    for ( ViMultiPolyh::ConElemePolyhIter iter = _selected->ConBegin_ElemePolyh(); iter; ++iter )
    {
      extEl = (ViElemePolyhExt*) & (*iter);
      TextureManager::deleteTextureFromObject( extEl );
    }
    _selected->DetachNode();
    //delete _selected;
  }
  
  _selectedList->clear();  // wyczy¶æ listê zaznaczonych obiektów
  
  Kernel::computeScene();
  CellFrame::refresh();
}




// slot zaznacza wszystkie obiekty na scenie
void CellFrame::selectAll()
{
  _selectedList->clear();
  ViMultiPolyh *mph;
  for ( ViScene::ConMultiPolyhIter iter = _scene->ConBegin_NormMultiPolyh(); iter; ++iter)
  {
    mph = (ViMultiPolyh*) & (*iter);
    _selectedList->append( mph );
  }
  emit userSelected( _selectedList );
  updateGLForAllViewers();
}



// skroty klawiaturowe
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
    case Key_B : {
                    setDrawBoxes( !_boxesAreDrawn );              // 'B' - rysuj obrysy bry³
                 } break;
    case Key_C : {
                    setCameraMoving( !_cameraIsMoving );               // 'C' - kamera
                 } break;
    case Key_Delete : {                                   // 'Delete' - usuniecie zaznaczonych obiektow
                        CellFrame::deleteSelectedObjects();
                        emit userSelected(_selectedList); // wy¶lij listê (pust±)
                      } break;
    case Key_F : showAllScene(); break;                     // 'F' - dopasuj scene do okna widoku
    case Key_G : setDrawGridXZ( !_gridIsDrawn ); break;     // 'G' - pokaz siatke
    case Key_H : setDrawGrid3D( !_grid3DIsDrawn ); break;     // 'H' - pokaz siatke 3D
//    case Key_I : setShowFPS( !_fpsDisplayed ); break;       // 'I' - poka¿ ilo¶æ klatek na sekundê
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
    case Key_Down: {                                   // 'strza³ka w dó³' - ZOOM OUT
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


