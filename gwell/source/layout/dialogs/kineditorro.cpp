#include "kineditorro.h"


KinematicsEditorRO::KinematicsEditorRO(QPtrList<ViMultiPolyh> *selectedList, QWidget *parent, const char *name, bool modal, WFlags fl) : QDialog(parent,name,modal,fl)
{
  _selectedList = selectedList;
  _multiPolyh = _selectedList->last();
  
  
  this->setCaption(tr("Kinematics"));
  
  QFont f;
  f.setPointSize( this->font().pointSize() - 2);
  
  // g³ówna ramka
  mainFrame = new QFrame( this );
  mainFrame->setFrameStyle( QFrame::Sunken | QFrame::Box );
  
  // g³ówny grid zawieraj±cy tylko ramkê
  mainGrid = new QGridLayout( this, 1,1, 5,5 );
  mainGrid->addWidget( mainFrame, 0,0 );
  
  frameGrid = new QGridLayout( mainFrame, 6,5, 10,5 ); // 6rows, 5cols
  
  // etykieta z nazw± elementu
  obLabel = new QLabel( tr("Object: "), mainFrame );
  obLabel->setAlignment( Qt::AlignRight );
  frameGrid->addWidget( obLabel, 0,0 );
  // pole wy¶wietlaj±ce ¶cie¿kê do elementu
  obEdit = new QLineEdit( mainFrame );
  QString s( _multiPolyh->GetNodeAddress().c_str() );
  obEdit->setText( s );
  obEdit->setReadOnly( true );
  frameGrid->addMultiCellWidget( obEdit, 0,0, 1,4 );
  

  // tabela
  table = new Table( _multiPolyh , mainFrame );
  frameGrid->addMultiCellWidget( table, 1,4, 0,3 );
  
  // pokrêt³o
  knob = new Knob( mainFrame );
  knob->setMinimumSize( QSize(100,100) );
  frameGrid->addMultiCellWidget( knob, 1,2, 4,4 );
  
  //addWidget( _, 3,4 );
  //addWidget( _, 4,4 );
  
  // przycisk OK
  okButton = new QPushButton( tr("OK"), mainFrame );
  frameGrid->addWidget( okButton, 5, 2 );
  
  
  connect( knob, SIGNAL( valueChanged(double) ), table, SLOT( setCurrentValue(double) ) );
  connect( knob, SIGNAL( valueChanged(double) ), this, SLOT( updateView(double) ) );
  connect( table, SIGNAL( MinMaxValueChanged(ViKinemCtrlItem*) ), knob, SLOT( setRangeFromItem(ViKinemCtrlItem*) ) );
  connect( table, SIGNAL( valueChangedIsOK() ), this, SLOT( updateView() ) );
  connect( okButton, SIGNAL( clicked() ), this, SLOT( close() ) );
  
  for ( ViKinemCtrlSet::ConCtrlIter iter = _multiPolyh->GetCtrlInterface().ConBegin_Ctrl(); iter; ++iter )
  {
    ViKinemCtrlItem *ci = (ViKinemCtrlItem*) & (*iter);
    table->addRow( ci );
  }
  // init
  
  this->resize( 900, 320 );
  this->show();
}



/*!
Metoda jest slotem uaktualniaj±cym widoki CellFrame po zmianie warto¶ci parametru.
*/
void KinematicsEditorRO::updateView()
{
  _multiPolyh->ComputeHierAllGlbVtx();
  CellFrame::refresh();
}

/*!
Slot nadmiarowy, specjalnie dla knoba. Dzia³a tak samo jak updateView().
*/
void KinematicsEditorRO::updateView(double)
{
  _multiPolyh->ComputeHierAllGlbVtx();
  CellFrame::refresh();
}


/*!
Metoda przechwytuje klawisze (obecnie nie reaguje na ¿adne).
*/
void KinematicsEditorRO::keyPressEvent( QKeyEvent* e)
{
  e->ignore();
}
