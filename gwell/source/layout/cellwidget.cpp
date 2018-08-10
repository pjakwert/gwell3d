#include "cellwidget.h"


CellWidget::CellWidget(QWidget* parent, const char* name, WFlags fl) : QFrame(parent, name, fl)
{
    // styl ramki
    this->setFrameStyle(QFrame::Sunken);
    this->setFrameShape(QFrame::Box);

    // wymiary
    this->setMinimumSize(QSize(0,40));
    this->setMaximumSize(QSize(32767,40));

    cameraButton = new QToolButton(this);             // camera Button
    cameraButton->setMinimumSize(QSize(30,30));
    cameraButton->setMaximumSize(QSize(30,30));
    cameraButton->setToggleButton(TRUE);
    cameraButton->setIconSet( QIconSet(QPixmap(Icons::cameraIcon())) );
    QToolTip::add( cameraButton, tr( "Move Camera (C)" ) );
    cameraButton->move(5,5);
     connect(cameraButton, SIGNAL(toggled(bool)), this, SLOT(cameraToggled(bool)));

  // odstep co 10

    showAllButton = new QToolButton(this);            // showALL Button
    showAllButton->setMinimumSize(QSize(30,30));
    showAllButton->setMaximumSize(QSize(30,30));
    showAllButton->setIconSet( QIconSet(QPixmap(Icons::showAllSceneIcon())) );
    QToolTip::add( showAllButton, tr( "Fit scene to viewport (F)" ) );
    showAllButton->move(45,5);
     connect(showAllButton, SIGNAL(clicked()), this, SLOT(showAll()));

    showGridButton = new QToolButton(this);           // grid Button
    showGridButton->setMinimumSize(QSize(30,30));
    showGridButton->setMaximumSize(QSize(30,30));
    showGridButton->setToggleButton( TRUE );
    showGridButton->setIconSet( QIconSet(QPixmap(Icons::gridIcon())) );
    QToolTip::add( showGridButton, tr( "Show grid (G)" ) );
    showGridButton->move(75,5);
     connect(showGridButton, SIGNAL(toggled(bool)), this, SLOT(gridToggled(bool)));

    showBoxesButton = new QToolButton(this);           // grid Button
    showBoxesButton->setMinimumSize(QSize(30,30));
    showBoxesButton->setMaximumSize(QSize(30,30));
    showBoxesButton->setToggleButton( TRUE );
    showBoxesButton->setIconSet( QIconSet(QPixmap(Icons::wireIcon())) );
    QToolTip::add( showBoxesButton, tr( "Show outline boxes (B)" ) );
    showBoxesButton->move(105,5);
     connect(showBoxesButton, SIGNAL(toggled(bool)), this, SLOT(boxesToggled(bool)));
    
    showAxisButton = new QToolButton(this);           // axis Button
    showAxisButton->setMinimumSize(QSize(30,30));
    showAxisButton->setMaximumSize(QSize(30,30));
    showAxisButton->setToggleButton( TRUE );
    showAxisButton->setIconSet( QIconSet(QPixmap(Icons::axisIcon())) );
    QToolTip::add( showAxisButton, tr( "Show axis (Alt+A)" ) );
    showAxisButton->move(135,5);
     connect(showAxisButton, SIGNAL(toggled(bool)), this, SLOT(axisToggled(bool)));

    showLightsButton = new QToolButton(this);           // lights Button
    showLightsButton->setMinimumSize(QSize(30,30));
    showLightsButton->setMaximumSize(QSize(30,30));
    showLightsButton->setToggleButton( TRUE );
    showLightsButton->setIconSet( QIconSet(QPixmap( *(Icons::bulbIcon()))) );
    QToolTip::add( showLightsButton, tr( "Show lights (Alt+L)" ) );
    showLightsButton->move(165,5);
     connect(showLightsButton, SIGNAL(toggled(bool)), this, SLOT(lightsToggled(bool)));
     
     // odstep
    viewDirCombo = new QComboBox(FALSE, this);       // view direction Combo
    viewDirCombo->setMinimumSize(QSize(80,30));
    viewDirCombo->setMaximumSize(QSize(80,30));
    
    // tutaj definiujemy font dla combo - musi byæ mniejszy ¿eby zmie¶ci³a siê ikona
    QFont comboFont (viewDirCombo->font());
    comboFont.setPointSize(viewDirCombo->font().pointSize()-3); // by³o 9
    
    viewDirCombo->setFont(comboFont);
    QToolTip::add( viewDirCombo, tr( "View direction" ) );
    viewDirCombo->insertItem( tr( "Custom" ) );
    viewDirCombo->insertItem( tr( "Top" ) );
    viewDirCombo->insertItem( tr( "Side" ) );
    viewDirCombo->insertItem( tr( "Front" ) );
    viewDirCombo->move(205,5);
     connect(viewDirCombo, SIGNAL(activated(int)), this, SLOT(viewDirChanged(int)));

    viewTypeCombo = new QComboBox(FALSE, this);    // view type Combo
    viewTypeCombo->setMinimumSize(QSize(100,30));
    viewTypeCombo->setMaximumSize(QSize(100,30));
    viewTypeCombo->setFont(comboFont);
    QToolTip::add( viewTypeCombo, tr( "Draw method (Alt+W,S,T)" ) );
    viewTypeCombo->insertItem( QPixmap(Icons::wireIcon()), tr( "Wire" ) );
    viewTypeCombo->insertItem( QPixmap(Icons::solidIcon()), tr( "Solid" ) );
    viewTypeCombo->insertItem( QPixmap(Icons::texturedIcon()), tr( "Textured" ) );
    viewTypeCombo->move(285,5);
     connect(viewTypeCombo, SIGNAL(activated(int)), this, SLOT(viewTypeChanged(int)));

    viewProjCombo = new QComboBox(FALSE, this);    // view projection Combo
    viewProjCombo->setMinimumSize(QSize(100,30));
    viewProjCombo->setMaximumSize(QSize(100,30));
    viewProjCombo->setFont(comboFont);
    QToolTip::add( viewProjCombo, tr( "Projection type (O,P)" ) );
    viewProjCombo->insertItem( tr( "Orthogonal" ) );
    viewProjCombo->insertItem( tr( "Perspective" ) );
    viewProjCombo->move(385,5);
     connect(viewProjCombo, SIGNAL(activated(int)), this, SLOT(viewProjChanged(int)));

  // odstep

    screenshotButton = new QToolButton(this);       // screenshot Button
    screenshotButton->setMinimumSize(QSize(30,30));
    screenshotButton->setMaximumSize(QSize(30,30));
    screenshotButton->setIconSet( QIconSet(QPixmap(Icons::fotoIcon())) );
    QToolTip::add( screenshotButton, tr( "Save screenshot (Ctrl+S)" ) );
    screenshotButton->move(495,5);
     connect(screenshotButton, SIGNAL(clicked()), this, SLOT(screenshotClicked()));

  // odstêp

    maximizeButton = new QToolButton(this);         // maximize Button
    maximizeButton->setFixedSize(QSize(30,30));
    maximizeButton->setIconSet(QIconSet(QPixmap(Icons::scaleIcon())));
    QToolTip::add(maximizeButton, tr( "Maximize Viewport (Ctrl+M)" ));
    maximizeButton->move(535,5);
     connect(maximizeButton, SIGNAL(clicked()), this, SLOT(maximizeClicked()));

    // cellWidget moze sie rozszerzac
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}



