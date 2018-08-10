/////////////////////////////////////////////////////////////////////
///
///  class: RotateCoordsModifier (.cpp)
///
///  klasa modyfikatora rotacji indywidualnego uk³adu wspó³rzêdnych
///
/////////////////////////////////////////////////////////////////////
#include "m_rotcoords.h"


RotateCoordsModifier::RotateCoordsModifier(QCursor cursor) : MModifier(cursor) {}


MModifier::ModifierType RotateCoordsModifier::type()
{
  return M_ROTATECOORDS;
}





void RotateCoordsModifier::mousePressEvent(QMouseEvent *e, qglviewer::Camera *camera, QPtrList<ViNTreeNode> *selectedList)
{
  _selectedList = selectedList;

  camera->computeModelViewMatrix();
  Vec v = camera->unprojectedCoordinatesOf(Vec(e->x(),e->y(), 1.0)); // v we wsp swiata

  _currentPos.Set(v.x, v.y, v.z);
  _currentPos2D = e->pos();
}




void RotateCoordsModifier::mouseMoveEvent(QMouseEvent *e, qglviewer::Camera *camera, QString &info)
{
  if (_selectedList->isEmpty()) return;
  

  camera->computeModelViewMatrix();
  Vec vw = camera->unprojectedCoordinatesOf(Vec(e->x(),e->y(), 1.0)); // we wsp swiata
  Vector3f pos(vw.x, vw.y, vw.z); // pozycja we wsp swiata


  Vector3f diff = pos - _currentPos; // roznica w przesunieciu
  diff *= PI/camera->sceneRadius();   // odpowiednie skalowanie wektora w zaleznosci od rozpietosci sceny  

   if (e->state() & Qt::ShiftButton) // wcisniety SHIFT - obrot o wielokrotnosc kata 45 st.
   {
   }

  MatrixH3f m;   
  ViElemePolyhExt *extEl;
  // zadaj rotacjê uk³adu wspó³rzêdnych wszystkim zaznaczonym obiektom
  for (ViNTreeNode *_selected = _selectedList->first(); _selected; _selected = _selectedList->next())
  {
    extEl = dynamic_cast<ViElemePolyhExt*>(_selected);
    if ( !extEl ) continue;
    
    // old one
    m = extEl->Mtx2IndivCoord();  // aktualna macierz transformacji obiektu

    //m.AddRotAngX_Rad(-diff.y);  // ruch wzdluz osi OY powoduje obrot wokol osi 0X zgodnie z ruchem myszy
    //m.AddRotAngY_Rad(diff.x);   // ruch wzdluz osi OX powoduje obrot wokol osi 0Y
    //m.AddRotAngZ_Rad(diff.z);
    
    m.AddAng_XYZ_TAfterR_Rad( -diff.y, diff.x, diff.z );
    
    extEl->SetMtx2IndivCoord( m );
  }

  // info
  Vector3f v = extEl->Mtx2IndivCoord().GetAng_XYZ_Rad();
  info = QString(tr("coords rotation: [%1, %2, %3]rad  ")).arg(v.x,0,'f',2).arg(v.y,0,'f',2).arg(v.z,0,'f',2);
  v *= 180.0/PI; // na stopnie
  info += QString("[%1, %2, %3]deg").arg(v.x,0,'f',2).arg(v.y,0,'f',2).arg(v.z,0,'f',2);
  // /info
                
  
  _currentPos.Set(pos);
  _currentPos2D = e->pos();

  emit vectorChanged(type(), v);  // kat wysylany jest w stopniach
}

      


      
void RotateCoordsModifier::mouseReleaseEvent(QMouseEvent*) {}

