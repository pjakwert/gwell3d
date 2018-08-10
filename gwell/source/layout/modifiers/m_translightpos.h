//////////////////////////////////////////////////////////////////////////////////////////////////////
///
///  class: TranslateLightPosModifier (.h)
///
///  modyfikator translacji pozycji �wiat�a
///
///  niniejszy modyfikator (podobnie jak TranslateLightDirModifier) dzia�a w nieco odmienny spos�b,
///  mianowicie: nie u�ywaj� wogle listy zaznaczonych obiekt�w _selectedList, deklaracja ta musi zosta�
///  zachowana, �eby dziedziczy� po MModifier
///  zamiast tego nale�y ustawia� �wiat�o, kt�re b�dzie poddawane modyfikacji,
///  dokonuje si� tego metod� setCurrentLight(Light*) w dowolym momencie dzia�ania modyfikatora
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
