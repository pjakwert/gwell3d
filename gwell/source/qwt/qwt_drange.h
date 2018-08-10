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

#ifndef QWT_DBLRANGE_H
#define QWT_DBLRANGE_H

#include "qwt_global.h"

/*!
  \brief A class which controls a value within an interval

  This class is useful as a base class or a member for sliders.
  It represents an interval of type double within which a value can
  be moved. The value can be either an arbitrary point inside 
  the interval (see QwtDblRange::setValue), or it can be fitted
  into a step raster (see QwtDblRange::fitValue and
  QwtDblRange::incValue).

  As a special case, a QwtDblRange can be periodic, which means that
  a value outside the interval will be mapped to a value inside the
  interval when QwtDblRange::setValue(), QwtDblRange::fitValue(), 
  QwtDblRange::incValue() or QwtDblRange::incPages() are called.
*/

class QWT_EXPORT QwtDblRange
{
public:
	QwtDblRange();

	void setRange(double vmin, double vmax, double vstep = 0.0,
		int pagesize = 1);

	virtual void setValue(double);
	double value() const;

	void setPeriodic(bool tf);
	bool periodic() const;

	void setStep(double);
	double step() const;

	double maxValue() const;
	double minValue() const; 

	int pageSize() const;

	virtual void incValue(int);
	virtual void incPages(int);
	virtual void fitValue(double);

protected:

	double exactValue() const;
	double exactPrevValue() const;
	double prevValue() const;

	virtual void valueChange();
	virtual void stepChange();
	virtual void rangeChange();

private:
	void setNewValue(double x,int align = 0);

	double d_minValue;
	double d_maxValue;
	double d_step;
	int d_pageSize;
	double d_value;
	double d_exactValue;
	double d_exactPrevValue;
	double d_prevValue;
	bool d_periodic;
};

#endif
