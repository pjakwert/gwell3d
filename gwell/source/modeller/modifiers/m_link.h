//////////////////////////////////////////////////////////////////
///
///  class: LinkModifier (.h)
///
///  klasa modyfikatora laczenia obiektow
///
//////////////////////////////////////////////////////////////////

#ifndef LINKMODIFIER_H
#define LINKMODIFIER_H

#include <qmessagebox.h>

#include <modifier.h>



class LinkModifier : public MModifier
{
  Q_OBJECT

  public:
    LinkModifier(QCursor cursor = 0);
    ~LinkModifier();
    virtual ModifierType type();

    void mousePressEvent(QMouseEvent *e, qglviewer::Camera *camera, QPtrList<ViNTreeNode> *selectedList);
    void mouseMoveEvent(QMouseEvent *e, qglviewer::Camera *camera, QString &info);
    void mouseReleaseEvent(QMouseEvent *e);

  signals:
    void vectorChanged(MModifier::ModifierType mType, Vector3f v);
};




#endif
