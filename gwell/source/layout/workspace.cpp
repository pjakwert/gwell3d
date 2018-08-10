//////////////////////////////////////////////////////////////////
///
///  class: Workspace (.cpp)
///
///  Zawiera wszystkie (4) okna edycyjne aplikacji ze splitterami
///
//////////////////////////////////////////////////////////////////

#include "workspace.h"


#define HasDescendants IsDescendant



QPtrList<CellFrame> Workspace::framesList;


// konstruktor
Workspace::Workspace(QWidget *parent, const char *name, WFlags fl) : QWidget(parent,name,fl)
{
  framesList.clear();
  grid = new QGridLayout(this, 1,1, 5,5);

  // splittery
  splitV = new QSplitter(QSplitter::Vertical, this);
  splitH = new QSplitter(QSplitter::Horizontal, splitV);
  split3 = new QSplitter(QSplitter::Horizontal, splitV);

  // utworz okna
  
  
  CellFrame* frame = new CellFrame( splitH );        // pierwszy CellFrame
  framesList.append( frame );
  TextureManager::setHostFrame( frame );             // ustaw CellFrame, kt�ry b�dzie przechowywa�
                                                     // wszystkie tekstury
  
  framesList.append(new CellFrame( splitH, "CellFrame 1", frame )); // nast�pne dziel� z nim listy OpenGL
  framesList.append(new CellFrame( split3, "CellFrame 2", frame ));
  framesList.append(new CellFrame( split3, "CellFrame 3", frame ));


  frame = framesList.at(0);
  frame->setDrawMethod(Wire);
  frame->setCameraType(qglviewer::Camera::ORTHO);
  frame->setViewDirection(3); // front

  frame = framesList.at(1);
  frame->setDrawMethod(Wire);
  frame->setCameraType(qglviewer::Camera::ORTHO);
  frame->setViewDirection(2); // side

  frame = framesList.at(2);
  frame->setDrawMethod(Wire);
  frame->setCameraType(qglviewer::Camera::ORTHO);
  frame->setViewDirection(1); // top

  frame = framesList.at(3);    
  frame->setDrawMethod(Solid);
  frame->setCameraType(qglviewer::Camera::PERSPECTIVE);
  frame->setViewDirection(0); // niezdefiniowany

  grid->addWidget(splitV, 0,0);

  // podlaczenie userSelectedObject
  for (CellFrame *frame = framesList.first(); frame; frame = framesList.next())
  {
    connect(frame, SIGNAL(userSelected(QPtrList<ViMultiPolyh>*)), this, SLOT(userSelected(QPtrList<ViMultiPolyh>*)));
    
    connect( frame, SIGNAL( setModifierFromCellFrame(MModifier::ModifierType) ), this, SLOT( modifierChangedFromCellFrame(MModifier::ModifierType) ) );
  }
}  



Workspace::~Workspace()
{}





//  ustawia scen� do wyswietlania dla wszystkich widokow
//  je�eli nowo wstawiana scena nie mie�ci si� w kt�rym� widoku,
//  widokowi temu ustawia si� nowy promie� sceny
void Workspace::setScene( ViScene *scene )
{ 
  scene->ComputeGlbVtx();
  CellFrame::setScene( scene );
  if ( CellFrame::sceneIsEmpty() ) // dla pustego mph - ustawienia domy�lne
  {
    for ( CellFrame* frame = framesList.first(); frame; frame = framesList.next() )
    {
      frame->setSceneCenter( 0.0, 0.0, 0.0 );
      frame->camera()->setRevolveAroundPoint( 0.0, 0.0, 0.0 );
      frame->setSceneRadius( 2.0 );
      frame->showEntireScene();
    }
    
    return;
  }
  
  // obrys prostopad�o�cienny ca�ej sceny
  
  Vector3f min( scene->GetOutlineBox().Min() );
  Vector3f max( scene->GetOutlineBox().Max() );

  // wyliczenie srodka i promienia sceny
  Vec vMax(max.x,max.y,max.z);
  Vec mid((min.x+max.x)/2, (min.y+max.y)/2, (min.z+max.z)/2); // srodek przekatnej prostopadloscianu ograniczajacego
  float r = Vec::Vec(vMax-mid).norm(); // promie� od �rodka do rogu prostopad�o�cianu
  
  for ( CellFrame* frame = framesList.first(); frame; frame = framesList.next() )
  {
    if ( frame->sceneRadius() < (r*1.3) ) frame->showAllScene();
  }
}



// ustawia wybrane obiekty dla wszystkich CellFrame
void Workspace::setSelected(QPtrList<ViMultiPolyh> *selectedList)
{
  CellFrame::setSelected( selectedList );
}



// metoda ustawia wska�nik statyczny CellFrames do listy �wiate�
// i ustawia wszystkim CellFrames te �wiat�a
void Workspace::setLightsList( QPtrList<Light> *lightsList )
{
 CellFrame::setLightsList( lightsList );
 
 for ( CellFrame *frame = framesList.first(); frame; frame = framesList.next() )
 {
    frame->setAllLights();
 }  
}


// metoda ustawia CellFrames w�a�ciwo�ci pojedynczego, edytowanego w�a�nie, �wiat�a
void Workspace::setLight( Light* light )
{
 for ( CellFrame *frame = framesList.first(); frame; frame = framesList.next() )
 {
    frame->setLight( light );
 }
}


// metoda w��cza/wy��cza o�wietlenie dla wszystkich CellFrames
void Workspace::setLightingEnabled( bool yes )
{
  for ( CellFrame *frame = framesList.first(); frame; frame = framesList.next() )
  {
    frame->turnAllLights( yes );
  }
}


