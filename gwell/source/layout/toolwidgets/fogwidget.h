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
Kompletna struktura opisuj�ca wszystkie parametry mg�y.
*/
typedef struct FogStruct
{
  /*!
  Konstruktor struktury mg�y ustawia warto�ci domy�lne.
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
  Czy mg�a jest w��czona.
  */
  bool      fogEnabled;
  /*!
  Typ mg�y.
  */
  GLuint    fogMode;
  /*!
  Wsp�czynnik g�sto�ci mg�y.
  */
  GLfloat   fogDensity;
  /*!
  Punkt, w kt�rym rozpoczyna si� obliczanie mg�y.
  */
  GLfloat   fogStart;
  /*!
  Punkt, w kt�rym ko�czy si� obliczanie mg�y.
  */
  GLfloat   fogEnd;
  /*!
  Kolor i przezroczysto�� mg�y.
  */
  GLfloat*  fogColor;
};




/*!
Klasa FogWidget reprezentuje widget do zmiany parametr�w mg�y.
*/
class FogWidget : public QWidget
{
  Q_OBJECT

  public:
    /*!
    \param title - tytu� widgetu.
    */
    FogWidget( QString title, QWidget *parent=0, const char *name=0 );
    ~FogWidget() { delete _fog; }
    /*!
    Zwraca wska�nik na u�ywan� struktur� mg�y.
    */
    static FogStruct* fog() { return _fog; }
    
  private:
    /*!
    U�ywana struktura mg�y.
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
    Slot w��cza/wy��cza mg��.
    */
    void fogToggled( bool );
    /*!
    Slot zmienia typ generowanej mg�y.
    */
    void fogModeChanged( int );
    /*!
    Slot zmienia g�sto�� mg�y.
    */
    void fogDensityChanged( float );
    /*!
    Slot zmienia punkt, w kt�rym rozpoczyna si� obliczanie mg�y.
    */
    void fogStartChanged( float );
    /*!
    Slot zmienia punkt, w kt�rym ko�czy si� obliczanie mg�y.
    */
    void fogEndChanged( float );
    /*!
    Slot zmienia kolor generowanej mg�y
    \param color - kolor,
    \param alpha - przezroczysto��.
    */
    void fogColorChanged( const QColor& color, int alpha );
    /*!
    Slot ustawia kolor mg�y zgodny z kolorem t�a sceny.
    */
    void getBackgroundColor();
    
  public slots:
    /*!
    Slot wywo�ywany w celu odpowiedniego ustawienia widget�w w zale�no�ci od warto�ci w strukturze FogStruct.
    */
    void updateWidgets();
    
  signals:
    /*!
    Sygna� wysy�any przy zmianie kt�regokolwiek z parametr�w mg�y:
    \param fog - struktura mg�y,
    \param whichParamChanged - kt�ry z parametr�w mg�y uleg� zmianie.
    */
    void fogChanged( FogStruct* fog, FogParamsEnum whichParamChanged );
};




#endif
