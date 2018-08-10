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
  TextureManager::setHostFrame( frame );             // ustaw CellFrame, który bêdzie przechowywa³
                                                     // wszystkie tekstury
  
  framesList.append(new CellFrame( splitH, "CellFrame 1", frame )); // nastêpne dziel± z nim listy OpenGL
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

  // podlaczenie ObjectExplorer-a
  /*
  for (frame = framesList.first(); frame; frame = framesList.next())
  {
    connect(frame, SIGNAL(showObjectExplorer()), this, SLOT(objExplorerClicked()));
  }
  */

  // podlaczenie userSelectedObject
  for (CellFrame *frame = framesList.first(); frame; frame = framesList.next())
  {
    connect(frame, SIGNAL(userSelected(QPtrList<ViNTreeNode>*)), this, SLOT(userSelected(QPtrList<ViNTreeNode>*)));
    
    connect( frame, SIGNAL( setModifierFromCellFrame(MModifier::ModifierType) ), this, SLOT( modifierChangedFromCellFrame(MModifier::ModifierType) ) );
    
    connect( frame, SIGNAL( mphStructureChanged() ), this, SLOT( structureChanged() ) );
  }
}  



Workspace::~Workspace()
{}



/*!
Metoda wywo³ywana przy zmianie struktury obiektu z³o¿onego w CellFrame przez np. usuniêcie elementu.
Emitowany jest sygna³ globalny mphStructureChanged(), obs³uguje go ObjectsWidget do odrysowania
drzewa obiektów.
*/
void Workspace::structureChanged()
{
  emit mphStructureChanged();
}




/*!
Metoda ustawia bry³ê z³o¿on± do wy¶wietlania dla wszystkich widoków edycyjnych.
Je¿eli nowo wstawiany obiekt nie mie¶ci siê w którym¶ widoku,
widokowi temu ustawia siê nowy promieñ sceny.
*/
void Workspace::setMultiPolyh( ViMultiPolyh *multiPolyh )
{ 
  if ( !multiPolyh->HasDescendants() ) // dla pustego mph - ustawienia domy¶lne
  {
    for ( CellFrame* frame = framesList.first(); frame; frame = framesList.next() )
    {
      frame->setSceneCenter( 0.0, 0.0, 0.0 );
      frame->camera()->setRevolveAroundPoint( 0.0, 0.0, 0.0 );
      frame->setSceneRadius( 2.0 );
      frame->showEntireScene();
    }
    CellFrame::refresh();
    return;
  }
  
  multiPolyh->ComputeHierAllGlbVtx();
  
  // obrys prostopadloscienny calej bryly zlozonej
  Vector3f min(multiPolyh->GlbOlnBox().Min());
  Vector3f max(multiPolyh->GlbOlnBox().Max());

  // wyliczenie srodka i promienia sceny
  Vec vMax(max.x,max.y,max.z);
  Vec mid((min.x+max.x)/2, (min.y+max.y)/2, (min.z+max.z)/2); // srodek przekatnej prostopadloscianu ograniczajacego
  float r = Vec::Vec(vMax-mid).norm(); // promieñ od ¶rodka do rogu prostopad³o¶cianu

  CellFrame::setMultiPolyh( multiPolyh );
  
  for ( CellFrame* frame = framesList.first(); frame; frame = framesList.next() )
  {
    if (( frame->sceneRadius() < (r*1.3) ) /*|| ( frame->sceneRadius() > (r*1.3*10) )*/ ) frame->showAllScene();
  }
}


/*!
Metoda ustawia listê wybranych obiektów.
*/
void Workspace::setSelected(QPtrList<ViNTreeNode> *selectedList)
{
  CellFrame::setSelected( selectedList );
}


/*!
Metoda ustawia wska¼nik statyczny do listy ¶wiate³, po czym
ustawia wszystkim oknom edycyjnym te ¶wiat³a.
*/
void Workspace::setLightsList( QPtrList<Light> *lightsList )
{
 CellFrame::setLightsList( lightsList );
 
 for ( CellFrame *frame = framesList.first(); frame; frame = framesList.next() )
 {
    frame->setAllLights();
 }  
}

