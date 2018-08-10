////////////////////////////////////////////////////////////////////////////////
///
///  class: FloatSpinBox (.h)
///
///  widget dziedzicz±cy QSpinBox, operuje na liczbach typu float
///  emituje sygna³ valueChanged( float );
///
////////////////////////////////////////////////////////////////////////////////
#ifndef FLOAT_SPIN_BOX_H
#define FLOAT_SPIN_BOX_H

#include <qspinbox.h>
#include <qvalidator.h>



class FloatSpinBox : public QSpinBox
{
  Q_OBJECT
      
  public:
    FloatSpinBox( float minValue, float maxValue, float step, int decimals=3, QWidget *parent=0 );
    ~FloatSpinBox();
    float value();
    float floatValue(); // zwraca to samo co value();
    
  public slots:
    void setFloatValue( float value );
    void setDecimals( int decimals ) { if (decimals>0) _decimals=decimals; }
    
  private:
    int _decimals;
    int _factor;
    
  protected:
    QString mapValueToText( int );
    int mapTextToValue( bool* );
    
  private slots:
    void sendFloatValue( int );
  
  signals:
    void valueChanged( float );
};


#endif
