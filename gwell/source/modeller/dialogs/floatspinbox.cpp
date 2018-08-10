////////////////////////////////////////////////////////////////////////////////
///
///  class: FloatSpinBox (.cpp)
///
///  widget dziedzicz�cy QSpinBox, operuje na liczbach typu float
///  emituje sygna� valueChanged( float );
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
  
  // Validator double, ale te� si� nadaje
  QDoubleValidator *doubleValidator = new QDoubleValidator( minValue, maxValue, _decimals, this );
  this->setValidator( doubleValidator );
  
  connect( this, SIGNAL(valueChanged(int)), this, SLOT(sendFloatValue(int)) );
}


// destruktor
FloatSpinBox::~FloatSpinBox() {}


/*!
Metoda ustawia warto�� dla SpinBox-a.
*/
void FloatSpinBox::setFloatValue( float value )
{
  int r = (int) ( value * (float) _factor );
  setValue( r );
}


/*!
Metoda zwraca aktualn� warto�� dla SpinBox-a.
U�ywanie tej metody nie jest zalecane ze wzgl�du na mo�liw� niejednoznaczno�� - klasa QSpinBox
r�wnie� posiada tak� metod� zwracaj�c� typ int.
Prosz� u�ywa� floatValue().
*/
float FloatSpinBox::value()
{
  float r = text().toFloat();
  return ( r );
}


/*!
Metoda zwraca aktualn� warto�� dla SpinBox-a.
U�ywanie tej metody jest zalecane zamiast metody value().
*/
float FloatSpinBox::floatValue()
{
  float r = text().toFloat();
  return ( r );
}


/*!
Metoda przekszta�ca warto�� wej�ciow� typu int na tekst.
*/
QString FloatSpinBox::mapValueToText( int v )
{
  float r = (float) v / (float) _factor;
  return QString::number( r, 'f', _decimals );
}


/*!
Metoda przekszta�ca wewn�trzn� zmienn� tekstow� na typ int.
*/
int FloatSpinBox::mapTextToValue( bool* )

{
  float r = (float)_factor * (text().toFloat());
  return ( (int) r );
}


/*!
Metoda wysy�a sygna� o zmianie warto�ci, przeliczaj�c wcze�niej warto�� int na float.
*/
void FloatSpinBox::sendFloatValue( int v )
{
  float r = (float) v / (float) _factor;
  emit valueChanged( r );
}

