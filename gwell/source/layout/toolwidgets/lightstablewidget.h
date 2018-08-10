//////////////////////////////////////////////////////////////////
///
///  class: LightsTableWidget (.h)
///
///  widget ze ¶wiat³ami dziedzicz±cy QTable
///
//////////////////////////////////////////////////////////////////
#ifndef LIGHTS_TABLE_WIDGET_H
#define LIGHTS_TABLE_WIDGET_H

#include <qtable.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qstringlist.h>

#include <icons.h>
#include <light.h>


typedef struct wl
{
  Light*     light;
  QCheckBox* tableCheck;
  QComboBox* tableCombo;
} WidgetsList;


class LightsTableWidget : public QTable
{
  Q_OBJECT
      
  public:
    LightsTableWidget( QWidget* parent );
    ~LightsTableWidget() {}

  private:
    QPtrList<Light>* _lightsList;
    QPtrList<WidgetsList>* _widgetsList;
    
  public slots:
    void setLightsList( QPtrList<Light>* lightsList );
    void addLight( int bulbOrSpotlight, bool isMovingWithCamera = false ); // 0=bulb, 1=spotlight
    void addLight( Light *light );
    void deleteLight();
    void deleteAllLights();
    
  private slots:
    void toggleLight( bool );
    void bulbOrSpotChanged( int );
    void currentLightChanged( int, int );
    void userChangedName(int,int);
    
  signals:
    void lightSelected( Light* light );
    void lightParamsChanged( Light* light );
    void lightRemoved();
    void lightAdded();
    
  protected:
    void resizeEvent( QResizeEvent* e );
};

#endif
