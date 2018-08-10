#include "helpwidget.h"


// konstruktor
HelpWidget::HelpWidget(QString title, QWidget *parent, const char *name) : QWidget(parent, name)
{
    //////////////////////////////////////////////////////////////////////////////////////    GUI
    mainGrid = new QGridLayout(this, 1,1, 0,0);
    
    groupBox = new QGroupBox( 1, Qt::Horizontal, this );
    groupBox->setTitle(title);
      
    QFont f( this->font() );
    f.setPointSize( f.pointSize() - 2 );
    
    infoText = new QTextEdit( groupBox );          // info
    infoText->setFont( f );
    infoText->setText( helpString );
    infoText->setReadOnly( true );
    
     
    aboutAppButton = new QPushButton( QIconSet(QPixmap(Icons::appleGreenIcon())), tr("about %1").arg(APPNAME), groupBox ); // o myViona
    
    aboutQTButton = new QPushButton( tr("about Qt"), groupBox );  // o QT
    
    mainGrid->addWidget(groupBox, 0,0);
    /////////////////////////////////////////////////////////////////////////////////////    GUI
    
    
    connect( aboutQTButton, SIGNAL(clicked()), qApp, SLOT(aboutQt()) );
    connect( aboutAppButton, SIGNAL(clicked()), this, SLOT(aboutApp()) );
}



void HelpWidget::aboutApp()
{
  QString info = tr("<B>%1 (%2)</B> was developed by Przemek Jakwert (2004) <br>(pjakwert@diablo.ict.pwr.wroc.pl, pjakwert@o2.pl).<br> <B>VIONA</B> library was developed by Bogdan Kreczmer.<br> <B>libQGLViewer</B> was developed by Gilles Debunne (http://artis.imag.fr/Membres/Gilles.Debunne/QGLViewer/).").arg(APPNAME).arg(APPDESCRIPTION);
  
  QMessageBox::information( 0, tr("%1").arg(APPNAME), info, QMessageBox::Ok );
}
