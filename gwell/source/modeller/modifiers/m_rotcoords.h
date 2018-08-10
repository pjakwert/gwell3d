/////////////////////////////////////////////////////////////////////
///
///  class: RotateCoordsModifier (.h)
///
///  klasa modyfikatora rotacji indywidualnego uk³adu wspó³rzêdnych
///
/////////////////////////////////////////////////////////////////////

#ifndef ROTATECOORDSMODIFIER_H
#define ROTATECOORDSMODIFIER_H


#include <modifier.h>



class RotateCoordsModifier : public MModifier
{
  Q_OBJECT

  public:
    RotateCoordsModifier(QCursor cursor = 0);
    ~RotateCoordsModifier() {}
    virtual ModifierType type();    

    void mousePressEvent(QMouseEvent *e, qglviewer::Camera *camera, QPtrList<ViNTreeNode> *selectedList);
    void mouseMoveEvent(QMouseEvent *e, qglviewer::Camera *camera, QString &info);
    void mouseReleaseEvent(QMouseEvent*);

  signals:
    void vectorChanged(MModifier::ModifierType mType, Vector3f v);  
};




#endif
