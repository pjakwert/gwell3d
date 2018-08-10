#ifndef GLMENUITEM_H
#define GLMENUITEM_H

#include <qtooltip.h>
#include <qcolor.h>

#include <QGLViewer/qglviewer.h>
#include <kernel.h>
#include <options.h>


class GLMenuItem : public QGLViewer
{
  Q_OBJECT

  public:
    GLMenuItem( QWidget *parent, ViPattePolyh const *pPaPolyh, const char *name = 0, QGLWidget *shareWidget=0, WFlags f = 0 );
    ~GLMenuItem();

  private:
    ViPattePolyh const  *_pPaPolyh;
    int _angle;
    
    static QColor _clearColor;
    static QColor _normalColor;
    static QColor _overColor;
    static QColor _clickColor;
    QColor _currentColor; // obiekt pomocniczy - kolor s³u¿±cy do rysowania w danej chwili
    
    void fitItemToScreen();
    
  protected:
    virtual void init();
    virtual void draw();
    virtual void animate();
    virtual void enterEvent(QEvent*);
    virtual void leaveEvent(QEvent*);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void wheelEvent(QWheelEvent *e);
    virtual void resizeEvent(QResizeEvent *e);

  signals:
    void objectSelected(const char *objectName);

  public slots:
    static void setNormalColor( const QColor& color );
    static void setOverColor  ( const QColor& color );
    static void setClickColor ( const QColor& color );
    static void setClearColor ( const QColor& color );
    void setPattePolyh ( ViPattePolyh const *pPaPolyh);
};


#endif
