#ifndef INPUT_WIDGET_H
#define INPUT_WIDGET_H

#include <qwidget.h>
#include <qvaluevector.h>
#include <qpainter.h>
#include <qtooltip.h>

#include <kernel.h>


class InputWidget : public QWidget
{
  Q_OBJECT
      
  public:
    InputWidget( QWidget* parent, ViKinemCtrlItem* controlItem );
    ~InputWidget() {}
    
    void setMin( double min ) { _min = min; _mid = (_min+_max)/2; }
    void setMax( double max ) { _max = max; _mid = (_min+_max)/2; };
    int  id() { return _id; }
    double value( int index );
    
  private:
    QValueVector<double> _valueVector;
    ViKinemCtrlItem *_controlItem;
    int _id;
    double _min;
    double _max;
    double _mid;
    double const _size;
    QPoint _pos;
    
  protected:
    virtual void paintEvent( QPaintEvent *e );
    virtual void mouseMoveEvent( QMouseEvent *e );
    virtual void mousePressEvent( QMouseEvent *e );
    
  signals:
    void valueChanged( int index, double value );
};



#endif
