//////////////////////////////////////////////////////////////////
///
///  class: TranslateLightDirModifier (.h)
///
///  modyfikator translacji kierunku ¶wiat³a
///
///  niniejszy modyfikator (podobnie jak TranslateLightPosModifier) dzia³a w nieco odmienny sposób,
///  mianowicie: nie u¿ywaj± wogle listy zaznaczonych obiektów _selectedList, deklaracja ta musi zostaæ
///  zachowana, ¿eby dziedziczyæ po MModifier
///  zamiast tego nale¿y ustawiaæ ¶wiat³o, które bêdzie poddawane modyfikacji,
///  dokonuje siê tego metod± setCurrentLight(Light*) w dowolym momencie dzia³ania modyfikatora
//////////////////////////////////////////////////////////////////
#ifndef TRANSLATELIGHTDIRMODIFIER_H
#define TRANSLATELIGHTDIRMODIFIER_H

#include <modifier.h>
#include <light.h>


class TranslateLightDirModifier : public MModifier
{
  Q_OBJECT
  Light* _currentLight;
      
  public:
    TranslateLightDirModifier( QCursor cursor = 0 );
    ~TranslateLightDirModifier();
    virtual ModifierType type();
    void setCurrentLight( Light* light ) { _currentLight = light; };

    void mousePressEvent( QMouseEvent *e, qglviewer::Camera *camera, QPtrList<ViMultiPolyh> *selectedList);
    void mouseMoveEvent( QMouseEvent *e, qglviewer::Camera *camera, QString &info );
    void mouseReleaseEvent( QMouseEvent* e );

  signals:
    void vectorChanged( MModifier::ModifierType mType, Vector3f v );
};


#endif
