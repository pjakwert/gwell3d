#include "modifywidget.h"


// #define SetTrans_TAfterR SetTrans_TBeforeR
// #define SetAng_XYZ_TAfterR_Rad SetAng_XYZ_TBeforeR_Rad
// #define SetAng_XYZ_TAfterR_Deg SetAng_XYZ_TBeforeR_Deg
// #define SetScale_TAfterR SetScale_TBeforeR
// #define GetTrans_TAfterR GetTrans_TBeforeR



// konstruktor
ModifyWidget::ModifyWidget(QString title, QWidget *parent, const char *name) : QWidget(parent, name)
{
    _rad = false; // domyslnie wyswietlamy katy w stopniach
    _selectedList = 0L;

    // tworzone sa modyfikatory
    mSelect = new SelectModifier(QCursor(Qt::ArrowCursor));
    mTrans  = new TranslateModifier(QCursor(QPixmap(Icons::transTextIcon())));
    mRot    = new RotateModifier(QCursor(QPixmap(Icons::rotateTextIcon())));
    mScale  = new ScaleModifier(QCursor(QPixmap(Icons::scaleTextIcon())));
    mLink   = new LinkModifier(QCursor(QPixmap(Icons::linkIcon())));
    mTransCoords = new TranslateCoordsModifier( QCursor( QPixmap( *Icons::transCoordsIcon() ) ) );
    mRotCoords   = new RotateCoordsModifier( QCursor( QPixmap( *Icons::rotCoordsIcon() ) ) );
    

    // sygnaly zmiany wartosci przez modyfikatory laczone sa z metoda uaktualniajaca okienka z wsp transformacji
    connect(mSelect, SIGNAL(vectorChanged(MModifier::ModifierType, Vector3f)), this, SLOT(updateData(MModifier::ModifierType, Vector3f)));
    connect(mTrans, SIGNAL(vectorChanged(MModifier::ModifierType, Vector3f)), this, SLOT(updateData(MModifier::ModifierType, Vector3f)));
    connect(mRot, SIGNAL(vectorChanged(MModifier::ModifierType, Vector3f)), this, SLOT(updateData(MModifier::ModifierType, Vector3f)));
    connect(mScale, SIGNAL(vectorChanged(MModifier::ModifierType, Vector3f)), this, SLOT(updateData(MModifier::ModifierType, Vector3f)));
    // mLink nie jest podlaczony bo nie zwraca zadnych wartosci
    connect( mTransCoords, SIGNAL( vectorChanged( MModifier::ModifierType, Vector3f ) ), this, SLOT( updateData( MModifier::ModifierType, Vector3f ) ) );
    connect( mRotCoords, SIGNAL( vectorChanged( MModifier::ModifierType, Vector3f ) ), this, SLOT( updateData( MModifier::ModifierType, Vector3f ) ) );

    grid = new QGridLayout(this, 7,1, 0,20); // glowny grid - zawiera 6 okien + wype³niacz


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////   N A R Z E D Z I A
///////////////////////////////////////////////////////////////////////////////////////////////
    toolsBox = new QGroupBox(2, Qt::Horizontal, this);
    toolsBox->setTitle(title);
      selectButton = new QToolButton(toolsBox);                            // przycisk selekcji
      selectButton->setIconSet(QIconSet(QPixmap(Icons::selectIcon())));    // ikona
      selectButton->setTextLabel(tr("Select (A)"), true);                      // tekst
      selectButton->setToggleButton(true);                                 // on/off
      selectButton->setAutoRaise(true);                                    // plaski przycisk
      connect(selectButton, SIGNAL(clicked()), this, SLOT(buttonClicked()));  // sygnaly ze wszystkich guzikow ida do jednego worka
      transButton  = new QToolButton(toolsBox);                           // translacja
      transButton->setIconSet(QIconSet(QPixmap(Icons::moveIcon())));
      transButton->setTextLabel(tr("Translate (T)"), true);
      transButton->setToggleButton(true);
      transButton->setAutoRaise(true);
      connect(transButton, SIGNAL(clicked()), this, SLOT(buttonClicked()));

      rotateButton = new QToolButton(toolsBox);                          // rotacja
      rotateButton->setIconSet(QIconSet(QPixmap(Icons::rotateIcon())));
      rotateButton->setTextLabel(tr("Rotate (R)"), true);
      rotateButton->setToggleButton(true);
      rotateButton->setAutoRaise(true);
      connect(rotateButton, SIGNAL(clicked()), this, SLOT(buttonClicked()));

      scaleButton = new QToolButton(toolsBox);                            // skalowanie
      scaleButton->setIconSet(QIconSet(QPixmap(Icons::scaleIcon())));
      scaleButton->setTextLabel(tr("Scale (S)"), true);
      scaleButton->setToggleButton(true);
      scaleButton->setAutoRaise(true);
      connect(scaleButton, SIGNAL(clicked()), this, SLOT(buttonClicked()));

      linkButton = new QToolButton(toolsBox);
      linkButton->setIconSet(QIconSet(QPixmap(Icons::linkIcon())));
      linkButton->setTextLabel(tr("Link object to another (L)"), true);
      linkButton->setToggleButton(true);
      linkButton->setAutoRaise(true);
      connect(linkButton, SIGNAL(clicked()), this, SLOT(buttonClicked()));

      emptyWidget = new QWidget( toolsBox );
      
      transCoordsButton = new QToolButton( toolsBox );
      transCoordsButton->setIconSet( QIconSet( QPixmap( Icons::moveIcon() ) ) );
      transCoordsButton->setTextLabel( tr("Translate object's coords"), true );
      transCoordsButton->setToggleButton( true );
      transCoordsButton->setAutoRaise( true );
      connect( transCoordsButton, SIGNAL(clicked()), this, SLOT(buttonClicked()) );
          
      rotateCoordsButton = new QToolButton( toolsBox );
      rotateCoordsButton->setIconSet( QIconSet( QPixmap( Icons::rotateIcon() ) ) );
      rotateCoordsButton->setTextLabel( tr("Rotate object's coords"), true );
      rotateCoordsButton->setToggleButton( true );
      rotateCoordsButton->setAutoRaise( true );
      connect( rotateCoordsButton, SIGNAL(clicked()), this, SLOT(buttonClicked()) );
        
    grid->addWidget(toolsBox, 0,0);

     QFont f( this->font() );
     f.setPointSize( f.pointSize() - 2);
     QFont ff = f;
     ff.setPointSize(ff.pointSize() - 3);


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////// EDIT BOX
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////


    editBox = new QGroupBox( tr("Transformation"), this );
    editBox->setAlignment( Qt::AlignHCenter );
    editGrid = new QGridLayout(editBox, 8,3, 5,5);  // 7rows+spacer, 3cols

    doubleValidator = new QDoubleValidator(this);     // validator dla wspolrzednych transform.
    doubleValidator->setDecimals( Options::decimals() );

    

//////////////////////////////////////////////////////////////////////////// TRANSLATION
    QSpacerItem *editSpacer = new QSpacerItem(5,15, QSizePolicy::Maximum,QSizePolicy::Fixed);
    editGrid->addItem( editSpacer, 0,0 );
    
    QLabel *transLabel = new QLabel(tr("<I>Translation</I>"), editBox);
   editGrid->addMultiCellWidget(transLabel, 1,1, 0,2);

    QHBox *thbox = new QHBox( editBox );
    thbox->setSpacing( 3 );
      
      QLabel *tx = new QLabel(tr("X"), thbox); tx->setFont(ff);
      txe = new QLineEdit(thbox);         // pole do edycji x-owej skladowej wektora translacji
      txe->setValidator(doubleValidator);
      txe->setFont(f);
       connect(txe, SIGNAL(returnPressed()), this, SLOT(setTrans())); // update widoku

      QLabel *ty = new QLabel(tr("Y"), thbox); ty->setFont(ff);
      tye = new QLineEdit(thbox);
      tye->setValidator(doubleValidator);
      tye->setFont(f);
       connect(tye, SIGNAL(returnPressed()), this, SLOT(setTrans()));

      QLabel *tz = new QLabel(tr("Z"), thbox); tz->setFont(ff);
      tze = new QLineEdit(thbox);
      tze->setValidator(doubleValidator);
      tze->setFont(f);
       connect(tze, SIGNAL(returnPressed()), this, SLOT(setTrans()));

    editGrid->addMultiCellWidget(thbox, 2,2, 0,2);


//////////////////////////////////////////////////////////////////////////// ROTATION
      QLabel *rotLabel = new QLabel(tr("<I>Rotation</I>"), editBox);
      editGrid->addMultiCellWidget(rotLabel, 3,3, 0,2);

    QHBox *rhbox = new QHBox(editBox);
    rhbox->setSpacing( 3 );

      QLabel *rx = new QLabel(tr("X"), rhbox); rx->setFont(ff);
      rxe = new QLineEdit(rhbox);
      rxe->setValidator(doubleValidator);
      rxe->setFont(f);
       connect(rxe, SIGNAL(returnPressed()), this, SLOT(setRot()));

      QLabel *ry = new QLabel(tr("Y"), rhbox); ry->setFont(ff);
      rye = new QLineEdit(rhbox);
      rye->setValidator(doubleValidator);
      rye->setFont(f);
       connect(rye, SIGNAL(returnPressed()), this, SLOT(setRot()));

      QLabel *rz = new QLabel(tr("Z"), rhbox); rz->setFont(ff);
      rze = new QLineEdit(rhbox);
      rze->setValidator(doubleValidator);
      rze->setFont(f);
       connect(rze, SIGNAL(returnPressed()), this, SLOT(setRot()));

    editGrid->addMultiCellWidget(rhbox, 4,4, 0,2);

////////////////////////////////////////////////////////////////////////////////// STOPNIE i RADIANY
    QHBox *kbox = new QHBox(editBox);
    kbox->setSpacing( 3 );

      degRadio = new QRadioButton(tr("degrees"), kbox);
      degRadio->setFont(f);
      degRadio->setChecked(true);
       connect(degRadio, SIGNAL(toggled(bool)), this, SLOT(setDeg(bool)));

      radRadio = new QRadioButton(tr("radians"), kbox);
      radRadio->setFont(f);
      radRadio->setChecked(false);
       connect(radRadio, SIGNAL(toggled(bool)), this, SLOT(setRad(bool)));

      QWidget* filler = new QWidget( kbox );
      filler->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Ignored );
       
      editGrid->addMultiCellWidget(kbox, 5,5, 0,2);

