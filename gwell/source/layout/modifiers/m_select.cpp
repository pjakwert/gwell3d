///////////////////////////////////////////////////////////////////////
///
///  class: SelectModifier (.cpp)
///
///  modyfikator selekcji - nie przeciaza metod obslugi zdarzen myszy
///
///////////////////////////////////////////////////////////////////////

#include "m_select.h"


SelectModifier::SelectModifier(QCursor cursor) : MModifier(cursor) {}
SelectModifier::~SelectModifier() {}

MModifier::ModifierType SelectModifier::type()
{
  return M_SELECT;
}


void SelectModifier::mousePressEvent(QMouseEvent *e, qglviewer::Camera *camera, QPtrList<ViMultiPolyh> *selectedList) {}
void SelectModifier::mouseMoveEvent(QMouseEvent *e, qglviewer::Camera *camera, QString &info) {}
void SelectModifier::mouseReleaseEvent(QMouseEvent *e) {}
