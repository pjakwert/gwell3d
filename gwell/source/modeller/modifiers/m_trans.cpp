//////////////////////////////////////////////////////////////////
///
///  class: TranslateModifier (.cpp)
///
///  modyfikator translacji
///
//////////////////////////////////////////////////////////////////

#include "m_trans.h"



TranslateModifier::TranslateModifier(QCursor cursor) : MModifier(cursor) {}



MModifier::ModifierType TranslateModifier::type()
{
  return M_TRANSLATE;
}


void TranslateModifier::mousePressEvent(QMouseEvent *e, qglviewer::Camera *camera, QPtrList<ViNTreeNode> *selectedList)
{
  _selectedList = selectedList;

  camera->computeModelViewMatrix();
  Vec v = camera->unprojectedCoordinatesOf(Vec(e->x(),e->y(), 1.0)); // v we wsp swiata

  _currentPos.Set(v.x, v.y, v.z);
  _currentPos2D = e->pos();
}



  
void TranslateModifier::mouseMoveEvent(QMouseEvent *e, qglviewer::Camera *camera, QString &info)
{
  if (_selectedList->isEmpty()) return;
  
  camera->computeModelViewMatrix();
  Vec vw = camera->unprojectedCoordinatesOf(Vec(e->x(),e->y(), 1.0)); // we wsp swiata
  Vector3f pos(vw.x, vw.y, vw.z);

  Vector3f diff = pos - _currentPos; // roznica w przesunieciu

  
  if (e->state() & Qt::ShiftButton) // jezeli wcisniety SHIFT - przesuwamy po pod³odze (y=0)
  {
    diff.y = 0.0;
  }

  if (e->state() & Qt::AltButton) // jezeli wcisniety ALT - przesuwamy tylko w pionie
  {
    diff.x = 0.0;
    diff.z = 0.0;   
  }


  MatrixH3f m;
 
  for (ViNTreeNode *_selected = _selectedList->first(); _selected; _selected = _selectedList->next())
  {
    m = _selected->Mtx2ParentCoord();  // aktualna macierz transformacji obiektu

    m.AddTrans_TAfterR( diff );             // dodanie wyliczonego wektora translacji do aktualnej macierzy transformacji

    _selected->SetMtx2ParentCoord(m); // zadanie nowej macierzy transformacji
  }


  Vector3f v = m.GetTrans_TAfterR();
  info = QString(tr("translation: [%1, %2, %3]")).arg(v.x,0,'f',2).arg(v.y,0,'f',2).arg(v.z,0,'f',2);
 
  

  if (e->state() & Qt::ShiftButton) _currentPos += diff;   // jezeli wcisniety SHIFT, koncowa pozycja wyglada inaczej
   else _currentPos.Set(pos);

  _currentPos2D = e->pos();

  emit vectorChanged(type(), v);
}




void TranslateModifier::mouseReleaseEvent(QMouseEvent*)
{

}