/*!
Metoda ustawia oknom w³a¶ciwo¶ci pojedynczego, edytowanego w³a¶nie ¶wiat³a.
*/
void Workspace::setLight( Light* light )
{
 for ( CellFrame *frame = framesList.first(); frame; frame = framesList.next() )
 {
    frame->setLight( light );
 }
}

/*!
Metoda w³±cza/wy³±cza o¶wietlenie dla wszystkich widoków.
*/
void Workspace::setLightingEnabled( bool yes )
{
  for ( CellFrame *frame = framesList.first(); frame; frame = framesList.next() )
  {
    frame->turnAllLights( yes );
  }
}

/*!
Metoda od¶wie¿a dany kolor danego ¶wiat³a wszystkim widokom.
*/
void Workspace::updateLightColor( GLenum GLcolorChanged, Light* light )
{
  for ( CellFrame *frame = framesList.first(); frame; frame = framesList.next() )
  {
    frame->updateColorForLight( GLcolorChanged, light );
  }
}


/*!
Metoda ustawia widokom dany modyfikator.
*/
void Workspace::setModifier(MModifier *modifier)
{
 CellFrame::setModifier(modifier);

 for (CellFrame *frame = framesList.first(); frame; frame = framesList.next())
 {
   if (!frame->cameraIsMoving()) frame->setCursor(modifier->cursor()); // ustawia kursory CF
 }
}

/*!
Widok wysy³a sygna³ o zmianie modyfikatora.
*/
void Workspace::modifierChangedFromCellFrame( MModifier::ModifierType mType )
{
  emit setModifierFromCellFrame( mType );
}

/*!
Metoda od¶wie¿a zawarto¶æ wszystkich widoków.
*/
void Workspace::refresh()
{                                                       
  CellFrame::refresh();
}

/*!
Metoda ustawia pocz±tkowe warto¶ci wszystkim widokom.
*/
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


/*!
Metoda wysy³a sygna³ z elementem zaznaczonym w widoku.
*/
void Workspace::userSelected(QPtrList<ViNTreeNode> *selectedList)
{
  emit userSelectedObject(selectedList);
}


/*!
Metoda zwraca wska¼nik do widoku aktualnie posiadaj±cegu focus lub 0L, 
gdy ¿aden widok go nie posiada.
*/
CellFrame* Workspace::currentFrame()
{
 for (CellFrame *frame = framesList.first(); frame; frame = framesList.next())
 {
   if ( frame->hasFocus() ) return frame;
 }
 return 0L;
}


/*!
Metoda wy³±cza kamerê dla aktywnego widoku.
*/
void Workspace::disableCameraInCurrentFrame()
{
  CellFrame *frame = currentFrame();
  if ( frame != 0L ) frame->setCameraMoving( false );
}

/*
Metoda jest slotem dla sygna³u showLightShapes.
W³±cza/wy³±cza rysowanie kszta³tów ¶wiate³ dla wszystkich widoków.
Z t± jednak¿e istotn± ró¿nic±, ¿e zapamiêtuje poprzednie stany w³±czenia/wy³±czenia
i przywraca je.

void Workspace::showLightShapes( bool yes )
{
  static QValueList<bool> shapesAreDrawn;
  
  if ( yes ) shapesAreDrawn.clear();
  
  int i=0;
  for ( CellFrame *frame = framesList.first(); frame; frame = framesList.next() )
  {
    if ( yes )
    {
     shapesAreDrawn.append( frame->lightsAreDrawn() ); // zapamiêtaj stan
     frame->setDrawLights( yes );
    }
    else // przywróæ poprzednie ustawienia
    {
      frame->setDrawLights( shapesAreDrawn[i] );
      i++;
    }
  }
}
*/


/*!
Metoda kopiuje ustawienia z globalnego menu do wszystkich widoków.
*/
void Workspace::setCameraIsMovingForAll( bool yes )
{
  for (CellFrame *frame = framesList.first(); frame; frame = framesList.next())
  {
    frame->setCameraMoving( yes );
  }
}

/*!
Metoda zadaje pokazanie ca³ej sceny wszystkim widokom.
*/
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

