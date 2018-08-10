#ifndef FOGWIDGET_H
#define FOGWIDGET_H

#include <qgroupbox.h>
#include <qlayout.h>
#include <qgrid.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qpushbutton.h>

#include <const.h>
#include <GL/gl.h>
#include <options.h>
#include <colorwidget.h>
#include <floatspinbox.h>



/*!
Kompletna struktura opisuj±ca wszystkie parametry mg³y.
*/
typedef struct FogStruct
{
  /*!
  Konstruktor struktury mg³y ustawia warto¶ci domy¶lne.
  */
  FogStruct()
  {
    fogEnabled = false;
    fogMode = GL_LINEAR;
    fogDensity = 0.35;
    fogStart = 0.0;
    fogEnd = 1000.0;
    fogColor = new GLfloat[4];
     for (int i=0; i<4; i++) *(fogColor+i) = 0.0;
  }
  ~FogStruct() { delete [] fogColor; }
  
  /*!
  Czy mg³a jest w³±czona.
  */
  bool      fogEnabled;
  /*!
  Typ mg³y.
  */
  GLuint    fogMode;
  /*!
  Wspó³czynnik gêsto¶ci mg³y.
  */
  GLfloat   fogDensity;
  /*!
  Punkt, w którym rozpoczyna siê obliczanie mg³y.
  */
  GLfloat   fogStart;
  /*!
  Punkt, w którym koñczy siê obliczanie mg³y.
  */
  GLfloat   fogEnd;
  /*!
  Kolor i przezroczysto¶æ mg³y.
  */
  GLfloat*  fogColor;
};




/*!
Klasa FogWidget reprezentuje widget do zmiany parametrów mg³y.
*/
class FogWidget : public QWidget
{
  Q_OBJECT

  public:
    /*!
    \param title - tytu³ widgetu.
    */
    FogWidget( QString title, QWidget *parent=0, const char *name=0 );
    ~FogWidget() { delete _fog; }
    /*!
    Zwraca wska¼nik na u¿ywan± strukturê mg³y.
    */
    static FogStruct* fog() { return _fog; }
    
  private:
    /*!
    U¿ywana struktura mg³y.
    */
    static FogStruct*      _fog;
    
    QGridLayout*    globalGrid;
    QGroupBox*      mainGroupBox;
    QGridLayout*    mainGrid;
     QLabel*        fogModeLabel;
     QComboBox*     fogModeCombo;
     QLabel*        fogDensityLabel;
     FloatSpinBox*  fogDensitySpinBox;
     QLabel*        fogStartLabel;
     QLabel*        fogEndLabel;
     FloatSpinBox*  fogStartSpinBox;
     FloatSpinBox*  fogEndSpinBox;
     ColorWidget*   fogColorBox;
    QPushButton*    getBkgColorButton;

  private slots:
    /*!
    Slot w³±cza/wy³±cza mg³ê.
    */
    void fogToggled( bool );
    /*!
    Slot zmienia typ generowanej mg³y.
    */
    void fogModeChanged( int );
    /*!
    Slot zmienia gêsto¶æ mg³y.
    */
    void fogDensityChanged( float );
    /*!
    Slot zmienia punkt, w którym rozpoczyna siê obliczanie mg³y.
    */
    void fogStartChanged( float );
    /*!
    Slot zmienia punkt, w którym koñczy siê obliczanie mg³y.
    */
    void fogEndChanged( float );
    /*!
    Slot zmienia kolor generowanej mg³y
    \param color - kolor,
    \param alpha - przezroczysto¶æ.
    */
    void fogColorChanged( const QColor& color, int alpha );
    /*!
    Slot ustawia kolor mg³y zgodny z kolorem t³a sceny.
    */
    void getBackgroundColor();
    
  public slots:
    /*!
    Slot wywo³ywany w celu odpowiedniego ustawienia widgetów w zale¿no¶ci od warto¶ci w strukturze FogStruct.
    */
    void updateWidgets();
    
  signals:
    /*!
    Sygna³ wysy³any przy zmianie któregokolwiek z parametrów mg³y:
    \param fog - struktura mg³y,
    \param whichParamChanged - który z parametrów mg³y uleg³ zmianie.
    */
    void fogChanged( FogStruct* fog, FogParamsEnum whichParamChanged );
};




#endif
