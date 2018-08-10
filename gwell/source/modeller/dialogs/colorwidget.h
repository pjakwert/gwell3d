//////////////////////////////////////////////////////////////////
///
///  class: ColorWidget (.h)
///
///  Widget do edycji koloru
///
//////////////////////////////////////////////////////////////////
#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <qgroupbox.h>
#include <qcolordialog.h>
#include <qlineedit.h>
#include <qslider.h>
#include <qlabel.h>
#include <qtoolbutton.h>
#include <qvalidator.h>
#include <qlayout.h>

#include <GL/gl.h>

/*!
Klasa implementuje widget do zmiany koloru.
*/
class ColorWidget : public QGroupBox
{
  Q_OBJECT

  public:
    ColorWidget(QWidget *parent, QString title, QColor color = QColor(255,255,255), int alpha=255);
    ~ColorWidget();
    QColor color();
    int alpha();

  private:
    QColor  _color;
    int     _alpha;

    QColorDialog *colorDialog;
    QToolButton  *colorButton;    
    QSlider *rSlide; QLineEdit *rEdit;
    QSlider *gSlide; QLineEdit *gEdit;
    QSlider *bSlide; QLineEdit *bEdit;
    QSlider *aSlide; QLineEdit *aEdit;
    QGridLayout *grid;
    QIntValidator *intValidator;
    void blockEditSignals(bool yes);
    void blockSliderSignals(bool yes);

  public slots:
    void setColor( const QColor& color, int alpha=255 );
    void setColor( const GLfloat* GLcolor4fv );

  private slots:
    void setColorFromSliders(int);
    void setSlidersFromEdits(const QString&);    
    void setAlpha(int value);
    void setAlpha(const QString& alpha);
    void openColorDialog();

  signals:
    void colorChanged( const QColor& color, int alpha );
};


#endif
