//////////////////////////////////////////////////////////////////
///
///  class: ShineWidget (.cpp)
///
///  widget do jasnosci
///
//////////////////////////////////////////////////////////////////


#include "shinewidget.h"


ShineWidget::ShineWidget(QWidget *parent, QString title, int shininess) : QGroupBox(title, parent)
{
  this->setTitle(title);
  this->setAlignment(Qt::AlignHCenter);

  // z konstruktora
  if (shininess >= 0 && shininess <= 128) _shine = shininess; else _shine = 0;

 
  intValidator = new QIntValidator(0,128, this);

 
   QLabel *sLabel = new QLabel(tr("intensity"), this);

   sSlide = new QSlider(0,128, 10, 128-_shine,   Qt::Vertical, this);
    sSlide->setTickmarks(QSlider::Both);
    sSlide->setTickInterval(20);

   sEdit = new QLineEdit(QString::number(_shine),   this);     sEdit->setValidator(intValidator);

   connect(sSlide, SIGNAL(valueChanged(int)), this, SLOT(setShine(int)));
   connect(sEdit, SIGNAL(textChanged(const QString&)), this, SLOT(setShine(const QString&)));


     QFont f;
     f.setFamily(this->font().family());
     f.setPointSize(this->font().pointSize()-2);

/////////// czcionki
     sLabel->setFont(f);
     sEdit->setFont(f);
     sEdit->setAlignment(Qt::AlignHCenter);

//////// GEOMETRIA
    sLabel->setGeometry(30,20,  54,20);
    sSlide->setGeometry(40,42,  26,110);
    sEdit->setGeometry (30,170, 50,25);

  this->setFixedSize(110,210); // widget ma staly rozmiar
}


ShineWidget::~ShineWidget()
{
}

/*!
Metoda zwraca aktualn± warto¶æ po³yskliwo¶ci obiektu.
*/
int ShineWidget::shininess()
{
  return _shine;
}

/*!
Metoda aktywowana wpisaniem warto¶ci do pola edycyjnego.
*/
void ShineWidget::setShine(const QString& shine)
{
  if (sEdit->hasAcceptableInput())
  {
    _shine = shine.toInt();

    sSlide->blockSignals(true);
     sSlide->setValue(sSlide->maxValue() - _shine);
    sSlide->blockSignals(false);

    emit shininessChanged(_shine);
  }
}


/*!
Metoda aktywowana zmian± suwaka.
*/
void ShineWidget::setShine(int shine)
{
  _shine = sSlide->maxValue() - shine;

  sEdit->blockSignals(true);
   sEdit->setText(QString::number(_shine));
  sEdit->blockSignals(false);

  emit shininessChanged(_shine);
}


/*!
Metoda ustawia po³yskliwo¶æ. Ustawia zgodnie z tym równie¿ wszystkie suwaki i pola edycyjne.
*/
void ShineWidget::setShininess(int shininess)
{
  if ((shininess < sSlide->minValue()) || (shininess > sSlide->maxValue())) return;

  _shine = shininess;

  sEdit->blockSignals(true);
   sEdit->setText(QString::number(_shine));
  sEdit->blockSignals(false);

  sSlide->blockSignals(true);
   sSlide->setValue(sSlide->maxValue() - _shine);
  sSlide->blockSignals(false);

  emit shininessChanged(_shine);
}

