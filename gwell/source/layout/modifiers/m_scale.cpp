//////////////////////////////////////////////////////////////////
///
///  class: ScaleModifier (.cpp)
///
///  klasa modyfikatora skali
///
//////////////////////////////////////////////////////////////////

#include "m_scale.h"



ScaleModifier::ScaleModifier(QCursor cursor) : MModifier(cursor) {}


ScaleModifier::~ScaleModifier() {}


MModifier::ModifierType ScaleModifier::type()
{
  return M_SCALE;
}





void ScaleModifier::mousePressEvent(QMouseEvent *e, qglviewer::Camera *camera, QPtrList<ViMultiPolyh> *selectedList)
{
  _selectedList = selectedList;
  
  if (_selectedList->isEmpty()) return;  

  camera->computeModelViewMatrix();
  Vec v = camera->unprojectedCoordinatesOf(Vec(e->x(),e->y(), 1.0)); // wsp swiata

  _currentPos.Set(v.x, v.y, v.z);
  _currentPos2D = e->pos();
}



// ! scaleVector jest dzielony przez maxDim dla proporcjonalnego skalowania !
const Vector3f ScaleModifier::scaleElement( ViElemePolyh* elem, const Vector3f& diff, float radius )
{
  MatrixH3f m = elem->Mtx2ElemeCoord();
  
  Vector3f minVec( elem->GlbOlnBox().Min() );
  Vector3f maxVec( elem->GlbOlnBox().Max() );
  Vector3f elemSize = maxVec-minVec; // wektor rozmiarów obiektu z zastosowan± skal±
    
  const Vector3f currentScale = m.GetScale(); // aktualny wektor skali obiektu

  // wektor pierwotnych rozmiarów obiektu
  Vector3f originalSize( elemSize.x / currentScale.x, elemSize.y / currentScale.y, elemSize.z / currentScale.z );
    
  // najwiêkszy z pierwotnych wymiarów obiektu
  float maxDim = QMAX( abs(originalSize.x), QMAX( abs(originalSize.y), abs(originalSize.z )) );
  
  Vector3f v = diff; ///maxDim;
  m.AddScale_TAfterR( v.x, v.y, v.z );
  
  elem->SetMtx2ElemeCoord( m );
  
  return ( m.GetScale() );
}



void ScaleModifier::mouseMoveEvent(QMouseEvent *e, qglviewer::Camera *camera, QString &info)
{
  if (_selectedList->isEmpty()) return;

  camera->computeModelViewMatrix();
  Vec vw = camera->unprojectedCoordinatesOf( Vec(e->x(),e->y(), 1.0) ); // v we wsp swiata
  Vector3f pos( vw.x, vw.y, vw.z );

  Vector3f diff = pos - _currentPos; // roznica w przesunieciu
  
  //diff /= camera->sceneRadius();
  
  if (e->state() & Qt::ShiftButton) /////////////////// wcisniety Shift - skalowanie proporcjonalne
  {
    float maxScale = QMAX(diff.x, QMAX(diff.y, diff.z));
    float minScale = QMIN(diff.x, QMIN(diff.y, diff.z));

    if (abs(maxScale) > abs(minScale))
    {
     diff.x = maxScale;
     diff.y = maxScale;
     diff.z = maxScale;
    }
    else
    {
     diff.x = minScale;
     diff.y = minScale;
     diff.z = minScale;
    }
  }

  Vector3f out;
  //Vector3f scaleVector = diff * (camera->sceneRadius());

  ViMultiPolyh *mph;
  
  for (ViMultiPolyh *_selected = _selectedList->first(); _selected; _selected = _selectedList->next())
  {
    mph = _selected;
    /*
    for( ViMultiPolyh::VarElemePolyhIter it = mph->VarBegin_ElemePolyh(); it; ++it)
    {
      out = scaleElement( it, diff, camera->sceneRadius() );
    }*/
    MatrixH3f m = mph->Mtx2ParentCoord();
    
    Vector3f minVec = ( mph->GlbOlnBox().Min() );
    Vector3f maxVec = ( mph->GlbOlnBox().Max() );
    Vector3f size = maxVec-minVec;
    const Vector3f currentScale = m.GetScale();
    Vector3f originalSize( size.x / currentScale.x, size.y / currentScale.y, size.z / currentScale.z );
    float maxDim = QMAX( abs(originalSize.x), QMAX( abs(originalSize.y), abs(originalSize.z )) );
    
    m.AddScale_TAfterR( diff/maxDim ); // (camera->sceneRadius()) );
    
    
    
    mph->SetMtx2ParentCoord( m );
    out = m.GetScale();
  }
  // info
  info = QString(tr("scale: [%1, %2, %3]")).arg(out.x,0,'f',2).arg(out.y,0,'f',2).arg(out.z,0,'f',2);
  // /info
      
  _currentPos.Set(pos);
  _currentPos2D = e->pos();

  emit vectorChanged(type(), out);
}




void ScaleModifier::mouseReleaseEvent(QMouseEvent *e)
{

}

