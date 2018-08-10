# The <code>KeyFrameInterpolator</code> test example.

# KeyFrameInterpolator smoothly interpolate their attached Frame over time on a path defined by
# Frames. The interpolation can be started/stopped/reset, played in loop, played at a different
# speed, etc...

# In this examples, the path is defined by four ManipulatedFrame which all can be moved with the
# mouse. The interpolating path is updated accordingly.

# The path and the interpolating axis are drawn using KeyFrameInterpolator::drawPath().

# By default, the Camera holds 12 KeyFrameInterpolator, binded to the F1-12 keys. Use Alt-Fx to
# define a new keyFrame for path x, and simply press Fx to play/pause the path x. See the <a
# href="../shortcuts.html">shortcuts</a> page for details.

TEMPLATE = app
TARGET   = keyFrames
CONFIG  += qt opengl warn_on release thread

HEADERS  = keyFrames.h
SOURCES  = keyFrames.cpp main.cpp

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