// przelaczanie widocznosci menu
void CellWidget::toggleVisibility()
{
  if (this->isVisible()) hide(); else show();
  parentWidget()->setFocus();
}


// przelaczanie ruchu kamera
void CellWidget::cameraToggled(bool on)
{
  emit moveCamera(on);
}


// pokaz cala scene
void CellWidget::showAll()
{
  emit showEntireScene();
}

// przelaczanie siatki
void CellWidget::gridToggled(bool on)
{
  emit showGrid(on);
}

// obrysy
void CellWidget::boxesToggled( bool on )
{
  emit showBoxes( on );
}

// przelaczanie ukladu wspolrzednych
void CellWidget::axisToggled(bool on)
{
  emit showAxis(on);
}

// prze³±czanie wy¶wietlania ¶wiate³
void CellWidget::lightsToggled( bool on )
{
  emit showLights( on );
}

// ustawienie jednego z predefiniowanych widokow
void CellWidget::viewDirChanged(int direction)
{
  emit viewDirectionChanged(direction);
}


// zmiana sposobu rysowania bryl
void CellWidget::viewTypeChanged(int viewType)
{
  DrawMethod vt;
  switch (viewType)
  {
    case 0 : vt=Wire; break;
    case 1 : vt=Solid; break;
    case 2 : vt=Textured; break;
  }
  emit setViewType(vt);
}


// zmiana sposobu rzutowania
void CellWidget::viewProjChanged(int viewProj)
{
  switch (viewProj)
  {
    case 0 : emit setProjType(qglviewer::Camera::ORTHO); break;
    case 1 : emit setProjType(qglviewer::Camera::PERSPECTIVE); break;
  }

}


// zapisz zrzut ekranu
void CellWidget::screenshotClicked()
{
  emit makeScreenshot();
}


// przeka¿ dalej sygna³ maksymalizacji widoku
void CellWidget::maximizeClicked()
{
  emit maximize();
}


// metoda ukrywa przyciski, które nie mog± byæ wykorzystane przez globalny CellWidet
void CellWidget::hidePrivateButtons()
{
  screenshotButton->hide();
  maximizeButton->hide();
}