// od�wie�a dany kolor danego �wiat�a wszystkim CellFrames
void Workspace::updateLightColor( GLenum GLcolorChanged, Light* light )
{
  for ( CellFrame *frame = framesList.first(); frame; frame = framesList.next() )
  {
    frame->updateColorForLight( GLcolorChanged, light );
  }
}



// ustaw CellFrame-om modyfikator
void Workspace::setModifier(MModifier *modifier)
{
 CellFrame::setModifier(modifier);

 for (CellFrame *frame = framesList.first(); frame; frame = framesList.next())
 {
   if (!frame->cameraIsMoving()) frame->setCursor(modifier->cursor()); // ustawia kursory CF
 }
}


// slot - CellFrame zmieni� modyfikator
void Workspace::modifierChangedFromCellFrame( MModifier::ModifierType mType )
{
  emit setModifierFromCellFrame( mType );
}


// id�wie�a zawarto�� wszystkich CellFrames
void Workspace::refresh()
{                                                       
  CellFrame::refresh();
}


// ustawia poczatkowe wartosci wszystkim cellFrames
void Workspace::resetAllFrames()
{
  CellFrame *frame = framesList.at(0);
  frame->setDrawMethod(Wire);
  frame->setCameraType(qglviewer::Camera::ORTHO);
  frame->setViewDirection(3); // front

  frame = framesList.at(1);
  frame->setDrawMethod(Wire);
  frame->setCameraType(qglviewer::Camera::ORTHO);
  frame->setViewDirection(2); // side

  frame = framesList.at(2);
  frame->setDrawMethod(Wire);
  frame->setCameraType(qglviewer::Camera::ORTHO);
  frame->setViewDirection(1); // top

  frame = framesList.at(3);    
  frame->setDrawMethod(Solid);
  frame->setCameraType(qglviewer::Camera::PERSPECTIVE);
  frame->setViewDirection(0); // niezdefiniowany
}



// wysyla sygnal z zaznaczonym elementem (gdy user wybierze go w CellFrame)
void Workspace::userSelected(QPtrList<ViMultiPolyh> *selectedList)
{
  emit userSelectedObject(selectedList);
}



// zwraca wska�nik do frame-a aktualnie posiadaj�cegu Focus
// 0L, gdy �adna z CellFrames go nie posiada
CellFrame* Workspace::currentFrame()
{
 for (CellFrame *frame = framesList.first(); frame; frame = framesList.next())
 {
   if ( frame->hasFocus() ) return frame;
 }
 return 0L;
}



// wy��cza kamer� dla aktywnej CellFrame,
// sprawdza wcze�niej czy jaka� jest aktywna
void Workspace::disableCameraInCurrentFrame()
{
  CellFrame *frame = currentFrame();
  if ( frame != 0L ) frame->setCameraMoving( false );
}


/*
// SLOT dla sygna�u showLightShapes
// w��cza/wy��cza rysowanie kszta�t�w �wiate� dla wszystkich CellFrames
// z t� jednak�e istotn� r�nic�, �e zapami�tuje poprzednie stany w��czenia/wy��czenia
// i przywraca je
void Workspace::showLightShapes( bool yes )
{
  static QValueList<bool> shapesAreDrawn;
  
  if ( yes ) shapesAreDrawn.clear();
  
  int i=0;
  for ( CellFrame *frame = framesList.first(); frame; frame = framesList.next() )
  {
    if ( yes )
    {
     shapesAreDrawn.append( frame->lightsAreDrawn() ); // zapami�taj stan
     frame->setDrawLights( yes );
    }
    else // przywr�� poprzednie ustawienia
    {
      frame->setDrawLights( shapesAreDrawn[i] );
      i++;
    }
  }
}
*/



// ustawienia z globalnego CellWidget dla wszystkich CellFrames
void Workspace::setCameraIsMovingForAll( bool yes )
{
  for (CellFrame *frame = framesList.first(); frame; frame = framesList.next())
  {
    frame->setCameraMoving( yes );
  }
}

void Workspace::showEntireSceneForAll()
{
  for (CellFrame *frame = framesList.first(); frame; frame = framesList.next())
  {
    frame->showAllScene();
  }
}

void Workspace::showGridForAll( bool on )
{
  for (CellFrame *frame = framesList.first(); frame; frame = framesList.next())
  {
    frame->setDrawGridXZ( on );
  }
}

void Workspace::showBoxesForAll( bool on )
{  
  for (CellFrame *frame = framesList.first(); frame; frame = framesList.next())
  {
    frame->setDrawBoxes( on );
  }
}


void Workspace::showAxisForAll( bool on )
{
  for (CellFrame *frame = framesList.first(); frame; frame = framesList.next())
  {
    frame->setDrawAxisXYZ( on );
  }
}

void Workspace::showLightsForAll( bool on )
{
  for (CellFrame *frame = framesList.first(); frame; frame = framesList.next())
  {
    frame->setDrawLights( on );
  }
}

void Workspace::viewDirectionChangedForAll(int direction)
{
  for (CellFrame *frame = framesList.first(); frame; frame = framesList.next())
  {
    frame->setViewDirection( direction );
  }
}

void Workspace::setViewTypeForAll( DrawMethod type )
{
  for (CellFrame *frame = framesList.first(); frame; frame = framesList.next())
  {
    frame->setDrawMethod( type );
  }
}

void Workspace::setProjTypeForAll( qglviewer::Camera::Type type )
{
  for ( CellFrame *frame = framesList.first(); frame; frame = framesList.next() )
  {
    frame->setCameraType( type );
  }
}


// slot ustawia CellFrame-om parametry mg�y
void Workspace::setFog( FogStruct* fog, FogParamsEnum whichParamChanged )
{
  for ( CellFrame *frame = framesList.first(); frame; frame = framesList.next() )
  {
    frame->setFog( fog, whichParamChanged );
  }
}


