//////////////////////////////////////////////////////////////////
///
///  class: Workspace (.h)
///
///  Zawiera wszystkie (4) okna edycyjne aplikacji ze splitterami
///
//////////////////////////////////////////////////////////////////

#ifndef WORKSPACE_H
#define WORKSPACE_H


#include <qsplitter.h>
#include <qlayout.h>
#include <qptrlist.h>

#include <kernel.h>
#include <cellframe.h>
#include <texturemanager.h>
#include <statusbar.h>


/*!
Klasa reprezentuje ca³y obszar roboczy. Zawiera wszystkie okna edycyjne aplikacji.
*/
class Workspace : public QWidget
{
  Q_OBJECT
  
  public:
    Workspace(QWidget *parent, const char *name = 0, WFlags fl = 0);
    ~Workspace();
    static void resetAllFrames();
    CellFrame* currentFrame();
    void disableCameraInCurrentFrame();
    
  private:
    QGridLayout *grid;
    QSplitter *splitV;
    QSplitter *splitH;
    QSplitter *split3;
    
    static QPtrList<CellFrame> framesList;
    
  private slots:
    void userSelected( QPtrList<ViNTreeNode> *selected ); // wybrane w CellFrame - podaj dalej
    void modifierChangedFromCellFrame( MModifier::ModifierType mType ); // CellFrame zmieni³ modyfikator
    void structureChanged(); // zmieni³a siê postaæ mph CellFrame, np. delete
  
  public slots:
    void setMultiPolyh( ViMultiPolyh *multiPolyh );
    void setLightsList( QPtrList<Light> *lightsList );
    void setLight( Light* light );
    void setLightingEnabled( bool yes );
    void updateLightColor( GLenum, Light* );
    //void showLightShapes( bool );
    
    void setSelected( QPtrList<ViNTreeNode> *selected );  // rozdaj CellFrame-om wybrane obiekty
    void setModifier( MModifier *modifier ); // ustaw CellFrame-om modyfikator
    void refresh();
    
    // ustawienia z globalnego CellWidget dla wszystkich CellFrames
    void setCameraIsMovingForAll( bool yes );
    void showEntireSceneForAll();
    void showGridForAll( bool on );
    void showAxisForAll( bool on );
    void showLightsForAll( bool on );
    void viewDirectionChangedForAll(int direction);
    void setViewTypeForAll( DrawMethod type );
    void setProjTypeForAll( qglviewer::Camera::Type type );
    
  signals:
    void setModifierFromCellFrame( MModifier::ModifierType mType ); // CellFrame zmienia modyfikator
    void userSelectedObject( QPtrList<ViNTreeNode> *selected );
    void mphStructureChanged();
};



#endif
