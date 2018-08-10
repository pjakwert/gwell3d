//////////////////////////////////////////////////////////////////
///
///  class: TranslateLightDirModifier (.cpp)
///
///  modyfikator translacji kierunku ¶wiat³a
///
//////////////////////////////////////////////////////////////////
#include "m_translightdir.h"


TranslateLightDirModifier::TranslateLightDirModifier( QCursor cursor ) : MModifier( cursor )
{
  _currentLight = 0L;
}


TranslateLightDirModifier::~TranslateLightDirModifier() {}



MModifier::ModifierType TranslateLightDirModifier::type()
{
  return M_TRANSLIGHTDIR;
}


void TranslateLightDirModifier::mousePressEvent( QMouseEvent *e, qglviewer::Camera *camera, QPtrList<ViMultiPolyh> *selectedList )
{
  camera->computeModelViewMatrix();
  Vec v = camera->unprojectedCoordinatesOf( Vec(e->x(),e->y(), 1.0) ); // v we wsp swiata

  _currentPos.Set(v.x, v.y, v.z);
  _currentPos2D = e->pos();
}



  
void TranslateLightDirModifier::mouseMoveEvent( QMouseEvent *e, qglviewer::Camera *camera, QString &info )
{
  if ( !_currentLight ) return;
  if ( !_currentLight->isSpotlight() ) return; // ¿aróweczkom kierunku nie zmieniamy
  
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

  
  Vector3f newDir;
  const GLfloat* currDirGL = _currentLight->spotDirection3fv();          // aktualny kierunek ¶wiat³a
  newDir.Set( currDirGL[0], currDirGL[1], currDirGL[2] );
  
  diff /= camera->sceneRadius();
  
  newDir+=diff;  // kierunek po dodaniu przesuniêcia
  _currentLight->setSpotDirection( newDir ); // zadanie nowego kierunku

  info = QString(tr("light's direction: [%1, %2, %3]")).arg(newDir.x,0,'f',2).arg(newDir.y,0,'f',2).arg(newDir.z,0,'f',2);
 

  if (e->state() & Qt::ShiftButton) _currentPos += diff;   // jezeli wcisniety SHIFT, koncowa pozycja wyglada inaczej
   else _currentPos.Set( pos );

  _currentPos2D = e->pos();

  emit vectorChanged( type(), newDir );
}




void TranslateLightDirModifier::mouseReleaseEvent( QMouseEvent* ) {}
