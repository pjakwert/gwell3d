//////////////////////////////////////////////////////////////////
///
///  class: RotateModifier (.cpp)
///
///  klasa modyfikatora rotacji
///
//////////////////////////////////////////////////////////////////

#include "m_rot.h"


RotateModifier::RotateModifier(QCursor cursor) : MModifier(cursor) {}


MModifier::ModifierType RotateModifier::type()
{
  return M_ROTATE;
}





void RotateModifier::mousePressEvent(QMouseEvent *e, qglviewer::Camera *camera, QPtrList<ViMultiPolyh> *selectedList)
{
  _selectedList = selectedList;

  //camera->computeModelViewMatrix();
  //Vec v = camera->unprojectedCoordinatesOf(Vec(e->x(),e->y(), 1.0)); // v we wsp swiata

  //_currentPos.Set(v.x, v.y, v.z);
  _currentPos2D = e->pos();
}




void RotateModifier::mouseMoveEvent(QMouseEvent *e, qglviewer::Camera *camera, QString &info)
{
  if (_selectedList->isEmpty()) return;
  

  //camera->computeModelViewMatrix();
  //Vec vw = camera->unprojectedCoordinatesOf(Vec(e->x(),e->y(), 1.0)); // we wsp swiata
  //Vector3f pos(vw.x, vw.y, vw.z); // pozycja we wsp swiata



  //Vector3f diff = pos - _currentPos; // roznica w przesunieciu
  //diff *= PI/camera->sceneRadius();   // odpowiednie skalowanie wektora w zaleznosci od rozpietosci sceny
  QPoint diff = _currentPos2D - e->pos();  

   if (e->state() & Qt::ShiftButton) // wcisniety SHIFT - obrot o wielokrotnosc kata 45 st.
   {
   }

  Vec rot2D( -diff.y(), diff.x(), 0 );
  MatrixH3f rotM;
  rotM.SetAng_XYZ_TAfterR_Deg( rot2D.x, rot2D.y, rot2D.z ); // macierz zadanego obrotu
    
  // zadaj rotacje wszystkim zaznaczonym obiektom
  for (ViMultiPolyh *_selected = _selectedList->first(); _selected; _selected = _selectedList->next())
  {
    // old one
    MatrixH3f m2pc_old = _selected->Mtx2ParentCoord();  // aktualna macierz transformacji obiektu

    MatrixH3f p2g;
    _selected->GetParentNode()->GetMtx2GlbCoord( p2g );
    
    MatrixH3f p2g_inv;
    MatrixH3f m2pc_new; // szukana macierz
    p2g.InvertFrame( p2g_inv );
    
    MatrixH3f c2w;
    const GLdouble *wm = camera->frame()->worldInverseMatrix();
     Vector3f col1_rot( *(wm+0), *(wm+4), *(wm+8) );
     Vector3f col2_rot( *(wm+1), *(wm+5), *(wm+9) );
     Vector3f col3_rot( *(wm+2), *(wm+6), *(wm+10) );
     Vector3f col4_trans( *(wm+3), *(wm+7), *(wm+11) );
     
    c2w.SetMatrix( col1_rot, col2_rot, col3_rot, col4_trans ); // macierz camera->world
    MatrixH3f c2w_inv;
    c2w.InvertFrame( c2w_inv );
    
    m2pc_new = p2g_inv * c2w * rotM * c2w_inv * p2g * m2pc_old;
        
    _selected->SetMtx2ParentCoord( m2pc_new );
  }

  // info
  Vector3f v = _selectedList->last()->Mtx2ParentCoord().GetAng_XYZ_Rad();
  info = QString(tr("rotation: [%1, %2, %3]rad   ")).arg(v.x,0,'f',2).arg(v.y,0,'f',2).arg(v.z,0,'f',2);
  v *= 180.0/PI; // na stopnie
  info += QString("[%1, %2, %3]deg").arg(v.x,0,'f',2).arg(v.y,0,'f',2).arg(v.z,0,'f',2);
  // /info
                
  
  //_currentPos.Set(pos);
  _currentPos2D = e->pos();

  emit vectorChanged(type(), v);  // kat wysylany jest w stopniach
}

      


      
void RotateModifier::mouseReleaseEvent(QMouseEvent *e)
{

}

