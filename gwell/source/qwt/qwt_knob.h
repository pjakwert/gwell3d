/*-*- c++ -*-******************************************************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *****************************************************************************/

#ifndef QWT_KNOB_H
#define QWT_KNOB_H

#include "qwt_global.h"
#include "qwt_sldbase.h"
#include "qwt_sclif.h"

/*!
  \brief The Knob Widget

  The QwtKnob widget imitates look and behaviour of a volume knob on a radio.
  It contains a scale around the knob which is set up automatically or can
  be configured manually (see QwtScaleIf).
  Automatic scrolling is enabled when the user presses a mouse
  button on the scale. For a description of signals, slots and other
  members, see QwtSliderBase.

  \image html knob.gif
  \sa   QwtSliderBase and QwtScaleIf for the descriptions
    of the inherited members.
*/

class QWT_EXPORT QwtKnob : public QwtSliderBase, public QwtScaleIf
{
public:
    /*!
        Symbol
        \sa QwtKnob::QwtKnob()
    */

    enum Symbol { Line, Dot };

    QwtKnob(QWidget* parent = 0, const char *name = 0);
    virtual ~QwtKnob();

    void setKnobWidth(int w);
    void setTotalAngle (double angle);
    void setBorderWidth(int bw);
    void setSymbol(Symbol);
    Symbol symbol() const;

    virtual QSize sizeHint() const;
    virtual QSize minimumSizeHint() const;
    virtual QSizePolicy sizePolicy() const;
    
protected:
    virtual void paintEvent(QPaintEvent *e);
    virtual void resizeEvent(QResizeEvent *e);

    void draw(QPainter *p, const QRect& ur);
    void drawKnob(QPainter *p, const QRect &r);
    void drawMarker(QPainter *p, double arc, const QColor &c);

private:
    void layoutKnob( bool update = TRUE );
    double getValue(const QPoint &p);
    void getScrollMode( const QPoint &p, int &scrollMode, int &direction );
    void recalcAngle();
    
    virtual void valueChange();
    virtual void rangeChange();
    virtual void scaleChange();
    virtual void fontChange(const QFont &oldFont);

    int d_borderWidth;
    int d_borderDist;
    int d_hasScale;
    int d_scaleDist;
    int d_maxScaleTicks;
    int d_knobWidth;
    int d_dotWidth;

    Symbol d_symbol;
    double d_angle;
    double d_oldAngle;
    double d_totalAngle;
    double d_nTurns;

    QRect d_kRect;
};

#endif
