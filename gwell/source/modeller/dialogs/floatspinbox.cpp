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


/*!
Metoda ustawia warto¶æ dla SpinBox-a.
*/
void FloatSpinBox::setFloatValue( float value )
{
  int r = (int) ( value * (float) _factor );
  setValue( r );
}


/*!
Metoda zwraca aktualn± warto¶æ dla SpinBox-a.
U¿ywanie tej metody nie jest zalecane ze wzglêdu na mo¿liw± niejednoznaczno¶æ - klasa QSpinBox
równie¿ posiada tak± metodê zwracaj±c± typ int.
Proszê u¿ywaæ floatValue().
*/
float FloatSpinBox::value()
{
  float r = text().toFloat();
  return ( r );
}


/*!
Metoda zwraca aktualn± warto¶æ dla SpinBox-a.
U¿ywanie tej metody jest zalecane zamiast metody value().
*/
float FloatSpinBox::floatValue()
{
  float r = text().toFloat();
  return ( r );
}


/*!
Metoda przekszta³ca warto¶æ wej¶ciow± typu int na tekst.
*/
QString FloatSpinBox::mapValueToText( int v )
{
  float r = (float) v / (float) _factor;
  return QString::number( r, 'f', _decimals );
}


/*!
Metoda przekszta³ca wewnêtrzn± zmienn± tekstow± na typ int.
*/
int FloatSpinBox::mapTextToValue( bool* )

{
  float r = (float)_factor * (text().toFloat());
  return ( (int) r );
}


/*!
Metoda wysy³a sygna³ o zmianie warto¶ci, przeliczaj±c wcze¶niej warto¶æ int na float.
*/
void FloatSpinBox::sendFloatValue( int v )
{
  float r = (float) v / (float) _factor;
  emit valueChanged( r );
}