//////////////////////////////////////////////////////////////////////////// SCALE
      QLabel *scaleLabel = new QLabel(tr("<I>Scale</I>"), editBox);
      editGrid->addMultiCellWidget(scaleLabel, 6,6, 0,2);

    QHBox *shbox = new QHBox(editBox);
    shbox->setSpacing( 3 );

      QLabel *sx = new QLabel(tr("X"), shbox);
      sx->setFont(ff);
      sxe = new QLineEdit(shbox);
      sxe->setValidator(doubleValidator);
      sxe->setFont(f);
       connect(sxe, SIGNAL(returnPressed()), this, SLOT(setScale()));

      QLabel *sy = new QLabel(tr("Y"), shbox);      
      sy->setFont(ff);
      sye = new QLineEdit(shbox);
      sye->setValidator(doubleValidator);
      sye->setFont(f);
       connect(sye, SIGNAL(returnPressed()), this, SLOT(setScale()));

      QLabel *sz = new QLabel(tr("Z"), shbox);      
      sz->setFont(ff);
      sze = new QLineEdit(shbox);
      sze->setValidator(doubleValidator);
      sze->setFont(f);
       connect(sze, SIGNAL(returnPressed()), this, SLOT(setScale()));

    editGrid->addMultiCellWidget(shbox, 7,7, 0,2);


     grid->addWidget(editBox, 1,0);


     
