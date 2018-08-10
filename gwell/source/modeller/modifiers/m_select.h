///////////////////////////////////////////////////////////////////////
///
///  class: SelectModifier (.h)
///
///  modyfikator selekcji - nie przeciaza metod obslugi zdarzen myszy
///
///////////////////////////////////////////////////////////////////////

#ifndef SELECTMODIFIER_H
#define SELECTMODIFIER_H

#include <modifier.h>



class SelectModifier : public MModifier
{
  Q_OBJECT

  public:
    SelectModifier(QCursor cursor = 0);
    ~SelectModifier();
    virtual ModifierType type();

    void mousePressEvent(QMouseEvent *e, qglviewer::Camera *camera, QPtrList<ViNTreeNode> *selectedList);
    void mouseMoveEvent(QMouseEvent *e, qglviewer::Camera *camera, QString &info);
    void mouseReleaseEvent(QMouseEvent *e);

  signals:
    void vectorChanged(MModifier::ModifierType mType, Vector3f v);    
};


#endif
