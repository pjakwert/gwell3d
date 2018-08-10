/////////////////////////////////////////////////////////////////
///
///  class: ColorWidget (.cpp)
///
///  widget do edycji koloru
///
//////////////////////////////////////////////////////////////////

#include "colorwidget.h"


ColorWidget::ColorWidget(QWidget *parent, QString title, QColor color, int alpha) : QGroupBox(title,parent)
{
  this->setTitle(title);
  this->setAlignment(Qt::AlignHCenter);

  _color = color;
  _alpha = alpha;

  intValidator = new QIntValidator(0,255, this);

  QFont f;
  f.setFamily(this->font().family());
  f.setPointSize(this->font().pointSize()-3);


// etykiety R G B A
   QLabel *rLabel = new QLabel(tr("R"), this);
    rLabel->setFont(f);
   QLabel *gLabel = new QLabel(tr("G"), this);
    gLabel->setFont(f);
   QLabel *bLabel = new QLabel(tr("B"), this);
    bLabel->setFont(f);
   QLabel *aLabel = new QLabel(tr("A"), this);
    aLabel->setFont(f);


 // ustaw zadane (ewentualnie domyslne) wartosci koloru w sliderach
   rSlide = new QSlider(0,255, 10, 255-_color.red(),   Qt::Vertical, this);
    rSlide->setTickmarks(QSlider::Both);
    rSlide->setTickInterval(20);
    rSlide->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
   gSlide = new QSlider(0,255, 10, 255-_color.green(), Qt::Vertical, this);
    gSlide->setTickmarks(QSlider::Both);
    gSlide->setTickInterval(20);
    gSlide->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
   bSlide = new QSlider(0,255, 10, 255-_color.blue(),  Qt::Vertical, this);
    bSlide->setTickmarks(QSlider::Both);
    bSlide->setTickInterval(20);
    bSlide->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
   aSlide = new QSlider(0,255, 10, 255-_alpha,         Qt::Vertical, this);
    aSlide->setTickmarks(QSlider::Both);
    aSlide->setTickInterval(20);
    aSlide->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);

// edity i validatory
   rEdit = new QLineEdit(QString::number(_color.red()),   this);
    rEdit->setValidator(intValidator);
    rEdit->setFont(f);
    rEdit->setAlignment(Qt::AlignHCenter);
   gEdit = new QLineEdit(QString::number(_color.green()), this);
    gEdit->setValidator(intValidator);
    gEdit->setFont(f);
    gEdit->setAlignment(Qt::AlignHCenter);
   bEdit = new QLineEdit(QString::number(_color.blue()),  this);
    bEdit->setValidator(intValidator);
    bEdit->setFont(f);
    bEdit->setAlignment(Qt::AlignHCenter);
   aEdit = new QLineEdit(QString::number(_alpha),         this);
    aEdit->setValidator(intValidator);
    aEdit->setFont(f);
    aEdit->setAlignment(Qt::AlignHCenter);

// przycisk do wybierania koloru z dialogu
   colorButton = new QToolButton(this);
   colorButton->setTextLabel(tr("Color ..."));
   colorButton->setUsesTextLabel(true);
   colorButton->setPaletteBackgroundColor(_color);     // tlo dla guzika


//////////// polaczenia
    connect(rSlide, SIGNAL(valueChanged(int)), this, SLOT(setColorFromSliders(int)));
    connect(gSlide, SIGNAL(valueChanged(int)), this, SLOT(setColorFromSliders(int)));
    connect(bSlide, SIGNAL(valueChanged(int)), this, SLOT(setColorFromSliders(int)));
    connect(aSlide, SIGNAL(valueChanged(int)), this, SLOT(setAlpha(int)));

    connect(rEdit, SIGNAL(textChanged(const QString&)), this, SLOT(setSlidersFromEdits(const QString&)));
    connect(gEdit, SIGNAL(textChanged(const QString&)), this, SLOT(setSlidersFromEdits(const QString&)));
    connect(bEdit, SIGNAL(textChanged(const QString&)), this, SLOT(setSlidersFromEdits(const QString&)));
    connect(aEdit, SIGNAL(textChanged(const QString&)), this, SLOT(setAlpha(const QString&)));

    connect(colorButton, SIGNAL(clicked()), this, SLOT(openColorDialog()));
//////////// polaczenia