/////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////// FIT BOX
/////////////////////////////////////////////////////////////////////////////////////////////////////////
     fitScaleBox = new QGroupBox(3, Qt::Horizontal, tr(" Dimensions "), this);
     fitScaleBox->setAlignment( Qt::AlignHCenter );
     widthEdit  = new QLineEdit( fitScaleBox ); 
      widthEdit->setValidator(doubleValidator);
      widthEdit->setFont(f);
     heightEdit = new QLineEdit( fitScaleBox ); 
      heightEdit->setValidator(doubleValidator);
      heightEdit->setFont(f);
     depthEdit  = new QLineEdit( fitScaleBox ); 
      depthEdit->setValidator(doubleValidator);
      depthEdit->setFont(f);
     
    connect(widthEdit, SIGNAL(returnPressed()), this, SLOT(fitScale()));
    connect(heightEdit, SIGNAL(returnPressed()), this, SLOT(fitScale()));
    connect(depthEdit, SIGNAL(returnPressed()), this, SLOT(fitScale()));
      
     QLabel *widthLabel  = new QLabel(tr("width"), fitScaleBox);
      widthLabel->setFont(f);
      widthLabel->setAlignment( Qt::AlignHCenter );
     QLabel *heightLabel = new QLabel(tr("height"),fitScaleBox); 
      heightLabel->setFont(f);
      heightLabel->setAlignment( Qt::AlignHCenter );
     QLabel *depthLabel  = new QLabel(tr("depth"), fitScaleBox); 
      depthLabel->setFont(f);
      depthLabel->setAlignment( Qt::AlignHCenter );
     
     grid->addWidget(fitScaleBox, 2,0);
     

////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////// COORDS BOX
/////////////////////////////////////////////////////////////////////////////////////////////////////////
   
   coordsBox = new QGroupBox( tr(" Coords transformation "), this );
   coordsBox->setAlignment( Qt::AlignHCenter );
   QGridLayout *coordsGrid = new QGridLayout( coordsBox, 5,1, 5,5 );
     
     QSpacerItem *spacer = new QSpacerItem( 5,15, QSizePolicy::Maximum, QSizePolicy::Fixed );
     coordsGrid->addItem( spacer, 0,0 );
    
     ctLabel = new QLabel( tr("<I>Translation</I>"), coordsBox );
     coordsGrid->addMultiCellWidget( ctLabel, 1,1, 0,0 );
     
     QHBox *ctBox = new QHBox( coordsBox );
     ctBox->setSpacing( 3 );
      QLabel* ctxl = new QLabel( tr("X"), ctBox );
      ctxl->setFont( ff );
      ctxe = new QLineEdit( ctBox );
      ctxe->setValidator(doubleValidator);
      ctxe->setFont( f );
      QLabel* ctyl = new QLabel( tr("Y"), ctBox );
      ctyl->setFont( ff );
      ctye = new QLineEdit( ctBox );
      ctye->setValidator(doubleValidator);
      ctye->setFont( f );
      QLabel* ctzl = new QLabel( tr("Z"), ctBox );
      ctzl->setFont( ff );
      ctze = new QLineEdit( ctBox );
      ctze->setValidator(doubleValidator);
      ctze->setFont( f );
     coordsGrid->addWidget( ctBox, 2,0 );
    
     connect( ctxe, SIGNAL( returnPressed() ), this, SLOT( setCoordsTrans() ) );
     connect( ctye, SIGNAL( returnPressed() ), this, SLOT( setCoordsTrans() ) );
     connect( ctze, SIGNAL( returnPressed() ), this, SLOT( setCoordsTrans() ) );
     
     crLabel = new QLabel( tr("<I>Rotation</I>"), coordsBox );
     coordsGrid->addMultiCellWidget( crLabel, 3,3, 0,0 );
     
     QHBox *crBox = new QHBox( coordsBox );
     crBox->setSpacing( 3 );
      QLabel* crxl = new QLabel( tr("X"), crBox );
      crxl->setFont( ff );
      crxe = new QLineEdit( crBox );
      crxe->setValidator(doubleValidator);
      crxe->setFont( f );
      QLabel* cryl = new QLabel( tr("Y"), crBox );
      cryl->setFont( ff );
      crye = new QLineEdit( crBox );
      crye->setValidator(doubleValidator);
      crye->setFont( f );
      QLabel* crzl = new QLabel( tr("Z"), crBox );
      crzl->setFont( ff );
      crze = new QLineEdit( crBox );
      crze->setValidator(doubleValidator);
      crze->setFont( f );
     coordsGrid->addWidget( crBox, 4,0 );
  
     connect( crxe, SIGNAL( returnPressed() ), this, SLOT( setCoordsRot() ) );
     connect( crye, SIGNAL( returnPressed() ), this, SLOT( setCoordsRot() ) );
     connect( crze, SIGNAL( returnPressed() ), this, SLOT( setCoordsRot() ) );
     
   grid->addWidget( coordsBox, 3,0 );    
     
         
/////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////// NAME BOX
/////////////////////////////////////////////////////////////////////////////////////////////////////////
  nameBox = new QGroupBox( tr(" Object's name "), this );
  nameBox->setAlignment( Qt::AlignHCenter );
  QGridLayout *nameGrid = new QGridLayout(nameBox, 4,2, 5,5); // 3rows + spacer, 2cols

      noDotValidator = new NoDotValidator(this);  // validator zabraniajacy wprowadzenia kropki

      QSpacerItem *nameSpacer = new QSpacerItem(5,15, QSizePolicy::Maximum, QSizePolicy::Fixed);
     nameGrid->addItem( nameSpacer, 0,0 );
      
      QLabel *obNameLabel = new QLabel(tr("Name:"), nameBox);
      obNameLabel->setFont(f);
     nameGrid->addWidget(obNameLabel, 1,0);

      obNameEdit = new QLineEdit(nameBox);
      obNameEdit->setFont(f);
      obNameEdit->setValidator(noDotValidator);
      obNameLabel->setBuddy(obNameEdit);
       connect(obNameEdit, SIGNAL(textChanged(const QString&)), this, SLOT(setName(const QString&)));
      //connect( onNameEdit, SIGNAL(returnPressed()), this, SLOT(setNameFromEdit()) );
     nameGrid->addWidget(obNameEdit, 1,1);
///////////////////////////////////////////////////////////////////////////////////////////////////// PARENT
      QLabel *obParentLabel = new QLabel(tr("Parent:"), nameBox);
      obParentLabel->setFont(f);
     nameGrid->addWidget(obParentLabel, 2,0);

      obParentEdit = new QLineEdit(nameBox);
      obParentEdit->setFont(f);
      obParentEdit->setReadOnly(true);
      obParentLabel->setBuddy(obParentEdit);
     nameGrid->addWidget(obParentEdit, 2,1);  
