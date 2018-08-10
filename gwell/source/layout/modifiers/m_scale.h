//////////////////////////////////////////////////////////////////
///
///  class: ScaleModifier (.h)
///
///  klasa modyfikatora skali
///
//////////////////////////////////////////////////////////////////

#ifndef SCALEMODIFIER_H
#define SCALEMODIFIER_H

#include <modifier.h>



class ScaleModifier : public MModifier
{
  Q_OBJECT

  public:
    ScaleModifier(QCursor cursor = 0);
    ~ScaleModifier();
    virtual ModifierType type();

    void mousePressEvent(QMouseEvent *e, qglviewer::Camera *camera, QPtrList<ViMultiPolyh> *selectedList);
    void mouseMoveEvent(QMouseEvent *e, qglviewer::Camera *camera, QString &info);   // w czasie modyfikacji moze byc wcisniety shift, control, alt, itp.
    void mouseReleaseEvent(QMouseEvent *e);

  private:
    const Vector3f scaleElement( ViElemePolyh* elem, const Vector3f& diff, float radius );
    
  signals:
    void vectorChanged(MModifier::ModifierType mType, Vector3f v);    
};



#endif
