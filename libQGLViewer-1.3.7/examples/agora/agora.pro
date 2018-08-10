# Implementation of the game of <i>Agora</i>. 

# <i>Agora</i> is a strategy game for two players. The code is rather complex and
# can be divided in two parts : a QGLViewer implementation for the viewer and an artificial
# intelligence that allows you to play against the computer.

# You should find the rules of the game on the web. Questions relative to the artificial
# intelligence implementation should be asked to <code>Jean-Guillaume dot Dumas at imag dot fr</code>.

TEMPLATE = app
TARGET   = agora
CONFIG  += qt opengl warn_on release thread

# Input
HEADERS += agora_alphabeta.inl  agora_coupspossibles.inl  agora_init.inl  agora_jouer.inl   agoraViewer.h
HEADERS += agora_class.h        agora_evaluation.inl      agora_io.h      container_stream.h agora_container.h
HEADERS += agora_coup.h         agora.h                   agora_io.inl    agora_types.h     givtimer.h
SOURCES += main.cpp givtimer.C agoraViewer.cpp

FORMS += agoraWindow.ui

# "make dist" additionnal files
DISTFILES += wood.png

QMAKE_CXXFLAGS_RELEASE *= -O7 -funroll-all-loops -felide-constructors -fstrict-aliasing -frerun-loop-opt \
			  -fexpensive-optimizations -fforce-addr -fforce-mem -fstrength-reduce

# JG's paths
#INCLUDEPATH *=/home/soft/libQGLViewer-1.3.5-1/include 
#LIBS *= -L/home/soft/libQGLViewer-1.3.5-1/lib -lQGLViewer

LIBS += -lXi
##  Windows Qt 2.3 users should uncomment the next 2 lines and remove all the remaining lines.
#DEFINES *= QT_DLL QT_THREAD_SUPPORT
#LIBS *= QGLViewer.lib


# Unix : same INCLUDE_DIR and LIB_DIR parameters than for the make install 
unix {
  isEmpty( PREFIX ) {
    PREFIX=/usr/local
  }
  isEmpty( LIB_DIR ) {
    LIB_DIR = $$PREFIX/lib
  }
  isEmpty( INCLUDE_DIR ) {
    INCLUDE_DIR = $$PREFIX/include
  }

  INCLUDE_PATH = $$INCLUDE_DIR

  !exists( $$INCLUDE_DIR/QGLViewer/qglviewer.h ) {
    message( Unable to find QGLViewer/qglviewer.h in $$INCLUDE_PATH )
    message( Use qmake INCLUDE_DIR~Path/To/QGLViewer/HeaderFiles )
    error( Replace the ~ by the "equals" character in the above line )
  }

  macx {
    LIB_NAME = libQGLViewer.*.dylib
  } else {
    LIB_NAME = libQGLViewer.so.*
  }
  !exists( $$LIB_DIR/$$LIB_NAME ) {
    message( Unable to find $$LIB_NAME in $$LIB_DIR )
    message( You should run qmake LIB_DIR~Path/To/QGLViewer/Lib )
    error( Replace the ~ by the "equals" character in the above line )
  }


  # Path was correctly detected
  INCLUDEPATH *= $$INCLUDE_PATH
  DEPENDPATH  *= $$INCLUDE_PATH
  LIBS        *= -L$$LIB_DIR -lQGLViewer
  LIBS        *= -lXi # Seems to be needed on RedHat 9
  macx {
    LIBS *= -lobjc
    CONFIG -= thread
  }

  # Remove debugging options
  QMAKE_CFLAGS_RELEASE -= -g
  QMAKE_CXXFLAGS_RELEASE -= -g
}


# Windows configuration.
# See doc/download.html page for details on include and lib paths.
win32 {
  # Various compilation flags
  QMAKE_CXXFLAGS = -TP -G6 -W1 -GR -GX -Zi
  # Optimise for speed, and expand any suitable inlines
  QMAKE_CXXFLAGS_RELEASE = -O2 -Ob2

  # Use the Qt DLL version
  DEFINES *= QT_DLL QT_THREAD_SUPPORT

  # Standard zip architechture : libQGLViewer-1.3.6 is ../../
  exists( ../../QGLViewer/qglviewer.h ) {
    INCLUDEPATH *= ../../
  }

  exists( ../../QGLViewer/Debug/QGLViewer*.lib ) {
    LIBPATH = ../../QGLViewer/Debug
  }

  exists( ../../QGLViewer/Release/QGLViewer*.lib ) {
    LIBPATH = ../../QGLViewer/Release
  }

  exists( ../../QGLViewer/QGLViewer*.lib ) {
    LIBPATH = ../../QGLViewer
  }

  win32-msvc.net {
    LIBS *= $$LIBPATH/QGLViewer137.lib
  } else {
    LIBS *= $$LIBPATH/QGLViewer.lib
  }
}