///////////////////////////////////////////////////////////////////////////////////////////////////// PATH
      QLabel *obPathLabel = new QLabel(tr("Path:"), nameBox);
      obPathLabel->setFont(f);
     nameGrid->addWidget(obPathLabel, 3,0);
      obPathEdit = new QLineEdit(nameBox);
      obPathEdit->setFont(f);
      obPathEdit->setReadOnly(true);
      obPathLabel->setBuddy(obPathEdit);
     nameGrid->addWidget(obPathEdit, 3,1);

   grid->addWidget( nameBox, 4,0 );

///////////////////////////////////////////////////////////////////////////////////////// PRIMITIVE TYPE   
   primitiveTypeBox = new QGroupBox( 1, Qt::Horizontal, tr(" Primitive type "), this );
   primitiveTypeBox->setAlignment( Qt::AlignHCenter );
   primitiveTypeCombo = new QComboBox( false, primitiveTypeBox );
   primitiveTypeCombo->setFont( f );
   grid->addWidget( primitiveTypeBox, 5,0 );
   connect( primitiveTypeCombo, SIGNAL( activated(int) ), this, SLOT( primitiveTypeChanged(int) ) );
   
  
  // g³ówny grid - koñcowy wype³niacz
  QSpacerItem *mainSpacer = new QSpacerItem(10,10, QSizePolicy::Expanding, QSizePolicy::Expanding);
  grid->addItem( mainSpacer, 6,0 );


    currentButton = selectButton;  // na pocz±tku domy¶lnym modyfikatorem jest select
    currentButton->setOn(true);    // w³±czamy go
    emit sendModifier((MModifier*) mSelect);  // i wysy³amy
    
    enableInput( false ); // wy³±czamy ca³y input
}



// publiczny slot, ustawiajacy listê nazw bry³ elementarnych dla primitiveTypeCombo
void ModifyWidget::setPrimitiveList( QStringList* primitiveList )
{
  _primitiveList = primitiveList;
  primitiveTypeCombo->clear();
  primitiveTypeCombo->insertStringList( *_primitiveList, 0 );
}
  
  

/*!
Metoda ustawia nazwê dla obiektu, testuje poprawno¶æ ci±gu i obecno¶æ obiektu o takiej nazwie.
*/
void ModifyWidget::setName(const QString &name)
{
  // tutaj powinno nastapic sprawdzenie czy obiekt o tej nazwie juz nie istnieje
  if (_selectedList == 0L) return;
  
  // lista jest pusta - nadajemy nazwê g³ównemu _mp
  if ( _selectedList->isEmpty() && obNameEdit->hasAcceptableInput() && name!="" )
  {
    ViMultiPolyh *mp = CellFrame::multiPolyh();
    mp->SetNodeName(name.ascii());
    ViNodeAddress adr = mp->GetNodeAddress();
    obPathEdit->setText( QString(adr.c_str()) );
    emit nameChanged();
    return;
  }
  
  
  if (obNameEdit->hasAcceptableInput() && name!="")
  {
     ViNTreeNode *_selected = _selectedList->last();

     _selected->SetNodeName(name.ascii());
     ViNodeAddress adr = _selected->GetNodeAddress();
     obPathEdit->setText(QString(adr.c_str()));
     emit nameChanged();
  }
}



// blokuje lub odblokowuje sygnaly textChanged, emitowane przez QLineEdits
// obecnie ta metoda nie ma sensu, poniewa¿ pod³±czy³em LineEdits sygna³
// returnPressed() zamiast valueChanged()
void ModifyWidget::block(bool yes)
{
  /*
  txe->blockSignals(yes);
  tye->blockSignals(yes);
  tze->blockSignals(yes);
  rxe->blockSignals(yes);
  rye->blockSignals(yes);
  rze->blockSignals(yes);
  sxe->blockSignals(yes);
  sye->blockSignals(yes);
  sze->blockSignals(yes);
  widthEdit->blockSignals(yes);
  heightEdit->blockSignals(yes);
  depthEdit->blockSignals(yes);
  */
  obNameEdit->blockSignals( yes );
  obParentEdit->blockSignals( yes );
  obPathEdit->blockSignals( yes );
}



// ustawia wektor translacji obiektowi, QString &s jest ignorowany
void ModifyWidget::setTrans()
{
  if (_selectedList == 0L) return;

  if (_selectedList->isEmpty() || (_selectedList->count()>1)) return;

  /* poni¿szy warunek sprawdza sygna³ returnPressed(), wiêc nie trzeba tego tutaj robiæ
  if (txe->hasAcceptableInput() && txe->text()!="" &&
      tye->hasAcceptableInput() && tye->text()!="" &&
      tze->hasAcceptableInput() && tze->text()!="") */
  {                                                          // ustaw translacje elementowi
    Vector3f t(txe->text().toFloat(), tye->text().toFloat(), tze->text().toFloat());

    ViNTreeNode *_selected = _selectedList->last(); // ustawia translacjê tylko ostatniemu elementowi
    MatrixH3f m = _selected->Mtx2ParentCoord();
    m.SetTrans_TAfterR( t );
    _selected->SetMtx2ParentCoord(m);

    CellFrame::refresh();
  }
}


// ustawia wektor rotacji, QString &s jest ignorowany
void ModifyWidget::setRot()
{
  if (_selectedList == 0L) return;

  if (_selectedList->isEmpty() || (_selectedList->count()>1)) return;

  /*
  if (rxe->hasAcceptableInput() && rxe->text()!="" &&
      rye->hasAcceptableInput() && rye->text()!="" &&
      rze->hasAcceptableInput() && rze->text()!="") */
  {

    Vector3f r(rxe->text().toFloat(), rye->text().toFloat(), rze->text().toFloat());

    ViNTreeNode *_selected = _selectedList->last();
    MatrixH3f m = _selected->Mtx2ParentCoord();

      if (_rad) // jezeli podane w rad
      {
        m.SetAng_XYZ_TAfterR_Rad( r );
        //m.NewRotX(r.x);
        //m.NewRotY(r.y);
        //m.NewRotZ(r.z);
      }
      else   // podane w deg
      {
        //m.NewRotX(r.x*PI/180.0);
        //m.NewRotY(r.y*PI/180.0);
        //m.NewRotZ(r.z*PI/180.0);
        m.SetAng_XYZ_TAfterR_Deg( r.x, r.y, r.z );
      }

    _selected->SetMtx2ParentCoord(m);
    CellFrame::refresh();
  } // if wpisane
} 




