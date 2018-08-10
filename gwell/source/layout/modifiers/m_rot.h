//////////////////////////////////////////////////////////////////
///
///  class: RotateModifier (.h)
///
///  klasa modyfikatora rotacji
///
//////////////////////////////////////////////////////////////////

#ifndef ROTATEMODIFIER_H
#define ROTATEMODIFIER_H


#include <modifier.h>



class RotateModifier : public MModifier
{
  Q_OBJECT

  public:
    RotateModifier(QCursor cursor = 0);
    ~RotateModifier() {}
    virtual ModifierType type();    

    void mousePressEvent(QMouseEvent *e, qglviewer::Camera *camera, QPtrList<ViMultiPolyh> *selectedList);
    void mouseMoveEvent(QMouseEvent *e, qglviewer::Camera *camera, QString &info);
    void mouseReleaseEvent(QMouseEvent *e);

  signals:
    void vectorChanged(MModifier::ModifierType mType, Vector3f v);  
};




#endif
