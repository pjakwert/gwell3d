//////////////////////////////////////////////////////////////////
///
///  class: TranslateCoordsModifier (.h)
///
///  modyfikator translacji uk³adu wspó³rzêdnych
///
//////////////////////////////////////////////////////////////////

#ifndef TRANSLATECOORDSMODIFIER_H
#define TRANSLATECOORDSMODIFIER_H

#include <modifier.h>


class TranslateCoordsModifier : public MModifier
{
  Q_OBJECT

  public:
    TranslateCoordsModifier( QCursor cursor = 0 );
    ~TranslateCoordsModifier() {}
    virtual ModifierType type();

    void mousePressEvent(QMouseEvent *e, qglviewer::Camera *camera, QPtrList<ViNTreeNode> *selectedList);
    void mouseMoveEvent(QMouseEvent *e, qglviewer::Camera *camera, QString &info);
    void mouseReleaseEvent(QMouseEvent*);

  signals:
    void vectorChanged( MModifier::ModifierType mType, Vector3f v );    
};





#endif
