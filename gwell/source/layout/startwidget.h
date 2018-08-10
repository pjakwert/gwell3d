#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <qwidget.h>
#include <qpixmap.h>
#include <qpainter.h>

#include <icons.h>

class StartWidget : public QWidget
{
  Q_OBJECT

  public:
    StartWidget(QWidget *parent, const char *name=0, WFlags fl=0);
    ~StartWidget();

  protected:
    virtual void paintEvent(QPaintEvent *e);
    virtual void mousePressEvent(QMouseEvent*e);

  signals:
    void clicked();
};

#endif