// ustawia wektor skali, QString &s jest ignorowany
void ModifyWidget::setScale()
{
  if (_selectedList == 0L) return;

  //if (_selectedList->isEmpty() || (_selectedList->count()>1)) return;    

  /*
  if (sxe->hasAcceptableInput() && sxe->text()!="" &&
      sye->hasAcceptableInput() && sye->text()!="" &&
      sze->hasAcceptableInput() && sze->text()!="") */
  {

    Vector3f s(sxe->text().toFloat(), sye->text().toFloat(), sze->text().toFloat());
    if (s.x == 0.0) return;
    if (s.y == 0.0) return;
    if (s.z == 0.0) return;


    ViNTreeNode *_selected = _selectedList->last();
    MatrixH3f m;
    
      switch (_selected->GetInheritorType())
      {
        case IT_MULTIPOLYH : m = _selected->Mtx2ParentCoord(); break;
        case IT_ELEMEPOLYH : m = ((ViElemePolyhExt*) _selected)->Mtx2ElemeCoord(); break;
        default : m = _selected->Mtx2ParentCoord(); break;
      }

    m.SetScale_TAfterR( s );

      switch (_selected->GetInheritorType())
      {
        case IT_MULTIPOLYH : _selected->SetMtx2ParentCoord(m); break;
        case IT_ELEMEPOLYH : ((ViElemePolyhExt*) _selected)->SetMtx2ElemeCoord(m); break;
        default : _selected->SetMtx2ParentCoord(m); break;
      }

      CellFrame::refresh();
      
    // przelicz dla tej skali wymiary obiektu
    updateData( MModifier::M_SCALE, s );
  }
}



// ustawia wektor skali tak, ¿eby uzyskane zosta³y ¿±dane wymiary
void ModifyWidget::fitScale()
{
  if (_selectedList == 0L) return;

  if (_selectedList->isEmpty() || (_selectedList->count()>1)) return;

  /*
  if (widthEdit->hasAcceptableInput() && widthEdit->text()!="" &&
      heightEdit->hasAcceptableInput() && heightEdit->text()!="" &&
      depthEdit->hasAcceptableInput() && depthEdit->text()!="") */
  {                                                          // ustaw skalê elementowi
    
    // s jest wektorem zadanych wymiarów
    Vector3f dim( widthEdit->text().toFloat(), heightEdit->text().toFloat(), depthEdit->text().toFloat() );
    
    if ((dim.x == 0.0) || (dim.y == 0.0) || (dim.z == 0.0)) return;

    ViNTreeNode *_selected = _selectedList->last(); // ustawia tylko ostatniemu elementowi
    
    MatrixH3f m;
    Vector3f vMin, vMax;
    float width = 0.0, height = 0.0, depth = 0.0;
    
    // zczytujemy wymiary w zale¿no¶ci od typu bry³y
    switch (_selected->GetInheritorType())
    {
      case IT_MULTIPOLYH : {
                            ViMultiPolyh *_mp = dynamic_cast<ViMultiPolyh*> (_selected);
                            // dla multiPolyha obowi±zuje obrys                           
                            vMin.Set( _mp->GlbOlnBox().Min() );
                            vMax.Set( _mp->GlbOlnBox().Max() );
                            width  = abs( vMax.x - vMin.x );
                            height = abs( vMax.y - vMin.y );
                            depth  = abs( vMax.z - vMin.z );
                            m = _mp->Mtx2ParentCoord();
                           } break;
      case IT_ELEMEPOLYH : {
                            ViElemePolyhExt *_el = (ViElemePolyhExt*) (_selected);
                            // tymczasowy element dla obliczenia pierwotnych rozmiarów
                            ViElemePolyhExt _newEl ( _el->PattePolyh(), "tmp" );
                            MatrixH3f m1;
                            _newEl.ComputeGlbVtx( m1 );
                            // oryginalne rozmiary
                            vMin.Set( _newEl.GlbOlnBox().Min() );
                            vMax.Set( _newEl.GlbOlnBox().Max() );
                            width  = abs (( vMax.x - vMin.x ));
                            height = abs (( vMax.y - vMin.y ));
                            depth  = abs (( vMax.z - vMin.z ));
                            //m = ((ViElemePolyhExt*) _selected)->Mtx2ElemeCoord();
                            m.SetUnitMtx();
                           } break;
      default : StatusBar::printStatusMsg(tr("error"), "ModifyWidget"); break;
    }
    
    // wspó³czynniki mno¿enia skali
    float wFactor = dim.x  / width;
    float hFactor = dim.y  / height;
    float dFactor = dim.z  / depth;
    
    // nowy wektor skali jest wynikiem mno¿enia poprzedniego wektora i wspó³czynników ró¿nicy
    Vector3f oldS = m.GetScale();
    Vector3f newS( oldS.x*wFactor,  oldS.y*hFactor,  oldS.z*dFactor );
    
    m.SetScale_TAfterR( newS );

    switch (_selected->GetInheritorType())
    {
      case IT_MULTIPOLYH : _selected->SetMtx2ParentCoord(m); break;
      case IT_ELEMEPOLYH : ((ViElemePolyhExt*) _selected)->SetMtx2ElemeCoord(m); break;
      default : _selected->SetMtx2ParentCoord(m); break;
    }

    
    /*
    sxe->setText( QString::number( wFactor, 'f', Options::decimals() ) );
    sye->setText( QString::number( hFactor, 'f', Options::decimals() ) );
    sze->setText( QString::number( dFactor, 'f', Options::decimals() ) );
    setScale();
    */
    
    CellFrame::refresh();
    
    // u¿ywamy slotu uaktualnienia dla modyfikatora skali, ¿eby wype³ni³ odpowiednio lineEdits
    updateData( MModifier::M_SCALE, newS );

  }
}





