#include "knob.h"




Knob::Knob( QWidget *parent, const char* name ) : QwtKnob( parent, name )
{
  
}




void Knob::setRangeFromItem( ViKinemCtrlItem *controlItem )
{
  double min = controlItem->GetMin();
  double max = controlItem->GetMax();
  double val = controlItem->GetVal();
  
  this->setRange( min, max, (max-min)/100 );
  this->setValue( val );
}


