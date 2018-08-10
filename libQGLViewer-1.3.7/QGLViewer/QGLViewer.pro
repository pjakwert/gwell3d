
#		l i b Q G L V i e w e r
#	C o m p i l a t i o n    c o n f i g u r a t i o n

# This configuration file is divided into architecture specific sections.
# You may need to tune some paths, especially for GL.
# Other than that, simply run "qmake" with optionnal arguments, as in "qmake PREFIX=$HOME".

# Attention : Windows Qt 2.3 users should use QGLViewer.Qt2.3.pro instead of this file.

# See doc/download.html for details.

# If your Qt version is lower than 3.1 (look at $QTDIR/lib), you need to link with GLUT.
# Uncomment the following line :
# USE_GLUT = yes

#		--  M a i n   v a r i a b l e s  --
TEMPLATE = lib
CONFIG  *= qt opengl warn_on release thread create_prl dll
TARGET   = QGLViewer
VERSION  = 1.3.7

HEADERS  = qglviewer.h \
	   camera.h \
	   manipulatedFrame.h \
	   manipulatedCameraFrame.h \
	   spinningFrame.h \
	   frame.h \
	   constraint.h \
	   keyFrameInterpolator.h \
	   mouseGrabber.h \
	   quaternion.h \
	   vec.h \
	   config.h

SOURCES  = qglviewer.cpp \
	   camera.cpp \
	   manipulatedFrame.cpp \
	   manipulatedCameraFrame.cpp \
	   spinningFrame.cpp \
	   frame.cpp \
	   saveSnapshot.cpp \
	   constraint.cpp \
	   keyFrameInterpolator.cpp \
	   mouseGrabber.cpp \
	   quaternion.cpp \
	   vec.cpp


