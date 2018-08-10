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

#ifndef QWT_SCALE_IF_H
#define QWT_SCALE_IF_H

#include "qwt_global.h"
#include "qwt_scldraw.h"


/*!
  \brief An interface class for widgets containing a scale 

  This interface class is used to provide classes
  with a protected QwtScaleDraw member and a public 
  interface to access that scale.

  \internal
  The primary purpose of this class is to define
  a common interface for classes which are supposed to
  contain a ScaleDraw class. It provides a protected 
  ScaleDraw member
  called d_scale and a couple of public member functions 
  which allow direct but restricted access 
  to this scale by the user.

  Widgets derived from this class have
  to implement the member function scaleChange(),
  which is called to notify changes of the
  scale parameters and usually requires repainting or
  resizing respectively.

  In general, a class derived from QwtScaleIf is 
  expected to manage the division and the position of its scale internally
  when no user-defined scale is set. It should take the d_maxMinor
  and d_maxMajor members into account, which can be set by the user.
  An implementation can check if a user-defined scale is set by calling the
  hasUserScale() member.
*/
class QWT_EXPORT QwtScaleIf
{
public:
    QwtScaleIf();
    virtual ~QwtScaleIf();
    
    void setScale (double vmin, double vmax, int logarithmic = 0);
    void setScale (double vmin, double vmax, double step, int logarithmic = 0);
    void setScale(const QwtScaleDiv &s);
    void setScaleMaxMajor( int ticks);
    void setScaleMaxMinor( int ticks);
    void autoScale();
    /*! \return max. number of minor tick intervals */
    int scaleMaxMinor() const {return d_maxMinor;}
    /*! \return max. number of major tick intervals */
    int scaleMaxMajor() const {return d_maxMinor;}

protected:
    //! Check for user-defined scale
    bool hasUserScale() {return d_userScale;}

    //! Notify changed scale
    virtual void scaleChange() = 0;

    QwtScaleDraw d_scale;
    int d_maxMajor;
    int d_maxMinor;
   
private:
    bool d_userScale;
};
#endif
