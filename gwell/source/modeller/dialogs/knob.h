#ifndef KNOB_H
#define KNOB_H

#include <qwt_knob.h>
#include <kernel.h>



class Knob : public QwtKnob
{
  Q_OBJECT
      
  public:
    Knob( QWidget *parent = 0, const char* name = 0 );
    ~Knob() {}

  public slots:
    void setRangeFromItem( ViKinemCtrlItem *controlItem );
};




#endif
