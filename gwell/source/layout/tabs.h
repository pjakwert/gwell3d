///////////////////////////////////////////////////////////////////////
//
//    class: Tabs (.h)
//
//    Gorne zakladki sterujace menu po lewej stronie
//
///////////////////////////////////////////////////////////////////////

#ifndef TABS_H
#define TABS_H


#include <qtabbar.h>
#include <qtooltip.h>

#include <const.h>




class Tabs : public QTabBar
{
  Q_OBJECT;

  public:
    Tabs( QWidget *parent, const char *name = 0 );
    ~Tabs() {}

  private:                   // poszczegolne zakladki:
    QTab    *fileTab;        // FILE
    QTab    *drawTab;        // DRAW
    QTab    *modifyTab;      // MODIFY
    QTab    *objectsTab;     // OBJECTS
    QTab    *lightsTab;      // LIGHTS
    QTab    *fogTab;         // FOG
    QTab    *optionsTab;     // OPTIONS
    QTab    *helpTab;        // HELP
};




         
#endif
