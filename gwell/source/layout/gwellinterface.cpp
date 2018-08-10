///////////////////////////////////////////////////////////////////////
//
//    class: GwellInterface (.cpp)
//
//    Kompletny interfejs Gwell.
//
///////////////////////////////////////////////////////////////////////

#include "gwellinterface.h"


// konstruktor
GwellInterface::GwellInterface(QWidget *parent, char *name, WFlags fl) : QWidget(parent,name,fl)
{
  /// zaczynamy od za³adowania ustawieñ
  if ( Options::loadSettings() )
  {
  
  grid = new QGridLayout(this, 1,1, 5,5);   // layout dla calej aplikacji

  this->setCaption( APPNAME );         // nazwa glownego okna aplikacji
  this->setIcon(QPixmap(*(Icons::appleRedIcon())));        // ikona aplikacji

  splitter8 = new QSplitter( QSplitter::Vertical, this );

  splitter7 = new QSplitter( QSplitter::Horizontal, splitter8 );

   // toolbar po lewej stronie ekranu
  toolbar = new ToolBar(tr("Tools"), splitter7);

  splitter6 = new QSplitter( QSplitter::Vertical, splitter7 );

  
  // górny HBox zawieraj±cy tabBar i mainCellWidget
  QHBox *hBox = new QHBox( splitter6 );
  hBox->setSpacing( 5 );
  hBox->setFixedHeight( 40 );
  
  tabBar = new Tabs( hBox );
  QToolTip::add( tabBar, tr("Keys (1-7) change tabs"));
  
  CellWidget *cell = new CellWidget( hBox );
  cell->hidePrivateButtons();
  cell->setFrameStyle( QFrame::NoFrame );
  
  
  // obszar roboczy (4 okna)
  workSpace = new Workspace(splitter6);
  
  // pasek statusu
  statusBar = new StatusBar(splitter8);

  grid->addWidget(splitter8, 0,0);
  
  _toolWidth = (int) (0.15 * (float) (this->width()));
  // ustawienie pocz±tkowych rozmiarów toolBara i statusBara - dobrane eksperymentalnie
  
  QValueList<int> list;
  list.append( _toolWidth );
  list.append( 900 - _toolWidth );
  splitter7->setSizes(list);
  
  list.clear();
  list.append(900-40);
  list.append(40);
  splitter8->setSizes(list);
  
  // pod³±czenie globalnych ustawieñ dla CellFrames
  connect( cell, SIGNAL( moveCamera(bool) ), workSpace, SLOT( setCameraIsMovingForAll(bool) ) );
  connect( cell, SIGNAL( showEntireScene() ), workSpace, SLOT( showEntireSceneForAll() ) );
  connect( cell, SIGNAL( showGrid(bool) ), workSpace, SLOT( showGridForAll(bool) ) );
  connect( cell, SIGNAL( showBoxes(bool) ), workSpace, SLOT( showBoxesForAll(bool) ) );
  connect( cell, SIGNAL( showAxis(bool) ), workSpace, SLOT( showAxisForAll(bool) ) );
  connect( cell, SIGNAL( showLights(bool) ), workSpace, SLOT( showLightsForAll(bool) ) );
  connect( cell, SIGNAL( viewDirectionChanged(int) ), workSpace, SLOT( viewDirectionChangedForAll(int) ) );
  connect( cell, SIGNAL( setViewType(DrawMethod) ), workSpace, SLOT( setViewTypeForAll(DrawMethod) ) );
  connect( cell, SIGNAL( setProjType(qglviewer::Camera::Type) ), workSpace, SLOT( setProjTypeForAll(qglviewer::Camera::Type) ) );
  
  
  // polaczenie sygnaly zmiany zakladki ze zmiana widgetu narzedzi
  connect(tabBar, SIGNAL(selected(int)), toolbar->widgetStack(), SLOT(raiseWidget(int)));

  
  ////////////////////////////////////////////////////////////////////////////////////////// Kernel
  kernel = new Kernel; // UTWORZENIE GLOWNEGO OBIEKTU ZARZADZAJACEGO
  // laczymy kernel z klientami zanim go zainicjujemy
   connect(  // kernel wysyla zaladowane obiekty (scene) do drawWidget
            kernel, 
            SIGNAL(sendScene(ViScene*)), 
            toolbar->drawWidget(), 
            SLOT(setScene(ViScene*))
          );
   connect( // kernel wysy³a do workSpace utworzony g³ówny obiekt z³o¿ony
            kernel, 
            SIGNAL(sendScene(ViScene*)), 
            workSpace, 
            SLOT(setScene(ViScene*))
          );
   connect( // kernel wysy³a g³ówny obiekt z³o¿ony do ObjectsWidget, ¿eby ten móg³ go ³adnie odrysowaæ
            kernel, 
            SIGNAL(sendScene(ViScene*)), 
            toolbar->objectsWidget(), 
            SLOT(setRoot(ViScene*))
          );
  //kernel->init("libs");  // kernel inicjowany bibliotekami z katalogu lokalnego "libs/"
   kernel->init( Options::libPaths()->first() );
  ////////////////////////////////////////////////////////////////////////////////////////// Kernel
  
  
  ///////////////////////////////////////////////////////////////////////////////////////// FileWidget
  connect( // fileWidget wysy³a do kernela ¿±danie za³adowania obiektu z³o¿onego
            toolbar->fileWidget(),
            SIGNAL( addMultiPolyh( const char*, const char*, const Vector3f&, const Vector3f&, const Vector3f& ) ),
            kernel,
            SLOT( addMultiPolyh( const char*, const char*, const Vector3f&, const Vector3f&, const Vector3f& ) )
         );
  
  connect( // fileWidget wysy³a do ObjectsWidget ¿±danie odrysowania hierarchii nowej sceny
            toolbar->fileWidget(),
            SIGNAL( setScene( ViScene* ) ),
            toolbar->objectsWidget(),
            SLOT( setRoot( ViScene* ) )
         );
  
  connect( // fileWidget wysy³a do Workspace scenê
            toolbar->fileWidget(),
            SIGNAL( setScene( ViScene* ) ),
            workSpace,
            SLOT( setScene( ViScene* ) )
         );
  
  connect(
            toolbar->fileWidget(),
            SIGNAL( setFileCaption( const QString& ) ),
            this,
            SLOT( setCaption( const QString& ) )
         );
  
  connect( // fileWidget wysy³a do LightsWidget ¿±danie w³/wy³ ca³ego o¶wietlenia
            toolbar->fileWidget(),
            SIGNAL( setLightingEnabled( bool ) ),
            toolbar->lightsWidget(),
            SLOT( enableLighting( bool ) )
         );
  
  connect( // fileWidget wysy³a do LightsWidget ¿±danie usuniêcia wszystkich ¶wiate³
            toolbar->fileWidget(),
            SIGNAL( clearAllLights() ),
            toolbar->lightsWidget(),
            SLOT( clearAllLights() )
         );
  
  connect( // fileWidget wysy³a do LightsWidget ¿±danie dodania nowego ¶wiat³a
            toolbar->fileWidget(),
            SIGNAL( addLight(Light*) ),
            toolbar->lightsWidget(),
            SLOT( addLight(Light*) )
         );
  
  connect( // fileWidget wysy³a do FogWidget informacje o zmianie parametrów mg³y
            toolbar->fileWidget(),
            SIGNAL( updateFog() ),
            toolbar->fogWidget(),
            SLOT( updateWidgets() )
         );
  ///////////////////////////////////////////////////////////////////////////////////////// FileWidget 
     
  
  ///////////////////////////////////////////////////////////////////////////////////////// DrawWidget
  connect( // drawWidget wysy³a do kernela nazwê wybranego obiektu
            toolbar->drawWidget(), 
            SIGNAL( addMultiPolyh(const char*) ), 
            kernel, 
            SLOT( addMultiPolyh(const char*) )
          );
  ///////////////////////////////////////////////////////////////////////////////////////// DrawWidget
  
  
  ///////////////////////////////////////////////////////////////////////////////////////// ModifyWidget
  connect( // modifyWidget wysyla modyfikator do workspace
           toolbar->modifyWidget(), 
           SIGNAL(sendModifier(MModifier*)), 
           workSpace, 
           SLOT(setModifier(MModifier*))
         );
  connect( // modifyWidget powiadamia lightsWidget, ¿e wybrano u niego modyfikator
           toolbar->modifyWidget(), 
           SIGNAL( modifierChoosed() ), 
           toolbar->lightsWidget(), 
           SLOT( turnModifiersButtonsOff() ) 
         );
  connect( // modifyWidget powiadamia ObjectsWidget o zmianie nazwy przez u¿ytkownika
           toolbar->modifyWidget(), 
           SIGNAL( nameChanged() ), 
           toolbar->objectsWidget(), 
           SLOT( update() ) 
         );
  ///////////////////////////////////////////////////////////////////////////////////////// ModifyWidget
  
  
  ///////////////////////////////////////////////////////////////////////////////////////// ObjectsWidget
  connect(
           toolbar->objectsWidget(), 
           SIGNAL(selectionChanged( QPtrList<ViMultiPolyh>*)), 
           workSpace, 
           SLOT(setSelected( QPtrList<ViMultiPolyh>*)) 
         );
  connect(
           toolbar->objectsWidget(), 
           SIGNAL(selectionChanged( QPtrList<ViMultiPolyh>*)), 
           toolbar->modifyWidget(), 
           SLOT(setSelected( QPtrList<ViMultiPolyh>*)) 
         );
  ///////////////////////////////////////////////////////////////////////////////////////// ObjectsWidget
  
  
  ///////////////////////////////////////////////////////////////////////////////////////// LightsWidget
  connect( 
           toolbar->lightsWidget(), 
           SIGNAL( setLightsList(QPtrList<Light>*) ), 
           workSpace, 
           SLOT( setLightsList(QPtrList<Light>*) ) 
         );
  connect( 
           toolbar->lightsWidget(), 
           SIGNAL( setLight(Light*) ), 
           workSpace, 
           SLOT( setLight(Light*) ) 
         );
  connect( 
           toolbar->lightsWidget(), 
           SIGNAL( setLightingEnabled(bool) ), 
           workSpace, 
           SLOT( setLightingEnabled(bool) ) 
         );
  connect( 
           toolbar->lightsWidget(), 
           SIGNAL( updateLightColor( GLenum, Light* ) ), 
           workSpace, 
           SLOT( updateLightColor( GLenum, Light* ) ) 
         );
  
  //connect( toolbar->lightsWidget(), SIGNAL( showLightShapes(bool) ), workSpace, SLOT( showLightShapes(bool) ) );
  
  connect( 
           toolbar->lightsWidget(), 
           SIGNAL( sendModifier(MModifier*) ), 
           workSpace, 
           SLOT(setModifier(MModifier*))
         );
  connect( // lightsWidget informuje modifyWidget, ¿e nie posiada ¿adnego modyfikatora
           toolbar->lightsWidget(), 
           SIGNAL( setDefaultModifier() ), 
           toolbar->modifyWidget(), 
           SLOT( setDefaultModifier() ) 
         );
  ///////////////////////////////////////////////////////////////////////////////////////// LightsWidget
  
  
  ///////////////////////////////////////////////////////////////////////////////////////// FogWidget
  connect(
          toolbar->fogWidget(),
          SIGNAL( fogChanged( FogStruct*, FogParamsEnum ) ),
          workSpace,
          SLOT( setFog( FogStruct*, FogParamsEnum ) )
         );
  ///////////////////////////////////////////////////////////////////////////////////////// FogWidget
  
  
  ///////////////////////////////////////////////////////////////////////////////////////// Workspace
  connect( // teraz odwrotnie workSpace wysy³a modyfikator modifyWidget (wybrany z popupMenu)
           workSpace, 
           SIGNAL( setModifierFromCellFrame( MModifier::ModifierType ) ), 
           toolbar->modifyWidget(), 
           SLOT( setModifier( MModifier::ModifierType ) ) 
         );
  connect( // lightswidget te¿ wysy³a modyfikator
           workSpace, 
           SIGNAL( setModifierFromCellFrame( MModifier::ModifierType ) ), 
           toolbar->lightsWidget(), 
           SLOT( setModifier( MModifier::ModifierType ) ) 
         );
  connect(
           workSpace, 
           SIGNAL(userSelectedObject(QPtrList<ViMultiPolyh>*)), 
           toolbar->modifyWidget(), 
           SLOT(setSelected(QPtrList<ViMultiPolyh>*))
         );
  connect(
           workSpace, 
           SIGNAL(userSelectedObject(QPtrList<ViMultiPolyh>*)), 
           toolbar->objectsWidget(), 
           SLOT(setSelectedList(QPtrList<ViMultiPolyh>*))
         );
  ///////////////////////////////////////////////////////////////////////////////////////// Workspace
  
  // i na koñcu ustawiamy modyfikator selekcji jako domy¶lny, uff..
  toolbar->modifyWidget()->setDefaultModifier();
  }
}




