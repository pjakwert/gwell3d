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

#include "qwt_sclif.h"

//! Constructor
QwtScaleIf::QwtScaleIf()
{
    d_userScale = FALSE;
    d_maxMajor = 5;
    d_maxMinor = 3;
    d_scale.setScale(0.0,100.0,d_maxMajor, d_maxMinor);
}

//! Destructor
QwtScaleIf::~QwtScaleIf()
{
}

/*!
  \brief Specify a user-defined scale.

  By default, the widget is supposed to control the range of its scale
  automatically, but sometimes it is desirable to have a user-defined
  scale which is not in sync with
  the widget's range, e.g. if a logarithmic scale is needed
  (sliders don't support that) or if the scale is required
  to have a fixed range (say 0...100%), independent of the
  widget's range. 
  \param vmin
  \param vmax boundary values
  \param logarithmic If != 0, Build a logarithmic scale
  \sa QwtScaleIf::autoScale()
*/
void QwtScaleIf::setScale(double vmin, double vmax, int logarithmic)
{
    setScale(vmin,vmax,0.0,logarithmic);
}


/*!
  \brief Specify a user-defined scale.

  By default, the widget is supposed to control the range of its scale
  automatically, but sometimes it is desirable to have a user-defined
  scale which is not in sync with
  the widget's range, e.g. if a logarithmic scale is needed
  (sliders don't support that) or if the scale is required
  to have a fixed range (say 0...100%), independent of the
  widget's range. 
  \param vmin
  \param vmax interval boundaries
  \param step major step size
  \param logarithmic If != 0, build a logarithmic scale
  \sa QwtScaleIf::autoScale()
*/
void QwtScaleIf::setScale(double vmin, double vmax, 
	double step, int logarithmic)
{
    QwtScaleDiv oldscl(d_scale.scaleDiv());
    
    d_scale.setScale(vmin, vmax, d_maxMajor, d_maxMinor, step, logarithmic);
    d_userScale = TRUE;
    if (oldscl != d_scale.scaleDiv())
       scaleChange();
}


/*!
  \param Assign a user-defined scale division
  \param s scale division
*/
void QwtScaleIf::setScale(const QwtScaleDiv &s)
{
	if (s != d_scale.scaleDiv())
	{
		d_scale.setScale(s);
		d_maxMajor = s.majCnt();
		d_maxMinor = s.minCnt();
		d_userScale = TRUE;
		scaleChange();
	}
}


/*!
  \brief Advise the widget to control the scale range internally.

  Autoscaling is on by default. 
  \sa QwtScaleIf::setScale()
*/
void QwtScaleIf::autoScale()
{
	if (!d_userScale) 
	{
		d_userScale = FALSE;
		scaleChange();
	}
}

/*!
  \brief Set the maximum number of major tick intervals.

  The scale's major ticks are calculated automatically such that
  the number of major intervals does not exceed <ticks>.
  The default value is 5.
  \param ticks maximal number of major ticks.
  \sa QwtScaleDraw
*/
void QwtScaleIf::setScaleMaxMajor(int ticks)
{
	if (ticks != d_maxMajor)
	{
		d_maxMajor = ticks;
		d_scale.setScale(d_scale.scaleDiv().lBound(), 
		d_scale.scaleDiv().hBound(),
		d_maxMajor, d_maxMinor, 0.0,d_scale.scaleDiv().logScale()); 
		scaleChange();
	}
}

/*!
  \brief Set the maximum number of minor tick intervals

  The scale's minor ticks are calculated automatically such that
  the number of minor intervals does not exceed <ticks>.
  The default value is 3.
  \param ticks
  \sa QwtScaleDraw
*/
void QwtScaleIf::setScaleMaxMinor(int ticks)
{
    if ( ticks != d_maxMinor)
    {
		d_maxMinor = ticks;
		d_scale.setScale(d_scale.scaleDiv().lBound(), 
			d_scale.scaleDiv().hBound(),
			d_maxMajor, d_maxMinor, 0.0, d_scale.scaleDiv().logScale()); 
		scaleChange();
    }
}
