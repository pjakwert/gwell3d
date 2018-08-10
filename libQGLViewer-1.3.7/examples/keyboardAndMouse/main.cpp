#include "keyboardAndMouse.h"
#include <qapplication.h>

int main(int argc, char** argv)
{
  // Read command lines arguments.
  QApplication application(argc,argv);

  // Instantiate the viewer.
  Viewer v;

  // Make the viewer window visible on screen.
  v.show();
  
  // Set the viewer as the application main widget.
  application.setMainWidget(&v);
  
  // Run main loop.
  return application.exec();
}
