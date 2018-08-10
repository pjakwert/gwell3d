#include "table.h"

#define ID 0
#define TRANSFORMATION 1
#define COORD 2
#define MIN 3
#define MAX 4
#define COMMENT 5
#define VALUE 6
#define NAME 7

#define MIN_INF "INF"
#define MAX_INF "INF"


Table::Table( ViMultiPolyh *multiPolyh, QWidget *parent, const char *name ) : QTable( parent, name )
{
  _multiPolyh = multiPolyh;
  
  this->setNumCols( 8 ); // ilo¶æ kolumn - ostatnia kolumna zawiera ¶cie¿kê do bry³y
  
  this->setSelectionMode( QTable::SingleRow ); // zaznaczamy pojedynczy wiersz
  this->setLeftMargin( 0 ); // brak lewego bar-a
  
  this->setColumnReadOnly( ID, true ); // kolumna z numerem KeyID jest tylko do odczytu
  this->setColumnReadOnly( NAME, true ); // kolumna z nazw± bry³y - tylko do odczytu
  
  QHeader *head = this->horizontalHeader();
  head->setLabel( ID            , tr("ID") );
  head->setLabel( TRANSFORMATION, tr("Transformation") );
  head->setLabel( COORD         , tr("Coord") );
  head->setLabel( MIN           , tr("Min") );
  head->setLabel( MAX           , tr("Max") );
  head->setLabel( COMMENT       , tr("Comment") );
  head->setLabel( VALUE         , tr("value") );
  head->setLabel( NAME          , tr("Name") );
  
  transfList << "Translate" << "Rotate" << "Scale"; // dla combo
  coordList << "X" << "Y" << "Z";                   // dla combo
  
  connect( this, SIGNAL( valueChanged(int,int) ), this, SLOT( validateAndSet(int,int) ) );
  
  connect( this, SIGNAL( currentChanged(int,int) ), this, SLOT( rowAndColChanged(int,int) ) );
}


/*!
Metoda "t³umaczy" typ transformacji na jego index w comboBox.
*/
int Table::transfTypeToIndex( Vi::TransformType tt )
{
  switch ( tt )
  {
    case ( Vi::TT_Trans )   : return 0;
    case ( Vi::TT_Rot_XYZ ) : return 1;
    case ( Vi::TT_Scale )   : return 2;
    default : return 1;
  }
}


/*!
Metoda zwraca typ transformacji na podstawie indeksu w comboBox.
*/
Vi::TransformType Table::indexToTransfType( int i )
{
  switch ( i )
  {
    case 0 : return Vi::TT_Trans;
    case 1 : return Vi::TT_Rot_XYZ;
    case 2 : return Vi::TT_Scale;
    default : return Vi::TT_Rot_XYZ;
  }
}



/*!
Metoda zwraca typ wspó³rzêdnej w zale¿no¶ci od indeksu w combo.
*/
Vi::Coord3DType Table::indexToCoordType( int i )
{
  switch ( i )
  {
    case 0 : return Vi::CT_1;
    case 1 : return Vi::CT_2;
    case 2 : return Vi::CT_3;
  }
}



/*!
Metoda dodaje nowy wiersz do kolumny w oparciu o warto¶ci elementu ViKinemCtrlItem* controlItem.
Po dodaniu zaznacza nowo dodany element i wysy³a odpowiedni sygna³.
*/
void Table::addRow( ViKinemCtrlItem* controlItem )
{
  this->insertRows( this->numRows(), 1 ); // dodaje pojedynczy wiersz na koñcu tabeli
  //this->insertRow( this->currentRow()+1, 1 ); // wstawia nowy wiersz za aktualnym
  
  int currRow = numRows()-1; // dodany element jest ostatni na li¶cie
  this->setRowHeight( currRow, rowHeight( currRow ) * 1.5 );
  QComboTableItem *trCombo = new QComboTableItem( this, transfList );
  QComboTableItem *coordCombo = new QComboTableItem( this, coordList );
  
  this->setText( currRow, ID, QString::number( controlItem->GetKeyID() ) ); // KeyID elementu
  this->setItem( currRow, TRANSFORMATION, trCombo ); // combo z typem transformacji
   trCombo->setCurrentItem( transfTypeToIndex( controlItem->GetTransfType() ) );
  this->setItem( currRow, COORD, coordCombo ); // wspó³rzêdna transformacji
   coordCombo->setCurrentItem( controlItem->GetCoordType() );
  
  if ( controlItem->IsMinUnlimited() ) // je¿eli nie ma ograniczenia dolnego
   this->setText( currRow, MIN, MIN_INF );
  else
   this->setText( currRow, MIN, QString::number( controlItem->GetMin(), 'f', Options::decimals() ) ); // min
  
  if ( controlItem->IsMaxUnlimited() ) // je¿eli nie ma ograniczenia górnego
   this->setText( currRow, MAX, MAX_INF );
  else
   this->setText( currRow, MAX, QString::number( controlItem->GetMax(), 'f', Options::decimals() ) ); // max
  
  this->setText( currRow, COMMENT, QString( controlItem->GetCommentName().c_str() ) ); // komentarz
  this->setText( currRow, VALUE, QString::number(controlItem->GetVal(), 'f', Options::decimals()) );// value
  
  this->setText( currRow, NAME, QString( controlItem->UsePolyh()->GetNodeAddress().c_str() ) );
  
  setCurrentCell( currRow, currentColumn() );
  emit MinMaxValueChanged( controlItem );
}



