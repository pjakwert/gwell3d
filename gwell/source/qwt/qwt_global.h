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

#ifndef QWT_GLOBAL_H
#define QWT_GLOBAL_H

#include <qmodules.h>
#include <qglobal.h>

#define QWT_VERSION       041
#define QWT_VERSION_STR   "0.4.1"

//
// Create Qwt DLL if QWT_DLL is defined (Windows only)
//

#if defined(Q_WS_WIN)

#if defined(_MSC_VER) /* MSVC Compiler */
/* template-class specialization 'identifier' is already instantiated */
#pragma warning(disable: 4660)
#endif

#if defined(QWT_NODLL)
#undef QWT_MAKEDLL
#undef QWT_DLL
#undef QWT_TEMPLATEDLL
#endif

#ifdef QWT_DLL
#if defined(QWT_MAKEDLL)     /* create a Qwt DLL library */
#undef QWT_DLL
#define QWT_EXPORT  __declspec(dllexport)
#define QWT_TEMPLATEDLL
#endif
#endif

#if defined(QWT_DLL)     /* use a Qwt DLL library */
#define QWT_EXPORT  __declspec(dllimport)
#define QWT_TEMPLATEDLL
#endif

#else // ! Q_WS_WIN
#undef QWT_MAKEDLL       /* ignore these for other platforms */
#undef QWT_DLL
#undef QWT_TEMPLATEDLL
#endif

#ifndef QWT_EXPORT
#define QWT_EXPORT
#endif

#if defined(QT_NO_TABLE) || !defined(QT_MODULE_TABLE)
#define QWT_NO_LEGEND
#endif

#endif // QWT_GLOBAL_H