//////// GEOMETRIA

  QGridLayout *grid = new QGridLayout(this, 3,5, 10,5, "mój grid"); //3rows, 5cols
   QSpacerItem *space = new QSpacerItem(5,10, QSizePolicy::Expanding,QSizePolicy::Fixed);
   grid->addMultiCell(space, 0,0, 0,4);

   QHBoxLayout *hBox = new QHBoxLayout(3, "hBox"); // ojciec

   QVBoxLayout *rBox = new QVBoxLayout(hBox, 5, "rBox");
    rBox->addWidget(rLabel, 0,Qt::AlignHCenter);
    rBox->addWidget(rSlide);
    rBox->addWidget(rEdit);
   QVBoxLayout *gBox = new QVBoxLayout(hBox, 5, "gBox");
    gBox->addWidget(gLabel, 0,Qt::AlignHCenter);
    gBox->addWidget(gSlide);
    gBox->addWidget(gEdit);
   QVBoxLayout *bBox = new QVBoxLayout(hBox, 5, "bBox");
    bBox->addWidget(bLabel, 0,Qt::AlignHCenter);
    bBox->addWidget(bSlide);
    bBox->addWidget(bEdit);
   QSpacerItem *spacer = new QSpacerItem(5,5, QSizePolicy::Expanding,QSizePolicy::Maximum);
    hBox->addItem(spacer);
   QVBoxLayout *aBox = new QVBoxLayout(hBox, 5, "aBox");
    aBox->addWidget(aLabel, 0,Qt::AlignHCenter);
    aBox->addWidget(aSlide);
    aBox->addWidget(aEdit);

  grid->addMultiCellLayout(hBox, 1,1, 0,4);

  grid->addMultiCellWidget(colorButton, 2,2, 0,2);

  //this->resize(150,260); // widget ma staly rozmiar
}


ColorWidget::~ColorWidget()
{
}


/*!
Metoda zwraca aktualny kolor.
*/
QColor ColorWidget::color()
{
  return _color;
}

/*!
Metoda zwraca aktualn± przezroczysto¶æ.
*/
int ColorWidget::alpha()
{
  return _alpha;
}

/*!
Metoda wywo³ywana przy zmianie dowolnego suwaka.
Uaktualnia pola edycyjne i wysy³a sygna³ zmiany koloru.
\param int - nie ma znaczenia - zachowany tylko dla kompatybilno¶ci z sygna³em.
*/
void ColorWidget::setColorFromSliders(int)
{
  int sMax = rSlide->maxValue();   // sMax jest po to, ¿eby maksymalna warto¶æ by³a na górze slidera a minimalna na dole
  _color.setRgb(sMax-rSlide->value(), sMax-gSlide->value(), sMax-bSlide->value()); // ustaw odpowiedni kolor

  blockEditSignals(true);
   rEdit->setText(QString::number(_color.red()));      // ustaw lineEdit-om
   gEdit->setText(QString::number(_color.green()));
   bEdit->setText(QString::number(_color.blue()));
  blockEditSignals(false);

  colorButton->setPaletteBackgroundColor(_color);     // tlo dla guzika

  emit colorChanged(_color, _alpha);
}


/*!
Metoda wywo³ywana przy zmianie tekstu w polach edycyjnych.
Uaktualnia wszystkie suwaki i wysy³a sygna³ zmiany koloru.
\param const QString& - nie ma znaczenia, tylko dla kompatybilno¶ci z sygna³em.
*/
void ColorWidget::setSlidersFromEdits(const QString&)
{
  if (rEdit->hasAcceptableInput() &&
      gEdit->hasAcceptableInput() &&
      bEdit->hasAcceptableInput())
  {
    _color.setRgb(rEdit->text().toInt(), gEdit->text().toInt(), bEdit->text().toInt()); // ustaw odpowiedni kolor

    int sMax = rSlide->maxValue();
    blockSliderSignals(true);
     rSlide->setValue(sMax-_color.red());
     gSlide->setValue(sMax-_color.green());
     bSlide->setValue(sMax-_color.blue());
    blockSliderSignals(false);

    colorButton->setPaletteBackgroundColor(_color);     // tlo dla guzika

    emit colorChanged(_color, _alpha);
  }
}