/*!
Metoda usuwa aktualnie zaznaczony element sterowania.
*/
void Table::removeCurrentRow()
{
  if ( this->numRows() == 0 ) return; // nie ma nic do usuniêcia
  
  bool ok;
  int KeyID = text( this->currentRow(), ID ).toInt( &ok );
  
  if ( !ok ) return; // ta sytuacja nigdy nie powinna siê zda¿yæ, ale ... nie takie rzeczy widziano
  
  _multiPolyh->UseCtrlInterface().DeleteByKeyID( KeyID ); // usuñ element sterowania
  this->removeRow( this->currentRow() ); // usuñ wiersz QTable
}


/*!
Metoda przelicza wierzcho³ki dla danej transformacji.
*/
void Table::updateItem( ViKinemCtrlItem *controlItem )
{
  controlItem->UpdateMtx();
  controlItem->ComputeAllPolyhGlbVtx();
}


/*!
Metoda obs³uguje sygna³ valueChanged(int,int). W zale¿no¶ci od zadanej warto¶ci i kolumny, w której
wpisana jest warto¶æ - ustawia j± b±d¼ odrzuca. Nie przejmujemy siê tutaj: numerem ID, typem transformacji (ReadOnly combo), typem wspó³rzêdnej oraz komentarzem. Pozosta³e warto¶ci trzeba sprawdziæ w obliczu potencjalnego zagro¿enia ze strony u¿ytkownika (Al-Kaida User). Zostaj± wiêc trzy: MIN, MAX i VALUE.
*/
bool Table::validateAndSet( int row, int col )
{
  QString _text = text( row, col );
  
  int keyID = text( row, ID ).toInt(); // zczytujemy KeyID z kolumny ID
  ViKinemCtrlItem* controlItem = _multiPolyh->UseCtrlInterface().FindByKeyID( keyID ); // szukamy elementu o takim ID
  
  if ( !controlItem ) // taki element nie istnieje - nie powinno siê zda¿yæ! a jednak...
  {
    StatusBar::printStatusMsg( tr("validateAndSet: bad KeyID = %1").arg(keyID), tr("Kinematics Editor") );
    return false;
  }
  
  switch ( col ) // w zale¿no¶ci od tego, w której kolumnie nast±pi³a modyfikacja...
  {
    case ( TRANSFORMATION ) : {
                                QComboTableItem *trCombo = dynamic_cast<QComboTableItem*>( item(row,col) );
                                controlItem->SetTransfType( indexToTransfType( trCombo->currentItem() ) );
                                updateItem( controlItem );
                                emit valueChangedIsOK();
                                return true;
                              }
    case ( COORD ) : {
                        QComboTableItem *coordCombo = dynamic_cast<QComboTableItem*>( item(row,col) );
                        controlItem->SetCoordType( indexToCoordType( coordCombo->currentItem() ) );
                        updateItem( controlItem );
                        emit valueChangedIsOK();
                        return true;
                     }
    case ( MIN ) : {
                      // je¿eli user nic nie wpisa³ - ustaw INF
                      if ( _text.isEmpty() )
                      {
                        controlItem->SetMin_Unlimited();
                        setText( row, col, MIN_INF ); // odpowiedni tekst
                        emit valueChangedIsOK();
                        emit MinMaxValueChanged( controlItem ); // do knoba
                        return true;
                      }
                      
                      // je¿eli user sam wpisa³ MIN_INF to OK
                      if ( strcmp( _text.ascii(), MIN_INF ) == 0 )
                      {
                        controlItem->SetMin_Unlimited();
                        emit valueChangedIsOK();
                        emit MinMaxValueChanged( controlItem ); // do knoba
                        return true;
                      }
      
                      // podstawowy test - MIN musi byæ liczb±
                      bool ok;
                      double v = _text.toDouble( &ok );
                      if ( !ok ) // nie jest liczb± - ustawiamy star± warto¶æ
                      {
                        if ( controlItem->IsMinUnlimited() )
                         setText( row,col, MIN_INF );
                        else
                         setText( row,col, QString::number(controlItem->GetMin(),'f',Options::decimals()) );
                        return false;
                      }
                      else // wpisano poprawn± warto¶æ
                      {
                        // min nie mo¿e byæ wiêksze ni¿ max
                        if ( v > controlItem->GetMax() )
                        {
                          if ( controlItem->IsMinUnlimited() )
                           setText( row,col, MIN_INF );
                          else
                           setText(row,col, QString::number(controlItem->GetMin(),'f',Options::decimals()));
                          return false;
                        }
                        
                        // je¿eli min jest wiêksze ni¿ value - zwiêksz value do warto¶ci min
                        if ( v > controlItem->GetVal() )
                        {
                          setText( row, VALUE, QString::number( v, 'f', Options::decimals() ) );
                          controlItem->SetVal( v );
                        }
                        
                        controlItem->SetMin( v );
                        
                        emit valueChangedIsOK();
                        emit MinMaxValueChanged( controlItem ); // sygna³ do knoba
                        return true;
                      }
                   }
    case ( MAX ) : {
                      // je¿eli user nic nie wpisa³ - ustaw INF
                      if ( _text.isEmpty() )
                      {
                        controlItem->SetMax_Unlimited();
                        setText( row, col, MAX_INF ); // odpowiedni tekst
                        emit valueChangedIsOK();
                        emit MinMaxValueChanged( controlItem ); // do knoba
                        return true;
                      }
                      
                      // je¿eli user sam wpisa³ MAX_INF to OK
                      if ( strcmp( _text.ascii(), MAX_INF ) == 0 )
                      {
                        controlItem->SetMax_Unlimited();
                        emit valueChangedIsOK();
                        emit MinMaxValueChanged( controlItem ); // do knoba
                        return true;
                      }
      
                      // podstawowy test - MAX musi byæ liczb±
                      bool ok;
                      double v = _text.toDouble( &ok );
                      if ( !ok ) // nie jest liczb± - ustawiamy star± warto¶æ
                      {
                        if ( controlItem->IsMaxUnlimited() )
                         setText( row,col, MAX_INF );
                        else
                         setText( row,col, QString::number(controlItem->GetMax(),'f',Options::decimals()) );
                        return false;
                      }
                      else // wpisano poprawn± warto¶æ
                      {
                        // max nie mo¿e byæ mniejsze ni¿ min
                        if ( v < controlItem->GetMin() )
                        {
                          if ( controlItem->IsMaxUnlimited() )
                           setText( row,col, MAX_INF );
                          else
                           setText(row,col, QString::number(controlItem->GetMax(),'f',Options::decimals()));
                          return false;
                        }
                        
                        // je¿eli max jest mniejsze ni¿ value - zmniejsz value do warto¶ci max
                        if ( v < controlItem->GetVal() )
                        {
                          setText( row, VALUE, QString::number( v, 'f', Options::decimals() ) );
                          controlItem->SetVal( v );
                        }
                        
                        controlItem->SetMax( v );
                        
                        emit valueChangedIsOK();
                        emit MinMaxValueChanged( controlItem ); // sygna³ do knoba
                        return true;
                      }
                  }
    case ( COMMENT ) : {
                        controlItem->SetCommentName( _text.ascii() );
                        //emit valueChangedIsOK();
                        return true;
                       }
    case ( VALUE ) : {
                      // je¿eli user nic nie wpisa³ - pozostaw star± warto¶æ
                      if ( _text.isEmpty() )
                      {
                        setText(row,col, QString::number( controlItem->GetVal(), 'f', Options::decimals()));
                        return false;
                      }
      
                      // podstawowy test - VALUE musi byæ liczb±
                      bool ok;
                      double v = _text.toDouble( &ok );
                      if ( !ok ) // nie jest liczb± - ustawiamy star± warto¶æ
                      {
                        setText( row,col, QString::number(controlItem->GetVal(),'f',Options::decimals()) );
                        return false;
                      }
                      else // wpisano poprawn± warto¶æ
                      {
                        // sprawdzamy czy nowa warto¶æ mie¶ci siê w przedziale (MIN,MAX)
                        switch ( controlItem->SetVal( v ) )
                        {
                          case 0  : /* OK */ break;
                          case -1 : /* v < MIN - ustawiamy value na MIN */
                                    { 
                                      controlItem->SetVal( controlItem->GetMin() );
                                      setText( row,col, QString::number(controlItem->GetVal(), 'f', Options::decimals()) );
                                      break;
                                    }
                          case 1  : /* v > MAX - ustawiamy value na MAX */
                                    { 
                                      controlItem->SetVal( controlItem->GetMax() );
                                      setText( row,col, QString::number(controlItem->GetVal(), 'f', Options::decimals()) );
                                      break;
                                    }
                        }
                      }
      
                      emit MinMaxValueChanged( controlItem );
                      emit valueChangedIsOK();
                      return true;
                     }
  }
  
  return true;
}



