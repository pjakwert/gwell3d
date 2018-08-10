/****************************************************************************

 This file is part of the QGLViewer library
 Copyright (C) 2002-2004  Gilles Debunne (Gilles.Debunne@imag.fr)
 Version 1.3.7 Release 1. Packaged on Friday April 30, 2004.

 http://artis.imag.fr/Members/Gilles.Debunne/QGLViewer

 libQGLViewer is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 libQGLViewer is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with libQGLViewer; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*****************************************************************************/

///////////////////////////////////////////////////////////////////
//               libQGLViewer configuration file                 //
//  Modify these settings according to your local configuration  //
///////////////////////////////////////////////////////////////////

#ifndef QGLVIEWER_CONFIG_H
#define QGLVIEWER_CONFIG_H

#define QGLVIEWER_VERSION 0x010307

#ifndef QT_CLEAN_NAMESPACE
# define QT_CLEAN_NAMESPACE
#endif

// Get QT_VERSION and other QT flags
#include <qglobal.h>

// Win 32 DLL export macros
#ifdef WIN32
# include <windows.h> // Warning : windows.h must be included BEFORE gl.h
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# ifdef MAKE_QGLVIEWER_DLL
#  define QGLVIEWER_EXPORT  __declspec(dllexport)
# else
#  define QGLVIEWER_EXPORT  __declspec(dllimport)
# endif
#endif // WIN32

// For other architectures, this macro is empty
#ifndef QGLVIEWER_EXPORT
# define QGLVIEWER_EXPORT
#endif

// Patch for gcc version <= 2.95
#if defined(__GNUC__) && defined(__GNUC_MINOR__) && (__GNUC__ < 3) && (__GNUC_MINOR__ < 96)
# include <iostream>
# include <qstring.h>

  std::ostream& operator<<(std::ostream& out, const QString& str)
  { out << str.latin1();  return out; }
#endif

// Minimal required QT version that does not need GLUT
#define QT_VERSION_WITHOUT_GLUT 0x030100

// OpenGL includes (see windows.h warning above)
#ifndef __APPLE__
# include <GL/gl.h>
# include <GL/glu.h>
# if QT_VERSION < QT_VERSION_WITHOUT_GLUT
#  include <GL/glut.h>
# endif
#else
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# if QT_VERSION < QT_VERSION_WITHOUT_GLUT
#  include <GLUT/glut.h>
# endif
#endif

// Qt 2.3 compatibility patches
#if QT_VERSION < 300
# include <vector> // also defines std::max and std::abs
# define QValueVector std::vector
# include <qlist.h>
# define QPtrList QList
# define QPtrListIterator QListIterator
# ifndef DOXYGEN
  // Used only to detect a Reality Center configuration for stereo mode.
  class QDesktopWidget
  {
  public:
    int width()  const { return 1280; };
    int height() const { return 1024; };
  };
# endif
#else
# include <qptrlist.h>
# include <qvaluevector.h>
#endif

#endif // QGLVIEWER_CONFIG_H