#		--  U n i x  --
unix {
  # INCLUDE_DIR and LIB_DIR specify where to install the include files and the library.
  # Use qmake INCLUDE_DIR=... LIB_DIR=... , or qmake PREFIX=... to customize your installation.
  isEmpty( PREFIX ) {
    PREFIX=/usr/local
  }
  isEmpty( LIB_DIR ) {
    LIB_DIR = $$PREFIX/lib
  }
  isEmpty( INCLUDE_DIR ) {
    INCLUDE_DIR = $$PREFIX/include
  }

  # GLUT for Unix architecture
  !isEmpty( USE_GLUT ) {
    QMAKE_LIBS_OPENGL *= -lglut
  }

  # Documentation install
  isEmpty( DOC_DIR ) {
    DOC_DIR = $$PREFIX/share/doc
  }

  # -p option should be -P, so that "make install" as root creates files owned by root
  # and links are preserved.
  QMAKE_COPY_FILE = $(COPY) -P

  # Make much smaller libraries, removing debugging informations
  QMAKE_CFLAGS_RELEASE -= -g
  QMAKE_CXXFLAGS_RELEASE -= -g

  # install header 
  include.path  = $$INCLUDE_DIR/QGLViewer
  include.files = $$HEADERS
  # install cw files
  cwFiles.path  = $$INCLUDE_DIR/QGLViewer/cwFiles
  cwFiles.files = cwFiles/*
  # install documentation html
  documentation.path = $$DOC_DIR/QGLViewer
  documentation.files = ../doc/*.html ../doc/*.css
  # install documentation images
  docImages.path = $$DOC_DIR/QGLViewer/images
  docImages.files = ../doc/images/*
  # install documentation examples
  #docExamples.path = $$DOC_DIR/QGLViewer/examples
  #docExamples.files = ../examples/*
  # install documentation refManual
  docRefManual.path = $$DOC_DIR/QGLViewer/refManual
  docRefManual.files = ../doc/refManual/*
  # install library
  target.path   = $$LIB_DIR
  # "make install" configuration options
  INSTALLS     += target include cwFiles documentation docImages docRefManual
}


#		--  S G I   I r i x  --
irix-n32 {
  QMAKE_CFLAGS_RELEASE   -= -O3 -O2 -OPT:Olimit=30000
  QMAKE_LFLAGS_RELEASE   -= -O3 -O2 -OPT:Olimit=30000
  QMAKE_CXXFLAGS_RELEASE -= -O3 -O2 -OPT:Olimit=30000
  QMAKE_CFLAGS_RELEASE   *= -IPA -Ofast=IP35
  QMAKE_LFLAGS_RELEASE   *= -IPA -Ofast=IP35
  QMAKE_CXXFLAGS_RELEASE *= -IPA -Ofast=IP35
  QMAKE_CFLAGS           *= -LANG:std
  QMAKE_LFLAGS           *= -LANG:std
  QMAKE_CXXFLAGS         *= -LANG:std 
  QMAKE_CFLAGS           += -woff 1424,3201,1110,1188
  QMAKE_CXXFLAGS         += -woff 1424,3201,1110,1188
  QMAKE_LIBS_OPENGL      -= -lXi
  # GLUT for SGI architecture
  !isEmpty( USE_GLUT ) {
    QMAKE_LIBDIR_OPENGL    *= /usr/local/lib32
    QMAKE_INCDIR_OPENGL    += /usr/local/include
  }
}


#		--  L i n u x  --
linux-g++ {
  # Patch for gcc 3.2.0
  system( g++ --version | grep "3\.2 " > /dev/null ) {
      message( Patching for gcc 3.2 - using debug configuration )
      CONFIG -= release
      CONFIG *= debug
  }

  # Patch for gcc 3.3.1-2
  system( g++ --version | grep "3\.3\.1\-2" > /dev/null ) {
      message( Patching for gcc 3.3.1-2 - using debug configuration )
      CONFIG -= release
      CONFIG *= debug
  }
}


#		--  W i n d o w s  --
win32 {
  # MSVC6.0 does it automatically, but not the dos window
  DEFINES *= WIN32

  # Creates a lib and a dll instead of a static lib
  DEFINES *= MAKE_QGLVIEWER_DLL

  # Make sur to have C++ files, PentiumPro code, few warnings, add
  # support to RTTI and Exceptions, and generate debug info "program database"
  # Any feedback welcome on these flags.
  QMAKE_CXXFLAGS = -TP -G6 -W1 -GR -GX -Zi
  # Optimise for speed, and expand any suitable inlines :
  QMAKE_CXXFLAGS_RELEASE = -O2
  # Optimise for debug, and generate browse database :
  QMAKE_CXXFLAGS_DEBUG   = -Od -FR"Debug/"

  # Make sure that link prints its arguments:
  QMAKE_LDFLAGS += -logo
}


#		--  M a c i n t o s h  --
macx {
  # GLUT for Macintosh architecture
  !isEmpty( USE_GLUT ) {
    QMAKE_LIBS_OPENGL -= -lglut
    QMAKE_LIBS_OPENGL += -framework GLUT
  }
  CONFIG -= thread
}


#		--  V e c t o r i a l   R e n d e r i n g  --
# In case of compilation troubles with EPS (vectorial) rendering, uncomment this line
# DEFINES *= NO_EPS_RENDER

contains( DEFINES, NO_EPS_RENDER ): message( EPS render option disabled )

!contains( DEFINES, NO_EPS_RENDER ) {
  FORMS    = EPSInterface.ui

  SOURCES  *= \
	EPSRender/Affichage.cpp \
	EPSRender/BSPTree.cpp \
	EPSRender/EPSRender.cpp \
	EPSRender/Geometry.cpp \
	EPSRender/GeometryUtils.cpp \
	EPSRender/gpc.cpp \
	EPSRender/VisibilityGraph.cpp

  HEADERS  *= \
	EPSRender/Affichage.h \
	EPSRender/BSPTree.h \
	EPSRender/EPSRender.h \
	EPSRender/Functions.h \
	EPSRender/Geometry.h \
	EPSRender/GeometryUtils.h \
	EPSRender/gpc.h \
	EPSRender/Liste.h \
	EPSRender/OffScreen.h \
	EPSRender/SecuredArray.h \
	EPSRender/Vects.h \
	EPSRender/VisibilityGraph.h 
}