/*!
Metoda wysy³a informacjê do knoba, je¿eli zmieni siê aktualny wiersz, ¿eby knob ustawi³
sobie odpowiednie warto¶ci.
*/
void Table::rowAndColChanged( int,int )
{
  int keyID = text( currentRow(), ID ).toInt(); // zczytaj KeyID z kolumny ID
  ViKinemCtrlItem *controlItem = _multiPolyh->UseCtrlInterface().FindByKeyID( keyID ); // znajd¼ element
  
  if ( controlItem ) emit MinMaxValueChanged( controlItem );
}


/*!
Metoda ustawia warto¶æ value z zewn±trz zaznaczonemu elementowi ViKinemCtrlItem.
Wysy³a sygna³ tylko wtedy, gdy podana warto¶æ jest poza przedzia³em i trzeba j± modyfikowaæ.
*/
void Table::setCurrentValue( double value )
{
  if ( numRows() == 0 ) return; // nie ma co ustawiaæ
  
  int keyID = text( currentRow(), ID ).toInt(); // zczytaj KeyID z kolumny ID
  ViKinemCtrlItem *controlItem = _multiPolyh->UseCtrlInterface().FindByKeyID( keyID ); // znajd¼ element
  
  if ( !controlItem ) // nie powinno zaj¶æ
  {
    StatusBar::printStatusMsg( tr("setCurrentValue: bad KeyID = %1").arg(keyID), tr("Kinematics Editor") );
    return;
  }
  
  switch( controlItem->SetVal( value ) )
  {
    case 0  : break; // OK
    case -1 : /* v < MIN */ controlItem->SetVal( controlItem->GetMin() );  // ogranicz VALUE
              emit MinMaxValueChanged( controlItem );
              break;
    case 1  : /* v > MAX */ controlItem->SetVal( controlItem->GetMax() );  // ogranicz VALUE
              emit MinMaxValueChanged( controlItem );
              break;
  }
  
  this->setText( currentRow(), VALUE, QString::number( controlItem->GetVal(), 'f', Options::decimals()) );
}



