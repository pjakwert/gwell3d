#include "toolbar.h"
#include <qtextedit.h>


ToolBar::ToolBar(QString title, QWidget *parent, const char *name, WFlags fl) : QWidget(parent, name, fl)
{
  //setLabel(title);
  _widgetStack = new QWidgetStack(this);

  grid = new QGridLayout(this, 1,1, 5,5);
  
    _fileWidget = new FileWidget( tr(" File "), _widgetStack);
  _widgetStack->addWidget(_fileWidget, FILE_TAB_ID);

    _drawWidget = new DrawWidget( tr(" Draw "), _widgetStack);
  _widgetStack->addWidget(_drawWidget, DRAW_TAB_ID);

    _modifyWidget = new ModifyWidget( tr(" Modify "), _widgetStack);
  _widgetStack->addWidget(_modifyWidget, MODIFY_TAB_ID);
  
    _objectsWidget = new ObjectsWidget( tr(" Objects" ), _widgetStack );
  _widgetStack->addWidget( _objectsWidget, OBJECTS_TAB_ID );

    _lightsWidget = new LightsWidget( tr(" Lights "), _widgetStack);
  _widgetStack->addWidget(_lightsWidget, LIGHTS_TAB_ID);
  
    _optionsWidget = new OptionsWidget( tr(" Options "), _widgetStack);
  _widgetStack->addWidget(_optionsWidget, OPTIONS_TAB_ID);
  
    _helpWidget = new HelpWidget( tr(" Help "), _widgetStack );
  _widgetStack->addWidget( _helpWidget, HELP_TAB_ID );

  grid->addWidget(_widgetStack, 0,0);  
}


