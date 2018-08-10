//////////////////////////////////////////////////////////////////
///
///  class: TranslateCoordsModifier (.cpp)
///
///  modyfikator translacji uk³adu wspó³rzêdnych
///
//////////////////////////////////////////////////////////////////

#include "m_transcoords.h"



TranslateCoordsModifier::TranslateCoordsModifier( QCursor cursor ) : MModifier( cursor ) {}



MModifier::ModifierType TranslateCoordsModifier::type()
{
  return M_TRANSLATECOORDS;
}


void TranslateCoordsModifier::mousePressEvent(QMouseEvent *e, qglviewer::Camera *camera, QPtrList<ViNTreeNode> *selectedList)
{
  _selectedList = selectedList;

  camera->computeModelViewMatrix();
  Vec v = camera->unprojectedCoordinatesOf(Vec(e->x(),e->y(), 1.0)); // v we wsp swiata

  _currentPos.Set(v.x, v.y, v.z);
  _currentPos2D = e->pos();
}



  
void TranslateCoordsModifier::mouseMoveEvent(QMouseEvent *e, qglviewer::Camera *camera, QString &info)
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
  ViElemePolyhExt *extEl;
  
  for (ViNTreeNode *_selected = _selectedList->first(); _selected; _selected = _selectedList->next())
  {
    extEl = dynamic_cast<ViElemePolyhExt*>(_selected);
    if ( !extEl ) continue; // tylko obiektom klasy ViElemePolyhExt mo¿na to zrobiæ
    
    //m = extEl->Mtx2IndivCoord();  // aktualna macierz translacji wspó³rzêdnych obiektu

    //m.AddTrans(diff);             // dodanie wyliczonego wektora translacji do aktualnej macierzy transformacji

    //extEl->SetMtx2IndivCoord( m ); // zadanie nowej macierzy transformacji
    extEl->TranslateIndivCoord( diff );
    m = extEl->Mtx2IndivCoord();
  }


  Vector3f v = m.GetTrans_TAfterR();
  info = QString(tr("coords translation: [%1, %2, %3]")).arg(v.x,0,'f',2).arg(v.y,0,'f',2).arg(v.z,0,'f',2);
 
  

  if (e->state() & Qt::ShiftButton) _currentPos += diff;   // jezeli wcisniety SHIFT, koncowa pozycja wyglada inaczej
   else _currentPos.Set(pos);

  _currentPos2D = e->pos();

  emit vectorChanged(type(), v);
}




void TranslateCoordsModifier::mouseReleaseEvent(QMouseEvent*)
{

}
