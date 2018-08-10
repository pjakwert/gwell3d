#include "startwidget.h"


StartWidget::StartWidget(QWidget *parent, const char *name, WFlags fl) : QWidget(parent,name,fl)
{
  this->setMinimumSize(QSize(40,40));
  this->setMaximumSize(QSize(40,40));

  this->setMask(QRegion(13,13, 16,16 ,QRegion::Ellipse));
}


StartWidget::~StartWidget()
{
}


/*!
Rysowanie ikonki.
*/
void StartWidget::paintEvent(QPaintEvent *e)
{
  QPainter painter(this);
  painter.drawPixmap(12,12,QPixmap(Icons::ballIcon()));
}

/*!
Metoda obs³uguje klikniêcie lewym klawiszem myszy.
*/
void StartWidget::mousePressEvent(QMouseEvent *e)
{
  if (e->button() == LeftButton)
  {
    emit clicked();
  }
}