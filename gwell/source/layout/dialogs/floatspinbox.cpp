////////////////////////////////////////////////////////////////////////////////
///
///  class: FloatSpinBox (.cpp)
///
///  widget dziedzicz±cy QSpinBox, operuje na liczbach typu float
///  emituje sygna³ valueChanged( float );
///
////////////////////////////////////////////////////////////////////////////////
#include "floatspinbox.h"


// konstruktor
FloatSpinBox::FloatSpinBox( float minValue, float maxValue, float step, int decimals, QWidget *parent )
 : QSpinBox( parent )
{
  _decimals = decimals;
  
  _factor = 1;
  for (int i=0; i<_decimals; i++) _factor*=10;
  
  this->setMinValue( (int) (minValue * _factor) );
  this->setMaxValue( (int) (maxValue * _factor) );
  this->setLineStep( (int) (step * _factor) );
  
  // Validator double, ale te¿ siê nadaje
  QDoubleValidator *doubleValidator = new QDoubleValidator( minValue, maxValue, _decimals, this );
  this->setValidator( doubleValidator );
  
  connect( this, SIGNAL(valueChanged(int)), this, SLOT(sendFloatValue(int)) );
}


// destruktor
FloatSpinBox::~FloatSpinBox() {}



void FloatSpinBox::setFloatValue( float value )
{
  int r = (int) ( value * (float) _factor );
  setValue( r );
}


float FloatSpinBox::value()
{
  float r = text().toFloat();
  return ( r );
}


// to samo co value()
float FloatSpinBox::floatValue()
{
  float r = text().toFloat();
  return ( r );
}



QString FloatSpinBox::mapValueToText( int v )
{
  float r = (float) v / (float) _factor;
  return QString::number( r, 'f', _decimals );
}



int FloatSpinBox::mapTextToValue( bool* )
{
  float r = (float)_factor * (text().toFloat());
  return ( (int) r );
}



void FloatSpinBox::sendFloatValue( int v )
{
  float r = (float) v / (float) _factor;
  emit valueChanged( r );
}

