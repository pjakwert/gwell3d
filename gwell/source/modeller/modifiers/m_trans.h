//////////////////////////////////////////////////////////////////
///
///  class: TranslateModifier (.h)
///
///  modyfikator translacji
///
//////////////////////////////////////////////////////////////////

#ifndef TRANSLATEMODIFIER_H
#define TRANSLATEMODIFIER_H

#include <modifier.h>



class TranslateModifier : public MModifier
{
  Q_OBJECT

  public:
    TranslateModifier(QCursor cursor = 0);
    ~TranslateModifier() {}
    virtual ModifierType type();

    void mousePressEvent(QMouseEvent *e, qglviewer::Camera *camera, QPtrList<ViNTreeNode> *selectedList);
    void mouseMoveEvent(QMouseEvent *e, qglviewer::Camera *camera, QString &info);
    void mouseReleaseEvent(QMouseEvent*);

  signals:
    void vectorChanged(MModifier::ModifierType mType, Vector3f v);    
};





#endif
