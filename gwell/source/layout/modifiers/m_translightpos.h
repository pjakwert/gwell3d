//////////////////////////////////////////////////////////////////////////////////////////////////////
///
///  class: TranslateLightPosModifier (.h)
///
///  modyfikator translacji pozycji ¶wiat³a
///
///  niniejszy modyfikator (podobnie jak TranslateLightDirModifier) dzia³a w nieco odmienny sposób,
///  mianowicie: nie u¿ywaj± wogle listy zaznaczonych obiektów _selectedList, deklaracja ta musi zostaæ
///  zachowana, ¿eby dziedziczyæ po MModifier
///  zamiast tego nale¿y ustawiaæ ¶wiat³o, które bêdzie poddawane modyfikacji,
///  dokonuje siê tego metod± setCurrentLight(Light*) w dowolym momencie dzia³ania modyfikatora
//////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef TRANSLATELIGHTPOSMODIFIER_H
#define TRANSLATELIGHTPOSMODIFIER_H

#include <modifier.h>
#include <light.h>

class TranslateLightPosModifier : public MModifier
{
  Q_OBJECT

  Light* _currentLight;
      
  public:
    TranslateLightPosModifier( QCursor cursor = 0 );
    ~TranslateLightPosModifier();
    virtual ModifierType type();
    void setCurrentLight( Light* light ) { _currentLight = light; };

    void mousePressEvent( QMouseEvent *e, qglviewer::Camera *camera, QPtrList<ViMultiPolyh> *selectedList);
    void mouseMoveEvent( QMouseEvent *e, qglviewer::Camera *camera, QString &info );
    void mouseReleaseEvent( QMouseEvent *e );

  signals:
    void vectorChanged( MModifier::ModifierType mType, Vector3f v );
};


#endif