// przestaw na wyswietlanie katow w stopniach
void ModifyWidget::setDeg(bool on)
{
  if (on)
  {
     block(true); // blokuj sygnaly textChanged
    _rad = false;
    radRadio->setChecked(false);
    degRadio->setChecked(true);
    rxe->setText( QString::number(rxe->text().toFloat()*180.0/PI, 'f', Options::decimals()) );
    rye->setText( QString::number(rye->text().toFloat()*180.0/PI, 'f', Options::decimals()) );
    rze->setText( QString::number(rze->text().toFloat()*180.0/PI, 'f', Options::decimals()) );
     block(false);
  }
}

// przestaw na wyswietlanie katow w radianach
void ModifyWidget::setRad(bool on)
{
  if (on)
  {
     block(true); // blokuj sygnaly textChanged
    _rad = true;
    degRadio->setChecked(false);
    radRadio->setChecked(true);
    rxe->setText( QString::number(rxe->text().toFloat()*PI/180.0, 'f', Options::decimals()) );
    rye->setText( QString::number(rye->text().toFloat()*PI/180.0, 'f', Options::decimals()) );
    rze->setText( QString::number(rze->text().toFloat()*PI/180.0, 'f', Options::decimals()) );
     block(false);
  }
}



// metoda ustawia wektor translacji dla wspó³rzêdnych obiektu
void ModifyWidget::setCoordsTrans()
{
  if (_selectedList == 0L) return;

  if ( _selectedList->isEmpty() || (_selectedList->count()>1) ) return;

  Vector3f t( ctxe->text().toFloat(), ctye->text().toFloat(), ctze->text().toFloat() );

  ViNTreeNode *_selected = _selectedList->last(); // ustawia translacjê tylko ostatniemu elementowi
  
  ViElemePolyhExt *extEl = dynamic_cast<ViElemePolyhExt*>(_selected);
  if ( !extEl ) return; // tylko obiektom klasy ViElemePolyhExt mo¿na zmieniaæ translacjê koordynat
  
  MatrixH3f m = extEl->Mtx2IndivCoord();
  m.SetTrans_TAfterR( t );
  extEl->SetMtx2IndivCoord(m);

  CellFrame::refresh();
}




// metoda ustawia wektor rotacji dla wspó³rzêdnych obiektu
void ModifyWidget::setCoordsRot()
{
  if ( _selectedList == 0L ) return;

  if (_selectedList->isEmpty() || (_selectedList->count()>1)) return;

  Vector3f r( crxe->text().toFloat(), crye->text().toFloat(), crze->text().toFloat() );

  ViNTreeNode *_selected = _selectedList->last();
  
  ViElemePolyhExt *extEl = dynamic_cast<ViElemePolyhExt*>(_selected);
  if ( !extEl ) return; // tylko obiektom ViElemePolyhExt mo¿na zadawaæ rotacjê koordynat
  
  MatrixH3f m = extEl->Mtx2IndivCoord();

  if (_rad) // jezeli podane w rad
  {
    //m.NewRotX(r.x);
    //m.NewRotY(r.y);
    //m.NewRotZ(r.z);
    m.SetAng_XYZ_TAfterR_Rad( r );
  }
  else  // w stopniach
  {
    //m.NewRotX(r.x*PI/180.0);
    //m.NewRotY(r.y*PI/180.0);
    //m.NewRotZ(r.z*PI/180.0);
    m.SetAng_XYZ_TAfterR_Deg( r.x, r.y, r.z );
  }

    extEl->SetMtx2IndivCoord(m);
    CellFrame::refresh();
}





// od¶wie¿a dane w okienkach pod wp³ywem dzia³ania modyfikatora
void ModifyWidget::updateData(MModifier::ModifierType mType, Vector3f v)
{
  if (_selectedList == 0L) return;
  if (_selectedList->isEmpty()) return;
  
  CellFrame::multiPolyh()->ComputeHierAllGlbVtx();     
      
  
  block(true); // blokuj sygnaly textChanged

  switch (mType)
  {
    case MModifier::M_SELECT : break;
    case MModifier::M_TRANSLATE : {
                                    txe->setText( QString::number( v.x, 'f', Options::decimals() ) );
                                    tye->setText( QString::number( v.y, 'f', Options::decimals() ) );
                                    tze->setText( QString::number( v.z, 'f', Options::decimals() ) );           
                                  } break;
    case MModifier::M_ROTATE : {
                                if (_rad) // przelicz na radiany (modyfikator zwraca w stopniach)
                                {
                                  rxe->setText( QString::number( v.x*PI/180.0, 'f', Options::decimals() ) );
                                  rye->setText( QString::number( v.y*PI/180.0, 'f', Options::decimals() ) );
                                  rze->setText( QString::number( v.z*PI/180.0, 'f', Options::decimals() ) );
                                }
                                else
                                {
                                  rxe->setText( QString::number( v.x, 'f', Options::decimals() ) );
                                  rye->setText( QString::number( v.y, 'f', Options::decimals() ) );
                                  rze->setText( QString::number( v.z, 'f', Options::decimals() ) );
                                }
                               } break;
    case MModifier::M_SCALE : {
                                sxe->setText( QString::number( v.x, 'f', Options::decimals() ) );
                                sye->setText( QString::number( v.y, 'f', Options::decimals() ) );
                                sze->setText( QString::number( v.z, 'f', Options::decimals() ) );
                                
                                // tutaj obliczamy aktualne wymiary obiektu dla danej skali
                                float width = 0.0, height = 0.0, depth = 0.0;
                                Vector3f vMin, vMax;
                                ViNTreeNode *_selected = _selectedList->last();
                                
                                switch ( _selected->GetInheritorType() )
                                {
                                  case IT_MULTIPOLYH : {
                                                        ViMultiPolyh* _mp = dynamic_cast<ViMultiPolyh*> (_selected);
                                                        // dla mp jest to na razie rozmiar outLineBox
                                                        vMin.Set( _mp->GlbOlnBox().Min() );
                                                        vMax.Set( _mp->GlbOlnBox().Max() );
                                                        width  = abs( vMax.x - vMin.x );
                                                        height = abs( vMax.y - vMin.y );
                                                        depth  = abs( vMax.z - vMin.z );
                                                       } break;
                                  case IT_ELEMEPOLYH : {
                                                        ViElemePolyhExt* _el = dynamic_cast<ViElemePolyhExt*> (_selected);
                                                        
                                                        // skala obiektu
                                                        MatrixH3f m = _el->Mtx2ElemeCoord();
                                                        Vector3f vs = m.GetScale();
                                                        // tymczasowy element dla obliczenia rozmiarów
                                                        ViElemePolyhExt _newEl ( _el->PattePolyh(), "tmp" );
                                                        MatrixH3f m1;
                                                        _newEl.ComputeGlbVtx(m1);
                                                        // oryginalne rozmiary
                                                        vMin.Set( _newEl.GlbOlnBox().Min() );
                                                        vMax.Set( _newEl.GlbOlnBox().Max() );
                                                        width  = abs (( vMax.x - vMin.x ) * vs.x );
                                                        height = abs (( vMax.y - vMin.y ) * vs.y );
                                                        depth  = abs (( vMax.z - vMin.z ) * vs.z );
                                                       } break;
                                  default : break;
                                } // ma³y switch
                                
                                widthEdit->setText ( QString::number( width,  'f', Options::decimals() ) );
                                heightEdit->setText( QString::number( height, 'f', Options::decimals() ) );
                                depthEdit->setText ( QString::number( depth,  'f', Options::decimals() ) );
                                
                              } break;
    case MModifier::M_LINK : {
                                  // od¶wie¿yæ ¶cie¿kê i rodzica
                               } break;
    case MModifier::M_TRANSLATECOORDS : {
                                          ctxe->setText( QString::number( v.x, 'f', Options::decimals() ) );
                                          ctye->setText( QString::number( v.y, 'f', Options::decimals() ) );
                                          ctze->setText( QString::number( v.z, 'f', Options::decimals() ) );
                                        } break;
    case MModifier::M_ROTATECOORDS : {
                                        crxe->setText( QString::number( v.x, 'f', Options::decimals() ) );
                                        crye->setText( QString::number( v.y, 'f', Options::decimals() ) );
                                        crze->setText( QString::number( v.z, 'f', Options::decimals() ) );
                                     } break;                                                                               
    default : break;
  }

  block(false);
}


