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

#ifndef QWT_DIMAP_H
#define QWT_DIMAP_H

#include "qwt_global.h"

/*!
  \brief Map a double interval into an integer interval

  The QwtDiMap class maps an interval of type double into an interval of
  type int. It consists
  of two intervals D = [d1, d2] (double) and I = [i1, i2] (int), which are
  specified with the QwtDiMap::setDblRange and QwtDiMap::setIntRange
  members. The point d1 is mapped to the point i1, and d2 is mapped to i2. 
  Any point inside or outside D can be mapped to a point inside or outside
  I using QwtDiMap::transform or QwtDiMap::limTransform or vice versa
  using QwtPlot::invTransform. D can be scaled linearly or
  logarithmically, as specified with QwtDiMap::setDblRange.

  <b>Usage</b>
\verbatim
#include <qwt_dimap.h>

QwtDiMap map;
int ival;
double dval;

map.setDblRange(0.0, 3.1415);   // Assign an interval of type double with
				// linear mapping
map.setIntRange(0,100);         // Assign an integer interval

ival = map.transform(1.0);      // obtain integer value corresponding to 1.0
dval = map.invTransform(77);    // obtain double value corresponding to 77
\endverbatim
*/

class QWT_EXPORT QwtDiMap
{
public:
	QwtDiMap();
	QwtDiMap(int i1, int i2, double d1, double d2, bool lg = FALSE);
	~QwtDiMap();

	bool contains(double x) const;
	bool contains(int x) const;

	void setIntRange(int i1, int i2);
	void setDblRange(double d1, double d2, bool lg = FALSE);

	int transform(double x) const;
	double invTransform(int i) const;

	int limTransform(double x) const;
	double xTransform(double x) const;

	inline double d1() const;
	inline double d2() const;
	inline int i1() const;
	inline int i2() const;
	inline bool logarithmic() const;

	QT_STATIC_CONST double LogMin;
	QT_STATIC_CONST double LogMax;

private:
	void newFactor();	

	double d_x1, d_x2;  // double interval boundaries
	int d_y1, d_y2;     // integer interval boundaries
	double d_cnv;       // conversion factor
	bool d_log;		// logarithmic scale?
};

/*!
    \return the first border of the double interval
*/
inline double QwtDiMap::d1() const 
{
	return d_x1;
}

/*!
    \return the second border of the double interval
*/
inline double QwtDiMap::d2() const 
{
	return d_x2;
}

/*!
    \return the second border of the integer interval
*/
inline int QwtDiMap::i1() const 
{
	return d_y1;
}

/*!
    \return the second border of the integer interval
*/
inline int QwtDiMap::i2() const 
{
	return d_y2;
}

/*!
    \return TRUE if the double interval is scaled logarithmically
*/
inline bool QwtDiMap::logarithmic() const 
{
	return d_log;
}

#endif
