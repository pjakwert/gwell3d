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

#ifndef QWT_SLDBASE_H
#define QWT_SLDBASE_H

#include <qframe.h>
#include <qpixmap.h>
#include <qdatetime.h>
#include "qwt_global.h"
#include "qwt_drange.h"

/*!
  \brief A Base class for sliders

  QwtSliderBase is a base class for
  slider widgets. QwtSliderBase handles the mouse events
  and updates the slider's value accordingly. Derived classes
  only have to implement the getValue() and 
  getScrollMode() members, and should react to a
  valueChange(), which normally requires repainting. 
*/

class QWT_EXPORT QwtSliderBase : public QWidget, public QwtDblRange
{
    Q_OBJECT 

public:
    enum ScrollMode { ScrNone, ScrMouse, 
        ScrTimer, ScrDirect, ScrPage };
    
    QwtSliderBase( QWidget *parent = 0, 
        const char *name = 0, WFlags flags = 0 );
    virtual ~QwtSliderBase();

    void setUpdateTime(int t);
    void stopMoving();
    void setTracking(bool enable);

public slots:
    void setValue(double val);
    void fitValue(double val);
    void incValue(int steps);

signals:

    /*!
      \brief Notify a change of value.

      In the default setting 
      (tracking enabled), this signal will be emitted every 
      time the value changes ( see setTracking() ). 
      \param value new value
    */
    void valueChanged(double value);

    /*!
      This signal is emitted when the user presses the 
      movable part of the slider (start ScrMouse Mode).
    */
    void sliderPressed();

    /*!
      This signal is emitted when the user releases the 
      movable part of the slider.
    */

    void sliderReleased();
    /*!
      This signal is emitted when the user moves the
      slider with the mouse.
      \param value new value
    */
    void sliderMoved(double value);
    
protected:
    virtual void setMass(double val);
    virtual double mass() const;

    void setPosition(const QPoint &p);
    virtual void valueChange();

    virtual void timerEvent(QTimerEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void wheelEvent(QWheelEvent *e);

  /*!
    \brief Determine the value corresponding to a specified poind

    This is an abstract virtual function which is called when
    the user presses or releases a mouse button or moves the
    mouse. It has to be implemented by the derived class.
    \param p point 
  */
    virtual double getValue(const QPoint & p) = 0;
  /*!
    \brief Determine what to do when the user presses a mouse button.

    This function is abstract and has to be implemented by derived classes.
    It is called on a mousePress event. The derived class can determine
    what should happen next in dependence of the position where the mouse
    was pressed by returning scrolling mode and direction. QwtSliderBase
    knows the following modes:<dl>
    <dt>QwtSliderBase::ScrNone
    <dd>Scrolling switched off. Don't change the value.
    <dt>QwtSliderBase::ScrMouse
    <dd>Change the value while the user keeps the
        button pressed and moves the mouse.
    <dt>QwtSliderBase::ScrTimer
    <dd>Automatic scrolling. Increment the value
        in the specified direction as long as
    the user keeps the button pressed.
    <dt>QwtSliderBase::ScrPage
    <dd>Automatic scrolling. Same as ScrTimer, but
        increment by page size.</dl>

    \param p point where the mouse was pressed
    \retval scrollMode The scrolling mode
    \retval direction  direction: 1, 0, or -1.
  */
    virtual void getScrollMode( const QPoint &p,
                  int &scrollMode, int &direction) = 0;

    int d_scrollMode;
    double d_mouseOffset;
    int d_direction;
    int d_tracking;

private:
    int d_tmrID;
    int d_updTime;
    int d_timerTick;
    QTime d_time;
    double d_speed;
    double d_mass;

    void buttonReleased();
};

#endif
