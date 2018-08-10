//////////////////////////////////////////////////////////////////
///
///  class: TranslateLightPosModifier (.cpp)
///
///  modyfikator translacji pozycji ¶wiat³a
///
//////////////////////////////////////////////////////////////////
#include "m_translightpos.h"


TranslateLightPosModifier::TranslateLightPosModifier( QCursor cursor ) : MModifier( cursor )
{ 
  _currentLight = 0L;
}


TranslateLightPosModifier::~TranslateLightPosModifier() {}



MModifier::ModifierType TranslateLightPosModifier::type()
{
  return M_TRANSLIGHTPOS;
}


void TranslateLightPosModifier::mousePressEvent( QMouseEvent *e, qglviewer::Camera *camera, QPtrList<ViNTreeNode> *selectedList )
{
  camera->computeModelViewMatrix();
  Vec v = camera->unprojectedCoordinatesOf( Vec(e->x(),e->y(), 1.0) ); // v we wsp swiata

  _currentPos.Set(v.x, v.y, v.z);
  _currentPos2D = e->pos();
}



  
void TranslateLightPosModifier::mouseMoveEvent( QMouseEvent *e, qglviewer::Camera *camera, QString &info )
{
  if ( !_currentLight ) return;
  if ( _currentLight->lightType() == Light::Directional ) return; // ¶wiate³ek bez ¼róde³ka nie przesuwamy
  
  camera->computeModelViewMatrix();
  Vec vw = camera->unprojectedCoordinatesOf(Vec(e->x(),e->y(), 1.0)); // we wsp swiata
  Vector3f pos(vw.x, vw.y, vw.z);

  Vector3f diff = pos - _currentPos; // roznica w przesunieciu

  
  if (e->state() & Qt::ShiftButton) // jezeli wcisniety SHIFT - zostawiamy tylko najszybciej zmieniajaca sie skladowa
  {
    float maxCoord = QMAX(QMAX(abs(diff.x), abs(diff.y)), abs(diff.z)); // najwieksza roznica - najszybciej zmieniajaca sie skladowa
    if (abs(diff.x) != maxCoord) diff.x = 0.0;
    if (abs(diff.y) != maxCoord) diff.y = 0.0;
    if (abs(diff.z) != maxCoord) diff.z = 0.0;
  }

  
  Vector3f newPos;
  const GLfloat* currPosGL = _currentLight->position4fv();          // aktualna pozycja ¶wiat³a
  newPos.Set( currPosGL[0], currPosGL[1], currPosGL[2] );
    
  newPos+=diff;  // pozycja po dodaniu przesuniêcia
  _currentLight->setPosition( newPos ); // zadanie nowej pozycji

  info = QString(tr("light's position: [%1, %2, %3]")).arg(newPos.x,0,'f',2).arg(newPos.y,0,'f',2).arg(newPos.z,0,'f',2);
 
  

  if (e->state() & Qt::ShiftButton) _currentPos += diff;   // jezeli wcisniety SHIFT, koncowa pozycja wyglada inaczej
   else _currentPos.Set( pos );

  _currentPos2D = e->pos();

  emit vectorChanged( type(), newPos );
}




void TranslateLightPosModifier::mouseReleaseEvent( QMouseEvent* ) {}