/*!
Metoda obs³ugi zdarzenia zmiany rozmiaru. Zachowuje odpowiednie szeroko¶ci kolumn.
*/
void Table::resizeEvent( QResizeEvent *e )
{
  int w = e->size().width()-40 -3;
  
  setColumnWidth( ID, 40 );
  setColumnWidth( TRANSFORMATION, (int) (0.25 * w) );
  setColumnWidth( COORD, (int) (0.12 * w) );
  setColumnWidth( MIN, (int) (0.10 * w) );
  setColumnWidth( MAX, (int) (0.10 * w) );
  setColumnWidth( COMMENT, (int) (0.33 * w) );
  setColumnWidth( VALUE, (int) (0.10 * w) );
  
  if ( !isColumnHidden( NAME ) ) // trzeba pokazaæ jeszcze kolumnê ze ¶cie¿kami elementów
  {
    setColumnWidth( TRANSFORMATION, (int) (0.15 * w) );
    setColumnWidth( COORD, (int) (0.10 * w) );
    setColumnWidth( MIN, (int) (0.08 * w) );
    setColumnWidth( MAX, (int) (0.08 * w) );
    setColumnWidth( COMMENT, (int) ( 0.15 * w ) );
    setColumnWidth( VALUE, (int) ( 0.08 * w ) );
    setColumnWidth( NAME, (int) ( 0.36 * w ) );
  }
}

