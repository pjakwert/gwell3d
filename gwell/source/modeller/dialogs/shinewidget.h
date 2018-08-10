//////////////////////////////////////////////////////////////////
///
///  class: ShineWidget (.h)
///
///  widget do jasnosci
///
//////////////////////////////////////////////////////////////////
#ifndef SHINEWIDGET_H
#define SHINEWIDGET_H

#include <qgroupbox.h>
#include <qlineedit.h>
#include <qslider.h>
#include <qlabel.h>
#include <qvalidator.h>

/*!
Klasa ShineWidget implementuje dialog do zmiany po³yskliwo¶ci obiektu.
*/
class ShineWidget : public QGroupBox
{
  Q_OBJECT

  public:
    ShineWidget(QWidget *parent, QString title, int shininess=0);
    ~ShineWidget();
    int shininess();

  private:
    int     _shine;

    QSlider *sSlide;
    QLineEdit *sEdit;
    QIntValidator *intValidator;

  public slots:
    void setShininess(int shininess);

  private slots:
    void setShine(int unused);
    void setShine(const QString& unused);

  signals:
    void shininessChanged(int shininess);
};


#endif
