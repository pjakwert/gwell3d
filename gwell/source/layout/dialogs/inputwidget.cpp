#include "inputwidget.h"

#define abs(a) (a>0) ? (a) : (-1*a)



InputWidget::InputWidget( QWidget* parent, ViKinemCtrlItem* controlItem ) : QWidget( parent ), _valueVector(1000), _size(1000)
{
  _controlItem = controlItem;
  
  setMin( _controlItem->GetMin() );
  setMax( _controlItem->GetMax() );
  _id = _controlItem->GetKeyID();
  
  double v = _controlItem->GetVal();
  for ( int i=0; i<_size; i++ )
  {
    _valueVector[i] = v;
  }
  
  QToolTip::add( this, QString( _controlItem->GetCommentName().c_str() ) );
}



/*!
Metoda zwraca warto¶æ wektora symulacji znajduj±c± siê na pozycji "index".
*/
double InputWidget::value( int index )
{
  if ( (index < _size) && (index >=0 ) ) return _valueVector[index];  
}



void InputWidget::paintEvent( QPaintEvent *e )
{
  QPainter paint( this );
  
  int l = 5;
  int w = this->width();
  int h = this->height();
  
  int top,bottom;
  
  paint.save();
  
  if ( _min < 0 )
  {
    paint.setWindow( 0, -_max, _size, abs(_max-_min) ); 
    top = -_max;
    bottom = -_min;
  }
  else
  {
    paint.setWindow( 0, _min, _size, abs(_max-_min) );
    top = _min;
    bottom = _max;
  }
  
  paint.setViewport( l, l, w-2*l, h-2*l );
  
  QFont f( paint.font() );
  f.setPointSize( f.pointSize() - 3);
  paint.setFont( f );
  
  // rysujemy dane
  paint.setPen( Qt::blue );
  for ( int i=0; i<_size; i++ )
  {
    double v;
    if ( _min < 0 )
    {
      v = -_valueVector[i];
      paint.drawLine( i, 0, i, (int) v );
    }
    else
    {
      v = _max - _valueVector[i];
      paint.drawLine( i, _max, i, (int) v );
    } 
  }
  
  // siatka
  paint.setPen( Qt::DotLine );
  // poziome  
  int k = (int) (abs(_max-_min))/6;
  for ( int i=0; i<7; i++ )
  {
    paint.drawLine( 0, top+(i*k), _size, top+(i*k) ); // top = _min
  }
  // pionowe
  k = (int) _size/10;
  for ( int i=0; i<11; i++ )
  {
      paint.drawLine( i*k, top, i*k, bottom ); // top = _min, bottom = _max
  }
  
  QPoint p = paint.xFormDev( _pos );
  
  paint.restore();
  
  paint.fillRect( l, l, 60,20, QBrush( QColor(235,17,49) ) );
   paint.drawText( 2*l, 2*l+f.pointSize(), QString::number( _max, 'f', 2 ) );
  paint.fillRect( l, h-20-l, 60,20, QBrush( QColor(235,17,49) ) );
   paint.drawText( 2*l, h-2*l, QString::number( _min, 'f', 2 ) );
}



void InputWidget::mouseMoveEvent( QMouseEvent *e )
{
  if ( (e->x() > 5) && ( e->x() < this->width()-5 ) && ( e->y() < this->height()-5 ) && (e->y() > 5) )
  {
    QPainter paint( this );
    int top,bottom;
    int l = 5;
    int w = this->width();
    int h = this->height();
    
    if ( _min < 0 )
    {
      paint.setWindow( 0, -_max, _size, abs(_max-_min) ); 
      top = -_max;
      bottom = -_min;
    }
    else
    {
      paint.setWindow( 0, _min, _size, abs(_max-_min) );
      top = _min;
      bottom = _max;
    }
    paint.setViewport( l, l, w-2*l, h-2*l );
  
    
    QPoint pos_tr = paint.xFormDev( _pos ); // poprzednia pozycja w uk³adzie danych
    
    QPoint p = paint.xFormDev( QPoint( e->x(), e->y() ) ); // punkt w uk³adzie danych: -y
    
    if ( e->state() & Qt::ShiftButton ) // naci¶niêty SHIFT - ruch poziomy
    {
      p.setY( pos_tr.y() );
    }
    
    int x = p.x();
    int y = p.y();
    
    QPoint diff = p - pos_tr; // aktualna_pozycja - poprzednia
    
    int d = diff.x(); // ilo¶æ zawartych punktów
    int value;    
    
    if ( _min < 0 )
    {
      value = -y;
      if ( d > 0 )
        for ( int i=pos_tr.x(); i<=p.x(); i++ ) _valueVector[i] = value;
      else
        for ( int i=pos_tr.x(); i>=p.x(); i-- ) _valueVector[i] = value;
    }
    else
    {
      value = _max - y;
      if ( d > 0 )
        for ( int i=pos_tr.x(); i<=p.x(); i++ ) _valueVector[i] = value;
      else
        for ( int i=pos_tr.x(); i>=p.x(); i-- ) _valueVector[i] = value;
    }
    update( e->x()-5, 0, 10, height() );
    
    if ( e->state() & Qt::ShiftButton ) // naci¶niêty SHIFT - ruch poziomy
    {
      _pos.setX( e->x() );
    }
    else _pos = e->pos();
    
    
    emit valueChanged( p.x(), (double) value );
  }
}




void InputWidget::mousePressEvent( QMouseEvent *e )
{
  _pos = e->pos();
}