// w³±cza/wy³±cza przyciski i widgety do wpisywania translacji, skali, itd.
void ModifyWidget::enableInput( bool yes )
{
  toolsBox->setEnabled( yes );
  editBox->setEnabled( yes );
  coordsBox->setEnabled( yes );
  fitScaleBox->setEnabled( yes );
  primitiveTypeBox->setEnabled( yes );
}


// ustawia zaznaczony obiekt (bierze pod uwagê ostatni) i wypelnia pola danymi
void ModifyWidget::setSelected(QPtrList<ViNTreeNode> *selectedList)
{
  _selectedList = selectedList;

  block(true);
   
  // czy¶cimy wszystkie pola
  if ( _selectedList->isEmpty() ) // pokazujemy nazwê i ¶cie¿ki g³ównego _mp
  {
    enableInput( false );
    
    // przesuniêcia, rotacje i skale
    txe->clear(); tye->clear(); tze->clear();
    rxe->clear(); rye->clear(); rze->clear();
    sxe->clear(); sye->clear(); sze->clear();
    widthEdit->clear(); heightEdit->clear(); depthEdit->clear();
    // wspó³rzêdne
    ctxe->clear(); ctye->clear(); ctze->clear();
    crxe->clear(); crye->clear(); crze->clear();
    
    
    QString s;
    ViMultiPolyh *mp = CellFrame::multiPolyh();
    if ( mp != 0L ) // wy¶wietlamy informacje o g³ównym _mp
    {
      obNameEdit->blockSignals( true );
      s = mp->NodeName();
      obNameEdit->setText( s );
      obNameEdit->blockSignals( false );
    
      obParentEdit->setText( tr("no parent") );
    
      ViNodeAddress adr = mp->GetNodeAddress();
      s = adr.c_str();
      obPathEdit->setText( s );
    }   
    
    return;
  }
  
  enableInput( true );
  
  ViNTreeNode *_selected = (ViNTreeNode*) _selectedList->last();   // wy¶wietlamy wsp ostatniego obiektu

  Vector3f _trans = _selected->Mtx2ParentCoord().GetTrans_TAfterR();
  Vector3f _rot = _selected->Mtx2ParentCoord().GetAng_XYZ_Deg();
  Vector3f _scale;
  Vector3f _cTrans;
  Vector3f _cRot;
  
  switch ( _selected->GetInheritorType() )
  {
    case IT_MULTIPOLYH : _scale = _selected->Mtx2ParentCoord().GetScale(); break;
    case IT_ELEMEPOLYH : {
                            _scale = ((ViElemePolyhExt*) _selected)->Mtx2ElemeCoord().GetScale();
                            // dla ViElemePolyhExt mo¿emy modyfikowaæ indywidualny uk³ad wsp.
                            _cTrans = ((ViElemePolyhExt*) _selected)->Mtx2IndivCoord().GetTrans_TAfterR();
                            _cRot = ((ViElemePolyhExt*) _selected)->Mtx2IndivCoord().GetAng_XYZ_Deg();
                         } break;
    default : _scale = _selected->Mtx2ParentCoord().GetScale(); break;
  }
  
  
  updateData( MModifier::M_TRANSLATE, _trans );
  updateData( MModifier::M_ROTATE, _rot );
  updateData( MModifier::M_SCALE, _scale );
  updateData( MModifier::M_TRANSLATECOORDS, _cTrans );
  updateData( MModifier::M_ROTATECOORDS, _cRot );

  QString s;
  if (_selectedList->count() == 1) // dla pojedynczego obiektu wypisujemy nazwe, rodzica i sciezke
  {
    obNameEdit->blockSignals( true );
    s = _selected->NodeName();
    obNameEdit->setText( s );
    obNameEdit->blockSignals( false );
    
    s = _selected->GetParentNode()->NodeName();
    obParentEdit->setText( s );
    
    ViNodeAddress adr = _selected->GetNodeAddress();
    s = adr.c_str();
     obPathEdit->setText( s );
  }
  else  // dla wielu obiektow INFO
  {
    obNameEdit->clear();
    obParentEdit->clear();
    obPathEdit->clear();
  }

  // typ prymitywu tylko dla obiektów elementarnych
  if ( _selected->GetInheritorType() == IT_ELEMEPOLYH )
  {
    primitiveTypeBox->setEnabled( true ); // w³±czamy combo
    ViElemePolyhExt *extEl = dynamic_cast<ViElemePolyhExt*> (_selected); // konwersja obiektu
    QString name( extEl->PattePolyh().GetName() ); // nazwa bry³y wzorcowej
    
    int ind = _primitiveList->findIndex( name ); // szukamy indeksu nazwy bry³y na li¶cie
    if ( ind != -1 ) primitiveTypeCombo->setCurrentItem( ind );  // znaleziono bry³ê
     else { primitiveTypeBox->setEnabled( false ); } // nie znaleziono - wy³±cz combo
    
  } else primitiveTypeBox->setEnabled( false ); // je¿eli nie jest to bry³a elementarna - OFF
  
  block(false);
}




