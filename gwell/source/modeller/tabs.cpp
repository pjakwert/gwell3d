///////////////////////////////////////////////////////////////////////
//
//    class: Tabs (.cpp)
//
//    Gorne zakladki sterujace menu po lewej stronie
//
///////////////////////////////////////////////////////////////////////

#include "tabs.h"



Tabs::Tabs( QWidget *parent, const char *name ) : QTabBar( parent, name )
{
  fileTab    = new QTab( tr("File") );
  drawTab    = new QTab( tr("Draw") );
  modifyTab  = new QTab( tr("Modify") );
  objectsTab = new QTab( tr("Objects") );
  lightsTab  = new QTab( tr("Lights") );
  optionsTab = new QTab( tr("Options") );
  helpTab    = new QTab( tr("Help") );
  
  this->insertTab( fileTab,    FILE_TAB_ID );
  this->insertTab( drawTab,    DRAW_TAB_ID );
  this->insertTab( modifyTab,  MODIFY_TAB_ID );
  this->insertTab( objectsTab, OBJECTS_TAB_ID );
  this->insertTab( lightsTab,  LIGHTS_TAB_ID );
  this->insertTab( optionsTab, OPTIONS_TAB_ID );
  this->insertTab( helpTab,    HELP_TAB_ID );
}