/*!
Metoda aktywowana wpisaniem warto¶ci do pola edycyjnego przezroczysto¶ci. Uaktualnia suwak.
Wysy³a sygna³ o zmianie koloru.
*/
void ColorWidget::setAlpha(const QString& alpha)
{
  if (aEdit->hasAcceptableInput())
  {
    _alpha = aSlide->maxValue() - alpha.toInt();

    aSlide->blockSignals(true);
     aSlide->setValue(_alpha);
    aSlide->blockSignals(false);

    emit colorChanged(_color, _alpha);
  }
}


/*!
Metoda aktywowana zmian± suwaka przezroczysto¶ci. Uaktualnia pole edycyjne.
Wysy³a sygna³ o zmianie koloru.
*/
void ColorWidget::setAlpha(int alpha)
{
  _alpha = aSlide->maxValue() - alpha;

  aEdit->blockSignals(true);
   aEdit->setText(QString::number(_alpha));
  aEdit->blockSignals(false);

  emit colorChanged(_color, _alpha);
}


/*!
Metoda otwiera dialog wyboru koloru i od¶wie¿a suwaki i pola edycyjne po wybraniu.
*/
void ColorWidget::openColorDialog()
{
  QColor newColor = QColorDialog::getColor(_color, this);
  if (newColor.isValid()) setColor(newColor, _alpha); // jezeli user nie strzelil w Cancel
}

/*!
Metoda ustawia nowy kolor i przezroczysto¶æ. Ustawia wszystkie suwaki i pola edycyjne.
*/
void ColorWidget::setColor( const QColor& color, int alpha )
{
  if ( !color.isValid() ) return;

  _color = color;
  _alpha = alpha;

  blockEditSignals(true);
   rEdit->setText(QString::number(_color.red()));      // ustaw lineEdit-om - one przesla sygnaly dalej
   gEdit->setText(QString::number(_color.green()));
   bEdit->setText(QString::number(_color.blue()));
   aEdit->setText(QString::number(_alpha));
  blockEditSignals(false);

  int sMax = rSlide->maxValue();
  blockSliderSignals(true);
   rSlide->setValue(sMax - _color.red());
   gSlide->setValue(sMax - _color.green());
   bSlide->setValue(sMax - _color.blue());
   aSlide->setValue(aSlide->maxValue() - _alpha);
  blockSliderSignals(false);

  colorButton->setPaletteBackgroundColor(_color);     // tlo dla guzika

  emit colorChanged(_color, _alpha);
}

/*!
Metoda ustawia kolor z wektora OpenGL.
*/
void ColorWidget::setColor( const GLfloat* GLcolor4fv )
{
  if ( !GLcolor4fv ) return;
  
  // konwersja na format QColor
  _color.setRgb( (int) ((*GLcolor4fv) * 255.0), (int) ((*(GLcolor4fv+1)) * 255.0), (int) ((*(GLcolor4fv+2)) * 255.0) );
  _alpha = (int) ((*(GLcolor4fv+3)) * 255.0);
  
  // ustawienie widgetów
  blockEditSignals(true);
   rEdit->setText(QString::number(_color.red()));      // ustaw lineEdit-om - one przesla sygnaly dalej
   gEdit->setText(QString::number(_color.green()));
   bEdit->setText(QString::number(_color.blue()));
   aEdit->setText(QString::number(_alpha));
  blockEditSignals(false);

  int sMax = rSlide->maxValue();
  blockSliderSignals(true);
   rSlide->setValue(sMax - _color.red());
   gSlide->setValue(sMax - _color.green());
   bSlide->setValue(sMax - _color.blue());
   aSlide->setValue(aSlide->maxValue() - _alpha);
  blockSliderSignals(false);

  colorButton->setPaletteBackgroundColor(_color);     // tlo dla guzika

  emit colorChanged( _color, _alpha );
}
  

/*!
Metoda blokuje wysy³anie sygna³ów przez pola edycyjne.
\param yes - okre¶la czy zablokowaæ sygna³y, czy nie.
*/
void ColorWidget::blockEditSignals(bool yes)
{
  rEdit->blockSignals(yes);
  gEdit->blockSignals(yes);
  bEdit->blockSignals(yes);
  aEdit->blockSignals(yes);
}

/*!
Metoda blokuje wysy³anie sygna³ów przez suwaki.
\param yes - okre¶la czy zablokowaæ sygna³y, czy nie.
*/
void ColorWidget::blockSliderSignals(bool yes)
{
  rSlide->blockSignals(yes);
  gSlide->blockSignals(yes);
  bSlide->blockSignals(yes);
  aSlide->blockSignals(yes);
}