// dla zachowania proporcji lewego toolbara
void GwellInterface::resizeEvent(QResizeEvent *e)
{
  /*
  if ( toolbar->width() < 5 ) return;
    
  _toolWidth = (int) (0.15 * (float) (e->size().width()) );
  QValueList<int> list;
  list.append( _toolWidth );
  list.append( e->size().width() - _toolWidth - 20 );
  splitter7->setSizes(list);
  */
  
  //toolbar->setMinimumSize(QSize(_toolWidth,0));
  //toolbar->setMaximumSize(QSize(_toolWidth,32767));  
}


// naci¶niêcie skrótu z narzêdziem (np. rotate) powinno powodowaæ automatyczne wy³±czenie kamery dla tego widoku
void GwellInterface::keyPressEvent(QKeyEvent *e)
{
  switch(e->key())
  {
   case Qt::Key_1 : {                           // sterowanie zakladkami
                      tabBar->setCurrentTab(0);
                    } break;
   case Qt::Key_2 : {                           // sterowanie zakladkami
                      tabBar->setCurrentTab(1);
                    } break;
   case Qt::Key_3 : {                           // sterowanie zakladkami
                      tabBar->setCurrentTab(2);
                    } break;
   case Qt::Key_4 : {                           // sterowanie zakladkami
                      tabBar->setCurrentTab(3);
                    } break;
   case Qt::Key_5 : {                           // sterowanie zakladkami
                      tabBar->setCurrentTab(4);
                    } break;
   case Qt::Key_6 : {                           // sterowanie zakladkami
                      tabBar->setCurrentTab(5);
                    } break;                
   case Qt::Key_7 : {                           // sterowanie zakladkami
                      tabBar->setCurrentTab(6);
                    } break;                
   case Qt::Key_8 : {                           // sterowanie zakladkami
                      tabBar->setCurrentTab(7);
                    } break;                

   case Qt::Key_A : {                                   // 'A' - modyfikator selekcji
                      if (e->state() != Qt::NoButton) e->ignore(); // z altem puszczamy dalej
                      else 
                      {
                        toolbar->modifyWidget()->setModifier(MModifier::M_SELECT);
                        workSpace->disableCameraInCurrentFrame(); // wy³±cz kamerê dla tego widoku
                      }
                      break;
                    }
   case Qt::Key_T : {                                       // T - modyfikator translacji
                      if (e->state() != Qt::NoButton) e->ignore();
                      else 
                      {
                        toolbar->modifyWidget()->setModifier(MModifier::M_TRANSLATE);
                        workSpace->disableCameraInCurrentFrame(); // wy³±cz kamerê dla tego widoku
                      }
                      break;
                    }
   case Qt::Key_R : {                                           // R - modyfikator rotacji
                      // nie sprawdza dodatkowych klawiszy bo nie ma skrótu dla Alt+R, CTRL+R, ...
                      {
                        toolbar->modifyWidget()->setModifier(MModifier::M_ROTATE);
                        workSpace->disableCameraInCurrentFrame(); // wy³±cz kamerê dla tego widoku
                      }
                      break;
                    }
   case Qt::Key_S : {                                             // S - modyfikator skalowania
                      if (e->state() != Qt::NoButton) e->ignore();
                      else 
                      {
                        toolbar->modifyWidget()->setModifier(MModifier::M_SCALE);
                        workSpace->disableCameraInCurrentFrame(); // wy³±cz kamerê dla tego widoku
                      }
                      break;
                    }
   case Qt::Key_L : {
                      toolbar->modifyWidget()->setModifier(MModifier::M_LINK); // L - link
                      workSpace->disableCameraInCurrentFrame(); // wy³±cz kamerê dla tego widoku
                    } break;
   default : e->ignore();  // jezeli nacisnieto inny klawisz, przekaz go dalej
  }
}



// obs³uguje zamniêcie widgetu
void GwellInterface::closeEvent(QCloseEvent *e)
{
  int choice = QMessageBox::question(qApp->mainWidget(),
                                     tr("Quit"),
                                     tr("Are you sure you want to quit? (i will try harder ;)"),
                                     QMessageBox::Yes, QMessageBox::No);
  if (choice == QMessageBox::Yes) e->accept(); else e->ignore();
}