// slot wywo³ywany przez primitiveTypeCombo, zmienia typ prymitywu dla aktualnej bry³y
void ModifyWidget::primitiveTypeChanged( int index )
{
  if ( _selectedList->isEmpty() ) return; // brak obiektu
  ViNTreeNode* _selected = _selectedList->last(); // bie¿emy tylko ostatni obiekt
  if ( _selected->GetInheritorType() != IT_ELEMEPOLYH ) return; // prymitywy maj± tylko bry³y elementarne
  
  ViPattePolyh const *pPaPolyh = Kernel::findPattePolyh( index ); // szukamy wska¼nika do bry³y wzorcowej
  if ( pPaPolyh ) // je¿eli jest taki wzorzec
  {
    ViElemePolyhExt* extEl = dynamic_cast<ViElemePolyhExt*> ( _selected );
    extEl->SetPattePolyh( pPaPolyh ); // ustawiamy bry³ê obiektowi
    CellFrame::refresh(); // od¶wie¿amy widoki
    emit nameChanged(); // troche oszukujemy wysy³aj±c sygna³ od¶wie¿enia do ObjectsWidget
  }  
}




// wylacza poprzedni aktywny przycisk i wlacza nowy !!!!! NIC NIE WYSYLA
void ModifyWidget::setActiveButton(QToolButton *activeButton)
{
  currentButton->setOn(false);
  currentButton = activeButton;
  currentButton->setOn(true);
  
  emit modifierChoosed();
}





// PRIVATE
// slot, ktory obsluguje sygnaly ze wszystkich guzikow
// uzywa metody QObject::sender() identyfikujacej jednoznacznie obiekt wysylajacy sygnal
// nie jest to zalecane (lamie idee obiektowosci), ale w tym przypadku uwazam to za bardzo dobre
// rozwiazanie, poniewaz stosowane jest w calkowicie bezpieczny sposob
void ModifyWidget::buttonClicked()
{ 
  QToolButton *tb = (QToolButton*) sender(); // konwersja obiektu wysylajacego sygnal na toolbutton

  if (tb == currentButton)                // jezeli przycisk ten jest juz aktywny - nie rob nic
  {
    currentButton->setOn(true); return;
  }

  if (tb == selectButton)                 // kliknieto przycisk selekcji
  {
    setActiveButton(selectButton);            // ustaw go jako przycisk aktywny
    emit sendModifier((MModifier*) mSelect);   // wyslij odpowiadajacy mu modyfikator
    return;
  }

  if (tb == transButton)                                   // itp
  {                                                        
    setActiveButton(transButton);
    emit sendModifier((MModifier*) mTrans);
    return;
  }

  if (tb == rotateButton)
  {
    setActiveButton(rotateButton);
    emit sendModifier((MModifier*) mRot);
    return;
  }

  if (tb == scaleButton)
  {
    setActiveButton(scaleButton);
    emit sendModifier((MModifier*) mScale);
    return;
  }

  if (tb == linkButton)
  {
    setActiveButton(linkButton);
    emit sendModifier((MModifier*) mLink);
    return;
  }
  
  if ( tb == transCoordsButton )
  {
    setActiveButton( transCoordsButton );
    emit sendModifier( (MModifier*) mTransCoords );
    return;
  }
  
  if ( tb == rotateCoordsButton )
  {
    setActiveButton( rotateCoordsButton );
    emit sendModifier( (MModifier*) mRotCoords );
    return;
  }
}



// z zewnatrz mozna ustawic domyslny modyfikator - SELEKCJA
void ModifyWidget::setDefaultModifier()
{
  setModifier(MModifier::M_SELECT);
}


// metoda pozwala ustawiæ z zewn±trz modyfikator
void ModifyWidget::setModifier(MModifier::ModifierType mType)
{
  switch (mType)
  {
    case MModifier::M_SELECT    : {
                                    setActiveButton(selectButton);
                                    emit sendModifier(dynamic_cast<MModifier*> (mSelect));
                                    break;
                                  }
    case MModifier::M_TRANSLATE : {
                                    setActiveButton(transButton);
                                    emit sendModifier(dynamic_cast<MModifier*> (mTrans));
                                    break;
                                  }
    case MModifier::M_ROTATE    : {
                                    setActiveButton(rotateButton);
                                    emit sendModifier(dynamic_cast<MModifier*> (mRot));
                                    break;
                                  }
    case MModifier::M_SCALE     : {
                                    setActiveButton(scaleButton);
                                    emit sendModifier(dynamic_cast<MModifier*> (mScale));
                                    break;
                                  }
    case MModifier::M_LINK      : {
                                    setActiveButton(linkButton);
                                    emit sendModifier(dynamic_cast<MModifier*> (mLink));
                                    break;
                                  }
    case MModifier::M_TRANSLATECOORDS : {
                                          setActiveButton( transCoordsButton );
                                          emit sendModifier( dynamic_cast<MModifier*> (mTransCoords) );
                                          break;
                                        }
    case MModifier::M_ROTATECOORDS : {
                                        setActiveButton( rotateCoordsButton );
                                        emit sendModifier( dynamic_cast<MModifier*> (mRotCoords) );
                                        break;
                                      }

    default                     : break;
  }
}

