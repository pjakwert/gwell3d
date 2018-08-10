//////////////////////////////////////////////////////////////////
///
///  class: Modifier (.h)
///
///  klasa abstrakcyjna dla modyfikatorow
///
//////////////////////////////////////////////////////////////////

#ifndef MODIFIER_H
#define MODIFIER_H

#define PI 3.14159265358979

#include <qobject.h>
#include <qcursor.h>
#include <qstring.h>
#include <qptrlist.h>

#include <QGLViewer/qglviewer.h>

#include <kernel.h>

using namespace qglviewer;


class MModifier : public QObject
{
  Q_OBJECT

  public:
    enum ModifierType { M_SELECT = 0, M_TRANSLATE, M_ROTATE, M_SCALE, M_LINK, M_TRANSLIGHTPOS, M_TRANSLIGHTDIR, M_TRANSLATECOORDS, M_ROTATECOORDS };
    
    MModifier( QCursor cursor = QCursor(Qt::ArrowCursor) );
    virtual ~MModifier();
    virtual ModifierType type() = 0;
    QCursor cursor();

    virtual void mousePressEvent( QMouseEvent *e, qglviewer::Camera *camera, QPtrList<ViNTreeNode> *selectedList ) {}
    virtual void mouseMoveEvent( QMouseEvent *e, qglviewer::Camera *camera, QString &info ) {}   // w czasie modyfikacji moze byc wcisniety shift, control, alt, itp.
    virtual void mouseReleaseEvent( QMouseEvent *e ) {}
    

  protected:
    QCursor _cursor; // taki kursor powinien otrzymac caly workspace
    QPtrList<ViNTreeNode> *_selectedList;
    Vector3f _currentPos;
    QPoint _currentPos2D;
};



#endif
