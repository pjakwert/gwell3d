#include <qapplication.h>
#include <qlayout.h>

#include <qpixmap.h>
#include <qsplashscreen.h>
#include <qmessagebox.h>
#include <qgl.h>


#include "gwellinterface.h"



int main (int argc, char **argv)
{
  QApplication *app = new QApplication(argc, argv);

  if ( !QGLFormat::hasOpenGL() )
  {
    printf("Gwell Modeler: You don't have any OpenGL implementation installed.\n");
    QMessageBox::critical(
                            0,
                            QObject::tr("No OpenGL"),
                            QObject::tr("You don't have any OpenGL implementation installed.")
                          );
    return -1;
  }
  
  // splash
  //QPixmap pixmap("../../images/apple.jpg");
  //QSplashScreen *splash = new QSplashScreen(pixmap);
  //splash->show();
  // splash
  
  //splash->message( "Setting language ...", Qt::AlignLeft | Qt::AlignBottom, QColor(192,192,192) );
  
  QSettings settings;
  settings.setPath( "PrzemekJakwert.pl", "Gwell" ); // domena korporacji i produkt :)
  settings.beginGroup( "/Gwell" );
   settings.beginGroup( "/Paths" ); // grupa ¶cie¿ek
    QString langPath = settings.readEntry( "/languages", "languages/" );
   settings.endGroup();
   QString tp = settings.readEntry( "/Modeler language", "english" ); // plik z jêzykiem dla Modeler-a
  settings.endGroup();
    
  QTranslator translator( 0 );
  if ( translator.load( tp, langPath ) ) qApp->installTranslator( &translator );
  
  //splash->message( "Loading interface ...", Qt::AlignLeft | Qt::AlignBottom, QColor(192,192,192) );
  GwellInterface *gwell = new GwellInterface;//(mainWindow);
  gwell->resize(800,600);
  // ikona ustawiana jest wewn±trz GwellInterface

  app->setMainWidget(gwell);
  QObject::connect(app, SIGNAL (lastWindowClosed()), app, SLOT (quit()));
  gwell->show();

  // splash
  //splash->finish(gwell);
  //delete splash;
  
  return app->exec();
}
