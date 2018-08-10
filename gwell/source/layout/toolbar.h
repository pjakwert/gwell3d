#ifndef TOOLBAR_H
#define TOOLBAR_H


#include <qwidget.h>
#include <qtoolbox.h>
#include <qwidgetstack.h>
#include <qlayout.h>

#include <const.h>
#include <filewidget.h>
#include <drawwidget.h>
#include <modifywidget.h>
#include <objectswidget.h>
#include <lightswidget.h>
#include <fogwidget.h>
#include <optionswidget.h>
#include <helpwidget.h>


class ToolBar : public QWidget
{
  Q_OBJECT

  public:
    ToolBar(QString title, QWidget *parent, const char *name=0, WFlags fl=0);
    ~ToolBar() {}
    const QWidgetStack *widgetStack()   { return _widgetStack; }
    FileWidget    *fileWidget()         { return _fileWidget; }
    DrawWidget    *drawWidget()         { return _drawWidget; }
    ModifyWidget  *modifyWidget()       { return _modifyWidget; }
    LightsWidget  *lightsWidget()       { return _lightsWidget; }
    ObjectsWidget *objectsWidget()      { return _objectsWidget; }
    FogWidget     *fogWidget()          { return _fogWidget; }
    OptionsWidget *optionsWidget()      { return _optionsWidget; }
    HelpWidget    *helpWidget()         { return _helpWidget; }

  private:
    QGridLayout   *grid;
    QWidgetStack  *_widgetStack;
     FileWidget    *_fileWidget;
     DrawWidget    *_drawWidget;
     ModifyWidget  *_modifyWidget;
     ObjectsWidget *_objectsWidget;
     LightsWidget  *_lightsWidget;
     FogWidget     *_fogWidget;
     OptionsWidget *_optionsWidget;
     HelpWidget    *_helpWidget;
};




#endif
