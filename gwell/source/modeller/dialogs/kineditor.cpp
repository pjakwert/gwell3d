#include "kineditor.h"

#define NAME 7

KinematicsEditor::KinematicsEditor(QPtrList<ViNTreeNode> *selectedList, QWidget *parent, const char *name, bool modal, WFlags fl) : QDialog(parent,name,modal,fl)
{
  _selectedList = selectedList;
  ViNTreeNode *_selected = _selectedList->last();
  
  if ( _selectedList->isEmpty() )
  {
    _multiPolyh = CellFrame::multiPolyh();
  }
  else
  // w zale¿no¶ci od tego czy jest zaznaczony element - u¿yj odpowiedniego interfejsu
  if ( _selected->GetInheritorType() == IT_MULTIPOLYH )
  {
    _multiPolyh = ((ViMultiPolyh*) _selected);
  }
  else
  {
    _multiPolyh = (ViMultiPolyh*) & *(_selected->GetAncestor_MultiPolyh()) ;
    if ( !_multiPolyh ) _multiPolyh = ((ViMultiPolyh*) (_selected->GetTreeRoot()));
    printf(" _multiPolyh ancestor name: %s\n", _multiPolyh->NodeName() );
    if ( _multiPolyh->IsCtrlInterface() ) printf( "_multiPolyh ma ctrl\n" ); 
     else printf( "_multiPolyh NIE MA ctrl\n" );
  }
  
  
  this->setCaption(tr("Kinematics Editor"));
  
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
  QString s;
    if ( !_selectedList->isEmpty() ) // jest zaznaczony element na li¶cie
    {
      s = QString( _selectedList->last()->GetNodeAddress().c_str() );
    }
    else // nie ma elementu - pokaz wszystkie
    {
      s = QString( _multiPolyh->GetNodeAddress().c_str() );
    }
  obEdit->setText( s );
  obEdit->setReadOnly( true );
  frameGrid->addMultiCellWidget( obEdit, 0,0, 1,4 );
  

  // tabela
  table = new Table( _multiPolyh , mainFrame );
  if ( !_selectedList->isEmpty() ) table->hideColumn( NAME ); // nazwy obiektów pokazuj tylko w trybie FULL
  frameGrid->addMultiCellWidget( table, 1,4, 0,3 );
  
  // pokrêt³o
  knob = new Knob( mainFrame );
  knob->setMinimumSize( QSize(100,100) );
  frameGrid->addMultiCellWidget( knob, 1,2, 4,4 );
  
  // przycisk dodania nowego elementu
  addButton = new QToolButton( mainFrame );
  addButton->setTextLabel( tr("add") );
  addButton->setPixmap( *(Icons::addIcon()) );
  addButton->setUsesTextLabel( true );
  frameGrid->addWidget( addButton, 3,4 );
  if ( _selectedList->isEmpty() ) addButton->setEnabled( false );
  
  // przycisk usuniêcia elementu
  removeButton = new QToolButton( mainFrame );
  removeButton->setTextLabel( tr("remove") );
  removeButton->setPixmap( *(Icons::deleteIcon()) );
  removeButton->setUsesTextLabel( true );
  frameGrid->addWidget( removeButton, 4,4 );
  
  // przycisk OK
  okButton = new QPushButton( tr("OK"), mainFrame );
  frameGrid->addWidget( okButton, 5, 2 );
  
  
  connect( addButton, SIGNAL( clicked() ), this, SLOT( addCtrlItem() ) );
  connect( removeButton, SIGNAL( clicked() ), table, SLOT( removeCurrentRow() ) );
  connect( knob, SIGNAL( valueChanged(double) ), table, SLOT( setCurrentValue(double) ) );
  connect( knob, SIGNAL( valueChanged(double) ), this, SLOT( updateView(double) ) );
  connect( table, SIGNAL( MinMaxValueChanged(ViKinemCtrlItem*) ), knob, SLOT( setRangeFromItem(ViKinemCtrlItem*) ) );
  connect( table, SIGNAL( valueChangedIsOK() ), this, SLOT( updateView() ) );
  connect( okButton, SIGNAL( clicked() ), this, SLOT( close() ) );
  
  // init - przeszukaj ca³± listê ViKinemCtrlSet pod k±tem tego elementu
  if ( !_selectedList->isEmpty() )
  {
    for ( ViKinemCtrlSet::ConCtrlIter iter = _multiPolyh->GetCtrlInterface().ConBegin_Ctrl(); iter; ++iter )
    {
      if ( iter->GetPolyh() == _selected )
      {
        ViKinemCtrlItem *ci = (ViKinemCtrlItem*) & (*iter);
        table->addRow( ci );
      }
    }
  }
  else // zaznaczony ca³y mp - iterujemy wszystko
  {
    for ( ViKinemCtrlSet::ConCtrlIter iter = _multiPolyh->GetCtrlInterface().ConBegin_Ctrl(); iter; ++iter )
    {
      ViKinemCtrlItem *ci = (ViKinemCtrlItem*) & (*iter);
      table->addRow( ci );
    }
  }
  // init
  
  int w;
  if ( _selectedList->isEmpty() ) w=900; else w=900; // gdy s± pokazywane nazwy - widget jest d³u¿szy
  
  this->resize( w, 320 );
  this->show();
}




/*!
Metoda dodaje nowy element kinematyki.
*/
void KinematicsEditor::addCtrlItem()
{
  ViKinemCtrlItem *ci;
  
  ci = _multiPolyh->UseCtrlInterface().Add( _selectedList->last(), 
                         _selectedList->last()->UseMtx2ParentCoord(),
                         Vi::TT_Rot_XYZ,
                         Vi::CT_1,
                         TO_After,
                         Vi::MU_Deg);
  
  // okre¶lamy klucz na podstawie ID istniej±cych elementów
  int key;
  if ( !_multiPolyh->IsCtrlInterface() ) key=1; else key = _multiPolyh->UseCtrlInterface().GetMaxKeyID() + 1;
  
  ci->SetKeyID( key );
  ci->SetMin( 0 );
  ci->SetMax( 90 );
  ci->SetKeyName( (QString::number( key )).ascii() );
  ci->SetCommentName( tr("New control item") );
  
  table->addRow( ci );
}



/*!
Metoda jest slotem uaktualniaj±cym widoki CellFrame po zmianie warto¶ci parametru.
*/
void KinematicsEditor::updateView()
{
  _multiPolyh->ComputeHierAllGlbVtx();
  CellFrame::refresh();
}

/*!
Slot nadmiarowy, specjalnie dla knoba. Dzia³a tak samo jak updateView().
*/
void KinematicsEditor::updateView(double)
{
  _multiPolyh->ComputeHierAllGlbVtx();
  CellFrame::refresh();
}


/*!
Metoda przechwytuje klawisze (obecnie nie reaguje na ¿adne).
*/
void KinematicsEditor::keyPressEvent( QKeyEvent* e)
{
  e->ignore();
}
